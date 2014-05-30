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
 * $Log: rcsacl.c,v $
 * Revision 1.14.11.2  1994/02/10  19:51:24  root
 * 	CR # 1049 - Compilation errors on sinix.
 * 	[1994/02/10  19:51:07  root]
 *
 * Revision 1.14.11.1  1993/12/31  20:48:00  marty
 * 	CR # 967 - bcreate -undo now removes rcs fiels with NONE or BIN comment leaders
 * 	[1993/12/31  20:47:46  marty]
 * 
 * Revision 1.14.9.2  1993/11/10  15:52:02  root
 * 	CR 463. Added include of stdlib.h
 * 	[1993/11/10  15:48:20  root]
 * 
 * Revision 1.14.9.1  1993/11/09  16:54:29  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:53:10  damon]
 * 
 * Revision 1.14.6.16  1993/06/08  18:48:03  marty
 * 	CR # 476 - Check for ancestry in descriptor field when removing rcs file.
 * 	[1993/06/08  18:44:06  marty]
 * 
 * Revision 1.14.6.15  1993/06/08  18:05:37  marty
 * 	Merged with changes from 1.14.6.14
 * 	[1993/06/08  18:05:30  marty]
 * 
 * 	CR # 476
 * 	[1993/06/08  18:03:57  marty]
 * 
 * 	CR # 476 - New "rm_rcs" command to delete empty rcs files.  No longer need side
 * 	effect to outdating a branch.
 * 	[1993/06/08  17:59:23  marty]
 * 
 * Revision 1.14.6.14  1993/06/08  18:02:26  marty
 * 	CR # 476 - New "rm_rcs" command to delete empty rcs files.  No longer need side
 * 	effect to outdating a branch.
 * 	[1993/06/08  17:59:23  marty]
 * 
 * Revision 1.14.6.13  1993/05/28  19:21:04  marty
 * 	CR # 558 - rios_aix build
 * 	[1993/05/28  19:20:54  marty]
 * 
 * Revision 1.14.6.12  1993/05/21  19:19:27  marty
 * 	CR # 387 - bcreate should remove rcs file after outdate.
 * 	[1993/05/21  19:19:07  marty]
 * 
 * Revision 1.14.6.11  1993/05/13  15:46:53  damon
 * 	CR 524. Moved rcsacl to server dir
 * 	[1993/05/13  15:46:26  damon]
 * 
 * Revision 1.14.6.10  1993/05/04  18:43:48  marty
 * 	Format of empty rcs file has changed.  The routine
 * 	for recogizing empty rcs files has been updated.
 * 	[1993/05/04  18:43:24  marty]
 * 
 * Revision 1.14.6.9  1993/05/03  21:46:38  marty
 * 	Fix more match problems
 * 	[1993/05/03  21:46:26  marty]
 * 
 * Revision 1.14.6.8  1993/05/03  21:40:37  marty
 * 	Fix remove_empty_file() code.
 * 	[1993/05/03  21:40:24  marty]
 * 
 * Revision 1.14.6.7  1993/05/03  21:27:18  marty
 * 	Changed the description of empty rcs file.
 * 	[1993/05/03  21:27:06  marty]
 * 
 * Revision 1.14.6.6  1993/04/29  21:14:05  marty
 * 	Prototype print_usage()
 * 	[1993/04/29  21:13:51  marty]
 * 
 * Revision 1.14.6.5  1993/03/31  20:47:54  damon
 * 	CR 452. Accept -q switch for more commands
 * 	[1993/03/31  20:47:42  damon]
 * 
 * Revision 1.14.6.4  1993/02/10  18:38:15  damon
 * 	CR 432. Accepts branch_ci -a
 * 	[1993/02/10  18:37:49  damon]
 * 
 * Revision 1.14.6.3  1993/01/20  22:01:34  damon
 * 	CR 196. Now allows -U switch to remove strict locking
 * 	[1993/01/20  22:00:59  damon]
 * 
 * Revision 1.14.6.2  1993/01/13  17:41:38  damon
 * 	CR 196. Removed rcs locking
 * 	[1993/01/04  20:34:14  damon]
 * 
 * Revision 1.14.4.9  1993/01/06  15:47:40  marty
 * 	Change getwd() to getcwd() for rios build.
 * 	[1993/01/06  15:47:11  marty]
 * 
 * Revision 1.14.4.8  1992/12/03  17:23:16  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:09:42  damon]
 * 
 * Revision 1.14.4.7  1992/11/23  16:01:58  damon
 * 	CR 336. Changed runv to runvp to use PATH instead of .cmd_prefix
 * 	[1992/11/23  16:01:46  damon]
 * 
 * Revision 1.14.4.6  1992/11/20  15:53:31  damon
 * 	CR 336. Removed references to .cmd_prefix
 * 	[1992/11/20  15:53:16  damon]
 * 
 * Revision 1.14.4.5  1992/11/09  20:15:32  damon
 * 	CR 329. Added include of odedefs.h
 * 	[1992/11/09  20:10:29  damon]
 * 
 * Revision 1.14.4.4  1992/09/24  19:03:17  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:20:51  gm]
 * 
 * Revision 1.14.4.3  1992/09/15  16:09:13  damon
 * 	Changed salloc to strdup
 * 	[1992/09/15  16:04:52  damon]
 * 
 * Revision 1.14.4.2  1992/06/15  19:23:56  damon
 * 	Synched with DCE changes
 * 	[1992/06/15  19:16:29  damon]
 * 
 * Revision 1.14.2.2  1992/04/09  16:43:45  mhickey
 * 	Fixed two logic errors that were causing segv's if the
 * 	wrong number of args were passed:
 * 	  1) if (argc < 1) quit - never true since by definition argc is
 * 	     always at least 1.  Changed to if (argc < 2) quit.
 * 
 * 	  2) if (argv != NULL && ...) - The thing to test is *argv.
 * 	     Changed to if (*argv != NULL && ...)
 * 
 * 	Defect 2514.
 * 	[1992/04/08  17:35:10  mhickey]
 * 
 * Revision 1.14  1991/12/17  21:01:28  devrcs
 * 	Allow access to TRUNK for merging
 * 	[1991/12/06  14:40:12  mckeen]
 * 
 * Revision 1.13  1991/12/05  21:13:43  devrcs
 * 	Fix for bug that does not remove the rcs file after a bcreate -undo (#75).
 * 	Modified the empty_desc array that is used to determine if a file has
 * 	no branches.  This was needed because RCS 5.5 file have a slightly
 * 	different format.
 * 	[91/10/29  12:53:13  rec]
 * 
 * 	Fixed bugs to support binary files.
 * 	[91/08/27  15:07:45  rec]
 * 
 * 	Modifications to support the branch_ci cover for RCS 5.5.
 * 	The old ci_main needs to be cleaned up.
 * 	[91/08/12  16:38:42  rec]
 * 
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:13:54  mckeen]
 * 
 * 	now elides path when setting progname
 * 	[91/07/23  11:41:30  ezf]
 * 
 * 	added print_revision() and "-version" switch
 * 	[91/07/20  16:02:33  ezf]
 * 
 * 	Added progname constant
 * 	[91/01/09  15:59:12  mckeen]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:57:10  dwm]
 * 
 * Revision 1.11  90/10/07  21:55:24  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:10:59  gm]
 * 
 * Revision 1.10  90/09/13  13:04:43  devrcs
 * 	Added code to recognize -s<state> rcs commands.
 * 	[90/08/25            gm]
 * 
 * Revision 1.9  90/08/09  14:42:31  devrcs
 * 	Added code to remove "almost" empty files.
 * 	[90/07/26  13:59:54  gm]
 * 
 * Revision 1.8  90/07/17  12:37:16  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:31:15  gm]
 * 
 * Revision 1.7  90/05/24  23:12:52  devrcs
 * 	Separated code into submodules for each command.  Removed kerberos
 * 	ACL checks, branches are now always ok, trunk is always off limits.
 * 	[90/05/06  13:51:17  gm]
 * 
 * Revision 1.6  90/04/14  00:53:10  devrcs
 * 	Added support for outdate ranges and reworked branch/trunk
 * 	acl tests.
 * 	[90/03/10  08:05:39  gm]
 * 
 * Revision 1.5  90/02/23  00:44:13  devrcs
 * 	Changed to understand about shared branches.
 * 	[90/02/07  14:31:49  gm]
 * 
 * Revision 1.4  90/01/18  08:53:09  gm
 * 	Added support for "rcs -[Nn]<symbol>[:<rev>]" without restriction.
 * 	[90/01/08            gm]
 * 
 * Revision 1.3  90/01/02  19:59:33  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.2  89/12/26  10:48:34  gm
 * 	Created.
 * 	[89/12/23            gm]
 * 
 * $EndLog$
 */
