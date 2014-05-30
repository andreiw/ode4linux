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
 * $Log: workon.c,v $
 * Revision 1.11.13.3  1994/01/20  17:17:42  marty
 * 	CR # 983 - Set the environment variable BCSSET when detting into a sandbox.
 * 	[1994/01/20  17:16:36  marty]
 *
 * Revision 1.11.13.2  1993/11/22  22:37:17  damon
 * 	CR 773. Check to see if set and default_set are the same
 * 	[1993/11/22  22:37:08  damon]
 * 
 * Revision 1.11.13.1  1993/11/19  17:57:13  damon
 * 	CR 818. No longer requires -setdir to use correct set dir
 * 	[1993/11/19  17:56:53  damon]
 * 
 * Revision 1.11.11.5  1993/11/10  15:40:20  root
 * 	CR 463. Added include of stdlib.h
 * 	[1993/11/10  15:18:04  root]
 * 
 * Revision 1.11.11.4  1993/11/04  22:13:02  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  22:12:35  damon]
 * 
 * Revision 1.11.11.3  1993/10/28  13:32:42  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:39  damon]
 * 
 * Revision 1.11.11.2  1993/10/22  19:19:21  damon
 * 	CR 669. Complain if SHELL is not set
 * 	[1993/10/22  19:19:10  damon]
 * 
 * Revision 1.11.11.1  1993/10/06  22:46:45  damon
 * 	CR 700. Only set BCSTEMP if -set is used
 * 	[1993/10/06  22:44:21  damon]
 * 
 * Revision 1.11.9.3  1993/09/21  16:48:40  damon
 * 	CR 673. Read all sb.conf files in backing chain
 * 	[1993/09/21  16:48:06  damon]
 * 
 * Revision 1.11.9.2  1993/09/21  14:44:50  damon
 * 	CR 674. Call bld_conf_read based on ode_build_env
 * 	[1993/09/21  14:44:31  damon]
 * 
 * Revision 1.11.9.1  1993/09/01  16:41:15  damon
 * 	CR 637. Fixed workon usage message
 * 	[1993/09/01  16:40:57  damon]
 * 
 * Revision 1.11.7.15  1993/06/07  16:39:39  damon
 * 	CR 571. Restored proper set name check
 * 	[1993/06/07  16:39:27  damon]
 * 
 * Revision 1.11.7.14  1993/06/02  13:51:56  damon
 * 	CR 517. Cleaned up subprojects wrt sb.conf and sc.conf
 * 	[1993/06/02  13:50:44  damon]
 * 
 * Revision 1.11.7.13  1993/05/28  18:03:52  marty
 * 	CR # 558 - Get it running on rios_aix
 * 	[1993/05/28  18:03:41  marty]
 * 
 * Revision 1.11.7.12  1993/05/27  15:20:16  damon
 * 	CR 548. Change sb_conf_read to use sb_path instead of basedir+sb
 * 	[1993/05/27  15:20:03  damon]
 * 
 * Revision 1.11.7.11  1993/05/14  16:50:40  damon
 * 	CR 518. Changed prj_read and prj_write to take full sb path
 * 	[1993/05/14  16:49:36  damon]
 * 
 * Revision 1.11.7.10  1993/05/12  19:51:36  damon
 * 	CR 517. Added subprojects
 * 	[1993/05/12  19:48:41  damon]
 * 
 * Revision 1.11.7.9  1993/04/29  17:02:51  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  17:02:35  marty]
 * 
 * Revision 1.11.7.8  1993/04/15  18:39:33  marty
 * 	Add include files stdio.h and ode/interface.h
 * 	[1993/04/15  18:39:13  marty]
 * 
 * Revision 1.11.7.7  1993/04/09  14:33:39  damon
 * 	CR 417. Works with new split sandbox setup
 * 	[1993/04/09  14:33:31  damon]
 * 
 * Revision 1.11.7.6  1993/02/01  22:04:34  damon
 * 	CR 417. Fixed sb_conf calls. Added bld_conf_read call
 * 	[1993/02/01  22:04:07  damon]
 * 
 * Revision 1.11.7.5  1993/01/28  23:33:25  damon
 * 	CR 417. Separated build and source control
 * 	[1993/01/28  23:30:53  damon]
 * 
 * Revision 1.11.7.4  1993/01/27  18:41:15  damon
 * 	CR 417. Now gets basedir from .sandboxrc instead of shared
 * 	[1993/01/27  18:40:58  damon]
 * 
 * Revision 1.11.7.3  1993/01/27  18:19:05  damon
 * 	CR 417
 * 	Now used sb_config_std to determine if ODE source control is
 * 	being used. If it isn't, then nothing relating to sets is
 * 	done or allowed. Also, .BCSlock is not created or checked for
 * 	in this case.
 * 	[1993/01/27  18:16:39  damon]
 * 
 * Revision 1.11.7.2  1993/01/26  17:23:22  damon
 * 	CR 417. Removed need for src_control_init rc variable
 * 	[1993/01/26  17:23:02  damon]
 * 
 * Revision 1.11.5.11  1992/12/03  19:08:34  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:45  damon]
 * 
 * Revision 1.11.5.10  1992/10/30  14:23:26  damon
 * 	CR 187. Workon now calls lock_sb instead of bco
 * 	[1992/10/30  14:23:01  damon]
 * 
 * Revision 1.11.5.9  1992/10/14  20:48:16  damon
 * 	CR 288. Updated call to ui_init
 * 	[1992/10/14  20:45:32  damon]
 * 
 * Revision 1.11.5.8  1992/09/24  19:00:55  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:20:00  gm]
 * 
 * Revision 1.11.5.7  1992/07/26  17:30:22  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/17  20:56:29  gm]
 * 
 * Revision 1.11.5.6  1992/07/08  14:45:17  gm
 * 	Bug #216: Add SANDBOXRC environment variable support.
 * 	[1992/07/08  14:44:33  gm]
 * 
 * Revision 1.11.5.5  1992/06/19  17:38:30  marty
 * 	Set SANDBOX and BCSSET variables always.
 * 	[1992/06/19  17:36:39  marty]
 * 
 * Revision 1.11.5.4  1992/06/17  12:36:06  damon
 * 	Fixed bug 48. Removed -nosh option.
 * 	[1992/06/17  12:30:25  damon]
 * 
 * Revision 1.11.5.3  1992/06/16  22:12:22  damon
 * 	more 2.1.1 touch-up
 * 	[1992/06/16  22:06:37  damon]
 * 
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:02:31  damon]
 * 
 * Revision 1.11.2.2  1992/03/25  22:47:38  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  22:27:25  damon]
 * 
 * Revision 1.11  1991/12/05  20:55:02  devrcs
 * 	updated print_usage(), print_revision()
 * 	[91/06/11  11:53:10  ezf]
 * 
 * 	Changed sdm to ode; std_defs.h to odedefs.h
 * 	[91/01/11  10:37:26  randyb]
 * 
 * 	Tools II update
 * 	[90/12/27  16:13:15  randyb]
 * 
 * 	Corrected core dump error in call to build_base_dir
 * 	[90/12/10  13:18:52  randyb]
 * 
 * 	Added support for the line "src_control_init" in the rc file.
 * 	This change enables an installation to use the build part of ODE without
 * 	having to have source control installed.
 * 	[90/11/29  16:44:42  damon]
 * 
 * 	Style clean up; saber c lint.
 * 	Added environment variable WORKON which is incremented each time workon
 * 	is run.
 * 	[90/11/07  13:56:53  randyb]
 * 
 * 	Added a new variable, WORKON, which indicates the number of workon's
 * 	the user is nested in.  It does this by setting WORKON to 1 if it is
 * 	not already set.  If it is set, it increments the value.
 * 	[90/10/31  16:52:33  randyb]
 * 
 * Revision 1.9  90/10/07  21:53:18  devrcs
 * 	Pre-OSF/1 changes.
 * 
 * $EndLog$
 */
