/*
 * teachEZWEED.c
 *
 *  Created on: 1 avr. 2019
 *      Author: jgaud
 */

#include "teachEZWEED.h"
#include "CONSTANTES.h"


int getF0(int* autocorr)
{
    // Les autres inputs sont des constantes:
    // LONGUEUR_TRAME
    // FS

    // Initialisation
    int i = 0;
    int amp_max = 0;
    int state = FIRST_MAX;
    short FirstPeak = 0, SecondPeak = 0;

    for (i=0; i<LONGUEUR_TRAME; i++)
    {
        if (state == FIRST_MAX)
        {
            // Trouver le premier maximum
            if (autocorr[i] > amp_max)
            {
                amp_max = autocorr[i];
            }
            else
            {
                FirstPeak = i - 1;
                state = FIRST_ZERO;
            }
        }
        else if (state == FIRST_ZERO)
        {
            // Passer en dessous de zero
            if (autocorr[i] < 0)
            {
               state = SECOND_ZERO;
            }
        }
        else if (state == SECOND_ZERO)
        {
            // Passer au dessus de zero
            if (autocorr[i] > 0)
            {
               state = SECOND_MAX;
            }
        }
        else if (state == SECOND_MAX)
        {
            // Trouver le premier maximum
            if (autocorr[i] > amp_max)
            {
                amp_max = autocorr[i];
            }
            else
            {
                SecondPeak = i - 1;
                break;
            }
        }
    }
    return FS/(SecondPeak - FirstPeak); // On retourne la F0 (fréquence réelle, pas normalisée)
}

void teachEZWEED()
{

}


