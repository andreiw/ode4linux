Summary: The OSF Development Environment
Name: ode
Version: 2.3.4
Release: 5f
Group: Development/Tools
Vendor: MkLinux.org
# I don't know if this is officially distributed anywhere.
Source: ode4linux.tar.gz
Patch0: ode-geoffk.patch
Patch1: ode-sbinfo.patch
Patch2: ode-fwb.patch
Patch3: ode-ppcbootstrap.patch
Patch4: ode-setup.patch
Copyright: Redistributable
BuildRoot: /tmp/ode-root
Prefix: /opt/ode
ExclusiveArch: ppc i386

%description
This is part of the build environment the Open Software Foundation
uses to build their kernels.  It is used by Apple to build the MkLinux
Mach kernel.

%package scontrol
Summary: The OSF Development Environment source control tools
Prefix: /opt/ode
Requires: ode rcs
Group: Development/Tools

%description scontrol
This is the source control part of the Open Software Foundation's
development environment.  You probably only need this if you are working
with OSF.

%package psdocs
Summary: The OSF Development Environment Documentation
Prefix: /opt/ode
Group: Documentation

%description psdocs
The ODE psdocs package contains postscript versions of the
OSF Development Environment System Administrator's Guide, the
ODE User's Guide and printable postscript versions of the man
pages.  You will only need this if you are interested in using
or customizing ODE for your your own projects or if you simply
want to learn how ODE works.

%changelog

* Mon May 03 1999 Fred Bacon <bacon@aerodyne.com>
- Since the System Administration Guide recommends building
  your sandbox with pieces from the ode sandbox, I've added
  the various configuration files.

* Sun May 02 1999 Fred Bacon <bacon@aerodyne.com>
- I believe that I finally have things setup so that ODE can be
  bootstrapped onto a system which doesn't have a pre-existing
  copy of ODE.

* Sat May 01 1999 Fred Bacon <bacon@aerodyne.com>
- Added a new package to distribute the ODE System Administrators'
  Guide, the ODE User's Guide and the man pages in postscript format.
- Added the README files to the list of documentation
  
* Sun Jan 24 1999 Fred Bacon <bacon@aerodyne.com>
- Moved installation from /usr/bin/lib to /opt/ode
- Fixed a number of build problems (mult. definitions of strndup, etc.)

* Sat Jan 09 1999 Geoff Keating <geoffk@ozemail.com.au>
- New package.

%prep
%setup -q -n ode4linux
%patch0 -p1 -b .patch0
%patch1 -p1 -b .patch1
%patch2 -p1 -b .patch2
#  This patch is needed to bootstrap on a powerpc linux box
%ifarch ppc
%patch3 -p1 -b .patch3
%endif
#  I've added workon to the list of tools which are
#  built during the bootstrap stage.
%patch4 -p1 -b .patch4

cat > sandboxrc <<EOF
default ode4linux
base * $RPM_BUILD_DIR
sb ode4linux
EOF
cat > rc_files/ode/sb.conf <<EOF
replace ode_sc  true
replace ode_build_env   true
EOF

%build
#
# Set the proper context and bootstrap the environment.
#
%ifarch ppc
context=ppc_linux
%else
context=at386_linux
%endif
cd src
export context=${context}
export OS=linux
echo $context
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
mkdir logs/${context} 
ln -s ${RPM_BUILD_DIR}/ode4linux/src/ode/bin/make/LINUXARCH/arch_fmtdep.c src/ode/bin/make/arch_fmtdep.c
export PATH="${RPM_BUILD_DIR}/ode4linux/tools/${context}/bin:$PATH" 
export context=${context}
export OS=linux
workon -sb ode4linux -rc `pwd`/sandboxrc <<EOF
set -x
build -here MAKEFILE_PASS=FIRST && \
build -here MAKEFILE_PASS=SECOND CC_OPT_LEVEL=-O2 && \
build MAKEFILE_PASS=BASIC ode/lib/oxm_relay_tcp CC_OPT_LEVEL=-O2 && \
build -here MAKEFILE_PASS=BASIC CC_OPT_LEVEL=-O2 ode/bin ode/server && \
build -here MAKEFILE_PASS=BASIC ode/man ode/doc
EOF

%install
%ifarch ppc
context=ppc_linux
%else
context=at386_linux
%endif

rm -rf $RPM_BUILD_ROOT
mkdir $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/opt/ode/{bin,server,man,lib}
mkdir -p $RPM_BUILD_ROOT/usr/bin

