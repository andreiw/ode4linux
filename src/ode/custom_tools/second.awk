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
# $Log: second.awk,v $
# Revision 1.1.2.3  1992/12/03  19:08:52  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:38:00  damon]
#
# Revision 1.1.2.2  1992/01/06  21:02:14  robert
# 	use with map.csh to create mapping.over file
# 	for 14 char filename suppport
# 	[1992/01/06  21:01:17  robert]
# 
# $EndLog$
BEGIN {print "@ bumpcnt = 0";print "set prevstring = \"\"";print "@ filecnt = 0"}
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
	print "	if (\"$prevstring\" == \"$shortstring\") then";
	print "		if (\"$bumpcnt\" == 999) @ bumpcnt = 0";
	print "		@ bumpcnt ++";
	print "		set numshortstring = `echo ${shortstring} | sed 's;^...;'$bumpcnt';'`";
	print "		set outstring = $numshortstring";
	print "	else";
	print "		set outstring = $shortstring";
	print "	endif";
#	print "	echo \""$0"					$outstring\"";
	print "	echo  \""$0"					$outstring\" >> map.tmp.digits";
	print "else";
#	print "	echo \""$0" is less than or = 14 chars\"";
	print "	echo \""$0"					"$0"\" >> map.tmp.digits"; 
	print "endif";
	print "set prevstring = $shortstring";
#	print "echo \"\"";
	print "";
}
