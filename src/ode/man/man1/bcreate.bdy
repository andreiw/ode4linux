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
.\" $Log: bcreate.bdy,v $
.\" Revision 1.2.8.1  1993/09/13  23:56:47  marty
.\" 	CR # 623 - Update spelling.
.\" 	[1993/09/13  23:56:35  marty]
.\"
.\" Revision 1.2.6.1  1993/08/23  19:30:48  marty
.\" 	Clean up the description a bit.
.\" 	[1993/08/23  19:30:31  marty]
.\" 
.\" Revision 1.2.4.2  1993/04/19  16:02:53  damon
.\" 	CR 421. Updated for 2.3
.\" 	[1993/04/19  16:02:39  damon]
.\" 
.\" Revision 1.2.2.3  1992/12/03  17:23:45  damon
.\" 	ODE 2.2 CR 183. Added CMU notice
.\" 	[1992/12/03  17:09:57  damon]
.\" 
.\" Revision 1.2.2.2  1992/10/20  18:30:20  damon
.\" 	CR 74. Updated to 2.2
.\" 	[1992/10/20  18:22:38  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:14:23  devrcs
.\" 	expanded description of path for ode2.1
.\" 	[1991/11/05  22:11:04  hester]
.\" 
.\" 	Changes for Reno make
.\" 	[91/03/22  16:28:19  mckeen]
.\" 
.\" $EndLog$

.SH DESCRIPTION
The \fBbcreate\fR command 
enters an empty file entry into the source control system and
leaves a \fIchecked-out\fR version of the file for editing in
the users sandbox.
.P
As with all ODE commands; the file to create can be specified
in one of three ways.  First, as an absolute pathname.   
This path starts at the top of the \fIsrc\fR directory in the sandbox.  
Second, in a 
path relative to the current working directory. Third, as
a file in the current working directory.  
When specifying an absolute or relative pathname; if the 
the path to the file does not exist, the path will be created.
.P
Since \fBbcreate\fR enters an empty file entry into the source
control system it is important to check the file in
(using \fBbci\fR) to save the initial contents of the file.
.P
\fBbcreate\fR can not be used to create an empty directory.
.P
.SH EXAMPLES
.IP "\fBbcreate /usr/bin/wakeup.c\fR"
Creates the file \fBwakeup.c,v\fR in  
the directory
.B /usr/bin
starting from the \fIsrc\fR directory in the sandbox.
.P
.SH FILES
.IP \fB${HOME}/.sandboxrc\fR 
rc file that specifies user's sandbox's and base directories
and the default sandbox
.IP \fI/sandbox\fB/rc_files/sets\fR 
list of valid sets in the sandbox
.IP \fI/sandbox\fB/set/.BCSset-<\fIuser_set_name\fB>\fR 
list of files in set
.IP \fI/sandbox\fB/set/.BCSlog-<\fIuser_set_name\fB>\fR 
record of log messages for set

.SH "SEE ALSO"
bcs(1),
bco(1),
bci(1),
bmerge(1),
oderc(5).
