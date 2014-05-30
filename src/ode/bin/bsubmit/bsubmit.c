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
 * $Log: bsubmit.c,v $
 * Revision 1.14.14.7  1994/02/04  15:06:58  damon
 * 	CR 1023. Put back prompt before merging
 * 	[1994/02/04  15:06:40  damon]
 *
 * Revision 1.14.14.6  1994/01/06  19:58:49  damon
 * 	CR 963. Removed -changed switch
 * 	[1994/01/06  19:58:33  damon]
 * 
 * Revision 1.14.14.5  1993/12/27  21:59:23  damon
 * 	CR 928. Fixed arguments to sci_copyright_init()
 * 	[1993/12/27  21:59:00  damon]
 * 
 * Revision 1.14.14.4  1993/12/16  21:40:17  damon
 * 	CR 923. do not print full name for log if no query done
 * 	[1993/12/16  21:40:04  damon]
 * 
 * Revision 1.14.14.3  1993/12/16  20:01:44  marty
 * 	CR # 724 - Add call to sci_copyright_init().
 * 	[1993/12/16  19:56:14  marty]
 * 
 * Revision 1.14.14.2  1993/12/06  22:09:14  marty
 * 	CR # 827 - Change interface to sci_check_in_file().
 * 	[1993/12/06  22:08:55  marty]
 * 
 * Revision 1.14.14.1  1993/11/22  18:46:37  damon
 * 	CR 852. Separated looking up ancestry from determining ancestor
 * 	[1993/11/22  18:46:04  damon]
 * 
 * Revision 1.14.12.6  1993/11/03  23:42:47  damon
 * 	CR 463. More pedantic
 * 	[1993/11/03  23:40:40  damon]
 * 
 * Revision 1.14.12.5  1993/10/28  13:32:05  damon
 * 	CR 761. Removed SB_RC_OP
 * 	[1993/10/28  13:24:16  damon]
 * 
 * Revision 1.14.12.4  1993/10/26  15:10:04  damon
 * 	CR 767. Aborted merging now removes held files
 * 	[1993/10/26  15:09:30  damon]
 * 
 * Revision 1.14.12.3  1993/10/21  17:23:40  damon
 * 	CR 758. Added 0:XX times for -resub and -rm
 * 	[1993/10/21  17:23:22  damon]
 * 
 * Revision 1.14.12.2  1993/10/20  14:43:16  damon
 * 	CR 755. Removed -m option from usage message
 * 	[1993/10/20  14:43:04  damon]
 * 
 * Revision 1.14.12.1  1993/10/07  17:37:36  damon
 * 	CR 728. Exit if problems checking in after merge
 * 	[1993/10/07  17:35:33  damon]
 * 
 * Revision 1.14.10.7  1993/09/22  16:04:21  damon
 * 	CR 675. Passing of -tag info between client/server restored
 * 	[1993/09/22  16:03:54  damon]
 * 
 * Revision 1.14.10.6  1993/09/08  13:40:13  root
 * 	CR # 558 - type casting problems on rios build.
 * 	[1993/09/08  13:39:30  root]
 * 
 * Revision 1.14.10.5  1993/09/07  16:34:11  damon
 * 	CR 625. Fixed bsubmit -info
 * 	[1993/09/07  16:33:22  damon]
 * 
 * Revision 1.14.10.4  1993/09/03  17:14:47  damon
 * 	CR 609. Corrected defect number checking
 * 	[1993/09/03  17:14:32  damon]
 * 
 * Revision 1.14.10.3  1993/09/01  19:19:53  damon
 * 	CR 645. Check for ABORT condition from merge
 * 	[1993/09/01  19:19:21  damon]
 * 
 * Revision 1.14.10.2  1993/08/30  20:24:36  damon
 * 	CR 624. Fixed bsbubmit typo in usage message
 * 	[1993/08/30  20:24:19  damon]
 * 
 * Revision 1.14.10.1  1993/08/25  16:10:51  damon
 * 	CR 625. disabled -info
 * 	[1993/08/25  16:10:39  damon]
 * 
 * Revision 1.14.8.1  1993/07/12  18:57:17  damon
 * 	CR 606. Look for lock_sb in correct dir
 * 	[1993/07/12  18:57:04  damon]
 * 
 * Revision 1.14.6.40  1993/06/28  21:27:47  damon
 * 	CR 596. Check for existance of file before checking r/w perms
 * 	[1993/06/28  21:27:30  damon]
 * 
 * Revision 1.14.6.39  1993/06/09  17:30:30  damon
 * 	CR 580. Pass original date stamp to subsequent sci_submit_client()s
 * 	[1993/06/09  17:30:11  damon]
 * 
 * Revision 1.14.6.38  1993/06/02  18:27:02  damon
 * 	CR 565. Fixed check for writeable file to deal with links
 * 	[1993/06/02  18:26:09  damon]
 * 
 * Revision 1.14.6.37  1993/05/28  18:18:00  marty
 * 	CR # 558 - Get it to build on rios_aix
 * 	[1993/05/28  18:17:39  marty]
 * 
 * Revision 1.14.6.36  1993/05/28  18:13:45  marty
 * 	CR # 558 - Get it bulding on rios_aix
 * 	[1993/05/28  18:13:25  marty]
 * 
 * Revision 1.14.6.35  1993/05/26  20:31:26  damon
 * 	CR 545. Changed access() to stat() for checking r/w perm
 * 	[1993/05/26  20:31:09  damon]
 * 
 * Revision 1.14.6.34  1993/05/25  18:48:43  damon
 * 	CR 542. Fixed defect handling when -rm is used
 * 	[1993/05/25  18:48:23  damon]
 * 
 * Revision 1.14.6.33  1993/05/25  17:58:45  damon
 * 	CR 539
 * 	Added in_submit_stage, resub_time, resub_date to sci_submit_client
 * 	[1993/05/25  17:57:31  damon]
 * 
 * Revision 1.14.6.32  1993/05/24  18:17:47  damon
 * 	CR 538. Updated merging log message
 * 	[1993/05/24  18:17:33  damon]
 * 
 * Revision 1.14.6.31  1993/05/24  17:46:17  damon
 * 	CR 501. For resub, list of files returned to client for outdate
 * 	[1993/05/24  17:45:35  damon]
 * 
 * Revision 1.14.6.30  1993/05/20  15:47:41  damon
 * 	CR 532. Made outdating optional for bsubmit
 * 	[1993/05/20  15:42:06  damon]
 * 
 * Revision 1.14.6.29  1993/05/18  20:49:05  marty
 * 	CR # 420 - Don't unlink the lock file. leave it.
 * 	[1993/05/18  20:48:50  marty]
 * 
 * Revision 1.14.6.28  1993/05/18  20:07:25  marty
 * 	CR # 420 - bsubmit now locks the sandbox (as opposed to sci_init() locking
 * 	it.
 * 	[1993/05/18  20:07:00  marty]
 * 
 * Revision 1.14.6.27  1993/05/18  17:46:08  marty
 * 	CR # 454 - Fixed call to sci_outdate_list_p2 so that "set" name is passed
 * 	(not setinfo structure).
 * 	[1993/05/18  17:45:48  marty]
 * 
 * Revision 1.14.6.26  1993/05/12  16:32:52  damon
 * 	CR 203. Add leading zero to single digit days
 * 	[1993/05/12  16:26:32  damon]
 * 
 * Revision 1.14.6.25  1993/05/11  18:12:35  damon
 * 	CR 469. Validate CRs
 * 	[1993/05/11  18:03:59  damon]
 * 
 * Revision 1.14.6.24  1993/05/10  17:36:58  damon
 * 	CR 509. No longer creates tracking file on client
 * 	[1993/05/10  17:36:48  damon]
 * 
 * Revision 1.14.6.23  1993/04/30  21:11:19  damon
 * 	CR 467. Check that files are r/o before doing submit
 * 	[1993/04/30  21:10:54  damon]
 * 
 * Revision 1.14.6.22  1993/04/29  16:33:02  marty
 * 	Prototypes for print_usage().   CR# 463
 * 	[1993/04/29  16:32:41  marty]
 * 
 * Revision 1.14.6.21  1993/04/20  21:46:13  marty
 * 	Added include files.
 * 	[1993/04/20  21:45:36  marty]
 * 
 * Revision 1.14.6.20  1993/04/16  20:43:08  damon
 * 	CR 421. Updated usage message for 2.3
 * 	[1993/04/16  20:42:38  damon]
 * 
 * Revision 1.14.6.19  1993/04/16  13:16:25  damon
 * 	CR 436. Fixed already_held logic
 * 	[1993/04/16  13:16:09  damon]
 * 
 * Revision 1.14.6.18  1993/04/13  17:25:58  damon
 * 	CR 436. Added new merge handling
 * 	[1993/04/13  17:25:44  damon]
 * 
 * Revision 1.14.6.17  1993/04/09  14:20:30  damon
 * 	CR 446. Clean up include files
 * 	[1993/04/09  14:20:19  damon]
 * 
 * Revision 1.14.6.16  1993/04/02  20:47:46  damon
 * 	CR 436. Removed redundant Checking Env message
 * 	[1993/04/02  20:44:21  damon]
 * 
 * Revision 1.14.6.15  1993/03/24  20:48:58  damon
 * 	CR 436. resub and remove options working client/server
 * 	[1993/03/24  20:48:19  damon]
 * 
 * Revision 1.14.6.14  1993/03/17  16:15:50  damon
 * 	CR 436.
 * 	Handles return code OE_MERGEREQ.
 * 	Cleaned out unused code.
 * 	[1993/03/17  16:15:36  damon]
 * 
 * Revision 1.14.6.13  1993/03/15  21:05:17  damon
 * 	CR 436. Send all info needed for submit log
 * 	[1993/03/15  20:59:58  damon]
 * 
 * Revision 1.14.6.12  1993/03/15  17:58:04  damon
 * 	CR 436. Removed non-client code
 * 	[1993/03/15  17:57:50  damon]
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
static const char * rcsid = "$RCSfile: bsubmit.c,v $ $Revision: 1.14.14.7 $ $Date: 1994/02/04 15:06:58 $";

