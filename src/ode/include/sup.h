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
 * $Log: sup.h,v $
 * Revision 1.3.5.5  1994/02/18  21:52:22  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:41  damon]
 *
 * Revision 1.3.5.4  1994/02/18  18:21:32  damon
 * 	CR 1056. Added protos
 * 	[1994/02/18  18:21:23  damon]
 * 
 * Revision 1.3.5.3  1994/02/17  16:25:45  damon
 * 	CR 1056. Moved from bin/sup
 * 	[1994/02/17  16:25:24  damon]
 * 
 * Revision 1.3.5.2  1994/02/15  20:37:43  damon
 * 	CR 1051. More pedantic
 * 	[1994/02/15  20:37:20  damon]
 * 
 * Revision 1.3.5.1  1994/02/15  17:36:15  damon
 * 	CR 1051. Made pedantic changes
 * 	[1994/02/15  17:35:48  damon]
 * 
 * Revision 1.3.2.6  1992/12/02  19:52:55  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:09  damon]
 * 
 * Revision 1.3.2.5  1992/11/13  15:20:01  root
 * 	Placed comments around garbabe at the end of #else
 * 	and #endif statements.
 * 	[1992/11/13  14:59:15  root]
 * 
 * Revision 1.3.2.4  1992/11/11  18:34:20  damon
 * 	CR 329. Replaced explicit decs with include of portable.h
 * 	[1992/11/11  18:32:07  damon]
 * 
 * Revision 1.3.2.3  1992/09/24  19:00:08  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:18:49  gm]
 * 
 * Revision 1.3.2.2  1992/08/06  16:03:03  damon
 * 	CR 265. Changed to used ODE parser.
 * 	[1992/08/06  16:02:11  damon]
 * 
 * Revision 1.3  1991/12/05  20:54:09  devrcs
 * 	Added definitions of TRUE and FALSE
 * 	[91/08/28  20:43:39  mckeen]
 * 
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:39  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:37:03  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:17:09  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:38  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:44  gm]
 * 
 * Revision 1.3  90/04/14  00:51:03  devrcs
 * 	Support for permission failures in NFS.
 * 	[90/03/06  20:17:21  gm]
 * 
 * Revision 1.2  90/01/02  19:56:17  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:05  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Moved coll.dir from supservers to supfiles.
 * 	[89/08/23            gm0w]
 * 
 * 	Added host=<hostfile> support to releases file.
 * 	[88/03/18            gm0w]
 * 
 * 	Added crosspatch support.  Removed nameserver support.
 * 	[87/12/27            gm0w]
 * 
 * 	Added TREELIST and other changes for "release" support.
 * 	[87/06/27            gm0w]
 * 
 * 	Version 6 of the network protocol, better support to reflect errors
 * 	back to server logfile.
 * 	[87/05/25            dwp]
 * 
 * 	Merged divergent CS and EE versions.
 * 	[87/05/21            chriss]
 * 
 * 	Added FILESUPTDEFAULT definition.
 * 	[86/09/19            mja]
 * 
 * 	Removed FILESRVBUSYWAIT.  Now uses exponential backoff.
 * 	[86/06/07            gm0w]
 * 
 * 	Added numeric port numbers to use when port names are not in the
 * 	host table.
 * 	[86/05/30            gm0w]
 * 
 * 	Update protocol version to 5 for name server protocol change to
 * 	allow multiple repositories per collection.  Added FILESRVBUSYWAIT
 * 	of 5 minutes.  Added FILELOCK file to indicate collections that
 * 	should be exclusively locked when upgraded.
 * 	[86/01/04            gm0w]
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
 * sup.h -- declarations for sup, supnamesrv, supfilesrv
 *
 * VERSION NUMBER for any program is given by:  a.b (c)
 * where	a = PROTOVERSION	is the protocol version #
 *		b = PGMVERSION		is program # within protocol
 *		c = scmversion		is communication module version
 *			(i.e. operating system for which scm is configured)
 */

#ifndef _SUP_H
#define _SUP_H
#include <ode/odedefs.h>
#include <stdarg.h>
#include <time.h>

/*
 * Command line switches
 */
