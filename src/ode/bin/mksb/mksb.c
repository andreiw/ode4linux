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
 * $Log: mksb.c,v $
 * Revision 1.11.15.4  1993/12/23  19:08:40  marty
 * 	CR # 749 - mksb now gives a better message when it can't find the "projects"
 * 	file in the backing tree.
 * 	[1993/12/23  19:08:11  marty]
 *
 * Revision 1.11.15.3  1993/12/15  01:10:28  marty
 * 	CR # 908 - Initailize variables.
 * 	[1993/12/15  01:07:53  marty]
 * 
 * Revision 1.11.15.2  1993/11/22  22:23:48  marty
 * 	CR # 849 - Variables used in get_rc_value() must first be initialized to NULL.
 * 	[1993/11/22  22:23:27  marty]
 * 
 * Revision 1.11.15.1  1993/11/22  21:53:13  damon
 * 	CR 773. Check to see if set and default_set are the same
 * 	[1993/11/22  21:52:59  damon]
 * 
 * Revision 1.11.13.7  1993/11/15  21:07:09  marty
 * 	CR # 796 - Fixed regression, where mksb was not removing sandboxes with
 * 	the "-undo" option.
 * 	[1993/11/15  21:06:45  marty]
 * 
 * Revision 1.11.13.6  1993/11/15  20:19:37  damon
 * 	CR 799. Now tells user that it is creating a sandbox
 * 	[1993/11/15  20:19:08  damon]
 * 
 * Revision 1.11.13.5  1993/11/10  20:25:08  damon
 * 	CR 463. Added include of param.h for stat.h
 * 	[1993/11/10  20:24:46  damon]
 * 
 * Revision 1.11.13.4  1993/11/09  20:32:52  damon
 * 	CR 782. Remove call to workon
 * 	[1993/11/09  20:32:34  damon]
 * 
 * Revision 1.11.13.3  1993/11/04  19:51:56  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  19:48:39  damon]
 * 
 * Revision 1.11.13.2  1993/10/29  12:41:35  damon
 * 	CR 683. do not add sandbox entry to .sandboxrc when upgrading
 * 	[1993/10/29  12:40:42  damon]
 * 
 * Revision 1.11.13.1  1993/10/27  15:59:14  damon
 * 	CR 768. Abort if USER not set
 * 	[1993/10/27  15:58:59  damon]
 * 
 * Revision 1.11.11.7  1993/09/30  14:54:47  root
 * 	CR 711. Set ode_sc correctly
 * 	[1993/09/30  14:53:42  root]
 * 
 * Revision 1.11.11.6  1993/09/27  18:55:04  damon
 * 	CR 694. Added more checks for ode_build_env
 * 	[1993/09/27  18:46:24  damon]
 * 
 * Revision 1.11.11.5  1993/09/24  15:38:06  damon
 * 	CR 681. Do not remove sandbox on error if upgrading
 * 	[1993/09/24  15:37:50  damon]
 * 
 * Revision 1.11.11.4  1993/09/22  17:12:16  marty
 * 	CR # 676 - mksb no longer changes the enviroment variable EDITOR before doing a "workon".
 * 	[1993/09/22  17:11:48  marty]
 * 
 * Revision 1.11.11.3  1993/09/21  18:49:01  damon
 * 	CR 673. Removed debugging statement
 * 	[1993/09/21  18:48:45  damon]
 * 
 * Revision 1.11.11.2  1993/09/21  16:48:27  damon
 * 	CR 673. Read all sb.conf files in backing chain
 * 	[1993/09/21  16:47:53  damon]
 * 
 * Revision 1.11.11.1  1993/09/03  21:47:48  damon
 * 	CR 643. mksb -u now more robust
 * 	[1993/09/03  21:47:26  damon]
 * 
 * Revision 1.11.9.1  1993/07/12  15:25:05  damon
 * 	CR 603. Works properly when no .sandboxrc and -dir not set
 * 	[1993/07/12  15:24:49  damon]
 * 
 * Revision 1.11.6.20  1993/06/10  19:32:37  damon
 * 	CR 583. Moved prj_read to legal_backing_tree()
 * 	[1993/06/10  19:32:23  damon]
 * 
 * Revision 1.11.6.19  1993/06/09  19:38:11  damon
 * 	CR 583. Removed ifdef, restored upgrade warning
 * 	[1993/06/09  19:38:02  damon]
 * 
 * Revision 1.11.6.18  1993/06/09  19:34:43  damon
 * 	CR 583. Upgrading sandboxes cleaned up
 * 	[1993/06/09  19:34:28  damon]
 * 
 * Revision 1.11.6.17  1993/06/07  16:30:15  damon
 * 	CR 571. Undoing previous change. Should be in workon
 * 	[1993/06/07  16:30:02  damon]
 * 
 * Revision 1.11.6.16  1993/06/07  15:39:32  damon
 * 	CR 571. mksb now uses the correct set name
 * 	[1993/06/07  15:39:20  damon]
 * 
 * Revision 1.11.6.15  1993/06/02  13:51:47  damon
 * 	CR 517. Cleaned up subprojects wrt sb.conf and sc.conf
 * 	[1993/06/02  13:50:39  damon]
 * 
 * Revision 1.11.6.14  1993/05/28  14:24:36  marty
 * 	CR # 558 - Get it building on rios_aix.
 * 	[1993/05/28  14:24:11  marty]
 * 
 * Revision 1.11.6.13  1993/05/26  14:51:00  damon
 * 	CR 543. -u option creates project dir in rc_files dir
 * 	[1993/05/26  14:50:45  damon]
 * 
 * Revision 1.11.6.12  1993/05/21  15:10:25  marty
 * 	CR # 533 - 'mksb' no longer checks for the files rc_files/shared.tmpl or
 * 	rc_files/loacl.tmpl.
 * 	[1993/05/21  15:09:57  marty]
 * 
 * Revision 1.11.6.11  1993/05/14  18:00:58  damon
 * 	CR 526. Informs user if backing build needs to be upgraded
 * 	[1993/05/14  18:00:49  damon]
 * 
 * Revision 1.11.6.10  1993/05/14  16:50:11  damon
 * 	CR 518. no longer requires -p
 * 	[1993/05/14  16:47:24  damon]
 * 
 * Revision 1.11.6.9  1993/05/14  15:00:24  damon
 * 	CR 481. Added upgrade option to upgrade old sbs to ODE 2.3 sbs
 * 	[1993/05/14  15:00:03  damon]
 * 
 * Revision 1.11.6.8  1993/04/29  16:50:06  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:49:50  marty]
 * 
 * Revision 1.11.6.7  1993/04/21  19:54:16  damon
 * 	CR 446. Added include of dirent.h
 * 	[1993/04/21  19:54:05  damon]
 * 
 * Revision 1.11.6.6  1993/04/20  22:03:04  marty
 * 	Added include files ode/interface and stdio.h.
 * 	Changes set_write() to sets_write().
 * 	[1993/04/20  22:02:37  marty]
 * 
 * Revision 1.11.6.5  1993/04/09  14:29:44  damon
 * 	CR 417. Works with new split sandbox setup
 * 	[1993/04/09  14:29:31  damon]
 * 
 * Revision 1.11.6.4  1993/03/31  20:46:38  marty
 * 	Variable "basedir" must contain the pathname of the directory where
 * 	the sandbox will reside.
 * 	[1993/03/31  20:46:18  marty]
 * 
 * Revision 1.11.6.3  1993/02/01  21:56:58  damon
 * 	CR 417. Now uses sb_conf calls
 * 	[1993/02/01  21:56:29  damon]
 * 
 * Revision 1.11.6.2  1993/01/13  16:43:37  damon
 * 	CR 382. Removed NO_DIRENT
 * 	[1993/01/05  20:50:48  damon]
 * 
 * Revision 1.11.4.8  1992/12/03  19:07:56  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:06  damon]
 * 
 * Revision 1.11.4.7  1992/10/14  20:47:52  damon
 * 	CR 288. Updated call to ui_init
 * 	[1992/10/14  20:45:14  damon]
 * 
 * Revision 1.11.4.6  1992/09/24  18:58:57  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:17:49  gm]
 * 
 * Revision 1.11.4.5  1992/07/26  17:29:54  gm
 * 	Fixed to remove warnings when compiling under OSF/1 R1.1.
 * 	[1992/07/17  20:48:54  gm]
 * 
 * Revision 1.11.4.4  1992/06/24  16:04:12  zeliff
 * 	Defect 48: removing invocation of workon with -nosh
 * 	[1992/06/24  16:02:16  zeliff]
 * 
 * Revision 1.11.4.3  1992/06/16  22:11:51  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:01:24  damon]
 * 
 * Revision 1.11.2.2  1992/03/25  22:46:48  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  22:19:57  damon]
 * 
 * Revision 1.11  1991/12/05  20:45:58  devrcs
 * 	Fixed call to populate_sandbox
 * 	[91/10/04  15:16:43  damon]
 * 
 * 	updated print_usage() and print_revision()
 * 	[91/06/11  12:00:41  ezf]
 * 
 * 	Corrected how mksb handled <Return> when answering the list of
 * 	backing builds.
 * 	Corrected call to workon so it creates .BCSlock file.
 * 	[91/01/22  16:49:39  randyb]
 * 
 * 	Code review; fixed -undo and -list which did not work properly
 * 	[91/01/11  10:31:16  randyb]
 * 
 * 	Fixed core dump when there was no sandboxrc file and only a build
 * 	name was given without its path.
 * 	[91/01/09  14:00:34  randyb]
 * 
 * 	Finished Tools II implementation.
 * 	[91/01/08  15:06:43  randyb]
 * 
 * 	Converted to interface.c way of doing things.
 * 	[91/01/07  16:20:00  damon]
 * 
 * 	Changed determining default rc file to library routine in libsb.a
 * 	[90/12/20  08:36:34  randyb]
 * 
 * 	Fixed initialization problem. 'b' now recognized as default option.
 * 	[90/12/15  11:14:18  damon]
 * 
 * 	Changed get_default_rc to set_default_rc which calls a new
 * 	get_default_rc from interace.c (libsb) which returns a string.
 * 	[90/12/10  18:05:20  damon]
 * 
 * 	Using libsb.a routines to determine base directory of backing
 * 	tree.
 * 	Now writes .sandboxrc file out using command line options.
 * 	Supports new command line options for populating tools, objects,
 * 	and source.
 * 	[90/12/10  13:17:21  randyb]
 * 
 * 	Major changes in the way mksb gets its build information.  It now
 * 	looks in the sandboxes backing rc file if it can.
 * 	Also changes were made to setup for future changes.
 * 	[90/11/13  17:21:44  randyb]
 * 
 * 	Style updates; saber c lint
 * 	[90/11/08  08:01:57  randyb]
 * 
 * Revision 1.8  90/09/23  16:55:56  devrcs
 * 	Pre-OSF1.0 changes
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
**	mksb.c creates a sandbox in accordance with the user's instructions.
**
 */

