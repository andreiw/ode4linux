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
 * $Log: sadmin.c,v $
 * Revision 1.7.14.2  1994/03/03  20:32:02  damon
 * 	CR 1084. Restored file names to previous names
 * 	[1994/03/03  20:31:42  damon]
 *
 * Revision 1.7.14.1  1993/12/10  21:54:34  marty
 * 	CR # 840 - Create local files in sandbox "tmp" directory.
 * 	[1993/12/10  21:52:36  marty]
 * 
 * Revision 1.7.12.2  1993/11/04  21:22:16  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  21:22:01  damon]
 * 
 * Revision 1.7.12.1  1993/10/28  13:32:29  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:31  damon]
 * 
 * Revision 1.7.10.1  1993/09/13  20:44:19  root
 * 	CR # 659 - The type passed to getenv_user is really a character
 * 	pointer and not an array.
 * 	[1993/09/13  20:40:55  root]
 * 
 * Revision 1.7.8.8  1993/06/10  19:15:36  damon
 * 	CR 395. Fixed to copy hold file. Fixed to work in top dir
 * 	[1993/06/10  19:15:28  damon]
 * 
 * Revision 1.7.8.7  1993/05/28  15:48:34  marty
 * 	CR # 558 - Get it running on rios_aix.
 * 	[1993/05/28  15:48:19  marty]
 * 
 * Revision 1.7.8.6  1993/05/25  15:08:56  damon
 * 	CR 395. Added HOLD_FILE_23
 * 	[1993/05/25  14:57:49  damon]
 * 
 * Revision 1.7.8.5  1993/05/21  18:07:21  damon
 * 	CR 395. Keep a lock on the file to be editted while editting
 * 	[1993/05/21  18:06:38  damon]
 * 
 * Revision 1.7.8.4  1993/03/31  15:18:43  marty
 * 	Added cleanup() routine.
 * 	[1993/03/31  15:16:11  marty]
 * 
 * 	Cleanup.
 * 	[1993/03/31  15:13:03  marty]
 * 
 * Revision 1.7.8.3  1993/03/30  19:16:21  marty
 * 	Remove all options except -copy and -edit
 * 	[1993/03/30  19:10:52  marty]
 * 
 * 	Remove all options expect -copy and -edit.
 * 
 * Revision 1.7.8.2  1993/01/14  16:57:42  damon
 * 	CR 395. Updated sadmin to use more sci_rcs.c functions
 * 	CR 392. Moved sadmin to its own dir
 * 	[1993/01/14  16:57:14  damon]
 * 	 *
 * 	Revision 1.7.6.7  1992/12/10  20:38:51  damon
 * 	CR 355. Changed getenv_user call to getenv_user2
 * 	[1992/12/10  20:38:34  damon]
 * 
 * Revision 1.7.6.6  1992/12/03  19:04:21  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:34:17  damon]
 * 
 * Revision 1.7.6.5  1992/10/28  19:43:07  damon
 * 	CR 317. Converted to odexm
 * 	[1992/10/28  19:42:17  damon]
 * 
 * Revision 1.7.6.4  1992/10/16  18:08:38  damon
 * 	CR 288. Fixed call to ui_init
 * 	[1992/10/16  18:08:21  damon]
 * 
 * Revision 1.7.6.3  1992/09/24  18:58:20  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:16:50  gm]
 * 
 * Revision 1.7.6.2  1992/06/11  19:46:54  damon
 * 	Synched with 2.1.1
 * 	[1992/06/11  19:44:22  damon]
 * 
 * Revision 1.7.2.3  1992/04/13  18:33:44  mhickey
 * 	Removed local definition of print_revision to allow
 * 	ui_print_revision to print the correct revision info.
 * 	[1992/04/13  18:32:28  mhickey]
 * 
 * Revision 1.7.2.2  1992/04/09  17:45:31  mhickey
 * 	*** empty log message ***
 * 	[1992/04/09  17:44:51  mhickey]
 * 
 * 	Fixed call to set_environ (was passing bad parameter list).
 * 	Defect 2507 (DCE OT number).
 * 	[1992/04/09  15:58:30  mhickey]
 * 
 * Revision 1.7  1991/12/05  20:40:54  devrcs
 * 	Fixed date format problem
 * 	[1991/11/13  14:57:30  damon]
 * 
 * 	Changed COPYHOLD to COPYFILE
 * 	[1991/10/30  21:48:54  damon]
 * 
 * 	Added COPYHOLD mechanism
 * 	[91/10/28  14:39:32  damon]
 * 
 * 	only attempts to remove tracking file if it exists
 * 	[91/09/13  14:57:35  ezf]
 * 
 * 	Changed AMAX_ARGS to MAX_ARGS
 * 	[91/08/01  13:48:55  damon]
 * 
 * 	updated print_usage() and print_revision()
 * 	[91/06/11  12:48:54  ezf]
 * 
 * 	Implemented Tools II including interface.
 * 	[91/01/08  14:50:07  randyb]
 * 
 * 	Upgrade to Tools II and new user interface
 * 	[91/01/03  16:49:28  randyb]
 * 
 * 	Corrected arguments for get_rc_value and build_base_dir
 * 	[90/12/10  16:06:41  randyb]
 * 
 * 	Added ability to determine backing tree by using the rc variable
 * 	build_list
 * 	[90/12/07  13:53:34  randyb]
 * 
 * 	Changed -b to -back for consistency.
 * 	Had sadmin remove temporary user files after use.
 * 	[90/12/05  15:24:40  randyb]
 * 
 * 	Major re-write to accomdate handling logs over the network.  Since the
 * 	primary purpose of sadmin is to work with these logs, this program had
 * 	much of its interface modified.
 * 	[90/11/29  16:40:24  randyb]
 * 
 * 	Reads project's build directory, default build, and default set for
 * 	  default build from rc files.
 * 	Changed -target to -b to match bsubmit.
 * 	Style updates; saber c lint
 * 	[90/11/14  09:56:32  randyb]
 * 
 * Revision 1.5  90/10/07  21:50:27  devrcs
 * 	Pre-osf1.0 changes
 * 
 * $EndLog$
