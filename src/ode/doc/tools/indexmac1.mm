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
.\" $Log: indexmac1.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:09:52  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:10  damon]
.\"
.\" Revision 1.2  1991/12/05  21:03:26  devrcs
.\" 	Modified to build in ODE 2.1
.\" 	[91/07/17  10:03:49  mckeen]
.\" 
.\" $EndLog$

...\"	index formatting macros
...\"
...\"
...\"	Iy  --  called between letters of the alphabet
.de Iy
.if !\\$1 \{\
.	fl
.	sp 5v
.	ne .75i
.	in \\n(I#u						\" do indent
\s30\&\\$1\s0
.	sp 1
.	rm I! I@
'	br \}
..
...\"
...\"
...\"	Ix  --  called for an individual index item
.de Ix
'in \\n(I#u						\" do indent
.if !\\$1\\*(I! \{\
.br
.sp .5v                           	\" make sure we're at the start of a line
.ti 0							\" major is always at left margin
\&\\$1\c\"						\" and - output "Major"
.ds I! \\$1\"					\" save major name
.	rm I@
'	br \}
.ie \\$2\\*(I@ \{\
.	ie \\$4 , \\$3\c\"	\" same minor - just output page #
.	el , \fB\\$3\fP\c\"			\"     highlight version
'	br \}
.el \{\
.	br							\" make sure we're on a new line
.	fl
.	ie \\$4 \&\\$2, \&\\$3\c\"	and output "Minor, page#"
.	el \&\\$2, \fB\\$3\fP\c\"	\"     highlight version
.	ds I@ \\$2\"				\" save minor name
'	br \}
..
...\"
...\"	the string I! is used to hold the last major index name
.ds I!
...\"
...\"	the string I@ is used to hold the last minor index name
.ds I@
...\"
...\"	the register I# is used to hold the current indent
.nr I# .5i
...\"
...\"	to get around formatter and sorting limitations:
'fl
...\"
...\"
...\"
...\"	do everything in two column mode:
.2C
.rs
.nh			\" NO hyphenation
.na			\" no justification
.nr Hu 1
.HU "Index"
.tr ~-^\&\"	\" tilde becomes a dash, hat goes to null
