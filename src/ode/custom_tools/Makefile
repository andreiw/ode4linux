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
# HISTORY
# $Log: Makefile,v $
# Revision 1.2.4.3  1993/05/19  20:09:57  damon
# 	CR 528. Moved odexm_cli to bin/odexm_cli
# 	[1993/05/19  20:09:52  damon]
#
# Revision 1.2.4.2  1993/01/14  18:38:19  damon
# 	CR 400. Created odexm_cli
# 	[1993/01/14  18:37:12  damon]
# 
# Revision 1.2.2.5  1992/12/03  19:08:38  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:37:49  damon]
# 
# Revision 1.2.2.4  1992/12/01  23:12:26  pnh
# 	Added bdelta.c to program list.
# 	[1992/12/01  23:01:26  pnh]
# 
# Revision 1.2.2.3  1992/08/03  18:37:48  robert
# 	remove -D_BSD to sync up to Glenn's removal of BSD func
# 	[1992/08/03  18:30:29  robert]
# 
# 	LIBS arg now updated to -lode for libode
# 	CFLAGS =-D_BSD like most ODE commands.
# 	[1992/01/16  23:27:21  robert]
# 
# Revision 1.2  1991/12/05  20:55:07  devrcs
# 	generic Makefile
# 	[91/10/16  16:53:37  ezf]
# 
# $EndLog$

PROGRAMS		= mkrelease bdelta

ILIST			= mkrelease bdelta
IDIR			= /bin/

# CFLAGS		= -D_BSD
LIBS			= -lode

.include <${RULES_MK}>
