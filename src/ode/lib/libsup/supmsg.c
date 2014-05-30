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
 * $Log: supmsg.c,v $
 * Revision 1.3.4.4  1994/02/18  23:09:14  damon
 * 	CR 1056. Made collname and basedir global
 * 	[1994/02/18  23:08:57  damon]
 *
 * Revision 1.3.4.3  1994/02/18  18:23:28  damon
 * 	CR 1056. Moved PFI def to include file
 * 	[1994/02/18  18:23:21  damon]
 * 
 * Revision 1.3.4.2  1994/02/18  15:54:19  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  15:54:06  damon]
 * 
 * Revision 1.3.4.1  1994/02/17  18:47:59  damon
 * 	CR 1056. Moved from ./bin/sup/
 * 	[1994/02/17  18:47:39  damon]
 * 
 * Revision 1.3.2.2  1992/12/02  19:53:18  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:26  damon]
 * 
 * Revision 1.3  1991/12/05  20:54:40  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:32  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:56  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:18:13  zeliff]
 * 
 * Revision 1.2  90/10/07  21:37:19  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:34  gm]
 * 
 * Revision 1.3  90/07/17  12:27:08  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:06:05  gm]
 * 
 * Revision 1.2  90/01/02  19:56:26  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:38  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.3  89/11/29  19:02:04  bww
 * 	Updated variable argument list usage for msgxfer.
 * 	[89/11/29  18:59:45  bww]
 * 
 * Revision 2.2  89/08/23  15:02:56  gm0w
 * 	Created from separate message modules.
 * 	[89/08/14            gm0w]
 * 
 * $EndLog$
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <ode/sup.h>
#define MSGSUBR
#define MSGFILE
#include <ode/supmsg.h>
#include <stdlib.h>
/*
 * signon message
 */
extern int	pgmver;			/* program version of partner */
extern int	pgmversion;		/* my program version */
extern char	*scmver;		/* scm version of partner */
extern int	fspid;			/* process id of fileserver */
extern  char    *collname_g;            /* collection name */
extern  char    *basedir_g;             /* base directory */

int msgsignon (void)
{
	int x;

	if (server) {
		x = readmsg (MSGSIGNON);
		if (x == SCMOK)  x = readint (&protver);
		if (x == SCMOK)  x = readint (&pgmver);
		if (x == SCMOK)  x = readstring (&scmver);
		if (x == SCMOK)  x = readmend ();
	} else {
		x = writemsg (MSGSIGNON);
		if (x == SCMOK)  x = writeint (PROTOVERSION);
		if (x == SCMOK)  x = writeint (pgmversion);
		if (x == SCMOK)  x = writestring (scmversion);
		if (x == SCMOK)  x = writemend ();
	}
	return (x);
}

int msgsignonack (void)
{
	int x;

	if (server) {
		x = writemsg (MSGSIGNONACK);
		if (x == SCMOK)  x = writeint (PROTOVERSION);
		if (x == SCMOK)  x = writeint (pgmversion);
		if (x == SCMOK)  x = writestring (scmversion);
		if (x == SCMOK)  x = writeint (fspid);
		if (x == SCMOK)  x = writemend ();
	} else {
		x = readmsg (MSGSIGNONACK);
		if (x == SCMOK)  x = readint (&protver);
		if (x == SCMOK)  x = readint (&pgmver);
		if (x == SCMOK)  x = readstring (&scmver);
		if (x == SCMOK)  x = readint (&fspid);
		if (x == SCMOK)  x = readmend ();
	}
	return (x);
}

/*
 * setup message
 */
extern int	xpatch;			/* setup crosspatch to a new client */
extern char	*xuser;			/* user,group,acct for crosspatch */
extern int	basedev;		/* base directory device */
extern int	baseino;		/* base directory inode */
extern long	lasttime;		/* time of last upgrade */
extern int	listonly;		/* only listing files, no data xfer */
extern int	newonly;		/* only send new files */
extern char	*release;		/* release name */
extern int	setupack;		/* ack return value for setup */

