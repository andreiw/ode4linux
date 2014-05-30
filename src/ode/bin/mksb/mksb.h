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
 * $Log: mksb.h,v $
 * Revision 1.9.6.1  1993/11/04  19:52:03  damon
 * 	CR 463. More pedantic
 * 	[1993/11/04  19:48:47  damon]
 *
 * Revision 1.9.4.3  1993/02/01  21:57:43  damon
 * 	CR 417. Removed MAX_ARGS
 * 	[1993/02/01  21:57:30  damon]
 * 
 * Revision 1.9.4.2  1993/01/13  16:43:45  damon
 * 	CR 382. Removed INC_DIRENT
 * 	[1993/01/05  20:50:59  damon]
 * 
 * Revision 1.9.2.6  1992/12/03  19:08:02  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:37:13  damon]
 * 
 * Revision 1.9.2.5  1992/11/10  20:43:20  damon
 * 	CR 329. Removed explicit decl of strrchr
 * 	[1992/11/10  20:42:58  damon]
 * 
 * Revision 1.9.2.4  1992/09/24  18:59:05  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/21  20:20:46  gm]
 * 
 * Revision 1.9.2.3  1992/06/24  19:33:03  zeliff
 * 	Changes for AIX 3.2: adding argument lists for function prototypes.
 * 	[1992/06/23  19:01:17  zeliff]
 * 
 * Revision 1.9.2.2  1991/12/30  21:25:45  damon
 * 	port to sparc_sunos and libsb to libode transition
 * 	[1991/12/20  20:13:22  damon]
 * 
 * Revision 1.9  1991/12/05  20:46:08  devrcs
 * 	Repeat submit for ODE
 * 	[1991/01/10  10:06:36  randyb]
 * 
 * 	Changed include files from sdm/ to ode/ and std_defs.h to
 * 	ode_defs.h
 * 	[91/01/09  14:01:21  randyb]
 * 
 * 	Eliminated old defines and set MAX_ARGS to correct value.
 * 	[91/01/08  15:07:36  randyb]
 * 
 * 	Updates necessary to handle searching for base directory and
 * 	supporting new population command line options.
 * 	[90/12/10  13:18:27  randyb]
 * 
 * 	Changes for the Tools II modifications.
 * 	[90/11/13  17:22:32  randyb]
 * 
 * 	Style updates; saber c lint
 * 	[90/11/08  08:02:13  randyb]
 * 
 * Revision 1.7  90/10/07  21:52:04  devrcs
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
**    Description:
**	This header file is for mksb.c
**
 */
/*                       INCLUDES					     */

#  include <string.h>
#  include <ode/odedefs.h>
#  include <sys/param.h>
#  include <sys/signal.h>
#  include <sys/wait.h>
#  include <ode/parse_rc_file.h>

/*                       DEFINES					     */

#  define  NEW		10
#  define  MODE		0775

#  define  HELP_GRP	"Release Engineering"
#  define  TOOLS_OP	"-tools"
#  define  OBJ_OP	"-obj"
#  define  SRC_OP	"-src"

#  define  DEF_MACH     "pmax"                       /* default machine list */
#  define  TMP_NAME     "/mksb.tmp"                   /* temporary file name */

#  define  RM           "rm"                             /* commands to exec */
#  define  WORKON	"workon"
#  define  MKLINKS	"mklinks"

#  define  BACK_CH      'b'                       /* default population mode */
#  define  COPY_CH	'c'
#  define  LINK_CH	'l'

/*                       GLOBAL DECLARATIONS				     */

	/* structure to hold an entry from an rc file.*/

    typedef struct entry {
      char      target [ NAME_LEN ],  /* the target for the value (optional) */
                value [ PATH_LEN ];   /* the value for the keyword or target */
      struct    entry  * nextentry;                 /* ptr to the next entry */
    } ENTRY;

	/* structure to hold the contens of an rc file.*/

    typedef struct rc_content {
      char      default_sb [ NAME_LEN ];          /* name of default sandbox */
      ENTRY   * base;                              /* holds list of sb bases */
      ENTRY   * sb;                                /* holds list of sb names */
      char      def_sb_base [ PATH_LEN ],            /* default sandbox base */
                def_machines [PATH_LEN ],                /* default machines */
                tools,                              /* how to populate tools */
                objects,                          /* how to populate objects */
                sources,                          /* how to populate sources */
                obj_dirs [ PATH_LEN ],  /* list of dirs to populate obj with */
                src_dirs [ PATH_LEN ];  /* list of dirs to populate src with */
    } RC_CONT;
