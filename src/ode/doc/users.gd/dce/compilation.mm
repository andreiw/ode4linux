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
.\" Revision 1.2.2.2  1992/12/03  19:11:56  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:05  damon]
.\"
.\" Revision 1.2  1991/12/05  20:57:13  devrcs
.\" 	merged from dce/devkit version
.\" 	[91/02/21  10:29:51  ezf]
.\" 
.\" 	Newly created for the DCE mini-DUG.
.\" 	[91/01/24  17:12:29  terry]
.\" 
.\" 	Newly created for DCE mini-DUG.
.\" 	[91/01/24  16:46:40  terry]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 3: Compilation Environment\s0\fR'"
.OH "'\fB\s10Chapter 3: Compilation Environment\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          Contents of DCE DUG: Compilation Environment
...\"*********************************************************************
.H 1 "Compilation Environment"
.P
There is a significant amount of DCE specific information regarding the
compilation environment.
Still, the common DUG outlines the general procedures and methods used
by DCE.
New users should read that chapter first and refer to this chapter for
DCE specifics.
This chapter has roughly the same sections as the common DUG to make
cross referencing easier.
.H 2 "The Default Compilation Environment"
.H 3 "Build and Make"
.H 4 "Customizing `make'"
.P
Before you can run \fBbuild\fR or \fBmake\fR to compile any DCE components, 
the \fBmake\fP command may need to be ported to your system.  The DCE 
system administrator should refer to the \fIODE System Administration Guide\fR
for information on porting \fBmake\fP. Developers should contact the DCE system 
administrator if they have questions about whether \fBmake\fP has been ported.
NOTE: You must do this before continuing, to ensure that your \fBmake\fR will
run properly.
Once you are assured that \fBmake\fP will run properly on your system, you
should continue with the remainder of this chapter about compilation.
.H 4 "The Compiler and Build"
The compiler used to build DCE should be configured in the backing build's
\fBshared\fP rc file by the DCE system administrator. DCE system administrators
should refer to the appendix on system administration for details on setting
the default compiler in DCE builds.
.H 4 "Exporting"
Regarding export directories, DCE uses
\fBexport\fI/machine\fB/usr/include/dce\fR as the location for all headers, and
\fBexport\fI/machine\fB/usr/lib\fR as the location for all libraries. 
.H 4 "Build Examples"
.P
DCE specific examples of building follow:
.P
.B Situation:
.SP 0
\fBthreads\fR is a directory with machine-dependent sub-directories
holding the actual source files.
The directory \fBthreads\fR contains, for example,
.P
.ti 2
\fB/project/dce/build/dce/src/threads/RIOS/getasyncinfo.s\fP
.P
.B Resolution:
.SP 0
\fBworkon\fR creates a set without referencing the
machine-dependent sub-directories; in this case:
.P
.ti 2
\fB/sandboxes/suzieq/symphony/movement/src/usr/bin/wakeup\fP
.P
without \fB./RIOS\fR.
You will need to instruct your source control system to check out machine
specific files.  For instance, at OSF you would use the following command:
.P
.ti 2
.B "bco RIOS/getasyncinfo.s"
.P
When ready to compile,
there are two ways in which machine dependent files can be handled.
The first assumes that \fBRIOS/getasyncinfo.s\fR is not a new file,
and therefore is already referenced in the Makefile as machine-dependent.
In this case, the user can enter \fBbuild\fP in the normal fashion.
.P
In the second case, where \fBRIOS/getasyncinfo.s\fR is not already in the
Makefile as being machine-dependent,
the user will need to check out the Makefile and add the 
following line to it:
.P
.ti 2
.B "VPATH = ${TARGET_MACHINE}"
.P
VPATH is a 
.B make
directive which tells \fBmake\fP to search in the specified directory as
well as in the current one.
\fBTARGET_MACHINE\fP is set in each build's \fBrc_file/shared\fR rc file
so it can be overridden locally.
Since the \fBTARGET_MACHINE\fP for examples in this document is \fBRIOS\fP,
.B make
would search in both the current directory and in \fB./RIOS\fP
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
.B Situation
.SP 0
What compiler and loader are being used to build \fBgetasyncinfo\fR?
.P
.B Resolution:
.SP 0
The compiler and the rest of the build tools are found through
the variable \fB$PATH\fP which should be set to look first in the 
backing tree's directory: \fB./tools/\fP\fItarget_machine\fP\fB/bin\fP.
The exceptions to this are when a cover program looks in specific
places for the tools it needs. For example, \fBgcc\fR looks for files it needs 
in the directory indicated by the \fBGCC_EXEC_PREFIX\fP variable.
.P
Many systems provide tools to show where an executable is being found.
For instance, on Unix systems, the command `\fBwhich cc\fP' will show which 
version of \fBcc\fR is being used.
.H 2 "Building With Passes"
.P
For a detailed description of the concept of building the source tree via
multiple passes of \fBmake\fP, refer to the building with passes section in the 
common DUG. The process of building DCE with passes does not differ from
the process discussed in the common DUG, but specifics of this process as it
relates to building DCE are reiterated here for clarity.
.P
All of the pass operations used in the DCE require a single
pass except for building, which requires two passes.
Single pass operations include those mentioned in the common DUG.
The build process is comprised of three passes, two for exporting and one for
the remainder of compilation. The following two export passes both build and 
export the associated targets:
.AL
.LI 
\fBEXPINC\fP 	builds and exports include files.
.LI 
\fBEXPLIB\fP	builds and exports static libraries.
.LE
.P
Building the remainder of DCE is done in the third pass (\fBBASIC\fP).
.H 3 "Descending the Tree"
.P
The process of descending the source tree to build subdirectories is described
in the descending the tree section of the common DUG.
The SUBDIRS variables that are defined for building DCE are the following:
.VL 20
.LI \fBEXPINC_SUBDIRS\fR
The list of sub-directories which should be searched for include
files to export.
.LI \fBEXPLIB_SUBDIRS\fR
The list of sub-directories which should be searched for libraries to export.
.LE
.P
Additional variables for other export passes are found in the common
makefile \fBpasses.mk\fR.
.H 3 "Processing the Leaves"
.P
The variables the user should be aware of for exporting and installing 
in the DCE project include:
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
For example, a make file might contain the line
.br

.in +0.25i
EXPLIB_TARGETS="export_libuser.a export_libkernel.a"
.in -0.25i

to make \fBlibuser.a\fR and \fBlibkernel.a\fR be exported.
.LI \fBILIST\fR
The list of files to install.
.LI \fIpass\fB_TARGETS\fR
The general form of the variables which list files for a pass,
for example, EXPINC_TARGETS.
.LI \fIfile_\fBEXPDIR\fR
The path to export a particular file into.
The path will be taken relative to the rc file variable \fBEXPORTBASE\fR
which is usually set to \fI/sandbox\fB/export/\fImachine\fR.
Defining an EXPDIR for a particlar file overrides the general
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
for the place to  export as well as install.
.LE
.P
The pass which exports include files uses the variable \fBINCLUDES\fR
to determine the list of files to export.
It puts these files in the location specified by the variable
\fB$EXPORTBASE/$EXPDIR\fR or, if a file has been designated specifically,
such as \fB$EXPORTBASE/$\fIfile\fB_EXPDIR\fR, it puts them in that location.
The same principle applies to other types of exports such as libraries.

.H 3 "Calling a Pass"
.P
Legal \fItag\fRs which apply to calling a pass in the DCE environment
include the following (these match the tags for SUBDIRS):
\fBEXPINC\fR and \fBEXPLIB\fR.
.P
The following examples explain the results of calling build with different
arguments in the DCE environment.
.VL 26
.LI "\fBbuild build_all\fR"
run all three passes: exporting headers, exporting libraries, and
finishing all the compilation.
.LI "\fBbuild\fR"
short for "build build_all"
.LI "\fBbuild all\fR"
short for "build build_all"
.LI "\fBbuild \fIfile\fR"
short for "build build_\fIfile\fR"
\fBNOTE\fR: whereas "build_all" goes through all the passes,
"build_\fIfile\fR" only invokes the compilation pass.
.LI "\fBbuild comp_all\fR"
invokes only the compilation pass on all files.
.LI "\fBbuild export_all\fR"
calls all export passes.
.LI "\fBbuild export_all_EXPINC\fR"
calls the pass which builds and exports the include files.
.LI "\fBbuild export_all_EXPLIB\fR"
calls the pass which builds and exports the libraries.

.H 3 "Build's Directory Structure"
.P
.B "src"
.P
The source used to create the DCE is located under \fBsrc\fR.
There are directories under \fBsrc\fR for each of the components in the DCE release,
as well as three directories which contain source code for the build tools, scripts
to build the tools, and the common makefiles used when building.
Beneath each component subdirectory, the source code is generally organized into
subdirectories for each part or program that makes up that component.
For example, the source code for the rpc daemon is found in the directory
\fBsrc/rpc/rpcd\fR.
.P
In a few instances, it is necessary to look deeper to find sources.
For example, the file \fBcma_vmprot.o\fR, which is used to build the threads library,
\fBlibcma.a\fR, contains machine dependencies, and thus the source file is under
the directory \fBsrc/threads/${TARGET_MACHINE}\fR, where \fB${TARGET_MACHINE}\fR
assumes the value `MIPS' or `VAX'.
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
.P
There is one important case where there is a single source
with machine-dependencies: the header files.
Each header file with machine-dependencies is under a machine-dependent
directory, not a directory with its own name.
For example, the user might expect that \fBcma_host.h\fR would be found
in a structure like:
.S -2
.DS I
.ft CW
                   src/threads
                       |
                    cma_host
                       |
          ---------------------------
          |            |            |
         MMAX         RIOS         VAX
          |            |            |
      cma_host.h   cma_host.h   cma_host.h
