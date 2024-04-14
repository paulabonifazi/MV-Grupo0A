#ifndef OPERANDO_H
#define OPERANDO_H //Es para poder importar la MV sin que tire error el compilador

#include "MV.h"


typedef struct{
    char tipo;
    unsigned int posicion;
    char parteReg; //la posicion se usa solo para registros y memoria y partereg solo para registros
    long int valor;
    long int offset;
} TOperando;
/* podríamos usar este tipo para los operandos así almacenamos toda la info
    no sé si op1 y op2 sean parte de la MV o definirlas en el main*/

/* En funciones con dos operandos, el tipo del operando A(1) nunca puede ser un inmediato, puede ser
    de memoria o de registro*/

/* Para poder asignar los tipos y el codigo de operacion a las variables
    habria que pasar la MV como parametro para poder ir leyendo de la RAM */

void decodifica_cod_op(TOperando *op1,TOperando *op2,char cod_op[],MV *mv);

void set_valor_inmediato(TOperando *op, long int valor);

char tam_operando(TOperando op, char tipo);

void set_parteReg(TOperando *op, char parteReg);

void set_posicion(TOperando *op, unsigned int pos);

void set_offset(TOperando *op, long int offset);

void lee_operando(TOperando *op, MV *mv);

char get_instruccion(MV *mv); //Nose si char o void porque hace dos cosas: devuleve instruccion y suma 1 al offset de IP

void set_valor_op(TOperando *op,MV *mv);

void reset_valor_op(TOperando *op,MV *mv);

#endif
