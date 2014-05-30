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
 * $Log: bco_s.c,v $
 * Revision 1.1.4.1  1993/11/09  16:53:51  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:48  damon]
 *
 * Revision 1.1.2.7  1993/06/07  22:07:12  marty
 * 	CR # 574 - in_lock_dirs() now checks for  null string.
 * 	[1993/06/07  22:07:00  marty]
 * 
 * Revision 1.1.2.6  1993/05/28  19:11:17  marty
 * 	CR # 558 - Proyping for rios_aix
 * 	[1993/05/28  19:11:05  marty]
 * 
 * Revision 1.1.2.5  1993/05/11  21:11:46  damon
 * 	CR 468. Made file locking customizeable
 * 	[1993/05/11  21:10:51  damon]
 * 
 * Revision 1.1.2.4  1993/05/05  18:59:36  damon
 * 	CR 489. Now removes non-existant files from hold file
 * 	[1993/05/05  18:59:28  damon]
 * 
 * Revision 1.1.2.3  1993/05/03  21:40:06  damon
 * 	CR 473. Fixed append_to_hold_file call
 * 	[1993/05/03  21:39:57  damon]
 * 
 * Revision 1.1.2.2  1993/04/14  19:19:37  damon
 * 	CR 193. Moved strict locking to server side
 * 	[1993/04/14  19:19:14  damon]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: bco_s.c,v $ $Revision: 1.1.4.1 $ $Date: 1993/11/09 16:53:51 $";

#include <limits.h>
#include <stdio.h>
#include <ode/errno.h>
#include <ode/interface.h>
#include <ode/lockcmds.h>
#include <ode/misc.h>
#include <ode/odedefs.h>
#include <ode/parse_rc_file.h>
#include <ode/public/error.h>
#include <ode/sci.h>
#include <ode/util.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

const char * progname = "bco_s";

UIINIT init [] = {
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" } };

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

BOOLEAN
in_lock_dirs ( const char * lock_dirs, const char * file )
{
  char * tmp_lock_dirs;
  char * ld_ptr;
  char * dir;
  BOOLEAN result = FALSE;

  if (lock_dirs == NULL)
	return (FALSE);
  tmp_lock_dirs = (char *)strdup ( lock_dirs );
  ld_ptr = tmp_lock_dirs;
  while ( *( dir = (char *)nxtarg ( &ld_ptr, ";" ) ) != NUL ) {
    if ( gmatch ( file, dir ) ) {
      result = TRUE;
      break;
    } /* if */
  } /* while */
  free ( tmp_lock_dirs );
  return ( result );
} /* end in_lock_dirs */

void
main ( int argc, char **argv )
{
  struct rcfile contents;
  char * submit_set = NULL;
ERR_LOG log;


  SCI_LIST file_set;
  FILE * odexm_args;
  char buf [MAXPATHLEN];
  BOOLEAN add;
  char * holdline;
  char * lock_dirs;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  sci_new_list ( &file_set );
  odexm_args = fopen ( ui_entry_value ( ARGS_OP, 1 ), "r" );
  fgets ( buf, sizeof (buf), odexm_args ); /* read ODE version string */
  rm_newline ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  holdline = (char *)strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  add = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  submit_set = (char *)strdup ( buf );
  if ( add ) {
    sci_init3 ( submit_set, &contents );
    get_rc_value ( "lock_dirs", &lock_dirs, &contents, FALSE );
  } /* if */
  while ( fgets ( buf, sizeof (buf), odexm_args ) != NULL ) {
    rm_newline ( buf );
    if ( !add || in_lock_dirs ( lock_dirs, buf ) ) {
      sci_add_to_list_as_is ( file_set, buf );
    } /* if */
  } /* while */
  fclose ( odexm_args );
  if ( add ) {
    exit ( append_to_hold_file ( holdline, file_set, FALSE, &log ) );
  } else {
    exit ( hold_cleanup ( holdline, file_set, submit_set, FALSE ) );
  } /* if */
} /* end main */
