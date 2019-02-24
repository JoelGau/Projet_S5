	.def _enableInterrupts
	.def _enableInterrupts_T0
	.def _enableInterrupts_T1
	.def _enableInterrupts_int4
	.def _enableInterrupts_int11
	.def _disableInterrupts_T0
	.def _disableInterrupts_T1
	.def _disableInterrupts_int4
	.def _disableInterrupts_int11

MASK_EN_GIE .set 0x00000001
MASK_EN_NMI_T0 .set 0x00004002
MASK_EN_NMI_T1 .set 0x00008002
MASK_EN_NMI_int4 .set 0x00000012
MASK_EN_NMI_int11 .set 0x00000802

_enableInterrupts
    .asmfunc

	MVC CSR, B0
	MVKL MASK_EN_GIE, B1
	MVKH MASK_EN_GIE, B1
	OR B1, B0, B0
	MVC B0, CSR

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_enableInterrupts_T0
    .asmfunc

    MVC IER,B0
	MVKL MASK_EN_NMI_T0, B1
	MVKH MASK_EN_NMI_T0, B1
	OR B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_enableInterrupts_T1
    .asmfunc

    MVC IER,B0
	MVKL MASK_EN_NMI_T1, B1
	MVKH MASK_EN_NMI_T1, B1
	OR B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_enableInterrupts_int4
    .asmfunc

    MVC IER,B0
	MVKL MASK_EN_NMI_int4, B1
	MVKH MASK_EN_NMI_int4, B1
	OR B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_enableInterrupts_int11
    .asmfunc

    MVC IER,B0
	MVKL MASK_EN_NMI_int11, B1
	MVKH MASK_EN_NMI_int11, B1
	OR B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_disableInterrupts_T0
    .asmfunc

    MVC IER,B0
	MVKL ~MASK_EN_NMI_T0, B1
	MVKH ~MASK_EN_NMI_T0, B1
	AND B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_disableInterrupts_T1
    .asmfunc

    MVC IER,B0
	MVKL ~MASK_EN_NMI_T1, B1
	MVKH ~MASK_EN_NMI_T1, B1
	AND B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_disableInterrupts_int4
    .asmfunc

    MVC IER,B0
	MVKL ~MASK_EN_NMI_int4, B1
	MVKH ~MASK_EN_NMI_int4, B1
	AND B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc

_disableInterrupts_int11
    .asmfunc

    MVC IER,B0
	MVKL ~MASK_EN_NMI_int11, B1
	MVKH ~MASK_EN_NMI_int11, B1
	AND B1,B0,B0
	MVC B0,IER

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
    .endasmfunc
