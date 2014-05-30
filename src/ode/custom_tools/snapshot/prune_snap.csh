#!/bin/csh
# @OSF_FREE_COPYRIGHT@
# COPYRIGHT NOTICE
# (c) Copyright 1992, 1991, 1990 OPEN SOFTWARE FOUNDATION, INC. 
# ALL RIGHTS RESERVED 
# HISTORY
# $Log: prune_snap.csh,v $
# Revision 1.1.2.3  1992/12/03  19:08:59  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:40:34  damon]
#
# Revision 1.1.2.2  1992/02/23  21:23:25  damon
# 	Initial Version
# 	[1992/02/23  21:21:55  damon]
# 
# $EndLog$
# 
# usage: prune_snap.csh SNAPSHOT < not_for_dist.<offering>
# where not_for_dist.* is a list of files to remove from SNAPSHOT
#
rm tmp.tmp
touch tmp.tmp
set str="dummy"
while ( "$str" != "END" )
  set str=$<
  grep $str $1 >> tmp.tmp
end
mv tmp.tmp $1
