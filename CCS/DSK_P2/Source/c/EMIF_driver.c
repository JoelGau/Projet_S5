/*
 * EMIF_driver.c
 *
 *  Created on: 21 mars 2019
 *      Author: louis
 */


#include "EMIF_driver.h"
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition
#include <csl.h>
#include <csl_gpio.h>
#include <dsk6713.h>

extern unsigned short ValLumen;
extern unsigned short ValHumidite;

void ActiveADCLuminosite(void){
    *(unsigned int *) ADRESSE_ADC_lumen = 0x0; // Activer ADC luminosit�
}

void ActiveADCHumidite(void){
    *(unsigned int *) ADRESSE_ADC_humidite = 0x0; // Activer ADC humidit�
}

/****************************************************************************
    ISR :
****************************************************************************/
void interrupt intHumidite(void){
        ValHumidite = *(unsigned short*) ADRESSE_ADC_humidite; //READ une donn�e de l�ADC
    return;
}

void interrupt intLumen(void){
        ValLumen = *(unsigned short*) ADRESSE_ADC_lumen; //READ une donn�e de l�ADC
    return;
}
