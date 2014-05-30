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
 * $Log: md.c,v $
 * Revision 1.10.9.1  1993/11/08  22:23:15  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/08  22:22:27  damon]
 *
 * Revision 1.10.7.5  1993/05/28  14:07:46  marty
 * 	CR # 558 - get it building on rios_aix
 * 	[1993/05/28  14:07:38  marty]
 * 
 * Revision 1.10.7.4  1993/05/28  14:06:01  marty
 * 	CR # 558 - get it building on rios_aix
 * 	[1993/05/28  14:05:45  marty]
 * 
 * Revision 1.10.7.3  1993/04/29  17:16:27  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  17:16:14  marty]
 * 
 * Revision 1.10.7.2  1993/01/13  16:43:13  damon
 * 	CR 382. Removed NO_DIRENT, _BLD, S_ISDIR, S_ISREG
 * 	[1993/01/05  20:42:28  damon]
 * 
 * Revision 1.10.2.7  1992/12/21  18:37:18  hester
 * 	Enclosed prototyping in #ifdef NO_ANSI_CC
 * 	[1992/12/21  18:37:03  hester]
 * 
 * Revision 1.10.2.6  1992/12/03  19:07:41  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:36:54  damon]
 * 
 * Revision 1.10.2.5  1992/11/05  20:46:27  damon
 * 	CR 296. Cleaned up warnings
 * 	[1992/11/05  20:46:11  damon]
 * 
 * Revision 1.10.2.4  1992/09/24  18:58:44  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/21  20:20:20  gm]
 * 
 * Revision 1.10.2.3  1992/06/16  23:08:54  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:47:56  damon]
 * 
 * Revision 1.10.2.2  1991/12/30  21:25:29  damon
 * 	port to sparc_sunos and libsb to libode transition
 * 	[1991/12/20  20:13:15  damon]
 * 
 * Revision 1.10  1991/12/05  20:45:41  devrcs
 * 	Moved #ifdef NO_DIRENT lines to outside #ifdef _BLD as
 * 	this define is used even when _BLD isn't.
 * 	[91/09/04  12:44:01  damon]
 * 
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:05:11  mckeen]
 * 
 * 	added print_revision() and "-version" switch
 * 	[91/06/03  16:13:59  ezf]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:55:34  dwm]
 * 
 * Revision 1.8  90/10/07  21:51:31  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:05:15  gm]
 * 
 * Revision 1.7  90/09/23  16:55:41  devrcs
 * 	Added NO_DIRENT support.
 * 	[90/09/20  18:02:31  gm]
 * 
 * Revision 1.6  90/09/13  13:04:13  devrcs
 * 	Remove dependencies of empty files.
 * 	[90/09/03  17:41:23  gm]
 * 
 * Revision 1.5  90/07/27  11:09:13  devrcs
 * 	More portability changes.
 * 	[90/07/22  11:44:06  gm]
 * 
 * 	Added more _BLD code.
 * 	[90/07/16  17:09:09  gm]
 * 
 * 	More gcc changes.
 * 	[90/07/16  01:39:35  gm]
 * 
 * Revision 1.4  90/07/17  12:34:44  devrcs
 * 	Updated for new configuration.
 * 	[90/07/07  11:21:51  gm]
 * 
 * 	More changes for gcc.
 * 	[90/07/04  22:29:45  gm]
 * 
 * Revision 1.3  90/06/22  21:54:47  devrcs
 * 	Added -K switch to keep prefix for dependencies.
 * 	[90/05/28  12:09:38  gm]
 * 
 * Revision 1.2  90/05/24  21:57:23  devrcs
 * 	Canonicalize -I switches since they may not some from genpath.
 * 	[90/05/23            gm]
 * 
 * 	Rewritten from scratch.
 * 	[90/05/18            gm]
 * 
 * $EndLog$
 */
#if !defined(lint) && !defined(_NOIDENT)
static const char rcsid[] = "@(#)$RCSfile: md.c,v $ $Revision: 1.10.9.1 $ (OSF) $Date: 1993/11/08 22:23:15 $";
#endif

#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ode/odedefs.h>
#include <ode/misc.h>
#include <ode/util.h>

struct table {
    int max;			/* max argc before realloc of argv */
    int argc;			/* current argument count */
    char **argv;		/* arguments */
};

struct target {
    char *name;
    struct table curdeps;
    struct table stddeps;
};

const char *progname;

struct table curincdirs;
struct table stdincdirs;

