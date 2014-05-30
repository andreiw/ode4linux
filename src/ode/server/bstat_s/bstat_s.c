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
 * $Log: bstat_s.c,v $
 * Revision 1.1.4.1  1993/11/09  16:54:06  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:56  damon]
 *
 * Revision 1.1.2.11  1993/05/28  19:17:28  marty
 * 	CR # 558 - type casting for rios_aix
 * 	[1993/05/28  19:17:19  marty]
 * 
 * Revision 1.1.2.10  1993/05/13  16:55:40  marty
 * 	CR # 516 - Print out "(defunct)" for defunct files.
 * 	[1993/05/13  16:55:25  marty]
 * 
 * Revision 1.1.2.9  1993/05/13  16:28:37  marty
 * 	CR # 516 - Weed out more glitches.
 * 	[1993/05/13  16:28:26  marty]
 * 
 * Revision 1.1.2.8  1993/05/13  16:23:38  marty
 * 	CR # 516 - Fix checks for types of output returned
 * 	from sci_real_fast_lookup_user_rev_list().
 * 	[1993/05/13  16:23:24  marty]
 * 
 * Revision 1.1.2.7  1993/05/12  21:40:37  marty
 * 	CR # 516 - Use sci_real_fast_lookup_user_rev_list().
 * 	[1993/05/12  21:39:49  marty]
 * 
 * Revision 1.1.2.6  1993/04/15  19:03:42  marty
 * 	Added include files stdio.h and ode/interface.h
 * 	[1993/04/15  19:03:25  marty]
 * 
 * Revision 1.1.2.5  1993/03/26  18:06:03  marty
 * 	Fix call to sci_fast_lookup_rev_list().
 * 	[1993/03/26  18:05:52  marty]
 * 
 * Revision 1.1.2.4  1993/03/25  20:37:17  marty
 * 	Added support for fast lookup of garge groups of files.
 * 	[1993/03/25  20:36:59  marty]
 * 
 * Revision 1.1.2.3  1993/03/18  18:38:34  marty
 * 	Debug problems on server side
 * 	[1993/03/18  18:31:57  marty]
 * 
 * Revision 1.1.2.2  1993/03/18  16:38:28  marty
 * 	Server side of bstat
 * 	[1993/03/18  16:35:26  marty]
 * 
 * $EndLog$
 */

#include <limits.h>
#include <ode/errno.h>
#include <ode/interface.h>
#include <ode/misc.h>
#include <ode/odedefs.h>
#include <ode/odexm.h>
#include <ode/parse_rc_file.h>
#include <ode/public/error.h>
#include <ode/public/odexm_client.h>
#include <ode/sci.h>
#include <ode/src_ctl_rcs.h>
#include <ode/util.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

#define RCS_MONITOR 0

extern OXM_CNXTN rcs_monitor;

const char * progname = "bstat_s";

UIINIT init [] = {
  { ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};

#define MAX_ARGS (sizeof(init) / sizeof(UIINIT))

extern BOOLEAN oxm_local;

void
main ( int argc, char ** argv )
{
  SCI_LIST file_set;
  SCI_ELEM sci_ptr;
  int missing_revs;
  FILE * odexm_args;
  char buf [MAXPATHLEN];
  char * rev_label=NULL;
  BOOLEAN rev_option;
  BOOLEAN print_filename;

  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

  sci_new_list ( &file_set );
  odexm_args = fopen ( ui_entry_value ( ARGS_OP, 1 ), "r" );
  fgets ( buf, sizeof (buf), odexm_args ); /* read ODE version string */
  rm_newline ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rev_option = str_to_BOOLEAN ( buf );
  if (rev_option) {
	fgets ( buf, sizeof (buf), odexm_args );
  	rm_newline ( buf );
	rev_label = strdup(buf);
  } 
  fgets ( buf, sizeof (buf), odexm_args );
  print_filename = str_to_BOOLEAN ( buf );

  while ( fgets ( buf, sizeof (buf), odexm_args ) != NULL ) {
    rm_newline ( buf );
    sci_add_to_list_as_is ( file_set, buf );
  }   
  fclose ( odexm_args );
  oxm_local = TRUE;
  sci_real_fast_lookup_user_rev_list ( file_set, rev_label, &missing_revs);

  for (sci_ptr = sci_first(file_set); sci_ptr != NULL; 
	sci_ptr = sci_next ( sci_ptr)) {
	if (sci_ptr->ver_user == NULL) {
		ui_print (VWARN, "No revision found for %s\n",
			sci_ptr->name);
	} else {
		if (is_revision (sci_ptr->ver_user)) {
			if (print_filename) {
				if (sci_ptr->defunct)
				   ui_print (VALWAYS, 
					"%s	%s	(defunct)\n", 
					sci_ptr->name, sci_ptr->ver_user);
				else
				   ui_print (VALWAYS, 
					"%s	%s\n", sci_ptr->name,
					sci_ptr->ver_user);
			} else {
				if (sci_ptr->defunct)
				   ui_print (VALWAYS, "%s	(defunct)\n", 
					sci_ptr->ver_user);
				else
				   ui_print (VALWAYS, "%s\n", 
					sci_ptr->ver_user);
			}
		} else {
			ui_print (VWARN, 
				"Invalid revision %s returned for %s\n",
				sci_ptr->ver_user, sci_ptr->name);
		}
	}
  }

  exit(0);
} /* end main */

