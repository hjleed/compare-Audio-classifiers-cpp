/******************************************************************************
  FrequencyDomainFunctions.cpp: This function contains Frequency Domain audio features

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
#define EPS 1e-15
#define fs 16e3
//===========================================================
    /** calculates the Nearest Superior Power of 2
     * This function was posted on geeksforgeeks.org 
     * @param interger number
     * @returns the nearist power of 2  
     */
int nextPowerOf2(int n)
{
  int count = 0;

  /* First n in the below condition is for the case where n is 0*/
  if (n && !(n&(n-1)))
    return n;

  while( n != 0)
  {
    n  >>= 1;
    count += 1;
  }

  return 1 << count;
}

//===========================================================       
    /** calculates the fft of a time domain audio signal buffer
     * @param buffer a time domain buffer containing audio samples
     * @returns absolute value of spectrum 
     */                                                          

vector<double> getfft(vector<double> & buffer)
{ 
    
    int pn=buffer.size();
    int n= nextPowerOf2(pn);   // next power of 2
    double w[2*n *5/4],aa[2*n];
    int ip[2*n];
    ip[0] = 0;    

    if(pn<n)       // padding zeros
    {
         vector<double> padding;
         padding.assign(n-pn,0);
         copy( padding.begin(), padding.end(), std::back_inserter( buffer ) );
    }
    
    double* a=&buffer[0];

   // add imaginary part
   for (int i=0;i<n;++i)
    {
        aa[2*i]=a[i];
        aa[2*i+1]=0.0;
    }
    // Ooura fft
    cdft(2*n, 1, aa, ip, w);
   vector<double> magnitudeSpectrum;
     for (int i=0; i<=n/2; i++)           //  half length
        magnitudeSpectrum.push_back(sqrt(pow(aa[2*i],2) + pow(aa[2*i+1],2)));

    return magnitudeSpectrum;
} //              

//===========================================================
    /** calculates magnitude response (dB) of the magnitude buffer
     * @param spectrum buffer
     * @returns the first half of the magnitude response in dB
     */
 vector<double> mag2db (const vector<double>& magnitudeSpectrum)
 {
  vector<double> magRes;
  for (int i=0; i<(int)(magnitudeSpectrum.size()); i++)
        magRes.push_back(int(20) * log(abs(magnitudeSpectrum[i])));
  return magRes;
}

//===========================================================
    /** calculates spectral centroid of the magnitude buffer
     * @param spectrum buffer
     * @returns the spectral centroid

     */
 double specCent (const vector<double>& magnitudeSpectrum)
 {
    int n=magnitudeSpectrum.size();
    double maxM =*max_element (magnitudeSpectrum.begin(), magnitudeSpectrum.end());
    double sum1=0.0;
    double sum2=0.0;
    for (int i=0; i<n; i++)
     {
             sum1+=double ((i+1)*fs/(2*n))* (magnitudeSpectrum[i]/maxM);
             sum2+= magnitudeSpectrum[i]/maxM;
     }
    //   return sum1/(sum2+EPS);
    return (sum1/(sum2+EPS))/(fs/2); // normalized so 1 corresponds to the maximum signal frequency, i.e fs/2
 }

//===========================================================
    /** calculates Spectral Sparsity of the magnitude buffer
     * @param magnitude buffer
     * @returns the Spectral Sparsity
     */

double SpecSpar (const vector<double>& MagRes)
{
    // create variable to hold the sum
   /*
    double sum = 0;
    for (int i = 0; i < MagRes.size(); i++)
            sum += MagRes[i];
   */
    double sum = accumulate(MagRes.begin(), MagRes.end(), 0);
//  double sum = boost::accumulate(MagRes, 0);
    double maxV =*max_element (MagRes.begin(), MagRes.end()); // '*' because max_element returns an iterator 
    // return the Spectral Sparsity
    return maxV/sum;
}

