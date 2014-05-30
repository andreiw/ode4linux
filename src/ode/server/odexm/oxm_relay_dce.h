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
 * $Log: oxm_relay_dce.h,v $
 * Revision 1.1.2.1  1993/08/06  18:46:51  damon
 * 	CR 619. DCE version of odexm
 * 	[1993/08/06  18:46:45  damon]
 *
 * $EndLog$
 */

#define MAX_SERVERS	10		/* single-digit server_num's, 0...9 */
#define CLIENT_NUM	-1		/* not equal to any server_num */
#define MAX_RANDOM	(10*1000*1000)	/* big, to observe threads in action */
#define DO_WORK_OK	0		/* pass */
#define DO_WORK_ERR	1		/* fail */

/* Package up do_work() args in a struct, because
   pthreads start routines take only one argument. */
typedef struct work_arg {
	int			server_num;	/* as ordered in arg list */
	unsigned_char_t		*server_name;	/* as named in arg list */
	rpc_binding_handle_t	bind_handle;	/* binding handle to server */
	idl_long_int		rand;		/* input to the rpc call */
	int			status;		/* returned from do_work() */
} work_arg_t;

/* Prototypes for client. */
int main(int _1, char *_2[]);
void do_work(work_arg_t *_1);
