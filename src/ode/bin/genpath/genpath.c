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
 * $Log: genpath.c,v $
 * Revision 1.7.10.2  1993/11/04  00:11:10  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  00:11:04  damon]
 *
 * Revision 1.7.10.1  1993/10/28  13:32:19  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:27  damon]
 * 
 * Revision 1.7.8.1  1993/08/05  18:13:46  damon
 * 	CR 617. Fixed use of concat
 * 	[1993/08/05  18:13:39  damon]
 * 
 * Revision 1.7.6.6  1993/05/28  13:51:31  marty
 * 	CR # 558 - type casting for rios_aix
 * 	[1993/05/28  13:51:18  marty]
 * 
 * Revision 1.7.6.5  1993/04/29  16:46:58  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:46:45  marty]
 * 
 * Revision 1.7.6.4  1993/04/15  17:05:28  marty
 * 	Add include of ode/interface.h
 * 	[1993/04/15  17:05:09  marty]
 * 
 * Revision 1.7.6.3  1993/01/29  14:47:36  damon
 * 	CR 419. Replace rc_file_field with get_rc_value
 * 	[1993/01/29  14:47:17  damon]
 * 
 * Revision 1.7.6.2  1993/01/25  18:55:04  damon
 * 	CR 275. Converted to ODE parser
 * 	[1993/01/25  18:54:33  damon]
 * 
 * Revision 1.7.2.7  1992/12/03  19:04:38  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:34:35  damon]
 * 
 * Revision 1.7.2.6  1992/11/13  15:19:42  root
 * 	Now includes ode/odedefs.h
 * 	Removed concat related declarations
 * 	[1992/11/13  14:53:40  root]
 * 
 * Revision 1.7.2.5  1992/09/24  18:58:38  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:17:22  gm]
 * 
 * Revision 1.7.2.4  1992/06/16  22:34:01  damon
 * 	more 2.1.1 touch-up
 * 	[1992/06/16  22:27:36  damon]
 * 
 * Revision 1.7.2.2  1991/12/30  21:24:52  damon
 * 	port to sparc_sunos and libsb to libode transition
 * 	[1991/12/20  20:12:38  damon]
 * 
 * Revision 1.7  1991/12/05  20:41:20  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:04:14  mckeen]
 * 
 * 	added print_revision() and "-version" switch
 * 	[91/06/03  15:54:45  ezf]
 * 
 * 	Removed references to parse_cmd_line and get_currents...
 * 	Replaced get_current with current_sb and current_set from
 * 	sbdata.c
 * 	[91/01/14  10:47:04  randyb]
 * 
 * 	Changed sdm to ode; prog to progname
 * 	[91/01/11  12:13:51  randyb]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:55:21  dwm]
 * 
 * Revision 1.5  90/10/07  21:51:13  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:04:44  gm]
 * 
 * Revision 1.4  90/08/09  14:41:40  devrcs
 * 	Updated for new location of sdm include files.
 * 	[90/08/05  13:51:59  gm]
 * 
 * Revision 1.3  90/07/17  12:34:37  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:29:40  gm]
 * 
 * Revision 1.2  90/05/24  21:57:20  devrcs
 * 	Support for empty SOURCEDIR.
 * 	[90/05/22            gm]
 * 
 * 	SOURCEDIR should not include source_base.
 * 	[90/05/16  19:02:03  gm]
 * 
 * 	Fixed bug in expand_flag routine.
 * 	[90/05/14            gm]
 * 
 * 	Changed so that you do not need a sandbox to run genpath.
 * 	[90/05/09            gm]
 * 
 * 	Created from cc/gcc cover.
 * 	[90/05/01  09:29:32  gm]
 * 
 * $EndLog$
 */
#if !defined(lint) && !defined(_NOIDENT)
static const char rcsid[] = "@(#)$RCSfile: genpath.c,v $ $Revision: 1.7.10.2 $ (OSF) $Date: 1993/11/04 00:11:10 $";
#endif
/*
 * program to generate command flags for sandboxes
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ode/interface.h>
#include <ode/misc.h>
#include <ode/odedefs.h>
#include <ode/parse_rc_file.h>
#include <ode/sandboxes.h>
#include <ode/util.h>

/*
 * PROTOTYPES
 */
char **
expand_flag(int * j, int *nargc, char **nargv, char * rel, char * search_path);
char *
path_relative_to(char * base_dir, char * curdir, int curdir_len);

UIINIT init [] = {
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { "*", UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))


const char *progname = "genpath";		/* program name */

