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
.\" $Log: bci.bdy,v $
.\" Revision 1.2.7.1  1993/08/23  18:25:25  marty
.\" 	Reword some sections.
.\" 	[1993/08/23  18:25:10  marty]
.\"
.\" Revision 1.2.5.2  1993/04/19  14:59:14  damon
.\" 	CR 421. Updated for 2.3
.\" 	[1993/04/19  14:59:01  damon]
.\" 
.\" Revision 1.2.3.3  1992/12/02  20:49:43  damon
.\" 	ODE 2.2 CR 183. Added CMU notice
.\" 	[1992/12/02  20:46:42  damon]
.\" 
.\" Revision 1.2.3.2  1992/10/20  18:47:50  damon
.\" 	CR 78. Updated to 2.2
.\" 	[1992/10/20  18:43:08  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:14:11  devrcs
.\" 	removed paragraph about obsolete -rm switch
.\" 
.\" 	updates for ode2.1
.\" 	[1991/11/06  14:36:18  hester]
.\" 
.\" 	Added _FREE_ to copyright marker
.\" 	[91/08/01  08:14:18  mckeen]
.\" 
.\" 	Changes for Reno make
.\" 	[91/03/22  16:24:09  mckeen]
.\" 
.\" $EndLog$
.SH DESCRIPTION
\fBbci\fP stores new revisions of files 
into the source control system.  Files being checked in must
already exist in the source control system.
.PP
This command requires that the copyright marker, 
\fBHISTORY\fP marker, and
\fB$Log...$\fP lines be present in \fIfile\fP.
Standard copyright markers recognized by this command are @OSF_COPYRIGHT@ and 
@OSF_FREE_COPYRIGHT@.  You can configure the backing tree to allow other
copyright markers (See the section  "Source Control Configuration File" in
the System Administrators Guide).
There are times when it is not appropriate to have copyright
and history markers in a file.  To suppress checking of
these markers, you must set the comment leader of the file to "NONE".
See the \fBbcs\fP man page for details.
.PP
The \fI-defunct\fP
option may be used to set the state of the file to "defunct".
.PP
An attempt is made to obtain the log message from
\fIfile\fP by extracting all lines beginning after a
\fBHISTORY\fP line up to but not including a
\fB$Log...$\fP line. The first \fIn\fP
(where \fIn\fP is the length of
the comment leader recorded for the file) characters of each extracted
line are stripped away.
(\fBN.B.\fR be careful with white space variants when manually
editing the log area - most leaders end with a space and the text
typically begins with a tab).
.PP
The option \fI\-m \fP
allows you to specify the message on the command line. (\fBN.B.\fR the message
must be contained in quotes).
.PP
Opportunity is provided to interactively edit the
tentative log message. If no log message was successfully 
extracted from \fIfile\fP
or supplied by \fI\-m\fP,
a draft log message is composed by the user.
.PP
When drafting the log message, it is also possible to edit the copy of
\fIfile\fP which is about to be checked-in,
or to compare this file with the previous version on the branch.
.PP
The 
working file is
left non-writable. 
If the \fI-defunct\fP switch is used, the file is removed.
.ft B

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
bco(1),
bsubmit(1).
