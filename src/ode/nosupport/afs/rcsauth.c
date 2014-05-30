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
 * $Log: rcsauth.c,v $
 * Revision 1.1.4.3  1992/12/03  17:27:11  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/03  17:11:35  damon]
 *
 * Revision 1.1.4.2  1992/06/16  13:41:31  damon
 * 	Synched with 2.1.1
 * 	[1992/06/16  13:36:36  damon]
 * 
 * Revision 1.1.2.2  1992/03/25  22:48:23  damon
 * 	Modified rcsauth 1.7.2.3 for afs
 * 	[1992/03/25  19:34:07  damon]
 * 
 * $EndLog$
 */
#if !defined(lint) && !defined(_NOIDENT)
static char rcsid[] = "@(#)$RCSfile: rcsauth.c,v $ $Revision: 1.1.4.3 $ (OSF) $Date: 1992/12/03 17:27:11 $";
#endif
/*
 * rcsauth - authentication cover for rcs commands
 */
#include <sys/param.h>
#include <sys/errno.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

#define SEND_OVER	1
#define WANT_BACK	2

char *progname="rcsauth";

main(argc, argv)
int argc;
char **argv;
{
  int i;
    char *authcover_testdir;
    char *authcover_host;
    char *authcover_user;
    char *prog;
    int tempmode = 0;
    int tempslot = 0;
    int debug;
    char buf[MAXPATHLEN];
    char *u;
    char *rindex(), *getenv();

    if (argc < 1)
	prog = "rcsauth";
    else if ((prog = rindex(argv[0], '/')) == NULL)
	prog = argv[0];
    else
	prog++;
    argc--;
    argv++;
    debug = (getenv("AUTHCOVER_DEBUG") != NULL);
    if (argc >= 2 && argv[0][0] == '-' && argv[0][1] == 't') {
	if (argv[0][2] == '0')
	    tempmode = WANT_BACK;
	else if (argv[0][2] == '1')
 	    tempmode = SEND_OVER;
	else if (argv[0][2] == '2')
	    tempmode = SEND_OVER|WANT_BACK;
	else
	    quit(1, "%s: invalid temp mode\n", prog);
	tempslot = atoi(argv[1]);
	if (tempslot < 0)
	    quit(1, "%s: bad tempslot\n", prog);
	argc -= 2;
	argv += 2;
    }
    if (argc < 1)
	quit(1, "usage: %s <cmd> <args>\n", prog);
    if ((authcover_host = getenv("AUTHCOVER_HOST")) == NULL)
	quit(1, "%s: no AUTHCOVER_HOST in environment\n", prog);
    if ((authcover_testdir = getenv("AUTHCOVER_TESTDIR")) == NULL)
	quit(1, "%s: no AUTHCOVER_TESTDIR in environment\n", prog);
    if ((authcover_user = getenv("AUTHCOVER_USER")) == NULL)
	quit(1, "%s: no AUTHCOVER_USER in environment\n", prog);

#define OSFRI
#ifdef OSFRI

    if ((strcmp (authcover_host, "AFS")) == 0)

      {
	if (debug)
	  diag ("rcsauth: AFS");
	exit (afscode (authcover_testdir, authcover_user,
		       tempmode, tempslot, debug, argc, argv));
      }
#endif
  if (debug)
    diag ("entering kxct");

  exit(kxct(authcover_host, authcover_testdir, authcover_user,
	    tempmode, tempslot, debug, argc, argv));
  if (debug)
    diag ("exiting kxct");
}
