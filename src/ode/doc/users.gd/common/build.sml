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
.\" $Log: build.sml,v $
.\" Revision 1.3.4.1  1993/11/18  21:39:24  marty
.\" 	CR # 629 - Updates
.\" 	[1993/11/18  21:39:02  marty]
.\"
.\" Revision 1.3.2.2  1992/12/03  19:10:41  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:30  damon]
.\" 
.\" Revision 1.3  1991/12/17  20:59:54  devrcs
.\" 	Changed building environment to build environment...
.\" 	[1991/12/12  21:37:48  mckeen]
.\" 
.\" 	Fixed up page numbering
.\" 	[1991/12/11  21:33:08  mckeen]
.\" 
.\" 	Another rewrite
.\" 	[1991/12/09  20:57:29  marty]
.\" 
.\" 	Reorganize
.\" 	[1991/11/20  01:17:02  marty]
.\" 
.\" 	Source for "Building Software" chapter of DUG
.\" 	[1991/11/08  22:30:31  alan]
.\" 
.\" 	Null delta
.\" 	[91/08/05  13:31:46  marty]
.\" 
.\" 	Rewrite, ready for review.
.\" 	[91/08/02  11:41:08  marty]
.\" 
.\" 	preliminary edit/rewrite
.\" 	[91/06/18  13:27:49  casey]
.\" 
.\" 	Separated DUG into common DUG and OSC Supplemental
.\" 	[91/01/25  10:34:26  randyb]
.\" 
.\" Revision 1.5  90/11/03  10:27:19  devrcs
.\" 	Pre Tools II release
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Reset page information for chapters in DUG
...\"*********************************************************************
.OH "'\fB\s10ODE User\'s Guide\fR''\\\\nP\s0'"	\"*** Set even page footers
.EH "'\s10\\\\nP''\fBBuild Environment\s0\fR'" \"*** Set odd page footers
.SK
...\"*********************************************************************
...\"          Contents of common DUG: Build Environment
...\"*********************************************************************
.H 1 "Build Environment"

This chapter covers the principles for building within an ODE sandbox.
This includes ODEs use of \fBmake\fR, the organization of
\fBmakefiles\fR, how \fBmake\fR uses sandboxes and backing chains, the
ability for one to tailor a build environment, and building through
\fBpasses\fR.
.P
ODE uses \fBmake\fR for building.  Backing chains and sandboxes
support the building model found on most Unix systems; building a set
of source files using a makefile and \fBmake\fR.
.P
The following are fundamental elements of building in ODE:
.BL
.LI
\fBbuild\fP and \fBmake\fP are used for all building. 
.LI
\fBbuild\fR and \fBmake\fR
derive much of their information from environment variables
defined in sandboxes and backing chains. Change  these variables
to customize the  build environment.
.LI
Sources and built objects are maintained in separate directories.
.LI
Frequently used build rules are collected into common makefiles.
.LI
Each component makefile includes the common makefiles.  When
building, definitions of variables within the makefile
are used to trigger the 
execution of rules in the common makefiles.
.LE

.H 2 "build: a Front-end to make"
.iX "build"
.iX "make"
The primary command for building software in ODE is \fBbuild\fP.  It
serves the same function as the command \fBmake\fP does in a standard
UNIX development environment.  In fact, \fBbuild\fP is actually a
front-end to \fBmake\fP.  The difference between \fBbuild\fR and
\fBmake\fR is that \fBbuild\fR can operate outside the scope of a
sandbox.  \fBmake\fR requires one to \fBworkon\fR into a sandbox
before building.
.P
The options for \fBbuild\fR and \fBmake\fR are mutually exclusive and 
any options that \fBbuild\fR does not recognize are passed on to \fBmake\fR.
.P

To see how \fBbuild\fR works;
if you want to create the binary
wakeup from wakeup.c in the directory

.ti 2
/sandboxes/suzieq/symphony/src/ode/tutorial/wakeup

Then type

.ti 2
\fBbuild wakeup\fP

