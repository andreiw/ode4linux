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
 * $Log: odexm_manager.c,v $
 * Revision 1.1.2.1  1993/08/06  18:44:24  damon
 * 	CR 619. DCE version of odexm
 * 	[1993/08/06  18:36:16  damon]
 *
 * $EndLog$
 */

#include <stdio.h>
#include <dce/utc.h>
#include "odexm.h"
#include "odexm_aux.h"
#include "odexm_dce.h"
#include <fcntl.h>
#include <sys/mode.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dce/pthread.h>

extern pthread_mutex_t IO_mutex;

/*
 *	getspan_ep()
 *
 *	Entry point for timop_getspan() operation.
 *	Note it is reentrant, so we can have a multi-threaded server.
 */

int in_pipe[2];
int out_pipe[2];
int pid;
int child;

void
oxm_begin_ep(
	rpc_binding_handle_t		bind_handle,
	stream_handle			*sh,
	idl_char			*test1 )
{
  int fd;
  char * arglist[16];
  int exit_status;

  *test1 = 'T';
  arglist[0] = "dc";
  arglist[1] = NULL;

  pipe (in_pipe);
  pipe (out_pipe);
  pid = fork ();
  if ( pid == 0 ) {
          dup2 ( out_pipe[0], 0 );
          close ( out_pipe[0] );
          close ( out_pipe[1] );
          dup2 ( in_pipe[1], 1 );
          close ( in_pipe[0] );
          close ( in_pipe[1] );
          exit_status = execvp(arglist[0], arglist);
    exit(0);
  } 
  close ( in_pipe[1] );
  close ( out_pipe[0] );

  *sh = (stream_handle)0;
}

void
oxm_write_ep(
	rpc_binding_handle_t		bind_handle,
	stream_handle			*sh,
	buffer				buf,
	long				max,
        error_status_t                  *remote_status_p)
{
  int fd;

  *remote_status_p = rpc_s_ok;
  pthread_mutex_lock ( &IO_mutex );
  fprintf ( stderr, "buf: %s\n", buf );
  write ( out_pipe[1], buf, max );
  pthread_mutex_unlock ( &IO_mutex );
}

void
oxm_read_ep(
	rpc_binding_handle_t		bind_handle,
	stream_handle			*sh,
	long				*len,
	buffer				buf,
        error_status_t                  *remote_status_p)
{
  int fd;

  fd_set rmask;

  fprintf ( stderr, "s cp 1\n" );
  *remote_status_p = rpc_s_ok;
  FD_ZERO ( &rmask );
  FD_SET ( in_pipe[0], &rmask );
  select ( in_pipe[0]+1, &rmask, (fd_set *)0, (fd_set *)0,
           (struct timeval *)0 );
  pthread_mutex_lock ( &IO_mutex );
  fprintf ( stderr, "s cp 2 l:%d\n", *len );
  *len = read ( in_pipe[0], buf, *len );
  fprintf ( stderr, "s cp 3 '%c' l: %d\n", buf[0], *len );
  pthread_mutex_unlock ( &IO_mutex );
}
