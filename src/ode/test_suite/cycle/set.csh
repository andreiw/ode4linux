#
# @OSF_FREE_COPYRIGHT@
#
# HISTORY
# $Log: set.csh,v $
# Revision 1.2.5.1  1993/06/08  18:51:09  damon
# 	CR 578. Updated for ODE 2.3
# 	[1993/06/08  18:51:02  damon]
#
# Revision 1.2.3.6  1993/01/07  19:28:32  marty
# 	Correct syntax error for hp700_hpux.
# 	[1993/01/07  19:28:15  marty]
# 
# Revision 1.2.3.5  1993/01/05  20:36:52  marty
# 	Cleaned the script up a bit.  It now allows for context names.
# 	Also the last few commands were reworked.
# 	[1993/01/05  20:36:31  marty]
# 
# Revision 1.2.3.4  1992/12/17  20:39:58  marty
# 	Add context if backing tree is test1 and test2.
# 	[1992/12/17  20:39:39  marty]
# 
# Revision 1.2.3.3  1992/12/16  14:15:05  damon
# 	CR 241. Updated for 2.2
# 	[1992/12/16  14:13:02  damon]
# 
# Revision 1.2.3.2  1992/06/08  15:18:00  robert
# 	Break up compound switches in if statements,
# 	shorten variable names, and otherwise add support
# 	for machine types "sparc" and "hp700". Add project
# 	ode to list of backing trees as the only project
# 	that allows context naming (this should change
# 	later on).
# 	[1992/06/08  15:04:42  robert]
# 
# 	clean up status checks/returns
# 	[1992/05/28  17:47:33  robert]
# 
# 	Added multiple files (1-99) for args to b-cmds as
# 	well as use of -all. Revised backing trees, and
# 	removed addition of RCS header info since bcreate
# 	does now.
# 	[1992/04/07  16:17:06  robert]
# 
# Revision 1.2  1991/12/05  21:19:03  devrcs
# 	2nd rev of test cycle - superedes anything under .../test
# 	? MAKESYSFILEPATH needs a fix for build to work on rios with
# 	reno make - these fixes may have been submitted to dce since this
# 	script, set.csh, was last tested.
# 	[91/08/09  15:11:37  robert]
# 
# $EndLog$

echo ""
echo "CHECKING BASIC ENVIRONMENT"
echo ""

# if $HOME not defined for mksb, get pathname - check that can write there;

if (!("$?HOME") || ("$HOME" == "")) then 
	echo -n '$HOME undefined - enter pathname: '
	set query = $<
	if (!((-w "${query}") && (-e "${query}") && (-d "${query}")) || \
	   ("${query}" == "")) then
		echo "Rerun and check/set path to ${query} directory"
		exit 1
	endif
	setenv HOME ${query}
else
	if (!((-w "${HOME}") && (-e "${HOME}") && (-d "${HOME}"))) then
		echo "check write/execute privileges on HOME directory = $HOME"
		exit 1
	endif
endif

# check for existing sandboxrc, if exists query for delete & do

if (-e "${HOME}"/.sandboxrc) then
	echo -n "${HOME}/.sandboxrc already exixts. OK to delete ? <y,n> [y] " 
	set query = $< 
	if ( "${query}" !~ [nN] && "${query}" !~ [nN][oO]) then
		rm ${HOME}/.sandboxrc
		if (${status} != 0) then
			echo "Couldn't delete existing .sandboxrc"
			exit 1
		endif
	else
		echo "Please rename or save ${HOME}/.sandboxrc and rerun"
		exit 1
	endif
endif


echo -n "Check for required & optional commands? (y,n) [y]: "
set query = $<
if (!("$query" =~ [nN] || "$query" =~ [nN][oO])) then

	# check cmds are available through path
	# mksb, workon, bcreate, bstat, bci, bcs, make cc 

	set cmds_status = 0
	set cmds_list = (mksb workon bcreate bstat build make cc bci bcs bsubmit)
	foreach cmd (${cmds_list})
		set which_output = "" 
		set which_output = `which ${cmd} | grep "^\/"`
		if ("${which_output}" == "") then
			echo "${cmd} not found"
			set cmds_status = 1
		else
			echo -n "${cmd} found: "
			which ${cmd} 
		endif
	end
	
	if (${cmds_status} != 0) then
		echo ""
		echo "Your current path = ${PATH}"
		echo ""
		echo "Modify path to get missing command(s) and rerun"
		exit 1 
	endif