static const char * rcsid =
 "$RCSfile: mksb.c,v $ $Revision: 1.11.15.4 $ $Date: 1993/12/23 19:08:40 $";

#include <sys/param.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ode/builddata.h>
#include <ode/interface.h>
#include <ode/errno.h>
#include <ode/project.h>
#include <ode/public/error.h>
#include <ode/sandboxes.h>
#include <ode/sets.h>
#include <ode/util.h>
#include <stdlib.h>
#include "mksb.h"

#define NOSC_OP       "-no_ode_sc"
#define NOBLD_OP      "-no_ode_bld"

const char        * progname = "mksb";                 /* the program's name */
    BOOLEAN 	  new_rc = FALSE;  		   /* is there a new rc file */
    BOOLEAN	ode_sc;
    BOOLEAN	ode_build_env;
    char * basedir = NULL;               /* base directory to sandbox */
    char * project = NULL;               /* project */
    char * backing_build = NULL;

    UIINIT init [] = {                      /* initialize the user interface */
      { BACK_OP,  1, OVERWRITE,	 1, 1,	ARGS_OP },
      { DIR_OP,   1, OVERWRITE,  1, 1,  "/*" },
      { SET_OP,	  1, OVERWRITE,	 1, 1,	ARGS_OP },
      { M_OP,	  1, OVERWRITE,	 1, 1,	ARGS_OP },
      { DEF_OP,	  1, OVERWRITE,	 0, 0,	"" },
      { TOOLS_OP, 1, OVERWRITE,	 1, 1,	"b c l" },
      { OBJ_OP,   1, OVERWRITE,  2, 2,  "b c l /*" },
      { SRC_OP,   1, OVERWRITE,  2, 2,  "b c l /*" },
      { LIST_OP,  1, OVERWRITE,	 0, 0,	"" },
      { UPGRADE_OP,  1, OVERWRITE,	 0, 0,	"" },
      { UNDO_OP,  1, OVERWRITE,	 0, 0,	"" },
      { NOSC_OP,  1, OVERWRITE,  0, 0,  "" },
      { NOBLD_OP,  1, OVERWRITE, 0, 0,  "" },
      { ARGS_OP,  1, OVERWRITE,	 0, 0,	"" } 
    };
#  define  MAX_ARGS     (sizeof(init) / sizeof(UIINIT)) /* number of args */

char * env_user;                      /* holds values from getenv */

/*
 * PROTOTYPES
 */
void
cmdline_syntax ( char ** , char ** , char ** , char ** , char ** );
void
legal_rc_file ( char ** );
void
set_default_rc ( char ** );
void
undo_sandbox ( char * sb, char * rc_file, char * sbrc );
void
list_sandboxes ( char * rc );
void
create_sandbox ( char * proj_dir, char * def_build, char * sb, char * rc_file,
                 char * sb_rc );
void
legal_sandbox ( char ** sb );
void
load_defaults ( char * , char ** , char ** , char ** , char ** );
void
legal_backing_tree ( char * build_dir, char * sbrc );
BOOLEAN	legal_sandbox_dir ( char * sandbox );
void
legal_setname ( char * sandbox );
BOOLEAN	legal_machine_names (void);
void
legal_tools_opt (void);
void
legal_object_dirs (void);
void
legal_source_dirs (void);
void
legal_list_undo (void);
BOOLEAN check_colon_line ( char * );
void
remove_sb ( char * sb, char * rcfile, char * sbdir );
BOOLEAN	remove_sb_from_rc ( char * sbname, char * rcfile );
FILE  *	create_tmp_file ( char * rc_path, char * tmp_rc );
void
init_rc_values ( RC_CONT * rc_values );
void
read_in_rc_info ( char * rc_file, RC_CONT * rc_values );
void
finish_fields ( char * , char * , char * , char * , RC_CONT * );
void
build_sb_structure ( char * sb, char * rc_file, char * sbbase );
void
create_user_rc_file ( RC_CONT * rc, char * sb, char * rc_file );
void
update_user_rc_file ( char * sb, char * rc, char * sbrc );
void
create_default_set ( char * sb, char * rc_file, char * sb_rcfile );
void
populate_sandbox ( RC_CONT * rc_values, char * sb_name, char * rc_file,
                   char * sb_rcfile );
void
load_base ( RC_CONT * rc_values, char targ[], char val[] );
void
load_sb ( RC_CONT * rc_values, char targ[] );
void
print_out_rc_values ( RC_CONT * rc );
void
unique_sb ( char * newsb, ENTRY * currentsb );
void
set_default_dir ( RC_CONT * rc_values, char * sb );
void
set_backing ( char * proj_dir, char * def_build, char * sb_rc );
void
set_default_machine ( RC_CONT * rc_values );
void
set_tools_population ( RC_CONT * rc_values );
void
set_obj_population ( RC_CONT * rc_values );
void
set_src_population ( RC_CONT * rc_values );
void
create_machine_sub_dirs ( char * sb, char * rc_file, char * sbbase,
                          char * machines );
void
tools_obj_run_through ( char * sb_name, char * rc_file, char * sb_rcfile,
                        char tsubdir [], char osubdir [], RC_CONT * rc_values );
void
create_local_files ( char * sb_name, char * rc_file, char * sb_rcfile,
                     char * directory, BOOLEAN copy );

void
main ( int argc, char **argv )

  	/* This function checks the command line arguments and makes
	   sure they are syntactically correct.  This is done using
	   the library function ui_init.  If this is correct,
	   the dependencies are checked.  Errors lead to usage messages.
	   If all is okay, the primary procedures are called. */
{
    char      	* def_build = NULL,        /* default build for this project */
              	* proj_dir = NULL,    /* location of builds for this project */
	      	* sb = NULL,                                 /* sandbox name */
		* rc_file = NULL,                            /* user rc file */
              	* sb_rc = NULL;                         /* sandbox's rc file */

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  cmdline_syntax ( &proj_dir, &def_build, &sb, &rc_file, &sb_rc );

  if ( ui_is_set ( UNDO_OP )) {
    undo_sandbox ( sb, rc_file, sb_rc );
  } else if ( ui_is_set ( LIST_OP ))
    list_sandboxes ( rc_file );
  else
    create_sandbox ( proj_dir, def_build, sb, rc_file, sb_rc );

  exit ( OK );
}                                                                    /* main */


void
cmdline_syntax ( char ** proj_dir, char ** def_build, char ** sb, char ** rc_file, char ** sb_rc )

	/* This procedure checks for relationships between the
	   command line arguments.  It assumes the syntax is
	   already correct. */

{

  if ( ! ui_is_set ( LIST_OP ))
    legal_sandbox ( sb );

  legal_rc_file ( rc_file );

  if ( ui_is_set ( RC_OP ))
    load_defaults ( *sb, proj_dir, def_build, sb_rc, rc_file );

  if ( ui_is_set ( BACK_OP ) )
    legal_backing_tree ( *proj_dir, *sb_rc ); 
  
  if ( ui_is_set ( DIR_OP ) && ! ui_is_set ( UPGRADE_OP ) ) 
    if ( ! legal_sandbox_dir ( *sb ))
      ui_unset ( DIR_OP );
  
  if ( ode_sc && ui_is_set ( SET_OP ))
    legal_setname ( *sb );
  
  if ( ui_is_set ( M_OP )) 
    if ( ! legal_machine_names ())
      ui_unset (  M_OP );
  
  if ( ui_is_set ( TOOLS_OP ))
    legal_tools_opt ();

  if ( ui_is_set ( OBJ_OP ))
    legal_object_dirs () ;

  if ( ui_is_set ( SRC_OP ))
    legal_source_dirs () ;

  legal_list_undo ();
}                                                          /* cmdline syntax */



void
legal_sandbox ( char ** sb )

	/* This procedure checks on the sandbox name to make sure
	   it is there when it should be and that it is legal. */
{
    int           ct;                                        /* misc counter */

  if (( *sb = ui_entry_value ( ARGS_OP, 1 )) == NULL )
    uquit ( ERROR, TRUE, "name of sandbox required.\n" );

  if ( ui_is_set ( SET_OP )) {
    for ( ct = 0; (unsigned)ct < strlen ( *sb ); ct++ ) {

      if ( **sb + ct == SLASH )
        uquit ( ERROR, TRUE, "sandbox name, %s, has '%c' character in it.\n",
		*sb, SLASH );
    } /* for */
  } /* if */

  else if ( ! ui_is_set ( UNDO_OP )) {
    ui_load ( SET_OP, 1, *sb );
    ui_print ( VDETAIL, "Name of default set will match sandbox name: %s.\n",
	                 *sb );
  } /* else if */
  
  ui_print ( VDETAIL, "Name of sandbox will be: %s.\n", *sb );
}                                                           /* legal sandbox */


void
legal_rc_file ( char ** rc )

	/* This procedure checks to see if the named rc file exists
	   and is writable.  If it does not exist, it checks to 
	   see if it can create it.  */

{
    FILE	* fptr;  /* misc file pointer */
    char          full_rc [ PATH_LEN ],                       /* misc string */
                  cwd [ MAXPATHLEN ];     /* holds current working directory */

  if (( *rc = ui_arg_value ( RC_OP, 1, 1 )) != NULL ) {
    if ( **rc != SLASH ) {
      if ( getcwd ( cwd, sizeof(cwd) ) == NULL )
        uquit ( ERROR, FALSE, "call to getcwd failed.\n" );

      concat ( full_rc, PATH_LEN, cwd, "/", *rc, NULL );
      ui_load ( RC_OP, 1, full_rc );
    } /* if */
  } /* if */
  
  else 
    set_default_rc ( rc );

  if ( access ( *rc, F_OK ) == ERROR ) {
    if (( fptr = fopen ( *rc, WRITE )) == NULL )
      uquit ( ERROR, FALSE, "Cannot create user's rc file: %s.\n", *rc );

    fclose ( fptr );
    unlink ( *rc );
    new_rc = TRUE;
    ui_print ( VNORMAL, "User rc file, %s, does not exist; will create it.\n",
                         *rc );
  } /* if */
  
  else if ( access ( *rc, W_OK ) == ERROR )
    uquit ( ERROR, FALSE, "Cannot write in user's rc file: %s.\n", *rc );
   
  else
    ui_print ( VDETAIL, "user's rc file is: %s.\n", *rc );
}                                                           /* legal rc file */


void
set_default_rc ( char ** rc )

 	/* This procedure fills in the name of the default rc file. */
{
  if ( ! get_default_usr_rcfile ( rc, FALSE ))
    new_rc = TRUE;

  ui_load ( RC_OP, 1, *rc );
}                                                          /* set default rc */



