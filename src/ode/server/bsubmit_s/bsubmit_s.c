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
 * $Log: bsubmit_s.c,v $
 * Revision 1.1.8.9  1994/02/03  22:33:42  damon
 * 	Rollback CR 890
 * 	[1994/02/03  22:18:51  damon]
 *
 * 	CR 1034. Use sci_add_to_list_as_is for resubs
 * 	[1994/02/03  21:59:40  damon]
 *
 * Revision 1.1.8.8  1994/01/31  20:06:20  damon
 * 	CR 1000. Return an error if no ancestor found
 * 	[1994/01/31  20:05:22  damon]
 * 
 * Revision 1.1.8.7  1994/01/20  00:01:18  damon
 * 	CR 899. Removed updating during merges for bsubmit -info
 * 	[1994/01/20  00:01:10  damon]
 * 
 * Revision 1.1.8.6  1994/01/19  20:38:32  damon
 * 	CR 961. Changed outdating message to be more friendly
 * 	[1994/01/19  20:38:23  damon]
 * 
 * Revision 1.1.8.5  1993/12/07  19:51:57  marty
 * 	CR 890 - Add call to sci_validate_submit_set_list() to make sure that submit_set points to a branch and not a revision number.
 * 	[1993/12/07  19:51:39  marty]
 * 
 * Revision 1.1.8.4  1993/11/30  16:35:32  damon
 * 	CR 867. Removed check for branch tip rev > 1
 * 	[1993/11/30  16:34:58  damon]
 * 
 * Revision 1.1.8.3  1993/11/22  20:35:22  damon
 * 	CR 679. Validate ancestry before it is ever used
 * 	[1993/11/22  20:34:29  damon]
 * 
 * Revision 1.1.8.2  1993/11/22  18:46:59  damon
 * 	CR 852. Separated looking up ancestry from determining ancestor
 * 	[1993/11/22  18:46:19  damon]
 * 
 * Revision 1.1.8.1  1993/11/16  21:40:52  damon
 * 	CR 807. Do less when ^C hit during merge stage
 * 	[1993/11/16  21:40:28  damon]
 * 
 * Revision 1.1.6.2  1993/11/09  16:54:11  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:52:59  damon]
 * 
 * Revision 1.1.6.1  1993/11/03  00:10:26  damon
 * 	CR 773. Complain if user set and submit set are the same
 * 	[1993/11/02  23:41:50  damon]
 * 
 * Revision 1.1.4.5  1993/10/01  19:15:07  damon
 * 	CR 719. Print user_id at end of line in list of tagged files
 * 	[1993/10/01  19:14:51  damon]
 * 
 * Revision 1.1.4.4  1993/09/21  14:53:30  damon
 * 	CR 658. Fixed time/ttime ttypo
 * 	[1993/09/16  19:15:26  damon]
 * 
 * Revision 1.1.4.3  1993/09/07  16:34:35  damon
 * 	CR 625. Fixed bsubmit -info
 * 	[1993/09/07  16:33:39  damon]
 * 
 * Revision 1.1.4.2  1993/09/03  16:48:10  damon
 * 	CR 639. Fixed printing of Tlog path
 * 	[1993/09/03  16:47:16  damon]
 * 
 * Revision 1.1.4.1  1993/09/02  20:45:04  damon
 * 	CR 604. Handle ci return values properly
 * 	[1993/09/02  20:44:28  damon]
 * 
 * Revision 1.1.2.33  1993/07/01  16:01:39  marty
 * 	CR # 586 - If sci_real_fast_lookup*() returns an error then bail out
 * 	of bsubmit.
 * 	[1993/07/01  16:01:23  marty]
 * 
 * Revision 1.1.2.32  1993/06/10  21:31:43  damon
 * 	CR 585. fixed typo with resub_ob/RESUB_OP
 * 	[1993/06/10  21:31:37  damon]
 * 
 * Revision 1.1.2.31  1993/06/10  21:21:13  damon
 * 	CR 585. check for resub_op instead of RESUB_OP
 * 	[1993/06/10  21:21:04  damon]
 * 
 * Revision 1.1.2.30  1993/06/09  17:30:44  damon
 * 	CR 580. Pass original date stamp to subsequent sci_submit_client()s
 * 	[1993/06/09  17:30:16  damon]
 * 
 * Revision 1.1.2.29  1993/06/07  16:55:49  damon
 * 	CR 572. Removes HH:MM files if merge required
 * 	[1993/06/07  16:55:41  damon]
 * 
 * Revision 1.1.2.28  1993/06/01  16:06:02  marty
 * 	DCR # 562 - Get bsubmit_s building on sparc_sunos.
 * 	[1993/06/01  16:05:45  marty]
 * 
 * Revision 1.1.2.27  1993/05/28  19:18:49  marty
 * 	CR # 558 - type casting for rios_aix
 * 	[1993/05/28  19:18:34  marty]
 * 
 * Revision 1.1.2.26  1993/05/26  20:20:25  damon
 * 	CR 549. Check for submission in progress for current minute
 * 	[1993/05/26  20:20:17  damon]
 * 
 * Revision 1.1.2.25  1993/05/26  19:12:38  damon
 * 	CR 550. Remove oldrevs file at completion
 * 	[1993/05/26  19:12:30  damon]
 * 
 * Revision 1.1.2.24  1993/05/25  17:59:00  damon
 * 	CR 539. Send back resub date
 * 	[1993/05/25  17:54:16  damon]
 * 
 * Revision 1.1.2.23  1993/05/25  15:09:09  damon
 * 	CR 395. Added HOLD_FILE_23
 * 	[1993/05/25  15:08:33  damon]
 * 
 * Revision 1.1.2.22  1993/05/24  18:36:27  damon
 * 	CR 499. Updated call to hold_cleanup()
 * 	[1993/05/24  18:36:17  damon]
 * 
 * Revision 1.1.2.21  1993/05/24  17:46:08  damon
 * 	CR 501. For resub, list of files returned to client for outdate
 * 	[1993/05/24  17:45:31  damon]
 * 
 * Revision 1.1.2.20  1993/05/24  16:13:25  damon
 * 	CR 484. Now gets log information back to client
 * 	[1993/05/24  16:06:08  damon]
 * 
 * Revision 1.1.2.19  1993/05/20  15:47:53  damon
 * 	CR 532. Made outdating optional for bsubmit
 * 	[1993/05/20  15:42:16  damon]
 * 
 * Revision 1.1.2.18  1993/05/14  21:01:31  marty
 * 	Bsubmit now uses "fast" lookup routines.
 * 	[1993/05/14  21:01:10  marty]
 * 
 * Revision 1.1.2.17  1993/05/11  21:11:49  damon
 * 	CR 468. Made file locking customizeable
 * 	[1993/05/11  21:10:54  damon]
 * 
 * Revision 1.1.2.16  1993/05/10  18:53:14  damon
 * 	CR 503. Changed checking of RESUB_OP, RM_OP to resub_op remove_op
 * 	[1993/05/10  18:53:05  damon]
 * 
 * Revision 1.1.2.15  1993/05/10  18:31:17  damon
 * 	CR 503. No longer complains about merges during resub or rm
 * 	[1993/05/10  18:31:01  damon]
 * 
 * Revision 1.1.2.14  1993/05/10  18:08:20  damon
 * 	CR 513. Now removes tracking file if operation is a success
 * 	[1993/05/10  18:07:37  damon]
 * 
 * Revision 1.1.2.13  1993/05/05  20:18:23  marty
 * 	The field for file_set->elem_num has been changed to file_set->elem_cnt.
 * 	[1993/05/05  20:18:09  marty]
 * 
 * Revision 1.1.2.12  1993/05/04  19:15:06  damon
 * 	CR 382. Removed bogus F I X M E comment
 * 	[1993/05/04  19:14:59  damon]
 * 
 * Revision 1.1.2.11  1993/05/03  21:28:34  damon
 * 	CR 473. Adjusted calls to hold_cleanup
 * 	[1993/05/03  21:27:27  damon]
 * 
 * Revision 1.1.2.10  1993/04/26  15:52:24  damon
 * 	CR 436. Now using ode2.3_server_base dir for tracking files
 * 	[1993/04/21  17:59:45  damon]
 * 
 * Revision 1.1.2.9  1993/04/13  17:26:56  damon
 * 	CR 436. Added new merge handling
 * 	[1993/04/13  17:26:44  damon]
 * 
 * Revision 1.1.2.8  1993/04/12  17:23:21  damon
 * 	CR 446. Cleaned up include files
 * 	[1993/04/12  17:23:11  damon]
 * 
 * 	CR 446. Clean up include files
 * 
 * Revision 1.1.2.7  1993/03/24  20:49:23  damon
 * 	CR 436. resub and remove options working client/server
 * 	[1993/03/24  20:39:22  damon]
 * 	 *
 * 	Revision 1.1.2.6  1993/03/17  16:00:19  damon
 * 	CR 436.
 * 	Lets calling program know if a merge is required.
 * 	Now updates oldrevs file and bcssteps file.
 * 	[1993/03/17  15:56:10  damon]
 * 
 * Revision 1.1.2.5  1993/03/15  21:05:11  damon
 * 	CR 436. Get all info needed for submit log
 * 	[1993/03/15  21:00:16  damon]
 * 
 * Revision 1.1.2.4  1993/03/15  18:59:51  damon
 * 	CR 436. Moved temp files to user_set directory
 * 	[1993/03/15  18:59:43  damon]
 * 
 * Revision 1.1.2.3  1993/03/15  17:56:21  damon
 * 	CR 436. Fixed log handling
 * 	[1993/03/15  17:56:11  damon]
 * 
 * Revision 1.1.2.2  1993/03/11  22:53:43  damon
 * 	CR 436. Server side of new bsubmit
 * 	[1993/03/11  22:47:03  damon]
 * 
 * Revision 1.14.6.11  1993/02/19  18:55:58  damon
 * 	CR 193. Added strict locking to lockcmds.c
 * 	[1993/02/19  18:55:10  damon]
 * 
 * Revision 1.14.6.10  1993/02/16  18:22:48  damon
 * 	CR 397. Generalized functions from lockcmds.c
 * 	[1993/02/16  18:22:13  damon]
 * 
 * Revision 1.14.6.9  1993/02/12  23:30:26  damon
 * 	CR 136. Hold file checking now done by logsubmit
 * 	[1993/02/12  23:08:51  damon]
 * 
 * Revision 1.14.6.8  1993/02/12  16:51:12  damon
 * 	CR 417. Move bsubmit.hold to rcs tree.
 * 	[1993/02/12  16:50:51  damon]
 * 
 * Revision 1.14.6.7  1993/02/11  21:38:24  damon
 * 	CR 429. Added -rm option
 * 	[1993/02/11  21:37:27  damon]
 * 
 * Revision 1.14.6.6  1993/02/11  21:15:06  damon
 * 	CR 409. Removed -nolog
 * 	[1993/02/11  21:14:28  damon]
 * 
 * Revision 1.14.6.5  1993/02/03  18:46:42  damon
 * 	CR 253. Now use checklocksb to see if build is locked
 * 	[1993/02/03  18:37:11  damon]
 * 
 * Revision 1.14.6.4  1993/01/25  19:01:38  damon
 * 	CR 382. Moved some code to misc.c
 * 	[1993/01/25  19:01:15  damon]
 * 
 * Revision 1.14.6.3  1993/01/13  20:37:19  damon
 * 	CR 382
 * 	Moved code from sbutil.c to here
 * 	Removed unused code
 * 	[1993/01/13  20:35:13  damon]
 * 
 * Revision 1.14.6.2  1993/01/13  17:41:30  damon
 * 	CR 196. Removed rcs locking
 * 	[1993/01/04  20:33:53  damon]
 * 
 * Revision 1.14.2.15  1992/12/15  21:14:23  damon
 * 	CR 360. Works for resub during outdating state
 * 	[1992/12/15  21:14:06  damon]
 * 
 * Revision 1.14.2.14  1992/12/03  19:04:05  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:34:03  damon]
 * 
 * Revision 1.14.2.13  1992/11/25  16:03:52  damon
 * 	CR 340. Fixed -resub option
 * 	[1992/11/25  16:03:27  damon]
 * 
 * Revision 1.14.2.12  1992/11/24  16:24:30  damon
 * 	CR 337. First shot at new bsubmit.log format
 * 	[1992/11/24  16:23:52  damon]
 * 
 * Revision 1.14.2.11  1992/11/12  18:27:36  damon
 * 	CR 329. Removed decl of strchr
 * 	[1992/11/12  18:08:25  damon]
 * 
 * Revision 1.14.2.10  1992/11/05  16:26:59  damon
 * 	CR 129. Now calls getenv_user2 always
 * 	[1992/11/05  16:26:13  damon]
 * 
 * Revision 1.14.2.9  1992/09/24  18:58:01  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:16:38  gm]
 * 
 * Revision 1.14.2.8  1992/09/17  20:06:50  damon
 * 	CR 238. Synched with changes in sci_rcs
 * 	[1992/09/17  20:06:19  damon]
 * 
 * Revision 1.14.2.7  1992/08/06  23:23:06  damon
 * 	CR 238. Converted to use newer sci_rcs
 * 	[1992/08/06  23:21:57  damon]
 * 
 * Revision 1.14.2.6  1992/06/24  19:32:45  zeliff
 * 	Changes for AIX 3.2: adding argument lists for function prototypes.
 * 	[1992/06/23  19:01:00  zeliff]
 * 
 * Revision 1.14.2.5  1992/06/17  12:43:27  damon
 * 	Fixed bug 163. Bogus -auto_merge option removed
 * 	[1992/06/17  12:12:00  damon]
 * 
 * Revision 1.14.2.4  1992/06/11  19:46:30  damon
 * 	Synched with 2.1.1
 * 	[1992/06/11  19:44:06  damon]
 * 
 * Revision 1.14.4.6  1992/03/25  22:45:19  damon
 * 	Changed to use ui_print_revision
 * 	[1992/03/25  20:14:51  damon]
 * 
 * Revision 1.14.4.5  1992/03/23  22:52:30  damon
 * 	Added uid to tag line for -tag option
 * 	[1992/03/23  22:51:35  damon]
 * 
 * Revision 1.14.4.4  1992/03/23  19:10:34  damon
 * 	Cleaned up -tag code in defunct case
 * 	[1992/03/23  19:08:06  damon]
 * 
 * Revision 1.14.4.3  1992/03/23  18:13:40  damon
 * 	Added -tag option
 * 	[1992/03/23  18:10:07  damon]
 * 
 * Revision 1.14.4.2  1992/01/27  19:55:11  damon
 * 	Patches from latest
 * 	[1992/01/27  19:47:39  damon]
 * 
 * Revision 1.14.2.3  1992/01/27  19:19:20  damon
 * 	Fixes (null) pointer in SNAPSHOT, bug 131
 * 	[1992/01/27  18:43:39  damon]
 * 
 * Revision 1.14.2.2  1992/01/02  21:34:27  damon
 * 	Fixed file revision list ommission bug
 * 	[1992/01/02  21:32:37  damon]
 * 
 * Revision 1.14  1991/12/17  20:58:42  devrcs
 * 	Ported to hp300_hpux
 * 	[1991/12/17  14:30:23  damon]
 * 
 * Revision 1.13  1991/12/05  20:40:36  devrcs
 * 	Removed all redundant calls to parse_rc_file.
 * 	Now uses passed in 'contents' variable.
 * 	This fixes the split backing trees problem.
 * 	[1991/11/18  15:59:01  damon]
 * 
 * 	Commented out src_ctl_check_servers call
 * 	[1991/11/15  16:07:13  damon]
 * 
 * 	Corrected exit status
 * 	[1991/11/13  14:59:11  damon]
 * 
 * 	don't prompt for user's full name if given -auto
 * 	[1991/11/12  21:35:56  ezf]
 * 
 * 	Removed unused code
 * 	[1991/11/11  20:24:28  damon]
 * 
 * 	Reinstituted nolog switch
 * 	[1991/11/11  19:39:51  damon]
 * 
 * 	Changed no branch message to no check-ins
 * 	[1991/11/06  19:59:24  damon]
 * 
 * 	Fixes bug 90: bsubmit messages confusing.
 * 	[1991/11/03  21:08:21  damon]
 * 
 * 	Changed COPYHOLD to COPYFILE
 * 	[1991/10/30  21:48:29  damon]
 * 
 * 	Info switch now works better
 * 	[91/10/30  09:16:53  damon]
 * 
 * 	Fixed bug 84: wrong # of files in log file
 * 	[91/10/29  17:05:01  damon]
 * 
 * 	Now exits if the editor cannot be run.
 * 	[91/10/29  15:00:01  damon]
 * 
 * 	Continue prompt during merging now gives options.
 * 	Clear option for interrupted merges no longer gives confusing message.
 * 	[91/10/27  15:53:01  damon]
 * 
 * 	Fixed -resub bug.
 * 	File was being read without being opened.
 * 	[91/10/27  15:24:08  damon]
 * 
 * 	lock_hold_file() and unlock_hold_file() are now functions
 * 	[91/09/18  11:03:53  ezf]
 * 
 * 	Now uses COPYHOLD function to read hold file.
 * 	[91/09/09  15:09:26  damon]
 * 
 * 	checks for local programs, diff and rcsdiff3
 * 	[91/08/30  15:46:49  ezf]
 * 
 * 	Moved call to sci_lookup_leader to prevent seg fault
 * 	[91/08/28  09:15:15  damon]
 * 
 * 	Removed -no_merge -no_build_ci -no_build_co
 * 	[91/08/16  12:51:50  damon]
 * 
 * 	Now removes <time>.bcssteps file.
 * 	[91/08/14  13:27:12  damon]
 * 
 * 	now checks for compatible versions of btools,
 * 	write_header_info() now uses getfullname()
 * 	[91/08/12  15:37:31  ezf]
 * 
 * 	Changed calls to sci_add_to_list to match sci_rcs.c
 * 	[91/08/11  19:10:35  damon]
 * 
 * 	No longer complains about hold file after reporting held files.
 * 	Correctly handles tutorial submissions:
 * 	  Used to be ignored.
 * 	  Does not permit mixed tutorial/non tutorial submissions.
 * 	[91/08/10  18:21:25  damon]
 * 
 * 	Shared sandbox and comment leader NONE support
 * 	[91/08/07  12:27:30  damon]
 * 
 * 	Putting all bsubmit code in synch
 * 	[91/08/05  17:06:59  damon]
 * 
 * 	Added more defuncting code. Changed to use SCI_ELEM/SCI_LIST
 * 	[91/08/02  16:56:19  damon]
 * 
 * 	First version using library version of SCAPI
 * 	[91/07/31  20:09:55  damon]
 * 
 * 	First version with merging
 * 	[91/07/30  14:22:26  damon]
 * 
 * 	Added call to sci_set_source_info
 * 	[91/07/25  13:58:56  damon]
 * 
 * 	Cleaner
 * 	[91/07/23  14:50:21  damon]
 * 
 * 	Everything but defunct, some resub, merge
 * 	[91/07/22  17:53:21  damon]
 * 
 * 	Have everything up to and including ci_to_build working minimally
 * 	[91/07/18  12:58:30  damon]
 * 
 * 	First new version to use hold file
 * 	[91/07/15  14:50:23  damon]
 * 
 * 	First round of SCAPI changes
 * 	[91/07/15  08:49:50  damon]
 * 
 * 	updated print_usage() and print_revision()
 * 	[91/06/11  12:47:40  ezf]
 * 
 * 	Corrected core dump on -debug in search_for_user ().
 * 	[91/01/10  12:29:11  randyb]
 * 
 * 	Implemented Tools II including interface.
 * 	[91/01/08  14:49:23  randyb]
 * 
 * 	Upgrade to Tools II and new user interface
 * 	[91/01/03  16:47:40  randyb]
 * 
 * 	Corrected arguments for build_base_dir
 * 	[90/12/10  16:06:18  randyb]
 * 
 * 	Added ability to determine backing tree by using the rc variable
 * 	[90/12/07  13:56:56  randyb]
 * 
 * 	Put in changes to create and use file-by-file tracking log
 * 	[90/12/05  15:25:55  randyb]
 * 
 * 	Major change in how logs are handled.  They are now updated through
 * 	the network using Kerberose.  The calls in bsubmit to functions in
 * 	"lockcmds.c" were changed to reflect the differences made to those
 * 	functions.
 * 	[90/11/29  14:56:57  randyb]
 * 
 * 	Checks but does not require tracking file.
 * 	Uses the build's .sandboxrc file instead of creating one.
 * 	Reads the project's build directory, default build, and default set for
 * 	  the default build from the rc files.
 * 	Determines whether or not to ask for defect number based on rc file
 * 	[90/11/14  09:56:07  randyb]
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
**	This program takes a set and submits it to a shared sandbox or
**	the default build.  It takes a series of options to indicate
**	which parts of its many functions it should do.
 */
