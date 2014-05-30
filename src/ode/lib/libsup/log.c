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
 * $Log: log.c,v $
 * Revision 1.3.8.3  1994/02/18  18:23:31  damon
 * 	CR 1056. Added const to char *'s
 * 	[1994/02/18  18:22:58  damon]
 *
 * Revision 1.3.8.2  1994/02/18  15:54:17  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  15:54:05  damon]
 * 
 * Revision 1.3.8.1  1994/02/17  18:47:53  damon
 * 	CR 1056. Moved from ./bin/sup/
 * 	[1994/02/17  18:47:38  damon]
 * 
 * Revision 1.3.6.1  1993/07/07  19:32:31  damon
 * 	CR 602. Add NO_SUP_LOCKS and NEED_LOCK_DEFS
 * 	[1993/07/07  19:32:03  damon]
 * 
 * Revision 1.3.4.4  1992/12/02  19:52:44  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:00  damon]
 * 
 * Revision 1.3.4.3  1992/06/16  23:08:58  damon
 * 	2.1.1 touch-up
 * 	[1992/06/16  22:57:51  damon]
 * 
 * Revision 1.3.2.2  1992/04/02  21:00:46  damon
 * 	Disable syslogging if NO_SYSLOG set
 * 	[1992/04/02  20:56:05  damon]
 * 
 * Revision 1.3  1991/12/05  20:53:53  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:09  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:46:39  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:16:41  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:12  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:17  gm]
 * 
 * Revision 1.3  90/07/17  12:26:28  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:03:55  gm]
 * 
 * Revision 1.2  90/01/02  19:56:11  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:32:49  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.4  89/11/29  17:40:24  bww
 * 	Updated variable argument list usage.
 * 	[89/11/29  17:27:28  bww]
 * 
 * Revision 1.4  89/08/03  19:48:59  mja
 * 	Updated to use v*printf() in place of _doprnt().
 * 	[89/04/19            mja]
 * 
 * Revision 0.0  87/12/27            gm0w
 * 	Added check to allow logopen() to be called multiple times.
 * 	[87/12/27            gm0w]
 * 
 * Revision 0.0  87/05/20            gm0w
 * 	Created.
 * 	[87/05/20            gm0w]
 * 
 * $EndLog$
 */
/*
 * Logging support for SUP
 */

#include <stdio.h>
#ifndef NO_SYSLOG
#include <sys/syslog.h>
#endif
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <ode/sup.h>
#include <ode/util.h>

static int opened = 0;

void
logopen( const char *program )
{
	if (opened)  return;
#ifndef NO_SYSLOG
	openlog(program,LOG_PID,LOG_DAEMON);
#endif
	opened++;
}

#if __STDC__
void
logquit(int retval,const char *fmt,...)
#else
/*VARARGS*/
void
logquit(va_alist)
va_dcl
#endif
{
#if !__STDC__
	int retval;
	const char *fmt;
#endif
	char buf[STRINGLENGTH];
	va_list ap;

#if __STDC__
	va_start(ap,fmt);
#else
	va_start(ap);
	retval = va_arg(ap,int);
	fmt = va_arg(ap,char *);
#endif
	vsprintf(buf, fmt, ap);
	va_end(ap);
	if (opened) {
#ifndef NO_SYSLOG
		syslog (LOG_ERR,buf);
#endif
		closelog ();
		exit (retval);
	}
	quit (retval,"SUP: %s\n",buf);
}

#if __STDC__
void
logerr(const char *fmt,...)
#else
/*VARARGS*/
void
logerr(va_alist)
va_dcl
#endif
{
#if !__STDC__
	const char *fmt;
#endif
	char buf[STRINGLENGTH];
	va_list ap;

#if __STDC__
	va_start(ap,fmt);
#else
	va_start(ap);
	fmt = va_arg(ap,char *);
#endif
	vsprintf(buf, fmt, ap);
	va_end(ap);
	if (opened) {
#ifndef NO_SYSLOG
		syslog (LOG_ERR,buf);
#endif
		return;
	}
	fprintf (stderr,"SUP: %s\n",buf);
	(void) fflush (stderr);
}

#if __STDC__
void
loginfo(const char *fmt,...)
#else
/*VARARGS*/
void
loginfo(va_alist)
va_dcl
#endif
{
#if !__STDC__
	const char *fmt;
#endif
	char buf[STRINGLENGTH];
	va_list ap;

#if __STDC__
	va_start(ap,fmt);
#else
	va_start(ap);
	fmt = va_arg(ap,char *);
#endif
	vsprintf(buf, fmt, ap);
	va_end(ap);
	if (opened) {
#ifndef NO_SYSLOG
		syslog (LOG_INFO,buf);
#endif
		return;
	}
	printf ("%s\n",buf);
	(void) fflush (stdout);
}
