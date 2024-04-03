#include "Operando.h"

void decodifica_cod_op(TOperando *op1,TOperando *op2,char *cod_op);

void set_operando(TOperando op, char tipo, long int valor);

void set_parteReg(TOperando op, char parteReg);

void set_posicion(TOperando op, unsigned int pos);

void set_offset(TOperando op, long int offset);

TOperando get_operando();

char set_cod_op(char* cod_op);
