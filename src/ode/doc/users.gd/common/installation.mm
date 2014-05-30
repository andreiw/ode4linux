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
.\" $Log: installation.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:11:00  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:40  damon]
.\"
.\" Revision 1.2  1991/12/05  20:56:25  devrcs
.\" 	preliminary edit/rewrite
.\" 	[91/06/18  13:27:59  casey]
.\" 
.\" 	Kill multiple occurrence of Endlog, HISTORY, or copyright header
.\" 	[91/02/04  16:50:54  robert]
.\" 
.\" 	Separated DUG into common DUG and OSC Supplemental
.\" 	[91/01/25  10:35:15  randyb]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Reset page information for chapters in DUG
...\"*********************************************************************
.EH "'''\fIODE User's Guide\fR'"
.OH "'\fBRelease Areas\fR'''"
.nr N 5
.nr P 0                			\"*** reset page number to page 1
.af P 1                			\"*** reset page number to Arabic
.nr Hs 4
.SK
...\"*********************************************************************
...\"          Contents of DUG: Installation
...\"*********************************************************************
.H 1 "Creating Release Areas"
The build step described in the previous chapter builds all executables
and places them in a sandbox \fBobj\fR directory.  Unfortunately the
\fBobj\fR tree is
not organized in a way that can be easily downloaded to a system for
use as system software, rather it is in a directory structure
that mirrors that of the src tree.  
.P
One of the passes mentioned in the chapter on building is
the \fBinstall\fR pass.  This pass does not install software on your
system, rather, it organizes all built objects in a directory structure
that mirrors that of an OSF/1 system.  
For example, the command \fBwakeup\fR when built might be in a sandbox under
\fBobj/\fImachine\fB/bin/wakeup/wakeup\fR and could have any owner,
group, and set of permissions.
On a users system, however, \fBwakeup\fR should be found 
under \fBusr/bin/wakeup\fR
with \fBbin\fR as both owner and group and permissions set to 755.
This directory structure can easily
be downloaded to a system using the \fBtar\fR utility.
.P
The build pass that sets up this directory structure
is called \fBinstall\fR but it is not an installation.  It is
\fICreating a Release Area\fR.  
A release area is merely an identifiable collection
of built software that is \fIreleased\fR for testing, benchmarking,
or internal use.  At OSF, many release areas are set up
to represent different instances of the built software.  
.P
To build a release tree, run \fBbuild\fR with the target \fBinstall_all\fR
and the path to the top of the release tree.
It sets owners, groups, and
permissions, so,  
you must be \fBroot\fR to do this. 
For example:
.P
.ti 2
\fBsu\fR
.ti 2
\fBcd /sandboxes/suzieq/symphony/src\fR
.ti 2
\fBbuild TOSTAGE=/sandboxes/suzieq/symphony/install install_all\fR
.P
It is, of course, possible to install only part of the tree or even
a single file, for example:.
.P
.ti 2
\fBsu\fR
.ti 2
\fBcd /sandboxes/suzieq/symphony/src/usr/bin/ls\fR
.ti 2
\fBbuild TOSTAGE=/sandboxes/suzieq/symphony/install install_all\fR
.br
or alternatively
.ti 2
\fBbuild TOSTAGE=/sandboxes/suzieq/symphony/install install_ls\fR
.P
The \fBinstall\fR pass uses the following variables defined in makefiles 
to  installing objects into the release areas.  
Changing how an executable is to be placed in a release area requires
simply changing these variables in the Makefile.
.P
.BL
.LI
.B IDIR 
- Specifies the relative directory to place the target.
.LI
.B ILIST
- Specifies a list of objects to be installed into the release area.
.LI
.B IOWNER
- Specifies the owner to set the object installed.
.LI
.B IGROUP
- Specifies the group to set the object installed.
.LI
.B IMODE
- Specifies the permissions to set the object.
.LI
.B ILINKS
- Specifies a symbolic link to create in the release area.
.LE
