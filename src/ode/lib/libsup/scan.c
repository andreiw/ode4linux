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
 * $Log: scan.c,v $
 * Revision 1.3.14.6  1994/02/17  18:47:56  damon
 * 	CR 1056. Moved global decl of collname_g and basedir_g to here
 * 	[1994/02/17  18:47:12  damon]
 *
 * Revision 1.3.14.5  1994/02/17  16:24:15  damon
 * 	CR 1056. Moved from bin/sup
 * 	[1994/02/17  16:22:32  damon]
 * 
 * Revision 1.3.14.4  1994/02/15  20:37:37  damon
 * 	CR 1051. More pedantic
 * 	[1994/02/15  20:37:13  damon]
 * 
 * Revision 1.3.14.3  1994/02/15  17:36:08  damon
 * 	CR 1051. Made pedantic changes
 * 	[1994/02/15  17:35:44  damon]
 * 
 * Revision 1.3.14.2  1994/02/14  23:49:22  damon
 * 	CR 1051. Fixed type casting
 * 	[1994/02/14  23:49:05  damon]
 * 
 * Revision 1.3.14.1  1994/02/10  20:18:35  damon
 * 	CR 1051. Added include of stdlib, changed **scanF to *scanF
 * 	[1994/02/10  20:18:20  damon]
 * 
 * Revision 1.3.10.1  1993/09/01  20:55:14  root
 * 	CR 647. Removed filename length restriction
 * 	[1993/09/01  20:51:41  root]
 * 
 * Revision 1.3.8.2  1993/05/04  18:26:33  damon
 * 	CR 435. Changed longs to time_t for time vals
 * 	[1993/05/04  18:26:21  damon]
 * 
 * Revision 1.3.2.7  1992/12/02  19:52:46  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:02  damon]
 * 
 * Revision 1.3.2.6  1992/11/11  18:34:18  damon
 * 	CR 329. Replaced explicit decs with include of portable.h
 * 	[1992/11/11  18:32:02  damon]
 * 
 * Revision 1.3.2.5  1992/09/24  18:59:49  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/21  20:32:40  gm]
 * 
 * Revision 1.3.2.4  1992/06/16  23:09:01  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:57:57  damon]
 * 
 * Revision 1.3.5.3  1992/04/02  21:00:49  damon
 * 	Include limits.h if NO_SYS_LIMITS defined
 * 	[1992/04/02  20:56:30  damon]
 * 
 * Revision 1.3.5.2  1992/03/10  16:54:58  damon
 * 	Added conditional use of d_ino instead of d_fileno
 * 	  based on USE_D_INO
 * 	Port to sparc_sunos
 * 	Taken from latest, 1.3.2.2
 * 	[1992/03/10  16:48:44  damon]
 * 
 * Revision 1.3  1991/12/05  20:53:56  devrcs
 * 	include sys/limits.h to get NAME_MAX definition.
 * 	[91/09/04  16:40:01  marty]
 * 
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:15  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:46:45  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:16:47  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:16  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:22  gm]
 * 
 * Revision 1.4  90/07/17  12:26:31  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:04:03  gm]
 * 
 * Revision 1.3  90/06/29  14:18:36  devrcs
 * 	Removed references to defunct libcs library.
 * 	[90/06/23  15:01:32  gm]
 * 
 * Revision 1.2  90/01/02  19:56:12  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:32:52  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Added host=<hostfile> support to releases file.
 * 	[88/03/18            gm0w]
 * 
 * 	Added "rsymlink" recursive symbolic link quoting directive.
 * 	[88/03/11            gm0w]
 * 
 * 	Added code for "release" support.
 * 	[87/06/28            gm0w]
 * 
 * 	Lets see if we'll be able to write the scan file BEFORE
 * 	we collect the data for it.  Include sys/file.h and use
 * 	new definitions for access check codes.
 * 	[87/05/26            dwp]
 * 
 * 	Added type casting information for lint.
 * 	[87/05/20            gm0w]
 * 
 * 	Added check for newonly upgrade when lasttime is the same as
 * 	scantime.  This will save us the trouble of parsing the scanfile
 * 	when the client has successfully received everything in the
 * 	scanfile already.
 * 	[86/01/21            gm0w]
 * 
 * 	Clear Texec pointers in execT so that Tfree of execT will not
 * 	free command trees associated with files in listT.
 * 	[86/01/16            gm0w]
 * 
 * 	Added code to omit scanned files from list if we want new files
 * 	only and they are old.
 * 	[86/01/06            gm0w]
 * 
 * 	Major rewrite for protocol version 4.  Added version numbers to
 * 	scan file.  Also added mode of file in addition to flags.
 * 	Execute commands are now immediately after file information.
 * 	[85/12/29            gm0w]
 * 
 * 	Added comments to list file format.
 * 	[85/12/13            gm0w]
 * 
 * 	Added code to implement omitany.  Currently doesn't know about
 * 	{a,b,c} patterns.
 * 	[85/12/08            gm0w]
 * 
 * 	Created.
 * 	[85/10/07            gm0w]
 * 
 * $EndLog$
 */
