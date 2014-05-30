/*
 * COPYRIGHT NOTICE
 * Copyright (c) 1992, 1991, 1990  
 * Open Software Foundation, Inc. 
 *  
 * Permission is hereby granted to use, copy, modify and freely distribute 
 * the software in this file and its documentation for any purpose without 
 * fee, provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation.  Further, provided that the name of Open 
 * Software Foundation, Inc. ("OSF") not be used in advertising or 
 * publicity pertaining to distribution of the software without prior 
 * written permission from OSF.  OSF makes no representations about the 
 * suitability of this software for any purpose.  It is provided "as is" 
 * without express or implied warranty. 
 *  
 * Copyright (c) 1992 Carnegie Mellon University 
 * All Rights Reserved. 
 *  
 * Permission to use, copy, modify and distribute this software and its 
 * documentation is hereby granted, provided that both the copyright 
 * notice and this permission notice appear in all copies of the 
 * software, derivative works or modified versions, and any portions 
 * thereof, and that both notices appear in supporting documentation. 
 *  
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR 
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE. 
 *  
 * Carnegie Mellon requests users of this software to return to 
 *  
 * Software Distribution Coordinator  or  Software_Distribution@CS.CMU.EDU 
 * School of Computer Science 
 * Carnegie Mellon University 
 * Pittsburgh PA 15213-3890 
 *  
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes. 
 */
