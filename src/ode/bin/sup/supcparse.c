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
 * $Log: supcparse.c,v $
 * Revision 1.3.8.2  1994/02/18  21:52:13  damon
 * 	CR 1056. Pedantic changes
 * 	[1994/02/18  21:51:36  damon]
 *
 * Revision 1.3.8.1  1994/02/17  15:44:30  damon
 * 	CR 1051. More pedantic
 * 	[1994/02/17  15:42:42  damon]
 * 
 * Revision 1.3.5.2  1993/05/28  17:35:45  marty
 * 	CR # 558 - Get it to build on rios_aix.
 * 	[1993/05/28  17:35:30  marty]
 * 
 * Revision 1.3.2.4  1992/12/02  19:53:08  damon
 * 	ODE 2.2 CR 183. Added CMU notice
 * 	[1992/12/02  19:51:21  damon]
 * 
 * Revision 1.3.2.3  1992/09/24  19:00:33  gm
 * 	CR282: Made more portable to non-BSD systems.
 * 	[1992/09/23  18:19:36  gm]
 * 
 * Revision 1.3.2.2  1992/02/13  15:09:28  gm
 * 	Add support for "nomtime" sup collection option.
 * 	[1992/02/09  02:17:13  gm]
 * 
 * Revision 1.3  1991/12/05  20:54:29  devrcs
 * 	Added _FREE_ to copyright marker
 * 	[91/08/01  08:08:14  mckeen]
 * 
 * 	"Adding sup to ODE"
 * 	[91/04/30  14:47:38  zeliff]
 * 
 * 	Integrating SUP into ODE RCS tree
 * 	[91/04/30  12:17:48  zeliff]
 * 
 * Revision 1.2  90/10/07  21:37:05  devrcs
 * 	Restored as unsupported.
 * 	[90/09/17  17:47:17  gm]
 * 
 * Revision 1.3  90/07/17  12:27:00  devrcs
 * 	More changes for gcc.
 * 	[90/07/09  18:42:41  gm]
 * 
 * Revision 1.2  90/01/02  19:56:23  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/12/26  10:33:27  gm
 * 	Current version from CMU.
 * 	[89/12/23            gm]
 * 
 * 	Added timeout to backoff.
 * 	[88/02/10            gm0w]
 * 
 * 	Added code for "release" support.  Removed obsolete options.
 * 	[87/06/28            gm0w]
 * 
 * 	Split off from sup.c
 * 	[87/05/25            dwp]
 * 
 * $EndLog$
 */
/*
 * sup collection parsing routines
 */

#include <ode/supcdefs.h>
#include <ode/util.h>
#include <stdlib.h>

typedef enum {				/* supfile options */
	OHOST, OBASE, OHOSTBASE, OPREFIX, ORELEASE,
	ONOTIFY, OLOGIN, OPASSWORD, OCRYPT,
	OBACKUP, ODELETE, OEXECUTE, OOLD, OTIMEOUT, ONOMTIME
} OPTION;

struct option {
	const char *op_name;
	OPTION op_enum;
} options[] = {
	{ "host",		OHOST},
	{"base",		OBASE},
	{"hostbase",	OHOSTBASE},
	{"prefix",	OPREFIX},
	{"release",	ORELEASE},
	{"notify",	ONOTIFY},
	{"login",	OLOGIN},
	{"password",	OPASSWORD},
	{"crypt",	OCRYPT},
	{"backup",	OBACKUP},
	{"delete",	ODELETE},
	{"execute",	OEXECUTE},
	{"old",		OOLD},
	{"timeout",	OTIMEOUT},
	{"nomtime",	ONOMTIME}
};

void
passdelim ( char **ptr, char delim ) /* skip over delimiter */
{
	extern char _argbreak;
	*ptr = (char *)skipover (*ptr, " \t");
	if (_argbreak != delim && **ptr == delim) {
		(*ptr)++;
		*ptr = (char *)skipover (*ptr, " \t");
	}
}

int
parsecoll( COLLECTION *c, char *collname_l, char *args )
{
	register char *arg,*p;
	register OPTION option;
	int opno;

	c->Cnext = NULL;
	c->Cname = strdup (collname_l);
	c->Chost = NULL;
	c->Chtree = NULL;
	c->Cbase = NULL;
	c->Chbase = NULL;
	c->Cprefix = NULL;
	c->Crelease = NULL;
	c->Cnotify = NULL;
	c->Clogin = NULL;
	c->Cpswd = NULL;
	c->Ccrypt = NULL;
	c->Ctimeout = -1;
	c->Cflags = 0;
	c->Cnogood = FALSE;
#ifndef NO_SUP_LOCKS
	c->Clockfd = -1;
#endif
	args = (char *)skipover (args," \t");
	while (*(arg=(char *)nxtarg(&args," \t="))) {
		for (opno = 0; opno < sizeof(options)/sizeof(options[0]); opno++)
			if (strcmp (arg,options[opno].op_name) == 0)
				break;
		if (opno == sizeof(options)/sizeof(options[0])) {
			logerr ("Invalid supfile option %s for collection %s",
				arg,c->Cname);
			return(-1);
		}
		option = options[opno].op_enum;
		switch (option) {
		case OHOST:
			passdelim (&args,'=');
			do {
				arg = (char *)nxtarg (&args,", \t");
				(void) Tinsert (&c->Chtree,arg,FALSE);
				arg = args;
				p = (char *)skipover (args," \t");
				if (*p++ == ',')  args = p;
			} while (arg != args);
			break;
		case OBASE:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Cbase = strdup (arg);
			break;
		case OHOSTBASE:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Chbase = strdup (arg);
			break;
		case OPREFIX:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Cprefix = strdup (arg);
			break;
		case ORELEASE:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Crelease = strdup (arg);
			break;
		case ONOTIFY:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Cnotify = strdup (arg);
			break;
		case OLOGIN:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Clogin = strdup (arg);
			break;
		case OPASSWORD:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Cpswd = strdup (arg);
			break;
		case OCRYPT:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Ccrypt = strdup (arg);
			break;
		case OBACKUP:
			c->Cflags |= CFBACKUP;
			break;
		case ODELETE:
			c->Cflags |= CFDELETE;
			break;
		case OEXECUTE:
			c->Cflags |= CFEXECUTE;
			break;
		case OOLD:
			c->Cflags |= CFOLD;
			break;
		case OTIMEOUT:
			passdelim (&args,'=');
			arg = (char *)nxtarg (&args," \t");
			c->Ctimeout = atoi (arg);
			break;
		case ONOMTIME:
			c->Cflags |= CFNOMTIME;
			break;
		}
	}
	return(0);
}
