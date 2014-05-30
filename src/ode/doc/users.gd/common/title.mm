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
.\" Revision 1.3.10.1  1995/05/17  19:42:32  robert
.\" 	check-in for free & unenc. release
.\" 	[1995/05/17  19:40:03  robert]
.\"
.\" Revision 1.3.8.1  1993/08/26  15:49:25  marty
.\" 	CR # 628 - Update to ODE 2.3
.\" 	[1993/08/26  15:49:09  marty]
.\" 
.\" Revision 1.3.6.2  1993/04/16  13:09:12  damon
.\" 	CR 459. Updated rev to 2.3
.\" 	[1993/04/16  13:06:09  damon]
.\" 
.\" Revision 1.3.4.5  1992/12/03  19:11:38  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:57  damon]
.\" 
.\" Revision 1.3.4.4  1992/11/18  00:54:33  damon
.\" 	CR 12. Updated revision information
.\" 	[1992/11/18  00:54:11  damon]
.\" 
.\" Revision 1.3.4.3  1992/06/16  23:09:23  damon
.\" 	2.1.1 touch-up
.\" 	[1992/06/16  22:54:58  damon]
.\" 
.\" Revision 1.3.2.2  1992/04/17  20:18:30  pshaw
.\" 	Add CMU copyright
.\" 	Update copyright string to 1992
.\" 	Change version to 2.1.1
.\" 	[1992/04/17  20:16:23  pshaw]
.\" 
.\" Revision 1.3  1991/12/17  21:00:36  devrcs
.\" 	Fixed up page numbering
.\" 	[1991/12/11  21:33:53  mckeen]
.\" 
.\" 	Added copyright notice
.\" 	[1991/12/06  21:06:45  mckeen]
.\" 
.\" Revision 1.2  1991/12/05  20:57:01  devrcs
.\" 	Add ODE release number
.\" 	[1991/11/08  14:45:09  marty]
.\" 
.\" 	preliminary edit/rewrite
.\" 	[91/06/18  13:28:39  casey]
.\" 
.\" 	 Now prints current date on title page
.\" 	[91/02/19  17:00:38  marty]
.\" 
.\" 	Separating DUG into common and OSC versions
.\" 	[91/01/16  17:03:18  randyb]
.\" 
.\" Revision 1.6  90/11/03  10:28:22  devrcs
.\" 	Pre Tools II release
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Contents of Common DUG: Title information
...\"*********************************************************************
.\"
...\"*********************************************************************
...\"          Macro Definitions
...\"*********************************************************************
.\"     Format for displaying output from commands: "(O"
.de (O
.S -2
.DS 
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
\"***.PF ""				\"*** Prevent page footer
.ds HF 3 3 3 3 3 3 3		\"*** Set heading fonts; bold bold italic
.ds HP 20 16 14 12 12 12 12	\"*** Set heading point sizes
.nr Hb 4			\"*** Headings to level 3 begin new line
.nr Hs 3			\"*** 1/2 vertical space after headings
\"*** .nr Ej 1			\"*** New page on each H 1 heading
...\"*********************************************************************
...\"          Enter the title of the book:
...\"*********************************************************************
.S 20
.SP 1.5i
.B "OSF Development Environment
.SP 1
.B "User's Guide" 
.S
...\"*********************************************************************
...\"          Enter the book's revision number
...\"*********************************************************************
.S 12
.SP 1i
ODE Release 2.3.4 \fB A \fR(Spring 1995)
.SP
Printed on:  \*(DT
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
Copyright (c) 1990, 1991, 1992, 1993, 1994, 1995  Open Software Foundation, Inc.
.P
This documentation and the software to which it relates are derived in part
from materials supplied by the following:
.P
Copyright (c) 1989, 1990 Carnegie-Mellon University
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
