/*
 * @OSF_FREE_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1992, 1991, 1990  
 * Open Software Foundation, Inc. 
 *  
 * Permission is hereby granted to use, copy, modify and freely distribute 
 * the software in this file and its documentation for any purpose without 
 * fee, provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation.  Further, provided that the name of Open 
 * Software Foundation, Inc. ("OSF") not be used in advertising or 
 * publicity pertaining to distribution of the software without prior 
 * written permission from OSF.  OSF makes no representations about the 
 * suitability of this software for any purpose.  It is provided "as is" 
 * without express or implied warranty. 
 */
/*
 * HISTORY
 * $Log: afscode.c,v $
 * Revision 1.2.2.2  1992/12/03  17:27:09  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:11:33  damon]
 *
 * Revision 1.2  1991/12/05  21:18:38  devrcs
 * 	Initial AFS files
 * 	[1991/11/18  17:22:24  damon]
 * 
 * $EndLog$
 */
#if !defined(lint) && !defined(_NOIDENT)
static char rcsid[] = "@(#)$RCSfile: afscode.c,v $ $Revision: 1.2.2.2 $ (OSF) $Date: 1992/12/03 17:27:09 $";
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#include <stdio.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/errno.h>
#ifdef INC_SELECT
#include <sys/select.h>
#endif
#include <varargs.h>
#include <pwd.h>

char *prog = "afscode";
char userbuf[128] = "USER=";
char *nenviron[] = {
    "PATH=:/usr/ucb:/bin:/usr/bin",
    userbuf,
    NULL
};

int i;
int errdesc;

extern char **environ;
extern int errno;
extern char *inet_ntoa();

extern char *rindex();
extern char *nxtarg();
extern char *malloc();
extern char *salloc();
extern char *concat();

char *progname;

#define MAXARGC	64

#define	SERVICE	"afscall"


#define ANAME_SZ	32

#define SEND_OVER	1
#define WANT_BACK	2
char tempdir[MAXPATHLEN];
char temppath[MAXPATHLEN];
char *tempfile;

char args[NCARGS];
char *av[MAXARGC];
char **arglist;
char cmdbuf[BUFSIZ];

char *sandboxdir;
char *BCSTEMP;			/* R */
char bcstempbuf[MAXPATHLEN];	/* buffer for generated BCSTEMP */
char *USER;			/* R */

int exit_status;

int debug;

/*ARGSUSED*/

afscode (basedir, owner, tempmode, tempslot, ldebug, argc, argv)
char *basedir;
char *owner;
int tempmode;
int tempslot;
int ldebug;
int argc;
char *argv[];

{
  errdesc = 1;
  debug = ldebug;
  if (debug)
    {
      diag("afscode:basedir is %s", basedir);
      diag("afscode:owner is %s", owner);
      diag("afscode:tempmode is %d", tempmode);
      diag("afscode:tempslot is %d", tempslot);
      diag("afscode:argc is %d", argc);
      for (i = 0; i <= argc; i++)
	diag("argv[%d] is %s", i, argv[i]);
    }

  /*
   * set some environment variables
   */

  setup();

  /*
   * read argument list for command
   */
  read_arglist(basedir, owner, tempslot, argc, argv);

  /*
   * check configuration
   */

  check_config(basedir, owner, tempslot, debug, argc, argv);
  
  /*
   * receive data file
   */

  if (tempslot != 0)
    copy_file(tempmode);

  /*
   * execute command
   */
  run_command();

  /* 
   * copy file back
   */

  if (tempslot != 0)
    copy_file_back(tempmode);

  /*
   * that is all
   */
  exit(exit_status);
}


setup()
{
  char *getenv();

  /*
   * BCSTEMP - temporary directory for bcs commands
   */

  BCSTEMP = getenv("BCSTEMP");
  if (BCSTEMP == NULL) {
    (void) concat(bcstempbuf, sizeof(bcstempbuf),
		  "/tmp/b-", USER, NULL);
    BCSTEMP = bcstempbuf;
    if (setenv("BCSTEMP", BCSTEMP, TRUE) < 0)
      fatal("BCSTEMP setenv failed");
    BCSTEMP = getenv("BCSTEMP");
    if (BCSTEMP == NULL)
      fatal("BCSTEMP not defined");
  }
  if (debug)
    diag("afscode:setup:bcstemp is %s", BCSTEMP);
}

