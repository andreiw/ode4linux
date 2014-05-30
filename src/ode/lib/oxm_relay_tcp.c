/*
 * @OSF_FREE_COPYRIGHT@
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
 */
/*
 * HISTORY
 * $Log: oxm_relay_tcp.c,v $
 * Revision 1.9.21.1  1993/11/09  20:08:28  damon
 * 	CR 463. Pedantic changes
 * 	[1993/11/09  20:08:05  damon]
 *
 * Revision 1.9.19.1  1993/09/28  15:50:50  damon
 * 	CR 690. Free tempfile only if alloc made
 * 	[1993/09/28  15:50:40  damon]
 * 
 * Revision 1.9.16.1  1993/08/19  19:02:49  damon
 * 	CR 622. Removed bzero and rindex bsdisms
 * 	[1993/08/19  18:57:29  damon]
 * 
 * Revision 1.9.12.10  1993/07/02  15:17:46  damon
 * 	CR 598. Read header more carefully
 * 	[1993/07/02  15:17:35  damon]
 * 
 * Revision 1.9.12.9  1993/07/01  14:11:20  damon
 * 	CR 597. Changed longs to ints
 * 	[1993/07/01  14:11:10  damon]
 * 
 * Revision 1.9.12.8  1993/06/28  16:51:26  damon
 * 	CR 592. Cleaned up some mem leaks
 * 	[1993/06/28  16:50:03  damon]
 * 
 * Revision 1.9.12.7  1993/05/27  20:20:16  marty
 * 	CR # 558 - more typecasting
 * 	[1993/05/27  20:20:02  marty]
 * 
 * Revision 1.9.12.6  1993/05/27  20:17:04  marty
 * 	CR # 558 - Type casting for rios_aix
 * 	[1993/05/27  20:16:39  marty]
 * 
 * Revision 1.9.12.5  1993/05/26  18:07:51  damon
 * 	CR 553. Check for and use tcp service number on cmd line
 * 	[1993/05/26  17:17:58  damon]
 * 
 * Revision 1.9.12.4  1993/05/19  19:56:44  damon
 * 	CR 515. Added handling for stdin
 * 	[1993/05/19  19:56:08  damon]
 * 
 * Revision 1.9.12.3  1993/03/24  16:16:39  damon
 * 	CR 449. Added TCP_NODELAY
 * 	[1993/03/24  16:15:37  damon]
 * 
 * Revision 1.9.12.2  1993/03/11  22:33:18  damon
 * 	CR 256. Added dummy read to satisfy Ultrix
 * 	[1993/03/11  21:41:37  damon]
 * 
 * Revision 1.9.6.19  1993/01/06  20:31:40  damon
 * 	CR 240. Changed SERV_NUM back to 549. Was 548 for tests
 * 	[1993/01/06  20:31:29  damon]
 * 
 * Revision 1.9.6.18  1992/12/03  17:23:12  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:09:39  damon]
 * 
 * Revision 1.9.6.17  1992/11/23  16:51:13  damon
 * 	CR 334. Added call to ntohs for header.count
 * 	[1992/11/23  16:50:58  damon]
 * 
 * Revision 1.9.6.16  1992/11/13  15:20:43  root
 * 	Added INC_SELECT conditional include of select.h
 * 	[1992/11/13  15:13:55  root]
 * 
 * Revision 1.9.6.15  1992/11/12  18:28:06  damon
 * 	CR 329. Changed include of sys/error.h to error.h
 * 	[1992/11/12  18:09:02  damon]
 * 
 * Revision 1.9.6.14  1992/11/09  21:04:30  damon
 * 	CR 329. Oops. Moved include of stdlib out of sys
 * 	[1992/11/09  21:03:16  damon]
 * 
 * Revision 1.9.6.13  1992/11/09  20:28:37  damon
 * 	CR 329. Added include of stdlib.h
 * 	[1992/11/09  20:25:46  damon]
 * 
 * Revision 1.9.6.12  1992/11/09  15:13:04  damon
 * 	CR 328. Removed extraneous debug code
 * 	[1992/11/09  15:02:43  damon]
 * 
 * Revision 1.9.6.11  1992/11/05  20:53:16  damon
 * 	CR 296. Changed memcopy to memcpy
 * 	[1992/11/05  20:53:03  damon]
 * 
 * Revision 1.9.6.10  1992/11/05  20:38:52  damon
 * 	CR 296. Cleaned up warnings.
 * 	[1992/11/05  20:38:27  damon]
 * 
 * Revision 1.9.6.9  1992/10/29  16:48:45  damon
 * 	CR 324. Changed sin to s_in
 * 	[1992/10/29  16:48:33  damon]
 * 
 * Revision 1.9.6.8  1992/10/14  17:04:28  damon
 * 	CR 295. changed errmsg to strerror
 * 	[1992/10/14  17:03:52  damon]
 * 
 * Revision 1.9.6.7  1992/10/13  16:30:59  damon
 * 	CR 240. Fixed some problems
 * 	[1992/10/13  16:29:53  damon]
 * 
 * Revision 1.9.6.6  1992/09/21  19:16:47  damon
 * 	CR 240. Changed from kxct.c
 * 	[1992/09/21  19:16:27  damon]
 * 
 * 	Changed debug flag to indicate new protocol
 * 	Now using newer rc files
 * 	Now detects EOF of command execution
 * 	[1992/09/03  19:55:27  damon]
 * 
 * Revision 1.9.6.3  1992/06/16  23:09:27  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:53:36  damon]
 * 
 * Revision 1.9.4.2  1992/03/11  22:17:58  root
 * 	Changed 1 select call
 * 	[1992/03/11  22:17:38  root]
 * 
 * Revision 1.9  1991/12/05  21:04:15  devrcs
 * 	Made kxct services number a define: SERV_NUM
 * 	[91/09/04  13:08:54  damon]
 * 
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:10:34  mckeen]
 * 
 * 	rcsid/RCSfile header cleanup
 * 	[90/12/01  18:57:04  dwm]
 * 
 * Revision 1.7  90/10/07  21:55:19  devrcs
 * 	Added EndLog Marker.
 * 	[90/09/29  14:10:51  gm]
 * 
 * Revision 1.6  90/07/17  12:36:28  devrcs
 * 	More changes for gcc.
 * 	[90/07/04  22:30:37  gm]
 * 
 * Revision 1.5  90/05/24  23:12:25  devrcs
 * 	Removed kerberos authentication.
 * 	[90/05/05  18:40:11  gm]
 * 
 * Revision 1.4  90/04/14  00:53:07  devrcs
 * 	Changes for new authentication protocol.
 * 	[90/03/06  20:22:08  gm]
 * 
 * Revision 1.3  90/01/02  19:59:32  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.2  89/12/26  10:48:31  gm
 * 	Created.
 * 	[89/12/23            gm]
 * 
 * $EndLog$
 */
