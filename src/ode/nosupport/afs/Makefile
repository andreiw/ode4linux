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
# Revision 1.2.2.2  1992/12/03  17:26:58  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:30  damon]
#
# Revision 1.2  1991/12/05  21:18:32  devrcs
# 	Initial AFS files
# 	[1991/11/18  17:21:46  damon]
# 
# 	Changes for Reno make
# 	[91/03/22  16:18:57  mckeen]
# 
# 	Added ${TARGET_FLAGS} to CFLAGS line.
# 	[91/02/01  16:25:28  damon]
# 
# 	Polish for ODE II 1.0
# 	[91/01/24  16:13:31  mckeen]
# 
# 	Added quotes around ${machine}
# 	[91/01/22  16:05:13  mckeen]
# 
# 	Added -DMACHINE to CARGS
# 	[91/01/22  15:05:23  mckeen]
# 
# 	Chenged BSD_LIBS to TARGET_LIBS
# 	[91/01/22  14:30:43  mckeen]
# 
# 	Creations/Fixes for project ode lbe
# 	[91/01/17  16:44:20  mckeen]
# 
# 	Finished adding logsubmit in all the places it should go
# 	[91/01/11  16:33:34  randyb]
# 
# 	Cleaned up for project ode
# 	[91/01/09  13:06:56  mckeen]
# 
# 	Added ${BSD_LIBS} to LIBS line for porting to BSD systems
# 	[90/12/12  15:02:48  damon]
# 
# 	Added logsubmit to list of commands.
# 	[90/11/29  16:51:38  randyb]
# 
# Revision 1.12  90/10/07  21:55:10  devrcs
# 	Added EndLog Marker.
# 	[90/09/29  14:10:38  gm]
# 
# Revision 1.11  90/08/09  14:42:28  devrcs
# 	Cleanup for export, install and post-freeze.
# 	[90/08/05  13:41:10  gm]
# 
# $EndLog$


SUBDIRS			= libsb
EXPLIB_SUBDIRS		= libsb

PROGRAMS		= rcsauth rcsacl srcacl logsubmit

ILIST			= rcsauth rcsacl srcacl logsubmit
IDIR			= /lib/

LIBS			= -lsb

AFSFILES		= ${USE_AFS_COMM:Dafscode.o:U}

CFLAGS			= -D_BSD
rcsauth_OFILES		= rcsauth.o kxct.o ${AFSFILES}
rcsacl_OFILES		= rcsacl.o
srcacl_OFILES		= srcacl.o
logsubmit_OFILES	= logsubmit.o

.include <${RULES_MK}>
