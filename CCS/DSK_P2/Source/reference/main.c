/*
 * main.c
 */
//Définition des états de l'enregistreuse
#define PENDING 0
#define INITIALIZING 1
#define SAMPLING 2
#define RECORDING 3
#define PENDING2 4
#define PLAYING 5

unsigned int State;

//Définition des masques et des adresses utiles pour l'APP
#define CPLD_USER_REG 0x90080000
#define MASK_LED0 0x01
#define MASK_LED1 0x02
#define MASK_LED2 0x04
#define MASK_DIP0 0x10
#define MASK_DIP1 0x20
#define MASK_DIP2 0x40
#define MASK_DIP3 0x80
#define CTL_TIMER1 0x01980000
#define PRD_TIMER1 0x01980004
#define MASK_HLDT1 0x0080
#define MUXL 0x019C0004

//Définition de la durée maximale d'enregistrement et de lecture
#define MAX 160000
#define PLAYBACK_TIMER_MAX 0x27100

//Initialisation du buffer contenant les données numérisées par l'ADC
short buffer[MAX];
long int moyenne = 0;
unsigned int i = 0;
#pragma DATA_SECTION(buffer,".EXT_RAM") // Buffer dans la SDRAM

//Initialisation des DIP switches
unsigned short DIP0 = 0;
unsigned short DIP1 = 0;
unsigned short DIP2 = 0;
unsigned short DIP3 = 0;

//Initialisation des variables utiles à la lecture
unsigned int playback_en_cours = 0;
unsigned int playback_timer = 0;
unsigned int fs=2;

//Initialisation du gain
unsigned short gain = 10;

#include <stdio.h>
#include "assembleur.h"
#include "general.h"
#include "Enregistrement.h"
#include "LectureAudio.h"
#include <math.h>

void main(void)
{
    //Initialisation du DSK
    comm_intr();

    //On éteint les LEDs 0 et 1
    *(unsigned int*) CPLD_USER_REG &= ~MASK_LED0;
    *(unsigned int*) CPLD_USER_REG &= ~MASK_LED1;
    State = PENDING;

    //On active le GIE et on configure le timer 1
    enableInterrupts();
    configAndStartTimer1();

    //Initialisation de l'enregistrement
    init_enregistrement();

    //On désactive l'interruption sur int11 (Lecture impossible sinon)
    disableInterrupts_int11();

    while(1)
    {
        //Lectures des états des DIPs switches
        DIP0 = readStatusDIP0();
        DIP1 = readStatusDIP1();

        switch (State)
        {
            case PENDING: // En attente de l'utilisateur
                if (DIP0==1)
                {
                    State = INITIALIZING;
                }
                else if (DIP1 == 1)
                {
                    State = PLAYING;
                }
                break;

            case INITIALIZING: // initialisation des interruptions
                enableInterrupts_T1(); // Interruption LED 0
                enableInterrupts_T0(); // Interruption Ping ADC
                enableInterrupts_int4(); // Interruption Lecture ADC
                i = 0;
                moyenne = 0;
                State = SAMPLING;
                break;

            case SAMPLING: // Recueillir l'échantillon de start et l'analyser
                *(unsigned int*) CPLD_USER_REG |= MASK_LED2;
                while (i < 64); // accumulation d'une seconde de data
                if (moyenne/64 >= 400)
                {
                    State = RECORDING;
                    *(unsigned int*) CPLD_USER_REG &= ~MASK_LED2;
                    i = 0;
                }
                else
                {
                    State = INITIALIZING;
                }
                break;

            case RECORDING: // Enregistrement de 10 secondes
                while(i < MAX);
                disableInterrupts_T0(); // Arrêt après une acquisition
                disableInterrupts_T1(); //
                disableInterrupts_int4(); // Interruption Lecture ADC
                *(unsigned int*) CPLD_USER_REG &= ~MASK_LED0;
                State = PENDING2;
                break;

            case PENDING2: // Après enregistrement
                if (DIP1 == 1)
                {
                    State = PLAYING;
                }
                else if (DIP0 == 0)
                {
                    State = PENDING;
                }
                break;

            case PLAYING: // Jouer sur le codec audio
                if (DIP1 == 0)
                {
                    State = PENDING;
                }
                i=0; //Remise à zéro du compteur pour la lecture
                enableInterrupts_int11(); //Interruption int11
                playback_timer = 0; //Remise à zéro du compteur pour l'interruption
                playback_en_cours = 1; //Activation de la lecture
                *(unsigned int*) CPLD_USER_REG |= MASK_LED1; //Allume la LED1
                while(i < MAX) //Permet d'attendre la fin de la lecture
                {
                    //Lecture de l'état des DIP switches pour le réglage du gain numérique
                    DIP2 = readStatusDIP2();
                    DIP3 = readStatusDIP3();
                    if (DIP2==0 && DIP3==0)
                    {
                        gain=0;
                    }
                    if (DIP2==1 && DIP3==0)
                    {
                        gain=10;
                    }
                    if (DIP2==0 && DIP3==1)
                    {
                        gain=20;
                    }
                    if (DIP2==1 && DIP3==1)
                    {
                        gain=30;
                    }
                }
                disableInterrupts_int11(); //Désactivation de l'interruption 11
                *(unsigned int*) CPLD_USER_REG &= ~MASK_LED1; //Eteint la LED1
                break;

        }
    }
}