endif

echo ""
echo "CHECKING FOR ARGUMENTS"
echo ""

# arg 1), lower case machine type

set lctype  = ("at386_osf1" "pmax_osf1" "pmax_ultrix" "rios_aix" "sparc_sunos" "hp700_hpux")
set lc_target_mach = ""
set arg = "$1"

while ("${lc_target_mach}" == "")
	if ("${arg}" == "") then 
		echo "Enter context name (e.g. at386_osf1):"
		echo -n "(${lctype[1]} ${lctype[2]} ${lctype[3]} ${lctype[4]} ${lctype[5]} ${lctype[6]}) [${lctype[1]}] ? "
		set arg = $<
		if ("${arg}" == "") set arg = ${lctype[1]} 
	endif

	set lc_target_mach = ${arg} 
end

echo "lower case machine name = ${lc_target_mach}"
echo ""

# arg 2) backing tree

set btree_mount = ("/project/osc/build/osc1.1" "/project/dce/build/junews" "/project/osc/build/osc1.0.4" "/project/ode/build/ode")
set btree_make_type = ("reno" "reno" "cmu" "reno")
set backtree = ""
set maketype = ""
set arg = "$2"

while ("${backtree}" == "")
	if ("$arg" != "") then
		set backtree = ${arg}
	else
		# arg may/may not be one of our predefined builds when we
		# go to the switch. If arg #2  is not one of the hardcoded
		# build choices, the switch will fail to set
		# maketype which means that if argument (#3) was not
		# provided  - we must query for it.

		if ("${backtree}" == "") then
			echo "Enter a pathname to a backing tree, or enter the number (1 2 3 4)"
			echo "to select the pathname of a backing tree listed below:"
			echo ""
			echo " 1: backing tree: ${btree_mount[1]}	make type: ${btree_make_type[1]}"
			echo " 2: backing tree: ${btree_mount[2]}	make type: ${btree_make_type[2]}"
			echo " 3: backing tree: ${btree_mount[3]}	make type: ${btree_make_type[3]}"	 
			echo " 4: backing tree: ${btree_mount[4]}	make type: ${btree_make_type[4]}"
			echo ""
			echo "If you do not enter anything, the default will be the first backing tree"
			echo ""
			echo -n "Choose a backing tree for the test sandbox (explicit path or 1-4) [1]: "
			set arg = $<
			if ("${arg}" == "") set arg = 1 
		endif
	
		switch ("$arg")
		# 
			case 1:
			set backtree = "${btree_mount[1]}"
			set maketype = "${btree_make_type[1]}"
			breaksw	
		# 
			case 2:
			set backtree = "${btree_mount[2]}"
			set maketype = "${btree_make_type[2]}"
			breaksw
		# 
			case 3:
			set backtree = "${btree_mount[3]}"
			set maketype = "${btree_make_type[3]}"
			breaksw
		#
			case 4:
			set backtree = "${btree_mount[4]}"
			set maketype = "${btree_make_type[4]}"
			breaksw
		#
			default:
			set backtree = "$arg"
			set maketype = ""
		endsw
	endif
	if (!((-d "${backtree}/src") && (-e "${backtree}/src"))) then
		echo ""
		echo "Can't stat backing tree = ${backtree}"
		echo "Please check your choice's path/mount"
		echo ""
		set backtree = ""
		set arg = ""	
	endif
end

echo "backing tree = ${backtree}"

# match up current state of supported machines and backing trees 

if ((${lc_target_mach} == "sparc") || (${lc_target_mach} == "hp700")) then
	if (${backtree} != "/project/ode/build/ode") then
		echo "machine type = ${lc_target_mach} not supported for ${backtree}"
		exit 1
	endif
endif

# arg 3) make type (reno or cmu)

# define maketype if not defined above from backing tree
set arg = "$3"

while ("${maketype}" == "")
	if ("${arg}" != "") then
		set query = ${arg} 
	endif	
	if ("${arg}" == "") then
		echo ""
		echo "What style of makefiles are used by ${backtree} ?"
		echo -n "(reno, cmu) [reno]: " 
		set query = $< 
		echo ""
		if ("$query" == "") set query = "reno"
	endif

	switch ("$query")
	#
		case [rR][eE][nN][oO]:
		set maketype = "reno"
		breaksw	
	#
		case [cC][mM][uU]:
		set maketype = "cmu"
		breaksw
	#
		default:
		echo "${query} is not a known make type"
		echo "" 
		set maketype = ""
		set arg = ""
	endsw
