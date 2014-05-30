.\" @OSF_FREE_COPYRIGHT@
.\" COPYRIGHT NOTICE
.\" (c) Copyright 1992, 1991, 1990 OPEN SOFTWARE FOUNDATION, INC. 
.\" ALL RIGHTS RESERVED 
.\" 
.\" HISTORY
.\" $Log: preface.mm,v $
.\" Revision 1.1.2.4  1992/12/03  19:12:42  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:30  damon]
.\"
.\" Revision 1.1.2.3  1992/03/16  15:22:47  hester
.\" 	documented ode-defect mailing list
.\" 	[1992/03/14  19:52:37  hester]
.\" 
.\" 	small changes
.\" 	[1992/03/13  19:45:54  hester]
.\" 
.\" Revision 1.1.2.2  1992/03/10  23:17:45  hester
.\" 	first cut for Motif mini-dug
.\" 	[1992/02/18  23:34:08  hester]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"       Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBPreface\s0\fR'"	\"*** Set odd page footers
.OH "'\fB\s10ODE User\'s Guide for Motif\fR''\\\\nP\s0'"	\"*** Set even page footers
.nr P 1					\"*** Start with page two
.af P i					\"*** Use 'i' as format
.nr Hu 1
.SK
...\"*********************************************************************
...\"       Preface for motif DUG
...\"*********************************************************************
.HU "Preface"
.nr H1 -1
.nr Hu 2
.P
The
...\"#doctitle
.I "OSF Development User's Guide (DUG) Motif Supplement"
provides information about the use of the OSF Development Environment
(ODE) for engineers working on the OSF/Motif offering.  
There is another document, 
.I "OSF Development User's Guide (DUG)"
which discusses in detail the general concepts, processes and methodologies
of ODE, and how to use the tools to control source, compilation, and 
release.
There are also DUG supplements related to other projects such as DCE and OSF/1.
This document only discusses those areas of ODE that are specific to the Motif
project and differ from the description given in the common DUG.
.HU "Audience"
This document is written for developers and release engineers using the
ODE tools on the Motif project. 
.HU "Applicability"
.P
This is Version 1.0 of this document.
It is accurate to the changes made in ODE 2.1.
.HU "Purpose"
The purpose of this document is to provide a guide
to the new and experienced developer using the OSF development
process and tools on the Motif project.
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
.LI "\fBItalic\fR"
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
.P
Note that this draft of the document does not yet conform completely
to these conventions.
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
\fBcurrentsb(1)\fR
.br
\fBgenpath(1)\fR
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
These can be found in appendix A of the common DUG.
.HU "Problem Reporting"
.P
If you have any problems with the software or documentation,
please contact a member of the Release Engineering group.
To report functionality defects in either the code or documentation, 
send mail to the \fBode-defect@osf.org\fP mailing list.
