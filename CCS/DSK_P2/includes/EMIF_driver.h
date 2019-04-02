/*
 * EMIF_driver.h
 *
 *  Created on: 21 mars 2019
 *      Author: louis
 */

#ifndef SOURCE_REFERENCE_EMIF_DRIVER_H_
#define SOURCE_REFERENCE_EMIF_DRIVER_H_


// standard libraries
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition

#define ADRESSE_ADC_humidite 0xB0380000 //Capteur humidité
#define ADRESSE_ADC_lumen 0xB0300000 //Capteur luminosité
#define Lumiere 1
#define Humidite 0


extern int FlagTLC1550;

// Function description here ...
void ActiveADCLuminosite(void);
void ActiveADCHumidite(void);

#endif /* SOURCE_REFERENCE_EMIF_DRIVER_H_ */
