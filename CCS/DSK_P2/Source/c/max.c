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
    int test = x[0];

    for(i; i < 64; i++){

        echantillon = x[i];

        if(echantillon > test){
            test = echantillon;
        }
    }

    return test;
}
