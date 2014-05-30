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
.\" $Log: trouble.mm,v $
.\" Revision 1.2.6.1  1993/11/20  21:21:59  damon
.\" 	CR 801. Added administration chapter. Moved ch 8 to ch 9
.\" 	[1993/11/20  21:21:31  damon]
.\"
.\" Revision 1.2.4.2  1993/04/22  15:28:08  damon
.\" 	CR 458. Updated for 2.3
.\" 	[1993/04/22  15:24:13  damon]
.\" 
.\" Revision 1.2.2.2  1992/12/03  19:09:39  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:05  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:03:17  devrcs
.\" 	added test_suite directory, fixed some minor errors
.\" 	[1991/11/04  20:02:26  hester]
.\" 
.\" 	removed header of empty paragraph
.\" 	[91/08/05  12:04:46  hester]
.\" 
.\" 	added a mention of the test suite and addded a few
.\" 	more problems/solutions
.\" 	[91/08/01  16:12:03  hester]
.\" 
.\" 	First cut at changes for SAG review.
.\" 	Added some beginnings of things that must be finished.
.\" 	[91/05/09  16:41:15  hester]
.\" 
.\" 	Chapter 8 of SAG
.\" 	[91/01/25  19:10:47  hester]
.\" 
.\" $EndLog$
.\"
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 9: Trouble Shooting and Error Recovery\s0\fR'"
.OH "'\fB\s10Chapter 9: Trouble Shooting and Error Recovery\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          Contents of ODE/SAG: Trouble Shooting and Error Recovery
...\"*********************************************************************
.H 1 "Trouble Shooting and Error Recovery"
.P
This chapter discusses various things which can go wrong in setting up
and administering
ODE and tries to give hints on where to look for fixes to the problems.
It is impossible to predict all the things that can go wrong in setting
up a complex development environment,
therefore, this chapter tries to cover the most common problems and to
indicate areas the user should investigate for various types of problems.
.P
This chapter assumes the user has read the preceding manual and has
a good understanding of the steps to install ODE.
.P
The chapter begins with suggestions on testing the ODE tools after initial
setup.
The section after that gives suggestions for fixing some common problems.
The section is divided according to different areas of ODE functionality.

.H 2 "Testing ODE Tools"
Once the ODE tools have been installed, you may want to use the unsupported
test suite that can be found in the \fBsrc/ode/test_suite\fR directory to test your installation.
The test suite will exercise basic commands for each ODE component.
The test suite should be self-explanatory when run.
.P
As a general testing mechanism, keep in mind that most of the commands 
have a \fB-debug\fR switch which may be used to give helpful
information on detailed processing when a problem is encountered.
Additionally, if you are having trouble with a command that is using
the remote authentication programs you can set the environment variable
AUTHCOVER_DEBUG to \fBon\fR to get processing information from those
programs

.H 2 "Error Recovery Procedures"
.P
The following sections give some examples of problems that might 
occur in the daily use/administration of ODE and the suggested
procedure for recovering from the errors.

.H 3 "In Using Makefiles to Build Objects"
.P
If a problem occurs when using the \fBmake\fR or \fBbuild\fR command
with \fImakefiles\fR
to compile programs, it may be helpful to invoke the \fBmake\fR command
with special debug switches set.  For example, the -d A switch will give
all possible debugging information for make.  
More info on the debug flags can be found in the \fBmake\fR man page.

.H 3 "In Using the Backing Tree"
.P
Occasionally the \fBSNAPSHOT\fR file will get corrupted.  
.P
When this happens, you can regenerate the \fBSNAPSHOT\fR file using 
the following command:
.ti 2
\fBcd /\fIbuild-tree/\fBsrc\fR
.ti 2
\fBfind . -type f -print | sort | \\
.ti 2
(cd \fIrcs-tree\fB; xargs rcsstat -q -V -R -r"\fISET_NAME\fP;\\
.ti 2
`cat \fIbuild-tree\fP/CONFIG`") > \fINEW_SNAPSHOT_FILE\fR


.H 3 "In Merging a Build's Files into Source Control"
.P
In the process of merging the sources from a build into source control
you often get conflicts when moving latest branches up the trunk.
.P
When this happens you will get put into the editor automatically and must
edit the file by hand.
You should always choose the code from branch extension version, 
never the trunk, as what you want to select in the merge.

.H 3 "In Submitting"
.P
An error might occur in the middle of the process of 
submitting (\fBbsubmit\fR) a file to source control, and
the file(s) will not get submitted.  
.P
When this happens, the user should use the -resub switch on \fBbsubmit\fR
to resubmit the file at the point in the submission process where it
left off after determining the cause of the initial error.
.P
If that doesn't work then you may have to use the \fBsadmin\fR command
to correct a problem in a \fBbsubmit\fR log.  Refer to the man \fBsadmin\fR
man page for more information.
.SP
.P
Another problem that might happen is when you first try to submit a file
you get an error that says that the revision of the file does not exist.
This may indicate an error in the date give in the \fBCONFIG\fR file.
For example, if the date is from the previous year, then the revision
of the file did not exist at that time.
.bp
