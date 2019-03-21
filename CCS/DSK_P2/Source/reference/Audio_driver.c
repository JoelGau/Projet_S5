/********************************************************
**  Session 5 - APP6 - Téléphonie par DSP
**  Fichier Audio_driver.c
**  Auteurs : < vos noms >
**  Date : < derniere modification >
********************************************************/

/***************************************************************************
	Include headers :
***************************************************************************/

//#include "something.h"


/***************************************************************************
	Include Module Header :
***************************************************************************/

#define AUDIO_DRIVER_MODULE_IMPORT
#include "Audio_driver.h"
#include "SPI_driver.h"
#include <dsk6713.h>
#include "C6713Helper_UdeS.h"
#include <dsk6713_aic23.h>

/****************************************************************************
	Extern content declaration :
****************************************************************************/

extern far void vectors();   // Vecteurs d'interruption
extern far unsigned char int2ulaw(short);
extern far unsigned short ulaw2int(char);
/****************************************************************************
	Private macros and constants :
****************************************************************************/


/****************************************************************************
	Private Types :
****************************************************************************/

// These type declaration are only valid in this .c

/****************************************************************************
	Private global variables :
****************************************************************************/
#define DSK6713_AIC23_INPUT_MIC 0x0015

int Son_lu = 0;
int FlagAIC = 0;
// Use static keyword here

/****************************************************************************
	Private functions :
****************************************************************************/

// these function can only be called by this .c
// Use static keyword

/****************************************************************************
	Public functions :
****************************************************************************/

// Function description here ...
void Audio_init(void)
{
    comm_intr(DSK6713_AIC23_FREQ_16KHZ,DSK6713_AIC23_INPUT_MIC); // Configurer l'AIC à 8kHz et l'entrée comme étant le mic
    DSK6713_waitusec(100000); // attendre pour s'assurer que la config de l'AIC se fait correctement
    return;
}

/****************************************************************************
	ISR :
****************************************************************************/

interrupt void intAIC(void)
{
    Son_lu = input_sample();
    FlagAIC = 1;
}

// end of Audio_driver.c
