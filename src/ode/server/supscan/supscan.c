/*
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
 * $Log: supscan.c,v $
 * Revision 1.3.8.3  1994/02/17  18:50:56  damon
 * 	CR 1056. Made collname_g and basedir_g extern
 * 	[1994/02/17  18:50:50  damon]
 *
 * Revision 1.3.8.2  1994/02/17  16:29:03  damon
 * 	CR 1056. Moved from /bin/sup/
 * 	[1994/02/17  16:28:33  damon]
 * 
 * Revision 1.3.8.1  1994/02/15  17:36:18  damon
 * 	CR 1051. Made pedantic changes
 * 	[1994/02/15  17:35:49  damon]
 * 
 * Revision 1.3.5.2  1993/05/04  18:50:29  damon
 * 	CR 435. Changed timevals from longs to time_t
 * 	[1993/05/04  18:50:20  damon]
 * 
 * Revision 1.3.2.4  1992/12/02  19:53:22  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:30  damon]
 * 
 * Revision 1.3.2.3  1992/11/11  18:34:24  damon
 * 	CR 329. Replaced explicit decs with include of portable.h
 * 	[1992/11/11  18:32:17  damon]
 * 
 * Revision 1.3.2.2  1992/09/24  19:00:42  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:19:42  gm]
 * 
 * Revision 1.3  1991/12/05  20:54:47  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:43  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:48:07  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:18:24  zeliff]
 * 
 * Revision 1.2  90/10/07  21:37:27  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:46  gm]
 * 
 * Revision 1.3  90/07/17  12:27:11  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:06:14  gm]
 * 
 * Revision 1.2  90/01/02  19:56:28  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:46  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.4  89/11/29  17:42:00  bww
 * 	Updated variable argument list usage.
 * 	[89/11/29  17:37:09  bww]
 * 
 * Revision 1.10  89/08/03  19:49:33  mja
 * 	Updated to use v*printf() in place of _doprnt().
 * 	[89/04/19            mja]
 * 
 * Revision 1.9  89/06/18  14:41:37  gm0w
 * 	Fixed up some notify messages of errors to use "SUP:" prefix.
 * 	[89/06/18            gm0w]
 * 
 * Revision 0.0  88/05/13            gm0w
 * 	Changed goaway to longjmp back to top-level to scan next
 * 	collection. [V7.6]
 * 	[88/05/13            gm0w]
 * 
 * Revision 0.0  88/02/19            gm0w
 * 	Added -f <filename> switch to scan all (or part) of the
 * 	collections in a file of collection/base-directory pairs.
 * 	[V7.5]
 * 	[88/02/19            gm0w]
 * 
 * Revision 0.0  87/12/27            gm0w
 * 	Removed nameserver support (which means to use a new
 * 	datafile).
 * 	[87/12/27            gm0w]
 * 
 * Revision 0.0  87/09/09            gm0w
 * 	Use case-insensitive hostname comparison.
 * 	[87/09/09            gm0w]
 * 
 * Revision 0.0  87/06/28            gm0w
 * 	Added code for "release" support. [V6.4]
 * 	[87/06/28            gm0w]
 * 
 * Revision 0.0  86/01/05            gm0w
 * 	Changed collection setup errors to be non-fatal. [V5.3]
 * 	[86/01/05            gm0w]
 * 
 * Revision 0.0  85/12/29            gm0w
 * 	Moved most of the scanning code to scan.c. [V4.2]
 * 	[85/12/29            gm0w]
 * 
 * Revision 0.0  85/11/02            gm0w
 * 	Added "-s" option.
 * 	[85/11/02            gm0w]
 * 
 * Revision 0.0  85/09/22            gm0w
 * 	Merged 4.1 and 4.2 versions together.
 * 	[85/09/22            gm0w]
 * 
 * Revision 0.0  85/06/04            sas
 * 	Created for 4.2 BSD.
 * 	[85/06/04            sas]
 * 
 * $EndLog$
 */
/*
 * supscan -- SUP Scan File Builder
 *
 * Usage: supscan [ -v ] collection [ basedir ]
 *	  supscan [ -v ] -f dirfile
 *	  supscan [ -v ] -s
 *	-f	"file" -- use dirfile instead of system coll.dir
 *	-s	"system" -- perform scan for system supfile
 *	-v	"verbose" -- print messages as you go
 *	collection	-- name of the desired collection if not -s
 *	basedir		-- name of the base directory, if not
 *			   the default or recorded in coll.dir
 *	dirfile		-- name of replacement for system coll.dir.
 */