end

echo "make type = ${maketype}"

# arg 4) test file name <filename>.c

set newfile = ""
set arg = "$4"
echo ""

while ("${newfile}" == "")
	if ("$arg" != "") then
		set newfile = ${arg} 
	else
		echo -n "Enter a C test file name [hello_${USER}.c]: "
		set query = $<
		if ("${query}" == "") then
			set newfile = "hello_${USER}.c"
		else
			set newfile = ${query}
		endif
	endif

	set file_string = ""
	set file_string = `echo "${newfile}" | grep '.c$'`
	if ("${file_string}" == "") then
		set newfile = ""
		set arg = ""
	else
		set newfile = ${file_string}
	endif
end
 
set target_file = `echo ${newfile} | sed 's;\.c$;;'`

# echo "test C file name = ${newfile}"
# echo "target file name = ${target_file}" 

set def_newfile_cnt = 0
while ("$def_newfile_cnt" == 0)
	echo -n "Select 1-99 instances of ${newfile} as file args for subsequent b-commands? [1]: "
	set query = $<
	if ("${query}" == "") then
		set newfile_cnt = 1
		set def_newfile_cnt = 1
	else
		if ("${query}" =~ [0-9][0-9] || "${query}" =~ [0-9]) then
			if ("${query}" >= 1 && "${query}" <= 99) then
				set def_newfile_cnt = 1
				set newfile_cnt = ${query}
			endif
		endif
	endif
end

set newfile_src_str = ""
set i = 1 
while ("$i" < ("$newfile_cnt" + 1))
	set newfile_src_str = "${newfile_src_str} f${i}.${newfile} "
	@ i++
end

set newfile_targ_str = `echo "${newfile_src_str}" | sed 's;\.c;;g'`

# echo "test C file name(s) = ${newfile_src_str}"
# echo "target file name(s) = ${newfile_targ_str}"

echo ""
echo "STARTING ODE COMMAND SEQUENCE"
echo ""
# define other variables 

set DEBUG = ""		# when not null, = -debug for detailed info

# set DEBUG = "-debug"

#for mksb etc...
# backtree defined above thru args/prompts
# maketype defined above thru args/prompts
# newfile (the C src test file name) defined above thru args/prompts
# lc_target_mach defined above thru args/prompts
set new_makefile = "Makefile"
set sandbox_root = `pwd` 
set sandbox_name = "test_suite"
set tools_pop_method = "b"
set obj_pop_method = "b"
set src_pop_method = "b"

# for workon etc...
set bcsset_name = "test_suite"
set setdir_path = "rat_test"
set setdir_name = "test_suite"

# do an extensive mksb that requires no prompting
# note that this works but mksb currently outputs a WARNING 
# for this and does not create the usual "complete"
# .sandboxrc file

# if sandbox already exists, prompt for delete & notify that
# cleanup may need to occur (for already created test files)

if ((-d "${sandbox_root}/${sandbox_name}") && (-e "${sandbox_root}/${sandbox_name}")) then
	echo "HOME = ${HOME}"
	echo -n "${sandbox_root}/${sandbox_name} already exixts. OK to delete ? <y,n> [y] " 
	set query = $< 
	if ( "${query}" !~ [nN] && "${query}" !~ [nN][oO]) then
		rm -rf "${sandbox_root}/${sandbox_name}" 
		if (${status} != 0) then
			echo "Couldn't delete existing sandbox "${sandbox_root}/${sandbox_name}""
			exit 1
		endif
	else
		echo "Please clean up and remove existing test sandbox and rerun"
		exit 1
	endif
endif

info_message:

