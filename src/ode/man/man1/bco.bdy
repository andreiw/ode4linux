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
.\" Copyright (c) 1992 Carnegie Mellon University 
.\" All Rights Reserved. 
.\"  
.\" Permission to use, copy, modify and distribute this software and its 
.\" documentation is hereby granted, provided that both the copyright 
.\" notice and this permission notice appear in all copies of the 
.\" software, derivative works or modified versions, and any portions 
.\" thereof, and that both notices appear in supporting documentation. 
.\"  
.\" CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
.\" CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR 
.\" ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE. 
.\"  
.\" Carnegie Mellon requests users of this software to return to 
.\"  
.\" Software Distribution Coordinator  or  Software_Distribution@CS.CMU.EDU 
.\" School of Computer Science 
.\" Carnegie Mellon University 
.\" Pittsburgh PA 15213-3890 
.\"  
.\" any improvements or extensions that they make and grant Carnegie Mellon 
.\" the rights to redistribute these changes. 
.\"
.\"
.\" HISTORY
.\" $Log: bco.bdy,v $
.\" Revision 1.2.10.1  1995/05/20  00:29:42  robert
.\" 	add support for -a option
.\" 	[1995/05/20  00:28:53  robert]
.\"
.\" Revision 1.2.8.1  1993/09/13  23:54:33  marty
.\" 	CR # 623 - Update description.
.\" 	[1993/09/13  23:54:07  marty]
.\" 
.\" Revision 1.2.6.1  1993/08/24  13:44:11  marty
.\" 	CR # 623 - Clean up description a bit.
.\" 	[1993/08/24  13:43:58  marty]
.\" 
.\" Revision 1.2.4.2  1993/04/19  15:11:29  damon
.\" 	CR 421. Updated for 2.3
.\" 	[1993/04/19  15:11:17  damon]
.\" 
.\" Revision 1.2.2.3  1992/12/02  20:49:46  damon
.\" 	ODE 2.2 CR 183. Added CMU notice
.\" 	[1992/12/02  20:46:45  damon]
.\" 
.\" Revision 1.2.2.2  1992/10/19  19:04:13  damon
.\" 	CR 83. CR 272. bco updates for 2.2
.\" 	[1992/10/19  19:00:12  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:14:17  devrcs
.\" 	fixed for ode2.1
.\" 	[1991/11/05  22:49:51  hester]
.\" 
.\" 	Added _FREE_ to copyright marker
.\" 	[91/08/01  08:14:29  mckeen]
.\" 
.\" 	Changes for Reno make
.\" 	[91/03/22  16:27:37  mckeen]
.\" 
.\" $EndLog$
.SH DESCRIPTION
\fBbco\fR checks out the latest revision of a file for editing 
from the user's
private branch.  If a private branch does not exist then the
latest revision from the backing tree is used to start a new
private branch.
.PP
The \fI-read\fR option allows you to check out the latest file revision
read-only.  You may also check out any file revision (read only) by
using the \fI-r\fR option together with \fI-read\fR option. The
\fI-r\fR option is currently only allowed when used in conjunction
with the \fI-read\fR option.

The \fI-a\fR option allows you to check out a specific revision from
any other branch onto your private sandbox branch. That is, with the 
proper argument to \fI-a\fR, you can check-out onto your branch a
(writable) copy of any file revision that has been checked in to any 
other private sandbox or public branch.  Use of \fI-a\fR causes the 
\fIancestry\fR to be updated accordingly; note that \fI-a\fR can only 
be used to start or initialize your branch.  
 
If file to be checked out does not already exist in the source control 
system, then \fBbcreate\fI(1)\fR must be run to create it. If a file
to be checked out already exists in the source control system, but
is not contained within the purview of your sandbox/backing tree
chain, then use the \fI-a\fR option to check-out the file from
another branch. The \fBblog -h\fR command can help you determine
branches of interest. 

Excessive need to use the \fI-a\fR option may indicate a problem 
with how your source collection/backing tree was created.  You should 
check with your ODE system administrators in this circumstance.

Once a file is checked out \fIread-only\fR it cannot be checked-in with 
\fBbci\fR.  You must check the file out for editing before checking 
it in.  Simply changing the permissions of the file will cause an error.

Files are incorporated into a set by having its name is added to
the \fB.BCSset-<\fIbranch-name\fB>\fR file.  Files are added to a set
when private branches are created (via \fBbco\fR) and are removed from
a set when the branch is outdates (via \fBbsubmit\fR or \fBbcs\fR).

.SH FILES
.IP \fB~/.sandboxrc\fR 
rc file that specifies default sandbox
.IP \fBrc_files/sets\fR 
list of valid sets in sandbox
.IP \fB.BCSset-<\fIuser_set_name\fB>\fR 
list of files in branch (base directory)
.IP \fB.BCSlog-<\fIuser_set_name\fB>\fR 
record of log messages for branch (base directory)

.SH "SEE ALSO"
bcs(1),
bci(1),
bcreate(1),
blog(1).