static const char * rcsid = "$RCSfile: bsubmit_s.c,v $ $Revision: 1.1.8.9 $ $Date: 1994/02/03 22:33:42 $";
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ode/builddata.h>
#include <ode/interface.h>
#include <ode/lockcmds.h>
#include <ode/misc.h>
#include <ode/run.h>
#include <ode/sci.h>
#include <ode/util.h>
#include "bsubmit.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

/*
 * These programs must exist on the local (client) system.
 * They are invoked using dummy arguments to verify that they
 * are properly installed and executable.
 */
#ifndef RCSDIFF
#    define	RCSDIFF		"rcsdiff"
#endif
#ifndef DIFF
#    define	DIFF		"diff /dev/null /dev/null"
#endif
#ifndef RCSDIFF3
#    define	RCSDIFF3	"rcsdiff3 /dev/null /dev/null /dev/null /dev/null /dev/null"
#endif


		      /* globals */
  const char  * progname = "bsubmit";                     /* name of program */
  char        * sb_base = NULL,
              * sb,                                        /* sandbox name */
              * sb_rcfile;                         /* sandbox rc file name */
  BOOLEAN       log_lock = FALSE;              /* is the logs file lock on */
  SETINFO     * setinfo_g;                      /* points to set information */
  SCI_LIST file_set_g;
  int submit_stage = PREPARING;
  int resub_stage = MERGING;
