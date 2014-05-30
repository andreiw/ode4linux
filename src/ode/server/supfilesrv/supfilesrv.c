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
 * $Log: supfilesrv.c,v $
 * Revision 1.3.12.5  1994/02/18  23:09:17  damon
 * 	CR 1056. Made collname and basedir global
 * 	[1994/02/18  23:08:59  damon]
 *
 * Revision 1.3.12.4  1994/02/18  21:52:30  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:47  damon]
 * 
 * Revision 1.3.12.3  1994/02/18  18:20:10  damon
 * 	CR 1056. Made pedantic
 * 	[1994/02/18  18:19:59  damon]
 * 
 * Revision 1.3.12.2  1994/02/17  18:44:52  damon
 * 	CR 1056. moved from /bin/sup
 * 	[1994/02/17  18:44:33  damon]
 * 
 * Revision 1.3.12.1  1994/02/10  20:20:11  root
 * 	CR # 1049 - Clean up error messages for rios_aix.  Include <sys/file.h>.
 * 	[1994/02/10  20:19:51  root]
 * 
 * Revision 1.3.9.1  1993/10/27  16:08:17  damon
 * 	CR 765. do not die if could not establish network connection
 * 	[1993/10/27  16:08:07  damon]
 * 
 * Revision 1.3.7.3  1993/05/28  18:41:48  marty
 * 	CR # 558 - Type casting for rios_aix
 * 	[1993/05/28  18:41:33  marty]
 * 
 * Revision 1.3.7.2  1993/05/04  18:47:35  damon
 * 	CR 435. Changed timevals from longs to time_t
 * 	[1993/05/04  18:47:07  damon]
 * 
 * Revision 1.3.2.10  1992/12/02  19:53:12  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:24  damon]
 * 
 * Revision 1.3.2.9  1992/11/13  15:20:07  root
 * 	Change include of sys/time.h to plain time.h
 * 	[1992/11/13  15:00:04  root]
 * 
 * Revision 1.3.2.8  1992/11/09  22:15:53  damon
 * 	CR 296. Removed warnings
 * 	[1992/11/09  22:14:48  damon]
 * 
 * Revision 1.3.2.7  1992/09/24  19:03:39  gm
 * 	CR282: Made more portable to non-BSD systems.  Added NO_SUP_LOCKS
 * 	around sup "lock" file support.
 * 	[1992/09/21  20:33:54  gm]
 * 
 * Revision 1.3.2.6  1992/07/26  17:37:50  gm
 * 	Removed BSD unix dependencies.
 * 	[1992/07/17  20:55:15  gm]
 * 
 * Revision 1.3.2.5  1992/06/16  23:09:20  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:58:35  damon]
 * 
 * Revision 1.3.4.3  1992/04/02  21:01:00  damon
 * 	include portable.h
 * 	[1992/04/02  20:58:13  damon]
 * 
 * Revision 1.3.4.2  1992/02/13  15:28:22  gm
 * 	About time we bumped the revision number.  Placed code for
 * 	setsid under an OSF1 conditional, restored alternative.
 * 	[1992/02/09  02:17:23  gm]
 * 
 * Revision 1.3.2.2  1992/01/08  15:29:06  damon
 * 	Synched with OSF/1 sup
 * 	[1992/01/08  15:15:12  damon]
 * 
 * Revision 1.3  1991/12/05  20:54:36  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:25  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:49  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:18:06  zeliff]
 * 
 * Revision 1.2  90/10/07  21:37:14  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:28  gm]
 * 
 * Revision 1.4  90/07/17  12:27:03  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:05:48  gm]
 * 
 * Revision 1.3  90/06/29  14:18:41  devrcs
 * 	Removed references to defunct libsys library.
 * 	[90/06/20  17:47:08  gm]
 * 
 * Revision 1.2  90/01/02  19:56:24  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:34  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.14  89/08/23  14:56:15  gm0w
 * 	Changed msgf routines to msg routines.
 * 	[89/08/23            gm0w]
 * 
 * Revision 1.13  89/08/03  19:57:33  mja
 * 	Remove setaid() call.
 * 
 * Revision 1.12  89/08/03  19:49:24  mja
 * 	Updated to use v*printf() in place of _doprnt().
 * 	[89/04/19            mja]
 * 
 * Revision 0.0  88/09/11            gm0w
 * 	Added code to record release name in logfile.
 * 	[88/09/11            gm0w]
 * 
 * Revision 0.0  88/03/18            gm0w
 * 	Added host=<hostfile> support to releases file. [V7.12]
 * 	[88/03/18            gm0w]
 * 
 * Revision 0.0  87/12/27            gm0w
 * 	Added crosspatch support.  Created docrypt() routine for crypt
 * 	test message.
 * 	[87/12/27            gm0w]
 * 
 * Revision 0.0  87/09/09            gm0w
 * 	Removed common information logging code, the quiet switch, and
 * 	moved samehost() check to after device/inode check.
 * 	[87/09/09            gm0w]
 * 
 * Revision 0.0  87/06/28            gm0w
 * 	Added code for "release" support. [V5.11]
 * 	[87/06/28            gm0w]
 * 
 * Revision 0.0  87/05/26            dwp
 * 	Added code to record final status of client in logfile. [V5.10]
 * 	[87/05/26            dwp]
 * 
 * Revision 0.0  87/05/22            chriss
 * 	Mergered divergent CS and ECE versions. [V5.9a]
 * 	[87/05/22            chriss]
 * 
 * Revision 0.0  87/05/20            gm0w
 * 	Removed support for version 3 of SUP protocol.  Added changes
 * 	to make lint happy.  Added calls to new logging routines. [V5.9]
 * 	[87/05/20            gm0w]
 * 
 * Revision 0.0  87/03/31            dan
 * 	Fixed so no password check is done when crypts are used.
 * 	[87/03/31            dan]
 * 
 * Revision 0.0  86/11/25            ern
 * 	Set F_APPEND fcntl in logging to increase the chance
 * 	that the log entry from this incarnation of the file
 * 	server will not be lost by another incarnation. [V5.8]
 * 	[86/11/25            ern]
 * 
 * Revision 0.0  86/10/20            dan
 * 	Changed not to call okmumbles when not compiled with CMUCS.
 * 	[86/10/20            dan]
 * 
 * Revision 0.0  86/08/04            gm0w
 * 	Added code to increment scmdebug as more -N flags are
 * 	added. [V5.7]
 * 	[86/08/04            gm0w]
 * 
 * Revision 0.0  86/05/25            jjc
 * 	Renamed local variable in main program from "sigmask" to
 * 	"signalmask" to avoid name conflict with 4.3BSD identifier.
 * 	Conditionally compile in calls to CMU routines, "setaid" and
 * 	"logaccess". [V5.6]
 * 	[86/05/25            jjc]
 * 
 * Revision 0.0  86/01/21            gm0w
 * 	Changed supfilesrv to use the crypt file owner and group for
 * 	access purposes, rather than the directory containing the crypt
 * 	file. [V5.5]
 * 	[86/01/21            gm0w]
 * 
 * Revision 0.0  86/01/07            gm0w
 * 	Added code to keep logfiles in repository collection directory.
 * 	Added code for locking collections. [V5.4]
 * 	[86/01/07            gm0w]
 * 
 * Revision 0.0  86/01/05            gm0w
 * 	Added code to support new FSETUPBUSY return.  Now accepts all
 * 	connections and tells any clients after the 8th that the
 * 	fileserver is busy.  New clients will retry again later. [V5.3]
 * 	[86/01/05            gm0w]
 * 
 * Revision 0.0  85/12/29            gm0w
 * 	Major rewrite for protocol version 4. [V4.2]
 * 	[85/12/29            gm0w]
 * 
 * Revision 0.0  85/12/12            gm0w
 * 	Fixed close of crypt file to use file pointer as argument
 * 	instead of string pointer.
 * 	[85/12/12            gm0w]
 * 
 * Revision 0.0  85/11/24            gm0w
 * 	Allow "!hostname" lines and comments in collection "host" file.
 * 	[85/11/24            gm0w]
 * 
 * Revision 0.0  85/11/13            gm0w
 * 	Don't use access() on symbolic links since they may not point to
 * 	an existing file.
 * 	[85/11/13            gm0w]
 * 
 * Revision 0.0  85/10/22            gm0w
 * 	Added code to restrict file server availability to when it has
 * 	less than or equal to eight children.
 * 	[85/10/22            gm0w]
 * 
 * Revision 0.0  85/09/22            gm0w
 * 	Merged 4.1 and 4.2 versions together.
 * 	[85/09/22            gm0w]
 * 
 * Revision 0.0  85/06/04            sas
 * 	Created for 4.2 BSD.
 * 	[85/06/04            sas]
 * 
 * $EndLog$
 */
