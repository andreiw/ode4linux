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
 * $Log: branch_ci.c,v $
 * Revision 1.1.9.2  1994/02/08  17:11:21  damon
 * 	CR 1049. Added include of sci.h for *_atomic() protos
 * 	[1994/02/08  17:02:53  damon]
 *
 * Revision 1.1.9.1  1994/01/04  19:57:23  marty
 * 	Add atomic regions for calls to routines that create ,, files
 * 	[1994/01/04  19:47:30  marty]
 * 
 * Revision 1.1.7.1  1993/11/09  16:54:03  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:54  damon]
 * 
 * Revision 1.1.5.1  1993/09/08  15:02:15  root
 * 	CR # 622 - sinix doesn't have strings.h, ifdef it out.
 * 	[1993/09/08  15:01:48  root]
 * 
 * Revision 1.1.2.11  1993/04/16  15:36:36  damon
 * 	CR 436. Synching create_branch code
 * 	[1993/04/16  15:36:24  damon]
 * 
 * Revision 1.1.2.10  1993/04/06  20:47:01  damon
 * 	CR 436. Fixed call to src_ctl_create_branch2
 * 	[1993/04/06  20:46:51  damon]
 * 
 * Revision 1.1.2.9  1993/04/06  20:04:01  damon
 * 	CR 436. Moved from rcs area
 * 	[1993/04/06  20:03:31  damon]
 * 
 * Revision 1.1.2.8  1993/03/04  21:24:37  damon
 * 	CR 432. For initial revision, set the ancestor to 1.1
 * 	[1993/03/04  21:24:26  damon]
 * 
 * Revision 1.1.2.7  1993/03/04  21:15:23  damon
 * 	CR 432. 1.1.1.1 should have been 1.1.1
 * 	[1993/03/04  21:15:09  damon]
 * 
 * Revision 1.1.2.6  1993/03/04  20:40:58  damon
 * 	CR 432. Added explicit choice of 1.1.1.1 for new files
 * 	[1993/03/04  20:40:47  damon]
 * 
 * Revision 1.1.2.5  1993/02/22  16:22:10  damon
 * 	CR 432. Fixed locking of trunk to be 1.1 always
 * 	[1993/02/22  16:21:58  damon]
 * 
 * Revision 1.1.2.4  1993/02/11  19:41:51  damon
 * 	CR 432. Added ancestry tracking with -a option
 * 	[1993/02/11  19:36:54  damon]
 * 
 * Revision 1.1.2.3  1993/02/10  00:22:33  damon
 * 	CR 196. Removed locking of branch code
 * 	[1993/02/10  00:22:20  damon]
 * 
 * Revision 1.1.2.2  1993/01/11  18:08:37  damon
 * 	CR 386. Moved from ODE
 * 	[1993/01/11  18:08:17  damon]
 * 
 * Revision 1.2.5.4  1992/12/02  19:15:22  damon
 * 	CR 183. Added CMU copyright
 * 	[1992/12/02  19:15:06  damon]
 * 
 * Revision 1.2.5.3  1992/06/26  15:40:29  damon
 * 	CR 126. Fixed locking logic
 * 	CR 181. Changed vfork to fork
 * 	[1992/06/26  15:40:00  damon]
 * 
 * Revision 1.2.5.2  1992/06/15  19:23:33  damon
 * 	Synched with DCE changes
 * 	[1992/06/15  19:12:47  damon]
 * 
 * Revision 1.2.3.2  1992/04/09  16:43:57  mhickey
 * 	Added much error checking to avoid segv's, etc.
 * 	DCE OT defect 2606.
 * 	[1992/04/09  16:43:05  mhickey]
 * 
 * Revision 1.2  1991/12/05  20:46:54  devrcs
 * 	Added -c switch that will change the comment leader for the rcs file
 * 	[91/09/25  10:06:16  rec]
 * 
 * 	Changed the execv to exevp to pass the environment path.  This
 * 	allows the rcs tools (rcs, ci, co and rlog) used, be from the
 * 	defined location for the specific installation.  No absolute
 * 	or relative paths are used in the file.
 * 	[91/08/21  16:23:47  rec]
 * 
 * 	Initial version of the cover for ci.
 * 	This cover creates the correct branch
 * 	taking the place of the 'ci -b' switch
 * 	in the old CMU rcs tools.
 * 	[91/08/14  14:08:38  rec]
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

const char *progname = "branch_ci";

#define revlength          30 /* max. length of revision numbers */
#undef lint

extern BOOLEAN oxm_local;
extern OXM_CNXTN rcs_monitor;

void
main ( int argc, char **argv )
{
  char *rev = (char *)NULL;
  char *leader = (char *)NULL;
  char *workingfile = (char *)NULL;
  char *filename = (char *)NULL;
  char *symbol = (char *)NULL;
  char *msg = (char *)NULL;
  char *ancestor = NULL;

  ERR_LOG log;
  BOOLEAN lock;

  /*---*
   *---* In the spirit of the rest of this code, I am letting rev and leader get
   *---* set to point to '\0' if the -r or -c option gets passed with no value.
   *---* At worst this should not cause a segv.
   *---*/
  lock = FALSE;
  while (--argc, ++argv, argc>=1 && ((*argv) [0] == '-'))  {
    switch ((*argv) [1])  {

    case 'r':
      if (*((*argv)+2) == '\0')
	 fprintf(stderr, "No revision specified with -r option.\n");
      rev = (*argv)+2;
      break;
    case 'u':
      if (*((*argv)+2) == '\0')
	 fprintf(stderr, "No revision specified with -r option.\n");
      rev = (*argv)+2;
      lock = TRUE;
      break;
    case 'm':
      if (*((*argv)+2) == '\0')
	 fprintf(stderr, "No message specified with -m option.\n");
      msg = (*argv)+2;
      break;
    case 'N':
      if (*((*argv)+2) == '\0')
	fprintf(stderr, "No symbol name specified with -N option\n");
      symbol = *argv+2;              /* symbol name with -N */
      break;
    case 'c':
      if (*((*argv)+2) == '\0')
	fprintf(stderr, "No comment leader specified with -c option\n");
      leader = *argv+2;
      break;

    case 'a':
      if (*((*argv)+2) == '\0')
	 fprintf(stderr, "No revision specified with -a option.\n");
      ancestor = (*argv)+2;
      break;

      default :
	fprintf (stderr, "branch_ci error: unknown option: %s\n", *argv);
    };
  }
  
  if (rev == (char *)NULL)
  {
     fprintf(stderr, "Missing -r option.\n");
     exit(1);
  }
  else if (symbol == (char *)NULL)
  {
     fprintf(stderr, "Missing -N option.\n");
     exit(1);
  }
  else if (argc < 2)
  {
     fprintf(stderr, "Missing %s \n", 
                               argc == 0? "working file and filename": "filename");
     exit(2);
  }

  workingfile = *argv++;
  filename = *argv;

  oxm_local = TRUE;
  log = oxm_open ( &rcs_monitor, 0 );
  begin_atomic ( );
  src_ctl_create_branch2 ( workingfile, filename, lock, rev, symbol, ancestor,
                           leader, msg, &log );
  end_atomic ( );
  log = oxm_close ( rcs_monitor );
  oxm_local = FALSE;
  exit (0);
} /* end branch_ci */
