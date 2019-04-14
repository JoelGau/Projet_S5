/*
 * CorrelationCroisee.h
 *
 *  Created on: 24 f�vr. 2019
 *     Authors: jgaud, mstpi
 */

#ifndef SOURCE_C_CORRELATIONCROISEE_H_
#define SOURCE_C_CORRELATIONCROISEE_H_

#include "CONSTANTES.h"

int SumASM(int* Tableau1, int* Tableau2, int Longueur);

int Sum(int* Tableau1, int* Tableau2, int Longueur)
{
    int i;
    int Sum = 0;
    for (i = 0; i < Longueur; i++)
    {
        Sum = Sum + Tableau1[i] * Tableau2[i];
    }
    return Sum;
}

float SumFloat(float* Tableau1, float* Tableau2, int Longueur)
{
    int i;
    float Sum = 0.0;
    for (i = 0; i < Longueur; i++)
    {
        Sum = Sum + Tableau1[i] * Tableau2[i];
    }
    return Sum;
}

int CorrelationCroisee(int* x1, int Longueur1, int* x2, int Longueur2, int* CORR)
{
    int i;
    int Kmin1, Kmax1, Kmin2, Kmax2;
    int *newx1, *newx2;

    // Ajout de z�ros pour compler les espaces manquants
    if (Longueur1 > LONGUEUR_TRAME || Longueur2 > LONGUEUR_TRAME)
    {
        // Le signal d'entr�e est plus long que pr�vue
        return 0; //erreur
    }
    if (Longueur2 < LONGUEUR_TRAME)
    {
        for (i = Longueur2; i < LONGUEUR_TRAME; i++)
        {
            x2[i] = 0;
        }
    }
    if (Longueur1 < LONGUEUR_TRAME)
    {
        for (i = Longueur1; i < LONGUEUR_TRAME; i++)
        {
            x1[i] = 0;
        }
    }
    // On assigne les index de d�buts pour les 2 signaux

    Kmin1 = 0;
    Kmax1 = 0;

    Kmin2 = LONGUEUR_TRAME-1;
    Kmax2 = Kmin2;

    for (i = 0; i < LONGUEUR_TRAME*2-1; i++)
    {
        newx1 = &x1[Kmin1];
        newx2 = &x2[Kmin2];

        CORR[i] = SumASM(newx1,newx2,(Kmax1-Kmin1+1));

        if(i < (LONGUEUR_TRAME*2-1)/2)
        {
            Kmax1 = Kmax1 + 1;
            Kmin2 = Kmin2 - 1;
        }
        else if (i >= (LONGUEUR_TRAME*2-1)/2)
        {
            Kmin1 = Kmin1 + 1;
            Kmax2 = Kmax2 - 1;
        }
    }
    return 1; //Succ�s

}

int AutoCorrelation(int* x1, int* CORR)
{
    // Cette fonction est bas�e sur CorrelationCroisee. Cependant elle est optimis�e
    // pour faire une autocorrelation. Prendre note qu'elle retourne un tableau de [LONGUEUR_TRAME].
    int i;
    int Kmin1, Kmax1, Kmin2;
    int *newx1, *newx2;

    // On assigne les index de d�buts pour les 2 signaux

    // Pour �viter la saturation
    for (i = 0; i < LONGUEUR_TRAME; i++)
    {
        x1[i] = x1[i] >> 8;
    }

    Kmin1 = 0;
    Kmax1 = 0;

    Kmin2 = LONGUEUR_TRAME-1;

    for (i = 0; i < LONGUEUR_TRAME; i++)
    {
        newx1 = &x1[Kmin1];
        newx2 = &x1[Kmin2];

        CORR[i] = SumASM(newx1,newx2,(Kmax1-Kmin1+1));

        Kmax1 = Kmax1 + 1;
        Kmin2 = Kmin2 - 1;
    }
    return 1; //Succ�s

}
int AutoCorrelationFloat(float* x1, float* CORR)
{
    // Cette fonction est bas�e sur CorrelationCroisee. Cependant elle est optimis�e
    // pour faire une autocorrelation. Prendre note qu'elle retourne un tableau de [LONGUEUR_TRAME].
    int i;
    int Kmin1, Kmax1, Kmin2;
    float *newx1, *newx2;

    // On assigne les index de d�buts pour les 2 signaux

    Kmin1 = 0;
    Kmax1 = 0;

    Kmin2 = LONGUEUR_TRAME-1;

    for (i = 0; i < LONGUEUR_TRAME; i++)
    {
        newx1 = &x1[Kmin1];
        newx2 = &x1[Kmin2];

        CORR[i] = SumFloat(newx1,newx2,(Kmax1-Kmin1+1));

        Kmax1 = Kmax1 + 1;
        Kmin2 = Kmin2 - 1;
    }
    return 1; //Succ�s

}

int AdditionInt(int* x1, int longueur)
{
    // Cette fonction retourne la somme du tableau
    int i;
    int Sum = 0;
    for (i = 0; i < longueur; i++)
    {
        Sum = Sum + x1[i];
    }
    return Sum;
}


#endif /* SOURCE_C_CORRELATIONCROISEE_H_ */
