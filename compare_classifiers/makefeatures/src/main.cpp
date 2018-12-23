#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <complex>
#include <GRT/GRT.h>

using namespace GRT;
using namespace std;

#define FREQ 16000                    //sampling frequency
#define WINSIZE 512                 // frame size in samples
#define HOPSIZE (0.5*WINSIZE)         // frame shift in samples
#define m 17                         // dimensionality of the data 


typedef struct header_file
{
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;		// number of channels i.e 1-mono 2-stereo
	int sample_rate;			// sample_rate denotes the sampling rate.
	int byte_rate;
	short int block_align;
	short int bits_per_sample;		// number of bits per sample
	char subchunk2_id[4];
	int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;


typedef struct header_file* header_p;

// featuree function decliration
vector<double> features(const vector<short int> & buffer);
// get wav file name
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp= nullptr;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
      if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
        files.push_back(string(dirp->d_name));
     
                 
    }
    closedir(dp);
    sort( files.begin(), files.end()); 
    return 0;
}


/**************  ------ Main Body---------  ******************/

int main(int argc, char* argv[])

{

    //Create a new instance of the ClassificationData
    ClassificationData trainingData;
 
    //Set the dimensionality of the data 
    trainingData.setNumDimensions(m);
    
    //giving the dataset a name (the name should have no spaces)
    trainingData.setDatasetName("ClassificationData");
    
    // adding some info text about the data
    trainingData.setInfoText("This data contains some audio records for classification purpose");
    
    VectorFloat sample(m);

    // reset the label
    UINT Label=0;
    // My data 
    //string classes[5] = {"breakingglass", "cough", "doorslam", "footsteps", "papercrumpling"};
  
    vector<string> classes = vector<string>();

    string filePath;
    string path = argv[1];
    string npath;
    getdir (path,classes);
      for(unsigned int Id=0; Id<classes.size(); Id++) // start Id loop -------------------
      {
        Label +=1;

        vector<string> files = vector<string>();
        npath=path + '/'+ classes[Id];

        getdir (npath,files);
        
         cout << "\n reading ( " << classes[Id] << " ) class folder that has : "<< files.size()<< " records" << endl;

        for (unsigned int num=0; num<files.size();num++)   // start num loop ----------------
        {
           //** Load wav file
            filePath=npath + '/'+ files[num];

          
            VectorFloat sample(m);
    	    FILE* infile = fopen(filePath.c_str(), "r");
    	  
   	    int count = 0;						// For counting number of frames in wave file.
   	    header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
	    
   	    if (!infile)   // start if (!infile
   	    {
		cout << " the file (" << filePath << " )is NOT exist! " << endl;
   	    }
   	     else
   	    {
		/* Print header information i.e sampling rate, no. of samples, etc */

		fread(meta, 1, sizeof(header), infile);
  
		if (FREQ !=(meta->sample_rate))  perror(" sampling frequency is not 16000 ");
		const int SHIFTSIZE= WINSIZE-HOPSIZE;
                //buff16.reserve(WINSIZE); 
                 vector<short int> buff16(WINSIZE); 
                
                short int sample_start, numb_samples;	// Variables for reading samples that fall within window for 1st frame		
		float hop_time = 0;			// Hop time for printing in output file

		for (int j = 0;j<WINSIZE; j++)
		{
			buff16[j] = 0;
		}
               /* Start reading file frame by frame */
		while (!feof(infile))
		{
			if (count == 0)
			{
				sample_start = floor((WINSIZE / 2) - (HOPSIZE));
				numb_samples = ceil((WINSIZE / 2) + (HOPSIZE));
                                 // For 1st frame, read only samples that fall within window and reamining samples are 0.
				fread(&buff16[sample_start], sizeof buff16[0], numb_samples, infile);
                               
			}
			else
			{
				for (int i = 0;i<((WINSIZE)-(HOPSIZE));i++)   // Shifting data in buffer so as to read new data equivalent only to Hop size 
				{
					buff16[i] = buff16[i + (HOPSIZE)];
				}
				fread(&buff16[SHIFTSIZE], sizeof buff16[0], (HOPSIZE), infile); // Reading new data equivalent to HOPSIZE from 2nd frame onwards

			}  // endif (count == 0)
                      /* ------- Features start here ------------------------------- */

                      vector<double> mysample=features(buff16);
		      sample.assign(mysample.begin(), mysample.end());
                      //Add the sample to the training data
                      trainingData.addSample( Label, sample );

                      /* -------features processing end ------------------------------- */

		      /* Print time and feature value to a file */
		      hop_time = hop_time + float(HOPSIZE/FREQ);


		      count++;
		}   // end while (!feof(infile))
 
   	    } // endif (!infile
             
         } // end num loop -----------------
        
      } // end Id loop ------------------


  //Save my features to a file
    if( !trainingData.save( "Features.grt" ) ){
		cout << "ERROR: Failed to save dataset to file!\n";
		return EXIT_FAILURE;
    }

    
    return EXIT_SUCCESS;
}