read_arglist (basedir, owner, slot, argc, argv)
char *basedir;
char *owner;
int slot;
int argc;
char *argv[];
{
  char *p;
  int count = argc + 2;
  
  /* 
    Some clues in this treasure hunt!
    Roughly chronological order of assignments from top to bottom.
    
	---------------------------------------------------------
	| basedir | owner | 	 |	|	|	|	|
	---------------------------------------------------------
	^	  ^	  ^	 ^			^
			  argv[0]argv[1]	...	argv[argc]
	av[0]     av[1]   av[2]	 av[3]			av[argc+2]
	arglist			 arglist[slot+2]
				 tempfile

	
     Notice the pointer to tempfile travelling around:
	
     e.g.	/afs/ri/user/chantal/sb/authors/balzac.c
                ^
		tempfile
		                                ^
						p
						arglist[slot+2]
						tempfile

      Now temppath is somewhere particular in space:
	-------------------
	|		...
	--------------------
	^
	temppath
	arglist[slot+2]

      And arglist[slot+2] is set up to point here and will later be filled
      in opentemp(tempdir, tempfile, temppath) so that arglist will sneakily
      be filled for passing on to runv!
  */

  if (debug)
    diag ("in read_arglist");
  av[0] = basedir;
  av[1] = owner;

  av[count] = NULL;
  for (i = 0; i <= argc; i++)
    av[i + 2] = argv[i];
  arglist = av;

  if (slot != 0) {
    tempfile = arglist[slot+2];
    if ((p = rindex(tempfile, '/')) != NULL)
      p++;
    else
      p = tempfile;
    arglist[slot+2] = salloc(p);

    tempfile = arglist[slot+2];
    arglist[slot+2] = temppath;
    if (debug)
      diag("afscode:read_arglist:tempfile is %s", tempfile);
  }
}

check_config (basedir, owner, tempslot, debug, argc, argv)
char *basedir;
char *owner;
int tempslot;
int debug;
int argc;
char **argv;
{
    char buf[BUFSIZ];
    char aclfile[BUFSIZ];
    char *tree_base;
    char *tree_owner;
    char *cmd;
    char *p;
    char *q;
    FILE *fp;
    int cmdfound;
    char config[MAXPATHLEN];
    struct stat st;
    struct passwd *pw;

    if (debug)
	diag("checking config");
    tree_base = *arglist++;
    if (debug)
      diag("afscode:check_config:tree_base %s", tree_base);
    (void) concat(config, sizeof(config), tree_base, "/kxct.conf", NULL);

    if (debug)
      diag("config file %s", config);
    if (lstat(config, &st) < 0 || (st.st_mode&S_IFMT) != S_IFREG) {
	sprintf(buf, "Invalid kxct config: %s\n", config);
	fatal(buf);
    }
    if (debug)
	diag("config mode ok");
    tree_owner = *arglist++;
    if ((pw = getpwnam(tree_owner)) == NULL)
	fatal("Owner of directory not found");
    if (pw->pw_uid != st.st_uid)
	fatal("Invalid kxct config owner");
    if (st.st_uid == 0)
	fatal("Invalid kxct config owner root");
    if (debug)
	diag("config ownership ok");
    if (chdir(tree_base) < 0)
	efatal("chdir");
    if (debug)
	diag("setuid/chdir ok");
    cmd = *arglist;
    if ((fp = fopen(config, "r")) == NULL)
	efatal("config fopen");
    cmdfound = FALSE;
    while ((p = fgets(buf, sizeof(buf), fp)) != NULL) {
      if ((q  = rindex(p, '\n')) != NULL)
	*q = '\0';
      q = nxtarg(&p, " \t");
      if (strcmp(q, "command") == 0) {
	if (cmdfound)
	  continue;
	q = nxtarg(&p, " \t");
	if (strcmp(q, cmd) != 0)
	  continue;
	q = nxtarg(&p, " \t");
	(void) strcpy(cmdbuf, q);
	q = nxtarg(&p, " \t");
	(void) strcpy(aclfile, q);
	q = nxtarg(&p, " \t");
	if (*q == '\0')
	  q = "/tmp/#kxctdXXXXXX";
	(void) strcpy(tempdir, q);
	cmdfound = TRUE;
	continue;
      }
    }
    (void) fclose(fp);
    if (!cmdfound)
	fatal("command not found");
    if (debug)
	diag("command %s acl %s temp ***%s***", cmdbuf, aclfile, tempdir);
}

/* 
 * yes, this is dumb, but I'm just copying kxct and kxctd right now
 * rather than thinking what should really happen.
 */

