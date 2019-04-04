/*
 * main.c
 *
 *  Created on: 25 févr. 2019
 *      Author: jgaud
 */

// Used modules headers
#include "EMIF_driver.h"
#include "SPI_driver.h"
#include "C6713Helper_UdeS.h"

// standard libraries
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition
#include <math.h>

#include <csl.h>
#include <csl_gpio.h>
#include <csl_mcbsp.h>
#include <csl_irq.h>
#include <dsk6713_led.h>
#include <dsk6713_aic23.h>
#include <dsk6713.h>
#include "dsk6713_dip.h"
#include "getEZWEED.h"
#include "Audio_Config.h"
#include "teachEZWEED.h"

void ALL_LED_OFF()
{
    DSK6713_LED_off(0);
    DSK6713_LED_off(1);
    DSK6713_LED_off(2);
    DSK6713_LED_off(3);
}
void ALL_LED_ON()
{
    DSK6713_LED_on(0);
    DSK6713_LED_on(1);
    DSK6713_LED_on(2);
    DSK6713_LED_on(3);
}


void main(void)
{
    // Ce main est en cours de conception, à modifier
    int F0;
    ALL_LED_OFF();
    Codec_Audio_init();
    getEZWEED_init();
    initteachEZWEED();

    while (1)
    {
        if (DSK6713_DIP_get(0) == 1)
        {
            teachEZWEED();
        }
        else if(DSK6713_DIP_get(0) == 0){
            F0 = concludeEZWEED();
        }
        //getEZWEED();
    }
}