/*
 * supfilesrv -- SUP File Server
 *
 * Usage:  supfilesrv [-l] [-P] [-N]
 *	-l	"live" -- don't fork daemon
 *	-P	"debug ports" -- use debugging network ports
 *	-N	"debug network" -- print debugging messages for network i/o
 */

#include <sys/param.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <ode/portable.h>
#include <ode/odedefs.h>
#include <ode/util.h>
#include <ode/sup.h>
#define MSGFILE
#include <ode/supmsg.h>
#include <sys/file.h>

#ifndef WAIT_ANY
#define WAIT_ANY -1
#endif

#define PGMVERSION 13

/*************************
 ***    M A C R O S    ***
 *************************/

#define HASHBITS 8
#define HASHSIZE (1<<HASHBITS)
#define HASHMASK (HASHSIZE-1)
#define HASHFUNC(x,y) ((x)&HASHMASK)

/*******************************************
 ***    D A T A   S T R U C T U R E S    ***
 *******************************************/

struct hashstruct {			/* hash table for number lists */
	int Hnum1;			/* numeric keys */
	int Hnum2;
	char *Hname;			/* string value */
	TREE *Htree;			/* TREE value */
	struct hashstruct *Hnext;
};
typedef struct hashstruct HASH;

/*********************************************
 ***    G L O B A L   V A R I A B L E S    ***
 *********************************************/

char program[] = "supfilesrv";		/* program name for SCM messages */
int progpid = -1;			/* and process id */

jmp_buf sjbuf;				/* jump location for network errors */
TREELIST *listTL;			/* list of trees to upgrade */

int live;				/* -l flag */
int dbgportsq;				/* -P flag */
extern int scmdebug;			/* -N flag */
extern int netfile;

int nchildren;				/* number of children that exist */
char *prefix;				/* collection pathname prefix */
char *release;				/* collection release name */
char *cryptkey;				/* encryption key if non-null */
#ifndef NO_SUP_LOCKS
int lockfd;				/* descriptor of lock file */
#endif

/* global variables for scan functions */
int trace = FALSE;			/* directory scan trace */

HASH *uidH[HASHSIZE];			/* for uid and gid lookup */
HASH *gidH[HASHSIZE];
HASH *inodeH[HASHSIZE];			/* for inode lookup for linked file check */

