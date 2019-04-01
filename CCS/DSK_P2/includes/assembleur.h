/*
 * assembleur.h
 *
 *  Created on: 4 févr. 2019
 *      Author: jgaud
 */

#ifndef SOURCE_C_ASSEMBLEUR_H_
#define SOURCE_C_ASSEMBLEUR_H_

//Déclaration des fonctions assembleurs

void enableInterrupts(void);

void enableInterrupts_T0(void);
void enableInterrupts_T1(void);
void enableInterrupts_int4(void);
void enableInterrupts_int11(void);

void disableInterrupts_T0(void);
void disableInterrupts_T1(void);
void disableInterrupts_int4(void);
void disableInterrupts_int11(void);

#endif /* SOURCE_C_ASSEMBLEUR_H_ */