/*
 * HISTORY
 * $Log: supcmain.c,v $
 * Revision 1.3.12.4  1994/02/22  15:51:26  damon
 * 	CR 1056. Added _g to collname and basedir
 * 	[1994/02/22  15:50:55  damon]
 *
 * Revision 1.3.12.3  1994/02/18  21:52:00  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:27  damon]
 * 
 * Revision 1.3.12.2  1994/02/17  15:44:22  damon
 * 	CR 1051. More pedantic
 * 	[1994/02/17  15:42:06  damon]
 * 
 * Revision 1.3.12.1  1994/02/15  20:37:45  damon
 * 	CR 1051. More pedantic
 * 	[1994/02/15  20:37:22  damon]
 * 
 * Revision 1.3.8.4  1993/05/28  15:53:25  marty
 * 	CR # 558 - rios_aix build
 * 	[1993/05/28  15:53:09  marty]
 * 
 * Revision 1.3.8.3  1993/05/04  18:38:02  damon
 * 	CR 435. Changed timevals from longs to time_t
 * 	[1993/05/04  18:37:55  damon]
 * 
 * Revision 1.3.8.2  1993/04/15  18:30:28  marty
 * 	Add include file ode/interface.h
 * 	[1993/04/15  18:30:10  marty]
 * 
 * Revision 1.3.2.7  1992/12/02  19:52:59  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:13  damon]
 * 
 * Revision 1.3.2.6  1992/09/24  19:00:13  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:19:04  gm]
 * 
 * Revision 1.3.2.5  1992/08/06  16:03:07  damon
 * 	CR 265. Changed to used ODE parser.
 * 	[1992/08/06  16:02:17  damon]
 * 
 * Revision 1.3.2.4  1992/06/16  23:09:11  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:58:18  damon]
 * 
 * Revision 1.3.5.2  1992/03/10  16:55:15  damon
 * 	Added conditional include of select.h with NO_INC_SYSCALL
 * 	Synched with OSF/1 sup
 * 	Derived from latest, 1.3.2.2
 * 	[1992/03/10  14:20:01  damon]
 * 
 * Revision 1.3  1991/12/05  20:54:16  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:50  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:14  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:17:17  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:46  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:55  gm]
 * 
 * Revision 1.3  90/07/17  12:26:51  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:05:16  gm]
 * 
 * Revision 1.2  90/01/02  19:56:18  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:13  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Added crosspatch support (is currently ignored).
 * 	[87/12/27            gm0w]
 * 
 * 	Added code for "release" support.
 * 	[87/06/28            gm0w]
 * 
 * 	Split into several files.  This is the main program and
 * 	command line processing and old history log. [V5.21]
 * 
 * 	Merged divergent CS and ECE versions. ifdeffed out the resource
 * 	pausing code - only compiled in if CMUCS defined. [V5.21a]
 * 
 * 	Removed support for version 3 of SUP protocol.  Added changes
 * 	to make lint happy.  Added calls to new logging routines. [V5.20]
 * 
 * 	Added -R switch to reenable resource pausing, which is currently
 * 	disabled by default.  Added code to check for free disk space
 * 	available on the target filesystem so that sup shouldn't run the
 * 	system out of disk space as frequently. [V5.19]
 * 
 * 	Changed default supfile name for system collections when -t
 * 	is specified to use FILESUPTDEFAULT; added missing new-line
 * 	in retry message. [V5.18]
 * 
 * 	Missed a caller to a routine which had an extra argument added
 * 	to it last edit. [V5.17]
 * 
 * 	Changed getcoll() so that fatal errors are checked immediately
 * 	instead of after sleeping for a little while.  Changed all
 * 	rm -rf commands to rmdir since the Mach folks keep deleting
 * 	their root and /usr directory trees.  Reversed the order of
 * 	delete commands to that directories will possibly empty so
 * 	that the rmdir's work. [V5.16]
 * 
 * 	Changed temporary file names to #n.sup format. [V5.15]
 * 
 * 	Moved PGMVERSION to supvers.c module. [V5.14]
 * 
 * 	Added check for file type before unlink when receiving a
 * 	symbolic link.  Now runs "rm -rf" if the file type is a
 * 	directory. [V5.13]
 * 
 * 	Fixed small bug in signon that didn't retry connections if an
 * 	error occured on the first attempt to connect. [V5.12]
 * 
 * 	New command interface.  Added -bBDEO flags and "delete",
 * 	"execute" and "old" supfile options.  Changed -d to work
 * 	correctly without implying -o. [V5.11]
 * 
 * 	Fix incorrect check for supfile changing.  Flush output buffers
 * 	before restart. [V5.10]
 * 
 * 	Add call to requestend() after connection errors are retried to
 * 	free file descriptors. [V5.9]
 * 
 * 	Fix SERIOUS merge error from previous edit.  Added notify
 * 	when execute command fails. [V5.8]
 * 
 * 	Changed ugconvert to clear setuid/setgid bits if it doesn't use
 * 	the user and group specified by the remote system.  Changed
 * 	execute code to invalidate collection if execute command returns
 * 	with a non-zero exit status.  Added support for execv() of
 * 	original arguments of supfile is upgraded sucessfully.  Changed
 * 	copyfile to always use a temp file if possible. [V5.7]
 * 
 * 	Added support for fileserver busy messages and new nameserver
 * 	protocol to support multiple repositories per collection.
 * 	Added code to lock collections with lock files. [V5.6]
 * 
 * 	Major rewrite for protocol version 4. [V4.5]
 * 
 * 	Changed to check for DIFFERENT mtime (again). [V3.4]
 * 
 * 	Replaced [ug]convert routines with ugconvert routine so that an
 * 	appropriate group will be used if the default user is used.
 * 	Changed switch parsing to allow multiple switches to be specified
 * 	at the same time. [V3.3]
 * 
 * 	Added test to request a new copy of an old file that already
 * 	exists if the mtime is different. [V3.2]
 * 
 * 	Added -l switch to enable upgrades from local repositories.
 * 	[85/11/24            gm0w]
 * 
 * 	Minor change in order -t prints so that columns line up.
 * 	[85/11/03            gm0w]
 * 
 * 	Added code to implement retry flag and pass this on to request().
 * 	[85/10/22            gm0w]
 * 
 * 	Merged 4.1 and 4.2 versions together.
 * 	[85/09/22            gm0w]
 * 
 * 	Created for 4.2 BSD.
 * 	[85/06/04            sas]
 * 
 * $EndLog$
 */