#if !defined(lint) && !defined(_NOIDENT)
static char rcsid[] = "@(#)$RCSfile: oxm_relay_tcp.c,v $ $Revision: 1.9.21.1 $ (OSF) $Date: 1993/11/09 20:08:28 $";
#endif
/*
 * odexm - command execution
 */
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#ifdef INC_SELECT
#include <sys/select.h>
#endif
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdarg.h>
#include <ode/odedefs.h>

#define SERV_NUM 549         /* number associated with odexm in /etc/services */
#define OXMBUFSIZE 16384

#define SEND_OVER	1
#define WANT_BACK	2

int service_number = SERV_NUM;
static int sigsock;
static int datasock;
static u_char debug;

struct sockaddr_in peername;
struct sockaddr_in sockname;
char *hostname;
int sock;
u_short sigport;
u_short dataport;
u_int cksum;

/*
 * PROTOTYPES
 */
void
diag( const char * fmt, ... );
int
wait_for_child( pid_t );
void
send_authentication(void);
void
send_config_info (void);
void
send_arglist( int argc, char **argv, int tempslot, int tempmode );
int
transmit_data( char *file, int mode );
void
handle_io (void);
int
receive_data( char *file, int mode );
void sendsig(int);

    char *p;
    char *tempfile;
    int rc;
#ifdef notdef
    char buf[BUFSIZ];
    int child;
    int cc;
    int i;
    int status;
    u_char byte;
    int len;
#endif
    pid_t pid;
    int s;
    struct hostent *hp;
    struct servent *sp;
    struct sockaddr_in s_in;
    u_short port;
  char * uniq_str;
  char * owner;

