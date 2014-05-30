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
# Revision 1.12.8.1  1994/02/07  14:26:46  damon
# 	Corrected comment leader
# 	[1994/02/07  14:26:37  damon]
#
# Revision 1.12.2.6  1992/12/03  19:03:43  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:33:43  damon]
# 
# Revision 1.12.2.5  1992/08/05  19:23:16  damon
# 	Narrowed down to just building bcs
# 	[1992/08/05  19:21:26  damon]
# 
# Revision 1.12.2.4  1992/07/26  17:37:28  gm
# 	Removed -D_BSD flag.
# 	[1992/07/17  20:43:07  gm]
# 
# Revision 1.12.2.3  1992/06/04  23:21:41  damon
# 	Synched with 2.1.1
# 	[1992/06/04  23:11:27  damon]
# 
# Revision 1.12.4.2  1992/04/15  17:15:25  damon
# 	Explicit recast via va_argv
# 	[1992/04/15  17:14:39  damon]
# 
# Revision 1.12  1991/12/17  20:57:36  devrcs
# 	Added LIBFLAGS definition to search cwd.
# 	[1991/12/09  17:03:26  mckeen]
# 
# Revision 1.11  1991/12/05  20:39:32  devrcs
# 	Added if_rcs.o
# 	[91/03/22  22:34:50  mckeen]
# 
# 	Changes for new source control API.
# 	[91/01/14  18:35:06  gm]
# 
# 	Changed BSD_LIBS, HOST_LIBS, and, HOST_FLAGS to
# 	TARGET_LIBS, TARGET_LIBS, and TARGET_FLAGS respectively.
# 	[91/01/14  15:58:28  damon]
# 
# 	Cleaned up for project ode
# 	[91/01/09  13:01:50  mckeen]
# 
# 	Added ${HOST_FLAGS} to CFLAGS line for porting to other hosts.
# 	[90/12/13  09:45:54  damon]
# 
# 	Added  ${BSD_LIBS} to LIBS line for porting to BSD systems.
# 	[90/12/12  14:59:41  damon]
# 
# Revision 1.10  90/10/31  15:34:13  devrcs
# 	Removed previous change - not appropriate for tools.
# 	[90/10/25  13:59:34  gm]
# 
# 	Added writable strings.  Need to fix addtobody, etc.
# 	[90/10/25  12:50:57  gm]
# 
# Revision 1.9  90/10/07  21:48:49  devrcs
# 	Added EndLog Marker.
# 	[90/09/29  14:01:16  gm]
# 
# Revision 1.8  90/08/09  14:40:52  devrcs
# 	Cleanup for export, install and post-freeze.
# 	[90/08/05  13:40:37  gm]
# 
# $EndLog$

PROGRAMS		= bcs

ILIST			= bcs
IDIR			= /bin/

LIBS			= -lode

INCFLAGS		= -I.
OFILES			= bcs.o

.include <${RULES_MK}>