for i in 1 5 8 ; do 
    mkdir $RPM_BUILD_ROOT/opt/ode/man/{man,cat}$i
    cp src/ode/man/man$i/*.$i $RPM_BUILD_ROOT/opt/ode/man/man$i
done
cp obj/${context}/ode/man/man1/*.1 $RPM_BUILD_ROOT/opt/ode/man/man1
gzip -9 $RPM_BUILD_ROOT/opt/ode/man/man?/*

cd obj/${context}/ode
for i in server/* bin/* ; do
  install -s -m 755 $i/`basename $i` $RPM_BUILD_ROOT/opt/ode/$i
done
install -s -m 755 lib/oxm_relay_tcp $RPM_BUILD_ROOT/opt/ode/lib

cat > $RPM_BUILD_ROOT/usr/bin/workon <<'EOF'
#!/bin/sh
#  What this script tries to do is locate the installation
#  directory of the ode package and add the appropriate
#  paths to the ode executables and man pages.  It picks 
#  up this path from the actual ode package.  Once the
#  paths have been set, the ``real'' workon executable is
#  called.  This way, the ode packages are only in your
#  path if you are working in the ODE environment.
I="`rpm -q ode --qf '%%{INSTALLPREFIX}\n'`"
MANPATH=$I/man${MANPATH:+':'$MANPATH}
PATH=$I/bin:$PATH
export MANPATH PATH
exec $I/bin/workon $*
EOF
chmod +x $RPM_BUILD_ROOT/usr/bin/workon

mkdir -p $RPM_BUILD_ROOT/opt/ode/doc/{sag,users.gd/common}
find doc -name \*.ps -print | xargs -t gzip -9

/usr/bin/install -m 644 -o root -g root doc/sag/sag.ps.gz ${RPM_BUILD_ROOT}/opt/ode/doc/sag
for x in doc/users.gd/common/*.ps.gz ; 
do
  /usr/bin/install -m 644 -o root -g root $x ${RPM_BUILD_ROOT}/opt/ode/doc/users.gd/common/
done;

#
# Let's keep the configuration files around in case
# someone wants to use them.  They will be stored as examples.
#

mkdir -p $RPM_BUILD_ROOT/opt/ode/share/{ode/mk,rc_files/ode} 
cd ../../../
/usr/bin/install -m 644 sandboxrc $RPM_BUILD_ROOT/opt/ode/share/

cd rc_files
for x in projects sets;
do
   /usr/bin/install -m 644 $x $RPM_BUILD_ROOT/opt/ode/share/rc_files;
done;

for x in ode/sb.conf ode/sc.conf;
do
   /usr/bin/install -m 644 $x $RPM_BUILD_ROOT/opt/ode/share/rc_files/ode;
done;

cd ../src
/usr/bin/install -m 644 Makeconf $RPM_BUILD_ROOT/opt/ode/share/
/usr/bin/install -m 644 Makefile $RPM_BUILD_ROOT/opt/ode/share/

cd ode
/usr/bin/install -m 644 Buildconf $RPM_BUILD_ROOT/opt/ode/share/ode
/usr/bin/install -m 644 Buildconf.exp $RPM_BUILD_ROOT/opt/ode/share/ode

cd mk
for x in osf.depend.mk \
         osf.doc.mk \
         osf.lib.mk \
         osf.lib.mk \
         osf.man.mk \
         osf.obj.mk \
         osf.prog.mk \
         osf.rules.mk \
         osf.script.mk \
         osf.std.mk \
         osf.ode.mk \
         osf.ode.passes.mk \
         sys.mk;
do
  /usr/bin/install -m 644 $x $RPM_BUILD_ROOT/opt/ode/share/ode/mk;
done;

#
# That should be everything that people would 
# want to have from this distribution.
#

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc src/README src/README.bin src/README.doc src/README.src src/README.top   
%dir /opt/ode
%dir /opt/ode/bin
%dir /opt/ode/man
%dir /opt/ode/man/man1
%dir /opt/ode/man/cat1
/opt/ode/bin/build
/opt/ode/bin/currentsb
/opt/ode/bin/genpath
/opt/ode/bin/make
/opt/ode/bin/makepath
/opt/ode/bin/md
/opt/ode/bin/mklinks
/opt/ode/bin/mksb
/opt/ode/bin/sbinfo
/opt/ode/bin/workon
/opt/ode/man/man1/build.1.gz
/opt/ode/man/man1/currentsb.1.gz
/opt/ode/man/man1/genpath.1.gz
/opt/ode/man/man1/make.1.gz
/opt/ode/man/man1/mklinks.1.gz
/opt/ode/man/man1/mksb.1.gz
/opt/ode/man/man1/sbinfo.1.gz
/opt/ode/man/man1/workon.1.gz
/opt/ode/man/man5
/opt/ode/share
%dir /opt/ode/man/cat5
/usr/bin/workon

%files scontrol
%defattr(-,root,root)
/opt/ode/bin/bci
/opt/ode/bin/bco
/opt/ode/bin/bcreate
/opt/ode/bin/bcs
/opt/ode/bin/bdiff
/opt/ode/bin/blog
/opt/ode/bin/bmerge
/opt/ode/bin/bstat
/opt/ode/bin/bsubmit
/opt/ode/bin/odexm_cli
/opt/ode/bin/release
/opt/ode/bin/resb
/opt/ode/bin/sadmin
/opt/ode/bin/sup
/opt/ode/bin/upgrade
/opt/ode/bin/uptodate
/opt/ode/man/man1/bci.1.gz
/opt/ode/man/man1/bco.1.gz
/opt/ode/man/man1/bcreate.1.gz
/opt/ode/man/man1/bcs.1.gz
/opt/ode/man/man1/bcsfileoptions.1.gz
/opt/ode/man/man1/bcsoptions.1.gz
/opt/ode/man/man1/bdelta.1.gz
/opt/ode/man/man1/bdiff.1.gz
/opt/ode/man/man1/blog.1.gz
/opt/ode/man/man1/bmerge.1.gz
/opt/ode/man/man1/bstat.1.gz
/opt/ode/man/man1/bsubmit.1.gz
/opt/ode/man/man1/no_ch_file_opts.1.gz
/opt/ode/man/man1/no_sv_file_opts.1.gz
/opt/ode/man/man1/release.1.gz
/opt/ode/man/man1/resb.1.gz
/opt/ode/man/man1/sadmin.1.gz
/opt/ode/man/man1/sup.1.gz
/opt/ode/man/man1/uptodate.1.gz
/opt/ode/lib
/opt/ode/man/man8
%dir /opt/ode/man/cat8
/opt/ode/server

%files psdocs
%defattr(-,root,root)
/opt/ode/doc/
