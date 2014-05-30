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
 * $Log: supcname.c,v $
 * Revision 1.3.6.1  1994/02/18  21:52:10  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:34  damon]
 *
 * Revision 1.3.4.2  1993/05/28  17:38:24  marty
 * 	CR # 558 - Get it to build on rios_aix
 * 	[1993/05/28  17:38:07  marty]
 * 
 * Revision 1.3.2.3  1992/12/02  19:53:06  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:19  damon]
 * 
 * Revision 1.3.2.2  1992/09/24  19:00:31  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:19:28  gm]
 * 
 * Revision 1.3  1991/12/05  20:54:26  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:09  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:33  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:17:38  zeliff]
 * 
 * Revision 1.2  90/10/07  21:37:01  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:13  gm]
 * 
 * Revision 1.2  90/01/02  19:56:22  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:24  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Changed to no longer use a name server.
 * 	[87/12/21            gm0w]
 * 
 * 	Changed getnams and added several new routines to change the
 * 	way that sup finds nameservers.  It now builds a tree of
 * 	servers to check.  It walks over the tree.  At each node, it
 * 	tries to contact the name server and get as many names
 * 	resolved as it can.  It stops after either all collections
 * 	have host names, or if some collections don't have host names
 * 	but either everyone doesn't know what they are, or after too
 * 	many tries, none could be reached.
 * 	[87/05/26            dwp]
 * 
 * 	Split off from sup.c
 * 	[87/05/25            dwp]
 * 
 * $EndLog$
 */
/*
 * sup client name server interface
 */

#include <ode/supcdefs.h>
#include <ode/util.h>

extern COLLECTION *firstC;		/* collection list pointer */

/*****************************************
 ***    G E T   H O S T   N A M E S    ***
 *****************************************/

/*
 * For each collection that doesn't have a host name specified, read
 * the file server list for the name of the host for that collection.
 * It's a fatal error if a collection has no file server.
 */

void
getnams (void)
{
	register COLLECTION *c;
	char buf[STRINGLENGTH];
	register FILE *f;
	char *p,*q;

	for (c = firstC; c && c->Chtree != NULL; c = c->Cnext);
	if (c == NULL) return;
	(void) sprintf (buf,FILEHOSTS,DEFDIR);
	f = fopen (buf,"r");
	if (f == NULL)  logquit (1,"Can't open %s",buf);
	while ((p = fgets (buf,STRINGLENGTH,f)) != NULL) {
		if ((q = strchr (p,'\n')))  *q = '\0';
		if (strchr ("#;:",*p))  continue;
		q = (char *)nxtarg (&p,"= \t");
		p = (char *)skipover (p," \t");
		if (*p == '=')  p++;
		p = (char *)skipover (p," \t");
		if (*p == '\0')  goaway ("error in collection/host file");
		do {
			if (strcmp (c->Cname, q) == 0) {
				do {
					q = (char *)nxtarg (&p,", \t");
					p = (char *)skipover (p," \t");
					if (*p == ',')  p++;
					p = (char *)skipover (p," \t");
					(void) Tinsert (&c->Chtree,q,FALSE);
				} while (*p != '\0');
			}
			while ((c = c->Cnext) != NULL && c->Chtree != NULL);
		} while (c != NULL);
		for (c = firstC; c && c->Chtree != NULL; c = c->Cnext);
		if (c == NULL) break;
	}
	(void) fclose (f);
	if (c == NULL)  return;
	do {
		logerr ("Host for collection %s not found",c->Cname);
		while ((c = c->Cnext) != NULL && c->Chtree != NULL);
	} while (c);
	logquit (1,"Hosts not found for all collections");
}
