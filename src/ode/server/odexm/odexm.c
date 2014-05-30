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
 *
 * Copyright (c) 1992 Carnegie Mellon University 
 * All Rights Reserved. 
 *  
 * Permission to use, copy, modify and distribute this software and its 
 * documentation is hereby granted, provided that both the copyright 
 * notice and this permission notice appear in all copies of the 
 * software, derivative works or modified versions, and any portions 
 * thereof, and that both notices appear in supporting documentation. 
 *  
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR 
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE. 
 *  
 * Carnegie Mellon requests users of this software to return to 
 *  
 * Software Distribution Coordinator  or  Software_Distribution@CS.CMU.EDU 
 * School of Computer Science 
 * Carnegie Mellon University 
 * Pittsburgh PA 15213-3890 
 *  
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes. 
 */
/*
 * HISTORY
 * $Log: odexm.c,v $
 * Revision 1.11.26.1  1995/04/18  17:53:03  robert
 * 	print out pathname for efatal opentemp failure
 * 	[1995/04/04  21:43:43  robert]
 *
 * Revision 1.11.19.3  1994/02/14  15:41:02  root
 * 	CR # 1049 - Get odexm to build on at386_sinix.
 * 	[1994/02/14  15:40:42  root]
 * 
 * Revision 1.11.19.2  1993/11/22  22:56:17  damon
 * 	CR 788. Make odexm.conf file location and name configurable
 * 	[1993/11/22  22:56:04  damon]
 * 
 * Revision 1.11.19.1  1993/11/19  22:52:33  damon
 * 	CR 841. Print path to conf and map files on error
 * 	[1993/11/19  22:52:25  damon]
 * 
 * Revision 1.11.17.2  1993/11/10  22:28:27  damon
 * 	CR 463
 * 	Swapped parameters to check_arglist() ep and sp
 * 	Changed initialization of q from NULL to ""
 * 	[1993/11/10  22:27:40  damon]
 * 
 * Revision 1.11.17.1  1993/11/09  16:54:20  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:53:05  damon]
 * 
 * Revision 1.11.10.11  1993/06/23  20:23:56  marty
 * 	CR # 592 - Change rindex to strrchr.
 * 	[1993/06/23  20:23:43  marty]
 * 
 * Revision 1.11.10.10  1993/05/19  19:58:56  damon
 * 	CR 515. Added handling for stdin
 * 	[1993/05/19  19:58:48  damon]
 * 
 * Revision 1.11.10.9  1993/05/04  19:07:55  damon
 * 	CR 435. Changed u_long to unsigned int
 * 	[1993/05/04  19:07:47  damon]
 * 
 * Revision 1.11.10.8  1993/04/15  18:54:01  marty
 * 	Add include of header files ode/interface.h and fcntl.h
 * 	[1993/04/15  18:53:44  marty]
 * 
 * Revision 1.11.10.7  1993/03/31  19:06:23  damon
 * 	CR 443. opentemp now just creates directory, no file
 * 	[1993/03/31  19:05:48  damon]
 * 
 * Revision 1.11.10.6  1993/03/30  21:27:33  damon
 * 	CR 440. Fixed temp dir handling
 * 	[1993/03/30  21:27:24  damon]
 * 
 * Revision 1.11.10.5  1993/03/25  15:56:34  damon
 * 	CR 440. Added makepath to odexm_cp
 * 	[1993/03/25  15:56:25  damon]
 * 
 * Revision 1.11.10.4  1993/03/24  15:56:58  damon
 * 	CR 440. Added odexm_cp
 * 	[1993/03/24  15:56:38  damon]
 * 
 * Revision 1.11.10.3  1993/03/15  18:00:25  damon
 * 	CR 443. Moved opentemp() to libode
 * 	[1993/03/15  17:59:54  damon]
 * 
 * Revision 1.11.10.2  1993/01/19  18:49:16  damon
 * 	CR 408. Moved streams/tcp specific code into odexm_tcp.c
 * 	[1993/01/19  18:48:13  damon]
 * 
 * Revision 1.11.2.18  1992/12/17  18:06:46  damon
 * 	CR 368. Added better kxct compatibility
 * 	[1992/12/17  18:06:08  damon]
 * 
 * Revision 1.11.2.17  1992/12/10  16:27:31  damon
 * 	CR 329. Now use setsid instead of setpgrp
 * 	[1992/12/10  16:20:30  damon]
 * 
 * Revision 1.11.2.15  1992/12/03  19:13:49  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:43:06  damon]
 * 
 * Revision 1.11.2.4  1992/08/24  20:26:43  damon
 * 	CR 240. First Version with persistant connections
 * 	[1992/08/24  20:23:44  damon]
 * 
 * Revision 1.11.2.3  1992/07/26  17:30:27  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/17  19:37:08  gm]
 * 
 * Revision 1.11.2.2  1991/12/31  16:25:56  damon
 * 	Removed SO_DONTLINGER
 * 	[1991/12/31  16:25:33  damon]
 * 
 * Revision 1.8  90/08/25  12:21:56  devrcs
 * 	Removed dependency upon old CMU include files.
 * 	[90/08/19  17:34:30  gm]
 * 
 * Revision 1.6  90/06/29  14:37:44  devrcs
 * 	Removed kerberos support.
 * 	[90/06/23  15:06:17  gm]
 * 
 * Revision 1.4  90/04/14  00:53:03  devrcs
 * 	Changes for new authentication protocol.
 * 	[90/03/06  20:21:33  gm]
 * 
 * Revision 1.2  89/12/26  10:48:13  gm
 * 	Created.
 * 	[89/12/23            gm]
 * 
 * $EndLog$
 */

