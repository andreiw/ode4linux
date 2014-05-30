#!/bin/csh
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
# HISTORY
# $Log: gcl.csh,v $
# Revision 1.1.2.5  1992/12/03  19:08:46  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:37:56  damon]
#
# Revision 1.1.2.4  1992/08/12  18:55:14  damon
# 	Fixed tab and changed cut
# 	[1992/08/12  18:54:57  damon]
# 
# Revision 1.1.2.3  1992/05/12  21:05:28  damon
# 	Fixed problem with " in comment leader
# 	[1992/05/12  21:03:20  damon]
# 
# Revision 1.1.2.2  1992/05/12  20:54:35  damon
# 	Initial Version
# 	[1992/05/12  20:54:18  damon]
# 
# $EndLog$
#
# This script produces a tab separated list of files and comment leaders for
# use with the copyscan program. To use it:
# -Generate a list of files which you want comment leaders for.
# -Add 'END' to the end of the list.
# -Move to the rcs tree for those files.
# -Run 'gcl.csh < file_list'
#
# This will send the tab separated list to standard out.
#
set str=$<
while ( "$str" != "END" )
  rm -f tmp.1 tmp.2
  echo $str > tmp.1
  rlog -h $str,v | grep 'comment leader' | cut -c18- | sed 's;\(.*\).$;\1;' > tmp.2
  echo "`cat tmp.1`	`cat tmp.2`"
  set str=$<
end
