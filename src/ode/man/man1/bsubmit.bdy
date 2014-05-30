.\"
.\" @OSF_FREE_COPYRIGHT@
.\" COPYRIGHT NOTICE
.\" Copyright (c) 1992, 1991, 1990  
.\" Open Software Foundation, Inc. 
.\"  
.\" Permission is hereby granted to use, copy, modify and freely distribute 
.\" the software in this file and its documentation for any purpose without 
.\" fee, provided that the above copyright notice appears in all copies and 
.\" that both the copyright notice and this permission notice appear in 
.\" supporting documentation.  Further, provided that the name of Open 
.\" Software Foundation, Inc. ("OSF") not be used in advertising or 
.\" publicity pertaining to distribution of the software without prior 
.\" written permission from OSF.  OSF makes no representations about the 
.\" suitability of this software for any purpose.  It is provided "as is" 
.\" without express or implied warranty. 
.\"
.\"
.\" HISTORY
.\" $Log: bsubmit.bdy,v $
.\" Revision 1.1.2.3  1993/04/21  14:17:07  damon
.\" 	CR 421. Fixed typos
.\" 	[1993/04/21  14:15:26  damon]
.\"
.\" Revision 1.1.2.2  1993/04/20  19:46:57  damon
.\" 	CR 421. Split apart from bsubmit.1 for 2.3
.\" 	[1993/04/20  19:46:43  damon]
.\" 
.\" Revision 1.10.2.3  1992/12/03  17:23:51  damon
.\" 	ODE 2.2 CR 183. Added CMU notice
.\" 	[1992/12/03  17:10:03  damon]
.\" 
.\" Revision 1.10.2.2  1992/10/19  20:45:05  damon
.\" 	CR 272. Updated for 2.2
.\" 	[1992/10/19  20:44:39  damon]
.\" 
.\" Revision 1.10  1991/12/05  21:15:06  devrcs
.\" 	Made some changes for new bsubmit
.\" 	[91/08/16  18:08:05  damon]
.\" 
.\" 	Changes to the manpage for Tools II.
.\" 	[91/01/08  14:55:03  randyb]
.\" 
.\" 	Updated to match addition of tracking
.\" 	[90/12/05  15:03:48  randyb]
.\" 
.\" Revision 1.8  90/12/06  14:21:04  devrcs
.\" 	Cleanup copyright and history log comments.
.\" 	[90/11/15  11:46:01  gm]
.\" 
.\" $EndLog$
.\"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
.SH DESCRIPTION
.P
\fBbsubmit\fR takes files from a user's private branch and submits them
to the public branch. It also updates the appropriate backing build for use
with a build environment.
.P
Like all ODE tools, \fBbsubmit\fR requires the user to
have a sandbox and a set to work from.
If the sandbox and set are not specified, \fBbsubmit\fR will
use the default settings.
If it cannot find a sandbox or set, it will exit with an error message.
.P
The list of files to submit can be specified in one of several ways
but each relative to the source directory in the sandbox.
First, if the file is given with an absolute path, i.e. it begins
with a '/', \fBbsubmit\fR searches that path from the sandbox's source
directory down.
Second, if the path isn't absolute, \fBbsubmit\fR will look relative to the
directory the user is in, assuming that directory is underneath the
sandbox's source directory.
If the file is not found there, \fBbsubmit\fR will look relative to the
default set directory.
.P
Thus a user can specify just the name of the file if it is either
in the current directory or in the set's default directory;
otherwise, the path to the file needs to be given.
.P
Another way the user can specify the files to submit is to give
the \fB-all\fR option.
\fBbsubmit\fR will use all the files listed in \fB.BCSset-\fIuser_setname\fR
as the list of files if this option is used.
.P
.SS "Steps for Submission"
.P
The following list enumerates the major steps \fBbsubmit\fR goes through
to submit a file.
Each step is discussed in terms of the build \fBlatest\fR
but applies equally to any build being submitted to.
The steps \fBbsubmit\fR goes through to submit a file to \fBlatest\fR are:
.IP "1)"
Check to see that none of the files to be submitted are checked-out.
.IP "2)"
Hold each of the files being submitted, i.e. do not let anyone else
attempt to submit one of these files
.IP "3)"
Merge the local and \fBlatest\fR revisions of each file
.IP "4)"
Check all merges in to \fBlatest\fR
.IP "5)"
Move the files from the user's private branch to the public branch
and copy the files out onto the \fBlatest\fR build
.IP "6)"
Prompt the user for log information and add this to the submission log
.IP "7)"
Update \fBlatest\fR's snapshot file
.IP "8)"
Release the hold on the files
.P
.SS "The User's Set"
.P
After a file has been submitted,
\fBbsubmit\fR can do a number of things with the branch of the file
in the user's set.
The default case is to prompt the user to outdate the file.
The benefit of outdating the file is that the next time the file
is checked out, the revision will come from the backing tree.
If the file isn't outdated, the next revision will be a continuation
of the branch of the file that was just submitted.
If there is more than one developer working on the file,
the next time a developer submits the file,
the merge is usually simpler if the file is taken off the backing
tree rather than a continuation of the user's branch.
.P
Of course, the user may not want to outdate the file, therefore
.B bsubmit
prompts the user before it does any outdating.
If the user answers "no" to outdating, a copy of the merged version
of the file will be left in the local set.
This version is a read-only copy and is not checked out.
.P
\fB-auto_out\fR, if used in conjunction with \fB-auto\fR, will
eliminate the prompt, i.e. it will automatically outdate the file list.
The purpose behind this option is to provide a completely non-interactive
submission when that is desirable.
.P
.SS "Logs"
After the files have been submitted, \fB bsubmit\fR updates three logs;
the \fBbsubmit.log\fR, the \fBDEFUNCT\fR file, and the \fBSNAPSHOT\fR file.
All submission must finish by successfully updating these logs.
.P
The \fBbsubmit.log\fR is located in the logs directory
and contains a running history of who submitted which files when
and what the major changes to the files were.
\fBbsubmit\fR prompts the user for some of this information and puts the user
in an editor to write the detailed description of the submission.
There are command line options which will give \fBbsubmit\fR
this information so the user does not have to wait for prompts.
The user also gets a copy of the submission log which he is asked to mail
to interested people.
.P
The other two files \fBbsubmit\fR updates are the \fBSNAPSHOT\fR and
\fBDEFUNCT\fR which contains a list all the files in the project
and their current revisions or, in the case of the latter the list of
files to make defunct.
After a submission, these file must be edited to include any new files
and to change the revision number of existing ones.
\fBbsubmit\fR does this without user interaction.
.SS "Recovery"
.P
\fBbsubmit\fR attempts to keep track of it progress so, if there is
a failure, it can fully recover from the problem.
.SS "Tutorial"
As part of the tutorial for the \fBODE User's Guide\fR
and to provide an area for practice submissions,
and submission containing a file in the directory \fB/ode/tutorial/\fR
will not update the SNAPSHOT file.
In this way, nothing submitted to that directory will show up in
builds or be released.