/*
 * scan.c - sup list file scanner
 */

#include <ode/odedefs.h>
#include <ode/portable.h>
#include <ode/sup.h>
#include <ode/util.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <utime.h>
#include <unistd.h>
#include <dirent.h>
#ifndef NAME_MAX
#define NAME_MAX _POSIX_NAME_MAX
#endif

/*************************
 ***    M A C R O S    ***
 *************************/

#define SPECNUMBER 1000
	/* number of filenames produced by a single spec in the list file */

/*******************************************
 ***    D A T A   S T R U C T U R E S    ***
 *******************************************/

typedef enum {			/* release options */
	ONEXT,		OPREFIX,	OLIST,		OSCAN,
	OHOST
} OPTION;

static const char *options[] = {
	"next",		"prefix",	"list",		"scan",
	"host",
	0
};

typedef enum {			/* <collection>/list file lines */
	LUPGRADE,	LOMIT,		LBACKUP,	LEXECUTE,
	LINCLUDE,	LNOACCT,	LOMITANY,	LALWAYS,
	LFOLLOW,	LRFOLLOW,	LSYMLINK,	LRSYMLINK
} LISTTYPE;

static const char *ltname[] = {
	"upgrade",	"omit",		"backup",	"execute",
	"include",	"noaccount",	"omitany",	"always",
	"follow",	"rfollow",	"symlink",	"rsymlink",
	0
};

#define FALWAYS		FUPDATE

/* list file lines */
static TREE *upgT;			/* files to upgrade */
static TREE *flagsT;			/* special flags: BACKUP NOACCT */
static TREE *omitT;			/* recursize file omition list */
static TREE *omanyT;			/* non-recursize file omition list */
static TREE *followT;			/* symbolic links to follow */
static TREE *rfollowT;			/* recursively follow symbolic links */
static TREE *execT;			/* execute command list */

/*
 * FORWARD DECLARATIONS
 */
static void
makescan ( char *, char *);
static void
getscan ( char *, char *);
static int
listone ( TREE *, va_list ap );
static
omitanyone ( TREE *, va_list ap );
static void
chkscanfile ( const char *);
static void
doscan ( const char *);
static void
makescanfile ( const char *);
static
int getscanfile ( const char *);
static void
readlistfile ( char *);
void
cdprefix ( char * );
static void
expTinsert ( char *, TREE **, int , char *);
static void
listentry( char * , char * , char * , int );
static void
listname ( char *, struct stat *);
static void
listdir ( char *, int );
static
anyglob ( char *, char *);
static BOOLEAN
recordone ( TREE *, va_list ap );
static BOOLEAN
recordexec ( TREE *, va_list ap );

/*************************
 ***    E X T E R N    ***
 *************************/