void
load_defaults ( char * sb, char ** proj_dir, char ** def_build, char ** sb_rc,
                char ** rcfile ) 

	/* This procedure finds the project directory and default
	   build for the project and loads that information. */

{
    char        * def_sb = NULL;                    /* holds default sandbox */

  if ( ui_is_set ( UPGRADE_OP ) ) {
    def_sb = sb;
  } /* if */
  if ( *rcfile != NULL && access ( *rcfile, R_OK ) != ERROR ) {
    
    if ( current_sb ( &def_sb, &basedir, sb_rc, rcfile ) == ERROR ) {
      *proj_dir = NULL;
      *def_build = NULL;
      ui_print ( VWARN, "could not get project directory or default build.\n" );
    } /* if */

    ui_print ( VDEBUG, "project dir: %s;\ndefault build: %s;\nsbrc: %s.\n",
			*proj_dir, *def_build, *sb_rc );
  } /* if */

  else {
    *proj_dir = NULL;
    *def_build = NULL;
  } /* else */
}                                                           /* load defaults */


void
legal_backing_tree ( char * build_dir, char * sbrc )

	/* This function checks to see if the backing tree is a
 	   legal entity.  If it is not, it unsets the flag so the
 	   program can prompt for this information later. */
{
    DIR       * dir_ptr;                            /* points to a directory */
    struct      rcfile    contents;             /* holds contents of rc file */
    char        tmp_file [ PATH_LEN ],                        /* misc string */
              * newbase,                           /* pts to build list base */
              * back_build;
    BOOLEAN     failed = FALSE;                              /* misc boolean */
    BOOLEAN     verbose;                                   /* verbose switch */
  char * sub_project;
  struct rcfile sbconf_rc;
  char * ode_build_env_rc = NULL;
  char * ode_sc_rc = NULL;

  verbose = ui_ver_level () >= VDETAIL;
  back_build = ui_arg_value ( BACK_OP, 1, 1 );

  if ( *back_build != SLASH ) {
    if ( build_dir != NULL )
      concat ( tmp_file, PATH_LEN, build_dir, "/", back_build, NULL);

    if ( build_dir != NULL &&
        (( dir_ptr = opendir ( tmp_file )) != NULL )) {
      ui_load ( BACK_OP, 1, tmp_file );
      closedir ( dir_ptr );
    } /* if */

    else {
      ui_print ( VDEBUG, "not in default build\n" );
      memset ( (char *)&contents, 0, sizeof ( contents ));

      if ( sbrc != NULL && parse_rc_file ( sbrc, &contents ) == OK )
	newbase = build_base_dir ( back_build, &contents, verbose, FALSE );
      else			  
	newbase = build_base_dir ( back_build, &contents, verbose, TRUE );

      if ( newbase != NULL ) {
	concat ( tmp_file, PATH_LEN, newbase, "/", back_build, NULL );

	if (( dir_ptr = opendir ( tmp_file )) != NULL ) {
	  ui_load ( BACK_OP, 1, tmp_file);
	  closedir ( dir_ptr );
	} /* if */

	else {
          ui_print ( VDEBUG, "not in build list build\n" );
	  failed = TRUE;
	} /* else */
      } /* if */

      else {
        ui_print ( VDEBUG, "parse rc failed\n" );
	failed = TRUE;
      } /* else */
    } /* else */
  } /* if */

  back_build = ui_arg_value ( BACK_OP, 1, 1 );

  if ( failed ) {
    ui_print ( VWARN, "%s is not a legal, accessible sandbox.\n", back_build );
    ui_print ( VCONT, "Will prompt for this information.\n" );
    ui_unset ( BACK_OP );
  } /* if */

  else {
    backing_build = ui_arg_value ( BACK_OP, 1, 1 );
    if ( ! prj_read ( backing_build, ".", &project, &sub_project ) ) {
      ui_print ( VFATAL, "The backing tree %s is incorrectly set up.\n",
                         backing_build );
      ui_print ( VCONT, "Could not read the file %s/%s\n",
		backing_build, PROJECTS);
      exit(-1);
    } /* if */
    sb_conf_read_chain ( &sbconf_rc, backing_build , project,
                         sub_project );
    get_rc_value ( "ode_build_env", &ode_build_env_rc, &sbconf_rc, FALSE );
    ode_sc_rc = NULL;
    get_rc_value ( "ode_sc", &ode_sc_rc, &sbconf_rc, FALSE );
    ode_sc = ( ode_sc_rc == NULL || strcmp ( ode_sc_rc, "true" ) == 0 );
    ode_build_env = ( ode_build_env_rc == NULL ||
                      strcmp ( ode_build_env_rc, "true" ) == 0 );
    if ( ui_is_set ( NOSC_OP ) ) {
      ode_sc = FALSE;
    } /* if */
    if ( ode_sc ) {
      if (( env_user = (char *)getenv ( "USER" )) == NULL ) {
        ui_print ( VFATAL, "Environment variable USER not set.\n" );
        ui_print ( VCONT, "Aborting mksb.\n" );
        exit (1);
      } /* if */
    } /* if */
    if ( ui_is_set ( NOBLD_OP ) ) {
      ode_build_env = FALSE;
    } /* if */
    ui_print ( VDETAIL, "Backing tree is build or sandbox: %s.\n", back_build );
  } /* if */
}                                                      /* legal backing tree */



BOOLEAN	legal_sandbox_dir ( char * sandbox )

	/* This function checks to see if the directory entered
	   to create the sandbox in exists.  If it does, then it
	   checks to see if it can be written into. It returns
	   FALSE if it cannot access the directory for any reason. */
{
    DIR         * dir_ptr;                          /* points to a directory */
    char          sb_string [ PATH_LEN ];           /* holds path to sandbox */
    char	* dir;

  dir = ui_arg_value ( DIR_OP, 1, 1 );

  if ( dir == NULL || ui_is_set ( UNDO_OP ) || ui_is_set ( LIST_OP ))
     return ( FALSE );	          /* cannot use this -dir with these options */

  if (( dir_ptr = opendir ( dir )) == NULL ) {
    ui_print ( VWARN, "the directory, %s,\n", dir );
    ui_print ( VCONT, "for the sandbox cannot be opened.\n" );
    return ( FALSE );
  } /* if */

  closedir ( dir_ptr );

  if ( access ( dir, W_OK ) == ERROR ) {
    ui_print ( VWARN, "cannot write in the directory, %s, for the sandbox.\n",
	      	       dir );
    return ( FALSE );
  } /* if */

  concat ( sb_string, PATH_LEN, dir, "/", sandbox, NULL );

  if ( access ( sb_string, F_OK ) == OK ) {               /* sb cannot exist */
    if ( ! ui_is_set ( LIST_OP ) && ! ui_is_set ( UPGRADE_OP ) ) {
      ui_print ( VWARN, "Found existing file at %s\n", sb_string );
      ui_print ( VCONT, "where sandbox was to be.\n" );
    } /* if */
    if ( ! ui_is_set ( UPGRADE_OP ) ) {
      return ( FALSE );
    } else {
      return ( TRUE );
    } /* if */
  } /* if */

  ui_print ( VDETAIL,"Sandbox directory and name will be: %s.\n", sb_string );
  basedir = strdup(dir);
  return ( TRUE );
}                                                       /* legal sandbox dir */



void
legal_setname ( char * sandbox )

	/* This procedure checks to see if the setname has any
	   illegal characters in it. */
{
    char	* set;  			   /* holds user entered set */
    int           ct;                                        /* misc counter */
    char * set_name;
  struct rcfile contents;
  char buf [MAXPATHLEN];
  char buf2 [MAXPATHLEN];
  char * default_set = NULL;

  set = ui_arg_value ( SET_OP, 1, 1 );

  for ( ct = 0; (unsigned)ct < strlen ( set ); ct++ ) {
    if (( set[ct] == PERIOD ) ||
        ( set[ct] == SLASH ) ||
        ( set[ct] == DASH )) {
      
      if ( streq ( set, sandbox ))
        uquit ( ERROR, FALSE, "\tsetname, %s, %s %s: '%c' or '%c' or '%c'.\n",
		set, "which was taken from the sandbox name,\n",
		"\thas one of the following characters in it",
		PERIOD, DASH, SLASH );

      else 
        uquit ( ERROR, FALSE,  "\tsetname, %s, %s\t'%c' or '%c' or '%c'.\n",
		set, "has one of the following characters in it:\n",
		PERIOD, DASH, SLASH );
    } /* if */
  } /* for */
  sets_fullname ( set, env_user, &set_name );
/*
 * FIXME!
 * This must go away when sc.conf dissappears from the backing build.
 */
  concat ( buf2, sizeof (buf2), backing_build, "/rc_files/", project, NULL );
  concat ( buf, sizeof (buf), buf2, "/sc.conf", NULL );
  if ( init_rc_contents ( &contents, buf ) == ERROR ) {
    ui_print ( VFATAL, "Unable to read sc.conf file from backing build.\n" );
    exit(1);
  }
  get_rc_value ( "default_set", &default_set, &contents, FALSE );
  if ( strcmp ( default_set, set_name ) == 0 ) {
    ui_print ( VWARN, "User's set cannot be the same as the submit set.\n" );
    ui_print ( VCONT, "User's set and submit set are both: %s\n",
                      default_set );
    ui_print ( VCONT, "Aborting mksb.\n" );
    exit(1);
  } /* if */
  ui_print ( VDETAIL, "Name of default set will be: %s.\n", set );
}                                                           /* legal setname */



BOOLEAN	legal_machine_names (void)

	/* This function checks to see if it can parse the list
	   of machine names.  If the arguments is not legal, it
	   returns FALSE. */


{
    char      * machine_args;             /* the information on the machines */
    int         ct;                                          /* misc counter */

  machine_args = ui_arg_value ( M_OP, 1, 1 );

  for ( ct = 0; (unsigned)ct < strlen ( machine_args ); ct++ ) {
    if ( machine_args[ct] == SLASH ) {
      ui_print ( VWARN, "machine string, %s, has an imbedded slash.\n",
		         machine_args );
      return (  FALSE );
    } /* if */
  } /* for */

  ui_print ( VDETAIL, "Name(s) of machines will be: %s.\n", machine_args );
  return ( TRUE );
}                                                     /* legal machine names */



void
legal_tools_opt (void)

	/* This function checks the argument given to the tools
	   populating option and verifies that it is legal. */

{
    char      * tool_arg;                /* the information on tools backing */

  tool_arg = ui_arg_value ( TOOLS_OP, 1, 1 );

  if ( *tool_arg != COPY_CH &&
       *tool_arg != LINK_CH  &&
       *tool_arg != BACK_CH ) 
    uquit ( ERROR, TRUE, "\targument to %s option must be %c, %c, or %c.\n",
	    TOOLS_OP, BACK_CH,COPY_CH, LINK_CH );

  ui_print ( VDETAIL, "Tools populating method: %c.\n", *tool_arg );
}                                                         /* legal tools opt */