extern char * check_out_config;
  char * defect_number,
       * submit_set = NULL,
       * submit_user_name,
       * coc_str = NULL,
       * user_set = NULL,
       * user_id = NULL,
       * user_sandbox = NULL;
  char * old_rev_file;
  char * recover_time;
  char * recover_date;
  BOOLEAN resub_op;
  BOOLEAN remove_op;
  BOOLEAN outdate_op;
  BOOLEAN already_held;
  char * bcsfile;

/*
 * FIXME
 * It would be nice to make the following variable non-global again or
 * at least separate out the parts needed for sig_int.
 */
  SHARED_F    sfiles_g;                                  /* the shared files */

int file_mode;

#define CHANGED_OP	"-changed"
#define SAVED_OP	"-saved"

    UIINIT init [] = {                      /* initialize the user interface */
      { AUTOOUT_OP,  1, OVERWRITE,  0, 0, "" },
      { CHANGED_OP,      1, OVERWRITE,  0, 0, "" },
      { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
      { ALL_OP,      1, OVERWRITE,  0, 0, "" },
      { LOCAL_CO_OP, 1, OVERWRITE,  0, 2, "backing lock" },
      { RM_OP,    1, OVERWRITE,  1, 1,
				       "[1-9]:[0-5][0-9] [12][0-9]:[0-5][0-9]"},
      { RESUB_OP,    1, OVERWRITE,  1, 1,
				       "[1-9]:[0-5][0-9] [12][0-9]:[0-5][0-9]"},
      { DATE_OP,     1, OVERWRITE,  1, 1, "[1-9]/[1-9]/[0-9][0-9] [1-9]/[1-3][0-9]/[0-9][0-9] 1[0-2]/[1-9]/[0-9][0-9] 1[0-2]/[1-3][0-9]/[0-9][0-9]" },
      { FN_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
      { DEFECT_OP,   1, OVERWRITE,  1, 1, "[0-9] [0-9][0-9] [0-9][0-9][0-9] [0-9][0-9][0-9][0-9] n/a" },
      { LOG_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
      { SET_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
/*
 * Leave for future fix of -back
 *
      { BACK_OP,     1, OVERWRITE,  1, 1, ARGS_OP },
 */
      { SB_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
      { TAG_OP,      1, OVERWRITE,  1, 1, ARGS_OP },
      { ARGS_OP,     UNLIMITED, OVERWRITE,  0, 0, "" }
    };


/*
 * table of local programs required by bsubmit
 * (these tools must be found in the current PATH)
 */
static const char *local_tools[] =
{
    DIFF,
    RCSDIFF3,
    NULL	/* end of table */
};


#ifdef notdef
/* these programs reside on the server and are run remotely */
static revinfo remote_vers[] =
{
    { LOGSUB,		MINVER_LOGSUBMIT,	MAXVER_LOGSUBMIT },
    { "rcsacl",		MINVER_RCSACL,		MAXVER_RCSACL },
    { "rcsauth",	MINVER_RCSAUTH,		MAXVER_RCSAUTH },
    { "srcauth",	MINVER_RCSAUTH,		MAXVER_RCSAUTH },
    { "subauth",	MINVER_RCSAUTH,		MAXVER_RCSAUTH },
    { NULL,		NULL,			NULL }	/* end of table */
};
#endif

/*
 * PROTOTYPES
 */
int general_setup (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  struct rcfile * contents );
void
setup_for_bcs ( 
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
    SCI_LIST * file_set);
void
validate_submission ( SCI_LIST , SETINFO * , SHARED_F * );
int rm_submit_work ( 
  SCI_LIST file_set,
  SETINFO   * setinfo,                        /* points to set information */
  SHARED_F  * sfiles);                                 /* the shared files */
void
submit (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set,
  struct rcfile * contents );
void
prepare_logs (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set );
int
remove_tracks ( 
  SHARED_F  * sfiles );                                /* the shared files */
void
write_logs (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles );                                /* the shared files */
void
write_tracks ( SHARED_F * sfiles, 
    FILE      * trackf,                      /* the running total track file */
    const char * msg,                                      /* string to write */
    const char * trackfile );               /* the step-by-step tracking file */
void
local_work (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F * sfiles,
  SCI_LIST file_set );
void
fill_in_sfiles (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles );                                /* the shared files */
int load_submit_state ( 
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST * file_set );
void
hold_files_in_build (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
    SCI_LIST file_set );
void
parse_steps ( 
  SCI_LIST file_set,
  SHARED_F * sfiles);                                 /* the shared files */
int make_resub_filelist (
    FILE      * ptr_holds,                         /* pts to file with holds */
    SETINFO   * setinfo,                        /* points to set information */
  SCI_LIST * file_set );
void
parse_tracks (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles );                                /* the shared files */
void
create_update_files ( 
    SETINFO   * setinfo,                        /* points to set information */
    char      * update_f,                       /* name of file to write in */
    char      * defunct_f,                       /* name of file to write in */
  SCI_LIST file_set );
int	user_log_input ( 
  SETINFO   * setinfo,                        /* points to set information */
  char      * sbpath,                                   /* name of sandbox */
  SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set );
BOOLEAN	write_header_info (
  SETINFO   * setinfo,                        /* points to set information */
  FILE      * ptr_log,                          /* ptr to file to write in */
  char      * sbpath,                       /* path to and name of sandbox */
  SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set );
BOOLEAN	append_log ( 
    char      * name,                           /* name of file to copy from */
    FILE      * to );                              /* ptr to file to copy to */
BOOLEAN	sort_log_files (
    char      * update_f,                                /* update file name */
    char      * defunct_f );                            /* defunct file name */
int
src_ctl_cmpnum( char *r1, char *r2 );
int getenv_user2 ( SETINFO * setinfo );
void
load_submit_rc_values ( 
    struct      rcfile * contents,          /* to hold contents of sb rcfile */
    SETINFO   * setinfo );                      /* points to set information */
void
chdir_to ( 
    char      * dir,                               /* directory to change to */
    SETINFO   * setinfo );                      /* points to set information */
void
print_sfiles ( 
    SHARED_F  * sfiles );                                /* the shared files */

/*
 * END PROTOTYPES
 */

void
exit_bsubmit ( int status )
{
  exit ( status );
} /* end exit_bsubmit */

void
exit_with_resub ( BOOLEAN problems )
{
  ui_print ( VALWAYS, "\n" );
  if ( problems )
    ui_print ( VALWAYS, "Please take appropriate steps and re-submit.\n\n"
               );
  /* end if */
  ui_print ( VALWAYS, "*** RE-SUBMISSION REQUIRED ***\n\n" );
  ui_print ( VCONT, "- Source control information is in an intermediate state.\n" );
  ui_print ( VCONT, "- Re-submit using -resub %s [ -date %s ]\n\n",
		    setinfo_g->ttime, setinfo_g->tdate );
  exit_bsubmit ( ERROR );
}

void
exit_without_resub ( int problems )
{
  if ( submit_stage >= VALIDATING )
    if ( hold_cleanup ( sfiles_g . holdline, file_set_g, submit_set, TRUE ) != OK)
      exit_with_resub ( TRUE );
    /* if */
    remove_tracks ( &sfiles_g );

  /* if */
  ui_print ( VALWAYS, "\n" );
  if ( problems )
    ui_print ( VALWAYS, "Please take appropriate steps and run bsubmit again.\n"
               );
  /* end if */
  ui_print ( VALWAYS, "- No work has been done for this submission.\n" );
  ui_print ( VALWAYS, "- No files have been changed in any way.\n" );
  ui_print ( VALWAYS, "- The files in this submission are not held.\n" );
  ui_print ( VALWAYS, "- The use of the -resub option is not required and will not be recognized.\n\n" );
  exit_bsubmit ( ERROR );
}

void
cleanup ( int problems )

	/* This procedure removes any extraneous files which
	   bsubmit has created before exiting. */

{
  if ( submit_stage < MERGING && ! resub_op )
    exit_without_resub ( problems );
  else
    exit_with_resub ( problems );
  /* end if */
}                                                                 /* cleanup */

void sig_int ( int sig )

	/* This procedure handles any interrupts; cleaning up
	   before exiting. */

	  							 /* ARGSUSED */
{
  ui_print ( VALWAYS, "\n\n*** SUBMISSION INTERRUPTED BY USER ***\n" );
  cleanup ( FALSE );
} /* end sig_int */

extern BOOLEAN oxm_local;

void
main ( 
    int         argc,                /* the number of command line arugments */
    char     ** argv)                          /* strings with each argument */

{
  struct rcfile contents;
  FILE * odexm_args;
  char buf [MAXPATHLEN];

  signal ( SIGINT, sig_int );

 /*
  * Parse the command line
  */
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );
  odexm_args = fopen ( ui_entry_value ( ARGS_OP, 1 ), "r" );
  fgets ( buf, sizeof (buf), odexm_args ); /* read ODE version string */
  rm_newline ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  user_set  = strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  user_sandbox  = strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  submit_set  = strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  coc_str  = strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  submit_user_name = strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  defect_number = strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  already_held = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  resub_op = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  remove_op = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  outdate_op = str_to_BOOLEAN ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  recover_time = strdup ( buf );
  fgets ( buf, sizeof (buf), odexm_args );
  rm_newline ( buf );
  recover_date = strdup ( buf );
  if ( !resub_op && !remove_op ) {
    sci_new_list ( &file_set_g );
    while ( fgets ( buf, sizeof (buf), odexm_args ) != NULL ) {
      rm_newline ( buf );
      sci_add_to_list_as_is ( file_set_g, buf );
    } /* while */
  } /* if */
  fclose ( odexm_args );
  if ( strcmp ( submit_set, user_set ) == 0 ) {
    ui_print ( VWARN, "User's set cannot be the same as the submit set.\n" );
    ui_print ( VCONT, "User's set and submit set are both: %s\n", submit_set );
    cleanup ( TRUE);
  } /* if */
  getenv_user ( &user_id );
  oxm_local = TRUE;

  sci_init2 ( submit_set );
  setinfo_g = ( SETINFO * ) malloc ( sizeof ( SETINFO ));

 /*
  * if resubmission, get prev time
  */
  get_date ( setinfo_g->date, setinfo_g->time );
  if ( resub_op || remove_op || already_held ) {
    strcpy ( setinfo_g->ttime, recover_time );
    /* if different date specified, use it */
    if ( recover_date != NULL && *recover_date != '\0' )
      strcpy ( setinfo_g->tdate, recover_date );
    else
      strcpy ( setinfo_g->tdate, setinfo_g->date );
  } else {         /* default values are now, today, and start at beginning */
    strcpy ( setinfo_g->ttime, setinfo_g->time );
    strcpy ( setinfo_g->tdate, setinfo_g->date );
  } /* else */

  ui_print ( VALWAYS, "%s\n", setinfo_g->ttime );
  ui_print ( VALWAYS, "%s\n", setinfo_g->tdate );

  if ( general_setup ( setinfo_g, &sfiles_g, &contents ) == ERROR )
    cleanup ( TRUE );
  setup_for_bcs ( setinfo_g, &sfiles_g, &file_set_g );
  if ( !remove_op || resub_stage != MERGING ) {
    validate_submission ( file_set_g, setinfo_g, &sfiles_g );
  } /* if */ 
  submit_stage = resub_stage;
  if ( remove_op ) {
    rm_submit_work ( file_set_g, setinfo_g, &sfiles_g );
  } else {
    sci_trackfile ( sfiles_g . trackbcsstep, bcsfile );
    if ( submit_stage < OUTDATING ) {
      submit ( setinfo_g, &sfiles_g, file_set_g, &contents );
      ui_print ( VALWAYS, "\nUpdating log files\n" );
      ui_print ( VALWAYS, "------------------\n" );
      prepare_logs ( setinfo_g, &sfiles_g, file_set_g );
      write_logs ( setinfo_g, &sfiles_g );
      write_tracks ( &sfiles_g, setinfo_g -> tracks , SUBMIT_DONE,
                     (&sfiles_g) -> trackbcsstep );
    } /* if */
    local_work ( setinfo_g, &sfiles_g, file_set_g );
  }
  fclose ( setinfo_g->tracks );
  if ( unlink ( sfiles_g.trackfile ) == ERROR ) {
    ui_print ( VWARN, "unable to remove track file: %s.\n",
                       sfiles_g.trackfile );
  } /* if */
  if ( !remove_op || resub_stage != MERGING ) {
    if ( unlink ( old_rev_file ) == ERROR )
      ui_print ( VWARN, "unable to remove old revs file: %s.\n",
                         old_rev_file );
    /* if */
  } /* if */
  rename ( sfiles_g.usr_log, ui_entry_value ( ARGS_OP, 1 ) );
  exit_bsubmit ( OK );
}                                                                    /* main */

STATIC
void
handle_merges ( SCI_LIST file_set, SHARED_F * sfiles )
{
  FILE * odexm_args;
  SCI_ELEM sci_ptr;

  odexm_args = fopen ( ui_entry_value ( ARGS_OP, 1 ), "w" );
  for ( sci_ptr = sci_first ( file_set); sci_ptr != NULL;
        sci_ptr = sci_next ( sci_ptr ) ) {
    if ( sci_ptr -> need_merge ) {
      fprintf ( odexm_args, "%s\n", sci_ptr -> name );
    } /* if */
  } /* for */
  fclose ( odexm_args );
  if ( ! ui_is_info () ) {
    if ( unlink ( sfiles->trackfile ) == ERROR )
      ui_print ( VWARN, "unable to remove track file: %s.\n",
                         sfiles->trackfile );
    /* if */
    if ( unlink ( old_rev_file ) == ERROR )
      ui_print ( VWARN, "unable to remove old revs file: %s.\n",
                         old_rev_file );
    /* if */
    exit ( OE_MERGEREQ );
  } /* if */
} /* end handle_merges */

int general_setup (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  struct rcfile * contents )

	/* This procedure does the preliminary setup for calling
	   the bcs commands. */

{
  char set_dir[MAXPATHLEN];

  setinfo->update_snap = TRUE;                  /* initialize these booleans */
  setinfo->update_logs = TRUE;                  /* initialize these booleans */
  setinfo->defunct = FALSE;
  setinfo->changed = FALSE;
  setinfo->cmerge = TRUE;
  setinfo->dmerge = TRUE;
  setinfo->do_locking = TRUE;
  setinfo->do_merging = TRUE;
  setinfo->do_checking_out = TRUE;
  setinfo->do_updating = TRUE;
  setinfo->cci = TRUE;
  setinfo->dci = TRUE;
  setinfo->cco = TRUE;
  setinfo->dco = TRUE;

  concat ( set_dir, sizeof(set_dir), "ode2.3_server_base/sets/", user_set,
                    NULL );
  mkdir ( set_dir, S_IRWXU );
/*
  if (src_ctl_check_servers(setinfo, &contents))
  {
      ui_print(VALWAYS, "\t Problem running tools in the local environment.\n");
      return (ERROR);
  }
*/
  fill_in_sfiles ( setinfo, sfiles );
  return ( OK );
}                                                           /* general setup */


void
legal_build ( 
    char      * back,                                  /* backing tree value */
    SETINFO   * setinfo,                        /* points to set information */
    struct      rcfile   * contents)        /* to hold contents of sb rcfile */

	/* This procedure makes sure that there is a legal
	   build at the point that the user has specified.
	   It also fills in the setinfo fields. */


{
    FILE      * ptr_file;                                  /* ptr to rc file */
    char        line [ PATH_LEN ],                            /* misc string */
                setfile [ PATH_LEN ],         /* holds path to sb set rcfile */
              * line_ptr,                      /* a way to traverse the line */
              * token;                         /* individual parts of a line */

  if ( *back != SLASH ) {
    if (( token = build_base_dir ( back, contents, ui_ver_level () >= VDETAIL,
				   FALSE )) == NULL )
      uquit ( ERROR, TRUE,
        "\tbuild name, %s, must start with '/' or be in build list.\n", back );
    
    concat ( line, PATH_LEN, token, "/", back, NULL );
    
    if ( ui_load ( BACK_OP, 1, line ) == ERROR )
      uquit ( ERROR, FALSE, "\tunable to load backing tree: %s.\n", line );
  } /* if */

  concat ( setfile, PATH_LEN, back, "/", SET_RC, NULL );

  if (( ptr_file = fopen ( setfile, READ )) == NULL )
    uquit ( ERROR, FALSE, "\tcould not open build rc file: %s.\n", setfile );

  while (( line_ptr = fgets ( line, PATH_LEN, ptr_file )) != NULL ) {
    token = nxtarg ( &line_ptr, WHITESPACE );

    if ( streq ( token, DEFAULT ))
      break;
  } /* while */

  fclose ( ptr_file );

  if ( line_ptr == NULL )
    uquit ( ERROR, FALSE, "\tno default set in build rcfile: %s.\n", setfile );

  token = nxtarg ( &line_ptr, WHITESPACE );

  if (( *token < 'A' ) || ( *token > 'Z' ))
    uquit ( ERROR, FALSE, "\tdefault set in build rcfile: %s,\n%s\n",
		           token, "  must start with captial letter." );

  strcpy ( setinfo->b_set, token );
  path ( back, setinfo->b_base, setinfo->b_name );
				     /* breaks build path into base and name */
  concat ( setinfo->b_src_dir, PATH_LEN, back, "/", SRC_DIR, NULL );
  concat ( setinfo->b_rcfile, PATH_LEN, back, "/", SANDBOXRC, NULL );

  if ( access ( setinfo->b_rcfile, R_OK ) != OK )
    uquit ( ERROR, FALSE, "\tcould not read build's rc file: %s\n",
			  setinfo->b_rcfile );
}                                                             /* legal build */

void
specify_build_info ( 
    SETINFO   * setinfo )                        /* points to set information */

	/* This procedure prints out the setinfo information.
	   It is only called with the verbose flag. */


{
  ui_print( VDETAIL, "build to submit to is: %s.\n", setinfo->b_name );
  ui_print( VDEBUG, "directory path to build is: %s.\n", setinfo->b_base );
  ui_print( VCONT, "directory to build source is: %s.\n", setinfo->b_src_dir );
  ui_print( VCONT, "set name for build is: %s.\n", setinfo->b_set );
  ui_print( VCONT, "use build's rc file: %s.\n", setinfo->b_rcfile );
  ui_print( VCONT, "submission cover: %s.\n", setinfo->submit_cover );
  ui_print( VCONT, "submission host: %s.\n", setinfo->submit_host );
  ui_print( VCONT, "submission base: %s.\n", setinfo->submit_base );
  ui_print( VCONT, "submission owner: %s.\n", setinfo->submit_owner );

  if ( setinfo->defect_num )
    ui_print( VCONT, "will ask for defect numbers.\n" );
  else
    ui_print( VCONT, "will not ask for defect numbers.\n" );
}                                                      /* specify build info */



BOOLEAN	build_is_locked ( SETINFO * setinfo )

	/* This procedure checks to see if there is a lock on the
	   entire build.  If there is, it prints out the lock
	   message and returns TRUE.  If not, it returns FALSE. */
{
  int status;
  OXM_CNXTN rcs_monitor;
  int i;
  ERR_LOG log;
  const char *av [16];

  ui_print ( VDETAIL, "checking for lock on build.\n" );
  log = oxm_open ( &rcs_monitor, 0 );
  i = 0;
  av [i++] = CHECKLOCKSB;
  log = oxm_runcmd ( rcs_monitor, i , av, NULL );
  log = oxm_endcmd ( rcs_monitor, &status );
  log = oxm_close ( rcs_monitor );

  switch ( status ) {
    case WAITING:
      ui_print ( VALWAYS, "The build being submitted to: %s/%s\n",
	                setinfo->b_base, setinfo->b_name );
      ui_print ( VCONT, "is locked.  Cannot continue.\n" );

      return ( TRUE );

    case OK:
      break;

    case NO_OPT:
    default:
      ui_print ( VFATAL, "syntax error %d in logsubmit(6).\n%s\n",
                          status, NOTIFY );
      return ( ERROR );
  } /* switch */

  return ( FALSE ); 
}                                                         /* build is locked */

void
list_sci_files ( SCI_LIST file_set )
{
  SCI_ELEM sci_ptr;

  for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
        sci_ptr = sci_next ( sci_ptr ) ) {
    ui_print ( VALWAYS, "%s\n", sci_ptr -> name );
  } /* end for */
}

void
validate_submission ( SCI_LIST file_set, SETINFO * setinfo, SHARED_F * sfiles )
{
  SCI_ELEM sci_ptr;
  int merge_flag;
  int problems;
  int missing_files;
  int not_in_set;
  int no_branch;
  FILE * old_rev_f;
  struct stat st;

  ui_print ( VDEBUG, "Entering validate_submission\n" );
  submit_stage = VALIDATING;
  ui_print ( VALWAYS, "\nValidating submission\n" );
  ui_print ( VALWAYS, "---------------------\n" );
  problems = FALSE;
#ifdef notdef
  if ( sci_validate_submit_set_list ( file_set, submit_set ) != TRUE) {
	cleanup (TRUE);
  }
#endif
  if ( sci_real_fast_lookup_user_rev_list ( file_set, user_set,
       &missing_files ) != OK ) {
    problems = TRUE;
  }
  if ( resub_stage < OUTDATING ) {
    if ( missing_files ) {
      ui_print ( VNORMAL, "missing files\n" );
      problems = TRUE;
    } /* if */
    if ( sci_lookup_leader_list ( file_set ) != OK )
      cleanup ( TRUE );
    /* end if */
    if ( sci_lookup_merge_rev_list ( file_set , submit_set,
                                     coc_str  ) != OK )
      cleanup ( TRUE );
    /* if */
    if ( ! remove_op && ! resub_op ) {
      if( stat ( old_rev_file, &st ) == 0 ) {
        ui_print ( VWARN, "You already have another submission using the\n" );
        ui_print ( VCONT, "timestamp %s. Try again in a minute.\n",
                          setinfo->ttime );
        cleanup ( TRUE );
      } /* if */;
      old_rev_f = fopen ( old_rev_file, WRITE );
      for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
            sci_ptr = sci_next ( sci_ptr ) ) 
        fprintf ( old_rev_f, "%s\t%s\n", sci_ptr -> name,
                           sci_ptr -> ver_merge );
      /* for */
      fclose ( old_rev_f );
    } /* if */
    if ( sci_ancestry_list ( file_set ) != OK ) 
      cleanup ( TRUE );
    /* if */
    if ( sci_ancestor_list ( file_set ) != OK )  {
      ui_print ( VALWAYS, "Missing common ancestor for file(s):\n" );
      for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
            sci_ptr = sci_next ( sci_ptr ) ) 
        ui_print ( VALWAYS, "  %s\n", sci_ptr -> name );
      /* for */
      cleanup ( TRUE );
    } /* if */

  } /* if */
    if ( is_in_error ( ) )
      cleanup ( TRUE );
    /* end if */
    merge_flag = FALSE;
    if ( ! resub_op && ! remove_op ) {
      sci_ptr = sci_first ( file_set );
      while ( sci_ptr != NULL) {
        if ( sci_ptr -> need_merge ) {
          if ( ! merge_flag ) {
            ui_print ( VALWAYS, "The following file(s) will require user\n" );
            ui_print ( VCONT, "interaction during the merge step:\n" );
          } /* end if */
          ui_print ( VALWAYS, "  %s\n", sci_ptr -> name );
          merge_flag = TRUE;
        }
        sci_ptr = sci_next ( sci_ptr );
      } /* end while */
      if ( ! merge_flag ) {
        ui_print ( VALWAYS, "No user interaction will be required.\n" );
      } else if ( !problems && !resub_op && !remove_op) {
        /* This function does not return if !ui_is_info() */
        handle_merges ( file_set, sfiles );
      } /* end if */
    } /* if */
  if ( problems ) {
    ui_print ( VALWAYS, "\n*** VALIDATION FAILURE ***\n\n" );
    for ( sci_ptr = sci_first ( file_set) ; sci_ptr != NULL;
          sci_ptr = sci_next ( sci_ptr ) ) {
      not_in_set = FALSE;
      no_branch = FALSE;
      if ( sci_ptr -> ver_user == NULL )
        not_in_set = TRUE;
      if ( ! sci_ptr -> has_user_branch )
        no_branch = TRUE;
      if ( not_in_set || no_branch ) {
        ui_print ( VCONT, "%s --", sci_ptr -> name );
        if ( not_in_set ) {
          ui_print ( VCONT, " not in set." );
          ui_print ( VCONT, "\n" );
          continue;
        } /* end if */
        if ( no_branch )
          ui_print ( VCONT, " no check-ins." );
        /* end if */
        ui_print ( VCONT, "\n" );
      } /* end if */
    } /* end for */
    ui_print ( VCONT, "\nConsult the bsubmit reference page for\n" );
    ui_print ( VCONT, "suggested corrective actions.\n" );
    cleanup ( TRUE );
  } /* end if */
  ui_print ( VDEBUG, "Leaving validate_submission\n" );
} /* validate_submission */


void
setup_for_bcs ( 
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
    SCI_LIST * file_set)

	/* This procedure does the preliminary setup for calling
	   the bcs commands including making the list of files
	   to submit. */


{
  SCI_ELEM sci_ptr;
  BOOLEAN found_non_tut;

  ui_print ( VDEBUG, "Entering setup_for_bcs\n" );
  if ( resub_op || remove_op ) {
    if ( load_submit_state ( setinfo, sfiles, file_set ) != OK)
      cleanup ( FALSE );
    /* if */
    if ( resub_op ) {
      ui_print ( VALWAYS, "outdate_list\n" );
      ui_print ( VALWAYS, "%d\n", sci_elem_cnt ( *file_set ) );
      for ( sci_ptr = sci_first ( *file_set ); sci_ptr != NULL;
            sci_ptr = sci_next ( sci_ptr ) ) {
        ui_print ( VALWAYS, "%s\n", sci_ptr -> name );
      } /* for */
    } /* if */
  } else {
    if (( setinfo->tracks = fopen ( sfiles->trackfile, WRITE )) == NULL ) {
      ui_print ( VFATAL, "Cannot create tracking file: %s.\n",
                             sfiles->trackfile );
      cleanup ( TRUE );
    } /* end if */
  } /* if */

  found_non_tut = FALSE;
  for ( sci_ptr = sci_first ( *file_set ); sci_ptr != NULL;
        sci_ptr = sci_next ( sci_ptr ) ) {
    if ( strncmp ( sci_ptr -> name, TUTORIAL, TUT_CT ) == 0 ) {
      if ( found_non_tut ) {
        ui_print ( VFATAL, "Cannot mix tutorial and non-tutorial submissions.\n" );
        cleanup ( TRUE );
      } /* end if */
      setinfo -> update_logs = FALSE;
    } else
      found_non_tut = TRUE;
    /* end if */
  } /* end for */

  if (( ui_ver_level () >= VDETAIL ) && ! setinfo->update_snap )
    ui_print ( VDETAIL, "Tutorial submission, SNAPSHOT will not be updated.\n");
  if ( ! already_held && ! resub_op && ! remove_op ) {
    hold_files_in_build ( setinfo, sfiles, *file_set );
  }
  ui_print ( VDEBUG, "Leaving setup_for_bcs\n" );
}                                                           /* setup for bcs */

void
load_old_revs ( SCI_LIST file_set )
{
  FILE * old_rev_f;
  char merge_line [MAXPATHLEN];
  char * merge_file;
  char * ver_merge;
  BOOLEAN found;
  char * m_ptr;
  SCI_ELEM sci_ptr;

  old_rev_f = fopen ( old_rev_file, READ );
  if ( old_rev_f != NULL ) {
    while ( fgets ( merge_line, MAXPATHLEN, old_rev_f ) != NULL ) {
      found = FALSE;
      m_ptr = merge_line;
      merge_file = strdup ( nxtarg ( &m_ptr, WHITESPACE ) );
      ver_merge = strdup ( nxtarg ( &m_ptr, WHITESPACE ) );
      for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
            sci_ptr = sci_next ( sci_ptr )  ) {
        if ( strcmp ( merge_file, sci_ptr -> name) == 0 ) {
          sci_ptr -> ver_merge = ver_merge;
          found = TRUE;
          break;
        } /* if */
      } /* for */
      if ( ! found ) {
        ui_print ( VFATAL, "Discrepancy between merge revision file and hold file.\n" );
        ui_print ( VCONT, "A file listed in the merge revision file was not present in the hold file.\n" );
        ui_print ( VCONT, "File: '%s'\n", merge_file );
        cleanup ( TRUE );
      } /* if */
    } /* while */
  } /* if */
  
  fclose ( old_rev_f );
} /* end load_old_revs */

