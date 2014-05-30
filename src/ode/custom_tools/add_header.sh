#!/bin/sh
#
# @OSF_FREE_COPYRIGHT@
# 
# HISTORY
# $Log: add_header.sh,v $
# Revision 1.2.2.1  1995/05/18  02:12:30  robert
# 	add to tree for free  unencumbered distrib
# 	[1995/05/18  02:06:46  robert]
#
# Revision 1.2  1991/12/05  20:55:10  devrcs
# 	This tool is just like the ode/setup/add_header.sh except that it:
# 	   - does not check in or do any other bcs/rcs thing
# 	   - accepts a second parameter that is used to tag output files
# 	     when running a couple of these processes in parallel.
# 	[1991/11/22  21:59:20  mhickey]
# 
# $EndLog$
# 

#
# add_header.sh
#
# usage: add_header.sh file_of_paths [tag]
# 
# Adds an OSF_COPYRIGHT marker, HISTORY, Log, EndLog to a variety of file 
# types.  Input is a file which contains a list of paths to files to check.
# If a second parameter is specified, it is used to tag output files.  This
# can be useful  if you are running a number of add_header.sh processes in
# parallel.
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
    echo $1 >> /usr/tmp/ASSUME_SHELL$2
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
  echo '# @OSF_COPYRIGHT@' >> files2.tmp
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
  echo ' * @OSF_COPYRIGHT@' >> files2.tmp
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
  echo '...\" @OSF_COPYRIGHT@' >> files2.tmp
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
  echo '/**/# @OSF_COPYRIGHT@' >> files2.tmp
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
  echo $1 >> /usr/tmp/FILES_NOT_FOUND$2
else
  echo $1 >> /usr/tmp/FILES_FOUND$2
fi
