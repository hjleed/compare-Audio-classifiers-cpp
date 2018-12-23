# compare-Audio-classifiers:
GMM, SVM, KNN, MinDist, RandomForests, AdaBoost, BAG, and Softmax

# To use:
* Open terminal. 
   $ cd /where/you/saved
* For permision (if needed)
   $ chmod -R 777 /where/you/saved
   
# Prerequisit: Install the two libraries

(A) Boost library (http://www.boost.org/)

Boost is a set of libraries for the C++ programming language that provide support for tasks and structures such as linear algebra, pseudorandom number generation, multithreading, image processing, regular expressions, and unit testing. It contains over eighty individual libraries. (wiki)
------------------------------------------------
(B) gesture-recognition-toolkit (GRT) (http://docsforge.com/7/grt/docs/latest/)

The Gesture Recognition Toolkit (GRT) is a cross-platform, open-source, c++ machine-learning library that has been specifically designed for real-time gesture recognition.
------------------------------------------------

# Contenents:
 (compare_classifiers) folder
     This program to test different classifiers.
     contains:
         |
    1  ---makefile: makefile that run multimakefiles 
         |
    2  ---compare.sh: bash function to execute this program
         |
    3  ---(AbaBoost) folder contains:
             |
              ---AdaBoostmain.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
        |
    4  ---(BAG) folder contains:
             |
              ---mainBAG.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
         |
    5  ---(GMM) folder contains:
             |
              ---useGMM.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
         |
    6  ---(KNN) folder contains:
             |
              ---useKNN.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
         |
    7  ---(MinDist) folder contains:
             |
              ---MinDistmain.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
         |
    8  ---(RandomForest) folder contains:
             |
              ---RandomForestmain.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
         |
    9  ---(Softmax) folder contains:
             |
              ---Softmax_main.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
         |
    10  ---(SVM) folder contains:
             |
              ---SVMmain.cpp: the main function of this folder
             |
              ---makefile: makefile to execute the program.
         |
    11  ---(makefeatures) folder contains:
             |
             ---makefile: makefile to execute the program.
             |
             ---(src) folder contains
                 |
                 ---main.cpp: the main function of this folder
                 |
                 ---getfeats.cpp: call features functions
                |
                 ---features.h:  header of features' fuctions
                |
                 ---TDFuns.cpp: function computes time domain features.
                |
                 ---FDFuns.cpp: function computes Frequency domain features.
                |
                 ---MelFreqCep.cpp: function computes mel-frequency cepstrum (MFCC).
                |
                 ---fft4g.cpp: function computes FFT
