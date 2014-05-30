...\" COPYRIGHT NOTICE
...\" Copyright (c) 1992, 1991, 1990  
...\" Open Software Foundation, Inc. 
...\"  
...\" Permission is hereby granted to use, copy, modify and freely distribute 
...\" the software in this file and its documentation for any purpose without 
...\" fee, provided that the above copyright notice appears in all copies and 
...\" that both the copyright notice and this permission notice appear in 
...\" supporting documentation.  Further, provided that the name of Open 
...\" Software Foundation, Inc. ("OSF") not be used in advertising or 
...\" publicity pertaining to distribution of the software without prior 
...\" written permission from OSF.  OSF makes no representations about the 
...\" suitability of this software for any purpose.  It is provided "as is" 
...\" without express or implied warranty. 
...\" 
...\" HISTORY
...\" $Log: admin.mm,v $
...\" Revision 1.1.2.1  1993/11/20  21:37:36  damon
...\" 	CR 801. Added administration chapter. Detailed build locking
...\" 	[1993/11/20  21:37:14  damon]
...\"
...\" $EndLog$
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 8: Administration\s0\fR'"
.OH "'\fB\s10Chapter 8: Administration\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          Contents of ODE/SAG: Administration
...\"*********************************************************************
.H 1 "Administrating ODE
.H 2 "Locking a build against submission"
.iX "locking" "build"
.iX "lock_sb"
.iX "submission" "locking"
.H 3 "Locking the entire build"
To lock a build against submission, create a directory called lock_sb in
the logs directory of the backing build. This will lock all submissions to
the build until the directory is removed.
.iX "locking" "build"
.iX "bsubmit.hold"
.H 3 "Locking portions of a build"
To lock a portion of a build, add an entry to the bsubmit.hold file that
looks like this:
.P
.nf
: <default_set> devsrc; Date: <date>; Time: <time>
./<pattern>
.fi
.P
This will lock any files matching <pattern>. See the match man page for details
on ODE pattern matching.
.P
This feature can also be used to lock the entire build if the pattern is '*'.
