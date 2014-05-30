.\"
.\" @OSF_FREE_COPYRIGHT@
.\" COPYRIGHT NOTICE
.\" Copyright (c) 1995, 1994, 1993, 1992, 1991, 1990
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
.\" HISTORY
.\" $Log: preface.mm,v $
.\" Revision 1.3.6.2  1995/05/22  19:45:03  robert
.\" 	Change/permute instances of Ode 2.3 -> Ode 2.3.4.
.\" 	[1995/05/22  17:13:49  robert]
.\"
.\" Revision 1.3.6.1  1995/05/18  21:43:45  ezf
.\" 	revised copyright notice
.\" 	[1995/05/18  21:35:29  ezf]
.\" 
.\" Revision 1.3.4.1  1993/08/25  21:23:33  marty
.\" 	CR # 628 - Update it to ODE2.3.
.\" 	[1993/08/25  21:23:11  marty]
.\" 
.\" Revision 1.3.2.3  1992/12/03  19:09:28  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:40:56  damon]
.\" 
.\" Revision 1.3.2.2  1992/11/18  15:26:56  damon
.\" 	CR 332. Changed DUG to User Guide
.\" 	[1992/11/18  15:26:32  damon]
.\" 
.\" Revision 1.3  1991/12/17  21:00:57  devrcs
.\" 	corrected typo
.\" 	[1991/12/09  22:06:58  ezf]
.\" 
.\" Revision 1.2  1991/12/05  21:00:09  devrcs
.\" 	added ode-info mail list documentation and removed some
.\" 	redundant info about chapter contents.
.\" 	[1991/11/06  16:15:18  hester]
.\" 
.\" 	updated to reflect latest chapter arrangement of sag
.\" 	[91/08/01  10:53:55  hester]
.\" 
.\" 	Changes to reflect new chapter layout in revised SAG.
.\" 	[91/05/01  16:23:17  hester]
.\" 
.\" 	preface for SAG
.\" 	[91/01/25  19:04:37  hester]
.\" 
.\" $EndLog$
.\"
...\"*********************************************************************
...\"       Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBPreface\s0\fR'"	\"*** Set even page footers
.OH "'\fB\s10Preface\fR''\\\\nP\s0'"	\"*** Set odd page footers
.nr P 2					\"*** Start with page three
.af P i					\"*** Use 'i' as format for intro
.SK
...\"*********************************************************************
...\"       Preface for ODE System Adminstration Guide
...\"*********************************************************************
.HU "Preface"
.P
The
.I "OSF Development Environment System Administration Guide (SAG)"
explains how to administer the OSF Development 
Environment (ODE), from initial set-up through implementation of
the tools used to control source, compilation and release.
.HU "Audience"
This document is written for ODE administrators or release engineers. 
.HU "Applicability"
.P
This document is accurate to the changes made in ODE 2.3.4.
.HU "Purpose"
The purpose of this document is to provide a guide for the ODE administrator
to installing, porting, configuring and supporting the OSF 
Development Environment.
In addition to the administration of the source control and build tools, 
the tasks required to provide developers with access to up-to-date source
code and builds will also be covered in this document.  
.HU "Typographic and Keying Conventions"
.P
This document uses the following typographic conventions: 
.VL 1.25i
.LI "\fBliteral\ values\fR"
.B "Bold:"
character, words, commands, and keywords including pathnames
which are used literally.
.B "Bold"
words in text indicate the first use of a new term.
.LI "\fIuser-supplied\ values\fR"
.I "Italic:"
words or characters which the user must supply.
.LI "\fBsample\ user\ input\fR"
In examples, information users enter appears in
.B "bold".
.LI "\f(CWoutput\fR"
Information the system displays appears in 
.ft CW
typewriter\  
.ft R
typeface.
.LI "[\ \ ]"
Brackets enclose optional items in command descriptions. 
.LI "{\ \ }"
Braces enclose a list from which the user must choose an item.
.LI "\ |\ "
A vertical bar separates items in a list of choices.
.LI "<\ \ >"
Angle brackets enclose the name of a key on the keyboard or
a generic term which must be replaced by a specific one,
for example, <user-id> must be replaced with an actual user's login id.
.LI "..."
Horizontal ellipsis points indicate the preceding item can be
repeated one or more times.
.LE
.SP 
.P
This document uses the following keying conventions: 
.VL 1.25i
.LI "Ctrl/\ or\ ^"
The notation Ctrl/ or ^, followed by the name of a key, indicates
a control character sequence.  
Hold down the Ctrl key while pressing the key.  
For example, to obtain <Ctrl/c> hold down the Ctrl key while pressing c.
.LI "<Return>"
The notation <Return> refers to the key on the terminal
or workstation that is labeled with the word Return or Enter, or 
with a left arrow.
.LI "entering\ commands"
When instructed to
.B "enter"
a command, type the command name and then press <Return>. 
For example, the instruction
"Enter the 
.B "ls"
command" means typing the
.B "ls"
command and
then pressing <Return>.
In other words, "enter" = type + <Return>.
.LE
.HU "Problem Reporting"
.P
An electronic mailing list has been set up called \fBode-info@osf.org\fR to
facilitate the exchange of information, comments, hints, tips, bug 
fixes, etc. between OSF licensees that are using ODE.
As appropriate, information about bugs and bug fixes along with
development issues will be posted to \fBode-info\fR.  
When you have questions about ODE please feel free to post them to this list,
possibly someone else on ode-info will be able to help.
.P
To be added to the ode-info mailing list please send a request to
\fBode-info-request@osf.org\fR.
.SK
.HU "Introduction"
This document is part of a collection of documents which describe the 
OSF Development Environment (ODE).
Other documents include the \fIOSF Development Environment User's Guide (DUG)\fP
and the man pages.
.P
This document is organized into eight chapters:
ODE Architecture and Development Model, ODE Distribution, 
Building and Installing the Tools, 
Source Control Server Configuration, 
Backing Build Configuration, Shared Sandboxes,
and Trouble Shooting and Error Recovery.
.P
First time administrators should first read Chapter 1 which explains
the concepts of ODE, its logical components, and gives a brief overview 
of how it is used.  
Follow Chapter 1 by becoming familiar
with each chapter by reading its introduction and then scanning its sections.
Follow this by reading the appropriate chapters in detail.

...\"*********************************************************************
...\"       return to arabic page numbering
...\"*********************************************************************
.af P 1					\"*** Use '1' as format for intro
