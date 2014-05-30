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
 * $Log: makepath.c,v $
 * Revision 1.7.8.1  1993/11/08  22:23:08  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/08  22:22:25  damon]
 *
 * Revision 1.7.6.5  1993/04/29  16:48:36  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:48:23  marty]
 * 
 * Revision 1.7.6.4  1993/04/20  21:58:11  marty
 * 	Use MAXPATHLEN instead of PATH_MAX.
 * 	[1993/04/20  21:57:54  marty]
 * 
 * Revision 1.7.6.3  1993/03/19  17:35:30  marty
 * 	Include odedefs.h.
 * 	[1993/03/19  17:35:11  marty]
 * 
 * Revision 1.7.6.2  1993/01/13  16:43:07  damon
 * 	CR 382. Removed PATH_MAX and _BLD cruft
 * 	[1993/01/05  20:27:05  damon]
 * 
 * Revision 1.7.2.7  1992/12/03  19:07:37  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:36:50  damon]
 * 
 * Revision 1.7.2.6  1992/11/06  19:40:11  damon
 * 	CR 296. Removed extra definitions
 * 	[1992/11/06  19:39:11  damon]
 * 
 * Revision 1.7.2.5  1992/09/24  18:58:41  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:17:29  gm]
 * 
 * Revision 1.7.2.4  1992/06/17  11:50:16  damon
 * 	2.1.1 touch-up
 * 	[1992/06/17  11:49:36  damon]
 * 
 * Revision 1.7.2.3  1992/06/16  23:08:51  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:49:06  damon]
 * 
 * Revision 1.7.2.2  1991/12/30  21:25:15  damon
 * 	port to sparc_sunos and libsb to libode transition
 * 	[1991/12/20  20:12:57  damon]
 * 
 * Revision 1.7  1991/12/05  20:45:35  devrcs
 * 	Added NO_SYS_LIMITS conditional.
 * 	[91/09/04  12:41:41  damon]
 * 
 * 	Fixed to build with _BLD
 * 	[91/08/28  20:43:34  mckeen]
 * 
 * 	Don't include odedefs under a _BLD and define an internal version of strdup
 * 	[91/08/01  13:18:42  mckeen]
 * 
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:04:59  mckeen]
 * 
 * 	now #includes <ode/odedefs.h>
 * 	[91/07/29  15:52:01  ezf]
 * 
 * 	added print_revision() and "-version" option
 * 	[91/06/03  16:04:25  ezf]
 * 
 * 	Changes for parallel make.
 * 	[91/04/21  17:20:08  gm]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:55:27  dwm]
 * 
 * Revision 1.5  90/10/07  21:51:22  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:04:57  gm]
 * 
 * Revision 1.4  90/07/27  11:09:06  devrcs
 * 	Added _BLD flag around include of limits.h
 * 	[90/07/11  12:16:00  pam]
 * 
 * 	Updated for new configuration.
 * 	Added define of PATH_MAX if not defined.
 * 	Moved here from usr/local/cmucs/etc.  Added "-" to read pathnames
 * 	from stdin.
 * 	[90/07/09  23:55:32  gm]
 * 
 * $EndLog$
 */
#if !defined(lint) && !defined(_NOIDENT)
static char rcsid[] = "@(#)$RCSfile: makepath.c,v $ $Revision: 1.7.8.1 $ (OSF) $Date: 1993/11/08 22:23:08 $";
#endif
/*
 *  makepath - create intermediate directories along a path
 *
 *  makepath path ...
 *
 *  Create any directories missing in path.
 */
#include <sys/param.h>

#include <limits.h>

#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ode/odedefs.h>

const char *progname;		/* program name */

static
char *fixpath( register char *pathname)
{
    register char *ls = NULL;
    register char *p = pathname;

    *p = *pathname;
    while (*pathname != '\0') {
	pathname++;
	while (*p == '/' && *pathname == '/')
	    pathname++;
	*++p = *pathname;
	if (*p == '/')
	    ls = p;
    }
    return(ls);
}

static int
mkpath( char *pathname, int trace)
{
    char *base;
    struct stat st;
    int ch, ididit;

    if (pathname == NULL) {
	fprintf(stderr, "%s: NULL path argument\n", progname);
	return(1);
    }

    pathname = (char *)strdup(pathname);
    if (pathname == NULL)
	fprintf(stderr, "%s: strdup failed\n", progname);
    base = fixpath(pathname);

    if (base == NULL || base == pathname) {
	fprintf(stderr, "%s: %s must have an imbedded '/' character\n",
		progname, pathname);
	return(1);
    }
    *base = '\0';
    base = pathname;
    if (*base == '/')
	base++;
    if (*base == '\0') {
	fprintf(stderr, "%s: illegal pathname %s\n", progname, pathname);
	return(1);
    }
    for (;;) {
	/* find end of this component */
	while (*base != '\0' && *base != '/')
	    base++;

	/* create path so far, if necessary */
	ch = *base;
	*base = '\0';
	if (stat(pathname, &st) < 0) {
	    if (mkdir(pathname, 0777) < 0) {
		if (errno != EEXIST) {
		    fprintf(stderr, "%s: unable to create directory %s: %s\n",
			    progname, pathname, strerror(errno));
		    return(1);
		}
		ididit = FALSE;
	    } else
		ididit = TRUE;
	    if (stat(pathname, &st) < 0) {
		fprintf(stderr, "%s: unable to stat directory %s: %s\n",
			progname, pathname, strerror(errno));
		return(1);
	    }
	    if (ididit && trace)
		fprintf(stderr, "%s: created directory\n", pathname);
	} else if ((st.st_mode&S_IFMT) != S_IFDIR) {
	    fprintf(stderr, "%s: %s is not a directory (mode %#o)\n",
		    progname, pathname, (st.st_mode&S_IFMT));
	    return(1);
	}
	if (ch == '\0')
	    break;
	*base++ = ch;
    }
    return(0);
}

void
main(int argc, char ** argv)
{
    int quiet = FALSE;
    int errors = 0;

    if (argc > 0) {
	if ((progname = strrchr(argv[0], '/')) == NULL)
	    progname = argv[0];
	else
	    progname++;
    } else
	progname = "makepath";
    argc--;
    argv++;

    if (argc > 0 && strcmp(argv[0], "-version") == 0)
    {
	ui_print_revision();
	exit(0);
    }

    if (argc > 0 && strcmp(argv[0], "-quiet") == 0) {
	quiet = TRUE;
	argc--;
	argv++;
    }

    if (argc == 0) {
	print_usage();
	exit(1);
    }

    if (strcmp(argv[0], "-") == 0) {	/* read stdin */
	char *pathname, *endp, *ptr;
	char buffer[MAXPATHLEN+1];

	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
	    ptr = buffer;
	    while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	    pathname = ptr;
	    while (*ptr && *ptr != '\n' && *ptr != ' ' && *ptr != '\t')
		ptr++;
	    endp = ptr;
	    while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	    if (*ptr && *ptr != '\n') {
		fprintf(stderr, "%s: bad pathname: %s\n", progname, buffer);
		continue;
	    }
	    *endp = 0;
	    if (*pathname == 0)
		continue;
	    errors |= mkpath(pathname, !quiet);
	}
    } else {
	while (argc > 0) {
	    errors |= mkpath(argv[0], !quiet);
	    argc--;
	    argv++;
	}
    }
    exit(errors);
}

/* show invocation options */
void print_usage(void)
{
    printf("usage: %s [ -version | -quiet ] path ...\n", progname);
}

