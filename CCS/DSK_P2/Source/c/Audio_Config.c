/*
 * Audio_Config.c
 *
 *  Created on: 2 avr. 2019
 *      Author: jgaud
 */

#include <stdio.h>
#include <math.h>
#include "CONSTANTES.h"
#include "C6713Helper_UdeS.h"
#include "Audio_Config.h"

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011

extern far void vectors();   // Vecteurs d'interruption

int n;                          // Index pour les buffers
int Buffer1[LONGUEUR_TRAME];    // Buffer 1
int Buffer2[LONGUEUR_TRAME];    // Buffer 1
int *Enregistrement;            // Pointeur pour les buffers
int input;
int *x_fn;

// Flags lecture trame
int Lock1;  // 0 = unlock, 1 = lock;
int Lock2;
int* Lock;

// Flag générer l'enveloppe
int FlagEnveloppe;

void Codec_Audio_init(void){

    n = 0;
    Enregistrement = Buffer1;
    Lock1 = 0;
    Lock2 = 0;
    Lock = &Lock1;
    comm_intr(DSK6713_AIC23_FREQ_16KHZ,DSK6713_AIC23_INPUT_MIC);
}

interrupt void c_int11(void){

    // On commence par écrire dans le bon buffer
    input = input_sample();
    input = input >> 16;
    FlagEnveloppe = 1;
    Enregistrement[n] = input;
    //output_sample(input);
    n++;

    if(n >= LONGUEUR_TRAME) // Atteinte de la fin du buffer
    {
        DSK6713_LED_toggle(0);
        if (Enregistrement == Buffer1 && Lock2 == 0)
        {
            Lock1 = 1;
            Lock = &Lock1;
            x_fn = Buffer1;

            Enregistrement = Buffer2;
        }
        else if (Enregistrement == Buffer2 && Lock1 == 0)
        {
            Lock2 = 1;
            Lock = &Lock2;
            x_fn = Buffer2;
            Enregistrement = Buffer1;
        }
        n = 0;
    }
    output_sample(0);
}



