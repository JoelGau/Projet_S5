/*
 * getEZWEED.h
 *
 *  Created on: 30 mars 2019
 *      Author: stjn1901
 */

#ifndef INCLUDES_GETEZWEED_H_
#define INCLUDES_GETEZWEED_H_

// standard libraries
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition
#include "CONSTANTES.h"

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011

void getEZWEED_init(void);
short findPeaks(short* mag);
void getEZWEED_Audio_init(void);
void getEZWEED(void);

#endif /* INCLUDES_GETEZWEED_H_ */
