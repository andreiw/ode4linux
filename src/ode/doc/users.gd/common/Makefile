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
# Revision 1.3.4.2  1993/05/13  13:36:13  damon
# 	CR 802. Add docs to install tree
# 	[1993/05/13  13:35:53  damon]
#
# Revision 1.3.4.1  1993/05/13  13:36:12  damon
# *** Initial Branch Revision ***
#
# Revision 1.3.2.4  1992/12/03  19:10:09  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:41:18  damon]
# 
# Revision 1.3.2.3  1992/11/18  15:44:42  damon
# 	CR 12. Changed dug to users.gd and UsersGuide as appropriate
# 	[1992/11/18  15:44:23  damon]
# 
# Revision 1.3.2.2  1992/07/26  18:17:18  gm
# 	Added correct quoting of dynamic dependents.
# 	[1992/07/17  20:57:26  gm]
# 
# Revision 1.3  1991/12/17  20:59:41  devrcs
# 	Fixed up some stupid build errors...
# 	[1991/12/12  21:37:42  mckeen]
# 
# 	Fixed up page numbering
# 	[1991/12/11  21:32:58  mckeen]
# 
# 	*** empty log message ***
# 	[1991/12/09  21:34:22  marty]
# 
# 	Added make(1) to man page list
# 	[1991/12/09  19:39:39  mckeen]
# 
# 	Added rules to build manpages for appendix
# 	[1991/12/09  19:31:42  mckeen]
# 
# Revision 1.2  1991/12/05  20:55:43  devrcs
# 	Modified to build in ODE 2.1
# 	[91/07/17  10:00:15  mckeen]
# 
# 	Allow building of individual chapters witht the title page.
# 	[91/07/15  16:21:44  marty]
# 
# 	Rewrote to build dug automaticaly
# 	[91/05/29  10:17:48  mckeen]
# 
# 	Changes for Reno make
# 	[91/03/22  16:17:56  mckeen]
# 
# 	Now creates postscript files in ode environment
# 	[91/02/13  17:33:04  marty]
# 
# 	Separating DUG into common and OSC versions
# 	[91/01/16  16:57:04  randyb]
# 
# 	Pre Tools II release
# 	[91/01/09  14:59:02  mckeen]
# 
# $EndLog$

VPATH		= ../../../man/man1:../../../man/man5

ILIST		= UsersGuide.ps UsersGuide.appendixA.ps
IDIR		= /doc/
EROFF		?= eroff
_EROFFFLAGS_	= -p -mm
PIC		= pic
TBL		= tbl

OTHERS		= UsersGuide.ps UsersGuide.appendixA.ps

UsersGuide.ps_CHAPTERS	= title.mm preface.mm intro.mm \
		  sandbox.mm source.control.mm build.sml \
		  submit.mm appendix.man.mm index.mm contents.mm 
		  
UsersGuide.ps_INCPS	= backing.trees.ps backing.tree.set.ps sb.dir.struct.ps \
		  rc.file.struct.ps build.dir.struct.ps

UsersGuide.appendixA.ps_MANPS	= bci.1.ps bco.1.ps bcreate.1.ps bcs.1.ps bdiff.1.ps \
		  blog.1.ps bmerge.1.ps bstat.1.ps bsubmit.1.ps build.1.ps \
		  currentsb.1.ps genpath.1.ps make.1.ps makefiles.5.ps \
                  mklinks.1.ps \
		  mksb.1.ps oderc.5.ps resb.1.ps sadmin.1.ps sbinfo.1.ps \
		  sup.1.ps uptodate.1.ps workon.1.ps

.include <${RULES_MK}>


#
#	rules for creating post script files for each portion of DUG
#

.SUFFIXES : .mm .pic .tbl .ps

UsersGuide.ps: $${$${.TARGET}_CHAPTERS} $${$${.TARGET}_INCPS}
	${EROFF} ${_EROFFFLAGS_} ${.ALLSRC:N*.ps} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

UsersGuide.appendixA.ps:  $${$${.TARGET}_MANPS}
	cat ${${.TARGET}_MANPS} >> ${.TARGET}

.tbl.mm:
	${TBL} ${_TBLFLAGS_} ${.IMPSRC} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

.pic.mm:
	${PIC} ${.IMPSRC} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

${UsersGuide.ps_INCPS} : $${.TARGET:.ps=.incps}
	cp ${${.TARGET:.ps=.incps}:P} ${.TARGET}

${UsersGuide.appendixA.ps_MANPS} : $${.TARGET:.ps=}
	${EROFF} -man -p ${${.TARGET:.ps=}:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

index.mm: ../../tools/indexmac1.mm index.mm.data ../../tools/indexmac2.mm
	cat ${.ALLSRC} > index.mm.X
	mv index.mm.X index.mm

index.mm.data: ../../tools/extmac.mm.alt $${UsersGuide.ps_CHAPTERS:N*index.mm} ../../tools/indexmac3.mm
	${EROFF} ${_EROFFFLAGS_} ${.ALLSRC} > /dev/null 2> index.mm.temp
	cat index.mm.temp | sed -n 's/\!INDEX: //p' | sed "s/-/~/g" | sort -fu |sed 's/~00*/~/g' | ../../tools/mmindex > index.mm.data
	rm -f index.mm.temp

build.ps: title.mm build.sml
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/build.sml:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

intro.ps: ${MAKETOP}ode/doc/users.gd/common/title.mm ${MAKETOP}ode/doc/users.gd/common/intro.mm
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/intro.mm:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

preface.ps: ${MAKETOP}ode/doc/users.gd/common/title.mm ${MAKETOP}ode/doc/users.gd/common/preface.mm
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/preface.mm:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}
	
sandbox.ps: ${MAKETOP}ode/doc/users.gd/common/title.mm ${MAKETOP}ode/doc/users.gd/common/sandbox.mm
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/sandbox.mm:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

source.control.ps: ${MAKETOP}ode/doc/users.gd/common/title.mm ${MAKETOP}ode/doc/users.gd/common/source.control.mm
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/source.control.mm:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

compilation.ps: ${MAKETOP}ode/doc/users.gd/common/title.mm ${MAKETOP}ode/doc/users.gd/common/compilation.mm
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/compilation.mm:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

submit.ps: ${MAKETOP}ode/doc/users.gd/common/title.mm ${MAKETOP}ode/doc/users.gd/common/submit.mm 
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/submit.mm:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

installation.ps: ${MAKETOP}ode/doc/users.gd/common/title.mm ${MAKETOP}ode/doc/users.gd/common/installation.mm
	${EROFF} ${_EROFFFLAGS_} ${${MAKETOP}ode/doc/users.gd/common/title.mm:P} \
		${${MAKETOP}ode/doc/users.gd/common/installation.mm:P} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}




