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
 * $Log: scmio.c,v $
 * Revision 1.3.13.3  1994/06/22  18:51:46  marty
 * 	Reorg for encryption
 * 	[1994/06/22  18:50:34  marty]
 *
 * Revision 1.3.13.2  1994/02/18  18:25:38  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  18:25:26  damon]
 * 
 * Revision 1.3.13.1  1994/02/17  18:49:45  damon
 * 	CR 1056. Moved from ./bin/sup/
 * 	[1994/02/17  18:49:32  damon]
 * 
 * Revision 1.3.11.1  1993/08/19  21:25:57  damon
 * 	CR 622. Removed conditional on include of stdio.h
 * 	[1993/08/19  21:25:38  damon]
 * 
 * Revision 1.3.8.2  1993/05/04  18:35:38  damon
 * 	CR 435. Changed a long to an int to work on 32/64 bit platforms
 * 	[1993/05/04  18:35:19  damon]
 * 
 * Revision 1.3.2.7  1992/12/02  19:52:51  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:06  damon]
 * 
 * Revision 1.3.2.6  1992/09/24  18:59:56  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:18:37  gm]
 * 
 * Revision 1.3.2.5  1992/06/16  23:09:05  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:58:08  damon]
 * 
 * Revision 1.3.5.2  1992/03/10  16:55:08  damon
 * 	Added conditional include of select using INC_SELECT.
 * 	Synched with OSF/1 sup
 * 	Port to sparc_sunos
 * 	[1992/03/10  13:57:55  damon]
 * 
 * Revision 1.3  1991/12/05  20:54:03  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:27  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:46:57  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:16:58  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:27  devrcs
 * 	Fixed return value for readfile.
 * 	[90/09/25  21:06:18  gm]
 * 
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:33  gm]
 * 
 * Revision 1.4  90/07/17  12:26:39  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:04:26  gm]
 * 
 * Revision 1.3  90/04/14  00:51:00  devrcs
 * 	Support for permission failures in NFS.
 * 	[90/03/06  20:17:15  gm]
 * 
 * Revision 1.2  90/01/02  19:56:15  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:32:59  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Added crosspatch support.
 * 	[87/12/27            gm0w]
 * 
 * 	Found error in debuging code for readint().
 * 	[87/06/28            gm0w]
 * 
 * 	Added code to readdata to "push" data back into the data buffer.
 * 	Added prereadcount() to return the message count size after
 * 	reading it and then pushing it back into the buffer.  Clear
 * 	any encryption when a GOAWAY message is detected before reading
 * 	the reason string. [V5.19]
 * 	Put a timeout on reading from the network.
 * 	[86/10/02            ern]
 * 
 * 	Renamed "howmany" parameter to routines "encode" and "decode" from
 * 	to "count" to avoid conflict with 4.3BSD macro.
 * 	[86/05/25            jjc]
 * 
 * 	Added readflush() to flush any unread data from the input
 * 	buffer.  Called by requestend() in scm.c module.
 * 	[86/02/15            gm0w]
 * 
 * 	Added register variables to decode() for speedup.  Added I/O
 * 	buffering to reduce the number or read/write system calls.
 * 	Removed readmfil/writemfil routines which were not used and were
 * 	not compatable with the other similarly defined routines anyway.
 * 	[86/01/19            gm0w]
 * 
 * 	Created from scm.c I/O and crypt routines.
 * 	[85/12/19            gm0w]
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
 * DATA ENCRYPTION
 *	netcrypt (key)		turn on/off encryption of strings and files
 *	  char *key;			encryption key
 *
 * OUTPUT TO NETWORK
 *
 *   MESSAGE START/END
 *	writemsg (msg)		start message
 *	  int msg;			message type
 *	writemend ()		end message and flush data to network
 *
 *   MESSAGE DATA
 *	writeint (i)		write int
 *	  int i;			integer to write
 *	writestring (p)		write string
 *	  char *p;			string pointer
 *	writefile (f)		write open file
 *	  int f;			open file descriptor
 *
 *   COMPLETE MESSAGE (start, one data block, end)
 *	writemnull (msg)	write message with no data
 *	  int msg;			message type
 *	writemint (msg,i)	write int message
 *	  int msg;			message type
 *	  int i;			integer to write
 *	writemstr (msg,p)	write string message
 *	  int msg;			message type
 *	  char *p;			string pointer
 *
 * INPUT FROM NETWORK
 *   MESSAGE START/END
 *	readflush ()		flush any unread data (close)
 *	readmsg (msg)		read specified message type
 *	  int msg;			message type
 *	readmend ()		read message end
 *
 *   MESSAGE DATA
 *	readskip ()		skip over one input data block
 *	readint (i)		read int
 *	  int *i;			pointer to integer
 *	readstring (p)		read string
 *	  char **p;			pointer to string pointer
 *	readfile (f)		read into open file
 *	  int f;			open file descriptor
 *
 *   COMPLETE MESSAGE (start, one data block, end)
 *	readmnull (msg)		read message with no data
 *	  int msg;			message type
 *	readmint (msg,i)	read int message
 *	  int msg;			message type
 *	  int *i;			pointer to integer
 *	readmstr (msg,p)	read string message
 *	  int msg;			message type
 *	  char **p;			pointer to string pointer
 *
 * RETURN CODES
 *	All routines normally return SCMOK.  SCMERR may be returned
 *	by any routine on abnormal (usually fatal) errors.  An
 *	unexpected MSGGOAWAY will result in SCMEOF being returned.
 *
 * COMMUNICATION PROTOCOL
 *	Messages always alternate, with the first message after
 *	connecting being sent by the client process.
 *
 *	At the end of the conversation, the client process will
 *	send a message to the server telling it to go away.  Then,
 *	both processes will close the network connection.
 *
 *	Any time a process receives a message it does not expect,
 *	the "readmsg" routine will send a MSGGOAWAY message and
 *	return SCMEOF.
 *	
 *	Each message has this format:
 *	    ----------    ------------    ------------         ----------
 *	    |msg type|    |count|data|    |count|data|   ...   |ENDCOUNT|
 *	    ----------    ------------    ------------         ----------
 *	size:  int	    int  var.	    int  var.	   	  int
 *
 *	All ints are assumed to be 32-bit quantities.  A message
 *	with no data simply has a message type followed by ENDCOUNT.
 */

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/time.h>
#include <ode/sup.h>
#include <ode/supmsg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef INC_SELECT
#include <sys/select.h>
#endif