#if !defined(lint) && !defined(_NOIDENT)
static const char rcsid[] = "@(#)$RCSfile: rcsacl.c,v $ $Revision: 1.14.11.2 $ (OSF) $Date: 1994/02/10 19:51:24 $";
#endif
/*
 * rcsacl - access control list support for rcs tree commands
 */
#include <ode/odedefs.h>
#include <ode/run.h>
#include <ode/util.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

const char *progname = "rcsacl";

static char *outdate_file = NULL;

/*
 * PROTOTYPES
 */
int
nrevfields( char *rev, int isodd );
void
exists_main( int argc, char **argv );
void
rcs_main( int argc, char **argv );
void
remove_empty_file(void);
void
ci_main( int argc, char **argv );
void
branch_ci_main( int argc, char **argv );
void
co_main( int argc, char **argv );
void
rcsdiff_main( int argc, char **argv );
void
get_one_line( char *file, char *line );

/* show command line options */
void print_usage(void)
{
	printf("usage: <cmd> <args> | -version\n");
}

void
main(int argc, char ** argv)
{
    char **av = argv;
    int status;
    register char *cp;

    if (argc < 2)
	quit(1, "usage: <cmd> <args> | -version\n");
    progname = argv[0];
    if ((cp = strrchr(argv[0], '/')) != NULL) {
	++cp;		/* point beyond the '/' */
	progname = cp;	/* strip the path from the command name */
    }
    argc--;
    argv++;
    if (*argv != NULL && strcmp(*argv, "-version") == 0)
	ui_print_revision();

    if (strcmp(progname, "exists") == 0)
	exists_main(argc, argv);
    if (strcmp(progname, "rcs") == 0)
	rcs_main(argc, argv);
    else if (strcmp(progname, "rm_rcs") == 0) {
	outdate_file = *argv;
	remove_empty_file();
	exit ( 0 );
    } else if (strcmp(progname, "version") == 0)
	ui_print_revision();
    else if (strcmp(progname, "ci") == 0)
	ci_main(argc, argv);
    else if (strcmp(progname, "branch_ci") == 0)
	branch_ci_main(argc, argv);
    else if (strcmp(progname, "co") == 0)
	co_main(argc, argv);
    else if (strcmp(progname, "rcsdiff") == 0)
	rcsdiff_main(argc, argv);
    else
	quit(1, "%s: command not found\n", progname);
/*
    get_one_line(".cmd_prefix", cmd_prefix);
    (void) concat(buf, sizeof(buf),
		  cmd_prefix, ":/bin:/usr/bin:/usr/ucb", NULL);
    (void) setenv("PATH", buf, 1);
    (void) concat(command, sizeof(command), cmd_prefix, "/", progname, NULL);
    status = runv(command, av);
*/
    status = runvp( progname, av);
    exit(status);
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
rcs_main( int argc, char **argv )
{
    char topwd[MAXPATHLEN];
    char curwd[MAXPATHLEN];
    char filbuf[MAXPATHLEN];
    char dirbuf[MAXPATHLEN];
    char *user;
    int userlen;
    int quiet = 0;
    int init = 0;
    int namesymbol = 0;
    int comment = 0;
    int state = 0;
    int lock = 0;
    int unlock = 0;
    int outdate = 0;
    int finish_outdate = 0;
    int needmakepath = 0;
    int isrange = 0;
    int i, j, k;
    char *p, *q;

    if ((user = getenv("USER")) == NULL)
	quit(1, "rcs: undefined user\n");
    userlen = strlen(user);
    for (; argc > 0 && **argv == '-'; argc--, argv++) {
	p = *argv;
	if (*(p+1) == 'q' && *(p+2) == '\0') {
	    quiet++;
	    continue;
	}
	if (*(p+1) == 'N' || *(p+1) == 'n') {
	    namesymbol++;
	    p += 2;
	    if ((*p < 'A' || *p > 'Z') &&
		(memcmp(p, user, userlen) != 0 || *(p+userlen) != '_'))
		quit(1, "rcs: symbol must begin with your user id\n");
	    while (*p != '\0' && *p != ':')
		p++;
	    if (*p == '\0' && quiet)
		finish_outdate++;
	    continue;
	}
	if (*(p+1) == 'c') {
	    comment++;
	    continue;
	}
	if (*(p+1) == 's') {
	    state++;
	    continue;
	}
	if (strcmp(p, "-i") == 0) {
	    init++;
	    argc--;
	    argv++;
	    if (argc <= 0 || strcmp(*argv, "-t/dev/null") != 0)
		quit(1, "rcs: -i must be followed by -t/dev/null\n");
	    continue;
	}
	if (*(p+1) == 'U') {
	    continue;
	}
	if (*(p+1) == 'u') {
	    p += 2;
	    if (*p < '0' || *p > '9')
		quit(1, "must use numeric revision for rcs\n");
	    if (nrevfields(p, 0) <= 2)
		quit(1, "rcs: should not be unlocking the trunk\n");
	    unlock++;
	    continue;
	}
	if ((*(p+1) == 'k') && (*(p+2) == 'o'))
	    continue;
	if (*(p+1) == 'l') {
	    p += 2;
	    if (*p < '0' || *p > '9')
		quit(1, "must use numeric revision for rcs\n");
/*	    if (nrevfields(p, 0) <= 2)
		quit(1, "rcs: should not be locking the trunk\n");
*/	    lock++;
	    continue;
	}
	if (*(p+1) == 'o') {
	    p += 2;
	    q = p;
	    while (*q != '\0') {
		if (*q == '-') {
		    *q = '\0';
		    isrange++;
		    break;
		}
		q++;
	    }
	    if (*p == '\0' && !isrange)
		quit(1, "invalid outdate revision specification\n");
	    if (*p != '\0' && nrevfields(p, 0) <= 2)
		quit(1, "rcs: should not outdate the trunk\n");
	    if (isrange) {
		*q++ = '-';
		if (*q == '\0')
		    quit(1, "invalid outdate revision specification\n");
		if (nrevfields(q, 0) <= 2)
		    quit(1, "rcs: should not outdate the trunk\n");
	    }
	    outdate++;
	    continue;
	}
	quit(1, "rcs: unsupported option: %s\n", p);
    }
    if (argc <= 0)
	quit(1, "rcs: missing rcs file argument\n");
    if (argc > 1)
	quit(1, "rcs: additional arguments to command\n");
    p = strdup(*argv);
    if (p == NULL)
	quit(1, "strdup: %s\n", strerror(errno));
    path(p, dirbuf, filbuf);
    j = strlen(filbuf);
    if (filbuf[j-2] != ',' || filbuf[j-1] != 'v')
	quit(1, "argument to rcs must be an rcs file\n");
    if ((char *)getcwd(topwd, sizeof(topwd)) == NULL)
	quit(1, "%s\n", topwd);
    if (chdir(dirbuf) < 0) {
	if (!init)
	    quit(1, "chdir: %s\n", strerror(errno));
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
    if ((char *)getcwd(curwd, sizeof(curwd)) == NULL)
	quit(1, "%s\n", curwd);
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

void
ci_main( int argc, char **argv )
{
    char topwd[MAXPATHLEN];
    char curwd[MAXPATHLEN];
    char filbuf[MAXPATHLEN];
    char dirbuf[MAXPATHLEN];
    char *user;
    int userlen;
    int force = 0;
    int update = 0;
    int msg = 0;
    int lock = 0;
    int unlock = 0;
    int createbranch = 0;
    int revision = 0;
    int state = 0;
    int date = 0;
    struct stat st;
    int j, k;
    char *p;

    if ((user = getenv("USER")) == NULL)
	quit(1, "ci: undefined user\n");
    userlen = strlen(user);
    for (; argc > 0 && **argv == '-'; argc--, argv++) {
	p = *argv;
	if (*(p+1) == 'b' && *(p+2) == '\0') {
	    createbranch++;
	    argc--;
	    argv++;
	    if (argc <= 0)
		quit(1, "ci: -b must be followed by -N<name>\n");
	    p = *argv;
	    if (*p != '-' || *(p+1) != 'N')
		quit(1, "ci: -b must be followed by -N<name>\n");
	    p += 2;
	    if ((*p < 'A' || *p > 'Z') &&
		((memcmp(p, user, userlen) != 0 || *(p+userlen) != '_')))
		quit(1, "ci: symbol must begin with your user id\n");
	    continue;
	}
	if (*(p+1) == 'l' && *(p+2) == '\0') {
	    lock++;
	    continue;
	}
	if (*(p+1) == 'u' && *(p+2) == '\0') {
	    unlock++;
	    continue;
	}
	if (*(p+1) == 'f' && *(p+2) == '\0') {
	    force++;
	    continue;
	}
	if (*(p+1) == 'd') {
	    date++;
	    continue;
	}
	if (*(p+1) == 's') {
	    state++;
	    continue;
	}
	if (*(p+1) == 'u') {
	    p += 2;
	    if (*p < '0' || *p > '9')
		quit(1, "must use numeric revision for check-in\n");
/*	    if (nrevfields(p, !createbranch) <= (!createbranch ? 1 : 2) &&
		!createbranch)
		quit(1, "ci: should not check-in onto the trunk\n");
*/	    update++;
	    continue;
	}
	if (*(p+1) == 'r') {
	    p += 2;
	    if (*p < '0' || *p > '9')
		quit(1, "must use numeric revision for check-in\n");
/*
	    if (nrevfields(p, 0) <= 2 &&
		!createbranch && strcmp(p, "1.1") != 0)
		quit(1, "ci: only revision 1.1 is permitted\n");
*/
	    revision++;
	    continue;
	}
	if (*(p+1) == 'm') {
	    msg++;
	    continue;
	}
	if (*(p+1) == 'q' && *(p+2) == '\0') {
	    continue;
	}
	quit(1, "ci: unsupported option: %s\n", p);
    }
    if (!revision && !update)
	quit(1, "ci: must specify revision to checkin\n");
    if (argc <= 0)
	quit(1, "ci: missing temporary file argument\n");
/*
    get_one_line(".temp_prefix", temp_prefix);
    if (strncmp(*argv, temp_prefix, strlen(temp_prefix)) != 0)
	quit(1, "ci: invalid temporary file\n");
*/
    if (stat(*argv, &st) < 0)
	quit(1, "ci: temporary file missing\n");
    if ((st.st_mode&S_IFMT) != S_IFREG)
	quit(1, "ci: temporary file not regular file\n");
/*
    if (revision && !createbranch && st.st_size != 0)
	quit(1, "ci: initial revision of file must be empty\n");
*/
    argc--;
    argv++;
    if (argc <= 0)
	quit(1, "ci: missing rcs file argument\n");
    if (argc > 1)
	quit(1, "ci: additional arguments to command\n");
    p = strdup(*argv);
    if (p == NULL)
	quit(1, "strdup: %s\n", strerror(errno));
    path(p, dirbuf, filbuf);
    j = strlen(filbuf);
    if (filbuf[j-2] != ',' || filbuf[j-1] != 'v')
	quit(1, "argument to check-in must be an rcs file\n");
    if ((char *)getcwd(topwd, sizeof(topwd)) == NULL)
	quit(1, "%s\n", topwd);
    if (chdir(dirbuf) < 0)
	quit(1, "chdir: %s\n", strerror(errno));
    if ((char *)getcwd(curwd, sizeof(curwd)) == NULL)
	quit(1, "%s\n", curwd);
    j = strlen(topwd);
    k = strlen(curwd);
    if (k < j || memcmp(curwd, topwd, j) != 0 ||
	(k > j && curwd[j] != '/'))
	quit(1, "argument not in correct directory tree\n");
    if (chdir(topwd) < 0)
	quit(1, "chdir: %s\n", strerror(errno));
}

void
branch_ci_main( int argc, char **argv )
{
   char topwd[MAXPATHLEN];
   char curwd[MAXPATHLEN];
   char filbuf[MAXPATHLEN];
   char dirbuf[MAXPATHLEN];
   char *user;
   int userlen;
   int revision = 0;
   int symbol = 0;
   struct stat st;
   int j, k;
   char *p;

   if ((user = getenv("USER")) == NULL)
     quit(1, "branch_ci: undefined user\n");
   userlen = strlen(user);
   for (; argc > 0 && **argv =='-'; argc--, argv++)  {
     p = *argv;
     if (*(p+1) == 'r' && *(p+2) != '\0')  {
       revision++;
       continue;
     }
     if (*(p+1) == 'a') {
       continue;
     }
     if (*(p+1) == 'c') {
       continue;
     }
     if (*(p+1) == 'N' && *(p+2) != '\0')  {
       symbol++;
/*
       p += 2;
       if ((*p > 'A' && *p < 'Z') &&
	   ((memcmp(p, user, userlen) != 0 || *(p+userlen) != '_')))
	 quit(1, "branch_ci: symbol must begin with your user id\n");
*/
       continue;
     }
     quit(1, "branch_ci: unsupported option: %s\n", p);
   }
   if (!revision)
    quit(1, "branch_ci: must specify revision to check in\n");
   if (!symbol)
     quit(1, "branch_ci: must specify symbol to check in\n");
   if (argc <= 0)
     quit(1, "branch_ci: missing temporary file argument\n");
/*
   get_one_line(".temp_prefix", temp_prefix);
   if (strncmp(*argv, temp_prefix, strlen(temp_prefix)) != 0)
     quit(1, "branch_ci: invalid temporary file\n");
*/
   if (stat(*argv, &st) < 0)
     quit(1, "branch_ci: temporary file missing\n");
   if ((st.st_mode&S_IFMT) != S_IFREG)
     quit(1, "branch_ci: temporary file not regular file\n");
   argc--;
   argv++;
   if (argc <= 0)
     quit(1, "branch_ci: missing rcs file argument\n");
   if (argc > 1)
     quit(1, "branch_ci: additional arguments to command\n");
   p = strdup(*argv);
   if (p == NULL)
     quit(1, "strdup: %s\n", strerror(errno));
   path(p, dirbuf, filbuf);
   j = strlen(filbuf);
   if (filbuf[j-2] != ',' || filbuf[j-1] != 'v')
     quit(1, "argument to check-in must be an rcs file\n");
   if ((char *)getcwd(topwd, sizeof(topwd)) == NULL)
     quit(1, "%s\n", topwd);
   if (chdir(dirbuf) < 0)
     quit(1, "chdir: %s\n", strerror(errno));
   if ((char *)getcwd(curwd, sizeof(curwd)) == NULL)
     quit(1, "%s\n", curwd);
   j = strlen(topwd);
   k = strlen(curwd);
   if (k < j || memcmp(curwd, topwd, j) != 0 ||
       (k > j && curwd[j] != '/'))
     quit(1, "argument not in correct directory tree\n");
   if (chdir(topwd) < 0)
     quit(1, "chdir: %s\n", strerror(errno));
}

void
co_main( int argc, char **argv )
{
    char topwd[MAXPATHLEN];
    char curwd[MAXPATHLEN];
    char filbuf[MAXPATHLEN];
    char dirbuf[MAXPATHLEN];
    int istrunk = 0;
    int quiet = 0;
    int print = 0;
    int lock = 0;
    int revision = 0;
    struct stat st;
    int j, k;
    char *p;

    for (; argc > 0 && **argv == '-'; argc--, argv++) {
	p = *argv;
	if (*(p+1) == 'q' && *(p+2) == '\0') {
	    quiet++;
	    continue;
	}
	if (*(p+1) == 'l' && *(p+2) == '\0') {
	    lock++;
	    continue;
	}
	if (*(p+1) == 'k' && *(p+2) == 'o') {
	  continue;
	}
	if (*(p+1) == 'p') {
	    p += 2;
	    if (*p < '0' || *p > '9')
		quit(1, "must use numeric revision for check-out\n");
	    if (nrevfields(p, 0) <= 2)
		istrunk++;
	    print++;
	    continue;
	}
	if (*(p+1) == 'r') {
	    p += 2;
	    if (*p < '0' || *p > '9')
		quit(1, "must use numeric revision for check-out\n");
	    if (nrevfields(p, 0) <= 2)
		istrunk++;
	    revision++;
	    continue;
	}
	quit(1, "co: unsupported option: %s\n", p);
    }
    if (!print && !revision)
	quit(1, "co: must specify revision to check-out\n");
/*    if (istrunk && lock)
	quit(1, "check-out should not lock the trunk\n");
*/    if (revision) {
	if (argc <= 0)
	    quit(1, "co: missing temporary file argument\n");
/*
	get_one_line(".temp_prefix", temp_prefix);
	if (strncmp(*argv, temp_prefix, strlen(temp_prefix)) != 0)
	    quit(1, "co: invalid temporary file\n");
*/
	if (stat(*argv, &st) == 0)
	    quit(1, "co: temporary file already exists\n");
	argc--;
	argv++;
    }
    if (argc <= 0)
	quit(1, "co: missing rcs file argument\n");
    if (argc > 1)
	quit(1, "co: additional arguments to command\n");
    p = strdup(*argv);
    if (p == NULL)
	quit(1, "strdup: %s\n", strerror(errno));
    path(p, dirbuf, filbuf);
    j = strlen(filbuf);
    if (filbuf[j-2] != ',' || filbuf[j-1] != 'v')
	quit(1, "argument to check-out must be an rcs file\n");
    if ((char *)getcwd(topwd, sizeof(topwd)) == NULL)
	quit(1, "%s\n", topwd);
    if (chdir(dirbuf) < 0)
	quit(1, "chdir: %s\n", strerror(errno));
    if ((char *)getcwd(curwd, sizeof(curwd)) == NULL)
	quit(1, "%s\n", curwd);
    j = strlen(topwd);
    k = strlen(curwd);
    if (k < j || memcmp(curwd, topwd, j) != 0 ||
	(k > j && curwd[j] != '/'))
	quit(1, "argument not in correct directory tree\n");
    if (chdir(topwd) < 0)
	quit(1, "chdir: %s\n", strerror(errno));
}

void
rcsdiff_main( int argc, char **argv )
{
    /* nothing worth checking... */
}

int
nrevfields( char *rev, int isodd )
{
    int i = 0;

    for (;;) {
	if (!isodd) {
	    if (*rev < '0' || *rev > '9')
		quit(1, "invalid revision specification\n");
	    while (*rev >= '0' && *rev <= '9')
		rev++;
	    if (*rev++ != '.')
		quit(1, "invalid revision specification\n");
	    i++;
	} else
	    isodd = 0;
	if (*rev < '0' || *rev > '9')
	    quit(1, "invalid revision specification\n");
	while (*rev >= '0' && *rev <= '9')
	    rev++;
	i++;
	if (*rev == '\0')
	    return(i);
	if (*rev++ != '.')
	    quit(1, "invalid revision specification\n");
    }
}

void
get_one_line( char *file, char *line )
{
    char buf[MAXPATHLEN];
    FILE *inf;
    char *ptr;

    inf = fopen(file, "r");
    if (inf == NULL)
	quit(1, "fopen: %s\n", strerror(errno));
    if (fgets(buf, sizeof(buf), inf) == NULL)
	quit(1, "fgets: %s\n", strerror(errno));
    if (ferror(inf) || fclose(inf) == EOF)
	quit(1, "error reading %s", file);
    if ((ptr = strchr(buf, '\n')) != NULL)
	*ptr = '\0';
    (void) strcpy(line, buf);
}


struct desc {
    const char *data;
    int match_all;
} empty_desc[] = {
        {"head	1.1;\n",		1},
	{"access;\n",			1},
	{"symbols;\n",			1},
	{"locks;\n",		1},
	{"comment	@",			0},
	{"\n",				1},
	{"\n",				1},
	{"1.1\n",				1},
	{"date	90.01.01.00.00.00;",				0},
	{"branches;\n",			1},
	{"next\t;",			0},
	{"\n",				1},
	{"\n",				1},
	{"desc\n",			1},
	{"@1.1.1.1>1.1;\n",				1},
	{"@\n",				1},
	{"\n",				1},
	{"\n",				1},
	{"1.1\n",				1},
	{"log\n",				1},
	{"@*** Initial Trunk Revision ***\n",	1},
	{"@\n",				1},
	{"text\n",				1},
	{"@@\n",				1},
	{0,				0}
};

void
remove_empty_file(void)
{
    char buf[MAXPATHLEN];
    FILE *fp;
    struct desc *dp;

    fp = fopen(outdate_file, "r");
    if (fp == NULL)
	return;
    for (dp = &empty_desc[0]; dp->data != 0; dp++) {
	if (fgets(buf, sizeof(buf), fp) == NULL)
	    return;
	if (ferror(fp))
	    return;
	if (dp->match_all) {
	    if (strcmp(buf, dp->data) == 0) {
		if (strcmp(buf, "desc\n") == 0) {
			/* check for ancestry information. */
			dp++;
			if (fgets(buf, sizeof(buf), fp) == NULL)
	    			return;
			if (ferror(fp))
	    			return;
			if (strcmp (buf, "@@\n") == 0) {
				dp++;
				continue;
			} else if (strcmp (buf, "@1.1.1.1>1.1;\n") == 0) {
				continue;
			} else	
				return;
		} else 
			continue;
	    }
	} else {
	    if (strncmp(buf, dp->data, strlen(dp->data)) == 0) {
		if ( (strncmp (buf, "comment\t@NONE@", 14) == 0) ||
		     (strncmp (buf, "comment\t@BIN@", 13) == 0) ) {
			/* Comment leaders NONE and BIN add an "expand"
			   line to the rcs file.  Skip over it. */
			if (fgets(buf, sizeof(buf), fp) == NULL)
                                return;
		}
	    	continue;
	    }
	}
	(void) fclose(fp);
	return;
    }
    if (fgets(buf, sizeof(buf), fp) != NULL)
	return;
    if (ferror(fp) || fclose(fp) == EOF)
	return;
    (void) unlink(outdate_file);
}