void
legal_object_dirs (void)

	/* This function checks the arguments given to the object
	   populating option and verifies that they are legal. */


{
    char      	* method,   		     /* method for populating object */
		* directories;      	      /* the directories to populate */

  method = ui_arg_value ( OBJ_OP, 1, 1 );
  directories = ui_arg_value ( OBJ_OP, 1, 2 );

  if ( *method != COPY_CH &&
       *method != LINK_CH  &&
       *method != BACK_CH ) {
    ui_print ( VWARN, "argument to %s option must be %c, %c, or %c.\n",
	               OBJ_OP, BACK_CH, COPY_CH, LINK_CH );
    ui_print ( VCONT, "will prompt for correct information.\n" );
    ui_unset ( OBJ_OP);
  } /* if */
  
  if ( ! check_colon_line ( directories )) {
    ui_unset ( OBJ_OP );
    ui_print ( VCONT, "will prompt for correct information.\n" );
  } /* if */

  if ( ui_is_set ( OBJ_OP )) {
    ui_print ( VDETAIL, "Object populating method: %c.\n", *method );
    ui_print ( VCONT, "directories to populate: %s.\n", directories );
  } /* if */
}                                                       /* legal object dirs */



BOOLEAN check_colon_line ( char * line )

	/* This function checks to see if each of the directories
	   in the colon separated lines starts with a SLASH.  It
	   returns TRUE if they all start with slash. */
{
    char        line_copy [ PATH_LEN ],    /* will hold first string of line */
              * line_ptr,                     /* needs to move along ns_line */
              * list;                         /* needs to move along ns_line */

  strcpy ( line_copy, line );
  line_ptr = line_copy;                         /* copy can't move, list can */

  do {
    list = nxtarg ( &line_ptr, ":" );

    if ( *list != SLASH ) {
      ui_print ( VWARN, "Each part of the colon separated list: %s,\n", line );
      ui_print ( VCONT, "must start with a '/'.\n" );
      return ( FALSE );
    } /* if */
  } while ( *line_ptr != NUL );

  return ( TRUE );
}                                                        /* check colon line */



void
legal_source_dirs (void)

	/* This function checks the arguments given to the source
	   populating option and verifies that they are legal. */


{
    char      	* method,  	        /* the method for populating sources */
		* dirs;                       /* the directories to populate */

  method = ui_arg_value ( SRC_OP, 1, 1 );
  dirs = ui_arg_value ( SRC_OP, 1, 2 );

  if ( *method != COPY_CH &&
       *method != LINK_CH  &&
       *method != BACK_CH ) {
    ui_print ( VWARN, "argument to %s option must be %c, %c, or %c.\n",
	      	       SRC_OP, BACK_CH, COPY_CH, LINK_CH );
    ui_print ( VCONT, "will prompt for correct information.\n" );
    ui_unset ( SRC_OP );
  } /* if */
  
  if ( ! check_colon_line ( dirs )) {
    ui_print ( VCONT, "will prompt for correct information.\n" );
    ui_unset ( SRC_OP );
  } /* if */

  if ( ui_is_set ( SRC_OP )) {
    ui_print ( VDETAIL, "Object populating method: %c.\n", *method );
    ui_print ( VCONT, "directories to populate: %s.\n", dirs );
  } /* if */
}                                                       /* legal source dirs */



void
legal_list_undo (void)

	/* This procedure checks to see if only legal options
	   were used with the list option.  */

{
  if ( ui_is_set ( UNDO_OP ) && ui_is_set ( LIST_OP ))
    uquit ( ERROR, TRUE, 
               "Both options %s and %se were set; this is not allowed.\n",
               LIST_OP, UNDO_OP );
}                                                    /* legal list undo */



void
undo_sandbox ( char * sb, char * rc_file, char * sbrc )

	/* This procedure undoes a sandbox if the sandbox has not
	   had files checked out into it.  It does this by opening
	   the directory and seeing if any BCS checkouts have
	   been done. */
{
    DIR         * dir_ptr;                          /* points to a directory */
    struct	dirent * ds;               /* points to struct with dir list */
    char          ssb_path [ PATH_LEN ],          /* path and name to sb/src */
                * dir_args = NULL;               /* to hold sandbox base dir */
    BOOLEAN       safe = TRUE;                               /* misc boolean */

  if ( new_rc )
    uquit ( ERROR, FALSE, "\t%s user's rc file does not exist.\n",
                      	   ui_arg_value ( RC_OP, 1, 1 ));

  if ( current_sb ( &sb, &dir_args, &sbrc, &rc_file ) == ERROR )
    uquit ( ERROR, FALSE,  
    	    "sandbox, %s, not correctly setup\n\tin user's rc file %s\n",
	     sb, rc_file );

				   /* Determine if BCSpath has been created. */
  concat ( ssb_path, PATH_LEN, dir_args, "/", sb, "/", SRC_DIR, NULL );

  if (( dir_ptr = opendir ( ssb_path )) == NULL )
    uquit ( ERROR, FALSE, "Did not find directory at %s to remove.\n",
			   ssb_path );

  for ( ds = readdir ( dir_ptr ); ds != NULL; ds = readdir ( dir_ptr )) {
    if (( strncmp ( ds->d_name, BCS_SET, BCS_SET_L )) == OK ) {
      ui_print ( VWARN,
	"Found BCS file, %s: indicating files have been checked out\n",
	 ds->d_name );
      ui_print ( VCONT, "therefore not removing sandbox %s.\n", sb );
      safe = FALSE;
    } /* if */
  } /* for */

  closedir ( dir_ptr );

  if ( safe )
    remove_sb ( sb, rc_file, dir_args );
}                                                            /* undo sandbox */



void
remove_sb ( char * sb, char * rcfile, char * sbdir )

	/* This procedure removes the sandbox directory. */
{
    char        file_path [ PATH_LEN ],                       /* misc string */
                reply [ NAME_LEN ];                           /* misc string */
    BOOLEAN     goahead = FALSE;                             /* misc boolean */

  if ( ui_is_set ( UPGRADE_OP ) ) {
    return ;
  } /* if */
  if ( chdir ( "/" ) == ERROR )
    ui_print ( VFATAL, "could not change directories to '/'.\n" );

  concat ( file_path, PATH_LEN, sbdir, "/", sb, NULL );
 
  if ( ui_is_auto ())
    goahead = TRUE;
    
  else {
    ui_print ( VALWAYS, "Remove sandbox %s? [y|<n>] ", file_path );
    gets ( reply );

    if ( streq ( reply, YES ))
      goahead = TRUE;
  } /* else */

  if ( goahead ) {
    ui_print ( VDETAIL, "Removing sandbox %s.\n", file_path );

    switch ( fork ()) {
      case ERROR: ui_print ( VFATAL,
		  "fork failed, could not remove sandbox: %s.\n", file_path );
		  break;

      case CHILD: if ( ui_is_info ())
		    ui_print ( VALWAYS, "Would have done: 'rm -rf %s'\n", file_path);

		  else {
		    execlp ( RM, RM, "-r", "-f", file_path, NULL );
    		    uquit ( ERROR, FALSE, "\treturned from execlp of: %s.\n",
				     		RM );
		  }  /* else */

		  break;

      default :   wait (( int * ) 0 );
	          break;
    } /* switch */

    if ( remove_sb_from_rc ( sb, rcfile ) == FALSE )
      ui_print ( VWARN, "did not remove sandbox %s from rc file %s.\n",
		 	 sb, rcfile );
  } /* if */
}                                                               /* remove sb */



BOOLEAN	remove_sb_from_rc ( char * sbname, char * rcfile )

	/* This procedure removes the references to the sandbox
	   which has just been deleted from the rc file.  If for
	   any reason the file cannot be edited, it returns FALSE. */
{
    FILE      * ptr_file,                                  /* ptr to rc file */
              * tmp_file=NULL;                         /* ptr to tmp rc file */
    char        line [ PATH_LEN ],                            /* misc string */
                line_copy [ PATH_LEN ],                       /* misc string */
                tmp_rc [ PATH_LEN ];                          /* misc string */
    char      * line_ptr,
              * key,
              * target;

  if (( ptr_file = fopen ( rcfile, READ )) == NULL ) {
    ui_print ( VFATAL, "cannot read user's rc file: %s.\n", rcfile );
    return ( FALSE );
  } /* if */

  if ( ! ui_is_info ())
    if (( tmp_file = create_tmp_file ( rcfile, tmp_rc )) == NULL )
      return ( FALSE );

  while (( line_ptr = fgets ( line, PATH_LEN, ptr_file )) != NULL ) {
    strcpy ( line_copy, line );
    line_ptr = line_copy;
    key = nxtarg ( &line_ptr, WHITESPACE );
    target = nxtarg ( &line_ptr, WHITESPACE );

    if ( ! streq ( target, sbname )) {
      if ( ! ui_is_info ())
        fputs ( line, tmp_file );
      continue;
    } /* if */

    if ( streq ( key, DEFAULT )) {
      ui_print ( VWARN, "rc file lists the default sandbox, %s,\n", sbname );
      ui_print ( VCONT, "as the same sandbox that was just removed.\n" );

      if ( ! ui_is_info ())
        fputs ( line, tmp_file );
    } /* if */

    else if (( ! streq ( key, BASE )) && ( ! streq ( key, SB )))
      if ( ! ui_is_info ())
        fputs ( line, tmp_file );
  } /* while */

  fclose ( ptr_file );

  if ( ! ui_is_info ()) {
    fclose ( tmp_file );

    if ( rename ( tmp_rc, rcfile ) == ERROR )
      return ( FALSE );
  }  /* if */

  return ( TRUE );
}                                                       /* remove sb from rc */



FILE  *	create_tmp_file ( char * rc_path, char * tmp_rc )

	/* This function creates a tmp file with the same path as
	   the rc file.  It opens the file for writing and passes
	   back the pointer. */
{
    FILE      * tmp_ptr;                               /* ptr to new rc file */
    char        line [ PATH_LEN ],                            /* misc string */
              * line_ptr,                                     /* misc string */
              * file_path,                                    /* misc string */
              * ptr_slash;                        /* ptr to slash in rc path */

  strcpy ( line, rc_path );
  ptr_slash = strrchr ( line, SLASH );

  if ( ptr_slash == NULL )
    strcpy ( tmp_rc, TMP_NAME );

  else {
    *ptr_slash = NUL;
    line_ptr = line;
    file_path = nxtarg ( &line_ptr, WHITESPACE );
    concat ( tmp_rc, PATH_LEN, file_path, TMP_NAME, NULL);
  } /* else */

  if (( tmp_ptr = fopen ( tmp_rc, WRITE )) == NULL ) {
    ui_print ( VFATAL, "cannot open temporary rc file %s.\n", tmp_rc );
    tmp_ptr = NULL;
  } /* if */

  return ( tmp_ptr );
}                                                         /* create tmp file */



