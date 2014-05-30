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
 * $Log: supcvers.c,v $
 * Revision 1.3.5.1  1994/02/18  21:52:17  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:38  damon]
 *
 * Revision 1.3.2.3  1992/12/02  19:53:10  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:22  damon]
 * 
 * Revision 1.3.2.2  1992/02/13  15:09:35  gm
 * 	About time we bumped the revision number.
 * 	[1992/02/09  02:17:18  gm]
 * 
 * Revision 1.3  1991/12/05  20:54:32  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:19  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:42  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:18:00  zeliff]
 * 
 * Revision 1.2  90/10/07  21:37:09  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:22  gm]
 * 
 * Revision 1.2  90/01/02  19:56:24  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:30  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Added crosspatch support.  Removed nameserver support. [V7.24]
 * 	Added code for "release" support. [V6.23]
 * 	Changes for Version 6, better supoort to reflect errors to
 * 	logfile. [V6.22]
 * 	Split sup.c into subparts. [V5.21]
 * 	Changes to many files to make lint happy. [V5.20]
 * 	Changes to sup.c and scmio.c. [V5.19]
 * 	Changes to sup.c. [V5.18]
 * 	Minor bug fix to previous edit in sup.c. [V5.17]
 * 	Changes to sup.c and sup.h. [V5.16]
 * 	Added changes to sup.c, sup.h, scm.c, scmio.h. [V5.15]
 * 	Created. [V5.14]
 * 
 * $EndLog$
 */

int PGMVERSION = 25;		/* program version of sup */
