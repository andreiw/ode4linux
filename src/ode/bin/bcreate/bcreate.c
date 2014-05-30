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
 * $Log: bcreate.c,v $
 * Revision 1.15.17.3  1993/12/16  19:54:23  marty
 * 	CR # 724 - Add call to sci_copyright_init().
 * 	[1993/12/16  19:54:09  marty]
 *
 * Revision 1.15.17.2  1993/12/15  00:32:10  marty
 * 	CR # 902 - Check status of sci_init() return for errors.
 * 	[1993/12/15  00:31:58  marty]
 * 
 * Revision 1.15.17.1  1993/11/22  16:57:46  marty
 * 	CR # 848 - bcreate now recognizes "BIN" and "NONE".  Also, of
 * 	-auto is specified, it will not try to confirm non-standard comment leaders.
 * 	[1993/11/22  16:57:11  marty]
 * 
 * Revision 1.15.14.2  1993/11/03  20:40:03  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  20:37:52  damon]
 * 
 * Revision 1.15.14.1  1993/10/28  13:31:44  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:05  damon]
 * 
 * Revision 1.15.12.4  1993/09/29  14:30:01  root
 * 	rios porting errors
 * 	[1993/09/29  14:21:40  root]
 * 
 * Revision 1.15.12.3  1993/09/24  17:16:02  marty
 * 	CR # 685 - Now checks for "check_copyrights" in backing tree before copyright
 * 	name processing.
 * 	[1993/09/24  17:15:46  marty]
 * 
 * Revision 1.15.12.2  1993/09/23  14:29:12  damon
 * 	CR 656. Use raw copyrights instead of valid ones
 * 	[1993/09/23  14:22:34  damon]
 * 
 * Revision 1.15.12.1  1993/09/21  21:23:13  marty
 * 	Cr # 670 - bcreate now supports named copyrights
 * 	[1993/09/21  21:22:45  marty]
 * 
 * Revision 1.15.9.16  1993/06/04  18:44:57  damon
 * 	CR 559. Fixed logic problem with comment leader loop
 * 	[1993/06/02  21:21:44  damon]
 * 
 * Revision 1.15.9.15  1993/06/02  19:33:26  damon
 * 	CR 559. More fastidious about accepting comment leaders
 * 	[1993/06/02  19:33:12  damon]
 * 
 * Revision 1.15.9.14  1993/05/27  18:40:32  marty
 * 	Cr # 558 - type casting for rios_aix
 * 	[1993/05/27  18:40:11  marty]
 * 
 * Revision 1.15.9.13  1993/05/18  20:46:45  marty
 * 	CR # 420 - Don't unlink the lock file. leave it.
 * 	[1993/05/18  20:46:35  marty]
 * 
 * Revision 1.15.9.12  1993/05/18  19:47:01  marty
 * 	CR # 420 - bcreate now locks (and unlocks) the sandbox.
 * 	[1993/05/18  19:46:38  marty]
 * 
 * Revision 1.15.9.11  1993/04/29  16:42:27  marty
 * 	Prototyping. CR # 463
 * 	[1993/04/29  16:42:14  marty]
 * 
 * Revision 1.15.9.10  1993/04/26  19:52:17  damon
 * 	CR 415. Fixed working with sets
 * 	[1993/04/26  19:28:40  damon]
 * 
 * Revision 1.15.9.9  1993/04/16  20:01:59  damon
 * 	CR 421. Updated usage message for 2.3
 * 	[1993/04/16  20:01:24  damon]
 * 
 * Revision 1.15.9.8  1993/04/15  17:14:45  marty
 * 	Include ode/interface.h.
 * 	[1993/04/15  17:14:28  marty]
 * 
 * Revision 1.15.9.7  1993/04/01  16:24:17  marty
 * 	Added support for "-auto" switch.  Un recognisable comment leaders
 * 	get set to NONE if -auto is used.
 * 	[1993/04/01  16:19:41  marty]
 * 
 * Revision 1.15.9.6  1993/03/19  17:29:28  marty
 * 	Remove include of "regex.h"
 * 	[1993/03/19  17:29:09  marty]
 * 
 * Revision 1.15.9.5  1993/03/16  19:35:13  marty
 * 	Changed arguments to alloc_comment_leader() and
 * 	match_comment_leader().
 * 	[1993/03/16  19:06:47  marty]
 * 
 * Revision 1.15.9.4  1993/03/15  21:29:27  marty
 * 	Now search the environment variable COMMENT_LEADERS to match
 * 	filenames ro correct comment leaders.
 * 	[1993/03/15  21:21:21  marty]
 * 
 * Revision 1.15.9.3  1993/02/25  16:16:01  marty
 * 	sci_rcs.h has been moved to sci.h
 * 	[1993/02/25  16:15:41  marty]
 * 
 * Revision 1.15.9.2  1993/02/03  19:56:14  damon
 * 	CR 417. Adjusted sci_init call
 * 	[1993/02/03  19:51:19  damon]
 * 
 * Revision 1.15.4.15  1993/01/08  18:47:48  marty
 * 	Add exit with zero error status.
 * 	[1993/01/08  18:47:23  marty]
 * 
 * Revision 1.15.4.14  1993/01/04  20:15:35  marty
 * 	OT# 371, bcreate not prompts user for comment leader if one
 * 	can't be determined from filename.
 * 	[1993/01/04  20:15:23  marty]
 * 
 * Revision 1.15.4.13  1992/12/03  19:03:41  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:33:41  damon]
 * 
 * Revision 1.15.4.12  1992/11/06  19:40:02  damon
 * 	CR 296. Removed extra definitions
 * 	[1992/11/06  19:39:04  damon]
 * 
 * Revision 1.15.4.11  1992/11/05  17:26:15  damon
 * 	CR 315. Updated usage message.
 * 	[1992/11/05  17:24:36  damon]
 * 
 * Revision 1.15.4.10  1992/11/02  21:58:41  damon
 * 	CR 306. Removed NOLOCK option
 * 	[1992/11/02  21:57:14  damon]
 * 
 * Revision 1.15.4.9  1992/10/30  16:42:57  damon
 * 	CR 326. Fixed bcreate -undo
 * 	[1992/10/30  16:42:07  damon]
 * 
 * Revision 1.15.4.8  1992/09/29  14:16:03  damon
 * 	CR 238. Adjusted for change to sci_init call
 * 	[1992/09/29  14:14:54  damon]
 * 
 * Revision 1.15.4.7  1992/08/14  16:12:11  marty
 * 	Rewrote for new source control api,  the last submission somehow
 * 	got wiped out.
 * 	[1992/08/14  16:11:53  marty]
 * 
 * Revision 1.15.4.6  1992/08/14  15:23:24  marty
 * 	*** empty log message ***
 * 
 * Revision 1.15.4.5  1992/08/06  23:33:09  damon
 * 	CR 238. Moved from bin/bcs
 * 	[1992/08/06  23:30:34  damon]
 * 
 * Revision 1.15.4.4  1992/07/26  17:29:31  gm
 * 	Fixed bug unlinking FILE * instead of char *.
 * 	[1992/07/17  20:43:57  gm]
 * 
 * Revision 1.15.4.3  1992/06/19  15:01:19  marty
 * 	Add comment leader option (-c) for ode bug # 173.
 * 	[1992/06/19  15:00:59  marty]
 * 
 * Revision 1.15.4.2  1992/06/04  23:21:58  damon
 * 	Synched with 2.1.1
 * 	[1992/06/04  23:14:57  damon]
 * 
 * Revision 1.15.2.2  1992/03/25  22:44:40  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  20:12:17  damon]
 * 
 * Revision 1.15  1991/12/17  20:58:02  devrcs
 * 	Added call to default_copyright()
 * 	[1991/12/09  17:04:03  mckeen]
 * 
 * 	bcreate now adds headers to new files
 * 	[1991/12/06  19:32:02  mckeen]
 * 
 * Revision 1.14  1991/12/05  20:39:46  devrcs
 * 	added print_revision() and stub for print_usage()
 * 	[91/06/11  11:13:02  ezf]
 * 
 * 	Added support for odedefs.h
 * 	[91/05/28  13:51:46  damon]
 * 
 * 	Changes for new source control API.
 * 	[91/01/14  18:35:22  gm]
 * 
 * 	Added OSF_FREE_COPYRIGHT and progname.
 * 	[91/01/03  14:24:21  randyb]
 * 
 * Revision 1.12  90/10/07  21:49:05  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:01:38  gm]
 * 
 * Revision 1.11  90/09/23  16:55:09  devrcs
 * 	Fixed broken -undo code.
 * 	[90/09/23            gm]
 * 
 * Revision 1.10  90/08/25  12:20:32  devrcs
 * 	this implmentation of -undo should supercede any previous version
 * 	[90/08/09  15:26:37  robert]
 * 
 * 	latest cut of adding -undo as routine to bcreate
 * 	[90/08/02  16:49:33  robert]
 * 
 * Revision 1.9  90/07/17  12:33:23  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:28:41  gm]
 * 
 * Revision 1.8  90/07/06  00:42:40  devrcs
 * 	Removed call to update_configs().
 * 	[90/06/27  15:27:44  gm]
 * 
 * Revision 1.7  90/06/22  21:53:57  devrcs
 * 	Added -nolock switch.
 * 	[90/06/14  13:01:48  gm]
 * 
 * Revision 1.6  90/05/24  23:11:07  devrcs
 * 	Added call to config_insert.  Moved create_branch to subrs module.
 * 	[90/05/10  14:55:09  gm]
 * 
 * 	Removed AFS unlog.  Major rewrite of internals.
 * 	[90/05/08            gm]
 * 
 * Revision 1.5  90/04/14  00:52:22  devrcs
 * 	Added initialization for need_makepath.
 * 	[90/03/10  12:15:32  gm]
 * 
 * Revision 1.4  90/02/23  00:43:50  devrcs
 * 	Added support for shared branches/sandboxes.
 * 	[90/02/12  16:28:13  gm]
 * 
 * Revision 1.3  90/01/02  19:59:03  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.2  89/12/26  10:46:49  gm
 * 	Created.
 * 	[89/12/23            gm]
 * 
 * $EndLog$
 */

