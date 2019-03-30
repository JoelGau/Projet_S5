/*
 * main.c
 *
 *  Created on: 25 févr. 2019
 *      Author: jgaud
 */

// Used modules headers
#include "EMIF_driver.h"
#include "SPI_driver.h"
#include "Audio_driver.h"
#include "C6713Helper_UdeS.h"
#include "CorrelationCroisee.h"

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

#define ATTENTE 0
#define ORTHO 1
#define AUTO 2
#define COMPUTING 3
#define AUTRE 4

int State = ATTENTE;

int Sref[LONGUEURTRAME] = {1,2,3,4,5,5,4,3,2,1};
int Sort[LONGUEURTRAME] = {0,0,0,0,0,0,0,0,0,0};
int Scus[LONGUEURTRAME] = {-1,0,1,0,-1,0,1,0,-1,0};

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
    ALL_LED_OFF();
    while (true)
    {


    }

}