void
list_sandboxes ( char * rc )

	/* This procedure lists the currents sandboxes. */
{
    FILE      * ptr_file;                                  /* ptr to rc file */
    char        line [ PATH_LEN ],                            /* misc string */
              * key,                                          /* misc string */
              * targ,                                         /* misc string */
              * targ2,                                        /* misc string */
              * line_ptr;                            /* needed for traveling */

  if ( new_rc )
    ui_print ( VNORMAL, "User's rc file, %s, is new.  No sandboxes in it.\n",
	      		 rc );

  if (( ptr_file = fopen ( rc, READ )) == NULL )
    uquit ( ERROR, FALSE, "cannot read user's rc file: %s.\n", rc );

  ui_print ( VNORMAL, "Sandboxes in user's rc file: %s\n", rc );

  while (( line_ptr = fgets ( line, PATH_LEN, ptr_file )) != NULL ) {
    key = nxtarg ( &line_ptr, WHITESPACE );

    if ( streq ( key, DEFAULT )) {
      targ = nxtarg ( &line_ptr, WHITESPACE );
      ui_print ( VALWAYS, "Default sandbox : %s.\n", targ );
    } /* if */

    else if ( streq ( key, SB )) {
      targ = nxtarg ( &line_ptr, WHITESPACE );
      ui_print ( VALWAYS, "Sandbox name is : %s.\n", targ );
    } /* else if */

    else if ( streq ( key, BASE )) {
      targ = nxtarg ( &line_ptr, WHITESPACE );
      targ2 = nxtarg ( &line_ptr, WHITESPACE );
      ui_print ( VALWAYS, "Sandbox base for %s is : %s.\n", targ, targ2 );
    } /* else if */
  } /* while */

  fclose ( ptr_file );
}                                                          /* list sandboxes */



void
create_sandbox ( char * proj_dir, char * def_build, char * sb, char * rc_file,
                 char * sb_rc )

	/* This procedure creates a sandbox.  It does the
	   primary function of this program. */
{
    RC_CONT       rc_values;                /* hold values read from rc file */
    ERR_LOG log;

  init_rc_values ( &rc_values );

  if ( ! new_rc )
    read_in_rc_info ( rc_file, &rc_values);

  finish_fields ( proj_dir, def_build, sb, sb_rc, &rc_values );
  ui_print ( VNORMAL, "Creating sandbox %s.\n", sb );
  build_sb_structure ( sb, rc_file, rc_values.def_sb_base );

  if ( new_rc )
    create_user_rc_file ( &rc_values, sb, rc_file );
  else
    update_user_rc_file ( sb, rc_file, sb_rc );
  if ( ( log = prj_write ( sb_full_path ( basedir, sb ), ".", project )
                         ) != OE_OK )
  { 
    ui_print ( VFATAL, "%s", err_str ( log ) );
    exit ( -1 );
  } /* if */
  if ( ( log = sb_conf_write ( basedir, sb, project, NULL,
                               backing_build, ode_sc, ode_build_env
                             ) ) != OE_OK )
  { 
    ui_print ( VFATAL, "%s", err_str ( log ) );
    exit ( -1 );
  } /* if */
  if ( ode_sc )
    create_default_set ( sb, rc_file, sb_rc );
  /* if */
  if ( ode_build_env )
    populate_sandbox ( &rc_values, sb, rc_file, sb_rc );
}                                                          /* create sandbox */



void
init_rc_values ( RC_CONT * rc_values )

	/* This procedure makes sure the rc_values start empty
	   or in the default mode. */
{
  char * tools, * objects, * sources;

  rc_values->default_sb[0] = NUL;
  rc_values->def_sb_base[0] = NUL;
  rc_values->def_machines[0] = NUL;
  rc_values->obj_dirs[0] = '/';
  rc_values->src_dirs[0] = '/';
  rc_values->obj_dirs[1] = NUL;
  rc_values->src_dirs[1] = NUL;
  rc_values->base = NULL;
  rc_values->sb = NULL;
  rc_values->tools = BACK_CH;
  rc_values->objects = BACK_CH;
  rc_values->sources = BACK_CH;

  if ( ui_is_set ( DIR_OP ) && ! ui_is_set ( UPGRADE_OP ) ) {
    strcpy ( rc_values->def_sb_base, ui_arg_value ( DIR_OP, 1, 1 ));
  } /* if */
  if ( ui_is_set ( UPGRADE_OP ) ) {
    strcpy ( rc_values->def_sb_base, basedir );
  } /* if */
  if ( ui_is_set ( M_OP ))
    strcpy ( rc_values->def_machines, ui_arg_value ( M_OP, 1, 1 ));

  if ( ui_is_set ( TOOLS_OP )) {
    tools = ui_arg_value ( TOOLS_OP, 1, 1 );
    rc_values->tools = *tools;
  }  /* if */

  if ( ui_is_set ( OBJ_OP )) {
    objects = ui_arg_value ( OBJ_OP, 1, 1 );
    rc_values->objects = *objects;
    strcpy ( rc_values->obj_dirs, ui_arg_value ( OBJ_OP, 1, 2 ));
  } /* if */

  if ( ui_is_set ( SRC_OP )) {
    sources = ui_arg_value ( SRC_OP, 1, 1 );
    rc_values->sources = *sources;
    strcpy ( rc_values->src_dirs, ui_arg_value ( SRC_OP, 1, 2 ));
  } /* if */
}                                                          /* init rc values */



void
read_in_rc_info ( char * rc_file, RC_CONT * rc_values )

	/* This procedure reads in the values of the rc file
	   into the rc_value structure. */
{
    FILE      * ptr_file;                                  /* ptr to rc file */
    char        line [ PATH_LEN ],                      /* line from rc file */
              * key,                                        /* holds keyword */
              * targ,                                        /* holds target */
              * val;                                          /* holds value */
    char      * line_ptr;

  if (( ptr_file = fopen ( rc_file, READ )) == NULL )
    uquit ( ERROR, FALSE, "cannot open user's rc file %s.\n", rc_file );
  
  while (( line_ptr = fgets ( line, PATH_LEN, ptr_file )) != NULL ) {
    if ( streq ( line, CR_STRING ))                    /* ignore blank lines */
      continue;
    key = nxtarg ( &line_ptr, WHITESPACE );

    if ( streq ( key, DEFAULT )) {
      targ = nxtarg ( &line_ptr, WHITESPACE );
      strcpy ( rc_values->default_sb, targ );
    } /* if */

    else if ( streq ( key, BASE )) {
      targ = nxtarg ( &line_ptr, WHITESPACE );
      val = nxtarg ( &line_ptr, WHITESPACE );
      load_base ( rc_values, targ, val );
    } /* else if */

    else if ( streq ( key, SB )) {
      targ = nxtarg ( &line_ptr, WHITESPACE );
      load_sb ( rc_values, targ );
    } /* else if */
  } /* while */

  if ( ui_ver_level () >= VDEBUG )
    print_out_rc_values ( rc_values );
}                                                         /* read in rc info */


void
load_base ( RC_CONT * rc_values, char targ[], char val[] )

	/* This procedure creates the next entry structure and
	   puts the base target and value in it. */
{
    ENTRY     * entry_ptr;                   /* points to last entry in list */

  if ( rc_values->base == NULL ) {                    /* first entry in base */
    rc_values->base = ( ENTRY * ) malloc ( sizeof ( ENTRY ));
    entry_ptr = rc_values->base;
  } /* if */

  else {                                               /* additional entries */
    entry_ptr = rc_values->base;

    while ( entry_ptr->nextentry != NULL )
      entry_ptr = entry_ptr->nextentry;

    entry_ptr->nextentry = ( ENTRY * ) malloc ( sizeof ( ENTRY ));
    entry_ptr = entry_ptr->nextentry;
  } /* else */

  strcpy ( entry_ptr->target, targ );
  strcpy ( entry_ptr->value, val );
  entry_ptr->nextentry = NULL;
}                                                               /* load base */


void
load_sb ( RC_CONT * rc_values, char targ[] )

	/* This procedure creates the next entry structure and
	   puts the sb target in it. */
{
    ENTRY     * entry_ptr;                   /* points to last entry in list */


  if ( rc_values->sb == NULL )  {                       /* first entry in sb */
    rc_values->sb = ( ENTRY * ) malloc ( sizeof ( ENTRY ));
    entry_ptr = rc_values->sb;
  } /* if */

  else {                                               /* additional entries */
    entry_ptr = rc_values->sb;

    while ( entry_ptr->nextentry != NULL )
      entry_ptr = entry_ptr->nextentry;

    entry_ptr->nextentry = ( ENTRY * ) malloc ( sizeof ( ENTRY ));
    entry_ptr = entry_ptr->nextentry;
  } /* else */

  strcpy ( entry_ptr->value, targ );
  entry_ptr->nextentry = NULL;
}                                                                 /* load sb */


void
print_out_rc_values ( RC_CONT * rc )

	/* This procedure prints out the values in rc_values. */
{
    ENTRY     * entry_ptr;                   /* points to last entry in list */

  ui_print ( VDETAIL, "Contents of rc file and entered values:\n" );
  ui_print ( VCONT, "  default sb         : %s\n", rc->default_sb );

  entry_ptr = rc->base;

  while ( entry_ptr != NULL ) {
    ui_print ( VCONT, "  sandbox and base   : %s, %s\n",
		      entry_ptr->target, entry_ptr->value );
    entry_ptr = entry_ptr->nextentry;
  } /* while */

  entry_ptr = rc->sb;

  while ( entry_ptr != NULL ) {
    ui_print ( VCONT, "  sandbox name       : %s\n", entry_ptr->value );
    entry_ptr = entry_ptr->nextentry;
  } /* while */

  ui_print ( VCONT, "  default sb base    : %s\n", rc->def_sb_base );
  ui_print ( VCONT, "  def machines       : %s\n", rc->def_machines );
  ui_print ( VCONT, "  tools population   : %c\n", rc->tools );
  ui_print ( VCONT, "  object population  : %c\n", rc->objects );
  ui_print ( VCONT, "  object directories : %s\n", rc->obj_dirs );
  ui_print ( VCONT, "  sources population : %c\n", rc->sources );
  ui_print ( VCONT, "  source directories : %s\n", rc->src_dirs );
}                                                     /* print out rc values */



void
finish_fields ( char * proj_dir , char * def_build , char * sb , char * sb_rc, 
                RC_CONT * rc_values)

	/* This procedure finishes off any un-filled fields.  After
	   it is done, the program is ready to do its work.  */

