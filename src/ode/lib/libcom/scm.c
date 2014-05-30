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
 * $Log: scm.c,v $
 * Revision 1.3.8.3  1994/02/18  18:25:35  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  18:25:24  damon]
 *
 * Revision 1.3.8.2  1994/02/17  18:49:41  damon
 * 	CR 1056. Moved from ./bin/sup/
 * 	[1994/02/17  18:49:30  damon]
 * 
 * Revision 1.3.8.1  1994/02/08  22:24:55  damon
 * 	CR 1049. Added include of portable.h
 * 	[1994/02/08  22:24:43  damon]
 * 
 * Revision 1.3.5.1  1993/11/24  15:48:06  damon
 * 	CR 793. Check for EINTR on first read in service()
 * 	[1993/11/24  15:47:54  damon]
 * 
 * Revision 1.3.2.5  1992/12/02  19:52:49  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:04  damon]
 * 
 * Revision 1.3.2.4  1992/11/09  22:15:49  damon
 * 	CR 296. Removed warnings
 * 	[1992/11/09  22:10:34  damon]
 * 
 * Revision 1.3.2.3  1992/09/24  18:59:53  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:18:29  gm]
 * 
 * Revision 1.3.2.2  1992/02/13  15:09:11  gm
 * 	Fixed OSF1 compilation warnings.  Removed old CMU code.
 * 	[1992/02/09  02:16:57  gm]
 * 
 * Revision 1.3  1991/12/05  20:53:59  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:21  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:46:50  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:16:53  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:21  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:28  gm]
 * 
 * Revision 1.4  90/07/17  12:26:35  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:04:16  gm]
 * 
 * Revision 1.3  90/04/14  00:50:56  devrcs
 * 	Support for permission failures in NFS.
 * 	[90/03/06  20:17:10  gm]
 * 
 * Revision 1.2  90/01/02  19:56:14  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:32:55  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.4  89/11/29  17:40:38  bww
 * 	Updated variable argument list usage.  Changed
 * 	to use CMU conditionals rather than CMUCS.
 * 	[89/11/29  17:31:19  bww]
 * 
 * Revision 1.11  89/08/03  19:49:03  mja
 * 	Updated to use v*printf() in place of _doprnt().
 * 	[89/04/19            mja]
 * 
 * Revision 0.0  88/02/11            gm0w
 * 	Moved sleep into computeBackoff, renamed to dobackoff.
 * 	[88/02/11            gm0w]
 * 
 * Revision 0.0  88/02/10            gm0w
 * 	Added timeout to backoff.
 * 	[88/02/10            gm0w]
 * 
 * Revision 0.0  87/12/27            gm0w
 * 	Removed nameserver support.
 * 	[87/12/27            gm0w]
 * 
 * Revision 0.0  87/09/09            gm0w
 * 	Fixed to depend less upon having name of remote host.
 * 	[87/09/09            gm0w]
 * 
 * Revision 0.0  87/05/25            dwp
 * 	Extracted backoff/sleeptime computation from "request" and
 * 	created "computeBackoff" so that I could use it in sup.c when
 * 	trying to get to nameservers as a group.
 * 	[87/05/25            dwp]
 * 
 * Revision 0.0  87/05/21            chriss
 * 	Merged divergent CS and EE versions.
 * 	[87/05/21            chriss]
 * 
 * Revision 0.0  87/05/02            gm0w
 * 	Added some bullet-proofing code around hostname calls.
 * 	[87/05/02            gm0w]
 * 
 * Revision 0.0  87/03/31            dan
 * 	Fixed for 4.3.
 * 	[87/03/31            dan]
 * 
 * Revision 0.0  86/05/30            gm0w
 * 	Added code to use known values for well-known ports if they are
 * 	not found in the host table.
 * 	[86/05/30            gm0w]
 * 
 * Revision 0.0  86/02/19            gm0w
 * 	Changed setsockopt SO_REUSEADDR to be non-fatal.  Added fourth
 * 	parameter as described in 4.3 manual entry.
 * 	[86/02/19            gm0w]
 * 
 * Revision 0.0  86/02/15            gm0w
 * 	Added call of readflush() to requestend() routine.
 * 	[86/02/15            gm0w]
 * 
 * Revision 0.0  85/12/29            gm0w
 * 	Major rewrite for protocol version 4.  All read/write and crypt
 * 	routines are now in scmio.c.
 * 	[85/12/29            gm0w]
 * 
 * Revision 0.0  85/12/14            gm0w
 * 	Added setsockopt SO_REUSEADDR call.
 * 	[85/12/14            gm0w]
 * 
 * Revision 0.0  85/12/01            gm0w
 * 	Removed code to "gracefully" handle unexpected messages.  This
 * 	seems reasonable since it didn't work anyway, and should be
 * 	handled at a higher level anyway by adhering to protocol version
 * 	number conventions.
 * 	[85/12/01            gm0w]
 * 
 * Revision 0.0  85/11/26            gm0w
 * 	Fixed scm.c to free space for remote host name when connection
 * 	is closed.
 * 	[85/11/26            gm0w]
 * 
 * Revision 0.0  85/11/07            gm0w
 * 	Fixed 4.2 retry code to reload sin values before retry.
 * 	[85/11/07            gm0w]
 * 
 * Revision 0.0  85/10/22            gm0w
 * 	Added code to retry initial connection open request.
 * 	[85/10/22            gm0w]
 * 
 * Revision 0.0  85/09/22            gm0w
 * 	Merged 4.1 and 4.2 versions together.
 * 	[85/09/22            gm0w]
 * 
 * Revision 0.0  85/09/21            gm0w
 * 	Add close() calls after pipe() call.
 * 	[85/09/21            gm0w]
 * 
 * Revision 0.0  85/06/12            sas
 * 	Converted for 4.2 sockets; added serviceprep() routine.
 * 	[85/06/12            sas]
 * 
 * Revision 0.0  85/06/04            sas
 * 	Created for 4.2 BSD.
 * 	[85/06/04            sas]
 * 
 * $EndLog$
 */
