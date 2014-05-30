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
# Revision 1.14.9.2  1994/02/17  21:14:18  damon
# 	CR 1056. Added libcom
# 	[1994/02/17  21:14:07  damon]
#
# Revision 1.14.9.1  1994/02/17  16:30:57  damon
# 	CR 1056. Added libsup
# 	[1994/02/17  16:30:40  damon]
# 
# Revision 1.14.4.3  1993/05/13  15:51:44  damon
# 	CR 524. Moved logsubmit,rcsacl,srcacl to server dir
# 	[1993/05/13  15:51:37  damon]
# 
# Revision 1.14.4.2  1993/04/30  14:51:02  damon
# 	CR 436. Install logsubmit & *acl to /server/
# 	[1993/04/30  14:50:46  damon]
# 
# $EndLog$


SUBDIRS			= libcom libode libsup
EXPLIB_SUBDIRS		= libcom libode libsup

PROGRAMS		= oxm_relay_tcp

ILIST			= oxm_relay_tcp
IDIR			= /bin/

LIBS			= -lode

OFILES			= oxm_relay_tcp.o oxm_relay.o

.include <${RULES_MK}>