/******************************************************************************
**                          Open Software Foundation                         **
**                              Cambridge, MA                                **
**                              Randy Barbano                                **
**                               April 1990                                  **
*******************************************************************************
**
**  Description:
**	This program creates a "set" and/or puts the user into that set in
**	a sub shell.
**
**  Functions:
**    main (int, ** char) int
**      cmdline_syntax (** char, ** char, ** char, ** char, ** char,
**			** char, * int) int
**        legal_sandbox (** char, ** char, ** char, ** char) int
**        legal_list_options () int
**        legal_setdir (** char) int
**        legal_setname (** char, ** char, ** char, ** char, * char, * int) int
**        legal_undo_options () int
**      list_sets (* char, * char, * char) int
**      cd_to_src_path (struct) int
**        isdir (* char) int
**      undo_set (* char, * char, * char, * char) int
**        remove_setname (* char, * char, * char) int
**      write_set (* char, * char, * char, * char, ** char, struct) int
**        check_setdir (** char) int
**        run_bco (* char, * char, * char) int
**      check_setdir 84
**      set_workon_bcsset_vars (setname) int
**      create_sub_shell (* char) int
**    print_usage () int
**
 */

static const char * rcsid =
 "$RCSfile: workon.c,v $ $Revision: 1.11.13.3 $ $Date: 1994/01/20 17:17:42 $";

