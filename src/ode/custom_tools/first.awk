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
# $Log: first.awk,v $
# Revision 1.1.2.3  1992/12/03  19:08:48  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:37:57  damon]
#
# Revision 1.1.2.2  1992/01/06  21:02:10  robert
# 	use with map.csh to create mapping.over file
# 	for 14 char filename suppport
# 	[1992/01/06  21:00:22  robert]
# 
# $EndLog$
BEGIN {print "@ filecnt = 0"}
{
	print "@ filecnt ++";
	print "echo -n \"$filecnt \""; 
	print "@ cnt = 0";
	print "set cnt = `echo \""$0"\" | wc -c`";
	print "@ cnt -=1";
	print "if (\"$cnt\" > 14) then";
#	print "	echo -n \""$0" is $cnt chars long; \"";
	print "	@ strip = $cnt";
	print "	@ strip -=14";
#	print "	echo \"removing 1st $strip characters\"";
	print "	set shortstring = `echo \""$0"\" | sed 's;^.\{'$strip'\};;'`";
	print "	set outstring = $shortstring";
#	print "	echo \""$0"					$outstring\"";
	print "	echo  \""$0"					$outstring\" >> map.tmp";
	print "else";
#	print "	echo \""$0" is less than or = 14 chars\"";
	print "	echo \""$0"					"$0"\" >> map.tmp"; 
	print "endif";
#	print "echo \"\"";
	print "";
}