extern int errno;

/*************************
 ***    M A C R O S    ***
 *************************/

/* end of message */
#define ENDCOUNT (-1)			/* end of message marker */
#define NULLCOUNT (-2)			/* used for sending NULL pointer */

#define RETRIES 15			/* # of times to retry io */
#define FILEXFER 2048			/* block transfer size */
#define XFERSIZE(count) ((count > FILEXFER) ? FILEXFER : count)

/*********************************************
 ***    G L O B A L   V A R I A B L E S    ***
 *********************************************/

extern int netfile;			/* network file descriptor */

int scmdebug;				/* scm debug flag */

int cryptflag = 0;			/* whether to encrypt/decrypt data */
char *cryptbuf;				/* buffer for data encryption/decryption */

extern char *goawayreason;		/* reason for goaway message */

struct buf {
	char b_data[FILEXFER];		/* buffered data */
	char *b_ptr;			/* pointer to end of buffer */
	int b_cnt;			/* number of bytes in buffer */
} buffers[2];
struct buf *bufptr;			/* buffer pointer */

/*
 * FORWARD DECLARATIONS
 */
extern int
getcryptbuf (int );
extern void
encode ( const char *,char *, int );
extern void
decode ( const char *, char *, int );

/***********************************************
 ***    O U T P U T   T O   N E T W O R K    ***
 ***********************************************/