#include <ode/builddata.h>
#include <ode/interface.h>
#include <ode/misc.h>
#include <ode/odedefs.h>
#include <ode/parse_rc_file.h>
#include <ode/project.h>
#include <ode/sandboxes.h>
#include <ode/sets.h>
#include <ode/util.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <math.h>
#include <unistd.h>

#define  MAX_ARGS     5
#define  WORKON       "WORKON"          /* env variable with nested levels */
#define  NO_EDIT      "cat"                  /* just cat the file, no edit */
#define  ECHO         "/bin/echo"                          /* echo command */

    UIINIT init [] = {                      /* initialize the user interface */
      		{ SB_OP,     1, OVERWRITE, 1, 1, ARGS_OP },
      		{ SETDIR_OP, 1, OVERWRITE, 1, 1, ARGS_OP },
      		{ UNDO_OP,   1, OVERWRITE, 0, 0, "" },
      		{ LIST_OP,   1, OVERWRITE, 0, 0, "" },
      		{ SET_OP,   1, OVERWRITE, 1, 1, ARGS_OP },
    };

    const char * progname;
    char * basedir = NULL;                     /* holds path to sandbox */
    char * user_name;                             /* points to editor env */
    char * project;
    char * build;
    BOOLEAN ode_sc;
    BOOLEAN ode_build_env;
    struct rcfile sbconf_rc;

/*
 * PROTOTYPES
 */
void
cmdline_syntax ( char ** sb, char ** sbbase, char ** sb_rcfile,
                 char ** rc_file, char ** setname, char ** setdir,
                 BOOLEAN * in_setsfile );
void
list_sets ( char * sb, char * sbbase, char * rc_file );
void
cd_to_src_path ( char * , char * );
void
check_setdir ( char ** setdir );
void
undo_set ( char * sb, char * sbbase, char * rc_file, char * setname );
void
set_workon_bcsset_vars (char *);
void
create_sub_shell ( char * setdir );
void
legal_sandbox ( char ** sb, char ** sbbase, char ** sb_rcfile, char ** );
void
legal_list_options (void );
void
legal_setdir ( char ** setdir );
void
legal_setname ( char ** setname, char ** sb, char ** rcfile, char ** setdir,
                char * set_ptr, BOOLEAN * in_setfile );
void
legal_undo_options (void);
void
remove_setname ( char * sb, char * sbbase, char * setname );

