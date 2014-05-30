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
 * $Log: bstat.c,v $
 * Revision 1.8.16.4  1994/01/31  20:13:09  damon
 * 	CR 1000. A curly brace was missing
 * 	[1994/01/31  20:13:02  damon]
 *
 * Revision 1.8.16.3  1994/01/31  19:48:36  damon
 * 	CR 1000. Complain if no ancestor found
 * 	[1994/01/31  19:43:28  damon]
 * 
 * Revision 1.8.16.2  1994/01/04  22:29:16  marty
 * 	CR # 966 - bstat now exits of sci_init() returns an error.
 * 	[1994/01/04  22:29:01  marty]
 * 
 * Revision 1.8.16.1  1993/12/02  21:10:22  damon
 * 	CR 880. Call sci_ancestry_list() prior to sci_ancestor_list()
 * 	[1993/12/02  21:09:14  damon]
 * 
 * Revision 1.8.14.4  1993/11/03  22:02:42  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  22:02:33  damon]
 * 
 * Revision 1.8.14.3  1993/10/28  13:32:01  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:14  damon]
 * 
 * Revision 1.8.14.2  1993/10/20  18:51:53  damon
 * 	CR 744. Added -a to usage message
 * 	[1993/10/20  18:51:47  damon]
 * 
 * Revision 1.8.14.1  1993/10/19  20:16:44  damon
 * 	CR 744. Updated usage message
 * 	[1993/10/19  20:16:36  damon]
 * 
 * Revision 1.8.12.1  1993/10/05  15:36:46  damon
 * 	CR 662. Added -a option for printing ancestor revs
 * 	[1993/10/05  15:36:35  damon]
 * 
 * Revision 1.8.10.13  1993/05/27  18:48:30  marty
 * 	CR # 558 - type cast for rios_aix
 * 	[1993/05/27  18:48:22  marty]
 * 
 * Revision 1.8.10.12  1993/05/12  21:14:52  marty
 * 	CR # 516 - bstat with now arguments now searches the set as well
 * 	as the backing tree for a revision.  (i.e. bstat Makefile now returns
 * 	a revision if Makefile is not in the current set).
 * 	[1993/05/12  21:14:39  marty]
 * 
 * Revision 1.8.10.11  1993/04/30  15:02:07  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/30  15:01:57  damon]
 * 
 * Revision 1.8.10.10  1993/04/29  17:35:58  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  17:35:45  marty]
 * 
 * Revision 1.8.10.9  1993/04/26  18:26:58  marty
 * 	Remove extranious output.
 * 	[1993/04/26  18:26:30  marty]
 * 
 * Revision 1.8.10.8  1993/04/20  21:39:46  marty
 * 	Remove genfiles() for now
 * 	[1993/04/20  21:39:36  marty]
 * 
 * Revision 1.8.10.7  1993/04/20  21:37:32  marty
 * 	Added include files ode/interface.h and stdio.h
 * 	[1993/04/20  21:37:21  marty]
 * 
 * Revision 1.8.10.6  1993/03/29  17:59:51  marty
 * 	Added generation of file list from the backing tree.
 * 	[1993/03/29  17:58:38  marty]
 * 
 * Revision 1.8.10.5  1993/03/26  18:30:25  marty
 * 	Allow bstat to generate the list of files from the
 * 	backing tree
 * 	[1993/03/26  18:30:07  marty]
 * 
 * Revision 1.8.10.4  1993/03/25  20:35:53  marty
 * 	Added support for fast revision lokkup of large groups of files.
 * 	[1993/03/25  20:34:53  marty]
 * 
 * Revision 1.8.10.3  1993/03/18  18:23:23  marty
 * 	Convert bstat to new client/server model.  Put all the work on the server.
 * 	[1993/03/18  18:19:48  marty]
 * 
 * Revision 1.8.10.2  1993/02/25  16:08:32  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:08:12  marty]
 * 
 * Revision 1.8.5.11  1992/12/03  19:04:00  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:33:57  damon]
 * 
 * Revision 1.8.5.10  1992/11/25  17:43:14  damon
 * 	CR 341. Closer to old behaviour. Changed -latest to -b
 * 	[1992/11/25  17:42:30  damon]
 * 
 * Revision 1.8.5.9  1992/11/23  19:37:52  damon
 * 	CR 339. Added -r option code
 * 	[1992/11/23  19:37:18  damon]
 * 
 * Revision 1.8.5.8  1992/11/12  18:45:11  damon
 * 	CR 329. Changed PATH_MAX to MAXPATHLEN and include param.h
 * 	[1992/11/12  18:44:22  damon]
 * 
 * Revision 1.8.5.7  1992/09/24  18:57:57  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:16:24  gm]
 * 
 * Revision 1.8.5.6  1992/09/17  18:03:14  damon
 * 	CR 238. Adjusted call to sci_init
 * 	[1992/09/17  18:02:58  damon]
 * 
 * Revision 1.8.5.5  1992/08/20  18:38:55  damon
 * 	CR 238. Fixed problem with creating list of files
 * 	[1992/08/20  18:38:35  damon]
 * 
 * Revision 1.8.5.4  1992/08/05  19:25:06  damon
 * 	Converted to use sci_rcs
 * 	[1992/08/05  19:24:49  damon]
 * 
 * Revision 1.8.5.3  1992/07/31  17:37:23  damon
 * 	Moved from bin/bcs
 * 	[1992/07/31  17:35:39  damon]
 * 
 * Revision 1.8.5.2  1992/06/04  23:22:21  damon
 * 	Synched with 2.1.1
 * 	[1992/06/04  23:15:21  damon]
 * 
 * Revision 1.8.2.2  1992/03/25  22:45:02  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  20:12:34  damon]
 * 
 * Revision 1.8  1991/12/05  20:40:07  devrcs
 * 	Fix for bug #54.  Error messages provided for case of bad revision
 * 	number provided and case of no branch for set.
 * 	[91/07/26  15:32:52  zeliff]
 * 
 * 	added print_revision() and stub print_usage()
 * 	[91/06/03  15:35:55  ezf]
 * 
 * 	Added support for odedefs.h
 * 	[91/05/28  13:52:10  damon]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  18:35:59  gm]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:25:07  randyb]
 * 
 * Revision 1.7  90/10/07  21:49:33  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:02:20  gm]
 * 
 * Revision 1.6  90/07/17  12:33:46  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:29:08  gm]
 * 
 * Revision 1.5  90/07/06  00:42:59  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:28:51  gm]
 * 
 * Revision 1.4  90/05/24  23:11:24  devrcs
 * 	Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.3  90/01/18  08:50:06  gm
 * 	Added support for "-R" option.
 * 	[90/01/07            gm]
 * 
 * Revision 1.2  90/01/02  19:59:08  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:47:11  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 2.4  89/06/18  17:33:40  gm0w
 * 	Updated to use new diag routine and to always print filename
 * 	of command target.
 * 	[89/06/18            gm0w]
 * 
 * Revision 2.3  89/02/05  16:05:20  gm0w
 * 	Renamed latest_private_rcs_file to just rcs_file.
 * 	[89/02/04            gm0w]
 * 
 * Revision 2.2  89/01/29  13:10:33  gm0w
 * 	Created.
 * 	[89/01/29            gm0w]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: bstat.c,v $ $Revision: 1.8.16.4 $ $Date: 1994/01/31 20:13:09 $";

