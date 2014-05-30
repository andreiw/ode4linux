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
 * $Log: blog_s.c,v $
 * Revision 1.1.4.1  1993/11/09  16:53:58  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:51  damon]
 *
 * Revision 1.1.2.5  1993/05/28  19:15:56  marty
 * 	CR # 558 - Typecasting for rios_aix
 * 	[1993/05/28  19:15:45  marty]
 * 
 * Revision 1.1.2.4  1993/04/15  18:49:14  marty
 * 	Added header files ode/interface.h and stdio.h
 * 	[1993/04/15  18:49:01  marty]
 * 
 * Revision 1.1.2.3  1993/03/19  17:24:47  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/03/19  17:24:10  marty]
 * 
 * Revision 1.1.2.2  1993/03/04  21:48:40  damon
 * 	CR 436. Server portion of blog
 * 	[1993/03/04  21:48:18  damon]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: blog_s.c,v $ $Revision: 1.1.4.1 $ $Date: 1993/11/09 16:53:58 $";

#include <limits.h>
#include <ode/errno.h>
#include <ode/public/error.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <stdio.h>
#include <ode/misc.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>
#include <ode/util.h>
#include <string.h>
#include <sys/param.h>

const char * progname = "blog_s";

UIINIT init [] = {
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

extern BOOLEAN oxm_local;

void
main ( int argc, char ** argv )
{
  SCI_LIST file_set;
  int missing_revs;
  FILE * odexm_args;
  char buf [MAXPATHLEN];
  char * rev_str;
  BOOLEAN all_revs;
  BOOLEAN lock_users;
  BOOLEAN header;
  BOOLEAN rcs_path;
  BOOLEAN long_format;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  sci_new_list ( &file_set );
  odexm_args = fopen ( ui_entry_value ( ARGS_OP, 1 ), "r" );
  fgets ( buf, sizeof (buf), odexm_args ); /* read ODE version string */
  rm_newline ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  rev_str = (char *)strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  all_revs = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  lock_users = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  header = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rcs_path = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  long_format = str_to_BOOLEAN ( buf );
  while ( fgets ( buf, sizeof (buf), odexm_args ) != NULL ) {
    rm_newline ( buf );
    sci_add_to_list_as_is ( file_set, buf );
  } /* while */
  fclose ( odexm_args );
  oxm_local = TRUE;
  sci_lookup_latest_rev_list ( file_set, rev_str, &missing_revs );
  if ( all_revs )
    sci_show_log_list ( file_set, REV_ALL, lock_users, header, rcs_path,
                        long_format );
  else
    sci_show_log_list ( file_set, REV_LATEST, lock_users, header, rcs_path,
                        long_format );
  /* if */
  exit(0);
} /* end main */
