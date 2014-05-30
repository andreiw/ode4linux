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
 * $Log: supcdefs.h,v $
 * Revision 1.3.6.2  1994/02/18  21:52:25  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:42  damon]
 *
 * Revision 1.3.6.1  1994/02/17  21:15:03  damon
 * 	CR 1056. moved from ./bin/sup/
 * 	[1994/02/17  21:14:51  damon]
 * 
 * Revision 1.3.2.5  1992/12/02  19:52:57  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:11  damon]
 * 
 * Revision 1.3.2.4  1992/11/11  18:34:22  damon
 * 	CR 329. Replaced explicit decs with include of portable.h
 * 	[1992/11/11  18:32:12  damon]
 * 
 * Revision 1.3.2.3  1992/09/24  19:00:10  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:18:56  gm]
 * 
 * Revision 1.3.2.2  1992/02/13  15:09:17  gm
 * 	Add support for "nomtime" collection option.
 * 	Removed old CMU code.
 * 	[1992/02/09  02:17:02  gm]
 * 
 * Revision 1.3  1991/12/05  20:54:12  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:44  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:07  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:17:13  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:42  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:50  gm]
 * 
 * Revision 1.3  90/07/17  12:26:48  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:05:02  gm]
 * 
 * Revision 1.2  90/01/02  19:56:18  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:08  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Added timeout for backoff.
 * 	[88/02/10            gm0w]
 * 
 * 	Added Crelease for "release" support.
 * 	[87/06/28            gm0w]
 * 
 * 	Created.
 * 	[87/05/25            dwp]
 * 
 * $EndLog$
 */
/*
 *	supcdefs.h -- Declarations shared by the collection of files
 *			that build the sup client.
 */

#ifndef _SUPCDEFS_H
#define _SUPCDEFS_H
#include <stdio.h>
#include <netdb.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <ode/portable.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <ode/sup.h>
#include <ode/supmsg.h>

extern int PGMVERSION;

/*******************************************
 ***    D A T A   S T R U C T U R E S    ***
 *******************************************/

struct collstruct {			/* one per collection to be upgraded */
	char *Cname;			/* collection name */
	TREE *Chost;			/* attempted host for collection */
	TREE *Chtree;			/* possible hosts for collection */
	char *Cbase;			/* local base directory */
	char *Chbase;			/* remote base directory */
	char *Cprefix;			/* local collection pathname prefix */
	char *Crelease;			/* release name */
	char *Cnotify;			/* user to notify of status */
	char *Clogin;			/* remote login name */
	char *Cpswd;			/* remote password */
	char *Ccrypt;			/* data encryption key */
	int Ctimeout;			/* timeout for backoff */
	int Cflags;			/* collection flags */
	int Cnogood;			/* upgrade no good, "when" unchanged */
#ifndef NO_SUP_LOCKS
	int Clockfd;			/* >= 0 if collection is locked */
#endif
	struct collstruct *Cnext;	/* next collection */
};
typedef struct collstruct COLLECTION;

#define CFALL		00001
#define CFBACKUP	00002
#define CFDELETE	00004
#define CFEXECUTE	00010
#define CFLIST		00020
#define CFLOCAL		00040
#define CFMAIL		00100
#define CFOLD		00200
#define CFVERBOSE	00400
#define CFNOMTIME	01000

/*************************
 ***	M A C R O S    ***
 *************************/

#define vnotify	if (thisC->Cflags&CFVERBOSE)  notify

int
parsecoll( COLLECTION *, char *, char *);

#endif
