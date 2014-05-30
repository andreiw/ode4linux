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
# $Log: install.sh,v $
# Revision 1.3.2.2  1992/12/03  17:27:25  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:40  damon]
#
# Revision 1.3  1991/12/17  21:01:49  devrcs
# 	Added -k to makeoptions so everything gets installed
# 	[1991/12/17  18:43:42  mckeen]
# 
# Revision 1.2  1991/12/05  21:18:50  devrcs
# 	Fixed changes for context naming scheme
# 	[91/09/19  15:21:33  mckeen]
# 
# 	Implement context naming
# 	[91/08/28  20:43:49  mckeen]
# 
# 	Changes for Reno make
# 	[91/03/22  16:37:34  mckeen]
# 
# 	Added support for context variable
# 	[91/03/11  08:39:38  mckeen]
# 
# 	merged from dce/devkit version
# 	[91/02/21  16:40:04  ezf]
# 
# 	Fixed stupid misspelling of MAKETYPE
# 	[91/01/22  14:01:23  mckeen]
# 
# 	Added changes to support RIOS and aix
# 	[91/01/22  13:01:11  mckeen]
# 
# 	Creations/Fixes for project ode lbe
# 	[91/01/17  16:44:53  mckeen]
# 
# $EndLog$

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
if [ $# -lt 1 ] 
then 
  USAGE="usage: install.sh <context> [install_top]"
  echo "ERROR: improper number of arguments"
  echo $USAGE
  exit 1
fi

context=$1

export context

#
# Setup immediate directory heirarchy
#

srcdir=`pwd`
base=`expr "${srcdir}" : "\(.*\)/.*"`
if [ `basename "${srcdir}"` != "src" ]
then
    echo "Please move source tree into a \"src\" subdirectory"
    exit 1
fi

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

bindir=${base}/tools/${context}/bin
if [ -d ${bindir} ]
then
    true
else
   echo "Must have a tools/${context}/bin directory"
   exit 1
fi

#
# Constrain search paths
#
PATH="${bindir}:/usr/ucb:/bin:/usr/bin"

export PATH

#
# Site/Environment stuff
#
OWNER="bin"
GROUP="bin"

export OWNER GROUP

#
# Project Definitions
#
PROJECT_NAME=ODE
project_name=ode
RULES_MK=osf.rules.mk
MAKESYSPATH="${srcdir}/ode/mk"

export PROJECT_NAME project_name RULES_MK MAKESYSPATH
#
# New build environment definitions
#
EXPORTBASE=${expdir}
SOURCEBASE=${srcdir}
SOURCEDIR=""
OBJECTDIR=../obj/${context}

export EXPORTBASE SOURCEBASE SOURCEDIR OBJECTDIR

#
# install targets
#
if [ "x$2" = "x" ]
then
    echo "Not install destination given.  /usr/ode assumed"
    TOSTAGE=/usr/ode
else
    TOSTAGE=$2
fi

export TOSTAGE

MAKEOPTIONS="-rik"

(cd ode; make ${MAKEOPTIONS} install_all)

exit 0