#include <limits.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>
#include <ode/sci_client.h>
#include <ode/util.h>
#include <string.h>
#include <sys/param.h>
#include <stdio.h>
#include <unistd.h>

#define CHANGED_OP	"-changed"
#define SAVED_OP	"-saved"
#define REVISION_OP	"-r"
#define RCSFILE_OP	"-R"
#define GETREV_OP	"-V"
#define GEN_OP		"-gen"
#define BACKING_OP	"-b"
#define ANCESTOR_OP	"-a"

UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { REVISION_OP, 1, OVERWRITE,  1, 1, ARGS_OP },
  { RCSFILE_OP,      1, OVERWRITE,  0, 0, ARGS_OP },
  { GETREV_OP,      1, OVERWRITE,  0, 0, "" },
  { GEN_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { BACKING_OP,      1, OVERWRITE,  0, 0, "" },
  { ANCESTOR_OP,      1, OVERWRITE,  0, 0, "" },
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

const char *progname = "bstat";		/* program name */

STATIC
char * dash_r;
STATIC
BOOLEAN wantfilename;
STATIC
BOOLEAN wantrevision;
SCI_LIST file_set;

/*
 * PROTOTYPES
 */
void
initialize_switches(void);
void
handle_args( struct rcfile * contents, char * symbolic_name );
void
handle_switches (void);

char co_buf [ MAXPATHLEN ];
char curdir [ PATH_LEN ] ;
char *reldir;
int file_mode;

char * submit_set = NULL;

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
  char * coc_str;
  char * co_str = co_buf;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  initialize_switches ( );

  handle_switches ( );

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;
  rc_file = ui_arg_value ( RC_OP, 1, 1 );

  if ( (char *) getcwd ( curdir, sizeof(curdir) ) == NULL )
      uquit ( ERROR, FALSE, "getcwd failed\n"); 

  symbolic_name = set;
  if (sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set,
	     &sbrc_file, file_mode, FALSE ) != OK)
	exit(ERROR) ;
  get_rc_value ( "check_out_config", &coc_str, &contents, FALSE );
  co_buf [0] = '\0';
  rci_expand_include ( &co_str, coc_str );
  handle_args ( &contents, symbolic_name );
  exit ( 0 );
} /* end main */

