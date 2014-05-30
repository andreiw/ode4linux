# @OSF_FREE_COPYRIGHT@
# HISTORY
# $Log: tool_test.sh,v $
# Revision 1.1.4.1  1993/06/10  21:59:07  damon
# 	CR 578. Updated for 2.3
# 	[1993/06/10  21:59:01  damon]
#
# Revision 1.1.2.2  1992/12/16  14:15:11  damon
# 	CR 241. Updated for 2.2
# 	[1992/12/16  14:12:36  damon]
# 
# $EndLog$
echo !/bin/sh


tbase=/tmp/$USER

sb1=${1}sb1
sb2=${1}sb2
sbase1=/tmp/$USER/$sb1/src
sbase2=/tmp/$USER/$sb2/src

defset1=${USER}_$sb1
defset2=${USER}_$sb2

tfile1=$USER/${1}1.sh
tfile2=$USER/${1}2.sh
tfile3=$USER/${1}3.sh

mkdir $tbase

echo "What backing tree do you wish to use?"
read backtree

echo 1:
echo [ Making two sandboxes ]
mksb -back $backtree -dir $tbase $sb1

defset=`sbinfo  -sb  $sb1 default_set`

if [ 0 = 1 ]
then
 :
fi

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

mksb -back $backtree -dir $tbase $sb2

trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo 2:
echo [ You should get a release of ODE 2.3 ]
bsubmit -version

trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo 3:
echo [ The first sequence of commands tests submissions involving merges. ]
echo [ A file will be created, checked in, and submitted. It will then    ]
echo [ be checked out in two sandboxes and have different changes made in ]
echo [ each sandbox. They will both be checked in. The file in the first  ]
echo [ sandbox will be submitted which will force a merge in the second   ]
echo [ sandbox.                                                           }
echo bcreate $tfile1 in $sb1
(cd $sbase1 ; bcreate -sb  $sb1 $tfile1 )
cat << EOF >> $sbase1/$tfile1
line 1
line 2
line 3
line 4
line 5
line 6
line 7
line 8
line 9
line 10
EOF

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 4:
echo bci $tfile1 in $sb1
(cd $sbase1 ; bci  -sb  $sb1 -m "First checkin from $sb1" -auto $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 5:
echo bsubmit $tfile1 in $sb1
(cd $sbase1 ; bsubmit  -sb  $sb1 -auto -auto_out -defect 0 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 6:
echo bco $tfile1 in both sandboxes
(cd $sbase1 ; bco  -sb  $sb1 $tfile1  )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

(cd $sbase2 ; bco -sb  $sb2 $tfile1  )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo [ Running ed to modify files ]
ed $sbase1/$tfile1 << EOF
/line 1
d
1,\$s:line 4:line 4 $sb1:
w
q
EOF

ed $sbase2/$tfile1 << EOF
/line 10
d
1,\$s:line 4:line 4 $sb2:
w
q
EOF

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 7:
echo bci $tfile1 in both sandboxes

(cd $sbase1 ; bci  -sb  $sb1 -auto -m "changes from $sb1" $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

(cd $sbase2 ; bci  -sb  $sb2 -auto -m "changes from $sb2" $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 8:
echo bsubmitting $tfile1 in $sb1
(cd $sbase1 ; bsubmit  -sb  $sb1 -auto -auto_out -defect 0 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo 9:
echo bsubmitting $tfile1 in $sb2
echo [ You should get 1 merge conflict. ]
echo [ You will need to resolve it. It does not matter ]
echo [ which line 4 you pick. ]
echo [ When you resolve it, you should have line 2 - line 9 ]
echo [ with only one line 4. ]
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

(cd $sbase2 ; bsubmit  -sb  $sb2 -auto -auto_out -defect 0 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo 10:
echo [ The second sequence of commands tests bmerge and bsubmit. A merge  ]
echo [ will be forced like before, but instead of doing the merge in      ]
echo [ bsubmit, the merge will be done by bmerge. This will remove the    ]
echo [ need to do a merge during bsubmit.                                 ]
echo bco $tfile1 in both sandboxes
(cd $sbase1 ; bco  -sb  $sb1 $tfile1  )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

(cd $sbase2 ; bco  -sb  $sb2 $tfile1  )
trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2


echo [ Check to make sure that the contents are ]
echo [ correct, e.g., that the submit worked. ]
echo file in $sb1
cat $tbase/$sb1/src/$tfile1
echo file in $sb2
cat $tbase/$sb2/src/$tfile1

echo Editting files to change line 6
ed $tbase/$sb1/src/$tfile1 << EOF
1,\$s:line 6:line 6 $sb1:
w
q
EOF

ed $tbase/$sb2/src/$tfile1 << EOF
1,\$s:line 6:line 6 $sb2:
w
q
EOF
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 11:
echo bci $tfile1 in both sandboxes
(cd $sbase1 ; bci  -sb  $sb1 -auto -m "more changes from $sb1" $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

(cd $sbase2 ; bci  -sb  $sb2 -auto -m "more changes from $sb2" $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 12:
echo bsubmit $tfile1 in $sb1
echo [ This should just work ]
(cd $sbase1 ; bsubmit  -sb  $sb1 -auto -auto_out -defect 0 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 13:
echo bmerge $tfile1 in $sb2
echo [ You should get 1 merge conflict overlap. ]
echo [ You will need to resolve it. It does not matter ]
echo [ which line 6 you pick. ]
echo [ When you resolve it, you should have line 2 - line 9 ]
echo [ with only one line 6. ]
(cd $sbase2 ; bmerge  -sb  $sb2 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 14:
echo bci $tfile1 in $sb2
(cd $sbase2 ; bci  -sb  $sb2 -auto -m "merge changes from $sb1 into $sb2" $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 15:
echo bsubmit $tfile1 in $sb2
(cd $sbase2 ; bsubmit  -sb  $sb2 -auto -auto_out -defect 0 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2


echo The rest of the testing is all done in $sb1:
echo
echo [ This next sequence of commands tests the error recovery of bsubmit  ]
echo [ and sadmin. Two additional files are created and bsubmit is         ]
echo [ interrupted at various points to simulate problems.                 ]
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 16:
echo bco $tfile1
echo [ Check to make sure that the contents are ]
echo [ correct, e.g., that the submit worked. ]
(cd $sbase1 ; bco  -sb  $sb1 $tfile1 )
cat $sbase1/$tfile1
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 17:
echo bcreate $tfile2
(cd $sbase1 ; bcreate  -sb  $sb1 $tfile2 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 18:
echo bcreate $tfile3
(cd $sbase1 ; bcreate  -sb  $sb1 $tfile3 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 19:
echo bci -all -auto -m "more testing in $sb1"
(cd $sbase1 ; bci -sb $sb1 -all -auto -m "more testing in $sb1")
trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo In the next step, hit Ctrl-C just after the 'Validating submission' step
echo starts.

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 20:
echo bsubmit -all
echo [ You should be told that you do not have to resubmit ]
(cd $sbase1 ; bsubmit  -sb  $sb1 -all )

trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo In the next step, hit Ctrl-C just after the 'Submitting Files' step
echo starts.

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 21:
echo bsubmit  -sb  $sb1 -all
(cd $sbase1 ; bsubmit  -sb  $sb1 -all )

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

resubtime=`(cd $sbase1; sadmin -sb $sb1 -copy hold resub.tmp; head -1 resub.tmp  | cut -f7,7 -d' ' )`

echo 22:
echo [ This step will test the ability of bsubmit to remove a partially ]
echo [ completed submission. Verify that your submission has been removed by ]
echo [ looking at the bsubmit.hold file in the ]
echo [ backing build. ]

echo bsubmit -rm $resubtime
( cd $sbase1; bsubmit -sb  $sb1 -rm $resubtime )

echo Here is the contents of bsubmit.hold:
echo ---file starts following this line---
cat $tbase/$sb1/link/logs/bsubmit.hold
echo ---file ends just before this line---

trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo In the next step, hit Ctrl-C just after the 'Submitting Files' step
echo starts. Do not worry if you hit Ctrl-C too late.
echo You should be told to resubmit.

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 23:
echo bsubmit -all
(cd $sbase1 ; bsubmit  -sb  $sb1 -all )

echo In the next step, hit Ctrl-C just after the 'Updating Log Files' step
echo starts.
echo You should be told to resubmit.

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

resubtime=`(cd $sbase1; sadmin -sb $sb1 -copy hold resub.tmp; head -1 resub.tmp  | cut -f7,7 -d' ' )`

echo 24:
echo bsubmit -resub $resubtime
(cd $sbase1 ; bsubmit  -sb  $sb1 -resub $resubtime )

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


(cd $sbase1 ; bsubmit  -sb  $sb1 -resub $resubtime -defect 0)
echo Make sure $tfile1 is completely submitted before proceeding.
trap 2 ; echo " <Return to continue>"
read foo ; clear
trap "echo Ctrl-C hit" 2

echo [ The remainder of the steps test the rest of the source control ]
echo [ commands. ]
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 28:
echo [ Note the version number for the symbolic name $defset ]
echo [ Note the highest revision ]
echo [ corresponding to this symbol. For instance, if ]
echo [ the revision is 1.1.2, and there are revisions ]
echo [ 1.1.2.1, 1.1.2.2, ..., 1.1.2.7, then 1.1.2.7 ]
echo [ is the highest. ]

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo blog $tfile1
(cd $sbase1 ; blog  -b -sb  $sb1 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 29:
echo [ The results of the following bstat should agree with what was printed ]
echo [ by blog in the previous step. E.g., it should return the highest      ]
echo [ revision corresponding to the symbolic name $defset. ]

echo bstat -r $defset $tfile1
(cd $sbase1 ; bstat -sb $sb1 -r $defset $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 30:
echo [ You should be told that there is no branch revision for $USER_$sb1 ]
echo bstat  -sb  $sb1 $tfile1
(cd $sbase1 ; bstat  -sb  $sb1 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 31:
echo bco $tfile1 in $sb1
echo [ This should just work ]
(cd $sbase1 ; bco  -sb  $sb1 $tfile1  )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 32:
echo bstat $tfile1
echo [ You should get 1.1.X.1 where X is some number. ]
(cd $sbase1 ; bstat  -sb  $sb1 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo Making a change to $tfile1 
cat << EOF >> $tbase/$sb1/src/$tfile1
Any Change
EOF

echo 33:
echo bdiff $tfile1
echo [ You should see the change you just made ]
(cd $sbase1 ; bdiff  -sb  $sb1 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 34:
echo bci -defunct $tfile1 
echo [ This should just work ]

(cd $sbase1 ; bci  -sb  $sb1 -m "Making defunct" -defunct $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 35:
echo bsubmit $tfile1
echo [ This should just work ]

(cd $sbase1 ; bsubmit  -sb  $sb1 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 36:
echo bco $tfile1
echo [ This should not work. You should get a    ]
echo [ message stating that the file is defunct. ] 

(cd $sbase1 ; bco  -sb  $sb1 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 37:
echo bco $tfile2
(cd $sbase1 ; bco  -sb  $sb1 $tfile2 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 38:
echo bsubmit $tfile1  Note: not $tfile2 
echo [ This should fail ]

(cd $sbase1 ; bsubmit  -sb  $sb1 $tfile1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 39:
echo bsubmit $tfile2
echo [ This should fail the validation step, saying ]
echo [ 'no check-ins. locked.' ]

(cd $sbase1 ; bsubmit  -sb  $sb1 $tfile2 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 40:
echo bci $tfile2
echo [ This should just work ]

(cd $sbase1 ; bci  -sb  $sb1 -m "Junk from step 40" -auto $tfile2 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo In the next step, hit Ctrl-C just after the 'Preparing for check-in(s)' step
echo starts. Do not worry if you hit Ctrl-C a little late.

trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2

echo 41:
echo bsubmit $tfile2
echo [ This should ask you to resubmit ]

(cd $sbase1 ; bsubmit  -sb  $sb1 $tfile2 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 42:
echo bsubmit $tfile2
echo [ This should tell you that the file is held by you. ]

(cd $sbase1 ; bsubmit  -sb  $sb1 $tfile2 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


resubtime=`(cd $sbase1; sadmin -sb $sb1 -copy hold resub.tmp; head -1 resub.tmp  | cut -f7,7 -d' ' )`

echo 43:
echo bsubmit -resub $resubtime
echo [ This should just work ]

(cd $sbase1 ; bsubmit  -sb  $sb1 -resub $resubtime )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 44:
echo currentsb
echo [ This should just work ]
(cd $sbase1 ; currentsb  -sb )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 45:
echo sbinfo
echo [ This should just work ]
(cd $sbase1 ; sbinfo  -sb  $sb1 )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 46:
echo mklinks .
echo [ This should just work ]

(cd $sbase1 ; mklinks  -sb  $sb1 . )
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


echo 47:
echo ls
echo [ In src/damon you should see $tfile2 and $tfile3 only ]

ls -R $tbase/$sb1/src
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2


mksb -undo $sb1
mksb -undo $sb2
trap 2 ; echo " <Return to continue>"
read foo ; echo "=============================="
trap "echo Ctrl-C hit" 2
