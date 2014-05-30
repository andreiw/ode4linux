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
 * $Log: bmerge.c,v $
 * Revision 1.10.15.13  1994/03/03  19:47:01  damon
 * 	CR 1083. Removed verify_merge_rev_list()
 * 	[1994/03/03  19:46:24  damon]
 *
 * Revision 1.10.15.12  1994/02/14  15:35:18  damon
 * 	CR 817. Use xlog featr so check in does not add log msg
 * 	[1994/02/14  15:35:07  damon]
 * 
 * Revision 1.10.15.11  1994/01/31  19:48:32  damon
 * 	CR 1000. Complain if no ancestor found
 * 	[1994/01/31  19:43:04  damon]
 * 
 * Revision 1.10.15.10  1994/01/18  22:35:42  marty
 * 	CR # 925 - Verify that revision with -common option exists.
 * 	[1994/01/18  22:35:18  marty]
 * 
 * Revision 1.10.15.9  1994/01/18  21:55:47  marty
 * 	CR # 925 - bmerge now complains if revision to merge is not found.
 * 	[1994/01/18  21:54:26  marty]
 * 
 * Revision 1.10.15.8  1993/12/16  20:35:40  damon
 * 	Merged with changes from 1.10.15.7
 * 	[1993/12/16  20:35:34  damon]
 * 
 * 	CR 918. Added test for no merge condition
 * 	[1993/12/16  20:34:45  damon]
 * 
 * Revision 1.10.15.7  1993/12/16  20:01:40  marty
 * 	CR # 724 - Add call to sci_copyright_init().
 * 	[1993/12/16  19:58:19  marty]
 * 
 * Revision 1.10.15.6  1993/12/16  16:16:35  damon
 * 	CR 918. Added sci_select_need_merge to reduce unnecessary merging
 * 	[1993/12/16  16:16:14  damon]
 * 
 * Revision 1.10.15.5  1993/12/06  22:05:23  marty
 * 	CR # 827 - Side effect for change in interface.
 * 	[1993/12/06  22:04:59  marty]
 * 
 * Revision 1.10.15.4  1993/11/30  16:58:38  damon
 * 	CR 773. Check for matching default and user set
 * 	[1993/11/30  16:58:30  damon]
 * 
 * Revision 1.10.15.3  1993/11/22  18:46:31  damon
 * 	CR 852. Separated looking up ancestry from determining ancestor
 * 	[1993/11/22  18:46:02  damon]
 * 
 * Revision 1.10.15.2  1993/11/18  17:39:35  damon
 * 	CR 817. Lookup new user revision before updating ancestry
 * 	[1993/11/18  17:39:24  damon]
 * 
 * Revision 1.10.15.1  1993/11/18  17:34:40  damon
 * 	CR 817. Do ci of file after merge
 * 	[1993/11/18  17:34:15  damon]
 * 
 * Revision 1.10.13.4  1993/11/10  15:40:17  root
 * 	CR 463. Added include of stdlib.h
 * 	[1993/11/10  15:12:45  root]
 * 
 * Revision 1.10.13.3  1993/11/03  21:54:53  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  21:54:44  damon]
 * 
 * Revision 1.10.13.2  1993/10/28  13:31:59  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:12  damon]
 * 
 * Revision 1.10.13.1  1993/10/07  18:18:56  damon
 * 	CR 728. Exit if problems during merge
 * 	[1993/10/07  18:10:43  damon]
 * 
 * Revision 1.10.11.1  1993/08/19  21:21:53  damon
 * 	CR 622. Added unistd.h
 * 	[1993/08/19  21:21:35  damon]
 * 
 * Revision 1.10.9.12  1993/06/10  19:31:08  damon
 * 	CR 575. Do not use .BCSconfig file
 * 	[1993/06/10  19:31:02  damon]
 * 
 * Revision 1.10.9.11  1993/05/27  18:47:10  marty
 * 	CR # 558 - Type cast for rios_aix
 * 	[1993/05/27  18:46:47  marty]
 * 
 * Revision 1.10.9.10  1993/05/24  18:24:35  marty
 * 	CR # 537 - bmerge now checks rw status of file merging.
 * 	[1993/05/24  18:24:17  marty]
 * 
 * Revision 1.10.9.9  1993/05/18  20:47:33  marty
 * 	CR # 420 - Don't unlink the lock file. leave it.
 * 	[1993/05/18  20:47:22  marty]
 * 
 * 	CR # 420 - bmerge now locks the sandbox.
 * 	[1993/05/18  19:58:31  marty]
 * 
 * Revision 1.10.9.8  1993/04/29  16:44:05  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:43:50  marty]
 * 
 * Revision 1.10.9.7  1993/04/26  19:52:29  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/26  19:36:09  damon]
 * 
 * Revision 1.10.9.6  1993/04/16  20:37:09  damon
 * 	CR 421. Updated usage message for 2.3
 * 	[1993/04/16  20:36:58  damon]
 * 
 * Revision 1.10.9.5  1993/04/15  17:26:30  marty
 * 	Add ode/interface.h
 * 	[1993/04/15  17:26:07  marty]
 * 
 * Revision 1.10.9.4  1993/03/17  19:45:45  damon
 * 	CR 196. Removed locking call
 * 	[1993/03/17  19:44:17  damon]
 * 
 * Revision 1.10.9.3  1993/02/25  16:11:23  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:09:54  marty]
 * 
 * Revision 1.10.9.2  1993/02/18  15:02:02  marty
 * 	Remove "rc_file" from sci_init call.
 * 	[1993/02/18  14:58:57  marty]
 * 
 * 	Remove argument "rc_file" from sci_init() call.
 * 	[1993/02/18  14:57:47  marty]
 * 
 * Revision 1.10.4.8  1992/12/18  17:46:47  damon
 * 	CR 370. Added -common functionality
 * 	[1992/12/18  17:46:01  damon]
 * 
 * Revision 1.10.4.7  1992/12/03  19:03:56  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:33:53  damon]
 * 
 * Revision 1.10.4.6  1992/11/06  19:40:09  damon
 * 	CR 296. Removed extra definitions
 * 	[1992/11/06  19:39:09  damon]
 * 
 * Revision 1.10.4.5  1992/09/24  18:57:53  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:16:17  gm]
 * 
 * Revision 1.10.4.4  1992/09/01  18:24:23  damon
 * 	CR 238. Converted to sci API
 * 	[1992/09/01  18:24:00  damon]
 * 
 * Revision 1.10.4.3  1992/08/06  23:33:26  damon
 * 	CR 238. Moved from bin/bcs
 * 	[1992/08/06  23:30:54  damon]
 * 
 * Revision 1.10.4.2  1992/06/04  23:22:16  damon
 * 	Synched with 2.1.1
 * 	[1992/06/04  23:15:13  damon]
 * 
 * Revision 1.10.2.2  1992/03/25  22:44:57  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  20:12:30  damon]
 * 
 * Revision 1.10  1991/12/05  20:40:03  devrcs
 * 	moved external function declarations to bcs.h
 * 	[91/07/23  11:10:00  ezf]
 * 
 * 	added print_revision() and stub print_usage()
 * 	[91/06/03  15:32:30  ezf]
 * 
 * 	Added support for odedefs.h
 * 	[91/05/28  13:52:03  damon]
 * 
 * 	Changed to work with odedefs.h
 * 	[91/04/29  14:58:03  damon]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  18:35:52  gm]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:25:00  randyb]
 * 
 * 	Added code to update the config file when we merge in new
 * 	changes from the same branch we were already started from.
 * 	[90/10/03  13:34:54  gm]
 * 
 * Revision 1.9  90/10/07  21:49:28  devrcs
 * 	Added warning when we called getancestor.
 * 	[90/09/27  12:22:26  gm]
 * 
 * Revision 1.8  90/07/17  12:33:42  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:29:01  gm]
 * 
 * Revision 1.7  90/07/06  00:42:53  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:28:39  gm]
 * 
 * Revision 1.6  90/06/22  21:54:03  devrcs
 * 	Added -nolock switch.
 * 	[90/06/14  13:02:08  gm]
 * 
 * Revision 1.5  90/05/24  23:11:20  devrcs
 * 	Added auto keyword to command loop.  Minor cleanup of branchmerge
 * 	subroutine.  Added code to disable auto when an actual merge takes
 * 	place.  Added code to check for proper ancestor.
 * 	[90/05/20  12:36:45  gm]
 * 
 * 	Call echo() instead of running echo.
 * 	[90/05/15            gm]
 * 
 * 	Added support for ancestor stored in new style config file.  Moved
 * 	create_branch to subrs module.
 * 	[90/05/10  15:04:40  gm]
 * 
 * 	Removed AFS unlog.  Removed -u switch.  Added -mrgf switch.
 * 	Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.4  90/04/14  00:52:28  devrcs
 * 	Added initialization for need_makepath.
 * 	Support for -xblog.
 * 	[90/03/06  19:56:09  gm]
 * 
 * 	Added code to extract log messages from target if branch.
 * 	[90/02/22  00:30:45  gm]
 * 
 * Revision 1.3  90/02/23  00:43:58  devrcs
 * 	Added code to handle sandboxes with symlinks to targets.
 * 	Added support for shared branches/sandboxes.
 * 	[90/02/12  16:35:04  gm]
 * 
 * Revision 1.2  90/01/02  19:59:07  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:47:07  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 2.7  89/07/05  14:46:18  gm0w
 * 	Check for -1 return value from rcsdiff3 endcmd.
 * 	[89/07/05            gm0w]
 * 
 * Revision 2.6  89/07/05  12:39:06  gm0w
 * 	Added additional -r<rev> option for specifying ancestor to use
 * 	for merge.  Note that the last -r<rev> option is always the
 * 	revision to merge against the branch and that the first -r<rev>
 * 	is the ancestor when two revisions are specified.
 * 	[89/07/05            gm0w]
 * 
 * Revision 2.5  89/06/18  17:33:34  gm0w
 * 	Updated to use new diag routine and to always print filename
 * 	of command target.
 * 	[89/06/18            gm0w]
 * 
 * Revision 2.4  89/02/20  09:37:14  gm0w
 * 	Fixed stat/chmod replacement for chmod +w to succeed when
 * 	working file is missing.
 * 	[89/02/20            gm0w]
 * 
 * Revision 2.3  89/02/05  16:05:03  gm0w
 * 	Added extract_log for reducing merge lossage.  Renamed
 * 	latest_private_rcs_file to just rcs_file.
 * 	[89/02/04            gm0w]
 * 
 * Revision 2.2  89/01/29  13:10:06  gm0w
 * 	Created.
 * 	[89/01/29            gm0w]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: bmerge.c,v $ $Revision: 1.10.15.13 $ $Date: 1994/03/03 19:47:01 $";

