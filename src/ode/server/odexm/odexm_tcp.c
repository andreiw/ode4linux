/*
 * COPYRIGHT NOTICE
 * Copyright (c) 1993, 1992, 1991, 1990
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
 * $Log: odexm_tcp.c,v $
 * Revision 1.1.11.1  1994/02/14  15:46:45  root
 * 	CR # 1049 - Use kill() instead of killpg() on sinix.
 * 	[1994/02/14  15:46:26  root]
 *
 * Revision 1.1.8.1  1993/11/09  16:54:24  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  16:53:08  damon]
 * 
 * Revision 1.1.6.1  1993/09/16  17:52:45  damon
 * 	Fixed COPYRIGHT NOTICE section
 * 	[1993/09/16  17:52:31  damon]
 * 
 * Revision 1.1.2.10  1993/06/23  20:06:06  marty
 * 	CR # 592 - Clean up type casting problems.
 * 	[1993/06/23  20:05:39  marty]
 * 
 * Revision 1.1.2.9  1993/05/19  19:59:00  damon
 * 	CR 515. Added handling for stdin
 * 	[1993/05/19  19:58:51  damon]
 * 
 * Revision 1.1.2.8  1993/05/04  19:07:59  damon
 * 	CR 435. Changed u_long to unsigned int
 * 	[1993/05/04  19:07:49  damon]
 * 
 * Revision 1.1.2.7  1993/04/30  15:07:40  damon
 * 	CR 463. Put in.h before tcp.h
 * 	[1993/04/30  15:07:35  damon]
 * 
 * Revision 1.1.2.6  1993/04/29  20:39:33  marty
 * 	Rearrange a few include files.
 * 	[1993/04/29  20:39:16  marty]
 * 
 * Revision 1.1.2.5  1993/03/29  18:54:43  damon
 * 	CR 436. Added htonl to status return
 * 	[1993/03/29  18:54:35  damon]
 * 
 * Revision 1.1.2.4  1993/03/29  18:30:57  damon
 * 	CR 440. Put back status return assignment
 * 	[1993/03/29  18:30:47  damon]
 * 
 * Revision 1.1.2.3  1993/03/24  15:57:02  damon
 * 	CR 440. Added odexm_cp
 * 	[1993/03/24  15:56:42  damon]
 * 
 * Revision 1.1.2.2  1993/01/19  18:49:21  damon
 * 	CR 408. Moved streams/tcp specific code into odexm_tcp.c
 * 	[1993/01/19  18:48:22  damon]
 * 	 *
 * 
 * $EndLog$
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#ifdef INC_STRINGS
#include <strings.h>
#endif
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <arpa/inet.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <sys/socket.h>
#ifdef INC_SELECT
#include <sys/select.h>
#endif
#include <netinet/in.h>
#include <pwd.h>
#include <ode/odedefs.h>
#include <ode/private/odexm.h>

#define MAXARGC	64

struct sockaddr_in peername;
struct sockaddr_in sockname;
struct sockaddr_in dataname;

typedef struct {
  unsigned short count;
  int status;
} odexm_header;

odexm_header * header;
char buf [OXMBUFSIZE];

#define ANAME_SZ	32
extern char lname[ANAME_SZ];
int sigsock;
int datasock;
int compat_sock; /* either datasock or 0 for compatability */
extern u_char tempmode;
extern u_short tempslot;
extern char tempdir[];
extern char temppath[MAXPATHLEN];
extern char *tempfile;

extern int errdesc;
extern u_char debug;
extern u_char flags;
extern int batch;
extern int exit_status;

extern char uniq_str [];

#ifndef NCARGS
#define NCARGS 1024
#endif
extern char args [NCARGS];
extern char ** arglist;

/*
 * PROTOTYPES
 */
void
setup_control(void);
void
diag(const char * fmt, ... );
void
warn(const char * fmt, ... );
void
ewarn(const char * fmt, ... );
void
fatal(const char * fmt, ... ) ;
void
efatal(const char * fmt, ... );

