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
 * $Log: blog.c,v $
 * Revision 1.8.14.4  1993/11/08  17:08:05  marty
 * 	CR # 776 - blog -h now gives header information regardless of whether
 * 	or not a users private branch exists.
 * 	[1993/11/08  17:01:26  marty]
 *
 * Revision 1.8.14.3  1993/11/03  21:55:26  marty
 * 	CR # 463 - Type cast sci_show_log_list_client()
 * 	[1993/11/03  21:55:06  marty]
 * 
 * Revision 1.8.14.2  1993/11/03  21:38:51  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  21:38:43  damon]
 * 
 * Revision 1.8.14.1  1993/10/28  13:31:56  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:10  damon]
 * 
 * Revision 1.8.12.1  1993/09/01  14:05:02  marty
 * 	CR # 644 - Clean out "-L, -R, and -l" options.  Also, add
 * 	"-A" (all_revs).
 * 	[1993/09/01  14:04:29  marty]
 * 
 * Revision 1.8.9.9  1993/05/27  18:44:50  marty
 * 	CR # 558 - type casting for rios_aix
 * 	[1993/05/27  18:44:43  marty]
 * 
 * Revision 1.8.9.8  1993/04/29  16:34:41  marty
 * 	Prototyping for print_usage(). CR # 463
 * 	[1993/04/29  16:34:28  marty]
 * 
 * Revision 1.8.9.7  1993/04/26  19:52:25  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/26  19:35:00  damon]
 * 
 * Revision 1.8.9.6  1993/04/16  20:31:57  damon
 * 	CR 421. Updated usage message for 2.3
 * 	[1993/04/16  20:31:45  damon]
 * 
 * Revision 1.8.9.5  1993/04/15  17:24:07  marty
 * 	Added ode/interface.h.
 * 	[1993/04/15  17:23:50  marty]
 * 
 * Revision 1.8.9.4  1993/03/04  21:50:41  damon
 * 	CR 436. Now calls sci_show_log_list_client
 * 	[1993/03/04  21:49:47  damon]
 * 
 * Revision 1.8.9.3  1993/02/25  16:31:14  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:30:54  marty]
 * 
 * Revision 1.8.9.2  1993/02/03  19:56:22  damon
 * 	CR 417. Adjusted sci_init call
 * 	[1993/02/03  19:51:22  damon]
 * 
 * Revision 1.8.4.13  1993/01/08  19:07:23  marty
 * 	Added explicit exit with zero error status.
 * 	[1993/01/08  19:00:33  marty]
 * 
 * Revision 1.8.4.12  1992/12/03  19:03:52  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:33:50  damon]
 * 
 * Revision 1.8.4.11  1992/11/25  19:58:06  damon
 * 	CR 331. Added -A switch to show all revisions
 * 	[1992/11/25  19:57:46  damon]
 * 
 * Revision 1.8.4.10  1992/11/12  18:45:08  damon
 * 	CR 329. Changed PATH_MAX to MAXPATHLEN and include param.h
 * 	[1992/11/12  18:44:17  damon]
 * 
 * Revision 1.8.4.9  1992/11/06  19:40:07  damon
 * 	CR 296. Removed extra definitions
 * 	[1992/11/06  19:39:08  damon]
 * 
 * Revision 1.8.4.8  1992/11/05  17:26:13  damon
 * 	CR 315. Updated usage message.
 * 	[1992/11/05  17:25:30  damon]
 * 
 * Revision 1.8.4.7  1992/11/02  20:57:19  damon
 * 	CR 300. sci_show_log_list handles problems better
 * 	[1992/11/02  20:55:53  damon]
 * 
 * Revision 1.8.4.6  1992/09/24  18:57:50  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:16:10  gm]
 * 
 * Revision 1.8.4.5  1992/09/17  18:01:22  damon
 * 	CR 236. Added some error checking.
 * 	[1992/09/17  18:00:16  damon]
 * 
 * Revision 1.8.4.4  1992/09/01  19:31:59  damon
 * 	CR 238. Synched with newer sci API
 * 	[1992/09/01  18:34:23  damon]
 * 
 * Revision 1.8.4.3  1992/08/05  22:11:54  damon
 * 	Converted to sci_rcs
 * 	[1992/08/05  22:10:51  damon]
 * 
 * Revision 1.8.4.2  1992/06/04  23:22:09  damon
 * 	Synched with 2.1.1
 * 	[1992/06/04  23:15:07  damon]
 * 
 * Revision 1.8.2.2  1992/03/25  22:44:50  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  20:12:25  damon]
 * 
 * Revision 1.8  1991/12/05  20:40:00  devrcs
 * 	Fix for bug where if no versions are taken out in the current set,
 * 	blog gave no information (bug #88).  Set revp to NULL if src_ctl_lookup
 * 	found no revision.
 * 	[91/10/29  09:15:06  rec]
 * 
 * 	Changed call to src_ctl_show_log to reflect changes in if_rcs.
 * 	This is to allow the new blog -i to emulate the old blog -i.
 * 	[91/08/30  13:04:17  damon]
 * 
 * 	Added support for the -l switch for rlog.  The -i switch also
 * 	translates to -l.
 * 	[91/08/27  14:57:23  rec]
 * 
 * 	Removed the -i switch which RCS 5.5 does not support.
 * 	[91/08/12  16:31:00  rec]
 * 
 * 	added print_revision() and stub print_usage()
 * 	[91/06/03  15:28:28  ezf]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  18:35:46  gm]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:24:51  randyb]
 * 
 * Revision 1.7  90/10/07  21:49:23  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:02:05  gm]
 * 
 * Revision 1.6  90/07/17  12:33:38  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:28:56  gm]
 * 
 * Revision 1.5  90/07/06  00:42:50  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:28:23  gm]
 * 
 * Revision 1.4  90/05/24  23:11:17  devrcs
 * 	Added support for -i switch to get information on locks.
 * 	[90/05/10            gm]
 * 
 * 	Added -L and -R switches.  Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.3  90/02/23  00:43:55  devrcs
 * 	Changed to not require a path exist to the target.
 * 	[90/02/17  11:48:45  gm]
 * 
 * Revision 1.2  90/01/02  19:59:06  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:47:02  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 2.4  89/06/18  17:33:29  gm0w
 * 	Updated to use new diag routine and to always print filename
 * 	of command target.
 * 	[89/06/18            gm0w]
 * 
 * Revision 2.3  89/02/05  16:04:52  gm0w
 * 	Renamed latest_private_rcs_file to just rcs_file.
 * 	[89/02/04            gm0w]
 * 
 * Revision 2.2  89/01/29  13:09:04  gm0w
 * 	Created.
 * 	[89/01/29            gm0w]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: blog.c,v $ $Revision: 1.8.14.4 $ $Date: 1993/11/08 17:08:05 $";

