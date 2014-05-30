#!/bin/bash

arch=`uname -m`
case "$arch" in
    i?86) context=at386_linux ;;
    x86_64) context=at386_linux ;;
    ppc) context=ppc_linux ;;
esac

cat > sandboxrc <<EOF
default ode4linux
base * ${PWD}/..
sb ode4linux
EOF
cat > rc_files/ode/sb.conf <<EOF
replace ode_sc  true
replace ode_build_env   true
EOF

cd src
export context=${context}
export OS=linux
sh +x ode/setup/setup.sh ${context}

# 
# Now we can actually begin to build ODE
# There seems to be something missing in the bootstrap 
# sequence.  It is necessary to link directly to the 
# LINUXARCH/arch_fmtdeps.c file.  We aren't finding it
# on our own the way we would if the full ODE build
# environment were available.
#
cd ..
mkdir -p logs/${context} 
rm -f src/ode/bin/make/arch_fmtdep.c
ln -s ${PWD}/src/ode/bin/make/LINUXARCH/arch_fmtdep.c src/ode/bin/make/arch_fmtdep.c
export PATH="${PWD}/tools/${context}/bin:$PATH" 
export context=${context}
export OS=linux
echo $PATH
workon -sb ode4linux -rc `pwd`/sandboxrc <<EOF
set -x
build -here MAKEFILE_PASS=FIRST && \
build -here MAKEFILE_PASS=SECOND CC_OPT_LEVEL=-O2 && \
build MAKEFILE_PASS=BASIC ode/lib/oxm_relay_tcp CC_OPT_LEVEL=-O2 && \
build -here MAKEFILE_PASS=BASIC CC_OPT_LEVEL=-O2 ode/bin ode/server && \
build -here MAKEFILE_PASS=BASIC ode/man ode/doc
EOF
