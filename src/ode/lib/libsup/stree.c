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
 * $Log: stree.c,v $
 * Revision 1.3.5.5  1994/02/17  16:24:18  damon
 * 	CR 1056. Moved from bin/sup
 * 	[1994/02/17  16:22:34  damon]
 *
 * Revision 1.3.5.4  1994/02/15  20:37:40  damon
 * 	CR 1051. More pedantic
 * 	[1994/02/15  20:37:18  damon]
 * 
 * Revision 1.3.5.3  1994/02/15  17:36:12  damon
 * 	CR 1051. Made pedantic changes
 * 	[1994/02/15  17:35:46  damon]
 * 
 * Revision 1.3.5.2  1994/02/14  23:49:25  damon
 * 	CR 1051. Fixed type casting
 * 	[1994/02/14  23:49:08  damon]
 * 
 * Revision 1.3.5.1  1994/02/08  22:27:34  damon
 * 	CR 1049. Added include of portable.h
 * 	[1994/02/08  22:27:18  damon]
 * 
 * Revision 1.3.2.3  1992/12/02  19:52:54  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:08  damon]
 * 
 * Revision 1.3.2.2  1992/09/24  19:00:05  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:18:43  gm]
 * 
 * Revision 1.3  1991/12/05  20:54:06  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:07:33  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:03  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:17:04  zeliff]
 * 
 * Revision 1.2  90/10/07  21:36:33  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:46:39  gm]
 * 
 * Revision 1.3  90/07/17  12:26:43  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  17:04:51  gm]
 * 
 * Revision 1.2  90/01/02  19:56:16  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:02  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * Revision 1.3  89/06/24  21:18:14  gm0w
 * 	Changed code in Tlookup to Tsearch for each subpart of path.
 * 	Added indent formatting code to Tprint.
 * 	[89/06/24            gm0w]
 * 
 * Revision 0.0  87/05/20            gm0w
 * 	Added code to please lint.
 * 	[87/05/20            gm0w]
 * 
 * Revision 0.0  85/12/29            gm0w
 * 	Added code to initialize new fields.  Added Tfree routine.
 * 	[85/12/29            gm0w]
 * 
 * Revision 0.0  85/09/27            gm0w
 * 	Created.
 * 	[85/09/27            gm0w]
 * 
 * $EndLog$
 */
/*
 * stree.c -- SUP Tree Routines
 */

#include <ode/portable.h>
#include <ode/sup.h>
#include <sys/param.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Static	/* static comment for debugging */

/*************************************************************
 ***    T R E E   P R O C E S S I N G   R O U T I N E S    ***
 *************************************************************/

void
Tfree ( TREE **t )
{
	if (*t == NULL)  return;
	Tfree (&((*t)->Tlink));
	Tfree (&((*t)->Texec));
	Tfree (&((*t)->Tlo));
	Tfree (&((*t)->Thi));
	if ((*t)->Tname)  free ((*t)->Tname);
	if ((*t)->Tuser)  free ((*t)->Tuser);
	if ((*t)->Tgroup)  free ((*t)->Tgroup);
	free (*(char **)t);
	*t = NULL;
}

Static
TREE *Tmake ( const char *p )
{
	register TREE *t;
	t = (TREE *) malloc (sizeof (TREE));
	t->Tname = (p == NULL) ? NULL : strdup (p);
	t->Tflags = 0;
	t->Tuid = 0;
	t->Tgid = 0;
	t->Tuser = NULL;
	t->Tgroup = NULL;
	t->Tmode = 0;
	t->Tctime = 0;
	t->Tmtime = 0;
	t->Tlink = NULL;
	t->Texec = NULL;
	t->Tbf = 0;
	t->Tlo = NULL;
	t->Thi = NULL;
	return (t);
}

Static
TREE *Trotll ( TREE *tp, TREE *tl )
{
    tp->Tlo = tl->Thi;
    tl->Thi = tp;
    tp->Tbf = tl->Tbf = 0;
    return(tl);
}

Static
TREE *Trotlh ( TREE *tp, TREE *tl )
{
    register TREE *th;

    th = tl->Thi;
    tp->Tlo = th->Thi;
    tl->Thi = th->Tlo;
    th->Thi = tp;
    th->Tlo = tl;
    tp->Tbf = tl->Tbf = 0;
    if (th->Tbf == 1)
	tp->Tbf = -1;
    else if (th->Tbf == -1)
	tl->Tbf = 1;
    th->Tbf = 0;
    return(th);
}

Static
TREE *Trothl ( TREE *tp, TREE *th )
{
    register TREE *tl;

    tl = th->Tlo;
    tp->Thi = tl->Tlo;
    th->Tlo = tl->Thi;
    tl->Tlo = tp;
    tl->Thi = th;
    tp->Tbf = th->Tbf = 0;
    if (tl->Tbf == -1)
	tp->Tbf = 1;
    else if (tl->Tbf == 1)
	th->Tbf = -1;
    tl->Tbf = 0;
    return(tl);
}

Static
TREE *Trothh ( TREE *tp, TREE *th )
{
    tp->Thi = th->Tlo;
    th->Tlo = tp;
    tp->Tbf = th->Tbf = 0;
    return(th);
}

