/*
 * max.c
 *
 *  Created on: 1 avr. 2019
 *      Author: stjn1901
 */

#include <stdio.h>
//#include <math.h>
#include "CONSTANTES.h" // Constantes partagées
#include "C6713Helper_UdeS.h"


short max(short* x){

    int i = 1;
    int echantillon;
    int test;

    for(i; i < LONGUEUR_TRAME; i++){

        echantillon = x[i];

        if(echantillon > x[i-1]){
            test = echantillon;
        }
    }

    return test;
}