extern char _argbreak;			/* break character from nxtarg */

extern TREELIST *listTL;		/* list of trees for scanning */
extern TREE *listT;			/* final list of files in collection */
extern TREE *refuseT;			/* files refused by client */

char *collname_g;			/* collection name */
char *basedir_g;			/* base directory name */
extern char *prefix;			/* collection pathname prefix */
extern time_t lasttime;			/* time of last upgrade */
extern time_t scantime;			/* time of this scan */
extern int trace;			/* trace directories */
extern int newonly;			/* new files only */

/*************************************************
 ***    L I S T   S C A N   R O U T I N E S    ***
 *************************************************/

static void
passdelim ( char **ptr, char delim) /* skip over delimiter */
{
	*ptr = skipover (*ptr, " \t");
	if (_argbreak != delim && **ptr == delim) {
		(*ptr)++;
		*ptr = skipover (*ptr, " \t");
	}
}

static
char *parserelease( TREELIST **tlp, char *relname,const char *args)
{
	register TREELIST *tl;
	register char *arg;
	register OPTION option;
	int opno;
	char *nextrel;
	char * args_dup;
	char * args_p;

	args_dup = strdup ( (char *)args );
	args_p = args_dup;
	tl = (TREELIST *) malloc (sizeof(TREELIST));
	if ((*tlp = tl) == NULL)
		goaway ("Couldn't allocate TREELIST");
	tl->TLnext = NULL;
	tl->TLname = strdup (relname);
	tl->TLprefix = NULL;
	tl->TLlist = NULL;
	tl->TLscan = NULL;
	tl->TLhost = NULL;
	nextrel = NULL;
	args_p = skipover (args_p," \t");
	while (*(arg=nxtarg(&args_p," \t="))) {
		for (opno = 0; options[opno] != NULL; opno++)
			if (strcmp (arg,options[opno]) == 0)
				break;
		if (options[opno] == NULL)
			goaway ("Invalid release option %s for release %s",
				arg,relname);
		option = (OPTION) opno;
		switch (option) {
		case ONEXT:
			passdelim (&args_p,'=');
			arg = nxtarg (&args_p," \t");
			nextrel = strdup (arg);
			break;
		case OPREFIX:
			passdelim (&args_p,'=');
			arg = nxtarg (&args_p," \t");
			tl->TLprefix = strdup (arg);
			break;
		case OLIST:
			passdelim (&args_p,'=');
			arg = nxtarg (&args_p," \t");
			tl->TLlist = strdup (arg);
			break;
		case OSCAN:
			passdelim (&args_p,'=');
			arg = nxtarg (&args_p," \t");
			tl->TLscan = strdup (arg);
			break;
		case OHOST:
			passdelim (&args_p,'=');
			arg = nxtarg (&args_p," \t");
			tl->TLhost = strdup (arg);
			break;
		}
	}
	free ( args_dup );
	return (nextrel);
}

BOOLEAN
getrelease ( char *release )
{
	TREELIST *tl;
	char buf[STRINGLENGTH];
	char *p,*q;
	int rewound;
	FILE *f;

	if (release == NULL)
		release = strdup (DEFRELEASE);
	listTL = NULL;

	(void) sprintf (buf,FILERELEASES,collname_g);
	f = fopen (buf,"r");
	if (f != NULL) {
		rewound = TRUE;
		for (;;) {
			p = fgets (buf,STRINGLENGTH,f);
			if (p == NULL) {
				if (rewound)
					break;
				rewind (f);
				rewound = TRUE;
				continue;
			}
			q = strchr (p,'\n');
			if (q)  *q = 0;
			if (strchr ("#;:",*p))  continue;
			q = nxtarg (&p," \t");
			if (strcmp (q,release) != 0)
				continue;
			release = parserelease (&tl,release,p);
			if (tl->TLprefix == NULL)
				tl->TLprefix = prefix;
			else if (chdir (tl->TLprefix) < 0)
				return (FALSE);
			else
				(void) chdir (basedir_g);
			tl->TLnext = listTL;
			listTL = tl;
			if (release == NULL)
				break;
			rewound = FALSE;
		}
		(void) fclose (f);
	}
	if (release == NULL)
		return (TRUE);
	if (strcmp (release,DEFRELEASE) != 0)
		return (FALSE);
	(void) parserelease (&tl,release,"");
	tl->TLprefix = prefix;
	tl->TLnext = listTL;
	listTL = tl;
	return (TRUE);
}

