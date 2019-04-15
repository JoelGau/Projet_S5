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

struct Input_Ana
{
    short value;    // valeur du capteur
    short request;    // 1 = lire le capteur, 2 = idle
};

extern struct Input_Ana Lumen;
extern struct Input_Ana Humidite;

void ActiveADCLuminosite(void){
    *(unsigned int *) ADRESSE_ADC_lumen = 0x0; // Activer ADC luminosité
}

void ActiveADCHumidite(void){
    *(unsigned int *) ADRESSE_ADC_humidite = 0x0; // Activer ADC humidité
}

/****************************************************************************
    ISR :
****************************************************************************/
void interrupt intHumidite(void){
		Humidite.value = *(unsigned short*) ADRESSE_ADC_humidite; //READ une donnée de l’ADC
        //Humidite.value = *(unsigned short*) ADRESSE_ADC_humidite; //READ une donnée de l’ADC
        if(Humidite.value > 999){
            Humidite.value = 999;
        }
    return;
}

void interrupt intLumen(void){
        Lumen.value = *(unsigned short*) ADRESSE_ADC_lumen; //READ une donnée de l’ADC
        Lumen.value = 1023 - Lumen.value;
        if(Lumen.value > 999){
            Lumen.value = 999;
        }
    return;
}
