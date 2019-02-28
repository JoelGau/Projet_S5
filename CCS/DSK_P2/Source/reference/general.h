/*
 * general.h
 *
 *  Created on: 4 févr. 2019
 *      Author: jgaud
 */

#ifndef GENERAL_H_
#define GENERAL_H_

//Fonctions de lecture des état des DIP switches
unsigned short readStatusDIP0(void)
{
    unsigned short DIP_status;
    DIP_status = *(unsigned int *) CPLD_USER_REG;
    DIP_status = DIP_status & MASK_DIP0;
    DIP_status = !(DIP_status >> 3);
    return DIP_status;
}

unsigned short readStatusDIP1(void)
{
    unsigned short DIP_status;
    DIP_status = *(unsigned int *) CPLD_USER_REG;
    DIP_status = DIP_status & MASK_DIP1;
    DIP_status = !(DIP_status >> 4);
    return DIP_status;
}

unsigned short readStatusDIP2(void)
{
    unsigned short DIP_status;
    DIP_status = *(unsigned int *) CPLD_USER_REG;
    DIP_status = DIP_status & MASK_DIP2;
    DIP_status = !(DIP_status >> 5);
    return DIP_status;
}

unsigned short readStatusDIP3(void)
{
    unsigned short DIP_status;
    DIP_status = *(unsigned int *) CPLD_USER_REG;
    DIP_status = DIP_status & MASK_DIP3;
    DIP_status = !(DIP_status >> 6);
    return DIP_status;
}

#endif /* GENERAL_H_ */
