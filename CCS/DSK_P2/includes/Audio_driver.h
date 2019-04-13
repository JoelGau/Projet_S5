/********************************************************
**  Session 5 - APP6 - Téléphonie par DSP
**  Fichier Audio_driver.h
**  Auteurs : < vos noms >
**  Date : < derniere modification >
********************************************************/

#pragma once
#ifndef _AUDIO_MODULE_
#define _AUDIO_MODULE_

/***************************************************************************
	Include headers :
***************************************************************************/


// standard libraries 
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition
#include <dsk6713.h>
#include "dsk6713_aic23.h"
#include "C6713Helper_UdeS.h"
#include <dsk6713_led.h>
#include <dsk6713_dip.h>


// #include "something.h"

/***************************************************************************
	Set EXTERN macro :
***************************************************************************/

#ifdef AUDIO_DRIVER_MODULE_IMPORT
	#define EXTERN  
#else 
	#define EXTERN extern
#endif


/***************************************************************************
	Global variables declaration :
***************************************************************************/

// look at example for EXTERN pattern


extern int message_envoyer;

/***************************************************************************		
	Function prototype :
***************************************************************************/

// Function description here ...
EXTERN void Audio_init(void);
void AIC_read();
void AIC_whrite();
extern far unsigned char int2ulaw(short);
extern int ulaw2int(unsigned char);
// ajoutez vos prototype de fonction ici

#undef AUDIO_DRIVER_MODULE_IMPORT

#undef EXTERN

#endif // end of #ifndef _AUDIO_MODULE_

// end of Audio_driver.h
