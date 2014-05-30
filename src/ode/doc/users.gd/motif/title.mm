.\" @OSF_FREE_COPYRIGHT@
.\" COPYRIGHT NOTICE
.\" (c) Copyright 1992, 1991, 1990 OPEN SOFTWARE FOUNDATION, INC. 
.\" ALL RIGHTS RESERVED 
.\" 
.\" HISTORY
.\" $Log: title.mm,v $
.\" Revision 1.1.2.3  1992/12/03  19:12:49  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:37  damon]
.\"
.\" Revision 1.1.2.2  1992/03/10  23:18:06  hester
.\" 	more changes to look like the common dug's formatting
.\" 	that was set up by the doc group.
.\" 	[1992/02/18  23:40:52  hester]
.\" 
.\" 	changed point sizes of headings to be like those of the
.\" 	common dug - larger and easier to read
.\" 	[1992/02/18  21:38:37  hester]
.\" 
.\" 	first cut for motif mini-dug
.\" 	[1992/02/18  21:34:00  hester]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Contents of Motif DUG: Title information
...\"*********************************************************************
.\"
...\"*********************************************************************
...\"          Macro Definitions
...\"*********************************************************************
.\"     Format for displaying output from commands: "(O"
.de (O
.S -2
.DS I
.ft CW
..
.\"     End output display format: ")O"
.de )O
.ft P
.DE
.S P
..
...\"*********************************************************************
...\"          Set up headers, footers, headings
...\"*********************************************************************
.ad r				\"*** Sets right justification
.PH "'''"			\"*** Prevent page header
.PF "''PRELIMINARY DRAFT'"	\"*** Pager Footer
.ds HF 3 3 3 3 3 3 3		\"*** Set heading fonts
.ds HP 20 16 14 12 12 12 12  	\"*** Set heading point sizes
.nr Hb 4			\"*** Headings to level 4 begin new line
.nr Hs 3			\"*** 1/2 vertical space after headings
\"*** .nr Ej 1			\"*** New page on each H 1 heading
...\"*********************************************************************
...\"          Enter the title of the book:
...\"*********************************************************************
.S 20
.SP 1.5i
.B "OSF Development Environment"
.SP 1
.B "User's Guide and Reference"
.SP 1
.B "Motif Supplement"
.S
...\"*********************************************************************
...\"          Enter the book's revision number
...\"*********************************************************************
.S 12
.SP 1i
ODE Release 2.1
.SP 1i
Revision 1.0
.SP
\*(DT
.SP 3.5i
Open Software Foundation
.SP .5
11 Cambridge Center
.SP .5
Cambridge, MA 02142
.P
.ad b	\"*** Resets justification
.SK
.P
Copyright (c) 1992, Open Software Foundation, Inc.
.P
Permission is hereby granted to use, copy, modify and freely
distribute this documentation for any purpose without fee, provided
that the above copyright notice appears in all copies and that both
the copyright notice and this permission notice appear in supporting
documentation.  Further, provided that the name of Open Software
Foundation, Inc. ("OSF") not be used in advertising or publicity
pertaining to distribution of the software without prior written
permission from OSF.  OSF makes no representations about the
suitability of this software for any purpose.  It is provided "as is"
without express or implied warranty.
