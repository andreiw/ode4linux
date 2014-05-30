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
.\" HISTORY
.\" $Log: title.mm,v $
.\" Revision 1.3.10.2  1995/05/18  21:43:47  ezf
.\" 	revised copyright notice
.\" 	[1995/05/18  21:36:08  ezf]
.\"
.\" Revision 1.3.10.1  1995/05/17  19:42:29  robert
.\" 	check-in for free & unenc. release
.\" 	[1995/05/17  19:37:46  robert]
.\" 
.\" Revision 1.3.8.1  1993/08/26  14:59:36  marty
.\" 	CR # 628 - Update to ODE2.3
.\" 	[1993/08/26  14:59:24  marty]
.\" 
.\" Revision 1.3.6.2  1993/04/16  13:18:04  damon
.\" 	CR 458. Updated rev to 2.3
.\" 	[1993/04/16  13:17:54  damon]
.\" 
.\" Revision 1.3.4.5  1992/12/03  19:09:35  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:02  damon]
.\" 
.\" Revision 1.3.4.4  1992/11/18  15:26:52  damon
.\" 	CR 332. Updated for 2.2
.\" 	[1992/11/18  15:25:42  damon]
.\" 
.\" Revision 1.3.4.3  1992/06/16  21:53:17  damon
.\" 	2.1.1 touch-up
.\" 	[1992/06/16  21:45:13  damon]
.\" 
.\" Revision 1.3.2.2  1992/04/17  20:17:39  pshaw
.\" 	Add CMU copyright
.\" 	Update copyright string to 1992
.\" 	Change version to 2.1.1
.\" 	[1992/04/17  20:17:07  pshaw]
.\" 
.\" Revision 1.3  1991/12/17  21:01:08  devrcs
.\" 	Added copyright notice
.\" 	[1991/12/06  21:04:06  mckeen]
.\" 
.\" Revision 1.2  1991/12/05  21:03:14  devrcs
.\" 	added ODE release version to title
.\" 	[91/07/31  16:31:45  hester]
.\" 
.\" 	 Now prints current date on title page
.\" 	[91/02/19  16:57:04  marty]
.\" 
.\" 	title page for SAG
.\" 	[91/01/25  19:08:02  hester]
.\" 
.\" $EndLog$
.\"
...\"*********************************************************************
...\"          Contents of SAG: Title information
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
.PF "'''"			\"*** Pager Footer
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
.B "OSF Development Environment"
.SP 1
.B "System Administration Guide"
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
Copyright (c) 1990, 1991, 1992, 1993, 1994, 1995 Open Software Foundation, Inc.
.P
This documentation and the software to which it relates are derived in part
from materials supplied by the following:
.P
Copyright (c) 1989, 1990 Carnegie-Mellon University
.P
Permission to use, copy, modify, and freely distribute this
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appears in all copies and 
that both the copyright notice and this permission notice appear in 
supporting documentation, and that the name of "OSF" or Open Software
Foundation not be used in advertising or publicity pertaining to 
distribution of the software without specific, written prior permission. 

OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL OSF BE LIABLE FOR ANY 
SPECIAL, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN 
ACTION OF CONTRACT, NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING 
OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE 