struct table keepincdirs;

struct table dependfiles;

struct table targets;

int depfile_bufsize;
char *depfile_buffer;

const char *outfile = "depend.mk";
int debug = FALSE;
int rmflag = FALSE;
int stdflag = FALSE;
int verbose = FALSE;

char _argbreak;

/*
 * PROTOTYPES
 */
void
parse_command_line(int , char ** );
void
read_dependencies(void);
void
update_database(void);
void
remove_dependencies(void);
void
print_table( struct table *tp );
void
output_target( FILE *outf, struct target *targ, int need_header );

void
main(int argc, char ** argv)
{

    /*
     * parse command line
     */
    parse_command_line(argc, argv);

    /*
     * process dependency files
     */
    read_dependencies();

    /*
     * update output file
     */
    update_database();

    /*
     * remove dependency files
     */
    remove_dependencies();

    exit(0);
}

/*
 * error routines
 */

/*VARARGS1*/
void
#if __STDC__
diag(const char *fmt, ...)
#else
diag(fmt, va_alist)
char *fmt;
va_dcl
#endif
{
    va_list vargs;

    (void) fflush(stdout);
#if __STDC__
    va_start(vargs, fmt);
#else
    va_start(vargs);
#endif
    (void) vfprintf(stderr, fmt, vargs);
    va_end(vargs);
    (void) putc('\n', stderr);
}

/*VARARGS1*/
void
#if __STDC__
ewarn(const char *fmt, ...)
#else
ewarn(fmt, va_alist)
char *fmt;
va_dcl
#endif
{
    va_list vargs;
    int serrno = errno;

    (void) fflush(stdout);
    (void) fputs(progname, stderr);
    (void) putc(':', stderr);
    (void) putc(' ', stderr);
#if __STDC__
    va_start(vargs, fmt);
#else
    va_start(vargs);
#endif
    (void) vfprintf(stderr, fmt, vargs);
    va_end(vargs);
    (void) putc(':', stderr);
    (void) putc(' ', stderr);
    (void) fputs(strerror(serrno), stderr);
    (void) putc('\n', stderr);
}

/*VARARGS1*/
void
#if __STDC__
efatal(const char *fmt, ...)
#else
efatal(fmt, va_alist)
char *fmt;
va_dcl
#endif
{
    va_list vargs;
    int serrno = errno;

    (void) fflush(stdout);
    (void) fputs(progname, stderr);
    (void) putc(':', stderr);
    (void) putc(' ', stderr);
#if __STDC__
    va_start(vargs, fmt);
#else
    va_start(vargs);
#endif
    (void) vfprintf(stderr, fmt, vargs);
    va_end(vargs);
    (void) putc(':', stderr);
    (void) putc(' ', stderr);
    (void) fputs(strerror(serrno), stderr);
    (void) putc('\n', stderr);
    exit(1);
}

/*VARARGS1*/
void
#if __STDC__
warn(const char *fmt, ...)
#else
warn(fmt, va_alist)
char *fmt;
va_dcl
#endif
{
    va_list vargs;

    (void) fflush(stdout);
    (void) fputs(progname, stderr);
    (void) putc(':', stderr);
    (void) putc(' ', stderr);
#if __STDC__
    va_start(vargs, fmt);
#else
    va_start(vargs);
#endif
    (void) vfprintf(stderr, fmt, vargs);
    va_end(vargs);
    (void) putc('\n', stderr);
}

/*VARARGS1*/
void
#if __STDC__
fatal(const char *fmt, ...)
#else
fatal(fmt, va_alist)
char *fmt;
va_dcl
#endif
{
    va_list vargs;

    (void) fflush(stdout);
    (void) fputs(progname, stderr);
    (void) putc(':', stderr);
    (void) putc(' ', stderr);
#if __STDC__
    va_start(vargs, fmt);
#else
    va_start(vargs);
#endif
    (void) vfprintf(stderr, fmt, vargs);
    va_end(vargs);
    (void) putc('\n', stderr);
    exit(1);
}

void
resize_table( struct table *tp)
{
    if (tp->max == 0) {
	tp->max = 4;
	tp->argv = (char **) malloc((unsigned) tp->max * sizeof(char *));
    } else {
	tp->max <<= 1;
	tp->argv = (char **) realloc((char *) tp->argv,
				     (unsigned) tp->max * sizeof(char *));
    }
    if (tp->argv == NULL)
	fatal("table argv malloc failed");
}