#include <sys/param.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/parse_rc_file.h>
#include <ode/sandboxes.h>
#include <ode/sci.h>
#include <ode/util.h>

#define STATIC static

UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { REVISION_OP, 1, OVERWRITE,  1, 1, ARGS_OP },
  { COMMON_OP, 1, OVERWRITE,  1, 1, ARGS_OP },
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

const char *progname = "bmerge";               /* program name */
char curdir [ MAXPATHLEN ];

int file_mode;
char co_buf [ MAXPATHLEN ];
char * submit_set = NULL;

/*
 * PROTOTYPES
 */
void
verify_ancestor_rev_list ( SCI_LIST, char *);
void
handle_switches (void);
void
handle_args( struct rcfile * contents, char * symbolic_name );
BOOLEAN
file_checked_in (char * file);

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
  char lock_file [ MAXPATHLEN ];
  char src_dir [ MAXPATHLEN ];

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  handle_switches ();
  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;
  rc_file = ui_arg_value ( RC_OP, 1, 1 );

  if ( (char *) getcwd ( curdir, sizeof(curdir) ) == NULL ) {
     ui_print ( VFATAL, "Could not get the current working directory.\n");
     exit(1);
  }
  symbolic_name = set;
  if (sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set, &sbrc_file,
             file_mode, FALSE ) != OK)
	exit(1);

  if (sci_copyright_init ( &contents, sb_base, sb) != OK) {
       exit(1);
  }

  if ( strcmp ( submit_set, symbolic_name ) == 0 ) {
    ui_print ( VWARN, "User's set cannot be the same as the submit set.\n" );
    ui_print ( VCONT, "User's set and submit set are both: %s\n",
                      submit_set );
    ui_print ( VCONT, "Aborting bmerge.\n" );
    exit(1);
  } /* if */

  /* Lock sandbox. */
  concat (src_dir, sizeof(src_dir), sb_base, "/", sb, "/src", NULL);
  concat (lock_file, sizeof(lock_file), src_dir, "/", BCSLOCK, NULL);
  if ( ! lock_sb (src_dir, lock_file, getenv ("USER")))
	exit (ERROR);

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
} /* end handle_switches */

