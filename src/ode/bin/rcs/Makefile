#
# @OSF_FREE_COPYRIGHT@
#
# HISTORY
# $Log: Makefile,v $
# Revision 1.3.6.1  1995/05/18  19:33:32  robert
# 	Change rcs_5.5/src ro rcs_5.6/src.
# 	Change rcs_5.5_patches to (generic) rcs_patches
# 	[1995/05/18  19:17:41  robert]
#
# Revision 1.3.4.5  1992/11/12  15:07:09  damon
# 	CR 329. Cleaned up building of rcs. Added INCDIRS
# 	[1992/11/12  15:06:42  damon]
# 
# Revision 1.3.4.4  1992/06/16  22:34:04  damon
# 	more 2.1.1 touch-up
# 	[1992/06/16  22:29:57  damon]
# 
# Revision 1.3.3.4  1992/04/15  13:43:44  damon
# 	Fixed bogus dependencies on rcsbase.h
# 	[1992/04/15  13:43:26  damon]
# 
# Revision 1.3.3.3  1992/04/02  14:30:39  damon
# 	Changed rcsbase.h to match change to str2expmode
# 	[1992/04/02  14:27:39  damon]
# 
# Revision 1.3.3.2  1992/03/23  20:45:27  damon
# 	Conditionally builds just rcsdiff3 or all based on NO_RCS
# 	[1992/03/23  20:44:36  damon]
# 
# 	Conditionally builds just rcsdiff3 or all based on NO_RCS
# 	[1992/03/23  20:38:39  damon]
# 
# Revision 1.3  1991/12/17  20:59:16  devrcs
# 	reordered programs to avoid install problems
# 	[1991/12/17  19:21:24  mckeen]
# 
# Revision 1.2  1991/12/05  20:46:11  devrcs
# 	Fixed flags to diff for GNU-diff
# 	[91/10/27  10:06:25  mckeen]
# 
# 	Changed OS_TYPE and CPU_TYPE to TARGET_os and TARGET_CPU
# 	[91/10/15  10:31:23  mckeen]
# 
# 	Fixed build problems on OSF/1 systems
# 	[91/10/08  10:59:49  mckeen]
# 
# 	Initail makefile for rcs 5.5
# 	[91/09/19  15:18:00  mckeen]
# 
# $EndLog$


VPATH		= ${TARGET_OS}:rcs_patches:rcs_5.6/src

IDIR		= /lib/
rcsdiff3_IDIR	= /bin/
ILIST		= ${PROGRAMS}
INCFLAGS	= -Ircs_patches -I. -I${TARGET_OS}
INCDIRS		= -Ircs_patches
rcsstat.o_INCFLAGS	= ${INCFLAGS} -Ircs_5.6/src
rcslex.o_INCFLAGS       = ${INCFLAGS} -Ircs_5.6/src
rcssyn.o_INCFLAGS       = ${INCFLAGS} -Ircs_5.6/src
# CENV = -g

SUBDIRS		= diff

RCSPREFIX	=
DIFF		= diff
DIFF_FLAGS	= -an
DIFF_L		= 1
DIFF3		= diff3
DIFF3_TYPE	= lib
SENDMAIL	= "/bin/mail"   # Yes, the quotes should be there...
COMPAT2 	= 0

BCOMMANDS	= ci ident rcs rcsdiff rlog co rcsmerge

RCSCOMMANDS	= ci co rcs rcsdiff rlog

PROGRAMS	= rcsdiff3 rcsstat branch_ci ${NO_RCS:D:U${RCSCOMMANDS}}
OTHERS		= conf.h

RCS_OFILES = partime.o rcsfcmp.o rcslex.o rcssyn.o \
	     ci.o rcs.o rcsfnms.o rcsmap.o rcsutil.o \
	     co.o rcsdiff.o rcsgen.o rlog.o \
	     ident.o rcskeep.o rcsrev.o \
	     maketime.o rcsedit.o rcskeys.o rcsstat.o 

${RCS_OFILES} rcsbase.h : conf.h

ci_OFILES = ci.o rcslex.o rcssyn.o rcsgen.o rcsedit.o rcskeys.o rcsmap.o \
	    rcsrev.o rcsutil.o rcsfnms.o partime.o maketime.o rcskeep.o \
	    rcsfcmp.o

co_OFILES = co.o rcslex.o rcssyn.o rcsgen.o rcsedit.o rcskeys.o rcsmap.o \
            rcsrev.o rcsutil.o rcsfnms.o partime.o maketime.o

ident_OFILES = ident.o rcsmap.o

rlog_OFILES = rlog.o rcslex.o rcsmap.o rcssyn.o rcsrev.o rcsutil.o partime.o \
              maketime.o rcsfnms.o

rcs_OFILES = rcs.o rcslex.o rcssyn.o rcsrev.o rcsutil.o rcsgen.o rcsedit.o \
	     rcskeys.o rcsmap.o rcsfnms.o

rcsdiff_OFILES = rcsdiff.o rcsutil.o rcsfnms.o rcsmap.o rcsrev.o rcssyn.o \
	          rcslex.o maketime.o partime.o

rcsstat_OFILES = rcsstat.o maketime.o partime.o rcslex.o rcssyn.o rcsrev.o \
		 rcsutil.o rcsgen.o rcsedit.o rcskeys.o rcsmap.o rcsfnms.o

.include <${RULES_MK}>

.if !exists(${TARGET_OS}/conf.h)
conf.h : conf.sh # Makefile
	C='${_CC_} ${CFLAGS} ${CENV}' \
	COMPAT2='${COMPAT2}' \
	DIFF='${DIFF}' \
	DIFF_L='${DIFF_L}' \
	DIFF_FLAGS='${DIFF_FLAGS}' \
	RCSPREFIX='${RCSPREFIX}' \
	SENDMAIL='${SENDMAIL}' \
	L='${LDLIBS}' \
	sh -x ${conf.sh:P} 2>conf.error
	mv a.h ${.TARGET}
	rm -f a.*
.endif