void print_usage(void)
{
    fprintf(stderr, "usage: %s [ options ] [ switches ... ]\n", progname);
    fprintf(stderr, "options include:\n");
    fprintf(stderr, "    -rc <rc_file>\n");
    fprintf(stderr, "    -sb <sandbox_name>\n");
    fprintf(stderr, "    -sb_rc <sandbox_rc_file>\n");
    fprintf(stderr, "    -usage | -version\n");
    fprintf(stderr, "    -verbose\n");
    exit(1);
}

void
main(int argc, char ** argv)
{
    char *rcfile_source_base;
    char *rcfile_object_base;
    char *sandbox = NULL;
    char *basedir = NULL;
    char *sb_rcfile = NULL;
    char *usr_rcfile = NULL;
    char search_path[1024*2];
    char source_base[1024];
    char sourcedir[1024];
    char curdir[1024];
    int curdir_len;
    char *relpath = NULL;
    int i, j;
    char ch,*b,*p,*p2,*p3,**nargv;
    int nargc;
    char buf[1024+2];
    int verbose = 0;
    const char *space;
    struct rcfile rcfile;
    int read_rcfile;
    int in_objdir;
    char * arg;

    ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

    sandbox = ui_arg_value ( SB_OP, 1, 1 );
    sb_rcfile = NULL;
    usr_rcfile = ui_arg_value ( RC_OP, 1, 1 );

    memset(&rcfile, 0, sizeof(struct rcfile));
    read_rcfile = 0;

    if (read_rcfile ||
	(b = getenv("SOURCEBASE")) == NULL ||
	(p = getenv("SOURCEDIR")) == NULL) {
	read_rcfile = 1;
	if (current_sb (&sandbox, &basedir, &sb_rcfile, &usr_rcfile) != 0) {
	    ui_print ( VWARN, "%s: unable to get sandbox basedir\n", progname);
	    exit(1);
	}
	if (parse_rc_file(sb_rcfile, &rcfile) != 0) {
	    ui_print ( VWARN, "%s: unable to parse %s sandbox description\n",
		    progname, sandbox);
	    exit(1);
	}
	if ( get_rc_value ( "source_base", &rcfile_source_base, &rcfile, TRUE )
             == ERROR ) {
	    ui_print ( VWARN, "%s: source_base not defined\n", progname);
	    exit(1);
	}
	if (*rcfile_source_base != '/') {
	    fprintf(stderr, "%s: source_base is not an absolute path\n", progname);
	    exit(1);
	}
	if ( get_rc_value ( "object_base", &rcfile_object_base, &rcfile, TRUE )
             == ERROR ) {
	    fprintf(stderr, "%s: object_base not defined\n", progname);
	    exit(1);
	}
	if (*rcfile_object_base != '/') {
	    fprintf(stderr, "%s: object_base is not an absolute path\n", progname);
	    exit(1);
	}
	if ((b = getenv("SOURCEBASE")) == NULL) {
	    fprintf(stderr, "%s: SOURCEBASE is not defined\n", progname);
	    exit(1);
	}
	if ((p = getenv("SOURCEDIR")) == NULL) {
	    fprintf(stderr, "%s: SOURCEDIR is not defined\n", progname);
	    exit(1);
	}
    }
    (void) strcpy(source_base, b);
    ui_print ( VDETAIL, "[ SOURCEBASE %s ]\n", b);
    (void) strcpy(sourcedir, p);
    ui_print ( VDETAIL, "[ SOURCEDIR %s ]\n", p);

    if ((char *)getcwd(curdir, sizeof(curdir)) == NULL) {
	fprintf(stderr, "%s: getcwd .: %s\n", progname, curdir);
	exit(1);
    }
    curdir_len = strlen(curdir);
    if (curdir_len == 0 || curdir[0] != '/') {
	fprintf(stderr, "%s: getcwd returned bad directory \"%s\"\n",
		progname, curdir);
	exit(1);
    }
    ui_print ( VDETAIL, "[ curdir %s ]\n", curdir);

    if (read_rcfile || (p = getenv("OBJECTDIR")) != NULL) {
	if (read_rcfile)
	    p = rcfile_object_base;
	if (verbose)
	    fprintf(stderr, "[ OBJECTDIR %s ]\n", p);
	if (*p != '/') {
	    canonicalize(source_base, p, buf, sizeof(buf));
	    p = buf;
	}
	if (verbose)
	    fprintf(stderr, "[ object_base %s ]\n", p);
	relpath = path_relative_to(p, curdir, curdir_len);
	in_objdir = (relpath != NULL);
    } else
	in_objdir = 0;
    if (!in_objdir)
	relpath = path_relative_to(source_base, curdir, curdir_len);
    if (relpath == NULL) {
	fprintf(stderr, "%s: unable to find path within sandbox\n", progname);
	exit(1);
    }
    ui_print ( VDETAIL, "[ relative path %s ]\n", relpath);

    b = source_base;
    p = sourcedir;
    if (*p == '\0')
	(void) concat(search_path, sizeof(search_path), ":", b, relpath, NULL);
    else if (*relpath == '\0')
	(void) concat(search_path, sizeof(search_path), ":", b, ":", p, NULL);
    else {
	concat(search_path, sizeof(search_path), ":", b, relpath, NULL);
	p3 = search_path+strlen(search_path);
	for (;;) {
	    p2 = p;
	    while (*p && *p != ':')
		p++;
	    ch = *p;
	    *p = '\0';
	    if (*p2 != '/') {
		fprintf(stderr, "%s: SOURCEDIR contains a relative path\n",
			progname);
		exit(1);
	    }
	    concat(p3, search_path + sizeof(search_path) - p3,
			":", p2, relpath, NULL);
	    p3 = search_path+strlen(search_path);
	    if (ch == '\0')
		break;
	    *p++ = ch;
	}
    }
    ui_print ( VDETAIL, "[ search_path %s ]\n", search_path);

    nargc = argc;
    nargv = (char **)malloc(nargc*sizeof(char *));
    j = 0;	/* argument counter for new arg list */

    for ( i = 1; ( arg = ui_entry_value ( "*", i )) != NULL; i++ ) {
	if (arg[2] == '/') {
	    nargv[j++] = arg;
	    continue;
	}
	nargv = expand_flag(&j, &nargc, nargv, arg, search_path);
    } /* for */

    space = "";
    for (i = 0; i < j; i++) {
	ui_print ( VNORMAL, "%s%s", space, nargv[i]);
	space = " ";
    }
    if (j > 0)
	ui_print ( VNORMAL, "\n");
    exit(0);
}