void
handle_args( struct rcfile * contents, char * symbolic_name )
{
  SCI_LIST file_set;
  SCI_LIST merge_file_set;
  SCI_ELEM sci_ptr;
  char * file;
  int ct;
  int missing_revs;
  char * coc_str;
  char * co_str = co_buf;
  char * merge_rev;
  BOOLEAN files_ok;
  int count;
  int result;
  char log_msg [MAXPATHLEN];

  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct )) != NULL; ct++ ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */

  /* Verify that all files are "checked-in". */
  files_ok = TRUE;
  count = 0;
  for (sci_ptr = sci_first(file_set); sci_ptr != NULL; 
		sci_ptr = sci_next(sci_ptr)) {
	if (file_checked_in(sci_ptr->name) == FALSE) {
		ui_print (VWARN, "File %s not checked in.\n",
			sci_ptr->name);
		files_ok = FALSE;
		count ++;
	}

  }
  if (files_ok == FALSE) {
	if (count > 1)
		ui_print (VWARN, 
			"Please check-in all files and rerun bmerge.\n");
	else
		ui_print (VWARN, 
			"Please check-in the file and rerun bmerge.\n");
	exit(1);
  }

  if ( ui_is_set ( REVISION_OP ) ) {
    merge_rev = ui_arg_value ( REVISION_OP, 1, 1 );
  } else {
    get_rc_value ( "check_out_config", &coc_str, contents, (int) FALSE );
    co_buf [0] = '\0';
    rci_expand_include ( &co_str, coc_str );
    merge_rev = submit_set;
  } /* if */
  sci_lookup_leader_list ( file_set );
  sci_lookup_user_rev_list ( file_set, symbolic_name, &missing_revs );
  sci_lookup_merge_rev_list ( file_set, merge_rev, co_buf );
  sci_ancestry_list ( file_set );
  if ( ui_is_set ( COMMON_OP ) ) {
    sci_lookup_ancestor_rev_list ( file_set, ui_arg_value ( COMMON_OP, 1, 1 ),
                                   &missing_revs );
    verify_ancestor_rev_list ( file_set, ui_arg_value ( COMMON_OP, 1, 1 ));
  } else
    if ( sci_ancestor_list ( file_set ) != OK ) {
      ui_print ( VALWAYS, "Missing common ancestor for file(s):\n" );
      for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
             sci_ptr = sci_next ( sci_ptr ) ) {
        ui_print ( VALWAYS, "  %s\n", sci_ptr -> name );
      } /* for */
      exit(1);
    } /* if */
  /* if */
  sci_select_need_merge ( file_set, &merge_file_set );
  sci_ptr = sci_first(merge_file_set);
  if ( sci_ptr == NULL ) {
    ui_print ( VNORMAL, "No merges required.\n" );
    return;
  } /* if */
  result = sci_merge_list ( merge_file_set, TRUE );
  if ( result == ABORT ) {
    exit ( 1 );
  } /* if */
  if ( result == ERROR ) {
    exit ( 1 );
  } /* if */
  for ( sci_ptr = sci_first ( merge_file_set ); sci_ptr != NULL;
        sci_ptr = sci_next ( sci_ptr ) ) {
    concat ( log_msg, sizeof(log_msg), "Merged with changes from ",
                      sci_ptr -> ver_merge, NULL );
    if ( sci_has_log ( sci_ptr ) ) {
      result = sci_check_in_file ( sci_ptr, symbolic_name, NULL, FALSE, TRUE,
                                   symbolic_name );
    } else {
      result = sci_check_in_file ( sci_ptr, symbolic_name, log_msg, FALSE, TRUE,
                                   symbolic_name );
    } /* if */
    if ( result == ABORT ) {
      exit ( 1 );
    } else if ( result == ERROR ) {
      exit ( 1 );
    } /* if */
  } /* for */
  sci_lookup_user_rev_list ( merge_file_set, symbolic_name, &missing_revs );
  sci_ancestor_update_list ( merge_file_set );
} /* end handle_args */

