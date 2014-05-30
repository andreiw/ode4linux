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
.\" $Log: distribution.mm,v $
.\" Revision 1.2.8.3  1995/05/22  22:08:39  robert
.\" 	last fix up for release
.\" 	[1995/05/22  22:06:56  robert]
.\"
.\" 	Fix up directory structure after proofread.
.\" 	[1995/05/22  21:48:24  robert]
.\"
.\" Revision 1.2.8.2  1995/05/22  19:45:00  robert
.\" 	Update directory structure to show oodexm client, sadmin,
.\" 	where to plug in source control (if used), sup commands
.\" 	and libraries (now that sup upses no_crypt.c), and libcom.
.\" 	[1995/05/22  17:11:48  robert]
.\" 
.\" Revision 1.2.8.1  1995/05/20  01:44:39  robert
.\" 	Update to reflect distribution by (anonymous) ftp.
.\" 	[1995/05/20  01:41:12  robert]
.\" 
.\" Revision 1.2.6.1  1993/08/26  13:52:56  marty
.\" 	CR # 628 - Update to ODE 2.3
.\" 	[1993/08/26  13:52:37  marty]
.\" 
.\" Revision 1.2.2.4  1992/12/03  19:09:24  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:40:53  damon]
.\" 
.\" Revision 1.2.2.3  1992/11/18  16:26:17  damon
.\" 	CR 332. Updated for 2.2
.\" 	[1992/11/18  16:25:32  damon]
.\" 
.\" Revision 1.2.2.2  1992/03/18  17:52:41  damon
.\" 	Updated to reflect new build procedure re: SETUP_ALL
.\" 	[1992/03/18  17:51:55  damon]
.\" 
.\" Revision 1.2  1991/12/05  21:00:03  devrcs
.\" 	put in numbers for Mb of src, revised directory structure
.\" 	[1991/11/06  18:40:59  hester]
.\" 
.\" 	aligned comments on directory structure listing
.\" 	[91/10/18  14:39:12  hester]
.\" 
.\" 	added unloading tape section from chapter 3
.\" 	[91/07/29  16:33:46  hester]
.\" 
.\" 	updated directory structure description for new sag
.\" 	[91/07/26  15:26:38  hester]
.\" 
.\" 	first take at revisions for SAG update
.\" 	[91/05/03  16:56:35  hester]
.\" 
.\" 	Initial Chapter 2 of SAG
.\" 	[91/01/25  18:58:19  hester]
.\" 
.\" $EndLog$
.\"
...\"*********************************************************************
...\"          Set page information
...\"*********************************************************************
.EH "'\s10\\\\nP''\fBChapter 2: ODE Distribution\s0\fR'"
.OH "'\fB\s10Chapter 2: ODE Distribution\fR''\\\\nP\s0'"
.SK
...\"*********************************************************************
...\"          Contents of ODE/AG: ODE Distribution
...\"*********************************************************************
.H 1 "ODE Distribution" 
This chapter discusses how to unload the OSF Development Environment (ODE) 
from the distribution media and shows 
the organization of the sources as they appear on the media.
.P
In addition to the source code for all the tools, the ODE distribution
includes scripts for installing and maintaining the system, man pages
and documentation.

.H 2 "Unloading the tape"
.P
The ODE build tree is distributed on the same media that your OSF
offering is on.  Consult the release notes which came with the
offering to determine how many archives are on the tape and which one
is the ODE archive.

.H 3 "Requirements for Unloading the tape"
.P
The ODE source code and documentation when unloaded off from the tape will 
require approximately 6 megabytes of disk space.

.H 3 "Instructions for Unloading the tape"
.P
To install all of the ODE sources from the distribution tape, follow
these steps:
.P
1. Make sure that there is enough disk storage space available for the
data to be unloaded from the tape.  Use the \fBdf\fR command or whatever
command is appropriate  for your operating system to determine the
amount of free space on your disks.
.P
2.  Mount the tape in accordance with site-specific and operating-system
specific procedures.
.P
3. Change directories to where you want to store the ODE source code.
.P
.ti 2
\fBcd /\fIode-path\fR
.P
In the instructions in this chapter the path to the ode directory is
indicated by \fB/\fIode-path\fR\fR.
.P
4. If this is an ODE distribution available via (anonymous) ftp, then 
instructions about where to find and unload the appropriate tar archives 
should be available directly on the server (e.g.,  README files).  
Announcements and mail messages sent to \fBode-info@osf.org\fR will also 
contain informative and up to date information about the whereabouts of the 
most recent ODE sources. 

If this is an ODE tape release, then
make sure your tape is positioned at the beginning of the ODE
archive.  Use the \fBmt\fR, or equivalent, command to  skip forward and backward
past other archives on the tape as needed.
.P
5. Use \fBtar\fR to unload the ODE archive.
.P
.ti 2
\fBtar xvfp /dev/\fInon-rewinding-tape-device\fR
.P
If the \fBtar\fR completes without errors, proceed to the next section on
building ODE.

.H 2 "The ODE Directory Structure"
.DS
     src/ode/bin/			o Sources to all of the ODE commands
                bci/	
                bco/	
                bcreate/	
                bcs/	
                bdiff/	
                blog/	
                bmerge/	
                bstat/	
                bsubmit/
                build/	
                currentsb/
                genpath/
                make/
                        AIXARCH/
                        BSDARCH/
                        OSFARCH/
                        SVR4ARCH/
                        doc/
                        lst.lib/
                makepath/
                md/	
                mklinks/
                mksb/
                odexm_cli/
                rcs/			o Plug in Source Control Tree (RCS)
                release/
                resb/
                sadmin/
                sbinfo/
                sup/
                upgrade/
                uptodate/
                workon/

     src/ode/doc/		o ODE documentation
                users.gd/
                        common/
                        osc/
                        dce/

                sag/	
                        templates/

     src/ode/server/			o Server side of tools
		bco_s/
		bcs_s/
		blog_s/
		bmerge_s/
		branch_ci/
		bstat_s/
		bsubmit_s/
		logsubmit/
		odexm/
		rcsacl/
		srcacl/
		supfilesrv/
		supscan/

     src/ode/lib/			o Some access control cmds and libode
                libcom/
                libode/		
                libsup/

     src/ode/man/		o Man pages
                man1/
                man3/
                man5/
                man8/

     src/ode/include/		o Global header files

     src/ode/setup/		o Scripts to build and install ODE

     src/ode/mk/			o Common Makefiles
.DE