void
makescanlists (void)
{
	TREELIST *tl;
	char buf[STRINGLENGTH];
	char *p,*q;
	FILE *f;
	char *saveprefix = prefix;
	int count = 0;

	(void) sprintf (buf,FILERELEASES,collname_g);
	f = fopen (buf,"r");
	if (f != NULL) {
		while ((p = fgets (buf,STRINGLENGTH,f))) {
			q = strchr (p,'\n');
			if (q)  *q = 0;
			if (strchr ("#;:",*p))  continue;
			q = nxtarg (&p," \t");
			(void) parserelease (&tl,q,p);
			if ((prefix = tl->TLprefix) == NULL)
				prefix = saveprefix;
			if (prefix != NULL) {
				if (chdir (prefix) < 0)
					goaway ("Can't chdir to %s",prefix);
				(void) chdir (basedir_g);
			}
			makescan (tl->TLlist,tl->TLscan);
			free ((char *)tl);
			count++;
		}
		(void) fclose (f);
	}
	if (count == 0)
		makescan ((char *)NULL,(char *)NULL);
}

static int
scanone (TREE *t, va_list ap)
{
	register TREE *newt;

	if (newonly && (t->Tflags&FNEW) == 0)
		return (SCMOK);
	newt = Tinsert (&listT,t->Tname,FALSE);
	if (newt == NULL)
		return (SCMOK);
	newt->Tmode = t->Tmode;
	newt->Tflags = t->Tflags;
	newt->Tmtime = t->Tmtime;
	return (SCMOK);
}

void
getscanlists (void)
{
	TREELIST *tl,*stl;

	stl = listTL;
	listTL = NULL;
	while ((tl = stl) != NULL) {
		prefix = tl->TLprefix;
		getscan (tl->TLlist,tl->TLscan);
		tl->TLtree = listT;
		stl = tl->TLnext;
		tl->TLnext = listTL;
		listTL = tl;
	}
	listT = NULL;
	for (tl = listTL; tl != NULL; tl = tl->TLnext)
		(void) Tprocess (tl->TLtree,scanone);
}

static void
makescan ( char *listfile, char *scanfile )
{
	listT = NULL;
	chkscanfile (scanfile);		/* can we can write a scan file? */
	doscan (listfile);		/* read list file and scan disk */
	makescanfile (scanfile);	/* record names in scan file */
	Tfree (&listT);			/* free file list tree */
}

static void
getscan ( char *listfile, char *scanfile )
{
	listT = NULL;
	if (!getscanfile(scanfile)) {	/* check for pre-scanned file list */
		scantime = time ((time_t *)NULL);
		doscan (listfile);	/* read list file and scan disk */
	}
}

static void
doscan ( const char *listfile )
{
	char buf[STRINGLENGTH];

	upgT = NULL;
	flagsT = NULL;
	omitT = NULL;
	omanyT = NULL;
	execT = NULL;
	followT = NULL;
	rfollowT = NULL;
	if (listfile == NULL)
		listfile = FILELISTDEF;
	(void) sprintf (buf,FILELIST,collname_g,listfile);
	readlistfile (buf);		/* get contents of list file */
	(void) Tprocess (upgT,listone); /* build list of files specified */
	cdprefix ((char *)NULL);
	Tfree (&upgT);
	Tfree (&flagsT);
	Tfree (&omitT);
	Tfree (&omanyT);
	Tfree (&execT);
	Tfree (&followT);
	Tfree (&rfollowT);
}

