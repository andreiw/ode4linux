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
.\" $Log: bstat.bdy,v $
.\" Revision 1.2.6.1  1993/08/24  14:09:57  marty
.\" 	CR # 623 - Clean up the description a bi.
.\" 	[1993/08/24  14:09:18  marty]
.\"
.\" Revision 1.2.4.2  1993/04/20  18:19:15  damon
.\" 	CR 421. Updated for 2.3
.\" 	[1993/04/20  18:18:08  damon]
.\" 
.\" Revision 1.2.2.3  1992/12/02  20:50:06  damon
.\" 	ODE 2.2 CR 183. Added CMU notice
.\" 	[1992/12/02  20:47:05  damon]
.\" 
.\" Revision 1.2.2.2  1992/10/19  21:01:28  damon
.\" 	CR 272. Updated for 2.2
.\" 	[1992/10/19  21:00:49  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:14:59  devrcs
.\" 	Changes for Reno make
.\" 	[91/03/22  16:35:16  mckeen]
.\" 
.\" $EndLog$
.SH DESCRIPTION
.PP
This command displays revision information on files in the source
control system.   It is primarily used to list revision numbers
at the end of private and public branches.
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
bci(1),
bco(1),
bcs(1),
blog(1),
bmerge(1),
bsubmit(1).
