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
 * $Log: srcacl.c,v $
 * Revision 1.6.13.1  1994/02/10  19:52:54  root
 * 	CR # 1049 - Compilation errors on sinix
 * 	[1994/02/10  19:52:39  root]
 *
 * Revision 1.6.10.2  1993/11/10  15:52:04  root
 * 	CR 463. Changed rindex to strrchr
 * 	[1993/11/10  15:51:16  root]
 * 
 * Revision 1.6.10.1  1993/11/09  16:54:33  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:53:12  damon]
 * 
 * Revision 1.6.6.3  1993/05/13  15:49:21  damon
 * 	CR 524. Moved srcacl to server dir
 * 	[1993/05/13  15:49:11  damon]
 * 
 * Revision 1.6.6.2  1993/04/29  21:27:06  marty
 * 	Prototyping
 * 	[1993/04/29  21:21:51  marty]
 * 
 * Revision 1.6.4.7  1992/12/03  17:23:19  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:09:45  damon]
 * 
 * Revision 1.6.4.6  1992/11/09  20:15:34  damon
 * 	CR 329. Added include of odedefs.h
 * 	[1992/11/09  20:10:33  damon]
 * 
 * Revision 1.6.4.5  1992/09/24  19:03:20  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:20:58  gm]
 * 
 * Revision 1.6.4.4  1992/09/15  16:09:16  damon
 * 	Changed salloc to strdup
 * 	[1992/09/15  16:04:56  damon]
 * 
 * Revision 1.6.4.3  1992/07/26  17:31:01  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/14  17:27:46  gm]
 * 
 * Revision 1.6.4.2  1992/06/15  19:24:02  damon
 * 	Synched with DCE changes
 * 	[1992/06/15  19:16:34  damon]
 * 
 * Revision 1.6.2.2  1992/04/09  16:43:52  mhickey
 * 	Fixed two logic errors that were causing segv's if the
 * 	wrong number of args were passed:
 * 	  1) if (argc < 1) quit - never true since by definition argc is
 * 	     always at least 1.  Changed to if (argc < 2) quit.
 * 
 * 	  2) if (argv != NULL && ...) - The thing to test is *argv.
 * 	     Changed to if (*argv != NULL && ...)
 * 
 * 	Defect 2516.
 * 	[1992/04/08  17:54:00  mhickey]
 * 
 * Revision 1.6  1991/12/05  21:13:49  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:14:07  mckeen]
 * 
 * 	now elides path from progname
 * 	[91/07/23  11:41:57  ezf]
 * 
 * 	added print_revision() and "-version" switch
 * 	[91/07/20  16:03:18  ezf]
 * 
 * 	Added progname constant
 * 	[91/01/09  15:59:26  mckeen]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:12:39  dwm]
 * 
 * Revision 1.4  90/10/07  21:55:34  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:11:12  gm]
 * 
 * Revision 1.3  90/07/17  12:37:23  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:31:26  gm]
 * 
 * Revision 1.2  90/05/24  23:12:57  devrcs
 * 	Created.
 * 	[90/05/07            gm]
 * 
 * $EndLog$
 */

/*
 * srcacl - access control list support for src tree commands
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ode/odedefs.h>
#include <ode/run.h>
#include <ode/util.h>
#include <sys/param.h>
#include <sys/stat.h>

const char *progname = "srcacl";

/*
 * PROTOTYPES
 */
void
exists_main( int argc, char **argv );
void
rm_main( int argc, char **argv );
void
cp_main( int argc, char **argv );

/* show command line options */
void print_usage(void)
{
    printf("usage: <cmd> <args> | -version\n");
}

void
main(int argc, char **argv)
{
    char **av = argv;
    register char *cp;

    progname = argv[0];
    if (argc < 2)
	quit(1, "usage: <cmd> <args> | -version\n");
    if ((cp = strrchr(argv[0], '/')) != NULL) {
	++cp;		/* skip past the '/' */
	progname = cp;	/* strip path from the command name */
    }
    argc--;
    argv++;
    if (*argv != NULL && strcmp(*argv, "-version") == 0)
	ui_print_revision();

    if (strcmp(progname, "exists") == 0)
	exists_main(argc, argv);
    if (strcmp(progname, "rm") == 0) {
	rm_main(argc, argv);
	exit(runv("/bin/rm", av));
    } else if (strcmp(progname, "version") == 0) {
	ui_print_revision();
    } else if (strcmp(progname, "cp") == 0) {
	cp_main(argc, argv);
	exit(runv("/bin/cp", av));
    }
    else
	quit(1, "%s: command not found\n", progname);
}

