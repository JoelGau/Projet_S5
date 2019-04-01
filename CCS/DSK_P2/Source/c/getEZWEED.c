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
int ComputingTrame;
int n

Uint16 inputsource = DSK6713_AIC23_INPUT_MIC; //select input

extern far void vectors();   // Vecteurs d'interruption

void getEZWEED_Audio_init(void){

    comm_intr(DSK6713_AIC23_FREQ_16KHZ,inputsource);
    return;
}

void getEZWEED_init(){

    state = IDLE;
    CompteF0 = 0;
    CompteTotal = 0;
    ComputingTrame = 0;
}

interrupt void intAIC(void){

    n = 0;

    Enregistrement = input_sample();

    if(Enregistrement > LONGUEUR_TRAME){

        if(ComputingTrame == 0){

            x_fn = Enregistrement;
            ComputingTrame = 1;         // La trame enregistrer est prête à être envoyé
        }

    }
}

