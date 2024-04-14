#ifndef MV_H
#define MV_H

#define cantSeg 2
#define cantReg 16


typedef struct {
    short int segmento;
    short int tam;
} tabla_segmentos;


typedef struct {
    char RAM[16384];
    tabla_segmentos  tabla_de_segmentos[cantSeg];
    int tabla_de_registros[cantReg];
} MV;

void ejecutaMV(char arch[], char disassembler[]);

#endif
