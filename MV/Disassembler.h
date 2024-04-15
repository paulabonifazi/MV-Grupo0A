#ifndef Disassembler_H_INCLUDED
#define Disassembler_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_MNEMONICOS 32
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

char *mnemonicos[NUM_MNEMONICOS] = {
        "MOV", "ADD", "SUB", "SWAP", "MUL", "DIV", "CMP", "SHL",
        "SHR", "AND", "OR", "XOR", "RND", NULL, NULL, NULL, "SYS", "JMP",
        "JZ", "JP", "JN", "JNZ", "JNP", "JNN", "LDL", "LDH",
        "NOT", NULL, NULL, NULL, NULL, "STOP"
    };

typedef struct {
    char tipo;
    long int nro;
    long int registro;
    short int codOp;
}TOp;

//defino otro tipo de operando ya que el TOperando tiene info que no nos sirve para printear el debbuger

typedef struct {
    char* reg[16];
    short int posinstr; //pos para printear desde el principio
    char instr;
    TOp op1,op2;
    short int codOp;
}TDisassembler;

void inicializaDisassembler(TDisassembler *dis);
void reiniciaOperandos(TDisassembler *dis);
void cargaIns(TDisassembler *dis, short int posinstr, char instr, char codOp[]);
void cargaOp(TDisassembler *dis, int nrodeop, char tipo, char codOp[], long int nro, long int registro);
void muestra(TDisassembler dis);


#endif
