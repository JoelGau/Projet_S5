/*
 * CorrelationCroisee.h
 *
 *  Created on: 24 févr. 2019
 *     Authors: jgaud
 */

#ifndef SOURCE_C_CORRELATIONCROISEE_H_
#define SOURCE_C_CORRELATIONCROISEE_H_

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

int* CorrelationCroisee(int* x1, int Longueur1, int* x2, int Longueur2)
{
    int i;
    int Kmin1, Kmax1, Kmin2, Kmax2;
    int LongueurS;

    // Ajout de zéros pour compler les espaces manquants
    // On détermine aussi la longueur du signal de sortie
    if (Longueur1 > Longueur2)
    {
        for (i = Longueur2; i <= Longueur1; i++)
        {
            x2[i] = 0;
        }
        LongueurS = Longueur1*2-1;
    }
    else if (Longueur1 < Longueur2)
    {
        for (i = Longueur1; i <= Longueur2; i++)
        {
            x1[i] = 0;
        }
        LongueurS = Longueur2*2-1;
    }
    else
    {
        LongueurS = Longueur1*2-1;
    }
    int C[LongueurS];
    // On assigne les index de débuts pour les 2 signaux

    Kmin1 = 1;
    Kmax1 = 1;

    Kmin2 = LongueurS/2;
    Kmax = Kmin2;

    for (i = 0; i < LongueurS; i++)
    {
        newx1 = &x1[Kmin1];
        newx2 = &x2[Kmin2];

        C[i] = Sum(newx1,newx2,Kmin1-Kmax1);

        if(i < LongueurS/2)
        {
            Kmax1 = Kmax1 + 1;
            Kmin2 = Kmin2 - 1;
        }
        else if (i >= LongueurS/2)
        {
            Kmin1 = Kmin1 + 1;
            Kmax2 = Kmax2 - 1;
        }
    }


}



#endif /* SOURCE_C_CORRELATIONCROISEE_H_ */