#define SYSUPGRADE_OP	"-s"
#define UPGRADETIME_OP	"-t"
#define RESPAUSE_OP	"-R"
#define NETDEBUG_OP	"-N"
#define PORTDEBUG_OP	"-P"
#define XPATCH_OP	"-X"
#define ALWAYS_OP	"-a"
#define BACKUP_OP	"-b"
#define NOBACKUP_OP	"-B"
#define DELETE_OP	"-d"
#define NODELETE_OP	"-D"
#define EXEC_OP		"-e"
#define NOEXEC_OP	"-E"
#define FAKE_OP		"-f"
#define LOCALUPGRADE_OP	"-l"
#define MAIL_OP		"-m"
#define OLD_OP		"-o"
#define NOOLD_OP	"-O"
#define TRACE_OP	"-v"

#ifndef TRUE
#define  TRUE                 1
#endif
#ifndef FALSE
#define  FALSE                0
#endif

/* PGMVERSION is defined separately in each program */
extern const char scmversion[];		/* string version of scm */
#define PROTOVERSION 8			/* version of network protocol */
#define SCANVERSION  2			/* version of scan file format */

/* TCP servers for name server and file server */
#define FILEPORT	"supfilesrv"
#define FILEPORTNUM	871
#define DEBUGFPORT	"supfiledbg"
#define DEBUGFPORTNUM	1127

/* Data files used in scan.c */
#define FILELIST	"sup/%s/%s"
#define FILESCAN	"sup/%s/%s"
#define FILEHOST	"sup/%s/%s"
#define FILELISTDEF	"list"
#define FILESCANDEF	"scan"
#define FILEHOSTDEF	"host"
#define DEFRELEASE	"default"

/* Data files used in sup.c */
#define FILEBASEDEFAULT	"/usr/%s" /* also supfilesrv and supscan */
#ifdef EE_XXX
#define FILESUPDEFAULT	"%s/supfiles/coll.list"
#define FILESUPTDEFAULT	"%s/supfiles/coll.what"
#define FILEHOSTS	"%s/supfiles/coll.host"
#else  /* EE_XXX */
#define FILESUPDEFAULT	"%s/lib/supfiles/coll.list"
#define FILESUPTDEFAULT	"%s/lib/supfiles/coll.what"
#define FILEHOSTS	"%s/lib/supfiles/coll.host"
#endif /* EE_XXX */
#define FILEBKDIR	"%s/BACKUP"
#define FILEBACKUP	"%s/BACKUP/%s"
#define FILELAST	"sup/%s/last"
#define FILELASTTEMP	"sup/%s/last.temp"
#define FILELOCK	"sup/%s/lock"	/* also supfilesrv */
#define FILEREFUSE	"sup/%s/refuse"
#define FILEWHEN	"sup/%s/when"

/* Data files used in supfilesrv.c */
#define FILEXPATCH	"%s/sup/xpatch.host"
#ifdef EE_XXX
#define FILEDIRS	"%s/supfiles/coll.dir" /* also supscan */
#else /* EE_XXX */
#define FILEDIRS	"%s/lib/supfiles/coll.dir" /* also supscan */
#endif /* EE_XXX */
#define FILECRYPT	"sup/%s/crypt"
#define FILELOGFILE	"sup/%s/logfile"
#define FILEPREFIX	"sup/%s/prefix"	/* also supscan */
#define FILERELEASES	"sup/%s/releases" /* also supscan */

/* String length */
#define STRINGLENGTH	2000

/* Password transmission encryption key */
#define PSWDCRYPT	"SuperMan"
/* Test string for encryption */
#define CRYPTTEST	"Hello there, Sailor Boy!"

/* Default directory for system sup information */
#ifndef	DEFDIR
#ifdef EE_XXX
#define DEFDIR		"/etc"
#else  /* EE_XXX */
#define DEFDIR		"/usr/cs"
#endif /* EE_XXX */
#endif /* DEFDIR */

/* Default login account for file server */
#ifndef	DEFUSER
#define DEFUSER		"anon"
#endif /* DEFUSER */

/* subroutine return codes */
#define SCMOK		(1)		/* routine performed correctly */
#define SCMEOF		(0)		/* read EOF on network connection */
#define SCMERR		(-1)		/* error occurred during routine */

/* data structure for describing a file being upgraded */

struct treestruct {
/* fields for file information */
	char *Tname;			/* path component name */
	int Tflags;			/* flags of file */
	int Tmode;			/* st_mode of file */
	char *Tuser;			/* owner of file */
	int Tuid;			/* owner id of file */
	char *Tgroup;			/* group of file */
	int Tgid;			/* group id of file */
	int Tctime;			/* inode modification time */
	int Tmtime;			/* data modification time */
	struct treestruct *Tlink;	/* tree of link names */
	struct treestruct *Texec;	/* tree of execute commands */
/* fields for sibling AVL tree */
	int Tbf;			/* balance factor */
	struct treestruct *Tlo,*Thi;	/* ordered sibling tree */
};
typedef struct treestruct TREE;