int msgsetup (void)
{
	int x;

	if (server) {
		x = readmsg (MSGSETUP);
		if (x != SCMOK)  return (x);
		if (protver >= 7) {
			x = readint (&xpatch);
			if (x != SCMOK)  return (x);
		} else
			xpatch = FALSE;
		if (xpatch) {
			x = readstring (&xuser);
			if (x != SCMOK)  return (x);
			return (readmend ());
		}
		x = readstring (&collname_g);
		if (x == SCMOK)  x = readint ((int *)&lasttime);
		if (x == SCMOK)  x = readstring (&basedir_g);
		if (x == SCMOK)  x = readint (&basedev);
		if (x == SCMOK)  x = readint (&baseino);
		if (x == SCMOK)  x = readint (&listonly);
		if (x == SCMOK)  x = readint (&newonly);
		if (x == SCMOK)
			if (protver < 6)
				release = (char *)NULL;
			else
				x = readstring (&release);
		if (x == SCMOK)  x = readmend ();
	} else {
		x = writemsg (MSGSETUP);
		if (x != SCMOK)  return (x);
		if (protver >= 7) {
			x = writeint (xpatch);
			if (x != SCMOK)  return (x);
		}
		if (xpatch) {
			x = writestring (xuser);
			if (x != SCMOK)  return (x);
			return (writemend ());
		}
		if (x == SCMOK)  x = writestring (collname_g);
		if (x == SCMOK)  x = writeint ((int)lasttime);
		if (x == SCMOK)  x = writestring (basedir_g);
		if (x == SCMOK)  x = writeint (basedev);
		if (x == SCMOK)  x = writeint (baseino);
		if (x == SCMOK)  x = writeint (listonly);
		if (x == SCMOK)  x = writeint (newonly);
		if (x == SCMOK && protver >= 6)  x = writestring (release);
		if (x == SCMOK)  x = writemend ();
	}
	return (x);
}

int msgsetupack (void)
{
	if (server)
		return (writemint (MSGSETUPACK,setupack));
	return (readmint (MSGSETUPACK,&setupack));
}

/*
 * crypt test message
 */
extern char	*crypttest;	/* encryption test string */

int msgcrypt (void)
{
	if (server)
		return (readmstr (MSGCRYPT,&crypttest));
	return (writemstr (MSGCRYPT,crypttest));
}

int msgcryptok (void)
{
	if (server)
		return (writemnull (MSGCRYPTOK));
	return (readmnull (MSGCRYPTOK));
}

/*
 * login message
 */
extern char	*logcrypt;		/* login encryption test */
extern char	*loguser;		/* login username */
extern char	*logpswd;		/* password for login */
extern int	logack;			/* login ack status */
extern char	*logerror;		/* error from login */

int msglogin (void)
{
	int x;
	if (server) {
		x = readmsg (MSGLOGIN);
		if (x == SCMOK)  x = readstring (&logcrypt);
		if (x == SCMOK)  x = readstring (&loguser);
		if (x == SCMOK)  x = readstring (&logpswd);
		if (x == SCMOK)  x = readmend ();
	} else {
		x = writemsg (MSGLOGIN);
		if (x == SCMOK)  x = writestring (logcrypt);
		if (x == SCMOK)  x = writestring (loguser);
		if (x == SCMOK)  x = writestring (logpswd);
		if (x == SCMOK)  x = writemend ();
	}
	return (x);
}

int msglogack (void)
{
	int x;
	if (server) {
		x = writemsg (MSGLOGACK);
		if (x == SCMOK)  x = writeint (logack);
		if (x == SCMOK)  x = writestring (logerror);
		if (x == SCMOK)  x = writemend ();
	} else {
		x = readmsg (MSGLOGACK);
		if (x == SCMOK)  x = readint (&logack);
		if (x == SCMOK)  x = readstring (&logerror);
		if (x == SCMOK)  x = readmend ();
	}
	return (x);
}

/*
 * refuse list message
 */
extern TREE	*refuseT;		/* tree of files to refuse */

static int refuseone ( TREE *t, va_list ap )
{
	return (writestring (t->Tname));
}

int msgrefuse (void)
{
	int x;
	if (server) {
		char *name;
		x = readmsg (MSGREFUSE);
		if (x == SCMOK)  x = readstring (&name);
		while (x == SCMOK) {
			if (name == NULL)  break;
			(void) Tinsert (&refuseT,name,FALSE);
			free (name);
			x = readstring (&name);
		}
		if (x == SCMOK)  x = readmend ();
	} else {
		x = writemsg (MSGREFUSE);
		if (x == SCMOK)  x = Tprocess (refuseT,refuseone);
		if (x == SCMOK)  x = writestring ((char *)NULL);
		if (x == SCMOK)  x = writemend ();
	}
	return (x);
}

/*
 * list files message
 */
extern TREE	*listT;			/* tree of files to list */
extern long	scantime;		/* time that collection was scanned */