/*
 *	sup -- Software Upgrade Protocol client process
 *
 *	Usage:  sup [ flags ] [ supfile ] [ collection ... ]
 *
 *	The only required argument to sup is the name of a supfile.  It
 *	must either be given explicitly on the command line, or the -s
 *	flag must be specified.  If the -s flag is given, the system
 *	supfile will be used and a supfile command argument should not be
 *	specified.  The list of collections is optional and if specified
 *	will be the only collections upgraded.  The following flags affect
 *	all collections specified.
 *
 *	-s	"system upgrade" flag
 *			As described above.
 *
 *	-t	"upgrade time" flag
 *			When this flag is given, Sup will print the time
 *			that each collection was last upgraded, rather than
 *			performing actual upgrades.
 *
 *	-R	"resource pause" flag
 *			Sup will not disable resource pausing and will not
 *			make filesystem space checks.
 *
 *	-N	"debug network" flag
 *			Sup will trace messages sent and received that
 *			implement the Sup network protocol.
 *
 *	-P	"debug ports" flag
 *	    		Sup will use a set of non-privileged network
 *			ports reserved for debugging purposes.
 *
 *	-X	"crosspatch" flag
 *	    		Sup is being run remotely with a crosspatch.
 *			Need to be carefull as we may be running as root
 *			instead of collection owner.
 *
 *	-a	"all files" flag
 *			All files in the collection will be copied from
 *			the repository, regardless of their status on the
 *			current machine.  Because of this, it is a very
 *			expensive operation and should only be done for
 *			small collections if data corruption is suspected
 *			and been confirmed.  In most cases, the -o flag
 *			should be sufficient.
 *
 *	-b	"backup files" flag
 *			If the -b flag if given, or the "backup" supfile
 *			option is specified, the contents of regular files
 *			on the local system will be saved before they are
 *			overwritten with new data.  The data will be saved
 *			in a subdirectory called "BACKUP" in the directory
 *			containing the original version of the file, in a
 *			file with the same non-directory part of the file
 *			name.  The files to backup are specified by the
 *			list file on the repository.
 *
 *	-B	"don't backup files" flag
 *			The -B flag overrides and disables the -b flag and
 *			the "backup" supfile option.
 *
 *	-d	"delete files" flag
 *			Files that are no longer in the collection on the
 *			repository will be deleted if present on the local
 *			machine.  This may also be specified in a supfile
 *			with the "delete" option.
 *
 *	-D	"don't delete files" flag
 *			The -D flag overrides and disables the -d flag and
 *			the "delete" supfile option.
 *
 *	-e	"execute files" flag
 *			Sup will execute commands sent from the repository
 *			that should be run when a file is upgraded.  If
 *			the -e flag is omitted, Sup will print a message
 *			that specifies the command to execute.  This may
 *			also be specified in a supfile with the "execute"
 *			option.
 *
 *	-E	"don't execute files" flag
 *			The -E flag overrides and disables the -e flag and
 *			the "execute" supfile option.
 *
 *	-f	"file listing" flag
 *			A "list-only" upgrade will be performed.  Messages
 *			will be printed that indicate what would happen if
 *			an actual upgrade were done.
 *
 *	-l	"local upgrade" flag
 *			Normally, Sup will not upgrade a collection if the
 *			repository is on the same machine.  This allows
 *			users to run upgrades on all machines without
 *			having to make special checks for the repository
 *			machine.  If the -l flag is specified, collections
 *			will be upgraded even if the repository is local.
 *
 *	-m	"mail" flag
 *			Normally, Sup used standard output for messages.
 *			If the -m flag if given, Sup will send mail to the
 *			user running Sup, or a user specified with the
 *			"notify" supfile option, that contains messages
 *			printed by Sup.
 *
 *	-o	"old files" flag
 *			Sup will normally only upgrade files that have
 *			changed on the repository since the last time an
 *			upgrade was performed.  The -o flag, or the "old"
 *			supfile option, will cause Sup to check all files
 *			in the collection for changes instead of just the
 *			new ones.
 *
 *	-O	"not old files" flag
 *			The -O flag overrides and disables the -o flag and
 *			the "old" supfile option.
 *
 *	-v	"verbose" flag
 *			Normally, Sup will only print messages if there
 *			are problems.  This flag causes Sup to also print
 *			messages during normal progress showing what Sup
 *			is doing.
 */

#define MSGFILE
#include <ode/odedefs.h>
#include <ode/interface.h>
#include <ode/supcdefs.h>
#include <ode/sup.h>
#include <ode/util.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef CMUCS
#include <syscall.h>
#endif
/*********************************************
 ***    G L O B A L   V A R I A B L E S    ***
 *********************************************/

const char *progname = "sup";		/* Required by ODE */
const char program[] = "SUP";		/* program name for SCM messages */
int progpid = -1;			/* and process id */

COLLECTION *firstC,*thisC;		/* collection list pointer */

extern int dontjump;			/* disable longjmp */
extern int scmdebug;			/* SCM debugging flag */

int sysflag;				/* system upgrade flag */
int timeflag;				/* print times flag */
int rpauseflag;				/* disable resource (disk) checks */
int xpatchflag;				/* crosspatched with remote system */
int portdebug;				/* network debugging ports */

/*
 * Command Line Parsing data
 */
