/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
 * HISTORY
 * $Log: odexm_aux.h,v $
 * Revision 1.1.2.1  1993/08/06  18:44:19  damon
 * 	CR 619. DCE version of odexm
 * 	[1993/08/06  18:36:14  damon]
 *
 * Revision 1.2.2.3  1993/02/04  20:32:23  cjd
 * 	Embedded copyright notice
 * 	[1993/02/04  20:29:39  cjd]
 * 
 * Revision 1.2.2.2  1992/12/18  18:18:16  marcyw
 * 	Defect 4998: adding disclaimer comment
 * 	[1992/12/18  18:12:06  marcyw]
 * 
 * Revision 1.2  1992/01/19  22:14:28  devrcs
 * 	Dropping DCE1.0 OSF1_misc port archive
 * 
 * $EndLog$
 */
/*
 * The Example code is provided to you as "Pass-through Code".
 * Pass-through Code and its related Documentation are not warrented,
 * supported, or indemnified by OSF, and are provided "AS IS".
 * You can use, sublicense, or disribute the same at your own risk.
 */
/*
 * Copyright (c) 1990, 1991  
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
 *  OSF DCE Version 1.0 
 */

/*
**	timop_aux.h
**
**      Auxiliary info for timop example.
**	There are other ways to do these things, but we're just
**	illustrating the basics here.
*/

/* Principal names for this example application.
   Change them to suit your environment. */
#define CLIENT_PRINC_NAME	(unsigned_char_t *)"/.../nomad_cell.osf.org/damon"
#define SERVER_PRINC_NAME	(unsigned_char_t *)"/.../nomad_cell.osf.org/damon"

/* Well-known object uuid for this example application. */
#define OBJ_UUID      (unsigned_char_t *)"2541af56-43a2-11ca-a9f5-02608c0ffe49"
