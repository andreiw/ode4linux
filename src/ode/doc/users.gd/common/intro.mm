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
.\" $Log: intro.mm,v $
.\" Revision 1.3.6.1  1993/11/18  21:15:56  marty
.\" 	CR # 629 - Updates
.\" 	[1993/11/18  21:14:48  marty]
.\"
.\" Revision 1.3.4.2  1993/08/30  15:44:15  marty
.\" 	CR # 629 -
.\" 	[1993/08/30  15:44:03  marty]
.\" 
.\" Revision 1.3.4.1  1993/08/26  16:02:05  marty
.\" 	CR # 628 - Update to ODE 2.3.
.\" 	[1993/08/26  16:01:53  marty]
.\" 
.\" Revision 1.3.2.2  1992/12/03  19:11:04  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:41  damon]
.\" 
.\" Revision 1.3  1991/12/17  21:00:07  devrcs
.\" 	Fixed up page numbering
.\" 	[1991/12/11  21:33:19  mckeen]
.\" 
.\" 	Final 2.1 review changes
.\" 	[1991/12/05  20:59:44  mckeen]
.\" 
.\" Revision 1.2  1991/12/05  20:56:28  devrcs
.\" 	 	Changes for DUG rewrite
.\" 	[91/07/23  16:15:40  marty]
.\" 
.\" 	 	preliminary edit/rewrite
.\" 	 	[91/06/18  13:28:04  casey]
.\" 	 	new chapter
.\" 	[91/07/09  16:37:23  casey]
.\" 
.\" 	 	Separating DUG into common and OSC versions
.\" 	 	[91/01/16  17:02:52  randyb]
.\" 	[91/01/25  10:47:53  randyb]
.\" 
.\" Revision 1.5  90/11/03  10:27:56  devrcs
.\" 	 	Pre Tools II release
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Reset page information for chapters in DUG
...\"*********************************************************************
.OH "'\fB\s10ODE User\'s Guide\fR''\\\\nP\s0'"	\"*** Set even page footers
.EH "'\s10\\\\nP''\fBIntroduction\s0\fR'"	\"*** Set odd page footers
.nr P 0                                 \"*** reset page number to page 1
.af P 1                                 \"*** reset page number to Arabic
.SK
...\"*********************************************************************
...\"          Contents of common DUG: Introduction
...\"*********************************************************************
.H 1 "Introduction"
\fIThe OSF Development Environment User's Guide\fR
(DUG) is part of a collection of documents that describe the
OSF Development Environment (ODE).
Other documents include the \fIOSF Development Environment 
System Administration Guide\fR and the man pages.
.H 2 "The OSF Development Environment"
.P
The OSF Development Environment (ODE)
is designed to allow simultaneous development on multiple
revisions of a single set of sources to be compiled for a
variety of different and essentially incompatible hardware platforms.
At the same time it must satisfy the needs 
to ship complete, reproducible systems to customers
while being flexible enough for  individual development.
.P
Three basic areas to ODE are:
.BL
.LI
Source code control
.LI
Build Environment
.LI
Private and Public work areas
.LE
.SP
Each area must allow the individual developer to work
independently of other developers, yet allow 
Release Engineering to bring this work together on a regular basis
to create systems for testing and release.
.P
The source control mechanism protects a public
revision of each file while
allowing developers to simultaneously modify private revisions.
It provides controls so these private changes, once they have
been built and tested, can be merged back
together and integrated with the public revision.
Finally, source control provides a method for reproducing earlier
releases for bug fixes.
.P
The build environment works with source control to
facilitate the building of systems for both release and individual
development.
It provides a standard set of tools, header files, and libraries
allowing official systems to be duplicated while
giving developers the flexibility to insert their own tools
and files as needed.
Much of the details of how a system is to be built is embedded in the
ODE common makefiles and the build tools.  Within ODE the build
environment "knows" a great deal about how the system is to be built.
.P
The ODE build processes are based on the UNIX\*F command \fBmake\fR
.FS
UNIX is a registered trademark of UNIX Systems Laboratories, Inc. in the 
U.S. and other countries.
.FE
and associated \fBMakefiles\fR.
ODE uses an enhanced version of \fBmake\fR, which has functionality to
support the build environment.
.H 3 "Terminology"
.P
You should understand the following terms before proceeding:
.VL 15
.LI \fBbuild\fR
A front-end to \fBmake\fR.
.LI \fIa build\fR
A complete set of sources, objects, and binaries which have been "built"
and put in one place.
.LI "\fBdefault build\fR"
For each project there is a default build that contains the newest
revisions of submitted sources.
In this document, that build is referred to as \fIlatest\fR;
see the supplemental DUGs for the actual name of the default build for
each project.
.LI \fBdefunct\fR
This refers to making a file that is under source control inactive.
Once it is made defunct, it can no longer be checked out for editing.
.LI "\fBoutdating\fR"
Removes from source control all references to work done on a file
in a private sandbox.
.LI \fBproject\fR
A set of sources that have been grouped together and are treated as
a unit.
Projects can be as large as the OS and as small or smaller than ODE itself.
Each project has separate builds and a separate default build from all
other projects.
.LI \fBsandbox\fR
A private working area that a developer owns and controls.
.LI \fBset\fR
A group of sources within a sandbox that can be manipulated as a
unit using the ODE tools.   
.LI "\fBbacking trees\fR"
A complete set of sources, compilation tools, header files, and libraries
that support a sandbox.
.LE
