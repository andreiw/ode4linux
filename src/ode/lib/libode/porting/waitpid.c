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
 * $Log: waitpid.c,v $
 * Revision 1.2.2.3  1992/12/03  17:22:07  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:08:52  damon]
 *
 * Revision 1.2.2.2  1992/09/24  19:02:25  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:23:10  gm]
 * 
 * Revision 1.2  1991/12/05  20:45:10  devrcs
 * 	Changes for parallel make.
 * 	[91/04/21  17:19:29  gm]
 * 
 * $EndLog$
 */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

typedef int pid_t;

struct plist {
	struct plist *next;
	pid_t pid;
	int status;
} *plist, *plist_end;

pid_t
waitpid(pid, status, options)
	pid_t pid;
	int *status;
	int options;
{
	pid_t wpid;
	struct plist *temp, *temp2;

	if (plist) {
		if (pid == -1) {
			pid = plist->pid;
			*status = plist->status;
			temp = plist;
			plist = temp->next;
			free(temp);
			return(pid);
		}
		for (temp = plist; temp; temp2 = temp, temp = temp->next) {
			if (temp->pid != pid)
				continue;
			*status = temp->status;
			if (temp == plist)
				plist = temp->next;
			else
				temp2->next = temp->next;
			if (plist_end == temp)
				plist_end = temp2;
			free(temp);
			return(pid);
		}
	}
	for (;;) {
		wpid = wait3(status, options, 0);
		if (wpid < 0 || pid == -1 || wpid == pid)
			break;
		temp = (struct plist *) malloc(sizeof(struct plist));
		temp->pid = wpid;
		temp->status = *status;
		temp->next = 0;
		if (plist)
			plist_end->next = temp;
		else
			plist = temp;
		plist_end = temp;
	}
	return(wpid);
}
