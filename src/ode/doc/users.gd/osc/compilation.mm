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
.\" $Log: compilation.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:13:06  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:43  damon]
.\"
.\" Revision 1.2  1991/12/05  20:57:47  devrcs
.\" 	Kill multiple occurrence of Endlog, HISTORY, or copyright header
.\" 	[91/02/04  17:30:16  robert]
.\" 
.\" 	Separated DUG into common DUG and OSC Supplemental
.\" 	[91/01/25  08:04:42  randyb]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 3: Compilation Environment\s0\fR'"
.OH "'\fB\s10Chapter 3: Compilation Environment\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          Contents of OSC DUG: Compilation Environment
...\"*********************************************************************
.H 1 "Compilation Environment"
There is a significant amount of OSC specific information regarding the
compilation environment.
Still, the common DUG outlines the general procedures and methods used
by the OSC.
New users should read that chapter first and refer to this chapter for
OSC specifics.
This chapter has roughly the same sections as the common DUG to make
cross referencing easier.
.P
Besides the specific comments on the OSC compilation environment,
this chapter covers building kernels and contains the compilation
tutorial.

.H 2 "The Default Compilation Environment"
.H 3 "Build and Make"
.H 4 "The Compiler and Build"
Though any compiler can be used with the OSC, the common makefiles have
been setup to default to \fBgcc\fR.
If this is not the compiler of choice, the makefiles can be edited.
Another way of changing the compiler is to use one of the
four supported values for the variable \fBCCTYPE\fR.
The four are:
.VL 16
.LI \fBansi\fR
The default value of \fBCCTYPE\fR, this sets the compiler to \fBgcc\fR.
.LI \fBtraditional\fR
The compiler for non-ansi behavior which is implemented as
\fBgcc -traditional\fR.
.LI \fBwritable_strings\fR
The variation for compiling with string constants which are writable,
implemented as \fBgcc -fwriteable-strings\fR.
.LI \fBhost\fR
The compiler for programs which will run on the host machines,
implemented as \fBcc\fR.
.LE
.P
All the options except host set the default \fBCFLAGS\fR to
the same values as defined in standard.mk.
They also use the gcc flag \fB-nostdinc\fR which stops the compiler
from automatically looking in the directory it found the source
file in for the associated header files.
This is needed for the case when the user has a local revision of the
header file but not the .c file.
Without this option, the compiler would use the header file from the
same directory as the .c file, but, with backing trees, the local
revision of the header should always be used.
.P
To set a different compiler, the user sets the appropriate flags.
For example, if the user was creating an object file that needed
to be built on the host system with local header files, he might
set the following flags:
.P
.ti 2
myfile.o_CCTYPE = host
.ti 2
myfile.o_INCFLAGS = -I.
.ti 2
myfile_CCTYPE = host
.P
Since gcc uses the environment variable \fBGCC_EXEC_PREFIX\fR as the
directory to find gcc in as well as the other programs the compiler needs,
but different machines need different compilers, the GCC_EXEC_PREFIX
must be overridden.
To do this, ODE uses machine specific variables which the makefiles
process to create switches to pass to gcc.
The variables used to do this are:
.ti 2
MACHO_GCC_EXEC_PREFIX \ \ COFF_GCC_EXEC_PREFIX
.ti 2
A_OUT_GCC_EXEC_PREFIX.
.P
and are set in the build's shared rc file.
These values are set without the \fBreplace\fR keyword so the
developer can override them by setting them in her own environment.
The values for these variables are similar to:
.P
.ti 2
.B "/project/osc/build/osc#.#b#/tools/pmax/gcc/"
.P
\fBNote\fR the trailing slash.
To override the value, use, as an example:
.P
.ti 2
\fBsetenv \fItype\fB_GCC_EXEC_PREFIX /\fIbuild\fB/tools/pmax/gcc/\fR
.P
Verifying actual pathnames for the parts of the compiler that
are running is done with the option:
.P
.ti 2
.B "build  CARGS=-v"
.P
To run only the gnu-preprocessor, use the .pp extension:
.P
.ti 2
.B "build  foo.pp"
.H 4 "Exporting"
Regarding export directories, the OSC uses
\fBexport\fI/machine\fB/usr/include\fR for headers and
\fBexport\fI/machine\fB/usr/ccs/lib\fR for libraries.
All libraries are placed in the latter while headers are either
directly under /usr/include or in /usr/include/\fIsub-dir\fR.
The export step also builds and exports the loader and shared libraries
in the default OSC environment.
.H 4 "Build Examples"
OSC specific examples of building follow:
.P
.B Situation:
.SP 0
wakeup is a single .c file which produces a binary found under /usr/bin,
but when looking under usr/bin in the src directory, there is a wakeup
directory but no .c file.
.P
.B Resolution:
.SP 0
All programs, even those compromised of a single source file,
are under individual directories in the OSC.
Therefore the source for wakeup will be under the directory /usr/bin/wakeup
and not just /usr/bin. 
.P
.B Situation:
.SP 0
wakeup is a directory with machine-dependent sub-directories
holding the actual source files.
The directory wakeup contains, for example,
.P
.ti 2
/project/osc/build/osc1.1b5/src/usr/bin/wakeup/PMAX/wakeup.c
.P
.B Resolution:
.SP 0
workon creates a set without referencing the
machine-dependent sub-directories; in this case:
.P
.ti 2
/sandboxes/suzieq/symphony/movement/src/usr/bin/wakeup
.P
without ./PMAX.
The bcs tools will need to be instructed to checkout machine-specific
sources, as in:
.P
.ti 2
.B "bco PMAX/wakeup.c"
.P
When ready to compile,
there are two possibilities.
The first assumes that PMAX/wakeup.c is not a new file,
and therefore is already referenced in the Makefile as machine-dependent.
In this case, the user can type build in the normal fashion.
.P
In the second case, where PMAX/wakeup.c is not already in the
Makefile as being machine-dependent,
the user will need to check out the Makefile and add the 
following line to it:
.P
.ti 2
.B "VPATH = ${TARGET_MACHINE}"
.P
VPATH is a 
.B make
directive which tells it to search in the following directory as
well as in the current one.
TARGET_MACHINE is set in each build's \fBrc_file/shared\fR rc file
so it can be overridden locally.
Since the TARGET_MACHINE for examples in this document is "PMAX",
.B make
would search in both the current directory and in ./PMAX
for the files it needs.
.P
If the rules for creating the machine-dependent binary are complex
the developer may also need to include the line:
.P
.ti 2
.B "-include ${TARGET_MACHINE}/machdep.mk"
.P
and then create another makefile called "machdep.mk" in the
machine-dependent directory which contains all the machine
dependent rules.
The machdep.mk include line must appear before the standard.mk
include line.
.P
.B Question:
.SP 0
What compiler and loader are being used to build wakeup?
.P
.B Resolution:
.SP 0
The compiler and the rest of the build tools are found through
the variable $PATH which should be set to look first in the 
backing tree's directory: ./tools/<target_machine>/bin.
The exceptions to this are when a cover program looks in specific
places for the tools it needs.
gcc looks, for example, where the variable GCC_EXEC_PREFIX indicates.