.SH EXAMPLES
.IP "\fBbsubmit -info /usr/bin/wakeup.c\fR"
Indicate what would happen if the file \fB/usr/bin/wakeup.c\fR
in the current sandbox and set was submitted to the default build
but don't actually submit it.
.IP "\fBbsubmit -verbose ./lbin/*\fR"
Submit all the files in the current sandbox which are under the source
tree in \fBlbin\fR to the default build and use the verbose mode.
For this command to work successfully, all the file under
\fBlbin\fR would need to be in the current set.
.IP "\fBbsubmit -auto -auto_out -all\fR"
Submit all the files in the current sandbox and current set to the default
build.
Whenever there is a default answer to a prompt,
use it without stopping for user input.
Afterwards, automatically outdate the files in the set.
.IP "\fBbsubmit -verbose -auto -resub 9:08\fR"
Resubmit the same submission begun by this user a 9:08 a.m. today.

.SH FILES
.P
.IP \fI/build/\fB.sandboxrc\fR 
The submit build's sandbox file.
.IP \fI/build/\fB/logs/SNAPSHOT\fR 
contains the current revision of each file in build.
.IP \fI/build/\fB/logs/DEFUNCT\fR 
contains the names of the files to defunct.
.IP \fI/build/\fB/logs/bsubmit.log\fR 
file containing the log entries for every submission.
.IP \fI<project_rcs_dir>/bsubmit.hold\fR 
file containing the list of files which are held, i.e. currently
being submitted.
A file can only be held by one submitter at a time.

.SH EXIT VALUES
.P
\fBbsubmit\fR returns '0' upon successful completion, '-1' otherwise.

.SH RELATED INFORMATION
.P
bci(1),
bmerge(1),
sadmin(1),
sandboxrc(5).
