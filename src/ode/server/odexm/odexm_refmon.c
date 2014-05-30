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
 * $Log: odexm_refmon.c,v $
 * Revision 1.1.2.1  1993/08/06  18:44:26  damon
 * 	CR 619. DCE version of odexm
 * 	[1993/08/06  18:36:17  damon]
 *
 * $EndLog$
 */

#include <stdio.h>
#include "odexm_aux.h"
#include "odexm.h"
#include "odexm_dce.h"


/*
 *	ref_mon()
 *
 *	Reference monitor for timop.
 *	It checks generalities, then calls is_authorized() to check specifics.
 */

int
ref_mon(
	rpc_binding_handle_t		bind_handle,
	int				requested_op)
{
	int				ret;
	rpc_authz_handle_t		privs;
	unsigned_char_t			*client_princ_name, *server_princ_name;
	unsigned32			protect_level, authn_svc, authz_svc,
	                                    status;


	/* Get client auth info. */
	rpc_binding_inq_auth_client(bind_handle, &privs, &server_princ_name,
	    &protect_level, &authn_svc, &authz_svc, &status);
	if (status != rpc_s_ok) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		return(DENY_ACCESS);
	}

	/* Check if selected authn service is acceptable to us. */
	if (authn_svc != rpc_c_authn_dce_secret) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		return(DENY_ACCESS);
	}

	/* Check if selected protection level is acceptable to us. */
	if (protect_level != rpc_c_protect_level_pkt_integ
	&&  protect_level != rpc_c_protect_level_pkt_privacy) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		return(DENY_ACCESS);
	}

	/* Check if selected authz service is acceptable to us. */
	if (authz_svc != rpc_c_authz_name) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		return(DENY_ACCESS);
	}
	/* If rpc_c_authz_dce were being used instead of rpc_c_authz_name,
	   privs would be a PAC (sec_id_pac_t *), not a name as it is here. */
	client_princ_name = (unsigned_char_t *)privs;

	/* Check if selected server principal name is supported. */
        fprintf(stderr, "%s %s\n", server_princ_name, SERVER_PRINC_NAME );
	if (strcmp(server_princ_name, SERVER_PRINC_NAME) != 0) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		return(DENY_ACCESS);
	}

	/* Now that things seem generally OK, check the specifics. */
	ret = is_authorized(client_princ_name, requested_op);
	if (ret == NOT_AUTHORIZED) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		return(DENY_ACCESS);
	}

	/* Cleared all the authorization hurdles -- grant access. */
	return(GRANT_ACCESS);
}


/*
 *	is_authorized()
 *
 *	Check authorization of client to the requested service.
 *	This could be arbitrarily application-specific, but we keep it simple.
 *	A normal application (i.e., one using PACs & ACLs) would be using
 *	sec_acl_mgr_is_authorized() instead of this function.
 */

int
is_authorized(
        unsigned_char_t			*client_princ_name,
	int				requested_op)
{
	/* Check if we want to let this client do this operation. */
	if (strcmp(client_princ_name, CLIENT_PRINC_NAME) == 0
	&&  requested_op == GETSPAN_OP) {
		/* OK, we'll let this access happen. */
		return(IS_AUTHORIZED);
	}

	/* Sorry, Charlie. */
	return(NOT_AUTHORIZED);
}