#include <string.h>
#include <unistd.h>
#include <ode/builddata.h>
#include <ode/errno.h>
#include <errno.h>
#include <ode/interface.h>
#include <ode/misc.h>
#include <ode/sandboxes.h>
#include <ode/sci_client.h>
#include <ode/sets.h>
#include <ode/util.h>
#include <stdio.h>
#include <stdlib.h>
#include "bsubmit.h"

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
  const char  * progname;                               /* name of program */
  char        * sb_base = NULL,
              * sb,                                        /* sandbox name */
              * sb_rcfile;                         /* sandbox rc file name */
  BOOLEAN       log_lock = FALSE;              /* is the logs file lock on */
  int submit_stage = PREPARING;
extern char * check_out_config;
  char * defect_number,
       * set = NULL;
  char * submit_set = NULL,
         submit_user_name [STRING_LEN];
  char   expanded_config [ MAXPATHLEN ];
  char   lock_file [ MAXPATHLEN ];
  char * merge_rev_file;
  BOOLEAN outdate_op = FALSE;
  BOOLEAN in_submit_stage = FALSE;
  char resub_time[MAXPATHLEN];
  char resub_date[MAXPATHLEN];
  char * recover_time = NULL;
  char * recover_date = NULL;

int file_mode;

    UIINIT init [] = {                      /* initialize the user interface */
      { AUTOOUT_OP,  1, OVERWRITE,  0, 0, "" },
      { SAVED_OP,      1, OVERWRITE,  0, 0, "" },
      { ALL_OP,      1, OVERWRITE,  0, 0, "" },
      { LOCAL_CO_OP, 1, OVERWRITE,  0, 2, "backing lock" },
      { RM_OP,    1, OVERWRITE,  1, 1,
				       "[1-9]:[0-5][0-9] [12][0-9]:[0-5][0-9] [0]:[0-5][0-9]"},
      { RESUB_OP,    1, OVERWRITE,  1, 1,
				       "[1-9]:[0-5][0-9] [12][0-9]:[0-5][0-9] [0]:[0-5][0-9]"},
      { DATE_OP,     1, OVERWRITE,  1, 1, "[1-9]/[1-9]/[0-9][0-9] [1-9]/[1-3][0-9]/[0-9][0-9] 1[0-2]/[1-9]/[0-9][0-9] 1[0-2]/[1-3][0-9]/[0-9][0-9]" },
      { FN_OP,       1, OVERWRITE,  1, 1, ARGS_OP },
      { DEFECT_OP,   1, OVERWRITE,  1, 1, ARGS_OP },
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
void
cmdline_syntax ( SETINFO * );
void
handle_merges ( SCI_LIST );
int general_setup ( 
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  struct rcfile * contents );
void
setup_for_bcs ( SETINFO * setinfo, SHARED_F * sfiles, SCI_LIST * file_set );
void
local_work ( SETINFO * setinfo, SCI_LIST file_set );
int fill_in_sbinfo ( SETINFO * setinfo, struct rcfile * contents );
void
fill_in_sfiles ( SETINFO * setinfo, SHARED_F * sfiles );
BOOLEAN	build_is_locked ( SETINFO * setinfo );
void
specify_build_info ( SETINFO * setinfo );
int make_filelist ( SETINFO * setinfo, SCI_LIST * file_set);
void
load_submit_rc_values ( struct rcfile * , SETINFO * );
void
print_sfiles ( SHARED_F * );
int
src_ctl_cmpnum(char * , char * );
void
get_full_setname2 ( SETINFO * );
int getenv_user2 ( SETINFO * );
void
cd_to_src_path ( struct rcfile * , SETINFO * );
void
prompt ( const char * string, char * ans );
void
getfullname( SETINFO * setinfo, char * name, int namelen);
void
defprompt ( const char * dprompt, char * ans, int len, char * def );
void
chdir_to (  char * dir, SETINFO * setinfo );

void
exit_bsubmit ( int status )
{
  ui_print ( VALWAYS, "Exiting bsubmit.\n\n" );
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
		    resub_time, resub_date );
  exit_bsubmit ( ERROR );
}