void
main ( int argc, char ** argv )

  	/* This function checks the command line arguments and makes
	   sure they are syntactically correct.  This is done using
	   the library function interface.  If this is correct, the
	   dependencies are checked.  Errors lead to usage messages.
	   If all is okay, the primary procedure is called. */
{
    char      * sb,                                          /* sandbox name */
              * sb_rcfile,                           /* sandbox rc file name */
              * rc_file,                                     /* user rc file */
              * setname,                           /* holds full name of set */
              * startdir;                             /* holds set directory */
    struct      rcfile  rc_contents;    /* structure with contents of rcfile */
    BOOLEAN     insetsfile = FALSE;             /* is found in rc_files/sets */
    char sandbox_base [MAXPATHLEN];
    char * sub_project;
  struct rcfile contents;
  char buf [MAXPATHLEN];
  char buf2 [MAXPATHLEN];
  char * default_set;

  if (argc > 0)
      progname = argv[0];
  else
      progname = "workon";
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  setname = ui_arg_value ( SET_OP, 1, 1 );
  cmdline_syntax ( &sb, &basedir, &sb_rcfile, &rc_file, &setname,
		   &startdir, &insetsfile );

  if ( ui_is_set ( LIST_OP ))
    list_sets ( sb, basedir, rc_file );

  else {
    memset ( (char *)&rc_contents, 0, sizeof ( rc_contents ));
    concat ( sandbox_base, sizeof(sandbox_base), basedir, "/", sb, NULL );
    cd_to_src_path ( basedir, sb );
    check_setdir ( &startdir );
    prj_read ( sb_full_path ( basedir, sb ), startdir, &project, &sub_project );
    ui_print ( VNORMAL, "project: %s\n", project );
    sb_conf_read_chain ( &sbconf_rc, sb_full_path ( basedir, sb ) , project,
                         sub_project );
    sb_conf_std ( &sbconf_rc, &project, &build, &ode_sc, &ode_build_env );
    if ( ode_build_env ) {
      bld_conf_read ( sandbox_base, project, &rc_contents );
    } /* if */
    if ( !ode_sc && ui_is_set ( SET_OP ) ) {
      ui_print ( VWARN, "ODE source control disabled.\n" );
      ui_print ( VCONT, "Unable to use %s option.\n", SET_OP );
      exit ( ERROR );
    } /* if */
    
    if ( ui_is_set ( UNDO_OP ))
      undo_set ( sb, basedir, rc_file, setname );
    else {                                               /* do actual workon */
      if ( ode_sc )
        if ( ! insetsfile ) {
/*
 * FIXME!
 * This must go away when sc.conf dissappears from the backing build.
 */
  concat ( buf2, sizeof (buf2), build, "/rc_files/", project, NULL );
  concat ( buf, sizeof (buf), buf2, "/sc.conf", NULL );
  if ( init_rc_contents ( &contents, buf ) == ERROR ) {
    ui_print ( VFATAL, "Unable to read sc.conf file from backing build.\n" );
    exit(1);
  }
  get_rc_value ( "default_set", &default_set, &contents, FALSE );
  if ( strcmp ( default_set, setname ) == 0 ) {
    ui_print ( VWARN, "User's set cannot be the same as the submit set.\n" );
    ui_print ( VCONT, "User's set and submit set are both: %s\n",
                      default_set );
    ui_print ( VCONT, "Aborting workon.\n" );
    exit(1);
  } /* if */

          sets_write ( sb, basedir, setname, startdir );
        } /* if */
      /* if */
      set_workon_bcsset_vars (setname);
      create_sub_shell ( startdir );
    } /* else */
  } /* else */

  exit ( OK );
}                                                                    /* main */


void
cmdline_syntax ( char ** sb, char ** sbbase, char ** sb_rcfile,
                 char ** rc_file, char ** setname, char ** setdir,
                 BOOLEAN * in_setsfile )

	/* This procedure checks for relationships between the
	   command line arguments.  It assumes the syntax is
	   already correct.  Most of the functions it calls
	   will use uquit to exit if there is an error. */

{
    char      * env_ptr;                         /* holds environment values */

  legal_sandbox ( sb, sbbase, sb_rcfile, rc_file );

  
  if ( setenv ( SANDBOX, *sb, TRUE ) == ERROR )
      uquit ( ERROR, FALSE, "\tSANDBOX setenv failure.\n" );

  ui_print ( VDETAIL, "setting environment variable %s to: %s.\n", SANDBOX, 
               *sb );

  if ( setenv ( "SANDBOXRC", *rc_file, TRUE ) == ERROR )
      uquit ( ERROR, FALSE, "\tSANDBOXRC setenv failure.\n" );

  ui_print ( VDETAIL, "setting environment variable %s to: %s.\n", "SANDBOXRC", 
               *rc_file );
  if ( ui_is_set ( LIST_OP ))
    legal_list_options ();

  else {
    if ( sets_access ( *sbbase, *sb ) ) {
      env_ptr = getenv ( BCSSET );
      legal_setdir ( setdir );
      legal_setname ( setname, sb, rc_file, setdir, env_ptr, in_setsfile );
      if ( ui_is_set ( SET_OP ) ) { 
        if ( setenv ( BCSSET, *setname, TRUE ) == ERROR )
          uquit ( ERROR, FALSE, "\tBSCSET setenv failure.\n" );
      
        ui_print ( VDETAIL, "setting environment variable %s to: %s.\n",
    		 BCSSET, *setname );
      } /* if */
    } else {
      *setdir = strdup (".");
    } /* if */
    if ( ui_is_set ( UNDO_OP ))
      legal_undo_options ();
    /* if */
  } /* if */
}                                                          /* cmdline syntax */



