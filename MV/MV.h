#ifndef MV_H
#define MV_H

#define cantSeg 8
#define cantReg 16
#define TAM_MEMO 16384

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    short int segmento;
    short int tam;
} tabla_segmentos;


typedef struct {
    unsigned char RAM[TAM_MEMO];
    unsigned short int tamanioM;      //tamanio logico de la ram
    unsigned short int EP;                  //entry point
    unsigned char breakpoint;           //flag que indica si hay o no breakpoint
    FILE *imagen;                                  //archivo imagen??
    tabla_segmentos  tabla_de_segmentos[cantSeg];
    long int tabla_de_registros[cantReg];
} MV;

void ejecutaMV(char arch[], char disassembler[], int tam, char img[]);

#endif