void
parse_command_line(int argc, char ** argv)
{
    struct table *tp;
    struct stat st;
    DIR *dirp;
    struct dirent *dp;
    char buf[MAXPATHLEN];
    char *p;
    int l;

    if (argc > 0) {
	if ((progname = strrchr(argv[0], '/')) != NULL)
	    progname++;
	else
	    progname = argv[0];
	argc--; argv++;
    } else
	progname = "md";

    memset((char *)&curincdirs, 0, sizeof(curincdirs));
    memset((char *)&stdincdirs, 0, sizeof(stdincdirs));
    tp = &curincdirs;

    while (argc > 0) {
	if (argv[0][0] != '-')
	    break;
	switch (argv[0][1]) {
	case 'I':
	    if (strcmp(argv[0], "-I-") == 0) {
		tp = &stdincdirs;
		break;
	    }
	    if (tp->argc == tp->max)
		resize_table(tp);
	    p = (argv[0]) + 2;
	    canonicalize("", p, buf, sizeof(buf));
	    if (*p == '/')
		p = buf;
	    else
		p = buf + 1;
	    p = strdup(p);
	    if (p == NULL)
		efatal("-I strdup failed");
	    tp->argv[tp->argc++] = p;
	    break;
	case 'K':
	    if (keepincdirs.argc == keepincdirs.max)
		resize_table(&keepincdirs);
	    p = (argv[0]) + 2;
	    canonicalize("", p, buf, sizeof(buf));
	    if (*p == '/')
		p = buf;
	    else
		p = buf + 1;
	    p = strdup(p);
	    if (p == NULL)
		efatal("-K strdup failed");
	    keepincdirs.argv[keepincdirs.argc++] = p;
	    break;
	case 'd':
	    if (strcmp(argv[0], "-debug") == 0)
		debug = TRUE;
	    else {
		warn("unknown switch: %s", argv[0]);
		print_usage();
	    }
	    break;
	case 'f':
	    if (strcmp(argv[0], "-file") == 0) {
		if (argc == 1)
		    fatal("missing argument to %s", argv[0]);
		argc--; argv++;
		outfile = argv[0];
	    } else {
		warn("unknown switch: %s", argv[0]);
		print_usage();
	    }
	    break;
	case 'r':
	    if (strcmp(argv[0], "-rm") == 0)
		rmflag = TRUE;
	    else {
		warn("unknown switch: %s", argv[0]);
		print_usage();
	    }
	    break;
	case 's':
	    if (strcmp(argv[0], "-std") == 0)
		stdflag = TRUE;
	    else {
		warn("unknown switch: %s", argv[0]);
		print_usage();
	    }
	    break;
	case 'v':
	    if (strcmp(argv[0], "-verbose") == 0)
		verbose = TRUE;
	    else if (strcmp(argv[0], "-version") == 0) {
		ui_print_revision();
		exit(0);
	    } else {
		warn("unknown switch: %s", argv[0]);
		print_usage();
	    }
	    break;
	default:
	    warn("unknown switch: %s", argv[0]);
	    print_usage();
	}
	argc--; argv++;
    }

    if (argc == 0)
	print_usage();

    if (tp == &curincdirs && tp->argc > 0) {
	memcpy(&stdincdirs, (char *)&curincdirs, sizeof(curincdirs));
	memset((char *)&curincdirs, 0, sizeof(curincdirs));
    }

    memset((char *)&dependfiles, 0, sizeof(dependfiles));
    tp = &dependfiles;

    while (argc > 0) {
	if (stat(argv[0], &st) < 0)
	    efatal("stat %s", argv[0]);
	if (S_ISREG(st.st_mode)) {
	    if (tp->argc == tp->max)
		resize_table(tp);
	    tp->argv[tp->argc++] = argv[0];
	    argc--; argv++;
	    continue;
	}
	if (!S_ISDIR(st.st_mode))
	    fatal("%s: Not a directory or regular file", argv[0]);
	if ((dirp = opendir(argv[0])) == NULL)
	    efatal("opendir %s", argv[0]);
	while ((dp = readdir(dirp)) != NULL) {
	    p = dp->d_name;
	    l = strlen(p);
	    if (l < 2 || p[l-2] != '.' || p[l-1] != 'd')
		continue;
	    if (sizeof(buf) < (strlen(argv[0]) + strlen(p) + 1))
		fatal("no room in buffer for %s/%s", argv[0], p);
	    else
	    	concat(buf, sizeof(buf), argv[0], "/", p, NULL);
	    p = strdup(buf);
	    if (p == NULL)
		efatal("strdup dirent name");
	    if (tp->argc == tp->max)
		resize_table(tp);
	    tp->argv[tp->argc++] = p;
	}
	(void) closedir(dirp);
	argc--; argv++;
    }

    /*
     * print tables
     */
    if (verbose) {
	print_table(&curincdirs);
	print_table(&stdincdirs);
	print_table(&dependfiles);
    }
}

