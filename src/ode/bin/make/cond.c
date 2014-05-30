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
 * $Log: cond.c,v $
 * Revision 1.2.5.1  1995/04/27  17:25:35  robert
 * 	Add debug function CondDoMake to show results of evaluating
 * 	.if make() conditionals. With the below fix, make conditionals are
 * 	now evaluated properly (per randys).
 *
 * 	Change prototypes from char * to string_t to match structure so that:
 * 	return(!Str_Match((char *)string,(char *)pattern))
 * 	is now:
 * 	return(!Str_Match(((string_t)string)->data,((string_t)pattern)->data))
 * 	and:
 * 	if (Lst_Find (create, (ClientData)arg, CondStrMatch) == NILLNODE)
 * 	is now:
 * 	if (Lst_Find (create, (ClientData)arg_string, CondStrMatch) == NILLNODE)
 * 	[1995/04/27  17:13:47  robert]
 *
 * Revision 1.2.2.3  1992/12/03  19:05:02  damon
 * 	ODE 2.2 CR 346. Expanded copyright
 * 	[1992/12/03  18:35:01  damon]
 * 
 * Revision 1.2.2.2  1992/09/24  19:23:42  gm
 * 	CR286: Major improvements to make internals.
 * 	[1992/09/24  17:53:49  gm]
 * 
 * Revision 1.2  1991/12/05  20:42:14  devrcs
 * 	Changes for parallel make.
 * 	[91/04/21  16:36:48  gm]
 * 
 * 	Changes for Reno make
 * 	[91/03/22  15:42:33  mckeen]
 * 
 * $EndLog$
 */
/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the University of California, Berkeley and its contributors''
 * in the documentation or other materials provided with the distribution
 * and in all advertising materials mentioning features or use of this
 * software. Neither the name of the University nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef lint
static char sccsid[] = "@(#)cond.c	5.6 (Berkeley) 6/1/90";
#endif /* not lint */

/*-
 * cond.c --
 *	Functions to handle conditionals in a makefile.
 *
 */

#include    "make.h"

/*-
 *-----------------------------------------------------------------------
 * CondStrMatch --
 *	Front-end for Str_Match so it returns 0 on match and non-zero
 *	on mismatch. Callback function for CondDoMake via Lst_Find
 *
 * Results:
 *	0 if string matches pattern
 *
 * Side Effects:
 *	None
 *
 *-----------------------------------------------------------------------
 */
static int
CondStrMatch(ClientData string, ClientData pattern)
{
    return(!Str_Match(((string_t)string)->data,((string_t)pattern)->data));
}

/*-
 *-----------------------------------------------------------------------
 * CondDoMake --
 *	Handle the 'make' function for conditionals.
 *
 * Results:
 *	TRUE if the given target is being made.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoMake (int argLen, char *arg)
{
    char    savec = arg[argLen];
    Boolean result;
    string_t arg_string = string_create(arg);

    arg[argLen] = '\0';
    if (Lst_Find (create, (ClientData)arg_string, CondStrMatch) == NILLNODE) {
	result = FALSE;
    } else {
	result = TRUE;
    }
    arg[argLen] = savec;
    if (DEBUG(COND)) {
	ListNode le;
	printf("CondDoMake: %s in \"", arg);
	for(le = Lst_First(create); le != NILLNODE; le = Lst_Succ(le)) {
	    printf(" %s", ((string_t) Lst_Datum(le))->data);
	}
        printf("\" %s\n", result ? "TRUE" : "FALSE");
    }
    return (result);
}

/*-
 *-----------------------------------------------------------------------
 * CondDoExists --
 *	See if the given file exists.
 *
 * Results:
 *	TRUE if the file exists and FALSE if it does not.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoExists (int argLen, char *arg)
{
    char    savec = arg[argLen];
    Boolean result;
    string_t path;

    arg[argLen] = '\0';
    path = Dir_FindFile(string_create(arg), dirSearchPath);
    if (path != (string_t)NULL) {
	result = TRUE;
	string_deref(path);
    } else {
	result = FALSE;
    }
    arg[argLen] = savec;
    return (result);
}

/*-
 *-----------------------------------------------------------------------
 * CondDoTarget --
 *	See if the given node exists and is an actual target.
 *
 * Results:
 *	TRUE if the node exists as a target and FALSE if it does not.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoTarget (int argLen, char *arg)
{
    char    savec = arg[argLen];
    Boolean result;
    GNode   *gn;

    arg[argLen] = '\0';
    gn = Targ_FindNode(string_create(arg), TARG_NOCREATE);
    if ((gn != NILGNODE) && !OP_NOP(gn->type)) {
	result = TRUE;
    } else {
	result = FALSE;
    }
    arg[argLen] = savec;
    return (result);
}

Boolean
CondKWMake(char **condExprPtr, int *arglenPtr, char **argPtr,
	   Boolean doEval)
{
    /*
     * Use CondDoMake to evaluate the argument and
     * Cond_GetArg to extract the argument from the 'function
     * call'.
     */
    *condExprPtr += 4;
    *arglenPtr = Cond_GetArg(condExprPtr, argPtr, "make", TRUE);
    if (*arglenPtr == 0) {
	*condExprPtr -= 4;
	return(TRUE);
    }
    return(FALSE);
}

Boolean
CondKWExists(char **condExprPtr, int *arglenPtr, char **argPtr,
	     Boolean doEval)
{
    /*
     * Use CondDoExists to evaluate the argument and
     * Cond_GetArg to extract the argument from the
     * 'function call'.
     */
    *condExprPtr += 6;
    *arglenPtr = Cond_GetArg(condExprPtr, argPtr, "exists", TRUE);
    if (*arglenPtr == 0) {
	*condExprPtr -= 6;
	return(TRUE);
    }
    return(FALSE);
}

Boolean
CondKWTarget(char **condExprPtr, int *arglenPtr, char **argPtr,
	     Boolean doEval)
{
    /*
     * Use CondDoTarget to evaluate the argument and
     * Cond_GetArg to extract the argument from the
     * 'function call'.
     */
    *condExprPtr += 6;
    *arglenPtr = Cond_GetArg(condExprPtr, argPtr, "target", TRUE);
    if (*arglenPtr == 0) {
	*condExprPtr -= 6;
	return(TRUE);
    }
    return(FALSE);
}

void
Cond_Setup(void)
{
    Cond_Init(VarParseCond, VarValueCond, ParseErrorCond, DEBUG(COND));
    Cond_AddKeyword("make", CondKWMake, CondDoMake);
    Cond_AddKeyword("exists", CondKWExists, CondDoExists);
    Cond_AddKeyword("target", CondKWTarget, CondDoTarget);
}
