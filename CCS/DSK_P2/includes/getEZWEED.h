/*
 * getEZWEED.h
 *
 *  Created on: 30 mars 2019
 *      Author: stjn1901
 */

#ifndef INCLUDES_GETEZWEED_H_
#define INCLUDES_GETEZWEED_H_

// standard libraries
#include "CONSTANTES.h"


#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011

void getEZWEED_init(void);
float findPeaks(float* mag);
void getEZWEED(void);
void bitrev_index(short *, int);


#endif /* INCLUDES_GETEZWEED_H_ */