void
print_table( struct table *tp )
{
    int i;

    printf("table %x max %d argc %d\n", (unsigned int)tp, tp->max, tp->argc);
    for (i = 0; i < tp->argc; i++)
	printf("  argv[%d] = %s\n", i, tp->argv[i]);
}

int
shorten_name( char *depbuf )
{
    char buf[MAXPATHLEN];
    char *ptr;
    int l1, l2, lmax;
    int maxcur, maxstd;
    int i;
    char *dep;

    canonicalize("", depbuf, buf, sizeof(buf));
    if (*depbuf == '/')
	dep = buf;
    else
	dep = buf + 1;
    l1 = strlen(dep);
    lmax = -1;
    maxcur = 0;
    for (i = 0; i < curincdirs.argc; i++) {
	ptr = curincdirs.argv[i];
	l2 = strlen(ptr);
	if (l1 < l2 || l2 <= lmax)
	    continue;
	if (l2 == 0) {
	    if (*dep == '/')
		continue;
	} else {
	    if (l1 > l2 && dep[l2] != '/')
		continue;
	    if (memcmp(ptr, dep, l2) != 0)
		continue;
	}
	lmax = l2;
	maxcur = 1;
    }
    maxstd = 0;
    for (i = 0; i < stdincdirs.argc; i++) {
	ptr = stdincdirs.argv[i];
	l2 = strlen(ptr);
	if (l1 < l2 || l2 <= lmax)
	    continue;
	if (l2 == 0) {
	    if (*dep == '/')
		continue;
	} else {
	    if (l1 > l2 && dep[l2] != '/')
		continue;
	    if (memcmp(ptr, dep, l2) != 0)
		continue;
	}
	lmax = l2;
	maxstd = 1;
    }
    if (lmax == -1)
	return(-1);
    for (i = 0; i < keepincdirs.argc; i++) {
	ptr = keepincdirs.argv[i];
	l2 = strlen(ptr);
	if (l2 == lmax && memcmp(ptr, dep, l2) == 0) {
	    (void) strcpy(depbuf, dep);
	    return(maxstd ? 1 : 0);
	}
    }
    ptr = dep + lmax;
    while (*ptr == '/')
	ptr++;
    (void) strcpy(depbuf, ptr);
    return(maxstd ? 1 : 0);
}

void
read_target_dependencies( char *file )
{
    char buf[MAXPATHLEN];
    int fd;
    char *ptr, *dep;
    struct stat st;
    struct target *targ;
    struct table *tp;
    int cnt;
    int status;

    targ = (struct target *) calloc(1, sizeof(struct target));
    if (targ == NULL)
	efatal("target calloc failed");
    if ((fd = open(file, O_RDONLY, 0)) < 0)
	efatal("open %s", file);
    if (fstat(fd, &st) < 0)
	efatal("fstat %s", file);
    if (st.st_size >= depfile_bufsize) {
	depfile_bufsize += 1024;
	if (st.st_size >= depfile_bufsize)
	    depfile_bufsize = st.st_size + 1;
	depfile_buffer = realloc(depfile_buffer, depfile_bufsize);
	if (depfile_buffer == NULL)
	    efatal("depfile_buffer realloc failed");
    }
    ptr = depfile_buffer;
    while (st.st_size > 0) {
	if ((cnt = read(fd, ptr, st.st_size)) < 0)
	    efatal("read %s", file);
	if (cnt == 0)
	    fatal("premature EOF");
	st.st_size -= cnt;
	ptr += cnt;
    }
    *ptr = '\0';
    if (close(fd) < 0)
	efatal("close %s", file);
    ptr = depfile_buffer;
    targ->name = (char *)nxtarg(&ptr, " \t:");
    if (*targ->name == '\0') {
	diag("%s: no dependencies", file);
	canonicalize("", file, buf, sizeof(buf));
	dep = strrchr(buf, '/');
	targ->name = strdup(dep + 1);
	if (targ->name == NULL)
	    efatal("target name strdup failed");
	dep = targ->name + strlen(targ->name);
	while (dep > targ->name && *(dep-1) != '.')
	    dep--;
	if (*dep == '\0') {
	    diag("%s: unable to generate filename");
	    return;
	}
	*dep = 'o';
    } else {
	targ->name = strdup(targ->name);
	if (targ->name == NULL)
	    efatal("target name strdup failed");
	if (_argbreak != ':') {
	    while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	    if (*ptr != ':') {
		diag("%s: missing colon in dependency file", file);
		return;
	    }
	    ptr++;
	}
    }
    while (*ptr != '\0') {
	dep = (char *)nxtarg(&ptr, " \t\\\n");
	if (*dep == '\0')
	    continue;
	status = shorten_name(dep);
	if (status < 0) {
	    warn("%s: unable to shorten '%s' - skipped", file, dep);
	    continue;
	}
	dep = strdup(dep);
	if (dep == NULL)
	    efatal("dependent strdup failed");
	tp = (status == 0 ? &targ->curdeps : &targ->stddeps);
	if (tp->argc == tp->max)
	    resize_table(tp);
	tp->argv[tp->argc++] = dep;
    }
    if (targets.argc == targets.max)
	resize_table(&targets);
    targets.argv[targets.argc++] = (char *)targ;
}