char **
expand_flag(int * j, int *nargc, char **nargv, char * rel, char * search_path)
{
    char ibuf[1024+2];
    char ch;
    char *p;
    char *p2;
    char *p3;

    ibuf[0] = *rel++;
    ibuf[1] = *rel++;
    p = search_path;
    for (;;) {
	p2 = p;
	while (*p && *p != ':')
	    p++;
	ch = *p;
	*p = '\0';
	p3 = NULL;
	if (*p2 == '\0' || (*p2 == '.' && *(p2+1) == '\0'))
	    p3 = rel;
	else if (*rel == '\0' || (*rel == '.' && *(rel+1) == '\0'))
	    p3 = p2;
	if (p3 == NULL)
	    canonicalize(p2, rel, ibuf+2, sizeof(ibuf)-2);
	else if (*p3 == '/')
	    canonicalize("", p3, ibuf+2, sizeof(ibuf)-2);
	else {
	    canonicalize("", p3, ibuf+1, sizeof(ibuf)-1);
	    ibuf[1] = *(rel-1);
	    if (ibuf[2] == '\0') {
		ibuf[2] = '.';
		ibuf[3] = '\0';
	    }
	}
	(*nargc)++;
	nargv = (char **)realloc((char *)nargv, (*nargc)*sizeof(char *));
	nargv[(*j)++] = strdup(ibuf);
	if (ch == '\0')
	    break;
	*p++ = ch;
    }
    return(nargv);
}

/*
 * If we are within the directory subtree of base_dir, return the path
 * from there to the current directory.  Otherwise, return NULL.
 */
char *
path_relative_to(char * base_dir, char * curdir, int curdir_len)
{
    char errbuf[BUFSIZ];
    int save_errno;
    char basedir[1024];
    char *rpath;
    int len;

    if (chdir(base_dir) < 0) {
	save_errno = errno;
	(void) sprintf(errbuf, "%s: chdir %s", progname, base_dir);
	errno = save_errno;
	perror(errbuf);
	exit(1);
    }
    if ((char *) getcwd(basedir, sizeof(basedir)) == NULL) {
	fprintf(stderr, "%s: getcwd %s: %s\n", progname, base_dir, basedir);
	exit(1);
    }
    if (chdir(curdir) < 0) {
	save_errno = errno;
	(void) sprintf(errbuf, "%s: chdir %s", progname, base_dir);
	errno = save_errno;
	perror(errbuf);
	exit(1);
    }
    len = strlen(basedir);
    if (len == 0 || basedir[0] != '/') {
	fprintf(stderr, "%s: getcwd returned bad base directory \"%s\"\n",
		progname, basedir);
	exit(1);
    }
    if (curdir_len < len)
	return(NULL);
    if (memcmp(basedir, curdir, len) != 0)
	return(NULL);
    if (curdir[len] != '\0' && curdir[len] != '/')
	return(NULL);
    if ((rpath = strdup(curdir+len)) == NULL) {
	save_errno = errno;
	(void) sprintf(errbuf, "%s: strdup relative path", progname);
	errno = save_errno;
	perror(errbuf);
	exit(1);
    }
    return(rpath);
}
