/*
 * GPIO_driver.c
 *
 *  Created on: 18 mars 2019
 *      Author: louis
 */

#include "GPIO_driver.h"
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition
#include <csl.h>
#include <csl_gpio.h>
#include <csl_irq.h>
#include <dsk6713.h>

GPIO_Handle hGpio;
extern far void vectors();   // Vecteurs d'interruption



void GPIO_init(void){
    // Settings of GPIO
    hGpio = GPIO_open(GPIO_DEV0,GPIO_OPEN_RESET);
    GPIO_pinEnable(hGpio,GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6| GPIO_PIN8 | GPIO_PIN10);// activer les GPIOs

    GPIO_pinDirection(hGpio,GPIO_PIN6,GPIO_INPUT);
    GPIO_pinDirection(hGpio,GPIO_PIN4,GPIO_INPUT); //GPIO en input
    GPIO_pinDirection(hGpio,GPIO_PIN5,GPIO_INPUT);
    GPIO_pinDirection(hGpio,GPIO_PIN8,GPIO_OUTPUT); //GPIO en output
    GPIO_pinDirection(hGpio,GPIO_PIN10,GPIO_OUTPUT);

    GPIO_intPolarity(hGpio,GPIO_GPINT6,GPIO_FALLING);
    GPIO_intPolarity(hGpio,GPIO_GPINT4,GPIO_FALLING); //GPIO actif lors d'un rising
    GPIO_intPolarity(hGpio,GPIO_GPINT5,GPIO_FALLING);

    GPIO_pinWrite(hGpio,GPIO_PIN8,0);
    GPIO_pinWrite(hGpio,GPIO_PIN10,0);

    // Settings of IRQ -> GPIO4 lié à int4 et GPIO5 lié à int5
    IRQ_setVecs(vectors);
    IRQ_map(IRQ_EVT_EXTINT6,6);
    IRQ_map(IRQ_EVT_EXTINT4,4);
    IRQ_map(IRQ_EVT_EXTINT5,5);
    IRQ_reset(IRQ_EVT_EXTINT6);
    IRQ_reset(IRQ_EVT_EXTINT4);
    IRQ_reset(IRQ_EVT_EXTINT5);
    IRQ_enable(IRQ_EVT_EXTINT6);
    IRQ_enable(IRQ_EVT_EXTINT4);
    IRQ_enable(IRQ_EVT_EXTINT5);
    IRQ_nmiEnable();
    IRQ_globalEnable();
}

void ActiverPompe(void){
    GPIO_pinWrite(hGpio,GPIO_PIN10,1);
}

void DesactiverPompe(void){
    GPIO_pinWrite(hGpio,GPIO_PIN10,0);
}

void ActiverLumiere(void){
    GPIO_pinWrite(hGpio,GPIO_PIN8,0);
}

void DesactiverLumiere(void){
    GPIO_pinWrite(hGpio,GPIO_PIN8,1);
}
/****************************************************************************
    ISR :
****************************************************************************/

