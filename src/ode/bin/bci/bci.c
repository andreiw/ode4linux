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
 * $Log: bci.c,v $
 * Revision 1.14.15.6  1994/02/28  19:35:59  damon
 * 	CR 1066. Changed -xlog to -x in usage message
 * 	[1994/02/28  19:35:51  damon]
 *
 * Revision 1.14.15.5  1994/02/04  20:30:46  damon
 * 	CR 827. Added xlog checking to sci_check_in_list2()
 * 	[1994/02/04  20:29:19  damon]
 * 
 * Revision 1.14.15.4  1994/02/04  16:12:17  damon
 * 	CR 827. Added -r. -x now defaults to user branch
 * 	[1994/02/04  16:12:06  damon]
 * 
 * Revision 1.14.15.3  1993/12/16  20:01:36  marty
 * 	CR # 724 - Add call to sci_copyright_init().
 * 	[1993/12/16  20:00:46  marty]
 * 
 * Revision 1.14.15.2  1993/12/06  21:54:37  marty
 * 	Merged with changes from 1.14.15.1
 * 	[1993/12/06  21:54:28  marty]
 * 
 * 	CR # 827 - Add -xlog option.
 * 	[1993/12/06  21:53:32  marty]
 * 
 * Revision 1.14.15.1  1993/11/30  16:56:33  damon
 * 	CR 773. Check for matching default and user set
 * 	[1993/11/30  16:56:25  damon]
 * 
 * Revision 1.14.12.3  1993/11/10  15:40:14  root
 * 	CR 463. Added include of stdlib.h
 * 	[1993/11/10  15:10:31  root]
 * 
 * Revision 1.14.12.2  1993/11/03  18:01:03  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  18:00:47  damon]
 * 
 * Revision 1.14.12.1  1993/10/28  13:31:36  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:00  damon]
 * 
 * Revision 1.14.10.3  1993/09/16  17:19:04  damon
 * 	Added COPYRIGHT NOTICE handling
 * 	[1993/09/16  17:13:08  damon]
 * 
 * Revision 1.14.10.2  1993/09/13  21:49:06  root
 * 	CR # 650 - bci now gives error message when checking in files not
 * 	in the current set.
 * 	[1993/09/13  21:48:51  root]
 * 
 * Revision 1.14.10.1  1993/09/02  15:55:20  damon
 * 	CR 631. Enabled abort option in bci
 * 	[1993/09/02  15:54:49  damon]
 * 
 * Revision 1.14.6.19  1993/06/04  18:34:31  damon
 * 	CR 569. Fixed behaviour in src directory
 * 	[1993/06/04  18:34:25  damon]
 * 
 * Revision 1.14.6.18  1993/06/02  20:05:44  marty
 * 	CR # 564 - Use a consistent set of paths (from getcwd and src_path)
 * 	for determining the relative directory.
 * 	[1993/06/02  20:05:28  marty]
 * 
 * Revision 1.14.6.17  1993/05/27  18:36:52  marty
 * 	Get it working on rios_aix
 * 	[1993/05/27  18:36:07  marty]
 * 
 * Revision 1.14.6.16  1993/05/18  20:44:32  marty
 * 	CR # 420 - Don't unlink the lock file. leave it.
 * 	[1993/05/18  20:44:14  marty]
 * 
 * Revision 1.14.6.15  1993/05/18  19:26:04  marty
 * 	CR # 420 - Locking and unlocking of sandboxes is now done within the
 * 	bcs tools (not libraries).
 * 	[1993/05/18  19:25:50  marty]
 * 
 * Revision 1.14.6.14  1993/05/14  17:19:09  damon
 * 	CR 495. Check result of sci_lookup_leader_list
 * 	[1993/05/14  17:19:01  damon]
 * 
 * Revision 1.14.6.13  1993/04/29  16:28:50  marty
 * 	Prototypes for print_usage(). CR # 463
 * 	[1993/04/29  16:28:36  marty]
 * 
 * Revision 1.14.6.12  1993/04/26  19:27:25  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/26  19:27:17  damon]
 * 
 * Revision 1.14.6.11  1993/04/26  17:38:21  marty
 * 	Fixed up usage output a bit.
 * 	[1993/04/26  17:38:03  marty]
 * 
 * Revision 1.14.6.10  1993/04/21  21:53:43  marty
 * 	Cleanup references to uninitialized variables.
 * 	[1993/04/21  21:53:24  marty]
 * 
 * Revision 1.14.6.9  1993/04/16  19:49:42  damon
 * 	CR 460. Added -changed and -saved
 * 	[1993/04/16  19:49:24  damon]
 * 
 * Revision 1.14.6.8  1993/04/16  19:03:44  damon
 * 	CR 422. Updated usage message
 * 	[1993/04/16  19:03:24  damon]
 * 
 * Revision 1.14.6.7  1993/04/15  17:10:20  marty
 * 	Added include of "ode/interface.h" and unistd.h".
 * 	[1993/04/15  17:10:03  marty]
 * 
 * Revision 1.14.6.6  1993/03/31  22:20:11  marty
 * 	Removed unneeded fprintf() calls.
 * 	[1993/03/31  22:19:56  marty]
 * 
 * Revision 1.14.6.5  1993/03/11  20:06:15  marty
 * 	OT# 441.  Check to make sure that files are in the sandbox
 * 	before trying to check them in.
 * 	[1993/03/11  20:06:00  marty]
 * 
 * Revision 1.14.6.4  1993/02/25  16:02:44  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:02:12  marty]
 * 
 * Revision 1.14.6.3  1993/02/03  19:56:06  damon
 * 	CR 417. Adjusted sci_init call
 * 	[1993/02/03  19:51:14  damon]
 * 
 * Revision 1.14.6.2  1993/01/13  16:42:56  damon
 * 	CR 382 removed S_ISREG stuff, removed cruft
 * 	[1993/01/05  20:09:16  damon]
 * 
 * Revision 1.14.4.14  1993/01/08  18:42:34  marty
 * 	Return '0' exit status.
 * 	[1993/01/08  18:40:23  marty]
 * 
 * Revision 1.14.4.13  1992/12/15  21:29:26  damon
 * 	CR 362. bci -m works without -auto
 * 	[1992/12/15  21:28:56  damon]
 * 
 * Revision 1.14.4.12  1992/12/03  19:03:31  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:33:32  damon]
 * 
 * Revision 1.14.4.11  1992/11/06  19:05:43  damon
 * 	CR 296. Removed extra defines
 * 	[1992/11/06  19:05:26  damon]
 * 
 * Revision 1.14.4.10  1992/11/05  20:13:53  damon
 * 	CR 296. Removed LOCK_OP
 * 	[1992/11/05  20:13:37  damon]
 * 
 * Revision 1.14.4.9  1992/11/05  16:51:38  damon
 * 	CR 315. Updated usage message.
 * 	[1992/11/05  16:51:19  damon]
 * 
 * Revision 1.14.4.8  1992/10/29  19:43:23  damon
 * 	CR 291. Fixed defuncting problem.
 * 	[1992/10/29  19:42:03  damon]
 * 
 * Revision 1.14.4.7  1992/10/27  20:12:02  damon
 * 	CR 294. Fixed formatting problem
 * 	[1992/10/27  20:11:42  damon]
 * 
 * Revision 1.14.4.6  1992/10/12  20:58:31  damon
 * 	CR 238. Converted to sci_rcs
 * 	[1992/10/12  20:57:19  damon]
 * 
 * Revision 1.14.4.5  1992/09/22  18:59:29  marty
 * 	Some changes toward the new source control API.
 * 	[1992/09/22  18:59:11  marty]
 * 
 * Revision 1.14  1991/12/17  20:57:43  devrcs
 * 	bcreate now adds headers to new files
 * 	[1991/12/06  19:31:55  mckeen]
 * 
 * Revision 1.13  1991/12/05  20:39:36  devrcs
 * 	ensure that temp_working_file is readable before check-in
 * 	[1991/11/01  23:00:28  ezf]
 * 
 * 	eliminated potential infinite loop in search_for() when
 * 	reusing input line.  The checklogstate() and search_for()
 * 	parsing routines should really be simplified.
 * 	[91/10/29  15:49:22  ezf]
 * 
 * 	no longer fails if trailing whitespace is missing from comment leader
 * 	[91/10/04  16:27:41  ezf]
 * 
 * 	Fixed bugs in support for binary files.
 * 	[91/08/27  15:00:57  rec]
 * 
 * 	search_for() now calls getline() in order to rescan current line on
 * 	failures, default option if checklogstate() fails is "edit", default
 * 	if okmesg() fails in "log".
 * 	[91/07/18  15:20:37  ezf]
 * 
 * 	avoid possible infinite loop in checklogstate(),
 * 	changed creation mode for temporary log file to 644
 * 	[91/07/09  14:53:00  ezf]
 * 
 * 	fixed warning bug in copyrights_from_string(), copyrights_from_file() now
 * 	permits comments, increased length limit of copyright markers to MAXPATHLEN
 * 	[91/07/01  16:57:24  ezf]
 * 
 * 	cosmetic changes, improved readability
 * 	[91/06/28  16:36:27  ezf]
 * 
 * 	Fixed bug that occurred only during bsubmits + BCSSET
 * 	[91/06/04  09:56:06  damon]
 * 
 * 	added print_revision() and stub print_usage()
 * 	[91/06/03  15:04:52  ezf]
 * 
 * 	Copyright markers now come from rc file variable 'copyright_list' or
 * 	built in defaults.
 * 	[91/06/03  14:39:41  damon]
 * 
 * 	First version with new copyright marker check.
 * 	Now uses a copyright_list file instead of only
 * 	two internally defined markers.
 * 	[91/05/02  11:22:11  damon]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  18:35:15  gm]
 * 
 * 	Fixed problem with accepting man pages.
 * 	[91/01/08  09:20:24  damon]
 * 
 * 	Fixed bug related to @OSF_FREE_COPYRIGHT@
 * 	Fixed bug related to COPYRIGHT NOTICE
 * 	[91/01/07  13:09:56  damon]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:22:41  randyb]
 * 
 * 	Now checks for @OSF_FREE_COPYRIGHT@
 * 	Now checks for COPYRIGHT NOTICE
 * 	[90/12/10  20:35:09  damon]
 * 
 * 	Finished log checking changes for C source files.
 * 	[90/12/05  13:41:33  damon]
 * 
 * 	Added testing for @OSF_FREE_COPYRIGHT@
 * 	Added testing for COPYRIGHT NOTICE
 * 	to add some functionality for dealing with C code and more testing.
 * 	[90/12/05  12:15:05  damon]
 * 
 * Revision 1.11  90/10/07  21:48:54  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:01:23  gm]
 * 
 * Revision 1.10  90/09/13  13:02:48  devrcs
 * 	Insert defuncted files into config file
 * 	[90/08/01  16:13:59  jbd]
 * 
 * Revision 1.9  90/07/17  12:33:15  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:28:24  gm]
 * 
 * Revision 1.8  90/07/06  00:42:33  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:27:01  gm]
 * 
 * 	Changed diff subcommand to not change default action.
 * 	[90/06/27  12:49:24  gm]
 * 
 * Revision 1.7  90/06/29  14:35:36  devrcs
 * 	Changed "rcsdiff" invokation from run() to runcmd().
 * 	[90/06/20            gm]
 * 
 * Revision 1.6  90/06/22  21:53:46  devrcs
 * 	Added -nolock switch.
 * 	[90/06/14  13:01:07  gm]
 * 
 * Revision 1.5  90/05/24  23:10:59  devrcs
 * 	Changed force (-f) flag to always be on.  Added auto keyword to command
 * 	loop to turn auto on for remaining files.  Added logdiff keyword to run
 * 	diff into the log file.
 * 	[90/05/20  11:32:56  gm]
 * 
 * 	Call echo() instead of running echo.
 * 	[90/05/15            gm]
 * 
 * 	Moved save_log_message to subrs module.
 * 	[90/05/10  14:49:03  gm]
 * 
 * 	Removed AFS unlog.  Removed -rm, -oknolog, -rlog and -xhist{ory}
 * 	switches.  Added leader subcommand.  Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.4  90/04/14  00:52:13  devrcs
 * 	Added initialization for need_makepath.
 * 	Support for -xblog.
 * 	[90/03/06  19:56:02  gm]
 * 
 * Revision 1.3  90/02/23  00:43:45  devrcs
 * 	Added code to handle sandboxes with symlinks to targets.
 * 	[90/02/12  16:17:49  gm]
 * 
 * Revision 1.2  90/01/02  19:59:01  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:46:43  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Added okmesg() for checking details about the log message.
 * 	Also added support for extracting a log message from the
 * 	RCS file when it is not present in the working file.
 * 	[89/09/21  18:24:39  bww]
 * 
 * Revision 2.5  89/06/18  17:33:06  gm0w
 * 	Updated to use new diag routine and to always print filename
 * 	of command target.
 * 	[89/06/18            gm0w]
 * 
 * Revision 2.4  89/02/18  12:41:54  gm0w
 * 	Changed -oknolog to -nolog (-oknolog will remain for compatability
 * 	until the next major release of the tools).  The -nolog switch will
 * 	not attempt to extract a history/log message.  Changed code so that
 * 	HISTORY/$Log...$ state is checked before extracting instead of after.
 * 	Added code to confirm running diff before entering the editor.
 * 	[89/02/18            gm0w]
 * 
 * Revision 2.3  89/02/05  16:03:52  gm0w
 * 	Minor bugfixes to extleader.  Moved code which called
 * 	extract_whist into bci_get_action and added "xtract" action.
 * 	Renamed latest_private_rcs_file to just rcs_file.  Moved
 * 	extract_whist to new extract.c module.  Changed code to
 * 	always attempt to extract whist messages (-xhist is a noop).
 * 	Added code to check for leader prefix on marker lines.
 * 	Changed bci_new default to local.
 * 	[89/02/04            gm0w]
 * 
 * Revision 2.2  89/01/29  13:09:50  gm0w
 * 	Created.
 * 	[89/01/29            gm0w]
 * 
 * $EndLog$
 */

