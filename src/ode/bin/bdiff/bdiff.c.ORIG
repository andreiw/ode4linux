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
 * $Log: bdiff.c,v $
 * Revision 1.9.13.2  1994/02/08  16:49:26  damon
 * 	CR 1049. Removed warnings by including string.h
 * 	[1994/02/08  16:49:14  damon]
 *
 * Revision 1.9.13.1  1994/01/05  20:00:16  marty
 * 	Add support for printing out label names with revision numbers during bdiffs
 * 	[1994/01/05  19:59:30  marty]
 * 
 * Revision 1.9.11.2  1993/11/03  21:30:54  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  21:30:47  damon]
 * 
 * Revision 1.9.11.1  1993/10/28  13:31:53  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:08  damon]
 * 
 * Revision 1.9.9.7  1993/04/29  16:40:44  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:40:30  marty]
 * 
 * Revision 1.9.9.6  1993/04/26  19:52:23  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/26  19:35:15  damon]
 * 
 * Revision 1.9.9.5  1993/04/16  20:23:59  damon
 * 	CR 421. Updated usage message for 2.3
 * 	[1993/04/16  20:23:41  damon]
 * 
 * Revision 1.9.9.4  1993/04/15  17:20:58  marty
 * 	Add include ode/interface.h.
 * 	[1993/04/15  17:20:41  marty]
 * 
 * Revision 1.9.9.3  1993/03/16  22:07:00  marty
 * 	Remove &rc_file from call to sci_init().
 * 	[1993/03/16  22:06:44  marty]
 * 
 * Revision 1.9.9.2  1993/02/25  16:13:05  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:12:44  marty]
 * 
 * Revision 1.9.4.8  1992/12/17  21:22:23  damon
 * 	CR 369. Added -b functionality
 * 	[1992/12/17  21:21:42  damon]
 * 
 * Revision 1.9.4.7  1992/12/03  19:03:48  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:33:46  damon]
 * 
 * Revision 1.9.4.6  1992/11/05  17:26:11  damon
 * 	CR 315. Updated usage message.
 * 	[1992/11/05  17:25:29  damon]
 * 
 * Revision 1.9.4.5  1992/09/28  19:39:41  damon
 * 	CR 238. First cut. Code to work with links is being moved
 * 	to some other place.
 * 	[1992/09/28  19:31:24  damon]
 * 
 * Revision 1.9.4.4  1992/08/06  23:33:18  damon
 * 	CR 238. Moved from bin/bcs
 * 	[1992/08/06  23:30:44  damon]
 * 
 * Revision 1.9.4.3  1992/06/23  16:05:25  marty
 * 	Fix up comments.
 * 	[1992/06/23  16:05:08  marty]
 * 
 * 	bdiff now handles files that are symbolic links.
 * 	[1992/06/23  15:59:00  marty]
 * 
 * Revision 1.9.4.2  1992/06/04  23:22:03  damon
 * 	Synched with 2.1.1
 * 	[1992/06/04  23:15:03  damon]
 * 
 * Revision 1.9.2.2  1992/03/25  22:44:45  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  20:12:21  damon]
 * 
 * Revision 1.9  1991/12/05  20:39:57  devrcs
 * 	Fix for bug when bdiff didn't use the correct default revision.
 * 	bdiff took the 1.1 version instead of the file checked out
 * 	when only one revision was given on the command line.
 * 	[91/10/29  07:28:17  rec]
 * 
 * 	added print_revision() and stub print_usage()
 * 	[91/06/03  15:25:21  ezf]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  18:35:40  gm]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:24:32  randyb]
 * 
 * Revision 1.7  90/10/07  21:49:18  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:01:59  gm]
 * 
 * Revision 1.6  90/07/17  12:33:34  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:28:51  gm]
 * 
 * Revision 1.5  90/07/06  00:42:47  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:28:11  gm]
 * 
 * Revision 1.4  90/05/24  23:11:15  devrcs
 * 	Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.3  90/01/03  12:53:19  gm
 * 	Fixed authcover tempfile index code.
 * 	[90/01/03            gm]
 * 
 * Revision 1.2  90/01/02  19:59:05  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:46:58  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 2.4  89/06/18  17:33:24  gm0w
 * 	Updated to use new diag routine and to always print filename
 * 	of command target.
 * 	[89/06/18            gm0w]
 * 
 * Revision 2.3  89/02/05  16:04:42  gm0w
 * 	Added support for -c switch to rcsdiff.  Renamed
 * 	latest_private_rcs_file to just rcs_file.
 * 	[89/02/04            gm0w]
 * 
 * Revision 2.2  89/01/29  13:09:10  gm0w
 * 	Created.
 * 	[89/01/29            gm0w]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: bdiff.c,v $ $Revision: 1.9.13.2 $ $Date: 1994/02/08 16:49:26 $";

