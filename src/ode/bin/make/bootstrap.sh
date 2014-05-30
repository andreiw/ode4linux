#! /bin/sh
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
# HISTORY
# $Log: bootstrap.sh,v $
# Revision 1.3.12.5  1995/05/12  18:52:23  robert
# 	change compiler to c89 for alpha_osf1
# 	[1995/05/12  18:15:50  robert]
#
# Revision 1.3.12.4  1995/05/08  18:17:06  ezf
# 	added at386_linux context
# 	[1995/05/08  17:51:12  ezf]
# 
# Revision 1.3.12.1  1995/04/18  17:52:44  robert
# 	add -DNO_LSTAT_DECL for sparc_sunos and pmax_ultrix
# 	[1995/04/18  17:23:31  robert]
# 
# 	Fix typo after pmax_ultrix definitoins.
# 	Add ANSI C definitions for hp700_hpux,
# 	or use c89 and "-Ae" for extended ANSI.
# 	[1995/04/05  21:26:39  robert]
# 
# 	update for ultrix ULTRIX V4.4 (Rev. 69) with cc3.0
# 	[1995/04/05  17:19:19  robert]
# 
# Revision 1.3.10.2  1993/11/24  16:48:56  marty
# 	CR # 860 - Use the compiler /usr/ccs/bin/cc on sinix if it is there.
# 	[1993/11/24  16:47:22  marty]
# 
# Revision 1.3.10.1  1993/11/20  21:44:25  damon
# 	CR 800. Made changes to match Makeconf
# 	[1993/11/20  21:44:19  damon]
# 
# Revision 1.3.8.2  1993/08/20  17:22:35  damon
# 	CR 622. Changed at386_svr4 to at386_sinix
# 	[1993/08/20  17:22:23  damon]
# 
# Revision 1.3.8.1  1993/08/10  19:24:03  damon
# 	CR 610. Added CC=c89 and _ALL_SOURCE for rios_aix
# 	[1993/08/10  19:23:55  damon]
# 
# Revision 1.3.6.2  1993/04/26  20:16:58  damon
# 	CR 464. port for 386bsd
# 	[1993/04/26  20:16:48  damon]
# 
# Revision 1.3.2.9  1993/01/06  22:58:16  marty
# 	Add path to export directory for header files.
# 	[1993/01/06  22:57:51  marty]
# 
# Revision 1.3.2.8  1992/12/03  19:04:54  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:34:51  damon]
# 
# Revision 1.3.2.7  1992/09/24  19:23:15  gm
# 	CR286: Major improvements to make internals.
# 	[1992/09/24  17:53:23  gm]
# 
# Revision 1.3.2.6  1992/06/12  00:49:00  damon
# 	Synched with 2.1.1
# 	[1992/06/11  20:00:03  damon]
# 
# Revision 1.3.2.5  1992/02/18  22:08:11  damon
# 	Some hp700_hpux porting changes
# 	[1992/02/18  22:06:51  damon]
# 
# Revision 1.3.2.4  1992/01/17  17:12:30  damon
# 	Added vax_ultrix
# 	[1992/01/17  17:12:16  damon]
# 	Revision 1.3.5.2  1992/06/12  00:32:46  damon
# 	Synched with 2.1.1
# 
# Revision 1.3.4.6  1992/04/02  16:33:03  damon
# 	Yanked BUILD_DATE define
# 	[1992/04/02  16:32:27  damon]
# 
# Revision 1.3.4.5  1992/04/02  16:21:48  damon
# 	Another fix for BUILD_DATE quoting
# 	[1992/04/02  15:27:21  damon]
# 
# Revision 1.3.2.3  1991/12/31  23:18:56  damon
# 	Changed make to use new libode porting directory
# 	[1991/12/31  23:17:53  damon]
# 
# Revision 1.3.2.2  1991/12/30  21:25:03  damon
# 	port to sparc_sunos and libsb to libode transition
# 	[1991/12/20  20:12:45  damon]
# 
# Revision 1.2.1.2  1991/12/17  15:26:06  damon
# 	Ported to hp300_hpux
# 	[1991/12/17  14:31:05  damon]
# 
# Revision 1.2  1991/12/05  20:42:02  devrcs
# 	Implement context naming
# 	[91/08/28  20:43:29  mckeen]
# 
# 	CFLAGS now includes ${CENV}
# 	[91/05/15  17:18:16  ezf]
# 
# 	Changes for parallel make.
# 	[91/04/21  16:36:30  gm]
# 
# 	Changes for Reno make
# 	[91/03/22  15:42:09  mckeen]
# 
# $EndLog$


