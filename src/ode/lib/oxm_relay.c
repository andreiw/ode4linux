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
 */
/*
 * HISTORY
 * $Log: oxm_relay.c,v $
 * Revision 1.9.12.1  1993/11/09  20:08:25  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  20:08:03  damon]
 *
 * Revision 1.9.10.1  1993/08/19  19:02:46  damon
 * 	CR 622. Fixed alloc problem, removed garbage
 * 	[1993/08/19  19:01:08  damon]
 * 
 * Revision 1.9.7.8  1993/06/28  16:51:23  damon
 * 	CR 592. Cleaned up some mem leaks
 * 	[1993/06/28  16:50:02  damon]
 * 
 * Revision 1.9.7.7  1993/06/24  14:12:01  damon
 * 	CR 592. Reduced memory leak
 * 	[1993/06/24  14:11:53  damon]
 * 
 * Revision 1.9.7.6  1993/05/27  20:10:13  marty
 * 	CR # 558 - get it building on rios_aix.
 * 	[1993/05/27  20:09:14  marty]
 * 
 * Revision 1.9.7.5  1993/05/26  18:07:48  damon
 * 	CR 553. Check for and use tcp service number on cmd line
 * 	[1993/05/26  17:17:56  damon]
 * 
 * Revision 1.9.7.4  1993/05/19  19:56:42  damon
 * 	CR 515. Changed getw()s to read()s
 * 	[1993/05/19  19:56:32  damon]
 * 
 * Revision 1.9.7.3  1993/04/29  19:18:21  damon
 * 	CR 464. Port to 386bsd from gm
 * 	[1993/04/29  19:10:52  damon]
 * 
 * Revision 1.9.7.2  1993/03/11  20:09:41  damon
 * 	CR 256. odexm_end now returns
 * 	[1993/03/11  20:09:22  damon]
 * 
 * 	CR 256. odexm_end now returns
 * 	[1993/03/11  12:13:41  damon]
 * 
 * Revision 1.9.5.5  1992/12/03  17:23:09  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:09:35  damon]
 * 
 * Revision 1.9.5.4  1992/11/13  15:20:41  root
 * 	Removed declarations of rindex, getenv
 * 	[1992/11/13  15:13:23  root]
 * 
 * Revision 1.9.5.3  1992/09/21  19:14:53  damon
 * 	Changed debug flag to indicate new protocol
 * 	[1992/09/21  19:14:37  damon]
 * 
 * Revision 1.9.4.2  1992/09/03  19:56:13  damon
 * 	Changed to handle args better
 * 	Now using newer rc files
 * 	Now detects EOF of command execution
 * 
 * Revision 1.9  1991/12/05  21:13:46  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:14:00  mckeen]
 * 
 * 	added print_revision() and "-version" switch
 * 	[91/07/20  15:25:40  ezf]
 * 
 * 	Added progname constant
 * 	[91/01/09  15:59:20  mckeen]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:12:33  dwm]
 * 
 * Revision 1.7  90/10/07  21:55:29  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:11:06  gm]
 * 
 * Revision 1.6  90/07/17  12:37:20  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:31:21  gm]
 * 
 * Revision 1.5  90/05/24  23:12:55  devrcs
 * 	Removed kerberos retry failure loop.  No kerberos, no failures.
 * 	[90/05/05  18:40:18  gm]
 * 
 * Revision 1.4  90/04/14  00:53:14  devrcs
 * 	Changes for new authentication protocol.
 * 	[90/03/06  20:22:15  gm]
 * 
 * Revision 1.3  90/01/02  19:59:34  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.2  89/12/26  10:48:39  gm
 * 	Created.
 * 	[89/12/23            gm]
 * 
 * $EndLog$
 */

/*
 * rcsauth - authentication cover for rcs commands
 */
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/errno.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <ode/odedefs.h>
#include <ode/private/oxm_relay.h>
#include <ode/util.h>

#define SEND_OVER	1
#define WANT_BACK	2

#define ATOI(n, p, s) \
    (s) = 0; \
    (n) = 0; \
    if ('0' > *(p) || *(p) > '9') \
        (s) = -1; \
    while ('0' <= *(p) && *(p) <= '9') { \
        (n) = (n) * 10 + (*(p) - '0'); \
        (p)++; \
    }

const char *progname = "oxm_relay";

    char *authcover_testdir;
    char *authcover_host;
    char *authcover_user;
    int tempmode = 0;
    int tempslot = 0;

extern int service_number;

/*
 * PROTOTYPES
 */