static int
writedata ( int count, const char *data )	/* write raw data to network */
{
	register int x,tries;
	register struct buf *bp;

	if (bufptr) {
		if (bufptr->b_cnt + count <= FILEXFER) {
			memcpy (bufptr->b_ptr,data,count);
			bufptr->b_cnt += count;
			bufptr->b_ptr += count;
			return (SCMOK);
		}
		bp = (bufptr == buffers) ? &buffers[1] : buffers;
		memcpy (bp->b_data,data,count);
		bp->b_cnt = count;
		bp->b_ptr = bp->b_data + count;
		data = bufptr->b_data;
		count = bufptr->b_cnt;
		bufptr->b_cnt = 0;
		bufptr->b_ptr = bufptr->b_data;
		bufptr = bp;
	}
	tries = 0;
	for (;;) {
		errno = 0;
		x = write (netfile,data,count);
		if (x > 0)  break;
		if (errno)  break;
		if (++tries > RETRIES)  break;
		if (scmdebug > 0)
			logerr ("SCM Retrying failed network write");
	}
	if (x <= 0) {
		if (errno == EPIPE)
			return (scmerr (-1,"Network write timed out"));
		if (errno)
			return (scmerr (errno,"Write error on network"));
		return (scmerr (-1,"Write retries failed"));
	}
	if (x != count)
		return (scmerr (-1,"Write error on network returned %d on write of %d",x,count));
	return (SCMOK);
}

static int
writeblock ( int count, const char *data )	/* write data block */
{
	register int x;
	int y = byteswap(count);

	x = writedata (sizeof(int),(char *)&y);
	if (x == SCMOK)  x = writedata (count,data);
	return (x);
}

int
writemsg ( int msg ) /* write start of message */
{
	int x;

	if (scmdebug > 1)
		loginfo ("SCM Writing message %d",msg);
	if (bufptr)
		return (scmerr (-1,"Buffering already enabled"));
	bufptr = buffers;
	bufptr->b_ptr = bufptr->b_data;
	bufptr->b_cnt = 0;
	x = byteswap (msg);
	return (writedata(sizeof(int),(char *)&x));
}

int
writemend (void)		/* write end of message */
{
	register int count;
	register char *data;
	int x;

	x = byteswap (ENDCOUNT);
	x = writedata (sizeof(int),(char *)&x);
	if (x != SCMOK)  return (x);
	if (bufptr == NULL)
		return (scmerr (-1,"Buffering already disabled"));
	if (bufptr->b_cnt == 0) {
		bufptr = NULL;
		return (SCMOK);
	}
	data = bufptr->b_data;
	count = bufptr->b_cnt;
	bufptr = NULL;
	return (writedata (count, data));
}

int
writeint ( int i )		/* write int as data block */
{
	int x;
	if (scmdebug > 2)
		loginfo ("SCM Writing integer %d",i);
	x = byteswap(i);
	return (writeblock(sizeof(int),(char *)&x));
}

int
writestring (const char *p)		/* write string as data block */
{
	register int len,x;
	if (p == NULL) {
		int y = byteswap(NULLCOUNT);
		if (scmdebug > 2)
			loginfo ("SCM Writing string NULL");
		return (writedata (sizeof(int),(char *)&y));
	}
	if (scmdebug > 2)
		loginfo ("SCM Writing string %s",p);
	len = strlen (p);
	if (cryptflag) {
		x = getcryptbuf (len+1);
		if (x != SCMOK)
			return (x);
		encode (p,cryptbuf,len);
		p = cryptbuf;
	}
	return (writeblock(len,p));
}