{
  if ( ! ui_is_set ( UPGRADE_OP ) ) {
    unique_sb ( sb, rc_values->sb );
  } /* if */

  if ( ! ui_is_set ( DIR_OP ) )
                                                       /* get directory name */
    set_default_dir ( rc_values, sb );

  if ( ! ui_is_set ( BACK_OP ))                     /* get backing tree name */
    set_backing ( proj_dir, def_build, sb_rc );

  if ( ode_build_env ) {
    if ( ! ui_is_set ( M_OP ))                          /* get machine names */
      set_default_machine ( rc_values );

    if ( ! ui_is_set ( TOOLS_OP ))       /* get tools population information */
      set_tools_population ( rc_values );

    if ( ! ui_is_set ( OBJ_OP ))    /* get object dir population information */
      set_obj_population ( rc_values );
  } /* if */

  if ( ! ui_is_set ( SRC_OP ))      /* get source dir population information */
    set_src_population ( rc_values );
}                                                            /* finish field */


void
unique_sb ( char * newsb, ENTRY * currentsb )

	/* This procedure checks to see if the sandbox name is
	   already in use by this user.  It won't allow that
	   even with a different directory.  */
{
    ENTRY     * travel = currentsb;               /* ptr to existing sb name */

  while ( travel != NULL ) {
    if ( streq ( newsb, travel->value ))
      uquit ( ERROR, TRUE, "\tsandbox name, %s, already in use.\n", newsb );

    travel = travel->nextentry;
  } /* while */
}                                                               /* unique sb */


void
set_default_dir ( RC_CONT * rc_values, char * sb )

	/* This procedure sets the directory to the default value
	   or, if that does not exist, it prompts the user for
	   an entry.  It then checks to see if this is a legal
	   directory.  It loops for a legal entry. */
{
    char        line [ PATH_LEN ],                            /* misc string */
	      * line_ptr,
	      * ptr;
    BOOLEAN     legal_dir = FALSE;                           /* misc boolean */

  while ( ! legal_dir ) {
    if ( *(rc_values->def_sb_base) == NUL ) {
      ui_print ( VALWAYS,
		 "No default for sandbox directory and none entered.\n");
      ui_print ( VALWAYS, "Please enter the full path to the sandbox: " );
      gets ( line );
      line_ptr = line;
      ptr = nxtarg ( &line_ptr, WHITESPACE );
      strcpy ( rc_values->def_sb_base, ptr );
    } /* if */

    if ( *(rc_values->def_sb_base) != SLASH ) {
      ui_print ( VWARN, "Base directory must start with a '/'.\n" );
      rc_values->def_sb_base[0] = NUL;
    } /* if */

    else {
      ui_load ( DIR_OP, 1, rc_values->def_sb_base ); 

      if ( !( legal_dir = legal_sandbox_dir ( sb )))
	rc_values->def_sb_base[0] = NUL;
    } /* else */
  } /* while */
}                                                         /* set default dir */


void
set_backing ( char * proj_dir, char * def_build, char * sb_rc )

	/* This procedure prompts the user for the backing tree after
	   first listing the available builds.  The available builds
	   are the directories in the proj_dir; the default build is
	   the value of def_build. */
{
    DIR       * dir_ptr;                            /* points to a directory */
    struct      dirent * ds;               /* points to struct with dir list */
    char        line [ PATH_LEN ],                            /* misc string */
              * build,                                        /* misc string */
              * line_ptr;                             /* misc string pointer */

  while ( ! ui_is_set ( BACK_OP )) {
    if ( proj_dir == NULL ) {
      ui_print ( VALWAYS, "No known current builds to pick from.\n" );
      ui_print ( VCONT,
	     "Enter absolute path to backing tree or name from build list: " );
    } /* if */

    else {
      if (( dir_ptr = opendir ( proj_dir )) == NULL ) {
	ui_print ( VALWAYS, "No known current builds to pick from.\n" );
        ui_print ( VCONT,
	     "Enter absolute path to backing tree or name from build list: " );
      } /* if */

      else {
	ui_print ( VALWAYS,
        "Enter name of backing tree: from the known list or a complete path\n");
	ui_print ( VCONT, "or a name from the build list.\n" );
	ui_print ( VCONT, "Known current builds include:\n" );

	for ( ds = readdir ( dir_ptr ); ds != NULL; ds = readdir ( dir_ptr ))
	  if ( *ds->d_name != PERIOD )
	    ui_print ( VALWAYS, "   %s", ds->d_name );

	ui_print ( VALWAYS, "\nBacking tree? <%s> ", def_build );
        closedir ( dir_ptr );
      } /* else */
    } /* else */

    gets ( line );

    if ( *line == NUL || *line == NEWLINE ) {
      if ( def_build == NULL ) 
        continue;
      else 
	ui_load ( BACK_OP, 1, def_build );
    } else {
      line_ptr = line;
      build = nxtarg ( &line_ptr, WHITESPACE );

      if ( *build == NUL )
	ui_load ( BACK_OP, 1, def_build );
      else
	ui_load ( BACK_OP, 1, build );
    } /* else */


    legal_backing_tree ( proj_dir, sb_rc );
  } /* while */
}                                                             /* set backing */
  

void
set_default_machine ( RC_CONT * rc_values )

	/* This procedure fills the machine entry either by
	   copying it from the defaults or prompting the user.
	   If the answer is illegal, it continues to prompt
	   the user. */
{
    char        line [ PATH_LEN ],                            /* misc string */
	      * line_ptr,
	      * ptr;
    BOOLEAN     legal = FALSE;                               /* misc boolean */

  if ( *rc_values->def_machines == NUL ) {
    while ( ! legal ) {
      ui_print ( VALWAYS,
		 "Enter colon separated list of machines: <%s> ", DEF_MACH );
      gets ( line );
      line_ptr = line;
      ptr = nxtarg ( &line_ptr, WHITESPACE );

      if ( *ptr == NUL )
        ui_load ( M_OP, 1, DEF_MACH );
      else
        ui_load ( M_OP, 1, ptr );

      legal = legal_machine_names ();
    } /* while */
  } /* if */

  else
    ui_load ( M_OP, 1, rc_values->def_machines );
}                                                     /* set default machine */


void
set_tools_population ( RC_CONT * rc_values )

	/* This procedure prompts the user for population of the
	   tools area. */
{
    char        line [ PATH_LEN ];                            /* misc string */
    BOOLEAN     chosen = FALSE;                              /* misc boolean */

  while ( ! chosen ) {
    ui_print ( VALWAYS,
      "Populate tools with links or copies or leave backed? [ l | c | <b> ] " );
    line[0] = NUL;
    gets ( line );

    if ( *line == NUL ) {
      rc_values->tools = BACK_CH;
      chosen = TRUE;
    } /* if */

    else {
      rc_values->tools = line[0];

      if (( rc_values->tools != LINK_CH ) &&
	  ( rc_values->tools != COPY_CH ) &&
	  ( rc_values->tools != BACK_CH ))
        ui_print ( VWARN, "Entry must be 'l', 'c', or 'b'.\n" );
      else
	chosen = TRUE;
    } /* else */
  } /* while */
}                                                    /* set tools population */


void
set_obj_population ( RC_CONT * rc_values )

	/* This procedure prompts the user for population of the
	   object area.  It gets both the type of population and,
	   if it is not backed, the list of directories to populate. */
{
    char        line [ PATH_LEN ],                            /* misc string */
              * line_ptr,                                 /* misc string ptr */
              * arg;                                      /* misc string ptr */
    BOOLEAN     chosen = FALSE;                              /* misc boolean */

  while ( ! chosen ) {
    ui_print ( VALWAYS,
     "Populate objects with links or copies or leave backed? [ l | c | <b> ] ");
    line[0] = NUL;
    gets ( line );

    if ( *line == NUL ) {
      rc_values->objects = BACK_CH;
      chosen = TRUE;
    } /* if */

    else {
      rc_values->objects = line[0];

      if (( rc_values->objects != LINK_CH ) &&
	  ( rc_values->objects != COPY_CH ) &&
	  ( rc_values->objects != BACK_CH ))
        ui_print ( VWARN, "Entry must be 'l', 'c', or 'b'.\n" );
      else
	chosen = TRUE;
    } /* else */
  } /* while */

  if ( rc_values->objects != BACK_CH ) {
    *rc_values->obj_dirs = NUL;

    while ( *rc_values->obj_dirs == NUL ) {
      ui_print ( VALWAYS,
       "Enter a colon separated list of the object directories to populate\n" );
      ui_print ( VALWAYS, "each beginning with '/'.  '/' can be used " );
      ui_print ( VALWAYS, "to indicate all. <NO DEFAULT> " );
      gets ( line );
      line_ptr = line;
      arg = nxtarg ( &line_ptr, WHITESPACE );

      if ( check_colon_line ( arg ))
	strcpy ( rc_values->obj_dirs, arg );
      else
	*rc_values->obj_dirs = NUL;
    } /* while */
  } /* if */
}                                                      /* set obj population */


void
set_src_population ( RC_CONT * rc_values )

	/* This procedure prompts the user for population of the
	   source area.  It gets both the type of population and,
	   if it is not backed, the list of directories to populate. */
{
    char        line [ PATH_LEN ],                            /* misc string */
              * line_ptr,                                 /* misc string ptr */
              * arg;                                      /* misc string ptr */
    BOOLEAN     chosen = FALSE;                              /* misc boolean */

  while ( ! chosen ) {
    ui_print ( VALWAYS,
      "Populate source with links or copies or leave backed? [ l | c | <b> ] ");
    *line = NUL;
    gets ( line );

    if ( *line == NUL ) {
      rc_values->sources = BACK_CH;
      chosen = TRUE;
    } /* if */

    else {
      rc_values->sources = line[0];

      if (( rc_values->sources != LINK_CH ) &&
	  ( rc_values->sources != COPY_CH ) &&
	  ( rc_values->sources != BACK_CH ))
        ui_print ( VWARN, "Entry must be 'l', 'c', or 'b'.\n" );
      else
	chosen = TRUE;
    } /* else */
  } /* while */

  if ( rc_values->sources != BACK_CH ) {
    *rc_values->src_dirs = NUL;

    while ( *rc_values->src_dirs == NUL ) {
      ui_print ( VALWAYS,
	"Enter a colon separated list of the source directories to populate\n");
      ui_print ( VALWAYS, "each beginning with '/'.  '/' can be used " );
      ui_print ( VALWAYS, "to indicate all. <NO DEFAULT> " );
      gets ( line );
      line_ptr = line;
      arg = nxtarg ( &line_ptr, WHITESPACE );

      if ( check_colon_line ( arg ))
	strcpy ( rc_values->src_dirs, arg );
      else
	*rc_values->src_dirs = NUL;
    } /* while */
  } /* if */
}                                                      /* set src population */


