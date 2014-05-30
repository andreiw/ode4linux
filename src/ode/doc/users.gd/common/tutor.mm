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
.\" HISTORY
.\" $Log: tutor.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:11:42  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:59  damon]
.\"
.\" Revision 1.2  1991/12/05  20:57:04  devrcs
.\" 	Expanded, more formatting
.\" 	[1991/11/27  01:05:54  damon]
.\" 
.\" 	First version of separate tutorial
.\" 	[1991/11/27  00:04:00  damon]
.\" 
.\" $EndLog$
.ad b   \"*** Resets justification
.PH "'''"                       \"*** Prevent page header
\"***.PF ""                             \"*** Prevent page footer
.ds HF 3 3 3 3 3 3 3            \"*** Set heading fonts; bold bold italic
.ds HP 20 16 14 12 12 12 12     \"*** Set heading point sizes
.nr Hb 4                        \"*** Headings to level 3 begin new line
.nr Hs 3                        \"*** 1/2 vertical space after headings
.OH "'''\fIODE Tutorial\fR"
.EH "'\fBSandboxes\fR'''"
.nr N 5
.nr P 0                                 \"*** reset page number to page 1
.af P 1                                 \"*** reset page number to Arabic
.nr Hs 4
.SK
.H 1 "Sandbox Commands"
.H 2 "Setting Up an ODE Environment"
.P
Usually, the ODE tools are located in /usr/ode/bin. This may be different at
your site. Wherever the tools are located, you will need to have them in
your path:
.P
set path=( /usr/ode/bin $path)
.P
You will also need to have access to a legal build. For instance, if you 
are going to work on the dce1.0.1 build, make sure that
/project/dce/build/dce1.0.1 is mounted.
.P
.H 2 "Working with Sandboxes"
.H 3 "The mksb Command"
.P
The first time you create a sandbox, \fBmksb\fR will collect information that it
will use when creating the first and all future sandboxes. After you have
created your first sandbox, you will only need to tell \fBmksb\fR which backing
build you wish to use for the new sandbox.
.P
When creating a sandbox, you can either give \fBmksb\fR all of the information it
needs on the command line or let \fBmksb\fR prompt you for it.
.P
For simplicity, we will let \fBmksb\fR prompt for the information it needs.
.P
.AL
.LI
.ti 4
.B "mksb dcework"
.P
.LI
.ti 4
Look at the .sandboxrc file that mksb has created:
.P
.ti 4
.B "more ~/.sandboxrc"
.P
Notice the lines that start with \fBmksb\fR. Many of the ODE tools read
the .sandboxrc file for default command line options. When you run \fBmksb\fR
again,
it will use the default command line options in your .sandboxrc file as
well as the 'default' and 'base' variables.
.P
.LI
.ti 4
You can have as many sandboxes as you wish. Make two more sandboxes. Call
them dcework2 and dcework3. Use the same backing build as before.
.P
.LI
.ti 4
Look at your .sandboxrc file again. Notice that two 'sb' lines have been
added.
.P
.LE
.H 3 "The workon Command"
Once you have created a sandbox, you can begin doing work in it. The
\fBworkon\fR
command starts a new shell and sets up your environment for the sandbox you
want to use. If you don't tell \fBworkon\fR which sandbox to use, it will assume
that you want to use the default sandbox from your .sandboxrc file.
.P
Look at your environment before using \fBworkon\fR:
.P
.B "printenv"
.P
.B "workon"
.P
Look at your new environment.
.P
The WORKON variable tells you how many workons deep you are.
.P
workon puts you in the 'src' directory of your sandbox. The actual base of
the sandbox is up one level in the directory hierarchy:
.P
.B "ls .."
.P
Since the workon command starts a new shell, it is easy to leave a sandbox:
.P
.B "exit"
.P
To begin work in a specific sandbox, use the -sb option:
.P
.B "workon -sb dcework2"
.P
Exit the dcework2 sandbox:
.P
.B "exit"
.H 3 "Building in a Sandbox"
One of the major advantages of building in a sandbox is that you don't have
to have all of the source files present for a target in order to build
that target.
.P
mkdir -p ode/tutorial
.P
cd ode/tutorial
.P
build
.P
The object files are in the object directory of the sandbox:
.P
ls ../../../obj/<platform>/ode/tutorial
.H 2 "Introduction to Source Control"
All of the files in the backing tree have corresponding RCS files. Status
type information can be obtained with the blog command:
.P
blog Makefile | more
.P
When you want to make changes to files, or add new files, you can use the
source control commands. For instance, let's say you want to add a module
to the hello_world program. First, you will need to check out the Makefile:
.P
bco Makefile
.P
You now have a copy of the Makefile in your sandbox and a private branch
in the corresponding RCS file.
.P
ls
.P
blog Makefile | more
.P
Notice that you now have a lock on your private branch as well as a symbolic
name associated with that branch. The latest branch is not locked.
.P
Change the OFILES line in the Makefile to read:
.P
OFILES	=	hello_world.o <your uid>/subrs.o
.P
Create a subdirectory with your uid as its name. Move to that subdirectory
and create the subrs.c file:
.P
.fi
mkdir <your uid>
cd <your uid>
bcreate subrs.c
.nf
.P
Normally, files are not stored in directories named after uids! This is only
being done so that later on your submission won't conflict with anyone else's.
.P
Every file which has a comment leader must have a copyright marker and
RCS history header. Add the following lines to subrs.c:
.P
.nf
/*
 * @OSF_FREE_COPYRIGHT@
 * COPYRIGHT NOTICE
 */
