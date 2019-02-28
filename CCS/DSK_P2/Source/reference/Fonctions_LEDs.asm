	.def _LED0

MASK_LED0 .set 0x01
MASK_LED1 .set 0x02
CPLD_USER_REG .set 0x90080000

_LED0
    .asmfunc

    MVC USER_REG, A0

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5

    .endasmfunc