void
build_sb_structure ( char * sb, char * rc_file, char * sbbase )

	/* This procedure makes the directories and files necessary
	   for a sandbox.  */
{
    char          mkconf [ PATH_LEN ],                        /* misc string */
                  sb_path [ PATH_LEN ];               /* path and name to sb */
    char rc_dir [MAXPATHLEN];

  concat ( sb_path, PATH_LEN, sbbase, "/", sb, NULL );

  if ( ui_is_info ()) {
    ui_print ( VALWAYS, "Would have created directory: %s.\n", sb_path );
    return;
  } /* if */

  if ( ! ui_is_set ( UPGRADE_OP ) ) {
    if ( mkdir ( sb_path, MODE ) == ERROR ) {
      remove_sb ( sb, rc_file, sbbase );
      uquit ( ERROR, FALSE, "could not create sandbox %s.\n", sb_path );
    } /* if */
  } /* if */
  if ( chdir ( sb_path ) == ERROR ) {
    remove_sb ( sb, rc_file, sbbase );
    uquit ( ERROR, FALSE, "\tcould not change directories to %s.\n", sb_path );
  } /* if */

  ui_print ( VDETAIL, "Successfully created new sandbox dir %s.\n", sb_path );
  if ( ui_is_set ( UPGRADE_OP ) ) {
    unlink ( LINK_DIR );
  } /* if */
  if ( symlink ( ui_arg_value ( BACK_OP, 1, 1 ), LINK_DIR ) == ERROR ) {
    remove_sb ( sb, rc_file, sbbase );
    uquit ( ERROR, FALSE, "could not create backing tree link to: %s.\n",
		           ui_arg_value ( BACK_OP, 1, 1 ));
  } /* if */
  if ( ! ui_is_set ( UPGRADE_OP ) ) {

    if (( mkdir ( SRC_DIR, MODE ) == ERROR ) ||
        ( mkdir ( RC_DIR, MODE ) == ERROR ) ||
        ( mkdir ( TOOL_DIR, MODE ) == ERROR )) {
      remove_sb ( sb, rc_file, sbbase );
      uquit ( ERROR, FALSE,
  	      "could not create sandbox directories:\n %s, %s, %s.\n",
  	      SRC_DIR, RC_DIR, TOOL_DIR );
    } /* if */
    ui_print ( VDETAIL, "Successfully created new dirs:%s, %s, %s.\n",
  		       SRC_DIR, RC_DIR, TOOL_DIR );
    if ( ode_build_env )
      if (( mkdir ( OBJ_DIR, MODE ) == ERROR ) ||
          ( mkdir ( EXP_DIR, MODE ) == ERROR ) ) {
        remove_sb ( sb, rc_file, sbbase );
        uquit ( ERROR, FALSE,
    	      "could not create sandbox directories:\n %s, %s.\n",
    	      OBJ_DIR, EXP_DIR );
    } /* if */

    ui_print ( VDETAIL, "Successfully created new dirs:%s, %s.\n",
  		       OBJ_DIR, EXP_DIR );

    concat ( mkconf, PATH_LEN, "../", LINK_DIR, "/", MKCONF_LINK, NULL );

    if ( ode_build_env ) {
      if ( symlink ( mkconf, MKCONF_LINK ) == ERROR ) {
        remove_sb ( sb, rc_file, sbbase );
        uquit ( ERROR, FALSE, "could not create link, %s, to: %s.\n",
  		    	   MKCONF_LINK, mkconf );
      } /* if */

      ui_print ( VDETAIL, "Successfully created backing tree link to %s.\n",
    		       ui_arg_value ( BACK_OP, 1, 1 ));
      create_machine_sub_dirs ( sb, rc_file, sbbase, ui_arg_value ( M_OP, 1, 1 ));
      ui_print ( VDETAIL, "Created new machine dirs %s.\n",
    		       ui_arg_value ( M_OP, 1, 1 ));
    } /* if */
  } /* if */
  concat ( rc_dir, sizeof(rc_dir), RC_DIR, "/", project, NULL );
  if ( mkdir ( rc_dir, MODE ) == ERROR ) {
    remove_sb ( sb, rc_file, sbbase );
    uquit ( ERROR, FALSE,
	      "could not create sandbox directory: %s\n", rc_dir );
  } /* if */
  ui_print ( VDETAIL, "Successfully created new dir:%s.\n", rc_dir );
}                                                      /* build sb structure */


void
create_machine_sub_dirs ( char * sb, char * rc_file, char * sbbase,
                          char * machines )

	/* This procedure attempts to create all the machine dependent
	   directories under OBJ.  It expects a colon separated list
	   of machines.  */
{
    char          copy [ PATH_LEN ],        /* holds edited copy of machines */
                  tpath [ PATH_LEN ],                /* path to create tools */
                  opath [ PATH_LEN ],                     /* path to objects */
                  epath [ PATH_LEN ],                     /* path to exports */
              	* list,                            /* points to each machine */
              	* line_ptr;                        /* points to each machine */

  strcpy ( copy, machines );
  line_ptr = copy;

  do {
    list = nxtarg ( &line_ptr, ":" );
    concat ( tpath, PATH_LEN, TOOL_DIR, "/", list, NULL );
    concat ( opath, PATH_LEN, OBJ_DIR, "/", list, NULL );
    concat ( epath, PATH_LEN, EXP_DIR, "/", list, NULL );

    if ( mkdir ( tpath, MODE ) == ERROR ) {
      remove_sb ( sb, rc_file, sbbase );
      uquit ( ERROR, FALSE, "\tcould not make directory %s.\n", tpath );
    } /* if */

    if ( mkdir ( opath, MODE ) == ERROR ) {
      remove_sb ( sb, rc_file, sbbase );
      uquit ( ERROR, FALSE, "\tcould not make directory %s.\n", opath );
    } /* if */

    if ( mkdir ( epath, MODE ) == ERROR ) {
      remove_sb ( sb, rc_file, sbbase );
      uquit ( ERROR, FALSE, "\tcould not make directory %s.\n", epath );
    } /* if */
  } while ( *line_ptr != NUL );
}                                                 /* create machine sub dirs */

void
create_user_rc_file ( RC_CONT * rc, char * sb, char * rc_file )

	/* This procedure creates a new rc file from the information
	   which the user has put into this sandbox. */
{
    FILE      * ptr_file;                                  /* ptr to rc file */

  if ( ui_is_info ())
    ui_print ( VALWAYS, "Would have created new user rc file: %s\n", rc_file );
  else
    ui_print ( VDETAIL, "Creating new user rc file: %s.\n", rc_file );

  strcpy ( rc->default_sb, sb );
  if ( ode_build_env ) {
    strcpy ( rc->def_machines, ui_arg_value ( M_OP, 1, 1 ));
  } /* if */
  strcpy ( rc->def_sb_base, ui_arg_value ( DIR_OP, 1, 1 ));

  if ( ui_ver_level () >= VDETAIL )
    print_out_rc_values ( rc );

  if ( ui_is_info ())
    return;

  if (( ptr_file = fopen ( rc_file, WRITE )) == NULL )
    uquit ( ERROR, FALSE, "\tcannot create new user rc file: %s.\n", rc_file );

  fprintf ( ptr_file, "\t# sandbox rc file created by %s\n", progname );
  fprintf ( ptr_file, "\n	# default sandbox\n" );
  fprintf ( ptr_file, "%s %s\n\n", DEFAULT, rc->default_sb );
  fprintf ( ptr_file, "\t# base directories to sandboxes\n" );
  fprintf ( ptr_file, "%s * %s\n\n", BASE, rc->def_sb_base );
  fprintf ( ptr_file, "\t# list of sandboxes\n" );
  fprintf ( ptr_file, "%s %s\n\n", SB, ui_entry_value ( ARGS_OP, 1 ));
  fprintf ( ptr_file, "\t# mksb config specific\n" );
  fprintf ( ptr_file, "%s %s %s\n", progname, DIR_OP,
		        ui_arg_value ( DIR_OP, 1, 1 ));
  if ( ode_build_env ) {
    fprintf ( ptr_file, "%s %s %s\n", progname, M_OP, rc->def_machines );
    fprintf ( ptr_file, "%s %s %c\n", progname, TOOLS_OP, rc->tools );
    fprintf ( ptr_file, "%s %s %c %s\n", progname, OBJ_OP, rc->objects,
  				       rc->obj_dirs );
  } /* if */
  fprintf ( ptr_file, "%s %s %c %s\n", progname, SRC_OP, rc->sources,
				       rc->src_dirs );
  fclose ( ptr_file );
}                                                     /* create user rc file */



void
update_user_rc_file ( char * sb, char * rc, char * sbrc )

	/* This procedure writes any new information into the
	   rc file or, if the rc file didn't exist, it creates
	   a new one. */
{
    FILE      	* ptr_file,                                /* ptr to rc file */
              	* tmp_file=NULL;                       /* ptr to tmp rc file */
    char      	* word,                                       /* misc string */
                  line [ PATH_LEN ],                          /* misc string */
                  line_copy [ PATH_LEN ],                     /* misc string */
                  tmp_rc [ PATH_LEN ],                        /* misc string */
                  new_base_dir [ PATH_LEN ],    /* to hold new base dir line */
              	* line_ptr,                           /* misc string pointer */
              	* dir;                             /* holds sandbox base dir */
    BOOLEAN       default_in = FALSE,                  /* default sb boolean */
                  base_dir_in,                       /* new base dir boolean */
                  sb_name_in = FALSE;                     /* sb name boolean */

  ui_print ( VDEBUG, "Updating rc file: %s.\n", rc );

  if (( ptr_file = fopen ( rc, READ )) == NULL )
    uquit ( ERROR, FALSE, "\tcannot read user's rc file %s.\n", rc );

  dir = ui_arg_value ( DIR_OP, 1, 1 );

  if ( ! ui_is_info ())
    tmp_file = create_tmp_file ( rc, tmp_rc );

  ui_print ( VDEBUG, "s: %s d: %s sbrc: %s rc: %s \n", sb, dir, sbrc, rc );
  base_dir_in = ( current_sb ( &sb, &dir, &sbrc, &rc ) == OK );

  if ( ! base_dir_in )
    concat ( new_base_dir, PATH_LEN, BASE, " ", sb, " ", dir, NULL );

  while (( line_ptr = fgets ( line, PATH_LEN, ptr_file )) != NULL ) {
    strcpy ( line_copy, line );
    line_ptr = line_copy;
    word = nxtarg ( &line_ptr, WHITESPACE );

    if ( streq ( word, DEFAULT )) {
      if ( ! ui_is_set ( DEF_OP )) {
        if ( ! ui_is_info ())
          fputs ( line, tmp_file );
	continue;
      } /* if */

      if ( default_in )
	continue;

      if ( ! ui_is_info ())
        fprintf ( tmp_file, "%s %s\n\n", DEFAULT, sb );

      default_in = TRUE;
      ui_print ( VDEBUG, "Making default sb, %s, in user's rc file.\n", sb );
      continue;
    } /* if */

    if (( streq ( word, BASE )) && ( ! base_dir_in )) {
      if ( ! ui_is_info ())
        fprintf ( tmp_file, "%s\n", new_base_dir );

      base_dir_in = TRUE;
      ui_print ( VDEBUG, "Adding base sandbox directory to user's rc file:\n" );
      ui_print ( VCONT, "%s.\n", new_base_dir );
    } /* if */

    else if (( streq ( word, SB )) && ( ! sb_name_in )) {
      if ( ! ui_is_info () && ! ui_is_set ( UPGRADE_OP ) )
        fprintf ( tmp_file, "%s %s\n", SB, sb );

      sb_name_in = TRUE;
      ui_print ( VDEBUG, "Adding new sandbox to user's rc file: %s.\n", sb );
    } /* else if */

    if ( ! ui_is_info ())
      fputs ( line, tmp_file );
  } /* while */

		  /* these last are for the case where there is no entry yet */
  if (( ui_is_set ( DEF_OP )) && ( ! default_in )) {
    if ( ! ui_is_info ())
      fprintf ( tmp_file, "%s %s\n\n", DEFAULT, sb );

    ui_print ( VDETAIL, "Making new, default sandbox, %s, in user's rc file.\n",
		         sb );
  } /* if */

  if ( !  base_dir_in ) {
    if ( !ui_is_info ())
      fprintf ( tmp_file, "%s\n", new_base_dir );

    ui_print ( VDEBUG, "Adding base sandbox directory to user's rc file:\n" );
    ui_print ( VCONT, "%s.\n", new_base_dir );
  } /* if */
      
  if ( ! sb_name_in && ! ui_is_set (UPGRADE_OP) ) {
     if ( ! ui_is_info ())
       fprintf ( tmp_file, "%s %s\n", SB, sb );

     ui_print ( VDETAIL, "Adding new sandbox to user's rc file: %s.\n", sb );
  } /* if */
      
  fclose ( ptr_file );

  if ( ! ui_is_info ()) {
    fclose ( tmp_file );
    rename ( tmp_rc, rc );
  } /* if */
}                                                     /* update user rc file */


