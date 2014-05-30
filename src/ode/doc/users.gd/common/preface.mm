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
.\" $Log: preface.mm,v $
.\" Revision 1.3.4.2  1993/08/30  15:21:44  marty
.\" 	CR # 629 - Fix typo's
.\" 	[1993/08/30  15:21:31  marty]
.\"
.\" Revision 1.3.4.1  1993/08/26  15:59:39  marty
.\" 	CR # 628 - Update to ODE 2.3.
.\" 	[1993/08/26  15:59:24  marty]
.\" 
.\" Revision 1.3.2.2  1992/12/03  19:11:09  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:43  damon]
.\" 
.\" Revision 1.3  1991/12/17  21:00:12  devrcs
.\" 	Fixed up page numbering
.\" 	[1991/12/11  21:33:24  mckeen]
.\" 
.\" Revision 1.2  1991/12/05  20:56:31  devrcs
.\" 	Minor typo
.\" 	[1991/11/22  21:32:11  marty]
.\" 
.\" 	*** empty log message ***
.\" 	[1991/11/11  20:54:23  marty]
.\" 
.\" 	*** empty log message ***
.\" 	[1991/11/11  20:49:23  marty]
.\" 
.\" 	 	More ode2.1 changes
.\" 
.\" 	 	More edits for ode2.1
.\" 	[1991/11/05  22:36:31  marty]
.\" 
.\" 	 	preliminary edit/rewrite
.\" 	 	[91/06/18  13:28:09  casey]
.\" 	[91/06/18  13:46:22  casey]
.\" 
.\" 	 	Separating DUG into common and OSC versions
.\" 	 	[91/01/16  17:02:40  randyb]
.\" 	[91/01/25  10:47:36  randyb]
.\" 
.\" Revision 1.6  90/11/03  10:27:51  devrcs
.\" 	 	Pre Tools II release
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"       Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBPreface\s0\fR'"	\"*** Set odd page footers
.OH "'\fB\s10ODE User\'s Guide\fR''\\\\nP\s0'"	\"*** Set even page footers
.nr P 1					\"*** Start with page two
.af P i					\"*** Use 'i' as format
.nr Hu 1
.SK
...\"*********************************************************************
...\"       Preface for common DUG
...\"*********************************************************************
.HU "Preface"
.nr H1 -1
.nr Hu 2
.P
The
...\"#doctitle
.I "OSF Development User's Guide (DUG)"
explains the concepts behind behind the OSF Development Environment
(ODE),  its methodologies, and the
use of the tools for source control, compilation, and release.
If you are a new user and have decided to familiarize yourself
with the ODE, 
you should read through the introductions and overviews of each chapter,
scanning the examples, before getting into the details.
Experienced developers can go directly to the topic or subtopic
they are interested in and get the details they need.
Listed below are the reference pages related to ODE.
.P
The chapters of this document covers four basic aspects of
ODE: sandboxes, compilation environments, source management, and the submission
of private work to a public backing tree.
.P
Many of the examples in this document use \fBsuzieq\fR as the user-ID,
\fBproj2.0b1\fR as the build name, and \fBlatest\fR as the default build;
\fBpmax\fR is used as the target machine.
.BL
.LI
Chapter 1 of the DUG introduces the basic concepts and terminology
of ODE.
.LI
Chapter 2, "Sandboxes" describe what sandboxes are and how 
one can use them.
.LI
Chapter 3, "Source Control," covers ODE's source control management system.
This includes a description on how ODE manages source control,
the source control operations available to the user, how to
group files into sets, and the operations that can be performed on sets.
The tutorial is concluded in this chapter.
.LI
Chapter 4, "Building Software," details the build process.
.LI
Chapter 5, "Submitting," describes how files get placed from the
developer's private sandbox into the next public build.
This chapter details the \fBbsubmit\fR command for submitting files.
The tutorial is concluded in this chapter.
.LE
.HU "Audience"
This document is written for developers and release engineers using the
ODE tools.. 
.HU "Applicability"
.P
This is Version 3.0 of this document.
It is accurate to the changes made in ODE 2.3.
.HU "Purpose"
The purpose of this document is to provide a guide
to the new and experienced developer using the OSF development
process and tools.
It is also intended to provide an introduction
to the concepts behind those processes and tools.
.HU "Typographic and Keying Conventions"
.P
This document uses the following typographic conventions: 
...\"************************************************************************
...\"      Be sure to modify these so they apply to YOUR book
...\"***********************************************************************
.VL \w@\f(CWoutput/source\ code\fR@u
.LI "\fBBold\fR"
.B "Bold"
words or characters represent system elements that you must use
literally, such as commands, flags, and pathnames. \fBBold\fR words
also indicate the first use of a term included in the glossary.
.LI "\fIItalic\fR"
.I "Italic"
words or characters represent variable values that you must supply.
.ft R
.LI "\f(CWConstant width\fR"
Examples and information that the system displays appear in 
the \f(CWconstant width\fR typeface. 
.LI "[\ \ ]"
Brackets enclose optional items in format and syntax
descriptions. 
.LI "{\ \ }"
Braces enclose a list from which you must choose an item 
in format and syntax descriptions. 
.LI "\ |\ "
A vertical bar separates items in a list of choices.
.LI "<\ \ >"
Angle brackets enclose the name of a key on the keyboard.
.LI "..."
Horizontal ellipsis points indicate that you can repeat the 
preceding item one or more times.
Vertical ellipsis points indicate that you can repeat the 
preceding item one or more times.
.LE
.P
This document uses the following keying conventions: 
.VL \w@\f(CWoutput/source\ code\fR@u
.LI "\fB<Ctrl-\fIx\fB>\fR\ or\ ^\fIx\fR"
The notation \fB<Ctrl-\fIx\fB>\fR or ^\fIx\fR, followed by 
the name of a key, indicates
a control character sequence.  
For example, \fB<Ctrl-c>\fR means that you hold down 
the control key while pressing \fB<c>\fR.
.LE
.HU "Reference Pages" 
.P
The following reference pages relate to ODE:
.br
.1C
\fBbci(1)\fR
.br
\fBbco(1)\fR
.br
\fBbcreate(1)\fR
.br
\fBbcs(1)\fR
.br
\fBbdiff(1)\fR
.br
\fBblog(1)\fR
.br
\fBbmerge(1)\fR
.br
\fBbstat(1)\fR
.br
\fBbsubmit(1)\fR
.br
\fBbuild(1)\fR
.br
\fBcurrentsb(1)\fR
.br
\fBgenpath(1)\fR
.br
\fBmakefiles(5)\fR
.br
\fBmake(1)\fR
.br
\fBmklinks(1)\fR
.br
\fBmksb(1)\fR
.br
\fBresb(1)\fR
.br
\fBsadmin(1)\fR
.br
\fBoderc(5)\fR
.br
\fBsbinfo(1)\fR
.br
\fBuptodate(1)\fR
.br
\fBworkon(1)\fR
.1C
.P
These can be found in appendix A of this document.
Reference pages also exist in Section 3 for the library routines found
in \fBlibsb.a\fR.
.HU "Problem Reporting"
.P
If you have any problems with the software or documentation,
please contact a member of the Release Engineering and Distribution group.
For ODE users outside OSF, you can send mail to 
the Release Engineering group at ode-info@osf.org. 