int rm_submit_work ( 
  SCI_LIST file_set,
  SETINFO   * setinfo,                        /* points to set information */
  SHARED_F  * sfiles)                                  /* the shared files */
{
  int missing_revs;

  /* If submit_stage == MERGING,
   * no check-ins or updates to the backing build have been done */
  /* so no special work needs to be done. */
  if ( submit_stage != MERGING ) {
    ui_print ( VALWAYS, "\nRemoving submissions\n" );
    ui_print ( VALWAYS, "--------------------\n" );
    load_old_revs ( file_set );
    parse_steps ( file_set, sfiles );
    if ( sci_real_fast_lookup_latest_rev_list ( file_set, submit_set,
                                      &missing_revs ) != OK )
      cleanup ( TRUE );
    /* if */
    sci_rm_submit ( file_set, submit_set );
  } /* if */
  if ( hold_cleanup ( sfiles -> holdline, file_set, submit_set, TRUE ) != OK)
    exit_with_resub ( TRUE );
  /* if */
  return ( OK );
} /* end rm_submit_work */

void
parse_steps ( 
  SCI_LIST file_set,
  SHARED_F * sfiles)                                  /* the shared files */
{
  BOOLEAN     found = FALSE;                               /* misc boolean */
  FILE * f;
  char donefile [ MAXPATHLEN ];
  SCI_ELEM sci_ptr;
  SCI_ELEM last = NULL;

  if ( remove_op )
    for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
          sci_ptr = sci_next ( sci_ptr )  )
      sci_ptr -> skip = TRUE;
    /* for */
  /* if */
  f = fopen ( sfiles -> trackbcsstep, READ );
  if ( f != NULL ) {
    while ( fgets ( donefile, MAXPATHLEN, f ) != NULL ) {
      found = FALSE;
      rm_newline ( donefile );
      for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
            sci_ptr = sci_next ( sci_ptr )  ) {
        if ( strcmp ( donefile, sci_ptr -> name) == 0 ) {
          if ( remove_op ) {
            sci_ptr -> skip = FALSE;
            last = sci_ptr;
          } else
            sci_ptr -> skip = TRUE;
          /* if */
          found = TRUE;
          break;
        } /* if */
      } /* for */
      if ( ! found ) {
        ui_print ( VFATAL, "Discrepancy between bcs tracking file and hold file.\n" );
        ui_print ( VCONT, "A file listed in the bcs tracking file was not present in the hold file.\n" );
        ui_print ( VCONT, "File: '%s'\n", donefile );
        cleanup ( TRUE );
      } /* if */
    } /* while */

    if ( remove_op ) {
      /* If N files are listed in the bcssteps file, then assume that at */
      /* least N+1 files were co'd. If N = all of the files, then just N */
      /* files were co'd. This is because the co operation may have */
      /* succeeded but not been recorded. */
      if ( last == NULL )
        sci_ptr = sci_first ( file_set );
      else
        sci_ptr = sci_next ( last );
      /* if */
      if ( sci_ptr != NULL )
        sci_ptr -> skip = FALSE;
      /* if */
    } /* if */

  } /* if */
} /* end parse steps */