/*
 * SUP Communication Module for 4.3 BSD
 *
 * SUP COMMUNICATION MODULE SPECIFICATIONS:
 *
 * IN THIS MODULE:
 *
 * CONNECTION ROUTINES
 *
 *   FOR SERVER
 *	servicesetup (port)	establish TCP port connection
 *	  char *port;			name of service
 *	service ()		accept TCP port connection
 *	servicekill ()		close TCP port in use by another process
 *	serviceprep ()		close temp ports used to make connection
 *	serviceend ()		close TCP port
 *
 *   FOR CLIENT
 *	request (port,hostname,retry) establish TCP port connection
 *	  char *port,*hostname;		  name of service and host
 *	  int retry;			  true if retries should be used
 *	requestend ()		close TCP port
 *
 * HOST NAME CHECKING
 *	p = remotehost ()	remote host name (if known)
 *	  char *p;
 *	i = samehost ()		whether remote host is also this host
 *	  int i;
 *	i = matchhost (name)	whether remote host is same as name
 *	  int i;
 *	  char *name;
 *
 * RETURN CODES
 *	All procedures return values as indicated above.  Other routines
 *	normally return SCMOK on success, SCMERR on error.
 *
 * COMMUNICATION PROTOCOL
 *
 *	Described in scmio.c.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ode/portable.h>
#include <ode/sup.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <stdlib.h>
#include <unistd.h>

const char scmversion[] = "OSF1";

/*************************
 ***    M A C R O S    ***
 *************************/

/* networking parameters */
#define NCONNECTS 5

/*********************************************
 ***    G L O B A L   V A R I A B L E S    ***
 *********************************************/

extern char program[];			/* name of program we are running */
extern int progpid;			/* process id to display */

int netfile = -1;			/* network file descriptor */

static int sock = -1;			/* socket used to make connection */
static struct in_addr remoteaddr;	/* remote host address */
static char *remotename = NULL;		/* remote host name */
static int swapmode;			/* byte-swapping needed on server? */

/*
 * FORWARD DECLARATIONS
 */
static
char *myhost (void);

#if __STDC__
int scmerr (int errnum,const char *fmt,...)
#else
/* VARARGS */
int scmerr (va_alist)
va_dcl
#endif
{
#if !__STDC__
	int errnum;
	const char *fmt;
#endif
	va_list ap;

	(void) fflush (stdout);
	if (progpid > 0)
		fprintf (stderr,"%s %d: ",program,progpid);
	else
		fprintf (stderr,"%s: ",program);
#if __STDC__
	va_start(ap,fmt);
#else
	va_start(ap);
	errnum = va_arg(ap,int);
	fmt = va_arg(ap,char *);
#endif
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	if (errnum >= 0)
		fprintf (stderr,": %s\n",strerror(errnum));
	else
		fprintf (stderr,"\n");
	(void) fflush (stderr);
	if (errnum >= 0)
	    errno = errnum;
	else
	    errno = 0;
	return (SCMERR);
}