static const char * rcsid =
 "$RCSfile: bcreate.c,v $ $Revision: 1.15.17.3 $ $Date: 1993/12/16 19:54:23 $";

#include <sys/param.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/parse_rc_file.h>
#include <ode/sandboxes.h>
#include <ode/sci.h>
#include <ode/util.h>
#include <stdlib.h>
#include <string.h>

extern int valid_copyrights;
extern char * copyright_name[];
#define COPYRIGHT_OP "-n"

UIINIT init [] = {
  { COMMENT_LEADER_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { COPYRIGHT_OP,	1, OVERWRITE, 1, 1, ARGS_OP },
  { UNDO_OP,      1, OVERWRITE,  0, 0, "" },
  { ALL_OP,      1, OVERWRITE,  0, 0, "" },
  { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
  { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

  struct copy_elem {
	char * cr_name;
	struct copy_elem * cr_next;
  };

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

const char *progname = "bcreate";		/* program name */

/*
 * PROTOTYPES
 */
BOOLEAN
match_copyright_name (const char * );

int file_mode;

void
main ( int argc, char ** argv )
{
  struct rcfile contents;
  char * sb_base = NULL,
       * sb = NULL,
       * sbrc_file = NULL, 
       * rc_file = NULL, 
       * symbolic_name = NULL, 
       * submit_set = NULL, 
       * set = NULL, 
       * file; 
  SCI_LIST file_set; 
  SCI_ELEM sl_elem; 
  int ct;
  int missing_revs;
  char prompt[MAXPATHLEN + 30];
  char leader[MAXPATHLEN];
  char src_dir[MAXPATHLEN];
  char lock_file[MAXPATHLEN];
  char * leader_a;
  const char * cpy_name;
  int i;
  char buffer[100];
  char * check_copyrights;
  BOOLEAN process_copyrights;
  BOOLEAN autoflag;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sbrc_file = NULL;
  rc_file = ui_arg_value ( RC_OP, 1, 1 );

  symbolic_name = set;
  if (sci_init ( &contents, &sb, &sb_base, &symbolic_name, &submit_set,
             &sbrc_file, file_mode, FALSE ) != OK)
	exit(1);

  if (sci_copyright_init ( &contents, sb_base, sb) != OK) {
      exit(1);
  }


  /* Build up file list */
  if ( ui_is_set ( ALL_OP )) {
    sci_all_list ( &file_set, symbolic_name );
  } else {
    sci_new_list ( &file_set );
    for ( ct = 1; ( file = ui_entry_value ( ARGS_OP, ct++ )) != NULL; ) {
      sci_add_to_list ( file_set, file );
    } /* for */
  } /* if */

  /* Lock the sandbox. */
  concat (src_dir, sizeof(src_dir), sb_base, "/", sb, "/src", NULL);
  concat (lock_file, sizeof(lock_file), src_dir, "/", BCSLOCK, NULL);
  if ( ! lock_sb (src_dir, lock_file, getenv ("USER") ) )
	exit (ERROR);

  autoflag = ui_is_set (AUTO_OP);
  if (ui_is_set (UNDO_OP)) {

    sci_lookup_user_rev_list ( file_set, symbolic_name, &missing_revs );
    sci_delete_files ( file_set, symbolic_name );

  } else {

    /* Set comment leader and "set" for each file */
    sl_elem = sci_first ( file_set );
    while (sl_elem != NULL) {
	sl_elem->set = symbolic_name;
	if (ui_is_set ( COMMENT_LEADER_OP ))
		sl_elem->leader = ui_arg_value (COMMENT_LEADER_OP, 1, 1);
	else {
		leader_a = alloc_comment_leader ( sl_elem->name, contents );
		if ( leader_a == NULL ) { 
			sprintf (prompt, "Comment leader for %s ", 
				sl_elem->name);
 			getstr (prompt, "NONE", leader);
			sl_elem->leader = strdup (leader);
                } else {
		  sl_elem->leader = leader_a;
        	} /* if */
        } /* if */
        for (;;) {
	  if ((match_comment_leader(sl_elem->leader, contents) == FALSE) &&
		(autoflag == FALSE)) {
			sprintf (prompt, "The comment leader you have specified for file %s\nis not standard.  You may enter a different one or keep this comment leader \nby typing carriage return", 
				sl_elem->name);
 			getstr (prompt, sl_elem->leader, leader);
            if ( strcmp ( sl_elem->leader, leader ) == 0 ) {
  	      sl_elem->leader = strdup (leader);
              break;
            } /* if */
	    sl_elem->leader = strdup (leader);
	  } else {
            break; 
          } /* if */
        } /* for */
	sl_elem = sci_next ( sl_elem );
    }

    /*  Get the copyright. */
    if (ui_is_set (COPYRIGHT_OP)) {
	cpy_name = ui_arg_value ( COPYRIGHT_OP, 1, 1 );
	if (cpy_name == NULL)
		cpy_name = "DEFAULT";
    } else
	cpy_name = "DEFAULT";

    if ( get_rc_value ( "check_copyrights", &check_copyrights, &contents, FALSE ) == OK ) {
	if ((strcmp (check_copyrights, "true") == 0) ||
		(strcmp (check_copyrights, "TRUE") == 0)) {
           process_copyrights = TRUE;
      	   while (match_copyright_name (cpy_name) == FALSE) {

		   ui_print (VNORMAL, "Copyright name %s is not legal.\n", cpy_name);
		   ui_print (VNORMAL, 
			   "Please choose one of the following copyright names:\n");
		   for (i = 0; i < valid_copyrights; i++) {
			   ui_print (VNORMAL, "%s\n", copyright_name[i]);
		   }
		   ui_print (VNORMAL, "> ");
		   gets (buffer);
		   cpy_name = strdup (buffer);
      	   } 
	} else {
           process_copyrights = FALSE;
	}
    } else {
	   process_copyrights = FALSE;
    }

    sci_create_files ( file_set, cpy_name, process_copyrights );
  }
  exit (0);

} /* end main */


void print_usage(void)
{
  ui_print ( VALWAYS, "USAGE:\n" );
  ui_print ( VALWAYS,  "%s [%s <leader> | %s [sandbox opts] [ODE opts] [<file>...]\n", progname, COMMENT_LEADER_OP, UNDO_OP );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}

BOOLEAN
match_copyright_name (const char * name)
{
int i;

if (name == NULL) return (FALSE);

for (i = 0; i < valid_copyrights; i++) {

	if (strcmp (copyright_name[i], name) == 0) {
		return (TRUE);
	}
}

return (FALSE);
}
