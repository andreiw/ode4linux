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
# Revision 1.10.4.3  1993/04/30  15:09:02  damon
# 	CR 436. Moved install from etc to server
# 	[1993/04/30  15:08:56  damon]
#
# Revision 1.10.4.2  1993/01/19  18:52:51  damon
# 	CR 408. Added odexm_tcp.c
# 	[1993/01/19  18:52:32  damon]
# 
# Revision 1.10.2.4  1992/12/03  19:13:47  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:43:03  damon]
# 
# Revision 1.10.2.3  1992/08/24  20:26:39  damon
# 	Fixed temp file transfers
# 	[1992/08/24  20:22:08  damon]
# 
# Revision 1.10.2.2  1991/12/30  21:27:23  damon
# 	Transition to libode from libsb
# 	[1991/12/20  22:10:48  damon]
# 
# Revision 1.10  1991/12/05  21:03:41  devrcs
# 	Added _FREE_ to copyright marker
# 	[91/08/01  08:10:05  mckeen]
# 
# 	Changes for Reno make
# 	[91/03/22  16:18:45  mckeen]
# 
# 	Added ${TARGET_FLAGS} to CFLAGS line.
# 	[91/02/02  11:55:01  damon]
# 
# 	Added changes to support RIOS and aix
# 	[91/01/22  13:00:08  mckeen]
# 
# 	Cleaned up for project ode
# 	[91/01/09  13:03:58  mckeen]
# 
# Revision 1.9  90/10/07  21:55:01  devrcs
# 	Added EndLog Marker.
# 	[90/09/29  14:10:24  gm]
# 
# Revision 1.8  90/08/09  14:42:25  devrcs
# 	Cleanup for export, install and post-freeze.
# 	[90/08/05  13:41:05  gm]
# 
# $EndLog$

PROGRAMS		= odexm

ILIST			= odexm
IDIR			= /server/

OFILES			= odexm.o odexm_tcp.o
LIBS			= -lode

.include <${RULES_MK}>