echo ""
echo "This script sill run the following sequence of ODE commands when you" 
echo "respond with the default reply (CRLF=yes) at each prompt."
echo ""
echo " 1) mksb ${DEBUG} -back ${backtree} -set ${bcsset_name} -dir ${sandbox_root}" 
echo " 2) workon ${DEBUG} -setdir ${setdir_path} ${setdir_name}"
echo " 3) bcreate ${DEBUG} -set ${setdir_name} ${newfile_src_str}" 
echo " 4) bstat ${DEBUG} -set ${setdir_name} -V -all"
echo " 5) Creating ${newfile_cnt} test C file(s) = src/${setdir_path}/${newfile_src_str}"
echo " 6) Creating test Makefile for ${maketype} make as src/${setdir_path}/Makefile"
echo " 7) build ${DEBUG} -verbose -set ${setdir_name} -all"
echo " 8) Execute: ../../obj/${lc_target_mach}/${setdir_path}/${newfile_targ_str}"
echo " 9) bci ${DEBUG} -set ${setdir_name} -m test_suite -auto -all"
echo "10) bstat ${DEBUG} -set ${setdir_name} -V -all"
echo "11) no | bsubmit ${DEBUG} -set ${setdir_name} -defect n/a -fn "$USER" -auto -all" 
echo "14) bcs ${DEBUG} -set ${setdir_name} -n ${user}_test_suite_label:1.1.1.1 -all" 
echo "15) bcs ${DEBUG} -set ${setdir_name} -n ${user}_test_suite_label: -all" 
echo "16) bcs ${DEBUG} -set ${setdir_name} -o -all" 
echo "17) mksb -undo -auto ${sandbox_name}"
echo ""
echo "Optional args: <lower case machine name> <backing tree> <make type> <C source file name>"
echo "		e.g., ${lc_target_mach} ${backtree} ${maketype} ${newfile}"
echo ""

command_1:

echo ""
echo "********************************************************************************"
echo "mksb ${DEBUG} -back ${backtree} -set ${bcsset_name} -dir ${sandbox_root}" 
echo "-m ${lc_target_mach} -tools ${tools_pop_method} -obj ${obj_pop_method}" -src ${src_pop_method} ${sandbox_name}
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_2 

echo ""
echo "This command may leave you in a sub-shell.  If this happens, simply"
echo "type 'exit' to return back to the test script."
echo ""
mksb ${DEBUG} -back ${backtree} -set ${bcsset_name} -dir ${sandbox_root} -m ${lc_target_mach} -tools ${tools_pop_method} -obj ${obj_pop_method} / -src ${src_pop_method} / ${sandbox_name}

set mksb_status = ${status}
echo "mksb exitted with status = ${mksb_status}"
echo ""

if (${mksb_status} != 0) then
	echo "Couldn't create test sandbox ${sandbox_name}"
	exit 1
endif

# The tools, obj, and src backing tree entries can also be read from
# an existing .sandboxrc file such as
#---------------------------------------------------------------
#	# sandbox rc file created by mksb
#
#	# default sandbox
#
#	# base directories to sandboxes
#
#	# list of sandboxes
#
#	# mksb config specific
#
#mksb -tools b
#mksb -obj b /
#mksb -src b /
#--------------------------------------------------------------

# check for basic components in sandbox
# ./src/.BCSlock ./src/Makeconf 
# ./obj/${machine}
# /export/${machine}
# ./rc_files  local, local.tmpl, shared, shared.tmpl

# do workon

command_2:

echo ""
echo "********************************************************************************"
echo "workon ${DEBUG} -setdir ${setdir_path} -set ${setdir_name}"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_3 

echo ""
echo "This command may leave you in a sub-shell.  If this happens, simply"
echo "type 'exit' to return back to the test script."
echo ""
workon -setdir ${setdir_path} -set ${setdir_name}
set workon_status = ${status}

# check that workon got us ${cur_dir}/${sandbox_name}/src/ ${setdir_path}

echo "workon exitted with status = ${workon_status}"
echo ""

if (!((-d "${sandbox_name}/src/${setdir_path}") && (-d "${sandbox_name}/src/${setdir_path}"))) then
	echo "failed to make ${setdir_path} after workon"
	echo "Exitting" 
	exit 1
endif

# testing could continue even if this fails, but currently exit upon failure

if (${workon_status} != 0) then
	echo "Exitting"
	exit 1
endif

echo "cd ${sandbox_name}/src/${setdir_path}"
cd ${sandbox_name}/src/${setdir_path}

# do bcreate <new file name> with user lock

command_3:

echo ""
echo "********************************************************************************"
echo "bcreate ${DEBUG} -set ${setdir_name} ${newfile_src_str}" 
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_4