.H 2 "Building With Passes"
All of the pass operations used in the OSC require a single
pass except for building which requires six passes.
Single pass operations include those mentioned in the common DUG.
The build pass is comprised of six passes, five for exporting and one for
the remainder of compilation.
Each of the following five exporting passes both builds and exports
the associate targets:
.AL
.LI
include files
.LI
libc, crt0.o, and libld (static)
.LI
the loader
.LI
shared libraries
.LI
static libraries
.LE
.P
Building the remainder of OSC is done in the sixth pass.
.P
An example of a pass in the OSC which calls multiple targets
is the second export pass which exports both the library targets
and the crt0 target.

.H 3 "Descending the Tree"
These are three of the special SUBDIRS which have been
created for exporting within the OSC:
.VL 20
.LI \fBEXPINC_SUBDIRS\fR
The list of sub-directories which should be searched for include
files to export.
.LI \fBEXPLIB_SUBDIRS\fR
The list of sub-directories which should be searched for libraries to export.
.LI \fBEXPCRT0_SUBDIRS\fR
The list of sub-directories which should be searched for crt0 to export.
.LE
.P
Additional variables for other export passes are found in the common
makefile \fBpasses.mk\fR and include passes for the loader, shared
libraries, and security.

.H 3 "Processing the Leaves"
The variables the user should be aware of for exporting and installing 
in the OSC project include:
.VL 20
.LI \fBEXPINC_TARGETS\fR
The list of include files to export.
These files are listed in the form \fBexport_\fIfile\fR.
.LI \fBINCLUDES\fR
The list of include files to export if EXPINC_TARGETS is not set.
The prefix, \fBexport_\fR will automatically be added to each file
in the list.
.LI \fBEXPLIB_TARGETS\fR
The list of libraries to export.
These libraries are listed in the form \fBexport_\fIlibrary\fR.
.LI \fBILIST\fR
The list of files to install.
.LI \fIpass\fB_TARGETS\fR
The general form of the variables which list files for a pass,
for example, EXPINC_TARGETS.
.LI \fIfile_\fBEXPDIR\fR
The path to export a particular file into.
The path will be taken relative to the rc file variable \fBEXPORTBASE\fR
which is usually set to \fI/sandbox\fB/export/\fImachine\fR.
Defining an EXPDIR for a particular file overrides the general
definition of EXPDIR.
.LI \fBEXPDIR\fR
The path to export files into
if \fIfile\fR_EXPDIR is not set for a particular file.
The path will be taken relative to the rc file variable \fBEXPORTBASE\fR
which is usually set to \fI/sandbox\fB/export/\fImachine\fR.
.LI \fIfile_\fBIDIR\fR
The path to install a particular file into.
The path will be taken relative to the variable TOSTAGE which
the user must set.
This variable is usually set to  \fI/sandbox\fB/install/\fImachine\fR.
Defining an IDIR for a particular file overrides the general
definition of IDIR.
If \fBEXPDIR\fR is not set, this variable is checked for the place
to export as well as install.
.LI \fBIDIR\fR
The path to install files into
if \fIfile\fR_IDIR is not set for a particular file.
The path will be taken relative to the variable TOSTAGE which
the user must set.
This variable is usually set to  \fI/sandbox\fB/install/\fImachine\fR.
If \fBEXPDIR\fR and file_IDIR are not set, this variable is checked
for the place to export as well as install.
.LE
.P
The pass which exports include files uses the variable \fBINCLUDES\fR
to determine the list of files to export.
It puts these files in the location specified by the variable
\fB$EXPORTBASE/$EXPDIR\fR or, if a file has been designated specifically,
such as \fB$EXPORTBASE/$\fIfile\fB_EXPDIR\fR, it puts them in that location.
The same principle applies to other types of exports such as libraries.