static void
readlistfile ( char *fname )
{
	char buf[STRINGLENGTH],*p;
	register char *q,*r;
	register FILE *f;
	register int ltn,n,i,flags;
	register TREE **t = NULL;
	register LISTTYPE lt;
	char *speclist[SPECNUMBER];

	f = fopen (fname,"r");
	if (f == NULL)  goaway ("Can't read list file %s",fname);
	cdprefix (prefix);
	while ((p = fgets (buf,STRINGLENGTH,f))) {
		if ((q = strchr (p,'\n')))  *q = '\0';
		if (strchr ("#;:",*p))  continue;
		q = nxtarg (&p," \t");
		if (*q == '\0') continue;
		for (ltn = 0; ltname[ltn] && strcmp(q,ltname[ltn]) != 0; ltn++);
		if (ltname[ltn] == NULL)
			goaway ("Invalid list file keyword %s",q);
		lt = (LISTTYPE) ltn;
		flags = 0;
		switch (lt) {
		case LUPGRADE:
			t = &upgT;
			break;
		case LBACKUP:
			t = &flagsT;
			flags = FBACKUP;
			break;
		case LNOACCT:
			t = &flagsT;
			flags = FNOACCT;
			break;
		case LFOLLOW:
			t = &followT;
			break;
		case LRFOLLOW:
			t = &rfollowT;
			break;
		case LSYMLINK:
		case LRSYMLINK:
			/* obsolete directives */
			break;
		case LOMIT:
			t = &omitT;
			break;
		case LOMITANY:
			t = &omanyT;
			break;
		case LALWAYS:
			t = &upgT;
			flags = FALWAYS;
			break;
		case LINCLUDE:
			while (*(q=nxtarg(&p," \t"))) {
				cdprefix ((char *)NULL);
				n = expand (q,speclist,SPECNUMBER);
				for (i = 0; i < n && i < SPECNUMBER; i++) {
					readlistfile (speclist[i]);
					cdprefix ((char *)NULL);
					free (speclist[i]);
				}
				cdprefix (prefix);
			}
			continue;
		case LEXECUTE:
			r = p = q = skipover (p," \t");
			do {
				q = p = skipto (p," \t(");
				p = skipover (p," \t");
			} while (*p != '(' && *p != '\0');
			if (*p++ == '(') {
				*q = '\0';
				do {
					q = nxtarg (&p," \t)");
					if (*q == 0)
						_argbreak = ')';
					else
						expTinsert (q,&execT,0,r);
				} while (_argbreak != ')');
				continue;
			}
			/* fall through */
		default:
			goaway ("Error in handling list file keyword %d",ltn);
		}
		while (*(q=nxtarg(&p," \t"))) {
			if (lt == LOMITANY)
				(void) Tinsert (t,q,FALSE);
			else
				expTinsert (q,t,flags,(char *)NULL);
		}
	}
	(void) fclose (f);
}

static void
expTinsert ( char *p, TREE **t, int flags, char *exec )
{
	register int n, i;
	register TREE *newt;
	char *speclist[SPECNUMBER];
	char buf[STRINGLENGTH];

	n = expand (p,speclist,SPECNUMBER);
	for (i = 0; i < n && i < SPECNUMBER; i++) {
		newt = Tinsert (t,speclist[i],TRUE);
		newt->Tflags |= flags;
		if (exec) {
			(void) sprintf (buf,exec,speclist[i]);
			(void) Tinsert (&newt->Texec,buf,FALSE);
		}
		free (speclist[i]);
	}
}

static int
listone ( TREE *t, va_list ap ) /* expand and add one name from upgrade list */
{
	listentry(t->Tname,t->Tname,(char *)NULL,(t->Tflags&FALWAYS) != 0);
	return (SCMOK);
}

