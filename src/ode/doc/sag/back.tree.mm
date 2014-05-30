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
.\" $Log: back.tree.mm,v $
.\" Revision 1.3.12.1  1995/05/22  19:44:56  robert
.\" 	Change/permute ode 2.3 -> ode2.3.4
.\" 	[1995/05/22  17:09:02  robert]
.\"
.\" Revision 1.3.8.4  1994/02/15  20:21:08  marty
.\" 	CR # 1041 - Add info about new copyright handling in SAG
.\" 	[1994/02/15  20:20:49  marty]
.\" 
.\" Revision 1.3.8.3  1993/11/23  17:36:22  damon
.\" 	CR 794. Added COPYRIGHT NOTICE description
.\" 	[1993/11/23  17:36:14  damon]
.\" 
.\" Revision 1.3.8.2  1993/11/23  15:52:06  damon
.\" 	CR 804. Elaborated description of sb.conf
.\" 	[1993/11/23  15:51:54  damon]
.\" 
.\" Revision 1.3.8.1  1993/11/20  21:15:44  damon
.\" 	CR 845. Added exclusive file locking lock_dirs description
.\" 	[1993/11/20  21:15:34  damon]
.\" 
.\" Revision 1.3.6.1  1993/08/26  14:55:20  marty
.\" 	CR # 628 - Update to ODE 2.3
.\" 	[1993/08/26  14:55:06  marty]
.\" 
.\" Revision 1.3.4.6  1993/06/07  20:36:51  damon
.\" 	CR 458. Added text for cr_validate
.\" 	[1993/06/07  20:36:39  damon]
.\" 
.\" Revision 1.3.4.5  1993/06/06  16:44:55  damon
.\" 	CR 458. Added sb.conf documentation
.\" 	[1993/06/06  16:44:48  damon]
.\" 
.\" Revision 1.3.4.4  1993/06/04  21:25:58  damon
.\" 	CR 458. Updated for 2.3
.\" 	[1993/06/04  21:25:52  damon]
.\" 
.\" Revision 1.3.4.3  1993/05/27  21:03:17  damon
.\" 	CR 557. Added Buildconf info
.\" 	[1993/05/27  21:03:10  damon]
.\" 
.\" Revision 1.3.4.2  1993/04/22  15:28:00  damon
.\" 	CR 458. Updated for 2.3
.\" 	[1993/04/22  15:24:08  damon]
.\" 
.\" Revision 1.3.2.6  1993/01/04  18:12:08  damon
.\" 	CR 332. Updated for 2.2
.\" 	[1993/01/04  18:11:34  damon]
.\" 
.\" Revision 1.3.2.5  1992/12/03  19:09:13  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:40:44  damon]
.\" 
.\" Revision 1.3.2.4  1992/11/18  20:12:03  damon
.\" 	CR 332. Added installation of tools used by odexm
.\" 	[1992/11/18  20:11:38  damon]
.\" 
.\" Revision 1.3.2.3  1992/11/18  19:40:09  damon
.\" 	CR 332. Changed section on odexm.conf
.\" 	[1992/11/18  19:39:45  damon]
.\" 
.\" Revision 1.3.2.2  1992/11/18  18:52:46  damon
.\" 	CR 332. Replaced kxctd references with odexm ones
.\" 	[1992/11/18  18:52:22  damon]
.\" 
.\" Revision 1.3  1991/12/17  21:00:45  devrcs
.\" 	corrected typo
.\" 	[1991/12/09  22:23:56  ezf]
.\" 
.\" Revision 1.2  1991/12/05  20:59:06  devrcs
.\" 	fixed some errors, changed description for setting
.\" 	shared 'context' vars
.\" 	[1991/11/06  22:54:41  hester]
.\" 
.\" 	removed vague references to other parts of doc, cleaned
.\" 	up some formatting
.\" 	[1991/11/01  15:45:12  hester]
.\" 
.\" 	updated after using to install ode2.1 system test rcs
.\" 	servers and build servers.
.\" 	[1991/10/31  21:17:56  hester]
.\" 
.\" 	changes for sag update: restructure some paragraphs
.\" 	and added chapter 6 to end.
.\" 	[91/07/31  15:53:02  hester]
.\" 
.\" 	includes ademola's changes
.\" 	[91/05/14  15:46:23  hester]
.\" 
.\" 	First cut at updates for SAG review.
.\" 	[91/05/10  16:29:10  hester]
.\" 
.\" 	Initial revision of Chapter 6 of SAG
.\" 	[91/01/25  18:42:13  hester]
.\" 
.\" $EndLog$
.\"
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 6: Backing Build Configuration\s0\fR'"
.OH "'\fB\s10Chapter 6: Backing Build Configuration\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          Contents of ODE/SAG: Backing Build Configuration
...\"*********************************************************************
.H 1 "Backing Build Configuration"
This chapter discusses how to create a backing build and populate it with
project sources to turn them into a backing build.
It also briefly discusses how to build the sources though this topic
is more thoroughly covered in the Release Notes for each offering.
.P
The reader should have already read and executed the work in the previous
chapters relating to creating and populating a source control tree,
and building the tools.
.H 2 "Creating the Backing Build"
Both types of builds, static and dynamic, are set up in the same way with 
the exception that the configuration variables that 
control submissions don't allow submissions to a static build.
.P
.iX "build" "dynamic"
.iX "build" "static"
.iX "static build"
.iX "dynamic build"
.iX "backing build"
.iX "build" "backing"
Each build defines a default submission build where the submissions are
made to.  The default build has to be a dynamic build.  A static build
will always reference a dynamic build as the submission build; a dynamic 
build will define itself to be the submission build.
.P
The first step in creating a backing build is to create the build's
directory.
At OSF, the physical location of the builds can be anywhere but is always
mounted on a user's system under:
.sp
.ti 2
\fB/project/\fIproject_name\fB/build\fI/build_name\fR
.P
where \fIproject_name\fR in OSF can be \fBosc\fR, \fBdce\fR, \fBmotif\fR,
\fBdme\fR, etc.
and \fIbuild_name\fR is the name of a specific build.  
At OSF, each build has a name of the form \fIproject.rel_num\fBb\fInum\fR,
for example osc1.1b1 or motif2.2b6.
.P
Create the actual physical directory on the build server. Make it owned
by the source file account and set the permissions to 755.
.H 3 "Directories to Create"
You will need to create a number of directories below the build directory.
The list of directories to make is:
.BL
.LI
src
.LI
export
.LI
logs
.LI
obj
.LI
rc_files
.LE
.P
Make them all owned by the source file owner and set the permissions to 755.
.H 3 "Log Files"
If the project is using ODE source control, the default build, i.e.
the build submissions are sent to, must have the following files
created under \fBlogs\fR:
.iX "DEFUNCT"
.iX "SNAPSHOT"
.iX "bsubmit.log"
.BL
.LI
DEFUNCT
.LI
SNAPSHOT
.LI
bsubmit.log
.LE
.P
Initially, these files must contain at least one blank line. 
.P
The \fBDEFUNCT\fR file will hold the list of files previously submitted but
which now have been deleted from the build.
\fBbsubmit.log\fR keeps the history of all submissions.
Refer to the \fIODE User's Guide\fR for more information on submissions.
Over time, this file can get quite large; it should be saved to some other
location and started over occasionally.
At OSF, this is done each time there is a new build.
.H 3 "Makeconf"
.iX "Makeconf"
This file is located under \fBsrc\fR and marks the top of the source tree.
It must be present in all builds.
.iX "make"
Several built-in \fBmake\fR variables for the ODE \fBmake\fR are
defined based upon the location of this file and its relationship to the
directory \fBmake\fR was invoked from.
You should copy this file from the src directory of the ODE distribution.
Change the file permissions to 444 and make the file owned by the source file
account.
.iX "common make files"
.iX "make files"
.iX "make"
.H 2 "Common make files"
If you are using an offering from OSF, use the common make files that have
been provided. If you are setting up a new project, copy the following files
into \fBsrc/ode/mk\fR:
.BL
.LI
osf.depend.mk
.LI
osf.doc.mk
.LI
osf.lib.mk
.LI
osf.man.mk
.LI
osf.obj.mk
.LI
osf.prog.mk
.LI
osf.rules.mk
.LI
osf.script.mk
.LI
osf.std.mk
.LI
sys.mk
.LE
Also, copy the osf.ode.* files. Rename them from osf.ode.* to
osf.<your project>.*.

