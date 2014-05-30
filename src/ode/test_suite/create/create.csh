#
# @OSF_FREE_COPYRIGHT@
# 
# HISTORY
# $Log: create.csh,v $
# Revision 1.1.2.1  1993/07/06  18:25:25  marty
# 	Test sciprt for bcreate.
# 	[1993/07/06  18:24:48  marty]
#
# $EndLog$
# 
#  This test suite will test the various ways to create
#  files under ODE.
#
#  

# Set up test files.
rm -rf rat_test/files
mkdir -p rat_test/files
(cd /usr/users/marty/ode2.3/src/test_suite/create ; tar cf - * ) | \
(cd rat_test/files ; tar xf - )

# Create the files with a non-standard comment leader.  (force it)
echo "-----------------------------------------------------"
echo "Create files with a non standard comment leader (% )."
echo "-----------------------------------------------------"
(cd rat_test/files ; bcreate -c '% ' -auto *)

# Specifically create files NOT copied from the backing tree.
(cd rat_test/files ; bcreate -c '% ' -auto  test.csh test.sh Makefile)

# Check the comment leaders 
echo
echo "-----------------------------------------------------"
echo "Checking that comment leaders are set to '% '."
@ cmt_check = 0
echo 'comment leader: "% "' > cmt
foreach i (rat_test/files/*)

# Get the comment leader for this file.
rm -f ${i}.cmt
blog -h ${i} | grep "comment leader" > ${i}.cmt

diff cmt ${i}.cmt
if ( ${status} != 0) then
        @ cmt_check = 1
	echo "**ERROR Invalid comment leader for file ${i}."
	cat ${i}.cmt
endif
rm -f ${i}.cmt

end
if ( ${cmt_check} != 1) then
	echo "Comment leaders set correctly."
else
	echo "Error, comment leaders not set correctly."
endif
echo "-----------------------------------------------------"
echo
rm -f cmt

# Check to see that user branches have been created for each file.
set ode_set = `currentsb -set`
echo
echo "-----------------------------------------------------"
echo "Check for user branches ${ode_set}."
foreach i (rat_test/files/*)

set rev = `bstat -r ${ode_set} ${i}`
echo "bstat returned ${rev}"

if ("${rev}" != "./${i} 1.1.1.1") then
	echo "User branch ${ode_set} was not created for ${i}."
else
	echo "bstat returned ${rev}"
endif

end
echo "-----------------------------------------------------"
echo

# Check to see that entries exist in .BCSconfig and .BCSset-???
echo
echo "-----------------------------------------------------"
echo "Check for entries in .BCSset-${ode_set} file."
@ check = 0
foreach i (rat_test/files/*)

grep -q ${i} ${SOURCEBASE}/.BCSset-${ode_set}
if ($status == 1) then
	@ check = 1
	echo "${i} is missing from the .BCSset-${ode_set} file."
endif
end


if ( ${check} == 0 ) then
	echo ".BCSset-${ode_set} updated correctly."
else
	echo "Error, .BCSset-${ode_set} not updated correctly."
endif

echo "-----------------------------------------------------"
echo

# Now get rid of them all.
ls -1  rat_test/files/* > files
echo
echo
echo
echo "-----------------------------------------------------"
echo "Removing all created files"
echo
(cd rat_test/files ; bcreate -undo *)
echo "-----------------------------------------------------"
echo

# Check to see that file is no longer under source control. 
# foreach i (`cat files`)

# blog -h ${i} >& /dev/null

# end

# Check to see that entries are removed from .BCSconfig and .BCSset-???
echo 
echo "-----------------------------------------------------"
echo "Check to see if files have been removed from .BCSset-${ode_set} file."
echo
@ check = 0
foreach i (`cat files`)
grep -q ${i} ${SOURCEBASE}/.BCSset-${ode_set}
if ($status == 0) then
	@ check = 1
	echo "${i} was not removed from the .BCSset-${ode_set} file."
endif

end

if (${check} == 0) then
	echo "Files removed from .BCSset-${ode_set} file."
else
	echo "Error - Files not removed from .BCSset-${ode_set} file."
endif
echo "-----------------------------------------------------"