void
get_temp_info ( int *argc, char *** argv );
int get_argv ( int * argc, char *** argv );
void
get_temp_info ( int *argc, char *** argv );
void
free_argv ( int argc, char ** argv, char ** orig_argv );

void
main(int argc, char ** argv)
{
    int debug;
  int status;
  int new_argc;
  char ** new_argv;
  char ** orig_argv;
  char * str1 = (char *)"odexm_begin";
  char * str2 = (char *)"odexm_end";
  char * arg_ptr;

  debug = ((char *)getenv("AUTHCOVER_DEBUG") != NULL);
    argc--;
    argv++;

    if (argc >= 1 && argv[0][0] == '-' && argv[0][1] == 'v') {
	ui_print_revision();	/* "-version" switch */
        exit(0);
    } /* if */
    if (argc < 1)
	quit( 1, "usage: %s <host> <uniq id> | -version\n",
              progname);
    if ( argc == 3 ) {
      arg_ptr = argv[2];
      ATOI ( service_number, arg_ptr, status );
    } /* if */
    if ( odexm_begin ( argv[0], argv[1], debug ) != 0 )
      exit ( -1 );
  /* if */
  if ( 1 ) {

   /*
    * Tell odexm that we're going to do a start a slew of commands.
    */
    new_argv = &str1;
    new_argc = 1;
    get_temp_info ( &new_argc, &new_argv );
    status = odexm ( tempmode, tempslot, new_argc, new_argv, TRUE );

    while ( get_argv ( &new_argc, &new_argv ) ) {
      orig_argv = new_argv;
      get_temp_info ( &new_argc, &new_argv );
      status = odexm( tempmode, tempslot,  new_argc, new_argv, FALSE);
      free_argv ( new_argc, new_argv, orig_argv );
    } /* while */
   /*
    * Tell odexm that we're done
    */
    new_argv = &str2;
    new_argc = 1;
    get_temp_info ( &new_argc, &new_argv );
    status = odexm ( tempmode, tempslot, new_argc, new_argv, TRUE );
  } else {
    get_temp_info ( &argc, &argv );
    status = odexm( tempmode, tempslot, argc, argv, FALSE);
  } /* if */
  odexm_end ( );
  exit ( status );
} /* main */

void
get_temp_info ( int *argc, char *** argv )
{
    tempslot = 0;
    tempmode = 0;
    if (*argc >= 2 && (*argv[0][0]) == '-' && (*argv)[0][1] == 't') {
	if ((*argv)[0][2] == '0')
	    tempmode = WANT_BACK;
	else if ((*argv)[0][2] == '1')
	    tempmode = SEND_OVER;
	else if ((*argv)[0][2] == '2')
	    tempmode = SEND_OVER|WANT_BACK;
	else
	    quit(1, "%s: invalid temp mode\n", progname);
	tempslot = atoi((*argv)[1]);
	if (tempslot < 0)
	    quit(1, "%s: bad tempslot\n", progname);
	*argc -= 2;
/*
        free(**argv);
*/
	*argv +=1;
/*
        free(**argv);
*/
	*argv +=1;
    } /* if */
} /* get_temp_info */

void
free_argv ( int argc, char ** argv, char ** orig_argv )
{
  int i;
  char ** arg_ptr;

  arg_ptr = argv;
  for ( i = 0; i < argc; i++ ) {
    free ( *arg_ptr );
    arg_ptr++;
  } /* for */
  free ( orig_argv );
} /* end free_argv */

int get_argv ( int * argc, char *** argv )
{
    char buf[16384];
    char dir[MAXPATHLEN];
    int i;
    int len;
    int bytes_read;

 /*
  * Get length of directory string. If zero, don't chdir.
  */
  bytes_read = read ( 0, &len, sizeof(len) );
  if ( bytes_read == 0 )
    return ( FALSE );
  /* if */
  if ( len > 0 ) {
    read ( 0, dir, len );
    dir [len] = '\0';
    chdir ( dir );
  } /* if */
  bytes_read = read ( 0, argc, sizeof (*argc) );
  if (( *argv = (char **) calloc ( *argc, sizeof (char *))) == NULL ) {
    fprintf ( stderr,   "could not calloc space for rc file options.\n" );
    return ( FALSE );
  } /* if */
  for ( i = 0; i < *argc; i++ ) {
    read ( 0, &len, sizeof(len) );
    read ( 0, buf, len );
    buf [len] = '\0';
    if (( (*argv)[i] = (char *)strdup ( buf )) == NULL ) {
      return ( FALSE );
    } /* if */

  } /* for */
  return ( TRUE );
} /* get_to_argv */