*/
/******************************************************************************
**                          Open Software Foundation                         **
**                              Cambridge, MA                                **
**                              Randy Barbano                                **
**                               July 1990                                   **
*******************************************************************************
**
**  Description:
**    This program does system administration on the submission area.
**
**  Functions:
**    main (int, ** char) int
**      cmdline_syntax (* struct, * struct, * int) int
**        load_src_dir (* struct, * struct) int
**          print_base (* struct) int
**        check_edit_copy (* struct) int
**        check_rm () int
**      parcel_out_work (* struct, * struct, int) int
**        set_sfiles (* struct, * struct) int
**        setup_filelist (* struct, * struct, * struct) int
**          make_list_of_files (* struct, * struct, int) int
**        lock_files (* struct, * struct, int) int
**        copy_file (* struct, * struct) int
**          filecc (* char, * char, * struct) int
**        edit_file (* struct, * struct) int
**          filecc 95
**        remove_hold_files (* struct, * struct) int
**        list_hold_file (* struct, * struct, * struct) int
**        unlock_files (* struct, * struct, int) int
**    print_usage () int
**    print_revision () int
**
 */

#include <stdio.h>
#include "sadmin.h"
#include <string.h>
#include <unistd.h>
#include <ode/interface.h>
#include <ode/util.h>
#include <stdlib.h>

    char curdir [ PATH_LEN ] ;
    char *reldir;

    const char  * progname;                               /* name of program */
    char        * sb,                                        /* sandbox name */
                * sb_rcfile,                         /* sandbox rc file name */
                * rc_file;                                   /* user rc file */
    BOOLEAN       hold_lock = FALSE;             /* is the hold file lock on */

    UIINIT init [] = {                      /* initialize the user interface */
      { COPY_OP,   1, OVERWRITE, 1, 1, "hold log snap defunct" },
      { EDIT_OP,   1, OVERWRITE, 1, 1, "hold log snap defunct" },
      { BACK_OP,   1, OVERWRITE, 1, 1, ARGS_OP },
      { SB_OP,     1, OVERWRITE, 1, 1, ARGS_OP },
      { ARGS_OP,   UNLIMITED, OVERWRITE, 0, 0, "" }
    };

/*
 * PROTOTYPES
 */
void
cmdline_syntax ( SETINFO * setinfo, struct rcfile * contents,
                 BOOLEAN * do_list );