void
legal_sandbox ( char ** sb, char ** sbbase, char ** sb_rcfile, char ** rc_file )

	/* This procedure checks to see if the sandbox entered is
	   legal.  It gets the path to the sandbox, the alternate
	   sb rcfile, and the user rcfile if they aren't entered. */
{
  *sb = ui_arg_value ( SB_OP, 1, 1 );
  *rc_file = ui_arg_value ( RC_OP, 1, 1 );
  *sb_rcfile = NULL;

  if ( current_sb ( sb, sbbase, sb_rcfile, rc_file ) == ERROR ) {
    if ( *sb == NULL )
      uquit ( ERROR, FALSE, "\tUnable to find default sandbox.\n" );
    else
      uquit ( ERROR, FALSE, "\tUnable to find base for sandbox %s.\n", *sb );
  } /* if */

  if ( ui_ver_level () >= VDEBUG ) {
    ui_print ( VDEBUG, "sandbox is: %s\n", *sb );
    ui_print ( VCONT, "path to sandbox is: %s\n", *sbbase );
    ui_print ( VCONT, "sandbox's local, rc file is: %s\n", *sb_rcfile );
    ui_print ( VCONT, "user's rc file is: %s\n", *rc_file );
  } /* if */
}                                                           /* legal sandbox */


void
legal_list_options (void )

	/* This procedure checks that the options passed with
	   the list flag are legal. */

{
  if ( ui_is_set ( SETDIR_OP ))
    ui_print ( VWARN, "-setdir option ignored; cannot be used with -list.\n" );
	    
  if ( ui_is_set ( SET_OP ))
    ui_print ( VWARN, "set name ignored; cannot be used with -list.\n" );
  
  if ( ui_is_set ( UNDO_OP ))
    uquit ( ERROR, TRUE, "\t-list option cannot be used with -undo.\n" );
}                                                      /* legal list options */



void
legal_setdir ( char ** setdir )

	/* This procedure checks to see if there is a setdir.
	   If not, it creates a default "." setdir but does not
	   set the is_set field as the user did not set it. */
{
  *setdir = ui_arg_value ( SETDIR_OP, 1, 1 );

  if ( *setdir == NULL )
    *setdir = strdup ( "." );

  ui_print ( VDEBUG, "set directory is: %s.\n", *setdir );
}                                                            /* legal setdir */



void
legal_setname ( char ** setname, char ** sb, char ** rcfile, char ** setdir,
                char * set_ptr, BOOLEAN * in_setfile )

	/* This procedure checks to see that the set name entered
	   is legal.  If it is, it puts the user's name in front of
	   it if it isn't already there and if the name doesn't
	   start with a capital letter.  A captial letter indicates
	   a shared set. */