.H 2 "Copyrights"
.iX "copyrights"
A backing tree can now be configured to handle copyrights in one of
two ways.  Using copyright markers (the old way) or embedding expanded
copyright text directly into source files (the new way).
Copyright markers (i.e. @OSF_COPYRIGHT@) have been used in the past to
mark the where, in the source file, copyright text should be placed.
During a projects lifecycle copyright text is added to a file
just before a release is done.  Typically, a release engineer checks out
all source files to a staging area and runs a script that replaces
copyright markers with copyright text.  This has turned out to be  both time
consuming and error prone.
.P
To expedite the release process we have enabled \fBbci\fR to recognise and
validate fully expanded copyright text within source files.
In order to use this feature each backing tree must be configured for
expanded copyright validation and each source file must have its copyright
markers replaced with expanded copyrights.
.P
Configuring a backing tree for expanded copyright validation requires
a \fBcopyrights\fR file and the variables \fBcheck_copyrights\fR and
\fBcopyright_years\fR must be set to
\fBtrue\fR in the \fBsc.conf\fR file.  Details are given in the section 
\fBSource Control Configuration File\fR.
.H 2 "rc File Setup"
An rc file is a file that contains information which affects the 
way the tools will work.  
For example, the tools read these files to determine where to find
a backing build and what machine types to build for.
The rc files need to be in place and contain the correct information
to allow the build to serve as a backing tree.
The relationship between the rc files is described in detail in the ODE
User's Guide; additional project-specific rc file variables
are discussed in the supplemental ODE User's Guides.
.iX ".sandboxrc"
Basically, the \fB.sandboxrc\fR file is needed to allow the build to
do sandbox operations such as check-outs and check-ins.
.iX "Buildconf"
.iX "sc.conf"
The Buildconf rc file sets the environment for the build and the sc.conf file
sets the environment for source control operations.
.H 3 ".sandboxrc"
This file is needed only in a build which which will actually be directly
built in or submitted from, such as a nightly build or a shared sandbox.
The file should be under the build
directory at the same level as \fBsrc\fR.  It contains three lines:
.sp
.ti 2
\fBdefault\fI build_name\fR
.ti 2
\fBbase *\fI base-directory\fR
.ti 2
\fBsb\fI build_name\fR
.P
These three lines provide the minimum sandbox description:
the default sandbox, its base directory, and the sandbox name.
Since the only sandbox is the build itself, the arguments to \fBdefault\fR
and \fBsb\fR are identical.
The "*" after \fBbase\fR and before the base directory indicates that all
sandboxes use this base directory.
It would also be correct to write the line like this:
.sp
.ti 2
\fBbase \fIbuild_name base-directory\fR
.P
At OSF, these three lines have values such as:
.sp
.ti 2
\fBdefault dce1.0\fR
.ti 2
\fBbase * /project/dce/build\fR
.ti 2
\fBsb dce1.0\fR
.P
All of the rc files use keywords before some entries.
The keyword \fBreplace\fR indicates that this line should override any
previously existing value.
If the keyword \fBreplace\fR is not present and there is already a value
for the variable, it is left as is.
The keyword \fBsetenv\fR indicates to ODE that this variable should be
treated internally as an environment variable.
The keyword \fBon\fR followed by a machine type, indicates that this
definition only applies to this specific machine type.
This must match exactly the \fBMACHINE\fR value from the machine-specific
configuration script used in building the tools (see Chapter 3).
.H 3 "Buildconf and Buildconf.exp"
.iX "Buildconf"
.iX "Buildconf.exp"
.iX "configuration files" "Buildconf"
.iX "configuration files" "Buildconf.exp"
OSF offerings using ODE 2.3.X will already have a Buildconf file and a
Buildconf.exp file which do
not need to be modified. If you are starting a new project,  you should copy
the Buildconf and Buildconf.exp files from the ODE distribution.
These files file resides
in a project specific directory in the source tree. This directory is
given the name of the project. The ODE project name is ode. Thus, ODE's
Buildconf file is in .../src/ode/Buildconf.
.P
The Buildconf file and the Buildconf.exp file serve similar purposes. For
a build which is not backed by other builds, only the Buildconf file is
used. The Buildconf file is evaluated and that is all.
.P
When the Buildconf file is evaluated, the variable 'sandbox_base' is set
to be the full path to the build that the user is working in. For instance,
at OSF, the ode2.3.4 build is in /project/ode/build. The full path is thus
/project/ode/build/ode2.3.4. This is the same as if the Buildconf file 
contained the following line:
.P
replace sandbox_base /project/ode/build/ode2.3.4
.P
Most variables set in the build environment are simple strings which do not
refer to multiple builds. All of these variables are set in Buildconf.
Here are a few simple variable settings:
.P
.nf
replace setenv RULES_MK osf.rules.mk
replace setenv MAKESYSPATH ${source_base}/ode/mk
.fi
.P
The Buildconf.exp is the 'expansion' file for Buildconf. It is used to
expand the values of certain variables. When the build that a user is building
in is backed by other builds, the
Buildconf file is evaluated first, and then the Buildconf.exp file is
evaluated once for each build in the backing chain, including the build
that the user is building in.
.P
In this case the value of \fBsandbox_base\fR is set a little differently.
\fBsandbox_base\fR is first set to the path for the last build in the
backing chain and Buildconf is evaluated. \fBsandbox_base\fR is then set
to each build in the chain starting with the last and ending with the
build that the user is in. Buildconf.exp is evaluated once for each value
of \fBsandbox_base\fR.
.P
Let's say that we are in the sandbox /usr/users/suzieq/sb/ode which is
backed by /project/ode/build/ode2.3.4. For the value of MAKESYSPATH, Buildconf
would have:
.P
replace setenv MAKESYSPATH ${source_base}/ode/mk
.P
Buildconf.exp would have:
.P
replace setenv MAKESYSPATH ${source_base}/ode/mk:${MAKESYSPATH}
.P
This would result in MAKESYSPATH having a value of:
.P
/usr/users/suzieq/sb/ode/src/ode/mk:/project/ode/build/ode2.3.4/src/ode/mk
.P
The first lines of the Buildconf file
contain settings for
the \fBcontext\fR variable using the \fBon\fR keyword, for 
specific machine types.
This variable is used in the \fBsrc/Makeconf\fR file to conditionally
set the \fBtarget_machine\fR and \fBtarget_os\fR used by make.
Again, these should match the values used to build the tools (see
Chapter 3) as well as the name of the machine-specific directories 
created earlier.
You need to edit these lines for each machine type being
supported.
.P
These next variables define the characteristics of the build:
.P
.VL 15
.LI \fBbuild_base\fR
This is the base directory for builds for this project.
The assumption in OSF is that there will be multiple builds for each
project but, within a project, the builds will all be accessed from under 
the same base directory.
You should edit this line.
.LI \fBsandbox_base\fR
You do not need to enter this field, it will be entered for you when this
file is evaluated. If you have this field, remove it.
.LI \fBbuild_list\fR
At OSF there are many builds and it is convenient to create a single file which
lists all build names, their configuration information and base directory.
By using this file, many of the tools can accept just the name of the build
as a command line option.
From this they figure out where the build is and what revision of the source
to apply to it.
This variable indicates the path and name of the file with this information.
If there is no \fBbuild_list\fR associated with the site, this entry should
be deleted.  See a latter section of this chapter for more information on this file.
.LE
.P
The remaining variables listed here affect the compilation environment.
.VL 15
.LI \fBbuild_makeflags\fR
These are the flags \fBbuild\fR calls \fBmake\fR with.
The flags are those needed on every call to \fBmake\fR.
You need to modify these flags according to the local
build environment.
.LI \fBsource_base\fR
The location of the src directory in the sandbox.
This line is normally not edited.
.LI \fBobject_base\fR
The location of the object directory in the sandbox.
This line is normally not edited.
.LI \fBexport_base\fR
The location of the export directory in the sandbox.
This line is normally not edited.
.LI \fBSITE\fR
This line should be edited to reflect the site of the project.
.LI \fBOWNER\fR
This line indicates the default owner for files which are installed.
.LI \fBGROUP\fR
This line indicates the default group for files which are installed.
.LI \fBPROJECT_NAME\fR
This string is used to include project-specific makefiles into the 
common makefiles.  You should modify this to contain your project name
in upper-case letters.
.LI \fBproject_name\fR
This string is used to include project-specific makefiles into the 
common makefiles.  You should modify this to contain your project name
in lower-case letters.
.LI \fBRULES_MK\fR
This indicates the name of the top-level common makefile.  It should not
be edited.
.LI \fBMAKESYSPATH\fR
This indicates the path to the common makefiles.
.LI \fBSOURCEDIR\fR
This variable gets used by sandboxes backed by this build and is set
here to override any existing value.
This line is normally not edited.
.LI \fBBACKED_SOURCEDIR\fR
This variable gets used by sandboxes backed by this build and begins by
being set to the build's source directory.
This line is not normally edited.
.LI \fBEXPORT_BASE\fR
This variable gets used by sandboxes backed by this build and begins by
being set to the build's export directory.
This line is not normally edited.
.LI \fBINCDIRS\fR
This variable sets the path for compiles to search for header files.
Each sandbox will put its own path in front of this path so the order
of search will be the sandbox's export directory followed by the build's
export directory.
This line is only edited if the exported header files are kept somewhere
other than the standard export directory.
.LI \fBLIBDIRS\fR
This variable sets the path for compiles to search for libraries.
Each sandbox will put its own path in front of this path so the order
of search will be the sandbox's export directory followed by the build's
export directory.
This line is only edited if the exported libraries are kept somewhere
other than the standard export directory.
.LI \fBSHLIBDIRS\fR
This variable is identical to \fBLIBDIRS\fR but applies to shared libraries.
This line is only edited if the exported shared libraries are kept somewhere
other than the standard export directory.
.LI \fBNO_SHARED_LIBRARIES\fR
If this variable is set, the build will not attempt to create shared
libraries.
To build shared libraries, remove this entry completely.
.LI \fBUSE_STATIC_LIBRARIES\fR
If this variable is set and \fBNO_SHARED_LIBRARIES\fR is not set,
the shared libraries will be built but no attempt will be made to link
with them.
To link to the shared libraries, remove this entry completely.
.LE
.H 3 "sets"
.iX "configuration files" "sets"
The \fBsets\fR file contains only two lines, one with the default set name
and one which would begin the list of sets if there was more than one.
The default set is the same value as \fBdefault_set\fR in the \fBBuildconf\fR
rc file. Create this file in the \fBrc_files\fR directory with permission
444 and owned by the source file account. The two lines should be:
.P
.ti 2
\fBdefault\fR <default_set>
.ti 2
\fBset\fR <default_set> .
.H 3 "Sandbox Configuration File"
.iX "sb.conf file"
.iX "configuration files" "sb.conf
This file is used to indicate whether or not a build is backed by another
build and whether ODE source control and/or the ODE build environment should
be used. Create an \fBsb.conf\fR file in the \fBrc_files\fR<project> directory.
.P
In a backing build that is not backed by another build, this file can be empty.
Optionally, there are two variables which can be set: \fBode_sc\fR and
\fBode_build_env\fR. In a build which is backed by another build, all four of
the variables listed must be set.
.VL 15
.LI \fBbacking_project\fR
Project that this build is backed by.
.LI \fBbacking_build\fR
Logical path to the build that this build is backed by.
.LI \fBode_sc\fR
This variable can be 'true' or 'false'. True means that ODE source control
should be used.
.LI \fBode_build_env\fR
This variable can also be 'true' or 'false'. true means that the ODE build
environment should be used.
.LE
.H 2 "Source Control Configuration File"
.iX "sc.conf"
.iX "source control" "configuration"
.iX "configuration files" "sc.conf"
The source control configuration file, \fIsc.conf\fR is
only necessary if you are using the ODE source control component.
It is needed so that developers can check-in, check-out, and otherwise
manipulate source control files which are actually kept on another system.
.P
You will need to create two identical sc.conf files. This need will be
removed in a future release. The sc.conf file resides in the
\fBrc_files\fR/<project> directory
of the backing build and a build specific directory in the
source control server tree. The directory in the source control server tree
is \fBode2.3.4_server_base/sets/\fR<\fIdefault_set\fR>. 
See below for information on naming the default set.
.P
The sc.conf file must contain the following entries:
.iX "submit_host"
.iX "source_host"
.iX "rcs_host"
.iX "rcs_relay"
.iX "oxm_relay_tcp"
.iX "tcp_service_number"
.iX "logs_relay"
.iX "src_relay"
.iX "copyright_list"
.iX "check_copyrights"
.iX "copyright_years"
.iX "copyrights file"
.iX "default_build"
.iX "default_set"
.iX "check_out_config"
.iX "submit_defect"
.iX "cr_validate"
.iX "lock_dirs"
.iX "locking"
.iX "exclusive file locking"
.iX "COMMENT_LEADERS"
.iX "comment leaders"
.VL 15
.LI \fBsubmit_host\fR
This variable indicates the machine where the build logs are actually kept.
At OSF it is one of the Release Engineering servers.
.LI \fBsource_host\fR
This variable indicates the machine where the build sources are actually kept.
At OSF it is one of the Release Engineering servers.
.LI \fBrcs_host\fR
This variable gives the name of the system rcs is running on; it does not
have to be the same as the system the builds are on.
If OSF's source control is being used, \fBrcs_host\fR needs to be specified.
.LI \fBrcs_relay\fR
The relay program to use for communicating with odexm on the rcs server.
This will usually be oxm_relay_tcp.
.LI \fBsrc_relay\fR
The relay program to use for communicating with odexm on the source server.
This will usually be oxm_relay_tcp.
.LI \fBlogs_relay\fR
The relay program to use for communicating with odexm on the source server.
This will usually be oxm_relay_tcp.
.LI \fBtcp_service_number\fR
Optional entry which sets the tcp service number that oxm_relay_tcp should
use to communicated with odexm. If this is not set, the value of SERV_NUM
in the oxm_relay_tcp.c file will be used.
.LI \fBcopyright_list\fR
This variable enables the use of alternative copyright markers to be
accepted by the \fBbci\fR program.  When copyright markers are used
in a backing tree, \fBbci\fR will normally recognize 
the OSF_COPYRIGHT or OSF_FREE_COPYRIGHT markers.  Additional copyright 
markers can be recognized by adding the markers to this list.
The copyright list should be a semicolon-separated list (enclosed in 
double quotes)
of copyright strings and/or files containing copyright strings preceded 
by 'include'.  A valid copyright string must contain the string 'COPYRIGHT'.
For example, "OSF_COPYRIGHT;include /project/othercopys;YOUR_COPYRIGHT_TOO"
The format of the file \fI/project/othercopys\fR is one copyright string per 
line. Keep in mind that there are now two ways in which copyrights are treated.
Using copyright markers is the old way and will be phased out over time.
Copyright markers will be replaced with expanded copyrights within the source 
files. 
.LI \fBcheck_copyrights\fR
This is used in conjunction with expanded copyrights.
When set to 'true' check for fully expanded copyrights at bci & bsubmit
time, and add full
copyrights to newly bcreated files from the copyrights file. See the
description of the copyrights file below.
.LI \fBcopyright_years\fR
This is used in conjunction with expanded copyrights.
The string to expand @YEARS@ to when inserting copyrights from the copyrights
file into newly bcreated files.
.LI \fBproject_name\fR
Same as the \fBproject_name\fR in the \fBBuildconf\fR file.
.LI \fBdefault_build\fR
This variable is the name of the build submissions are made to.
.LI \fBdefault_set\fR
Submissions require the name of the default set to submit to.
Since there is normally only one set associated with any build, this
variable should contain the name of that set.
It is important that this name be in ALL capital letters.
.LI \fBsubmit_defect\fR
This variable is used to toggle the defect query in submissions.
If the value is \fBtrue\fR, \fBbsubmit\fR will ask the user for a
defect number to associate with the submission.
Otherwise, it will not prompt the user for this information.
.LI \fBcr_validate\fR
Sets the validation level for the defect query. Levels are: \fBany\fR,
\fBstrict_or_space\fR, or \fBstrict\fR. \fBany\fR is the default and will
be used if there is no entry for \fBcr_validate\fR. \fBstrict_or_space\fR
is the same as \fBstrict\fR, but whitespace is allowed. \fBstrict\fR requires
the cr field to consist of cardinals > 0 separated by commas. Whitespace is
permissible, but there must be at least one cr # entered.
.LI \fBcheck_out_config\fR
Because the OSF source control retrieves the correct file revision
using a set name and/or by date, it is necessary to
establish the order of search.
This variable defines the search order with a semi-colon separated list of
set names and dates.
It usually gives the default set name followed by 
an \fBinclude\fR of the \fBCONFIG\fR file (see subsequent section).
.LI \fBlock_dirs\fR
This variable governs exclusive file locking. When it is present, exclusive
file locking is on. If it is not present exclusive file locking is off.
The value is a semicolon separated list of directories and/or files to lock.
At bco time, any file that matches the pattern of one of the lock_dirs
entries will be added to a list of files that are locked. This list is kept
in the bsubmit.hold file. Exclusive file lock entries are prefaced by a "::"
as opposed to the hold file entries which are prefaced with a ":". If a
person tries to bco a file which already has a "::" entry, that person will
be prevented from checking out the file.
.LI \fBCOMMENT_LEADERS\fR
This is the list of default comment leaders to use with various file types.
The format is:
"(<file_pattern>;<comment_leader>)..."
See the man page for match(3) for details on ODE's pattern matching.
.LE
.P
.iX "copyrights file"
.iX "sc.conf"
.iX "check_copyrights"
.H 2 "copyrights file"
The file 'copyrights' lives in the backing build with the sc.conf file. This
file is used when check_copyrights is set to 'true' in the sc.conf file.
.P
.iX "COPYRIGHT NOTICE"
.iX "default copyright"
.iX "copyright" "default"
The copyrights file is a concatenation of all of the legal (literally!)
copyrights for a project. Each copyright entry consists of a header and a body.
The header is a single line starting with 'COPYRIGHT NOTICE' followed by
the name for the copyright. There must be at least one copyright entry and
there must be one and at most one entry named 'DEFAULT'. An example of
a copyright header is:
.P
COPYRIGHT NOTICE DEFAULT
.P
The copyright body consists of one legal copyright and may take as many lines
as necessary.
.P
The body may contain the string '@YEARS@'. When bci and bsubmit are checking
a file for legal copyrights, the string '@YEARS@' will match any comma
separated list of numbers.
.P
Here is an example copyrights file:
.P
.nf
---cut---
COPYRIGHT NOTICE DEFAULT
Copyright (c) @YEARS@ Open Software Foundation, Inc.
ALL RIGHTS RESERVED
COPYRIGHT NOTICE BORING
Copyright (c) 1993, XYZ Software Associates
Please do not distribute our software for free. We worked on it really hard.
If you find a bug, please fix it and send us the patch.
---cut---
.fi
.P
The copyrights in source files are compared to the copyrights defined
in the backing tree as follows.  A legal copyright in a source file has 
the following format:
.nf
<comment leader>COPYRIGHT NOTICE
<comment leader>copyright text...............
<comment leader>copyright text...............
<comment leader>copyright text...............
<comment leader>copyright text...............
<comment leader>copyright text...............
<end-of-copyright>
.fi
.P
ODE recognizes the end of a copyright section of a source file in 
one of two ways.

