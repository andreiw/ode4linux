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
.\" $Log: title.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:13:43  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:59  damon]
.\"
.\" Revision 1.2  1991/12/05  20:58:52  devrcs
.\" 	Now prints current date on title page
.\" 	[91/02/19  17:05:55  marty]
.\" 
.\" 	Kill multiple occurrence of Endlog, HISTORY, or copyright header
.\" 	[91/02/04  17:55:57  robert]
.\" 
.\" 	Separating DUG into common and OSC versions
.\" 	[91/01/16  17:03:59  randyb]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Contents of OSC DUG: Title information
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
.PF ""				\"*** Prevent page footer
.ds HF 3 3 2 2 2 2 2		\"*** Set heading fonts; bold bold italic
.ds HP 14 12 12 12 12 12 12	\"*** Set heading point sizes
.nr Hb 3			\"*** Headings to level 3 begin new line
.nr Hs 3			\"*** 1/2 vertical space after headings
\"*** .nr Ej 1			\"*** New page on each H 1 heading
...\"*********************************************************************
...\"          Enter the title of the book:
...\"*********************************************************************
.S 20
.SP 1.5i
.B "OSF Development User's"
.SP 1
.B "Guide and Reference"
.SP 1
.B "OSC Supplement"
.S
...\"*********************************************************************
...\"          Enter the book's revision number
...\"*********************************************************************
.S 12
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