#include <netdb.h>
#include <setjmp.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <string.h>
#include <ode/portable.h>
#include <ode/sup.h>
#include <ode/util.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PGMVERSION 6

/*******************************************
 ***    D A T A   S T R U C T U R E S    ***
 *******************************************/

struct collstruct {			/* one per collection to be upgraded */
	char *Cname;			/* collection name */
	char *Cbase;			/* local base directory */
	char *Cprefix;			/* local collection pathname prefix */
	struct collstruct *Cnext;	/* next collection */
};
typedef struct collstruct COLLECTION;

/*********************************************
 ***    G L O B A L   V A R I A B L E S    ***
 *********************************************/

int trace;				/* -v flag */

COLLECTION *firstC;			/* collection list pointer */
extern char *collname_g;		/* collection name */
extern char *basedir_g;			/* base directory name */
char *prefix;				/* collection pathname prefix */
time_t lasttime = 0;			/* time of last upgrade */
time_t scantime;			/* time of this scan */
int newonly = FALSE;			/* new files only */
jmp_buf sjbuf;				/* jump location for errors */

TREELIST *listTL;	/* list of all files specified by <coll>.list */
TREE *listT;		/* final list of files in collection */
TREE *refuseT = NULL;	/* list of all files specified by <coll>.list */

COLLECTION *c_g;

void
init ( int , char **);
COLLECTION *
getcoll( char *,char *,char *);
int localhost ( char *);

/*************************************
 ***    M A I N   R O U T I N E    ***
 *************************************/

void
main ( int argc, char **argv )
{

	init (argc,argv);		/* process arguments */
	for (c_g = firstC; c_g; c_g = c_g->Cnext) {
		collname_g = c_g->Cname;
		basedir_g = c_g->Cbase;
		prefix = c_g->Cprefix;
		(void) chdir (basedir_g);
		scantime = time ((time_t *)NULL);
		printf ("SUP Scan for %s starting at %s",collname_g,
			ctime (&scantime));
		(void) fflush (stdout);
		if (!setjmp (sjbuf)) {
			makescanlists (); /* record names in scan files */
			scantime = time ((time_t *)NULL);
			printf ("SUP Scan for %s completed at %s",collname_g,
				ctime (&scantime));
		} else
			printf ("SUP: Scan for %s aborted at %s",collname_g,
				ctime (&scantime));
		(void) fflush (stdout);
	}
	while ((c_g = firstC)) {
		firstC = firstC->Cnext;
		free (c_g->Cname);
		free (c_g->Cbase);
		if (c_g->Cprefix)  free (c_g->Cprefix);
		free ((char *)c_g);
	}
	exit (0);
}

/*****************************************
 ***    I N I T I A L I Z A T I O N    ***
 *****************************************/

void
usage (void)
{
	fprintf (stderr,"Usage: supscan [ -v ] collection [ basedir ]\n");
	fprintf (stderr,"       supscan [ -v ] -f dirfile\n");
	fprintf (stderr,"       supscan [ -v ] -s\n");
	exit (1);
}

