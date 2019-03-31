/********************************************************
**  Session 5 - APP6 - TÈlÈphonie par DSP
**  Fichier SPI_driver.c
**  Auteurs : < vos noms >
**  Date : < derniere modification >
********************************************************/


/***************************************************************************
	Include headers :
***************************************************************************/

//#include "something.h"

#include <csl.h>
#include <csl_gpio.h>
#include <csl_mcbsp.h>
#include <stdio.h>
#include <csl_irq.h>
#include <dsk6713_led.h>
#include <dsk6713_aic23.h>
#include <dsk6713.h>


/***************************************************************************
	Include Module Header :
***************************************************************************/

#define SPI_DRIVER_MODULE_IMPORT
#include "SPI_driver.h"


/****************************************************************************
	Extern content declaration :
****************************************************************************/

extern far void vectors();   // Vecteurs d'interruption
extern int Data_in;
extern int Data_out;

/****************************************************************************
	Private macros and constants :
****************************************************************************/

// These defines are only valid is this .c

//#define something somethingelse

/****************************************************************************
	Private Types :
****************************************************************************/

// These type declaration are only valid in this .c

/****************************************************************************
	Private global variables :
****************************************************************************/

int FlagSPI = 0;

extern MCBSP_Handle DSK6713_AIC23_CONTROLHANDLE;

MCBSP_Config MCBSP0_SPI_Cfg = {
           MCBSP_FMKS(SPCR, FREE, NO)              |
           MCBSP_FMKS(SPCR, SOFT, NO)              |
           MCBSP_FMKS(SPCR, FRST, YES)             | // FSG est g√©n√©r√© par le sample-rate generator (Pas de sortie car le SRG est tenu en reset)
           MCBSP_FMKS(SPCR, GRST, YES)             | // Le sample rate generator est tenu en reset
           MCBSP_FMKS(SPCR, XINTM, XRDY)           | // Mode d'interruption de transmission
           MCBSP_FMKS(SPCR, XSYNCERR, NO)          | // Erreur de synchronisation de transmission
           MCBSP_FMKS(SPCR, XRST, YES)             | // Serial Port Transmitter est d√©sactiv√© et tenu en reset
           MCBSP_FMKS(SPCR, DLB, OFF)              | // Le mode Digital Loop-back est d√©sactiv√©
           MCBSP_FMKS(SPCR, RJUST, RZF)            | // Receive sign extension and justification mode bit
           MCBSP_FMKS(SPCR, CLKSTP, DELAY)         | // Clock stop mode bit (DELAY = clock starts with delay)
           MCBSP_FMKS(SPCR, DXENA, OFF)            | //
           MCBSP_FMKS(SPCR, RINTM, RRDY)           | //
           MCBSP_FMKS(SPCR, RSYNCERR, NO)          | //
           MCBSP_FMKS(SPCR, RRST, YES),              //

           MCBSP_FMKS(RCR, RPHASE, SINGLE)         | // Single phase frame
           MCBSP_FMKS(RCR, RFRLEN2, DEFAULT)       |
           MCBSP_FMKS(RCR, RWDLEN2, DEFAULT)       |
           MCBSP_FMKS(RCR, RCOMPAND, MSB)          |
           MCBSP_FMKS(RCR, RFIG, NO)               |
           MCBSP_FMKS(RCR, RDATDLY, 1BIT)          | // 1 bit delay
           MCBSP_FMKS(RCR, RFRLEN1, OF(0))         | // 1 FRAME
           MCBSP_FMKS(RCR, RWDLEN1, 16BIT)         | // 16 bits per frame
           MCBSP_FMKS(RCR, RWDREVRS, DISABLE),

           MCBSP_FMKS(XCR, XPHASE, SINGLE)         | // 1 Phase
           MCBSP_FMKS(XCR, XFRLEN2, DEFAULT)       |
           MCBSP_FMKS(XCR, XWDLEN2, DEFAULT)       |
           MCBSP_FMKS(XCR, XCOMPAND, MSB)          |
           MCBSP_FMKS(XCR, XFIG, NO)               |
           MCBSP_FMKS(XCR, XDATDLY, 1BIT)          | // 1 bit delay
           MCBSP_FMKS(XCR, XFRLEN1, OF(0))         | // This changes to 1 FRAME
           MCBSP_FMKS(XCR, XWDLEN1, 16BIT)         | // This changes to 16 bits per frame
           MCBSP_FMKS(XCR, XWDREVRS, DISABLE),

           MCBSP_FMKS(SRGR, GSYNC, DEFAULT)        |
           MCBSP_FMKS(SRGR, CLKSP, DEFAULT)        | // Sans int√©r√™t : Seulement utilis√© avec horloge externe
           MCBSP_FMKS(SRGR, CLKSM, INTERNAL)       | // Input clock source mode (INTERNAL (1) = Sample-rate generator clock derived from the CPU clock)
           MCBSP_FMKS(SRGR, FSGM, DEFAULT)         | // FSX est conduit par le Sample rate generator
           MCBSP_FMKS(SRGR, FPER, DEFAULT)         | // Largeur de frame sync pulse
           MCBSP_FMKS(SRGR, FWID, DEFAULT)         | // Trame de 16 bits
           MCBSP_FMKS(SRGR, CLKGDV, OF(0x32)),       // Clock divide down (64, Number of input clocks per data bit clock, to generate the required sample-rate generator clock frequency) Fe = 439453,125 Hz

           MCBSP_MCR_DEFAULT,
           MCBSP_RCER_DEFAULT,
           MCBSP_XCER_DEFAULT,

           MCBSP_FMKS(PCR, XIOEN, SP)              | //
           MCBSP_FMKS(PCR, RIOEN, SP)              | //
           MCBSP_FMKS(PCR, FSXM, INTERNAL)         | //
           MCBSP_FMKS(PCR, FSRM, EXTERNAL)         |
           MCBSP_FMKS(PCR, CLKXM, OUTPUT)          | // Transmitter clock mode bit (OUTPUT (1) = Data clock CLKX driven by the internal sample generator)
           MCBSP_FMKS(PCR, CLKRM, INPUT)           | // Receiver clock mode bit (INPUT (0) = Data clock CLKR is an input)
           MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)      |
           MCBSP_FMKS(PCR, DXSTAT, DEFAULT)        |
           MCBSP_FMKS(PCR, FSXP, ACTIVELOW)        | //
           MCBSP_FMKS(PCR, FSRP, ACTIVELOW)        | //
           MCBSP_FMKS(PCR, CLKXP, RISING)          | //
           MCBSP_FMKS(PCR, CLKRP, RISING)            //
       };