#if !defined(lint) && !defined(_NOIDENT)
static char rcsid[] = "@(#)$RCSfile: odexm.c,v $ $Revision: 1.11.26.1 $ (OSF) $Date: 1995/04/18 17:53:03 $";
#endif

/*
 * ODE execution monitor
 */
#include <ode/interface.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <pwd.h>
#include <ode/odedefs.h>
#include <ode/private/odexm.h>
#include <ode/run.h>
#include <ode/util.h>
#include <stdlib.h>
#include <unistd.h>

char userbuf[128] = "USER=";
char *nenviron[] = {
    (char *)"PATH=:/usr/ucb:/bin:/usr/bin",
    userbuf,
    NULL
};

int errdesc;

extern char **environ;

const char *progname = "odexm";

#define MAXARGC 64

#define ANAME_SZ        32
char lname[ANAME_SZ];

u_char tempmode;
#define SEND_OVER	1
#define WANT_BACK	2
u_short tempslot;
char tempdir[MAXPATHLEN];
char temppath[MAXPATHLEN];
char *tempfile;

#ifndef NCARGS
#define NCARGS 1024
#endif

char args[NCARGS];
char *av[MAXARGC];
char **arglist;
char cmdbuf[MAXPATHLEN];

u_char debug;
u_char flags;

int exit_status;

char uniq_str [MAXPATHLEN];

int batch = 0;
int start_batch = 0;
int end_batch = 0;

static made_temp_dir = FALSE;
const char *conf_file = "/etc/odexm.conf"; /* default for odexm.conf file */

/*
 * PROTOTYPES
 */
void
transmit_data(void);
void
check_config(void);
void
run_command(void);
void
receive_data (void);
void
diag(const char * fmt, ... );
void
warn(const char * fmt, ... );
void
ewarn(const char * fmt, ... );
void
fatal(const char * fmt, ... ) ;
void
efatal(const char * fmt, ... );

/*ARGSUSED*/
void
main( int argc, char **argv)
{
    errdesc = 1;
    debug = 0;

  if ( argc == 2 ) {
    conf_file = *(argv+1);
  } /* if */
    /*
     * setup network connections
     */
    setup_connections();

    if ( batch ) {
      /*
       * check authentication
       */

      authenticate_client();

      read_config_info ();

    } else {
      strcpy ( uniq_str, "kxct-compatible" );
    } /* if */
    for (;;) {
      /*
       * read argument list for command
       */
      read_arglist();
      /*
       * check configuration
       */
      check_config();

      if ( start_batch ) {
        start_batch = 0;
        continue;
      } /* if */
      if ( end_batch ) {
        break;
      } /* if */
      /*
       * receive data file
       */
      if (tempslot != 0)
          receive_data();

    /*
     * execute command
     */
    run_command();
    /*
     * transmit data file
     */
    if (tempslot != 0)
        transmit_data();

    /*
     * transmit the exit status
     */
    transmit_status();
    if ( ! batch ) {
      break;
    } /* if */
}
    /*
     * that is all
     */
    if ( made_temp_dir )
      (void) rmdir(tempdir);
    /* if */
    exit(0);
}