int load_submit_state ( 
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST * file_set )

	/* This procedure checks whether the submission is a retry
	   of a previous one.  If it is, it skips the steps which
	   have been done; if not, it sets up the tracking file. */


{
  FILE      * ptr_holds;                         /* pts to file with holds */
  char        line [ PATH_LEN ];                            /* misc string */
  BOOLEAN     found = FALSE;                               /* misc boolean */

  ui_print ( VDETAIL, "checking HOLD file: %s %s\n", sfiles->usr_hold,
                      sfiles->holdfile );
  if (( ptr_holds = fopen ( sfiles->holdfile, READ )) == NULL ) {
    ui_print ( VFATAL, "could not read hold file: %s.\n", sfiles->holdfile );
    return ( ERROR );
  }

  while ((( fgets ( line, STRING_LEN, ptr_holds )) != NULL ) && ( ! found )) {
    rm_newline ( line );
    if ( streq ( line, sfiles->holdline )) {   /* find user's existing holds */
      make_resub_filelist ( ptr_holds, setinfo, file_set );
      found = TRUE;
    } /* if */
  } /* while */

  fclose ( ptr_holds );

  if ( ! found ) {
    ui_print ( VFATAL, "No entry for: %s,\n\tin file: %s.\n",
                           sfiles->holdline, sfiles->holdfile );
    cleanup ( FALSE );
  }
  parse_tracks ( setinfo, sfiles );

  if (( setinfo->tracks = fopen ( sfiles->trackfile, APPEND )) == NULL ) {
    ui_print ( VFATAL, "Cannot append to tracking file: %s.\n",
                           sfiles->trackfile );
    cleanup ( TRUE );
  } /* if */
  if ( resub_stage != CHECKING_OUT )
    parse_steps ( *file_set, sfiles );
  /* if */
  return ( OK );
} /* end load_submit_state */




