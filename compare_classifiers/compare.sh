#!/bin/bash
# 
# 
# (In case) for permition <sudo chmod -R 777 /dir/to/here>
# ******************************************************************************
#  bashfile (compare.sh): call makefile to compare classifiers

#  Author : Hitham Jleed
#  Univeristy of Ottawa  
#  © Copyright <2017>
# *******************************************************************************

echo "time and date are:"
date +%Y/%m/%d_%H:%M:%S


PS3='recompile makefile? [1 or 2] :'
options=("Yes" "No")
select opt in "${options[@]}"
do
  case $opt in
        "Yes")
	   make 
           make clean
           echo "--------building is done ----"
	    break
            ;;
        "No")
           echo "-- run the program"
	    break
            ;;
        *) echo "invalid option";;
  esac
done
echo "*********************"



feat=Features.grt
featdir=./makefeatures/src
Funcfeat='feat'

if [ -f "$feat" ]
then
	echo "features have been extracted in $feat"
else
        echo "first: extract features"
        time $featdir/$Funcfeat  ../../audio
fi


options=("GMM" "SVM" "KNN" "MinDist" "RandomForests" "AdaBoost" "BAG" "Softmax")
select opt in "${options[@]}"
do
    case $opt in
        "GMM")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose GMM"

            echo "run: GMM classifier"
            time ./GMM/GMM Features.grt
	    break
            ;;
        "SVM")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose SVM"

            echo "run: SVM classifier"
            time ./SVM/svm Features.grt
	    break
            ;;
        "KNN")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose KNN"

            echo "run: KNN classifier"
            time ./KNN/KNN Features.grt
	    break
            ;;
        "MinDist")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose MinDist"

            echo "run: MinDist classifier"
            time ./MinDist/MinDist Features.grt
	    break
            ;;
        "RandomForests")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose RandomForests"

            echo "run: RandomForests classifier"
            time ./RandomForests/RandomForests Features.grt
	    break
            ;;
        "AdaBoost")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose AdaBoost"

            echo "run: AdaBoost classifier"
            time ./AdaBoost/AdaBoost Features.grt
	    break
            ;;
        "BAG")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose BAG"

            echo "run: BAG classifier"
            time ./BAG/BAG Features.grt
	    break
            ;;
        "Softmax")
	    echo "time and date are:"
	    date +%Y/%m/%d_%H:%M:%S
            echo "-----you chose Softmax"

            echo "run: Softmax classifier"
            time ./Softmax/Softmax Features.grt
	    break
            ;;
        *) echo invalid option;;
    esac
done