#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/sandboxes.h>
#include <ode/sci.h>
#include <ode/util.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *progname = "bci";		/* program name */
extern char setrev[];
extern char * src_path;

/* global variables */

char *group;			/* use group of files for args */
char *groupset;			/* use group of files from <set> for args */

char *sandbox;
char *basedir;
char *sb_rcfile;
char *usr_rcfile;
char *setname;

int file_mode; 
char curdirbuf[MAXPATHLEN];     /* buffer for curdir */
char sandboxdir[MAXPATHLEN];

/* structure declarations */

struct table {
    int maxa;                   /* max argc before realloc of argv */
    int argc;                   /* current argument count */
    char **argv;                /* arguments */
};

struct table currel;            /* current directory relative args */
struct table baserel;           /* base directory relative args */

UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { NOLOG_OP,     1, OVERWRITE,  0, 0, "" },
  { XLOG_OP, 	  1, OVERWRITE,  0, 0, ARGS_OP },
  { REVISION_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { FAST_OP,     1, OVERWRITE,  0, 0, "" },
  { MSG_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { DEFUNCT_OP,   1, OVERWRITE,  0, 0, "" },
  { ALL_OP,       1, OVERWRITE,  0, 0, "" },
  { SET_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,        1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

STATIC
BOOLEAN defunct;

/*
 * PROTOTYPES
 */
void
handle_switches (void);
BOOLEAN
file_exists (const char * , const char * );

void
main(int argc, char ** argv)
{
  struct rcfile contents;
  char * sb_base = NULL,
       * sb = NULL,
       * sbrc_file = NULL,
       * symbolic_name = NULL,
       * submit_set = NULL,
       * set = NULL,
       * file;
  SCI_LIST file_set;
  SCI_ELEM sci_ptr;
  int ct;
  char curdir [PATH_LEN];
  char src_dir [PATH_LEN];
  char lock_file [PATH_LEN];
  int missing_revs;
  char *xlog_rev;
  BOOLEAN xlog_op;

  /* Initialize */
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;

  if ( getcwd ( curdir, sizeof(curdir) ) == NULL )
	uquit ( ERROR, FALSE, "Could not get the current working directory.\n");

  handle_switches ();

  symbolic_name = set;
  if ( sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set,
                  &sbrc_file, file_mode, FALSE ) != OK ) {
    exit ( ERROR );
  } /* if */
  if (sci_copyright_init ( &contents, sb_base, sb) != OK) {
       exit( ERROR );
  }

  if ( strcmp ( submit_set, symbolic_name ) == 0 ) {
    ui_print ( VWARN, "User's set cannot be the same as the submit set.\n" );
    ui_print ( VCONT, "User's set and submit set are both: %s\n",
                      submit_set );
    ui_print ( VCONT, "Aborting bci.\n" );
    exit(1);
  } /* if */

  /* src_path is the source directory of the sandbox derived from sci_init() */
  strcpy (sandboxdir, src_path);

  /* Lock the sandbox. */
  concat (src_dir, sizeof(src_dir), sb_base, "/", sb, "/src", NULL);
  concat (lock_file, sizeof(lock_file), src_dir, "/", BCSLOCK, NULL);
  if ( ! lock_sb (src_dir, BCSLOCK, getenv ("USER")) )
	exit (ERROR);


  /* Build up file list of files to process. */
  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {

    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct++ )) != NULL; ) {
      if (file_exists (file, curdir) == TRUE)
      	sci_add_to_list ( file_set, file );
      else {
	ui_print (VWARN, "Could not find file %s in the current sandbox.\n",
		file);
      }
    }

  }
  if ( sci_lookup_leader_list ( file_set ) == ERROR ) {
    exit (-1);
  } /* if */
  if ( sci_lookup_user_rev_list 
		( file_set, symbolic_name, &missing_revs ) == ERROR)
	exit(1);
  if (missing_revs == TRUE) {
    ui_print (VFATAL, "The following files are not in the set %s.\n", symbolic_name);
    for ( sci_ptr = sci_first ( file_set); sci_ptr != NULL;
          sci_ptr = sci_next ( sci_ptr ) ) {
	if (sci_ptr->ver_user == NULL)
		ui_print (VNORMAL, "%s\n", sci_ptr->name);
    }
    exit(1);
  }
  if ( ui_is_set ( XLOG_OP ) ) {
	xlog_op = TRUE;
        if ( ui_is_set ( REVISION_OP ) ) {
	  xlog_rev = ui_arg_value ( REVISION_OP, 1, 1 );
        } else {
          xlog_rev = symbolic_name;
        } /* if */
  } else {
	xlog_op = FALSE;
	xlog_rev = NULL;
  }
  if ( ui_is_set ( MSG_OP ) && ui_is_auto () )
    sci_check_in_list2 ( file_set, symbolic_name, ui_arg_value ( MSG_OP, 1, 1 ),
                         ui_is_set ( DEFUNCT_OP ), xlog_op, xlog_rev );
  else {
    for ( sci_ptr = sci_first ( file_set); sci_ptr != NULL;
          sci_ptr = sci_next ( sci_ptr ) ) {
      if ( sci_check_in_file ( sci_ptr, symbolic_name,
                               ui_arg_value ( MSG_OP, 1, 1 ),
                               ui_is_set ( DEFUNCT_OP ), xlog_op, xlog_rev ) == ABORT ) {
        exit (0);
      } /* if */
    } /* for */
  } /* if */
  exit(0);
}

