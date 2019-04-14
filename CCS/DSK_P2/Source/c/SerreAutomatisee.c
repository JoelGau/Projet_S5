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
#include "getEZWEED.h"

#define ATTENTE 0
#define ORTHO 1
#define AUTO 2
#define COMPUTING 3
#define AUTRE 4
#define LONGUEURTRAME 10
#define NB_CYCLES_PAR_SEC 225000000     // Nombre de cycles par secondes

#define A 0x41
#define B 0x42
#define E 0x45
#define H 0x48
#define L 0x4C
#define M 0x4D
#define P 0x50
#define S 0x53
#define T 0x54
#define V 0x56

int State = ATTENTE;

int Sref[LONGUEURTRAME] = {1,2,3,4,5,5,4,3,2,1};
int Sort[LONGUEURTRAME] = {0,0,0,0,0,0,0,0,0,0};
int Scus[LONGUEURTRAME] = {-1,0,1,0,-1,0,1,0,-1,0};

unsigned char rx_msg;
int rx_flag;
int Son_out;
int sb = 0;
unsigned short ValLumen = 0;
unsigned short ValHumidite = 0;
int FlagTLC1550 = 0;
unsigned long long mainCounter = 1;
unsigned long long time = 0;

// Partie Communication
unsigned char i_rx_msg = 0;
unsigned char type = 0;
unsigned char byte1 = 0;
unsigned char byte2 = 0;
unsigned char answer = 0;
unsigned short temperature = 0;
unsigned short humidite = 0;
unsigned char volet = 0;
unsigned short plant = 0;
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
void attendre(float seconds)
{
    int cnt=0;
    int fin = (int)NB_CYCLES_PAR_SEC*seconds;
    while (cnt++<fin) {}
}

void main(void)
{
    // Ce main est en cours de conception, à modifier
    DSK6713_init();
    GPIO_init();
    Audio_init();
    SPI_init();
    ALL_LED_OFF();
    //sendUART(0x53); //humidite du sol
    DSK6713_waitusec(2000);
    MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    DSK6713_waitusec(2000);
    MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    DSK6713_waitusec(2000);
    ValLumen = 254;
    ValHumidite = 694;
    sendUART(M);
    sendUART(S);
    sendUART(E);
    DSK6713_waitusec(2000);
    ValHumidite = *(unsigned short*) ADRESSE_ADC_humidite; //READ une donnée de l’ADC;
    DSK6713_waitusec(2000);
    ValLumen = *(unsigned short*) ADRESSE_ADC_lumen; //READ une donnée de l’ADC
    DSK6713_waitusec(2000);

    while (true)
    {
        mainCounter++;
        if(mainCounter == 0x0FFFF){
            ActiveADCLuminosite();
        }
        if(mainCounter == 0x1FFFF){
            ActiveADCHumidite();
            mainCounter = 0;
        }
        if(time == mainCounter){
            lire_MCBSP();
        }




        //attendre(5);
        //printf("write data \n");
        if(FlagSPI == 1)
        {
            time = mainCounter;
            lire_MCBSP();
            FlagSPI = 0;    // Reset Flag à 0
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
        case A:{
            break;}
        case B:{
            break;}
        case E:{
            break;}
        case H:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x48);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0xFF);
            break;}
        case 0x4C:{
            break;}
        case P:{
            break;}
        case S:{
            break;}
        case T:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x54);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0x00);
            ecrire_MCBSP(0xFF);
            break;}
        case V:{
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
        case A:{
            break;}
        case B:{
            break;}
        case E:{
            break;}
        case H:{
            humidite = byte1 << 8;
            humidite = humidite | byte2;
            break;}
        case 0x4C:{
            break;}
        case P:{
            plant = byte2;
            break;}
        case S:{
            break;}
        case T:{
            temperature = byte1 << 8;
            temperature = temperature | byte2;
            break;}
        case V:{
            volet = byte2;
            break;}
        default:{
            break;}
    }
    i_rx_msg = 0;
}
void sendUART(unsigned char type){
    switch(type){
        case A:{
            break;}
        case B:{
            break;}
        case E:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x45);
            ecrire_MCBSP(ValLumen >> 8);
            ecrire_MCBSP(ValLumen & 0x00FF);
            ecrire_MCBSP(0x00);
            break;}
        case H:{
            break;}
        case 0x4C:{
            break;}
        case P:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(P);
            ecrire_MCBSP(0);
            ecrire_MCBSP(plant);
            ecrire_MCBSP(0x00);
            break;}
        case S:{
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x53);
            ecrire_MCBSP(ValHumidite >> 8);
            ecrire_MCBSP(ValHumidite & 0x00FF);
            ecrire_MCBSP(0x00);
            break;}
        case T:{
            break;}
        case V:{
            break;}
        default:{
            break;}
    }
    i_rx_msg = 0;
}



