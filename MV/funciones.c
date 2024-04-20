#include "funciones.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>



void setea_cc(long int resultadoFunc, MV *mv){
    if (resultadoFunc < 0)
        mv->tabla_de_registros[8] = 0x10000000; //  indicador signo
    else if (resultadoFunc == 0)
         mv->tabla_de_registros[8] = 0x01000000; // indicador 0
    else
        mv->tabla_de_registros[8] = 0;
}

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

//2 operandos

void MOV(TOperando *op1, TOperando *op2, MV *mv){
    op1->valor = op2->valor;
    reset_valor_op(op1,mv);
}

void ADD(TOperando *op1, TOperando *op2, MV *mv){
    long int suma;
    suma = op1->valor + op2->valor;
    op1->valor = suma; //Creo que puede evitarse la variable auxiliar en ADD SUB MUL DIV
    setea_cc(suma, mv);
    reset_valor_op(op1,mv);
}

void SUB(TOperando *op1, TOperando *op2, MV *mv){
    long int resta;
    resta = op1->valor - op2->valor;
    op1->valor = resta;
    setea_cc(resta, mv);
    reset_valor_op(op1,mv);
}

void MUL(TOperando *op1, TOperando *op2, MV *mv){
    long int prod;
    prod = op1->valor * op2->valor;
    op1->valor = prod;
    setea_cc(prod, mv);
    reset_valor_op(op1,mv);
}

void DIV(TOperando *op1, TOperando *op2, MV *mv){
    long int div;
    long int res;
    if(op2->valor != 0){
        div = op1->valor / op2->valor;
        res = op1->valor % op2->valor;
        op1->valor = div;
        mv->tabla_de_registros[9] = res; //reg[9] -> AC
        setea_cc(div,mv);
        reset_valor_op(op1,mv);
    }
    else{
        printf("Division por cero");
        exit(1);
    }

}

void SWAP(TOperando *op1, TOperando *op2, MV *mv){
    if(op2->tipo != 1){ //  Operando B distinto de inmediato, el A nunca puede ser inmediato
        long int aux;
        aux = op1->valor;
        op1->valor = op2->valor;
        op2->valor = aux;
        reset_valor_op(op1,mv);
        reset_valor_op(op2,mv);
    }
}


void CMP(TOperando *op1, TOperando *op2, MV *mv){
    long int aux;
    aux = op1->valor - op2->valor;
    setea_cc(aux, mv);
}


void SHL(TOperando *op1, TOperando *op2, MV *mv){
    long int aux;
    aux = op1->valor << op2->valor;
    setea_cc(aux,mv);
    op1->valor = aux;
    reset_valor_op(op1,mv);
}

void SHR(TOperando *op1, TOperando *op2, MV *mv){
    long int aux;
    long int maskN = op1->valor & 0x80000000;
    aux = op1->valor >> op2->valor;
    aux = aux | maskN; // Si era negativo, pone 1 en bit mas significativo, sino se mantiene en 0
    setea_cc(aux,mv);
    op1->valor = aux;
    reset_valor_op(op1,mv);
}


void AND(TOperando *op1, TOperando *op2, MV *mv){
    long int and;
    and = op1->valor & op2->valor;
    op1->valor = and;
    setea_cc(and,mv);
    reset_valor_op(op1,mv);
}

void OR(TOperando *op1, TOperando *op2, MV *mv){
    long int or;
    or = op1->valor | op2->valor;
    op1->valor = or;
    setea_cc(or,mv);
    reset_valor_op(op1,mv);
}

void XOR(TOperando *op1, TOperando *op2, MV *mv){
    long int xor;
    xor = op1->valor ^ op2->valor;
    op1->valor = xor;
    setea_cc(xor,mv);
    reset_valor_op(op1,mv);
}

void RND(TOperando *op1, TOperando *op2, MV *mv){
    srand (time(NULL));
    op1->valor = rand() % (op2->valor + 1);
    reset_valor_op(op1,mv);
}

//1 operando

