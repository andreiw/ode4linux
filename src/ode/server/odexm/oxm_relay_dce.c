/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
 * HISTORY
 * $Log: oxm_relay_dce.c,v $
 * Revision 1.1.2.1  1993/08/06  18:47:49  damon
 * 	CR 619. DCE version of odexm
 * 	[1993/08/06  18:47:42  damon]
 *
 * Revision 1.2.2.3  1993/02/04  20:32:26  cjd
 * 	Embedded copyright notice
 * 	[1993/02/04  20:29:44  cjd]
 * 
 * Revision 1.2.2.2  1992/12/18  18:18:23  marcyw
 * 	Defect 4998: adding disclaimer comment
 * 	[1992/12/18  18:12:12  marcyw]
 * 
 * Revision 1.2  1992/01/19  22:14:29  devrcs
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
**	timop_client.c
**
**	Client program for timop interface.
*/

#include <errno.h>
#include <stdio.h>
#include <dce/rpc.h>
#include <dce/pthread.h>
#include <time.h>
#include <dce/utc.h>
#include "odexm.h"
#include "odexm_aux.h"
#include "oxm_relay_dce.h"

long			Rand;		/* sum of random numbers */
int			Workers;	/* number of active worker threads */
pthread_mutex_t		Work_mutex;	/* guard access to Workers, Rand */
pthread_cond_t		Work_cond;	/* condition variable for Workers==0 */

stream_handle sh;

/*
 *	main()
 *
 *	Get started, and main loop.
 */

int
main(
	int				argc,
	char				*argv[])
{
	int				server_num, nservers, ret;
	work_arg_t			work_arg[MAX_SERVERS];
	unsigned_char_t			*server_name[MAX_SERVERS],
	                                    *string_binding, *protseq;
	rpc_binding_handle_t		bind_handle[MAX_SERVERS];
	unsigned32			status;
	utc_t				start_utc, stop_utc, span_utc;
	struct tm			time_tm;
	uuid_t				obj_uuid;
	rpc_ns_handle_t			import_context;
	pthread_t			thread_id[MAX_SERVERS];
	error_status_t			remote_status = rpc_s_ok;
        char test1;
        char buf[1000];
	int len;
        int e_status;
	int i;
	char c;
	/* Check usage and initialize. */
	if (argc < 2 || (nservers = argc-1) > MAX_SERVERS) {
		fprintf(stderr,
		    "Usage: %s server_name ...(up to %d server_name's)...\n",
		    argv[0], MAX_SERVERS);
		exit(1);
	}
	for (server_num = 0; server_num < nservers; server_num += 1) {
		server_name[server_num] = (unsigned_char_t *)argv[1+server_num];
	}

	/* Initialize object uuid. */
	uuid_from_string(OBJ_UUID, &obj_uuid, &status);
	if (status != uuid_s_ok) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}

	/* Import binding info from namespace. */
	for (server_num = 0; server_num < nservers; server_num += 1) {
		/* Begin the binding import loop. */
		rpc_ns_binding_import_begin(rpc_c_ns_syntax_dce,
		    server_name[server_num], odexm_v1_0_c_ifspec,
		    &obj_uuid, &import_context, &status);
		if (status != rpc_s_ok) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}
		/* Import bindings one at a time. */
		while (1) {
			rpc_ns_binding_import_next(import_context,
			    &bind_handle[server_num], &status);
			if (status != rpc_s_ok) {
				fprintf(stderr, "FAULT: %s:%d\n", __FILE__,
				    __LINE__);
				exit(1);
			}
			/* Select, say, the first binding over UDP. */
			rpc_binding_to_string_binding(bind_handle[server_num],
			    &string_binding, &status);
			if (status != rpc_s_ok) {
				fprintf(stderr, "FAULT: %s:%d\n", __FILE__,
				    __LINE__);
				exit(1);
			}
			rpc_string_binding_parse(string_binding, NULL,
			    &protseq, NULL, NULL, NULL, &status);
			if (status != rpc_s_ok) {
				fprintf(stderr, "FAULT: %s:%d\n", __FILE__,
				    __LINE__);
				exit(1);
			}
			rpc_string_free(&string_binding, &status);
			ret = strcmp(protseq, "ncadg_ip_udp");
		        rpc_string_free(&protseq, &status);
			if (ret == 0) {
		                break;
			}
		}
		/* End the binding import loop. */
		rpc_ns_binding_import_done(&import_context, &status);
		if (status != rpc_s_ok) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}
	}

	/* Annotate binding handles for security. */
	for (server_num = 0; server_num < nservers; server_num += 1) {
		rpc_binding_set_auth_info(bind_handle[server_num],
		    SERVER_PRINC_NAME, rpc_c_protect_level_pkt_integ,
		    rpc_c_authn_dce_secret, NULL /*default login context*/,
		    rpc_c_authz_name, &status);
		if (status != rpc_s_ok) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}
	}

	/* Initialize mutex and condition variable. */
	ret = pthread_mutex_init(&Work_mutex, pthread_mutexattr_default);
	if (ret == -1) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}
	ret = pthread_cond_init(&Work_cond, pthread_condattr_default);
	if (ret == -1) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}

	/* Initialize random number generator. */
	srandom(time(NULL));

	/* Initialize work args that are constant throughout main loop. */
	for (server_num = 0; server_num < nservers; server_num += 1) {
		work_arg[server_num].server_num = server_num;
		work_arg[server_num].server_name = server_name[server_num];
		work_arg[server_num].bind_handle = bind_handle[server_num];
	}

	/* Print out the year and date, just once. */
	ret = utc_gettime(&start_utc);
	if (ret == -1) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}
	ret = utc_gmtime(&time_tm, NULL, NULL, NULL, &start_utc);
	if (ret == -1) {
		fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}
	fprintf(stdout, "\n%24.24s UTC (Z time zone)\n\n", asctime(&time_tm));

	/* Main loop -- never exits -- interrupt to quit. */
        odexm_begin ( work_arg[0].bind_handle, &sh );
	while (1) {
		/* Per-loop initialization.  We're single-threaded here, so
		   locks and reentrant random number generator unnecessary. */
		Rand = 0;
		Workers = nservers;
		for (server_num = 0; server_num < nservers; server_num += 1) {
			work_arg[server_num].rand = random()%MAX_RANDOM;
		}

		/* Get client's start timestamp. */
		ret = utc_gettime(&start_utc);
		if (ret == -1) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}

		/* Spawn a worker thread for each server. */
		for (server_num = 0; server_num < nservers; server_num += 1) {
			ret = pthread_create(&thread_id[server_num],
			    pthread_attr_default, (void *)do_work,
			    (void *)&work_arg[server_num]);
			if (ret == -1) {
				fprintf(stderr, "FAULT: %s:%d\n", __FILE__,
				    __LINE__);
				exit(1);
			}
		}

		/* Reap the worker threads; pthread_cond_wait() semantics
		   requires it to be coded this way. */
		ret = pthread_mutex_lock(&Work_mutex);
		if (ret == -1) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}
		while (Workers != 0) {
			ret = pthread_cond_wait(&Work_cond, &Work_mutex);
			if (ret == -1) {
				fprintf(stderr, "FAULT: %s:%d\n", __FILE__,
				    __LINE__);
				exit(1);
			}
		}
		ret = pthread_mutex_unlock(&Work_mutex);
		if (ret == -1) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}
		/* Reclaim storage. */
		for (server_num = 0; server_num < nservers; server_num += 1) {
			ret = pthread_detach(&thread_id[server_num]);
			if (ret == -1) {
				fprintf(stderr, "FAULT: %s:%d\n", __FILE__,
				    __LINE__);
				exit(1);
			}
		}

		/* Any failures? */
		for (server_num = 0; server_num < nservers; server_num += 1) {
			if (work_arg[server_num].status != DO_WORK_OK) {
				exit(1);
			}
		}

		/* Get client's stop timestamp. */
		ret = utc_gettime(&stop_utc);
		if (ret == -1) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}

		/* Calculate the span of client's start and stop timestamps. */
		ret = utc_spantime(&span_utc, &start_utc, &stop_utc);
		if (ret == -1) {
			fprintf(stderr, "FAULT: %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}

	}

	/* Not reached. */
}