void
create_default_set ( char * sb, char * rc_file, char * sb_rcfile )

	/* This procedure creates the default set for the sandbox.
	   It distinguishes between names which start with a capital
	   letter and those that don't by only preppending the user's
	   name to those that don't. */
{
    FILE      	* setptr;                                   /* original file */
    char          file_path [ PATH_LEN ],                     /* misc string */
		* sbbase = NULL,  /* sandbox base dir */
              	* set;                                 /* points to set name */
    char * set_name;

  if ( sb == NULL || rc_file == NULL || sb_rcfile == NULL ) {
    if ( current_sb ( &sb, &sbbase, &sb_rcfile, &rc_file ) == ERROR )
      uquit ( ERROR, FALSE, "Last try at getting sandbox env failed." );
  } /* if */

  if ( ui_is_set ( UPGRADE_OP ) ) {
    concat ( file_path, PATH_LEN, basedir, "/", sb, "/",
                   SET_RC, NULL );
  } else {
    concat ( file_path, PATH_LEN, ui_arg_value ( DIR_OP, 1, 1 ), "/", sb, "/",
                   SET_RC, NULL );
  } /* if */
  ui_print ( VDEBUG, "path for sets file is: %s.\n", file_path );
  set = ui_arg_value ( SET_OP, 1, 1 );

  sets_fullname ( set, env_user, &set_name );
  if ( ! ui_is_info ()) {
    if (( setptr = fopen ( file_path, WRITE )) == NULL ) {
      ui_print ( VWARN, "cannot open sets rc file, %s,\n", file_path );
      ui_print ( VCONT, "for writing.  No default set.\n" );
      return;
    } /* if */

    fprintf ( setptr, "%s %s\n", DEFAULT, set_name );

    fclose ( setptr );
  } /* if */
  sets_write ( sb, basedir, set_name, "." );
}                                                      /* create default set */



void
populate_sandbox ( RC_CONT * rc_values, char * sb_name, char * rc_file,
                   char * sb_rcfile )

	/* This procedure populates the tools, object, and
	   source areas per the user's request. */
{
    char          copy [ PATH_LEN ],        /* holds edited copy of dir list */
                  tsubdir [ PATH_LEN ],                  /* sub dir to tools */
                  osubdir [ PATH_LEN ],                /* sub dir to objects */
                  srcpath [ PATH_LEN ],               /* path of src to link */
              	* list,                          /* points to each directory */
              	* copy_ptr;                        /* points to each machine */
  
  copy_ptr = ui_arg_value ( M_OP, 1, 1 );          /* do tools and objs */

  do {                                    /* do a pass for each machine type */
    list = nxtarg ( &copy_ptr, ":" );
    concat ( tsubdir, PATH_LEN, "/", TOOL_DIR, "/", list, NULL );
    concat ( osubdir, PATH_LEN, "/", OBJ_DIR, "/", list, NULL );
    tools_obj_run_through ( sb_name, rc_file, sb_rcfile, tsubdir, osubdir,
			    rc_values );
  } while ( *copy_ptr != NUL );

  if ( rc_values->sources == BACK_CH )                     /* do sources now */
    return;

  strcpy ( copy, rc_values->src_dirs );       /* don't want to ruin original */
  copy_ptr = copy;                              /* copy can't move, list can */

  do {                                /* do a pass for each source directory */
    list = nxtarg ( &copy_ptr, ":" );
    concat ( srcpath, PATH_LEN, "/", SRC_DIR, list, NULL );

    if ( rc_values->sources == COPY_CH )
      create_local_files ( sb_name, rc_file, sb_rcfile, srcpath, TRUE );
    else if ( rc_values->sources == LINK_CH )
      create_local_files ( sb_name, rc_file, sb_rcfile, srcpath, FALSE );
  } while ( *copy_ptr != NUL );
}                                                        /* populate sandbox */


void
tools_obj_run_through ( char * sb_name, char * rc_file, char * sb_rcfile,
                        char tsubdir [], char osubdir [], RC_CONT * rc_values )

	/* This procedure creates the various run throughs for
	   mklinks for tools and for each machine type. */

{
    char        copy [ PATH_LEN ],          /* holds edited copy of dir list */
              * list,                            /* points to each directory */
              * copy_ptr,                          /* points to each machine */
                objpath [ PATH_LEN ];                 /* path of obj to link */

  if ( rc_values->tools == COPY_CH )
    create_local_files ( sb_name, rc_file, sb_rcfile, tsubdir, TRUE );
  else if ( rc_values->tools == LINK_CH )
    create_local_files ( sb_name, rc_file, sb_rcfile, tsubdir, FALSE );

  if ( rc_values->objects == BACK_CH )
    return;

  strcpy ( copy, rc_values->obj_dirs );       /* don't want to ruin original */
  copy_ptr = copy;                              /* copy can't move, list can */

  do {
    list = nxtarg ( &copy_ptr, ":" );
    concat ( objpath, PATH_LEN, osubdir, "/", list, NULL );

    if ( rc_values->objects == COPY_CH )
      create_local_files ( sb_name, rc_file, sb_rcfile, objpath, TRUE );
    else if ( rc_values->objects == LINK_CH )
      create_local_files ( sb_name, rc_file, sb_rcfile, objpath, FALSE );

  } while ( *copy_ptr != NUL );
}                                                   /* tools obj run through */


void
create_local_files ( char * sb_name, char * rc_file, char * sb_rcfile,
                     char * directory, BOOLEAN copy )

	/* This procedure does the call to mklinks to generate
	   the local copies of the files.  It uses copy to
	   determine if the files should be copied or linked. */

{
  ui_print ( VDETAIL, "%s directory into sandbox:\n",
		       copy ? "Copying" : "Linking" );
  switch ( fork ()) {
    case ERROR: ui_print ( VFATAL, "fork failed at mklinks.\n" );
		break;

    case CHILD:
      if ( ! ui_is_info ()) {
	if ( copy ) {
          if ( ui_is_auto ())
	    execlp ( MKLINKS, MKLINKS, COPY_OP, SB_OP, sb_name, RC_OP,
		     rc_file, ui_ver_switch (), AUTO_OP,
		     directory, NULL );
          else
	    execlp ( MKLINKS, MKLINKS, COPY_OP, SB_OP, sb_name, RC_OP, rc_file,
		     ui_ver_switch (), directory, NULL );
	} /* if */

	else {
          if ( ui_is_auto ())
	    execlp ( MKLINKS, MKLINKS, SB_OP, sb_name, RC_OP, rc_file,
	             ui_ver_switch (), AUTO_OP, directory,
		     NULL );
          else
	    execlp ( MKLINKS, MKLINKS, SB_OP, sb_name, RC_OP, rc_file,
		     ui_ver_switch (), directory, NULL );
	} /* else */

        uquit ( ERROR, FALSE, "returned from execlp of: %s.\n", MKLINKS );
      } /* if */

      else
        ui_print ( VALWAYS, "mklinks %s %s %s %s %s %s %s %s %s %s\n",
		   copy ? COPY_OP : "", SB_OP, sb_name, RC_OP, rc_file,
		   ui_ver_switch (),
		   ui_is_auto () ? AUTO_OP : "", directory );
      break;

    default :   wait (( int * ) 0 );
	        break;
  } /* switch */
}                                                      /* create local files */




void print_usage (void)

	/* This procedure prints the usages for mksb. */

{
  printf ( "USAGE:\n" );
  printf ( "%s [-back <backing-tree>] [-dir <sandbox-dir>] [-m <machine>[:<machine>]*]\n", progname );
  printf ( "     [-def] [sb_opts] [ODE opts] [populate_opts] sandbox\n" );
  printf ( "       -back <backing-tree>: back sandbox with backing tree\n" );
  printf ( "       -dir <sandbox-dir>: directory to make sandbox in\n" );
  printf ( "       -m <machine>: colon separated list of machines to set up\n");
  printf ( "       -def: make new sandbox default sandbox\n" );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  printf ( "     populate_opts:\n" );
  printf ( "       -tools <mode>: populate tools area\n" );
  printf ( "         mode: 'c' copy; 'l' link\n" );
  printf ( "       -obj <mode> <dirs>: populate object area\n" );
  printf ( "         dirs: colon separated list of directories to populate\n" );
  printf ( "       -src <mode> <dirs>: populate source area\n" );
  printf ( "     sandbox: name of sandbox to create\n\n" );
  printf ( "%s -list\n", progname );
  printf ( "%s -undo sandbox\n", progname );
  ui_print ( VNORMAL, "%s %s\n", progname, USAGE_VER_USAGE );
}                                                             /* print usage */
