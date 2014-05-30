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
 * $Log: no_crypt.c,v $
 * Revision 1.1.4.1  1995/04/18  17:52:54  robert
 * 	Add changes from Mary Thompson (1/31/95)
 * 	Moved decode before encode so that decode would
 * 	be defined before it is used.
 * 	[1995/04/05  21:38:49  robert]
 *
 * 	initial check in
 * 	[1995/04/05  17:24:31  robert]
 *
 * Revision 1.1.2.1  1994/06/22  18:51:43  marty
 * 	Reorg for encryption
 * 	[1994/06/22  18:50:31  marty]
 * 
 * 	Reorg for encryption problem.
 * 	[1994/06/22  18:37:43  marty]
 * 
 * $EndLog$
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
extern int cryptflag;
extern char *cryptbuf;       

/*******************************************
 ***    D A T A   E N C R Y P T I O N    ***
 *******************************************/

/*
 * Subroutine version of "crypt" program
 */

#define ROTORSZ 256
#define MASK 0377
static char	t1[ROTORSZ];
static char	t2[ROTORSZ];
static char	t3[ROTORSZ];

int
netcrypt (const char *pword)
{
	int ic, i, k, temp;
	unsigned random_l;
	char buf[13];
	int seed;

	if (pword == NULL) {
		cryptflag = 0;
		(void) getcryptbuf (0);
		return (SCMOK);
	}
	cryptflag = 1;
/*
	Encryption code has been removed.
*/
	return (SCMOK);
}

int
getcryptbuf (int x)
{
	static int cryptsize = 0;	/* size of current cryptbuf */

	if (cryptflag == 0) {
		if (cryptsize > 0)  free (cryptbuf);
		cryptsize = 0;
	} else if (x > cryptsize) {
		if (cryptsize > 0)  free (cryptbuf);
		cryptbuf = malloc ((unsigned)x+1);
		if (cryptbuf == NULL)
			return (scmerr (-1,"Can't allocate encryption buffer"));
		cryptsize = x;
	}
	return (SCMOK);
}

void
decode ( const char *in, char *out, int count )
{
	register char *t1p,*t2p,*t3p;
	register int n1,n2;

	strncpy ( out, in, count);
/*
	Encryption code has been removed.
*/
}
void
encode ( const char *in,char *out, int count )
{
	decode (in,out,count);
}