void
exit_without_resub ( int problems )
{
  ERR_LOG log;

  if ( submit_stage == MERGING ) {
    if ( (log = sci_submit_client ( NULL, NULL, set, sb,
                                    submit_set, "dummy", submit_user_name,
                                    defect_number, FALSE, FALSE,
                                    NULL, FALSE, TRUE, FALSE, resub_time,
                                    resub_date, &in_submit_stage, resub_time,
                                    resub_date
                                  ) ) != OE_OK )
    exit_with_resub ( TRUE );
  } /* if */
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
  if ( in_submit_stage || ui_is_set ( RESUB_OP) ) {
    exit_with_resub ( problems );
  } else {
    exit_without_resub ( problems );
  } /*if */
}                                                                 /* cleanup */

void sig_int ( int sig )

	/* This procedure handles any interrupts; cleaning up
	   before exiting. */

	  							 /* ARGSUSED */
{
  ui_print ( VALWAYS, "\n\n*** SUBMISSION INTERRUPTED BY USER ***\n" );
  cleanup ( FALSE );
} /* end sig_int */

char *
normalize_date ( const char * raw_date )
{
  char * tmp_date;
  char * d_ptr;
  char n_date [11];
  char * month;
  char * day;
  char * year;

  tmp_date = (char *)strdup ( (char *) raw_date );
  d_ptr = tmp_date;
  month = nxtarg ( &d_ptr, "/" );
  day = nxtarg ( &d_ptr, "/" );
  year = nxtarg ( &d_ptr, WHITESPACE );
  if ( strlen ( day ) == 2 ) {
    concat ( n_date, sizeof(n_date), month, "/", day, "/", year, NULL );
  } else {
    concat ( n_date, sizeof(n_date), month, "/0", day, "/", year, NULL );
  } /* if */
  free ( tmp_date );
  return ( strdup ( n_date ) );
} /* end normalize_date */

