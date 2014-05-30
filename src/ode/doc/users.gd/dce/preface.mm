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
.\" $Log: preface.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:12:13  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:12  damon]
.\"
.\" Revision 1.2  1991/12/05  20:57:26  devrcs
.\" 	merged from dce/devkit version
.\" 	[91/02/21  11:59:11  ezf]
.\" 
.\" 	Changed all occurences of and references to "mini-DUG" to "supplemental DUG".
.\" 
.\" 	rewrote Problem reporting
.\" 	[91/01/25  16:59:01  terry]
.\" 
.\" 	Newly created for the DCE mini-DUG.
.\" 	[91/01/24  17:15:59  terry]
.\" 
.\" 	Newly created for DCE mini-DUG.
.\" 	[91/01/24  16:43:01  terry]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"       Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBPreface\s0\fR'"	\"*** Set even page footers
.OH "'\fB\s10Preface\fR''\\\\nP\s0'"	\"*** Set odd page footers
.nr P 1					\"*** Start with page two
.af P i					\"*** Use 'i' as format
.SK
...\"*********************************************************************
...\"       Preface for DCE DUG
...\"*********************************************************************
.HU "Preface"
.P
The
...\"#doctitle
DCE supplemental \fIDevelopment User's Guide (DUG)\fP
provides information about about use of the OSF Development Environment (ODE)
for developers working on the OSF Distributed Computing Environment (DCE)
offering.
There is a common DUG which explains in detail the general concepts, 
processes and methodologies of the ODE, and how to use the ODE tools to 
control source modification, compilation, and release.  There are also other
DUG's that provide information on the use of the ODE tools for development
work on other offerings.  This document only discusses areas of the ODE that
differ from what is described in the common DUG when working on the DCE
offering.
.P
If you have familiarized yourself with other supplemental DUG's, you should be aware
that the concepts and examples in other supplemental DUG's are not necessarily
relevant to this particular supplemental DUG.
.HU "Audience"
This document is written for developers and release engineers using the
ODE tools.  
.P
There is also an appendix that contains information for the person
who will set up and maintain the ODE environment for developers working on 
DCE; the DCE system administrator.  This appendix contains information about
setup and maintenance of the ODE when used for development on 
DCE.  The DCE system administrator should read
the \fIOSF Development Environment System Administration Guide\fP in order to 
grasp the fundamentals of ODE system administration, and refer to the appendix
for differences specific to the DCE environment.
.HU "Applicability"
.P
This is Version 1.0 of this document.
It is accurate to the changes made in ODE as of February 1, 1991.
.HU "Purpose"
The purpose of this document is to provide a guide
to the new and experienced developer using the DCE development
processes and tools.
It is also intended to provide an introduction
to the concepts behind those processes and tools.
.HU "Typographic and Keying Conventions"
.P
This document uses the following typographic conventions: 
.VL 1.75i
.LI "\fBliteral\ values\fR"
.B "Bold:"
character, words, commands, and keywords including pathnames
which are used literally.
.B "Bold"
words in text indicate the first use of a new term.
.LI "\fIuser-supplied\ values\fR"
.I "Italic:"
words or characters which the user must supply.
.LI "\fBsample\ user\ input\fR"
In examples, information users enter appears in
.B "bold".
.LI "\f(CWoutput\fR"
Information the system displays appears in 
.ft CW
typewriter\  
.ft R
typeface.
.LI "[\ \ ]"
Brackets enclose optional items in command descriptions. 
.LI "{\ \ }"
Braces enclose a list from which the user must choose an item.
.LI "\ |\ "
A vertical bar separates items in a list of choices.
.LI "<\ \ >"
Angle brackets enclose the name of a key on the keyboard or
a generic term which must be replaced by a specific one,
for example, <user-id> must be replaced with an actual user's login id.
.LI "..."
Horizontal ellipsis points indicate the preceding item can be
repeated one or more times.
.LE
.SP 
.P
This document uses the following keying conventions: 
.VL 1.75i
.LI "Ctrl/\ or\ ^"
The notation Ctrl/ or ^, followed by the name of a key, indicates
a control character sequence.  
Hold down the Ctrl key while pressing the key.  
For example, to obtain <Ctrl/c> hold down the Ctrl key while pressing c.
.LI "<Return>"
The notation <Return> refers to the key on the terminal
or workstation that is labeled with the word Return or Enter, or 
with a left arrow.
.LI "entering\ commands"
When instructed to
.B "enter"
a command, type the command name and then press <Return>. 
For example, the instruction
"Enter the 
.B "ls"
command" means typing the
.B "ls"
command and
then pressing <Return>.
In other words, "enter" = type + <Return>.
.LE
.P
Note that this draft of the book does not yet conform completely
to these conventions.
.HU "Problem Reporting"
.P
Please report problems with the software or documentation as follows:
.VL 20
.LI "Within OSF:" 
report problems to a member of the Release Engineering and
Distribution group;
.LI "All others:" 
report problems to OSF.
.LE
.SK
.HU "Introduction"
This guide is part of a collection of documents which describe the
Open Software Foundation's OSF Development Environment (ODE).
Other documents include: the \fIODE System Administration Guide\fR, which
describes how to set up the ODE; the common
\fIDevelopment User's Guide\fR (DUG), which describes the shared portions of the
development environment, tools, and processes which apply to any organization
using ODE; and other supplemental DUG's which give specific
information for using the ODE for development on a particular offering.
Other supplemental DUGs include the \fBOSC\fR and \fBMotif\fR DUG's.
.P
This document contains DCE specific information on using ODE
tools and processes.
The best way to learn how development is done for DCE is to introduce
one's self to ODE as explained in the common DUG.
The introduction in that document suggests a good way to get started.
.P
Once the developer has a general understanding of ODE, she can return
to this document for specific details and examples.
.P
This document is organized into the same five chapters as the common DUG:
Sandboxes, Source Management, Compilation, Submitting Files,
and Installation.
There are no additional chapters specific to the DCE project.
.P
An attempt has been made to make the general structure of each chapter
similar to the common DUG:
.SP
.DS
  I. Topic 1
     Introduction
        Overview
        Philosophy/history
     A. Sub topic one
         Overview
           Detail
             More Detail
          Examples
     B. Sub topic two
         Overview
           Detail
             More Detail
          Examples
        1. Sub-sub topic 
           etc
   II. Topic 2
     etc
   III. Tutorial
