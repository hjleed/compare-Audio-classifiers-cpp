
/*
 
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT> <MIT License>
 Edited (c) <2017> <Hitham Jleed, Uottawa> <WatchLife Co License>
 
*/

#include <GRT/GRT.h>
using namespace GRT;
using namespace std;

int main (int argc, const char * argv[])
{
    //Parse the data filename from the argument list
    if( argc != 2 ){
        cout << "Error: failed to parse data filename from command line. You should run this example with at least one argument pointing to the data filename!\n";
        return EXIT_FAILURE;
    }
    const string filename = argv[1];

        UINT Kfold;
     if (argc > 2)
     {
         Kfold = stoi(argv[2]);
             // ...    
      }else
      {
          Kfold = 5;
      }
    
    //Create a new Softmax instance
    Softmax softmax;
    
    //Load some training data to train the classifier
    ClassificationData trainingData;
    
    if( !trainingData.load( filename ) ){
        cout << "Failed to load training data: " << filename << endl;
        return EXIT_FAILURE;
    }
    

          int exCount [5] = { 0, 0, 0, 0, 0 };
          double confMat [5][5] = { { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0} };


    if( !trainingData.spiltDataIntoKFolds( Kfold, true ) ){
       cout << "Failed to spiltDataIntoKFolds!\n";
       return EXIT_FAILURE;
    }
     double Taccuracy = 0;
      //After you have called the spilt function you can then get the training and test sets for each fold
    for(UINT foldIndex=0; foldIndex<Kfold; foldIndex++)
    {      
          ClassificationData foldTrainingData = trainingData.getTrainingFoldData( foldIndex );
          ClassificationData foldTestingData = trainingData.getTestFoldData( foldIndex );
         //Train the classifier
         if( !softmax.train( foldTrainingData ) ){
             cout << "Failed to train classifier!\n";
  	      return EXIT_FAILURE;
  	  }
    
     
   	 //Use the test dataset to test the softmax model
   	 double accuracy = 0;
   	 for(UINT i=0; i<foldTestingData.getNumSamples(); i++){
   	     //Get the i'th test sample
   	     UINT classLabel = foldTestingData[i].getClassLabel();
   	     VectorFloat inputVector = foldTestingData[i].getSample();
   	     
   	     //Perform a prediction using the classifier
   	     if( !softmax.predict( inputVector ) ){
   	         cout << "Failed to perform prediction for test sample: " << i <<"\n";
   	         return EXIT_FAILURE;
   	     }
   	     
   	     //Get the predicted class label
   	     UINT predictedClassLabel = softmax.getPredictedClassLabel();

   	     if (predictedClassLabel<1 && predictedClassLabel>5) perror ("This IS IT !!!!!!");
	
   	     VectorFloat classLikelihoods = softmax.getClassLikelihoods();
   	     VectorFloat classDistances = softmax.getClassDistances();
   	     
   	     //Update the accuracy
   	     if( classLabel == predictedClassLabel ) accuracy++;
   	     exCount[int(classLabel-1)] += 1;
             int colm=int(predictedClassLabel-1);
             int raw=int(classLabel-1);
             confMat[raw][colm] += 1.0;


       	 } // end test
         Taccuracy+= accuracy/double(foldTestingData.getNumSamples())*100.0;
         cout << "Test Accuracy: " << accuracy/double(foldTestingData.getNumSamples())*100.0 << "%" << endl;
      }// end fold

     cout<< " K-folds # :      "<< Kfold << endl;
     cout<< " Total Accuracy =   "<< Taccuracy/Kfold << "  % "<<endl;
     cout<< "Total confusion matrix ="<<endl;
     for (unsigned int im = 0; im < 5; im++)
     {
         for (unsigned int in = 0; in < 5; in++)
          {
              confMat[im][in]= (confMat[im][in] / exCount[im]) * 100;
              cout << confMat[im][in] << "    ";
          }
          cout << endl;
     }
      
    return EXIT_SUCCESS;
}
