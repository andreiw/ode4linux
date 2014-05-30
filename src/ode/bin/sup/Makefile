# COPYRIGHT NOTICE
# Copyright (c) 1992, 1991, 1990  
# Open Software Foundation, Inc. 
#  
# Permission is hereby granted to use, copy, modify and freely distribute 
# the software in this file and its documentation for any purpose without 
# fee, provided that the above copyright notice appears in all copies and 
# that both the copyright notice and this permission notice appear in 
# supporting documentation.  Further, provided that the name of Open 
# Software Foundation, Inc. ("OSF") not be used in advertising or 
# publicity pertaining to distribution of the software without prior 
# written permission from OSF.  OSF makes no representations about the 
# suitability of this software for any purpose.  It is provided "as is" 
# without express or implied warranty. 
#  
# Copyright (c) 1992 Carnegie Mellon University 
# All Rights Reserved. 
#  
# Permission to use, copy, modify and distribute this software and its 
# documentation is hereby granted, provided that both the copyright 
# notice and this permission notice appear in all copies of the 
# software, derivative works or modified versions, and any portions 
# thereof, and that both notices appear in supporting documentation. 
#  
# CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
# CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR 
# ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE. 
#  
# Carnegie Mellon requests users of this software to return to 
#  
# Software Distribution Coordinator  or  Software_Distribution@CS.CMU.EDU 
# School of Computer Science 
# Carnegie Mellon University 
# Pittsburgh PA 15213-3890 
#  
# any improvements or extensions that they make and grant Carnegie Mellon 
# the rights to redistribute these changes. 
#
#
# HISTORY
# $Log: Makefile,v $
# Revision 1.3.10.3  1994/02/18  18:24:18  damon
# 	CR 1056. Moved supscan and supfilesrv to server dir
# 	[1994/02/18  18:24:07  damon]
#
# Revision 1.3.10.2  1994/02/15  17:36:02  damon
# 	CR 1051. Allow pedantic flags to be used
# 	[1994/02/15  17:34:08  damon]
# 
# Revision 1.3.10.1  1994/02/08  22:40:38  damon
# 	CR 1049. Removed -DNEED_LOCKDEFS
# 	[1994/02/08  22:40:26  damon]
# 
# Revision 1.3.7.4  1993/05/28  18:45:40  marty
# 	CR # 558 - supfilesrv.c needs  -DNEED_LOCK_DEFS
# 	[1993/05/28  18:45:27  marty]
# 
# Revision 1.3.7.3  1993/04/30  17:20:07  damon
# 	CR 436. supfilesrv and supscan now installed in /server/
# 	[1993/04/30  17:19:57  damon]
# 
# Revision 1.3.7.2  1993/04/29  20:20:16  damon
# 	CR 464. Port to 386bsd from gm
# 	[1993/04/29  19:04:09  damon]
# 
# Revision 1.3.2.6  1992/12/02  19:52:42  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/02  19:50:58  damon]
# 
# Revision 1.3.2.5  1992/09/24  18:59:43  gm
# 	CR282: Made more portable to non-BSD systems.
# 	[1992/09/23  18:18:16  gm]
# 
# Revision 1.3.2.4  1992/07/26  17:37:43  gm
# 	Removed -D_BSD flag.
# 	[1992/07/17  20:53:54  gm]
# 
# Revision 1.3.2.3  1992/02/13  15:08:58  gm
# 	Added INCFLAGS to search the current directory.  Moved include
# 	of system rules to correct location.
# 	[1992/02/09  02:16:51  gm]
# 
# Revision 1.3.2.2  1991/12/30  21:26:40  damon
# 	Transition to libode from libsb
# 	[1991/12/20  21:58:35  damon]
# 
# Revision 1.3  1991/12/05  20:53:47  devrcs
# 	Changed OS_TYPE and CPU_TYPE to TARGET_os and TARGET_CPU
# 	[91/10/15  10:31:28  mckeen]
# 
# 	Added "-D${OS_TYPE}" for building supcmeat.o
# 	[91/09/05  16:42:39  marty]
# 
# 	Added _FREE_ to copyright marker
# 	[91/08/01  08:06:57  mckeen]
# 
# 	"Adding sup to ODE"
# 	[91/04/30  14:39:03  zeliff]
# 
# 	Integrating SUP into ODE RCS tree
# 	[91/04/30  12:16:29  zeliff]
# 
# 	Integrating SUP into ODE RCS tree
# 	[91/04/30  12:16:29  zeliff]
# 
# Revision 1.2  90/10/07  21:36:02  devrcs
# 	Restored as unsupported.
# 	[90/09/17  17:46:06  gm]
# 
# Revision 1.6  90/07/27  10:50:39  devrcs
# 	Added Support for Install
# 	[90/07/20  08:52:55  mckeen]
# 
# 	More gcc changes.
# 	[90/07/16  01:37:49  gm]
# 
# Revision 1.5  90/07/17  12:26:21  devrcs
# 	More changes for gcc.
# 	[90/07/09  18:41:50  gm]
# 
# Revision 1.4  90/06/29  14:18:28  devrcs
# 	Removed references to defunct libcs library.
# 	[90/06/23  15:00:56  gm]
# 
# 	Removed references to defunct libsys library.
# 	[90/06/20  17:46:37  gm]
# 
# Revision 1.3  90/05/24  21:56:40  devrcs
# 	Libraries moved to /usr/ccs/lib.
# 	[90/05/23  17:08:59  gm]
# 
# 	INCFLAGS/LIBFLAGS changes.
# 	[90/05/15  15:27:32  gm]
# 
# Revision 1.2  90/01/02  19:56:29  gm
# 	Fixes for first snapshot.
# 
# Revision 1.1  89/12/26  15:20:57  gm
# 	Current version from CMU.
# 	[89/12/23            gm]
# 
# Revision 1.10  89/08/23  14:55:19  gm0w
# 	Replaced msg<xxx>.o modules with new supmsg.o module.
# 	[89/08/23            gm0w]
# 
# Revision 1.9  88/11/08  20:09:05  gm0w
# 	Created for new and improved SSP format.
# 	[88/10/23            gm0w]
# 
# $EndLog$

ILIST			= sup
IDIR			= /bin/

PROGRAMS		= sup

OFILES			= supcmain.o supcmeat.o supcmisc.o supcname.o \
			   supcparse.o supcvers.o
LIBS			= -lcom -lsup -lode ${SUP_TARGET_LIBS}

CFLAGS			+= ${NO_SUP_LOCKS:D-DNO_SUP_LOCKS}

.include <${RULES_MK}>
