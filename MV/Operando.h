#ifndef OPERANDO_H
#define OPERANDO_H //Es para poder importar la MV sin que tire error el compilador

#include "MV.h"


typedef struct{
    char tipo;
    unsigned int posicion;
    char parteReg; //la posicion se usa solo para registros y memoria y partereg solo para registros
    long int valor;
    long int offset;
    char tamCelda; //solo para memoria
} TOperando;

void decodifica_cod_op(TOperando *op1,TOperando *op2,short int *cod_op, MV *mv, char *inst);

void set_valor_inmediato(TOperando *op, long int valor);

char tam_operando(TOperando op, char tipo);

void set_parteReg(TOperando *op, char parteReg);

void set_posicion(TOperando *op, unsigned int pos);

void set_offset(TOperando *op, long int offset);

void lee_operando(TOperando *op, MV *mv);

void set_valor_op(TOperando *op,MV *mv);

void reset_valor_op(TOperando *op,MV *mv);

char get_instruccion(MV *mv);

#endif