.P
\fBbuild\fR first searches the \fBsrc\fR tree in the sandbox then the \fBsrc\fR tree in the backing chain for the source.
Once the source is found, \fBbuild\fR provides 
the compiler with 
a search list for libraries and header files.  Libraries and header files are
searched first in the \fBexport\fR directory of the sandbox then in the 
\fBexport\fR directory of the backing chain.

The search list passed to the compiler for header files
is similar to:
.in +2
.nf
.ft B   \" default font is bold
\f(CW-I../../../myinclude -I/sandboxes/suzieq/symphony/src/myinclude
-I/project/build/proj2.0b1/src/myinclude\fP
.ft R   \" Return default font to Roman
.fi
.in -2


The search list passed to the compiler for libraries 
is similar to:
.in +2
.nf
.ft B   \" default font is bold
\f(CW-L/sandboxes/suzieq/symphony/export/pmax/usr/shlib
-L/project/build/proj2.0b1/export/pmax/usr/shlib\fP
.ft R   \" Return default font to Roman
.fi
.in -2

.P
You will not find the built objects in the same directory as the sources.
All objects are built in the \fBobj\fR directory.

.H 3 "Exporting"

Components of a system that are used to build other components are placed in
the \fBexport\fR directory. 
.P
In most large software projects, many of the header files and libraries 
needed to build
the system are often part of the project itself.  While developing the system;
libraries are also being developed.  These libraries require development and
testing before becoming stable enough to be used by the rest of the system.
ODE stages the development and availability of these libraries by 
using the \fBexport\fR
directory in the sandbox.  A library that is under development 
is not available to
the rest of the system until a developer places  it into the 
\fBexport\fR directory.
The processing of placing anything in this directory is called \fBexporting\fR.

In addition to libraries, it is convenient to group header 
files into the \fBexport\fR
directory to cut down on the number of search paths passed to the compiler. 

.H 3 "Walkthrough of \fBbuild\fP Execution"

The following is a walkthrough of how \fBbuild\fP would compile the program
helloworld.  All references to command execution will be from the directory
\fBode/tutorial/helloworld\fR in a sandbox which contain the files 
\fBMakefile\fR and \fBhelloworld.c\fR.  The sandbox is backed by a full backing build.
.P
The contents of the files \fBMakefile\fR and \fBhelloworld.c\fR are:
.P

.in +2
.nf
.ft B	\" default font is bold
\f(CWPROGRAMS                = helloworld

ILIST                   = helloworld 
IDIR                    = /tmp/

\&.include <${RULES_MK}>\fP
.ft R	\" Return default font to Roman
.fi
.in -2

and

.in +2
.nf
.ft B   \" default font is bold
\f(CW#include <stdio.h>

main() {

printf ("Hello world\\n");

}

.ft R   \" Return default font to Roman
.fi
.in -2


Running \fBbuild\fR illustrates
the way the tools search for source, header files, and
libraries.

.in +2
.nf
.ft B	\" default font is bold
\f(CW% \fPbuild
\f(CWrelative path: ./ode/tutorial/helloworld.
mkdir ../../../../obj/pmax/ode/tutorial/helloworld
cd ../../../../obj/pmax/ode/tutorial/helloworld
.ne 10
gcc -B -gline -c  -Dmips -D__mips__ -D_SHARED_LIBRARIES -O     \\
-nostdinc -I. -I/\fIsandbox\f(CW/src/ode/tutorial/helloworld \\
-I/\fIbacking-tree\f(CW\f(CW/src/ode/tutorial/helloworld -I-  \\
-I/\fIsandbox\f(CW/export/pmax/usr/include \\
-I/\fIbacking-tree\f(CW/export/pmax/usr/include -pic-lib   \\
-L/\fIsandbox\f(CW/export/pmax/usr/shlib \\
-L/\fIbacking-tree\f(CW/export/pmax/usr/shlib \\
-L/\fIsandbox\f(CW/export/pmax/usr/ccs/lib \\
-L/\fIbacking-tree\f(CW/export/pmax/usr/ccs/lib     \\
 \f(CW../../../../../src/ode/tutorial/helloworld/helloworld.c
.ne 5
gcc -B -gline -%ld," -warn_nopic -glue"         \\
-L/\fIsandbox\f(CW/export/pmax/usr/shlib \\
-L/\fIbacking-tree\f(CW/export/pmax/usr/shlib \\
-L/\fIsandbox\f(CW/export/pmax/usr/ccs/lib \\
-L/\fIbacking-tree\f(CW/export/pmax/usr/ccs/lib -o helloworld.X helloworld.o    
mv helloworld.X helloworld\fP
.ft R	\" Return default font to Roman
.fi
.in -2

.P
Note that relative to the current directory in the sandbox, the objects
were built in \f(CW../../../../obj/pmax/ode/tutorial/helloworld\fR.

So, the command that \fBbuild\fP runs for compiling and linking 
\fBhelloworld\fP consists of:
.BL
.LI
The compiler (\fBgcc\fP in our example).
.LI
A series of default compiler options
.br
\f(CW-B -gline -c -Dmips -D__mips__ -D_SHARED_LIBRARIES -O -nostdinc\fP
.LI
Compiler options to search for include files
.br
\f(CW-I. -I/\fIsandbox\f(CW/src/ode/tutorial/helloworld \\
.br
-I/\fIbacking-tree\f(CW/src/ode/tutorial/helloworld\fR  
.LI
Standard include files 
.br
\f(CW -I-  -I/\fIsandbox\f(CW/export/pmax/usr/include \\
.br
-I/\fIbacking-tree\f(CW/export/pmax/usr/include\fR
.LI
A standard linker option (\f(CW-pic-lib\fR).
.LI
Linker options to search for library files
.br
\f(CW-L/\fIsandbox\f(CW/export/pmax/usr/shlib \\
.br
-L/\fIbacking-tree\f(CW/export/pmax/usr/shlib \\
.br
-L/\fIsandbox\f(CW/export/pmax/usr/ccs/lib \\
.br
-L/\fIbacking-tree\f(CW/export/pmax/usr/ccs/lib\fR
.LI
The source file to be compiled (relative to the \fBobj\fR
directory) \f(CW../../../../../src/ode/tutorial/helloworld/helloworld.c\fR
.br
Had the source not been found in the sandbox, each \fBsrc\fR tree
in the backing chain would be searched.
.LE

.ft R	\" Return default font to Roman
.fi
.in -2 
.H 2 "Building with Passes" 
.P
Most large systems require that its components follow some sort of
ordering when being built.  Components of the system that are
used to build other components of the system must, of course, 
be built before they can be used.
.P
In most large software projects the best example of this
is  libraries.  If there are components of a software system
that require the use of one of its libraries then the library must be
built first.  By the same token, if the system requires header files
to be exported then they must be exported before the system is built.
.P
For software projects, ODE supports ordering builds into the 
following functions:
.BL
.LI
setting up header files in the \fBexport\fR directory
.LI
building libraries and placing them in the \fBexport\fR directory
.LI
building software components that use these headers and libraries
.LI
installing the built software for testing
.LI
removing unneeded objects and executables from the \fBobj\fR directory
.LE
.P
Each step in the build order is called a \fIpass\fR.  Each  pass
is applied to the \fBsrc\fR tree in succession.  The scope within 
the \fBsrc\fR tree varies from pass to pass, but each pass is must be
completed before the next pass begins.
.P
The passes that are supported in ODE are: 
.BL
.LI
\fIexport\fP \ puts any target which can be exported into the export area
.LI
\fIcomp\fP \ does just the compilation step without doing \fIexport\fP.
.LI
\fIbuild\fP \ does \fIexport\fP and \fIcomp\fP.
.LI
\fIinstall\fP \ puts files in the directories they will be in
on an installed system.
.LI
\fIclean\fP \ removes object (.o) files.
.LI
\fIrmtarget\fP \ removes the target (usually a program).
.LI
\fIclobber\fP \ does a \fIclean\fP and a \fIrmtarget\fP.
.LI
\fIlint\fP \ runs lint on the sources.
.LI
\fItags\fP \ creates a tags file.
.LE
.P
During each pass the \fBsrc\fR tree is traversed.  Each makefile
in the \fBsrc\fR tree directs an 
operation to be performed by the pass being done on the target supplied to
the \fBbuild\fR command.  
The pass indicates the operation to be done while the 
target indicates the component on which to perform the pass.
Many targets may be listed in the makefile
with each one applicable to one or more passes.

The syntax for specifying a pass to \fBbuild\fR is:

.in +2
.nf
.ft B	\" default to bold
pass
pass_\fItarget\fP
pass_all
pass_all_tag
.ft R	\" revert to regular font
.fi
.in -2

where the terms are defined as:
.in +2
.BL
.LI \fBpass\fP
The pass to be done.
(\fBexport\fR, \fBcomp\fR, \fBclean\fR, \fBinstall\fR, etc.)
If a pass is not specified, the  default will be the \fIbuild\fP pass.
.LI \fItarget\fP
The target to perform the pass on.
Whenever the target is left out, the default target \fBall\fR is used.
.LI \fBall\fP
A special word which tells \fBmake\fP to perform the action
on all targets listed in the \fBMakefile\fP.
.LI \fBtag\fP
The target to apply the pass to.
The legal tags match the tags a project has setup for \fBSUBDIRS\fP.
.LE
.in -2

Therefore, to run \fBlint\fP on the program \fBhelloworld\fP, the command is:

.ti 2
\fBbuild lint_helloworld.c\fP

\fBall\fR causes the pass specified to be applied to all 
targets in the makefile.

For example:
.ti 2
\fBbuild clean_all\fP

removes all objects for all targets listed in each makefile of the source tree.


\fBExample:\fP

If you want to export a file such as \fBstdio.h\fR then type 

.in +2
.nf
.ft B	\" default font is bold
\f(CW% \fPbuild export_stdio.h
\f(CW% \fP
.ft R	\" Return default font to Roman
.fi
.in -2

of course, \fBstdio.h\fR must be listed in the \fBMakefile\fR as 
a target for exporting.

If you want to export all header files then type

.in +2
.nf
.ft B	\" default font is bold
\f(CW% \fPbuild export_all
\f(CW% \fP
.ft R	\" Return default font to Roman
.fi
.in -2
.H 2 "ODE Makefiles"
.P
One significant difference between the standard UNIX development
environment and ODE is the use of common makefiles.
Common makefiles hold frequently used build rules in one place
so they don't have to be duplicated in each makefile in the \fBsrc\fR
tree.
.P
Makefiles for most systems are simple.
They include the common makefiles and define makefile
variables that trigger execution of common rules.
.P
Including the common makefiles requires 
the line \f(CW.include <${RULES_MK}>\fP in each 
makefile.  It is important that this line appear after all 
variable defines in the makefile.

.P
The pass, in conjunction 
with the variable definitions in the makefile,
defines which common rules are triggered.
Certain variables are used for certain passes.

The comp and build passes perform compilation 
and derive much of their information from these makefile variables.
.BL
.LI
.B PROGRAMS
- list of programs to compile and link.
.LI
.B OFILES
- list of objects that comprise a program or library.
.LI
.B HFILES
- list of header  files on which PROGRAMS and OFILES are dependent.
.LI
.B MSGHDIRS
- list of message source files to be processed by \fBmkcatdefs\fR 
for the OSF/1 Message Facility.
.LI
.B CATFILES
- list of message catalogs to create for the OSF/1 Message Facility.  
.LE
.P
The export pass builds and places libraries and header files
in an export area for subsequent building.
This pass derives much of its information from the following 
makefile variables.
.P
.BL
.LI
.B INCLUDES
- list of header files to export.
.LI
.B EXPDIR
- the relative directory within the export area.
.LI
.B EXPLINKS
- list of links  to export.
.LI
.B EXPINC_SUBDIRS
- list of subdirectories to traverse during export pass.
.LI
.B EXPLIB_TARGETS
- export a library.  Must be assigned a value with prefix \fBexport_\fR.
For example \fBexport_libsecurity.a\fR.
.LE
.P
The install  pass installs an executable or datafile into a release
area and sets access rights.  It derives much of its information
from the following makefile variables:
.P
.BL
.LI
.B ILIST
- list of executables or data files to install
.LI
.B IDIR
- the directory in which to install them.
.LI
.B IMODE
- permissions to set on installed executables.
.LI
.B IGROUP
- group to set on installed executables.
.LI
.B IOWNER
- owner to set on installed executables.
.LE

.H 3 "How Passes are implemented in Makefiles"

To specify which directories of the tree to process for each pass,
ODE uses the makefile variables \fBSUBDIRS\fP and
\fIpass_\fP\fBSUBDIRS\fP.

\fBSUBDIRS\fP is used by passes which visit every directory of the
\fBsrc\fP tree.
In each source directory, 
the makefile variable \fBSUBDIRS\fR  lists all subdirectories
to traverse.
.P
\fBMakefile\fP will also have a line setting
\fIpass_\fP\fBSUBDIRS\fP to the set of subdirectories which should be
processed for \fIpass\fR.
.P
During each pass, if \fBSUBDIRS\fP 
is defined, \fBmake\fP will process each of the
subdirectories listed.  This is how a pass is applied to 
an entire source tree.

Some variables used are:

.BL
.LI
\fBSUBDIRS\fP \ The list of sub-directories to to be searched.
.LI
\fBEXPINC\fP\fB_SUBDIRS\fP \ The list of sub-directories
which should be searched for include files to export.
.LI
\fBEXPLIB\fP\fB_SUBDIRS\fP \ The list of sub-directories
which should be searched for libraries to export.
.LE

These would appear in a makefile as follows:
.in +2
.nf
\f(CWSUBDIRS = bin ccs dict doc include lib local sbin
EXPINC_SUBDIRS = include
EXPLIB_SUBDIRS = lib
.fi
.in -2



.H 2 "Modifying the Build  Environment"

Since the ODE build environment revolves around environment and 
makefile variables, almost
all changes to it are made by changing variables.

Generally, where you change a variable will depend on:
.BL
.LI
How long you want it to be affected.
.in +2
.BL
.LI
If you want the change to last only as long as one run of \fBbuild\fP,
set the variable on the \fBbuild\fP command line.
.LI
If you want the change to last for the duration of this login session,
affecting all builds during that time, set the variable in the shell
environment.
.LI
If you want the change to last forever, put it in a \fBMakefile\fP or
in sandbox \fBrc_files\fP.
.LE
.in -2
.LI
What part of  the source tree you want to be affected. 
.in +2
.BL
.LI
Changes to components are made in the \fBMakefile\fRs and common makefiles.
.LE
.in -2
.LI
Whom you want the change to affect.
.in +2
.BL
.LI
If you want it to affect just you, set it in the \fBrc_files\fR in
your own sandbox.
.LI
If you want it to affect every build that is backed by the backing build,
set it in a \fBMakefile\fP or in the \fBrc_files\fP of the backing chain.
.LE
.in -2
.LE

Most of the commonly used variables in makefiles can be specified on a 
per-target basis
by prepending the name of the target and an underscore to the variable.
So 

.ti +2
\fBfoo_CARGS=-DMAKETAB\fP

applies \fB-DMAKETAB\fR to \fBfoo\fR and no other target.


.H 3 "Adding a Program Target"

To build a new program in a directory that already builds another program,
just edit the \fBMakefile\fP to add the new program name to the
\fBPROGRAMS\fP list.


To build a simple version of the \fByes\fP program from a new source file,
\fByes.c\fP in the \fBtc\fP
directory, edit \fBMakefile\fP, and change

.ti +2
\f(CWPROGRAMS                = tc\fP

to

.ti +2
\f(CWPROGRAMS                = tc yes\fP

When you run \fBbuild\fP, this will tell the common makefiles to build
both programs.


To build a simple version of the \fByes\fP program in a new
directory, create a \fBMakefile\fP with the line

.ti +2
\f(CWPROGRAMS                = yes\fP

and the line that include the common   makefiles.
When you run \fBbuild\fP, this will tell the common makefiles to build
the new program.


.H 3 "Location for Building Objects"

By default, all objects are built in the \fBobj\fR tree.
If you wish to build objects in another location, change the \fBOBJECTDIR\fP
variable in the \fBrc_files/local\fP file in your sandbox.
You may specify either a relative or absolute pathname.
If you specify a relative pathname, it must start from
the \fBsrc\fR directory.


A special case is that if you set

.ti +2
\fBOBJECTDIR = ""\fP

the objects will be put in the same directory as the sources.


.H 3 "Compiler Flags"

The flags passed to the compiler are taken from a list of variables
defined on either the command line, or in a makefile.
You can change what gets passed to the compiler by
overriding a  variable  defined in one  of these places.

For example, changing a compiler option from the command line:

.ti +2
\fBbuild "CARGS=-DTARGET"\fP

will add "-DTARGET" on the \fBcc\fP command line.

The following  variables allow different people to change this 
list.
.in +2
.BL
.LI \fBCARGS\fP  
Set by the developer on the \fBbuild\fP command line.
.LI \fBCENV\fP  
Set by the developer as shell environment variables.
.LI \fBCFLAGS\fP  
Set in \fBMakefile\fP by whoever edits it.
.LE
.in -2


.H 3 "Compiler Include Directories"

The \fBcc\fP compiler accepts a list of \fB-I\fP options, each with a
directory name.  The list of directories specified by   these options
is searched to find files in \fB#include\fP directives in the .c
source file.
The following  variables allow different people to change this 
list.

.in +2
.BL
.LI \fBINCARGS\fP
Set by the developer on the \fBbuild\fP command line.
.LI \fBINCENV\fP
Set by the developer as shell environment variables.
.LI \fBINCFLAGS\fP
Set in \fBMakefile\fP by whoever edits it.
.LI \fBINCDIRS\fP
Set in the \fBrc_files\fP by whoever edits them.
.LE
.in -2

\fBExample:\fP

.ti +2
\fBbuild "INCARGS=-I../../corona/flare -I../../corona/spots"\fP

will cause the directories ../../corona/flare and ../../corona/spots
(in the sandbox and the backing chain) to be searched for each
\fB#include\fP in the source files being built.


.H 3 "Build Tools"

Which language tools are used for a project is usually decided on a project
basis and set in the common makefiles by Release Engineering.
They can usually be overridden on the command line,
rc_files, or in the makefile by changing the variables that define them.

\fBExample:\fP

If you need to use a different linker than the rest of the project,
you can use 

.ti +2
\fBLD = gld\fP

The list of tools include:
\fBCC\fR,
\fBLD\fR,
\fBAR\fR,
and
\fBRANLIB\fR.


.H 3 "Linker Flags"

The flags passed to the linker are taken from a list of variables
defined on either the command line, in a makefile, or in a file in the
\fBrc_files\fR directory.
You can change what gets passed to the linker   by
overriding a  variable  defined in one  of these places.

For example, to add an option to the linker from the command line:

.ti +2
\fBbuild "LDARGS=-nostdlib"\fP

will place "-nostdlib" on the \fBld\fP command line.

The following  variables allow different people to change this
list.
.in +2
.BL
.LI \fBLDARGS\fP
Set by the developer on the \fBbuild\fP command line.
.LI \fBLDENV\fP
Set by the developer as shell environment variables.
.LI \fBLDFLAGS\fP
Set in \fBMakefile\fP by whoever edits it.
.LE
.in -2



.H 3 "Linker Library Directories

The linker accepts a list of \fB-L\fR options, each with
a directory name.  The list of directories extracted from these
options is searched for libraries during linking.

A set of variables has been defined to allow different people to set
the directory list in various places:

.BL
.LI \fBLIBARGS\fP
Set by the developer on the \fBbuild\fP command line.
.LI \fBLIBENV\fP
Set by the developer as shell environment variables.
.LI \fBLIBFLAGS\fP
Set in \fBMakefile\fP by whoever edits it.
.LI \fBLIBDIRS\fP
Set in the \fBrc_files\fP by whoever edits them.
.LE


\fBExample:\fP

.ti +2
\fBbuild "LIBARGS=-L../../export/pmax/usr/lib/corona/flare 
-L../../export/pmax/usr/lib/corona/spots"\fP
will cause these directories 
to be searched for each
library specified on the \fBld\fP command line.


.H 3 "Optimization and Debugging"

A separate environment variable, \fBOPT_LEVEL\fP, is provided for defining one of the
several debugging and optimization options
that can be used with both the compiler and linker.  

Because the \fB-g\fP option is used by both the \fBcc\fP compiler and
the \fBld\fP linker, \fBOPT_LEVEL\fP is passed to both.


\fBExamples:\fP

To build with debug on:

.ti +2
\fBOPT_LEVEL = -g\fP

To build with optimization:

.ti +2
\fBOPT_LEVEL = -O\fP

To build with neither debug nor optimization, set:

.ti +2
\fBOPT_LEVEL = ""\fP

To specify optimization for just the compiler use the variable 
\fBCC_OPT_LEVEL\fR. 
To specify optimization for just the linker use the variable 
\fBLD_OPT_LEVEL\fR. 

.H 3 "Installing a New Target in \fBMakefile\fP"

During the \fIinstall\fP pass, the common makefiles will
install any file listed in the \fBILIST\fP variable into the directory
specified by the IDIR variable.


\fBExample:\fP

Assume you have built the simple \fByes\fP program in the same directory
as the \fBtc\fP program (as described in the example for "Adding a New
Target"), and now want to install it.

.ne 7
Edit \fBMakefile\fP and change

.ti +2
\fBILIST                   = tc\fP

to

.ti +2
\fBILIST                   = tc yes\fP

and \fBbuild\fP will thereafter install the \fByes\fP program when it
installs the \fBtc\fP program.


\fBExample:\fP

Assume that you have built simple \fByes\fP program in its own
directory, and now want to install it.

Edit the makefile to add the line

.ti +2
\fBILIST                   = yes\fP

Henceforward, \fBbuild\fP will install the \fByes\fP program on
the \fIinstall\fP pass.  (Be sure that this directory is in the
\fBinstall_\fBSUBDIRS\fP list of the \fBMakefile\fP in the
directory above this one.)

.H 3 "Location to install Programs"

The variable \fBTOSTAGE\fR defines the base directory where all executables
are to be installed.  The pathname for executables after the install
pass will be \fB${TOSTAGE}/${IDIR}/\fIexecutable\fR.  \fBTOSTAGE\fR
can    be set as an environment variable or passed to \fBbuild\fR on
the command line.

As a side effect, objects cannot be rebuilt if \fBTOSTAGE\fR is set.
If, during the install pass, this variable is set and you find you
need to rebuild a command; you must unset this variable before
rebuilding.

.H 3 "Changing Variables in the Common Makefiles"

Every \fBMakefile\fP in the source tree includes the common makefiles
which contain the shared rules.  A significant advantage of having
common makefiles is the ability to make a change in one common
makefile and have it "seen" by every \fBMakefile\fP which uses those
rules.  For example, if a serious defect in the optimizer was found
which necessitated turning it off, changing the \fBOPT_LEVEL\fP
variable in the common makefiles to omit the \fB-O\fP option would
immediately turn optimization off for all compiles backed by that
backing build.  While particularly advantageous for Release
Engineering, which has to build the entire source tree, this feature
is also useful for developers.  By checking out one of the common
makefiles into their sandbox, a developer can change the build rules
for all their work with a single edit.

This is not meant to suggest that the first thing a developer should
do is modify all the common makefiles.  In fact, they are not usually
checked out at all, but are picked up from the backing build.  Nor are
developers the people who usually make permanent modifications to
these files.  Such changes are normally made by Release Engineering.
But there are times when the developer needs to temporarily modify
their entire working environment and the \fBrc_files\fP aren't
sufficient for the purpose.  That's when a local copy of a common
makefile comes in handy.

The syntax of the common makefiles is mostly that of the standard UNIX
\fBmake\fP command, but most of the lines are comprised of variables
so they can work with any type of input.
