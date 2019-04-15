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
#include <csl_timer.h>
#include <dsk6713_led.h>
#include <dsk6713_aic23.h>
#include <dsk6713.h>
#include "dsk6713_dip.h"
#include "getEZWEED.h"
#include "Audio_Config.h"
#include "teachEZWEED.h"

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

// Définir des structures de références
struct Output_Bin
{
    short state;      // 0 = off, 1 = on
    short request;    // 0 = mettre à off, 1 = mettre à on, 2 = idle
};

struct Output_Bin  Pompe;
struct Output_Bin  Lumiere;

struct Input_Ana
{
    unsigned short value;    // valeur du capteur
    short request;    // 1 = lire le capteur, 2 = idle
};

struct Input_Ana Humidite;
struct Input_Ana Lumen;

/*unsigned short LumState = 0;
unsigned short PompeState = 0;
unsigned short ValHumidite = 0;
unsigned short ValLumen = 0;
unsigned long long mainCounter = 0;
unsigned long long time = 0;*/

// Variables globales externes
extern int* Lock;
extern int PIDFlag;

unsigned char rx_msg;
int rx_flag;
int Son_out;
int sb = 0;

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

void main(void)
{
    /******************/
    /* Initialisation */
    /******************/

    // Communication et GPIO
    DSK6713_init();
    DSK6713_waitusec(2000);
    GPIO_init();
    DSK6713_waitusec(2000);

    // Traitement de Signal
    Codec_Audio_init();
    DSK6713_waitusec(2000);
    getEZWEED_init();
    DSK6713_waitusec(2000);
    initteachEZWEED();
    DSK6713_waitusec(2000);
    *Lock = 0;

    SPI_init();
    DSK6713_waitusec(2000);
    Timer1Init();
    DSK6713_waitusec(2000);

    // Vider buffer à valider!
    MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    DSK6713_waitusec(2000);
    MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    DSK6713_waitusec(2000);

    // Configurer les IO au démarrage
    ALL_LED_OFF();

    Pompe.request = 2;
    Pompe.state = 0;
    DesactiverPompe();

    Lumiere.request = 2;
    Lumiere.state = 0;
    DesactiverLumiere();

    // Check ADC
    ActiveADCHumidite();
    ActiveADCLuminosite();
    DSK6713_waitusec(2000);
    Lumen.value = *(unsigned short*) ADRESSE_ADC_lumen; //READ une donnée de l’ADC
    Humidite.value = *(unsigned short*) ADRESSE_ADC_humidite; //READ une donnée de l’ADC
    sendUART(S);

    while (true)
    {
        /***************************************/
        /*         Section sur le PID          */
        /***************************************/

        if (PIDFlag)
        {
            PIDFlag = 0;

            // Faire une demande de lecture des capteurs du PIC

            pollUART(T);
            //pollUART(H);
            ActiveADCLuminosite();
            ActiveADCHumidite();

            // Faire les actions conséquentes

            // Condition sur les volets
            if (humidite > 700 || Humidite.value > 700 || temperature > 250)
            {
                volet = 1;
                sendUART(V);

            }
            // Condition sur les
            if (humidite < 300 || Humidite.value < 300 || temperature < 250)
            {
                Lumiere.request = 1;
            }

        }


        /***************************************/
        /* Section sur le traitement de signal */
        /***************************************/

        if (DSK6713_DIP_get(0) == 0)
        {
            teachEZWEED();
        }
        else
        {
            getEZWEED();
        }

        /***************************************/
        /*   Section sur la communication SPI  */
        /***************************************/
        mainCounter++;
        if(mainCounter == time){
            lire_MCBSP();
        }
        if(FlagSPI == 1)
        {
            time = mainCounter;
            lire_MCBSP();
            FlagSPI = 0;    // Reset Flag à 0
        }
        readRXData();

        /*****************************************/
        /* Section sur l'écriture des actuateurs */
        /*****************************************/

        // Pompe eau
        if (Pompe.request == 1)
        {
            ActiverPompe();
            Pompe.state = 1;
            Pompe.request = 2;
            //Pompe.request = 0;
        }
        if (Pompe.request == 0)
        {
            DesactiverPompe();
            Pompe.state = 0;
            Pompe.request = 2;
        }

        // Lampe UV
        if (Lumiere.request == 1)
        {
            ActiverLumiere();
            Lumiere.state = 1;
            Lumiere.request = 2;
        }
        if (Lumiere.request == 0)
        {
            DesactiverLumiere();
            Lumiere.state = 0;
            Lumiere.request = 2;
        }
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
        case L:{
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
            if(Pompe.request == 1){
                Pompe.request = 0;
            }
            else if(Pompe.request == 0){
                Pompe.request = 1;
            }
            break;}
        case B:{
            break;}
        case E:{
            break;}
        case H:{
            humidite = byte1 << 8;
            humidite = humidite | byte2;
            break;}
        case L:{
            if(Lumiere.request == 1){
                Lumiere.request = 0;
            }
            else if(Lumiere.request == 0){
                Lumiere.request = 1;
            }
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
            ecrire_MCBSP(Lumen.value >> 8);
            ecrire_MCBSP(Lumen.value & 0x00FF);
            ecrire_MCBSP(0x00);
            break;}
        case H:{
            break;}
        case L:{
            /*ecrire_MCBSP(0x55);
            ecrire_MCBSP(0x55);
            ecrire_MCBSP(L);
            ecrire_MCBSP(0);
            ecrire_MCBSP(Lumiere.state);
            ecrire_MCBSP(0x00);*/
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
            ecrire_MCBSP(Humidite.value >> 8);
            ecrire_MCBSP(Humidite.value & 0x00FF);
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



