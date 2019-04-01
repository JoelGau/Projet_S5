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

#define IDLE 0
#define COMPUTING 1
#define RESULT 2
#define F0MIN 20
#define F0MAX 25

const float ACCEPTABILITE = 0.4;
const float SEUIL_HAUT = 0.1;
const float SEUIL_BAS = 0.01;

int state;
int CompteF0;
int CompteTotal;
int ComputingTrame;             // = 0 -> compute rien, = 1 -> compute trame 1, = 2 -> compute trame 2
int n;                          // Index pour les buffers
short Buffer1[LONGUEUR_TRAME];    // Buffer 1
short Buffer2[LONGUEUR_TRAME];    // Buffer 2
short Butch[LONGUEUR_TRAME];      // Buffer pour les donnees non-utiles
short *Enregistrement;            // Pointeur pour les buffers
short *x_fn;


short echLineIn;               // Ampliutde de l'échantillon provenant de l'entrée LINE IN
short echLineInFilt;           // Ampliutde de l'échantillon filtré

#pragma DATA_ALIGN(Enveloppe, LONGUEUR_TRAME*2);    // Requis pour l'adressage circulaire en assembleur

short Enveloppe[LONGUEUR_TRAME]={0};                // Tampon d'échantillons
short *pEnveloppe=&Enveloppe[LONGUEUR_TRAME-1];     // Pointeur sur l'échantillon courant

Uint16 inputsource = DSK6713_AIC23_INPUT_MIC; //select input

extern far void vectors();   // Vecteurs d'interruption

void getEZWEED(void){
    // Détection de seuil
    if(state == IDLE){
        pEnveloppe = direct1FIR_ASM(pEnveloppe,echLineIn, CoeffsFIR, &echLineInFilt);

    if(max(&echLineInFilt)>SEUIL){
        state = COMPUTING;
        }
    }
    // Detection de fin
    if(state == COMPUTING){
        pEnveloppe = direct1FIR_ASM(pEnveloppe,echLineIn, CoeffsFIR, &echLineInFilt);

    if(max(&echLineInFilt)<SEUIL){
            state = RESULT;
        }
    }

    // Trame prête à être utilisée
    if(ComputingTrame == 1){
        int a = 0;
        //Fenetrage
        //x_hm = F_hm'.*x_fn;
        for(a=0; a < LONGUEUR_TRAME; a++){
            x_fn[a] = hamming[a]*x_fn[a];
        }
    }

    return;

}


void getEZWEED_Audio_init(void){

    comm_intr(DSK6713_AIC23_FREQ_16KHZ,DSK6713_AIC23_INPUT_MIC);
}

short findPeaks(short* mag)
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

    state = IDLE;
    n = 0;
    CompteF0 = 0;
    CompteTotal = 0;
    ComputingTrame = 0;
    // On commence par assigner le bon buffer pour l'enregistrement
    Enregistrement = Buffer1;
}

interrupt void c_int11(void){

    // On commence par écrire dans le bon buffer
    Enregistrement[n] = input_right_sample();
    n++;

    if(n >= LONGUEUR_TRAME) // Atteinte de la fin du buffer
    {
        DSK6713_LED_toggle(0);
        if (ComputingTrame == 0) // On est prêt à calculer
        {
            if(Enregistrement == Buffer1)
            {
                ComputingTrame = 1;         // La trame enregistrée est prête à être envoyée
                x_fn = Buffer1;
                Enregistrement = Buffer2;   // On change l'enregistrement d'emplacement
            }
            else if (Enregistrement == Buffer2)
            {
                ComputingTrame = 2;         // La trame enregistrée est prête à être envoyée
                x_fn = Buffer2;
                Enregistrement = Buffer1;   // On change l'enregistrement d'emplacement
            }
        }
        else // On est pas prêt à calculer
        {
            Enregistrement = Butch;
        }
        n = 0;
    }
    output_sample(0);
}

