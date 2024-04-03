#define cantSeg 2;
#define cantReg 16;
#include Operando.h

typedef struct {
    char segmento;
    char offset;
} tabla_segmentos;


typedef struct {
    char RAM[16384];
    tabla_segmentos  tabla_de_segmentos[cantSeg];
    char tabla_de_registros[cantReg];
    TOpeando op1;
    TOperando op2;
    char cod_op;
} MV;