void
init ( int argc, char **argv )
{
	char buf[STRINGLENGTH],fbuf[STRINGLENGTH],*p,*q;
	FILE *f;
	COLLECTION **c;
	int fflag,sflag;
	char *filename = NULL;

	trace = FALSE;
	fflag = FALSE;
	sflag = FALSE;
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 'f':
			fflag = TRUE;
			if (argc == 2)
				usage ();
			--argc;
			argv++;
			filename = argv[1];
			break;
		case 'v':
			trace = TRUE;
			break;
		case 's':
			sflag = TRUE;
			break;
		default:
			fprintf (stderr,"supscan: Invalid flag %s ignored\n",argv[1]);
			(void) fflush (stderr);
		}
		--argc;
		argv++;
	}
	if (!fflag) {
		(void) sprintf (fbuf,FILEDIRS,DEFDIR);
		filename = fbuf;
	}
	if (sflag) {
		if (argc != 1)
			usage ();
		firstC = NULL;
		c = &firstC;
		(void) sprintf (buf,FILEHOSTS,DEFDIR);
		if ((f = fopen (buf,"r")) == NULL)
			quit (1,"supscan: Unable to open %s\n",buf);
		while ((p = fgets (buf,STRINGLENGTH,f)) != NULL) {
			q = strchr (p,'\n');
			if (q)  *q = 0;
			if (strchr ("#;:",*p))  continue;
			collname_g = nxtarg (&p," \t=");
			p = skipover (p," \t=");
			if (!localhost (p))  continue;
			*c = getcoll(filename,strdup (collname_g),
					(char *)NULL);
			if (*c)  c = &((*c)->Cnext);
		}
		(void) fclose (f);
		return;
	}
	if (argc < 2 && fflag) {
		firstC = NULL;
		c = &firstC;
		if ((f = fopen (filename,"r")) == NULL)
			quit (1,"supscan: Unable to open %s\n",filename);
		while ((p = fgets (buf,STRINGLENGTH,f))) {
			q = strchr (p,'\n');
			if (q)  *q = 0;
			if (strchr ("#;:",*p))  continue;
			q = nxtarg (&p," \t=");
			p = skipover (p," \t=");
			*c = getcoll(filename,strdup (q),strdup (p));
			if (*c)  c = &((*c)->Cnext);
		}
		(void) fclose (f);
		return;
	}
	if (argc < 2 || argc > 3)
		usage ();
	firstC = getcoll(filename,strdup (argv[1]),
			argc > 2 ? strdup (argv[2]) : (char *)NULL);
}

COLLECTION *
getcoll( char *filename,char *collname,char *basedir )
{
	char buf[STRINGLENGTH],*p,*q;
	FILE *f;
	COLLECTION *c;

	if (basedir == NULL) {
		if ((f = fopen (filename,"r"))) {
			while ((p = fgets (buf,STRINGLENGTH,f))) {
				q = strchr (p,'\n');
				if (q)  *q = 0;
				if (strchr ("#;:",*p))  continue;
				q = nxtarg (&p," \t=");
				if (strcmp (q,collname) == 0) {
					p = skipover (p," \t=");
					basedir = strdup (p);
					break;
				}
			}
			(void) fclose (f);
		}
		if (basedir == NULL) {
			(void) sprintf (buf,FILEBASEDEFAULT,collname);
			basedir = strdup (buf);
		}
	}
	if (chdir(basedir) < 0) {
		fprintf (stderr,"supscan:  Can't chdir to base directory %s for %s\n",
			basedir,collname);
		return (NULL);
	}
	prefix = NULL;
	(void) sprintf (buf,FILEPREFIX,collname);
	if ((f = fopen (buf,"r"))) {
		while ((p = fgets (buf,STRINGLENGTH,f))) {
			q = strchr (p,'\n');
			if (q) *q = 0;
			if (strchr ("#;:",*p))  continue;
			prefix = strdup (p);
			if (chdir(prefix) < 0) {
				fprintf (stderr,"supscan: can't chdir to %s from base directory %s for %s\n",
					prefix,basedir,collname);
				return (NULL);
			}
			break;
		}
		(void) fclose (f);
	}
	if ((c = (COLLECTION *) malloc (sizeof(COLLECTION))) == NULL)
		quit (1,"supscan: can't malloc collection structure\n");
	c->Cname = collname;
	c->Cbase = basedir;
	c->Cprefix = prefix;
	c->Cnext = NULL;
	return (c);
}

#if __STDC__
void
goaway (const char *fmt,...)
#else
/* VARARGS */
void
goaway (va_alist)
va_dcl
#endif
{
#if !__STDC__
	const char *fmt;
#endif
	va_list ap;

#if __STDC__
	va_start(ap,fmt);
#else
	va_start(ap);
	fmt = va_arg(ap,char *);
#endif
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void) putc ('\n',stderr);
	(void) fflush (stderr);
	longjmp (sjbuf,TRUE);
}

int localhost ( char *host )
{
	int status;

	register struct hostent *h;
	static char myhost[STRINGLENGTH];
	if (*myhost == '\0') {
		status =  gethostname (myhost,sizeof (myhost));
		h = gethostbyname (myhost);
		if (h == NULL) quit (1,"supscan: can't find my host entry\n");
		(void) strcpy (myhost,h->h_name);
	}
	h = gethostbyname (host);
	if (h == NULL) return (0);
	return (strcasecmp (myhost,h->h_name) == 0);
}
