/*
 * main.c
 *
 *  Created on: 25 févr. 2019
 *      Author: jgaud
 */
#include <stdio.h>
#include <math.h>
#include <dsk6713.h>

#define CPLD_USER_REG 0x90080000

void En_Attente ();
void LED_1_ON();



void ALL_LED_OFF()
{
    DSK6713_LED_off(0);
    DSK6713_LED_off(1);
    DSK6713_LED_off(2);
    DSK6713_LED_off(3);
}

void En_Attente (){
    DSK6713_LED_on(0);
}

void cinqsecondes(){
    int i;
    while(i<100000000)
    {
        i++;
    }
}

void main(void)
{
    int i=0;
    int Bidon_index_correlation =0;
    ALL_LED_OFF();
    while (1){
        En_Attente();
        // Enregistrement du micro en appuyant sur la DIP switch 0
        if(((*(unsigned int*)CPLD_USER_REG) & 0x10) == 0x00)
        {
            ALL_LED_OFF();
            DSK6713_LED_on(1);
            cinqsecondes();
            // Implémentation de l'enregistrement
            DSK6713_LED_off(1);


        }
        // Activation de la comparaison avec la DIP switch 1
                else if(((*(unsigned int*)CPLD_USER_REG) & 0x20) == 0x00)
                {
                    ALL_LED_OFF();
                    // Implémentation de la comparaison

                   if(Bidon_index_correlation == 0){
                       DSK6713_LED_on(2);
                       cinqsecondes();
                       DSK6713_LED_off(2);
                   }
                   else{
                       DSK6713_LED_on(3);
                       cinqsecondes();
                       DSK6713_LED_off(3);
                   }
                }
    }

}