/*
 * FORWARD DECLARATIONS
 */
void
chldsig(int);
void
init ( int , char ** );
char *fmttime (time_t );
void
answer (void);
int
denyone ( TREE *, va_list );
void
signon (void);
void
setup (void);
void
docrypt (void);
void
login (void);
void
listfiles (void);
void
sendfiles (void);
void
finishup ( time_t );
void
Hfree ( HASH **);
char *
changeuid ( char *,char *, int , int );
TREE *
linkcheck ( TREE *, int , int );
int
sendone ( TREE *, va_list );
int
senddir ( TREE *, va_list );
int
sendfile ( TREE *, va_list);
char *
uconvert (int );
char *
gconvert (int );

/*************************************
 ***    M A I N   R O U T I N E    ***
 *************************************/

void
main ( int argc, char ** argv )
{
	register int x,pid;
	struct sigaction sigact;
	sigset_t newset, oldset;
	time_t tloc;

	/* initialize global variables */
	pgmversion = PGMVERSION;	/* export version number */
	server = TRUE;			/* export that we're not a server */
	collname_g = NULL;		/* no current collection yet */

	init (argc,argv);		/* process arguments */
	logopen ("supfile");
	tloc = time ((time_t *)NULL);
	loginfo ("SUP File Server Version %d.%d (%s) starting at %s",
		PROTOVERSION,PGMVERSION,scmversion,fmttime (tloc));
	if (live) {
		x = service ();
		if (x != SCMOK)
			logquit (1,"Can't connect to network");
		answer ();
		(void) serviceend ();
		exit (0);
	}
	if (getenv("RUNNING_UNDER_NANNY") == 0) {
		while ((pid = fork()) == -1)
			sleep(10);
		if (pid != 0)
			exit(0);
#ifdef NO_SETSID 
		(void) setpgrp(0, getpid());
		if ((x = open("/dev/tty", O_RDWR, 0)) != -1) {
			(void) ioctl(x, TIOCNOTTY, (char *) 0);
			(void) close(x);
		}
#else
		(void) setsid();
#endif
	}
	sigact.sa_handler = SIG_IGN;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	(void) sigaction (SIGHUP,&sigact,(struct sigaction *)0);
	(void) sigaction (SIGINT,&sigact,(struct sigaction *)0);
	(void) sigaction (SIGPIPE,&sigact,(struct sigaction *)0);
	sigact.sa_handler = chldsig;
	(void) sigaction (SIGCHLD,&sigact,(struct sigaction *)0);
	nchildren = 0;
	for (;;) {
		x = service ();
		if (x != SCMOK) {
			logerr ("Error in establishing network connection");
                        sleep(30);
			continue;
                } /* if */
		sigemptyset(&newset);
		sigaddset(&newset, SIGCHLD);
		(void) sigprocmask (SIG_BLOCK,&newset,&oldset);
		if ((pid = fork()) == 0) { /* server process */
			(void) serviceprep ();
			answer ();
			(void) serviceend ();
			exit (0);
		}
		(void) servicekill ();	/* parent */
		if (pid > 0) nchildren++;
		(void) sigprocmask (SIG_SETMASK,&oldset,(sigset_t *)0);
	}
}

/*
 * Child status signal handler
 */

void
chldsig(int ignored)
{
	int status;

	while (waitpid(WAIT_ANY, &status, WNOHANG) > 0)
		if (nchildren) nchildren--;
}

/*****************************************
 ***    I N I T I A L I Z A T I O N    ***
 *****************************************/

void
usage (void)
{
	quit (1,"Usage: supfilesrv [ -l | -P | -N | -H <host> <user> <cryptfile> <supargs> ]\n");
}