UIINIT cli_init [] = {
  { SYSUPGRADE_OP, 1, OVERWRITE, 0, 0, "" },
  { UPGRADETIME_OP, 1, OVERWRITE, 0, 0, "" },
  { RESPAUSE_OP, 1, OVERWRITE, 0, 0, "" },
  { NETDEBUG_OP, 1, OVERWRITE, 1, 1, "[0-9]" },
  { PORTDEBUG_OP, 1, OVERWRITE, 0, 0, "" },
  { XPATCH_OP, 1, OVERWRITE, 0, 0, "" },
  { ALWAYS_OP, 1, OVERWRITE, 0, 0, "" },
  { BACKUP_OP, 1, OVERWRITE, 0, 0, "" },
  { NOBACKUP_OP, 1, OVERWRITE, 0, 0, "" },
  { DELETE_OP, 1, OVERWRITE, 0, 0, "" },
  { NODELETE_OP, 1, OVERWRITE, 0, 0, "" },
  { EXEC_OP, 1, OVERWRITE, 0, 0, "" },
  { NOEXEC_OP, 1, OVERWRITE, 0, 0, "" },
  { FAKE_OP, 1, OVERWRITE, 0, 0, "" },
  { LOCALUPGRADE_OP, 1, OVERWRITE, 0, 0, "" },
  { MAIL_OP, 1, OVERWRITE, 0, 0, "" },
  { OLD_OP, 1, OVERWRITE, 0, 0, "" },
  { NOOLD_OP, 1, OVERWRITE, 0, 0, "" },
  { TRACE_OP, 1, OVERWRITE, 0, 0, "" },
};
#define MAX_ARGS (sizeof(cli_init) / sizeof(UIINIT))
UIINIT cli_posix_init [] = {
  { POSIX_ARGS_OP, UNLIMITED, OVERWRITE, 0, 0, "" },
};
#define MAX_POSIX_ARGS (sizeof(cli_posix_init) / sizeof(UIINIT))

/*
 * FORWARD DECLARATIONS
 */
char *init ( int , char **);
int
checkcoll ( TREE *, va_list );
void
getcoll (void);

/*************************************
 ***    M A I N   R O U T I N E    ***
 *************************************/

void
main ( int argc, char **argv )
{
	char *supfname;
	int restart,sfdev=0,sfino=0,sfmtime=0;
	struct stat sbuf;
	struct sigaction ignact;

	/* initialize global variables */
	pgmversion = PGMVERSION;	/* export version number */
	server = FALSE;			/* export that we're not a server */
	collname_g = NULL;		/* no current collection yet */
	dontjump = TRUE;		/* clear setjmp buffer */

	supfname = init (argc,argv);
	restart = -1;			/* don't make restart checks */
	if ( *supfname == '/') {
		if (stat (supfname,&sbuf) < 0)
			logerr ("Can't stat supfile %s",supfname);
		else {
			sfdev = sbuf.st_dev;
			sfino = sbuf.st_ino;
			sfmtime = sbuf.st_mtime;
			restart = 0;
		}
	}
	if (timeflag) {
		for (thisC = firstC; thisC; thisC = thisC->Cnext)
			prtime ();
	} else {
		/* ignore network pipe signals */
		ignact.sa_handler = SIG_IGN;
		ignact.sa_flags = 0;
		sigemptyset(&ignact.sa_mask);
		(void) sigaction (SIGPIPE,&ignact,(struct sigaction *)0);
		getnams ();		/* find unknown repositories */
		for (thisC = firstC; thisC; thisC = thisC->Cnext) {
			getcoll ();	/* upgrade each collection */
			if (restart == 0) {
				if (stat (supfname,&sbuf) < 0)
					logerr ("Can't stat supfile %s",
						supfname);
				else if (sfmtime != sbuf.st_mtime ||
					 sfino != sbuf.st_ino ||
					 sfdev != sbuf.st_dev) {
					restart = 1;
					break;
				}
			}
		}
		endpwent ();		/* close /etc/passwd */
		(void) endgrent ();	/* close /etc/group */
		if (restart == 1) {
			int fd;
			loginfo ("SUP Restarting %s with new supfile %s",
				progname,supfname);
			for (fd = sysconf (_SC_OPEN_MAX); fd > 3; fd--)
				(void) close (fd);
			execv (progname,argv);
			logquit (1,"Restart failed");
		}
	}
	while ((thisC = firstC)) {
		firstC = firstC->Cnext;
		free (thisC->Cname);
		Tfree (&thisC->Chtree);
		free (thisC->Cbase);
		if (thisC->Chbase)  free (thisC->Chbase);
		if (thisC->Cprefix)  free (thisC->Cprefix);
		if (thisC->Crelease)  free (thisC->Crelease);
		if (thisC->Cnotify)  free (thisC->Cnotify);
		if (thisC->Clogin)  free (thisC->Clogin);
		if (thisC->Cpswd)  free (thisC->Cpswd);
		if (thisC->Ccrypt)  free (thisC->Ccrypt);
		free ((char *)thisC);
	}
	exit (0);
}

