#ifndef Disassembler_H_INCLUDED
#define Disassembler_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMINSTR 5 //4 letras max  de cada mnemonico + \0

#define CS 0
#define DS 1
#define IP 5
#define CC 8
#define AC 9
#define EAX 10
#define EBX 11
#define ECX 12
#define EDX 13
#define EEX 14
#define EFX 15


typedef struct {
    char tipo,tamaniocelda;
    long int nro;
    long int registro;
    short int codOp;
}TOp;

//defino otro tipo de operando ya que el TOperando tiene info que no nos sirve para printear el debbuger

typedef struct {
    char* reg[16];
    unsigned int posinstr; //pos para printear desde el principio
    char instr;
    TOp op1,op2;
    char codoperacion[TAMINSTR];
}TDisassembler;

void inicializaDisassembler(TDisassembler *dis);
void reiniciaOperandos(TDisassembler *ins);
void cargaIns(TDisassembler *dis, unsigned int posinstr, char instr, char codoperacion[]);
void cargaOp(TDisassembler *dis, int nrodeop, char tipo, short int codOp, long int nro, long int registro, char tamaniocelda);
void muestra(TDisassembler dis);


#endif