static int listone ( TREE *t, va_list ap )
{
	int x;

	x = writestring (t->Tname);
	if (x == SCMOK)  x = writeint ((int)t->Tmode);
	if (x == SCMOK)  x = writeint ((int)t->Tflags);
	if (x == SCMOK)  x = writeint (t->Tmtime);
	return (x);
}

int msglist (void)
{
	int x;
	if (server) {
		x = writemsg (MSGLIST);
		if (x == SCMOK)  x = Tprocess (listT,listone);
		if (x == SCMOK)  x = writestring ((char *)NULL);
		if (x == SCMOK)  x = writeint ((int)scantime);
		if (x == SCMOK)  x = writemend ();
	} else {
		char *name;
		int mode,flags,mtime;
		TREE *t;
		x = readmsg (MSGLIST);
		if (x == SCMOK)  x = readstring (&name);
		while (x == SCMOK) {
			if (name == NULL)  break;
			x = readint (&mode);
			if (x == SCMOK)  x = readint (&flags);
			if (x == SCMOK)  x = readint (&mtime);
			if (x != SCMOK)  break;
			t = Tinsert (&listT,name,TRUE);
			free (name);
			t->Tmode = mode;
			t->Tflags = flags;
			t->Tmtime = mtime;
			x = readstring (&name);
		}
		if (x == SCMOK)  x = readint ((int *)&scantime);
		if (x == SCMOK)  x = readmend ();
	}
	return (x);
}

/*
 * files needed message
 */
extern TREE	*needT;			/* tree of files to need */

static int needone ( TREE *t, va_list ap )
{
	int x;
	x = writestring (t->Tname);
	if (x == SCMOK)  x = writeint ((t->Tflags&FUPDATE) != 0);
	return (x);
}

int msgneed (void)
{
	int x;
	if (server) {
		char *name;
		int update;
		TREE *t;
		x = readmsg (MSGNEED);
		if (x == SCMOK)  x = readstring (&name);
		while (x == SCMOK) {
			if (name == NULL)  break;
			x = readint (&update);
			if (x != SCMOK)  break;
			t = Tinsert (&needT,name,TRUE);
			free (name);
			if (update)  t->Tflags |= FUPDATE;
			x = readstring (&name);
		}
		if (x == SCMOK)  x = readmend ();
	} else {
		x = writemsg (MSGNEED);
		if (x == SCMOK)  x = Tprocess (needT,needone);
		if (x == SCMOK)  x = writestring ((char *)NULL);
		if (x == SCMOK)  x = writemend ();
	}
	return (x);
}

/*
 * files denied message
 */
extern TREE	*denyT;			/* tree of files to deny */

static int denyone ( TREE *t, va_list ap )
{
	return (writestring (t->Tname));
}

int msgdeny (void)
{
	int x;
	if (server) {
		x = writemsg (MSGDENY);
		if (x == SCMOK)  x = Tprocess (denyT,denyone);
		if (x == SCMOK)  x = writestring ((char *)NULL);
		if (x == SCMOK)  x = writemend ();
	} else {
		char *name;
		x = readmsg (MSGDENY);
		if (x == SCMOK)  x = readstring (&name);
		while (x == SCMOK) {
			if (name == NULL)  break;
			(void) Tinsert (&denyT,name,FALSE);
			free (name);
			x = readstring (&name);
		}
		if (x == SCMOK)  x = readmend ();
	}
	return (x);
}

/*
 * send file message
 */
int msgsend (void)
{
	if (server)
		return (readmnull (MSGSEND));
	return (writemnull (MSGSEND));
}

/*
 * receive file message
 */
extern TREE	*upgradeT;		/* pointer to file being upgraded */

static int writeone ( TREE *t, va_list ap )
{
	return (writestring (t->Tname));
}

