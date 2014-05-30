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
# HISTORY
# $Log: add_header.sh,v $
# Revision 1.2.4.2  1993/05/17  15:58:48  damon
# 	CR 879. Set locking to be non-strict
# 	[1993/05/17  15:58:38  damon]
#
# Revision 1.2.4.1  1993/05/17  15:58:47  damon
# *** Initial Branch Revision ***
#
# Revision 1.2.2.2  1992/12/03  17:27:16  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:36  damon]
# 
# Revision 1.2  1991/12/05  21:18:41  devrcs
# 	Made the following changes
# 	           - Fixed handling of .sh and .csh files so that
# 	             the #!/bin/[c]sh stays at the top of the file (before
# 	             the comment containing the copyleft marker).
# 	           - Added code to determine if files with no filename
# 	             extension are shell scripts.
# 	           - added code to handle .idl and .acf files
# 	           - changed the log string from "$Log: add_header.sh,v $
# Revision 1.2.4.2  1993/05/17  15:58:48  damon
# 	CR 879. Set locking to be non-strict
# 	[1993/05/17  15:58:38  damon]
#
# Revision 1.2.4.1  1993/05/17  15:58:47  damon
# *** Initial Branch Revision ***
#
# 	Revision 1.2.3.2  1993/05/17  15:58:38  damon
# 	CR 879. Set locking to be non-strict
# 
# 	Revision 1.2.2.2  1992/12/03  17:27:16  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:36  damon]
# 
# 	Revision 1.2.1.2  1992/12/03  17:11:36  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 
# 	Revision 1.2.1.1  1992/12/03  15:37:23  damon
# 	 to "$Log: add_header.sh,v $
# Revision 1.2.4.2  1993/05/17  15:58:48  damon
# 	CR 879. Set locking to be non-strict
# 	[1993/05/17  15:58:38  damon]
#
# Revision 1.2.4.1  1993/05/17  15:58:47  damon
# *** Initial Branch Revision ***
#
# 	Revision 1.2.3.2  1993/05/17  15:58:38  damon
# 	CR 879. Set locking to be non-strict
# 
# 	Revision 1.2.2.2  1992/12/03  17:27:16  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:36  damon]
# 
# 	Revision 1.2.1.2  1992/12/03  17:11:36  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 
# 	Revision 1.2.1.1  1992/12/03  15:37:23  damon
# 	             to agree with prepfile/mkrelease
# 	           - changed all occurances of extention to extension :-)
# 	~
# 	[1991/11/22  21:21:33  mhickey]
# 
# $EndLog$
# 


# Get the extension and the file name
EXT=`echo $1 | sed 's;^.*\.;;'`
BASE_NAME=`basename $1`

DLOGD='$''Log:''$'

# Set the LEADER flag to not defined
LEADER="NOT_DEFINED"

#
# Determine the type of comment leader by looking at the file
# name extension.  You should add additional comment leaders 
# for all file types (extensions) that you know exist in your
# source tree.

#
# if we have no extension at this point, see if this is a shell script. If
# we determine that it is a shell script or if the extension indicates a shell
# script, rip off line 1 for use later.
#
if [ "$EXT" = "" -o "$EXT" = "sh" -o "$EXT" = "csh" ]
then
  temp=`head -1 $1`
fi
if [ "$EXT" = "" ]
then
  is_shell=`echo $temp | grep '^#![ 	]/bin/'` 
  if [ $? -eq 0 -o "$EXT" = "sh" -o "$EXT" = "csh" ]
  then
    echo $1 >> /usr/tmp/ASSUME_SHELL
    EXT="sh"
  fi
fi

if [ "$BASE_NAME" = "Makefile" ] || [ "$EXT" = "mk" ] || [ "$BASE_NAME" = "makefile" ] || [ "$EXT" = "sh" ] ||  [ "$EXT" = "csh" ]
then
  LEADER="# "
fi

if [ "$BASE_NAME" = "Imakefile" ]
then
  LEADER="/**/# "
