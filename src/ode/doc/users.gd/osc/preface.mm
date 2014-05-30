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
.\" Revision 1.2.2.2  1992/12/03  19:13:27  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:52  damon]
.\"
.\" Revision 1.2  1991/12/05  20:58:01  devrcs
.\" 	Separating DUG into common and OSC versions
.\" 	[91/01/16  17:03:42  randyb]
.\" 
.\" $EndLog$
.\" 
...\"*********************************************************************
...\"       Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBPreface\s0\fR'"	\"*** Set even page footers
.OH "'\fB\s10Preface\fR''\\\\nP\s0'"	\"*** Set odd page footers
.nr P 1					\"*** Start with page two
.af P i					\"*** Use 'i' as format
.SK
...\"*********************************************************************
...\"       Preface for OSC DUG
...\"*********************************************************************
.HU "Preface"
.P
The
...\"#doctitle
.I "OSF Development User's Guide (DUG)"
explains the concepts and processes behind the OSF Development Environment
(ODE) and its methodologies
and how to use the tools to control source, compilation, and release.
This document discusses the Operating System Component (OSC) specific
portions of ODE;
there is also a common DUG which discusses the development environment
in general, as well as other supplemental-DUG's which give specific information
for other projects.
.HU "Audience"
This document is written for developers and release engineers using the
ODE tools. 
.HU "Applicability"
.P
This is Version 1.0 of this document.
It is accurate to the changes made in ODE as of February 1, 1991.
.HU "Purpose"
The purpose of this document is to provide a guide
to the new and experienced developer using the OSF development
process and tools.
It is also intended to provide an introduction
to the concepts behind those processes and tools.
.HU "Typographic and Keying Conventions"
.P
This document uses the following typographic conventions: 
.VL 1.25i
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
.VL 1.25i
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
If you have any problems with the software or documentation,
please contact a member of the Release Engineering and Distribution group.
.SK
.HU "Introduction"
This document is part of a collection of documents which describe the
OSF Development Environment (ODE).
Other documents include the ODE System Administration Guide; the common
Development User's Guide (DUG) which describes the shared portions of the
development environment, tools, and processes which apply to any project
using ODE; as well as other supplemental-DUGs which give specific
information for particular projects.
Other the supplemental-DUGs include the \fBDCE\fR and \fBMotif\fR DUGs.
.P
This document contains OSC specific information on using ODE
tools and processes.
For OSC developers, since the OSC project uses all of ODE's capabilities,
the best way to learn how development is done in the OSC is to introduce
one's self to ODE as explained in the common-DUG.
The introduction in that document suggest a good way to get started.
.P
Once the developer has a general understanding of ODE, she can return
to this document for specific details and examples.
.P
This document is organized into the same five chapters as the common DUG:
Sandboxes, Source Management, Compilation, Submitting Files,
and Installation.
There are no additional chapters specific to the OSC project;
there are, however, areas within some chapters such as the discussion of
building the kernel in the compilation chapter, which do not have counter
parts in the common DUG.
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

.H 2 "Introduction to ODE for Project OSC"
At OSF the OSC uses ODE in its complete form including sandboxes,
source control, building, and installation.
For this reason, almost all of the material in the common DUG applies
to the OSC project.
What users will find in this document are OSC specific details and
examples which extend the information in the common DUG.
While some chapters contain considerable extensions, other have
no additional information at all.
.P
Chapter three on the compilation environment, for example, covers
build-specific arguments, the gcc compiler, building the kernel,
and OSC specific compilation issues and is fairly large.
Similarly, the bulk of information on installations and updates, chapter five,
is in this document as it, too, is OSC specific.
.P
On the other hand, chapters two and four contain no additional
information as the common DUG completely covers source control for the OSC.
Somewhere in the middle, chapter one gets most of its information
from the common DUG but there are OSC specifics the user should be
aware of.
.P
The following terms are defined in the common DUG but are placed here
for the reader's convenience.
.VL 15
.LI \fBbuild\fR
(the tool)
a tool for compiling objects and binaries, supersedes "make" in most cases.
.LI \fBbuilds\fR
complete sets of sources, objects, and binaries which have been "built"
and put in one place.
.LI "\fBdefault build\fR"
For each project there is a default build which contains the newest
revisions of submitted sources.
In examples, that build is referred to as \fBlatest\fR;
but the actual names at OSF for OSC are: \fBosc1.0\fR, \fBosc1.1\fR,
and, in the case of submitting to a shared sandbox, \fBosc1.0.1s\fR.
.LI \fBproject\fR
a set of sources which have been grouped together and are treated as
a unit.
Projects can be as large as the OS and as small or smaller than ODE itself.
Each project has separate builds and a separate default build from all
other projects.
.LI \fBsandbox\fR
a private working area which a developer own and controls.
.LI \fBbcs\fR
a group of revision control programs which operate on top of rcs.
.LI \fBset\fR
a grouping of sources within a sandbox which can be manipulated as a
whole using the bcs commands.
The naming conventions for sets is lower case for private sets and
upper case for build and shared sets (see shared set, below).
Private sets get the name of the user as a prefix, so a set named
"melody" becomes "suzieq_melody".
.LI "\fBbacking trees\fR"
any build, including the default build,
or any sandbox which "backs" another sandbox;
i.e. if the other sandbox does not have a file locally,
ODE searches the backing tree, the build or sandbox, for the file.
Backing trees can themselves be backed.
.LI "\fBchild sandbox\fR"
how the backing tree views the sandboxes which uses it as a backing tree.
For example, if sandbox symphony is backed by build latest,
then latest has symphony as one of its child sandboxes.
.LI "\fBshared sandbox\fR"
a sandbox which backs another sandbox.
.LI "\fBshared set\fR"
a set which multiple developer's check-out from and submit to.
The default builds have a shared set, usually named the same as the
build but using capital letters.
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