void
check_arglist ( int count, char * ep, char * sp, unsigned int checksum )
{
    int i;
    unsigned int cksum;

    if (*(ep-1) != '\0')
        fatal("arg list not terminated");
    if (debug)
        diag("arglist teminated ok");
    sp = args;
    for (i = 0; i < count; i++) {
        av[i] = sp;
        sp += strlen(sp) + 1;
        if (sp > ep)
            break;
    }
    if (sp != ep)
        fatal("count/length mismatch");
    if (debug)
        diag("arglist count/length ok");
    av[i] = NULL;
    cksum = 0;
    for (i = 0; i < count; i++) {
        sp = av[i];
        while (*sp != '\0')
            cksum += ((unsigned)(*sp++));
    }
    if (cksum != checksum)
        fatal("checksum error");
    if (debug)
        diag("arglist checksum ok");
    arglist = av;
    if (tempslot != 0) {
      if ( batch ) {
        tempfile = arglist[tempslot];
        arglist[tempslot] = temppath;
      } else {
        tempfile = arglist[tempslot+2];
        arglist[tempslot+2] = temppath;
      }
    }
    if (debug)
        diag("arglist ok");
}

char exec_path [MAXPATHLEN];
char *tree_base;

static first = TRUE;
static int map_entries;

static struct {
  char cmd [32];
  char bin [32];
  char acl [32];
} map_data [50];