.DE
However, it is not always necessary to have all these sections in
each chapter.

.HU "Introduction to ODE for DCE"
Before proceeding with a discussion of the specific elements of ODE for DCE, 
it will be helpful to grasp the larger framework for DCE development.
.P
DCE is an offering that is being developed by a variety of companies, known as
technology providers, including DEC, Hewlett-Packard, Siemens, and Transarc.
All of the technology providers submit their source code, along with test results and related documention, to IBM.
IBM integrates and tests the technology submissions.
IBM then makes the code available to OSF for integration into the OSF/1 offering.
.P
As is the case in any software engineering effort, the development of DCE
requires facilities for source control, code development and testing, product
building, product release, and product installation. The system that OSF
uses to meet these requirements is the OSF ODE,
which is comprised of \fBbcs\fP (source control), the \fBsandbox\fP
environment (code development and testing), and the \fBbuild\fP environment 
(product build, release, and installation). The ODE and associated 
documentation are made available for other parties interested in using 
this sytem. It is not necessarily the case, however, that ODE is required 
in order to do DCE development/integration. Within OSF, all of the components 
of the ODE are used in the development cycle. Other organizations 
utilize a subset of the facilities provided by the ODE, generally those 
provided for code development and testing (the sandbox environment).
.P
The following terms are defined in the common DUG but are placed here
for the reader's convenience.
.VL 15
.LI \fBbuild\fR
(the tool)
a tool for compiling objects and binaries; supersedes "make" in most cases.
.LI \fBbuilds\fR
complete sets of sources, objects, and binaries which have been "built"
and put in one place.
.LI "\fBdefault build\fR"
For each project there is a default build which contains the newest
revisions of submitted sources.
In this document, that build is referred to as \fBdce 1.0\fR.
.LI \fBproject\fR
a set of sources which have been grouped together and are treated as
a unit.
Projects can be as large as the OS and as small or smaller than ODE itself.
Each project has separate builds and a separate default build from all
other projects.
.LI \fBsandbox\fR
a private working area which a developer own and controls.
.LI \fBbcs\fR
a group of revision control programs which operate on top of \fBrcs\fR.
.LI \fBset\fR
a grouping of sources within a sandbox which can be manipulated as a
whole using the bcs commands.
The naming conventions for sets is lower case for private sets and
upper case for build and shared sets (see \fBshared set\fR, below).
Private sets get the name of the user as a prefix, so a set named
"melody" becomes "suzieq_melody".
.LI "\fBbacking trees\fR"
any sandbox or build (including the default build) that backs a sandbox. For
example, if the sandbox that is being backed does not have a file locally, ODE
searches the backing tree for the file. Note that backing trees can also be 
backed.
.LI "\fBchild sandbox\fR"
how the backing tree views the sandboxes which use it as a backing tree.
For example, if sandbox \fBsymphony\fP is backed by build \fBlatest\fP,
then latest has symphony as one of its child sandboxes.
.LI "\fBshared sandbox\fR"
a sandbox which backs another sandbox.
.LI "\fBshared set\fR"
a set which multiple developers check out from and submit to.
The default builds have a shared set that usually bears the same name as the
build, replacing the lower case letters with capital letters.
Shared sandbox's must have a shared set if developers are going to
submit to the sandbox.
Note that the name of the shared set is in capital letters and does
not have a user name as a prefix.
.LI \fBtrunk\fR
the rcs tree's primary revisions of each file.
A new revision is normally created with each build if the file
has been submitted since the previous build.
The top of the trunk is normally the revision of the file in
the last build not including the default build.
.LI \fBbranch\fR
a bcs copy of a file taken off the rcs tree.
Any change made to a branch remains private until the developer
submits the file to the default build.
At that time it is merged with the branch of the file the default build has.
Only when the next build is made will the file be put back onto the trunk.
.LE