copy_file(tempmode)
     int tempmode;
{
  u_long count;
  u_short perm;
  char *buffer;
  int bufsize;
  int len, len2;
  int c;
  char file[MAXPATHLEN];
  struct stat st;
  char exists;
  char *getenv();
  int error;
  int fd, from;
  
  struct stat statbuf;
  char *getwd();
  char pathname[MAXPATHLEN];

  getwd(pathname);
  if (debug)
    diag("afscode:copy_file:pathname is %s", pathname);

  if (tempmode == 1)
    {
      if ((sandboxdir = getenv("SOURCEBASE")) == NULL)
	if ((sandboxdir = getenv ("BACKED_SOURCEDIR")) == NULL)
	  quit (1, "%s: no SOURCEBASE in environment\n", prog);
      diag("afscode:copy_file: tempmode = 1");
      diag("afscode:copy_file: sandboxdir %s", sandboxdir);
      (void) concat(file, MAXPATHLEN, sandboxdir, "/", tempfile, NULL);
    }
  else
    {
      diag("afscode:copy_file: else");
      (void) concat(file, sizeof(file),	BCSTEMP, "/", tempfile, NULL);
    }

  if (debug)
    diag("afscode:copy_file:file is %s", file);

  /*
   * lstat
   */

  if (lstat(file, &st) < 0) {
    if (debug)
      diag("afscode:copy_file:lstat error");
    if (errno != ENOENT) {
      if (debug)
	diag("afscode:copy_file:lstat noent");
      fprintf(stderr, "lstat %s: %s\n", tempfile, errmsg(-1));
      return(-1);
    }
    if (debug)
      diag("does not exist but has not returned");
    if ((tempmode&SEND_OVER) == 0)
      {
	if (debug)
	  diag("afscode:copy_file: not sure what to do here");
      }
    exists = 0;
    perm = 0600;
    count = 0;
  } else {
    if ((tempmode&SEND_OVER) == 0) {
      fprintf(stderr, "file %s exists and would be overwritten\n", tempfile);
      return(-1);
    }
    if ((st.st_mode&S_IFMT) != S_IFREG) {
      fprintf(stderr, "%s not a regular file\n");
      return(-1);
    }
    exists = 1;
    count = st.st_size;
    perm = st.st_mode&0777;
  }
  if (debug)
    {
      diag("afscode:copy_file:exists %d", exists);
      diag("afscode:copy_file:333333perm %#o", perm);
    }

  /*
   * open temporary file
   */

  if ((fd = opentemp(tempdir, tempfile, temppath)) == NULL)
    efatal("opentemp failed");
  if (debug)
    {
      diag("afscode:copy_file:temppath is %s", temppath);
      diag("afscode:copy_file:tempdir is %s", tempdir);
      diag("afscode:copy_file:about to chmode");
    }

  if (chmod(temppath, (int)(perm&0777)) < 0)
    {
      if (debug)
	diag("afscode:copy_file:chmod failed");
      efatal("chmod failed");
    }
  
  if (debug)
    {
      lstat(temppath, &statbuf);
      diag("afscode:copy_file:statbuf.st_mode %#o", statbuf.st_mode);
      diag("afscode:copy_file:chmoded already");
    }
  if (!exists)
    {
      (void) unlink(temppath);
      return(0);
    }
  if (debug)
    diag("afscode:copy_file:exists");
  if (count == 0) {
    return(0);
  }
  if (debug)
    diag("afscode:copy_file:will copy file");

  /*
   * copy file
   */

  if ((from = open(file, O_RDONLY, 0)) < 0)
    {
      (void) unlink(file);
      (void) rmdir(tempdir);
      if (debug)
	diag("afscode:copy_file:open failed");
      efatal("open failed");
    }
  
  /*
   * copy file
   */

    if ((bufsize = count) > 10*1024)
	buffer = malloc(bufsize = 10*1024);
    else
	buffer = malloc(bufsize);
    if (buffer == NULL) {
	fprintf(stderr, "malloc failed\n");
	(void) close(fd);
	return(-1);
    }
    if (debug) {
	fprintf(stderr, "client: bufsize %d\n", bufsize); fflush(stderr);
    }
    while (count != 0) {
	if (debug) {
	    fprintf(stderr, "loop count %d\n", count); fflush(stderr);
	}
	if ((len = read(from, buffer, bufsize)) <= 0) {
	    if (len == 0)
		fprintf(stderr, "premature EOF\n");
	    else
		fprintf(stderr, "afscode:copy_file: %s\n", errmsg(-1));
	    (void) close(fd);
	    return(-1);
	}
	if (debug) {
	    fprintf(stderr, "afscode:copy_file:read %d bytes\n", len);
	}
	if ((len2 = write(fd, buffer, len)) != len) {
	    fprintf(stderr, "write: %s\n", errmsg(-1));
	    (void) close(fd);
	    return(-1);
	}
	if (debug) {
	    fprintf(stderr, "afscode:copy_file: wrote %d bytes\n", len2); 
	    fflush(stderr);
	}
	count -= len;
	if (count < bufsize)
	    bufsize = count;
    }

  if (close(fd) < 0)
    {
      error = errno;
      (void) unlink(file);
      (void) unlink(tempdir);
      errno = error;
      if (debug)
	diag("afscode:copy_file:close");
      efatal("close");
    }
}