int make_resub_filelist (
    FILE      * ptr_holds,                         /* pts to file with holds */
    SETINFO   * setinfo,                        /* points to set information */
  SCI_LIST * file_set )

	/* This procedure assembles the list of files to submit.
	   It does this by reading in the each line from the
	   resubmit tracking file. */


{
    char        filebuf [ PATH_LEN ],                         /* misc string */
              * ptr_buff;                                /* misc ptr to char */

  if ( sci_new_list ( file_set ) != OK )
    cleanup ( TRUE );
  /* end if */
  while ((( fgets ( filebuf, STRING_LEN, ptr_holds )) != NULL ) &&
	 ( *filebuf != COLON )) {
    if ( *filebuf == '\n' )
      continue;
    rm_newline ( filebuf );

    if (( ptr_buff = strdup ( filebuf )) == NULL ) {
      ui_print ( VFATAL, "No room for strdup of: %s\n", filebuf );
      cleanup ( TRUE );
    } /* if */
    if ( sci_add_to_list_as_is ( *file_set, ptr_buff ) != OK )
      cleanup ( TRUE );
    /* end if */
  } /* while */
  return ( OK );
}                                                     /* make resub filelist */

void
parse_tracks (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles )                                 /* the shared files */


	/* This procedure reads through the tracks files and determines
	   which steps have already been taken. */
{
    char        line [ PATH_LEN ];                            /* misc string */

  if (( setinfo->tracks = fopen ( sfiles->trackfile, READ )) != NULL ) {
    while (( fgets ( line, STRING_LEN, setinfo->tracks )) != NULL ) {
      rm_newline ( line );               /* set skips for steps already done */

      if ( streq ( SUBMIT_DONE, line )) {
        resub_stage = OUTDATING;
      } /* if */
    } /* while */

    fclose ( setinfo->tracks );          /* close and reopen to write tracks */
  } /* if */
}                                                            /* parse tracks */


void
hold_files_in_build (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
    SCI_LIST file_set )

	/* This procedure calls routines to: lock the bsubmit hold
	   file, check to see if the files are already held, exit
	   if files are held, append the new submissions to the
	   bsubmit hold file, and unlock the hold file. */

{

  ERR_LOG log;

  if ( ui_is_info ( ) )
    ui_print ( VALWAYS, "Would append files to be submitted to hold file.\n" );
  else
    if ( ! append_to_hold_file ( sfiles -> holdline,
                                 file_set, TRUE, &log ) )
      cleanup ( FALSE );
    /* if */
  /* if */
}                                                     /* hold files in build */


void
submit (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set,
  struct rcfile * contents )

	/* This procedure runs the bcs commands that actually do the
	   submittal.  It also handles when to check for locks: if a merge
	   is being done, locks are always checked for; if a check-out is
	   being done and a check-in was not done, locks are checked for.
	   Finally, it separates the steps between changed and defunct
	   files. */


{
  int missing_revs;

  ui_print ( VALWAYS, "\nSubmitting files\n" );
  ui_print ( VALWAYS, "----------------\n" );
  if ( sci_submit ( file_set, submit_set, user_set, ui_is_info() ) != OE_OK ) {
    cleanup ( TRUE );
  } /* if */
  oxm_local = TRUE;

/*
 * The latest revs are needed to create the usr_snap file later on. This code
 * is always executed, even if this is a resubmission because the information
 * is always needed for the usr_snap file.
 */
  if (sci_real_fast_lookup_latest_rev_list 
	( file_set, submit_set, &missing_revs ) != OK)
	cleanup ( TRUE );
  oxm_local = FALSE;
  submit_stage = OUTDATING;
}                                                                  /* submit */

int
remove_tracks ( 
  SHARED_F  * sfiles )                                 /* the shared files */
{
  if (exists(sfiles->trackbcsstep) == OK &&
      unlink ( sfiles->trackbcsstep ) == ERROR ) {
    ui_print ( VFATAL, "Unable to remove track file: %s.\n",
               sfiles->trackbcsstep);
    return ( ERROR );
  } /* if */
  return ( OK );
} /* end remove_tracks */

void
write_tracks ( SHARED_F * sfiles, 
    FILE       * trackf,                      /* the running total track file */
    const char * msg,                                      /* string to write */
    const char * trackfile )                /* the step-by-step tracking file */

	/* This procedure writes to the track file and then flushes
	   it so the information is in place.  */


{
  if ( ! ui_is_info ()) {
    fprintf ( trackf, "%s\n", msg );
    fflush ( trackf );
    if ( access ( trackfile, R_OK ) == OK )
      remove_tracks ( sfiles );
    /* end if */
  } /* if */
}                                                            /* write tracks */


void
prepare_logs (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set )

	/* This procedure calls the functions need to produce the three
	   files which must be sent to the server: usr_snap, usr_defunct,
	   and usr_log. */

{
    char        sbpath [ PATH_LEN ];             /* path and name of sandbox */

  create_update_files ( setinfo, sfiles->usr_snap, sfiles -> usr_defunct,
                        file_set );

  if ( user_log_input ( setinfo, sbpath, sfiles, file_set ) != OK) {
    ui_print ( VFATAL, "Notify Release Engineering immediately(1).\n" );
    ui_print ( VCONT, "Log files need completing.\n" );
    cleanup ( TRUE );
  } /* if */

  if ( ! sort_log_files ( sfiles->usr_snap, sfiles->usr_defunct )) {
    ui_print ( VFATAL, "Log files need completing.\n" );
    cleanup ( TRUE );
  } /* if */
}                                                            /* prepare logs */

void
create_update_files ( 
    SETINFO   * setinfo,                        /* points to set information */
    char      * update_f,                       /* name of file to write in */
    char      * defunct_f,                       /* name of file to write in */
  SCI_LIST file_set )

	/* This procedure writes the files to be defuncted into
	   usr_defunct. */


{
    FILE      * def_outf, * upd_outf;             /* pointer to defunct file */
  struct sci_elem * sci_ptr;
  BOOLEAN problems;

  enter ( "create_update_file" );
  ui_print ( VDEBUG, "update_f '%s'\n", update_f );
  ui_print ( VDEBUG, "defunct_f '%s'\n", defunct_f );
  unlink ( update_f );
  if (( upd_outf = fopen ( update_f, WRITE )) == NULL ) {
    ui_print ( VFATAL, "Unable to open log file: %s.\n", update_f );
    cleanup ( TRUE );
  } /* if */
  unlink ( defunct_f );
  if (( def_outf = fopen ( defunct_f, WRITE )) == NULL ) {
    ui_print ( VFATAL, "Unable to open log file: %s.\n", defunct_f );
    fclose ( upd_outf );
    cleanup ( TRUE );
  } /* if */

  for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
        sci_ptr = sci_next ( sci_ptr ) ) 
    if ( sci_ptr -> defunct) {
      fprintf ( def_outf, "%s\t%s\n", sci_ptr -> name, DEFUNCT_MARK );
      setinfo -> defunct = TRUE;
    }
    else {
      fprintf ( upd_outf, "%s\t%s\t%s\n", sci_ptr -> name,
                           sci_ptr -> ver_latest,
                           sci_ptr -> ver_ancestor );
      setinfo -> changed = TRUE;
    } /* end if */
  /* end for */

  problems = FALSE;
  if ( ferror ( upd_outf ) || ( fclose ( upd_outf ) == EOF )) {
    ui_print ( VFATAL, "Unable to write to log file: %s.\n", update_f );
    problems = TRUE;
  } /* if */
  if ( ferror ( def_outf ) || ( fclose ( def_outf ) == EOF )) {
    ui_print ( VFATAL, "Unable to write to log file: %s.\n", defunct_f );
    problems = TRUE;
  } /* if */
  if ( problems ) {
    cleanup ( TRUE );
  } /* end if */
  leave ( );
} /* end create_update_files */



int	user_log_input ( 
  SETINFO   * setinfo,                        /* points to set information */
  char      * sbpath,                                   /* name of sandbox */
  SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set )

	/* This function prompts the user to fill out the log
	   information.  It uses an editor to get the bcs log
	   file to the user for the user to edit.  It also
	   prompts for little additonal information. */


{
    FILE      * ptr_log;                              /* pointer to tmp file */
    char      * logfile;                                  /* pts to log file */
  BOOLEAN       have_log = FALSE;                            /* misc boolean */

  if ( access ( bcsfile, W_OK ) != OK ) {
    if (( ptr_log = fopen ( bcsfile, WRITE )) == NULL ) {
      ui_print ( VFATAL, "cannot open build log, %s, to write.\n", bcsfile );
      return ( ERROR );
    } /* if */

    else
      fclose ( ptr_log );
  } /* if */
  if (( ptr_log = fopen ( sfiles->usr_log, WRITE )) == NULL ) {
    ui_print ( VFATAL, "could not create new log file, %s.\n", sfiles->usr_log);
    return ( ERROR );
  } /* if */
  if ( ! write_header_info ( setinfo, ptr_log, sbpath, sfiles, file_set ))
    return ( ERROR );

  if ( ui_is_set ( LOG_OP )) {
    if ((( logfile = ui_arg_value ( LOG_OP, 1, 1 )) != NULL ) &&
        ( access ( logfile, R_OK ) == OK ) &&
        ( append_log ( logfile, ptr_log )))
      have_log = TRUE;

    if ( ! have_log ) {
      ui_print ( VWARN, "Could not open input log: %s.\n", logfile );
      ui_print ( VCONT, "         Please edit log file.\n" );
    } /* if */
  } /* if */
  if ( ! have_log ) {
    if ( ! append_log ( bcsfile, ptr_log ))
      return ( ERROR );

    if ( unlink ( bcsfile ) == ERROR )
      ui_print ( VWARN, "bcs log file, %s, could not be removed.\n", bcsfile );
  } /* if */
  fprintf ( ptr_log, "\nEnd Log *****\n\n" );
  fclose ( ptr_log );
  return ( OK );
}                                                          /* user log input */