void
main ( int argc, char ** argv )
{
  struct rcfile contents;
  char *ptr = expanded_config;
  ERR_LOG log;
  char * orig_time = NULL;
  char * orig_date = NULL;
  SCI_LIST file_set;
  SCI_LIST file_set2;
  SETINFO * setinfo;                      /* points to set information */
  SHARED_F sfiles;                                  /* the shared files */
  BOOLEAN already_held;

  signal ( SIGINT, sig_int );

  ui_print ( VALWAYS, "\nEntering bsubmit\n" );
  ui_print ( VALWAYS, "----------------\n" );

  if (argc > 0)
    progname = argv[0];
  else
    progname = "bsubmit";

 /*
  * Parse the command line
  */
  ui_init ( argc, argv, MAX_ARGS, init, 0, NULL );

#ifdef notdef
  if ( ui_is_info() ) {
    ui_print ( VALWAYS, "-info temporarily disabled\n" );
    exit ( -1 );
  } /* if */
#endif
  setinfo = ( SETINFO * ) malloc ( sizeof ( SETINFO ));

  cmdline_syntax ( setinfo );
  if ( general_setup ( setinfo, &sfiles, &contents ) == ERROR )
    cleanup ( TRUE );
  setup_for_bcs ( setinfo, &sfiles, &file_set );
  expanded_config[0] = '\0';
  rci_expand_include ( &ptr, check_out_config );
  if ( ui_is_set ( RESUB_OP ) )
    recover_time = ui_arg_value ( RESUB_OP, 1, 1 );
  /* if */
  if ( ui_is_set ( RM_OP ) )
    recover_time = ui_arg_value ( RM_OP, 1, 1 );
  /* if */
  if ( ui_is_set ( DATE_OP ) ) {
    recover_date = normalize_date ( ui_arg_value ( DATE_OP, 1, 1 ) );
  } /* if */

  already_held = FALSE;
  resub_time[0] = '\0';
  resub_date[0] = '\0';
  for ( ;; ) {
    ui_print ( VNORMAL, "\nChecking environment\n" );
    ui_print ( VNORMAL, "--------------------\n" );

    in_submit_stage = FALSE;
    if ( (log = sci_submit_client ( file_set, &file_set2, set, sb,
                                    submit_set,
                                    expanded_config, submit_user_name,
                                    defect_number, already_held, ui_is_info (), 
                                    ui_arg_value ( TAG_OP, 1, 1 ),
                                    ui_is_set ( RESUB_OP ), ui_is_set ( RM_OP),
                                    outdate_op, recover_time,
                                    recover_date, &in_submit_stage, resub_time,
                                    resub_date
                                  ) ) != OE_OK )
      if ( err_ode_errno ( log ) == OE_MERGEREQ ) {
        handle_merges ( file_set2 );
        if ( !already_held ) {
          orig_time = strdup ( resub_time );
          orig_date = strdup ( resub_date );
          already_held = TRUE;
        } /* if */
        recover_time = orig_time;
        recover_date = orig_date;
      } else {
        exit ( err_ode_errno ( log ) );
      /* if */
    } else 
      break;
    /* if */
  } /* for */

  if ( ui_is_info () ) {
    ui_print ( VNORMAL, "Would remove files from sandbox.\n" );
  } else if ( !ui_is_set ( RM_OP ) && outdate_op ) {
    /* if resub, use the file_set2 sent back from the server */
    if ( ui_is_set ( RESUB_OP ) ) {
      sci_outdate_list_p2 ( file_set2, set );
    } else {
      sci_outdate_list_p2 ( file_set, set );
    }
  } /* if */
  local_work ( setinfo, file_set );

  if ( ui_is_set ( RM_OP ) )
    ui_print ( VALWAYS, "\nRemoval completed successfully.\n\n" );
  else
    ui_print ( VALWAYS, "\nSubmission completed successfully.\n\n" );
  /* if */

  fclose ( setinfo->tracks );
  exit_bsubmit ( OK );
}                                                                    /* main */

void
handle_merges ( SCI_LIST file_set )
{
  SCI_ELEM sci_ptr;
  int missing_revs;
  char log_msg [MAXPATHLEN];
  int result;
  char answer [STRING_LEN];

  submit_stage = MERGING;
  ui_print ( VALWAYS, "Do you wish to continue ? (Yy)es or (Nn)o [Y] " );
  gets ( answer );
  if ( *answer == 'n' || *answer == 'N' ) {
    cleanup ( FALSE );
  } /* end if */
  sci_lookup_user_rev_list ( file_set, set, &missing_revs );
  sci_lookup_leader_list ( file_set );
  sci_lookup_merge_rev_list ( file_set, submit_set, expanded_config );
  sci_ancestry_list ( file_set );
  sci_ancestor_list ( file_set );
  if ( sci_merge_list ( file_set, FALSE ) == ABORT ) {
    cleanup(FALSE);
  } /* if */
  for ( sci_ptr = sci_first ( file_set ); sci_ptr != NULL;
        sci_ptr = sci_next ( sci_ptr ) ) {
    concat ( log_msg, sizeof(log_msg), "Merged with changes from ",
                      sci_ptr -> ver_merge, NULL );
    result = sci_check_in_file ( sci_ptr, set, log_msg, FALSE, FALSE, NULL );
    if ( result == ABORT ) {
      cleanup(FALSE);
    } else if ( result == ERROR ) {
      cleanup(TRUE);
    } /* if */
  } /* for */
  sci_ancestor_update_list ( file_set );
  submit_stage = SUBMITTING;
} /* end handle_merges */

