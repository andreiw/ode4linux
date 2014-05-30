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
 * $Log: supcmisc.c,v $
 * Revision 1.3.7.2  1994/02/22  15:51:32  damon
 * 	CR 1056. Added _g to collname and basedir
 * 	[1994/02/22  15:51:00  damon]
 *
 * Revision 1.3.7.1  1994/02/18  21:52:07  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:33  damon]
 * 
 * Revision 1.3.5.2  1993/05/04  18:44:49  damon
 * 	CR 435. Changed timevals from longs to time_t
 * 	[1993/05/04  18:44:31  damon]
 * 
 * Revision 1.3.2.5  1992/12/02  19:53:05  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:18  damon]
 * 
 * Revision 1.3.2.4  1992/11/13  21:07:15  root
 * 	Added include of time.h
 * 	[1992/11/13  21:07:03  root]
 * 
 * Revision 1.3.2.3  1992/11/09  22:15:43  damon
 * 	CR 296. Removed warnings
 * 	[1992/11/09  22:10:29  damon]
 * 
 * Revision 1.3.2.2  1992/09/24  19:00:25  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:19:22  gm]
 * 
 * Revision 1.3  1991/12/05  20:54:23  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:04  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:28  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:17:34  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:56  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:07  gm]
 * 
 * Revision 1.2  90/01/02  19:56:21  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:21  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.4  89/11/29  17:41:27  bww
 * 	Updated variable argument list usage.
 * 	[89/11/29  17:35:19  bww]
 * 
 * Revision 1.4  89/08/03  19:49:19  mja
 * 	Updated to use v*printf() in place of _doprnt().
 * 	[89/04/19            mja]
 * 
 * Revision 0.0  87/12/27            gm0w
 * 	Fixed bug in ugconvert() which left pw uninitialized.
 * 	[87/12/27            gm0w]
 * 
 * Revision 0.0  87/05/25            dwp
 * 	Split off from sup.c and changed goaway to use printf
 * 	instead of notify if thisC is NULL.
 * 	[87/05/25            dwp]
 * 
 * $EndLog$
 */
/*
 * sup misc. routines, include list processing.
 */

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <ode/supcdefs.h>
#include <ode/util.h>

struct liststruct {		/* uid and gid lists */
	char *Lname;		/* name */
	int Lnumber;		/* uid or gid */
	struct liststruct *Lnext;
};
typedef struct liststruct LIST;

#define HASHBITS	4
#define HASHSIZE	(1<<HASHBITS)
#define HASHMASK	(HASHSIZE-1)
#define LISTSIZE	(HASHSIZE*HASHSIZE)

static LIST *uidL[LISTSIZE];		/* uid and gid lists */
static LIST *gidL[LISTSIZE];

extern COLLECTION *thisC;		/* collection list pointer */

/*
 * FORWARD DECLARATIONS
 */
int estabd ( char *,char *);

/*********************************************
 ***    U T I L I T Y   R O U T I N E S    ***
 *********************************************/

#if __STDC__
void
notify (const char *fmt,...)		/* record error message */
#else
/* VARARGS */
void
notify (va_alist)		/* record error message */
va_dcl
#endif
{
#if !__STDC__
	const char *fmt;
#endif
	char buf[STRINGLENGTH];
	time_t tloc;
	static FILE *noteF = NULL;	/* mail program on pipe */
	va_list ap;

#if __STDC__
	va_start(ap,fmt);
#else
	va_start(ap);
	fmt = va_arg(ap,char *);
#endif
	if (fmt == NULL) {
		if (noteF && noteF != stdout)
			(void) pclose (noteF);
		noteF = NULL;
		return;
	}
	if (noteF == NULL) {
		if ((thisC->Cflags&CFMAIL) && thisC->Cnotify) {
			(void) sprintf (buf,"mail -s \"SUP Upgrade of %s\" %s >/dev/null",
				collname_g,thisC->Cnotify);
			noteF = popen (buf,"w");
			if (noteF == NULL) {
				logerr ("Can't send mail to %s for %s",
					thisC->Cnotify,collname_g);
				noteF = stdout;
			}
		} else
			noteF = stdout;
		tloc = time ((time_t *)NULL);
		fprintf (noteF,"SUP Upgrade of %s at %s",
			collname_g,ctime (&tloc));
		(void) fflush (noteF);
	}
	vfprintf(noteF,fmt,ap);
	va_end(ap);
	(void) fflush (noteF);
}

void
lockout (int on)		/* lock out interrupts */
{
	static sigset_t newset, oldset;
	static int first = TRUE;

	if (on) {
		if (first) {
			sigemptyset(&newset);
			sigaddset(&newset, SIGHUP);
			sigaddset(&newset, SIGINT);
			sigaddset(&newset, SIGQUIT);
			sigaddset(&newset, SIGTERM);
			first = FALSE;
		}
		(void) sigprocmask (SIG_BLOCK,&newset,&oldset);
	}
	else {
		(void) sigprocmask (SIG_SETMASK,&oldset,(sigset_t *)0);
	}
}

