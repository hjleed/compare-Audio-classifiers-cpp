/*
 
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT> <MIT License>
 Edited (c) <2017> <Hitham Jleed, Uottawa> 
 
*/

#include <string>
#include <GRT/GRT.h>
#include <vector>
using namespace GRT;
using namespace std;

int main (int argc, const char * argv[])
{
    //Parse the data filename from the argument list
    if( argc != 2 ){
        cout << "Error: failed to parse data filename from command line. You should run this example with one argument pointing to the data filename!\n";
        return EXIT_FAILURE;
    }
    const string filename = argv[1];
     UINT Kfold;
    if (argc > 2)
    {
          Kfold = stoi(argv[2]);
               
     }else
     {
         Kfold = 5;
     }

    //Create a new GMM instance and set the number of mixture models to 2
    GMM gmm;
    gmm.setNumMixtureModels(2);
    
    //Load some training data to train the classifier
    ClassificationData trainingData;
    
    if( !trainingData.load( filename ) ){
        cout << "Failed to load training data!\n";
        return EXIT_FAILURE;
    }
    
//If you want to run K-Fold cross validation using the dataset then you should first spilt the dataset into K-Folds
    //A value of 10 splits the dataset into 5 folds and the true parameter signals that stratified sampling should be used
    if( !trainingData.spiltDataIntoKFolds( Kfold, true ) ){
       cout << "Failed to spiltDataIntoKFolds!\n";
       return EXIT_FAILURE;
    }
        // initial confusion matrix
      vector<int> exCount = { 0, 0, 0, 0, 0 };
     vector<vector<double>> confMat = { { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0} };

      double Taccuracy = 0;

       //After you have called the spilt function you can then get the training and test sets for each fold
    for(UINT foldIndex=0; foldIndex<5; foldIndex++)
    {        // start fold
       
        double accuracy = 0;

        ClassificationData foldTrainingData = trainingData.getTrainingFoldData( foldIndex );
        ClassificationData foldTestingData = trainingData.getTestFoldData( foldIndex );
    
        //Train the classifier
        if( !gmm.train( foldTrainingData ) ){
            cout << "Failed to train classifier!\n";
            return EXIT_FAILURE;
        }
  
       //Use the test dataset to test the GMM model

       for(UINT i=0; i<foldTestingData.getNumSamples(); i++){
            //Get the i'th test sample
            UINT classLabel = foldTestingData[i].getClassLabel();
            VectorFloat inputVector = foldTestingData[i].getSample();
        
            //Perform a prediction using the classifier
            bool predictSuccess = gmm.predict( inputVector );
        
            if( !predictSuccess ){
                 cout << "Failed to perform prediction for test sampel: " << i <<"\n";
                 return EXIT_FAILURE;
            }
        
            //Get the predicted class label

            VectorFloat classLikelihoods = gmm.getClassLikelihoods();
            VectorFloat classDistances = gmm.getClassDistances();
        
            /*
                /// compute maximum likelihoods ////
            VectorFloat y(classLikelihoods.size());
            size_t nind(0);
            generate(begin(y), end(y), [&]{ return nind++; });
            sort( begin(y),end(y),[&](int i1, int i2) { return classLikelihoods[i1] > classLikelihoods[i2]; } );
            UINT predictedClassLabel=y[0];
                 /// end maximum likelihoods   ///
           */
            
           UINT predictedClassLabel = gmm.getPredictedClassLabel();
            //Update the accuracy
            if( classLabel == predictedClassLabel ) accuracy++;
           exCount[int(classLabel-1)] += 1;   // # of each class 
            
            confMat[int(classLabel-1)][int(predictedClassLabel-1)] += 1.0;
         }  // end testing
     
    
         cout<<"=================================="<<endl;
         Taccuracy+= accuracy/double(foldTestingData.getNumSamples())*100.0;
         cout<< "fold # ( "<< foldIndex+1 <<" ) is done"<<endl; 
    }// end fold
    cout<<"=================================="<<endl;
    cout<< " K-folds # :      "<< Kfold << endl;
    cout<< " Total Accuracy =   "<< Taccuracy/Kfold << "  % "<<endl;
    cout<< "Total confusion matrix ="<<endl;
   for (UINT im = 0; im < Kfold; im++)
   {
       for (UINT in = 0; in < Kfold; in++)
        {
          confMat[im][in]= (confMat[im][in] / exCount[im]) * 100;
           cout << confMat[im][in] << "    ";
        }
       cout << endl;
   }
    
    return EXIT_SUCCESS;
}