/*****************************************
 ***    I N I T I A L I Z A T I O N    ***
 *****************************************/
/* Set up collection list from supfile.  Check all fields except
 * hostname to be sure they make sense.
 */

#define Toflags	Tflags
#define Taflags	Tmode
#define Twant	Tuid
#define Tcount	Tgid

void
doswitch ( TREE **collTp, int *oflagsp,int *aflagsp )
{
	int oflags,aflags;

	oflags = aflags = 0;
  if ( ui_is_set ( NETDEBUG_OP ) ) {
    scmdebug = atoi ( ui_arg_value ( NETDEBUG_OP, 1, 1 ) );
  }
  if ( ui_is_set ( PORTDEBUG_OP ) )
    portdebug = TRUE;
  if ( ui_is_set ( RESPAUSE_OP ) )
    rpauseflag = TRUE;
  if ( ui_is_set ( XPATCH_OP ) )
    xpatchflag = TRUE;
  if ( ui_is_set ( SYSUPGRADE_OP ) )
    sysflag = TRUE;
  if ( ui_is_set ( UPGRADETIME_OP ) )
    timeflag = TRUE;
  if ( ui_is_set ( ALWAYS_OP ) )
    oflags |= CFALL;
  if ( ui_is_set ( BACKUP_OP ) ) {
    oflags |= CFBACKUP;
    aflags &= ~CFBACKUP;
  }
  if ( ui_is_set ( NOBACKUP_OP ) ) {
    oflags &= ~CFBACKUP;
    aflags |= CFBACKUP;
  }
  if ( ui_is_set ( DELETE_OP ) ) {
    oflags |= CFDELETE;
    aflags &= ~CFDELETE;
  }
  if ( ui_is_set ( NODELETE_OP ) ) {
    oflags &= ~CFDELETE;
    aflags |= CFDELETE;
  }
  if ( ui_is_set ( EXEC_OP ) ) {
    oflags |= CFEXECUTE;
    aflags &= ~CFEXECUTE;
  }
  if ( ui_is_set ( NOEXEC_OP ) ) {
    oflags &= ~CFEXECUTE;
    aflags |= CFEXECUTE;
  }
  if ( ui_is_set ( FAKE_OP ) ) {
    oflags |= CFLIST;
  }
  if ( ui_is_set ( LOCALUPGRADE_OP ) )
    oflags |= CFLOCAL;
  if ( ui_is_set ( MAIL_OP ) )
    oflags |= CFMAIL;
  if ( ui_is_set ( OLD_OP ) ) {
    oflags |= CFOLD;
    aflags &= ~CFOLD;
  }
  if ( ui_is_set ( NOOLD_OP ) ) {
    oflags &= ~CFOLD;
    aflags |= CFOLD;
  }
  if ( ui_is_set ( TRACE_OP ) )
    oflags |= CFVERBOSE;
  *oflagsp |= oflags;
  *oflagsp &= ~aflags;
  *aflagsp |= aflags;
  *aflagsp &= ~oflags;
}