void
cmdline_syntax ( SETINFO * setinfo )

	/* This procedure checks for relationships between the
	   command line arguments.  It assumes the syntax is
	   already correct.  Most of the functions it calls
	   will use uquit to exit if there is an error. */

{
  file_mode = FILES_GIVEN;
  if ( ui_is_set ( SAVED_OP ) )
    file_mode = FILES_SAVED;
  /* if */
  setinfo->co_mode = CO_M_OUT;                /* check out mode is outdate */

  get_full_setname2 ( setinfo );
  (void) getenv_user2 ( setinfo );
  if ( ui_is_set ( RESUB_OP ) || ui_is_set ( RM_OP) ) {
    if ( ui_is_set ( ARGS_OP ) || ui_is_set ( ALL_OP ))
      uquit ( ERROR, TRUE,
	"\tThe following options cannot be set when specific files are listed %s , %s.\n", RESUB_OP, RM_OP );
  } /* if */

  else if ( ui_is_set ( DATE_OP ))
    uquit ( ERROR, TRUE, "\t%s can only used with either the %s or %s options.\n",
	    DATE_OP, RESUB_OP, RM_OP );

  else if ( ui_is_set ( ALL_OP )) {
    if (  ui_is_set ( ARGS_OP ))
      uquit ( ERROR, TRUE,
	      "\t%s cannot be set when specific files are listed.\n", ALL_OP );
  } /* else if */

  else if ( ! ui_is_set ( ARGS_OP ))
    uquit ( ERROR, TRUE, "\tno files were listed to submit.\n" );
}                                                          /* cmdline syntax */

BOOLEAN
validate_strict ( const char * cr_list )
{
  char * tmp_cr_list;
  char * cr_ptr;
  BOOLEAN result = TRUE;
  char * cr;
  BOOLEAN first = TRUE;

  tmp_cr_list = (char *)strdup ( (char * )cr_list );
  cr_ptr = tmp_cr_list;
  for (;; ) {
    cr = nxtarg ( &cr_ptr, "," );
    if ( cr == NULL || *cr == '\0' ) {
     /* 
      * Handle bad strings like '   ,1'
      */
      if ( first && strchr ( cr_list, ',' ) != NULL ) {
        result = FALSE;
      } /* if */
      break;
    } /* if */
    first = FALSE;
    if ( strcmp ( cr, "0" ) == 0 ) {
      result = FALSE;
      break;
    } /* if */
    while ( *cr != '\0' ) {
      if ( strchr ( "0123456789", *cr ) == NULL ) { 
        result = FALSE; 
        break;
      } /* if */
      (void)*cr++;
    } /* while */
    if ( result == FALSE ) {
      break;
    } /* if */
  } /* for */
  free ( tmp_cr_list );
  return ( result );
} /* end validate_strict */

BOOLEAN
valid_crs ( struct rcfile * contents,
                    const char * cr_list )
{
  char * cr_validate;
  char * tmp_cr_list;
  BOOLEAN result;
  char * cr_ptr;
  char * cr;

  if ( get_rc_value ( "cr_validate", &cr_validate, contents, FALSE ) != OK ) {
    result = TRUE;
  } else if ( strcmp ( cr_validate, "any" ) == 0 ) {
    result = TRUE;
  } else if ( strcmp ( cr_validate, "strict_or_space" ) == 0 ) {
    tmp_cr_list = (char *)strdup ( (char *)cr_list );
    cr_ptr = tmp_cr_list;
    cr = nxtarg ( &cr_ptr, WHITESPACE );
    if ( *cr == '\0' || cr == NULL ) {
      free ( tmp_cr_list );
      result = TRUE;
    } else {
      free ( tmp_cr_list );
      if ( validate_strict ( cr_list ) ) {
        result = TRUE;
      } else {
        ui_print ( VWARN, "CR validation is set to 'strict_or_space'.\n" );
        ui_print ( VCONT, "Cardinals > 0 separated by commas are acceptable.\n" );
        ui_print ( VCONT, "A blank CR (whitespace) is acceptable.\n" );
        result = FALSE;
      } /* if */
    } /* if */
  } else if ( strcmp ( cr_validate, "strict" ) == 0 ) {
    if ( validate_strict ( cr_list ) ) {
      result = TRUE;
    } else {
      ui_print ( VWARN, "CR validation is set to 'strict'.\n" );
      ui_print ( VCONT, "Only cardinals > 0 separated by commas are acceptable.\n" );
      result = FALSE;
    } /* if */
  } else {
    ui_print ( VWARN, "The rc variable '%s' has an invalid value: '%s'.\n",
                      "cr_validate", cr_validate );
    result = FALSE;
  } /* if */
  return ( result );
} /* end valid_crs */

int general_setup ( 
    SETINFO   * setinfo,                        /* points to set information */
    SHARED_F  * sfiles,                                  /* the shared files */
  struct rcfile * contents )

	/* This procedure does the preliminary setup for calling
	   the bcs commands. */