void
parcel_out_work ( SETINFO * setinfo, struct rcfile * contents, BOOLEAN );
void
check_edit_copy ( SETINFO * setinfo );
void
set_sfiles ( SETINFO * setinfo, SHARED_F * sfiles );
void
copy_file ( SETINFO * setinfo, SHARED_F * sfiles );
void
edit_file ( SETINFO * setinfo, SHARED_F * sfiles );
void
fill_in_sfiles ( SETINFO * setinfo, SHARED_F * sfiles );
void
filecc (  char * reading, char * writing, SETINFO * setinfo );

void
main ( int argc, char ** argv )

  	/* This function checks the command line arguments and makes
	   sure they are syntactically correct.  This is done using
	   the library function parse_cmd_line.  If this is correct,
	   the dependencies are checked.  Errors lead to usage messages.
	   If all is okay, the primary procedure is called. */
{
  SETINFO   * setinfo;                        /* points to set information */
  struct      rcfile   contents;          /* to hold contents of sb rcfile */
  BOOLEAN     listing;                                 /* do we do listing */
  char * sb_base = NULL,
       * set = NULL,
       * submit_set = NULL;

  rc_file = NULL;
  sb_rcfile = NULL;
  sb = NULL;
  if (argc > 0)
    progname = argv[0];
  else
    progname = "sadmin";
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

 /*
  * Initialize the source control system
  */
  sb = ui_arg_value ( SB_OP, 1, 1 );
  sb_rcfile = NULL;
  rc_file = ui_arg_value ( RC_OP, 1, 1 );

  if ( getcwd ( curdir, sizeof(curdir) ) == NULL )
      uquit ( ERROR, FALSE, "getcwd failed\n");

  if ( sci_init ( &contents, &sb, &sb_base, &set, &submit_set,
                  &sb_rcfile, 0, FALSE ) != OK )
    exit (1);

  reldir = &curdir [ strlen (sb_base) + strlen(sb) + 6 ];

  /* if */
  setinfo = ( SETINFO * ) malloc ( sizeof ( SETINFO ));
  cmdline_syntax ( setinfo, &contents, &listing );
  parcel_out_work ( setinfo, &contents, listing );
  exit( OK );
}                                                                    /* main */


void
cmdline_syntax ( SETINFO * setinfo, struct rcfile * contents,
                 BOOLEAN * do_list )

	/* This procedure checks for relationships between the
	   command line arguments.  It assumes the syntax is
	   already correct.  Most of the functions it calls
	   will use uquit to exit if there is an error. */
{

  if ( ui_is_set ( COPY_OP ) || ui_is_set ( EDIT_OP ))
    check_edit_copy ( setinfo );
}                                                          /* cmdline syntax */



void
print_base ( SETINFO * setinfo )

	/* This procedure prints the fields in setinfo that are
	   filled in. */
{
  ui_print ( VDETAIL, "build name is: %s.\n", setinfo->b_name );
  ui_print ( VDEBUG, "build path is: %s.\n", setinfo->b_base );
  ui_print ( VCONT, "build src directory is: %s.\n", setinfo->b_src_dir );
  ui_print ( VCONT, "default set for build is: %s.\n", setinfo->b_set );
  ui_print ( VCONT, "build sandboxrc file is: %s.\n", setinfo->b_rcfile );
}                                                              /* print base */




void
check_edit_copy ( SETINFO * setinfo )

	/* This procedure checks to make sure the edit and copy
	   options are set correctly. */
{
    char      * arg;                                /* holds option argument */

  if ( ui_is_set ( COPY_OP ) && ui_is_set ( EDIT_OP ))
    uquit ( ERROR, TRUE, "\t%s and %s options cannot be used together.\n",
      	 		    EDIT_OP, COPY_OP );
 
  if ( ui_is_set ( EDIT_OP ))
    arg = ui_arg_value ( EDIT_OP, 1, 1 );
  else
    arg = ui_arg_value ( COPY_OP, 1, 1 );

  if ( streq ( arg, HOLD_OPT ))
    setinfo->co_mode = EDITHOLD;

  else if ( streq ( arg, LOG_OPT ))
    setinfo->co_mode = EDITLOG;

  else if ( streq ( arg, SNAP_OPT ))
    setinfo->co_mode = EDITSNAP;

  else
    setinfo->co_mode = EDITDEF;

  if ( ui_is_set ( COPY_OP )) {
    if ( ui_entry_cnt ( ARGS_OP ) != 1 )
      uquit ( ERROR, TRUE, "\t%s option must have one target file.\n", COPY_OP);
  } /* if */
}                                                         /* check edit copy */



