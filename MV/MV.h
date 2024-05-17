#ifndef MV_H
#define MV_H

#define cantSeg 2
#define cantReg 16
#define TAM_MEMO 16384

typedef struct {
    short int segmento;
    short int tam;
} tabla_segmentos;


typedef struct {
    unsigned char RAM[TAM_MEMO];
    unsigned short int tamanioM;
    unsigned short int EP; //entry point
    tabla_segmentos  tabla_de_segmentos[cantSeg];
    long int tabla_de_registros[cantReg];
} MV;

void ejecutaMV(char arch[], char disassembler[], int tam, char img[]);

#endif
