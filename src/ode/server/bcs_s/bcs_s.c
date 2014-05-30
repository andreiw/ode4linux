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
 * $Log: bcs_s.c,v $
 * Revision 1.1.6.1  1994/01/04  19:57:17  marty
 * 	Add atomic regions for calls to routines that create ,, files
 * 	[1994/01/04  19:47:27  marty]
 *
 * Revision 1.1.4.1  1993/11/09  16:53:56  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:49  damon]
 * 
 * Revision 1.1.2.9  1993/05/28  19:14:05  marty
 * 	CR # 558 - type casting for rios_aix
 * 	[1993/05/28  19:13:52  marty]
 * 
 * Revision 1.1.2.8  1993/05/12  20:21:57  marty
 * 	CR # Yup, another glitch
 * 	[1993/05/12  20:21:45  marty]
 * 
 * Revision 1.1.2.7  1993/05/12  20:18:16  marty
 * 	CR # 480 - Will these bugs ever go away?
 * 	[1993/05/12  20:18:04  marty]
 * 
 * Revision 1.1.2.6  1993/05/12  19:40:04  marty
 * 	CR # 480 - Rearrange code to recognise attempts to outdate revisions "1.1.1.1".
 * 	[1993/05/12  19:39:47  marty]
 * 
 * 	CR # 480 - support for "bcs -o -r".
 * 	[1993/05/12  16:28:31  marty]
 * 
 * Revision 1.1.2.5  1993/05/11  17:47:02  marty
 * 	Null delta
 * 	[1993/05/11  17:46:49  marty]
 * 
 * 	Support for "-r" option.
 * 
 * 	CR # 480 - Add support for "-r" option.
 * 	 *
 * 	Revision 1.1.2.4  1993/05/03  20:10:17  damon
 * 	CR 473. outdating now removes co locks from hold file
 * 	[1993/05/03  20:10:03  damon]
 * 
 * Revision 1.1.2.3  1993/04/30  17:15:35  marty
 * 	Add include fiels stdio.h and ode/interface.h
 * 	[1993/04/30  17:15:23  marty]
 * 
 * Revision 1.1.2.2  1993/03/19  15:31:31  marty
 * 	Initial version
 * 	[1993/03/18  22:39:50  marty]
 * 
 * $EndLog$
 */

#include <limits.h>
#include <ode/errno.h>
#include <ode/interface.h>
#include <stdio.h>
#include <ode/lockcmds.h>
#include <ode/misc.h>
#include <ode/public/error.h>
#include <ode/odedefs.h>
#include <ode/parse_rc_file.h>
#include <ode/sci.h>
#include <ode/src_ctl_rcs.h>
#include <ode/util.h>
#include <string.h>
#include <sys/param.h>

const char * progname = "bcs_s";