#include <limits.h>
#include <ode/errno.h>
#include <ode/public/error.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>
#include <ode/sci_client.h>
#include <string.h>
#include <sys/param.h>

const char * progname = "blog";

int file_mode;

BOOLEAN header;		/* -h flag  - header only */
BOOLEAN all_revs;	/* -A flag  - list all revisions */
BOOLEAN rev_op;		/* -r flag  - list specified branch */
BOOLEAN backing_op;	/* -b flag  - list whatever branch I'm backed by */

UIINIT init [] = {
  { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
  { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
  { HEADER_OP,      1, OVERWRITE,  0, 0, "" },
  { REVISION_OP, 1, OVERWRITE,  1, 1, ARGS_OP },
  { BACKING_OP,      1, OVERWRITE,  0, 0, "" },
  { ALL_REVS_OP,      1, OVERWRITE,  0, 0, "" },
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

char co_buf [ MAXPATHLEN ];

/*
 * PROTOTYPES
 */
void
handle_switches (void);
void
handle_args( struct rcfile * , char * );

void
main ( int argc, char ** argv )
{
  struct rcfile contents;
  char * sb_base = NULL,
       * sb = NULL,
       * sbrc_file = NULL,
       * rc_file = NULL,
       * symbolic_name = NULL,
       * set = NULL,
       * submit_set = NULL;
  char * coc_str;
  char * co_str = co_buf;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  handle_switches ();

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;
  rc_file = ui_arg_value ( RC_OP, 1, 1 );

  symbolic_name = set;
  sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set, &sbrc_file,
             file_mode, FALSE );
  if ( ui_is_set ( BACKING_OP ) ) {
    get_rc_value ( "check_out_config", &coc_str, &contents, FALSE );
    co_buf [0] = '\0';
    rci_expand_include ( &co_str, coc_str );
  } /* if */
  handle_args ( &contents, symbolic_name );
  exit(0);
} /* end main */

void
handle_switches (void)
{
  header = ui_is_set ( HEADER_OP );
  all_revs = ui_is_set ( ALL_REVS_OP );
  backing_op = ui_is_set ( BACKING_OP );
  rev_op = ui_is_set ( REVISION_OP );
  if ((header) && (all_revs)) {
	ui_print (VFATAL, "Cannot specify -h and -A options together.\n");
	exit (1);
  }
  if ((rev_op) && (all_revs)) {
	ui_print (VFATAL, "Cannot specify -r and -A options together.\n");
	exit (1);
  }
  if ((backing_op) && (all_revs)) {
	ui_print (VFATAL, "Cannot specify -b and -A options together.\n");
	exit (1);
  }
  if ((backing_op) && (rev_op)) {
	ui_print (VFATAL, "Cannot specify -b and -r options together.\n");
	exit (1);
  }
} /* end handle_switches */

void
handle_args( struct rcfile * contents, char * symbolic_name )
{
  SCI_LIST file_set;
  int ct;
  char * file;
  char * rev_str;
  ERR_LOG log;

  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct )) != NULL; ct++ ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */
  if ( header ) {
       /* Specifying '-h' implies the backing option. */
       rev_str = strdup ( co_buf );
  } else {
     if ( backing_op )
       rev_str = strdup ( co_buf );
     else if ( rev_op )
       rev_str = ui_arg_value ( REVISION_OP, 1, 1 );
     else
       rev_str = strdup ( symbolic_name);
     /* if */
  }
  log = (ERR_LOG) sci_show_log_list_client ( file_set, rev_str, 
				   all_revs, FALSE, header, FALSE, FALSE );
  if ( log != OE_OK )
    ui_print ( VALWAYS, "%s\n", err_str ( log ) );
  /* if */
} /* end handle_args */

/* show invocation options */
void print_usage(void)
{
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS, "%s [%s <rev> | -A | -h | -b ] [sandbox opts] [ODE opts] [file opts]\n", progname, REVISION_OP );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}

