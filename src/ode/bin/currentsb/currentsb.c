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
 * $Log: currentsb.c,v $
 * Revision 1.8.8.3  1993/11/15  20:15:09  damon
 * 	CR 797. progname set to currentsb
 * 	[1993/11/15  20:15:02  damon]
 *
 * Revision 1.8.8.2  1993/11/04  00:03:17  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  00:02:47  damon]
 * 
 * Revision 1.8.8.1  1993/10/28  13:32:16  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:25  damon]
 * 
 * Revision 1.8.6.8  1993/05/28  13:45:21  marty
 * 	CR # 558 - Type casting for rios_aix
 * 	[1993/05/28  13:45:04  marty]
 * 
 * Revision 1.8.6.7  1993/05/10  19:09:52  marty
 * 	CR # 472 - Print warning message if a users sandbox environment can't be found.
 * 	[1993/05/10  19:09:39  marty]
 * 
 * Revision 1.8.6.6  1993/05/07  15:05:36  marty
 * 	Remove --EMPTY reference from usage output.
 * 	[1993/05/07  15:05:22  marty]
 * 
 * Revision 1.8.6.5  1993/05/07  15:01:13  marty
 * 	Print out berrter error messages when running currentsb outside of
 * 	a sandbox environment.
 * 	[1993/05/07  15:00:48  marty]
 * 
 * Revision 1.8.6.4  1993/04/29  16:38:27  marty
 * 	Prototype print_usage() CR 463
 * 	[1993/04/29  16:38:16  marty]
 * 
 * Revision 1.8.6.3  1993/04/26  17:47:41  marty
 * 	Fixed up print_usage message.
 * 	[1993/04/26  17:47:22  marty]
 * 
 * Revision 1.8.6.2  1993/04/15  17:31:46  marty
 * 	Add include files ode/interface.h, and stdio.h
 * 	[1993/04/15  17:31:20  marty]
 * 
 * Revision 1.8.4.7  1992/12/03  19:04:34  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:34:31  damon]
 * 
 * Revision 1.8.4.6  1992/10/14  20:47:41  damon
 * 	CR 288. Updated call to ui_init
 * 	[1992/10/14  20:45:06  damon]
 * 
 * Revision 1.8.4.5  1992/09/24  18:58:35  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:17:15  gm]
 * 
 * Revision 1.8.4.4  1992/06/16  23:08:48  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:45:58  damon]
 * 
 * Revision 1.8.4.3  1992/06/12  00:48:51  damon
 * 	Synched with 2.1.1
 * 	[1992/06/11  19:53:59  damon]
 * 
 * Revision 1.8.4.2  1992/05/11  21:42:25  marty
 * 	Remove training spaces in output.
 * 	[1992/05/11  21:41:58  marty]
 * 
 * Revision 1.8.2.2  1992/03/25  22:45:45  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  22:00:51  damon]
 * 
 * Revision 1.8  1991/12/05  20:41:14  devrcs
 * 	updated print_usage() and print_revision()
 * 	[91/06/11  12:04:35  ezf]
 * 
 * 	Changed sdm to ode; std_defs.h to odedefs.h
 * 	[91/01/11  10:40:24  randyb]
 * 
 * 	Made all Tools II changes.
 * 	Added new switch, -sbrc, to give the current sandbox rc file.
 * 	Changed -back to give the backing tree according to the sb rc file.
 * 	[90/12/28  11:22:45  randyb]
 * 
 * 	Style fixes
 * 	[90/11/07  13:20:53  randyb]
 * 
 * Revision 1.6  90/10/07  21:50:54  devrcs
 * 	Pre-OSF/1 fixes
 * 
 * $EndLog$
 */
/******************************************************************************
**                          Open Software Foundation                         **
**                              Cambridge, MA                                **
**                              Randy Barbano                                **
**                                May 1990                                   **
*******************************************************************************
**
**    Description:
**	This program prints out the information on the current sandbox
**	and current set including base dir, set dir, and backing tree.
**
**  Functions:
**    main (int, ** char) int
**      cmdline_syntax (** char, ** char) int
**      fill_data (** char, ** char, ** char, ** char, ** char, ** char) int
**      print_output (* char, * char, * char, * char, * char) int
**        cd_to_sbdir (* char) int
**    print_usage () int
**    print_revision () int
**
 */

static const char * rcsid =
 "$RCSfile: currentsb.c,v $ $Revision: 1.8.8.3 $ $Date: 1993/11/15 20:15:09 $";