run_command()
{
  int i;

  char *pathname;
  char *getenv();

  if (debug)
    diag("command started");
  (void) strcpy(userbuf+sizeof("USER=")-1, getenv("USER")); 
  environ = nenviron;
  if (debug)
    {
      diag ("afscode:run_command:command is %s", cmdbuf);
      for (i = 0; i < 10; i ++)
	diag ("afscode:run_command:arglist[%d] is %s", i, arglist[i]);
    }
  exit_status = runv(cmdbuf, arglist);
  if (debug)
    diag("afscode:command finished status %d", exit_status);
}

copy_file_back(tempmode)
     int tempmode;
{
  struct stat st;
  u_long count;
  u_short perm;
  char *buffer;
  int bufsize;
  int len, len2;
  int error;
  char exists;
  int c;
  char temp_working_file[MAXPATHLEN];
  int writeto, readfrom;

  struct stat statbuf;

  if (debug) 
    diag ("in copy_file_back");
  
  if (debug)
    {
      diag("afscode:copy_file_back:tempfile is %s", tempfile);
      diag("afscode:copy_file_back:tempmode is %d", tempmode);
    }

  /* 
   * do we send the data back at all?
   */

  if (debug)
    diag("sending data");
  if ((tempmode&WANT_BACK) == 0) {
    (void) unlink(temppath);
    if (debug)
      diag("afscode:copy:removing dir1: %s", tempdir);
    (void) rmdir(tempdir);
    if (debug)
      diag("not wanted back");
    return(0);
  }

  /*
   * does the file exist?
   */

  if (lstat(temppath, &st) < 0) {
    if (errno != ENOENT) {
      error = errno;
      (void) unlink(temppath);
      if (debug)
	diag("afscode:copy:removing dir2: %s", tempdir);
      (void) rmdir(tempdir);
      errno = error;
      efatal("lstat", error);
    }
    exists = 0;
    (void) unlink(temppath);
    if (debug)
      diag("afscode:copy:removing dir3: %s", tempdir);
    (void) rmdir(tempdir);
    return(0);
  } else {
    if ((st.st_mode&S_IFMT) != S_IFREG) {
      (void) unlink(temppath);
      if (debug)
	diag("afscode:copy:removing dir4: %s", tempdir);
      (void) rmdir(tempdir);
      fatal("temppath no longer a regular file");
    }
    exists = 1;
  }
  if (debug)
    diag("exists %d", exists);

  perm = st.st_mode&0777;
  if (debug)
    diag("afscode:copy_file_back:perm %#o", perm);
  count = st.st_size;
  
  /*
   * open "write to" file
   */

  (void) concat(temp_working_file, sizeof(temp_working_file),
		BCSTEMP, "/", tempfile, NULL);
  if (debug)
    {
      diag("afscode:copy_file_back:temp_working_file is %s", 
	   temp_working_file);
      diag("afscode:copy_file_back:temppath is %s", temppath);
    }

  (void) chmod(temp_working_file, (int)((perm&0777)|0200));
  if (debug)
    {
      lstat(temp_working_file, &statbuf);
      diag("afscode:copy_file_back:mode is %#o", statbuf.st_mode);
    }
  if ((writeto = open(temp_working_file, 
		      O_WRONLY|O_TRUNC|O_CREAT, 0600)) < 0) {
    fprintf(stderr, "open failed: %s\n", errmsg(-1));
    return(-1);
  }
  if (debug)
    {
      lstat(temp_working_file, &statbuf);
      diag("afscode:copy_file_back:mode is %#o", statbuf.st_mode);
    }
  if (fchmod(writeto, (int)(perm&0777)) < 0) {
    fprintf(stderr, "fchmod failed: %s\n", errmsg(-1));
    return(-1);
  }
  if (debug)
    {
      lstat(temp_working_file, &statbuf);
      diag("afscode:copy_file_back:mode is %#o", statbuf.st_mode);
    }

  if (count == 0) {
    (void) close(writeto);
    (void) unlink(temppath);
    if (debug)
      diag("afscode:copy:removing dir5: %s", tempdir);
    (void) rmdir(tempdir);
    return(0);
  }

  /*
   * open "read from" file
   */

  if ((readfrom = open(temppath, O_RDONLY, 0)) < 0) {
	(void) unlink(temppath);
	if (debug)
	  diag("afscode:copy:removing dir6: %s", tempdir);
	(void) rmdir(tempdir);
	efatal("open failed");
    }
  
  /*
   * copy file
   */

    if ((bufsize = count) > 10*1024)
	buffer = malloc(bufsize = 10*1024);
    else
	buffer = malloc(bufsize);
    if (buffer == NULL) {
	fprintf(stderr, "malloc failed\n");
	(void) close(writeto);
	return(-1);
    }
    if (debug) {
	fprintf(stderr, "client: bufsize %d\n", bufsize); fflush(stderr);
    }
    while (count != 0) {
	if (debug) {
	    fprintf(stderr, "client: loop count %d\n", count); fflush(stderr);
	}
	if ((len = read(readfrom, buffer, bufsize)) <= 0) {
	    if (len == 0)
		fprintf(stderr, "premature EOF\n");
	    else
		fprintf(stderr, "client read4: %s\n", errmsg(-1));
	    (void) close(writeto);
	    return(-1);
	}
	if (debug) {
	    fprintf(stderr, "client: read %d bytes\n", len);
	}
	if ((len2 = write(writeto, buffer, len)) != len) {
	    fprintf(stderr, "write: %s\n", errmsg(-1));
	    (void) close(writeto);
	    return(-1);
	}
	if (debug) {
	    fprintf(stderr, "client: wrote %d bytes\n", len2); fflush(stderr);
	}
	count -= len;
	if (count < bufsize)
	    bufsize = count;
    }

  /*
   * clean up
   */

  (void) unlink(temppath);
  if (debug)
    diag("afscode:copy:removing dir7: %s", tempdir);
  (void) rmdir(tempdir);
    if (close(readfrom) < 0) {
	error = errno;
	(void) unlink(temppath);
	if (debug)
	  diag("afscode:copy:removing dir8: %s", tempdir);
	(void) rmdir(tempdir);
	errno = error;
	efatal("close");
    }
  
  if (close(writeto) < 0)
   { 
     error = errno;
     (void) unlink(temppath);
     if (debug)
       diag("afscode:copy:removing dir9: %s", tempdir);
     (void) rmdir(tempdir);
     errno = error;
     efatal("close");
   }
  (void) unlink(temppath);
  if (debug)
    diag("afscode:copy:removing dir10: %s", tempdir);
  (void) rmdir(tempdir);

  (void) free(buffer);
  return(0);

  if (debug)
    diag("transfer complete");
}

