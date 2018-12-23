/******************************************************************************
  TimeDomainFunctions.cpp: This function contains Time Domain audio features

  Author : Hitham Jleed
  Univeristy of Ottawa & iWatchLife Inc. 
  © Copyright <2017>
*******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include "features.h"

#define PI 4*atan(1.0)



//===========================================================
    /** calculates the peak energy (max absolute value) in a time
     * domain audio signal buffer in vector format
     * @param buffer a time domain buffer containing audio samples
     * @returns the peak energy value
     */
double peakEnergy (const vector<double>& buffer)
{
    // create variable with very small value to hold the peak value
    double peak = -10000.0;

    // for each audio sample
    for (unsigned i = 0; i < buffer.size(); i++)
    {
        // store the absolute value of the sample
        double absSample = fabs (buffer[i]);

        // if the absolute value is larger than the peak
        if (absSample > peak)
        {
            // the peak takes on the sample value
            peak = absSample;
        }
    }

    // return the peak value
    return peak;
}
//===========================================================
    /** calculates the zero crossing rate of a time domain audio signal buffer
     * @param buffer a time domain buffer containing audio samples
     * @returns the zero crossing rate
     */
double ZCRate (const vector<double>& buffer)
{
    // create a variable to hold the zero crossing rate
   double zcr = 0;
    
    // for each audio sample, starting from the second one
    for (int i = 1; i < (int)buffer.size(); i++)
    {
        // initialise two booleans indicating whether or not
        // the current and previous sample are positive
        bool current = (buffer[i] > 0);
        bool previous = (buffer[i - 1] > 0);

        // if the sign is different
        if (current != previous)
        {
            // add one to the zero crossing rate
            zcr = zcr + 1.0;
        }
    }
   
    // return the zero crossing rate
    return zcr/buffer.size();
}

 //===========================================================
    /** calculates the Root Mean Square (RMS) of an audio buffer
     * in vector format
     * @param buffer a time domain buffer containing audio samples
     * @returns the RMS value
     */
double rootMeanSquare (const vector<double>& buffer)
{
    // create variable to hold the sum
    double sum = 0;

    // sum the squared samples
    for (int i = 0; i < (int)buffer.size(); i++)
    {
        sum += pow (buffer[i], 2);
    }

    // return the square root of the mean of squared samples
    return sqrt (sum / ((double)buffer.size()));
}

//===========================================================
    /** calculates the window of a time domain audio signal buffer
     * @param buffer a time domain buffer containing audio samples
     * (1): Rectangular
     * (2): Hamming
     * (3): Hann
     * @returns buffer of windowed buffer 
     */
 vector<double> windbuffer(const vector<short int> & buffer,int type)
{ 
   
   vector<double> frame;
   double multiplier;
    int n=buffer.size();
     for (int i = 0; i < n; i++)
     {
        if(type == 1)  multiplier=1;
    	if(type == 2)  multiplier = 0.5 * (1 - cos(2*PI*(double)i/(double)(n-1)));        //hann window
        if(type == 3)  multiplier=(double)(0.54-0.46*cos((double)i*2*PI/(double)(n-1)));    // hamming window
    	frame.push_back(multiplier * (double)buffer[i]);
     }

    return frame;
}

 //===========================================================
    /** computes autocorrelation (corrected divided by N to divided (N-leg) from Tobias Mueller
     * in vector format
     * @param buffer a time domain buffer containing audio samples, and leg
     * @returns the autocorrelation 
     */
double autocorr (const vector<double>& buffer, int leg)
{
	int n=buffer.size();
        double mean= (accumulate(buffer.begin(), buffer.end(), 0))/double(n);
	double var=0.0;        // variance
	double autocv= 0.0;   // autoconvariance
	for (int i=0; i<n; i++)
	{
             var+=(pow((buffer[i] -mean), 2.0)/n);
	     if (i<(n-leg))    autocv+=((buffer[i] -mean)*(buffer[i+leg] -mean));
        }
	autocv=(1.0/(n-leg))*autocv;
       // autocorrelation is autoconvarience divided by variance
	return (autocv/var);
}

