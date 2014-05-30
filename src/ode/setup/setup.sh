#!/bin/sh
#
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
# $Log: setup.sh,v $
# Revision 1.3.10.3  1995/05/12  22:32:00  robert
# 	change site definition tests for /usr/include
# 	files to use "-f" instead of "-e" for rios_aix port
# 	(these tests previously added for at386_linux port).
# 	[1995/05/12  22:30:29  robert]
#
# Revision 1.3.10.2  1995/05/08  18:17:13  ezf
# 	test for system header files and set porting variables accordingly
# 	[1995/05/08  17:45:29  ezf]
# 
# Revision 1.3.8.1  1994/05/27  15:44:10  root
# 	CR # 1118 - Build full libode for bootstrapping.
# 	[1994/05/27  15:43:50  root]
# 
# Revision 1.3.6.3  1993/05/17  18:23:47  damon
# 	CR 531. Export more includes
# 	[1993/05/17  18:22:25  damon]
# 
# Revision 1.3.6.2  1993/04/29  19:16:20  damon
# 	CR 464. Port to 386bsd from gm
# 	[1993/04/29  19:16:09  damon]
# 
# Revision 1.3.2.12  1993/01/06  22:52:18  marty
# 	Build utilities after exporting header files.
# 	[1993/01/06  22:51:51  marty]
# 
# Revision 1.3.2.11  1992/12/03  17:27:30  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:43  damon]
# 
# Revision 1.3.2.10  1992/09/24  19:03:34  gm
# 	CR282: Made more portable to non-BSD systems.
# 	[1992/09/23  18:23:38  gm]
# 
# Revision 1.3.2.9  1992/06/16  21:53:22  damon
# 	2.1.1 touch-up
# 	[1992/06/16  21:43:18  damon]
# 
# Revision 1.3.2.8  1992/06/16  13:41:34  damon
# 	Synched with 2.1.1
# 	[1992/06/16  13:37:43  damon]
# 
# Revision 1.3.2.7  1992/02/19  17:43:25  damon
# 	Uncommented build of make
# 	[1992/02/19  17:43:04  damon]
# 
# Revision 1.3.4.3  1992/04/04  19:42:18  damon
# 	Added export of versions.h
# 	[1992/04/04  19:42:05  damon]
# 
# Revision 1.3.4.2  1992/03/10  20:55:50  damon
# 	Uncommented build of make
# 	Export include files for LBE removal changes
# 	[1992/02/19  16:06:23  damon]
# 
# Revision 1.3.2.5  1992/02/18  22:04:38  damon
# 	Changes for LBE removal
# 	[1992/02/18  21:57:16  damon]
# 
# Revision 1.3.2.4  1991/12/31  22:44:05  damon
# 	Removed cyclic genpath dependency
# 	[1991/12/31  22:43:23  damon]
# 
# Revision 1.3.2.3  1991/12/31  17:11:27  damon
# 	Correction to last fix
# 	[1991/12/31  17:11:07  damon]
# 
# Revision 1.3.2.2  1991/12/30  21:28:13  damon
# 	port to sparc_sunos and libsb to libode transition
# 	[1991/12/20  20:14:49  damon]
# 
# Revision 1.3  1991/12/17  21:02:55  devrcs
# 	Ported to hp300_hpux
# 	[1991/12/17  14:32:17  damon]
# 
# Revision 1.2  1991/12/05  21:18:59  devrcs
# 	Implement context naming
# 	[91/08/28  20:44:00  mckeen]
# 
# 	Context implementation
# 	[91/06/11  13:24:18  mckeen]
# 
# 	Added context variable and NO_STRDUP variable
# 	[91/05/28  12:45:10  damon]
# 
# 	Added NO_RCS to enable conditional rcs building
# 	[91/04/03  14:47:59  damon]
# 
# 	Added INC_TYPES.
# 	[91/04/03  12:47:28  damon]
# 
# 	Added INC_AOUTHDR INC_FILEHDR
# 	[91/04/03  12:28:44  damon]
# 
# 	Changes for Reno make
# 	[91/03/22  16:37:46  mckeen]
# 
# 	merged from dce/devkit version
# 	[91/02/21  16:53:52  ezf]
# 
# 	Final fix for ${TARGET_LIBS} on genpath and makepath.
# 	[91/01/27  17:02:02  damon]
# 
# 	Yet another TARGET_LIBS fix.
# 	[91/01/27  16:24:23  damon]
# 
# 	Fix ${TARGET_LIBS} line.
# 	[91/01/27  16:06:30  damon]
# 
# 	Added ${TARGET_LIBS} to support porting.
# 	[91/01/27  15:29:37  damon]
# 
# 	Added changes to support RIOS and aix
# 	[91/01/22  13:01:16  mckeen]
# 
# 	Added conditional compile of make type based on MAKETYPE
# 	[91/01/19  14:06:27  mckeen]
# 
# 	Creations/Fixes for project ode lbe
# 	[91/01/17  16:45:53  mckeen]
# 
# $EndLog$

# This is the setup script for building the source tree from scratch
# using as little as possible from the environment already installed on
# the current machine.  The basic process is to create the "environment"
# as we go along, which requires that this script "understand" all of the
# interdependencies between components and their environment.  When porting
# the sources to a "unknown" machine, this script is the place to start
# making changes.  Good Luck!
#

#
# Make sure we are in a reasonable starting directory
#
srcdir=`pwd`
base=`expr "${srcdir}" : "\(.*\)/.*"`
if [ `basename "${srcdir}"` != "src" ]
then
    echo "Please move source tree into a \"src\" subdirectory"
    exit 1