void
init ( int argc, char ** argv )
{
	register int i;
	register int x;
	char *clienthost;
	const char *clientuser;
	char *p,*q;
	char buf[STRINGLENGTH];
	register FILE *f;
	int retry;

	live = FALSE;
	dbgportsq = FALSE;
	scmdebug = 0;
	clienthost = NULL;
	clientuser = NULL;
	if (--argc < 0)
		usage ();
	argv++;
	while (clienthost == NULL && argc > 0 && argv[0][0] == '-') {
		switch (argv[0][1]) {
		case 'l':
			live = TRUE;
			break;
		case 'P':
			dbgportsq = TRUE;
			break;
		case 'N':
			scmdebug++;
			break;
		case 'H':
			if (--argc < 3)
				quit (1,"Missing args to -H\n");
			argv++;
			clienthost = (char *)argv[0];
			clientuser = argv[1];
			cryptkey = argv[2];
			argc -= 2;
			argv += 2;
			break;
		default:
			fprintf (stderr,"Unknown flag %s ignored\n",argv[0]);
			break;
		}
		--argc;
		argv++;
	}
	if (clienthost == NULL) {
		if (argc != 0)
			usage ();
		x = servicesetup (dbgportsq ? DEBUGFPORT : FILEPORT);
		if (x != SCMOK)
			quit (1,"Error in network setup");
		for (i = 0; i < HASHSIZE; i++)
			uidH[i] = gidH[i] = inodeH[i] = NULL;
		return;
	}
	server = FALSE;
	if (argc < 1)
		usage ();
	f = fopen (cryptkey,"r");
	if (f == NULL)
		quit (1,"Unable to open cryptfile %s\n",cryptkey);
	if ((p = fgets (buf,STRINGLENGTH,f))) {
		if ((q = strchr (p,'\n')))  *q = '\0';
		if (*p == '\0')
			quit (1,"No cryptkey found in %s\n",cryptkey);
		cryptkey = strdup (buf);
	}
	(void) fclose (f);
	retry = 1;
	x = request (dbgportsq ? DEBUGFPORT : FILEPORT,clienthost,&retry);
	if (x != SCMOK)
		quit (1,"Unable to connect to host %s\n",clienthost);
	x = msgsignon ();
	if (x != SCMOK)
		quit (1,"Error sending signon request to fileserver\n");
	x = msgsignonack ();
	if (x != SCMOK)
		quit (1,"Error reading signon reply from fileserver\n");
	printf ("SUP Fileserver %d.%d (%s) %d on %s\n",
		protver,pgmver,scmver,fspid,remotehost());
	free (scmver);
	scmver = NULL;
	if (protver < 7)
		quit (1,"Remote fileserver does not implement reverse sup\n");
	xpatch = TRUE;
	xuser = (char *)clientuser;
	x = msgsetup ();
	if (x != SCMOK)
		quit (1,"Error sending setup request to fileserver\n");
	x = msgsetupack ();
	if (x != SCMOK)
		quit (1,"Error reading setup reply from fileserver\n");
	switch (setupack) {
	case FSETUPOK:
		break;
	case FSETUPSAME:
		quit (1,"User %s not found on remote client\n",xuser);
	case FSETUPHOST:
		quit (1,"This host has no permission to reverse sup\n");
	default:
		quit (1,"Unrecognized file server setup status %d\n",setupack);
	}
	(void) netcrypt (cryptkey);
	crypttest = (char *)CRYPTTEST;
	x = msgcrypt ();
	if (x != SCMOK)
		quit (1,"Error sending encryption test request\n");
	x = msgcryptok ();
	if (x == SCMEOF)
		quit (1,"Data encryption test failed\n");
	if (x != SCMOK)
		quit (1,"Error reading encryption test reply\n");
	logcrypt = (char *)CRYPTTEST;
	loguser = NULL;
	logpswd = NULL;
	(void) netcrypt (PSWDCRYPT);	/* encrypt password data */
	x = msglogin ();
	(void) netcrypt ((char *)NULL);	/* turn off encryption */
	if (x != SCMOK)
		quit (1,"Error sending login request to file server\n");
	x = msglogack ();
	if (x != SCMOK)
		quit (1,"Error reading login reply from file server\n");
	if (logack == FLOGNG)
		quit (1,"%s\nImproper login to %s account\n",logerror,xuser);
	xargc = argc;
	xargv = argv;
	x = msgxpatch ();
	if (x != SCMOK)
		quit (1,"Error sending crosspatch request\n");
    	crosspatch ();
	exit (0);
}

#if __STDC__
void
goaway (const char *fmt,...)
#else
/* VARARGS */
void
goaway (va_alist)
va_dcl
#endif
{
#if !__STDC__
	const char *fmt;
#endif
	char buf[STRINGLENGTH];
	va_list ap;

	(void) netcrypt ((char *)NULL);
#if __STDC__
	va_start(ap,fmt);
#else
	va_start(ap);
	fmt = va_arg(ap,char *);
#endif
	vsprintf(buf, fmt, ap);
	va_end(ap);
	goawayreason = strdup (buf);
	(void) msggoaway ();
	logerr ("%s",buf);
	longjmp (sjbuf,TRUE);
}

/*****************************************
 ***    A N S W E R   R E Q U E S T    ***
 *****************************************/

void
answer (void)
{
	time_t starttime;
	register int x;

	progpid = fspid = getpid ();
	collname_g = NULL;
	basedir_g = NULL;
	prefix = NULL;
	release = NULL;
	goawayreason = NULL;
	donereason = NULL;
#ifndef NO_SUP_LOCKS
	lockfd = -1;
#endif
	starttime = time ((time_t *)NULL);
	if (!setjmp (sjbuf)) {
		signon ();
		setup ();
		docrypt ();
		login ();
		if (xpatch) {
			int fd;

			x = msgxpatch ();
			if (x != SCMOK)
				exit (0);
			xargv[0] = (char *)"/usr/cs/bin/sup";
			xargv[1] = (char *)"-X";
			xargv[xargc] = (char *)NULL;
			dup2 (netfile,0);
			dup2 (netfile,1);
			dup2 (netfile,2);
			fd = sysconf (_SC_OPEN_MAX);
			while (--fd > 2)
				close (fd);
			execv (xargv[0],xargv);
			exit (0);
		}
		listfiles ();
		sendfiles ();
	}
	finishup (starttime);
	if (collname_g)  free (collname_g);
	if (basedir_g)  free (basedir_g);
	if (prefix)  free (prefix);
	if (release)  free (release);
	if (goawayreason) {
		if (donereason == goawayreason)
			donereason = NULL;
		free (goawayreason);
	}
	if (donereason)  free (donereason);
#ifndef NO_SUP_LOCKS
	if (lockfd >= 0)  (void) close (lockfd);
#endif
	endpwent ();
	(void) endgrent ();
	Hfree (uidH);
	Hfree (gidH);
	Hfree (inodeH);
}

/*****************************************
 ***    S I G N   O N   C L I E N T    ***
 *****************************************/

void
signon (void)
{
	register int x;

	xpatch = FALSE;
	x = msgsignon ();
	if (x != SCMOK)  goaway ("Error reading signon request from client");
	x = msgsignonack ();
	if (x != SCMOK)  goaway ("Error sending signon reply to client");
	free (scmver);
	scmver = NULL;
}