char *init ( int argc, char **argv )
{
	char buf[STRINGLENGTH];
	char *p;
	char username[STRINGLENGTH];
	const char *supfname;
	char *q,*arg;
	COLLECTION *c,*lastC;
	FILE *f;
	int bogus;
	struct passwd *pw;
	TREE *t;
	TREE *collT;			/* collections we are interested in */
	time_t timenow;			/* startup time */
	int oflags,aflags;
	int cwant;
	int ct;
	const char *s;

	sysflag = FALSE;		/* not system upgrade */
	timeflag = FALSE;		/* don't print times */
	rpauseflag = FALSE;		/* disable resource (disk) checks */
	xpatchflag = FALSE;		/* not normally crosspatched */
	scmdebug = 0;			/* level zero, no SCM debugging */
	portdebug = FALSE;		/* no debugging ports */

	collT = NULL;
	oflags = aflags = 0;
        ui_init ( argc, argv, MAX_ARGS, cli_init, MAX_POSIX_ARGS,
                  cli_posix_init );
        doswitch ( &collT, &oflags, &aflags );
	if ( ui_entry_cnt ( POSIX_ARGS_OP ) == 0 && !sysflag)
		logquit (1,"Need either -s or supfile");
#if     CMUCS && defined(SYS_rpause)
        oldsigsys = signal (SIGSYS,SIG_IGN);
        if (!rpauseflag && rpause(ENOSPC,RPAUSE_ALL,RPAUSE_DISABLE) < 0)
                rpauseflag = TRUE;
        (void) signal (SIGSYS,oldsigsys);
#endif
	if (sysflag) {
		(void) sprintf (buf, timeflag?FILESUPTDEFAULT:FILESUPDEFAULT,
				DEFDIR);
		supfname = buf;
	} else {
		supfname = ui_entry_value ( POSIX_ARGS_OP, 1 );
		if (strcmp (supfname,"-") == 0)
			supfname = "";
	}
	cwant = ui_entry_cnt ( POSIX_ARGS_OP ) >= 2;
        for ( ct = 2; ct <= ui_entry_cnt ( POSIX_ARGS_OP ); ct++ ) {
		t = Tinsert ( &collT, ui_entry_value ( POSIX_ARGS_OP, ct ), TRUE );
		t->Twant = TRUE;
	}
	if ((p = getlogin()) ||
	    ((pw = getpwuid ((int)getuid())) && (p = pw->pw_name)))
		(void) strcpy (username,p);
	else
		*username = '\0';
	if (*supfname) {
		f = fopen (supfname,"r");
		if (f == NULL)
			logquit (1,"Can't open supfile %s",supfname);
	} else
		f = stdin;
	firstC = NULL;
	lastC = NULL;
	bogus = FALSE;
	while ((p = fgets (buf,STRINGLENGTH,f))) {
		q = strchr (p,'\n');
		if (q)  *q = '\0';
		if (strchr ("#;:",*p))  continue;
		arg = nxtarg (&p," \t");
		if (*arg == '\0') {
			logerr ("Missing collection name in supfile");
			bogus = TRUE;
			continue;
		}
		if (cwant) {
			TREE *t2;
			if ((t2 = Tsearch (collT,arg)) == NULL)
				continue;
			t2->Tcount++;
		}
		c = (COLLECTION *) malloc (sizeof(COLLECTION));
		if (firstC == NULL)  firstC = c;
		if (lastC != NULL) lastC->Cnext = c;
		lastC = c;
		if (parsecoll(c,arg,p) < 0) {
			bogus = TRUE;
			continue;
		}
		c->Cflags |= oflags;
		c->Cflags &= ~aflags;
		if ((t = Tsearch (collT,c->Cname))) {
			c->Cflags |= t->Toflags;
			c->Cflags &= ~t->Taflags;
		}
		if ((c->Cflags&CFMAIL) && c->Cnotify == NULL) {
			if (*username == '\0')
				logerr ("User unknown, notification disabled");
			else
				c->Cnotify = strdup (username);
		}
		if (c->Cbase == NULL) {
			(void) sprintf (buf,FILEBASEDEFAULT,c->Cname);
			c->Cbase = strdup (buf);
		}
	}
	if (bogus)  logquit (1,"Aborted due to supfile errors");
	if (f != stdin)  (void) fclose (f);
	if (cwant)  (void) Tprocess (collT,checkcoll);
	Tfree (&collT);
	if (firstC == NULL)  logquit (1,"No collections to upgrade");
	timenow = time ((time_t *)NULL);
	if (*supfname == '\0')
		s = "standard input";
	else if (sysflag)
		s = "system software";
	else {
		(void) sprintf (buf,"file %s",supfname);
		s = buf;
	}
	loginfo ("SUP %d.%d (%s) for %s at %s",PROTOVERSION,PGMVERSION,
		scmversion,s,fmttime (timenow));
	return (strdup (supfname));
}

int
checkcoll ( TREE *t, va_list ap )
{
	if (!t->Twant)  return (SCMOK);
	if (t->Tcount == 0)
		logerr ("Collection %s not found",t->Tname);
	if (t->Tcount > 1)
		logerr ("Collection %s found more than once",t->Tname);
	return (SCMOK);
}