int odexm_begin ( char *host, char *us, int dbg )
{
  int i;
  int status;
  u_char flags;

    debug = (dbg != 0);
if (debug)
diag("odexm entered");
  uniq_str = us;
    /*
     * create main connection
     */
    (void) memset((char *)&peername, 0, sizeof(peername));
    peername.sin_port = htons( service_number );
if (debug)
diag("host lookup");
    hp = gethostbyname(host);
    if (hp == NULL) {
	fprintf(stderr, "Unknown host: %s\n", host);
	return(-1);
    }
if (debug)
diag("hostname %s", hp->h_name);
    hostname = strdup(hp->h_name);
    if (hostname == NULL) {
	fprintf(stderr, "strdup: %s", strerror ( errno ) );
	return(-1);
    }
    peername.sin_family = hp->h_addrtype;
    (void) memcpy( (char *)&peername.sin_addr, (char *)hp->h_addr,
		 sizeof(hp->h_addr));
if (debug) diag("socket");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
	fprintf(stderr, "socket: %s\n", strerror(errno));
	return(-1);
    }
if (debug) diag("connect");
    if (connect(sock, (struct sockaddr *)&peername, sizeof(peername)) < 0) {
	fprintf(stderr, "connect: %s\n", strerror(errno));
	(void) close(sock);
	return(-1);
    }
    i = sizeof(sockname);
if (debug) diag("getsockname");
    if (getsockname(sock, (struct sockaddr *) &sockname, &i) < 0) {
	fprintf(stderr, "getsockname: %s\n", strerror(errno));
	(void) close(sock);
	return(-1);
    }

    /*
     * indicate debugging option
     */
if (debug) diag("write debug");
    flags = debug + 2;
    if (write(sock, (char *)&flags, sizeof(flags)) != sizeof(flags)) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(sock);
	return(-1);
    }

    /*
     * create control connection
     */
if (debug) diag("socket control");
    sigsock = socket(AF_INET, SOCK_STREAM, 0);
    if (sigsock < 0) {
	fprintf(stderr, "socket: %s\n", strerror(errno));
	(void) close(sock);
	return(-1);
    }
    memcpy(&s_in, &sockname, sizeof(s_in));
    s_in.sin_port = 0;