{
    char        tmp_name [ NAME_LEN ],                        /* misc string */
                tsetname [ PATH_LEN ],                  /* temporary setname */
              * tsetdir = NULL;                        /* temp ptr to setdir */
    int         ct;                                          /* misc counter */

  if ( *setname == NULL ) {
    if ( current_set ( setname, &tsetdir, sb, rcfile ) == ERROR ) {
      if ( set_ptr != NULL )
        quit ( ERROR, FALSE, 
               "\tset, %s, from env var, %s, not found in sandbox, %s.\n",
               set_ptr, BCSSET, sb );
      else
        quit ( ERROR, FALSE, "\tno default set name; none entered.\n" );
    } /* if */
    if ( ! ui_is_set ( SETDIR_OP ))
      *setdir = tsetdir;
    *in_setfile = TRUE;
  } /* if */
  for ( ct = 0; (unsigned)ct < strlen ( *setname ); ct++ ) {
    if (( **setname + ct == PERIOD ) ||                  /* legal chars only */
        ( **setname + ct == SLASH ) ||
        ( **setname + ct == DASH ))
      uquit ( ERROR, FALSE, "\tsetname: %s, %s'%c' or '%c' or '%c'.\n",
              *setname, "has one of the following characters in it:\n      ",
	      PERIOD, DASH, SLASH );
  } /* for */

  if (( user_name = getenv ( "USER" )) == NULL )         /* insert user name */
    uquit ( ERROR, FALSE, "\tUSER not found in environment.\n" );

  concat ( tmp_name, NAME_LEN, user_name, "_", NULL );

		/* prepend user name if the setname does not start with
	   	   a capital letter and it isn't already there */

  if ((( **setname < 'A' ) || ( **setname > 'Z' )) &&
      ( strncmp ( tmp_name, *setname, strlen(tmp_name) ))) {
    concat ( tsetname,  NAME_LEN, tmp_name, *setname, NULL );
    *setname = strdup ( tsetname );
  } /* if */
  if ( ! *in_setfile ) {
    if ( current_set ( setname, &tsetdir, sb, rcfile ) != ERROR ) {
      if ( ! ui_is_set ( SETDIR_OP )) {
        *setdir = tsetdir;
      } /* if */
    } /* if */
  } /* if */
  ui_print ( VDEBUG, "name of set is: %s.\n", *setname );
}                                                           /* legal setname */



void
legal_undo_options (void)

	/* This procedure checks that the options passed with
	   the undo flag are legal. */

{
  if ( ui_is_set ( SETDIR_OP ))
    ui_print ( VWARN, "-setdir option ignored; cannot be used with -undo.\n" );
	    
}                                                      /* legal undo options */


void
list_sets ( char * sb, char * sbbase, char * rc_file )

	/* This function lists the sets, including the current
	   default one. */
{
    FILE      * ptr_file;                                  /* ptr to rc file */
    char        line [ STRING_LEN ],                    /* line from rc file */
                file [ PATH_LEN ],           /* holds set file path and name */
              * setname = NULL,                        /* holds full setname */
              * setdir = NULL,                        /* dummy set directory */
              * line_ptr,                                     /* misc string */
              * token;                                        /* misc string */

  if ( current_set ( &setname, &setdir, &sb, &rc_file ) == OK )
    ui_print ( VALWAYS, "Current set for sandbox %s %s is\n\tset: %s.\n",
               sb, "(environment variable or default)", setname );
  else
    ui_print ( VALWAYS, "No current default set for sandbox: %s.\n", sb );

  ui_print ( VCONT,
	"Existing sets and default set directories for sandbox %s:\n", sb );
  concat ( file, PATH_LEN, sbbase, "/", sb, "/", SET_RC, NULL );

  if (( ptr_file = fopen ( file, READ )) == NULL )
    uquit ( ERROR, FALSE, "\tcannot open set rcfile %s.\n", file );

  while (( line_ptr = fgets ( line, STRING_LEN, ptr_file )) != NULL ) {
    token = (char *)nxtarg ( &line_ptr, WHITESPACE );

    if ( streq ( token, SET_KEY )) {
      token = (char *)nxtarg ( &line_ptr, WHITESPACE );
      ui_print ( VCONT, "  set  %s;", token );
      token = (char *)nxtarg ( &line_ptr, WHITESPACE );
      ui_print ( VALWAYS, "\t setdir  %s\n", token );
    } /* if */
  } /* while */

  fclose ( ptr_file );
}                                                               /* list sets */


void
cd_to_src_path ( char * basepath, char * sb )

	/* This procedure determines the source directory for
	   the user and then does a cd to it. */
{
    char        src_dir [PATH_LEN ],     /* points to string with source dir */
                src_dir_file [ PATH_LEN ];   /* string to add phoney file to */

  concat ( src_dir, sizeof ( src_dir ), basepath, "/", sb, "/src", NULL );
  if ( isdir ( src_dir ) == ERROR ) {
    concat ( src_dir_file, sizeof ( src_dir_file ), src_dir, "/.", NULL );

    if ( makepath ( src_dir_file, NULL, TRUE, TRUE ) == ERROR )
      uquit ( ERROR, FALSE, "\tcould not create path %s.\n", src_dir );
  } /* if */

  if ( chdir ( src_dir ) == ERROR ) 
    uquit ( ERROR, FALSE, "\tcould not change directory to %s.\n", src_dir );

  ui_print ( VNORMAL, "cd'ing to sandbox source directory: %s.\n", src_dir );
}                                                          /* cd to src path */

