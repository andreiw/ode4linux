# @OSF_FREE_COPYRIGHT@
# COPYRIGHT NOTICE
# (c) Copyright 1992, 1991, 1990 OPEN SOFTWARE FOUNDATION, INC. 
# ALL RIGHTS RESERVED 
# 
# HISTORY
# $Log: Makefile,v $
# Revision 1.1.2.4  1992/12/03  19:12:33  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:42:22  damon]
#
# Revision 1.1.2.3  1992/03/10  23:52:45  hester
# 	removed installation chapter
# 	[1992/03/10  23:52:30  hester]
# 
# Revision 1.1.2.2  1992/03/10  23:17:21  hester
# 	added pic and tbl rules
# 	[1992/02/24  22:53:20  hester]
# 
# 	added intro chapter
# 	[1992/02/19  16:00:33  hester]
# 
# 	first cut for Motif mini-DUG
# 	[1992/02/18  21:29:37  hester]
# 
# $EndLog$

INFORMATION	= title contents preface 
#		  index

CHAPTERS	= intro sandbox source.control compilation submit 

EROFF		= eroff
_EROFFFLAGS_	= -p -mm
PIC		= pic
TBL		= tbl

DATAFILES	= intro.mm sandbox.mm source.control.mm compilation.mm submit.mm title.mm preface.mm contents.mm

MMFILES		= ${DATAFILES}

#
#	OBJECTDIR needs to be set to DUG directory: build OBJECTDIR=.
#

.include <${RULES_MK}>

#
#	rules for creating all of DUG as a post script file
#

dug: dug.ps

dug.ps: dug.mm 
	${EROFF} ${_EROFFFLAGS_} dug.mm > dug.ps

dug.mm : ${MMFILES}

#
#	rules for creating post script files for each portion of DUG
#

.SUFFIXES : .mm .pic .tbl .ps

.mm.ps:
	${EROFF} title.mm ${.IMPSRC} ${_EROFFFLAGS_} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

.tbl.mm:
	${TBL} ${_TBLFLAGS_} ${.IMPSRC} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

.pic.mm:
	${PIC} ${.IMPSRC} > ${.TARGET}.X
	${MV} ${.TARGET}.X ${.TARGET}

title: title.ps
title.ps: title.mm

contents: contents.ps
contents.ps: title.mm contents.mm

preface: preface.ps
preface.ps: title.mm preface.mm

intro: intro.ps
intro.ps: title.mm intro.mm

sandbox: sandbox.ps
sandbox.ps: title.mm sandbox.mm

source.control: source.control.ps
source.control.ps: title.mm source.control.mm

compilation: compilation.ps
compilation.ps: title.mm compilation.mm

submit: submit.ps
submit.ps: title.mm submit.mm

index: index.ps
index.ps: title.mm index.mm

#
#	dependency rules for each information and chapter file
#	also tbl and pic file conversions
#

index.mm: index.tbl
