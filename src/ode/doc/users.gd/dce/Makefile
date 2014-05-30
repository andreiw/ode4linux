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
# Revision 1.2.2.2  1992/12/03  19:11:46  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:42:01  damon]
#
# Revision 1.2  1991/12/05  20:57:08  devrcs
# 	Added _FREE_ to copyright marker
# 	[91/08/01  08:09:36  mckeen]
# 
# 	Changes for Reno make
# 	[91/03/22  16:18:08  mckeen]
# 
# 	added appA (appendix A) to list of chapters and datafiles
# 	[91/02/21  14:52:31  ezf]
# 
# 	Now creates postscript files in ode environment
# 	[91/02/13  17:33:47  marty]
# 
# 	Newly created for DCE mini-DUG.
# 	[91/01/24  16:58:12  terry]
# 
# $EndLog$

INFORMATION     = title contents preface

CHAPTERS        = sandbox source.control compilation submit installation appA

_EROFFFLAGS_	= -p -mm

DATAFILES	= title.mm preface.mm contents.mm sandbox.mm source.control.mm compilation.mm submit.mm installation.mm appA.mm

MMFILES		= ${DATAFILES}
#
#       OBJECTDIR needs to be set to DUG directory: build OBJECTDIR=.
#

.include <${RULES_MK}>

#
#       rules for creating all of DUG as a post script file
#

dug: dug.ps

dug.ps: dug.mm
	${EROFF} ${_EROFFFLAGS_} dug.mm > dug.ps

dug.mm: ${MMFILES}

#
#       rules for creating post script files for each portion of DUG
#

.SUFFIXES : .mm .ps

.mm.ps:
	cat title.mm $*.mm  | ${EROFF} ${_EROFFFLAGS_} > $*.ps

title: title.ps
title.ps: title.mm
	cat title.mm | ${EROFF} ${_EROFFFLAGS_} > $*.ps

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

appA: appA.ps
appA.ps: title.mm appA.mm
