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
# Revision 1.2.5.1  1994/01/11  15:12:28  marty
# 	CR # 759 - Add sadmin man page.
# 	[1994/01/11  15:12:12  marty]
#
# Revision 1.2.2.2  1992/12/03  17:23:27  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:09:49  damon]
# 
# Revision 1.2  1991/12/05  21:13:55  devrcs
# 	Added make man page
# 	[1991/11/13  16:12:31  mckeen]
# 
# 	created cat directories to build formated manpages in
# 	[91/07/30  13:04:19  mckeen]
# 
# $EndLog$

VPATH			= ../man1

BCMDS			= bci bco bcs bdiff blog bmerge bstat
MANPAGES		= ${BCMDS} bcreate make mklinks mksb \
			  resb bsubmit sadmin sbinfo build workon \
			  currentsb genpath sup release
MANSECTION		= 1

ILIST			= ${MANPAGES:=.0} 
IDIR			= /man/cat1/
IMODE			= 444

.include <${RULES_MK}>

