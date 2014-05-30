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
.\" $Log: sandbox.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:13:32  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:42:53  damon]
.\"
.\" Revision 1.2  1991/12/05  20:58:05  devrcs
.\" 	Kill multiple occurrence of Endlog, HISTORY, or copyright header
.\" 	[91/02/04  17:49:00  robert]
.\" 
.\" 	Separating DUG into common and OSC versions
.\" 	[91/01/16  17:03:49  randyb]
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
...\"          Contents of OSC DUG: Sandboxes
...\"*********************************************************************
.H 1 "Sandboxes"
There is very little specific information regarding OSC sandboxes
different from the sandbox information common to other ODE projects.
The reader should use the common DUG to learn about and reference
sandboxes, using this chapter to provide specific information on
the location of builds, tools, etc.

.H 3 "Sandbox Structure"
.P
\fBmksb\fR prompts the users for the name of machine types to build for.
The most common names in OSC within OSF are:
.BL
.LI
pmax
.LI
mmax
.LI
at386
.LE
.P
The user can also enter these machine names using the \fB-m\fR option.

.H 3 "Creating a Sandbox"
Within OSF,
the OSC uses the following naming conventions for builds to back sandboxes:
the default build, formerly called \fBlatest\fR, is now called
\fBoscR.R\fR where R.R is the revision number, 1.0, 1.0.1, 1.1, 2.0, etc.
This allows there to be more than one build to submit to.
Each build associated with a particular default build starts
with the same naming convention and has the prefix \fBbN\fR where
N is the number of the build.
.P
Developers should expect to see builds with names like osc1.1b4,
osc1.0.1b3, and osc2.0b25.
When a project is set up, it needs to decide upon one place to put all
its builds.
The location is set in the rc files in the variable \fBbuild_base\fR.
At OSF, all OSC builds need to be accessible under:
.sp
.ti 2
\fB/project/osc/build\fR
.P
on the developer's system.

.H 3 "Retargeting a Sandbox"
.P
Developers can remain backed by the same build or sandbox until
that environment is too far behind the default build
to permit effective development,
at which time the sandbox needs to be retargeted.
Within OSF, the number of available builds varies depending on the release,
but for the most current release Release Engineering keeps
four OSC builds on line plus the nightly build of the default build.
One of the four builds may be a security build.
.P
This means that if the builds are done weekly, a developer must
retarget his sandboxes at least once a month.
If the developer chooses to be backed by the default build,
this is not necessary, however, most OSC developers have found
the default build too unstable to remain permanently backed-by.

.H 2 "Multiple Backing Trees"
Multiple backing trees were not available in 1.0 ODE.
For most OSC developers, multiple backing tree are still not necessary.
However, using them can make other projects of interest such as
the documentation and ODE itself available in the sandbox.

.H 2 "Setting the Sandbox Environment"
Since each site will need to determine its own environment, the
information in this section only applies within OSF.
.H 3 "Accessing the Builds"
The easiest way to access the OSC builds is to mount them using:
.sp
.ti 2
.B "osfmount osc build"
.P
This command mounts the builds under \fB/project/osc/build\fR
which is where they need to be located.
.P
It is not necessary for the developer to use "osfmount",
but it is necessary for the builds to show up in \fB/project/osc/build\fR.
All OSC ODE tools will search for builds using this path;
if the developer would rather symbolically link builds underneath
/project/osc/build or use another method for mounting,
that is perfectly acceptable, but the build must show up there.
.P
Another directory that should be mounted by OSC developers is
\fBserver2:/u0/projects\fR.
This should be mount on \fB/project/projects\fR.
Developers can use
.sp
.ti 2
.B "osfmount ode projects"
.P
to put this in place.
The file in this directory, normally  \fBbuild list\fR contains the
list of builds, configuration information, and
the base directories for all the builds, not just those in the OSC.
It allows users the shorthand of entering just \fIname\fR as an
argument to the tools instead of having to give the entire path.
It also is used by the \fBbco -from\fR option to locate the appropriate
revision to check-out if the build is no longer on line.
.H 3 "Environment Variables"
To get access to the ODE tools, developers need to mount them from
server2.
For example:
.sp
.ti 2
\fBmount server2:/u0/release/\fImachine\fB/ode /usr/ode\fR
.P
This is a release area and can be sup'ed (see chapter 5) or copied or
left mounted.
.P
The directories under ode include \fBbin\fR, \fBnewbin\fR, \fBlib\fR,
\fBetc\fR, and \fBman\fR.
Since the man pages are available from other sources, most developers
will only be interested in bin and newbin.
lib and etc contain ODE administration programs.
At least bin and maybe newbin need to be in the developer's \fBPATH\fR
environment variable and fairly close to the first so ODE versions of
tools like \fBmake\fR are accessed before other versions.
.P
As with the location of the build, it does not matter how the tools are
accessed just as long as they are.
The tools can be mounted anywhere, and they can be accessed directly or
through links.
One way to do this would be to follow the X11 model. 
In that model ode would be mounted under /usr/ode and a symbolic link
would be made from /usr/bin/ode to /usr/ode/bin.
\fBPATH\fR would then be set with:
.sp
.ti 2
\fBsetenv PATH /usr/bin/ode:$PATH\fR
.P
Whenever a new revision of a tool comes out, it is place under
\fBode/newbin\fR.
It remains there for a week so developers can help test it;
after which, if there have been no problems, it is moved to \fBode/bin\fR.
In these cases it is necessary to set \fBPATH\fR to include newbin
before bin.
.P
Finally, there are occasionally times when a build-specific tool is needed.
These are kept under each build in \fBtools\fI/machine\fB/bin\fR and
are best accessed through the sandbox link so, if the sandbox is retargeted,
\fBPATH\fR is still set correctly.
Putting all these together, the complete \fBPATH\fR would look like:
.SP
.ti 2
\fBsetenv \  PATH \  /\fIsandbox\fB/link/tools\fI/machine\fB/bin:/usr/ode/newbin:
.ti 4
/usr/bin/ode:$PATH\fR
.P
\fBPATH\fR can also be set inside the start-up script for the shell.
This makes it convenient to use another ODE variable, $SANDBOX, as
part of the \fBPATH\fR.

.H 2 "Tutorial: Sandboxes"
This section fills in some of the details left out of the common DUG
tutorial on sandboxes.
Like the section on setting the environment above, it is OSF site
specific.
Outside users will need to get this information from their ODE
system administrator.
.AL 1
.LI "Step" X
For project OSC it is necessary to mount the build directories:
.SP
.ti 6
.B "osfmount osc build"
.P
As stated above, there are other ways to do this, but it is necessary
the tools be able find the builds under \fB/project/osc/build\fR.
This step will only need to be repeated when the workstation is rebooted.
.LI "Step" X
As described above, the ODE tools need to be mounted, as well as
\fBprojects\fR, and \fBPATH\fR needs to be set to find the ODE tools early
on in its search.
.P
.ti 6
\fBosfmount ode\fR
.ti 6
\fBosfmount ode projects\fR
.ti 6
\fBsetenv PATH /sandboxes/suzieq/${SANDBOX}/link/tools/pmax/bin:\fR
.ti 8
\fB/usr/ode/bin:$PATH\fR
.P
This step insures that the proper set of tools is used in creating binaries.
.LE