.H 3 "Calling a Pass"
Legal \fItag\fRs which apply to calling a pass in the OSC environment
include the following (these match the tags for SUBDIRS):
\fBEXPINC\fR, \fBEXPLIB\fR, and \fBEXPCRT0\fR.
.P
The following examples explain the results of calling build with different
arguments in the OSC environment.
.VL 26
.LI "\fBbuild build_all\fR
run the first three passes: exporting headers, exporting libraries and crt0,
finishing all the compilation.
.LI "\fBbuild\fR
short for "build build_all"
.LI "\fBbuild all\fR
short for "build build_all"
.LI "\fBbuild \fIfile\fR
short for "build build_\fIfile\fR"
\fBNOTE\fR: whereas "build_all" goes through all the passes,
"build_\fIfile\fR" only invokes the compilation pass.
.LI "\fBbuild comp_all\fR
invokes only the compilation pass on all files.
.LI "\fBbuild export_all\fR
calls all export passes.
.LI "\fBbuild export_all_EXPINC\fR
calls the pass which builds and exports the include files.
.LI "\fBbuild export_all_EXPLIB\fR
calls the pass which builds and exports the libraries.
\fBNOTE\fR: in the current model, this pass will also export crt0.
.LI "\fBbuild export_\fIfile\fR
builds and exports the file \fIfile\fR.
.LI "\fBbuild install_all\fR
calls all installation passes.
At this time installation is a single pass process.
.LI "\fBbuild install_\fIfile\fR
installs the file \fIfile\fR.
.LE

.H 2 "Builds as Backing Trees"
The actual OSC builds are kept on various systems at OSF
but need to be accessed on the user's system from the directory:
.P
.ti 2
.B /project/osc/build
.P
Build names are of the form oscR.RbN where 'R' is the revision number
and 'N' is the number of the build.
The default build, which also must be accessed from /project/osc/build,
was previously called \fBlatest\fR, however, since there may be
more than one default build, they are now called oscR.R without the build
suffix.

