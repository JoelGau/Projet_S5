/*
 * Enregistrement.h
 *
 *  Created on: 4 févr. 2019
 *      Author: jgaud
 */

#ifndef ENREGISTREMENT_H_
#define ENREGISTREMENT_H_

#define CTL_TIMER0 0x01940000
#define PRD_TIMER0 0x01940004
#define MASK_HLDT0 0x0080

#define GPEN_REG_GPIO 0x01B00000
#define GPDIR_REG_GPIO 0x01B00004
#define GPPOL_REG_GPIO 0x01B00024

#define ADDRESS_ADC 0xB0380000

void configAndStartTimer1(void)
{
    *(unsigned int*) CTL_TIMER1 &= ~MASK_HLDT1; // Étape 1 mettre HLD = 0
    *(unsigned int*) PRD_TIMER1 = 2812500; // fréquence de 10 Hz
    *(unsigned int*) CTL_TIMER1 |= 0x00000303; // Étape 3
    *(unsigned int*) CTL_TIMER1 |= 0x000000C0; // Étape 4
}

interrupt void interruptionLED(void)
{
    *(unsigned int*) CPLD_USER_REG ^= MASK_LED0; // flash la LED0
}

void configAndStartTimer0_16kHz(void)
{
    *(unsigned int*) CTL_TIMER0 &= ~MASK_HLDT0; // Étape 1 mettre HLD = 0
    *(unsigned int*) PRD_TIMER0 = 1758; // Étape 2 mettre frequence de 16kHz
    *(unsigned int*) CTL_TIMER0 |= 0x00000303; // Étape 3
    *(unsigned int*) CTL_TIMER0 |= 0x000000C0; // Étape 4
}
void configInterruptEXTInt4(void)
{
    *(unsigned int*) GPEN_REG_GPIO = (*(unsigned int*) GPEN_REG_GPIO) | 0x00000010; // Active GP4 commme I/0
    *(unsigned int*) GPDIR_REG_GPIO = (*(unsigned int*) GPDIR_REG_GPIO) & 0xFFFFFFEF; // Set GP4 comme input
    *(unsigned int*) GPPOL_REG_GPIO = (*(unsigned int*) GPPOL_REG_GPIO) | 0x00000010; // Set GP4 en front descendant

}

void init_enregistrement(void)
{
    configAndStartTimer0_16kHz();
    configInterruptEXTInt4();
}

interrupt void echantillonageADC(void)
{
    //On veut ping l'ADC pour lui dire de préparer une lecture
    *(unsigned int*) ADDRESS_ADC = 0x00;
}

interrupt void lectureADC(void)
{
    //On veut lire la valeur de l'ADC et enregistrer dans la SDRAM
    buffer[i] = *(unsigned int*) ADDRESS_ADC;
    if (State == SAMPLING)
    {
        moyenne = moyenne + fabs(buffer[i]-512); // détecteur d'enveloppe
    }
    i++;
}



#endif /* ENREGISTREMENT_H_ */