static void
listentry( char * name, char * fullname, char * updir, int always )
{
	struct stat statbuf;
	int link_l = 0;

	if (Tlookup (refuseT,fullname))  return;
	if (!always) {
		if (Tsearch (omitT,fullname))  return;
		if (Tprocess (omanyT,omitanyone,fullname) != SCMOK)
			return;
	}
	if (lstat(name,&statbuf) < 0)
		return;
	if ((statbuf.st_mode&S_IFMT) == S_IFLNK) {
		if (Tsearch (followT,fullname) == 0 &&
		    Tlookup (rfollowT,fullname) == 0) {
			listname (fullname,&statbuf);
			return;
		}
		if (updir) link_l++;
		if (stat(name,&statbuf) < 0) return;
	}
	if ((statbuf.st_mode&S_IFMT) == S_IFDIR) {
		if (access(name,R_OK|X_OK) < 0) return;
		if (chdir(name) < 0) return;
		listname (fullname,&statbuf);
		if (trace) {
			printf ("Scanning directory %s\n",fullname);
			(void) fflush (stdout);
		}
		listdir (fullname,always);
		if (updir == 0 || link_l) {
			(void) chdir (basedir_g);
			if (prefix) (void) chdir (prefix);
			if (updir && *updir) (void) chdir (updir);
		} else
			(void) chdir ("..");
		return;
	}
	if (access(name,R_OK) < 0) return;
	listname (fullname,&statbuf);
}

static void
listname ( char *name, struct stat *st )
{
	register TREE *t,*ts;
	register int new;
	register TREELIST *tl;

	new = st->st_ctime > lasttime;
	if (newonly && !new) {
		for (tl = listTL; tl != NULL; tl = tl->TLnext)
			if ((ts = Tsearch (tl->TLtree,name)))
				ts->Tflags &= ~FNEW;
		return;
	}
	t = Tinsert (&listT,name,FALSE);
	if (t == NULL)  return;
	t->Tmode = st->st_mode;
	t->Tctime = st->st_ctime;
	t->Tmtime = st->st_mtime;
	if (new)  t->Tflags |= FNEW;
	if ((ts = Tsearch (flagsT,name)))
		t->Tflags |= ts->Tflags;
	if ((ts = Tsearch (execT,name))) {
		t->Texec = ts->Texec;
		ts->Texec = NULL;
	}
}

static void
listdir ( char *name, int always ) /* expand directory */
{
	struct dirent *dentry;
	register DIR *dirp;
	char ename[STRINGLENGTH],newname[STRINGLENGTH],filename[STRINGLENGTH];
	register char *p,*newp;

	dirp = opendir (".");
	if (dirp == 0) return;	/* unreadable: probably protected */

	p = name;		/* punt leading ./ and trailing / */
	newp = newname;
	if (p[0] == '.' && p[1] == '/') {
		p += 2;
		while (*p == '/') p++;
	}
	while ((*newp++ = *p++)) ;	/* copy string */
	--newp;				/* trailing null */
	while (newp > newname && newp[-1] == '/') --newp; /* trailing / */
	*newp = 0;
	if (strcmp (newname,".") == 0) newname[0] = 0;	/* "." ==> "" */

	while ((dentry=readdir(dirp))) {
		if (dentry->d_ino == 0) continue;
		if (strcmp(dentry->d_name,".") == 0) continue;
		if (strcmp(dentry->d_name,"..") == 0) continue;
		strcpy ( ename, dentry->d_name );
		if (*newname)
			(void) sprintf (filename,"%s/%s",newname,ename);
		else
			(void) strcpy (filename,ename);
		listentry(ename,filename,newname,always);
	}
	closedir (dirp);
}

static int
omitanyone ( TREE *t, va_list ap )
{
	char *filename;

	filename = va_arg ( ap, char * );
	if (anyglob (t->Tname,filename))
		return (SCMERR);
	return (SCMOK);
}