char *fmttime ( time_t time_l )
{
	static char buf[STRINGLENGTH];
	int len;

	(void) strcpy (buf,ctime (&time_l));
	len = strlen(buf+4)-6;
	(void) strncpy (buf,buf+4,len);
	buf[len] = '\0';
	return (buf);
}

/*************************************************
 ***    P R I N T   U P D A T E   T I M E S    ***
 *************************************************/

void
prtime (void)
{
	char buf[STRINGLENGTH];
	time_t twhen;
	int f;

	if (chdir (thisC->Cbase) < 0)
		logerr ("Can't change to base directory %s for collection %s",
			thisC->Cbase,thisC->Cname);
	(void) sprintf (buf,FILEWHEN,thisC->Cname);
	f = open (buf,O_RDONLY,0);
	if (f >= 0) {
		if (read(f,(char *)&twhen,sizeof(time_t)) != sizeof(time_t))
			twhen = 0;
		(void) close (f);
	} else
		twhen = 0;
	(void) strcpy (buf,ctime (&twhen));
	buf[strlen(buf)-1] = '\0';
	loginfo ("Last update occurred at %s for collection %s",
		buf,thisC->Cname);
}

int establishdir ( char *fname )
{
	char dpart[STRINGLENGTH],fpart[STRINGLENGTH];
	path (fname,dpart,fpart);
	return (estabd (fname,dpart));
}

int estabd ( char *fname,char *dname )
{
	char dpart[STRINGLENGTH],fpart[STRINGLENGTH];
	struct stat sbuf;
	register int x;

	if (stat (dname,&sbuf) >= 0)  return (FALSE); /* exists */
	path (dname,dpart,fpart);
	if (strcmp (fpart,".") == 0) {		/* dname is / or . */
		notify ("SUP: Can't create directory %s for %s\n",dname,fname);
		return (TRUE);
	}
	x = estabd (fname,dpart);
	if (x)  return (TRUE);
	(void) mkdir (dname,0755);
	if (stat (dname,&sbuf) < 0) {		/* didn't work */
		notify ("SUP: Can't create directory %s for %s\n",dname,fname);
		return (TRUE);
	}
	vnotify ("SUP Created directory %s for %s\n",dname,fname);
	return (FALSE);
}

/***************************************
 ***    L I S T   R O U T I N E S    ***
 ***************************************/

static
int Lhash (char * name)
{
	/* Hash function is:  HASHSIZE * (strlen mod HASHSIZE)
	 *		      +          (char   mod HASHSIZE)
	 * where "char" is last character of name (if name is non-null).
	 */

	register int len;
	register char c;

	len = strlen (name);
	if (len > 0)	c = name[len-1];
	else		c = 0;
	return (((len&HASHMASK)<<HASHBITS)|(((int)c)&HASHMASK));
}

static void
Linsert ( LIST **table, char *name, int number )
{
	register LIST *l;
	register int lno;
	lno = Lhash (name);
	l = (LIST *) malloc (sizeof(LIST));
	l->Lname = name;
	l->Lnumber = number;
	l->Lnext = table[lno];
	table[lno] = l;
}

static
LIST *Llookup ( LIST **table, char *name )
{
	register int lno;
	register LIST *l;
	lno = Lhash (name);
	for (l = table[lno]; l && strcmp(l->Lname,name) != 0; l = l->Lnext);
	return (l);
}

void
ugconvert ( char *uname,char *gname, int *uid,int *gid,int *mode )
{
	register LIST *u,*g;
	register struct passwd *pw;
	register struct group *gr;
	struct stat sbuf;
	static int defuid = -1;
	static int defgid;
	static int first = TRUE;

	if (first) {
		memset ((char *)uidL, 0, sizeof (uidL));
		memset ((char *)gidL, 0, sizeof (gidL));
		first = FALSE;
	}
	pw = NULL;
	if ((u = Llookup (uidL,uname)))
		*uid = u->Lnumber;
	else if ((pw = getpwnam (uname))) {
		Linsert (uidL,strdup(uname),pw->pw_uid);
		*uid = pw->pw_uid;
	}
	if (u || pw) {
		if ((g = Llookup (gidL,gname))) {
			*gid = g->Lnumber;
			return;
		}
		if ((gr = getgrnam (gname))) {
			Linsert (gidL,strdup(gname),gr->gr_gid);
			*gid = gr->gr_gid;
			return;
		}
		if (pw == NULL)
			pw = getpwnam (uname);
		*mode &= ~S_ISGID;
		*gid = pw->pw_gid;
		return;
	}
	*mode &= ~(S_ISUID|S_ISGID);
	if (defuid >= 0) {
		*uid = defuid;
		*gid = defgid;
		return;
	}
	if (stat (".",&sbuf) < 0) {
		*uid = defuid = getuid ();
		*gid = defgid = getgid ();
		return;
	}
	*uid = defuid = sbuf.st_uid;
	*gid = defgid = sbuf.st_gid;
}