echo "bcreate ${DEBUG} -set ${setdir_name} ${newfile_src_str}"
bcreate ${DEBUG} -set ${setdir_name} ${newfile_src_str}
set bcreate_status = ${status}

echo "bcreate exitted with status = ${bcreate_status}"
echo ""

if ("${bcreate_status}" != 0) then
	echo "Couldn't bcreate ${newfile}"

	# ? remove land mark again
	# with current branch name so can delete ?
	#
	# add further code to skip appropriate steps
	# and continue (just bco a new version)
	# else - set expected_rev = 1.1.1.1 

	exit 1
endif

command_4:

echo ""
echo "********************************************************************************"
echo "bstat ${DEBUG} -set ${setdir_name} -V -all"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_5 

bstat ${DEBUG} -set ${setdir_name} -all
set bstat_status = ${status}

echo "bstat exitted with status = ${bstat_status}"
echo ""

set i = 1 
while ("$i" < ("$newfile_cnt" + 1))
	echo "stat on file #${i} = f${i}.${newfile}"
	set filestat = `bstat ${DEBUG} -set ${setdir_name} -V f${i}.${newfile}` 
	if (("${filestat}" != "1.1.1.1") || ("${filestat}" == "")) then
		echo "bstat of f${i}.${newfile} fails for bcreate of 1.1.1.1"
		exit 1
	endif
	@ i++
end


command_5:

# echo out a test C file

echo ""
echo "********************************************************************************"
echo "Creating test C file = src/${setdir_path}/${newfile_src_str}"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_6 

set i = 1
while ("$i" < ("$newfile_cnt" + 1))
	echo "creating source file #${i} = f${i}.${newfile}"
	set srcfile = "f${i}.${newfile}"

#	bcreate now does automatically
# 	echo '/*'>> ${srcfile}
# 	echo -n ' * @' >> ${srcfile}
# 	echo -n 'OSF' >> ${srcfile}
# 	echo -n '_' >> ${srcfile}
# 	echo -n 'COPYRIGHT'>> ${srcfile}
# 	echo '@'>> ${srcfile}
# 	echo ' */'>> ${srcfile}
# 	echo '/*'>> ${srcfile}
# 	echo -n ' * H'>> ${srcfile}
# 	echo 'ISTORY'>> ${srcfile}
# 	echo -n ' * $'>> ${srcfile}
# 	echo -n 'Log'>> ${srcfile}
# 	echo ': $'>> ${srcfile}
# 	echo -n ' * $'>> ${srcfile}
# 	echo -n 'End'>> ${srcfile}
# 	echo -n 'Log'>> ${srcfile}
#	echo '$'>> ${srcfile}
#	echo ' */'>> ${srcfile}

	echo ""
	echo '#include <stdio.h>'>> ${srcfile}
	echo "">> ${srcfile}
	echo 'main()'>> ${srcfile}
	echo '{'>> ${srcfile}
	echo -n '	printf ("hello dude - from file #'>> ${srcfile}
	echo -n "${i}">> ${srcfile} 
	echo '");'>> ${srcfile}
	echo '}'>> ${srcfile}

	echo ""
	echo "Soucre file #${i}:"
	cat ${srcfile}
	echo ""
 
	@ i++
end

command_6:

# echo out a test Makefile

echo ""
echo "********************************************************************************"
echo "Creating test Makefile for ${maketype} make as src/${setdir_path}/Makefile"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_7 

echo '#' > ${new_makefile}
echo -n '# @' >> ${new_makefile}
echo -n 'OSF' >> ${new_makefile}
echo -n '_' >> ${new_makefile}
echo -n 'COPYRIGHT' >> ${new_makefile}
echo '@' >> ${new_makefile}
echo '#' >> ${new_makefile}
echo -n '# H' >> ${new_makefile}
echo 'ISTORY' >> ${new_makefile}
echo '#' >> ${new_makefile}
echo -n '# $' >> ${new_makefile}
echo -n 'Log' >> ${new_makefile}
echo ': $' >> ${new_makefile}
echo -n '# $' >> ${new_makefile}
echo -n 'End' >> ${new_makefile}
echo -n 'Log' >> ${new_makefile}
echo '$' >> ${new_makefile}
echo '#' >> ${new_makefile}
echo "" >> ${new_makefile}
echo "PROGRAMS		= ${newfile_targ_str}" >> ${new_makefile} 
echo "ILIST		= ${newfile_targ_str}" >> ${new_makefile}
echo "" >> ${new_makefile}
echo 'IDIR		= /dev/null' >> ${new_makefile}
echo ""
if ("${maketype}" == "reno") then
#	echo '.include ${MAKESYSPATH}/<${RULES_MK}>' >> ${new_makefile}
	echo '.include <${RULES_MK}>' >> ${new_makefile}
