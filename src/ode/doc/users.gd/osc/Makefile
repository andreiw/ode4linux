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
# Revision 1.2.2.2  1992/12/03  19:12:54  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:42:39  damon]
#
# Revision 1.2  1991/12/05  20:57:41  devrcs
# 	Changes for Reno make
# 	[91/03/22  16:18:15  mckeen]
# 
# 	Now creates postscript files in ode environment
# 	[91/02/13  17:34:23  marty]
# 
# 	Kill multiple occurrence of Endlog, HISTORY, or copyright header
# 	[91/02/04  17:28:04  robert]
# 
# 	Separating DUG into common and OSC versions
# 	[91/01/16  17:03:24  randyb]
# 
# $EndLog$

INFORMATION	= title contents preface 
#		  index

CHAPTERS	= sandbox source.control compilation submit installation

_EROFFFLAGS_	= -p -mm

DATAFILES	= sandbox.mm source.control.mm compilation.mm submit.mm installation.mm title.mm preface.mm contents.mm

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

.SUFFIXES : .mm .ps

.mm.ps:
	cat title.mm $*.mm | ${EROFF} ${_EROFFFLAGS_} > $*.ps

title: title.ps
title.ps: title.mm

contents: contents.ps
contents.ps: title.mm contents.mm

preface: preface.ps
preface.ps: title.mm preface.mm

sandbox: sandbox.ps
sandbox.ps: title.mm sandbox.mm

source.control: source.control.ps
source.control.ps: title.mm source.control.mm

compilation: compilation.ps
compilation.ps: title.mm compilation.mm

submit: submit.ps
submit.ps: title.mm submit.mm

installation: installation.ps
installation.ps: title.mm installation.mm

index: index.ps
index.ps: title.mm index.mm

#
#	dependency rules for each information and chapter file
#	also tbl and pic file conversions
#

installation.mm: installation.tbl

index.mm: index.tbl