void
undo_set ( char * sb, char * sbbase, char * rc_file, char * setname )

	/* This procedure undoes a set after checking to see if
	   it is safe to do so.  It removes the set dir found
	   in .BCSpath- if there are no files in it, and then
	   removes the .BCS*setname files. */
{
    char        file [ NAME_LEN ],                      /* file to check for */
                reply [ NAME_LEN ],                           /* misc string */
              * setdir = NULL;                               /* place holder */
    BOOLEAN     goahead = FALSE;                             /* misc boolean */

  if ( current_set ( &setname, &setdir, &sb, &rc_file ) == ERROR )
    uquit ( ERROR, FALSE, "\tno set to undo.\n" );

  concat ( file, NAME_LEN, BCS_SET, setname, NULL );

  if ( access ( file, F_OK ) == OK )
    uquit ( ERROR, FALSE, "\tset %s has checked out files; cannot delete it.\n",
			setname );

  if ( ui_is_auto ())
    goahead = TRUE;

  else {
    ui_print ( VALWAYS, "Remove set %s? [y|<n>] ", setname );
    gets ( reply );

    if ( streq ( reply, YES ))
      goahead = TRUE;
  } /* else */

  if ( goahead ) {
    if ( ui_is_info ())
      ui_print ( VALWAYS, "Would remove set, %s, from sandbox: %s.\n",
			   setname, sb );

    else {
      remove_setname ( sb, sbbase, setname );
      ui_print ( VNORMAL, "NOTE:  you may still be in a sub shell.\n" );
    } /* else */
  } /* if */
}                                                                /* undo set */



void
remove_setname ( char * sb, char * sbbase, char * setname )

	/* This function removes the name of the set from the
	   sets rcfile. */
{
    FILE      * ptr_file,                                  /* ptr to rc file */
              * ptr_new;                               /* ptr to new rc file */
    char        line [ STRING_LEN ],                    /* line from rc file */
                line_copy [ STRING_LEN ],               /* line from rc file */
                newfile [ PATH_LEN ],                /* holds file to create */
                file [ PATH_LEN ],           /* holds set file path and name */
              * line_ptr,                          /* allows parsing of line */
              * token;                    /* holds each piece of parsed line */

  ui_print ( VNORMAL, "Removing set, %s, from sandbox: %s.\n", setname, sb );
  concat ( file, PATH_LEN, sbbase, "/", sb, "/", SET_RC, NULL );
  concat ( newfile, PATH_LEN, file, ".new", NULL );

  if (( ptr_file = fopen ( file, READ )) == NULL )
    uquit ( ERROR, FALSE, "\tcannot open set rcfile %s.\n", file );

  if (( ptr_new = fopen ( newfile, WRITE )) == NULL )
    uquit ( ERROR, FALSE, "\tcannot open tmp rcfile %s.\n", file);

  while (( fgets ( line, STRING_LEN, ptr_file )) != NULL ) {
    strcpy ( line_copy, line );
    line_ptr = line_copy;
    token = (char *)nxtarg ( &line_ptr, WHITESPACE );

    if ( streq ( token, SET_KEY )) {                   /* set field to check */
      token = (char *)nxtarg ( &line_ptr, WHITESPACE );

      if ( ! streq ( token, setname ))          /* no match so keep this set */
        fputs ( line, ptr_new );
    } /* if */

    else if ( *token != NUL )                    /* don't put in empty lines */
      fputs ( line, ptr_new );
  } /* while */

  fclose ( ptr_file );
  fclose ( ptr_new );
  rename ( newfile, file );
}                                                          /* remove setname */