static BOOLEAN
anyglob ( char * pattern, char * match)
{
	register char *p,*m;
	register char *pb,*pe;

	p = pattern; 
	m = match;
	while (*m && *p == *m ) { 
		p++; 
		m++; 
	}
	if (*p == '\0' && *m == '\0')
		return (TRUE);
	switch (*p++) {
	case '*':
		for (;;) {
			if (*p == '\0')
				return (TRUE);
			if (*m == '\0')
				return (*p == '\0');
			if (anyglob (p,++m))
				return (TRUE);
		}
	case '?':
		return (anyglob (p,++m));
	case '[':
		pb = p;
		while (*(++p) != ']')
			if (*p == '\0')
				return (FALSE);
		pe = p;
		for (p = pb + 1; p != pe; p++) {
			switch (*p) {
			case '-':
				if (p == pb && *m == '-') {
					p = pe + 1;
					return (anyglob (p,++m));
				}
				if (p == pb)
					continue;
				if ((p + 1) == pe)
					return (FALSE);
				if (*m > *(p - 1) &&
				    *m <= *(p + 1)) {
					p = pe + 1;
					return (anyglob (p,++m));
				}
				continue;
			default:
				if (*m == *p) {
					p = pe + 1;
					return (anyglob (p,++m));
				}
			}
		}
		return (FALSE);
	default:
		return (FALSE);
	}
}

/*****************************************
 ***    R E A D   S C A N   F I L E    ***
 *****************************************/

static
unsigned int atoo( char *ap )
{
	register unsigned int n;
	register char *p;

	p = ap;
	n = 0;
	while (*p == ' ' || *p == '\t')
		p++;
	while (*p >= '0' && *p <= '7')
		n = n * 8 + *p++ - '0';
	return(n);
}

static
int getscanfile ( const char *scanfile )
{
	char buf[STRINGLENGTH];
	struct stat sbuf;
	register FILE *f;
	TREE ts;
	register char *p,*q;
	register TREE *tmp, *t = NULL;
	register notwanted;
	register TREELIST *tl;

	if (scanfile == NULL)
		scanfile = FILESCANDEF;
	(void) sprintf (buf,FILESCAN,collname_g,scanfile);
	if (stat(buf,&sbuf) < 0)
		return (FALSE);
	if ((f = fopen (buf,"r")) == NULL)
		return (FALSE);
	if ((p = fgets (buf,STRINGLENGTH,f)) == NULL) {
		(void) fclose (f);
		return (FALSE);
	}
	if ((q = strchr (p,'\n')))  *q = '\0';
	if (*p++ != 'V') {
		(void) fclose (f);
		return (FALSE);
	}
	if (atoi (p) != SCANVERSION) {
		(void) fclose (f);
		return (FALSE);
	}
	scantime = sbuf.st_mtime;	/* upgrade time is time of supscan,
					 * i.e. time of creation of scanfile */
	if (newonly && scantime == lasttime) {
		(void) fclose (f);
		return (TRUE);
	}
	notwanted = FALSE;
	while ((p = fgets (buf,STRINGLENGTH,f))) {
		q = strchr (p,'\n');
		if (q)  *q = 0;
		ts.Tflags = 0;
		if (*p == 'X') {
			if (notwanted)  continue;
			if (t == NULL)
				goaway ("scanfile format inconsistant");
			(void) Tinsert (&t->Texec,++p,FALSE);
			continue;
		}
		notwanted = FALSE;
		if (*p == 'B') {
			p++;
			ts.Tflags |= FBACKUP;
		}
		if (*p == 'N') {
			p++;
			ts.Tflags |= FNOACCT;
		}
		if ((q = strchr (p,' ')) == NULL)
			goaway ("scanfile format inconsistant");
		*q++ = '\0';
		ts.Tmode = atoo (p);
		p = q;
		if ((q = strchr (p,' ')) == NULL)
			goaway ("scanfile format inconsistant");
		*q++ = '\0';
		ts.Tctime = atoi (p);
		p = q;
		if ((q = strchr (p,' ')) == NULL)
			goaway ("scanfile format inconsistant");
		*q++ = 0;
		ts.Tmtime = atoi (p);
		if (ts.Tctime > lasttime)
			ts.Tflags |= FNEW;
		else if (newonly) {
			for (tl = listTL; tl != NULL; tl = tl->TLnext)
				if ((tmp = Tsearch (tl->TLtree,q)))
					tmp->Tflags &= ~FNEW;
			notwanted = TRUE;
			continue;
		}
		if (Tlookup (refuseT,q)) {
			notwanted = TRUE;
			continue;
		}
		t = Tinsert (&listT,q,TRUE);
		t->Tmode = ts.Tmode;
		t->Tflags = ts.Tflags;
		t->Tctime = ts.Tctime;
		t->Tmtime = ts.Tmtime;
	}
	(void) fclose (f);
	return (TRUE);
}