/****************************************************************************
	Private functions :
****************************************************************************/

// these function can only be called by this .c
// Use static keyword

/****************************************************************************
	Public functions :
****************************************************************************/

// Function description here ...

void SPI_init(void)
{
    MCBSP_config(DSK6713_AIC23_CONTROLHANDLE, &MCBSP0_SPI_Cfg); //mettre en place la nouvelle configuration du MCBSP
    MCBSP_start(DSK6713_AIC23_CONTROLHANDLE,MCBSP_XMIT_START | MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 256); //‡ quoi servent "XMIT_START", "RCV_START", "SRGR_START"?

    int CPLD_MISC_value =  DSK6713_rget(DSK6713_MISC);    // obtenir la valeur du registre MISC!
    CPLD_MISC_value |= 0x1; //masquage ici pour mettre le bon bit ‡ 1 ou ‡ 0
    DSK6713_rset(DSK6713_MISC, CPLD_MISC_value); // rÈÈcrire la valeur du registre MISC

    while(!MCBSP_xrdy(DSK6713_AIC23_CONTROLHANDLE)); //attendre que les 16 coups de clock correspondant au MCBSP_write soient terminÈs
    MCBSP_write(DSK6713_AIC23_CONTROLHANDLE, SPI_WRITE_CONFIG); // envoyer la config

	return;
}

void lire_MCBSP(void){
    while(!MCBSP_xrdy(DSK6713_AIC23_CONTROLHANDLE)); //attendre que les 16 coups de clock correspondant au MCBSP_write soient terminÈs
    MCBSP_write(DSK6713_AIC23_CONTROLHANDLE,0x00);
    while(!MCBSP_rrdy(DSK6713_AIC23_CONTROLHANDLE)); //attendre que les 16 coups de clock correspondant au MCBSP_read soient terminÈs
    Data_in = MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
}

void ecrire_MCBSP(void){
    while(!MCBSP_xrdy(DSK6713_AIC23_CONTROLHANDLE)); //attendre que les 16 coups de clock correspondant au MCBSP_write soient terminÈs
    MCBSP_write(DSK6713_AIC23_CONTROLHANDLE, Data_out | SPI_WRITE_DATA);
}

/****************************************************************************
	ISR :
****************************************************************************/
void interrupt intSPI(void){
    FlagSPI = 1;
    return;
}

// end of SPI_driver.c