void
setup_connections(void)
{
    int i;
    struct linger linger;
    struct sockaddr_in s_in;
    u_short port;
    u_short sigport;
    u_short dataport;

    header = (odexm_header *) buf;

    /*
     * setup file descriptors
     */
    for (;;) {
	errno = 0;
	i = dup(0);
	if (i == -1) {
	    efatal("dup failed");
	}
	if (i > 2)
	    break;
    }
    errdesc = i;
    if (dup2(i, 0) < 0)
	efatal("dup2 #0 failed");
    if (dup2(i, 1) < 0)
	efatal("dup2 #1 failed");
    if (dup2(i, 2) < 0)
	efatal("dup2 #2 failed");
    (void) close(i);
    errdesc = 2;

    /*
     * setup main (command) connection
     */
    i = 1;
    if (setsockopt(0, SOL_SOCKET, SO_KEEPALIVE, (char *)&i, sizeof(i)) < 0)
	ewarn("setsockopt (SO_KEEPALIVE)");
#ifdef DONT_SO_LINGER
    if (setsockopt(0, SOL_SOCKET, SO_LINGER, (char *)&i, sizeof(i)) < 0 )
#else
    linger.l_onoff = 1;
    linger.l_linger = 60;
    if (setsockopt(0, SOL_SOCKET, SO_LINGER, (char *)&linger, sizeof(linger))
                   < 0)
#endif
	ewarn("setsockopt (SO_LINGER)");
    i = sizeof(peername);
    if (getpeername(0, (struct sockaddr *)&peername, &i) < 0)
	efatal("getpeername");
    i = sizeof(sockname);
    if (getsockname(0, (struct sockaddr *)&sockname, &i) < 0)
	efatal("getsockname");
    if (debug)
	diag("connection from %s (%d)",
	     inet_ntoa(peername.sin_addr), ntohs(peername.sin_port));

    /*
     * get flags
     */
    if (read(0, &flags, sizeof(flags)) != sizeof(flags))
	efatal("server read");

    if ( flags == 1 || flags == 3 )
      debug = 1;
    /* if */
    if ( flags > 1 )
      batch = 1;
    /* if */

    /*
     * setup control (signal) connection
     */
    if (read(0, (char *)&sigport, sizeof(sigport)) != sizeof(sigport))
	efatal("server read");
    sigsock = socket(AF_INET, SOCK_STREAM, 0);
    if (sigsock < 0)
	efatal("socket");
    memcpy (&s_in, &sockname, sizeof(s_in));
    s_in.sin_port = 0;
    if (bind(sigsock, (struct sockaddr *)&s_in, sizeof(s_in)) < 0)
	efatal("bind");
    i = sizeof(s_in);
    if (getsockname(sigsock, (struct sockaddr *)&s_in, &i) < 0)
	efatal("getsockname");
    port = s_in.sin_port;
    if (write(1, (char *)&port, sizeof(port)) != sizeof(port))
	efatal("write");
    memcpy(&s_in, &peername, sizeof(s_in));
    s_in.sin_port = sigport;
    if (connect(sigsock, (struct sockaddr *)&s_in, sizeof(s_in)) < 0)
	efatal("connect");

    /*
     * start control process (actually parent)
     */
    setup_control();
    /*
     * safe now for debugging
     */

    /*
     * setup data transfer connection
     */
    if (debug)
	diag("reading data port");
    if (read(0, (char *)&dataport, sizeof(dataport)) != sizeof(dataport))
	efatal("server read");
    if (debug)
	diag("data port %d", ntohs(dataport));
    datasock = socket(AF_INET, SOCK_STREAM, 0);
    if (datasock < 0)
	efatal("socket");
    memcpy(&s_in, &sockname, sizeof(s_in));
    s_in.sin_port = 0;
    if (bind(datasock, (struct sockaddr *)&s_in, sizeof(s_in)) < 0)
	efatal("bind");
    i = sizeof(s_in);
    if (getsockname(datasock, (struct sockaddr *)&s_in, &i) < 0)
	efatal("getsockname");
    port = s_in.sin_port;
    if (debug)
	diag("sending data port %d", ntohs(port));
    if (write(1, (char *)&port, sizeof(port)) != sizeof(port))
	efatal("write");
    memcpy(&s_in, &peername, sizeof(s_in));
    s_in.sin_port = dataport;
    if (connect(datasock, (struct sockaddr *)&s_in, sizeof(s_in)) < 0)
	efatal("connect");
    if (debug)
	diag("connected to dataport");
    if ( batch )
      compat_sock = datasock;
    else
      compat_sock = 0;
    /* if */
}

