/*
 * main.c
 */

#include <stdio.h>
#include <math.h>
#include "CorrelationCroisee.h"

int Signal1[LONGUEURTRAME] = {1,1,1,1,0,0,0,0,0,0};
int Signal2[LONGUEURTRAME] = {1,1,1,1,0,0,0,0,0,1};

#pragma DATA_SECTION(Signal1,".EXT_RAM")
#pragma DATA_SECTION(Signal2,".EXT_RAM")

void main(void)
{

    int *Corr;
    Corr = CorrelationCroisee(Signal1, 10, Signal2, 10);

    int bidon = 0;
    bidon = 4;

}