int
writefile (int f)		/* write open file as a data block */
{
	char buf[FILEXFER];
	register int number=0,sum,filesize,x;
	int y;
	struct stat statbuf;
	int errnum=0;

	if (fstat(f,&statbuf) < 0) {
		errnum = errno;
		(void) scmerr (errno,"Can't fstat open file");
		if (protver < 8)
			return (SCMERR);
		filesize = -1;
	} else if ((filesize = statbuf.st_size) > 0) {
		number = read (f,buf,FILEXFER);
		if (number < 0) {
			errnum = errno;
			(void) scmerr (errno,"Can't read file");
			if (protver < 8)
				return (SCMERR);
			filesize = -1;
		}
		if (number == 0) {
			errnum = 0;
			(void) scmerr (-1,"Premature EOF");
			if (protver < 8)
				return (SCMERR);
			filesize = -1;
		}
	}

	y = byteswap(filesize);
	x = writedata (sizeof(int),(char *)&y);

	if (filesize == 0)
		return (x);

	if (protver >= 8 && filesize == -1) {
		y = byteswap(errnum);
		x = writedata (sizeof(int),(char *)&y);
		return (SCMOK);
	}

	if (cryptflag)  x = getcryptbuf (FILEXFER);

	sum = 0;
	while (x == SCMOK && number > 0) {
		if (cryptflag) {
			encode (buf,cryptbuf,number);
			x = writedata (number,cryptbuf);
		}
		else {
			x = writedata (number,buf);
		}
		sum += number;
		number = read (f,buf,FILEXFER);
		if (number < 0)
			return (scmerr (errno,
					"Read error on file output message"));
	}

	if (sum != filesize)
		return (scmerr (-1, "File size error on output message"));

	return (x);
}

int
writemnull (int msg)	/* write message with no data */
{
	register int x;
	x = writemsg (msg);
	if (x == SCMOK)  x = writemend ();
	return (x);
}

int
writemint (int msg,int i)		/* write message of one int */
{
	register int x;
	x = writemsg (msg);
	if (x == SCMOK)  x = writeint (i);
	if (x == SCMOK)  x = writemend ();
	return (x);
}

int
writemstr (int msg,char *p)		/* write message of one string */
{
	register int x;
	x = writemsg (msg);
	if (x == SCMOK)  x = writestring (p);
	if (x == SCMOK)  x = writemend ();
	return (x);
}

/*************************************************
 ***    I N P U T   F R O M   N E T W O R K    ***
 *************************************************/

static int
readdata (int count,char * data)	/* read raw data from network */
{
	register char *p;
	register int n,m,x;
	int tries;
	int lookahead;
	fd_set imask;
	struct timeval timout;
	static int unbufcnt = 0;
	static int bufcnt = 0;
	static char *bufptr_l;
	static char unbuffer[sizeof(int)];
	static char buffer[FILEXFER];

	if (count == 0) {
		if (data != NULL)
			return (SCMOK);
		bufcnt = 0;
		unbufcnt = 0;
		return (SCMOK);
	}
	if (data == NULL)
		return (SCMERR);
	if (count < 0) {
		count = -count;
		if (count != sizeof(unbuffer))
			return (SCMERR);
		lookahead = TRUE;
	} else
		lookahead = FALSE;
	if (unbufcnt > 0) {
		if (lookahead || count != unbufcnt)
			return (SCMERR);
		memcpy (data,unbuffer,count);
		unbufcnt = 0;
		return (SCMOK);
	}
	if (count <= bufcnt) {
		if (lookahead) {
			memcpy (unbuffer,bufptr_l,count);
			unbufcnt = count;
		}
		memcpy (data,bufptr_l,count);
		bufptr_l += count;
		bufcnt -= count;
		return (SCMOK);
	}
	if (bufcnt > 0) {
		if (lookahead) {
			memcpy (unbuffer,bufptr_l,bufcnt);
			unbufcnt = bufcnt;
		}
		memcpy (data,bufptr_l,bufcnt);
		data += bufcnt;
		count -= bufcnt;
	}
	bufptr_l = buffer;
	bufcnt = 0;
	timout.tv_usec = 0;
	timout.tv_sec = 2*60*60;
	p = buffer;
	n = FILEXFER;
	m = count;
	while (m > 0) {
		tries = 0;
		for (;;) {
			FD_ZERO (&imask);
			FD_SET (netfile,&imask);
			if (select (netfile+1,(fd_set *)&imask,(fd_set *)0,(fd_set *)0,&timout) < 0)
				FD_SET (netfile,&imask);
			errno = 0;
			if (!FD_ISSET (netfile,&imask))
				return (scmerr (-1,"Timeout on network input"));
			x = read (netfile,p,n);
			if (x > 0)  break;
			if (x == 0)
				return (scmerr (-1,"Premature EOF on network input"));
			if (errno)  break;
			if (++tries > RETRIES)  break;
			if (scmdebug > 0)
				loginfo ("SCM Retrying failed network read");
		}
		if (x < 0) {
			if (errno)
				return (scmerr (errno,"Read error on network"));
			return (scmerr (-1,"Read retries failed"));
		}
		p += x;
		n -= x;
		m -= x;
		bufcnt += x;
	}
	if (lookahead) {
	    memcpy (unbuffer+unbufcnt,bufptr_l,count);
	    unbufcnt += count;
	}
	memcpy (data,bufptr_l,count);
	bufptr_l += count;
	bufcnt -= count;
	return (SCMOK);
}

