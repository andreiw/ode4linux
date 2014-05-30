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
.\" HISTORY
.\" $Log: shared.mm,v $
.\" Revision 1.1.4.4  1993/06/07  17:14:35  damon
.\" 	CR 458. Added setup instructions for .sandboxrc and sets file
.\" 	[1993/06/07  17:14:29  damon]
.\"
.\" Revision 1.1.4.3  1993/06/07  14:21:30  damon
.\" 	CR 458. Added info about sc.conf file
.\" 	[1993/06/07  14:21:21  damon]
.\" 
.\" Revision 1.1.4.2  1993/04/22  15:28:21  damon
.\" 	CR 458. Updated for 2.3
.\" 	[1993/04/22  15:24:19  damon]
.\" 
.\" Revision 1.1.2.4  1993/01/04  18:12:12  damon
.\" 	CR 332. Updated for 2.2
.\" 	[1993/01/04  18:11:38  damon]
.\" 
.\" Revision 1.1.2.3  1992/12/03  19:09:33  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:00  damon]
.\" 
.\" Revision 1.1.2.2  1992/11/19  18:59:21  damon
.\" 	CR 332. New chapter on shared sandboxes
.\" 	[1992/11/19  18:59:08  damon]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 7: Shared Sandboxes\s0\fR'"
.OH "'\fB\s10Chapter 7: Shared Sandboxes\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          Contents of ODE/SAG: Shared Sandbox Configuration
...\"*********************************************************************
.H 1 "Shared Sandboxes"
.iX "sandbox" "shared"
.iX "shared sandbox"
Shared sandboxes, as the name implies, are special sandboxes that are meant
to be shared by multiple users. This chapter describes how to create and
use a shared sandbox.
.H 2 "Creating a shared sandbox"
A shared sandbox is really just a variation of a regular sandbox, so the
first step is to make a sandbox with \fBmksb\fR.
.iX "mksb"
.(O
su devsrc
mkdir /build_base>/<shared_sandbox>
mksb -rc   /<build_base>/<shared_sandbox>
     -back <backing_build>
      -dir <build_base>
           <shared_sandbox> 
.)O
.P
For instance, if you wanted to create a shared sandbox called patches for
DCE 1.0, you would do the following:
.P
.(O
su devsrc
mkdir /project/dce/build/patches
mksb -rc   /project/dce/build/patches
     -back /project/dce/build/dce1.0
     -dir  /project/dce/build
           patches
.)O
.P
Remove the sandbox lock
.ta -.5
.(O
rm src/.BCSlock
.)O
.ta
.P
.iX "SNAPSHOT"
You will also need to follow the directions in Chapter 6 pertaining to
creating directories, log files, and sc.conf files. Don't worry about
the SNAPSHOT file. It
should be empty. The sections that you should read are 6.1.2, 6.1.3, and
6.4.
.H 2 "Distributed Access Setup"
.iX "CONFIG"
Follow the instructions in the Distributed Access Setup section of Chapter
6, Backing Build Configuration. Skip the part about the CONFIG file.
.H 2 "Using a shared sandbox"
For the most part, using a shared sandbox is the same as using a backing
build. You can make a sandbox backed by the shared sandbox, you can do
source control operations with it, and you can build backed by it. You can
also submit from it to the build that it is backed by.
.H 3 "Submitting from a shared sandbox"
Before submitting from a shared sandbox, follow the directions for creating
a .sandboxrc file and a sets file in sections 6.3.1 and 6.3.3 respectively.
.P
Submitting from a shared sandbox is now the same as submitting from a
user sandbox. Simply become the user that owns the shared sandbox, and submit
from the shared sandbox as though you were submitting from a user's sandbox.
.iX ".sandboxrc"
If the .sandboxrc file is not in the user's home directory, make sure
to use the \fB-rc\fR switch to access the correct .sandboxrc file.