Static void
Tbalance ( TREE **t )
{
    if ((*t)->Tbf < 2 && (*t)->Tbf > -2)
	return;
    if ((*t)->Tbf > 0) {
	if ((*t)->Tlo->Tbf > 0)
	    *t = Trotll(*t, (*t)->Tlo);
	else
	    *t = Trotlh(*t, (*t)->Tlo);
    } else {
	if ((*t)->Thi->Tbf > 0)
	    *t = Trothl(*t, (*t)->Thi);
	else
	    *t = Trothh(*t, (*t)->Thi);
    }
}

Static
TREE *Tinsertavl ( TREE **t, const char *p, int find, int *dh )
{
	register TREE *newt;
	register int cmp;
	int deltah;

	if (*t == NULL) {
	    *t = Tmake (p);
	    *dh = 1;
	    return (*t);
	}
	if ((cmp = strcmp(p, (*t)->Tname)) == 0) {
	    if (!find)  return (NULL);	/* node already exists */
	    *dh = 0;
	    return (*t);
	} else if (cmp < 0) {
	    if ((newt = Tinsertavl (&((*t)->Tlo),p,find,&deltah)) == NULL)
		return (NULL);
	    (*t)->Tbf += deltah;
	} else {
	    if ((newt = Tinsertavl (&((*t)->Thi),p,find,&deltah)) == NULL)
		return (NULL);
	    (*t)->Tbf -= deltah;
	}
	Tbalance(t);
	if ((*t)->Tbf == 0) deltah = 0;
	*dh = deltah;
	return (newt);
}

TREE *Tinsert ( TREE **t, const char *p, int find )
{
	int deltah;

	if (p != NULL && p[0] == '.' && p[1] == '/') {
		p += 2;
		while (*p == '/') p++;
		if (*p == 0) p = ".";
	}
	return (Tinsertavl (t,p,find,&deltah));
}

TREE *Tsearch ( TREE *t, const char *p )
{
	register TREE *x;
	register int cmp;

	x = t;
	while (x) {
		cmp = strcmp (p,x->Tname);
		if (cmp == 0)  return (x);
		if (cmp < 0)	x = x->Tlo;
		else		x = x->Thi;
	}
	return (NULL);
}

TREE *Tlookup ( TREE *t, char *p )
{
	register TREE *x;
	char buf[MAXPATHLEN+1];

	if (p == NULL)
		return (NULL);
	if (p[0] == '.' && p[1] == '/') {
		p += 2;
		while (*p == '/') p++;
		if (*p == 0) strcpy (p, ".");
	}
	if ((x = Tsearch (t,p)) != NULL)
		return (x);
	if (*p != '/' && (x = Tsearch (t,".")) != NULL)
		return (x);
	(void) strncpy(buf, p, sizeof(buf)-1);
	buf[MAXPATHLEN] = '\0';
	while ((p = strrchr(buf, '/')) != NULL) {
		while (p >= buf && *(p-1) == '/')
			p--;
		if (p == buf)
			*(p+1) = '\0';
		else
			*p = '\0';
		if ((x = Tsearch (t,buf)) != NULL)
			return (x);
		if (p == buf)
			break;
	}
	return (NULL);
}

Static int process_level;

Static
int Tsubprocess ( TREE *t, int reverse, int (*f)( TREE *, va_list ),
                  va_list ap )
{
	register int x = SCMOK;

	process_level++;
	if (reverse?t->Thi:t->Tlo)
		x = Tsubprocess (reverse?t->Thi:t->Tlo,
				 reverse,f,ap);
	if (x == SCMOK) {
		x = (*f) (t,ap);
		if (x == SCMOK) {
			if (reverse?t->Tlo:t->Thi)
				x = Tsubprocess (reverse?t->Tlo:t->Thi,
						 reverse,f, ap);
		}
	}
	process_level--;
	return (x);
}

/* VARARGS2 */
int Trprocess ( TREE *t, int (*f)( TREE *, va_list ), ... )
{
        int status;
	va_list ap;

        va_start ( ap, f );
	if (t == NULL)  return (SCMOK);
	process_level = 0;
	status = Tsubprocess (t,TRUE,f,ap);
        va_end (ap);
        return (status);
}

/* VARARGS2 */
int Tprocess ( TREE *t, int (*f)( TREE *, va_list ), ... )
{
	int status;
	va_list ap;

	if (t == NULL)  return (SCMOK);
	process_level = 0;
	va_start ( ap, f );
	status = Tsubprocess (t,FALSE,f,ap);
	va_end (ap);
	return ( status );
}

Static
int Tprintone ( TREE *t, va_list ap )
{
	int i;

	for (i = 0; i < (process_level*2); i++)
		(void) putchar(' ');
	printf ("Node at %p name '%s' flags %o hi %p lo %p\n",t,t->Tname,t->Tflags,t->Thi,t->Tlo);
	return (SCMOK);
}

void
Tprint ( TREE *t, char *p )		/* print tree -- for debugging */
{
	printf ("%s\n",p);
	(void) Tprocess (t,Tprintone);
	printf ("End of tree\n");
	(void) fflush (stdout);
}