/*
 *	do_work()
 *
 *	Do the work.  This is done in parallel threads, so we want it
 *	(and the subroutine print_report() it calls) to be reentrant.
 */

void
do_work(
	work_arg_t			*work_arg_p)
{
	int				server_num, *status_p, ret;
	unsigned_char_t			*server_name;
	rpc_binding_handle_t		bind_handle;
	idl_long_int			rand, status;
        char				test1, test2;
	error_status_t			remote_status = rpc_s_ok;
        char buf[1000];
        int e_status;
	int len;

	/* Unpackage the args into local variables. */
	server_num = work_arg_p->server_num;
	server_name = work_arg_p->server_name;
	bind_handle = work_arg_p->bind_handle;
	rand = work_arg_p->rand;
	status_p = &work_arg_p->status;

        fprintf ( stderr, "server %d\n", server_num );
        for (;;) {
          if ( server_num == 0 ) {
          	fprintf ( stderr, "a: %s\n", buf );
	  	len = read ( 0, buf, sizeof(buf) );
          	fprintf ( stderr, "b: %s\n", buf );
          	odexm_write ( bind_handle, &sh, buf, len, &remote_status);
          	dce_error_inq_text ( status, buf, &remote_status );
          	fprintf ( stderr, "c: %s\n", buf );
          } else {
	  	len = sizeof(buf);
	  	fprintf ( stderr, "c cp 1\n" );
	  	odexm_read ( bind_handle, &sh, &len, buf,
                           &remote_status );
	  	fprintf ( stderr, "c cp 2\n" );
	  	write ( 1, buf, len );
          	dce_error_inq_text ( status, buf, &remote_status );
          	fprintf ( stderr, "e2: %s\n", buf );
          }
        }
	/* Do the RPC! */
	*status_p = DO_WORK_OK;
	pthread_exit(NULL);
	/* Not reached. */
}
