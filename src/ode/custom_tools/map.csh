#! /bin/csh -f
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
# $Log: map.csh,v $
# Revision 1.1.2.3  1992/12/03  19:08:50  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:37:59  damon]
#
# Revision 1.1.2.2  1992/01/06  22:00:45  robert
# 	Create a list of unique 14 char filenames from
# 	the output of find on a src tree with filenames
# 	greater then 14 chars. Non-unique 14 char
# 	names are made by removing (1-3) chars
# 	from the beginning of the file name, and pre-pending
# 	digits. This is done using awk scripts first.awk
# 	and second.awk. Modify second.awk to change
# 	the deletion/addition of chars to create unique names.
# 
# 	Note that the mapping.over file must be
# 	included with the icon tool as described in
# 	section 2.1.3 of the OSF/1 release notes.
# 	The icon tool typically shortens some strings
# 	in the context of files incorrectly, so
# 	beware that the only true test of the mapping.over
# 	file is to actually use it with the shorten tool
# 	and then perform a build.
# 
# 	No other guarantees can be made!
# 	[1992/01/06  22:00:11  robert]
# 
# $EndLog$

# requires awk scripts:
#			first.awk
#			second.awk
#
# mark filenames >= 14 chars from the output of find, then
# remove only those that are unique for further processing
# It does not matter if the input file is sorted or uniqued.
# If "files" is the output from find, invoke as
#
#		map.csh files
#
# redirect output as desired

set infile = $1
if (!(-e first.awk && -e second.awk)) then
	echo ""
	echo "Cannot find required awk scripts - check and rerun"
	exit 1
endif
if (-e mapping.over) then
	echo ""
	echo -n "A mapping.over file alredy exists. Delete it (y/n) ? [y] "
	set query = $<
	if ( "$query" !~ [nN] && "$query" !~ [nN][oO]) then 
		rm mapping.over 
	else
		echo "Please remove or rename mapping.over and run again"
		exit 1 
	endif
endif

if (-e ${infile}.to.process) rm ${infile}.to.process
echo ""
echo "Extracting file names >= 14 chars"
echo ""
cat ${infile}  | sed 's;...............*;>=14 &;' | grep '>=14' | sed 's;^>=14;;' | sort | uniq > ${infile}.to.process

# show how many files to process
# (including those 14 char ones we will later exclude
# from mapping.over

echo "Number of file >= 14 chars:"
echo "wc -l ${infile}.to.process"
echo ""
wc -l ${infile}.to.process
set files_to_proc = `wc -l ${infile}.to.process | sed 's;^[ ]*;;' | sed 's;[ ].*;;'`
if ("$files_to_proc" == 0) then
	echo "No files >= 14 chars to do - exitting."
	exit 0
endif
echo ""

# Do 1st pass to collect names shortened to 14 chars
# with any existing 14 char names found above and write to map.tmp.

if (-e map.tmp) rm map.tmp
echo "Sorting by 14 char file name - truncate from start of file name if necessary"
echo "${files_to_proc} filenames to process"
echo ""
cat ${infile}.to.process | awk -f first.awk | csh -f 
# do extra crlf after last number echoes
echo ""

# check for equal file line counts

set cnt1 = `wc -l ${infile}.to.process | sed 's;^[ ]*;;' | sed 's;[ ].*;;'`
set cnt2 = `wc -l map.tmp | sed 's;^[ ]*;;' | sed 's;[ ].*;;'`
echo "Counts will agree if file processing succeeded" 
echo "wc -l ${infile}.to.process map.tmp"
wc -l ${infile}.to.process map.tmp
echo ""
if ("$cnt1" != "$cnt2") then
	echo "Count of shortened file names in map.tmp does not agree - exitting" 
	echo ""
	exit 1
endif
	
# Sort map.tmp by this 2nd column (of shortened names) so
# that 2nd pass will process sequential file names with the same
# 14 char string

if (-e map.tmp.sortby14) rm map.tmp.sortby14
sort -t'	' +1 -o map.tmp.sortby14 map.tmp

# Do 2nd pass and mow off the 1st 3 chars, replacing them with numbers 0-999 for any 
# duplicate 14 char names. Only reset to 0 after exhausting all numbers. 
# Write a new file with this 2nd column scheme to map.tmp.digits

echo "Removing chars and prepending digits to duplicate 14 char filenames"
echo "Scanning all ${files_to_proc} shortened names sequentially"
echo "" 
if (-e map.tmp.digits) rm map.tmp.digits
cat map.tmp.sortby14 | awk '{print $1}' | awk -f second.awk | csh -f

# check to make sure really no duplicates in the second column

echo ""
if (-e col2.digits) rm col2.digits
if (-e col2.digits.su) rm col2.digits.su
cat map.tmp.digits | awk '{print $2}' | sort | uniq > col2.digits 
cat map.tmp.digits | awk '{print $2}' > col2.digits.su
set cnt1 = `wc -l col2.digits | sed 's;^[ ]*;;' | sed 's;[ ].*;;'`
set cnt2 = `wc -l col2.digits.su | sed 's;^[ ]*;;' | sed 's;[ ].*;;'`
echo "Counts will agree if creation of unique names succeeded"
echo "wc -l col2.digits col2.digits.su"
wc -l col2.digits col2.digits.su
echo ""
if ("$cnt1" != "$cnt2") then
	echo "Shortened names in 2nd column of map.tmp.digits still contain duplicates"
	echo "Change 2nd pass strategy and re-run"
	exit 1
endif 
rm col2.digits col2.digits.su

# now just create the final mapping over, which should only contain
# file names > 14 chars. This also changes to sorting by the 1st column.

echo "Creating mapping.over file"
cat map.tmp.digits | sed 's;^..............	.*;;' | sort | uniq  > mapping.over 
echo "wc -l mapping.over"
wc -l mapping.over
echo ""
echo "Check to see if a single blank line exists at the top of mapping.over"
echo "if so, delete it"
echo ""

# remove intermediate files
rm ${infile}.to.process map.tmp map.tmp.digits map.tmp.sortby14 

exit 0
