/******************************************************************************
  MelFrequencyCepstrum.cpp: This function computes Mel-Frequency Cepstrum Coefficients

  Author : Hitham Jleed
  Univeristy of Ottawa & iWatchLife Inc. 
  © Copyright <2017>
*******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include "features.h"

#define PI 4*atan(1.0)

//===========================================================
/* Compute MFCC. I modified libmfcc 
 * Copyright (c) 2010 Jeremy Sawruk
 * The code was released under the MIT License. 
 */
    double GetCenterFrequency(unsigned int filterBand)
{
	double centerFrequency = 0.0f;
	double exponent;

	if(filterBand == 0)
	{
		centerFrequency = 0;
	}
	else if(filterBand >= 1 && filterBand <= 14)
	{
		centerFrequency = (200.0f * filterBand) / 3.0f;
	}
	else
	{
		exponent = filterBand - 14.0f;
		centerFrequency = pow(1.0711703, exponent);
		centerFrequency *= 1073.4;
	}
	
	return centerFrequency;
}

 
/* 
 * Compute the band-dependent magnitude factor for the given filter band (Eq. 3)
 * Used for internal computation only - not the be called directly
 */
double GetMagnitudeFactor(unsigned int filterBand)
{
	double magnitudeFactor = 0.0f;
	
	if(filterBand >= 1 && filterBand <= 14)
	{
		magnitudeFactor = 0.015;
	}
	else if(filterBand >= 15 && filterBand <= 48)
	{
		magnitudeFactor = 2.0f / (GetCenterFrequency(filterBand + 1) - GetCenterFrequency(filterBand -1));
	}

	return magnitudeFactor;
}
/* 
 * Compute the filter parameter for the specified frequency and filter bands (Eq. 2)
 * Used for internal computation only - not the be called directly
 */
double GetFilterParameter(unsigned int samplingRate, unsigned int binSize, unsigned int frequencyBand, unsigned int filterBand)
{
	double filterParameter = 0.0f;

	double boundary = (frequencyBand * samplingRate) / binSize;		// k * Fs / N
	double prevCenterFrequency = GetCenterFrequency(filterBand - 1);		// fc(l - 1) etc.
	double thisCenterFrequency = GetCenterFrequency(filterBand);
	double nextCenterFrequency = GetCenterFrequency(filterBand + 1);

	if(boundary >= 0 && boundary < prevCenterFrequency)
	{
		filterParameter = 0.0f;
	}
	else if(boundary >= prevCenterFrequency && boundary < thisCenterFrequency)
	{
		filterParameter = (boundary - prevCenterFrequency) / (thisCenterFrequency - prevCenterFrequency);
		filterParameter *= GetMagnitudeFactor(filterBand);
	}
	else if(boundary >= thisCenterFrequency && boundary < nextCenterFrequency)
	{
		filterParameter = (boundary - nextCenterFrequency) / (thisCenterFrequency - nextCenterFrequency);
		filterParameter *= GetMagnitudeFactor(filterBand);
	}
	else if(boundary >= nextCenterFrequency && boundary < samplingRate)
	{
		filterParameter = 0.0f;
	}

	return filterParameter;
}
/* 
 * Computes the Normalization Factor (Equation 6)
 * Used for internal computation only - not to be called directly
 */
double NormalizationFactor(int NumFilters, int m)
{
	double normalizationFactor = 0.0f;

	if(m == 0)
	{
		normalizationFactor = sqrt(1.0f / NumFilters);
	}
	else 
	{
		normalizationFactor = sqrt(2.0f / NumFilters);
	}
	
	return normalizationFactor;
}

/* 
 * Computes the specified (mth) MFCC
 *
 * spectralData - vector containing the results of FFT computation. 
 * samplingRate - the rate that the original time-series data was sampled at (i.e 16000)
 * NumFilters - the number of filters to use in the computation. Recommended value = 48
 * binSize - the size of the spectralData array, usually a power of 2
 * m - The mth MFCC coefficient to compute
 *
 */
double GetCoefficient(const vector<double>& spectralData, unsigned int samplingRate, unsigned int NumFilters, unsigned int binSize, unsigned int m)
{
	double result = 0.0f;
	double outerSum = 0.0f;
	double innerSum = 0.0f;
	unsigned int k, l;

	// 0 <= m < L
	if(m >= NumFilters)
	{
		// This represents an error condition - the specified coefficient is greater than or equal to the number of filters. The behavior in this case is undefined.
		return 0.0f;
	}

	result = NormalizationFactor(NumFilters, m);

	
	for(l = 1; l <= NumFilters; l++)
	{
		// Compute inner sum
		innerSum = 0.0f;
		for(k = 0; k < binSize - 1; k++)
		{
			innerSum += fabs(spectralData[k] * GetFilterParameter(samplingRate, binSize, k, l));
		}

		if(innerSum > 0.0f)
		{
			innerSum = log(innerSum); // The log of 0 is undefined, so don't use it
		}

		innerSum = innerSum * cos(((m * PI) / NumFilters) * (l - 0.5f));

		outerSum += innerSum;
	}

	result *= outerSum;

	return result;
}