fi

if [ "$EXT" = "c" ] || [ "$EXT" = "h" ] || [ "$EXT" = "idl" ] || [ "$EXT" = "acf" ]
then
  LEADER=" * "
fi

if [ "$EXT" = "mm" ]
then
  LEADER='...\" '
fi

# Cat the comment leader, with the file itself.
if [ "$LEADER" = "# " ]
then
  if [ "$EXT" = "sh" -o "$EXT" = "csh" ]
  then
       #
       # We handle shell scripts specially since if the first line doesn't
       # have the "#!/bin/..", the thing won't execute.  We take the line 1
       # that we previously stored, and put it in the output file first.
       #
       echo $temp > files2.tmp
       echo '#' >> files2.tmp
  else
       echo '#' > files2.tmp
  fi
  echo '# @OSF_FREE_COPYRIGHT@' >> files2.tmp
  echo '#' >> files2.tmp
  echo '#' >> files2.tmp
  echo '# HISTORY' >> files2.tmp
  echo  "$LEADER$DLOGD" >> files2.tmp
  echo '# $EndLog$' >> files2.tmp
  echo '#' >> files2.tmp
  if [ "$EXT" = "sh" -o "$EXT" = "csh" ]
  then
       #
       # We handle shell scripts specially. We already wrote the original line
       # 1 to the output file, so only write the rest of the lines (thanks, 
       # tail!!) at this point.
       #
       tail +2 $1 >> files2.tmp
  else
       cat $1 >> files2.tmp
  fi
  mv files2.tmp $1
fi

if [ "$LEADER" = " * " ]
then
  echo '/*' > files2.tmp
  echo ' * @OSF_FREE_COPYRIGHT@' >> files2.tmp
  echo ' */' >> files2.tmp
  echo '/*' >> files2.tmp
  echo ' * HISTORY' >> files2.tmp
  echo  "$LEADER$DLOGD" >> files2.tmp
  echo ' * $EndLog$' >> files2.tmp
  echo ' */' >> files2.tmp
  cat $1 >> files2.tmp
  mv files2.tmp $1
fi

if [ "$LEADER" = '...\" ' ]
then
  echo '...\"' > files2.tmp
  echo '...\" @OSF_FREE_COPYRIGHT@' >> files2.tmp
  echo '...\"' >> files2.tmp
  echo '...\"' >> files2.tmp
  echo '...\" HISTORY' >> files2.tmp
  echo  "$LEADER$DLOGD" >> files2.tmp
  echo '...\" $EndLog$' >> files2.tmp
  echo '...\"' >> files2.tmp
  cat $1 >> files2.tmp
  mv files2.tmp $1
fi

if [ "$LEADER" = "/**/# " ]
then
  echo '/**/#' > files2.tmp
  echo '/**/# @OSF_FREE_COPYRIGHT@' >> files2.tmp
  echo '/**/#' >> files2.tmp
  echo '/**/#' >> files2.tmp
  echo '/**/# HISTORY' >> files2.tmp
  echo  "$LEADER$DLOGD" >> files2.tmp
  echo '/**/# $EndLog$' >> files2.tmp
  echo '/**/#' >> files2.tmp
  cat $1 >> files2.tmp
  mv files2.tmp $1
fi

# If the file type is not known, add it to the list
# of files not done, else check it in.

if [ "$LEADER" = "NOT_DEFINED" ]
then
  echo $1 >> FILES_NOT_FOUND
else
  ci -t/dev/null $1
fi

if [ "$LEADER" != "NOT_DEFINED" ] && [ "$EXT" != "c" ] 
then
  rcs -c"$LEADER" $1,v
fi

# Set locking to be non-strict.
rcs -U $1,v


# Uncomment the following line if you just want to add all the unknown files
# to the rcs tree with leader = NONE

#if [ "$LEADER" = "NOT_DEFINED" ] 
#then
#  ci -t/dev/null $1
#  rcs -c"NONE" $1,v
#fi