/* show invocation options */
void print_usage(void)
{
  printf( "USAGE:\n" );
  printf( "%s [merge opts] [sandbox opts] [ODE opts] [file opts]\n",
          progname );
  printf ( "\tmerge options:\n" );
  printf ( "\t  [-r <revision> [-common <revision>]]\n" );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}

BOOLEAN
file_checked_in (char * file)
{
    char file_path[PATH_LEN];
    char sandboxdir[PATH_LEN];
    char current_directory[PATH_LEN];
    char * sb = NULL,
         * basedir = NULL,
         * sb_rcfile = NULL,
         * rc_file = NULL;

    if ( current_sb ( &sb, &basedir, &sb_rcfile, &rc_file ) != OK ) {
        ui_print ( VFATAL, "could not get current sandbox information.\n");
	exit(1);
    }

    strcpy (current_directory, curdir);
    concat (sandboxdir, sizeof(sandboxdir), basedir, "/", sb, "/src", NULL);
    concat (file_path, sizeof(file_path), sandboxdir, "/", file, NULL);

    if (access (file_path, F_OK) == 0) {
	if (access (file_path, W_OK) == 0)
        	return (FALSE);
	else
        	return (TRUE);
    } else
        return (TRUE);


}

void 
verify_ancestor_rev_list ( SCI_LIST file_set, char * ancestor_rev)
{
    SCI_ELEM sci_ptr;
    SCI_ELEM tmp_ptr;

    for (sci_ptr = sci_first (file_set); sci_ptr != NULL; ) {

	if (sci_ptr->ver_ancestor == NULL) {
		ui_print (VERROR,
			"File %s does not have revision '%s'.\n", sci_ptr->name, 
			ancestor_rev);
		ui_print (VCONT, "Cannot use this revision as a common ancestor.\n");
		tmp_ptr = sci_next (sci_ptr);
		sci_remove_from_list (file_set, sci_ptr);
		sci_ptr = tmp_ptr;
	} else
		sci_ptr = sci_next (sci_ptr);

    }

}