void
initialize_switches(void)
{
    wantfilename = FALSE;
    wantrevision = FALSE;
}

void
handle_switches (void)
{
  BOOLEAN ch_flg, sv_flg;

  wantfilename = ui_is_set ( RCSFILE_OP );
  wantrevision = ui_is_set ( GETREV_OP );
  ch_flg = ui_is_set ( CHANGED_OP);
  sv_flg = ui_is_set ( SAVED_OP );
  if (ui_is_set (GEN_OP))
	reldir = strdup(ui_arg_value ( GEN_OP, 1, 1 ));
  file_mode = 0;
  if ( ch_flg && sv_flg ) {
    ui_print ( VWARN, "Cannot use the %s switch with the %s switch.\n",
               CHANGED_OP, SAVED_OP );
    exit ( ERROR );
  } /* if */
  if ( ch_flg )
    file_mode = 1;
  else if ( sv_flg )
    file_mode = 2;
  /* if */
 /*
  * If neither -R or -V are set, default to both revision and filename
  * being wanted.
  */
  if ( !wantfilename && !wantrevision ) {
    wantfilename = TRUE;
    wantrevision = TRUE;
  } /* if */
  if ( ui_is_set ( REVISION_OP ) ) {
    if ( ui_entry_cnt ( REVISION_OP ) > 1 ) {
      ui_print ( VFATAL, "Only one %s switch is allowed.\n", REVISION_OP );
      exit ( ERROR );
    } else
      dash_r = ui_arg_value ( REVISION_OP, 1, 1 );
    /* if */
  } /* if */
}

void
handle_args( struct rcfile * contents, char * symbolic_name )
{
  int ct;
  char * file;
  SCI_ELEM sci_ptr;
  BOOLEAN missing_revs;
  char full_co_str [MAXPATHLEN];
  char * coc_str;
  char * co_str = co_buf;

  if ( ui_is_set ( BACKING_OP ) ) {
    /* Search the backing tree for latest revision. */
    strcpy ( full_co_str, co_buf );
  } else if ( ui_is_set ( REVISION_OP ) ) {
    /* Search given a revision search string from command line. */ 
    strcpy ( full_co_str, ui_arg_value ( REVISION_OP, 1, 1 ) );
  } else
    /* Search current set, then the backing tree for a revision. */
    concat (full_co_str, sizeof(full_co_str), symbolic_name, ";", 
		co_buf, NULL);

  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct )) != NULL; ct++ ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */

  if ( ui_is_set ( ANCESTOR_OP ) ) {
    get_rc_value ( "check_out_config", &coc_str, contents, FALSE );
    co_buf [0] = '\0';
    rci_expand_include ( &co_str, coc_str );
    sci_lookup_user_rev_list ( file_set, symbolic_name, &missing_revs );
    if ( missing_revs ) {
      ui_print ( VWARN, "Unable to find user branch for all files.\n" );
      exit ( 1 );
    } /* if */
    sci_ancestry_list ( file_set );
    sci_lookup_merge_rev_list ( file_set, submit_set, co_buf );
    sci_ancestor_list ( file_set );
    for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
          sci_ptr = sci_next ( sci_ptr ) ) {
      if ( sci_ptr -> ver_ancestor == NULL ) {
        ui_print ( VALWAYS, "%s\tnone\n", sci_ptr -> name );
      } else {
        ui_print ( VALWAYS, "%s\t%s\n", sci_ptr -> name,
                            sci_ptr -> ver_ancestor );
      } /* if */
    } /* for */
    return;
  } /* if */

 /*
  * Don't have to look up revisions if only the file name is requested.
  */
 if (!wantrevision) { 
	for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
        	sci_ptr = sci_next ( sci_ptr ) ) {
               ui_print ( VALWAYS, "%s\n", sci_ptr -> name );
  	} 
    } else { 
         sci_client_latest_rev_list ( file_set, TRUE, 
		full_co_str, wantfilename) ; 
    }


} /* end handle_args */

/*
 * show invocation options
 */
void print_usage(void)
{
  printf ( "USAGE:\n" );
  printf ( "%s [sandbox opts] [ODE opts] [revision options] [file opts]\n", progname);
  ui_print ( VNORMAL, "%s\n", USAGE_SB_OPTS );
  printf ( "\trevision options:\n" );
  printf ( "\t  -r <revision>, -R, -V, -a\n" );
  ui_print ( VNORMAL, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VNORMAL, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VNORMAL, "%s %s\n", progname, USAGE_VER_USAGE );
}
