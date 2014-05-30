#
# @OSF_FREE_COPYRIGHT@
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
#
# HISTORY
# $Log: Makefile,v $
# Revision 1.13.4.2  1993/01/13  20:38:19  damon
# 	CR 392. Removed sadmin.c, lockcmds.c, and sbutil.c
# 	[1993/01/13  20:33:36  damon]
#
# Revision 1.13.2.4  1992/12/03  19:04:03  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:34:00  damon]
# 
# Revision 1.13.2.3  1992/09/24  18:45:11  gm
# 	CR259: Removed bcscall.o from OFILES.
# 	[1992/09/23  18:16:31  gm]
# 
# Revision 1.13.2.2  1991/12/30  21:24:34  damon
# 	Transition to libode from libsb
# 	[1991/12/20  21:57:53  damon]
# 
# Revision 1.13  1991/12/05  20:40:28  devrcs
# 	Added _FREE_ to copyright marker
# 	[91/08/01  08:03:39  mckeen]
# 
# 	Changes for Reno make
# 	[91/03/22  15:30:06  mckeen]
# 
# 	Added ${TARGET_FLAGS} to CFLAGS line for porting.
# 	[91/02/01  16:36:17  damon]
# 
# 	Changed BSD_LIBS, HOST_LIBS, and, HOST_FLAGS to
# 	TARGET_LIBS, TARGET_LIBS, and TARGET_FLAGS respectively.
# 	[91/01/14  16:01:55  damon]
# 
# 	Changed IDIR for project ode
# 	[91/01/10  09:19:22  mckeen]
# 
# 	Cleaned up for project ode
# 	[91/01/09  13:01:56  mckeen]
# 
# 	Added ${HOST_LIBS} to LIBS line for porting to other systems.
# 	[90/12/13  19:32:26  damon]
# 
# 	Added ${HOST_LIBS} to LIBS line for porting to other systems.
# 	[90/12/13  19:32:26  damon]
# 
# Revision 1.12  90/10/07  21:49:55  devrcs
# 	Added EndLog Marker.
# 	[90/09/29  14:02:51  gm]
# 
# Revision 1.11  90/09/13  13:03:06  devrcs
# 	Added bsubmit.h to HFILES.
# 	[90/08/26            gm]
# 
# Revision 1.10  90/08/09  14:40:59  devrcs
# 	Cleanup for export, install and post-freeze.
# 	[90/08/05  13:40:43  gm]
# 
# $EndLog$

PROGRAMS		= bsubmit

ILIST			= bsubmit
IDIR			= /bin/

LIBS			= -lode

HFILES			= bsubmit.h

.include <${RULES_MK}>