/*
 * HISTORY
 * $Log: tutor.mm,v $
.\" Revision 1.2.2.2  1992/12/03  19:11:42  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\" 	[1992/12/03  18:41:59  damon]
.\"
.\" Revision 1.2.1.2  1992/12/03  18:41:59  damon
.\" 	ODE 2.2 CR 346. Expanded copyright
.\"
.\" Revision 1.2  1991/12/05  20:57:04  devrcs
.\" 	Expanded, more formatting
.\" 	[1991/11/27  01:05:54  damon]
.\"
.\" 	First version of separate tutorial
.\" 	[1991/11/27  00:04:00  damon]
.\"
.\" Revision 1.1.2.3  1991/11/27  01:09:57  damon
.\" 	Expanded, more formatting
.\" 	[1991/11/27  01:05:54  damon]
.\"
.\" Revision 1.1.3.2  1991/11/27  01:05:54  damon
.\" 	Expanded, more formatting
.\"
 * $EndLog$
 */
.fi
.P
We also want to put a function in subrs.c that will be used by hello_world.c:
nice_day ( )
.nf
{
  print ( "Have a nice day!\n" );
}
.fi
.P
Go back and change the hello_world.c program to call nice_day.
.P
Build hello_world
.P
When hello_world is building without any errors, check in your subrs.c
file:
.P
bci subrs.c
.P
Press <Enter> to enter a log. Use whatever you want for the log message.
.P
At the [check-in] prompt, press <Enter>.
.P
Your file has now been checked in to your local branch. Check the status
of the file with blog.
.P
If you just want to see the header of the blog report you can use:
.P
blog -h subrs.c
.P
Notice that the file is now read only, to remind you that you shouldn't
work on a file that isn't checked out:
.P
ls
.P
Later on, when you submit this file, it will use the most recently checked-in
file and not the file in your sandbox. Thus, if you edit a checked-in file,
you will lose any changes you make!
.P
You can check a file out and in as many times as you want to. This is
usually done at milestone points so that old work can be retrieved for
comparison.
.P
bco subrs.c
.P
Add another printf statment to subrs.c
.P
bci has command line options which can take the place of the interactive
prompts:
.P
bci -auto -m'<Log message>' subrs.c
.P
.H 3 "Introduction to File Submission"
Once you have made all of the changes you want to make and have tested your
changes, you are ready to submit your files. When you submit your files,
your changes become visible to all other developers using the build you
submitted to.
.P
The answers for the prompts follow. Submit subrs.c:
.P
bsubmit subrs.c
.P
Answer the following questions as given:
.P
.(O
Enter you full name for the log: [<your name>] <Return>
.)O
.P
Exit the editor without making any changes.
.P
.nf
.(O
Outdate the submitted files from set: <your uid>_dcework?
Answer: [<y>|n] <Return>
.)O
.fi
.P
.H 2 "Merging"
Merging is required when some one submits to a file between the time
you check it out and submit it.
We can simulate this by having you use
two sandboxes.
There are two ways to deal with this issue.
You can do the merge work within bsubmit, or you can do the merge work
outside of bsubmit.
.H 3 "Merging Within bsubmit"
.P
Check out subrs.c
.P
Add another printf to subrs.c
.P
Check in subrs.c
.P
Work on the dcework2 sandbox:
.P
workon -sb dcework2
.P
Check out subrs.c
.P
Add a different printf to subrs.c
.P
Check in subrs.c
.P
Submit subrs.c
.P
Exit the dcework2 sandbox:
.P
exit
.P
The version of subrs.c in this sandbox was checked out prior to the
submission you just did. If you then submitted this version without doing
any merging, the changes from the earlier submission would be lost.
Therefore, bsubmit detects these situations and requires you to merge
the two versions.
.P
Submit subrs.c
.H 3 "Merging Outside of bsubmit Using bmerge"
Repeat the steps used to create two versions of a file, one in each of
two sandboxes.
.P
.H 2 "Removing Unwanted Work"
.H 3 "Removing Sandboxes"
Although you can have as many sandboxes as you want and individual sandboxes
are relatively cheap, you may sometimes want to remove sandboxes. This
is done by using the -undo option of \fBmksb\fR. Note that -undo will only work
when you have no files checked out into your sandbox.
.P
mksb -undo dcework3
.P
.H 3 "Undoing a check-ou"
.H 3 "Deleting checked-in work"
