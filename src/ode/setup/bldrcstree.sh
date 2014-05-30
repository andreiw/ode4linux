#!/bin/sh
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
# $Log: bldrcstree.sh,v $
# Revision 1.2.2.2  1992/12/03  17:27:21  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:38  damon]
#
# Revision 1.2  1991/12/05  21:18:44  devrcs
# 	Updated for ode2.1 and rcs5.5
# 	[1991/11/04  19:00:53  mckeen]
# 
# 	removed deletion of leader.changes file
# 	[91/05/14  10:07:26  hester]
# 
# 	First revision of this script
# 	[91/01/25  19:12:05  rec]
# 
# $EndLog$
#


# usage "create_v_files <src-base>"

# create files
touch FILES_NOT_FOUND

# Find all the files in the tree

find $1 -type f -print -exec add_header.sh {} \;

# or use the following if running a second time (move FILES_NOT_FOUND to 
# FILE_LIST and update add_header.sh).

#cat  FILE_LIST | xargs -n1 add_header.sh

