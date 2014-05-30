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
# Revision 1.3.6.1  1993/11/20  21:21:57  damon
# 	CR 801. Added administration chapter
# 	[1993/11/20  21:21:45  damon]
#
# Revision 1.3.4.3  1993/05/13  13:36:09  damon
# 	CR 802. Add docs to install tree
# 	[1993/05/13  13:35:52  damon]
# 
# Revision 1.3.4.2  1993/04/22  15:27:54  damon
# 	CR 458. Updated for 2.3
# 	[1993/04/22  15:24:05  damon]
# 
# Revision 1.3.2.5  1992/12/03  19:09:04  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:40:39  damon]
# 
# Revision 1.3.2.4  1992/11/19  19:13:30  damon
# 	CR 332. Added shared.mm
# 	[1992/11/19  19:13:10  damon]
# 
# Revision 1.3.2.3  1992/11/18  22:30:13  damon
# 	CR 332. Added odexm.tbl
# 	[1992/11/18  22:29:36  damon]
# 
# Revision 1.3.2.2  1992/11/18  15:07:58  damon
# 	CR 332. Removed merge.pic
# 	[1992/11/18  15:07:21  damon]
# 
# Revision 1.3  1991/12/17  21:00:41  devrcs
# 	converted to operate similar to DUG makefile
# 	[1991/12/06  21:04:01  mckeen]
# 
# Revision 1.2  1991/12/05  20:58:55  devrcs
# 	removed upd.builds.mm and release.mm
# 	[91/08/02  15:23:38  hester]
# 
# 	added merge.pic
# 	[91/08/01  17:21:47  hester]
# 
# 	goes with interim changes to SAG, including
# 	rearrangement of chapters, adding pictures.
# 	[91/07/23  13:53:42  hester]
# 
# 	Changes for Reno make
# 	[91/03/22  16:18:26  mckeen]
# 
# 	Now makes posrscript files in ode environment
# 	[91/02/13  17:32:10  marty]
# 
# 	SAG Makefile
# 	[91/01/25  19:42:14  hester]
# 
# $EndLog$
#

VPATH		= templates
ILIST		= sag.ps odexm.map
odexm.map_IDIR	= /server/
IDIR		= /doc/

EROFF           = eroff
_EROFFFLAGS_    = -p -mm
PIC             = pic
TBL             = tbl

sag.ps_CHAPTERS = title.mm preface.mm component.mm distribution.mm \
		  build.instl.mm odexm.mm src.cntrl.mm back.tree.mm\
		  shared.mm admin.mm trouble.mm index.mm contents.mm

OTHERS		= sag.ps

.include <${RULES_MK}>

#
#	rule for creating all of SAG as a post script file
#

.SUFFIXES : .mm .pic .tbl .ps

${OTHERS}: $${$${.TARGET}_CHAPTERS}
	${EROFF} ${_EROFFFLAGS_} ${.ALLSRC} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

.tbl.mm:
	${TBL} ${_TBLFLAGS_} ${.IMPSRC} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

.pic.mm:
	${PIC} ${.IMPSRC} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

#
#	rules for creating post script files for each portion of SAG
#

.pic.mm:
	${PIC} ${_PICFLAGS_} ${.IMPSRC} > ${.TARGET}

.tbl.mm:
	${TBL} ${_TBLFLAGS_} ${.IMPSRC} > ${.TARGET}

index.mm:  ../tools/indexmac1.mm index.mm.data ../tools/indexmac2.mm
	cat ${.ALLSRC} > index.mm.X
	mv index.mm.X index.mm

index.mm.data: ../tools/extmac.mm.alt $${sag.ps_CHAPTERS:N*index.mm} ../tools/indexmac3.mm
	${EROFF} ${_EROFFFLAGS_} ${.ALLSRC} > /dev/null 2> index.mm.temp
	cat index.mm.temp | sed -n 's/\!INDEX: //p' | sed "s/-/~/g" | sort -fu | sed 's/~00*/~/g' | ../tools/mmindex > index.mm.data
	rm -f index.mm.temp