1) A '<comment leader>HISTORY' marker is found.
.P
For example:
.P
.nf
# COPYRIGHT NOTICE
# Copyright (c) 1992 Open Software Foundation, Inc.
# ALL RIGHTS RESERVED
#
# HISTORY
.fi
.P
This example states that all lines between COPYRIGHT NOTICE and
HISTORY are copyrights to be verified against the 'copyrights' file.
There may be multiple copyrights, however, each one will be verified
against the list defined in the backing tree.
This behavior allows users to make sure that all copyrights  in the 
source file are legal copyrights.
.P
2) A line containing any text that DOES NOT START with a comment leader.
.P                
For example:
.nf
# COPYRIGHT NOTICE
# Copyright (c) 1993, XYZ Software Associates
# Please do not distribute our software for free. We worked on it really hard.
# If you find a bug, please fix it and send us the patch.
#
Any other text
# Copyright (c) 1992 Brockport State University
# All Rights Reserved.
# HISTORY
.fi
.P
This example states that all lines between "COPYRIGHT NOTICE"
and "Any other text" are copyrights to be verified in the
'copyrights' file.  The copyright from Brockport State 
University is ignored.  This allows users to add copyright
notices (or any other text) that need not be verified
with the list of legal copyrights.

.H 2 "Distributed Access Setup"
.P
If you are not using the ODE source control component, you may want to 
test out your system up to this point.  For instance you might want to
try using the \fBmksb\fR or \fBbuild\fR commands.  Refer to Chapter 7
for more information about testing out your system.
.P
.H 3 "The CONFIG File"
The \fBCONFIG\fR file is required in all builds if using the ODE source 
control component.
This file provides the source control tools with the 
information on which revision of a file to check out.
It does this using a date set to the time the build was created.
The time should be set after all file versions for the build have
been determined.
The revision of the file to check-out is the revision closest to the
date without being greater than it.
.P
The format of the date is:
.sp
.ti 2
\fB<\fIYYYY\fB/\fIMM\fB/\fIDD\fB,\fIHH\fB:\fIII\fR
.P
where \fIYYYY\fR is the year, \fIMM\fR the month, \fIDD\fR the date, \fIHH\fR the hour, \fIII\fR the minute.
The "<" symbol is necessary as are the comma and colon.
This file needs to be directly under the build in:
.sp
.ti 2
\fI/base_dir/build_name\fB/CONFIG\fR
.P
.H 3 "Making the build accessible via odexm"
.iX "odexm.conf"
.iX "/etc/odexm.conf"
.iX "configuration files" "odexm.conf"
In order to allow users to submit to a dynamic backing build, you will need
to set up odexm and/or add two entries to the odexm.conf file in the /etc
directory on the build server. You will need an entry for the src directory
and the logs
directory. In both cases, the owner should be the same. At OSF it is devsrc.
Refer to Chapter 4 for detailed instructions on how to set up odexm and
add entries to odexm.conf .
.H 3 "Tools needed by odexm for builds"
There are two remote execution programs which need to be
available (installed) on each machine that uses ode tools for sandboxes.
These are installed by default in \fB/usr/ode/server\fR (see chapter 3):
.P
.BL
.LI
\fBlogsubmit\fR
.LI
\fBsrcacl\fR
.LE
.P
Install these tools in an appropriate tools directory. This should be
in one central place on a machine, such as \fB/usr/ode/server\fR, or
/usr/ode2.3.4tools.
Make sure that
the tools directory in the odexm.conf file refers to the directory containing
these tools.
.H 2 "Compiling a Backing Build"
Once there is a fully populated source directory and all the support
files are in place, at least some of the sources need to be built.
How much depends on the project's needs.
If nothing else is built, at least those files which need to be exported
must be compiled and put in the export directory.
See the ODE User's Guide for more information about the
export directory.
In some cases, the entire source directory is built so the object
directory is completely populated.
One reason for doing this would be to provide targets for the ODE command
\fBmklinks\fR which links files in the backing build to the sandbox.
.P
If building an OSF offering, the \fBOSF Release Notes\fR will explain
how to build and export the sources.
.P
If the project is not from OSF, you will need to compile the
build as appropriate making sure the export directory is completely filled.
Optionally, you may also populate the object directory.

