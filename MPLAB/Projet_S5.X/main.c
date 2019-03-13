/* 
 * File:   main.c
 * Author: labm2830
 *
 * Created on 25 février 2019, 12:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "LCD.h"
#include "keyboard.h"
#include "servo.h"

/*
 * 
 */
unsigned char column = 0;
int cntTimer = 0;
void main()
{
    unsigned char value = 0xFF;
    unsigned char lastValue = 0xFF;
    
    unsigned char KBdata = 0;
    initialisation_LCD();
    clearDisplay();
    
    putStringLCD("      EZ-weed       ");
    
    initialisation_keyboard();
    displayCtrl(1,0,0);
    
    while(true)
    {
        KBdata = PORTE;
        
        value = readKeyboard(KBdata);
        
        if(value != 0xFF && value != lastValue)
        {
            putchLCD(value);
            lastValue = value;
            value = 0xFF;
            cntTimer = 0;
        }
        if(cntTimer > 16)
            lastValue = 0xFF;
    }
}

void __interrupt mux_keyboard(void)
{
    if(INTCONbits.TMR0IF == 1)
    {
        column = mux(column, PORTE);
        cntTimer++;
        INTCONbits.TMR0IF = 0;
    }
}