static
int readcount (int *count)			/* read count of data block */
{
	register int x;
	int y;
	x = readdata (sizeof(int),(char *)&y);
	if (x != SCMOK)  return (x);
	*count = byteswap(y);
	return (SCMOK);
}

int prereadcount (int *count)		/* preread count of data block */
{
	register int x;
	int y;
	x = readdata (-sizeof(int),(char *)&y);
	if (x != SCMOK)  return (x);
	*count = byteswap(y);
	return (SCMOK);
}

int
readflush (void)
{
	return (readdata (0, (char *)NULL));
}

int
readmsg (int msg)	/* read header for expected message */
			/* if message is unexpected, send back SCMHUH */
{
	register int x;
	int m;
	if (scmdebug > 1)
		loginfo ("SCM Reading message %d",msg);
	x = readdata (sizeof(int),(char *)&m);	/* msg type */
	if (x != SCMOK)  return (x);
	m = byteswap(m);
	if (m == msg)  return (x);

	/* check for MSGGOAWAY in case he noticed problems first */
	if (m != MSGGOAWAY)
		return (scmerr (-1,"Received unexpected message %d",m));
	(void) netcrypt ((char *)NULL);
	(void) readstring (&goawayreason);
	(void) readmend ();
	if (goawayreason == NULL)
		return (SCMEOF);
	logerr ("SCM GOAWAY %s",goawayreason);
	return (SCMEOF);
}

int
readmend (void)
{
	register int x;
	int y;
	x = readdata (sizeof(int),(char *)&y);
	y = byteswap(y);
	if (x == SCMOK && y != ENDCOUNT)
		return (scmerr (-1,"Error reading end of message"));
	return (x);
}

int
readskip (void)			/* skip over one input block */
{
	register int x;
	int n;
	char buf[FILEXFER];
	x = readcount (&n);
	if (x != SCMOK)  return (x);
	if (n < 0)
		return (scmerr (-1,"Invalid message count %d",n));
	while (x == SCMOK && n > 0) {
		x = readdata (XFERSIZE(n),buf);
		n -= XFERSIZE(n);
	}
	return (x);
}

int readint (int *buf)		/* read int data block */
{
	register int x;
	int y;
	x = readcount (&y);
	if (x != SCMOK)  return (x);
	if (y < 0)
		return (scmerr (-1,"Invalid message count %d",y));
	if (y != sizeof(int))
		return (scmerr (-1,"Size error for int message is %d",y));
	x = readdata (sizeof(int),(char *)&y);
	(*buf) = byteswap(y);
	if (scmdebug > 2)
		loginfo ("SCM Reading integer %d",*buf);
	return (x);
}

int readstring (char **buf)	/* read string data block */
{
	register int x;
	int count;
	register char *p;

	x = readcount (&count);
	if (x != SCMOK)  return (x);
	if (count == NULLCOUNT) {
		if (scmdebug > 2)
			loginfo ("SCM Reading string NULL");
		*buf = NULL;
		return (SCMOK);
	}
	if (count < 0)
		return (scmerr (-1,"Invalid message count %d",count));
	if ((p = malloc ((unsigned)count+1)) == NULL)
		return (scmerr (-1,"Can't malloc %d bytes for string",count));
	if (cryptflag) {
		x = getcryptbuf (count+1);
		if (x == SCMOK)  x = readdata (count,cryptbuf);
		if (x != SCMOK)  return (x);
		decode (cryptbuf,p,count);
	}
	else {
		x = readdata (count,p);
		if (x != SCMOK)  return (x);
	}
	p[count] = 0;		/* NULL at end of string */
	*buf = p;
	if (scmdebug > 2)
		loginfo ("SCM Reading string %s",*buf);
	return (SCMOK);
}