{
  char answer [STRING_LEN];
  char   src_dir [ MAXPATHLEN ];

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

 /*
  * Initialize the source control system
  */
  sb = ui_arg_value ( SB_OP, 1, 1 );
  set = ui_arg_value ( SET_OP, 1, 1 );
  sb_rcfile = NULL;

  if ( sci_init ( contents, &sb, &sb_base, &set, &submit_set,
                  &sb_rcfile, file_mode, !ui_is_set ( RM_OP ) ) != OK )
    cleanup ( TRUE );

  if (sci_copyright_init ( contents, sb_base, sb) != OK) {
      cleanup (TRUE);
  }


  /* Lock sandbox. */
  concat (src_dir, sizeof(src_dir), sb_base, "/", sb, "/src", NULL);
  concat (lock_file, sizeof(lock_file), src_dir, "/", BCSLOCK, NULL);
  if ( ! lock_sb (src_dir, lock_file, getenv ("USER")))
        exit (ERROR);

  strcpy ( setinfo->b_set, submit_set);
  strcpy ( setinfo->l_base, sb_base );
  if ( *(setinfo->l_set) == NUL )
    strcpy ( setinfo->l_set, set );

  if ( fill_in_sbinfo ( setinfo, contents ) == ERROR )
    return ( ERROR );
  /* end if */
/*
  if ( get_rc_value ( "check_out_config", &check_out_config, contents, 
       TRUE ) != OK ) 
    return ( ERROR );
*/
  /* end if */
  ui_print ( VDEBUG, "check_out_config is '%s'\n", check_out_config );

  if ( ui_ver_level () >= VDETAIL )
    specify_build_info ( setinfo );

  get_date ( setinfo->date, setinfo->time );
/*
  if (src_ctl_check_servers(setinfo, &contents)) 
  {
      ui_print(VALWAYS, "\t Problem running tools in the local environment.\n");
      return (ERROR);
  }
*/
 /*
  * if resubmission, get prev time
  */
  if ( ui_is_set ( RESUB_OP ) || ui_is_set ( RM_OP ) ) {
    if ( ui_is_set ( RESUB_OP ) )
      strcpy ( setinfo->ttime, ui_arg_value ( RESUB_OP, 1, 1 ));
    else
      strcpy ( setinfo->ttime, ui_arg_value ( RM_OP, 1, 1 ));
    /* if */
    if ( ui_is_set ( DATE_OP ))       /* if different date specified, use it */
      strcpy ( setinfo->tdate, ui_arg_value ( DATE_OP, 1, 1 ));
    else
      strcpy ( setinfo->tdate, setinfo->date );
  } /* if */

  else {            /* default values are now, today, and start at beginning */
    strcpy ( setinfo->ttime, setinfo->time );
    strcpy ( setinfo->tdate, setinfo->date );
  } /* else */

  cd_to_src_path ( contents, setinfo );

  fill_in_sfiles ( setinfo, sfiles );


  if ( (ui_is_set ( RESUB_OP ) || ui_is_set ( RM_OP )) &&
      ( access ( sfiles->trackbcsstep, F_OK ) == OK ))
    setinfo->full_list = FALSE;
  else
    setinfo->full_list = TRUE;
  /* if */

  if ( build_is_locked ( setinfo )) {
    exit ( OK );
  }
  /* if */
  if ( ui_is_set ( DEFECT_OP ))
    defect_number = strdup ( ui_arg_value ( DEFECT_OP, 1, 1 ) );
  else if ( setinfo->defect_num && ! ui_is_set ( RM_OP ) ) {
    prompt ( "Enter the defect number this submission applies to",
             answer );
    defect_number = strdup ( answer );
  } else
    defect_number = NULL;
  /* if */
  if ( defect_number != NULL && ! ui_is_set ( RM_OP ) &&
       ! valid_crs ( contents, defect_number ) ) {
    return ( ERROR );
  } /* if */
  getfullname ( setinfo, submit_user_name, sizeof (submit_user_name ) );
  if ( ui_is_set ( AUTOOUT_OP ) ) {
    outdate_op = TRUE;
  } else {
    ui_print ( VALWAYS, "Outdate the submitted files from set" );
    ui_print ( VALWAYS, ": %s?\nAnswer: [<y>|n] ", setinfo->l_set );
    gets ( answer );
    outdate_op = ( *answer != 'n' && *answer != 'N' );
  } /* if */
  return ( OK );
}                                                           /* general setup */