/*******************************************
 ***    W R I T E   S C A N   F I L E    ***
 *******************************************/

static void
chkscanfile ( const char *scanfile )
{
	char tname[STRINGLENGTH], fname[STRINGLENGTH];
	FILE *f;

	if (scanfile == NULL)
		scanfile = FILESCANDEF;
	(void) sprintf (fname,FILESCAN,collname_g,scanfile);
	(void) sprintf (tname,"%s.temp",fname);
	if (NULL == (f = fopen (tname, "w")))
		goaway ("Can't test scan file temp %s for %s",tname,collname_g);
	else {
		(void) unlink (tname);
		(void) fclose (f);
	}
}

static void
makescanfile ( const char *scanfile )
{
	char tname[STRINGLENGTH],fname[STRINGLENGTH];
	struct utimbuf tbuf;
	FILE *scanF;			/* output file for scanned file list */

	if (scanfile == NULL)
		scanfile = FILESCANDEF;
	(void) sprintf (fname,FILESCAN,collname_g,scanfile);
	(void) sprintf (tname,"%s.temp",fname);
	scanF = fopen (tname,"w");
	if (scanF == NULL)
		goaway ("Can't write scan file temp %s for %s",tname,collname_g);
	fprintf (scanF,"V%d\n",SCANVERSION);
	(void) Tprocess (listT,recordone,scanF);
	(void) fclose (scanF);
	if (rename (tname,fname) < 0)
		goaway ("Can't change %s to %s",tname,fname);
	(void) unlink (tname);
	tbuf.actime = time((time_t *)NULL);
	tbuf.modtime = scantime;
	(void) utime (fname,&tbuf);
}

static BOOLEAN
recordone ( TREE *t, va_list ap )
{
	FILE *scanF;

	scanF = va_arg ( ap, FILE * );
	if (t->Tflags&FBACKUP)  fprintf (scanF,"B");
	if (t->Tflags&FNOACCT)  fprintf (scanF,"N");
	fprintf (scanF,"%o %d %d %s\n",
		t->Tmode,t->Tctime,t->Tmtime,t->Tname);
	(void) Tprocess (t->Texec,recordexec,scanF);
	return (SCMOK);
}

static BOOLEAN
recordexec ( TREE *t, va_list ap )
{
	FILE *scanF;

	scanF = va_arg ( ap, FILE * );
	fprintf(scanF,"X%s\n",t->Tname);
	return (SCMOK);
}

void
cdprefix ( char *prefix_l )
{
	static char *curprefix = NULL;

	if (curprefix == NULL) {
		if (prefix_l == NULL)
			return;
		(void) chdir (prefix_l);
		curprefix = prefix_l;
		return;
	}
	if (prefix_l == NULL) {
		(void) chdir (basedir_g);
		curprefix = NULL;
		return;
	}
	if (prefix_l == curprefix)
		return;
	if (strcmp (prefix_l, curprefix) == 0) {
		curprefix = prefix_l;
		return;
	}
	(void) chdir (basedir_g);
	(void) chdir (prefix_l);
	curprefix = prefix_l;
}
