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
# Revision 1.6.7.1  1994/01/11  15:13:33  marty
# 	CR # 759 - Add sadmin man page.
# 	[1994/01/11  15:13:20  marty]
#
# Revision 1.6.4.3  1993/04/21  14:16:50  damon
# 	CR 421. Fixed typos
# 	[1993/04/21  14:15:14  damon]
# 
# Revision 1.6.4.2  1993/04/20  18:18:45  damon
# 	CR 421. Updated for 2.3
# 	[1993/04/20  18:17:54  damon]
# 
# Revision 1.6.2.3  1992/12/03  17:23:43  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:09:56  damon]
# 
# Revision 1.6.2.2  1992/12/01  23:04:20  pnh
# 	Added bdelta.1 to list of man files to make.
# 	[1992/12/01  22:57:40  pnh]
# 
# Revision 1.6  1991/12/05  21:14:07  devrcs
# 	Added make man page
# 	[1991/11/13  16:12:38  mckeen]
# 
# 	Added cat directories and set man directories to only build sources
# 	[91/07/30  13:04:33  mckeen]
# 
# 	Install mm files instead of cat file
# 	[91/04/19  11:01:30  mckeen]
# 
# 	Fixed bcreate.1 rule
# 	[91/03/22  23:15:19  mckeen]
# 
# 	Changes for Reno make
# 	[91/03/22  16:19:23  mckeen]
# 
# 	Cleaned up for project ode
# 	[91/01/09  13:07:51  mckeen]
# 
# Revision 1.5  90/10/07  21:55:43  devrcs
# 	Added EndLog Marker.
# 	[90/09/29  14:11:26  gm]
# 
# Revision 1.4  90/08/09  14:42:37  devrcs
# 	Cleanup for export, install and post-freeze.
# 	[90/08/05  13:41:22  gm]
# 
# $EndLog$

ALL_FILE_OPTS		= bcs bdiff blog bstat
MANSOURCE		= ${ALL_FILE_OPTS} bci bco bcreate bmerge make \
			  mklinks mksb \
			  resb bsubmit sadmin sbinfo build workon \
			  currentsb genpath sup release \
			  bdelta
DATAFILES		= ${MANSOURCE:=.1} 

ILIST			= ${MANSOURCE:=.1} 
IDIR			= /man/man1/
IMODE			= 444

.include <${RULES_MK}>

${ALL_FILE_OPTS:=.1}: $${.TARGET:.1=.hdr} bcsoptions.1 bcsfileoptions.1 $${.TARGET:.1=.bdy}
	cat ${${.TARGET:.1=.hdr}:P} \
	    ${bcsoptions.1:P} \
	    ${bcsfileoptions.1:P} \
	    ${${.TARGET:.1=.bdy}:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

bcreate.1: bcreate.hdr bcsoptions.1 bcreate.bdy
	cat ${bcreate.hdr:P} ${bcsoptions.1:P} ${bcreate.bdy:P} > bcreate.1.X
	${MV} bcreate.1.X bcreate.1

bci.1: bci.hdr bcsoptions.1 no_sv_file_opts.1 bci.bdy
	cat ${bci.hdr:P} \
	    ${bcsoptions.1:P} \
	    ${no_sv_file_opts.1:P} \
            ${bci.bdy:P} > bci.1.X
	${MV} bci.1.X bci.1

bco.1: bco.hdr bcsoptions.1 no_ch_file_opts.1 bco.bdy
	cat ${bco.hdr:P} \
	    ${bcsoptions.1:P} \
	    ${no_ch_file_opts.1:P} \
            ${bco.bdy:P} > bco.1.X
	${MV} bco.1.X bco.1

bmerge.1: bmerge.hdr bcsoptions.1 no_ch_file_opts.1 bmerge.bdy
	cat ${bmerge.hdr:P} \
	    ${bcsoptions.1:P} \
	    ${no_ch_file_opts.1:P} \
            ${bmerge.bdy:P} > bmerge.1.X
	${MV} bmerge.1.X bmerge.1

bsubmit.1: bsubmit.hdr bcsoptions.1 no_ch_file_opts.1 bsubmit.bdy
	cat ${bsubmit.hdr:P} \
	    ${bcsoptions.1:P} \
	    ${no_ch_file_opts.1:P} \
            ${bsubmit.bdy:P} > bsubmit.1.X
	${MV} bsubmit.1.X bsubmit.1