if (debug) diag("bind control");
    if (bind(sigsock, (struct sockaddr *)&s_in, sizeof(s_in)) < 0) {
	fprintf(stderr, "bind: %s\n", strerror(errno));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
    i = sizeof(s_in);
if (debug) diag("getsockname control");
    if (getsockname(sigsock, (struct sockaddr *)&s_in, &i) < 0) {
	fprintf(stderr, "getsockname: %s\n", strerror(errno));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
    port = s_in.sin_port;
if (debug) diag("listen control");
    if (listen(sigsock, 1) < 0) {
	fprintf(stderr, "listen: %s\n", strerror(errno));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
if (debug) diag("write control port");
    if (write(sock, (char *)&port, sizeof(port)) != sizeof(port)) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
if (debug) diag("read control port");
    if (read(sock, (char *)&sigport, sizeof(sigport)) != sizeof(sigport)) {
	fprintf(stderr, "client read1: %s\n", strerror(errno));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
if (debug) diag("accept control");
    if ((s = accept(sigsock, (struct sockaddr *)&s_in, &i)) < 0) {
	fprintf(stderr, "accept: %s\n", strerror(errno));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
    (void) close(sigsock);
    sigsock = s;
    if (i != sizeof(s_in)) {
	fprintf(stderr, "accept: len %d vs %d\n", i, sizeof(s_in));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
    if (memcmp(&peername.sin_addr, &s_in.sin_addr, sizeof(peername.sin_addr))) {
	fprintf(stderr, "accept: connection from wrong host: %s\n",
		inet_ntoa(s_in.sin_addr));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
    if (s_in.sin_port != sigport) {
	fprintf(stderr, "accept: connection from wrong port: %d vs %d\n",
		ntohs(s_in.sin_port), ntohs(sigport));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }

    /*
     * setup child for work
     */
if (debug) diag("fork");
    pid = fork();
    if (pid == -1) {
	fprintf(stderr, "fork: %s\n", strerror(errno));
	(void) close(sigsock);
	(void) close(sock);
	return(-1);
    }
    if (pid != 0) {			/* child does work, parent waits */
	(void) close(sock);
	(void) free(hostname);
	status = wait_for_child(pid);
if (debug)
diag("odexm exited");
        exit ( 0 );
    }
    (void) close(sigsock);

    /*
     * create data connection
     */
    datasock = socket(AF_INET, SOCK_STREAM, 0);
    if (datasock < 0) {
	fprintf(stderr, "socket: %s\n", strerror(errno));
	(void) close(sock);
	exit(-1);
    }
    memcpy(&s_in, &sockname, sizeof(s_in));
    s_in.sin_port = 0;
    if (bind(datasock, (struct sockaddr *)&s_in, sizeof(s_in)) < 0) {
	fprintf(stderr, "bind: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    i = sizeof(s_in);
    if (getsockname(datasock, (struct sockaddr *)&s_in, &i) < 0) {
	fprintf(stderr, "getsockname: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    port = s_in.sin_port;
    if (listen(datasock, 1) < 0) {
	fprintf(stderr, "listen: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if (write(sock, (char *)&port, sizeof(port)) != sizeof(port)) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    errno = 0;
    if (read(sock, (char *)&dataport, sizeof(dataport)) != sizeof(dataport)) {
	fprintf(stderr, "client read2: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if ((s = accept(datasock, (struct sockaddr *)&s_in, &i)) < 0) {
	fprintf(stderr, "accept: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    (void) close(datasock);
    datasock = s;
    if (i != sizeof(s_in)) {
	fprintf(stderr, "accept: len %d vs %d\n", i, sizeof(s_in));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if (memcmp(&peername.sin_addr, &s_in.sin_addr, sizeof(peername.sin_addr))) {
	fprintf(stderr, "accept: connection from wrong host: %s\n",
		inet_ntoa(s_in.sin_addr));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if (s_in.sin_port != dataport) {
	fprintf(stderr, "accept: connection from wrong port: %d vs %d\n",
		ntohs(s_in.sin_port), ntohs(dataport));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    /*
     * send authentication
     */
    send_authentication();
    send_config_info ();
    return ( 0 );
} /* end odexm_begin */

int
odexm ( int tempmode, int tempslot, int argc, char **argv, BOOLEAN special )
{
  int i;

    /*
     * adjust argument list for tempslot
     */
    if (tempslot != 0) {
	tempfile = strdup(argv[tempslot]);
	if ((p = strrchr(tempfile, '/')) != NULL)
	    p++;
	else
	    p = tempfile;
        free(argv[tempslot]);
	argv[tempslot] = strdup(p);
	if (argv[tempslot] == NULL) {
	    fprintf(stderr, "strdup: %s", strerror(errno));
	    (void) close(datasock);
	    (void) close(sock);
	    exit(-1);
	}
    }

    /*
     * authenticate with server
     */
    cksum = 0;
/*
    p = uniq_str;
    while (*p != '\0')
	cksum += ((unsigned)(*p++));
    p = owner;
    while (*p != '\0')
	cksum += ((unsigned)(*p++));
*/
    for (i = 0; i < argc; i++) {
	p = argv[i];
	while (*p != '\0')
	    cksum += ((unsigned)(*p++));
    }

    /*
     * send argument list description
     */
    send_arglist(argc, argv, tempslot, tempmode);

  if ( special )
    return ( 0 );
  /* if */
    /*
     * send temporary file
     */
    if (tempslot != 0 && transmit_data(tempfile, tempmode) < 0) {
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    handle_io ();
    /*
     * receive temporary file
     */
    if (tempslot != 0 && receive_data(tempfile, tempmode) < 0) {
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if ( tempslot != 0 ) {
      free(tempfile);
    } /* if */
  /*
   * receive exit code
   */
  handle_io ();
  return ( 0 ); 
} /* end odexm */

void
odexm_end (void)
{
  char dummy;
  int len;

  /*
   * This code seems to clear state information the indicates
   * to Ultrix that there is still data in the socket, even though
   * 'len' is always 0. DO NOT REMOVE THIS UNLESS THE BUG IS
   * FOUND!!
   */
  len = read ( datasock, (char *)&dummy, 1 );
  close(datasock);
  close(sock);

  if (debug)
  diag("odex exited");


} /* end odexm_end */

int
get_stderr (void)
{
  int i;
  int cc;
  char buf[BUFSIZ];

  fd_set imask;

    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
        signal(SIGINT, sendsig);
    if (signal(SIGQUIT, SIG_IGN) != SIG_IGN)
        signal(SIGQUIT, sendsig);
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
        signal(SIGTERM, sendsig);
    i = 1;
    ioctl(sigsock, FIONBIO, &i);
    for (;;) {
        FD_ZERO ( &imask );
        FD_SET ( sigsock, &imask );
        if ( select ( sigsock + 1, (fd_set *)&imask, (fd_set *)0, (fd_set *)0,
                    ( struct timeval *) NULL ) < 1) {
            if (errno != EINTR) {
                (void) fprintf(stderr, "select: %s\n", strerror(errno));
                (void) close(sigsock);
                (void) kill(pid, SIGKILL);
                return(-1);
            }
            continue;
        }
        if ( FD_ISSET ( sigsock, &imask ) ) {
            errno = 0;
            cc = read(sigsock, buf, sizeof(buf) );
            if (cc < 0 && errno == EWOULDBLOCK)
               cc = 0;
            else {
                if ( cc <= 0) {
                  break;
                }
                (void) write(2, buf, cc );
            }
        }
    }
  return ( 0 );
} /* end get_stderr */

int
wait_for_child( pid_t w_pid )
{
    pid_t child;
    int status;

    get_stderr ();
    do {
	child = wait(&status);
    } while (child != w_pid && child != -1);
    (void) close(sigsock);
    if (child == -1) {
	(void) fprintf(stderr, "wait: %s\n", strerror(errno));
	return(-1);
    }
    if (WIFSIGNALED(status) || WEXITSTATUS(status) == 0377)
	return(-1);
    return(WEXITSTATUS(status));
}

static int buf_len;
static char send_buf [16384];

/*
 * This code makes oxm_relay_tcp/odexm faster, but there is
 * probably a way to get the write command to do this for us.
 * Only really works in the case of a command fully contained
 * within odexm that does not involve a temporary file.
 */
static
void
flush_buffer (void)
{
  int op=1;
  setsockopt(datasock, IPPROTO_TCP, TCP_NODELAY, (char *)&op, sizeof(op) );
  write(datasock, send_buf, buf_len );
  op=0;
  setsockopt(datasock, IPPROTO_TCP, TCP_NODELAY, (char *)&op, sizeof(op) );
  buf_len = 0;
}

static void
buffered_write ( char * fill, int size )
{
  if ( buf_len + size > 16384 )
    flush_buffer ();
  memcpy ( send_buf + buf_len, fill, size );
  buf_len = buf_len + size;
}

void
send_arglist( int argc, char **argv, int tempslot, int tempmode )
{
    int length;
    u_short count;
    int i;
    u_char byte;

    buf_len = 0;
    /*
     * indicate that we have no secrets
     */
    byte = 0;
#ifdef notdef
    if (write(datasock, &byte, sizeof(byte)) != sizeof(byte)) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
#endif
    buffered_write ((char *)&byte, sizeof(byte));
    count = htons((u_short)(argc));
#ifdef notdef
    if (write(datasock, (char *)&count, sizeof(count)) != sizeof(count)) {
	fprintf(stderr, "write argc error: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
#endif
    buffered_write ((char *)&count, sizeof(count));
    length = 0;
    for (i = 0; i < argc; i++)
	length += strlen(argv[i])+1;
    count = htons((u_short)length);
#ifdef notdef
    if (write(datasock, (char *)&count, sizeof(count)) != sizeof(count)) {
	fprintf(stderr, "write length error: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
#endif
    buffered_write ((char *)&count, sizeof(count));
    count = htons((u_short)tempslot);
#ifdef notdef
    if (write(datasock, (char *)&count, sizeof(count)) != sizeof(count)) {
	fprintf(stderr, "write tempslot error: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
#endif
    buffered_write ((char *)&count, sizeof(count));
    if (tempslot != 0) {
	if (tempmode == 0) {
	    fprintf(stderr, "tempfile requested without file transfer\n");
	    (void) close(datasock);
	    (void) close(sock);
	    exit(-1);
	}
	byte = tempmode;
#ifdef notdef
	if (write(datasock, &byte, sizeof(byte)) != sizeof(byte)) {
	    fprintf(stderr, "write tempmode error: %s\n", strerror(errno));
	    (void) close(datasock);
	    (void) close(sock);
	    exit(-1);
	}
#endif
    buffered_write ((char *)&byte, sizeof(byte));
    }
    cksum = htonl(cksum);
#ifdef notdef
    if (write(datasock, (char *)&cksum, sizeof(cksum)) != sizeof(cksum)) {
	fprintf(stderr, "write cksum error: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
#endif
    buffered_write ((char *)&cksum, sizeof(cksum));
    for (i = 0; i < argc; i++) {
	length = strlen(argv[i])+1;
#ifdef notdef
	if (write(datasock, argv[i], length) != length) {
	    fprintf(stderr, "write argv[%d] error: %s\n",
		 i, strerror(errno));
	    (void) close(datasock);
	    (void) close(sock);
	    exit(-1);
	}
#endif
        buffered_write (argv[i], length );
    }
    flush_buffer();
}

void
send_authentication(void)
{
    u_short count;
    int len;
    u_char byte;
    char *user;

    count = htons((u_short)getuid());
    if (write(datasock, (char *)&count, sizeof(count)) != sizeof(count)) {
	fprintf(stderr, "write userid error: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    count = ntohs(count);
    byte = 0;
    if (write(datasock, &byte, sizeof(byte)) != sizeof(byte)) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if ((user = getenv("USER")) == NULL) {
	fprintf(stderr, "getenv: USER not defined\n");
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    len = strlen(user);
    byte = len;
    if (write(datasock, &byte, sizeof(byte)) != sizeof(byte)) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if (write(datasock, user, len) != len) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
}

void
send_config_info (void)
{
    int len;
    u_char byte;

    len = strlen(uniq_str);
    byte = len;
    if (write(datasock, &byte, sizeof(byte)) != sizeof(byte)) {
	fprintf(stderr, "write: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
    if (write(datasock, uniq_str, len) != len) {
	fprintf(stderr, "write uniq_str: %s\n", strerror(errno));
	(void) close(datasock);
	(void) close(sock);
	exit(-1);
    }
} /* end send_config_info */

typedef struct {
  unsigned short count;
  int status;
} odex_header;

void
handle_io (void)
{
  char buf [OXMBUFSIZE];
  int len;
  odex_header header;
  int count;
  fd_set imask;
  int chunk_size;
  char * hd_ptr;

  for (;;) {
    FD_ZERO ( &imask );
    FD_SET ( datasock, &imask );
    FD_SET ( 0, &imask );
    if ( select ( datasock + 1, (fd_set *)&imask, (fd_set *)0, (fd_set *)0,
                  ( struct timeval *) NULL ) < 1 ) {
      continue;
    } /* if */
    if ( FD_ISSET ( datasock, &imask ) ) {
      count = sizeof(header);
      hd_ptr = (char *)&header;
      while ( count > 0 ) {
        len = read ( datasock, hd_ptr, count );
        count -= len;
        hd_ptr = hd_ptr + len;
      }
      header.count = ntohs ( header.count );
      write ( 1, (char *)&header, sizeof(header) );
      count = header.count;
      if ( count == 0 )
        break;
      /* if */
      while ( count > 0 ) {
        len = read ( datasock, buf, count );
        write ( 1, buf, len );
        count -= len;
      } /* while */
    } else if ( FD_ISSET ( 0, &imask ) ) {
      len = read ( 0, (char *)&header, sizeof(header ) );
      count = header.count;
      header.count = htons ( header.count );
      write ( datasock, (char *)&header, sizeof(header) );
      while ( count > 0 ) {
        if ( count > sizeof(buf) ) {
          chunk_size = sizeof(buf);
        } else {
          chunk_size = count;
        } /* if */
        len = read ( 0, buf, chunk_size );
        write ( datasock, buf, len );
        count -= len;
      } /* while */
    } /* if */
  } /* for */
} /* end handle_io */

/*
relay_stdout ()
{
  char inbuf[BUFSIZ];
  int i;
  char *bp;
  int cc, rc;
  int child;
  char buf[BUFSIZ];
  int readfrom,rfds,wfds,writeto;

    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
	signal(SIGINT, sendsig);
    if (signal(SIGQUIT, SIG_IGN) != SIG_IGN)
	signal(SIGQUIT, sendsig);
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
	signal(SIGTERM, sendsig);
    i = 1;
    ioctl(sock, FIONBIO, &i);
    readfrom = (1<<sock) | (1<<0);
    writeto = 0;
    bp = NULL;
    for (;;) {
	rfds = readfrom;
	wfds = writeto;
	if ((rfds & (1<<sock)) == 0 && wfds == 0)
	    break;
	if (select(16, &rfds, &wfds, 0, 0) < 0) {
	    if (errno != EINTR) {
		perror("select");
		exit(-1);
	    }
	    continue;
	}
	if (rfds & (1<<sock)) {
	    errno = 0;
	    cc = read(sock, buf, sizeof(buf));
	    if (cc <= 0) {
		if (errno != EWOULDBLOCK)
		    readfrom &= ~(1<<sock);
	    } else
		(void) write(1, buf, cc);
	}
	if (wfds & (1<<sock)) {
	    cc = write(sock, bp, rc);
	    if (cc < 0) {
		if (errno == EWOULDBLOCK)
		    continue;
		readfrom &= ~(1<<0);
		writeto &= ~(1<<sock);
		(void) shutdown(sock, 1);
		continue;
	    }
	    rc -= cc; bp += cc;
	    if (rc != 0)
		continue;
	    writeto &= ~(1<<sock);
	    readfrom |= (1<<0);
	    bp = NULL;
	}
	if (bp != NULL)
	    continue;
	if (rfds & (1<<0)) {
	    errno = 0;
	    rc = read(0, inbuf, sizeof(inbuf));
	    if (rc <= 0) {
		if (errno != EWOULDBLOCK) {
		    readfrom &= ~(1<<0);
		    writeto &= ~(1<<sock);
		    (void) shutdown(sock, 1);
		    continue;
		}
		continue;
	    }
	    bp = inbuf;
	    readfrom &= ~(1<<0);
	    writeto |= (1<<sock);
	}
    }
}
*/

void
sendsig(int signo)
{
    char sig = (char) signo;

    (void) write(sigsock, &sig, 1);
}

static char buffer[10240];

int
transmit_data( char *file, int mode )
{
    u_int count;
    u_short perm;
    int bufsize;
    int fd;
    struct stat st;
    int len, len2;
    char exists;


    if (lstat(file, &st) < 0) {
	if (errno != ENOENT) {
	    fprintf(stderr, "lstat %s: %s\n", file, strerror(errno));
	    return(-1);
	}
	if ((mode&SEND_OVER) == 0)
	    return(0);
	exists = 0;
    } else {
	if ((mode&SEND_OVER) == 0) {
	    fprintf(stderr, "file %s exists and would be overwritten\n", file);
	    return(-1);
	}
	if ((st.st_mode&S_IFMT) != S_IFREG ) {
	    fprintf(stderr, "%s not a regular file\n", file );
	    return(-1);
	}
	exists = 1;
    }
    if (write(datasock, (char *)&exists, sizeof(exists)) != sizeof(exists)) {
	fprintf(stderr, "write failed: %s", strerror(errno));
	return(-1);
    }
    if (!exists)
	return(0);
    perm = st.st_mode&0777;
    perm = htons(perm);
    if (write(datasock, (char *)&perm, sizeof(perm)) != sizeof(perm)) {
	fprintf(stderr, "write failed: %s", strerror(errno));
	return(-1);
    }
    count = st.st_size;
    count = htonl(count);
    if (write(datasock, (char *)&count, sizeof(count)) != sizeof(count)) {
	fprintf(stderr, "write failed: %s", strerror(errno));
	return(-1);
    }
    count = st.st_size;
    if (count == 0)
	return(0);
    if ((fd = open(file, O_RDONLY, 0)) < 0) {
	fprintf(stderr, "open failed: %s\n", strerror(errno));
	return(-1);
    }
    if ((bufsize = count) > 10*1024) {
	bufsize = 10*1024;
    }
    while (count != 0) {
	if ((len = read(fd, buffer, bufsize)) <= 0) {
	    if (len == 0)
		fprintf(stderr, "premature EOF\n");
	    else
		fprintf(stderr, "client read3: %s\n", strerror(errno));
	    (void) close(fd);
	    return(-1);
	}
	if ((len2 = write(datasock, buffer, len)) != len) {
	    fprintf(stderr, "write: %s\n", strerror(errno));
	    (void) close(fd);
	    return(-1);
	}
	count -= len;
	if (count < bufsize)
	    bufsize = count;
    }
    if (close(fd) < 0) {
	fprintf(stderr, "close: %s\n", strerror(errno));
	return(-1);
    }
    return(0);
}

int
receive_data( char *file, int mode )
{
    u_int count;
    u_short perm;
    int bufsize;
    int fd;
    int len, len2;
    char exists;
    int readsize;

    if (debug) {
	fprintf(stderr, "client: receiving data\n"); fflush(stderr);
    }
    if ((mode&WANT_BACK) == 0)
	return(0);
    if (read(datasock, (char *)&exists, sizeof(exists)) != sizeof(exists)) {
	fprintf(stderr, "client read failed2: %s\n", strerror(errno));
	return(-1);
    }
    if (debug) {
	fprintf(stderr, "client: exists %d\n", exists); fflush(stderr);
    }
    if (!exists) {
	(void) unlink(file);
	return(0);
    }
    if (read(datasock, (char *)&perm, sizeof(perm)) != sizeof(perm)) {
	fprintf(stderr, "client read failed3: %s\n", strerror(errno));
	return(-1);
    }
    perm = ntohs(perm);
    if (debug) {
	fprintf(stderr, "client: perm %#o\n", perm); fflush(stderr);
    }
    if (read(datasock, (char *)&count, sizeof(count)) != sizeof(count)) {
	fprintf(stderr, "client read failed4: %s\n", strerror(errno));
	return(-1);
    }
    count = ntohl(count);
    if (debug) {
	fprintf(stderr, "client: count %d\n", count); fflush(stderr);
    }
    (void) chmod(file, (int)((perm&0777)|0200));
    if ((fd = open(file, O_WRONLY|O_TRUNC|O_CREAT, 0600)) < 0) {
	fprintf(stderr, "open failed: %s\n", strerror(errno));
	return(-1);
    }
    if (fchmod(fd, (mode_t)(perm&0777)) < 0) {
	fprintf(stderr, "fchmod failed: %s\n", strerror(errno));
	return(-1);
    }
    if (count == 0) {
	(void) close(fd);
	return(0);
    }
    /*
     * should check for space on disk, but could be expensive and unreliable
     */
    if ((bufsize = count) > 10*1024) {
	bufsize = 10*1024;
    }
    if (debug) {
	fprintf(stderr, "client: bufsize %d\n", bufsize); fflush(stderr);
    }
    while (count != 0) {
	if (debug) {
	    fprintf(stderr, "client: loop count %d\n", count); fflush(stderr);
	}
        if ( count > bufsize )
          readsize = bufsize;
        else
          readsize = count;
        /* if */
	if ((len = read(datasock, buffer, readsize)) <= 0) {
	    if (len == 0)
		fprintf(stderr, "premature EOF\n");
	    else
		fprintf(stderr, "client read4: %s\n", strerror(errno));
	    (void) close(fd);
	    return(-1);
	}
	if (debug) {
	    fprintf(stderr, "client: read %d bytes\n", len);
	}
	if ((len2 = write(fd, buffer, len)) != len) {
	    fprintf(stderr, "write: %s\n", strerror(errno));
	    (void) close(fd);
	    return(-1);
	}
	if (debug) {
	    fprintf(stderr, "client: wrote %d bytes\n", len2); fflush(stderr);
	}
	count -= len;
	if (count < bufsize)
	    bufsize = count;
    }
    if (close(fd) < 0) {
	fprintf(stderr, "close: %s\n", strerror(errno));
	return(-1);
    }
    return(0);
}

/*VARARGS1*/
void
diag( const char * fmt, ... )
{
    char buf[BUFSIZ];
    char *ptr;
    va_list vargs;
    struct timeval tv;

    (void) gettimeofday(&tv, (struct timezone *)0);
    (void) sprintf(buf, "%d.%d= ", tv.tv_sec, tv.tv_usec);
    ptr = buf + strlen(buf);
    va_start(vargs, fmt);
    ptr += vsprintf(ptr, fmt, vargs);
    va_end(vargs);
    *ptr++ = '\n';
    *ptr = '\0';
    (void) fputs(buf, stderr);
    (void) fflush(stderr);
}
