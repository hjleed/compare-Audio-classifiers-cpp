
 /*
 
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT> <MIT License>
 Edited (c) <2017> <Hitham Jleed, Uottawa> <WatchLife Co License>
 
*/

#include <string>

#include <GRT/GRT.h>
using namespace GRT;
using namespace std;

int main (int argc, const char * argv[])
{
    //Parse the data filename from the argument list
    if( argc < 2 ){
        cout << "Error: failed to parse data filename from command line.!\n";
        return EXIT_FAILURE;
    }
    UINT Kfold;
    const string filename = argv[1];
     if (argc > 2)
         {
             Kfold = stoi(argv[2]);
             // ...    
         }else
         {
             Kfold = 5;
         }


    //Create a new RandomForests instance
    RandomForests forest;
    
    //Set the number of trees in the forest
    forest.setForestSize( 10 );
    
    //Set the number of random candidate splits that will be used to choose the best splitting values
    //More steps will give you a better model, but will take longer to train
    forest.setNumRandomSplits( 100 );
    
    //Set the maximum depth of the tree
    forest.setMaxDepth( 10 );
    
    //Set the minimum number of samples allowed per node
    forest.setMinNumSamplesPerNode( 10 );
    
    //Load some training data to train the classifier
    ClassificationData trainingData;
    
    cout << "Loading Training Data\n";
    if( !trainingData.load( filename ) ){
        cout << "Failed to load training data: " << filename << endl;
        return EXIT_FAILURE;
    }

    
   

    //If you want to run K-Fold cross validation using the dataset then you should first spilt the dataset into K-Folds
    //A value of 10 splits the dataset into 5 folds and the true parameter signals that stratified sampling should be used
    if( !trainingData.spiltDataIntoKFolds( Kfold, true ) ){
       cout << "Failed to spiltDataIntoKFolds!\n";
       return EXIT_FAILURE;
    }
        
      vector<int> exCount = { 0, 0, 0, 0, 0 };
     vector<vector<double>> confMat = { { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0} };

   double Taccuracy = 0;

       //After you have called the spilt function you can then get the training and test sets for each fold
    for(UINT foldIndex=0; foldIndex<Kfold; foldIndex++)
    {        // start fold

     double accuracy = 0;

      ClassificationData foldTrainingData = trainingData.getTrainingFoldData( foldIndex );
      ClassificationData foldTestingData = trainingData.getTestFoldData( foldIndex );

        //Train the classifier
    if( !forest.train( foldTrainingData ) ){
        cout << "Failed to train classifier!\n";
        return EXIT_FAILURE;
    }

    
   
    for(UINT i=0; i<foldTestingData.getNumSamples(); i++){
        //Get the i'th test sample
        UINT classLabel = foldTestingData[i].getClassLabel();
        VectorDouble inputVector = foldTestingData[i].getSample();
        
        //Perform a prediction using the classifier
        bool predictSuccess = forest.predict( inputVector );
        
        if( !predictSuccess ){
            cout << "Failed to perform prediction for test sampel: " << i <<"\n";
            return EXIT_FAILURE;
        }
        
        //Get the predicted class label
        UINT predictedClassLabel = forest.getPredictedClassLabel();
        VectorDouble classLikelihoods = forest.getClassLikelihoods();
        VectorDouble classDistances = forest.getClassDistances();
 
        //Update the accuracy
        if( classLabel == predictedClassLabel ) accuracy++;

        exCount[int(classLabel-1)] += 1;
            
        confMat[int(classLabel-1)][int(predictedClassLabel-1)] += 1.0;
        
    }

     cout<<"=================================="<<endl;
     Taccuracy+= accuracy/double(foldTestingData.getNumSamples())*100.0;
    }// end fold
    cout<<"=================================="<<endl;
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
