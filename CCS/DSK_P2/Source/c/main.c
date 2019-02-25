/*
 * main.c
 *
 *  Created on: 25 févr. 2019
 *      Author: jgaud
 */
#include <stdio.h>
#include <math.h>

#define MASK_LED3 0x08
#define MASK_LED2 0x04
#define MASK_LED0 0x01
#define MASK_LED1 0x02

#define CPLD_USER_REG 0x90080000
void En_Attente ();
void LED_1_ON();

void LED0_ON()
{
    *(unsigned int*)CPLD_USER_REG |= MASK_LED0;
}

void LED0_OFF()
{
    *(unsigned int*)CPLD_USER_REG &= ~MASK_LED0;
}

void LED1_ON()
{
    *(unsigned int*)CPLD_USER_REG |= MASK_LED1;
}

void LED1_OFF()
{
    *(unsigned int*)CPLD_USER_REG &= ~MASK_LED1;
}

void LED2_ON()
{
    *(unsigned int*)CPLD_USER_REG |= MASK_LED2;
}

void LED2_OFF()
{
    *(unsigned int*)CPLD_USER_REG &= ~MASK_LED2;
}

void LED3_ON()
{
    *(unsigned int*)CPLD_USER_REG |= MASK_LED3;
}

void LED3_OFF()
{
    *(unsigned int*)CPLD_USER_REG &= ~MASK_LED3;
}

void ALL_LED_OFF()
{
    LED0_OFF();
    LED1_OFF();
    LED2_OFF();
    LED3_OFF();
}

void En_Attente (){
    LED0_ON();
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
            LED1_ON();
            cinqsecondes();
            // Implémentation de l'enregistrement


            LED1_OFF();
        }
        // Activation de la comparaison avec la DIP switch 1
                else if(((*(unsigned int*)CPLD_USER_REG) & 0x20) == 0x00)
                {
                    ALL_LED_OFF();
                    // Implémentation de la comparaison

                   if(Bidon_index_correlation == 0){
                       LED2_ON();
                       cinqsecondes();
                       LED2_OFF();
                   }
                   else{
                       LED3_ON();
                       cinqsecondes();
                       LED3_OFF();
                   }
                }
    }

}