void
setup_control(void)
{
    char buf2[BUFSIZ];
    int pid;
    int pv[2];
    long ready, readfrom;
    char sig;
    int i;

    (void) signal(SIGINT, SIG_DFL);
    (void) signal(SIGQUIT, SIG_DFL);
    (void) signal(SIGTERM, SIG_DFL);

    if (pipe(pv) < 0)
	efatal("pipe failed");
    pid = fork();
    if (pid == -1)
	efatal("fork failed");
    if (pid == 0) {
    (void) setsid();
	(void) close(sigsock);
	(void) close(pv[0]);
	dup2(pv[1], 2);
	(void) close(pv[1]);
	return;
    }
    (void) close(0);
    (void) close(1);
    (void) close(2);
    (void) close(pv[1]);
    readfrom = (1L<<sigsock) | (1L<<pv[0]);
    i = 1;
    ioctl(pv[0], FIONBIO, (char *)&i);
    do {
	ready = readfrom;
	if (select(16, (fd_set *)&ready, (fd_set *)0,
		   (fd_set *)0, (struct timeval *)0) < 0)
	    break;
	if (ready & (1L<<sigsock)) {
	    if (read(sigsock, &sig, 1) <= 0)
		readfrom &= ~(1L<<sigsock);
	    else
#ifdef NO_KILLPG
		kill(pid, sig);
#else
		killpg(pid, sig);
#endif
	}
	if (ready & (1L<<pv[0])) {
	    i = read(pv[0], buf2, sizeof (buf2));
	    if (i <= 0) {
		shutdown(sigsock, 1+1);
		readfrom &= ~(1L<<pv[0]);
	    } else
		(void) write(sigsock, buf2, i);
	}
    } while (readfrom);
    exit(0);
}

void
read_arglist(void)
{
    int i;
    u_char byte;
    u_short count;
    u_short length;
    char *sp;
    char *ep;
    unsigned int checksum;

    if (read(compat_sock, &byte, sizeof(byte)) != sizeof(byte))
	efatal("read needsecret failed");
    if (byte)
	efatal("request for secret");
    if (debug)
	diag("reading arglist");
    if (read(compat_sock, (char *)&count, sizeof(count)) != sizeof(count))
	efatal("server read");
    count = ntohs(count);
    if (debug)
	diag("arglist count %d", count);
    if ( ( batch && count < 1) || ( !batch && count < 3 ) || count > MAXARGC - 1)
	fatal("Invalid arg count");
    if (read(compat_sock, (char *)&length, sizeof(length)) != sizeof(length))
	efatal("server read");
    length = ntohs(length);
    if (debug)
	diag("arglist length %d", length);
    if ((int)length > NCARGS)
	fatal("Arglist too long");
    if (read(compat_sock, (char *)&tempslot, sizeof(tempslot)) != sizeof(tempslot))
	efatal("server read");
    tempslot = ntohs(tempslot);
    if (debug)
	diag("tempslot %d", tempslot);
    if ( ( batch && tempslot >= count) ||
         (!batch && tempslot >= count - 2 ) )
	fatal("Invalid temp file index");
    if (tempslot != 0) {
	if (read(compat_sock, (char *)&tempmode, sizeof(tempmode)) != sizeof(tempmode))
	    efatal("server read");
	if (debug)
	    diag("tempmode %d", tempmode);
    }
    if (read(compat_sock, (char *)&checksum, sizeof(checksum)) != sizeof(checksum))
	efatal("server read");
    checksum = ntohl(checksum);
    if (debug)
	diag("checksum %x", checksum);
    memset (args, 0, sizeof(args));
    sp = args;
    ep = args + length;
    while (ep > sp) {
	i = ep - sp;
	i = read(compat_sock, sp, i);
	if (i < 0)
	    efatal("server read");
	else if (i == 0)
	    fatal("read (eof)");
	sp += i;
    }
    check_arglist ( count, ep, sp, checksum);
}

void
authenticate_client(void)
{
    u_char secretlen;
    u_short userid;

    if (read(compat_sock, (char *)&userid, sizeof(userid)) != sizeof(userid))
	efatal("server read");
    userid = ntohs(userid);
    if (debug)
	diag("read userid %d", userid);
    if (read(compat_sock, &secretlen, sizeof(secretlen)) != sizeof(secretlen))
	efatal("server read");
    if (debug)
	diag("read secretlen %d", secretlen);
    if (secretlen != 0)
	efatal("non-zero secretlen");
    if (read(compat_sock, &secretlen, sizeof(secretlen)) != sizeof(secretlen))
	efatal("server read");
    if (secretlen <= 0 || secretlen >= ANAME_SZ)
	fatal("bad local name length");
    if (read(compat_sock, lname, secretlen) != secretlen)
	efatal("server read??");
    if (debug)
	diag("local name %s", lname);
}

void
read_config_info (void)
{
    u_char len;
    if (read(datasock, &len, sizeof(len)) != sizeof(len))
	efatal("server read");
    if (read(datasock, uniq_str, len) != len)
	efatal("server read??");
} /* end read_config_info */

BOOLEAN get_exists ( char * exists )
{
  return ( read(datasock, exists, sizeof(*exists)) == sizeof(*exists) );
} /* end get_exists */

