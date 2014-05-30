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
 * $Log: sbinfo.c,v $
 * Revision 1.9.13.1  1993/11/19  18:27:03  damon
 * 	CR 806. Complain and exit if unable to find sandbox
 * 	[1993/11/19  18:26:02  damon]
 *
 * Revision 1.9.11.3  1993/11/04  21:32:50  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  21:32:26  damon]
 * 
 * Revision 1.9.11.2  1993/10/28  13:32:33  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:33  damon]
 * 
 * Revision 1.9.11.1  1993/10/06  23:27:59  damon
 * 	CR 697. Works correctly when in bottom most link of backing chain
 * 	[1993/10/06  23:27:42  damon]
 * 
 * Revision 1.9.9.1  1993/09/21  16:48:37  damon
 * 	CR 673. Read all sb.conf files in backing chain
 * 	[1993/09/21  16:48:04  damon]
 * 
 * Revision 1.9.7.6  1993/06/08  17:13:55  damon
 * 	CR 576. Now conditionally reads both Buildconf* and sc.conf
 * 	[1993/06/08  17:13:49  damon]
 * 
 * Revision 1.9.7.5  1993/05/28  15:51:06  marty
 * 	CR # 558 - for rios_aix build
 * 	[1993/05/28  15:50:54  marty]
 * 
 * Revision 1.9.7.4  1993/05/26  21:05:21  marty
 * 	Works outside a sandbox now.
 * 	[1993/05/26  20:56:22  marty]
 * 
 * Revision 1.9.7.3  1993/05/17  20:24:55  damon
 * 	CR 419. replaced calls to rc_file_field
 * 	[1993/05/17  20:24:42  damon]
 * 
 * Revision 1.9.7.2  1993/04/29  16:54:38  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:54:25  marty]
 * 
 * Revision 1.9.4.6  1992/12/03  19:08:22  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:31  damon]
 * 
 * Revision 1.9.4.5  1992/11/11  16:02:35  damon
 * 	CR 329. Added include of unistd.h
 * 	[1992/11/11  16:02:19  damon]
 * 
 * Revision 1.9.4.4  1992/10/14  20:48:05  damon
 * 	CR 288. Updated call to ui_init
 * 	[1992/10/14  20:45:23  damon]
 * 
 * Revision 1.9.4.3  1992/06/16  22:12:08  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:01:58  damon]
 * 
 * Revision 1.9.2.2  1992/03/25  22:47:13  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  22:24:39  damon]
 * 
 * Revision 1.9  1991/12/05  20:53:43  devrcs
 * 	Changed sdm to ode; std_defs.h to odedefs.h
 * 	[91/01/11  10:52:20  randyb]
 * 
 * 	Updated to Tools II specs including interface module
 * 	[90/12/31  11:51:06  randyb]
 * 
 * Revision 1.7  90/10/07  21:52:48  devrcs
 * 	Pre-OSF/1 changes
 * 
 * $EndLog$
 */
/******************************************************************************
**                          Open Software Foundation                         **
**                              Cambridge, MA                                **
**                               April 1990                                  **
*******************************************************************************
**
**  Description:
** 	This program prints out a description of the current sandbox
**	environment.
**
**  Functions:
**    main (int, * * char) int
**      print_sandbox (* char, * struct) int
**        print_envvar (* struct, int) int
**        print_field (* struct, * char, int) int
**    print_usage () int
 */

static const char * rcsid =
 "$RCSfile: sbinfo.c,v $ $Revision: 1.9.13.1 $ $Date: 1993/11/19 18:27:03 $";

#include <unistd.h>
#include <stdio.h>
#include <ode/builddata.h>
#include <ode/interface.h>
#include <ode/odedefs.h>
#include <ode/parse_rc_file.h>
#include <ode/project.h>
#include <ode/sandboxes.h>
#include <ode/sets.h>
#include <ode/util.h>
#include <sys/param.h>

