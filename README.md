# compare-Audio-classifiers:
GMM, SVM, KNN, MinDist, RandomForests, AdaBoost, BAG, and Softmax

![alt text](https://github.com/hjleed/compare-Audio-classifiers-cpp/blob/master/gg.png)

# To use:
* Open terminal. 
   $ cd /where/you/saved
* For permision (if needed)
   $ chmod -R 777 /where/you/saved
   
# Prerequisit: Install the two libraries

(A) Boost library (http://www.boost.org/):
--------------
Boost is a set of libraries for the C++ programming language that provide support for tasks and structures such as linear algebra, pseudorandom number generation, multithreading, image processing, regular expressions, and unit testing. It contains over eighty individual libraries. (wiki)

(B) gesture-recognition-toolkit (GRT) (http://docsforge.com/7/grt/docs/latest/):
-------------------------
The Gesture Recognition Toolkit (GRT) is a cross-platform, open-source, c++ machine-learning library that has been specifically designed for real-time gesture recognition.


# Continents:
 (compare_classifiers) folder
     This program to test different classifiers.
     contains:<br>
     ------ <br>
         | <br>
    1  ---makefile: makefile that run multimakefiles <br>
         | <br>
    2  ---compare.sh: bash function to execute this program <br>
         | <br>
    3  ---(AbaBoost) folder contains:<br>
             | <br>
              ---AdaBoostmain.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
        | <br>
    4  ---(BAG) folder contains: <br>
             | <br>
              ---mainBAG.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
         | <br>
    5  ---(GMM) folder contains: <br>
             | <br>
              ---useGMM.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
         | <br>
    6  ---(KNN) folder contains: <br>
             | <br>
              ---useKNN.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
         | <br>
    7  ---(MinDist) folder contains: <br>
             | <br>
              ---MinDistmain.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
         | <br>
    8  ---(RandomForest) folder contains: <br>
             | <br>
              ---RandomForestmain.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
         | <br>
    9  ---(Softmax) folder contains: <br>
             | <br>
              ---Softmax_main.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
         | <br>
    10  ---(SVM) folder contains: <br>
             | <br>
              ---SVMmain.cpp: the main function of this folder <br>
             | <br>
              ---makefile: makefile to execute the program. <br>
         | <br>
    11  ---(makefeatures) folder contains: <br>
             | <br>
             ---makefile: makefile to execute the program. <br>
             | <br>
             ---(src) folder contains <br>
                 | <br>
                 ---main.cpp: the main function of this folder <br>
                 | <br>
                 ---getfeats.cpp: call features functions <br>
                | <br>
                 ---features.h:  header of features' fuctions <br>
                | <br>
                 ---TDFuns.cpp: function computes time domain features. <br>
                | <br>
                 ---FDFuns.cpp: function computes Frequency domain features. <br>
                | <br>
                 ---MelFreqCep.cpp: function computes mel-frequency cepstrum (MFCC). <br>
                | <br>
                 ---fft4g.cpp: function computes FFT <br>