.H 2 "Creating the build_list file"
It is possible
to provide a \fBbuild_list\fR file which allows users the shorthand
of giving only the name of the build as command line options.
The file can be set up using a project-independent pathname and made
available to all users.  For example, at OSF the file is located in 
\fB/project/projects/build_list\fR.
This file is read to provide the tools the additional information they need.
.P
The file has one line for each build.
The format of each line is:
.sp
.ti 2
\fBbuildname \ \ configinfo \ \ basedirectory\fR
.P
where each entry is separated by a tab.
The buildname is simply the name of the build directory.
The config info usually contains the build's source control label
followed by the date found in the \fBCONFIG\fR file,
described below in the section on \fBSubmission Setup\fR; and the base
directory is the path to the build name.
.P
An example line from OSF is:
.sp
.ti 2
\fBdce1.0b2 \ \ DCE1_0;<1990/12/11,16:00 \ \ /project/dce/build\fR
.P
A shorthand way of specifying the \fBconfiginfo\fR is to use a "*" for
the middle field.
This indicates that the CONFIG info from the build should be used.
.H 2 "Populating the src Directory"
If the project is not using ODE source control, the \fBsrc\fR directory
should be populated in a manner appropriate for the set of tools being
used.
.P
If the project is using ODE source control, this should be done
by checking all the files out, unlocked, into a directory.
The files must be owned by the special source user,
\fBdevsrc\fR at OSF, as defined in the odexm.conf file for the src directory
If the files are not owned by this special user, the source control
commands will not work.
However, if you are using the straight \fIrcs\fR command \fBco\fR, as shown
in the following subsections, you will have to run the command as the
rcs tree owner (\fBdevrcs\fR at OSF) and then change the ownership of the
files to the source owner.
.P
The files can be checked-out a number of ways including using the
ODE command \fBbco\fR, or by mounting the
rcs tree on the build's system and use \fBco\fR directly.
.H 3 "Creating a SNAPSHOT file"
.SP
.P
Before you check out the files, you need to create a list of the files
and version numbers that you wish to check out.
This file is called the SNAPSHOT file and contains the list of every file and
its
revision number in the submission build.
You may want to put this file in a static backing build as well, just
to have a reference list of the files comprising the build.
You should move the SNAPSHOT file that you used to check out your
sources into the \fBlogs\fR directory.
To create a \fBSNAPSHOT\fR file that represents the most recent trunk revision
of the files in the rcs tree, use the following command from the build 
directory (one level above the \fIsrc\fR directory):
.sp
.ti 2
\fBcd /\fIbuild-tree\fR
.ti 2
\fB(cd /\fIrcs-tree\fP; find . -name "*,v" -print | \\
.ti 2
rcsstat -q -R -V -r"<>" - ) | sort > SNAPSHOT\fR
.P
Note that the \fIrcs\fR commands must be installed and in your command 
search path.
.sp
.H 3 "Checking Out Sources from the rcs Tree"
.SP
.P
To check out the top of the
trunk you would run the following commands from the \fBsrc\fR directory in
the build to create the necessary
directories and then checkout the sources as listed in the SNAPSHOT file:
.sp
.ti 2
\fBcd /\fIbuild-tree\fB/src\fR
.ti 2
\fBcat ../SNAPSHOT | sed 's;,v.*;;' | awk '{print "makepath "$0}' | sh -x\fR
.ti 2
\fBcat ../SNAPSHOT | sed 's;^\\./\\(.*\\),v\fI<tab>\fP\\(.*\\);co -u\\2 /\fIrcs-tree\fP/\\1,v \\1;'  | sh -x\fR
.sp
.P
As mentioned earlier, these commands must be run as the \fBrcs_owner\fR,
\fBdevrcs\fR at OSF, in order to access the rcs tree directly.  
Once the files have been checked out, their ownership should be changed 
back to the \fBsource_owner\fR, \fBdevsrc\fR at OSF.
Note that the ODE command \fBmakepath\fR is used to create the 
directories.  Make sure that in the second \fBsed\fR command a tab
follows the \fB,v\fR.
.H 2 "Subsequent Builds"
.P
Backing trees can be used to reflect the sources at a 
specific point in time (e.g. a baseline) or
reflect the current state of the sources under development.  
Periodic full builds of the software under development are helpful in 
identifying integration problems.  
After a certain amount of changes have gone into a build it is often
desirable to preserve that build in it's current state and create a 
new build in which the sources will continue to change with ongoing
development.
.P
A separate copy of the sources (and tools) should be used for the new build.  
The SNAPSHOT file, which is updated automatically with each \fBbsubmit\fR, in 
the backing tree can be used to quickly 
capture the entire set of sources in a backing tree.  
This file contains a list of all files and version numbers that define
the sources at a certain point in development.  
.P
Builds are done by first copying the SNAPSHOT file to a 
build machine, checking out the sources represented by the SNAPSHOT file,
and then following the build procedures used in
your specific project.
See Chapter 3 for more information on tailoring the build environment.
