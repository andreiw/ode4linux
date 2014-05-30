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
 * $Log: bco.c,v $
 * Revision 1.14.16.8  1994/02/24  18:45:27  marty
 * 	CR # 1061 - Use correct pathname when using "-undo" switch.
 * 	[1994/02/24  18:45:08  marty]
 *
 * Revision 1.14.16.7  1994/01/06  17:21:25  damon
 * 	CR 949. Exit with status 1 if files do not exist
 * 	[1994/01/06  17:21:16  damon]
 * 
 * Revision 1.14.16.6  1993/12/16  21:26:20  damon
 * 	CR 922. Print out msg if no file to undo
 * 	[1993/12/16  21:26:06  damon]
 * 
 * Revision 1.14.16.5  1993/11/23  16:53:30  damon
 * 	CR 747. Added user selectable ancestor check-out
 * 	[1993/11/23  16:53:18  damon]
 * 
 * Revision 1.14.16.4  1993/11/22  20:34:13  marty
 * 	CR # 234 - Add "-p" switch (output to screen) to bco.
 * 	[1993/11/22  20:33:52  marty]
 * 
 * Revision 1.14.16.3  1993/11/22  17:48:58  damon
 * 	CR 463. Added length_of_branch proto
 * 	[1993/11/22  17:48:50  damon]
 * 
 * Revision 1.14.16.2  1993/11/19  20:44:59  marty
 * 	CR # 463 - Pedantic messages
 * 	[1993/11/19  20:44:43  marty]
 * 
 * Revision 1.14.16.1  1993/11/19  19:35:13  marty
 * 	CR # 663 - Bring back "-undo" option.
 * 	[1993/11/19  19:34:53  marty]
 * 
 * 	CR # 663 - Adde "-undo" option.
 * 	[1993/11/16  13:33:27  marty]
 * 
 * Revision 1.14.14.4  1993/11/03  20:58:06  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  20:57:39  damon]
 * 
 * Revision 1.14.14.3  1993/11/03  20:40:00  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  18:40:46  damon]
 * 
 * Revision 1.14.14.2  1993/11/03  00:10:22  damon
 * 	CR 773. Complain if user set and submit set are the same
 * 	[1993/11/02  23:58:18  damon]
 * 
 * Revision 1.14.14.1  1993/10/28  13:31:40  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:03  damon]
 * 
 * Revision 1.14.11.2  1993/09/10  14:16:46  marty
 * 	CR # 664 - "bco -read" should check out from private branch if one exists.
 * 	[1993/09/10  14:15:01  marty]
 * 
 * Revision 1.14.11.1  1993/09/02  20:54:31  marty
 * 	CR # 649 - Add alias of -u to -read option. (Along with warnings).
 * 	[1993/09/02  20:54:10  marty]
 * 
 * Revision 1.14.7.17  1993/05/27  18:38:42  marty
 * 	CR # 558 - Type casting on the rios_aix.
 * 	[1993/05/27  18:38:28  marty]
 * 
 * Revision 1.14.7.16  1993/05/18  20:45:53  marty
 * 	CR # 420 - Don't unlink the lock file. leave it.
 * 	[1993/05/18  20:45:39  marty]
 * 
 * Revision 1.14.7.15  1993/05/18  19:38:27  marty
 * 	CR # 420 - bco now locks the sandbox during check-outs (as opposed
 * 	to sci_init() locking it).
 * 	[1993/05/18  19:38:12  marty]
 * 
 * Revision 1.14.7.14  1993/05/11  21:11:42  damon
 * 	CR 468. Made file locking customizeable
 * 	[1993/05/11  21:11:16  damon]
 * 
 * Revision 1.14.7.13  1993/05/05  18:58:10  damon
 * 	CR 489. Does not add non-existant files to hold file
 * 	[1993/05/05  18:58:04  damon]
 * 
 * Revision 1.14.7.12  1993/04/30  19:51:39  damon
 * 	Removed extraneous ifdef notdefs
 * 	[1993/04/30  19:51:29  damon]
 * 
 * Revision 1.14.7.11  1993/04/29  16:30:45  marty
 * 	Prototypes for print_usage(). CR # 463
 * 	[1993/04/29  16:30:33  marty]
 * 
 * Revision 1.14.7.10  1993/04/26  19:52:14  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/26  19:28:11  damon]
 * 
 * Revision 1.14.7.9  1993/04/16  19:57:42  damon
 * 	CR 421. Updated usage message for 2.3
 * 	[1993/04/16  19:57:16  damon]
 * 
 * Revision 1.14.7.8  1993/04/14  19:22:32  damon
 * 	CR 193. Moved strict locking to server side
 * 	[1993/04/14  19:22:12  damon]
 * 
 * Revision 1.14.7.7  1993/03/30  19:14:54  damon
 * 	CR 193. Temporarily disabling file locking
 * 	[1993/03/30  19:14:43  damon]
 * 
 * Revision 1.14.7.6  1993/02/25  16:17:22  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:17:04  marty]
 * 
 * Revision 1.14.7.5  1993/02/19  18:55:55  damon
 * 	CR 193. Added strict locking to lockcmds.c
 * 	[1993/02/19  18:55:07  damon]
 * 
 * Revision 1.14.7.4  1993/02/11  16:24:27  damon
 * 	CR 196. Changed -u to -read
 * 	[1993/02/11  16:23:40  damon]
 * 
 * Revision 1.14.7.3  1993/02/03  19:56:09  damon
 * 	CR 417. Adjusted sci_init call
 * 	[1993/02/03  19:51:17  damon]
 * 
 * Revision 1.14.7.2  1993/01/13  16:43:03  damon
 * 	CR 382. Removed S_ISREG and other cruft
 * 	[1993/01/05  20:20:32  damon]
 * 
 * Revision 1.14.4.13  1993/01/08  18:45:09  marty
 * 	Add exit with zero error status.
 * 	[1993/01/08  18:44:53  marty]
 * 
 * Revision 1.14.4.12  1992/12/03  19:03:37  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:33:37  damon]
 * 
 * Revision 1.14.4.11  1992/11/05  16:58:22  damon
 * 	CR 315. Updated usage message.
 * 	[1992/11/05  16:57:50  damon]
 * 
 * Revision 1.14.4.10  1992/11/02  19:32:41  damon
 * 	CR 292. Removed -undo option.
 * 	[1992/11/02  16:50:44  damon]
 * 
 * Revision 1.14.4.9  1992/10/19  14:53:07  damon
 * 	CR 309. -u works
 * 	[1992/10/19  14:45:31  damon]
 * 
 * Revision 1.14.4.8  1992/09/30  14:11:20  damon
 * 	CR 238. Adjusted to synch with sci API
 * 	[1992/09/30  14:10:49  damon]
 * 
 * Revision 1.14.4.7  1992/09/24  18:57:42  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:15:57  gm]
 * 
 * Revision 1.14.4.6  1992/08/27  16:15:39  marty
 * 	Small fix.
 * 	[1992/08/27  16:14:54  marty]
 * 
 * 	Testing.
 * 	[1992/08/27  16:05:25  marty]
 * 
 * Revision 1.14.4.5  1992/08/27  15:03:58  marty
 * 	Rewrite for new source control API.
 * 	[1992/08/27  15:03:38  marty]
 * 
 * 	More cahnges
 * 	[1992/08/26  21:31:31  marty]
 * 
 * 	More edits for source control API work.
 * 	[1992/08/21  20:51:36  marty]
 * 
 * Revision 1.14.4.4  1992/08/20  22:22:13  marty
 * 	More source code API stuff
 * 	[1992/08/20  22:21:56  marty]
 * 
 * 	Fix bco for source control API.
 * 	[1992/08/18  20:47:30  marty]
 * 
 * 	*** empty log message ***
 * 	[1992/08/17  23:19:38  marty]
 * 
 * 	*** empty log message ***
 * 	[1992/08/14  21:22:33  marty]
 * 
 * Revision 1.14.4.3  1992/08/06  23:33:06  damon
 * 	CR 238. Moved from bin/bcs
 * 	[1992/08/06  23:30:28  damon]
 * 
 * Revision 1.14.4.2  1992/06/16  22:11:35  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:01:02  damon]
 * 
 * Revision 1.14.2.2  1992/03/25  22:44:33  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  20:12:13  damon]
 * 
 * Revision 1.14  1991/12/05  20:39:42  devrcs
 * 	Fixed case where a specific revision is checked out
 * 	unlocked. (e.g., -u -rx.x.x.x).  SCAPI expects only
 * 	to receive the revision number, not the '-r' flag as well.
 * 	[91/07/25  10:33:20  zeliff]
 * 
 * 	added print_revision() and stub print_usage()
 * 	[91/06/03  15:14:29  ezf]
 * 
 * 	Added support for odedefs.h
 * 	[91/05/28  13:51:39  damon]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  17:42:39  gm]
 * 
 * 	Removed references to parse_cmd_line and get_currents...
 * 	Replaced get_current with current_sb and current_set from sbdata.c
 * 	[91/01/14  10:46:39  randyb]
 * 
 * 	Change/fix processing of swiches for -r, -u, -from
 * 	[91/01/11  16:27:07  robert]
 * 
 * 	Changed sdm to ode
 * 	[91/01/11  12:07:58  randyb]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:24:15  randyb]
 * 
 * 	changed argument to get_rc_value to pointer
 * 	[90/12/31  10:39:04  randyb]
 * 
 * 	Lots of new changes, prior to Glenn's abstraction of
 * 	RCS interface. Add ptr to sandbox rc as param to
 * 	call of build_list_getrec
 * 	[90/12/14  14:51:58  robert]
 * 
 * 	Added check_from routine & changes to local parser
 * 	for -from arg. Requires new libsb routine blist_getrec.c.
 * 	This is first version of -from.
 * 	[90/12/07  14:49:15  robert]
 * 
 * 	Changed order of tests for check-out of an unlocked
 * 	revision.  Allow "bco -u -r[arg] <file>" even if file
 * 	revision exists on current branch.
 * 	[90/11/06  15:07:01  robert]
 * 
 * Revision 1.12  90/10/07  21:49:00  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:01:31  gm]
 * 
 * Revision 1.11  90/09/13  13:02:53  devrcs
 * 	Added defunct support.
 * 	[90/08/26  16:50:08  gm]
 * 
 * Revision 1.10  90/08/25  12:20:28  devrcs
 * 	This implementation of -undo should supercede any previous versions
 * 	[90/08/09  15:25:43  robert]
 * 
 * Revision 1.9  90/07/17  12:33:19  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:28:35  gm]
 * 
 * Revision 1.8  90/07/06  00:42:37  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:27:18  gm]
 * 
 * Revision 1.7  90/06/22  21:53:53  devrcs
 * 	Added -nolock switch.
 * 	[90/06/14  13:01:37  gm]
 * 
 * Revision 1.6  90/05/24  23:11:04  devrcs
 * 	Fixed bug that caused bco -u to not get revision from current set.
 * 	[90/05/20  11:34:39  gm]
 * 
 * 	Moved create_branch to subrs module.  Added code to call
 * 	config_insert.  Changed -u to not insert into set file.
 * 	[90/05/10  13:28:09  gm]
 * 
 * 	Removed AFS unlog.  Removed -nowrite switch.  Require that -u be
 * 	specified with -r<rev> switch.  Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.5  90/04/14  00:52:19  devrcs
 * 	Added initialization for need_makepath.  Changed code to use the
 * 	revision checked out before creating initial branch as the working
 * 	file to avoid "*** Initial Branch Revision ***" log message.
 * 	[90/03/10  12:15:26  gm]
 * 
 * Revision 1.4  90/02/23  00:43:48  devrcs
 * 	Added code to handle sandboxes with symlinks to targets.
 * 	Added support for shared branches/sandboxes.
 * 	[90/02/12  16:24:35  gm]
 * 
 * Revision 1.3  90/01/18  08:49:57  gm
 * 	Added code to make sure that -nowrite is enforced.
 * 	[90/01/07            gm]
 * 
 * Revision 1.2  90/01/03  12:53:15  gm
 * 	Fixes for first snapshot.
 * 	[90/01/03  09:50:47  gm]
 * 
 * Revision 1.1  89/12/26  10:46:46  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 2.4  89/06/18  17:33:14  gm0w
 * 	Updated to use new diag routine and to always print filename
 * 	of command target.
 * 	[89/06/18            gm0w]
 * 
 * Revision 2.3  89/02/05  16:04:09  gm0w
 * 	Renamed latest_private_rcs_file to just rcs_file.
 * 	[89/02/04            gm0w]
 * 
 * Revision 2.2  89/01/29  13:10:26  gm0w
 * 	Created.
 * 	[89/01/29            gm0w]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: bco.c,v $ $Revision: 1.14.16.8 $ $Date: 1994/02/24 18:45:27 $";