else
	echo 'include ${MAKEFILEPATH}/standard.mk' >> ${new_makefile}
	echo 'include ${MAKEFILEPATH}/programs.mk' >> ${new_makefile}
	echo 'include ${MAKEFILEPATH}/objects.mk' >> ${new_makefile}
endif

cat ${new_makefile}

command_7:

echo ""
echo "********************************************************************************"
echo "build ${DEBUG} -set ${setdir_name} -all"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_9 

build ${DEBUG} ${newfile_targ_str}
set build_status = "$status"

echo ""
echo "build exitted with status = ${build_status}"

if ("${build_status}" != 0) then
	echo ""
	echo "Build failed for src/${setdir_path}/${newfile_targ_str}"
	echo ""

	# future - track/increment error count and log

	echo "Skip execution and bsubmit of ${target_file} and  ${newfile},"
	echo -n "and continue with test cycle ? <y, n> [y] " 

	set query = $< 
	if ( "${query}" !~ [nN] && "${query}" !~ [nN][oO]) then
		goto bsubmit_end 
	else
		echo "Exitting"
		exit 1
	endif
endif

# check for each built target file in the obj tree

set i = 1
while ("$i" < ("$newfile_cnt" + 1))
	set obj_file = `echo "f${i}.${newfile}" | sed 's;\.c;;'`
	if (!(-e ../../obj/${lc_target_mach}/${setdir_path}/${obj_file})) then
		echo "Can't find expected built target:"
		echo "./../obj/${lc_target_mach}/${setdir_path}/${obj_file}"
		echo "Exitting."
		exit 1
	else
		echo ""
		echo "ls -l ../../obj/${lc_target_mach}/${setdir_path}/${obj_file}"
		ls -l ../../obj/${lc_target_mach}/${setdir_path}/${obj_file} 
		echo ""

	@ i++
end

	# try and run built targets

command_8:

	echo ""
	echo "********************************************************************************"
	echo "Execute: ../../obj/${lc_target_mach}/${setdir_path}/${newfile_targ_str}"
	echo "********************************************************************************"
	echo ""
	echo -n "Do this command/operation ? (y/n) [y]: "

	set prompt_query = $<
	if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_9 

	set i = 1
	while ("$i" < ("$newfile_cnt" + 1))
		set obj_file = `echo "f${i}.${newfile}" | sed 's;\.c;;'`
		if (!(-x ../../obj/${lc_target_mach}/${setdir_path}/${obj_file})) then
			chmod +x ../../obj/${lc_target_mach}/${setdir_path}/${obj_file}
			set chmod_status = ${status}
			if ("$chmod_status" != 0) then
				echo  "Couldn't chmod +x ../../obj/${lc_target_mach}/${setdir_path}/${obj_file}"
				echo "Exitting."
				exit 1		
			endif
		endif
	
		../../obj/${lc_target_mach}/${setdir_path}/${obj_file}
		set exec_status = ${status}
		echo ""
		echo "Exec of ../../obj/${lc_target_mach}/${setdir_path}/${obj_file}"
		echo "returns status = ${exec_status}"
		echo ""
		../../obj/${lc_target_mach}/${setdir_path}/${obj_file} >& /tmp/${obj_file}.out
		grep "hello dude - from file #" /tmp/${obj_file}.out
		rm /tmp/${obj_file}.out
		set exec_grep_status = ${status}
		if ("$exec_grep_status" != 0) then
			echo "Exitting"
			exit 1
		endif
	
		@ i++
	end
endif

command_9:

echo ""
echo "********************************************************************************"
echo "bci ${DEBUG} -set ${setdir_name} -m test_suite -auto -all"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_10 

bci ${DEBUG} -set ${setdir_name} -m test_suite -auto -all 
set bci_status = ${status}

echo "bci exitted with status = ${bci_status}"
echo ""

