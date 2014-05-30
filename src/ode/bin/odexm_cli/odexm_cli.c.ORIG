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
 */
/*
 * HISTORY
 * $Log: odexm_cli.c,v $
 * Revision 1.1.10.1  1993/11/04  20:17:22  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  20:17:14  damon]
 *
 * Revision 1.1.7.4  1993/08/13  19:20:40  damon
 * 	CR 607. Termination change did not get in
 * 	[1993/08/13  19:20:34  damon]
 * 
 * Revision 1.1.7.3  1993/08/11  17:05:19  damon
 * 	CR 610. Added INC_SELECT
 * 	[1993/08/11  17:05:14  damon]
 * 
 * Revision 1.1.7.2  1993/08/09  18:02:23  damon
 * 	CR 607. Added proper termination
 * 	[1993/08/09  18:00:36  damon]
 * 
 * Revision 1.1.7.1  1993/07/21  16:01:41  damon
 * 	CR 607. Added stdin handling
 * 	[1993/07/21  16:00:47  damon]
 * 
 * Revision 1.1.2.7  1993/05/28  14:28:44  marty
 * 	CR # 558 - Get it bulding on rios_aix
 * 	[1993/05/28  14:28:33  marty]
 * 
 * Revision 1.1.2.6  1993/05/19  19:45:35  damon
 * 	CR 486. Fix printing of buffer
 * 	[1993/05/19  19:45:26  damon]
 * 
 * Revision 1.1.2.5  1993/05/05  20:17:35  damon
 * 	CR 486. Using oxm_read instead of oxm_gets
 * 	[1993/05/05  20:17:26  damon]
 * 
 * Revision 1.1.2.4  1993/01/18  17:24:08  damon
 * 	CR 400. Changed puts to printf to remove extra newline
 * 	[1993/01/18  17:23:54  damon]
 * 
 * Revision 1.1.2.3  1993/01/18  17:19:56  damon
 * 	CR 400. Pass along stdout
 * 	[1993/01/18  17:19:30  damon]
 * 
 * Revision 1.1.2.2  1993/01/14  18:38:23  damon
 * 	CR 400. Created odexm_cli
 * 	[1993/01/14  18:37:54  damon]
 * 
 * $EndLog$
 */
#include <stdio.h>
#include <ode/interface.h>
#include <ode/odexm.h>
#include <ode/public/odexm_client.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#ifdef INC_SELECT
#include <sys/select.h>
#endif
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

const char * progname = "odexm_cli";

#define MAX_MONITORS 1

OXMINIT oxminit [MAX_MONITORS];

void
main(int argc, char **argv)
{
  ERR_LOG log;
  OXM_CNXTN monitor;
  char **arg_ptr;
  int status;
  int len;
  int out_fd;
  fd_set rmask;
  int res;

  char buf [MAXPATHLEN+1];
  char buf2 [MAXPATHLEN+1];
  arg_ptr = argv;
  arg_ptr++;
  oxminit [0].monitor = 0;
  oxminit [0].host = (char *)strdup ( *arg_ptr++ );
  oxminit [0].relay = "oxm_relay_tcp";
  oxminit [0].ident = (char *)strdup ( *arg_ptr++ );
  oxm_init ( MAX_MONITORS, oxminit );
  log = oxm_open ( &monitor, 0 );
  out_fd = oxm_stdout ( monitor );
  log = oxm_runcmd ( monitor, argc-3, (const char **)arg_ptr, NULL );
  for (;;) {
    FD_ZERO ( &rmask );
    FD_SET ( 0, &rmask );
    FD_SET ( out_fd, &rmask );
    if ( ( res = select ( out_fd+1, (fd_set *)&rmask, (fd_set *)0,
                          (fd_set *)0, (struct timeval *)0 ) ) < 1) {
      continue;
    } /* if */
    if ( FD_ISSET ( out_fd, &rmask ) ) {
      len = oxm_read ( monitor, buf, sizeof(buf)-1, &log );
      if ( len == 0 ) {
        break;
      } /* if */
      write ( 1, buf, len );
      while ( oxm_poll ( monitor ) ) {
        len = oxm_read ( monitor, buf, sizeof(buf)-1, &log );
        if ( len == 0 ) {
          break;
        } /* if */
        write ( 1, buf, len );
      } /* while */
    } else if ( FD_ISSET ( 0, &rmask ) ) {
      len = read ( 0, buf2, sizeof(buf2) );
      oxm_write ( monitor, buf2, len, &log );
    } /* if */
  } /* for */
  log = oxm_endcmd ( monitor, &status );
  log = oxm_close ( monitor );
  exit ( status );
}