void
legal_build ( char * back, SETINFO * setinfo, struct rcfile * contents )

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
specify_build_info ( SETINFO * setinfo )

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
  log = oxm_open ( &rcs_monitor, 2 );
  i = 0;
  av [i++] = CHECKLOCKSB;
  log = oxm_runcmd ( rcs_monitor, i , av, NULL );
  log = oxm_endcmd ( rcs_monitor, &status );
  log = oxm_close ( rcs_monitor );

  switch ( status ) {
    case WAITING:
      ui_print ( VALWAYS, "The set being submitted to: %s\n", submit_set );
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
setup_for_bcs ( SETINFO * setinfo, SHARED_F * sfiles, SCI_LIST * file_set )

	/* This procedure does the preliminary setup for calling
	   the bcs commands including making the list of files
	   to submit. */

{
  SCI_ELEM sci_ptr;
  BOOLEAN found_non_tut;
  BOOLEAN writeable_files = FALSE;
  struct stat st;
  BOOLEAN is_link;

  ui_print ( VDEBUG, "Entering setup_for_bcs\n" );
  if ( ui_is_set ( RESUB_OP ) || ui_is_set ( RM_OP) ) {
  } else {
    (void) make_filelist ( setinfo, file_set );
  } /* end if */

  if ( ! ui_is_set ( RESUB_OP ) && ! ui_is_set ( RM_OP ) ) {
  if ( ui_ver_level () >= VDETAIL ) {
    ui_print ( VDETAIL, "Working with the following files:\n" );

    list_sci_files ( *file_set );
  } /* if */
  found_non_tut = FALSE;
  for ( sci_ptr = sci_first ( *file_set ); sci_ptr != NULL;
        sci_ptr = sci_next ( sci_ptr ) ) {
    lstat ( sci_ptr->name, &st );
    is_link = ( st.st_mode & S_IFMT ) == S_IFLNK;
   /*
    * The file may be defunct and thus missing.
    */
    if ( stat ( sci_ptr -> name, &st ) != 0 ) {
      continue;
    } /* if */
    if ( (st.st_mode & S_IWUSR) && ! is_link ) {
      if ( !writeable_files ) {
        ui_print ( VALWAYS, "\nThe following files are writeable which\n" );
        ui_print ( VCONT, "indicates that they need to be checked-in:\n\n" );
        writeable_files = TRUE;
      } /* if */
      ui_print ( VCONT, "%s\n", sci_ptr -> name );
    } /* if */
    if ( strncmp ( sci_ptr -> name, TUTORIAL, TUT_CT ) == 0 ) {
      if ( found_non_tut ) {
        ui_print ( VFATAL, "Cannot mix tutorial and non-tutorial submissions.\n" );
        cleanup ( TRUE );
      } /* end if */
    } else
      found_non_tut = TRUE;
    /* end if */
  } /* end for */
  if ( writeable_files )
    cleanup ( TRUE );

  if (( ui_ver_level () >= VDETAIL ) && ! setinfo->update_snap )
    ui_print ( VDETAIL, "Tutorial submission, SNAPSHOT will not be updated.\n");
  }
  ui_print ( VDEBUG, "Leaving setup_for_bcs\n" );
}                                                           /* setup for bcs */

void
load_merge_revs ( SCI_LIST file_set )
{
  FILE * merge_f;
  char merge_line [MAXPATHLEN];
  char * merge_file;
  char * ver_merge;
  BOOLEAN found;
  char * m_ptr;
  SCI_ELEM sci_ptr;

  merge_f = fopen ( merge_rev_file, READ );
  if ( merge_f != NULL ) {
    while ( fgets ( merge_line, MAXPATHLEN, merge_f ) != NULL ) {
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
  
  fclose ( merge_f );
} /* end load_merge_revs */

void
parse_steps ( SCI_LIST file_set, SHARED_F * sfiles )
{
  BOOLEAN     found = FALSE;                               /* misc boolean */
  FILE * f;
  char donefile [ MAXPATHLEN ];
  SCI_ELEM sci_ptr;
  SCI_ELEM last = NULL;

  if ( ui_is_set ( RM_OP ) )
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
          if ( ui_is_set ( RM_OP ) ) {
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

    if ( ui_is_set ( RM_OP ) ) {
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

int make_filelist ( SETINFO * setinfo, SCI_LIST * file_set)

	/* This procedure assembles the list of files to submit.
	   It checks to see that it knows how to reach them and
	   that they are checked in. */
{
    char      * file;                       /* points to each file to submit */
    int         ct = 1;                          /* count of files to submit */

  ui_print ( VDEBUG, "Entering make_filelist\n" );

  if ( ui_is_set ( ALL_OP )) {                    /* if all, set up cmd line */
    return ( sci_all_list ( file_set, setinfo -> l_set ) );
  } else {
    sci_new_list ( file_set );
    ui_print ( VDEBUG, "org_dir is '%s'\n", setinfo -> org_dir );
    while (( file = ui_entry_value ( ARGS_OP, ct++ )) != NULL ) {
      sci_add_to_list ( *file_set, file );
    } /* while */
  } /* else */
  ui_print ( VDEBUG, "Leaving make_filelist\n" );
  return ( OK );
}                                                           /* make filelist */

int
remove_tracks ( SHARED_F * sfiles )
{
  if (exists(sfiles->trackfile) == OK &&
      unlink ( sfiles->trackfile ) == ERROR ) {
    ui_print ( VFATAL, "Unable to remove track file: %s.\n",
               sfiles->trackfile);
    return ( ERROR );
  } /* if */
  return ( OK );
} /* end remove_tracks */

void
write_tracks ( SHARED_F * sfiles, FILE * trackf, char * msg, char * trackfile )

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


/*
 * use command line argument (if provided), otherwise prompt for
 * user's full name (using password DB full name field as default)
 * (if "-auto" is given, don't bother prompting)
 */
void
getfullname( SETINFO * setinfo, char * name, int namelen)
{
    struct passwd *pwd;

    if ( ui_is_set ( FN_OP ))
	strcpy ( name, ui_arg_value ( FN_OP, 1, 1 ));
    else
    {
	register char *cp;

	if ((pwd = getpwnam(setinfo->user)) != NULL)
	    if ((cp = strchr(pwd->pw_gecos, ',')) != NULL)
		*cp = NUL;	/* terminate name field at first comma */
	if (pwd != NULL && ui_is_auto())	/* don't need confirmation */
	{
	    strncpy(name, pwd->pw_gecos, namelen);
	}
	else
	    defprompt ( "Enter your full name for the log", name, namelen,
		         (pwd == NULL) ? NULL : pwd->pw_gecos );
    }
}

void
local_work ( SETINFO * setinfo, SCI_LIST file_set )

	/* This procedure does any necessary checking out, outdating,
	   and clean up of the local area.  If the check out mode
	   is locked-build or less, an outdate is done; then, if it is
	   build or greater, a check out is done. */
{
    char        setfile [ PATH_LEN ];                         /* misc string */

  if ( ! ui_is_info ()) {
    concat ( setfile, PATH_LEN, BCS_SET, setinfo->b_set, NULL );
    ( void ) unlink ( setfile );
  } else {
    ui_print ( VNORMAL, "Would remove file names from set file.\n" );
  } /* if */
}                                                              /* local work */



/*
 * determine version by invoking command with '-version' switch,
 * capture output and scan for RCS revision number
 *	returns revision string
 *		or NULL on error
 */
char *
src_ctl_get_progver(char * prog)
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
src_ctl_check_progver(char * name, char * vmin, char * vmax)
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
src_ctl_check_servers( SETINFO * si, struct rcfile * rcfp)
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
get_full_setname2 ( SETINFO * setinfo )

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



int fill_in_sbinfo ( SETINFO * setinfo, struct rcfile * contents )

	/* This procedure fills in the sandbox fields which
	   the user did not fill in. */
{
  load_submit_rc_values ( contents, setinfo );
  ui_print ( VDEBUG, "from the set: %s\n", setinfo->l_set );
  return ( OK );
}                                                          /* fill in sbinfo */

void
load_submit_rc_values ( struct rcfile * contents, SETINFO * setinfo )

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
cd_to_src_path ( struct rcfile * contents, SETINFO * setinfo )

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
chdir_to (  char * dir, SETINFO * setinfo )

	/* This procedure attempts to change directories to the
	   dir.  If it fails, it quits. */
{
  if ( chdir ( dir ) == ERROR ) {
    cleanup ( TRUE );
    uquit ( ERROR, FALSE, "\tcould not change directory to: %s.\n", dir );
  } /* if */
}                                                                /* chdir to */

void
fill_in_sfiles ( SETINFO * setinfo, SHARED_F * sfiles )

	/* This procedure fills in all the fields for the shared
	   files which will need to be accessed later. */
{
    char        file_path [ PATH_LEN ],   /* path and name to build snapshot */
                begin [ PATH_LEN ];                     /* beginning of path */

  concat ( begin, PATH_LEN, setinfo->ttime, ".", NULL);

  concat ( file_path, PATH_LEN,
	   setinfo->l_src_dir, "/", setinfo->ttime, ".", setinfo->user, NULL );

  if (( sfiles->trackfile = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN,
	   setinfo->l_src_dir, "/", setinfo->ttime, ".", BCSSTEPS, NULL );

  if (( sfiles->trackbcsstep = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN, ": ", setinfo -> b_set, " ", setinfo->user,
                           "; Date: ", setinfo->tdate, "; Time: ",
                           setinfo->ttime, NULL );

  if (( sfiles->holdline = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );

  concat ( file_path, PATH_LEN,
	   setinfo->l_src_dir, "/", setinfo->ttime, ".", "mergerevs", NULL );

  if (( merge_rev_file = strdup ( file_path )) == NULL )
    uquit ( ERROR, FALSE, "\tno room for strdup of: %s\n", file_path );
  if ( ui_ver_level () >= VDEBUG )
    print_sfiles ( sfiles );
}                                                          /* fill in sfiles */


void
print_sfiles ( SHARED_F * sfiles )

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
defprompt (const char * dprompt, char * ans, int len, char * def )
{
    register char *cp;

    *ans = NUL;
    do
    {
	if (def != NULL && *def != NUL)
	    ui_print ( VALWAYS, "\n%s: [%s] ", dprompt, def);
	else
	    ui_print ( VALWAYS, "\n%s: ", dprompt );

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
prompt ( const char * string, char * ans )

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
src_ctl_cmpnum(char * r1, char * r2)
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

void print_usage (void )

	/* This procedure prints the usages for bsubmit. */

{
  printf ( "USAGE:\n" );
  printf ( "%s [-auto_out]\n", progname );
  printf ( "\t[-fn <full name> -defect <num> -log <logfile>] [sandbox opts] [ODE opts]\n");
  printf ( "\trecovery opts | -all | <file1 file2...>\n" );
  printf ( "\t  -auto_out : outdate files without pompting\n" );
  printf ( "\t  -fn <full name> : user's full name\n" );
  printf ( "\t  -defect <num> : defect number this submission fixes\n" );
  printf ( "\t  -log <logfile> : the file to use as log file\n" );
  ui_print ( VALWAYS, "%s\n", USAGE_SB_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_ODE_OPTS );
  ui_print ( VALWAYS, "%s\n", USAGE_FILE_OPTS );
  printf ( "\trecovery opts\n" );
  printf ( "\t  -rm    <time> : time of submission to remove\n" );
  printf ( "\t  -resub <time> : time of submission to resubmit\n" );
  printf ( "\t  -date <date>  : use date if <time> is not based on today\n" );
  ui_print ( VALWAYS, "%s %s\n", progname, USAGE_VER_USAGE );
}                                                             /* print usage */