fi

#
# Read the configuration information for this host
#
if [ $# -ne 1 ]
then
  USAGE="usage: setup.sh <context>"
  echo "ERROR: improper number of arguments"
  echo $USAGE
  exit 1
fi

context=$1

export context

#
# Setup immediate directory heirarchy
#
obj=${base}/obj
if [ -d ${obj} ]
then
    true
else
    mkdir ${obj}
fi
objdir=${obj}/${context}
if [ -d ${objdir} ]
then
    true
else
    mkdir ${objdir}
fi
log=${base}/log
if [ -d ${log} ]
then 
    true
else
    mkdir ${log}
fi
logdir=${log}/${context}
if [ -d ${logdir} ]
then
    true
else
    mkdir ${logdir}
fi
exp=${base}/export
if [ -d ${exp} ]
then
    true
else
    mkdir ${exp}
fi
expdir=${exp}/${context}
if [ -d ${expdir} ]
then
    true
else
    mkdir ${expdir}
fi
tools=${base}/tools
if [ -d ${tools} ]
then
    true
else
    mkdir ${tools}
fi
toolsdir=${tools}/${context}
if [ -d ${toolsdir} ]
then
    true
else
    mkdir ${toolsdir}
fi
bindir=${toolsdir}/bin
if [ -d ${bindir} ]
then
    true
else
    mkdir ${bindir}
fi
libdir=${toolsdir}/lib
if [ -d ${libdir} ]
then
    true
else
    mkdir ${libdir}
fi

#
# Constrain search paths
#
PATH="${bindir}:/usr/ucb:/bin:/usr/bin"
INCDIRS="-I${expdir}/usr/include"
LIBDIRS="-L${objdir}/ode/lib/libode"

export PATH INCDIRS LIBDIRS

#
# Site Definitions
#
if [ -f /usr/include/sys/statvfs.h ]
then
    true
else
    NO_STATVFS=1
    export NO_STATVFS
fi
if [ -f /usr/include/sys/vfs.h ]
then
    INC_VFS=1
    export INC_VFS
fi
TARGET_FLAGS="-D_BLD"
OWNER="bin"
GROUP="bin"

export TARGET_FLAGS OWNER GROUP

#
# Project Definitions
#
PROJECT_NAME=ODE
project_name=ode
RULES_MK=osf.rules.mk
MAKESYSPATH="${srcdir}/ode/mk"

export PROJECT_NAME project_name RULES_MK MAKESYSPATH

#
# build environment definitions
#
EXPORTBASE=${expdir}
SOURCEBASE=${srcdir}
SOURCEDIR=""
OBJECTDIR=../obj/${context}

export EXPORTBASE SOURCEBASE SOURCEDIR OBJECTDIR

#
# bootstrap make program in current environment
#
d=${objdir}/make
if [ -d ${d} ]
then
    true
else
    mkdir ${d}
fi
if [ -d ${d} ]
then
    true
else
    echo "Please create the path for ${d}"
    exit 1
fi
MAKETOP=../../../src/
MAKESUB=ode/bin/make/
export MAKETOP MAKESUB

mkdir ${expdir}/usr
mkdir ${expdir}/usr/include
mkdir ${expdir}/usr/include/ode
mkdir ${expdir}/usr/include/ode/public
(cd ode/include ; tar cf - * ) | ( cd ${expdir}/usr/include/ode ; tar xvf - )

(cd ${objdir}/make; sh -x ${MAKETOP}${MAKESUB}bootstrap.sh)
cp ${objdir}/make/make ${bindir}/make
rm -rf ${objdir}/make
MAKEOPTIONS="${MAKEOPTIONS} -r"

(cd ode/lib/libode; \
 make ${MAKEOPTIONS} LIBS= GENPATH=true _GENINC_= libode.a )

#
# create program to support object directory path searches
#
(cd ode/bin/genpath; \
 make ${MAKEOPTIONS} GENPATH=true _GENINC_= genpath)
cp ${objdir}/ode/bin/genpath/genpath ${bindir}/genpath
rm -rf ${objdir}/ode/bin/genpath

#
# program to create paths for files
#
(cd ode/bin/makepath; \
 make ${MAKEOPTIONS} makepath)
cp ${objdir}/ode/bin/makepath/makepath ${bindir}/makepath
rm -rf ${objdir}/ode/bin/makepath

#
# front end to make
#
(cd ode/bin/build; \
 make ${MAKEOPTIONS} build)
cp ${objdir}/ode/bin/build/build ${bindir}/build
rm -rf ${objdir}/ode/bin/build

#
# program to install in non-sandbox environment
#
(cd ode/bin/release; \
 make ${MAKEOPTIONS} NO_RELEASE_DATABASE= release)
cp ${objdir}/ode/bin/release/release ${bindir}/release
rm -rf ${objdir}/ode/bin/release

#
# md - make dependency post-processor
#
PORTING_CARGS=
if [ -n "$NO_DIRENT" ]
then
    PORTING_CARGS="-DNO_DIRENT"
fi
(cd ode/bin/md; \
 make ${MAKEOPTIONS} CARGS="${PORTING_CARGS}" md)
cp ${objdir}/ode/bin/md/md ${bindir}/md
rm -rf ${objdir}/ode/bin/md

rm -rf ${expdir}/usr/include/ode/*
rm -rf ${objdir}/ode/lib/libode/libode.a

exit 0