/*****************************************************************
 ***    E X C H A N G E   S E T U P   I N F O R M A T I O N    ***
 *****************************************************************/

void
setup (void)
{
	register int x;
	char *p,*q;
	char buf[STRINGLENGTH];
	register FILE *f;
	struct stat sbuf;
	register TREELIST *tl;

	x = msgsetup ();
	if (x != SCMOK)  goaway ("Error reading setup request from client");
	if (protver < 4) {
		setupack = FSETUPOLD;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Sup client using obsolete version of protocol");
	}
	if (xpatch) {
		register struct passwd *pw;

		if ((pw = getpwnam (xuser)) == NULL) {
			setupack = FSETUPSAME;
			(void) msgsetupack ();
			if (protver >= 6)  longjmp (sjbuf,TRUE);
			goaway ("User not found");
		}
		(void) free (xuser);
		xuser = strdup (pw->pw_dir);

		/* check crosspatch host access file */
		cryptkey = NULL;
		(void) sprintf (buf,FILEXPATCH,xuser);
		f = fopen (buf,"r");
		if (f) {
			int hostok = FALSE;

			while ((p = fgets (buf,STRINGLENGTH,f))) {
				q = strchr (p,'\n');
				if (q)  *q = 0;
				if (strchr ("#;:",*p))  continue;
				q = nxtarg (&p," \t");
				if (*p == '\0')  continue;
				if (matchhost(q)) {
					cryptkey = strdup (p);
					hostok = TRUE;
					break;
				}
			}
			(void) fclose (f);
			if (!hostok) {
				setupack = FSETUPHOST;
				(void) msgsetupack ();
				if (protver >= 6)  longjmp (sjbuf,TRUE);
				goaway ("Host not on access list");
			}
		}
		setupack = FSETUPOK;
		x = msgsetupack ();
		if (x != SCMOK)
			goaway ("Error sending setup reply to client");
		return;
	}
	if (release == NULL)
		release = strdup (DEFRELEASE);
	if (basedir_g == NULL || *basedir_g == '\0') {
		basedir_g = NULL;
		(void) sprintf (buf,FILEDIRS,DEFDIR);
		f = fopen (buf,"r");
		if (f) {
			while ((p = fgets (buf,STRINGLENGTH,f))) {
				q = strchr (p,'\n');
				if (q)  *q = 0;
				if (strchr ("#;:",*p))  continue;
				q = nxtarg (&p," \t=");
				if (strcmp(q,collname_g) == 0) {
					basedir_g = skipover(p," \t=");
					basedir_g = strdup (basedir_g);
					break;
				}
			}
			(void) fclose (f);
		}
		if (basedir_g == NULL) {
			(void) sprintf (buf,FILEBASEDEFAULT,collname_g);
			basedir_g = strdup(buf);
		}
	}
	if (chdir (basedir_g) < 0)
		goaway ("Can't chdir to base directory %s",basedir_g);
	(void) sprintf (buf,FILEPREFIX,collname_g);
	f = fopen (buf,"r");
	if (f) {
		while ((p = fgets (buf,STRINGLENGTH,f))) {
			q = strchr (p,'\n');
			if (q)  *q = 0;
			if (strchr ("#;:",*p))  continue;
			prefix = strdup(p);
			if (chdir (prefix) < 0)
				goaway ("Can't chdir to %s from base directory %s",
					prefix,basedir_g);
			break;
		}
		(void) fclose (f);
	}
	x = stat (".",&sbuf);
	if (prefix)  (void) chdir (basedir_g);
	if (x < 0)
		goaway ("Can't stat base/prefix directory");
	if (nchildren >= MAXCHILDREN) {
		setupack = FSETUPBUSY;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Sup client told to try again later");
	}
	if (sbuf.st_dev == basedev && sbuf.st_ino == baseino && samehost()) {
		setupack = FSETUPSAME;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Attempt to upgrade to same directory on same host");
	}
	/* obtain release information */
	if (!getrelease (release)) {
		setupack = FSETUPRELEASE;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Invalid release information");
	}
	/* check host access file */
	cryptkey = NULL;
	for (tl = listTL; tl != NULL; tl = tl->TLnext) {
		const char *h;
		if ((h = tl->TLhost) == NULL)
			h = FILEHOSTDEF;
		(void) sprintf (buf,FILEHOST,collname_g,h);
		f = fopen (buf,"r");
		if (f) {
			int hostok = FALSE;
			while ((p = fgets (buf,STRINGLENGTH,f))) {
				int not;
				q = strchr (p,'\n');
				if (q)  *q = 0;
				if (strchr ("#;:",*p))  continue;
				q = nxtarg (&p," \t");
				if ((not = (*q == '!')) && *++q == '\0')
					q = nxtarg (&p," \t");
				hostok = (not == (matchhost(q) == 0));
				if (hostok) {
					if (*p)  cryptkey = strdup (p);
					break;
				}
			}
			(void) fclose (f);
			if (!hostok) {
				setupack = FSETUPHOST;
				(void) msgsetupack ();
				if (protver >= 6)  longjmp (sjbuf,TRUE);
				goaway ("Host not on access list for %s",
					collname_g);
			}
		}
	}
#ifndef NO_SUP_LOCKS
	/* try to lock collection */
	(void) sprintf (buf,FILELOCK,collname_g);
	x = open (buf,O_RDONLY,0);
	if (x >= 0) {
		if (flock (x, (int)(LOCK_SH|LOCK_NB)) < 0) {
			(void) close (x);
			if (errno != EWOULDBLOCK)
				goaway ("Can't lock collection %s",collname_g);
			setupack = FSETUPBUSY;
			(void) msgsetupack ();
			if (protver >= 6)  longjmp (sjbuf,TRUE);
			goaway ("Sup client told to wait for lock");
		}
		lockfd = x;
	}
#endif
	setupack = FSETUPOK;
	x = msgsetupack ();
	if (x != SCMOK)  goaway ("Error sending setup reply to client");
}

