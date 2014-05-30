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
 * 
 * Copyright (c) 1992 Carnegie Mellon University 
 * All Rights Reserved. 
 *  
 * Permission to use, copy, modify and distribute this software and its 
 * documentation is hereby granted, provided that both the copyright 
 * notice and this permission notice appear in all copies of the 
 * software, derivative works or modified versions, and any portions 
 * thereof, and that both notices appear in supporting documentation. 
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 * Software Distribution Coordinator  or  Software_Distribution@CS.CMU.EDU
 * School of Computer Science
 * Carnegie Mellon University
 * Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes. 
 */
/* 
 * HISTORY
 * $Log: bmerge_s.c,v $
 * Revision 1.1.8.3  1994/02/08  20:34:12  damon
 * 	CR 1049. Removed extra comment end
 * 	[1994/02/08  20:34:02  damon]
 *
 * Revision 1.1.8.2  1994/02/08  17:11:19  damon
 * 	CR 1049. Added include of sci.h for *_atomic() protos
 * 	[1994/02/08  17:08:28  damon]
 * 
 * Revision 1.1.8.1  1994/01/04  19:57:20  marty
 * 	Add atomic regions for calls to routines that create ,, files
 * 	[1994/01/04  19:47:29  marty]
 * 
 * Revision 1.1.6.1  1993/11/09  16:54:01  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:52  damon]
 * 
 * Revision 1.1.4.1  1993/09/08  14:56:59  root
 * 	CR # 622 - sinix does not have "strings.h".  ifdef it out.
 * 	[1993/09/08  14:56:35  root]
 * 
 * Revision 1.1.2.4  1993/04/14  14:41:21  damon
 * 	CR 436. Changed to use libode routine
 * 	[1993/04/14  14:41:16  damon]
 * 
 * Revision 1.1.2.3  1993/03/31  20:44:09  damon
 * 	CR 436. Fixed file argument
 * 	[1993/03/31  20:44:00  damon]
 * 
 * Revision 1.1.2.2  1993/03/30  20:13:11  damon
 * 	CR 436. Small gesture of client/server for bmerge
 * 	[1993/03/30  20:12:55  damon]
 * 
 * $EndLog$
 */

#include <malloc.h>
#include <stdio.h>
#ifndef NO_STRINGS
#include <strings.h>
#endif
#include <ode/odedefs.h>
#include <ode/odexm.h>
#include <ode/errno.h>
#include <ode/public/error.h>
#include <ode/public/odexm_client.h>
#include <ode/sci.h>
#include <ode/src_ctl_rcs.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <sys/file.h>

const char *progname = "bmerge_s";

extern BOOLEAN oxm_local;
extern OXM_CNXTN rcs_monitor;

void
main ( int argc, char **argv )
{
  char * new_ancestry = (char *)"";
  char *filename = (char *)NULL;
  ERR_LOG log;

  /*---*
   *---* In the spirit of the rest of this code, I am letting rev and leader get
   *---* set to point to '\0' if the -r or -c option gets passed with no value.
   *---* At worst this should not cause a segv.
   *---*/
  while (--argc, ++argv, argc>=1 && ((*argv) [0] == '-'))  {
    switch ((*argv) [1])  {

    case 'a':
      if (*((*argv)+2) == '\0')
	 fprintf(stderr, "No ancestry given with -a option.\n");
      new_ancestry = (*argv)+2;
      break;

      default :
	fprintf (stderr, "bmerge_s error: unknown option: %s\n", *argv);
    };
  }
  
  if (argc < 1)
  {
     fprintf(stderr, "Missing filename\n" );
     exit(1);
  }

  filename = *argv;

  oxm_local = TRUE;
  log = oxm_open ( &rcs_monitor, 0 );
  begin_atomic();
  src_ctl_add_ancestry2 ( filename, new_ancestry );
  end_atomic();
  log = oxm_close ( rcs_monitor );
  oxm_local = FALSE;
  exit(0);
} /* end bmerge_s */
