#!/bin/bash
# 
# 
# (In case) for permition <sudo chmod -R 777 /dir/to/here>
#/*******************************************************************************
#  bashfile (execute.sh): call makefile to test classification algorithm

#  Author : Hitham Jleed
#  Univeristy of Ottawa 
#  © Copyright <2017>
#*******************************************************************************/

#Adding shared library
codedir=`pwd`
parentdir="$(dirname "$codedir")"
export LD_LIBRARY_PATH=$parentdir/toolkits/lib:$LD_LIBRARY_PATH

# Call makefile to build FuncName if it isn't exist
FuncName='svm'

if [ -f "$FuncName" ]
then
	echo "-- run $FuncName"
else
	make -f make.mk
        make -f make.mk clean
        echo "--------building is done ----"
        echo "-- run $FuncName"
fi

time ./$FuncName  $parentdir/myFeatures.grt