/** Test data encryption **/
void
docrypt (void)
{
	register int x;
	char *p,*q;
	char buf[STRINGLENGTH];
	register FILE *f;

	if (!xpatch && cryptkey == NULL) {
		(void) sprintf (buf,FILECRYPT,collname_g);
		f = fopen (buf,"r");
		if (f) {
			if ((p = fgets (buf,STRINGLENGTH,f))) {
				if ((q = strchr (p,'\n')))  *q = '\0';
				if (*p)  cryptkey = strdup (buf);
			}
			(void) fclose (f);
		}
	}
	(void) netcrypt (cryptkey);
	x = msgcrypt ();
	if (x != SCMOK)
		goaway ("Error reading encryption test request from client");
	(void) netcrypt ((char *)NULL);
	if (strcmp(crypttest,CRYPTTEST) != 0)
		goaway ("Client not encrypting data properly");
	free (crypttest);
	crypttest = NULL;
	x = msgcryptok ();
	if (x != SCMOK)
		goaway ("Error sending encryption test reply to client");
}

/***************************************************************
 ***    C O N N E C T   T O   P R O P E R   A C C O U N T    ***
 ***************************************************************/

void
login (void)
{
	register int x,fileuid=-1,filegid=-1;
	struct stat sbuf;
	char buf[STRINGLENGTH];

	(void) netcrypt (PSWDCRYPT);	/* encrypt acct name and password */
	x = msglogin ();
	(void) netcrypt ((char *)NULL); /* turn off encryption */
	if (x != SCMOK)  goaway ("Error reading login request from client");
	if (strcmp(logcrypt,CRYPTTEST) != 0) {
		logack = FLOGNG;
		logerror = (char *)"Improper login encryption";
		(void) msglogack ();
		goaway ("Client not encrypting login information properly");
	}
	free (logcrypt);
	logcrypt = NULL;
	if (loguser == NULL) {
		if (cryptkey) {
			if (xpatch)
				(void) sprintf (buf,FILEXPATCH,xuser);
			else
				(void) sprintf (buf,FILECRYPT,collname_g);
			if (stat (buf,&sbuf) == 0) {
				fileuid = sbuf.st_uid;
				filegid = sbuf.st_gid;
				loguser = NULL;
			} else
				loguser = strdup (DEFUSER);
		} else
			loguser = strdup (DEFUSER);
	}
	if ((logerror = changeuid (loguser,logpswd,fileuid,filegid)) != NULL) {
		logack = FLOGNG;
		(void) msglogack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Client denied login access");
	}
	if (loguser)  free (loguser);
	if (logpswd)  free (logpswd);
	logack = FLOGOK;
	x = msglogack ();
	if (x != SCMOK)  goaway ("Error sending login reply to client");
	if (!xpatch)
		(void) netcrypt (cryptkey); /* restore desired encryption */
	free (cryptkey);
	cryptkey = NULL;
}

/*****************************************
 ***    M A K E   N A M E   L I S T    ***
 *****************************************/

void
listfiles (void)
{
	register int x;

	refuseT = NULL;
	x = msgrefuse ();
	if (x != SCMOK)  goaway ("Error reading refuse list from client");
	getscanlists ();
	Tfree (&refuseT);
	x = msglist ();
	if (x != SCMOK)  goaway ("Error sending file list to client");
	Tfree (&listT);
	listT = NULL;
	needT = NULL;
	x = msgneed ();
	if (x != SCMOK)
		goaway ("Error reading needed files list from client");
	denyT = NULL;
	(void) Tprocess (needT,denyone);
	Tfree (&needT);
	x = msgdeny ();
	if (x != SCMOK)  goaway ("Error sending denied files list to client");
	Tfree (&denyT);
}

int
denyone ( TREE *t, va_list ap )
{
	register TREELIST *tl;
	register char *name = t->Tname;
	register int update = (t->Tflags&FUPDATE) != 0;
	struct stat sbuf;
	register TREE *tlink;
	char slinkname[STRINGLENGTH];
	register int x;

	for (tl = listTL; tl != NULL; tl = tl->TLnext)
		if ((t = Tsearch (tl->TLtree,name)) != NULL)
			break;
	if (t == NULL) {
		(void) Tinsert (&denyT,name,FALSE);
		return (SCMOK);
	}
	cdprefix (tl->TLprefix);
	if ((t->Tmode&S_IFMT) == S_IFLNK)
		x = lstat(name,&sbuf);
	else
		x = stat(name,&sbuf);
	if (x < 0 || (sbuf.st_mode&S_IFMT) != (t->Tmode&S_IFMT)) {
		(void) Tinsert (&denyT,name,FALSE);
		return (SCMOK);
	}
	switch (t->Tmode&S_IFMT) {
	case S_IFLNK:
		if ((x = readlink (name,slinkname,STRINGLENGTH)) <= 0) {
			(void) Tinsert (&denyT,name,FALSE);
			return (SCMOK);
		}
		slinkname[x] = '\0';
		(void) Tinsert (&t->Tlink,slinkname,FALSE);
		break;
	case S_IFREG:
		if (sbuf.st_nlink > 1 &&
		    (tlink = linkcheck (t,(int)sbuf.st_dev,(int)sbuf.st_ino)))
		{
			(void) Tinsert (&tlink->Tlink,name,FALSE);
			return (SCMOK);
		}
		if (update)  t->Tflags |= FUPDATE;
	case S_IFDIR:
		t->Tuid = sbuf.st_uid;
		t->Tgid = sbuf.st_gid;
		break;
	default:
		(void) Tinsert (&denyT,name,FALSE);
		return (SCMOK);
	}
	t->Tflags |= FNEEDED;
	return (SCMOK);
}