BOOLEAN	write_header_info (
  SETINFO   * setinfo,                        /* points to set information */
  FILE      * ptr_log,                          /* ptr to file to write in */
  char      * sbpath,                       /* path to and name of sandbox */
  SHARED_F  * sfiles,                                  /* the shared files */
  SCI_LIST file_set )

	/* This function prompts for and writes the header information
	   into the new log.  It also puts the list of files and the
	   revs into the log.  It returns TRUE unless the usr_snap
	   could not be appended to the log. */


{
  struct sci_elem * sci_ptr;
  char * tag;

  fprintf ( ptr_log, "Submission Log *****\n\n" );
  fprintf ( ptr_log, "  Submitted by %s; User name: %s\n",
			submit_user_name, user_id );
  fprintf ( ptr_log, "  Date: %s; Time: %s\n", setinfo->date, setinfo->time );

  if ( defect_number != NULL )
    fprintf ( ptr_log, "  Number of files: %d; Defect number: %s.\n",
			  file_set -> elem_cnt, defect_number );
  else
    fprintf ( ptr_log, "  Number of files: %d.\n", file_set -> elem_cnt );

  fprintf ( ptr_log, "  Set name: %s; Sandbox: %s\n", user_set, user_sandbox );

  if ( ui_is_set ( TAG_OP ) ) {
    tag = ui_arg_value ( TAG_OP, 1, 1 );
    fprintf ( ptr_log, "  Tagged list of files and revisions:\n" );
    for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
          sci_ptr = sci_next ( sci_ptr ) )
      if ( sci_ptr -> defunct) {
        fprintf ( ptr_log, "%s,v\t%s\t%s\t%s\n", sci_ptr -> name,
                  DEFUNCT_MARK, tag, setinfo -> user );
      }
      else {
        fprintf ( ptr_log, "%s,v\t%s\t%s\t%s\t%s\n", sci_ptr -> name,
                             sci_ptr -> ver_ancestor, sci_ptr -> ver_latest,
                             tag, user_id );
      } /* end if */
    /* end for */
  } /* if */
  if ( setinfo->changed ) {
    fprintf ( ptr_log, "  List of files and revisions:\n" );

    if ( ! append_log ( sfiles->usr_snap, ptr_log ))
      return ( FALSE );                        /* put submission list in log */
  } /* if */

  if ( setinfo->defunct ) {
    fprintf ( ptr_log, "  List of defunct files:\n" );

    if ( ! append_log ( sfiles->usr_defunct, ptr_log ))
      return ( FALSE );
  } /* if */

  fprintf ( ptr_log, "\n  Detailed description:\n\n" );
  return ( TRUE );
}                                                       /* write header info */



BOOLEAN	sort_log_files (
    char      * update_f,                                /* update file name */
    char      * defunct_f )                             /* defunct file name */

	/* This function sorts the user snapshot and defunct.  It
	   returns TRUE is all was sorted, FALSE otherwise. */


{
    int         status;                                      /* error output */

  status = runp ( "sort", "sort", "-o", update_f, update_f, NULL );

  if ( status != 0 ) {
    ui_print ( VFATAL, "Could not sort file: %s.\n", update_f );
    return ( FALSE );
  } /* if */

  status = runp ( "sort", "sort", "-o", defunct_f, defunct_f, NULL );

  if ( status != 0 ) {
    ui_print ( VFATAL, "Could not sort file: %s.\n", defunct_f );
    return ( FALSE );
  } /* if */

  return ( TRUE );
}                                                          /* sort log files */


void
write_logs (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles )                                 /* the shared files */

	/* This procedure calls the functions to lock the logs and
	   update all the log files. */


{
  if ( setinfo -> update_logs ) {
    if ( ui_is_info () ) { 
      ui_print ( VNORMAL, "Would update log files.\n" );
    } else { 
      if ( ! update_all_logs ( setinfo -> defunct, sfiles -> usr_snap,
                               sfiles -> usr_defunct, sfiles -> usr_log )) {
        ui_print ( VFATAL, "Log files need completing.\n" );
        cleanup ( TRUE );
      } /* if */
    } /* if */
  } else
    ui_print ( VALWAYS, "Tutorial submission, log files were not updated.\n");
  /* end if */

  if ( access ( sfiles->usr_snap, F_OK ) == OK ) {
    if ( unlink ( sfiles->usr_snap ) == ERROR )
      ui_print ( VWARN, "Could not remove user's snapshot file: %s.\n",
			 sfiles->usr_snap );
  } /* if */

  if ( access ( sfiles->usr_defunct, F_OK ) == OK ) {
    if ( unlink ( sfiles->usr_defunct ) == ERROR )
      ui_print ( VWARN, "Could not remove user's defunct file: %s.\n",
			 sfiles->usr_defunct );
  } /* if */
}                                                              /* write logs */

void
outdate_set ( 
  SCI_LIST file_set,
    SETINFO   * setinfo )                       /* points to set information */

        /* This procedure outdates a set.  It will always ask the
           user if he wants to do this unless BOTH AUTO and
           OUTDATE are set. */


{
    char        answer [ NAME_LEN ];                          /* misc string */
    BOOLEAN     okay;                                        /* misc boolean */

  ui_print ( VNORMAL, "\nOutdating User Branches\n" );
  ui_print ( VNORMAL, "-----------------------\n" );

  okay = TRUE;

  if ( ! okay ) {                           /* prompt for different co modes */
    if ( setinfo->co_mode >= CO_M_BLD ) {
      ui_print ( VALWAYS, "To check out files from the build, the files in " );
      ui_print ( VALWAYS, "the set,\n  %s, must be outdated.", setinfo->l_set );
      ui_print ( VALWAYS, "  Please verify.\nAnswer: [<y>|n] " );
      gets ( answer );
      okay = ( *answer != 'n' );
    } /* if */

    else {
      ui_print ( VALWAYS, "Outdate the submitted files from set" );
      ui_print ( VALWAYS, ": %s?\nAnswer: [<y>|n] ", setinfo->l_set );
      gets ( answer );
      okay = ( *answer != 'n' );
    } /* else */
  } /* if */

  if ( okay ) {
    if ( ui_is_info () ) {
      ui_print ( VALWAYS, "Would outdate the submitted files from the set: %s\n",
                    user_set );
    } else {
      ui_print ( VDETAIL, "Outdating the submitted files from the set: %s\n",
                           user_set );
      if ( sci_outdate_list_p1 ( file_set, user_set ) != OK )
        cleanup ( TRUE );
      /* if */
    } /* if */
  } /* if */
} /* outdate set */


void
local_work (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F * sfiles,
  SCI_LIST file_set )

	/* This procedure does any necessary checking out, outdating,
	   and clean up of the local area.  If the check out mode
	   is locked-build or less, an outdate is done; then, if it is
	   build or greater, a check out is done. */


{
    oxm_local = TRUE;

    if ( outdate_op ) {
      outdate_set ( file_set, setinfo );
    } /* if */

    if ( ui_is_info () ) {
      ui_print ( VNORMAL, "Would remove files from hold file.\n" );
    } else {
      oxm_local = FALSE;
      if ( hold_cleanup ( sfiles->holdline, file_set, submit_set, TRUE ) != OK)
        exit_with_resub ( TRUE );
      /* if */
      if ( access ( sfiles->usr_hold, F_OK ) == OK ) {
        if ( unlink ( sfiles->usr_hold ) == ERROR )
          ui_print ( VWARN, "Could not remove user's hold file: %s.\n",
    			 sfiles->usr_hold );
      } /* if */
    } /* if */
}                                                              /* local work */



/*
 * determine version by invoking command with '-version' switch,
 * capture output and scan for RCS revision number
 *	returns revision string
 *		or NULL on error
 */
char *
src_ctl_get_progver( char *prog )
{
    char cmdline[MAXPATHLEN];
    char buf[BUFSIZ];
    char *cp = NULL;
    register FILE *fp;

    strcpy(cmdline, prog);
    (void) strcat(cmdline, " -version");
    
    if ((fp = popen(cmdline, "r")) == NULL) {
	ui_print(VFATAL, "couldn't run %s to get version\n", prog);
	return NULL;
    }

    ui_print(VDEBUG, "command line is %s\n", cmdline);

    while (fgets(buf, BUFSIZ-1, fp) != NULL) {
	ui_print(VDEBUG, "got: %s", buf);
	if ((cp = strstr(buf, "Revision: ")) != NULL)
	    break;
    }
    (void) pclose(fp);
    if (cp != NULL) {
	register char *dol;

	if ((dol = strstr(cp, "$")) != NULL) {
	    --dol;
	    *dol = NUL;		/* remove trailing dollar */
	}
	cp = strstr(cp, " ");	/* skip over the "Revision:" */
	++cp;	/* skip the space */
    }
    else
	ui_print(VFATAL, "Couldn't find \"Revision\" for %s\n", prog);

    ui_print(VDEBUG, "src_ctl_get_progver returning '%s'\n",
	     (cp == NULL) ? "(null)" : cp);
    return (cp);
}



/*
 * compare program version against static revision table
 */
int
src_ctl_check_progver( char *name, char *vmin, char *vmax )
{
    char *vers;
    register int result;

    if ((vers = src_ctl_get_progver(name)) == NULL) {
	ui_print(VWARN, "couldn't determine revision of %s\n", name);
	return (-1);
    }
    /* check range: require vmin <= vers <= vmax */
    result = src_ctl_cmpnum(vers, vmin);
    if (result >= 0)
	return (src_ctl_cmpnum(vers, vmax) > 0);
    return (result);
}



/*
 * check that programs have valid versions and that servers are reachable
 * returns 0 if programs have proper versions,
 *        non-zero otherwise
 */
int
src_ctl_check_servers( SETINFO *si,
                       struct rcfile *rcfp )	/* contents of sandbox rcfile */
{
    const char **cp;

#ifdef notdef
    /* check the versions of the local btools */
    for (vp = tools_vers; (vp != NULL) && (vp->vprog != NULL); ++vp) {
	if (src_ctl_check_progver(vp->vprog, vp->vermin, vp->vermax)) {
	    ui_print(VFATAL, "version mismatch for %s,\n", vp->vprog);
	    ui_print(VCONT, "must be between %s and %s\n", vp->vermin, vp->vermax);
	    return (-1);
	}
    }
#endif
    /* invoke required tools with dummy args to verify existence */
    for (cp = local_tools; cp != NULL && *cp != NULL; ++cp) {
	register int status;

	ui_print(VDEBUG, "about to run '%s'\n", *cp);
	if ((status = system(*cp))) {
	    ui_print(VFATAL, "unable to run %s, exit status was %d\n",
		     *cp, status);
	    return (status);
	}
    }

#ifdef notdef
    /* check revisions of remote programs */
    if (get_rc_value(TOOLS_BASE, &base, rcfp, TRUE) == ERROR) {
	ui_print(VFATAL, "cannot determine location of server executables\n");
	return (-1);
    }
    ui_print(VDEBUG, "tools_base is %s\n", base);
    for (vp = remote_vers; (vp != NULL) && (vp->vprog != NULL); ++vp)
    {
	(void) sprintf(lpath, "%s/lib/%s", base, vp->vprog);
	if (src_ctl_check_progver(lpath, vp->vermin, vp->vermax))
	{
	    ui_print(VFATAL, "version mismatch for %s,\n", vp->vprog);
	    ui_print(VCONT, "must be between %s and %s\n", vp->vermin, vp->vermax);
	    return (-1);
	}
    }
#endif
    return (0);
}