/*ARGSUSED*/
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

  defunct = FALSE;
  if (ui_is_set(DEFUNCT_OP)) {
    defunct = TRUE;
  }
}

/* show command line invocation options */
void print_usage(void)
{
  ui_print ( VALWAYS, "USAGE:\n");
  ui_print ( VALWAYS, "%s [%s <message>] [%s] [-x [ -r <revision>] ] [sandbox opts] [ODE opts] [file opts]\n", progname, MSG_OP, DEFUNCT_OP );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}

/* Check to see if the file exists in the users sandbox.  */
BOOLEAN
file_exists (const char * file, const char * curdir)
{
    char file_path[PATH_LEN];
    char current_directory[PATH_LEN];
    char * reldir = NULL;


	
    if ((file == NULL) || (*file == '\0'))
	return (FALSE);

    strcpy (current_directory, curdir);
    if ( strncmp(file, "/", 1) == 0 ||
         strlen ( sandboxdir ) == strlen ( current_directory ) ) {
      concat (file_path, sizeof(file_path), sandboxdir, "/", file, NULL);
    } else {
      reldir = current_directory + strlen ( sandboxdir ) + 1;
      concat (file_path, sizeof(file_path), sandboxdir, "/", reldir, 
              "/", file, NULL);
    }

    if (access (file_path, F_OK) == 0)
	return (TRUE);
    else
	return (FALSE);
}