void
parcel_out_work ( SETINFO * setinfo, struct rcfile * contents, BOOLEAN listing )

	/* This procedure determines which steps need to be done
	   and then calls the routines to do them. */
{
    SHARED_F    sfiles;                                  /* the shared files */

  set_sfiles ( setinfo, &sfiles );

  if ( ui_is_set ( COPY_OP ))
    copy_file ( setinfo, &sfiles );

  else if ( ui_is_set ( EDIT_OP ))
    edit_file ( setinfo, &sfiles );

}                                                         /* parcel out work */


void
set_sfiles ( SETINFO * setinfo, SHARED_F * sfiles )

	/* This procedure gets the date, time, and user to set
	   the leader information. */
{
    char * user;

    getenv_user ( &user );
    strcpy (setinfo->user, user);
  
  fill_in_sfiles ( setinfo, sfiles );
}                                                              /* set sfiles */




void
copy_file ( SETINFO * setinfo, SHARED_F * sfiles )

	/* This procecure sets up for copying one of the four logs. */
{
    char        filename [ NAME_LEN ];               /* name of file to read */
  char temp [ NAME_LEN ];
  int status;
  OXM_CNXTN monitor;
  int i;
  ERR_LOG log;
  const char *av [16];
  char file[PATH_LEN];
  int monitor_num;

  monitor_num = 2;
  if ( setinfo->co_mode == EDITHOLD ) {
    strcpy ( filename, sfiles->holdfile );
    strcpy ( temp, sfiles->usr_hold );
    monitor_num = 0;
  }
  else if ( setinfo->co_mode == EDITLOG ) {
    strcpy ( filename, SUBLOG );
        strcpy ( temp, sfiles->usr_log );
  }
  else if ( setinfo->co_mode == EDITSNAP ) {
    strcpy ( filename, SNAPSHOT );
    strcpy ( temp, sfiles->usr_snap );
  }
  else if ( setinfo->co_mode == EDITDEF ) {
    strcpy ( filename, DEFUNCT );
    strcpy ( temp, sfiles->usr_defunct );
  }
  if ( ui_is_info ())
    ui_print ( VALWAYS, "would copy file %s to %s.\n", filename,
			 ui_entry_value ( ARGS_OP, 1 ));
  else {
    ui_print ( VDETAIL, "fetching file for copy: %s <-- %s\n", temp, filename );
    oxm_open ( &monitor, monitor_num );
    i = 0;
    av [i++] = "-t2";
    av [i++] = "2";
    av [i++] = COPYFILE;
    av [i++] = filename;
    av [i++] = temp;
    av [i++] = ui_ver_switch ();
    log = oxm_runcmd ( monitor, i, av, NULL );

    log = oxm_endcmd ( monitor, &status );  
    log = oxm_close ( monitor );
    switch ( status ) {
      case ERROR:
        uquit ( ERROR, FALSE,
                "\tcould not copy file, %s.\n", filename );

      case OK:
        break;

      case NO_OPT:
      default:
        uquit ( ERROR, FALSE, 
                "Syntax error %d in logsubmit(1).\n%s\n", status, NOTIFY );
    } /* switch */
    if ( *reldir == '\0' ) {
      strcpy ( file, ui_entry_value ( ARGS_OP, 1 ) );
    } else {
      concat (file, sizeof(file), reldir, "/", 
		ui_entry_value ( ARGS_OP, 1 ), NULL);
    } /* if */
    filecc (  temp, file, setinfo );
    if ( unlink ( temp ) != OK )
      ui_print ( VWARN, "could not remove local copy of file:\n  %s.\n",
                         temp );

  }
}                                                               /* copy file */


void
filecc (  char * reading, char * writing, SETINFO * setinfo )

	/* This procedure copies the reading file into the writing
	   file. */
{
    FILE      * read_f,                          /* ptr to file to read from */
              * write_f;                          /* ptr to file to write to */

  ui_print ( VDETAIL, "copying file %s to %s.\n", reading, writing );

  if (( read_f = fopen ( reading, READ )) == NULL ) {
#ifdef notdef
    unlock_hold_file ( setinfo );
#endif
    uquit ( ERROR, FALSE, "\tcould not open file, %s, for reading.\n", reading);
  } /* if */

  if (( write_f = fopen ( writing, WRITE )) == NULL ) {
#ifdef notdef
    unlock_hold_file ( setinfo );
#endif
    uquit ( ERROR, FALSE, "\tcould not open file, %s, for writing.\n", writing);
  } /* if */

  if ( ffilecopy ( read_f, write_f ) != OK ) {
#ifdef notdef
    unlock_hold_file ( setinfo );
#endif
    uquit ( ERROR, FALSE, 
    		"\tcould not copy file: %s into %s.\n", reading, writing );
  } /* if */

  fclose ( read_f );
  fclose ( write_f );
}                                                                  /* filecc */


