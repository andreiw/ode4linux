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
 * $Log: mmindex.c,v $
 * Revision 1.2.2.2  1992/12/03  19:10:04  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:41:14  damon]
 *
 * Revision 1.2  1991/12/05  21:03:35  devrcs
 * 	Added to ODE to build dug indexes.
 * 	[91/07/23  10:15:01  mckeen]
 * 
 * $EndLog$
 */
/*	indexer
 *
 *	SYNOPSIS: indexer
 *
 *		always reads from standard input and writes to standard output
 *
 *	revision history:
 *
 *		6/12/89	written for OSF by David Eaglesfield
 *		6/13/89 enhanced (de)
 *		6/23/89	fix: dumps core if user omits quoted arg on tm line (de)
 *		6/29/89 simplified operation - output the input intersperced
 *				with .Iy macros when the primary letter changes (fld)
 *		9/29/89	add "new-letter" as arg to .Iy (fld)
 *
 *	Expected form of input is lines that look like:
 *
 *		"primary-part" "secondary part" "pagenum"
 *
 *	where the quotes are always there, and some text is required for
 *	primary-part and pagenum.  Secondary part may have no text (but
 *	always has the quotes).
 */


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "ctype.h"


#define BUFSIZE 1000
#define MAXLINE (BUFSIZE - 1)

#define FALSE 0
#define TRUE 1

main(argc,argv)
int argc;
char **argv;
{
	register char lastChar, nextChar, *cP, ch;
	register short firstOne;
	char buf[BUFSIZE];

#define NORMALIZEDCHAR(letter) (isupper(letter) ? tolower(letter) : letter)

	lastChar = '\0';			/* first letter in last record */
	firstOne = TRUE;			/* first record */

	while(fgets(buf,MAXLINE,stdin) != NULL)
	{

		for (cP=buf;  *cP && (*cP != '"');  cP++)
			;						/* find first quote */

		nextChar = * ++cP;			/* point at first char of word */

		ch = isupper(nextChar) ? tolower(nextChar) : nextChar;

		if ( lastChar != ch )	{

			if ( (ch >= 'a' && ch <= 'z') ||
				 (ch >= '0' && ch <= '9'))	{
											/* separate diff letters */
				printf(".Iy \"%c\"\n", toupper(ch));

			} else {
				if ( ! firstOne )	{
					printf(".Iy\n");		/* separate diff letters */
				}
			}
		}

		printf(".Ix %s", buf);	/* output line */

		lastChar = ch;
		firstOne = FALSE;
	}
} /* end of process() */
