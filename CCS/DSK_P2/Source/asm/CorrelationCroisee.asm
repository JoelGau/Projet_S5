	.def _SumASM

	.data

SET_AMR .set 0x00060001
LONGUEURTRAME .set 0x00000014


_SumASM
	.asmfunc

	;A4 ; Index tableau1
	;B4 ; Index tableau2
	;A6 ; Index longueur boucle

	; Protection du contexte
	STW B0, *B15--[2]
	STW B5, *B15--[2]
	STW B6, *B15--[2]	;Push tous les registres utilisés lors de la fonction
	STW A5, *B15--[2]	;**Pas nécessaire pour A4, B4, A6 car ce sont les registres de passage de paramètres
	STW A7, *B15--[2]


	MV A6,B0
	|| MVK 0,B6

BoucleAddition:

	LDW .D1 *A4++,A5
	|| LDW .D2 *B4++,B5
	SUB B0,1,B0
	NOP 4

	MPY A5,B5,A7
	NOP 1
	ADD B6,A7,B6

	[B0] B BoucleAddition
	NOP 5

	MV B6,A4

	; Restaurer le contexte
	LDW *++B15[2], A7
	LDW *++B15[2], A5
	LDW *++B15[2], B6
	LDW *++B15[2], B5
	LDW *++B15[2], B0
	NOP 5

	B B3
	NOP 5

	.endasmfunc
	.end
