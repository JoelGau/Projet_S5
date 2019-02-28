/* 
 * File:   keyboard.h
 * Author: labm2830
 *
 * Created on 25 février 2019, 13:24
 */

#ifndef KEYBOARD_H
#define	KEYBOARD_H

#include <p18f67j94.h>
#include <xc.h>

void initialisation_keyboard(void);
unsigned char readKeyboard(unsigned char);
unsigned char mux(unsigned char, unsigned char);

#define _XTAL_FREQ 8000000


#endif	/* KEYBOARD_H */