#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/sandboxes.h>
#include <ode/sets.h>
#include <ode/util.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#  define  MAX_ARGS	7
#  define  SBRC_OP	"-sbrc"
#  define  INCLUDE	"include"

    UIINIT init [ ] = {                     /* initialize the user interface */
	   	{ SB_OP,     1, OVERWRITE, 0, 0, "" },
	   	{ SET_OP,    1, OVERWRITE, 0, 0, "" },
	   	{ DIR_OP,    1, OVERWRITE, 0, 0, "" },
	   	{ SETDIR_OP, 1, OVERWRITE, 0, 0, "" },
	   	{ SBRC_OP,   1, OVERWRITE, 0, 0, "" },
	   	{ BACK_OP,   1, OVERWRITE, 0, 0, "" },
	   	{ ALL_OP,    1, OVERWRITE, 0, 0, "" }
    };

const char 	* progname="currentsb";

/*
 * PROTOTYPES
 */
void
cmdline_syntax ( char ** sb_rcfile, char ** rc_file );
void
fill_data ( char ** sb, char ** sbbase, char ** sb_rcfile, char ** rc_file,
            char ** setname, char ** setdir );
void
print_output ( char * sb, char * sbbase, char * sb_rcfile, char * setname,
               char * setdir );
void
cd_to_sbdir ( char * sb_rcfile );

void
main ( int argc, char ** argv )

  	/* This function checks the command line arguments and makes
	   sure they are syntactically correct.  This is done using
	   the library function interface.  If this is correct, the
	   dependencies are checked.  Errors lead to usage messages.
	   If all is okay, the primary procedure is called. */
{
    char        * sb = NULL,                                 /* sandbox name */
                * sbbase = NULL,                          /* path to sandbox */
                * sb_rcfile,                         /* sandbox rc file name */
                * rc_file,                                   /* user rc file */
                * setname = NULL,                        /* full name of set */
                * setdir = NULL;                    /* path of set directory */

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  cmdline_syntax ( &sb_rcfile, &rc_file );
  fill_data ( &sb, &sbbase, &sb_rcfile, &rc_file, &setname, &setdir );
  print_output ( sb, sbbase, sb_rcfile, setname, setdir );
  exit ( 0 );
}                                                                    /* main */


void
cmdline_syntax ( char ** sb_rcfile, char ** rc_file )

	/* This procedure checks for relationships between the
	   command line arguments.  It assumes the syntax is
	   already correct.  */
{
  *rc_file = ui_arg_value ( RC_OP, 1, 1 );
  *sb_rcfile = NULL;

  if ( ui_is_set ( ALL_OP )) {
    ui_load ( SB_OP, 0 );
    ui_load ( SET_OP, 0 );
    ui_load ( DIR_OP, 0 );
    ui_load ( SETDIR_OP, 0 );
    ui_load ( SBRC_OP, 0 );
    ui_load ( BACK_OP, 0 );
  } /* if */

  else if (( ! ui_is_set ( SB_OP )) &&
	   ( ! ui_is_set ( SET_OP )) &&
	   ( ! ui_is_set ( DIR_OP )) &&
	   ( ! ui_is_set ( SETDIR_OP )) &&
           ( ! ui_is_set ( SBRC_OP )) &&
	   ( ! ui_is_set ( BACK_OP ))) {
    ui_load ( SB_OP, 0 );
    ui_load ( SET_OP, 0 );
  } /* else if */
}                                                          /* cmdline syntax */


void
fill_data ( char ** sb, char ** sbbase, char ** sb_rcfile, char ** rc_file,
            char ** setname, char ** setdir )

	/* This procedure fills in the values of the strings
	   which then can be printed out according to the 
	   command line instructions. */

{
  if ( current_sb ( sb, sbbase, sb_rcfile, rc_file) == ERROR) {
    ui_print ( VFATAL, "Could not establish sandbox environment.\n" );
    exit ( ERROR );
  } /* if */

  if ( current_set (  setname,  setdir,  sb, rc_file ) == ERROR ) {
     if ( *setname == NULL )
      uquit ( ERROR, FALSE, "\tSandbox, %s, has no default set.\n", *sb );
    else
      uquit ( ERROR, FALSE, "\tThe set, %s, is not part of the sandbox, %s.\n",
                               *setname, *sb );
  } /* if */

  if (in_sandbox() != TRUE)
	ui_print (VWARN, "You are not in a sandbox environment. Looking up default sandbox.\n");
  
}                                                               /* fill data */



