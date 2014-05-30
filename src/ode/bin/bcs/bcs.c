/*
 * COPYRIGHT NOTICE
 * Copyright (c) 1993, 1992, 1991, 1990
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
 * $Log: bcs.c,v $
 * Revision 1.12.10.5  1993/11/08  16:39:25  marty
 * 	CR # 732 - Now verifies non-standard comment leaders with the user.
 * 	[1993/11/08  16:39:10  marty]
 *
 * Revision 1.12.10.4  1993/11/03  22:23:02  marty
 * 	CR # 463 - Include declarations of functions
 * 	[1993/11/03  22:22:34  marty]
 * 
 * Revision 1.12.10.3  1993/11/03  21:18:30  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  21:18:21  damon]
 * 
 * Revision 1.12.10.2  1993/11/03  00:21:01  damon
 * 	CR 773. Complain if user set and submit set are the same
 * 	[1993/11/03  00:20:54  damon]
 * 
 * Revision 1.12.10.1  1993/10/28  13:31:50  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:06  damon]
 * 
 * Revision 1.12.8.1  1993/09/16  17:49:11  damon
 * 	Fixed COPYRIGHT NOTICE section
 * 	[1993/09/16  17:47:14  damon]
 * 
 * Revision 1.12.4.13  1993/05/27  18:41:54  marty
 * 	CR # 558 - type cast for rios_aix
 * 	[1993/05/27  18:41:38  marty]
 * 
 * Revision 1.12.4.12  1993/05/12  19:49:50  marty
 * 	CR # 480 - Fix for outdating specific revisions.
 * 	[1993/05/12  19:49:38  marty]
 * 
 * Revision 1.12.4.11  1993/05/11  18:03:32  marty
 * 	CR# 480 - Add support for "-r" option.
 * 	[1993/05/11  18:03:14  marty]
 * 
 * Revision 1.12.4.10  1993/05/03  20:10:51  damon
 * 	CR 473. outdating now removes co locks from hold file
 * 	[1993/05/03  20:10:44  damon]
 * 
 * Revision 1.12.4.9  1993/04/29  16:36:53  marty
 * 	Prototyping for print_usage() Cr# 463
 * 	[1993/04/29  16:36:41  marty]
 * 
 * Revision 1.12.4.8  1993/04/26  19:52:20  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/26  19:29:25  damon]
 * 
 * Revision 1.12.4.7  1993/04/16  20:11:52  damon
 * 	CR 421. Updated usage message for 2.3
 * 	[1993/04/16  20:11:45  damon]
 * 
 * Revision 1.12.4.6  1993/04/15  17:17:08  marty
 * 	include ode/interface.h file
 * 	[1993/04/15  17:16:49  marty]
 * 
 * Revision 1.12.4.5  1993/03/19  14:56:36  marty
 * 	Convert to client server model.
 * 	[1993/03/18  22:45:43  marty]
 * 
 * Revision 1.12.4.4  1993/02/25  16:14:34  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:14:17  marty]
 * 
 * Revision 1.12.4.3  1993/02/03  19:56:17  damon
 * 	CR 417. Adjusted sci_init call
 * 	[1993/02/03  19:51:20  damon]
 * 
 * Revision 1.12.4.2  1993/01/13  17:41:10  damon
 * 	CR 196. Removed rcs locking
 * 	[1993/01/04  20:33:50  damon]
 * 
 * Revision 1.12.2.12  1993/01/08  18:54:00  marty
 * 	Added exit of zero error status.
 * 	[1993/01/08  18:53:43  marty]
 * 
 * Revision 1.12.2.11  1992/11/30  19:11:43  damon
 * 	CR 342. Added calls to sci_set_symbol_list for -N and -n
 * 	[1992/11/30  19:10:07  damon]
 * 
 * Revision 1.12.2.10  1992/11/12  18:45:05  damon
 * 	CR 329. Changed PATH_MAX to MAXPATHLEN and include param.h
 * 	[1992/11/12  18:44:14  damon]
 * 
 * Revision 1.12.2.9  1992/11/06  19:40:05  damon
 * 	CR 296. Removed extra definitions
 * 	[1992/11/06  19:39:06  damon]
 * 
 * Revision 1.12.2.8  1992/11/05  17:26:09  damon
 * 	CR 315. Updated usage message.
 * 	[1992/11/05  17:25:27  damon]
 * 
 * Revision 1.12.2.7  1992/11/02  19:37:10  damon
 * 	CR 310. Allow -o && -u
 * 	[1992/11/02  19:36:56  damon]
 * 
 * Revision 1.12.2.6  1992/09/24  18:57:47  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:16:03  gm]
 * 
 * Revision 1.12.2.5  1992/09/17  18:30:49  damon
 * 	CR 238. Adjusted call to sci_init
 * 	[1992/09/17  18:23:18  damon]
 * 
 * Revision 1.12.2.4  1992/08/27  21:32:52  damon
 * 	CR 238. Fixed argument processing error.
 * 	[1992/08/27  21:32:34  damon]
 * 
 * Revision 1.12.2.3  1992/08/06  22:11:00  damon
 * 	CR 238. Fixed logic error with REV_OP
 * 	[1992/08/06  22:10:17  damon]
 * 
 * Revision 1.12.2.2  1992/08/05  19:23:24  damon
 * 	Converted to use sci_rcs
 * 	[1992/08/05  19:22:33  damon]
 * 
 * Revision 1.12  1991/12/05  20:39:50  devrcs
 * 	now gives setname when confirming outdate (rather than "BCSSET")
 * 	[91/10/30  10:38:17  ezf]
 * 
 * 	moved external function declarations to bcs.h
 * 	[91/07/23  11:08:49  ezf]
 * 
 * 	added print_revision()
 * 	[91/06/03  14:50:52  ezf]
 * 
 * 	Added support for odedefs.h
 * 	[91/05/28  13:51:52  damon]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  18:35:29  gm]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:24:27  randyb]
 * 
 * Revision 1.10  90/10/07  21:49:10  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:01:46  gm]
 * 
 * Revision 1.9  90/09/13  13:02:56  devrcs
 * 	Added rcsfullstat to use new rcsstat -D feature for defuncting
 * 	[90/08/03  12:55:40  jbd]
 * 	Change state to Exp on outdates to foil defuncting
 * 	[90/08/01  16:12:30  jbd]
 * 
 * Revision 1.8  90/07/17  12:33:28  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:28:46  gm]
 * 
 * Revision 1.7  90/07/06  00:42:44  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:27:57  gm]
 * 
 * Revision 1.6  90/06/22  21:54:00  devrcs
 * 	Added -nolock switch.
 * 	[90/06/14  13:01:54  gm]
 * 
 * Revision 1.5  90/05/24  23:11:10  devrcs
 * 	Fixed bug in outdate_branch that did not return a status value.
 * 	[90/05/13            gm]
 * 
 * 	Added code to set file permission for -l and -u switches.
 * 	[90/05/10            gm]
 * 
 * 	Added call to config_remove when file has been outdated and removed.
 * 	Added check to suppress rcs command execution when no arguments were
 * 	being passed to it.
 * 	[90/05/10  15:07:05  gm]
 * 
 * 	Removed -rm and -oknew switches.  Added -autooutdate and -unlock
 * 	switches.  Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.4  90/04/14  00:52:25  devrcs
 * 	Fixed bug in outdate range code.  Reworked outdate code to
 * 	be more flexible.
 * 	[90/03/10  09:28:41  gm]
 * 
 * Revision 1.3  90/01/18  08:50:01  gm
 * 	Added -N and -n to manipulate branch name symbols.
 * 	[90/01/08            gm]
 * 
 * Revision 1.2  90/01/02  19:59:04  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:46:52  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 2.4  89/06/18  17:33:19  gm0w
 * 	Updated to use new diag routine and to always print filename
 * 	of command target.
 * 	[89/06/18            gm0w]
 * 
 * Revision 2.3  89/02/05  16:04:20  gm0w
 * 	Renamed latest_private_rcs_file to just rcs_file.
 * 	[89/02/04            gm0w]
 * 
 * Revision 2.2  89/01/29  13:09:36  gm0w
 * 	Created.
 * 	[89/01/29            gm0w]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: bcs.c,v $ $Revision: 1.12.10.5 $ $Date: 1993/11/08 16:39:25 $";

#include <limits.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>
#include <ode/sci_client.h>
#include <ode/util.h>
#include <string.h>
#include <sys/param.h>

UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { OUTDATE_OP,      1, OVERWRITE,  0, 1, "" },
  { REVISION_OP, 1, OVERWRITE,  1, 1, ARGS_OP },
  { BIG_SYMNAME_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SML_SYMNAME_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { COMMENT_LEADER_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

const char *progname = "bcs";

int file_mode;

char * submit_set = NULL;

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
       * set = NULL;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  handle_switches ( );

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;
  rc_file = ui_arg_value ( RC_OP, 1, 1 );

  symbolic_name = set;
  sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set,
	     &sbrc_file, file_mode, FALSE );
  handle_args ( &contents, symbolic_name );
  exit(0);
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
} /* end handle_switches */