/* data structure to represent a list of trees to upgrade */

struct tliststruct {
	struct tliststruct *TLnext;	/* next entry in tree list */
/* fields for tree information */
	char *TLname;			/* release name for tree */
	char *TLprefix;			/* prefix of tree */
	char *TLlist;			/* name of list file */
	char *TLscan;			/* name of scan file */
	char *TLhost;			/* name of host file */
	TREE *TLtree;			/* tree of files to upgrade */
};
typedef struct tliststruct TREELIST;

/* bitfield not defined in stat.h */
#define S_IMODE		  07777		/* part of st_mode that chmod sets */

/* flag bits for files */
#define FNEW		     01		/* ctime of file has changed */
#define FBACKUP		     02		/* backup of file is allowed */
#define FNOACCT		     04		/* don't set file information */
#define FUPDATE		    010		/* only set file information */
#define FNEEDED		0100000		/* file needed for upgrade */

/* version 3 compatability */
#define	FCOMPAT		0010000		/* Added to detect execute commands to send */

/* message types now obsolete */
#define MSGFEXECQ	(115)
#define MSGFEXECNAMES	(116)

/* flag bits for files in list of all files */
#define ALLNEW		      01
#define ALLBACKUP	      02
#define ALLEND		      04
#define ALLDIR		     010
#define ALLNOACCT	     020
#define ALLSLINK	    0100

/* flag bits for file mode word */
#define MODELINK	  010000
#define MODEDIR		  040000
#define MODESYM		 0100000
#define MODENOACCT	 0200000
#define MODEUPDATE	01000000

/* blocking factor for filenames in list of all file names */
#define BLOCKALL	32

/* end version 3 compatability */

#define MAXCHILDREN 8			/* maximum number of children allowed
					   to sup at the same time */

typedef int (*PFI)( TREE *, va_list);

/* scm and stree external declarations */
const char *remotehost(void);
TREE *Tinsert(TREE **, const char *, int );
TREE *Tsearch(TREE *, const char *);
TREE *Tlookup(TREE *, char * );

void
makescanlists (void);
void
goaway (const char *fmt,...);
int
Tprocess ( TREE *t, int (*f)( TREE *, va_list ), ... );
int
Trprocess ( TREE *t, int (*f)( TREE *, va_list ), ... );
void
Tfree ( TREE **t );
int
expand( char *, char **, int );

int
writemsg (int);
int
writemend(void);
int
writeint(int);
int
writestring(const char *);
int
writemnull(int);
int
writemint(int, int);
int
writemstr(int, char *);
int
writefile (int );
int
readmsg (int );
int
readmend(void);
int
readskip (void);
int
readint (int *);
int
readstring ( char ** );
int
readfile (int );
int
readmnull (int );
int
readmint(int, int *);
int
readmstr(int, char **);
int
prereadcount (int *);
int
readflush (void);

int
scmerr (int ,const char *,...);
void
logerr(const char *,...);
void
loginfo ( const char *, ... );
void
logopen ( const char * );
void
logquit(int ,const char *,...);

int
byteswap ( int );

int
servicesetup ( const char *);
int
service (void);
int
serviceprep (void);
int
servicekill (void);
int
serviceend (void);
int
dobackoff ( int *, int *);
int
request ( const char *, char *, int *);
int
requestend (void);
int
thishost ( char *);

int
msgsignon (void);
int
msgsignonack (void);
int
msgsetup (void);
int
msgsetupack (void);
int
netcrypt (const char *);
int
msgcrypt (void);
int
msgcryptok (void);
int
msglogin (void);
int
msglogack (void);
int
msgxpatch (void);
void
crosspatch (void);
int
msggoaway (void);
int
msgrefuse (void);
int
msglist (void);
int
msgneed (void);
int
msgdeny (void);
int
msgsend (void);
int
msgrecv (PFI xferfile,...);
int
msgdone (void);

void
cdprefix ( char *);

int
matchhost ( char *);
int
samehost (void );
BOOLEAN
getrelease ( char * );

void
getscanlists (void);

char *fmttime ( time_t );
void
prtime (void);

void
getnams (void);

#endif