/***************************************************
 ***    C O N N E C T I O N   R O U T I N E S    ***
 ***    F O R   S E R V E R                      ***
 ***************************************************/

int
servicesetup ( const char *server)		/* listen for clients */
{
	struct sockaddr_in s_in;
	struct servent *sp;
	short port;
	int one = 1;

	if (myhost () == NULL)
		return (scmerr (-1,"Local hostname not known"));
	if ((sp = getservbyname(server,"tcp")) == 0) {
		if (strcmp(server, FILEPORT) == 0)
			port = htons((u_short)FILEPORTNUM);
		else if (strcmp(server, DEBUGFPORT) == 0)
			port = htons((u_short)DEBUGFPORTNUM);
		else
			return (scmerr (-1,"Can't find %s server description",server));
	} else
		port = sp->s_port;
	endservent ();
	sock = socket (AF_INET,SOCK_STREAM,0);
	if (sock < 0)
		return (scmerr (errno,"Can't create socket for connections"));
	if (setsockopt (sock,SOL_SOCKET,SO_REUSEADDR,(char *)&one,sizeof(int)) < 0)
		(void) scmerr (errno,"Can't set SO_REUSEADDR socket option");
	memset ((char *)&s_in,0,sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = port;
	if (bind (sock,(struct sockaddr *)&s_in,sizeof(s_in)) < 0)
		return (scmerr (errno,"Can't bind socket for connections"));
	if (listen (sock,NCONNECTS) < 0)
		return (scmerr (errno,"Can't listen on socket"));
	return (SCMOK);
}

int
service (void)
{
	struct sockaddr_in from;
	int x,len;
        int res;

	remotename = NULL;
	len = sizeof (from);
	do {
		netfile = accept (sock,(struct sockaddr *)&from,&len);
	} while (netfile < 0 && errno == EINTR);
	if (netfile < 0)
		return (scmerr (errno,"Can't accept connections"));
	remoteaddr = from.sin_addr;
        do { 
	  res = read(netfile,(char *)&x,sizeof(int));
        } while ( res != sizeof(int) && errno == EINTR);
        if ( res != sizeof(int) )
		return (scmerr (errno,"Can't transmit data on connection"));
	if (x == 0x01020304)
		swapmode = 0;
	else if (x == 0x04030201)
		swapmode = 1;
	else
		return (scmerr (-1,"Unexpected byteswap mode %x",x));
	return (SCMOK);
}

int
serviceprep (void)		/* kill temp socket in daemon */
{
	if (sock >= 0) {
		(void) close (sock);
		sock = -1;
	}
	return (SCMOK);
}

int
servicekill (void)		/* kill net file in daemon's parent */
{
	if (netfile >= 0) {
		(void) close (netfile);
		netfile = -1;
	}
	if (remotename) {
		free (remotename);
		remotename = NULL;
	}
	return (SCMOK);
}

int
serviceend (void)		/* kill net file after use in daemon */
{
	if (netfile >= 0) {
		(void) close (netfile);
		netfile = -1;
	}
	if (remotename) {
		free (remotename);
		remotename = NULL;
	}
	return (SCMOK);
}

/***************************************************
 ***    C O N N E C T I O N   R O U T I N E S    ***
 ***    F O R   C L I E N T                      ***
 ***************************************************/

int
dobackoff ( int *t, int *b )
{
	struct timeval tt;
	unsigned s;

	if (*t == 0)
		return (0);
	s = *b * 30;
	if (gettimeofday (&tt,(struct timezone *)NULL) >= 0)
		s += (tt.tv_usec >> 8) % s;
	if (*b < 32) *b <<= 1;
	if (*t != -1) {
		if (s > *t)
			s = *t;
		*t -= s;
	}
	(void) scmerr (-1,"Will retry in %d seconds",s);
	sleep (s);
	return (1);
}

/* connect to server */
int
request ( const char *server, char *hostname, int *retry )
{
	int x, backoff;
	struct hostent *h;
	struct servent *sp;
	struct sockaddr_in s_in;
	short port;

	if ((sp = getservbyname(server,"tcp")) == 0) {
		if (strcmp(server, FILEPORT) == 0)
			port = htons((u_short)FILEPORTNUM);
		else if (strcmp(server, DEBUGFPORT) == 0)
			port = htons((u_short)DEBUGFPORTNUM);
		else
			return (scmerr (-1,"Can't find %s server description",
					server));
	} else
		port = sp->s_port;
	if ((h = gethostbyname (hostname)) == NULL)
		return (scmerr (-1,"Can't find host entry for %s",hostname));
	backoff = 1;
	for (;;) {
		netfile = socket (AF_INET,SOCK_STREAM,0);
		if (netfile < 0)
			return (scmerr (errno,"Can't create socket"));
		memset ((char *)&s_in,0,sizeof(s_in));
		memcpy ((char *)&s_in.sin_addr,h->h_addr,h->h_length);
		s_in.sin_family = AF_INET;
		s_in.sin_port = port;
		if (connect(netfile,(struct sockaddr *)&s_in,sizeof(s_in)) >= 0)
			break;
		(void) scmerr (errno,"Can't connect to server for %s",server);
		(void) close(netfile);
		if (!dobackoff (retry,&backoff))
			return (SCMERR);
	}
	remoteaddr = s_in.sin_addr;
	remotename = strdup(h->h_name);
	x = 0x01020304;
	(void) write (netfile,(char *)&x,sizeof(int));
	swapmode = 0;		/* swap only on server, not client */
	return (SCMOK);
}

int
requestend (void)			/* end connection to server */
{
	(void) readflush ();
	if (netfile >= 0) {
		(void) close (netfile);
		netfile = -1;
	}
	if (remotename) {
		free (remotename);
		remotename = NULL;
	}
	return (SCMOK);
}

/*************************************************
 ***    H O S T   N A M E   C H E C K I N G    ***
 *************************************************/

static
char *myhost (void)		/* find my host name */
{
	struct hostent *h;
	static char name[256];

	if (name[0] != '\0')
		return (name);
	if (gethostname (name,256) < 0)
		return (NULL);
	if ((h = gethostbyname (name)) == NULL)
		return (NULL);
	(void) strcpy (name,h->h_name);
	return (name);
}

const char *remotehost (void)	/* remote host name (if known) */
{
	if (remotename == NULL)
		remotename = strdup(inet_ntoa(remoteaddr));
	if (remotename == NULL)
		return("UNKNOWN");
	return (remotename);
}

int thishost ( char *host )
{
	register struct hostent *h;
	char *name;

	if ((name = myhost ()) == NULL)
		logquit (1,"Can't find my host entry");
	h = gethostbyname (host);
	if (h == NULL) return (0);
	return (strcasecmp (name,h->h_name) == 0);
}

int samehost (void)		/* is remote host same as local host? */
{
	char *name;
	struct hostent *h;

	if ((name = myhost ()) == NULL)
		return (0);
	if (remotename == NULL) {
		h = gethostbyaddr ((char *)&remoteaddr,sizeof(remoteaddr),
				AF_INET);
		if (h == 0)
			remotename = strdup (inet_ntoa(remoteaddr));
		else
			remotename = strdup (h->h_name);
	}
	return (strcasecmp (remotename,name) == 0);
}

int matchhost ( char *name )	/* is this name of remote host? */
{
	struct hostent *h;

	if (remotename == NULL) {
		h = gethostbyaddr ((char *)&remoteaddr,sizeof(remoteaddr),
				AF_INET);
		if (h == 0)
			remotename = strdup (inet_ntoa(remoteaddr));
		else
			remotename = strdup (h->h_name);
	}
	if ((h = gethostbyname (name)) == 0)
		return (0);
	return (strcasecmp (remotename,h->h_name) == 0);
}

/*******************************************************
 ***    I N T E G E R   B Y T E - S W A P P I N G    ***
 *******************************************************/

union intchar {
	int ui;
	char uc[sizeof(int)];
};

int byteswap ( int in )
{
	union intchar x,y;
	register int ix,iy;

	if (swapmode == 0)  return (in);
	x.ui = in;
	iy = sizeof(int);
	for (ix=0; ix<sizeof(int); ix++) {
		--iy;
		y.uc[iy] = x.uc[ix];
	}
	return (y.ui);
}