.H 3 "Build's Directory Structure"
.B "src"
.P
The source used to create the OSC is all located under \fBsrc\fR.
src is a pseudo root with directories like \fBsbin\fR and \fBusr\fR
directly under it.
Most source will be found under this tree in the same directory
the binaries are found in on an OSF system plus a directory with
its own name, for example, the source for \fBls\fR is found in
\fBsrc/usr/bin/ls/ls.c\fR and the binary in \fB/usr/bin/ls\fR.
.P
In a few instances, it is necessary to look deeper to find sources.
In the case of \fB/sbin/cfgmgr\fR, for example, one of the source files,
\fBcm_method_defs.c\fR has machine dependencies and is under the
directory \fB/sbin/cfgmgr/\fIMACHINE\fR, where \fIMACHINE\fR has
values such as MMAX and PMAX.
Also found under these machine-dependent directories are machine-dependent
portions of the Makefile which are always called \fBmachdep.mk\fR.
The non-machine-dependent Makefile gets the machine-dependent Makefile's
information by including it with the line:
.P
.ti
\fBinclude ${TARGET_MACHINE}/machdep.mk\fR
.P
In the case of multiple sources and machine-dependencies,
the sources have both a directory of their own
and machine-dependent sub-directories.
The fourth case, one source with machine-dependencies,
is not very common, as almost any source which has machine-dependencies
is complex enough to need a different Makefile for each machine.
This means there are two files associated with each machine,
the source and the Makefile, and therefore puts this source
into the third category.
.P
There is one important case where there is a single source
with machine-dependencies: the header files.
Each header file with machine-dependencies is under a machine-dependent
directory, not a directory with its own name.
For example, the user might expect that 
.B math.h
would be found in a structure like:
.S -2
.DS I
.ft CW
               usr/include
                   |
                 math
                   |
          -------------------
          |        |        |
         MMAX     PMAX     VAX
          |        |        |
         math.h  math.h  math.h
.DE
.S P
But, since it is a single source with machine-dependencies,
the structure is actually:
.S -2
.DS I
.ft CW
               usr/include
                   |
          -------------------
          |        |        |
         MMAX     PMAX     VAX
          |        |        |
         math.h  math.h  math.h
.DE
.S P
All machine-specific header files are found under the same
machine-specific directory.
.P
Under any of these various conditions,
the location of each file, including its sub-directories,
will match the path listed in the build's SNAPSHOT file.
.P
.B "obj"
.P
Most binaries are under the same directory they would be under on a running
system except they are one additional level down.
For example, \fBls\fR is found in obj/\fImachine\fB/usr/bin/ls/ls\fR
while it would be in \fB/usr/bin/ls\fR on a running system.
.P
The kernel is located under \fBobj/\fImachine\fB/kernel\fR
which contains, amongst other items, the object files, the header files, and 
.B vmunix.
.P
.B "export"
.P
As noted earlier in this document, OSC export headers are located under the
sub-directory \fI<machine>\fB/usr/include\fR
and libraries under \fI<machine>\fB/usr/ccs/lib\fR.
.P
.B "tools"
.P
The tools directory, which is normally part of a developer's $PATH,
holds machine-dependent, ODE programs which are specific to that build.
Normally, ODE programs are mounted from a server (see chapter
1), but, in the case of a special version of a tool,
it will need to take precedence over the normal ODE tools.
For this reason, the build's tools directory should be in the developer's
PATH before the standard ODE tools.

.H 2 "Modifying the Build Environment"
.H 3 "Modifying Sandbox rc Files"
.H 4 "Include Files (Headers)"
The placement of headers in the export area for the OSC project is the
same as described in the common DUG,
and the default value of \fBINCDIRS\fR is the also the same as in that
document:
.sp
.ti 2
\fBsetenv INCDIRS "-I${export_base}/usr/include ${INCDIRS}"\fR
.H 4 "Libraries"
Unlike header files, libraries have a different placement in the OSC
from the one described in the common DUG.
The \fBlocal\fR sandbox rc file is the same:
.P
.ti 2
.B "setenv LIBDIRS ${LIBDIRS}"
.P
but the \fBshared\fR rc file is set to:
.P
.ti 2
\fBsetenv LIBDIRS "-L${export_base}/usr/ccs/lib ${LIBDIRS}"\fR
.P
and in the builds to:
.P
.ti 2
.B "setenv LIBDIRS -L${export_base}/usr/ccs/lib

