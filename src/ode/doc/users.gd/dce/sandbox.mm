.\""
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
.\" $Log: sandbox.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:12:18  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:14  damon]
.\"
.\" Revision 1.2  1991/12/05  20:57:30  devrcs
.\" 	merged from dce/devkit version
.\" 	[91/02/21  12:07:43  ezf]
.\" 
.\" 	Newly created for the DCE mini-DUG.
.\" 	[91/01/24  17:16:31  terry]
.\" 
.\" 	Newly created for DCE mini-DUG.
.\" 	[91/01/24  16:43:57  terry]
.\" 
.\" $EndLog$
...\"*********************************************************************
...\"          Reset page information for chapters in DUG
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 1: Sandboxes\s0\fR'"
.OH "'\fB\s10Chapter 1: Sandboxes\fR''\\\\nP\s0'"
.nr P 0                			\"*** reset page number to page 1
.af P 1                			\"*** reset page number to Arabic
.SK
...\"*********************************************************************
...\"          Contents of DCE DUG: Sandboxes
...\"*********************************************************************
.H 1 "Sandboxes"
Before continuing with this chapter, read chapter 1: "Sandboxes"
in the common Development User's Guide (DUG). That chapter fully explains the
development environment concepts and introduces the basic mechanism for
code development and testing (the sandbox environment).
.P
There is very little specific information regarding DCE sandboxes that is
different from the sandbox information common to other ODE projects.
The reader should use the common DUG to learn about and reference
sandboxes, using this chapter to provide specific information on
the location of DCE builds, tools, etc.
.H 3 "Sandbox Structure"
.P
The common names for machine types for DCE (specified to the \fB-m\fP option
of the \fBmksb\fP command) within OSF are:
.BL
.LI
rios	(RISC System/6000 running AIX)
.LI
pmax	(DECstation 3100 running OSF/1)
.LI
at386	(intel 386 running OSF/1)
.LI
mips	(DECstation 3100 running ULTRIX)
.LE
.H 3 "ODE rc Files"
The contents of the sandbox \fBrc_files\fP for DCE sandboxes differ from those
of a generic sandbox in two ways. The first difference is that the \fBCCTYPE\fP
variable, which determines the compiler that is used for building, must often be
set specially for DCE. Generally, this variable is not set by the sandbox
user; it is set in the backing build's \fBrc_files\fP by the DCE system
administrator. For more details on setting the \fBCCTYPE\fP variable in DCE
builds, DCE system administrators should refer to the appendix containing 
system administration information.
.P
The second difference is that the \fBNLSPATH\fP environmental variable, which defines 
the search path for message catalogs, must be set in DCE sandboxes.  This 
is because there are special message catalogs for DCE
placed in the tools area of DCE backing builds.  The line in the sandbox 
rc file to set this variable should look like:
.in +0.25i
.sp 1
\s10
.B "replace setenv NLSPATH ${sandbox_base}/tools/${target_machine}/bin/%N:${NLSPATH}\fP"
\s0
.in -0.25i
.sp 1
This will cause the following directories to be searched for message catalogs:
the sandbox tools area, the backing build's tools area, and any other 
directories that were specified by the value of \fBNLSPATH\fP in the user's 
environment before the rc file was 
parsed.  Note that if the user wishes to have other directories searched for
message catalogs before the tools areas, he must modify this line accordingly.
If he wishes to have other directories searched after the tools directories, 
he can just set the \fBNLSPATH\fP variable accordingly in the environment.
.H 3 "Creating a Sandbox"
Within OSF,
the DCE project uses the following naming conventions for builds to back 
sandboxes. The default build is called
\fBdce1.0\fR;  it is the newest version of the DCE build.
Other builds are called \fBdce.N\fR, where \fBN\fR is the number given to the
build by IBM (the integrator for the DCE offering).
Developers should expect to see builds with names like \fBdce.22, dce.25, and 
dce.28\fP.
.P
The DCE system administrator must decide where to place all
the DCE builds. The location is set in the \fBrc_files\fP in the backing build 
by the variable 
\fBbuild_base\fP. At OSF, all DCE builds need to be accessible under
.sp
.ti 2
\fB/project/dce/build\fR
.P
on the developer's system.
.H 3 "Retargeting a Sandbox"
.P
Developers can remain backed by the same build or sandbox until
that environment is too far behind the default build
to permit effective development,
at which time the sandbox needs to be \fBretargeted\fP.
For the DCE project within OSF, there will usually be only two builds available
at any time:  the most recent IBM build, and the \fBdce1.0\fP build that is 
based on the most recent IBM build.
Since IBM is the DCE integrator, and since the main DCE source tree is at IBM,
the need for retargeting is driven by the availability of IBM builds.
Each time IBM makes a new build available, a new version of the \fBdce1.0\fP
build will
be created, composed of the latest IBM build as well as all OSF changes not yet integrated into the IBM tree.
If a developer wishes to be backed by the latest IBM build, he must retarget
each time a new IBM build becomes available.
If the developer wishes to be backed by the \fBdce1.0\fP build,
no retargeting is necessary.
.P
\fINote:\fR  Sites that participate in the \fBdcenet\fR WAN have immediate access
to new IBM builds via the \fBdillo\fP AFS cell in the directory \fB/afs/dillo/project/dce/builds\fP.  Access depends on the ability to authenticate into that AFS 
cell.
.H 2 "Multiple Backing Trees"
.P
The use of \fBmultiple backing trees\fP in DCE is not significantly
different from the description in the common DUG;  however, an explanation
is provided here for clarity. This explanation is given in the context of 
a DCE developer working on interfaces to the kernel.
.P
DCE developers working on kernel interfaces generally need to
access and modify files from both a DCE build and from an OSC
build.  This need is satisfied by setting up a sandbox that is backed
by the two types of builds via the multiple backing tree mechanism.  The steps
for setting up such a sandbox are as follows:
.AL
.LI
Create a sandbox \fIsb\fP that is backed by a DCE build (as described in 
chapter 1 of the common DUG).
.LI
Create a sandbox rc file that refers to an OSC build that you wish
to be backed by.  To do this, copy the file \fIsb\fP\fB/rc_files/shared\fR to
\fIsb\fP\fB/rc_files/kernel.rc\fR. Note that the \fBkernel.rc\fP filename has
no significance save that it is descriptive of the file contents in this case.
In reality, this file may have any name.
.LI   
Edit the file \fIsb\fP\fB/rc_files/kernel.rc\fR and replace the first line
.br
.in +1i
.sp 1
\fBinclude ../link/rc_files/shared\fP 
.sp 1
.in -1i
with a line that includes the shared sandbox rc file from the OSC build.  The
rc file from the OSC build can be included via a symbolic link in the sandbox
directory, as in 
.br
.sp 1
.in +1i
\fBinclude ../\fP\fIalt_link\fP\fB/rc_files/shared\fP
.in -1i
.sp 1
where \fIalt_link\fP is the name of the link to the OSC build, or by specifying
the absolute path to the shared rc file in the OSC build, as in
.br
.sp 1
.in +1i
\fBinclude \fP\fIpath_to_build\fP\fB/rc_files/shared\fP
.in -1i
.sp 1
where \fIpath_to_build\fP is the absolute path to the OSC build.
You must also add the line
.sp 1
.in +1i
\fBsetenv OBJECTDIR ../obj/${target_machine}\fP
.in -1i
.sp 1
at the end of the file.
.LE
.sp 1
At this point the sandbox is backed by both builds. 
.sp 1
.P
When using the ODE commands in a sandbox backed by multiple builds, there are 
two methods for indicating which of the backing builds the command refers to.
The first method is to specify the rc file associated with the desired backing
build to the command line option \fB-sb_rc\fP.
All of the ODE commands understand this option, which tells the tools which rc
file in the \fIsb\fP\fB/rc_files\fP directory to read for configuration 
information.  If the `-sb_rc' option is not specified, the ODE tools default to
using the file \fIsb\fP/\fBrc_files/local\fP.  Use of this method in a sandbox
created following the above steps would mean that the command-line option
\fB-sb_rc kernel.rc\fP would be passed to ODE commands that are to refer to the
OSC backing build.
.P
The second method requires some additional setup but is more automatic. When
this method is used, the ODE commands determine which backing build
to use from the path to the directory in which they were invoked. The following
steps describe additional setup for the second method:
.AL
.LI
Create the directory \fIsb\fP\fB/src/kernel\fP. The name kernel refers to
the \fBsrc/kernel\fP directory in the OSC backing tree. The directory created
in this step must exist in one of
the build trees backing the sandbox, and the path from \fBsrc\fP may be as
long as desired. For example, the directory created could have been \fBkernel/includes\fP or \fBkernel/includes/mach\fP.
.LI
Create the file \fIsb\fP\fB/rc_files/projects\fP, comprised of lines of the form
.sp 1
.in +1i
\fIpath	 rc_file\fP
.sp 1
.in -1i
where \fIpath\fP is the path from \fIsb\fP\fB/src\fP to the directory
that was just created in step 1, and \fIrc_file\fP is the name of the rc file created
in step 2 while setting up the sandbox. Each line of this file, which all the 
ODE commands look for
when invoked, associates the \fIsb\fP\fB/src/path\fP directory with
\fIsb\fP\fB/rc_files\fP\fI/rc_file\fP. Each time an ODE command is executed 
from a
directory that is below some path which is specified in \fIsb\fP\fB/rc_files/projects\fP file, the command reads configuration information from the associated 
\fBrc_file\fP
(in \fIsb\fP\fB/rc_files\fP). 
.LE
.P
Use of this method in a sandbox created following the 
above steps would mean that the \fIsb\fP\fB/rc_files/projects\fP file would 
contain the line
.sp 1
.in +1i
\fB/kernel     kernel.rc\fP
.sp 1
.in -1i
and ODE commands would refer to the OSC build when run from under
the \fIsb\fP\fB/src/kernel\fP directory.
.P
When creating the \fIsb\fP\fB/rc_files/projects\fP file, it is important to
keep in mind that when the ODE commands search the 
\fIsb\fP\fB/rc_files/projects\fP file for a path, the first path in the file
that matches the directory 
from which the command was invoked is used. For example, if the
\fIsb\fP/\fBrc_files/projects\fP file looked like
.sp 1
.in +1i
\fB/kernel		osc.25.rc\fP
.br
\fB/kernel/includes	osc.20.rc\fP
.sp 1
.in -1i
and an ODE command was executed from
.sp 1
.in +1i
\fBsrc/kernel/includes\fP
.sp 1
.in -1i
the command would take configuration information from the file \fIsb\fP/\fBrc_files/osc.25.rc\fP. This would be the case because \fBkernel\fP is the first entry
in the \fIsb\fP\fB/rc_files/projects\fP file, and the command was executed from
below the \fBsrc/kernel\fP directory. The correct way to consruct the \fIsb\fP/\fBrc_files/projects\fP file is to put the longest paths at the beginning of the
file.
.sp 1
.in +1i
\fB/kernel/includes	osc.20.rc\fP
.br
\fB/kernel		osc.25.rc\fP
.sp 1
.in -1i

.H 2 "Setting the Sandbox Environment"
Since each site will need to determine its own environment, the
information in this section only applies within OSF.
.H 3 "Accessing the Builds"
The easiest way to access the DCE builds is to mount them using:
.sp
.ti 2
.B "osfmount dce build"
.P
This command mounts the builds under \fB/project/dce/build\fR,
which is where they need to be located.
.P
It is not necessary for the developer to use \fBosfmount\fP,
but it is necessary for the builds to show up in \fB/project/dce/build\fR.
All DCE ODE tools will search for builds using this path;
if the developer would rather symbolically link builds underneath
\fB/project/dce/build\fP or use another method for mounting,
that is perfectly acceptable, but the build must show up there.
.P
Another directory that should be mounted by DCE developers is
\fBserver2:/u0/projects\fR.
This should be mounted on \fB/project/projects\fR, using the command
.sp
.ti 2
.B "osfmount ode projects"
.P
This file contains the list of builds, configuration information, and
the base directories for all build projects.
It allows users the shorthand of entering just \fIname\fR (the name of a build)
as an argument to the tools instead of having to give the entire path.
It also is used by the \fBbco -from\fR option to locate the appropriate
revision to check-out.
.H 3 "Environmental Variables"
\fIThe\fP \fBPATH\fP \fIVariable\fP
.sp 1
In order to access the ODE tools, developers must add the paths to the ODE
tools directories to the value of the \fBPATH\fP environmental variable.
The path to the ODE tools will vary from site to site. Developers at a specific
site need to contact the ODE system administrator to find out where the ODE
tools that run on their system are located. 
.P
At OSF, developers need to mount the ODE tools from \fBserver2\fP.
For example:
.sp
.ti 2
\fBmount server2:/u0/release/\fImachine\fB/ode /usr/ode\fR
.P
The directories under \fBode\fP include \fBbin\fR, \fBnewbin\fR, \fBlib\fR,
\fBetc\fR, and \fBman\fR.
Since the man pages are available from other sources, most developers
will only be interested in \fBbin\fR and \fBnewbin\fR.
At least \fBbin\fR and maybe \fBnewbin\fR need to be in the developer's \fBPATH\fR environment variable and should be amoung the first directories in the
\fBPATH\fP, so ODE versions of tools like \fBmake\fR are accessed before other 
versions.
.P
As with the location of the build, it does not matter how the tools are
accessed just as long as they are.
The tools can be mounted anywhere, and they can be accessed directly or
through links.
One way to do this would be to follow the X11 model. 
In that model ode would be mounted under \fB/usr/ode\fP and a symbolic link
would be made from \fB/usr/bin/ode\fP to \fB/usr/ode/bin\fP.
\fBPATH\fR would then be set with:
.sp
.ti 2
.B "setenv PATH /usr/bin/ode:$PATH"
.P
Whenever a new revision of a tool comes out, it is placed 
under \fBode/newbin\fR. It remains there for a week so developers can help 
test it, after which, if there have been no problems, it is moved 
to \fBode/bin\fR.
In order to access these new versions of the ODE tools, it is necessary to put 
the path to \fBnewbin\fP in
\fBPATH\fR before \fBbin\fP.
.P
There are occasionally times when a build-specific tool is needed.
These are kept under the build in \fBtools\fI/machine\fB/bin\fR and
are best accessed through the sandbox link so that, if the sandbox is
retargeted, \fBPATH\fR is still set correctly.
Putting all these together, the complete \fBPATH\fR would look like:
.SP
.ti 2
\fBsetenv PATH /\fIsandbox\fB/link/tools\fI/machine\fB/bin:/usr/ode/newbin:
.ti 4
/usr/bin/ode:$PATH\fR
.P
\fBPATH\fR can also be set inside the startup script for the shell.
This makes it convenient to use another ODE variable, \fB$SANDBOX\fP, as
part of the \fBPATH\fR.
.P 
\fIThe \fP\fBNLSPATH\fP \fIvariable\fP
.sp 1
The \fBNLSPATH\fP environmental variable defines the directories that are 
searched for message catalogs. This variable should be set in your environment
to specify directories on your system that contain such catalogs. See
the section on ODE rc files for information on the use of this variable
in the sandbox environment.
.H 2 "Tutorial: Sandboxes"
This section fills in some of the details left out of the common DUG
tutorial on sandboxes.
Like the section on setting the environment above, it is OSF site
specific.
Outside users will need to get this information from their ODE
system administrator.
.AL 1
.LI "Step" X
For project DCE it is necessary to mount the build directories:
.SP
.ti 6
.B "osfmount dce build"
.P
As stated above, there are other ways to do this, but it is necessary
for the tools to be able find the builds under \fB/project/dce/build\fR. 
This step will only need to be repeated when the workstation is rebooted.
.LI "Step" X
As described above, the ODE tools need to be mounted, as well as
\fBprojects\fR, and \fBPATH\fR needs to be set to find the ODE tools early
on in its search.
.P
.ti 6
.B "mount server2:/u0/release/\fImachine\fB/ode /usr/ode"
.ti 6
.B "osfmount ode projects"
.ti 6
.B "setenv PATH /sandboxes/suzieq/${SANDBOX}/link/tools/rios/bin:"
.ti 8
.B "/usr/ode/bin:$PATH"
.P
These steps ensure that the proper set of tools is used in creating binaries.
.LE
