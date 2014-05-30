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
.\" $Log: submit.mm,v $
.\" Revision 1.3.6.1  1993/08/26  16:33:17  marty
.\" 	CR # 628 - Update to ODE 2.3
.\" 	[1993/08/26  16:33:05  marty]
.\"
.\" Revision 1.3.4.3  1993/05/14  20:01:53  damon
.\" 	CR 459. Removed tutorial section
.\" 	[1993/05/14  20:01:41  damon]
.\" 
.\" Revision 1.3.4.2  1993/04/16  16:01:21  damon
.\" 	CR 459. Updated for 2.3
.\" 	[1993/04/16  16:01:12  damon]
.\" 
.\" Revision 1.3.2.2  1992/12/03  19:11:35  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:55  damon]
.\" 
.\" Revision 1.3  1991/12/17  21:00:31  devrcs
.\" 	Fixed up page numbering
.\" 	[1991/12/11  21:33:46  mckeen]
.\" 
.\" 	Final edits from DUG review
.\" 	[1991/12/06  21:34:39  damon]
.\" 
.\" 	Changes as per review
.\" 	[1991/12/03  14:16:52  damon]
.\" 
.\" 	Signifigantly expanded the material which explains the submission
.\" 	process.
.\" 	[1991/11/04  17:59:03  damon]
.\" 
.\" 	Updated tutorial, made superficial changes to rest
.\" 	[91/10/04  10:25:10  damon]
.\" 
.\" 	Changed for new bsubmit
.\" 	[91/08/16  18:26:29  damon]
.\" 
.\" 	preliminary edit/rewrite
.\" 	[91/06/18  13:28:33  casey]
.\" 
.\" 	Separated DUG into common DUG and OSC Supplemental
.\" 	[91/01/25  10:38:16  randyb]
.\" 
.\" Revision 1.4  90/10/07  21:54:46  devrcs
.\" 	Pre Tools II release
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Reset page information for chapters in DUG
...\"*********************************************************************
.OH "'\fB\s10ODE User\'s Guide\fR''\\\\nP\s0'"	\"*** Set even page footers
.EH "'\s10\\\\nP''\fBSubmitting\s0\fR'"	\"*** Set odd page footers
.SK
...\"*********************************************************************
...\"          Contents of Common DUG: Submitting
...\"*********************************************************************
.H 1 "Submitting"
During development, all work is performed in sandboxes. The work that one
developer does has no effect on the work of another developer. As developers
complete their work, they update the default build from their sandboxes. When
they have updated the default build, their changes are then visible to all
other developers backed by that build.
.P
The process of updating the default build from a sandbox is called submitting.
The program that handles the submission process is called \fBbsubmit\fR.
.P
This chapter describes the general process of submitting files.  For
complete information on the submit command and its options, refer 
to the \fBbsubmit.1\fR reference page.
.H 2 "The Submission Process"
The goal of any submission is to update a default build to reflect changes
made to files in a developer's sandbox. This includes updating the source
control system, the default build backing tree, and the submission logs. Since
the work of one developer may overlap the work of another developer, this
process needs to be coordinated.
.P
\fBbsubmit\fR coordinates submissions in two ways. It prevents developers from
submitting the same files at the same time and it detects situations in which
the submission of a file would in effect wipe out an earlier submission. The
first situation is handled by putting a hold on submitted files.
.P
All files in the process of being submitted are considered "held." That is,
while a file is being held for submission by one developer, no other developer
may submit it. If any of the files being submitted are held, \fBbsubmit\fR
will notify the user and exit.
.P
If none of the files being submitted are held, \fBbsubmit\fR will proceed to
"validate" the submission. The validation stage consists of checking that each
file being submitted is in a valid state in the source control system. This
stage is explained in detail in the next section of this chapter. After
\fBbsubmit\fR has validated the submission it checks to see if any of the
files require merging.
.P
Merging is necessary because two or more developers may
check out and make different changes to the same version of a file. Without
the merging, all changes excepting those made by the last developer's
submission would be lost.
.P
Let's say that two developers check out and make changes to version 1.1.2.6 of
the file wakeup.c. The first developer to submit his changes will not have to
perform any special action to preserve his work. His submission will produce
version 1.1.2.7 of the file wakeup.c. If the second developer then
submits his changes without performing any special actions, he will produce
version 1.1.2.8 of the file wakeup.c which will not contain the changes made
by the first developer and incorporated in version 1.1.2.7. This situation is
handled by performing a "merge."
.P
A merge is
required for a file only when it is not a direct descendant of the most
recent version in the source control system.
.P
If the ancestor of a file being submitted is the most recent version in the
source control system, that is, the local copy was taken from the default
build and no one has submitted in the time between then and now, no merge
is required. Otherwise, the changes incorporated in the file being submitted
and changes incorporated in the most recent version in the default build are
merged into
one new file. After the user resolves any merge conflicts,
\fBbsubmit\fR checks in the merged files and updates their ancestry information.
.P
At this point, all of the files are ready for submission. There are
three steps in the submission process for each file. The first step is the
check-out step. The file is checked out of the users private branch and
the check-in messages for this branch are condensed into one log message
for the public branch. The result is then checked-in to the public branch.
.P
The last step in the submission process is to update the copy of the file
in the backing build. The files in the backing build are used for doing
builds. Once this step has been completed, the file is
considered to be submitted.
.P
After all files have been submitted, \fBbsubmit\fR updates the appropriate
log files and removes the private branches.
.P
\fBbsubmit\fR keeps track of the work that it has done in two special files,
the SNAPSHOT file and the bsubmit.log file. The SNAPSHOT file contains a
listing of the most recent versions of all of the files in the default build.
The bsubmit.log file contains a history of all of the log information entered
for all of the files submitted.
.P
At the end of the submission process, the user is asked whether or not she
wants to perform an outdate. Outdating removes all of the submitted files
from the user's sandbox and all of the user's versions of the submitted files
from the source control system. If this point is reached with no errors,
\fBbsubmit\fR will inform the user that the submission has succeeded and it
will exit.
.P
.H 2 "Preparing to Submit Files"
\fBbsubmit\fR has a number of requirements that must be satisfied by all of the
files in a submission before any work may take place. To qualify for
submission, a file must be:
.BL
.LI
In your sandbox and in the source control system
.LI
In your current set, or in the set specified to \fBbsubmit\fR
.LI
Read only. This prevents writeable files, which represent un-saved work,
from being submitted.
.LE
.P
When listing files to submit, you can use the \fB-all\fR option or 
you can enter the filenames on the command line.
If you use the \fB-all\fR, all of the files in your current set or the set
specified to \fBbsubmit\fR with the \fB-all\fR option
will be submitted.
Although \fBbsubmit\fR does not accept input from standard input,
you can keep your own list of files and input it by entering a line like:
.SP
.ti 4
\fBbsubmit \fI-options\fB `cat \fImylist\fR`
.H 2 "Merging Files"
If an actual merge is necessary and
the program thinks it successfully merged the files it prints:
.(O
Merge successful\fR
.)O
A merge which contains conflicts that
\fBbsubmit\fR could not resolve produces the message:
.(O
\f(CWWarning: \fInum\fP overlaps during merge\fR
.)O
where \fInum\fR is the number of conflicts it found.
After this warning, it will be necessary to edit the file that \fBbsubmit\fR
created.
.P
You will be given the following prompt:
.P
.(O
Abort, ok, edit, merge, [r]co, [r]diff  [edit]
.)O
.P
At this prompt you have the following options:
.P
.nf
Abort - exit bsubmit
ok - accept the file as it is and proceed to the next file
edit - edit the file
merge - perform the merge again
co - check out the latest version of the file
rco - check out the user's version of the file
diff - diff the common ancestor against the latest version of the file
rdiff - diff the common ancestor against the user's version of the file
.fi
.P
If there are merge conflicts, you will need to edit the file with the
conflicts and decide how to resolve the conflicts.
The conflicts will be delineated by less-than and
greater-than signs separated by equal signs.
The pattern is
.P
.ti 4
.B "<<<<<<"
.ti 3
.I "code being submitted"
.ti 4
.B "======"
.ti 3
.I "code currently in the default build"
.ti 4
.B ">>>>>>"
.P
You need to search through the file for these patterns,
decide which lines are correct and delete the rest.
Remember to delete the less-than, greater-than, and equal signs.
This file becomes the file that will be checked in to the default build
exactly as you have edited it.
.P
If you are absolutely sure the copy of the file you are
submitting is correct and want to overwrite the existing file without
dealing with the merge, you can enter:
.P
.ti 4
.B rco
.P
followed by
.P
.ti 4
.B ok
.P
and the program will use the submitted revision without reference to
the existing file in the default build or the common ancestor.
\fBWARNING:\fR, this procedure removes any changes other developers have made
to the
file unless they were also in the local revision being submitted.
.H 2 "Local Cleanup"
After the submission is complete and the files have been checked into
the default build, checked out again to make them public, and the logs
are updated, you  have the option of cleaning up your local set.
.P
The advantage to outdating the branch is that the next check out
will be based on the revision of the file in the backing tree
instead of on the local branch you already have.
If the file was merged during the submission, the next time 
you want to work on the file, you will
normally want to use the merged revision of the file.
To get this revision, you will have to outdate your
local branch and be backed by the default build.
.H 2 "Submission Failure and Recovery"
Whenever any part of a submission fails, \fBbsubmit\fR prints out one of
two messages. If the submission failed, but no actual work has been done,
\fBbsubmit\fR will print:
.(O
- No work has been done for this submission.
- No files have been changed in any way.
- The files in this submission are not held.
- The use of the -resub option is not required and will not be recognized.

Exiting bsubmit.
.)O
If the submission failed and work has been done, \fBbsubmit\fR will print:
.(O
*** RE-SUBMISSION REQUIRED ***

- Source control information is in an intermediate state.
- Re-submit using -resub \fItime\fB [ -date \fIdate\fB ]\f(CW

Exiting bsubmit.
.)O
where \fItime\fR is the time of submission and \fIdate\fR is the
date of submission.
.P
Resubmissions are based on tracks left by \fBbsubmit\fR as it works.
Each original submission records the user, time, and date of the
submission, as well as the files being submitted, in the
the \fBbsubmit.hold\fR file.
During a resubmission, \fBbsubmit\fR uses this file to confirm the
contents of the original submission.
If the owner, time, or date is incorrect, it will not allow the
resubmission to continue.
.P
It also will not allow a resubmission with a different set of files
than those listed in \fBbsubmit.hold\fR.
When you resubmit, \fBbsubmit\fR will not accept a list of files 
because it expects to get the list from \fBbsubmit.hold\fR.
.P
The second file \fBbsubmit\fR looks for during a resubmission is the
\fBtracking\fR log which lists the steps completed in the original
submission.
This filename is in the format \fIH:MM.USER\fR where \fIH\fR is the hour,
\fIMM\fR is the minute of the submission and \fIUSER\fR is the user's name.
The file is located in the source control tree and is not accessible
by users.
On a resubmission, \fBbsubmit\fR uses this information to determine which
steps it has already completed.
.P
Most of the time, \fBbsubmit\fR is able to pick up the submission from
where it left off and you do not have to be involved in fixing
the logs.
There are, however, times when it is necessary to edit the logs
or change an entry.
While it is safe for you to edit your local logs,
the \fBSNAPSHOT\fR, \fBbsubmit.hold\fR, and \fBbsubmit.logs\fR 
files must be treated more carefully.
The program \fBsadmin\fR allows safe access to these
files, for copying, editing, locking and unlocking them.
If you need to work with these files, you should always use this program.
