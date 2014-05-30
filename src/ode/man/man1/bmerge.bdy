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
.\" $Log: bmerge.bdy,v $
.\" Revision 1.2.6.1  1993/08/24  14:01:19  marty
.\" 	CR # 623 - Clean up the description a bit.
.\" 	[1993/08/24  14:01:02  marty]
.\"
.\" Revision 1.2.4.2  1993/04/20  18:19:12  damon
.\" 	CR 421. Updated for 2.3
.\" 	[1993/04/20  18:18:07  damon]
.\" 
.\" Revision 1.2.2.3  1992/12/02  20:50:03  damon
.\" 	ODE 2.2 CR 183. Added CMU notice
.\" 	[1992/12/02  20:47:01  damon]
.\" 
.\" Revision 1.2.2.2  1992/11/08  16:39:06  damon
.\" 	CR 272. Updated to 2.2
.\" 	[1992/11/08  16:33:19  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:14:52  devrcs
.\" 	Changes for Reno make
.\" 	[91/03/22  16:34:45  mckeen]
.\" 
.\" $EndLog$

.SH DESCRIPTION
\fBbmerge\fR merges changes applied to different revisions of a file.
.PP
This command is primarily used to keep development of a file
on a private branch in-sync with changes made to the backing build.
.PP
By default, \fBbmerge\fR merges the most recently checked-in revision of the
user's file with the
revision of the file in the backing build. To find out what revision this is,
you can run \fBbstat -b \fIfile\fR. You must check-in files with \fBbci\fR
before running \fBbmerge\fR.
.PP
If no changes have been made to the revision in the backing build, then
\fBbmerge\fR doesn't do anything to the file. If there have been changes,
then \fBbmerge\fR will do a 3-way diff to produce the merged file. The
three revisions participating in the diff are: the top of the user's private
branch, the ancestor of the user's private branch, and the revision in the
backing build. For a more detailed description of merging, refer to the
ODE Users Guide.
.PP
An opportunity is provided to interactively edit the
merged \fIfile\fR, which is especially important
if the merge produced conflicts which must be resolved
manually. At this point, it is also possible
to check-out the previous version on the branch as
\fIfile\fR (i.e. when no changes from the merge revision
are applicable after the merge),
to check-out the merge revision as
\fIfile\fR
(i.e. when no changes from the current branch are applicable after the merge),
to compare this file to the previous version on the branch,
to compare this file to the merge revision
from which it was merged, and
to perform the merge operation over again
(when manual editing of the merged \fIfile\fR
has been botched so thoroughly as to suggest that
starting over again from the top may be prudent).

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
bci(1),
bstat(1),
bsubmit(1).
