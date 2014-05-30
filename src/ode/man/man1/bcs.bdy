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
.\" $Log: bcs.bdy,v $
.\" Revision 1.2.8.2  1993/09/14  14:34:27  marty
.\" 	CR # 623 - Fix rc_files
.\" 	[1993/09/14  14:34:10  marty]
.\"
.\" Revision 1.2.8.1  1993/09/14  00:02:29  marty
.\" 	CR # 623 - A few changes.
.\" 	[1993/09/14  00:02:14  marty]
.\" 
.\" Revision 1.2.6.1  1993/08/23  19:52:12  marty
.\" 	Clean up description a bit.
.\" 	[1993/08/23  19:51:59  marty]
.\" 
.\" Revision 1.2.4.2  1993/04/19  18:24:14  damon
.\" 	CR 421. Updated for 2.3
.\" 	[1993/04/19  18:23:51  damon]
.\" 
.\" Revision 1.2.2.3  1992/12/02  20:49:50  damon
.\" 	ODE 2.2 CR 183. Added CMU notice
.\" 	[1992/12/02  20:46:48  damon]
.\" 
.\" Revision 1.2.2.2  1992/10/19  21:25:35  damon
.\" 	CR 272. Updated to 2.2
.\" 	[1992/10/19  21:25:08  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:14:29  devrcs
.\" 	Changes for Reno make
.\" 	[91/03/22  16:29:10  mckeen]
.\" 
.\" $EndLog$
.SH DESCRIPTION
.PP
This command is a general utility program.  It performs three functions on
files under source control:
changing comment leaders, manipulating source control symbolic names, and
outdating a user's private branch.
.P
The most common functions used by developers are outdating of private branches
and changing of comment leaders.  Outdating a private branch (the 
\fB-o\fR option) will remove
all revisions on the users branch.  This should only be done when all 
changes made
to the file have already been submitted to the backing tree, or, when
the user feels that the work done on the branch is no longer needed
and should be discarded.
.P
Changing the comment leader is often done when the user inadvertently specifies
the wrong comment leader when using the \fBbcreate\fR command.  
.PP
To find the current list of symbolic name associations, comment leaders, and
file revisions, use \fBblog\fR.
.PP
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
bcreate(1),
blog(1),
oderc(5).