.H 3 "Modifying Makefiles"
The Makefile template for OSC can be found in:
.P
.ti 2
\fI/build\fBsrc/usr/lib/makefiles/template.mk\fR
.H 3 "Modifying Common Makefiles"
The OSC common makefiles are also located under the directory:
.P
.ti 2
\fI/build\fBsrc/usr/lib/makefiles\fR.

.H 2 "Building a Kernel"
This section describes how to go about building an OSC kernel. 
It also describes how to configure a kernel with features and/or debugging
information.
.P
The commands used to build a kernel,
for example \fBbuild\fR/\fBmake\fR, \fBbci\fR, and \fBbco\fR,
are similar to the commands used to build any other software component.
However, the kernel is a bit unusual in that it is very large and
results in only one "program".
.P
The OSC kernel build procedure is necessarily different from the
vanilla kernel build procedures of other common UNIX implementations.
As a reference, the OSC
kernel build procedure is more similar to the BSD than the SYSV procedures.
.P
The build procedure itself is simple:
merely \fBcd\fR into the \fBsrc/kernel\fR directory and type \fBbuild\fR.
This builds a kernel in a sandbox.
.P
Once done, subsequent builds look for anything changed after the last
kernel build, recompile what they find, and relink the kernel.
However, the procedure for discovering what is out-of-date can take
quite a while, and so there are some short-cuts which are discussed
in the "Selected Topics" section.
.H 3 "The Kernel Layout"
There are several files that are important to the kernel build
procedure:
.VL 30
.LI \fBsrc/kernel/conf/files\fR
The \fBfiles\fR file contains a list of kernel source files and the
options they depend on.
The files listed therein are relative to
src/kernel and the options are listed in the \fBDEFAULT\fR file.
(See below.)
.P
This particular file is for the machine independent portions of the kernel.
.LI \fBsrc/kernel/conf/\fIMACHINE\fB/files\fR
This file is similar to the \fBsrc/kernel/conf/files\fR file except that it
contains the definitions specific to a particular machine.
The definitions in this file override those in the machine independent file.
.LI \fBsrc/kernel/conf/\fIMACHINE\fB/DEFAULT\fR
This is, of the most part, a standard Berkeley config input file as
described in the config(8) man page.
Developers change this file to change the configuration of the kernel.
.LE
.P
The developer can modify the above files as required to change the kernel
configuration.
.P
In addition to the configuration files, the OSC kernel
source area has a distinct directory structure:
.VL 30
.LI \fBsrc/kernel\fR
This is the root of the kernel source tree.
This is distinguished from the rest of OSC i.e. commands and libraries.
This directory contains the kernel Makefile,
the makefile that is used to build the kernel from scratch.
.LI \fBsrc/kernel/include\fR
This directory is unique to the OSC build environment because the
OBJECTDIR variable is used.
It is a directory that is populated with all the machine
dependent include files for a target configuration.
The directory is populated when the kernel is configured.
.LI \fBsrc/kernel/\fImachine\fR
Contains the kernel modules that are specific to a particular machine.
.LI \fBsrc/kernel/conf\fR
Contains the various files used in the kernel configuration phases of
the build procedure.
Of note is the \fBtemplate.mk\fR file which forms the
basis for the creation of the Makefile produced by the config program.
.LI \fBsrc/kernel/conf/syscalls.master\fR
A table listing the various system calls and their attributes. The
format of the table is documented in the file. This file is modified
when adding new system calls to any OSC implementations.
.LI \fBsrc/kernel/DEFAULT\fR
This directory is not distributed, however, a developer is likely to
create it and cd to it to issue a \fBbuild\fR or \fBmake\fR command in order to
rebuild the kernel without a complete reconfiguration.
Typically, this
directory is empty however the \fBobj/\fImachine\fB/kernel/DEFAULT\fR directory
is where most of the objects for the kernel are put.
.LE
.H 3 "Kernel Build Process"
There are two major variants of UNIX kernels: System V and BSD. The
System V variants are characterized by the constructing of libraries
and then linking these libraries to form a kernel.
The BSD variants are characterized by running a program (\fBconfig\fR)
that constructs a  makefile which, when run with \fBmake\fR, produces
a set of objects that are subsequently linked together.
.P
The OSC kernel is a variant on the BSD style of kernel building.
In OSC, a makefile is constructed using \fBconfig\fR, which is
subsequently run through \fBmake\fR to compile and link the kernel.
The major difference between OSC and BSD is the target machine nature of
the OSC kernel directory.
.H 4 "Steps to Build a Kernel"
A full kernel build goes through the following steps:
.AL
.LI
Populate the include files in the src/kernel/include directory tree.
.LI
Populate the include files in the src/kernel/include/mach directory
tree. This is done in the same machine-dependent manner as
src/kernel/include. 
.LI
Run the config program.
This program 'configures' the kernel by reading the \fBDEFAULT\fR
and \fBfiles\fR files and creating a makefile that describes the kernel
to be built.
The build process then invokes \fBmake\fR with this makefile to
build the actual kernel.
.P
It is this makefile that determines the configuration of the kernel.
Change this makefile and the kernel's configuration will change next
time it is built.
However, this makefile is generated by the config program.
If the makefile is changed and not the \fBDEFAULT\fR and \fBfile\fR files,
the changes will be lost the next time the kernel is completely rebuilt.
One of these two files must be changed to affect this generated file.
.LI
Construct the system call entry point file \fBconf/init_sysent.c\fR.
This file depends upon the kernel configuration, and thus
is built after the configuration is determined.
This file lists all the system calls.
available to user programs. 
.LI
Build the source files for the various kernel components
and link the kernel.
.LE
.P
After this procedure is finished, the new kernel can be booted and tested.
.H 3 "Kernel Build Tools"
The kernel build process uses a variety of tools.
The less obvious ones are discussed in the following subsections.
Others, such as \fBbuild\fR, \fBmake\fR, and \fBcc\fR are covered
in earlier sections of this chapter.
.H 4 config
The config program operates much like the BSD config(8) program, with
the only difference being the optional generation of header files in addition
to the normally generated .c files.
.P
The config program reads various 'parameter' files (of which \fBDEFAULT\fR
and \fBfiles\fR are but two), and creates a makefile, which is
used to build the kernel.
This tool allows for incremental and independent kernel modifications
by several developers.
.H 4 mig
The mig program is the MACH Interface Generator.
It takes as input a list of routine calls descriptions and generates a 
header or .c file with its C equivalents.
It is functionally equivalent but not syntax compatible with RPC.
.H 4 md
This program reads the \fBgcc\fR dependency output and
maintains an incremental list of dependencies.
The incremental list is kept in \fBobj/\fImachine\fB/kernel/DEFAULT/depend.mk\fR
and grows as dependencies are created.
.H 4 src/kernel/conf/makesyscalls.sh
This is a shell script that generates the \fBsrc/kernel/conf/init_sysent.c\fR
file.
It takes several command line options which are documented within the script.
They are not documented here because the script can change from build to build.
This section discusses issues that are frequently raised.
.H 3 "Changing a Kernel Configuration" 
There are two methods that can be used to change the kernel configuration.
The method chosen depends upon the desired results:
.AL
.LI
A permanent change is affected by modifying the
.P
.ti 6
\fBsrc/kernel/config/\fImachine\fB/DEFAULT\fR
.P
file.
This specifies the default configuration for all builds.
.LI
Less permanent changes can be made by creating a new copy of the \fBDEFAULT\fR
file.
Typically, this is achieved by copying the \fBDEFAULT\fR file to a
different name, making the desired changes to the copy, and then invoking:
.SP
.ti 2
\fBbuild KERNEL_CONFIG=\fIdefault-copy\fR
.LE
.H 3 "Building Under Same Configuration"
If the developer is concentrating on only a few files and wants to
rebuild just these portions of the kernel she changed, the
obvious method would be to use the \fBbuild\fR command.
However, there are times when the extensive checking this does is undesirable.
Instead, the developer can perform the following steps after configuring
the kernel:
.AL
.LI
Create a directory: \fBsrc/kernel/DEFAULT\fR.
This directory is not created by the tools.
.LI
Change to this subdirectory.
.LI
Enter \fBbuild \fItarget\fR relink
.LE
.P
This procedure causes a rebuild using the intermediate makefile from
the last kernel configuration, so, unless this intermediate makefile
has been modified, only the files that have changed will be built.
.P
This procedure will not work for developers using machine
specific subdirectories.
If their changes do not have the side-effect of changing their
kernel's configuration, they can modify this procedure to simply
cd to the 'src/build' subdirectory before issuing the build command.
.H 3 "Adding a New Machine Type"
There are several places where the machine type appears in the kernel
directory tree:
.P
.ti 2
\fBsrc/kernel/conf/\fITARGET_MACHINE\fR,
.ti 2
\fBsrc/kernel/mach/\fImachine\fR,
.ti 2
\fBsrc/kernel/mach_debug/\fImachine\fR, and
.ti 2
\fBsrc/kernel/\fImachine\fR.
.P
These directories contain files that are
required for a particular machine's implementation of OSC.
There is no overlap in functionality between the files in these
directories; they are all separate and are necessary when building
OSC for a particular machine.
.P
Of course, the files in these directories are machine specific.
Attempting to describe how they differ from other files
is beyond the scope of this document.
.H 3 "Turning on Debugging"
Every developer will be interested in a different set of debugging
information for the kernel.
For this reason, it is not feasible to have a debugging kernel
and a non-debugging kernel.
.P
However, there are 'debugging' configurations of the various kernel
components.
To get these into the kernel, make a copy of the
\fBsrc/kernel/config/DEFAULT\fR file and select the debugging versions
of the desired components. 
Rebuild the kernel using this configuration.

