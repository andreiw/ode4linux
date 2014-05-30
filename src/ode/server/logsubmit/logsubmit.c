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
 * $Log: logsubmit.c,v $
 * Revision 1.3.9.1  1993/11/09  16:54:15  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:53:03  damon]
 *
 * Revision 1.3.6.13  1993/05/25  15:08:51  damon
 * 	CR 395. Added HOLD_FILE_23
 * 	[1993/05/25  14:57:47  damon]
 * 
 * Revision 1.3.6.12  1993/05/21  18:07:12  damon
 * 	CR 395. Restored LOCKHOLD and LOCKLOG functions
 * 	[1993/05/21  18:05:38  damon]
 * 
 * Revision 1.3.6.11  1993/05/13  15:01:04  damon
 * 	CR 524. Moved logsubmit to server dir
 * 	[1993/05/13  15:00:21  damon]
 * 
 * Revision 1.3.6.10  1993/04/29  21:27:01  marty
 * 	Prototyping
 * 	[1993/04/29  21:21:40  marty]
 * 
 * Revision 1.3.6.9  1993/04/14  15:12:38  damon
 * 	CR 457. Removed lock calls. No longer needed
 * 	[1993/04/14  15:11:40  damon]
 * 
 * Revision 1.3.6.8  1993/04/05  17:26:24  damon
 * 	CR 457. Replaced lock dirs with flock calls
 * 	[1993/04/05  17:04:17  damon]
 * 
 * Revision 1.3.6.7  1993/03/04  17:56:10  damon
 * 	CR 438. Was checking co locks with gmatch instead of submit locks
 * 	[1993/03/04  17:55:50  damon]
 * 
 * Revision 1.3.6.6  1993/03/03  21:39:35  damon
 * 	CR 438. Changed strcmp to gmatch for more powerful locking
 * 	[1993/03/03  21:39:10  damon]
 * 
 * Revision 1.3.6.5  1993/02/22  17:02:17  damon
 * 	CR 193. submit locks are prepended, co locks are appended
 * 	[1993/02/22  17:01:43  damon]
 * 
 * Revision 1.3.6.4  1993/02/19  17:28:30  damon
 * 	CR 193. Added strict file locking code
 * 	[1993/02/19  17:28:07  damon]
 * 
 * Revision 1.3.6.3  1993/02/12  23:11:55  damon
 * 	CR 136. Hold file checking now done by logsubmit
 * 	[1993/02/12  23:08:02  damon]
 * 
 * Revision 1.3.6.2  1993/02/03  18:46:54  damon
 * 	CR 253. Now use checklocksb to see if build is locked
 * 	[1993/02/03  18:37:09  damon]
 * 
 * Revision 1.3.2.5  1992/12/15  23:27:19  damon
 * 	CR 364. Fixed call to ui_init
 * 	[1992/12/15  23:27:06  damon]
 * 
 * Revision 1.3.2.4  1992/12/03  17:23:06  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:09:32  damon]
 * 
 * Revision 1.3.2.3  1992/09/24  19:03:12  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:20:38  gm]
 * 
 * Revision 1.3.2.2  1992/01/31  20:51:13  damon
 * 	Changed some VDEBUGs to VFATAL
 * 	[1992/01/31  20:50:43  damon]
 * 
 * Revision 1.3  1991/12/05  21:13:37  devrcs
 * 	Changed COPYHOLD to COPYFILE
 * 	[1991/11/07  14:21:53  damon]
 * 
 * 	check progname and call copy_hold() if invoked as "copyhold" command
 * 	[91/09/13  13:34:56  ezf]
 * 
 * 	Added copyhold function
 * 	[91/09/05  10:14:17  damon]
 * 
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:12:23  mckeen]
 * 
 * 	"-version" now prints single line of revision info
 * 	[91/07/17  13:42:31  ezf]
 * 
 * 	additional debugging
 * 	[91/05/14  14:13:16  ezf]
 * 
 * 	Now closes defunct file only if it was opened.
 * 	[91/01/24  11:43:40  damon]
 * 
 * 	Added changes to support RIOS and aix
 * 	[91/01/22  13:00:43  mckeen]
 * 
 * 	Changed sdm/std_defs.h to ode/odedefs.h
 * 	[91/01/11  16:12:29  randyb]
 * 
 * 	Upgrade to Tools II and new user interface
 * 	[91/01/03  16:50:09  randyb]
 * 
 * 	Added ability to determine backing tree by using the rc variable
 * 	build_list
 * 	[90/12/07  13:53:46  randyb]
 * 
 * 	Added deleting temporary log files.
 * 	[90/12/06  13:21:15  randyb]
 * 
 * 	This program runs on the server and updates the logs.
 * 	[90/11/29  16:43:49  randyb]
 * 
 * $EndLog$
 */
