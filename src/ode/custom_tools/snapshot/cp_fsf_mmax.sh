# @OSF_FREE_COPYRIGHT@
# COPYRIGHT NOTICE
# (c) Copyright 1992, 1991, 1990 OPEN SOFTWARE FOUNDATION, INC. 
# ALL RIGHTS RESERVED 
# HISTORY
# $Log: cp_fsf_mmax.sh,v $
# Revision 1.1.2.3  1992/12/03  19:08:55  damon
# 	ODE 2.2 CR 346. Expanded copyright
# 	[1992/12/03  18:40:30  damon]
#
# Revision 1.1.2.2  1992/02/23  21:23:05  damon
# 	Initial Version
# 	[1992/02/23  21:21:18  damon]
# 
# $EndLog$
(cd $1/gcc; tar cf - cc1 cpp gcc gcc-COPYING ) | (cd gcc;tar xvpf - )
(cd $1/gcc; tar cf - gcc-ChangeLog gcc-README.OSF gcc-as gcc-cc1 ) | (cd gcc; tar xvpf - )
(cd $1/gcc; tar cf - gcc-cpp gcc-gnulib gcc-ld gnulib ) | ( cd gcc; tar xvpf -)
(cd $1/macho; tar cf - ar as cc1 cpp gas gcc) | ( cd macho; tar xvpf -)
(cd $1/macho; tar cf - gcc-COPYING gcc-ChangeLog ) | ( cd macho; tar xvpf -)
(cd $1/macho; tar cf - gcc-README.OSF gcc-as gcc-cc1 gcc-cpp ) | ( cd macho; tar xvpf -)
(cd $1/macho; tar cf - gcc-gnulib gcc-ld gld gnulib ld nm ranlib)|(cd macho;tar xvpf -)
