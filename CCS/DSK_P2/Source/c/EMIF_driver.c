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

int FlagTLC1550 = 0;
int SelectionADC = 0;
short ValeurADC = 0;

void ActiveADCLuminosite(void){
    *(unsigned int *) ADRESSE_ADC_lumen = 0x0; // Activer ADC luminosit�
    SelectionADC = Lumiere;
}

void ActiveADCHumidite(void){
    *(unsigned int *) ADRESSE_ADC_humidite = 0x0; // Activer ADC humidit�
    SelectionADC = Humidite;
}

/****************************************************************************
    ISR :
****************************************************************************/
void interrupt intTLC1550(void){
    FlagTLC1550 = 1;
    if(SelectionADC == Lumiere){
        ValeurADC = *(unsigned short*) ADRESSE_ADC_lumen; //READ une donn�e de l�ADC
    }
    else{
        ValeurADC = *(unsigned short*) ADRESSE_ADC_humidite; //READ une donn�e de l�ADC
    }
    return;
}