opentemp(dir, file, path)
char *dir, *file, *path;
{
  int pid;
  char *p, *q;

  pid = getpid();

  p = path;
  q = dir;
  do {
    *p++ = *q;
  } while (*q++ != '\0');
  p--;
  while (*--p == 'X') {
    *p = (pid % 10) + '0';
    pid /= 10;
  }
  p++;
  for (;;) {
    if (mkdir(path, 0700) >= 0)
      break;
    if (*p < 'a' && *p > 'z')
      *p = 'a';
    else
      (*p)++;
  }
  (void) strcpy(dir, path);
  (void) concat(path, MAXPATHLEN, dir, "/", file, NULL);
  return(open(path, O_CREAT|O_EXCL|O_RDWR, 0600));
}

/*VARARGS1*/
fatal(fmt, va_alist)
char *fmt;
va_dcl
{
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;

    ptr = concat(buf, sizeof(buf), "afscode: ", NULL);
    va_start(vargs);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = '\n';
    (void) write(errdesc, buf, ptr-buf);
    exit(-1);
}

efatal(fmt, va_alist)
char *fmt;
va_dcl
{
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;
    int serrno = errno;

    ptr = concat(buf, sizeof(buf), "afscode: ", NULL);
    va_start(vargs);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = ':';
    *ptr++ = ' ';
    ptr = concat(ptr, buf+sizeof(buf)-ptr, errmsg(serrno), NULL);
    *ptr++ = '\n';
    (void) write(errdesc, buf, ptr-buf);
    exit(-1);
}