UIINIT init [] = {
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

extern BOOLEAN oxm_local;

void
main ( int argc, char ** argv )
{
  char * symbolic_name = NULL,
       * submit_set = NULL,
       * user = NULL;

  SCI_LIST file_set;
  SCI_ELEM sci_ptr;
  int missing_revs;
  FILE * odexm_args;
  char buf [MAXPATHLEN];
  BOOLEAN outdate_option;
  BOOLEAN revision_option;
  BOOLEAN leader_option;
  BOOLEAN big_symname_option;
  BOOLEAN small_symname_option;
  char *  leader=NULL,
       *  big_symname=NULL,
       *  small_symname=NULL;
  char holdline[MAXPATHLEN];

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  sci_new_list ( &file_set );
  odexm_args = fopen ( ui_entry_value ( ARGS_OP, 1 ), "r" );
  fgets ( buf, sizeof (buf), odexm_args ); /* read ODE version string */

  fgets ( buf, sizeof (buf), odexm_args );
  revision_option = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  outdate_option = str_to_BOOLEAN ( buf );
  if (outdate_option) {
	fgets ( buf, sizeof (buf), odexm_args );
  	rm_newline ( buf );
	symbolic_name = (char *)strdup(buf);
  }
  if ((outdate_option) && (revision_option == FALSE)) {
	fgets ( buf, sizeof (buf), odexm_args );
  	rm_newline ( buf );
	submit_set = (char *)strdup(buf);
  } 
  
  fgets ( buf, sizeof (buf), odexm_args );
  leader_option = str_to_BOOLEAN ( buf );
  if (leader_option) {
	fgets ( buf, sizeof (buf), odexm_args );
  	rm_newline ( buf );
	leader = (char *)strdup(buf);
  } 

  fgets ( buf, sizeof (buf), odexm_args );
  big_symname_option = str_to_BOOLEAN ( buf );
  if (big_symname_option ) {
	fgets ( buf, sizeof (buf), odexm_args );
  	rm_newline ( buf );
	big_symname = (char *)strdup(buf);
  } 

  fgets ( buf, sizeof (buf), odexm_args );
  small_symname_option = str_to_BOOLEAN ( buf );
  if (small_symname_option) {
	fgets ( buf, sizeof (buf), odexm_args );
  	rm_newline ( buf );
	small_symname = (char *)strdup(buf);
  } 

  while ( fgets ( buf, sizeof (buf), odexm_args ) != NULL ) {
    rm_newline ( buf );
    sci_add_to_list_as_is ( file_set, buf );
  } /* while */
  fclose ( odexm_args );
  oxm_local = TRUE;

  if ((outdate_option) && (revision_option == FALSE)) {
  	sci_lookup_user_rev_list ( file_set, symbolic_name, &missing_revs );
	/* Do the server side of the outdate. */
	sci_outdate_list_p1 (file_set, symbolic_name);
       	getenv_user ( &user );
       	concat ( holdline, sizeof(holdline), ":: ", submit_set, " ", 
		user, NULL );
       	hold_cleanup ( holdline, file_set, submit_set, FALSE );
  } else if ((outdate_option) && (revision_option)) {
	if (is_revision(symbolic_name) == FALSE) {
		/* Lookup tip revisions on branch 'symbolic_name'. */
  		sci_lookup_user_rev_list ( file_set, symbolic_name, 
			&missing_revs );
		for (sci_ptr = sci_first (file_set); sci_ptr != NULL; 
			sci_ptr = sci_next(sci_ptr)) { 
			if (is_base_of_branch(sci_ptr->ver_user) == FALSE) {
				begin_atomic();
				src_ctl_outdate (sci_ptr->name, 
					sci_ptr->ver_user, NULL, TRUE );
				end_atomic();
			} else {
				ui_print (VWARN,
			  	"Cannot outdate the first revision on a branch with the '-r' option.\n");
				ui_print (VWARN,
			  	"Use '-o <branch_name>' to remove %s from %s\n",
			  	sci_ptr->ver_user, sci_ptr->name);
			 	continue;
			}
		}
	} else {
  		sci_lookup_user_rev_list ( file_set, get_branch(symbolic_name), 
			&missing_revs );

		for (sci_ptr = sci_first (file_set); sci_ptr != NULL; 
			sci_ptr = sci_next(sci_ptr)) { 

			/* Make sure that revisionis not first revision
			   on the branch. */
		        if (is_base_of_branch( symbolic_name ) == TRUE) {
				ui_print (VWARN,
			  	"Cannot outdate the first revision on a branch with the '-r' option.\n");
				ui_print (VWARN,
			  	"Use '-o <branch_name>' to remove %s from %s\n",
			  	symbolic_name, sci_ptr->name);
			 	continue;
			}
			/* If a revision was supplied, make sure that it
			   is the tip revision on the branch. */
			if (strcmp (symbolic_name, sci_ptr->ver_user) != 0) {
				ui_print (VWARN,
				   "Revision %s is not the last revision on branch %s of file %s\n>> Revision not outdated.\n",
				   symbolic_name, get_branch(sci_ptr->ver_user),
				   sci_ptr->name);
				continue;
			}
			begin_atomic();
			src_ctl_outdate (sci_ptr->name, symbolic_name, 
				NULL, TRUE);
			end_atomic();
		}
	
	}


  }

  if (leader_option) 
	sci_set_cmt_leader_list (file_set, leader);
  
  if (big_symname_option)
	sci_set_symbol_list (file_set, big_symname, TRUE);

  if (small_symname_option)
	sci_set_symbol_list (file_set, small_symname, FALSE);

  exit(0);
} /* end main */