/******************************************************************************
**                          Open Software Foundation                         **
**                              Cambridge, MA                                **
**                              Randy Barbano                                **
**                              November 1990                                **
*******************************************************************************
**
**  Description:
**	These routines do all the work necessary to log submissions.
**
**  Functions:
**    main (int, ** char) int
**      cmdline_syntax (* char) int
**        check_file () int
**      set_lock (* char) int
**      unset_lock (* char) int
**      copy_log (* char) int
**        filename (* char) * char
**        filecp (* char, * char, * char) int
**      copy_admin (* char) int
**        filecp 26
**      add_to_hold_file (* char) int
**        filename 22
**        filecp 26
**        unset_lock 17
**      update_logs (* char) int
**        filename 22
**        update_snapshot (* char, * char, * char, * char, int) int
**          sort_snap (* struct, * struct, * struct, * struct) int
**        update_defunct (* char, * char, * char) int
**          sort_defunct (* struct, * struct, * struct) int
**        update_submit_log (* char, * char, * char) int
**          filecp 26
**        unset_lock 17
**      cleanup_hold (* char) int
**        set_lock 14
**        delete_from_hold_file (* char) int
**        unset_lock 17
**    print_usage () int
 */

#include <ode/interface.h>
#include <ode/lockcmds.h>
#include <ode/odedefs.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define  WAITING      1                  /* return value for legal waiting */
#define  NO_OPT       2             /* return value for doing no operation */
#define  HELD         3     /* return value indicating that files are held */
#define  MAX_ARGS     1
#define  ONEWRITE     0600		/* mode for lock directories */

#define  LOCAL_SNAP   "LOCAL_SNAP"         /* name of temp, local snapshot */
#define  LOCAL_DEF    "LOCAL_DEF"      /* name of temp, local defunct file */
#define  LOCAL_HOLD   "LOCAL_HOLD"        /* name of temp, local hold file */
#define  LOCAL_LOG    "LOCAL_LOG"          /* name of temp, local log file */

    const char 	* progname;  			  /* name of program running */

    UIINIT init [] = {                      /* initialize the user interface */
      { ARGS_OP, 2, OVERWRITE, 0, 0, "" }
    };

/*
 * PROTOTYPES
 */
int
cmdline_syntax ( const char * program );

void
main ( int argc, char ** argv )

  	/* This function checks the command line arguments and makes
	   sure they are syntactically correct.  This is done using
	   the library function parse_cmd_line.  If this is correct,
	   the dependencies are checked.  Errors lead to usage messages.
	   If all is okay, the primary procedure is called. */
{
    int         rvalue;                                      /* return value */

  progname = argv[0];
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  /* use program name to determine operation */
  if (( rvalue = cmdline_syntax ( argv[0] )) == OK ) {
    if ( streq ( argv[0], COPYFILE ))
      rvalue = copy_hold ( ui_entry_value ( ARGS_OP, 1), ui_entry_value ( ARGS_OP, 2 ));
    else if ( streq ( argv[0], CHECKLOCKSB ))
      rvalue = check_lock ( LOCK_SB );
    else if ( streq ( argv[0], LOCKHOLD ))
      rvalue = lock_for_edit ( HOLD_FILE_23 );
    else if ( streq ( argv[0], LOCKLOG ))
      rvalue = lock_for_edit ( SUBLOG );
    else if ( streq ( argv[0], COPYLOG ))
      rvalue = copy_log ( ui_entry_value ( ARGS_OP, 1 ));
    else if ( streq ( argv[0], ADMINCOPY ))
      rvalue = copy_admin ( ui_entry_value ( ARGS_OP, 1 ));
    else if ( streq ( argv[0], UPDATELOGS ))
      rvalue = update_logs ( ui_entry_value ( ARGS_OP, 1 ));
  } /* if */

  exit ( rvalue );
}                                                                    /* main */