#if __STDC__
int msgrecv (PFI xferfile,...)
#else
/* VARARGS */
int msgrecv (va_alist)
va_dcl
#endif
{
#if !__STDC__
	PFI xferfile;
#endif
	va_list args;
	int x;
	TREE *t = upgradeT;

#if __STDC__
	va_start(args,xferfile);
#else
	va_start(args);
	xferfile = va_arg(args, PFI);
#endif
	if (server) {
		x = writemsg (MSGRECV);
		if (t == NULL) {
			if (x == SCMOK)  x = writestring ((char *)NULL);
			if (x == SCMOK)  x = writemend ();
			return (x);
		}
		if (x == SCMOK)  x = writestring (t->Tname);
		if (x == SCMOK)  x = writeint (t->Tmode);
		if (t->Tmode == 0) {
			if (x == SCMOK)  x = writemend ();
			return (x);
		}
		if (x == SCMOK)  x = writeint (t->Tflags);
		if (x == SCMOK)  x = writestring (t->Tuser);
		if (x == SCMOK)  x = writestring (t->Tgroup);
		if (x == SCMOK)  x = writeint (t->Tmtime);
		if (x == SCMOK)  x = Tprocess (t->Tlink,writeone);
		if (x == SCMOK)  x = writestring ((char *)NULL);
		if (x == SCMOK)  x = Tprocess (t->Texec,writeone);
		if (x == SCMOK)  x = writestring ((char *)NULL);
		if (x == SCMOK)  x = (*xferfile) (t,args);
		if (x == SCMOK)  x = writemend ();
	} else {
		char *linkname,*execcmd;
		if (t == NULL)  return (SCMERR);
		x = readmsg (MSGRECV);
		if (x == SCMOK)  x = readstring (&t->Tname);
		if (x == SCMOK && t->Tname == NULL) {
			x = readmend ();
			if (x == SCMOK)  x = (*xferfile) (NULL,args);
			return (x);
		}
		if (x == SCMOK)  x = readint (&t->Tmode);
		if (t->Tmode == 0) {
			x = readmend ();
			if (x == SCMOK)  x = (*xferfile) (t,args);
			return (x);
		}
		if (x == SCMOK)  x = readint (&t->Tflags);
		if (x == SCMOK)  x = readstring (&t->Tuser);
		if (x == SCMOK)  x = readstring (&t->Tgroup);
		if (x == SCMOK)  x = readint (&t->Tmtime);
		t->Tlink = NULL;
		if (x == SCMOK)  x = readstring (&linkname);
		while (x == SCMOK) {
			if (linkname == NULL)  break;
			(void) Tinsert (&t->Tlink,linkname,FALSE);
			free (linkname);
			x = readstring (&linkname);
		}
		t->Texec = NULL;
		if (x == SCMOK)  x = readstring (&execcmd);
		while (x == SCMOK) {
			if (execcmd == NULL)  break;
			(void) Tinsert (&t->Texec,execcmd,FALSE);
			free (execcmd);
			x = readstring (&execcmd);
		}
		if (x == SCMOK)  x = (*xferfile) (t,args);
		if (x == SCMOK)  x = readmend ();
	}
	va_end(args);
	return (x);
}

/*
 * protocol done message
 */
extern int	doneack;
extern char	*donereason;

int msgdone (void)
{
	int x;

	if (protver < 6) {
		printf ("Error, msgdone should not have been called.");
		return (SCMERR);
	}
	if (server) {
		x = readmsg (MSGDONE);
		if (x == SCMOK)  x = readint (&doneack);
		if (x == SCMOK)  x = readstring (&donereason);
		if (x == SCMOK)  x = readmend ();
	} else {
		x = writemsg (MSGDONE);
		if (x == SCMOK)  x = writeint (doneack);
		if (x == SCMOK)  x = writestring (donereason);
		if (x == SCMOK)  x = writemend ();
	}
	return (x);
}

/*
 * go away message
 */
extern char	*goawayreason;		/* reason for goaway */

int msggoaway (void)
{
	return (writemstr (MSGGOAWAY,goawayreason));
}

/*
 * cross-patch protocol message
 */
extern int	xargc;			/* arg count for crosspatch */
extern char	**xargv;		/* arg array for crosspatch */

int msgxpatch (void)
{
	int x;
	int i;

	if (server) {
		x = readmsg (MSGXPATCH);
		if (x != SCMOK)  return (x);
		x = readint (&xargc);
		if (x != SCMOK)  return (x);
		xargc += 2;
		xargv = (char **)calloc (sizeof (char *),(unsigned)xargc+1);
		if (xargv == NULL)
			return (SCMERR);
		for (i = 2; i < xargc; i++) {
			x = readstring (&xargv[i]);
			if (x != SCMOK)  return (x);
		}
		x = readmend ();
	} else {
		x = writemsg (MSGXPATCH);
		if (x != SCMOK)  return (x);
		x = writeint (xargc);
		if (x != SCMOK)  return (x);
		for (i = 0; i < xargc; i++) {
			x = writestring (xargv[i]);
			if (x != SCMOK)  return (x);
		}
		x = writemend ();
	}
	return (x);
}