# Defines that Make cares about 
#
# MACHINE NO_SETENV NO_STRDUP NO_STRERROR NO_GETCWD NO_UTIMES NO_WAITPID
# ARCHIVE_FORMAT TARGET_LIBS


case $context in
	"pmax_osf1")	MACHINE="mips" ;
			ARCHIVE_FORMAT=OSFARCH;;
	"mmax_osf1")	MACHINE="mmax" ;
			ARCHIVE_FORMAT=OSFARCH;;
	"386bsd")	MACHINE="i386";
			ARCHIVE_FORMAT=BSDARCH;;
	"at386_osf1")	MACHINE="i386";
			ARCHIVE_FORMAT=OSFARCH;;
	"alpha_osf1")	MACHINE="alpha";
			CC=c89;
			ARCHIVE_FORMAT=BSDARCH;;
	"mac2_osf1")	MACHINE="mac2";
			ARCHIVE_FORMAT=OSFARCH;;
	"at386_linux")	MACHINE="i386";
			TARGET_FLAGS="-DNO_RANLIB"
			ARCHIVE_FORMAT=BSDARCH;
			CC=cc;;
	"pmax_ultrix")	MACHINE="mips" ;
			ARCHIVE_FORMAT=BSDARCH ;
			NO_STRDUP=NO_STRDUP ;
			NO_SETENV=NO_SETENV;
			NO_STAT=NO_STAT;
			CC=cc;
			TARGET_FLAGS="-std1 -DNO_LSTAT_DECL";;
	"vax_ultrix")	MACHINE="vax" ;
			ARCHIVE_FORMAT=BSDARCH ;
			NO_STRDUP=NO_STRDUP ;
			NO_SETENV=NO_SETENV ;;
	"rios_aix")	MACHINE="RIOS";
			ARCHIVE_FORMAT=AIXARCH;
			NO_SETENV=NO_SETENV;
			CC=c89;
			TARGET_FLAGS="-D_ALL_SOURCE";
			TARGET_LIBS=-lbsd;;
	"hp700_hpux")	MACHINE="hp700";
			ARCHIVE_FORMAT=BSDARCH;
			TARGET_LIBS=-lBSD;
			NO_SETENV=NO_SETENV;
			CC=c89;
			TARGET_FLAGS="-Ae -DNO_UTIMES";;
	"hp300_hpux")	MACHINE="hp300";
			ARCHIVE_FORMAT=BSDARCH;
			TARGET_LIBS=-lBSD;
                        NO_FFS=NO_FFS;
			NO_SETENV=NO_SETENV;
			TARGET_FLAGS=-DNO_UTIMES;;
	"sparc_sunos")	MACHINE="sparc";
			ARCHIVE_FORMAT=BSDARCH;
			NO_SETENV=NO_SETENV;
			CC=gcc;
			NO_STRERROR=NO_STRERROR;
			TARGET_FLAGS="-DNO_LSTAT_DECL";;
	"at386_sinix")	MACHINE="i386";
			ARCHIVE_FORMAT=SVR4ARCH;
			if [ -f /usr/ccs/bin/cc ]
			then
				CC=/usr/ccs/bin/cc;
			fi
			NO_SETENV=NO_SETENV;;
	"mipsmag_svr4")	MACHINE="MIPSMAG";
			ARCHIVE_FORMAT=SVR4ARCH;
			ARCH_FMTDEP_CFLAGS=-Di386;
			TARGET_FLAGS="${TARGET_FLAGS} -DINC_TYPES -DNO_UTIMES";
			NO_STRDUP=NO_STRDUP;
			NO_STRERROR=NO_STRERROR;
			NO_WAITPID=NO_WAITPID;
			NO_GETCWD=NO_GETCWD;;
esac

#                        NO_FFS=NO_FFS;