.DE
.S P
But, since it is a single source with machine-dependencies,
the structure is actually:
.S -2
.DS I
.ft CW
                   src/threads
                       |
          ---------------------------
          |            |            |
         MMAX         RIOS         VAX
          |            |            |
      cma_host.h   cma_host.h   cma_host.h
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
All binaries are located in a directory under the directory \fBobj/${machine}\fR
that corresponds to the source directory for the binary.
For example, the \fBnidl\fR program, the source for which is located under the
directory \fBsrc/rpc/idl/src\fR, is found under the directory
\fBobj/${machine}/rpc/idl/src\fR.
.P
.B "export"
.P
As noted earlier in this document, DCE export headers are located under the
sub-directory \fBexport/${machine}/usr/include/dce\fR,
and libraries are located under \fB${machine}/usr/lib\fR.
.P
.B "tools"
.P
The tools directory, which is normally part of a developer's \fB$PATH\fP,
holds machine-dependent, ODE programs which are specific to that build.
Normally at OSF, ODE programs are mounted from a server (see chapter
1), but, in the case of a special version of a tool,
it will need to take precedence over the normal ODE tools.
For this reason, the build's tools directory should be in the developer's
\fB$PATH\fP before the path to the standard ODE tools.

.H 2 "Modifying the Build Environment"
.H 3 "Modifying Sandbox rc Files"
.H 4 "Include Files (Headers)"
.P
The placement of headers in the export area for the DCE project is different 
from what is described in the common DUG,
and the default value of \fBINCDIRS\fR also differs from what is described in 
that document. For DCE sandboxes, \fBINCFLAGS\fP should be set as follows:
.sp
.ti 2
\fBsetenv INCDIRS "-I${export_base}/usr/include/dce ${INCDIRS}"\fR
.H 4 "Libraries"
.P
Unlike header files, libraries have the same placement in the DCE
as is described in the common DUG.
The \fBlocal\fR sandbox rc file is
.P
.ti 2
.B "setenv LIBDIRS ${LIBDIRS}"
.P
the \fBshared\fR rc file is set to:
.P
.ti 2
\fBsetenv LIBDIRS "-L${export_base}/usr/lib ${LIBDIRS}"\fR
.P
and in the builds to:
.P
.ti 2
.B "setenv LIBDIRS -L${export_base}/usr/lib

.H 3 "Modifying Makefiles"
.P
The Makefile template for DCE can be found in:
.P
.ti 2
\fI/build\fB/src/usr/lib/makefiles/template.mk\fR
.H 3 "Modifying Common Makefiles"

.P
The DCE common makefiles are also located under the directory:
.P
.ti 2
/\fIbuild\fB/src/usr/lib/makefiles\fR.
