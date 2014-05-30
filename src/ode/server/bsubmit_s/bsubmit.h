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
 * $Log: bsubmit.h,v $
 * Revision 1.1.4.1  1993/11/09  16:54:08  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:57  damon]
 *
 * Revision 1.1.2.2  1993/03/17  16:00:17  damon
 * 	CR 436. Initial Version
 * 	[1993/03/17  15:49:41  damon]
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
**  Description:
**	This header file is for bsubmit.c, bcscall.c lockcmds.c, sbutil.c,
**	and sadmin.c.
**
 */
/*                       INCLUDES					     */
#  include <ode/odedefs.h>
#  include <ode/versions.h>
#  include <signal.h>
#  include <sys/param.h>
#  include <sys/stat.h>
#  include <sys/time.h>
#  include <sys/wait.h>
#  include <sys/file.h>
#  include <sys/errno.h>
#  include <pwd.h>
#  include <ode/errno.h>
#  include <ode/parse_rc_file.h>
#  include <ode/sci.h>
#  include <ode/odexm.h>
#  include <ode/public/error.h>
#  include <ode/public/odexm_client.h>

#ifdef INC_TIME
#  include <time.h>
#endif

/*                       DEFINES					     */

#  define  MAX_ARGS	(sizeof(init) / sizeof(UIINIT))	/* number of args */
#  define  PASSARGS	30

#  define  ALLWRITE	0666
#  define  MEWRITE	0600

#  define  LOCKWAIT	3

#  define  CO_M_OUT     0                     /* mode to do local check outs */
#  define  CO_M_LOCK	1
#  define  CO_M_BLD	2
#  define  CO_M_LBLD	3
#  define  CO_M_LO	4
#  define  CO_M_LLO	5

#  define  LOCKHOLDF    0                  /* modes to do locking, unlocking */
#  define  LOCKLOGF	1

#  define  EDITHOLD     0                    /* modes to do copying, editing */
#  define  EDITLOG	1
#  define  EDITSNAP	2
#  define  EDITDEF	3

#  define  WAITING      1                  /* return value for legal waiting */
#  define  NO_OPT       2             /* return value for doing no operation */

#  define  AUTOOUT_OP	"-auto_out"
#  define  DEFECT_OP	"-defect"
#  define  FN_OP	"-fn"
#  define  LOCAL_CO_OP	"-local_co"
#  define  RESUB_OP	"-resub"
#  define  TAG_OP	"-tag"

#  define  BACK_OPT     "backing"         /* option for co from backing tree */
#  define  LOCK_OPT     "lock"                    /* option for co with lock */
#  define  SB_OPT       "sb"                            /* option for sadmin */
#  define  SET_OPT      "set"                           /* option for sadmin */

#  define  BCSSTEPS	"bcssteps"	/* part of name of file tracking bcs */
#  define  BLOCALRC     "rc_files/bsub.local"  /* name of bsubmit sb rc file */
#  define  DEF_EDITOR   "vi"                       /* default editor if none */
#  define  ECHO         "/bin/echo"                          /* echo command */
#  define  LOCAL	"local"  		       /* default sb rc file */
#  define  LOGS         "logs"                                  /* directory */
#  define  LOGSUB	"logsubmit"  	        /* program running on server */
#  define  NO_EDIT      "cat"                  /* just cat the file, no edit */
#  define  NOTIFY	"Please Notify Release Engineering" /* call for help */
#  define  TUTORIAL     "./ode/tutorial/"             /* tutorial area */
#  define  TUT_CT	strlen ( TUTORIAL )
#  define  MERGED_TRACK "Files already merged"
#  define  C_MERGE      "Changed files already merged"   /* lines indicating */
#  define  D_MERGE      "Defunct files already merged"   /* which steps have */
#  define  LOCKED_TRACK "Files already locked"
#  define  C_B_CI       "Changed files already checked-in" /* been completed */
#  define  D_B_CI	"Defunct files already checked-in"       /* during a */
#  define  C_B_CO	"Changed files already checked-out"        /* submit */
#  define  D_B_CO	"Defunct files already checked-out"
#  define  UPDATED_TRACK "Logs already updated"
#  define  SUBMIT_DONE   "Submission done"
#  define PREPARING 0
#  define VALIDATING 1
#  define MERGING 2
#  define LOCKING 3
#  define CHECKING_IN 4
#  define CHECKING_OUT 5
#  define OUTDATING 6