SRCPATH=${MAKETOP}${MAKESUB}
EXPORTPATH=${MAKETOP}/../export/${context}/usr/include
LIBODEPATH=${MAKETOP}/ode/lib/libode
PORTPATH=${MAKETOP}/ode/lib/libode/porting
CFLAGS="-O ${CENV} ${PROFILING_FLAGS} -I${SRCPATH} -I${SRCPATH}lst.lib -I${EXPORTPATH} ${TARGET_FLAGS}"
BUILD_DATE=`date`
MAIN_CFLAGS="-DMACHINE=\"$MACHINE\""

CC=${CC-cc}
PORTING_OFILES=
if [ -n "$NO_FFS" ]
then
    ${CC} -c ${CFLAGS} ${PORTPATH}/ffs.c
    PORTING_OFILES="${PORTING_OFILES} ffs.o"
fi
if [ -n "$NO_SETENV" ]
then
    ${CC} -c ${CFLAGS} ${PORTPATH}/environment.c
    PORTING_OFILES="${PORTING_OFILES} environment.o"
fi
if [ -n "$NO_STRDUP" ]
then
    ${CC} -c ${CFLAGS} ${PORTPATH}/strdup.c
    PORTING_OFILES="${PORTING_OFILES} strdup.o"
fi
if [ -n "$NO_STRERROR" ]
then
    ${CC} -c ${CFLAGS} ${PORTPATH}/strerror.c
    PORTING_OFILES="${PORTING_OFILES} strerror.o"
fi
if [ -n "$NO_GETCWD" ]
then
    ${CC} -c ${CFLAGS} ${PORTPATH}/getcwd.c
    PORTING_OFILES="${PORTING_OFILES} getcwd.o"
fi
if [ -n "$NO_WAITPID" ]
then
    ${CC} -c ${CFLAGS} ${PORTPATH}/waitpid.c
    PORTING_OFILES="${PORTING_OFILES} waitpid.o"
fi
cp ${LIBODEPATH}/cond.c ode_cond.c
${CC} -c ${CFLAGS} ode_cond.c
${CC} -c ${CFLAGS} ${SRCPATH}arch.c
${CC} -c ${CFLAGS} ${ARCH_FMTDEP_CFLAGS} ${SRCPATH}${ARCHIVE_FORMAT}/arch_fmtdep.c
${CC} -c ${CFLAGS} ${SRCPATH}buf.c
${CC} -c ${CFLAGS} ${SRCPATH}cond.c
${CC} -c ${CFLAGS} ${SRCPATH}dir.c
${CC} -c ${CFLAGS} ${SRCPATH}hash.c
${CC} -c ${CFLAGS} ${SRCPATH}job.c
${CC} -c ${CFLAGS} ${MAIN_CFLAGS} ${SRCPATH}main.c
${CC} -c ${CFLAGS} ${SRCPATH}make.c
${CC} -c ${CFLAGS} ${SRCPATH}parse.c
${CC} -c ${CFLAGS} ${SRCPATH}str.c
${CC} -c ${CFLAGS} ${SRCPATH}suff.c
${CC} -c ${CFLAGS} ${SRCPATH}targ.c
${CC} -c ${CFLAGS} ${SRCPATH}var.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstAlloc.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstAppend.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstClose.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstConcat.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstDeQueue.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstDestroy.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstDupl.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstFindFrom.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstForEachFrom.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstInit.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstInsert.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstIsAtEnd.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstMember.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstNext.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstOpen.c
${CC} -c ${CFLAGS} ${SRCPATH}lst.lib/lstRemove.c
${CC} -O ${PROFILING_FLAGS}\
    ode_cond.o\
    arch.o\
    arch_fmtdep.o\
    buf.o\
    cond.o\
    dir.o\
    hash.o\
    job.o\
    main.o\
    make.o\
    parse.o\
    str.o\
    suff.o\
    targ.o\
    var.o\
    lstAlloc.o\
    lstAppend.o\
    lstClose.o\
    lstConcat.o\
    lstDeQueue.o\
    lstDestroy.o\
    lstDupl.o\
    lstFindFrom.o\
    lstForEachFrom.o\
    lstInit.o\
    lstInsert.o\
    lstIsAtEnd.o\
    lstMember.o\
    lstNext.o\
    lstOpen.o\
    lstRemove.o\
    ${PORTING_OFILES}\
    ${TARGET_LIBS}\
    -o make.X
mv make.X make