void SYS(TOperando *op, TOperando *op2, MV *mv){
    unsigned int entrada;
    long int salida = 0;
    char tamCeldas = (mv->tabla_de_registros[12] & 0x0000FF00) >> 8; // CH
    char cantCeldas = mv->tabla_de_registros[12] & 0x000000FF; // CL
    char formato = mv->tabla_de_registros[10] & 0x000000FF; //AL
    int posEDX = mv->tabla_de_registros[13];

    if(op->valor == 1){ //  READ
        for(int i = 0; i<cantCeldas; i++){
            printf("[%04X]: ",posEDX);
            if(formato & 0b1000) // Hexa
                scanf("%x",&entrada);
            else if(formato & 0b0100) //Octal
                scanf("%o",&entrada);
            else if(formato & 0b0010) //Caracter
                scanf("%c",&entrada);
            else if(formato & 0b0001) // Decimal
                scanf("%d",&entrada);
            else{
                printf("Formato de instruccion invalida \n");
                exit(1);
            }
            for(int j=0; j<tamCeldas; j++)
                mv->RAM[posEDX++] = entrada & (0x000000FF << (8*(tamCeldas-(j+1))));
        }
    }
    else if(op->valor == 2){ //WRITE
        for(int i = 0; i<cantCeldas; i++){
            printf("[%04X]: ",posEDX);
            for(int j=0; j<tamCeldas; j++){
                salida = salida | ((mv->RAM[posEDX++] << (8*(tamCeldas-(j+1)))) & (0x000000FF << (8*(tamCeldas-(j+1)))));
            }
            if((salida & 0x8000) == 0x8000){
                salida = salida | 0xFFFF0000;
            }
            if(formato & 0b1000) // Hexa
                printf("%% %08X ",salida);
            if(formato & 0b0100) //Octal
                printf("@ %o ",salida);
            if(formato & 0b0010){ //Caracter
                if(salida >= 32 && salida <= 126)
                    printf("%c ",salida);
                else
                    printf(". ");
            }
            if(formato & 0b0001){ // Decimal
                printf("%d ",salida);
            }
            printf("\n");
        }
    }
}

void JMP(TOperando *op, TOperando *op2, MV *mv){
    mv->tabla_de_registros[5] = op->valor;
}

void JZ(TOperando *op, TOperando *op2, MV *mv){
    if(mv->tabla_de_registros[8] == 0x01000000) // == 0
        mv->tabla_de_registros[5] = op->valor;
}

void JP(TOperando *op, TOperando *op2, MV *mv){
    if(mv->tabla_de_registros[8] != 0x01000000 && mv->tabla_de_registros[8] != 0x10000000) // >0
        mv->tabla_de_registros[5] = op->valor;
}

void JN(TOperando *op, TOperando *op2, MV *mv){
    if(mv->tabla_de_registros[8] == 0x10000000) // <0
        mv->tabla_de_registros[5] = op->valor;
}

void JNZ(TOperando *op, TOperando *op2, MV *mv){
    if(mv->tabla_de_registros[8] != 0x01000000) // !=0
        mv->tabla_de_registros[5] = op->valor;
}

void JNP(TOperando *op, TOperando *op2, MV *mv){
    if(mv->tabla_de_registros[8] == 0x01000000 || mv->tabla_de_registros[8] == 0x10000000) // <=0
        mv->tabla_de_registros[5] = op->valor;
}

void JNN(TOperando *op, TOperando *op2, MV *mv){
    if(mv->tabla_de_registros[8] != 0x10000000) // >=0
        mv->tabla_de_registros[5] = op->valor;
}


void LDL(TOperando *op, TOperando *op2, MV *mv){
    int ms;
    ms = op->valor & 0x0000FFFF;
    mv->tabla_de_registros[9] = ms;
}


void LDH(TOperando *op, TOperando *op2, MV *mv){
    long int ms;
    ms = (op->valor & 0x0000FFFF) << 16;
    mv->tabla_de_registros[9] = ms;
}


void NOT(TOperando *op, TOperando *op2, MV *mv){
    long int not;
    not = ~(op->valor);
    op->valor = not;
    setea_cc(not,mv);
    reset_valor_op(op,mv);
}


//0 operandos
void STOP(TOperando *op, TOperando *op2, MV *mv){
    mv->tabla_de_registros[5] = 0xFFFFFFFF;
}


void iniciaVectorFunciones(VectorFunciones vecF)
{
    vecF[0x00]=&MOV;
    vecF[0x01]=&ADD;
    vecF[0x02]=&SUB;
    vecF[0x03]=&SWAP;
    vecF[0x04]=&MUL;
    vecF[0x05]=&DIV;
    vecF[0x06]=&CMP;
    vecF[0x07]=&SHL;
    vecF[0x08]=&SHR;
    vecF[0x09]=&AND;
    vecF[0x0A]=&OR;
    vecF[0x0B]=&XOR;
    vecF[0x0C]=&RND;

    vecF[0x10]=&SYS;
    vecF[0x11]=&JMP;
    vecF[0x12]=&JZ;
    vecF[0x13]=&JP;
    vecF[0x14]=&JN;
    vecF[0x15]=&JNZ;
    vecF[0x16]=&JNP;
    vecF[0x17]=&JNN;
    vecF[0x18]=&LDL;
    vecF[0x19]=&LDH;
    vecF[0x1A]=&NOT;

    vecF[0x1F]=&STOP;
}