void
edit_file ( SETINFO * setinfo, SHARED_F * sfiles )

	/* This procecure makes a copy of the file to edit; calls
	   the editor, then calls the network routines to have the
	   file copied back into place. */
{
    char        real [ PATH_LEN ],                   /* name of file to read */
                local [ PATH_LEN ];                    /* local copy of file */
  char temp [ PATH_LEN ];
  char tmpbuf[PATH_LEN];
  int         status;                    /* results of remote command call */
  OXM_CNXTN monitor;
  OXM_CNXTN monitor2;
  int monitor_num;
  const char * lock_str;

  int i;
  ERR_LOG log;
  const char *av [16];
  char buf[MAXPATHLEN];

  monitor_num = 2;
  lock_str = LOCKLOG;
  if ( setinfo->co_mode == EDITHOLD ) {
    strcpy ( real, sfiles->holdfile );
    strcpy ( temp, sfiles->usr_hold );
    concat ( tmpbuf, sizeof(tmpbuf), HOLD_FILE, NULL );
    strcpy (local, tmpfile_name (tmpbuf));
    monitor_num = 0;
    lock_str = LOCKHOLD;
  } /* if */

  else if ( setinfo->co_mode == EDITLOG ) {
    strcpy ( real, SUBLOG );
    strcpy ( temp, sfiles->usr_log );
    concat ( tmpbuf, sizeof(tmpbuf), SUBLOG, NULL );
    strcpy (local, tmpfile_name (tmpbuf));
  } /* else if */

  else if ( setinfo->co_mode == EDITSNAP ) {
    strcpy ( real, SNAPSHOT );
    strcpy ( temp, sfiles->usr_snap );
    concat ( tmpbuf, sizeof(tmpbuf), SNAPSHOT, NULL );
    strcpy (local, tmpfile_name (tmpbuf));
  } /* else if */

  else if ( setinfo->co_mode == EDITDEF ) {
    strcpy ( real, DEFUNCT );
    strcpy ( temp, sfiles->usr_defunct );
    concat ( tmpbuf, sizeof(tmpbuf), DEFUNCT, NULL );
    strcpy (local, tmpfile_name (tmpbuf));
  } /* else if */

  if ( access ( local, F_OK ) == OK ) {
#ifdef notdef
    if ( setinfo->co_mode == EDITHOLD )
      unlock_hold_file ( setinfo );
    else
      unlock_log_files ( setinfo );
#endif

    uquit ( ERROR, FALSE, 
	 "\tlocal copy of file, %s, exists;\t\nwon't overwrite it.\n", local );
  } /* if */

  if ( ui_is_info ()) {
    ui_print ( VALWAYS, "would copy file %s\n     to %s.\n", real, local );
    ui_print ( VALWAYS, "would edit file %s.\n", local );
    ui_print ( VALWAYS, "would copy file %s\n     back to %s.\n", local, real );
    return;
  } /* if */

  ui_print ( VDETAIL, "fetching file for edit: %s <-- %s\n", local, real );

  oxm_open ( &monitor2, monitor_num );
  i = 0;
  av [i++] = lock_str;
  av [i++] = ui_ver_switch ();
  av[i] = NULL;
  log = oxm_runcmd ( monitor2, i, av, NULL );
  oxm_gets ( monitor2, buf, sizeof(buf), &log );
  rm_newline ( buf );
  if ( strcmp ( buf, "locked") == 0 ) {
    log = oxm_endcmd ( monitor2, &status );
    log = oxm_close ( monitor2 );
    ui_print ( VNORMAL, "File is already locked for editing.\n" );
    exit ( 1 );
  } /* if */
  oxm_open ( &monitor, monitor_num );
  i = 0;
  av [i++] = "-t2";
  av [i++] = "2";
  av [i++] = COPYFILE;
  av [i++] = real;
  av [i++] = temp;
  av [i++] = ui_ver_switch ();
  av[i] = NULL;
  log = oxm_runcmd ( monitor, i, av, NULL );
  log = oxm_endcmd ( monitor, &status );
  log = oxm_close ( monitor );

  switch ( status ) {
    case ERROR:
#ifdef notdef
      if ( setinfo->co_mode == EDITHOLD )
        unlock_hold_file ( setinfo );
      else
        unlock_log_files ( setinfo );
#endif
      uquit ( ERROR, FALSE,
             "\tcould not copy file, %s,\t\n for editting.\n", real );

    case OK:
      break;

    case NO_OPT:
    default:
#ifdef notdef
      if ( setinfo->co_mode == EDITHOLD )
        unlock_hold_file ( setinfo );
      else
        unlock_log_files ( setinfo );
#endif

      uquit ( ERROR, FALSE,
                  "\tsyntax error %d in logsubmit(1).\n%s\n", status, NOTIFY );
  } /* switch */

  filecc (  temp, local, setinfo );
  if ( unlink ( temp ) != OK )
    ui_print ( VWARN, "could not remove local copy of file:\n  %s.\n",
                       temp );


  editor ( local, "Editing file:" );

  oxm_open ( &monitor, monitor_num );
  i = 0;
  av [i++] = "-t1";
  av [i++] = "1";
  av [i++] = ADMINCOPY;
  av [i++] = local;
  log = oxm_runcmd ( monitor, i, av, NULL );
  log = oxm_endcmd ( monitor, &status );
  log = oxm_close ( monitor );

  switch ( status ) {
    case ERROR:
#ifdef notdef
      if ( setinfo->co_mode == EDITHOLD )
	unlock_hold_file ( setinfo );
      else
	unlock_log_files ( setinfo );
#endif
      
      uquit ( ERROR, FALSE, 
	     "\tcould not copy edited file, %s,\t\n back to build.\n", local );

    case OK:
      if ( unlink ( local ) != OK )
	ui_print ( VWARN, "could not remove local copy of file:\n  %s.\n",
			   local );
      oxm_write ( monitor2, "\n", 1, &log );
      log = oxm_endcmd ( monitor2, &status );
      log = oxm_close ( monitor2 );
      break;

    case NO_OPT:
    default:
#ifdef notdef
      if ( setinfo->co_mode == EDITHOLD )
	unlock_hold_file ( setinfo );
      else
	unlock_log_files ( setinfo );
#endif      
      uquit ( ERROR, FALSE, 
      		  "\tsyntax error %d in logsubmit(1).\n%s\n", status, NOTIFY );
  } /* switch */
}                                                               /* edit file */