void
read_dependencies(void)
{
    char *file;
    int i;

    depfile_bufsize = (8*1024)+1;
    depfile_buffer = malloc(depfile_bufsize);
    if (depfile_buffer == NULL)
	efatal("depfile_buffer realloc failed");
    for (i = 0; i < dependfiles.argc; i++) {
	file = dependfiles.argv[i];
	read_target_dependencies(file);
    }
}

int
#ifdef NO_ANSI_CC
cmp_targets(v1, v2)
struct target **v1;
struct target **v2;
#else
cmp_targets(const void *v1, const void *v2)
#endif
{
    struct target **t1 = (struct target **)v1;
    struct target **t2 = (struct target **)v2;

    return(strcmp((*t1)->name, (*t2)->name));
}

int
#ifdef NO_ANSI_CC
compare_targets(t1, t2)
char *t1;
char *t2;
#else
compare_targets(char *t1, char *t2)
#endif
{
    char *p;
    int cmp;

    p = t1 + strlen(t1) - 1;
    if (*p-- != '\n')
	return(-1);
    if (*p != ':')
	return(-1);
    *p = '\0';
    cmp = strcmp(t1, t2);
    *p = ':';
    return(cmp);
}

void
update_database(void)
{
    char buf[MAXPATHLEN];
    char oldbuf[MAXPATHLEN];
    char buffer[BUFSIZ];
    FILE *inf, *outf;
    int i;
    struct target *targ;
    int need_header;
    int eof;
    int cmp;

    if (targets.argc == 0)
	return;
    qsort(targets.argv, targets.argc, sizeof(char *), cmp_targets);
if (debug) {
for (i = 0; i < targets.argc; i++) {
targ = (struct target *) targets.argv[i];
printf("curdeps[%d]\n", i);
print_table(&targ->curdeps);
printf("curdeps[%d]\n", i);
print_table(&targ->stddeps);
}
}
    (void) concat(buf, sizeof(buf), outfile, ".tmp", NULL);
    (void) unlink(buf);
    if ((outf = fopen(buf, "w")) == NULL) {
	ewarn("unable to open %s for write", buf);
	(void) unlink(buf);
	exit(1);
    }
    if ((inf = fopen(outfile, "r")) == NULL) {
	if (errno != ENOENT) {
	    ewarn("unable to open %s for read", outfile);
	    (void) fclose(outf);
	    (void) unlink(buf);
	    exit(1);
	}
	for (i = 0; i < targets.argc; i++)
	    output_target(outf, (struct target *) targets.argv[i], TRUE);
	if (ferror(outf) || fclose(outf) == EOF) {
	    ewarn("error writing %s", buf);
	    (void) fclose(outf);
	    (void) unlink(buf);
	    exit(1);
	}
	if (rename(buf, outfile) < 0)
	    efatal("rename %s to %s", buf, outfile);
	return;
    }
    i = 0;
    targ = (struct target *) targets.argv[i];
    while ((fgets(buffer, sizeof(buffer), inf)) != NULL) {
	if (memcmp("# dependents of ", buffer, 16) != 0) {
	    (void) fputs(buffer, outf);
	    continue;
	}
	cmp = compare_targets(buffer + 16, targ->name);
	if (cmp < 0) {
	    (void) fputs(buffer, outf);
	    continue;
	}
	if (cmp == 0) {
	    (void) fputs(buffer, outf);
	    eof = TRUE;
	    while ((fgets(buffer, sizeof(buffer), inf)) != NULL)
		if (memcmp("# dependents of ", buffer, 16) == 0) {
		    eof = FALSE;
		    break;
		}
	} else {
	    eof = FALSE;
	    (void) fputs("# dependents of ", outf);
	    (void) fputs(targ->name, outf);
	    (void) fputs(":\n", outf);
	}
	need_header = FALSE;
	for (;;) {
	    output_target(outf, targ, need_header);
	    if (++i == targets.argc) {
		if (!eof) {
		    (void) fputs("#\n", outf);
		    (void) fputs(buffer, outf);
		    ffilecopy(inf, outf);
		}
		break;
	    }
	    need_header = TRUE;
	    targ = (struct target *) targets.argv[i];
	    if (eof)
		continue;
	    cmp = compare_targets(buffer + 16, targ->name);
	    if (cmp > 0)
		continue;
	    if (cmp < 0) {
		(void) fputs("#\n", outf);
		(void) fputs(buffer, outf);
		break;
	    }
	    (void) fputs("#\n", outf);
	    (void) fputs(buffer, outf);
	    eof = TRUE;
	    while ((fgets(buffer, sizeof(buffer), inf)) != NULL)
		if (memcmp("# dependents of ", buffer, 16) == 0) {
		    eof = FALSE;
		    break;
		}
	    need_header = FALSE;
	}
	if (i == targets.argc)
	    break;
    }
    while (i < targets.argc)
	output_target(outf, (struct target *) targets.argv[i++], TRUE);
    if (ferror(inf) || fclose(inf) == EOF) {
	ewarn("error reading %s", outfile);
	(void) fclose(inf);
	(void) fclose(outf);
	(void) unlink(buf);
	exit(1);
    }
    if (ferror(outf) || fclose(outf) == EOF) {
	ewarn("error writing %s", buf);
	(void) fclose(outf);
	(void) unlink(buf);
	exit(1);
    }
    (void) concat(oldbuf, sizeof(oldbuf), outfile, ".old", NULL);
    (void) unlink(oldbuf);
    if (link(outfile, oldbuf) < 0) {
	ewarn("link %s to %s", outfile, oldbuf);
	(void) unlink(buf);
	exit(1);
    }
    if (rename(buf, outfile) < 0) {
	ewarn("rename %s to %s", buf, outfile);
	exit(1);
    }
}

