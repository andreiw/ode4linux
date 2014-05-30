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
 * $Log: supmsg.h,v $
 * Revision 1.3.7.4  1994/02/18  23:09:11  damon
 * 	CR 1056. Made collname and basedir global
 * 	[1994/02/18  23:08:55  damon]
 *
 * Revision 1.3.7.3  1994/02/18  21:52:27  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:44  damon]
 * 
 * Revision 1.3.7.2  1994/02/18  18:22:14  damon
 * 	CR 1056. pedantic change
 * 	[1994/02/18  18:22:08  damon]
 * 
 * Revision 1.3.7.1  1994/02/17  21:15:06  damon
 * 	CR 1056. moved from ./bin/sup/
 * 	[1994/02/17  21:14:53  damon]
 * 
 * Revision 1.3.5.2  1993/05/04  18:48:51  damon
 * 	CR 435. Changed timevals from longs to time_t
 * 	[1993/05/04  18:48:43  damon]
 * 
 * Revision 1.3.2.3  1992/12/02  19:53:20  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:28  damon]
 * 
 * Revision 1.3.2.2  1992/11/13  15:20:14  root
 * 	Change sys/time.h to time.h
 * 	Place comments around garbage after #endif, #else
 * 	[1992/11/13  15:00:53  root]
 * 
 * Revision 1.3  1991/12/05  20:54:43  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:38  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:48:02  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:18:18  zeliff]
 * 
 * Revision 1.2  90/10/07  21:37:23  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:39  gm]
 * 
 * Revision 1.2  90/01/02  19:56:27  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:41  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.6  89/08/23  14:56:42  gm0w
 * 	Changed MSGF to MSG constants.
 * 	[89/08/23            gm0w]
 * 
 * Revision 0.0  87/12/27            gm0w
 * 	Added crosspatch support.  Removed nameserver support.
 * 	[87/12/27            gm0w]
 * 
 * Revision 0.0  87/06/29            gm0w
 * 	Added "release" support.
 * 	[87/06/29            gm0w]
 * 
 * Revision 0.0  87/05/27            dwp
 * 	Added MSGFDONE and subvalues, added doneack and donereason.
 * 	[87/05/27            dwp]
 * 
 * Revision 0.0  87/05/20            gm0w
 * 	Added changes to make lint happy.
 * 	[87/05/20            gm0w]
 * 
 * Revision 0.0  86/01/04            gm0w
 * 	Changed hostname to hostT to support multiple repositories per
 * 	collection.  Added FSETUPBUSY to tell clients that server is
 * 	currently busy.
 * 	[86/01/04            gm0w]
 * 
 * Revision 0.0  85/12/19            gm0w
 * 	Created.
 * 	[85/12/19            gm0w]
 * 
 * $EndLog$
 */
/*
 * supmsg.h - global definitions/variables used in msg routines.
 */

#ifndef _SUPMSG_H
#define _SUPMSG_H
/* Special messages reserved for SCM */
#define MSGGOAWAY	(-1)		/* see scm.c */

/* Message types -- see supmsg.c */
#define MSGSIGNON	(101)
#define MSGSIGNONACK	(102)
#define MSGSETUP	(103)
#define MSGSETUPACK	(104)
#define MSGLOGIN	(105)
#define MSGLOGACK	(106)
#define MSGCRYPT	(107)
#define MSGCRYPTOK	(108)
#define MSGREFUSE	(109)
#define MSGLIST		(110)
#define MSGNEED		(111)
#define MSGDENY		(112)
#define MSGSEND		(113)
#define MSGRECV		(114)
#define MSGDONE		(115)
#define MSGXPATCH	(117)

/* MSGSETUPACK data codes - setupack */
#define FSETUPOK	(999)
#define FSETUPHOST	(998)
#define FSETUPSAME	(997)
#define FSETUPOLD	(996)
#define FSETUPBUSY	(995)
#define FSETUPRELEASE	(994)

/* MSGLOGACK data codes - loginack */
#define FLOGOK		(989)
#define FLOGNG		(988)

/* MSGDONE data codes - doneack */
#define FDONESUCCESS	(979)
#define FDONEDONTLOG	(978)
#define FDONESRVERROR	(977)
#define FDONEUSRERROR	(976)
#define FDONEGOAWAY	(975)

#ifdef	MSGSUBR

/* used in all msg routines */
extern int	server;			/* true if we are the server */
extern int	protver;		/* protocol version of partner */

#else /* MSGSUBR */

#ifdef	MSGFILE
#define	EXTERN
#else /* MSGFILE */
#define	EXTERN	extern
#endif /* MSGFILE */

/* used in all msg routines */
EXTERN	int	server;			/* true if we are the server */

/* msggoaway */
EXTERN	char	*goawayreason;		/* reason for goaway */

/* msgsignon */
EXTERN	int	pgmversion;		/* version of this program */
EXTERN	int	protver;		/* protocol version of partner */
EXTERN	int	pgmver;			/* program version of partner */
EXTERN	char	*scmver;		/* scm version of partner */
EXTERN	int	fspid;			/* process id of fileserver */

/* msgsetup */
EXTERN	int	xpatch;			/* setup crosspatch to a new client */
EXTERN	char	*xuser;			/* user for crosspatch */
EXTERN	char	*collname_g;		/* collection name */
EXTERN	char	*basedir_g;		/* base directory */
EXTERN	int	basedev;		/* base directory device */
EXTERN	int	baseino;		/* base directory inode */
EXTERN	time_t	lasttime;		/* time of last upgrade */
EXTERN	int	listonly;		/* only listing files, no data xfer */
EXTERN	int	newonly;		/* only send new files */
EXTERN	char	*release;		/* release name */
EXTERN	int	setupack;		/* ack return value for setup */

/* msgcrypt */
EXTERN	char	*crypttest;		/* encryption test string */

/* msglogin */
EXTERN	char	*logcrypt;		/* login encryption test */
EXTERN	char	*loguser;		/* login username */
EXTERN	char	*logpswd;		/* password for login */
EXTERN	int	logack;			/* login ack status */
EXTERN	char	*logerror;		/* error string from oklogin */

/* msgxpatch */
EXTERN	int	xargc;			/* arg count for crosspatch */
EXTERN	char	** xargv;	/* arg array for crosspatch */

/* msgrefuse */
EXTERN	TREE	*refuseT;		/* tree of files to refuse */

/* msglist */
EXTERN	TREE	*listT;			/* tree of files to list */
EXTERN	time_t	scantime;		/* time that collection was scanned */

/* msgneed */
EXTERN	TREE	*needT;			/* tree of files to need */

/* msgdeny */
EXTERN	TREE	*denyT;			/* tree of files to deny */

/* msgrecv */
/* msgsend */
EXTERN	TREE	*upgradeT;		/* pointer to file being upgraded */

/* msgdone */
EXTERN	int	doneack;		/* done ack status */
EXTERN	char 	*donereason;		/* set if indicated by doneack */

#undef	EXTERN

#endif /* MSGSUBR */
#endif
