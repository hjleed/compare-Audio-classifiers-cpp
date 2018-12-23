/******************************************************************************
  getfeatures.cpp: This function contains audio features

  Author : Hitham Jleed
  Univeristy of Ottawa & iWatchLife Inc. 
  © Copyright <2017>
*******************************************************************************/

#include <math.h>
#include <vector>
#include "features.h"

using namespace std;

//===========================================================
    /** The main body calculates Audio features
     * @param buffer a time domain buffer containing audio samples
     * @returns mysample <features vector>
     */
//                                                                  ***    **  The dominating function
 vector<double> features(const vector<short int> & buffer)
{

   vector<double> mysample;
 vector<double> wbuffer=windbuffer(buffer,2);
   double ZCR= ZCRate(wbuffer);                         // ZERO CROSSING RATE
   double rmsV= rootMeanSquare(wbuffer);                // root Mean Square
   double loudness= 20* log (rmsV);                    // loudness measure
   vector<double> magnitudeSpectrum=getfft(wbuffer);   // magnitude spectrum
   vector<double> MagRes = mag2db(magnitudeSpectrum);  // magnitude response
   double Sprty=SpecSpar(MagRes);                      // Spectral Sparsity  
   double Spcntrd=specCent(MagRes);                    // Spectral Centroid
   double acorr=autocorr(wbuffer,10);
   mysample.push_back(ZCR);
   mysample.push_back(loudness);
   mysample.push_back(Sprty);
   mysample.push_back(Spcntrd);
   mysample.push_back(acorr);
    unsigned int coeff;
   double mfcc_result;
	for(coeff = 1; coeff < 13; coeff++)
	{
		mfcc_result = GetCoefficient(magnitudeSpectrum,16000, 48, 128, coeff);
		mysample.push_back(mfcc_result);
	}
  // FILL with my features
   
 
 
  
 return mysample;
}