int
readfile (int f)		/* read data block into open file */
{
	register int x,n,tries;
	int count,wcount,errnum;
	char buf[FILEXFER];
	char *bufp;

	if (cryptflag) {
		x = getcryptbuf (FILEXFER);
		if (x != SCMOK)  return (x);
	}
	x = readcount (&count);
	if (x != SCMOK)  return (x);
	if (protver >= 8 && count == -1) {
		x = readcount (&errnum);
		if (x != SCMOK)  return (x);
		if (errnum == 0)  return (scmerr (-1,"Premature EOF"));
		return (scmerr (errnum,"Error reading file"));
	}
	if (count < 0)  return (scmerr (-1,"Invalid message count %d",count));
	while (count > 0) {
		bufp = cryptflag ? cryptbuf : buf;
		x = readdata (XFERSIZE(count),bufp);
		if (x != SCMOK)  return (x);
		if (cryptflag) {
			decode (cryptbuf,buf,XFERSIZE(count));
			bufp = buf;
		}
		wcount = XFERSIZE(count);
		tries = 0;
		while (wcount > 0) {
			errno = 0;
			n = write (f,bufp,wcount);
			if (n == wcount)  break;
			if (n < 0 && errno != EINTR)
				return (scmerr (errno,"Write error to file"));
			if (n < 0 && ++tries > RETRIES)
				return (scmerr (-1,"Write retries failed"));
			if (n < 0) {
				logerr ("SCM retrying after EINTR...");
				continue;
			}
			if (n == 0 && ++tries > RETRIES)
				return (scmerr (-1,"Write retries failed"));
			if (n == 0) {
				logerr ("SCM retrying after empty write...");
				continue;
			}
			wcount -= n;
			bufp += n;
		}
		count -= XFERSIZE(count);
	}
	return (x);
}

int
readmnull (int msg)		/* read null message */
{
	register int x;
	x = readmsg (msg);
	if (x == SCMOK)  x = readmend ();
	return (x);
}

int
readmint (int msg,int *buf)		/* read int message */
{
	register int x;
	x = readmsg (msg);
	if (x == SCMOK)  x = readint (buf);
	if (x == SCMOK)  x = readmend ();
	return (x);
}

int readmstr (int msg,char **buf)		/* read string message */
{
	register int x;
	x = readmsg (msg);
	if (x == SCMOK)  x = readstring (buf);
	if (x == SCMOK)  x = readmend ();
	return (x);
}

/**********************************
 ***    C R O S S P A T C H     ***
 **********************************/

void
crosspatch (void)
{
	fd_set imask;
	register int c;
	char buf[STRINGLENGTH];

	for (;;) {
		FD_ZERO (&imask);
		FD_SET (0,&imask);
		FD_SET (netfile,&imask);
		if ((c = select (netfile+1,&imask,(fd_set *)0,(fd_set *)0,
				(struct timeval *)NULL)) < 1) {
			if (c == -1) {
				if (errno == EINTR) {
					continue;
				}
			}
			sleep (5);
			continue;
		}
		if (FD_ISSET (netfile,&imask)) {
			c = read (netfile,buf,sizeof (buf));
			if (c < 0 && errno == EWOULDBLOCK)
				c = 0;
			else {
				if (c <= 0) {
					break;
				}
				write (1,buf,c);
			}
		}
		if (FD_ISSET(0, &imask)) {
			c = read (0,buf,sizeof (buf));
			if (c < 0 && errno == EWOULDBLOCK)
				c = 0;
			else {
				if (c <= 0)
					break;
				(void) write (netfile,buf,c);
			}
		}
	}
}

/*******************************************
 ***    D A T A   E N C R Y P T I O N    ***
 *******************************************/

/* Data encryption  routines have beem moved to crypt.c and no_crypt.c. */
