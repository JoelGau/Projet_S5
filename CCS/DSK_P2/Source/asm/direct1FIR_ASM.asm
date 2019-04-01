;****************************************************************************************
; APPEL :
; short * direct1FIR_ASM(short *cPtr, short ech, const short h[], short *y);
;
; A4 : Adresse du pointeur sur l'�chantillon pr�c�dent
; B4 : Valeur de l'�chantillon courant
; A6 : Adresse du d�but du tableau de coefficients du filtre, h[]
; B6 : Adresse de l'�chantillon de sortie
;
; Return : la nouvelle adresse de cPtr (A4)
;
; NB:
; 1) La longueur du filtre passe-haut, N = 63 (ordre = 62), est fixe (hardcoded)
;    et n'est donc pas pass�e comme param�tre � la fonction
; 2) Comme le mode d'adressage circulaire est employ� pour le tampon, il n'est pas n�cessaire
;    de sp�cifier l'adresse de d�but du tampon mais simplement l'adresse de l'�chantillon
;    courant. En effet, quand le pointeur du tampon est incr�ment� ou d�cr�ment�, le
;    mode d'adressage circulaire force le pointeur � rester dans le tampon ("wrapping"). Il suffit simplement
;    de sp�cifier la bonne longueur avec l'AMR et de bien aligner le tampon lors de sa
;    d�claration dans le programme C avec "#pragma DATA_ALIGN"
;
;****************************************************************************************

		.def	_direct1FIR_ASM
_direct1FIR_ASM:

; M�moriser le contenu de AMR 
			MVC	AMR, B5
			STW	B5,*--B15 

; Ajuster le registre AMR
			MVKL 0x00C08000, B9	; Utiliser B7 comme pointeur avec BK1 comme compteur vers
			MVKH 0x00C08000, B9	; Le tampon contient 64 �chantillons de 16 bits chacuns, donc 128 octets (2 X 64)
			MVC B9, AMR

; Charger l'adresse de l'�chantillon pr�c�dent du tampon dans B7
			MV A4, B7

; �crire l'�chantillon courant dans le tampon
			STH B4, *++B7

; Retourner l'adresse de l'�chantillon courant
			MV B7, A4

; Longueur du filtre, N (ordre + 1, valeur impaire puisque c'est un passe-haut symm�trique)
			MVK 63, A1

; Initialisation y[n]=0
			ZERO A11;

;**********************************************************************
; Filtrage : boucle y[n] = y[n] + x[n-k]*h[k], pour k = 0..N, o� N = 63
;            et o� A11 est un accumulateur auquel on sont ajout�s les
;            produits x[n-k]*h[k] � chaque it�ration, k, de la boucle.
;            Le filtre n'est pas r�cursif...
;
;            ATTENTION: les x[n] sont contenus dans le tampon circulaire
;                       et sont donc load�s avec B7 et non A4.
;*********************************************************************

;**********
; Filtrage
;**********

Boucle:
			SUB A1,1,A1 ; Diminution du compteur de tour (delay slot 0)
			|| LDH *A6++, A5
			|| LDH *--B7, B5   ; Chargement de l'�chantillon dans B5 (delay slot 4)
			NOP 4
			MPY A5,B5,A9 ; A9 = x[n-i]*h[n+j] (delay slot 1)
			NOP 1
			ADD A9, A11, A11; y[n] = y[n] + x[n-i]*h[n+j] (delay slot 0)

			[A1] B  Boucle ;boucle si A1 n'est pas 0 (delay slot 5)
			NOP 5

; Enregistrer la sortie y[n]
			SHR A11,15,A11 ;Q30->Q15
			STH A11,*B6

; R�tablir le contenu de AMR
			LDW	*B15++,B5
			NOP	5
			MVC	B5,AMR

; Retourner l'adresse � la fonction qui a fait l'appel (return)
			B B3
			NOP 5

		.end