void
output_target( FILE *outf, struct target *targ, int need_header )
{
    int i;

    if (need_header) {
	(void) fputs("#\n", outf);
	(void) fputs("# dependents of ", outf);
	(void) fputs(targ->name, outf);
	(void) fputs(":\n", outf);
    }
    for (i = 0; i < targ->curdeps.argc; i++) {
	(void) fputs(targ->name, outf);
	(void) fputs(": ", outf);
	(void) fputs(targ->curdeps.argv[i], outf);
	(void) putc('\n', outf);
    }
    if (!stdflag)
	return;
    for (i = 0; i < targ->stddeps.argc; i++) {
	(void) fputs("# ", outf);
	(void) fputs(targ->name, outf);
	(void) fputs(": <", outf);
	(void) fputs(targ->stddeps.argv[i], outf);
	(void) fputs(">\n", outf);
    }
}

void
remove_dependencies(void)
{
    char *file;
    int i;

    for (i = 0; i < dependfiles.argc; i++) {
	file = dependfiles.argv[i];
	if (rmflag && unlink(file) < 0)
	    ewarn("unlink %s", file);
    }
}

void print_usage(void)
{
    fprintf(stderr, "usage: %s [ options ] <dependency-files>\n", progname);
    fprintf(stderr, "options include:\n");
    fprintf(stderr, "    -I<include-directory>\n");
    fprintf(stderr, "    -K<include-directory>\n");
    fprintf(stderr, "    -file <output-file>\n");
    fprintf(stderr, "    -debug\n");
    fprintf(stderr, "    -rm\n");
    fprintf(stderr, "    -std\n");
    fprintf(stderr, "    -verbose\n");
    fprintf(stderr, "    -version\n");
    exit(1);
}
