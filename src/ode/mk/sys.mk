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
# $Log: sys.mk,v $
# Revision 1.2.2.2  1992/12/03  17:26:54  damon
# 	ODE 2.2 CR 183. Added CMU notice
# 	[1992/12/03  17:11:28  damon]
#
# Revision 1.2  1991/12/05  21:18:29  devrcs
# 	System make rule from BSD Reno make
# 	[91/07/10  13:46:42  mckeen]
# 
# $EndLog$

#	@(#)sys.mk	5.9 (Berkeley) 6/29/90

unix=		We run UNIX.

.SUFFIXES: .out .a .ln .o .c .F .f .e .r .y .l .s .cl .p .h 

.LIBS:		.a

AR=		ar
ARFLAGS=	rl
RANLIB=		ranlib

.if (${MACHINE} == "hp300")
AS=		/usr/local/lib/gcc-as
.else
AS=		as
.endif

AFLAGS=

CC=		cc
CFLAGS=		-O

.if (${MACHINE} == "hp300")
CPP=		/usr/local/lib/gcc-cpp -traditional
.else
CPP=		cpp
.endif

FC=		f77
FFLAGS=		-O
EFLAGS=

LEX=		lex
LFLAGS=

LD=		ld
LDFLAGS=

LINT=		lint
LINTFLAGS=	-chapbx

MAKE=		make

PC=		pc
PFLAGS=

RC=		f77
RFLAGS=

SHELL=		sh

YACC=		yacc
YFLAGS=-d

.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC}

.p.o:
	${PC} ${PFLAGS} -c ${.IMPSRC}

.e.o .r.o .F.o .f.o:
	${FC} ${RFLAGS} ${EFLAGS} ${FFLAGS} -c ${.IMPSRC}

.s.o:
	${AS} ${AFLAGS} -o ${.TARGET} ${.IMPSRC}

.y.o:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} -c y.tab.c -o ${.TARGET}
	rm -f y.tab.c

.l.o:
	${LEX} ${LFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} -c lex.yy.c -o ${.TARGET}
	rm -f lex.yy.c

.y.c:
	${YACC} ${YFLAGS} ${.IMPSRC}
	mv y.tab.c ${.TARGET}

.l.c:
	${LEX} ${LFLAGS} ${.IMPSRC}
	mv lex.yy.c ${.TARGET}

.s.out .c.out .o.out:
	${CC} ${CFLAGS} ${.IMPSRC} ${LDLIBS} -o ${.TARGET}

.f.out .F.out .r.out .e.out:
	${FC} ${EFLAGS} ${RFLAGS} ${FFLAGS} ${.IMPSRC} \
	    ${LDLIBS} -o ${.TARGET}
	rm -f ${.PREFIX}.o

.y.out:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} y.tab.c ${LDLIBS} -ly -o ${.TARGET}
	rm -f y.tab.c

.l.out:
	${LEX} ${LFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} lex.yy.c ${LDLIBS} -ll -o ${.TARGET}
	rm -f lex.yy.c