#  define  MAX_ARGS	3

    UIINIT init [] = {                      /* initialize the user interface */
   		{ SB_OP,   1, 	      OVERWRITE, 1, 1, ARGS_OP },
   		{ SET_OP,   1, 	      OVERWRITE, 1, 1, ARGS_OP },
   		{ ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" }
    };

    const char * progname = "sbinfo";                     /* program's name */
    struct      rcfile   rcfile;      /* structure to hold rc file internals */

/*
 * PROTOTYPES
 */
void
print_sandbox ( char * sandbox, struct rcfile * rcfile_p );
void
print_envvar ( struct arg_list * var, int all );
void
print_field ( struct field * field_p, char * indent, int all );

void
main ( int argc, char ** argv )
	
	/*
	 * Establishes the environment and parses the arguments then
	 * calls the print routine.
	 */
{
    char        * sandbox,                                /* name of sandbox */
                * basedir = NULL,                /* sandbox's base directory */
                * sb_rcfile,                              /* sandbox rc file */
                * usr_rcfile;                              /* user's rc file */

  char * project;
  char * sub_project;
  char * dir;
  char * set;
  char * backing_project;
  char * backing_build;
  BOOLEAN ode_sc;
  BOOLEAN ode_build_env;
  struct rcfile sb_contents;
  char sc_file [MAXPATHLEN];

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  sandbox = ui_arg_value ( SB_OP, 1, 1 );
  sb_rcfile = NULL;
  usr_rcfile = ui_arg_value ( RC_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );

  if ( current_sb ( &sandbox, &basedir, &sb_rcfile, &usr_rcfile ) == ERROR ) {
    if ( sandbox == NULL ) {
      ui_print ( VWARN, "Could not find default sandbox.\n" );
    } else {
      ui_print ( VWARN, "Could not find sandbox %s.\n", sandbox );
    } /* if */
    exit (1);
  } /* if */
  if (ui_is_set ( SET_OP )) {
	current_set(&set, &dir, &sandbox, &usr_rcfile);
  } else {
  	if (sb_current_dir ( sandbox, basedir, &dir ) != TRUE)
		current_set(&set, &dir, &sandbox, &usr_rcfile);
  }
  if (dir == NULL)
	dir = (char *)".";
  prj_read ( sb_full_path ( basedir, sandbox ), dir, &project, &sub_project );
  sb_conf_read_chain ( &sb_contents, sb_full_path ( basedir, sandbox ), project,
                       sub_project );
  sb_conf_std ( &sb_contents, &backing_project, &backing_build, &ode_sc,
                &ode_build_env );
  if ( backing_build == NULL ) {
    backing_build = sb_full_path ( basedir, sandbox );
  } /* if */
  if ( sub_project == NULL ) {
    concat ( sc_file, sizeof (sc_file), backing_build, "/rc_files/", project,
                  "/sc.conf", NULL );
  } else {
    concat ( sc_file, sizeof (sc_file), backing_build, "/rc_files/", project,
                  "/", sub_project, "/sc.conf", NULL );
  } /* if */
  if ( ode_build_env ) {
    bld_conf_read ( sb_full_path ( basedir, sandbox ), project, &rcfile );
    if ( ode_sc ) {
      parse_rc_file ( sc_file, &rcfile );
    } /* if */
  } else {
    if ( ode_sc ) {
      init_rc_contents ( &rcfile,  sc_file );
    } /* if */
  } /* if */
  print_sandbox ( sandbox, &rcfile );
  exit ( OK );
}                                                                    /* main */


void
print_sandbox ( char * sandbox, struct rcfile * rcfile_p )

	/*
	 * Goes through the list of variables to print and has them
	 * printed.  Checks to see if all should be printed.
	 */
{
    struct 	field    * field_p;
    struct 	arg_list * args_p;
    char 	* indent;
    const char 	* spaces = "            ";
    int 	  ct;
    BOOLEAN 	  all = ! ui_is_set ( ARGS_OP );

  indent = (char *)(spaces + strlen ( spaces ));

  if ( all ) {
    ui_print ( VNORMAL, "Description of rc_file for %s sandbox:\n", sandbox );
    indent -= 4;

    if ( find_field ( rcfile_p, "setenv", &field_p, 0 ) == 0 ) {
      ui_print ( VNORMAL, "\nThe following environment variables were set:\n");
      for  ( args_p = field_p->args; args_p != NULL; args_p = args_p->next )
	print_envvar ( args_p, all );
    } 

    if ( find_field ( rcfile_p, "unsetenv", &field_p, 0 ) == 0 ) {
      ui_print ( VNORMAL,
		 "\nThe following environment variables were removed:\n" );
      for ( args_p = field_p->args; args_p != NULL; args_p = args_p->next )
	ui_print ( VNORMAL, "    ", args_p->tokens[0] );
    }
  } /* if */

  else if ( find_field ( rcfile_p, "setenv", &field_p, 0 ) == 0 ) {
    for ( args_p = field_p-> args; args_p != NULL; args_p = args_p-> next ) {
      for ( ct = 1; ct <= ui_entry_cnt ( ARGS_OP ); ct++ ) {
	if ( streq ( ui_entry_value ( ARGS_OP, ct ), args_p-> tokens [ 0 ] ))
	  break;
      } /* for */

      if ( ct > ui_entry_cnt ( ARGS_OP ))
	continue;

      print_envvar ( args_p, all );
    } /* for */
  } /* else if */

  if ( all )
    ui_print ( VNORMAL,
	       "\nThe following directives are defined in the rc file:\n" );

  for ( field_p = rcfile_p->list; field_p != NULL; field_p = field_p->next ) {
    if ( all ) {
      if ( streq ( field_p->name, "setenv" ))
	continue;
      if (streq ( field_p->name, "unsetenv" ))
	continue;
      print_field ( field_p, indent, all );
      continue;
    }

    for ( ct = 1; ct <= ui_entry_cnt ( ARGS_OP ); ct++ ) {
      if ( streq ( ui_entry_value ( ARGS_OP, ct ), field_p->name ))
	break;
    } /* for */

    if ( ct > ui_entry_cnt ( ARGS_OP ))
      continue;

    print_field ( field_p, indent, all );
  }
}                                                           /* print sandbox */


void
print_envvar ( struct arg_list * var, int all )

	/*
	 * Prints a piece of information if the environment variable
	 * is set.
	 */
{
    char 	* val;

  if ( var->ntokens != 1 )
    return;

  if (( val = (char *)getenv ( var->tokens[0] )) == NULL )
    return;

  if ( all )
    ui_print ( VALWAYS, "    %s=%s\n", var->tokens[0], val );
  else
    ui_print  ( VALWAYS, "%s\n", val );
}                                                            /* print envvar */


void
print_field ( struct field * field_p, char * indent, int all )

	/*
	 * Prints a piece of information
	 */
{
    struct 	arg_list * args_p;
    int 	  i;

  if (( args_p = field_p->args)->next == NULL ) {
    if ( args_p->ntokens == 0 ) {
      ui_print ( VALWAYS, "%s%s\n", indent, field_p->name );
      return;
    } /* if */

    ui_print ( VALWAYS, "%s%s%s%s", indent, all ? field_p->name : "",
	       		 all ? ": " : "", args_p->tokens[0]);

    for ( i = 1; i < args_p->ntokens; i++ )
      ui_print ( VALWAYS, " %s", args_p->tokens[i] );

    (void) putchar ('\n');
    return;
  } /* if */

  if ( all ) {
    ui_print ( VALWAYS, "%s%s:\n", indent, field_p->name );
    indent -= 4;
  } /* if */

  do {
    if ( args_p->ntokens == 0 ) {
      ui_print ( VALWAYS, "%s%s\n", indent, field_p->name );
      continue;
    } /* if */

    ui_print ( VALWAYS, "%s%s", indent, args_p->tokens[0] );

    for ( i = 1; i < args_p->ntokens; i++ )
	ui_print ( VALWAYS, " %s", args_p->tokens[i] );

    (void) putchar( NEWLINE );
    args_p = args_p->next;
  } while ( args_p != NULL );
}                                                             /* print field */



void print_usage (void)
	
	/*
	 * This procedure prints the usages for workon.
	 */

{
    printf ( "USAGE:\n" );
    printf ( "%s [ sb_opts ] [field(s)]\n", progname );
    printf ( "       field(s): specific variable to give the value of\n" );
    printf ( "       sb_opts:\n" );
    printf ( "\t-sb <sandbox>, -rc <user rc file>, -sb_rc <sb rc file>\n" );
    printf ( "%s -usage | -rev\n", progname );
}                                                             /* print usage */
