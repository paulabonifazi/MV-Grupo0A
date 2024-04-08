#include "Operando.h"


/*
    A revisar, lo pense asi pero capaz hay alguna manera mejor de calcular las posiciones en la memoria
    Despues desarrolle un poco las otras funciones aca adentro, habria que pasarlas cada una a su funcion
    y cambiar las cabeceras para poder pasar la instruccion como parametro
 */
void decodifica_cod_op(TOperando *op1,TOperando *op2,char cod_op[],MV *mv){

    char inst = get_instruccion(mv);

    /* primer linea: bbaooooo
        a = tipo a -> 00000bba & 00000001 (0x01)
        b = tipo b -> 000000bb
        o = cod op -> bbaooooo & 00011111 (0x1F) -> es vector asi que es bit a bit
    */
    /*
    //set operando
    (*op2).tipo = inst>>6;
    (*op1).tipo = (inst>>5) & 0x01;
    */

    //set cod operacion
    for(int i=0; i<5; i++)
        cod_op[i] = (inst >> (5-i+1)) & 0x01;

    if(cod_op[0] == 0){
        // dos operandos
        (*op2).tipo = inst>>6; //opB
        (*op1).tipo = (inst>>5) & 0x01; //opA
        lee_operando(op1, mv); //lectura op en base a tipo (opA)
        lee_operando(op2, mv); //lectura op en base a tipo (opB)
    }
    else if(inst>>6 == 0b11){
        // un operando
        (*op1).tipo = inst>>6; //opA
        lee_operando(op1, mv);  //lectura op en base a tipo (opA)
    }
    else {
        // sin operando
    }
}

void set_valor(TOperando *op, long int valor){
    (*op).valor = valor;
}

char tam_operando(TOperando op, char tipo){
    return (~op.tipo) & 0x03;
}

void set_parteReg(TOperando *op, char parteReg){
    (*op).parteReg = parteReg;
}

void set_posicion(TOperando *op, unsigned int pos){
    (*op).posicion = pos;
}

void set_offset(TOperando *op, long int offset){
    (*op).offset = offset;
}

void lee_operando(TOperando *op, MV *mv){
    switch((*op).tipo){
        case 0: {   //memoria
            char cod_reg = get_instruccion(mv);
            unsigned int pos = cod_reg;
            set_posicion(op,pos);
            char offset_h = get_instruccion(mv);
            long int offset = offset_h;
            offset = offset<<8;
            char offset_l = get_instruccion(mv);
            offset += offset_l;
            set_offset(op, offset);
            break;
        }
        case 1:{    //inmediato
            char valor_h = get_instruccion(mv);
            long int valor = valor_h;
            valor = valor<<8;
            char valor_l = get_instruccion(mv);
            valor += valor_l;
            set_valor(op, valor);
            break;
        }
        case 2:{    //registro
            char sec_reg = get_instruccion(mv);
            set_parteReg(op,sec_reg);
            char cod_reg = get_instruccion(mv);
            unsigned int pos = cod_reg;
            set_posicion(op,pos);
            break;
        }
    }
}

char get_instruccion(MV *mv){
    char ip = mv->tabla_de_registros[5];
    char posSeg = mv->tabla_de_segmentos[ip & 0xF0].segmento; //Busca indice de IP y devuelve el codigo en tabla segmentos
    char posRAM = ((mv->tabla_de_segmentos[posSeg].offset & 0xF0)>>4) + (ip & 0x0F); //Posicion DS en tabla segmento + offset IP
    char inst = mv->RAM[posRAM];

    mv->tabla_de_registros[5] += 0x01; //Suma 1 al offset de ip

    return inst;
}