void
check_config(void)
{
  char buf[BUFSIZ];
  char aclfile[MAXPATHLEN];
  char *tools_dir=NULL;
  char *tree_owner=NULL;
  char *map_file=NULL;
  char *cmd;
  char *p;
  char *q=(char *)"";
  FILE *fp;
  int cmdfound;
  char *uniq_str_arg;
  struct stat st;
  struct passwd *pw;
  char * bufptr;
  BOOLEAN matched;
  int i;
  char * dummy;

  if (debug)
      diag("checking config");
  if ( !batch ) {
    tree_base = *arglist++;
    tree_owner = *arglist++;
  } /* if */
  cmd = *arglist;
  if (debug)
      diag("command: %s", cmd );
  if ( strcmp ( cmd, "odexm_begin") == 0 ) {
     start_batch = 1;
     return;
  } /* if */
  if ( strcmp ( cmd, "odexm_end") == 0 ) {
     end_batch = 1;
     return;
  } /* if */
  if ( first ) {
    first = FALSE;
    if ((fp = fopen( conf_file, "r")) == NULL)
      efatal("fopen %s", conf_file);
    matched = FALSE;
    while ( fgets( buf, sizeof(buf), fp ) != NULL) {
      rm_newline ( buf );
      bufptr = (char *) buf;
      uniq_str_arg = strdup ( nxtarg ( &bufptr, " \t" ) );
      if ( strcmp ( uniq_str_arg, uniq_str ) != 0 )
        continue;
      /* if */
      matched = TRUE;
      if ( batch )
        tree_base = strdup ( nxtarg ( &bufptr, " \t" ) );
      else
	/* Skip over argument */
        dummy = nxtarg ( &bufptr, " \t" );
      /* if */
      tools_dir = strdup ( nxtarg ( &bufptr, " \t" ) );
      if ( batch )
        tree_owner = strdup ( nxtarg ( &bufptr, " \t" ) );
      else
	/* Skip over argument */
        dummy = nxtarg ( &bufptr, " \t" );
      /* if */
      map_file = strdup ( nxtarg ( &bufptr, " \t" ) );
      break;
    } /* while */
    fclose ( fp );
    if ( ! matched ) {
      sprintf (buf, "No match for unique string %s\nin configuration file %s.\n", uniq_str, conf_file );
      fatal (buf);
    }
    if (debug)
      diag("map file %s", map_file );
    if (lstat(map_file, &st) < 0 || (st.st_mode&S_IFMT) != S_IFREG) {
      sprintf(buf, "Invalid odexm map file: %s\n", map_file);
      fatal(buf);
    }
    if (debug)
      diag("map file mode ok");
    if ((pw = getpwnam(tree_owner)) == NULL)
      fatal("Owner of directory not found");
    if (pw -> pw_uid == 0)
      fatal("Cannot run as root");
    if (setgid(pw->pw_gid) < 0)
      efatal("setgid");
    if (setuid(pw->pw_uid) < 0)
      efatal("setuid");
    if (chdir(tree_base) < 0)
      efatal("chdir");
    if (debug)
      diag("setuid/chdir ok");
    (void) concat ( exec_path, sizeof (exec_path), tools_dir,
                    ":/bin:/usr/bin:/usr/ucb", NULL );
    if ((fp = fopen(map_file, "r")) == NULL)
        efatal("map file fopen");
    i = 0;
    while ((p = fgets(buf, sizeof(buf), fp)) != NULL) {
      if ((q  = strrchr (p, '\n')) != NULL)
          *q = '\0';
      q = nxtarg(&p, " \t");
      strcpy ( map_data [i].cmd, q );
      q = nxtarg(&p, " \t");
      strcpy ( map_data [i].bin, q );
      q = nxtarg(&p, " \t");
      strcpy ( map_data [i].acl, q );
      i++;
    }
    map_entries = i;
    (void) fclose(fp);
  } /* if */
  if ( tempslot != 0 && !made_temp_dir ) {
    made_temp_dir = TRUE;
    concat ( tempdir, sizeof(tempdir), tree_base, "/#odexmXXXXXX", NULL);
    if ( opentemp(tempdir, tempdir ) < 0) {
    	efatal("opentemp %s failed", tree_base); 
    }
  } /* if */
  cmdfound = FALSE;
  if ( strcmp ( cmd, "odexm_cp" ) != 0 ) {
    for ( i = 0; i < map_entries; i++ ) {
      if (strcmp( map_data [i].cmd, cmd) == 0) {
        cmdfound = TRUE;
        (void) strcpy(aclfile, q);
        strcpy ( cmdbuf, map_data [i].bin );
      } /* if */
    } /* for */
    if (!cmdfound) {
      sprintf (buf, "No match for command %s in map file %s.\n", cmd, map_file );
      fatal("%s", buf);
    }
    if (debug)
      diag("command %s acl %s temp %s", cmdbuf, aclfile, tempdir);
    /* if */
  } /* if */
  if ( !batch )
    authenticate_client ();
  /* if */
}

void
receive_data (void)
{
    unsigned int count;
    u_short perm;
    char *buffer;
    int bufsize;
    int fd;
    int len, len2;
    int error;
    char exists;
    int readsize;

    if (debug)
        diag("receiving data");
    if ((tempmode&SEND_OVER) == 0)
        exists = 0;
    else if ( ! get_exists ( &exists ) )
        efatal("server read failed");
    if (debug)
        diag("exists %d", exists);
    if (exists) {
        if ( ! get_perm ( &perm ) )
            efatal("server read failed");
        if ( ! get_count ( &count ) )
            efatal("server read failed");
    } else {
        perm = 0600;
        count = 0;
    }
    concat ( temppath, sizeof(temppath), tempdir, "/", tempfile, NULL );
    tempfile = temppath;
    if (debug) {
        diag("perm %#o, count %d", perm, count);
        diag("d: %s f: %s p: %s", tempdir, tempfile, temppath );
    }
    fd = open ( tempfile, O_CREAT | O_RDWR, 0600 );
    if (debug)
        diag("tempfile %s", tempfile);
    if (fchmod(fd, (mode_t) (perm & ( S_IRWXU | S_IRWXG | S_IRWXO ) ) ) < 0)
        efatal("fchmod failed");
    if (!exists)
        (void) unlink(tempfile);
    if (count == 0) {
        (void) close(fd);
        return;
    }
    /*
     * should check for space on disk, but could be expensive and unreliable
     */
    if ((bufsize = count) > 10*1024)
        buffer = (char *) malloc(bufsize = 10*1024);
    else
        buffer = (char *) malloc(bufsize);
    if (buffer == NULL)
        fatal("malloc failed");
    while (count != 0) {
        if (debug)
            diag("loop count %d", count);
        if ( count > bufsize )
          readsize = bufsize;
        else
          readsize = count;
        /* if */
        get_buffer ( buffer, &len, readsize, fd );
        if ((len2 = write(fd, buffer, len)) != len) {
            error = errno;
            (void) close(fd);
            (void) unlink(tempfile);
            (void) rmdir(tempdir);
            errno = error;
            efatal("write", error);
        }
        count -= len;
        if (count < bufsize)
            bufsize = count;
    }
    if (close(fd) < 0) {
        error = errno;
        (void) unlink(tempfile);
        (void) rmdir(tempdir);
        errno = error;
        efatal("close");
    }
    (void) free(buffer);
    if (debug)
        diag("transfer complete");
} /* end receive_data */

