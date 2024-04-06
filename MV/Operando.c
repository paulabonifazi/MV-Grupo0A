#include "Operando.h"


/*
    A revisar, lo pense asi pero capaz hay alguna manera mejor de calcular las posiciones en la memoria
    Despues desarrolle un poco las otras funciones aca adentro, habria que pasarlas cada una a su funcion
    y cambiar las cabeceras para poder pasar la instruccion como parametro
 */
void decodifica_cod_op(TOperando *op1,TOperando *op2,char *cod_op,MV *mv){
    char ip = mv->tabla_de_registros[5];
    char posSeg = mv->tabla_de_segmentos[ip & 0xF0]; //Busca indice de IP y devuelve el codigo en tabla segmentos
    char posRAM = (mv->tabla_de_segmentos[posSeg] & 0xF0)>>4 + (ip & 0x0F); //Posicion DS en tabla segmento + offset IP
    char inst = mv->RAM[posRAM];

    /* primer linea: bbaooooo
        a = tipo a -> 00000bba & 00000001 (0x01)
        b = tipo b -> 000000bb
        o = cod op -> bbaooooo & 00011111 (0x1F) -> es vector asi que es bit a bit
    */

    //set operando
    (*op2).tipo = inst>>6;
    (*op1).tipo = (inst>>5) & 0x01;

    //set cod operacion
    for(int i=0; i<5; i++)
        (*cod_op)[i] = (inst >> (5-i+1)) & 0x01;
}

void set_operando(TOperando op, char tipo, long int valor);

void set_parteReg(TOperando op, char parteReg);

void set_posicion(TOperando op, unsigned int pos);

void set_offset(TOperando op, long int offset);

TOperando get_operando();

char set_cod_op(char* cod_op);
