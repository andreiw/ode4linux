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
# Revision 1.2.6.1  1993/11/16  02:30:47  marty
# 	CR # 812 - Remove sindex from Makefiles.
# 	[1993/11/16  02:30:09  marty]
#
# Revision 1.2.4.2  1993/03/19  17:47:48  marty
# 	Remove salloc from the list.  The file is defunct.
# 	[1993/03/19  17:47:29  marty]
# 
# Revision 1.2.2.2  1992/12/03  17:23:32  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:09:50  damon]
# 
# Revision 1.2  1991/12/05  21:13:58  devrcs
# 	created cat directories to build formated manpages in
# 	[91/07/30  13:04:24  mckeen]
# 
# $EndLog$

VPATH			= ../man3

MANPAGES		= abspath concat def_build editor fdate filecopy \
			  fold getbool getstr interface makepath match \
			  nxtarg par_rc_file path prstab quit run \
			  sbdata searchp skipto stablk stlmatch \
			  stubs uquit

MANSECTION		= 3

ILIST			= ${MANPAGES:=.0}
IDIR			= /man/cat3/
IMODE			= 444

.include <${RULES_MK}>
