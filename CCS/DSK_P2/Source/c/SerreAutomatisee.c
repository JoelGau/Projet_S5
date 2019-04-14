/*
 * main.c
 *
 *  Created on: 25 f�vr. 2019
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
// Variables globales externes
extern int* Lock;
extern int F0;

unsigned char rx_msg;
int rx_flag;
int Son_out;
int sb = 0;
unsigned short ValLumen = 0;
unsigned short ValHumidite = 694;
int FlagTLC1550 = 0;

// Partie Communication
unsigned char i_rx_msg = 0;
unsigned char type = 0;
unsigned char byte1 = 0;
unsigned char byte2 = 0;
unsigned char answer = 0;
unsigned short temperature = 0;
unsigned short humidite = 0;
unsigned char volet = 0;
void readRXData(void);
void pollUART(unsigned char);
void infoUART(unsigned char);
void sendUART(unsigned char);

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

// Attente en sec. (approximatif)
/*void attendre(float seconds)
{
    int cnt=0;
    int fin = (int)NB_CYCLES_PAR_SEC*seconds;
    while (cnt++<fin) {}
}*/

void main(void)
{
    // Ce main est en cours de conception, � modifier
    DSK6713_init();
    GPIO_init();
    SPI_init();
    ALL_LED_OFF();
    //sendUART(0x53); //humidite du sol
    DSK6713_waitusec(2000);
    Codec_Audio_init();
    getEZWEED_init();
    initteachEZWEED();
    MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    DSK6713_waitusec(2000);
    MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    DSK6713_waitusec(2000);
    // Attendre l'initialisation du codec
    *Lock = 0;

    while (true)
    {
        /*
        ActiveADCLuminosite();
        attendre(0.05);
        ActiveADCHumidite();
        attendre(0.05);
        printf("Luminosite = %u \n",ValLumen);
        printf("Humidit� = %u \n",ValHumidite);
        */
        if (DSK6713_DIP_get(0) == 0)
        {
            teachEZWEED();
        }
        if (DSK6713_DIP_get(1) == 0)
        {
            getEZWEED();
        }

        //attendre(5);
        //printf("write data \n");
        if(FlagSPI == 1)
        {
            lire_MCBSP();
            FlagSPI = 0;    // Reset Flag � 0
        }
        readRXData();
    }

}

void readRXData(void)
{
    unsigned char valRX = 0;
    if(rx_flag){
        rx_flag = 0;
        valRX = rx_msg;

        if(valRX == 0x55 && sb == 0){
            sb = 1;
        }
        else if(valRX == 0x55 && sb == 1){
            i_rx_msg = 1;
            sb = 0;
        }
        else{
            sb = 0;
        }

        if(i_rx_msg == 5){
            if(rx_msg == 0xFF){
                answer = 1;
            }
            else{
                //putchUART(ACK);
            }
            i_rx_msg = 6;
        }
        else if(i_rx_msg == 4){
            byte2 = rx_msg;
            i_rx_msg = 5;
        }
        else if(i_rx_msg == 3){
            byte1 = rx_msg;
            i_rx_msg = 4;
        }
        else if(i_rx_msg == 2){
            type = rx_msg;
            i_rx_msg = 3;
        }
        else if(i_rx_msg == 1){
            i_rx_msg = 2;
        }
           /* else if(rx_msg == 0x00){
                ecrire_MCBSP(0xAA);
            }*/

    }

    if(i_rx_msg == 6 && answer == 1){
        sendUART(type);
        answer = 0;
    }
    else if(i_rx_msg == 6 && answer == 0){
        infoUART(type);
    }
}

void pollUART(unsigned char type){
    switch(type){
        case 0x41:{
            break;}
        case 0x42:{
            break;}
        case 0x45:{
            break;}
        case 0x48:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x48);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0xFF);
            break;}
        case 0x4C:{
            break;}
        case 0x50:{
            break;}
        case 0x53:{
            break;}
        case 0x54:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x54);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0xFF);
            break;}
        case 0x56:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x56);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0xFF);
            break;}
        default:{
            break;}
    }
    i_rx_msg = 0;
}
void infoUART(unsigned char type){
    switch(type){
        case 0x41:{
            break;}
        case 0x42:{
            break;}
        case 0x45:{
            break;}
        case 0x48:{
            humidite = byte1 << 8;
            humidite = humidite | byte2;
            break;}
        case 0x4C:{
            break;}
        case 0x50:{
            break;}
        case 0x53:{
            break;}
        case 0x54:{
            temperature = byte1 << 8;
            temperature = temperature | byte2;
            break;}
        case 0x56:{
            volet = byte2;
            break;}
        default:{
            break;}
    }
    i_rx_msg = 0;
}
void sendUART(unsigned char type){
    switch(type){
        case 0x41:{
            break;}
        case 0x42:{
            break;}
        case 0x45:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x45);
            ecrire_MCBSP(ValLumen>>8);
            ecrire_MCBSP(ValLumen&0xFF);
            ecrire_MCBSP(0x00);
            break;}
        case 0x48:{
            break;}
        case 0x4C:{
            break;}
        case 0x50:{
            break;}
        case 0x53:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x53);
            ecrire_MCBSP(ValHumidite >> 8);
            ecrire_MCBSP(ValHumidite & 0xFF);
            ecrire_MCBSP(0x00);
            break;}
        case 0x54:{
            break;}
        case 0x56:{
            break;}
        default:{
            break;}
    }
    i_rx_msg = 0;
}



