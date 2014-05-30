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
.\" $Log: appA.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:11:50  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:03  damon]
.\"
.\" Revision 1.2  1991/12/05  20:57:10  devrcs
.\" 	Added _FREE_ to copyright marker
.\" 	[91/08/01  08:09:41  mckeen]
.\" 
.\" 	merged from dce/devkit version
.\" 	[91/02/21  10:31:22  ezf]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBAppendix A\s0\fR'"
.OH "'\fB\s10Appendix A\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          DCE Development User's Guide: System Administration Appendix
...\"*********************************************************************
.H 1 "Appendix A"
.S 18
.ce
ODE System Administration for DCE
.S P
.P
This appendix contains information about the setup and maintenance of the ODE
for work on the OSF DCE offering.  The
\fIOSF Development Environment System Administration Guide (SAG)\fP describes
the general procedures for setting up and maintaining the ODE;  this appendix
is intended as a supplement to the SAG that provides system administration 
information specific to the DCE offering.  The DCE system administrator should 
read the SAG in order grasp the fundamentals of ODE administration, and then
read this appendix for system administration information specific to using 
the ODE on the DCE offering.
.P
The information in this appendix is organized in the same general order as 
the chapters in the body of the DCE DUG; eg: sandbox information, source
management information, etc.  In general, the sections of this document 
correspond to the references to this appendix in the body of the DUG.  Other
sections contain information that is only for DCE system administrators.
.H 2 "Sandboxes"
There are a few differences concerning sandboxes for the DCE offering. Refer to
the SAG for general system administration information on sandboxes. 
This section only contains information about sandboxes where that information
differ from what is described in the SAG.
.H 3 "ODE rc Files"
The DCE system administrator must determine the correct setting for the 
variables that control the default compilation environment in the \fBshared\fP
rc file in the DCE backing builds.  See the section 
"The Compiler and Build" below for information on setting the values of these
variables.
.P
The system administrator must also set the search path for message catalogs
for DCE sandboxes in the \fBshared\fP rc file in DCE backing builds. This done
by making sure the following line is in the \fBshared\fP rc file.
.in +0.25i
.sp 1
\s10
.B "replace setenv NLSPATH ${sandbox_base}/tools/${target_machine}/bin/%N:${NLSP
ATH}\fP"
\s0
.in -0.25i
.sp 1
This will cause the following directories to be searched for message catalogs:
the sandbox tools area, the backing build's tools area, and any other
directories that were specified by the value of \fBNLSPATH\fP in the user's
environment before the rc file was parsed.
.H 3 "Creating a Sandbox"
The DCE system administrator must set the base directory under which the 
DCE backing builds will live in the \fBshared\fP rc file in the DCE backing
builds.  This directory is specified by the value of the variable 
\fBbuild_base\fP.  As an example, at OSF, all DCE builds are available under 
the directory \fB/project/dce/build\fP, so the value of \fBbuild_base\fP in
the \fBshared\fP rc_file in the DCE backing builds is \fB/project/dce/build\fP.
You should set the \fBbuild_base\fP variable to the path to the directory
where all DCE builds will live in your environment.
.H 2 "Source Management"
If you are not using the ODE source management facility, \fBbcs\fP, then you
will have to work with the ODE system administrator to establish policies and
procedures for using your local source control facility with the ODE.  
The only requirement made by the rest of the ODE on the source control 
facility is that the source control facility can produce a tree in the same
format as the source trees that you recieve from OSF.
.H 2 "Compilation Environment"
This section contains DCE specific information on the compilation environment
provided by the ODE.  As with the other sections of this appendix, the DCE
system administrator should refer to the corresponding section of the SAG for
general information on the Compilation Environment.
.H 3 "The Compiler and Build"
Though any compiler can be used for development on the DCE offering under the
ODE, the common makefiles have
been set up to default to \fBgcc\fR.
If this is not the compiler of choice, or is not available at your site,
a different compiler can be specified by setting the value of the \fBCCTYPE\fR
variable.  This variable can be set in 
the environment, the \fBstandard.mk\fP common makefile, the \fBlocal\fP or
\fBshared\fP rc file in a sandbox, or in the \fBshared\fP rc file in the
backing build (this is the suggested method).  The following are the supported 
values for the \fBCCTYPE\fR variable:
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
The value that tends to be used most often in the absence of the \fBgcc\fP 
compiler is \fBhost\fP.
.P
All the values except \fBhost\fP set the default \fBCFLAGS\fR to
the same values as defined in standard.mk.
They also use the \fBgcc\fP flag \fB-nostdinc\fR which stops the compiler
from automatically looking for included header files in the same directory as
the including source file.
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
and are set in the build's \fBshared\fP rc file.
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


