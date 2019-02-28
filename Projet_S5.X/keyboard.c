/*
 * File:   keyboard.c
 * Author: MatLab
 *
 * Created on February 25, 2019, 1:26 PM
 */

#include <pic18f67j94.h>

#include "keyboard.h"

void initialisation_keyboard(void)
{
    INTCONbits.GIE = 1;
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0b01;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b101;
    
    INTCONbits.TMR0IE = 1;
    
    TRISE = 0b11110000;
    
    
}

unsigned char readKeyboard(unsigned char E)
{
    unsigned char value;
    switch(E)
    {
        case 0b11101110:
            value = 0x31;
            break;
        case 0b11101101:
            value = 0x32;
            break;
        case 0b11101011:
            value = 0x33;
            break;
        case 0b11100111:
            value = 0x46;
            break;
            
        case 0b11011110:
            value = 0x34;
            break;
        case 0b11011101:
            value = 0x35;
            break;
        case 0b11011011:
            value = 0x36;
            break;
        case 0b11010111:
            value = 0x45;
            break;
            
        case 0b10111110:
            value = 0x37;
            break;
        case 0b10111101:
            value = 0x38;
            break;
        case 0b10111011:
            value = 0x39;
            break;
        case 0b10110111:
            value = 0x44;
            break;
            
        case 0b01111110:
            value = 0x41;
            break;
        case 0b01111101:
            value = 0x30;
            break;
        case 0b01111011:
            value = 0x42;
            break;
        case 0b01110111:
            value = 0x43;
            break;
            
        default:
            value = 0xFF;
            break;
    }
    return value;
}

unsigned char mux(unsigned char col, unsigned char E)
{
    unsigned char temp_low, temp_high;
    switch(col)
    {
        case 0 :
        {
            col = 1;
            break;
        }
        case 1 :
        {
            col = 2;
            break;
        }
        case 2 :
        {
            col = 3;
            break;
        }
        case 3 :
        {
            col = 0;
            break;
        }
    }
    temp_low = ~(0b00000001 << col);
    temp_high = (E & 0b11110000)|0b00001111;
    LATE = temp_high & temp_low;
    return col;
}