void
run_command(void)
{
  int in_pipe[2];
  int out_pipe[2];
  int pid;
  int child;
  int status;
  char * src;
  char * dst;
  int src_f;
  int dst_f;

    if (debug)
        diag("command started %s ", cmdbuf );
    (void) strcpy(userbuf+sizeof("USER=")-1, lname);
    environ = nenviron;
    if ( batch ) {
      if ( strcmp ( *arglist, "odexm_cp") == 0 ) {
        src = strdup ( *(arglist+1) );
        dst = strdup ( *(arglist+2) );
        unlink ( dst );
        makepath ( dst, NULL, 0, 0 );
        src_f = open ( src, O_RDONLY, 0 );
        dst_f = open ( dst, O_CREAT | O_WRONLY, S_IWUSR );
        status = filecopy ( src_f, dst_f ); 
        close ( src_f );
        close ( dst_f );
        chmod ( dst, S_IRUSR | S_IRGRP | S_IROTH );
        transmit_status2 ();
      } else {
        pipe (in_pipe);
        pipe (out_pipe);
        pid = fork ();
        if ( pid == 0 ) {
          setenv ( "PATH", exec_path, 1 );
          dup2 ( out_pipe[0], 0 );
          close ( out_pipe[0] );
          close ( out_pipe[1] );
          dup2 ( in_pipe[1], 1 );
          close ( in_pipe[0] );
          close ( in_pipe[1] );
          exit_status = runvp(cmdbuf, arglist);
          exit ( exit_status );
        } /* if */
        close ( in_pipe[1] );
        close ( out_pipe[0] );

        handle_io ( in_pipe[0], out_pipe[1] );

        do {
          child = wait ( &status );
        } while ( child != pid && child != -1 );
        if (child == -1) {
          (void) fprintf(stderr, "wait: %s\n", strerror ( errno ) );
          exit_status = -1;
        } else {
          if (WIFSIGNALED(status) || WEXITSTATUS(status) == 0377)
            exit_status = -1;
          else
            exit_status = WEXITSTATUS(status);
          /* if */
        } /* if */
        transmit_status2 ();
        close ( in_pipe[0] );
        close ( out_pipe[1] );
      } /* if */
    } else {
      setenv ( "PATH", exec_path, 1 );
      exit_status = runvp(cmdbuf, arglist);
      (void) close(0);
      (void) close(1);
    } /* if */
    if (debug)
        diag("command finished status %d", exit_status);
}

