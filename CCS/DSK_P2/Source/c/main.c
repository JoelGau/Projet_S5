/*
 * main.c
 *
 *  Created on: 25 févr. 2019
 *      Author: jgaud
 */
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <dsk6713.h>
#include <dsk6713_dip.h>
#include <dsk6713_led.h>

#include "CorrelationCroisee.h"

#define ATTENTE 0
#define ORTHO 1
#define AUTO 2
#define COMPUTING 3
#define AUTRE 4

int State = ATTENTE;

int Sref[LONGUEURTRAME] = {1,2,3,4,5,5,4,3,2,1};
int Sort[LONGUEURTRAME] = {0,0,0,0,0,0,0,0,0,0};
int Scus[LONGUEURTRAME] = {-1,0,1,0,-1,0,1,0,-1,0};

void ALL_LED_OFF()
{
    DSK6713_LED_off(0);
    DSK6713_LED_off(1);
    DSK6713_LED_off(2);
    DSK6713_LED_off(3);
}
void ALL_LED_ON()
{
    DSK6713_LED_on(0);
    DSK6713_LED_on(1);
    DSK6713_LED_on(2);
    DSK6713_LED_on(3);
}


int main(void)
{
    // Ce main est seulement pour la démo 1
    int i = 0;
    int Corr[LONGUEURTRAME*2-1];
    bool dip0, dip1, dip2, dip3;
    ALL_LED_OFF();
    while (true)
    {
        dip0 = DSK6713_DIP_get(0);
        dip1 = DSK6713_DIP_get(1);
        dip2 = DSK6713_DIP_get(2);
        dip3 = DSK6713_DIP_get(3);

        switch (State)
        {
            case ATTENTE:
                DSK6713_LED_on(0);
                if (dip1)
                {
                    CorrelationCroisee(Sort, LONGUEURTRAME, Sref, LONGUEURTRAME, Corr);
                    State = COMPUTING;
                    DSK6713_LED_off(0);
                }
                else if (dip2)
                {
                    CorrelationCroisee(Sref, LONGUEURTRAME, Sref, LONGUEURTRAME, Corr);
                    State = COMPUTING;
                    DSK6713_LED_off(0);
                }
                else if (dip3)
                {
                    CorrelationCroisee(Scus, LONGUEURTRAME, Sref, LONGUEURTRAME, Corr);
                    State = COMPUTING;
                    DSK6713_LED_off(0);
                }
                break;
            case COMPUTING:
                if (AdditionInt(Corr, LONGUEURTRAME*2-1) == 0)
                {
                    State = ORTHO;
                }
                else if (AdditionInt(Corr, LONGUEURTRAME*2-1) == 900)
                {
                    State = AUTO;
                }
                else
                {
                    State = AUTRE;
                }
                break;
            case ORTHO:
                DSK6713_LED_on(1);
                DSK6713_waitusec(5000000);
                DSK6713_LED_off(1);
                State = ATTENTE;
                break;
            case AUTO:
                DSK6713_LED_on(2);
                DSK6713_waitusec(5000000);
                DSK6713_LED_off(2);
                State = ATTENTE;
                break;
            case AUTRE:
                i = 0;
                while(i<10)
                {
                    ALL_LED_OFF();
                    DSK6713_wait(2500000);
                    ALL_LED_ON();
                    DSK6713_wait(2500000);
                    i++;
                }
                ALL_LED_OFF();
                State = ATTENTE;
                break;
            default:
                return 1;
        }
    }

}