/*********************************
 ***    S E N D   F I L E S    ***
 *********************************/

void
sendfiles (void)
{
	register TREELIST *tl;
	register int x;

	/* send all files */
	for (tl = listTL; tl != NULL; tl = tl->TLnext) {
		cdprefix (tl->TLprefix);
		(void) Tprocess (tl->TLtree,sendone);
	}
	/* send directories in reverse order */
	for (tl = listTL; tl != NULL; tl = tl->TLnext) {
		cdprefix (tl->TLprefix);
		(void) Trprocess (tl->TLtree,senddir);
	}
	x = msgsend ();
	if (x != SCMOK)
		goaway ("Error reading receive file request from client");
	upgradeT = NULL;
	x = msgrecv (sendfile,0);
	if (x != SCMOK)
		goaway ("Error sending file to client");
}

int
sendone ( TREE *t, va_list ap )
{
	register int x,fd;

	if ((t->Tflags&FNEEDED) == 0)	/* only send needed files */
		return (SCMOK);
	if ((t->Tmode&S_IFMT) == S_IFDIR) /* send no directories this pass */
		return (SCMOK);
	x = msgsend ();
	if (x != SCMOK)  goaway ("Error reading receive file request from client");
	upgradeT = t;			/* upgrade file pointer */
	fd = -1;			/* no open file */
	if ((t->Tmode&S_IFMT) == S_IFREG) {
		if (!listonly && (t->Tflags&FUPDATE) == 0) {
			fd = open (t->Tname,O_RDONLY,0);
			if (fd < 0)  t->Tmode = 0;
		}
		if (t->Tmode) {
			t->Tuser = strdup (uconvert (t->Tuid));
			t->Tgroup = strdup (gconvert (t->Tgid));
		}
	}
	x = msgrecv (sendfile,fd);
	if (x != SCMOK)  goaway ("Error sending file to client");
	return (SCMOK);
}

int
senddir ( TREE *t, va_list ap)
{
	register int x;

	if ((t->Tflags&FNEEDED) == 0)	/* only send needed files */
		return (SCMOK);
	if ((t->Tmode&S_IFMT) != S_IFDIR) /* send only directories this pass */
		return (SCMOK);
	x = msgsend ();
	if (x != SCMOK)  goaway ("Error reading receive file request from client");
	upgradeT = t;			/* upgrade file pointer */
	t->Tuser = strdup (uconvert (t->Tuid));
	t->Tgroup = strdup (gconvert (t->Tgid));
	x = msgrecv (sendfile,0);
	if (x != SCMOK)  goaway ("Error sending file to client");
	return (SCMOK);
}

int
sendfile ( TREE *t, va_list ap )
{
	register int x;
	int fd = va_arg(ap,int);

	if ((t->Tmode&S_IFMT) != S_IFREG || listonly || (t->Tflags&FUPDATE))
		return (SCMOK);
	x = writefile (fd);
	if (x != SCMOK)  goaway ("Error sending file to client");
	(void) close (fd);
	return (SCMOK);
}

/*****************************************
 ***    E N D   C O N N E C T I O N    ***
 *****************************************/

void
finishup ( time_t starttime )
{
	register int x = SCMOK;
	char buf[STRINGLENGTH];
	register FILE *f;
	struct stat sbuf;
	time_t finishtime;
	int flags;
	const char *releasename;

	(void) netcrypt ((char *)NULL);
	if (protver < 6) {
		if (goawayreason != NULL)
			free (goawayreason);
		goawayreason = (char *)NULL;
		x = msggoaway();
		doneack = FDONESUCCESS;
		donereason = strdup ("Unknown");
	} else if (goawayreason == (char *)NULL)
		x = msgdone ();
	else {
		doneack = FDONEGOAWAY;
		donereason = goawayreason;
	}
	if (x == SCMEOF || x == SCMERR) {
		doneack = FDONEUSRERROR;
		donereason = strdup ("Premature EOF on network");
	} else if (x != SCMOK) {
		doneack = FDONESRVERROR;
		donereason = strdup ("Unknown SCM code");
	}
	if (doneack == FDONEDONTLOG)
		return;
	if (donereason == NULL)
		donereason = strdup ("No reason");
	if (doneack == FDONESRVERROR || doneack == FDONEUSRERROR)
		logerr ("%s", donereason);
	else if (doneack == FDONEGOAWAY)
		logerr ("GOAWAY: %s",donereason);
	else if (doneack != FDONESUCCESS)
		logerr ("Reason %d:  %s",doneack,donereason);
	goawayreason = donereason;
	cdprefix ((char *)NULL);
	(void) sprintf (buf,FILELOGFILE,collname_g);
	if (stat (buf,&sbuf) < 0 || (f = fopen (buf,"a")) == NULL)
		return;
	finishtime = time ((time_t *)NULL);
	if ((flags = fcntl (fileno (f),F_GETFL,0)) != -1) {
		flags |= O_APPEND;
		(void) fcntl (fileno (f),F_SETFL,flags);
	}
	(void) sprintf (buf,"%s ",fmttime (lasttime));
	(void) sprintf (buf,"%s%s ",buf,fmttime (starttime));
	(void) sprintf (buf,"%s%s ",buf,fmttime (finishtime));
	if ((releasename = release) == NULL)
		releasename = "UNKNOWN";
	fprintf (f,"%s%s %s %d %s\n",buf,remotehost (),releasename,
		FDONESUCCESS-doneack,donereason);
	(void) fclose (f);
}