int
cmdline_syntax ( const char * program )

	/* This function checks to make sure the syntax of the arguments
	   is legal.  If it is, it returns OK, else NO_OPT. */
{
    int         rtval = OK;                                  /* return value */

  if ( streq ( program, LOCKHOLD ) || streq ( program, UNLOCKHOLD ) || 
       streq ( program, LOCKLOG )  || streq ( program, UNLOCKLOG ) ||
       streq ( program, CHECKLOCKSB )  || 
       streq ( program, LOCKSB )  || streq ( program, UNLOCKSB )) {
    if ( ui_is_set ( ARGS_OP )) {
      ui_print ( VFATAL, "no arguments can be given with %s.\n",
			  program );
      rtval = NO_OPT;
    } /* if */
  } else if (  streq ( program, UPDATELOGS ) ||
	    streq ( program, COPYLOG )    || streq ( program, ADMINCOPY )) {
    rtval = check_file ();

    ui_print ( VDEBUG, "Arg is: %s.\n", ui_entry_value ( ARGS_OP, 1 ));
  } else if ( streq ( program, COPYFILE )) {
    if ( ! ui_is_set ( ARGS_OP )) {
      ui_print ( VFATAL, "two arguments must be given with %s.\n",
                          program );
      rtval = NO_OPT;
    } /* if */

    ui_print ( VDEBUG, "Arg[0] is: %s.\n", ui_entry_value ( ARGS_OP, 1 ));
    ui_print ( VDEBUG, "Arg[1] is: %s.\n", ui_entry_value ( ARGS_OP, 2 ));
  } else if ( streq ( program, HOLDCLEANUP )) {
    if ( ! ui_is_set ( ARGS_OP )) {
      ui_print ( VFATAL, "one argument must be given with %s.\n",
			  program );
      rtval = NO_OPT;
/*
    } else if ( *(ui_entry_value ( ARGS_OP, 1 )) != COLON ) {
      ui_print ( VFATAL, "argument to %s must begin with %c.\n",
			  program, COLON );
      rtval = NO_OPT;
*/
    } /* if */

    ui_print ( VDEBUG, "Arg is: %s.\n", ui_entry_value ( ARGS_OP, 1 ));
  } else {                                                 /* non legal name */
    ui_print ( VFATAL, "program called with illegal name: %s.\n", program );
    rtval = NO_OPT;
  } /* if */

  return ( rtval );
}                                             		   /* cmdline syntax */

void print_usage (void) 

	/* This procedure prints the usages for locksubmit. */
	
{
  printf ( "USAGE:\n" );
  printf ( "%s\n", LOCKHOLD );
  printf ( "%s\n", UNLOCKHOLD );
  printf ( "%s\n", LOCKLOG );
  printf ( "%s\n", UNLOCKLOG );
  printf ( "-t1 1 %s HH:MM.%s | HH.MM.%s\n", COPYLOG, TMP_SNAP, TMP_DEFUNCT );
  printf ( "-t1 1 %s %s | %s | %s | %s\n", ADMINCOPY, SNAPSHOT, HOLD_FILE,
					   SUBLOG, DEFUNCT );
  printf ( "-t1 1 %s HH:MM.%s\n", APPENDHOLD, TMP_HOLD );
  printf ( "-t1 1 %s HH:MM.%s\n", UPDATELOGS, TMP_LOG );
  printf ( "-t2 2 %s <bsubmit.hold> HH:MM.%s\n", COPYFILE, TMP_HOLD );
  printf ( "%s :<holdline>\n", HOLDCLEANUP );
  printf ( "%s -usage | -version\n", progname );
}                                                             /* print usage */