void
check_setdir ( char ** setdir )

	/* This procedure makes sure the first two characters in
	   the set directory name are "./".  This is so everything
	   is relative to the source directory. */
{
    char        tmp_setdir [ PATH_LEN ],           /* holds setdir with file */
                tmpline [ PATH_LEN ],          /* holds setdir before prefix */
              * prefix = NULL;                     /* holds prefix of setdir */
    BOOLEAN     fine = FALSE;                                /* misc boolean */

  if ( ! streq ( *setdir, "." )) {
    if ( **setdir == SLASH )
      prefix = (char *)".";
    else if (( **setdir != '.' ) ||
	     ( **setdir + 1 != '/' ))
      prefix = (char *)"./";
    else
      fine = TRUE;

    if ( ! fine ) {
      concat ( tmpline, PATH_LEN, prefix, *setdir, NULL );
      *setdir = strdup ( tmpline );
    } /* if */

    concat ( tmp_setdir, PATH_LEN, *setdir, "/.", NULL );

    if ( isdir ( *setdir ) == ERROR ) {
      if ( ui_is_info ())
	ui_print ( VALWAYS, "would create directory: %s.\n", *setdir );
      else if ( makepath ( tmp_setdir, NULL, TRUE, TRUE ) == ERROR )
	uquit ( ERROR, FALSE, "\tcould not create directory %s.\n", *setdir );
    } /* if */
  } /* if */
}                                                            /* check setdir */

void
set_workon_bcsset_vars (char * set_name)

	/* This procedure sets the workon environment variable
	   WORKON.  It tells how many levels of workon have been set. */

{
    char      * env_ptr,                         /* holds environment values */
                buf [ NAME_LEN ];                             /* misc string */
    int         count;                                       /* misc integer */

  env_ptr = getenv ( WORKON );

  if ( env_ptr == NULL ) {
    if ( setenv ( WORKON, "1", TRUE ) == ERROR )
      ui_print ( VWARN, "WORKON setenv failure.\n" );
  } /* if */

  else {
    count = atoi ( env_ptr );
    count++;
    sprintf ( buf, "%d", count );

    if ( setenv ( WORKON, buf, TRUE ) == ERROR )
      ui_print ( VWARN, "WORKON setenv failure.\n" );
  } /* else */
  if ( setenv ( "BCSSET", set_name, TRUE) == ERROR )
      ui_print ( VWARN, "BCSSET setenv failure.\n" );
}                                                  /* set workon bcsset var */


void
create_sub_shell ( char * setdir )

	/* This procedure creates a new sub shell and puts the
	   user in it.  It first sets the environment, then
	   changes directory to the set directory.  Finally,
	   it execs a new shell. */
{
    char      * ptr,                                     /* pointer for path */
              * shell_type;                              /* pointer for path */

  if (( shell_type = getenv ( "SHELL" )) == NULL ){ /* get shell and exec it */ 
    ui_print ( VWARN, "Environment variable 'SHELL' not set.\n" );
    ui_print ( VCONT, "%s aborted.\n", progname );
    exit (1);
  } else if (( ptr = (char *)strrchr ( shell_type, SLASH )) != NULL )
    ptr++;
  else
    ptr = shell_type;

  if ( ! streq ( setdir, "." )) {
    if ( ! ui_is_info ())
      if ( chdir ( setdir ) == ERROR )
	uquit ( ERROR, FALSE, "\tcould not change directory to %s for shell.\n",
			       setdir );

    ui_print ( VNORMAL, "cd'ing to set directory: %s.\n", setdir );
  } /* if */

  if ( ui_is_info ())
    ui_print ( VALWAYS, "would start new shell: %s.\n", shell_type );
  else {
    ui_print ( VNORMAL, "starting new shell: %s.\n", shell_type );
    execlp ( shell_type, ptr, 0 );
  } /* else */
}                                                        /* create sub shell */



void print_usage (void)

	/* This procedure prints the usages for workon. */

{
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS, "%s [-setdir <directory>] [sb_opts] [ODE opts]\n", progname );
  ui_print ( VALWAYS, "\t -setdir <directory> : directory the set cd's to\n" );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s -undo [sb_opts] setname\n", progname );
  ui_print ( VALWAYS, "%s -list [sb_opts]\n", progname );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}                                                             /* print usage */
