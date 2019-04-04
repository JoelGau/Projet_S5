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
#include "DSPF_sp_cfftr4_dif.h"

#define IDLE 0
#define COMPUTING 1
#define RESULT 2
#define F0MIN 200
#define F0MAX 250

const float ACCEPTABILITE = 0.4;
const float SEUIL_HAUT = 0.1;
const float SEUIL_BAS = 0.01;

int Freq_norm_index;
int stateget;
int CompteF0 = 0;
int CompteTotal =0;

extern int *Lock;
extern short *x_fn;
short X;
short loc;

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
    for (i = 0; i < 2*LONGUEUR_TRAME; i=+2)
    {
        if (mag[i] > amp)
        {
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
        echLineIn = (short) input;
        pEnveloppe = direct1FIR_ASM(pEnveloppe,echLineIn, CoeffsFIR, &echLineInFilt);
        FlagEnveloppe = 0;
    }

    if(*Lock == 1) // La trame est prête à être utilisée
    {
        if(stateget == IDLE){
            // Détection de seuil
            if(max(Enveloppe)>SEUIL_HAUT){
                stateget = COMPUTING;
            }
        }
        if(stateget == COMPUTING){
            // Detection de fin
            if(max(Enveloppe)<SEUIL_BAS){
                stateget = RESULT;
            }

            int a;
            //Fenetrage
            //x_hm = F_hm'.*x_fn;
            for(a=0; a < LONGUEUR_TRAME; a++){
                x_fn[a] = hamming[a]*x_fn[a];
            }

            // Ajoute la partie imaginaire au signal d entree

            for (a=0;a<LONGUEUR_TRAME; a++)
            {
                X_fn[2*a] = x_fn[a];
                X_fn[2*a+1] = 0;
            }

            //X = fft(x_fn);
            DSPF_sp_cfftr4_dif(X_fn, w,LONGUEUR_TRAME);

            // Bit rev
            DSPF_sp_bitrev_cplx((double*) X_fn, L, LONGUEUR_TRAME);

            for (j=0;j<LONGUEUR_TRAME; j++)
            {
                X_fn[2*j] = (X_fn[2*j]*X_fn[2*j])+(X_fn[2*j+1]*X_fn[2*j+1]);
                X_fn[2*j+1] = 0;
            }

            index_peak = findPeaks(X_fn);

            Freq_norm_index = (index_peak/2)*FS;

            if(Freq_norm_index > F0MIN && Freq_norm_index < F0MAX)
            {
                CompteF0++;
            }
            CompteTotal++;

            *Lock = 0;

        }

        if(stateget == RESULT){
            if((CompteF0/CompteTotal)>ACCEPTABILITE){
                printf("Vous avez dit EZWEED");
            }
            else{
                printf("....");
            }
            stateget = IDLE;
        }
    }
}

