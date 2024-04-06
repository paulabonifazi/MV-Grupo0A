#ifndef MV_H
#define MV_H

#define cantSeg 2
#define cantReg 16


typedef struct {
    char segmento;
    char offset;
} tabla_segmentos;


typedef struct {
    char RAM[16384];
    tabla_segmentos  tabla_de_segmentos[cantSeg];
    char tabla_de_registros[cantReg];
} MV;

#endif
