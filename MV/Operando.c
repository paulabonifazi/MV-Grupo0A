#include "Operando.h"
#include <stdlib.h>
#include <stdio.h>

/*
    A revisar, lo pense asi pero capaz hay alguna manera mejor de calcular las posiciones en la memoria
    Despues desarrolle un poco las otras funciones aca adentro, habria que pasarlas cada una a su funcion
    y cambiar las cabeceras para poder pasar la instruccion como parametro
 */
void decodifica_cod_op(TOperando *op1,TOperando *op2,short int *cod_op,MV *mv, char *inst){

    *inst = get_instruccion(mv);
    *cod_op = 0;
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
    *cod_op = (*inst) & 0x1F;

    printf("cod operacion: %d\n", cod_op);

    if((*cod_op >> 4) == 0){
        // dos operandos
        op2->tipo = (*inst)>>6; //opB
        op1->tipo = ((*inst)>>5) & 0x01; //opA
        lee_operando(op2, mv); //lectura op en base a tipo (opA)
        lee_operando(op1, mv); //lectura op en base a tipo (opB)
    }
    else if((*inst)>>6 != 0b11){
        // un operando
        op1->tipo = (*inst)>>6; //opA
        lee_operando(op1, mv);  //lectura op en base a tipo (opA)
    }
    else {
        // sin operando
    }
}

void set_valor_inmediato(TOperando *op, long int valor){
    op->valor = valor;
}

char tam_operando(TOperando op, char tipo){
    return (~op.tipo) & 0x03;
}

void set_parteReg(TOperando *op, char parteReg){
    op->parteReg = parteReg;
}

void set_posicion(TOperando *op, unsigned int pos){
    op->posicion = pos;
}

void set_offset(TOperando *op, long int offset){
    op->offset = offset;
}

void lee_operando(TOperando *op, MV *mv){
    switch(op->tipo){
        case 0: {   //memoria
            op->valor = 0;
            char cod_reg = get_instruccion(mv);
            unsigned int pos = cod_reg;
            set_posicion(op,pos);
            char offset_h = get_instruccion(mv);
            long int offset = offset_h;
            offset = offset<<8;
            char offset_l = get_instruccion(mv);
            offset += offset_l;
            set_offset(op, offset);
            set_valor_op(op,mv); // En base a la posicion y el offset se obtiene el valor de esa posicion de memoria y se almacena en op.valor
            break;
        }
        case 1:{    //inmediato
            char valor_h = get_instruccion(mv);
            long int valor = valor_h;
            valor = valor<<8;
            char valor_l = get_instruccion(mv);
            valor += valor_l;
            set_valor_inmediato(op, valor);
            break;
        }
        case 2:{    //registro
            op->valor = 0;
            char sec_reg = get_instruccion(mv);
            set_parteReg(op,sec_reg);
            char cod_reg = get_instruccion(mv);
            unsigned int pos = cod_reg;
            set_posicion(op,pos);
            set_valor_op(op,mv); // En base al sector y el codigo de reg se obtiene el valor de ese registro y se almacena en op.valor
            break;
        }
    }
}

char get_instruccion(MV *mv){
    // REVISAR
    char ip = mv->tabla_de_registros[5];
    char posSeg = mv->tabla_de_segmentos[ip & 0xFFFF0000].segmento; //Busca indice de IP y devuelve el codigo en tabla segmentos
    char posRAM = posSeg + (ip & 0x0000FFFF);//((mv->tabla_de_segmentos[posSeg].tam & 0xF0)>>4) + (ip & 0x0F); //Posicion DS en tabla segmento + offset IP
    char inst = mv->RAM[posRAM];

    mv->tabla_de_registros[5] += 0x01; //Suma 1 al offset de ip

    return inst;
}

void set_valor_op(TOperando *op,MV *mv){ //Guarda en op el valor que esta almacenado en la posicion de memoria o de registro a la cual apunta op
    if(op->tipo == 0b00){   //Memoria
        int i = 0;
        unsigned int posRAM = mv->tabla_de_segmentos[op->posicion].segmento + op->offset + i;
        //printf("%d", op->posicion);
        //printf("%d", op->offset);
        //printf("%d", posRAM);
        while(i<4 && posRAM<16384){
            op->valor = op->valor + (mv->RAM[posRAM] << (24 - (i*8)));
            i += 1;
            posRAM += 1;
        }
        if(posRAM>=16384){
            printf("Fallo de segmento");
            exit(1);
        }
        //for(int i=0; i<4; i++)
            //op->valor = op->valor + (mv->RAM[mv->tabla_de_segmentos[op->posicion].segmento + op->offset + i] << (24 - (i*8))); //0x11111111 22222222 33333333 44444444
    }
    else if(op->tipo == 0b10){  //Registro
        switch(op->parteReg) {
            case 0x00: {
                //registro de 4 bytes
                op->valor = mv->tabla_de_registros[op->posicion];
                break;}
            case 0x01: {
                //4to byte del registro
                op->valor = mv->tabla_de_registros[op->posicion] & 0x000000FF;
                break;}
            case 0x10: {
                //3er byte del registro
                op->valor = (mv->tabla_de_registros[op->posicion] & 0x0000FF00) >> 8;
                break;}
            case 0x11: {
                //registro de 2 bytes
                op->valor = mv->tabla_de_registros[op->posicion] & 0x0000FFFF;
                break;}
        }
    }
    //Si es inmediato ya tiene el valor seteado de cuando se ley� el codigo de operacion
}

void reset_valor_op(TOperando *op,MV *mv){ //Guarda en la posicion a la cual apunta op en memoria o en registro el valor almacenado en op->valor
    if(op->tipo == 0b00){   //Memoria
        for(int i=0; i<4; i++)
            mv->RAM[mv->tabla_de_segmentos[op->posicion].segmento + op->offset + i] = (op->valor>>(24-i*8)) & 0x000000FF;
    }
    else if(op->tipo == 0b10){  //Registro
        switch(op->parteReg) {
            case 0x00: {
                //registro de 4 bytes
                mv->tabla_de_registros[op->posicion] = op->valor;
                break;}
            case 0x01: {
                //4to byte del registro
                mv->tabla_de_registros[op->posicion] = op->valor & 0x000000FF;
                break;}
            case 0x10: {
                //3er byte del registro
                mv->tabla_de_registros[op->posicion] = (op->valor & 0x0000FF00) >> 8;
                break;}
            case 0x11: {
                //registro de 2 bytes
                mv->tabla_de_registros[op->posicion] = op->valor & 0x0000FFFF;
                break;}
        }
    }
}