void
print_output ( char * sb, char * sbbase, char * sb_rcfile, char * setname,
               char * setdir )

	/* This procedure prints out each type of info if it
	   is set.  It also does a change directory and prints
	   out the current directory to get the backing tree. */
{
    char        link_path [ PATH_LEN ],                /* holds path to link */
                defsbrc [ PATH_LEN ],                  /* default sb rc file */
                currentdir [ PATH_LEN ];                      /* misc string */
  int list = 0;

  if ( ui_is_set ( SB_OP )) {
    list=1;
    ui_print ( VALWAYS, "%s", sb );
  }

  if ( ui_is_set ( SET_OP )) {
    if (list) ui_print ( VALWAYS, " ");
    else list=1;
    ui_print ( VALWAYS, "%s", setname );
  }

  if ( ui_is_set ( DIR_OP )) {
    if (list) ui_print ( VALWAYS, " ");
    else list=1;
    ui_print ( VALWAYS, "%s", sbbase );
  }

  if ( ui_is_set ( SETDIR_OP )) {
    if (list) ui_print ( VALWAYS, " ");
    else list=1;
    ui_print ( VALWAYS, "%s", setdir );
  }

  if ( ui_is_set ( SBRC_OP )) {
    if (list) ui_print ( VALWAYS, " ");
    else list=1;
    ui_print ( VALWAYS, "%s", sb_rcfile );
  }

  if ( ui_is_set ( BACK_OP )) {
    concat ( defsbrc, PATH_LEN, sbbase, "/", sb, "/", LOCAL_RC, NULL );

    if ( streq ( sb_rcfile, defsbrc )) {
      concat ( link_path, PATH_LEN, sbbase, "/", sb, "/", LINK_DIR, NULL );

      if ( chdir ( link_path ) == ERROR )
	uquit ( ERROR, FALSE, "could not change directories to %s\n%s", link_path,
		"\t\t  to get backing tree.\n" );
    } /* if */

    else
      cd_to_sbdir ( sb_rcfile );

    if ( getcwd ( currentdir, sizeof(currentdir) ) == NUL )
      uquit ( ERROR, FALSE, "could not get current directories\n%s",
	      "\t\t  to get backing tree.\n" );

    if (list)  ui_print ( VALWAYS, " ");
    ui_print ( VALWAYS, "%s", currentdir );
  } /* if */

  ui_print ( VALWAYS, "\n" );
}                                                            /* print output */


void
cd_to_sbdir ( char * sb_rcfile )

	/*
	 *  Finds the directory indicated in the sb_rcfile and changes
	 *  to it.
	 */
{
    FILE        * sbptr;                                     /* file to read */
    char          line [ PATH_LEN ],                          /* misc string */
                * lineptr,                         /* allows parsing of line */
                * token;                             /* piece of parsed line */
    BOOLEAN       looking = TRUE;                            /* misc boolean */

  if (( sbptr = fopen ( sb_rcfile, READ )) == NULL )
    uquit ( ERROR, FALSE, "could not open sb rc file: %s,\n%s",
	      sb_rcfile, "\t\t  to read to get backing tree.\n" );

  while ( looking && ( lineptr = fgets ( line, PATH_LEN, sbptr )) != NULL ) {
    token = (char *) nxtarg ( &lineptr, WHITESPACE );

    if ( streq ( token, INCLUDE ))
      looking = FALSE;
  } /* while */

  if ( looking )
    uquit ( ERROR, FALSE, "could find %s line in sb rc file: %s,\n%s",
	    INCLUDE, sb_rcfile, "\t\t  to read to get backing tree.\n" );

  if (( token = ( char *) strrchr ( sb_rcfile, SLASH )) != NULL )
    *token = NUL; 

  if ( chdir ( sb_rcfile ) == ERROR )
    uquit ( ERROR, FALSE, "could not change directories to %s\n%s", sb_rcfile,
	    "\t\t  to get backing tree.\n" );

  if (( token = (char *) strrchr ( lineptr, SLASH )) != NULL ) {
    *token = NUL; 

    if (( token = (char *) strrchr ( lineptr, SLASH )) != NULL )
      *token = NUL; 
  } /* if */

  if ( chdir ( lineptr ) == ERROR )
    uquit ( ERROR, FALSE, "could not change directories to %s\n%s", lineptr,
	    "\t\t  to get backing tree.\n" );
}                                                             /* cd to sbdir */



void print_usage (void)

	/* This procedure prints the usages for currentsb. */

{
  printf ( "USAGE:\n" );
  printf ( "%s [-sb -set -dir -setdir -back -sbrc] [-all]\n", progname );
  printf ( "\t  -sb : list current sandbox\n" );
  printf ( "\t  -set : list current set\n" );
  printf ( "\t  -dir : list base directory of current sandbox\n" );
  printf ( "\t  -setdir : list default set directory of current set\n" );
  printf ( "\t  -sbrc : list sandbox rc file for current directory\n" );
  printf ( "\t  -back : list backing tree of current sandbox\n" );
  printf ( "\t  -all : list all the current information\n" );
  printf ( "\t    defaults to -sb and -set\n" );
  printf ( "\t  sandbox opts:\n" );
  printf ( "\t    -rc <user rc>, -sb_rc <sb rc>\n" );
  printf ( "%s [ -usage | -version ]\n", progname );
}                                                             /* print usage */
