/********************************************************
**  Session 5 - APP5 - Téléphonie par DSP
**  Fichier Audio_driver.c
**  Auteurs : <Yehonatan Naidich, Louis Massicotte Morissette, Raphaël Cliche, Simon Vaillancourt >
**  Date : < 12-03-2019 >
********************************************************/

/***************************************************************************
	Include Module Header :
***************************************************************************/

#define AUDIO_DRIVER_MODULE_IMPORT
#include "Audio_driver.h"

/****************************************************************************
	Extern content declaration :
****************************************************************************/
extern far void vectors();   // Vecteurs d'interruption

/****************************************************************************
	Private global variables :
****************************************************************************/
int AIC_flag;
int message_recu;
Uint16 imputsource = 0x0015;

/****************************************************************************
	Public functions :
****************************************************************************/

// Function description here ...
void Audio_init(void)
{
    comm_intr(DSK6713_AIC23_FREQ_8KHZ,imputsource);  // Configurer le AIC
	return;
}

/****************************************************************************
	ISR :
****************************************************************************/

// end of Audio_driver.c
