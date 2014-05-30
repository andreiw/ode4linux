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
# Revision 1.4.2.6  1992/12/03  19:08:12  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:37:23  damon]
#
# Revision 1.4.2.5  1992/09/24  18:59:36  gm
# 	CR282: Made more portable to non-BSD systems.
# 	[1992/09/23  18:18:01  gm]
# 
# Revision 1.4.2.4  1992/07/26  17:37:36  gm
# 	Removed -D_BSD flag.
# 	[1992/07/17  20:52:02  gm]
# 
# Revision 1.4.2.3  1992/06/12  20:01:19  damon
# 	Synched with 2.1.1
# 	[1992/06/12  19:49:16  damon]
# 
# Revision 1.4.2.2  1991/12/30  21:25:55  damon
# 	port to sparc_sunos and libsb to libode transition
# 	[1991/12/20  20:13:28  damon]
# 
# Revision 1.4.4.3  1992/04/03  14:20:56  damon
# 	Fixed NO_RELEASE_DATABASE syntax
# 	[1992/04/03  14:20:37  damon]
# 
# Revision 1.4.4.2  1992/04/02  23:41:01  damon
# 	Made NO_RELEASE_DATABASE an env and skip release_db.o build
# 	[1992/04/02  23:40:18  damon]
# 
# Revision 1.4  1991/12/05  20:53:16  devrcs
# 	Added _FREE_ to copyright marker
# 	[91/08/01  08:06:29  mckeen]
# 
# 	Added -D_BLD to release CFLAGS.
# 	[91/05/28  09:35:07  mckeen]
# 
# 	Changes for Reno make
# 	[91/03/22  16:17:14  mckeen]
# 
# 	Added changes to support RIOS and aix
# 	[91/01/22  12:59:53  mckeen]
# 
# 	Cleaned up for project ode
# 	[91/01/09  13:02:50  mckeen]
# 
# Revision 1.3  90/10/07  21:52:08  devrcs
# 	Added EndLog Marker.
# 	[90/09/29  14:06:07  gm]
# 
# Revision 1.2  90/09/23  16:56:06  devrcs
# 	Moved components into their own subdirectories.
# 	[90/09/22  15:49:07  gm]
# 
# $EndLog$

VPATH			= ${OBJECT_FORMAT}

PROGRAMS		= release

ILIST			= release
IDIR			= /bin/

CFLAGS			= -D_BLD -D${OBJECT_FORMAT}
HFILES			= ${NO_RELEASE_DATABASE:D:Urelease_db.h}
OFILES			= release.o stripfile.o\
			  ${NO_RELEASE_DATABASE:D:Urelease_db.o}
LIBS			= -lode

.include <${RULES_MK}>