/***************************************************
 ***    H A S H   T A B L E   R O U T I N E S    ***
 ***************************************************/

void
Hfree ( HASH **table )
{
	register HASH *h;
	register int i;
	for (i = 0; i < HASHSIZE; i++)
		while ((h = table[i])) {
			table[i] = h->Hnext;
			if (h->Hname)  free (h->Hname);
			free ((char *)h);
		}
}

HASH *Hlookup ( HASH **table, int num1, int num2 )
{
	register HASH *h;
	register int hno;
	hno = HASHFUNC(num1,num2);
	for (h = table[hno]; h && (h->Hnum1 != num1 || h->Hnum2 != num2); h = h->Hnext);
	return (h);
}

void
Hinsert ( HASH **table, int num1, int num2, char *name, TREE *tree )
{
	register HASH *h;
	register int hno;
	hno = HASHFUNC(num1,num2);
	h = (HASH *) malloc (sizeof(HASH));
	h->Hnum1 = num1;
	h->Hnum2 = num2;
	h->Hname = name;
	h->Htree = tree;
	h->Hnext = table[hno];
	table[hno] = h;
}

/*********************************************
 ***    U T I L I T Y   R O U T I N E S    ***
 *********************************************/

TREE *linkcheck ( TREE *t, int d, int i)	/* inode # and device # */
{
	register HASH *h;
	h = Hlookup (inodeH,i,d);
	if (h)  return (h->Htree);
	Hinsert (inodeH,i,d,(char *)NULL,t);
	return ((TREE *)NULL);
}

char *uconvert (int uid)
{
	register struct passwd *pw;
	register char *p;
	register HASH *u;
	u = Hlookup (uidH,uid,0);
	if (u)  return (u->Hname);
	pw = getpwuid (uid);
	if (pw == NULL) {
	  p = strdup ("");
	  return ( p );
	} /* if */
	p = strdup (pw->pw_name);
	Hinsert (uidH,uid,0,p,(TREE*)NULL);
	return (p);
}

char *gconvert (int gid)
{
	register struct group *gr;
	register char *p;
	register HASH *g;
	g = Hlookup (gidH,gid,0);
	if (g)  return (g->Hname);
	gr = getgrgid (gid);
	if (gr == NULL) {
	  p = strdup ("");
	  return ( p );
	} /* if */
	p = strdup (gr->gr_name);
	Hinsert (gidH,gid,0,p,(TREE *)NULL);
	return (p);
}

char *changeuid ( char *namep,char *passwordp, int fileuid, int filegid )
{
	char *group;
	const char *pswdp;
	struct passwd *pwd;
	struct group *grp;
	char nbuf[STRINGLENGTH];
	static char errbuf[STRINGLENGTH];

	if (namep == NULL) {
		pwd = getpwuid (fileuid);
		if (pwd == NULL) {
			(void) sprintf (errbuf,"Reason:  Unknown user id %d",
					fileuid);
			return (errbuf);
		}
		grp = getgrgid (filegid);
		if (grp)  group = strcpy (nbuf,grp->gr_name);
		else  group = NULL;
		pswdp = NULL;
	} else {
		(void) strcpy (nbuf,namep);
		group = strchr (nbuf,',');
		if (group != NULL) {
			*group++ = '\0';
			if (*group == '\0')  group = NULL;
		}
		pwd = getpwnam (nbuf);
		if (pwd == NULL) {
			(void) sprintf (errbuf,"Reason:  Unknown user %s",
					nbuf);
			return (errbuf);
		}
		if (strcmp (nbuf,DEFUSER) == 0)
			pswdp = NULL;
		else
			pswdp = passwordp ? passwordp : "";
	}
	if (getuid () != 0) {
		if (getuid () == pwd->pw_uid)
			return (NULL);
		if (strcmp (pwd->pw_name,DEFUSER) == 0)
			return (NULL);
		logerr ("Fileserver not superuser");
		strcpy ( errbuf,
			 "Reason:  fileserver is not running privileged");
		return ( errbuf );
	}
	if (namep && strcmp(pwd->pw_name, DEFUSER) != 0)
		if (strcmp(pwd->pw_passwd,(char *)crypt(pswdp,pwd->pw_passwd))) {
			strcpy (errbuf, "Reason:  Invalid password" );
			logerr ("Login failure for %s",pwd->pw_name);
			logerr ("%s",errbuf);
			return (errbuf);
		}
	if (initgroups (pwd->pw_name,pwd->pw_gid) < 0) {
		strcpy ( errbuf , "Error setting group list" );
		return ( errbuf );
	} /* if */
	if (setgid (pwd->pw_gid) < 0)
		logerr ("setgid: %%m");
	if (setuid (pwd->pw_uid) < 0)
		logerr ("setuid: %%m");
	return (NULL);
}

char *fmttime (time_t time_l)
{
	static char buf[STRINGLENGTH];
	int len;

	(void) strcpy (buf,ctime (&time_l));
	len = strlen(buf+4)-6;
	(void) strncpy (buf,buf+4,len);
	buf[len] = '\0';
	return (buf);
}