#include <string.h>
#include <sys/param.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>

const char *progname = "bdiff";		/* program name */

UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { BACKING_OP,      1, OVERWRITE,  0, 0, "" },
  { REVISION_OP, UNLIMITED, OVERWRITE,  1, 1, ARGS_OP },
  { REVISION2_OP, UNLIMITED, OVERWRITE,  1, 1, ARGS_OP },
  { CONTEXT_OP, 1, OVERWRITE,  0, 0, "" },
  { WHITESPACE_OP, 1, OVERWRITE,  0, 0, ""},
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

char co_buf [ MAXPATHLEN ];
int file_mode;

/*
 * PROTOTYPES
 */
void
handle_switches (void);
void
handle_args( struct rcfile * contents, char * symbolic_name );

void
main ( int argc, char ** argv )
{
  struct rcfile contents;
  char * sb_base = NULL,
       * sb = NULL,
       * sbrc_file = NULL,
       * rc_file = NULL,
       * symbolic_name = NULL,
       * set = NULL,
       * submit_set = NULL;
  char * coc_str;
  char * co_str = co_buf;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  handle_switches ( );

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;
  rc_file = ui_arg_value ( RC_OP, 1, 1 );
  symbolic_name = set;
  sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set,
             &sbrc_file, file_mode, TRUE );
  if ( ui_is_set ( BACKING_OP ) ) {
    get_rc_value ( "check_out_config", &coc_str, &contents, FALSE );
    co_buf [0] = '\0';
    rci_expand_include ( &co_str, coc_str );
  } /* if */
  handle_args ( &contents, symbolic_name );
  exit ( 0 );
} /* end main */

void
handle_switches (void)
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
  if ( ui_is_set ( REVISION2_OP ) ) {
    if ( !ui_is_set ( REVISION_OP ) ) {
      ui_print ( VFATAL, "%s switch requires the %s switch.\n", REVISION2_OP,
                         REVISION_OP );
      exit ( ERROR );
    } /* if */
  } /* if */
}

void
handle_args( struct rcfile * contents, char * symbolic_name )
{
  SCI_LIST file_set;
  int ct;
  char * file;
  BOOLEAN missing_revs;
  char full_co_str [ MAXPATHLEN];
  char * r_symname = NULL;
  char * R_symname = NULL;
  char rev [MAXPATHLEN];

  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct )) != NULL; ct++ ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */
  if ( ui_is_set ( BACKING_OP ) )
    strcpy ( full_co_str, co_buf );
  else if ( ui_is_set ( REVISION_OP ) ) {
    strcpy ( full_co_str, ui_arg_value ( REVISION_OP, 1, 1 ) );
    if (strchr (full_co_str, '.') == NULL)
	r_symname = strdup(full_co_str);
  } else
    strcpy ( full_co_str, symbolic_name );
  /* if */
  sci_lookup_rev_list ( file_set, full_co_str, REV_GENERIC1, &missing_revs );
  if ( ui_is_set ( REVISION2_OP ) ) {
    strcpy (rev, ui_arg_value ( REVISION2_OP, 1, 1 ));
    if (strchr(rev, '.') == NULL)
	R_symname = strdup (rev);

    sci_lookup_rev_list ( file_set, rev, REV_GENERIC2, &missing_revs );
    sci_diff_rev_with_rev ( file_set, ui_is_set ( CONTEXT_OP ),
                            ui_is_set ( WHITESPACE_OP ), r_symname, R_symname );
  } else
    sci_diff_rev_with_file ( file_set, ui_is_set ( CONTEXT_OP ),
                             ui_is_set ( WHITESPACE_OP ), r_symname );
  /* if */
} /* end handle_args */

/* show invocation options */
void print_usage(void)
{ 
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS, "%s [%s rev [%s rev]] [sandbox opts] [ODE opts] [file opts]\n", progname, REVISION_OP, REVISION2_OP );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}
