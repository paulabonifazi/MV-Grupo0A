	XOR EFX, EFX
	MOV [1], 0	

OTRO:	MOV AL, %1
	MOV EDX, DS
	MOV CL, 1
	MOV CH, 4
	SYS %1

CALC:	DIV [0], 2
	CMP [0], 0
	JZ FIN	
	SHR AC, EFX
	ADD EFX, 1
	ADD [4], AC
	JMP CALC
	
FIN:	MOV EDX, DS
	ADD EDX, 4
	MOV CL, 1
	MOV CH, 4
	SYS %2
	STOP