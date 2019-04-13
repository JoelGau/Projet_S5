/*
 * teachEZWEED.c
 *
 *  Created on: 1 avr. 2019
 *      Author: jgaud
 */

#include "teachEZWEED.h"
#include "CONSTANTES.h"
#include "CorrelationCroisee.h"

#define TRESHOLD 6

extern int* Lock;
extern int *x_fn;             // pointeur vers l'échantillon lue

int F0;
int F0max;
int F0min;
int moyF0;
short compteF;

int CORR[LONGUEUR_TRAME];

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

    for (i=LONGUEUR_TRAME-1; i>=0; i--)
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
                FirstPeak = i + 1;
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
               amp_max = 0;
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
                SecondPeak = i + 1;
                break;
            }
        }
    }
    return FS/(FirstPeak - SecondPeak); // On retourne la F0 (fréquence réelle, pas normalisée)
}

void initteachEZWEED()
{
    moyF0 = 0;
    compteF = 0;
}

void teachEZWEED()
{
    if (*Lock == 1)
    {
        AutoCorrelation((int*) x_fn, CORR);
        // Incrémente la moyenne et le compte
        moyF0 = moyF0 + getF0(CORR);
        compteF++;
        *Lock = 0;
        if (compteF >= 50)
        {
            F0 = concludeEZWEED();
            F0max = F0 + F0/TRESHOLD;
            F0min = F0 - F0/TRESHOLD;
        }
    }
}

int concludeEZWEED()
{
    int LaF0 = moyF0/compteF;
    moyF0 = 0;
    compteF = 0;
    return LaF0;
}