#include <stdio.h>
#include <ode/interface.h>
#include <ode/odedefs.h>
#include <sys/param.h>
#include <ode/parse_rc_file.h>
#include <ode/sandboxes.h>
#include <ode/sci.h>
#include <ode/sci_client.h>
#include <ode/util.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ode/misc.h>

#define ALIAS_READ_OP             "-u" /* Alias to -read, used to ease 
					  conversion to ode2.3. This must
					  be removed in the future. */
UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { READ_OP,      1, OVERWRITE,  0, 0, "" },
  { ALIAS_READ_OP,      1, OVERWRITE,  0, 0, "" },
  { ANCESTOR_OP,      1, OVERWRITE,  1, 1, ARGS_OP},
  { REVISION_OP,      1, OVERWRITE,  1, 1, ARGS_OP},
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { PRINT_TO_SCREEN_OP,      1, OVERWRITE,  0, 0, "" },
  { UNDO_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

const char *progname = "bco";             /* program name */

/*
 * PROTOTYPES
 */
void
handle_switches (void);
int
length_of_branch ( char * );

int file_mode;

void
main ( int argc, char ** argv )
{
  struct rcfile contents;
  char * sb_base = NULL,
       * sb = NULL,
       * sbrc_file = NULL,
       * symbolic_name = NULL,
       * set = NULL,
       * submit_set = NULL,
       * file,
       * user = NULL,
       * revision;
  SCI_LIST file_set;
  SCI_LIST tmp_set;
  SCI_LIST not_files;
  SCI_ELEM sci_ptr;
  SCI_ELEM tmp_sci_ptr;
  int ct, length;
  char expanded_config [ MAXPATHLEN ];
  char full_revision_string [ MAXPATHLEN ];
  char src_dir [ MAXPATHLEN ];
  char lock_file [ MAXPATHLEN ];
  char *check_out_config;
  char *ptr = expanded_config;
  ERR_LOG log;
  int missing_revs;
  char holdline [MAXPATHLEN];
  char * default_set;
  struct stat statbuf;

  /* Initialize */
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;

  symbolic_name = set;
  sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set, &sbrc_file,
             file_mode, FALSE );

  /* Lookup "check_out_config" parameter from the backing tree. */
  handle_switches ();
  get_rc_value ( "check_out_config", &check_out_config, &contents, TRUE );
  get_rc_value ( "default_set", &default_set, &contents, TRUE );
  rci_expand_include ( &ptr, check_out_config); 
  concat (full_revision_string, sizeof (full_revision_string), 
	symbolic_name, ";", expanded_config, NULL);

  /* Build up file list of files to process. */
  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct )) != NULL; ct++ ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */ 

  /* Lock the sandbox. */
  concat (src_dir, sizeof(src_dir), sb_base, "/", sb, "/src", NULL);
  concat (lock_file, sizeof(lock_file), src_dir, "/", BCSLOCK, NULL);
  if ( ! lock_sb (src_dir, lock_file, getenv ("USER") ))
	exit (ERROR);

  if ( ui_is_set ( REVISION_OP ) ) {
    if ( ui_is_set ( ANCESTOR_OP ) ) {
      ui_print (VWARN, "Cannot use the '%s' option with the '%s' option\n", 
                       REVISION_OP, ANCESTOR_OP );
      exit(1);
    } /* if */ 
    if ( (!ui_is_set ( READ_OP )) && (!ui_is_set ( ALIAS_READ_OP )) ) {
      ui_print (VWARN, "Must specify '%s' option with the '%s' option\n", 
				READ_OP, REVISION_OP);
    } else {
      if (ui_is_set ( ALIAS_READ_OP ))
	  ui_print (VWARN, 
		"The -u option is being phased out.  In the future, use the -read option.\n");
      revision = ui_arg_value ( REVISION_OP, 1, 1 );
      sci_read_files ( file_set, revision, ui_is_set (PRINT_TO_SCREEN_OP));
    } /* if */
  } else if ( (ui_is_set ( READ_OP )) || (ui_is_set ( ALIAS_READ_OP )) ) {
    if (ui_is_set ( ALIAS_READ_OP ))
	ui_print (VWARN, "The -u option is being phased out.  In the future, use the -read option.\n");
    sci_read_files ( file_set, full_revision_string, 
		ui_is_set (PRINT_TO_SCREEN_OP));
  } else {
    if ( strcmp ( submit_set, symbolic_name ) == 0 ) {
      ui_print ( VWARN, "User's set cannot be the same as the submit set.\n" );
      ui_print ( VCONT, "User's set and submit set are both: %s\n",
                        submit_set );
      ui_print ( VCONT, "Aborting bco.\n" );
      exit(1);
    } /* if */

    if (ui_is_set ( UNDO_OP ) ) {
	/*  Undo the last executed 'bco' command. */
    	sci_lookup_user_rev_list ( file_set, symbolic_name, 
		&missing_revs );
	for (sci_ptr = sci_first ( file_set ) ;
		sci_ptr != NULL; sci_ptr = sci_next ( sci_ptr )) {
		fprintf (stderr, "Undoing file %s\n", sci_ptr->name);

		lstat (sci_ptr->name, &statbuf);
		if ((statbuf.st_mode & S_IFMT) == S_IFLNK) {
			ui_print (VALWAYS, 
			   "File %s is a symbolic link.  There is nothing on this file to undo.\n",
			   sci_ptr->name);
			/* File is a symbolic link, skip it. */
			continue;
		}
		if (sci_ptr->ver_user == NULL) {
			/* No user branch.  Remove regular files. */
			if ((statbuf.st_mode & S_IFMT) == S_IFREG) {
				ui_print (VALWAYS,
					"Read-only file %s is being removed from your sandbox.\n", sci_ptr->name);
				(void) unlink (sci_ptr->name);
			} else {
			  ui_print (VALWAYS, 
			   "File %s does not exist in your sandbox.\n",
                                            sci_ptr->name);
                          ui_print ( VCONT, "There is nothing on this file to undo.\n" );
                        }
		} else {
			length = length_of_branch (sci_ptr->ver_user);
			if (length == 1) {
				/* Outdate the branch and file. */
				if ((statbuf.st_mode & S_IFMT) == S_IFREG) {
				   begin_atomic ();
    				   sci_new_list ( &tmp_set );
      				   sci_add_to_list_as_is ( tmp_set, sci_ptr->name );
				   tmp_sci_ptr = sci_first (tmp_set);
				   tmp_sci_ptr->ver_user = 
					strdup (sci_ptr->ver_user);
				   sci_server_bcs_opts (tmp_set,
					FALSE, TRUE, symbolic_name,
					submit_set, FALSE, "", FALSE, "",
					FALSE, "");
				   src_ctl_set_remove ( sci_ptr );
				   ui_print (VALWAYS,
					"File %s is being outdated and removed.\n",
					sci_ptr->name);
				   (void) unlink(sci_ptr->name);
				   end_atomic();
				}
			} else if (length > 1) {
				/* Unlink the regular file and checkout
				   again Read-only. */
				if ((statbuf.st_mode & S_IFMT) == S_IFREG) {
				   begin_atomic ();
				   (void) unlink (sci_ptr->name);
    				   sci_new_list ( &tmp_set );
      				   sci_add_to_list_as_is ( tmp_set, sci_ptr->name );
				   tmp_sci_ptr = sci_first (tmp_set);
				   tmp_sci_ptr->ver_user = 
					strdup (sci_ptr->ver_user);
				   sci_read_files (tmp_set,
					full_revision_string, FALSE);
				   ui_print (VALWAYS, 
					"File %s has been replaced by the latest revision on your private branch.\n", sci_ptr->name);
					
				   end_atomic();
				}

			} else {
				/* Warning, should never get here. */
				ui_print (VWARN,
					"Cannot undo file %s\n", 
					sci_ptr->name);
			}

		}

	}

    } else {
       if (ui_is_set (PRINT_TO_SCREEN_OP)) {
		ui_print (VFATAL, 
			"You can only use the -p option when checking a file out read-only.\n");
		exit(1);
       }
       if ( ui_is_set ( ANCESTOR_OP ) ) {
         revision = ui_arg_value ( ANCESTOR_OP, 1, 1 );
       } else {
         revision = strdup (expanded_config);
       } /* if */
       sci_lookup_user_rev_list ( file_set, symbolic_name, &missing_revs );
       getenv_user ( &user );
       concat ( holdline, sizeof ( holdline ), ":: ", default_set, " ", user,
             NULL );
       if ( sci_check_out_client ( file_set, holdline, TRUE, default_set,
                                &log ) ) {
         sci_edit_files (file_set, symbolic_name, revision);
         sci_select_not_exists ( file_set, &not_files );
         sci_check_out_client ( not_files, holdline, FALSE, default_set,
                             &log );
         if ( sci_elem_cnt ( not_files ) != 0 ) {
           exit ( 1 );
         } /* if */
       } /* if */
    }
  } /* if */
  exit(0);
}

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

#ifdef notdef
cleanup ( p )
int p;
{
}
#endif

/* show invocation options */
void print_usage(void )
{
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS, "%s\t[%s [%s <revision>]] [%s <revision>]\n", progname, READ_OP, REVISION_OP, ANCESTOR_OP );
  ui_print ( VALWAYS, "\t[sandbox opts] [ODE opts] [<file>...]\n" );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s -undo\n", progname);
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}

int
length_of_branch ( char * revision )
{
  int a, b, c, d, dots;
  char *j;
  if (revision == NULL)
        return(0);

  for (j = revision, dots = 0; *j != '\0'; j++)
	if (*j == '.') dots++;

  if (dots != 3)
	return (0);

  sscanf (revision, "%d.%d.%d.%d", &a, &b, &c, &d);

  return(d);
}