if (${bci_status} != 0) then
	echo "Couldn't bci ${newfile}"
	exit 1
endif

command_10:

echo ""
echo "********************************************************************************"
echo "bstat ${DEBUG} -set ${setdir_name} -V -all"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_11 

# bstat should succeed and return 1.1.1.2

set i = 1 
while ("$i" < ("$newfile_cnt" + 1))
	echo "stat on file #${i} = f${i}.${newfile}"
	set filestat = `bstat -set ${setdir_name} -V f${i}.${newfile}`
	if ("${filestat}" != "1.1.1.2") then
		echo "bstat of ${newfile} fails for bci 1.1.1.1 -> 1.1.1.2"
		exit 1
	endif
	@ i++
end

bstat ${DEBUG} -set ${setdir_name} -all 
set bstat_status = ${status}

echo "bstat exitted with status = ${bstat_status}"
echo ""

if (${bstat_status} != 0) then
	echo "Exitting"
	exit 1
endif

command_11:

# -m ${setdir_name} redundant

echo ""
echo "********************************************************************************"
echo "no | bsubmit ${DEBUG} -set ${setdir_name} -defect n/a -fn "$USER" -auto -all" 
echo "********************************************************************************"
echo ""
echo "You may want to skip bsubmit if you would like to leave no history in"
echo "the rcs tree - or are unsure of testing bsubmit's functionality." 
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_14 

if ("$?EDITOR") then 
	set editor_save = "$EDITOR"
else
	echo "EDITOR currently undefined" 
	set editor_save = "null"
endif

echo no | bsubmit -set ${setdir_name} -defect n/a -fn "$USER" -auto -all 
set bsubmit_status = "$status"

if ("$editor_save" != "null") then 
	echo ""
	echo "setenv EDITOR ${editor_save}"
	setenv EDITOR ${editor_save}
	echo ""
endif

echo "no"
echo ""
echo "bsubmit exitted with status = ${bsubmit_status}"
echo ""

if ("$bsubmit_status" != 0) then
	echo "Exitting."
	exit 1
endif

bsubmit_end:

command_14:

echo ""
echo "********************************************************************************"
echo "bcs ${DEBUG} -set ${setdir_name} -n ${user}_test_suite_label:1.1.1.1 -all" 
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_15 

bcs ${DEBUG} -set ${setdir_name} -n ${user}_test_suite_label:1.1.1.1 -all 
set bcs_status = ${status}

echo "bcs exitted with status = ${bcs_status}"
echo ""

if (${bcs_status} != 0) then
	echo "Couldn't bcs -set ${setdir_name} -n ${user}_test_suite_label:1.1.1.1 -all"
	exit 1
endif

command_15:

echo ""
echo "********************************************************************************"
echo "bcs ${DEBUG} -set ${setdir_name} -n ${user}_test_suite_label: -all" 
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_16 

bcs ${DEBUG} -set ${setdir_name} -n ${user}_test_suite_label: -all 
set bcs_status = ${status}

echo "bcs exitted with status = ${bcs_status}"
echo ""

if (${bcs_status} != 0) then
	echo "Couldn't bcs -set ${setdir_name} -n ${user}_test_suite_label: -all"
	exit 1
endif

command_16:

echo ""
echo "********************************************************************************"
echo "echo yes | bcs -set ${setdir_name} -o -all"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) goto command_17 

echo "yes" | bcs -set ${setdir_name} -o -all 
set bcs_status = ${status}

echo ""
echo "bcs exitted with status = ${bcs_status}"
echo ""

if (${bcs_status} != 0) then
	echo "Couldn't bcs -o -set ${setdir} -all"
 	exit 1
endif

command_17:

echo ""
echo "********************************************************************************"
echo "mksb -undo -auto ${sandbox_name}"
echo "********************************************************************************"
echo ""
echo -n "Do this command/operation ? (y/n) [y]: "

set prompt_query = $<
if ("$prompt_query" =~ [nN][oO] || "$prompt_query" =~ [nN]) exit 0 

mksb -undo -auto ${sandbox_name}
set mksb_status = ${status}

echo "mksb exitted with status = ${mksb_status}"
echo ""

if (${mksb_status} != 0) then
	echo "Couldn't mksb -undo ${sandbox_name}"
	exit 1
endif

# rm ${HOME}/.sandboxrc
 
exit 0
