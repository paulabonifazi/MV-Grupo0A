#ifndef Disassembler_H_INCLUDED
#define Disassembler_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Operando.h"
#define NUM_MNEMONICOS 32
#define TAMINSTR 5 //4 letras max  de cada mnemonico + \0

#define CS 0
#define DS 1
#define ES 2
#define SS 3
#define KS 4
#define IP 5
#define SP 6
#define BP 7
#define CC 8
#define AC 9
#define EAX 10
#define EBX 11
#define ECX 12
#define EDX 13
#define EEX 14
#define EFX 15

#define AL 26
#define BL 27
#define CL 28
#define DL 29
#define EL 30
#define FL 31

#define AH 42
#define BH 43
#define CH 44
#define DH 45
#define EH 46
#define FH 47

#define AX 58
#define BX 59
#define CX 60
#define DX 61
#define EX 62
#define FX 63

typedef struct {
    char* reg[16];
    short int posinstr; //pos para printear desde el principio
    char instr;
    TOperando op1,op2;
    short int codOp;
}TDisassembler;

void cargaIns(TDisassembler *dis, short int posinstr, unsigned char instr, short int  codOp);
void cargaOp(TDisassembler *dis, int nrodeop, TOperando operando);
void escribeInstruccion(TOperando op, int tamanio);
void mnemonicoOp(TOperando op);
void muestra(TDisassembler dis);


#endif