BOOLEAN get_perm ( u_short * perm )
{
  int len;
  len = read(datasock, (char *)perm, sizeof(*perm));
  *perm = ntohs(*perm);
  return ( len == sizeof(*perm) );
} /* end get_perm */

BOOLEAN get_count ( unsigned int * count )
{
  int len;

  len = read(datasock, (char *)count, sizeof(*count));
  *count = ntohl(*count);
  return (len == sizeof(*count) );
} /* end get_count */

void
get_buffer ( char * buffer, int * len, int readsize, int fd )
{
  int error;
        if ((*len = read(datasock, buffer, readsize)) <= 0) {
            error = errno;
            (void) close(fd);
            (void) unlink(tempfile);
            (void) rmdir(tempdir);
            if (len == 0)
                fatal("premature EOF");
            errno = error;
            efatal("server read", error);
        }
}

void
handle_io ( int in_fd, int out_fd )
{
  int cc;
  char * bufptr;
  fd_set imask;
  int high_fd;

 /*
  * init
  */
  if ( in_fd > datasock ) {
    high_fd = in_fd+1;
  } else {
    high_fd = datasock+1;
  } /* if */

  (*header).status = 0;
  bufptr = buf + sizeof (*header);

  for (;; ) {
    FD_ZERO ( &imask );
    FD_SET ( in_fd, &imask );
    FD_SET ( datasock, &imask );
    if ( select ( high_fd, (fd_set *)&imask, (fd_set *)0, (fd_set *)0,
                  ( struct timeval *)0 ) < 1 ) {
      continue;
    } /* if */
    if ( FD_ISSET ( in_fd, &imask ) ) {
      cc = read ( in_fd, bufptr, sizeof (buf) - sizeof (*header) );
      if ( cc < 0)
        if ( errno == EWOULDBLOCK)
          continue;
        /* if */
      /* if */
      if ( cc == 0 )
        break;
      /* if */
      (*header).count = htons ( (unsigned short )cc );
      write ( datasock, buf, cc + sizeof (*header) );
    } else if ( FD_ISSET ( datasock, &imask ) ) {
      read ( datasock, header, sizeof (*header) );
      (*header).count = ntohs ( (*header).count );
      cc = read ( datasock, bufptr, (*header).count );
      if ( cc < 0)
        if ( errno == EWOULDBLOCK)
          continue;
        /* if */
      /* if */
      if ( cc == 0 )
        break;
      /* if */
      write ( out_fd, bufptr, cc );
    } /* if */
  } /* while */
} /* end handle_io */

void
transmit_status2 (void)
{
  int op;

  if (debug)
    diag ( "transmitting status %d", exit_status );
  (*header).status = htonl (exit_status);
  (*header).count = 0;
  op=1;
  setsockopt(datasock, IPPROTO_TCP, TCP_NODELAY, (char *)&op ,
             sizeof(op) );
  write ( datasock, buf, sizeof(*header) );
  op=0;
   setsockopt(datasock, IPPROTO_TCP, TCP_NODELAY, (char *)&op ,
              sizeof(op) );
}

BOOLEAN put_exists ( char * exists )
{
  return (write(datasock, exists, sizeof(*exists)) == sizeof(*exists) );
} /* end put_exists */

BOOLEAN put_perm ( u_short * perm )
{
  *perm = htons(*perm);
  return (write(datasock, (char *)perm, sizeof(*perm)) == sizeof(*perm) );
} /* end put_perm */

BOOLEAN put_count ( unsigned int * count )
{
  *count = htonl(*count);
  return ( write(datasock, (char *)count, sizeof(*count)) == sizeof(*count) );
} /* end put_count */

void
put_buffer ( char * buffer, int len, int * len2, int fd )
{
  int error;
        if ((*len2 = write(datasock, buffer, len)) != len) {
            error = errno;
            (void) close(fd);
            (void) unlink(tempfile);
            (void) rmdir(tempdir);
            errno = error;
            efatal("write", error);
        }

}

void
transmit_status(void)
{
    unsigned int status;
    int op;

    if (debug)
	diag("sending status %d", exit_status);
    if ( batch ) {
      (*header).count = 0;
      (*header).status = htonl (exit_status);
      op=1;
      setsockopt(datasock, IPPROTO_TCP, TCP_NODELAY, (char *)&op ,
                 sizeof(op) );
      write ( datasock, buf, sizeof(*header) );
      op=0;
      setsockopt(datasock, IPPROTO_TCP, TCP_NODELAY, (char *)&op ,
                 sizeof(op) );
    } else {
      status = htonl((unsigned int)exit_status);
      if (write(datasock, (char *)&status, sizeof(status)) != sizeof(status))
  	efatal("write failed");
    } /* if */
}