void
fill_in_sfiles ( SETINFO * setinfo, SHARED_F * sfiles )

        /* This procedure fills in all the fields for the shared
           files which will need to be accessed later. */
{
    char        file_path [ PATH_LEN ],   /* path and name to build snapshot */
                begin [ PATH_LEN ];                     /* beginning of path */

  concat ( begin, PATH_LEN, setinfo->ttime, ".", NULL);
  concat ( file_path, PATH_LEN, begin, TMP_LOG, NULL );

  if (( sfiles->usr_log = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, TMP_SNAP, NULL );

  if (( sfiles->usr_snap = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );


  concat ( file_path, PATH_LEN, begin, TMP_DEFUNCT, NULL );

  if (( sfiles->usr_defunct = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, TMP_HOLD, NULL );

  if (( sfiles->usr_hold = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  strcpy ( file_path, HOLD_FILE_23 );

  if (( sfiles->holdfile = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN,
           setinfo->l_src_dir, "/", setinfo->ttime, ".", setinfo->user, NULL );

  if (( sfiles->trackfile = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );


  concat ( file_path, PATH_LEN,
           setinfo->l_src_dir, "/", setinfo->ttime, ".", BCSSTEPS, NULL );

  if (( sfiles->trackbcsstep = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, ": ", setinfo->user, "; Date: ",
           setinfo->tdate, "; Time: ", setinfo->ttime, NULL );

  if (( sfiles->holdline = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

}                                                          /* fill in sfiles */


void
print_usage (void)

	/* This procedure prints the usages for sadmin. */

{
  printf ( "USAGE:\n" );
  printf ( "%s -copy hold | log | snap | defunct \n",
		progname );
  printf ( "%s -edit hold | log | snap | defunct [-back]\n", progname );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}                                                             /* print usage */

void
cleanup ( SETINFO * setinfo, BOOLEAN * msg )

	/* Dummy routine right now. */

{
}                                                                 /* cleanup */