void
get_full_setname2 ( 
    SETINFO   * setinfo )                       /* points to set information */

	/* This procedure prepends the user name to the setname
	   if the setname does not start with a capital letter
	   and it isn't already there.  It puts the final setname
	   in setinfo. */


{
    char        tmp_name [ NAME_LEN ],                        /* misc string */
              * setn,                             /* original set name value */
              * ptr;                                  /* point to env string */

  if ( ui_is_set ( SET_OP )) {
    setn = ui_arg_value ( SET_OP, 1, 1 );
    getenv_user2 ( setinfo );

    if (( ptr = concat ( tmp_name, NAME_LEN , setinfo->user, "_", NULL ))
	      == NULL)
      uquit ( ERROR, FALSE, "\tno room in buffer for '%s_'\n", setinfo->user );

    if ((( *setn < 'A' ) || ( *setn > 'Z' )) &&
	( strncmp ( tmp_name, setn, ptr - tmp_name )))
      concat ( setinfo->l_set, NAME_LEN, tmp_name, setn, NULL );
    else
      strcpy ( setinfo->l_set, setn );
  } /* if */

  else
    *(setinfo->l_set) = NUL;
}                                                        /* get full setname */



int getenv_user2 ( SETINFO * setinfo )

	/* This procedure gets the user's name. */
{
    char      * env_ptr;                              /* point to env string */

  if (( env_ptr = (char *)getenv ( "USER" )) == NULL ) {          /* insert user name */
    ui_print ( VFATAL, "USER not found in environment.\n" );
    return (ERROR );
  }

  strcpy ( setinfo->user, env_ptr );
  return ( OK );
}                                                             /* getenv user */



int fill_in_sbinfo ( 
    SETINFO   	* setinfo,                      /* points to set information */
    struct      rcfile * contents )         /* to hold contents of sb rcfile */

	/* This procedure fills in the sandbox fields which
	   the user did not fill in. */


{
  load_submit_rc_values ( contents, setinfo );
  ui_print ( VDEBUG, "from the set: %s\n", setinfo->l_set );
  return ( OK );
}                                                          /* fill in sbinfo */

void
load_submit_rc_values ( 
    struct      rcfile * contents,          /* to hold contents of sb rcfile */
    SETINFO   * setinfo )                       /* points to set information */

	/* This procedure calls the routines to find the various
	   rc values for submission.  It loads those values in
	   setinfo. */


{
    char     *  value;                           /* points to value returned */

  get_rc_value ( SUBMIT_DEFECT, &value, contents, TRUE );

  if ( streq ( value, "true" ))
    setinfo->defect_num = TRUE;
  else
    setinfo->defect_num = FALSE;
}                                                   /* load submit rc values */


void
cd_to_src_path (
    struct      rcfile  * contents,         /* to hold contents of sb rcfile */
    SETINFO   * setinfo )                       /* points to set information */

	/* This procedure determines the source directory for the user
	   and then does a cd to it.  First, however, it finds out where
	   the user is and sets up the current directory.  This is used
	   for searching for paths for files to submit later. */


{
    char      * src_dir,                 /* points to string with source dir */
                tmpdir [ STRING_LEN ];                        /* misc string */

  concat ( tmpdir, sizeof (tmpdir), sb_base, "/", sb, "/src", NULL );
  src_dir = strdup ( tmpdir );
  if ( *src_dir != SLASH )
    uquit ( ERROR, FALSE, 
       "\tvalue of %s field does not begin with a %c.\n", SOURCE_BASE, SLASH );

  if (( isdir ( src_dir ) == ERROR ))
    uquit ( ERROR, FALSE, "\tno source directory, %s, in sandbox.\n", src_dir );

  if ( getcwd ( tmpdir, sizeof(tmpdir) ) == NULL )
    uquit ( ERROR, FALSE, "\tgetcwd: %s.\n", strerror(errno) );

  chdir_to ( src_dir, setinfo );

  if (( getcwd ( setinfo->l_src_dir, sizeof(setinfo->l_src_dir) ) == NULL ))
    uquit ( ERROR, FALSE, "\tgetcwd: %s.\n", strerror(errno) );

  if ( strncmp ( setinfo->l_src_dir, tmpdir,
		 		  strlen ( setinfo->l_src_dir )) != OK ) {
    ui_print ( VWARN, "current directory not in source base: %s.\n",
		       setinfo->l_src_dir);
  } /* if */

  ui_print ( VDETAIL, "cd'ing to sandbox source directory: %s.\n", src_dir );
}                                                          /* cd to src path */

void
chdir_to ( 
    char      * dir,                               /* directory to change to */
    SETINFO   * setinfo )                       /* points to set information */

	/* This procedure attempts to change directories to the
	   dir.  If it fails, it quits. */


{
  if ( chdir ( dir ) == ERROR ) {
    cleanup ( TRUE );
    uquit ( ERROR, FALSE, "\tcould not change directory to: %s.\n", dir );
  } /* if */
}                                                                /* chdir to */

void
fill_in_sfiles (
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles )                                 /* the shared files */

	/* This procedure fills in all the fields for the shared
	   files which will need to be accessed later. */


{
    char        file_path [ PATH_LEN ],   /* path and name to build snapshot */
                begin [ PATH_LEN ];                     /* beginning of path */

  concat ( begin, PATH_LEN, "ode2.3_server_base/sets/", user_set, "/",
                  setinfo->ttime, ".", NULL);
  concat ( file_path, PATH_LEN, begin, TMP_LOG, NULL );

  if (( sfiles->usr_log = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, TMP_SNAP, NULL );

  if (( sfiles->usr_snap = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, TMP_DEFUNCT, NULL );

  if (( sfiles->usr_defunct = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, TMP_HOLD, NULL );

  if (( sfiles->usr_hold = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  strcpy ( file_path, HOLD_FILE_23 );

  if (( sfiles->holdfile = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, user_id, NULL );

  if (( sfiles->trackfile = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN,
	   begin, BCSSTEPS, NULL );

  if (( sfiles->trackbcsstep = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, ": ", submit_set, " ", user_id,
                           "; Date: ", setinfo->tdate, "; Time: ",
                           setinfo->ttime, NULL );

  if (( sfiles->holdline = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, "oldrevs", NULL );

  if (( old_rev_file = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, begin, "BCSlog", NULL );

  if (( bcsfile = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  if ( ui_ver_level () >= VDEBUG )
    print_sfiles ( sfiles );
}                                                          /* fill in sfiles */


void
print_sfiles ( 
    SHARED_F  * sfiles )                                 /* the shared files */

	/* This procedure prints the files which have been created. */


{
  ui_print ( VDEBUG, "The following files and directories will be used:\n" );
  ui_print ( VCONT, "%s\n", sfiles->usr_log );
  ui_print ( VCONT, "%s\n", sfiles->usr_snap );
  ui_print ( VCONT, "%s\n", sfiles->usr_defunct );
  ui_print ( VCONT, "%s\n", sfiles->usr_hold );
  ui_print ( VCONT, "%s\n", sfiles->holdfile );
  ui_print ( VCONT, "%s\n", sfiles->trackfile );
  ui_print ( VCONT, "%s\n", sfiles->trackbcsstep );
  ui_print ( VCONT, "%s\n", sfiles->holdline );
}                                                             /* print files */

/*
 * prompt the user for input using a default value.
 * use explicit answer if user provides one,
 * otherwise use default.
 */
void
defprompt (
char  * prompt,		/* the prompt */
char  * ans,		/* the answer */
char  * def,		/* default string (if any) */
int	len )		/* size of answer buffer */
{
    register char *cp;

    *ans = NUL;
    do
    {
	if (def != NULL && *def != NUL)
	    ui_print ( VALWAYS, "\n%s: [%s] ", prompt, def);
	else
	    ui_print ( VALWAYS, "\n%s: ", prompt );

	if (fgets ( ans, len, stdin ) == NULL)
	    ui_print (VWARN, "error reading from stdin\n");

	if (def != NULL && *def != NUL)
	{
	    if (*ans == NUL || *ans == '\n')
		strcpy(ans, def);	/* use default */
	}

	if ((cp = strchr(ans, '\n')) != NULL)
	    *cp = NUL;	/* remove any trailing newline */

    } while ( *ans == NUL );
}	/* defprompt */


void
prompt ( 
    char      * string,                                        /* the prompt */
    char      * ans )                                          /* the answer */

	/* This procedure prompts the user for input and then
	   gets the answer.  If the user doesn't input anything,
	   it tries again.  */


{
    BOOLEAN     answered = FALSE;                            /* misc boolean */

  *ans = NUL;

  while ( ! answered ) {
    ui_print ( VALWAYS, "\n%s: ", string );
    gets ( ans );

    if ( *ans != NUL )
      answered = TRUE;
  } /* while */
}                                                                  /* prompt */



BOOLEAN	append_log ( 
    char      * name,                           /* name of file to copy from */
    FILE      * to )                               /* ptr to file to copy to */

	/* This function appends the information in the file
	   "name" to the "to" file.  It returns FALSE if it fails. */


{
    FILE      * from;                        /* pointer to file to copy from */

  if (( from = fopen ( name, READ )) == NULL ) {
    ui_print ( VFATAL, "could not open file to copy from: %s\n", name );
    return ( FALSE );
  } /* if */

  ffilecopy ( from, to );
  fclose ( from );
  return ( TRUE );
}                                                              /* append log */

#ifndef EOS
#    define	EOS	'\0'		/* end of string terminator */
#endif

static char zero[] = "0";

/*
 * src_ctl_cmpnum() is similar to the RCS cmpnum() function, written
 * recursively (revisions strings are usually less than 4 deep)
 * compares two revision strings and returns:
 *	< 0, if r2 > r1
 *	0,   if r1 and r2 are identical
 *	> 0, if r1 > r2
 */
int
src_ctl_cmpnum( char *r1, char *r2 )
{
    char *cp1, *cp2;
    register int diff;

    /* treat missing args as "0" */
    if (r1 == NULL || *r1 == EOS)
	r1 = zero;
    if (r2 == NULL || *r2 == EOS)
	r2 = zero;

    /*
     * compare this component of revision string
     * (atoi only uses digits up to dot)
     */
    diff = atoi(r1) - atoi(r2);

    cp1 = strchr(r1, '.');
    cp2 = strchr(r2, '.');

    if (cp1 == NULL && cp2 == NULL)
	return (diff);	/* nothing more to compare */
    if (cp1 != NULL)
	++cp1;		/* point to next component */
    if (cp2 != NULL)
	++cp2;		/* point to next component */
    /* if this component matches, recurse on the remainder */
    return ( (diff) ? diff : src_ctl_cmpnum(cp1, cp2));
}
