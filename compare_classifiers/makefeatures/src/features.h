/*******************************************************************************
Filename : features.h

Author : Hitham Jleed
© Copyright <2017>
*******************************************************************************/

#ifndef FEATURES_H
#define FEATURES_H

#include <vector>
#include <iostream>
using namespace std;



//===========================================================
    /** calculates the Nearest Superior Power of 2
     * @param interger number
     * @returns the nearist power of 2  
     */
int nextPowerOf2(int );

//===========================================================
    /** applying windows
     * @param buffer of sampling, type of window
     * (1): Rectangular
     * (2): Hamming
     * (3): Hann
     * @returns buffer of windowed buffer 
     */
vector<double> windbuffer(const vector<short int>&, int );


/*    --Time Domain Features--     */      //**********

//===========================================================
    /** calculates the peak energy (max absolute value) in a time
     * domain audio signal buffer in vector format
     * @param buffer a time domain buffer containing audio samples
     * @returns the peak energy value
     */
double peakEnergy (const vector<double>& );

//===========================================================
    /** calculates the zero crossing rate of a time domain audio signal buffer
     * @param buffer a time domain buffer containing audio samples
     * @returns the zero crossing rate
     */
double ZCRate (const vector<double>& );

 //===========================================================
    /** calculates the Root Mean Square (RMS) of an audio buffer
     * in vector format
     * @param buffer a time domain buffer containing audio samples
     * @returns the RMS value
     */
double rootMeanSquare (const vector<double>& );
 //===========================================================
    /** computes autocorrelation (corrected divided by N to divided (N-leg) from Tobias Mueller
     * in vector format
     * @param buffer a time domain buffer containing audio samples, and autocorrelation leg
     * @returns the autocorrelation 
     */
double autocorr (const vector<double>& , int );

/*    --  compute FFT  --     */      //**********

//===========================================================
    // declare cdft from Ooura toolkit (fft4g.cpp or fftg.cpp)
void cdft(int, int, double *, int *, double *);

//===========================================================       
    /** calculates absolute value of half length of fft 
     * @param buffer a time domain buffer containing audio samples
     * @returns absolute value of spectrum 
     */                                                          
vector<double> getfft(vector<double> & );


/*    --Frequency Domain Features--     */      //**********


//===========================================================
    /** calculates magnitude response (dB) of the magnitude buffer
     * @param spectrum buffer
     * @returns the first half of the magnitude response in dB
     */
 vector<double> mag2db (const vector<double>&);
//===========================================================
    /** calculates spectral centroid of the magnitude buffer
     * @param spectrum buffer
     * @returns the spectral centroid
     */
 double specCent (const vector<double>&);
//===========================================================
    /** calculates Spectral Sparsity of the magnitude buffer
     * @param magnitude buffer
     * @returns the Spectral Sparsity
     */
 double SpecSpar (const vector<double>&);


/*    --MFCC Features--     */      //**********

//=========================================================== 
 /* Computes the specified (mth) MFCC
  * I modified libmfcc Toolkit
  * Copyright (c) 2010 Jeremy Sawruk
  * The code was released under the MIT License.
  *
  * @param 
  * spectralData - vector containing the results of FFT computation. 
  * samplingRate - the rate that the original time-series data was sampled at (i.e 16000)
  * NumFilters - the number of filters to use in the computation. Recommended value = 48
  * binSize - the size of the spectralData array, usually a power of 2
  * m - The mth MFCC coefficient to compute
  *
  */
double GetCoefficient(const vector<double>&, unsigned int, unsigned int, unsigned int, unsigned int);
//===========================================================
/* 
 * @param filterBand
 * @return centerFrequency 
 */
  double GetCenterFrequency(unsigned int );
//===========================================================
/* 
 * Compute the band-dependent magnitude factor for the given filter band (Eq. 3)
 * Used for internal computation only - not the be called directly
 * @param filterBand
 */
  double GetMagnitudeFactor(unsigned int );
//===========================================================
/* 
 * Compute the filter parameter for the specified frequency and filter bands (Eq. 2)
 * Used for internal computation only - not the be called directly
 * @param samplingRate, binSize, frequencyBand, and filterBand
 */
double GetFilterParameter(unsigned int, unsigned int, unsigned int, unsigned int );
//===========================================================
/* 
 * Computes the Normalization Factor (Equation 6)
 * Used for internal computation only - not to be called directly
 * @param NumFilters, and m
 */
double NormalizationFactor(int , int );



#endif





