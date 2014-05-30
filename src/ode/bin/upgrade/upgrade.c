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
 * $Log: upgrade.c,v $
 * Revision 1.1.3.3  1993/11/04  21:48:52  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  21:48:45  damon]
 *
 * Revision 1.1.3.2  1993/10/28  13:32:35  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:35  damon]
 * 
 * Revision 1.1.3.1  1993/10/19  20:25:29  damon
 * 	CR 709. Check exit status of sci_init
 * 	[1993/10/19  20:25:20  damon]
 * 
 * Revision 1.1.2.2  1993/05/07  17:11:19  damon
 * 	CR 482. New upgrade command
 * 	[1993/05/07  14:43:40  damon]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: upgrade.c,v $ $Revision: 1.1.3.3 $ $Date: 1993/11/04 21:48:52 $";

#include <stdio.h>
#include <ode/interface.h>
#include <ode/odedefs.h>
#include <sys/param.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>

UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

const char *progname = "upgrade";             /* program name */


int file_mode;

/*
 * PROTOTYPES
 */
void
handle_switches ( void );

void
main ( int argc, char **argv )
{
  struct rcfile contents;
  char * sb_base = NULL,
       * sb = NULL,
       * sbrc_file = NULL,
       * symbolic_name = NULL,
       * set = NULL,
       * submit_set = NULL,
       * file;
  SCI_LIST file_set;
  int ct;
  int missing_revs;

  /* Initialize */
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;

  symbolic_name = set;
  if ( sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set,
       &sbrc_file, file_mode, FALSE ) != OK ) {
    exit ( 1 );
  } /* if */

  /* Lookup "check_out_config" parameter from the backing tree. */
  handle_switches ();

  /* Build up file list of files to process. */
  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct )) != NULL; ct++ ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */ 
  sci_lookup_user_rev_list ( file_set, symbolic_name, &missing_revs );
  sci_config_lookup_list ( file_set );
  sci_ancestor_update_list2 ( file_set );
  exit (0);
}

void
handle_switches ( void )
{
  BOOLEAN ch_flg, sv_flg;

  ch_flg = ui_is_set ( CHANGED_OP);
  sv_flg = ui_is_set ( SAVED_OP );
  file_mode = 0;
  if ( ch_flg && sv_flg ) {
    ui_print ( VFATAL, "Cannot use the %s switch with the %s switch.\n",
               CHANGED_OP, SAVED_OP );
    exit ( ERROR );
  } /* if */
  if ( ch_flg )
    file_mode = 1;
  else if ( sv_flg )
    file_mode = 2;
  /* if */
} /* end handle_switches */

/* show invocation options */
void print_usage(void )
{
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS, "%s [sandbox opts] [ODE opts] [<file>...]\n", progname );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}
