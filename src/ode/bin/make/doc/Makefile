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
# Revision 1.2.2.2  1992/12/03  19:05:13  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:35:08  damon]
#
# Revision 1.2  1991/12/05  20:42:26  devrcs
# 	Changes for Reno make
# 	[91/03/22  19:05:19  mckeen]
# 
# $EndLog$
#
LOCALS		= tutorial.ms tutorial.psc \
                  pmake.mansp pmake.psc \
		  Lst.mansp Lst.psc Makefile makefile tmac.ansp \
                  cctrl.8 customs.8 importquota.8 reginfo.1

SUBDIRS		= index ex1 ex2 customs


tutorial.t	: index/tmac.index tutorial.ms 
	ditroff -Plw -ms -t $(.ALLSRC) > tut.temp
	index/index -Plw -t tut.temp > $(.TARGET)
	rm -f tut.temp

print 		: tutorial.t
	lpr -Plw -h -n tutorial.t

package		::
	if [ ! -d $(PKGDIR) ]; then
		mkdir $(PKGDIR)
	fi
	cp $(LOCALS) $(PKGDIR)
	for i in $(SUBDIRS); do
		(cd $i; $(MAKE) "PKGDIR=$(PKGDIR)/$i" package)
	done
