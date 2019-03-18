/*
 * GPIO_driver.h
 *
 *  Created on: 18 mars 2019
 *      Author: louis
 */

#ifndef SOURCE_REFERENCE_GPIO_DRIVER_H_
#define SOURCE_REFERENCE_GPIO_DRIVER_H_

/***************************************************************************
    Include headers :
***************************************************************************/


// standard libraries
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition


extern int FlagTLC1550;

// Function description here ...
void GPIO_init(void);
void ActiverPompe(void);
void DesactiverPompe(void);
void ActiverLumiere(void);
void DesactiverLumiere(void);

#endif /* SOURCE_REFERENCE_GPIO_DRIVER_H_ */