void
transmit_data(void)
{
    unsigned int count;
    u_short perm;
    char *buffer;
    int bufsize;
    int fd;
    struct stat st;
    int len, len2;
    int error;
    char exists;

    if (debug)
        diag("sending data");
    if ((tempmode&WANT_BACK) == 0) {
        (void) unlink(tempfile);
        if (debug)
            diag("not wanted back");
        return;
    }
    if (lstat(tempfile, &st) < 0) {
        if (errno != ENOENT) {
            error = errno;
            (void) unlink(tempfile);
            (void) rmdir(tempdir);
            errno = error;
            efatal("lstat", error);
        }
        exists = 0;
    } else {
        if ((st.st_mode&S_IFMT) != S_IFREG) {
            (void) unlink(tempfile);
            (void) rmdir(tempdir);
            fatal("tempfile no longer a regular file");
        }
        exists = 1;
    }
    if (debug)
        diag("exists %d", exists);
    if ( ! put_exists ( &exists ) ) {
        (void) unlink(tempfile);
        (void) rmdir(tempdir);
        efatal("write failed");
    }
    if (!exists) {
        (void) unlink(tempfile);
        return;
    }
    perm = st.st_mode&0777;
    if (debug)
        diag("perm %#o", perm);
    if ( ! put_perm ( &perm ) ) {
        (void) unlink(tempfile);
        (void) rmdir(tempdir);
        efatal("write failed");
    }
    count = st.st_size;
    if (debug)
        diag("count %d", count);
    if ( ! put_count ( &count ) ) {
        (void) unlink(tempfile);
        (void) rmdir(tempdir);
        efatal("write failed");
    }
    count = st.st_size;
    if (count == 0) {
        (void) unlink(tempfile);
#ifdef notdef
        (void) rmdir(tempdir);
#endif
        return;
    }
    if ((fd = open(tempfile, O_RDONLY, 0)) < 0) {
        (void) unlink(tempfile);
        (void) rmdir(tempdir);
        efatal("open failed");
    }
    if ((bufsize = count) > 10*1024)
        buffer = (char *) malloc(bufsize = 10*1024);
    else
        buffer = (char *) malloc(bufsize);
    if (buffer == NULL) {
        (void) unlink(tempfile);
        (void) rmdir(tempdir);
        fatal("malloc failed");
    }
    if (debug)
        diag("bufsize %d", bufsize);
    while (count != 0) {
        if (debug)
            diag("loop count %d", count);
        if ((len = read(fd, buffer, bufsize)) <= 0) {
            error = errno;
            (void) close(fd);
            (void) unlink(tempfile);
            (void) rmdir(tempdir);
            if (len == 0)
                fatal("1 premature EOF");
            errno = error;
            efatal("server read", error);
        }
        if (debug)
            diag("read %d bytes", len);
        put_buffer ( buffer, len, &len2, fd );
        if (debug)
            diag("wrote %d bytes", len2);
        count -= len;
        if (count < bufsize)
            bufsize = count;
    }
    if (close(fd) < 0) {
        error = errno;
        (void) unlink(tempfile);
        (void) rmdir(tempdir);
        errno = error;
        efatal("close");
    }
    (void) free(buffer);
    (void) unlink(tempfile);
    if (debug)
        diag("transfer complete");
}

/*VARARGS1*/
void
diag(const char * fmt, ... )
{
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;
    struct timeval tv;

    if (gettimeofday(&tv, (struct timezone *)0) < 0)
        efatal("gettimeofday failed");
    (void) sprintf(buf, "%d.%d: ", tv.tv_sec, tv.tv_usec);
    ptr = buf + strlen(buf);
    va_start(vargs,fmt);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = '\n';
    (void) write(errdesc, buf, ptr-buf);
}

/*VARARGS1*/
void
warn(const char * fmt, ... ) 
{
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;

    ptr = concat(buf, sizeof(buf), "odexm: ", NULL);
    va_start(vargs, fmt);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = '\n';
    (void) write(errdesc, buf, ptr-buf);
}

void
ewarn(const char * fmt, ... )
{
    int serrno = errno;
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;

    ptr = concat(buf, sizeof(buf), "odexm: ", NULL);
    va_start(vargs, fmt);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = ':';
    *ptr++ = ' ';
    ptr = concat(ptr, buf+sizeof(buf)-ptr, strerror (serrno), NULL);
    *ptr++ = '\n';
    (void) write(errdesc, buf, ptr-buf);
}

/*VARARGS1*/
void
fatal(const char * fmt, ... ) 
{
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;

    ptr = concat(buf, sizeof(buf), "odexm: ", NULL);
    va_start(vargs,fmt);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = '\n';
    (void) write(errdesc, buf, ptr-buf);
    exit(0);
}

void
efatal(const char * fmt, ... )
{
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;
    int serrno = errno;

    ptr = concat(buf, sizeof(buf), "odexm: ", NULL);
    va_start(vargs, fmt);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = ':';
    *ptr++ = ' ';
    ptr = concat(ptr, buf+sizeof(buf)-ptr, strerror (serrno), NULL);
    *ptr++ = '\n';
    (void) write(errdesc, buf, ptr-buf);
    exit(0);
}
