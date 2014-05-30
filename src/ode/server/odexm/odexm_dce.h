/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
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
 * HISTORY
 * $Log: odexm_dce.h,v $
 * Revision 1.1.2.1  1993/08/06  18:44:22  damon
 * 	CR 619. DCE version of odexm
 * 	[1993/08/06  18:36:15  damon]
 *
 * $EndLog$
 */

#define NUM_OBJS		1	/* num of objs supported */
#define MAX_CONC_CALLS_PROTSEQ	5	/* max conc calls per protseq */
#define MAX_CONC_CALLS_TOTAL	10	/* max conc calls total */

/* Success/failure for remote procedures. */
#define GETSPAN_OK		0	/* pass */
#define GETSPAN_ERR		1	/* fail */

/* Defines for access control. */
#define GETSPAN_OP		1	/* requested operation */
#define GRANT_ACCESS		0	/* reference monitor success */
#define DENY_ACCESS		1	/* reference monitor failure */
#define IS_AUTHORIZED		0	/* authorization success */
#define	NOT_AUTHORIZED		1	/* authorization failure */

/* Server key table for this example.  Change name of keyfile to suit your
   environment, and populate it with "rgy_edit ktadd tserver /tmp/tkeyfile". */
#define KEYFILE			"/tmp/tkeyfile"
#define KEYTAB			"FILE:" ## KEYFILE

/* Prototypes for server. */
int main(int _1, char *_2[]);
void oxm_begin_ep(rpc_binding_handle_t _1, stream_handle *_2 );
void oxm_read_ep(rpc_binding_handle_t _1, stream_handle *_2, idl_long_int * _3,
                 buffer _4, error_status_t *_5 );
void oxm_write_ep(rpc_binding_handle_t _1, stream_handle *_2, buffer _3,
                 idl_long_int _4, error_status_t *_5 );
void do_oxm_begin();
int ref_mon(rpc_binding_handle_t _1, int _2);
int is_authorized(unsigned_char_t *_1, int _2);