void
handle_args( struct rcfile * contents, char * symbolic_name )
{
  SCI_LIST file_set;
  int ct;
  char * file;
  char prompt[MAXPATHLEN];
  BOOLEAN outdate,
	  revision_opt = FALSE,
	  leader_opt,
	  big_sym_opt,
	  small_sym_opt;
  char 	* name,
	* leader,
	* big_symbol,
	* small_symbol,
	* revision = NULL;
  char  outdate_msg[MAXPATHLEN];
  char  new_leader[MAXPATHLEN];

  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct )) != NULL; ct++ ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */
  if ( ui_is_set ( OUTDATE_OP ) ) {
    if ( ui_is_set ( REVISION_OP ) ) {
	revision = ui_arg_value ( REVISION_OP, 1, 1 );
	revision_opt = TRUE;
	name = strdup(revision);  
	sprintf (outdate_msg, "Confirm outdate for revision %s",
		revision);
    } else {
	strcpy (outdate_msg, "Confirm outdate for (all revisions)");
    	name = symbolic_name;
    }

    if ( ! ui_is_set ( AUTO_OP ) ) {
      (void) concat(prompt, sizeof(prompt), outdate_msg, NULL);
      if (!getbool(prompt, FALSE))
        exit(1);
      /* if */
    } /* if */

    outdate = TRUE;
  } else {
    outdate = FALSE;
    name = NULL; 
  } 
  if ( ui_is_set ( COMMENT_LEADER_OP ) ) {
    leader_opt = TRUE;
    leader = ui_arg_value ( COMMENT_LEADER_OP, 1, 1 );

    for (;;) {
      if (match_comment_leader(leader, *contents) == FALSE) {
                        sprintf (prompt, "The comment leader you have specified \nis not standard.  You may enter a different one or keep this comment leader \nby typing carriage return");
                        getstr (prompt, leader, new_leader);
            if ( strcmp ( leader, new_leader ) == 0 ) {
              leader = (char *) strdup (new_leader);
              break;
            } /* if */
            leader = (char *) strdup (new_leader);
      } else {
            break;
      } /* if */
    } /* for */

  } else {
    leader_opt = FALSE;
    leader = NULL; 
  }
  if ( ui_is_set ( BIG_SYMNAME_OP ) ) {
    big_sym_opt = TRUE;
    big_symbol = ui_arg_value ( BIG_SYMNAME_OP, 1, 1 );
  } else {
    big_sym_opt = FALSE;
    big_symbol = NULL;
  } 
  if ( ui_is_set ( SML_SYMNAME_OP ) ) {
    small_sym_opt = TRUE;
    small_symbol = ui_arg_value ( SML_SYMNAME_OP, 1, 1 );
  } else {
    small_sym_opt = FALSE;
    small_symbol = NULL;
  }
  if ( outdate && strcmp ( submit_set, name ) == 0 ) {
      ui_print ( VWARN, "User's set cannot be the same as the submit set.\n" );
      ui_print ( VCONT, "User's set and submit set are both: %s\n",
                        submit_set );
      ui_print ( VCONT, "Aborting bcs.\n" );
      exit(1);
  } /* if */
  sci_server_bcs_opts ( file_set, revision_opt, outdate, name, 
			submit_set, leader_opt,
                        leader, big_sym_opt, big_symbol, small_sym_opt,
                        small_symbol);

  if ((outdate) && (revision_opt == FALSE))
	sci_outdate_list_p2 (file_set, name);
  

} /* end handle_args */

/* show invocation options */
void print_usage(void)
{
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS,
             "%s\t[%s CmtLeader] [[%s | %s] SymbolicName] [%s [%s rev]]\n",
             progname, COMMENT_LEADER_OP, BIG_SYMNAME_OP, SML_SYMNAME_OP,
             OUTDATE_OP, REVISION_OP );
  ui_print ( VALWAYS, "\t[sandbox opts] [ODE opts] [file opts]\n\n", progname );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VALWAYS, "%s\n\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s\t%s\n", progname, USAGE_VER_USAGE );
}