.H 2 "Tutorial: Compilation Environment"
This tutorial is a continuation of the tutorial in chapter 2.
Because of its OSC specific nature, it is in this document rather
that the common DUG.
The tutorial  assumes the user has already created a sandbox and is
working in the directory:
.P
.ti 2
\fI/sandbox\fB/usr/local/tutorial\fI/username\fR
.P
The user may practice building with any file(s) he wishes but a small
practice set is available.
This tutorial starts by explaining how to get that practice set.
.AL 1
.LI "Step" X
Build the practice program.
.P
.ti 6
.B "resb latest"
.ti 6
.B "cd /sandboxes/suzieq/symphony/usr/local/tutorial/form"
.ti 6
.B build
.P
If the directory does not exist, make it.
After entering \fBbuild\fR, the user will note that the program
builds even though there is nothing in the directory.
The output is something like:
.(O
[ /project/osc/build/latest/src ]
[ /sandboxes/suzieq/symphony/src ]
[ relative path ./usr/local/tutorial/form ]
mkdir ../../../../../obj/pmax/usr/local/tutorial/form
cd ../../../../../obj/pmax/usr/local/tutorial/form
gcc -B/project/osc/build/latest/tools/pmax/macho/ -gline -c -G 0
  -DBSD44 -DMSG -DNLS -DMACH -DCMU -DOSF -Dmips -D__mips__
  -D_SHARED_LIBRARIES -O -nostdinc `genpath -I.` -I- `genpath `
  -I/var/sandboxes/rad/export/pmax/usr/include
  -I/project/osc/build/latest/export/pmax/usr/include -pic-lib 
  `genpath   ` -L/var/sandboxes/rad/export/pmax/usr/shlib
   -L/project/osc/build/latest/export/pmax/usr/shlib
   -L/var/sandboxes/rad/export/pmax/usr/ccs/lib
   -L/project/osc/build/latest/export/pmax/usr/ccs/lib  -lsb
   ../../../../../../src/usr/local/tutorial/form/form.c
gcc -B/project/osc/build/latest/tools/pmax/macho/ -gline -%ld,
  "-warn_nopic -glue" `genpath ` -L/var/sandboxes/rad/export/pmax/usr/shlib
  -L/project/osc/build/latest/export/pmax/usr/shlib
  -L/var/sandboxes/rad/export/pmax/usr/ccs/lib
  -L/project/osc/build/latest/export/pmax/usr/ccs/lib -o form.X form.o
mv form.X form
.)O
.P
\fBbuild\fR first changes directory to the obj tree; if it does not
exist it creates it.
Next it builds the programs using \fBgenpath\fR to build the list
of directories to search for the header files and libraries.
\fBgenpath\fR is given the path "../../../../usr/local/tutorial/form"
in the Makefile.
.P
For this program there are two programs to build; program.c and ofile.c.
Since there are no copies of these programs locally nor a Makefile,
it will search for them in the backing tree.
To see the search path for sources, use \fBsbinfo\fR and read the entry
\fBSOURCEDIR.\fR
.LI "Step" X
Check-out the practice files.
.P
.ti 6
.B "bco -u -rLATEST program.c header.h Makefile ofile.c"
.P
This checks out an unlock copy of the correct revision of the practice files.
The user can now look at the Makefile and files which were compiled.
.LI "Step" X
Rebuild the command.
.P
.ti 6
.B build
.P
Note that from the user's point-of-view, exactly the same thing happens
when the files are local as happened when they were backed,
except the object directories did not have to be remade.
.LI "Step" X
Clean up these files as they will not be used.
.P
.ti 6
.B "build clobber_all"
.P
This will remove all the .o's and the binary itself.
\fBclean_all\fR would leave the executable.
.LI "Step" X
Create personal revisions of the files.
.P
.ti 6
\fBmkdir ../username\fR
.ti 6
\fBcp * ../\fIusername\fR
.ti 6
\fBcd ../\fIusername\fR
.ti 6
.B "bcreate *"
.P
For each file, \fBbcreate\fR will indicate that it is leaving the
existing file as it is but is creating a new rcs revision:
.(O
  [ ./usr/local/tutorial/suzieq/program.c ]
  [ creating ./usr/local/tutorial/suzieq/program.c,v ]
  ./usr/local/tutorial/suzieq/program.c,v  <--  ./rcstemp012638/program.c
  initial revision: 1.1
  done
  [ ./usr/local/tutorial/suzieq/program.c already exists, not modified ]
  [ working file set writable ]
  [ setting leader to ' * ' ]
  ./usr/local/tutorial/suzieq/program.c,v  <--  ./rcstemp012649/program.c
  new revision: 1.1.1.1; previous revision: 1.1
  done
  [ updating ./.BCSconfig ]
  > ./usr/local/tutorial/suzieq/program.c,v       1.1
  [ updating ./.BCSset-devsrc_movement ]
  > ./usr/local/tutorial/suzieq/program.c
.)O
.P
The user now has a local revision of each of the practice files
which can be modified as desired.
.LI "Step" X
Preview the \fBbuild\fR.
.P
.ti 6
.B "build -info"
.P
This option show all the variables set by \fBbuild\fR finishing
with the line \fBbuild\fR would use to call \fBmake\fR; something like:
.(O
string passed to /usr/local/osftools/bin/make: "make -cF build_all"
.)O
The \fB-info\fR option prevents \fBbuild\fR from actually doing anything.
.LI "Step" X
Preview \fBmake\fR.
.P
.ti 6
.B "build -n"
.P
The \fB-n\fR option is passed to \fBmake\fR which then outputs
the calls to \fBcc\fR it would run but does not actually do anything.
To preview both the \fBbuild\fR and \fBmake\fR output,
the options are \fBbuild -verbose -n\fR.
.LI "Step" X
Build the program with debugging turned on.
.P
.ti 6
.B "build OPT_LEVEL=-g program"
.P
The program could have been built without adding the word \fBprogram\fR;
it is just there for example.
The significant difference in the output is that the default build arguments
are:
.(O
cc -c -DBSD44 -DNLS -DMSG -D_BSD -DBSD_COM -D_NO_PROTO -O
.)O
while the addition of the \fBOPT_LEVEL\fR argument changes this to:
.(O
cc -c -DBSD44 -DNLS -DMSG -D_BSD -DBSD_COM -D_NO_PROTO -g
.)O
\fBOPT_LEVEL\fR will also make sure the linker receives the correct arguments.
.LI "Step" X
Attempt to build without the header file.
.P
.ti 6
.B "build clean_all"
.ti 6
.B "rm header.h"
.ti 6
.B build
.P
An error will be returned:
.(O
Make:  Don't know how to make header.h.  Stop.
.)O
This error is received because the make file has the line:
.P
.ti 6
.B "program.o: header.h"
.P
in it and therefore expects to find the header file locally.
To correct this error, edit the file and change the line and the one
below it to read:
.P
.ti 6
.B "program.o: ${MAKETOP}/usr/local/tutorial/form/header.h"
.ti 6
.B "ofile.o: ${MAKETOP}/usr/local/tutorial/form/header.h"
.P
The program will now build.
.LI "Step" X
Experiment with the common makefiles.
Edit the Makefile putting a comment in front of the last line:
.P
.ti 6
.B "# include ${MAKETOP}/usr/lib/makefiles/objects.mk"
.ti 6
.B "build clean_all"
.P
Note that the the .o files were not removed.
To see where this rule, as well as the other .o rules are determined,
check-out, unlocked a copy of the common makefile.
.P
.ti 6
.B "bco -u ../../../../usr/lib/makefiles/objects.mk"
.P
Now search for in the file for \fB_CLEAN_OFILES_\fR.
This line describes which files will be removed when this rule is invoked.
Re-edit the Makefile, undoing the comment, and run the clean again.
.LE
