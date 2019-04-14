/*
 * getEZWEED.c
 *
 *  Created on: 30 mars 2019
 *      Author: stjn1901
 */

#include <stdio.h>
#include <math.h>
#include "getEZWEED.h"
#include "CONSTANTES.h" // Constantes partagées
#include "C6713Helper_UdeS.h"
#include "direct1FIRcoeffs11.dat"
#include "direct1FIR_ASM.h"
#include "max.h"
#include "DSK6713_LED.h"
#include "hamming.dat"
#include "twiddle.h"
#include "DSPF_sp_bitrev_cplx.h"
#include "DSPF_sp_cfftr2_dit.h"
#include "DSPF_sp_fir_gen.h"
#include "DSK6713_LED.h"


#define IDLE 0
#define COMPUTING 1
#define RESULT 2
#define SEUIL_HAUT 5000
#define SEUIL_BAS 2000

const float ACCEPTABILITE = 0.4;


int Freq_norm_index;
int stateget;
int CompteF0 = 0;
int CompteTotal =0;

extern int *Lock;
extern int *x_fn;
extern int F0max;
extern int F0min;
short X;
short loc;
short max_enveloppe;
/***************************************************************************************************/
/* Variables globales propres au filtre FIR pour générer l'enveloppe                               */
/***************************************************************************************************/
extern int FlagEnveloppe;
extern int input;

short echLineIn;               // Ampliutde de l'échantillon provenant de l'entrée LINE IN
short echLineInFilt;           // Ampliutde de l'échantillon filtré

#define TAMPON_L  64
short Enveloppe[TAMPON_L]={0};                // Tampon d'échantillons
#pragma DATA_ALIGN(Enveloppe, TAMPON_L*2);    // Requis pour l'adressage circulaire en assembleur
short *pEnveloppe=&Enveloppe[TAMPON_L-1];     // Pointeur sur l'échantillon courant
/***************************************************************************************************/

/***************************************************************************************************/

extern far void vectors();   // Vecteurs d'interruption

// Variables globales FFT
// w = twiddle (1024 coefficients)
#pragma DATA_ALIGN(L, 8);
short L[32];

#pragma DATA_ALIGN(X_fn, 8);
float X_fn[2*LONGUEUR_TRAME];

float findPeaks(float * mag)
{
    // Cette fonction prend en entrée un tableau de 2048 échantillons
    // Elle retourne l'index de la valeur la plus haute du tableau
    int i;
    int amp = 0;
    int index = 0;
    for (i = 0; i < LONGUEUR_TRAME/8; i=i+2)
    {
        if (mag[i] > amp)
        {
            amp = mag[i];
            index = i;
        }
    }
    return index;
}

void getEZWEED_init(){

    stateget = IDLE;
    CompteF0 = 0;
    CompteTotal = 0;
    bitrev_index(L, LONGUEUR_TRAME);

    echLineInFilt = 0;
}

void getEZWEED(void){
    int index_peak;
    int j = 0;


    // Calculer la prochaine sortie de l'enveloppe
    if (FlagEnveloppe == 1)
    {
        echLineIn = abs((short) input);
        pEnveloppe = direct1FIR_ASM(pEnveloppe,abs(echLineIn), CoeffsFIR, &echLineInFilt);
        FlagEnveloppe = 0;
    }

    if(*Lock == 1) // La trame est prête à être utilisée
    {
        max_enveloppe = max(Enveloppe);

        if(stateget == IDLE){
            // Détection de seuil
            if(max_enveloppe>SEUIL_HAUT){
                stateget = COMPUTING;
                *Lock = 0;
                DSK6713_LED_off(1);
                DSK6713_LED_off(2);
                DSK6713_LED_on(3);
            }
        }
        if(stateget == COMPUTING){
            // Detection de fin

            if(max_enveloppe<SEUIL_BAS){
                stateget = RESULT;
                DSK6713_LED_off(1);
                DSK6713_LED_on(2);
                DSK6713_LED_off(3);
            }
            int a;
            //Fenetrage
            //x_hm = F_hm'.*x_fn;
            // Ajoute la partie imaginaire au signal d entree

            for (a=0;a<LONGUEUR_TRAME; a++)
            {
                X_fn[2*a] = hamming[a]*(float)x_fn[a];
                X_fn[2*a+1] = 0;
            }

            //X = fft(x_fn);
            DSPF_sp_cfftr2_dit(X_fn, w,LONGUEUR_TRAME);

            // Bit rev
            DSPF_sp_bitrev_cplx((double*) X_fn, L, LONGUEUR_TRAME);

            for (j=0;j<LONGUEUR_TRAME; j++)
            {
                X_fn[2*j] = (X_fn[2*j]*X_fn[2*j])+(X_fn[2*j+1]*X_fn[2*j+1]);
                X_fn[2*j+1] = 0;
            }

            index_peak = findPeaks(X_fn);
            Freq_norm_index = (index_peak*FS/2)/(LONGUEUR_TRAME);

            if(Freq_norm_index > F0min && Freq_norm_index < F0max)
            {
                CompteF0++;
            }
            CompteTotal++;
            *Lock = 0;
        }

        if(stateget == RESULT){
            if (CompteTotal != 0){
                if((CompteF0/CompteTotal)>ACCEPTABILITE){

                }
            }
            else{

            }
            CompteTotal = 0;
            CompteF0 = 0;
            stateget = IDLE;
        }
    }
}