void
exists_main( int argc, char **argv )
{
    struct stat st;

    if (argc <= 0)
	quit(1, "exists: missing rcs file argument\n");
    if (argc > 1)
	quit(1, "exists: additional arguments to command\n");
    exit(stat(*argv, &st) < 0 || (st.st_mode&S_IFMT) != S_IFREG);
}

void
rm_main( int argc, char **argv )
{
    char topwd[MAXPATHLEN];
    char curwd[MAXPATHLEN];
    char filbuf[MAXPATHLEN];
    char dirbuf[MAXPATHLEN];
    int quiet = 0;
    int j, k;
    char *p;

    for (; argc > 0 && **argv == '-'; argc--, argv++) {
	p = *argv;
	if (*(p+1) == 'f' && *(p+2) == '\0') {
	    quiet++;
	    continue;
	}
	quit(1, "rm: unsupported option: %s\n", p);
    }
    if (argc <= 0)
	quit(1, "rm: missing source file argument\n");
    if (argc > 1)
	quit(1, "rm: additional arguments to command\n");
    p = strdup(*argv);
    if (p == NULL)
	quit(1, "strdup: %s\n", strerror(errno));
    path(p, dirbuf, filbuf);
    if (getcwd(topwd, sizeof(topwd)) == NULL)
	quit(1, "%s\n", strerror(errno));
    if (chdir(dirbuf) < 0) {
	if (quiet)
	    exit(0);
	quit(1, "chdir: %s\n", strerror(errno));
    }
    if (getcwd(curwd, sizeof(curwd)) == NULL)
	quit(1, "%s\n", strerror(errno));
    j = strlen(topwd);
    k = strlen(curwd);
    if (k < j || memcmp(curwd, topwd, j) != 0 ||
	(k > j && curwd[j] != '/'))
	quit(1, "argument not in correct directory tree\n");
    if (chdir(topwd) < 0)
	quit(1, "chdir: %s\n", strerror(errno));
}

void
cp_main( int argc, char **argv )
{
    char topwd[MAXPATHLEN];
    char curwd[MAXPATHLEN];
    char filbuf[MAXPATHLEN];
    char dirbuf[MAXPATHLEN];
    int needmakepath = 0;
    int preserve = 0;
    struct stat st;
    int i, j, k;
    char *p;

    for (; argc > 0 && **argv == '-'; argc--, argv++) {
	p = *argv;
	if (*(p+1) == 'p' && *(p+2) == '\0') {
	    preserve++;
	    continue;
	}
	quit(1, "cp: unsupported option: %s\n", p);
    }
    if (argc <= 0)
	quit(1, "cp: missing temporary file argument\n");
    if (stat(*argv, &st) < 0)
	quit(1, "cp: temporary file missing\n");
    if ((st.st_mode&S_IFMT) != S_IFREG)
	quit(1, "cp: temporary file not regular file\n");
    argc--;
    argv++;
    if (argc <= 0)
	quit(1, "cp: missing source file argument\n");
    if (argc > 1)
	quit(1, "cp: additional arguments to command\n");
    p = strdup(*argv);
    if (p == NULL)
	quit(1, "strdup: %s\n", strerror(errno));
    path(p, dirbuf, filbuf);
    if (getcwd(topwd, sizeof(topwd)) == NULL)
	quit(1, "%s\n", strerror(errno));
    if (chdir(dirbuf) < 0) {
	i = 0;
	do {
	    path(dirbuf, dirbuf, filbuf);
	    if (filbuf[0] == '.' &&
		(filbuf[1] == '\0' ||
		 (filbuf[1] == '.' && filbuf[2] == '\0')))
		quit(1, "illegal to have %s in pathname\n", filbuf);
	    if (i++ > 256)
		quit(1, "path/chdir infinite loop\n");
	} while (chdir(dirbuf) < 0);
	needmakepath++;
    }
    if (getcwd(curwd, sizeof(curwd)) == NULL)
	quit(1, "%s\n", strerror(errno));
    j = strlen(topwd);
    k = strlen(curwd);
    if (k < j || memcmp(curwd, topwd, j) != 0 ||
	(k > j && curwd[j] != '/'))
	quit(1, "argument not in correct directory tree\n");
    if (chdir(topwd) < 0)
	quit(1, "chdir: %s\n", strerror(errno));
    if (needmakepath && makepath(p, NULL, 1, 1) != 0)
	quit(1, "makepath failed\n");
}
