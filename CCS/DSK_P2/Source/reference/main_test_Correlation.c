/*
 * main.c
 */

#include <stdio.h>
#include <math.h>
#include "CorrelationCroisee.h"

int Signal1[LONGUEURTRAME] = {1,0,1,0};
int Signal2[LONGUEURTRAME] = {0,1,1,0};

#pragma DATA_SECTION(Signal1,".EXT_RAM")
#pragma DATA_SECTION(Signal2,".EXT_RAM")

void main(void)
{

    int *Corr;
    Corr = CorrelationCroisee(Signal2, 4, Signal1, 4);

    int bidon = 0;
    bidon = 4;

}
