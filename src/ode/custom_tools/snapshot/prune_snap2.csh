#!/bin/csh
# @OSF_FREE_COPYRIGHT@
# COPYRIGHT NOTICE
# (c) Copyright 1992, 1991, 1990 OPEN SOFTWARE FOUNDATION, INC. 
# ALL RIGHTS RESERVED 
# HISTORY
# $Log: prune_snap2.csh,v $
# Revision 1.1.2.3  1992/12/03  19:09:00  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:40:36  damon]
#
# Revision 1.1.2.2  1992/02/23  21:23:32  damon
# 	Initial Version
# 	[1992/02/23  21:22:06  damon]
# 
# $EndLog$
#
# usage: prune_snap2.csh SNAPSHOT < dist.<offering>
# where dist.* is a list of files and directories to keep in SNAPSHOT
#
rm tmp.tmp
echo "./Makefile" > tmp.tmp
set str="dummy"
while ( "$str" != "END" )
  set str=$<
  grep $str $1 >> tmp.tmp
end
mv tmp.tmp $1
