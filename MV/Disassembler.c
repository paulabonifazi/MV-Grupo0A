#include "Disassembler.h"
#include <string.h>

void cargaIns(TDisassembler *dis, short int posinstr, unsigned char instr, short int codOp){
    (*dis).posinstr = posinstr;
    (*dis).instr = instr;
    (*dis).codOp = codOp;
}

void cargaOp(TDisassembler *dis, int nrodeop, TOperando operando){
    if(nrodeop == 1)
        (*dis).op1 = operando;
    else
        (*dis).op2 = operando;
}

void escribeInstruccion(TOperando op, int tamanio){
    switch (tamanio){
        case 1:{ // registro
            char aux = 0;
            aux = (op.parteReg << 4) & 0xF0;
            aux = aux | (op.posicion & 0x0F);
            printf("%02X ", aux);
            break;
        }
        case 2:{ //inmediato
            int auxh = 0,auxl = 0;
            auxh = ((op.valor & 0xFF00) >> 8) & 0x000000FF;
            auxl = op.valor & 0x000000FF;
            printf("%02X %02X ",auxh,auxl);
            break;
        }
        case 3:{ // memoria
            char auxh = 0,auxl = 0;
            auxh = (op.offset & 0xFF00) >> 8;
            auxl = op.offset & 0x00FF;
            printf("0%01X %02X %02X ",op.posicion,auxh,auxl);
            break;
        }
    }
}

void mnemonicoOp(TOperando op){
    char *registros[64] = {
        "CS", "DS", "ES", "SS", "KS", "IP", "SP", "BP", "CC", "AC",
        "EAX", "EBX", "ECX", "EDX", "EEX", "EFX", NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, "AL", "BL", "CL", "DL",
        "EL", "FL", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, "AH", "BH", "CH", "DH", "EH", "FH", NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "AX", "BX",
        "CX", "DX", "EX", "FX"
        };

    char muestra[40];
    strcpy(muestra,"");

    switch(op.tipo){
        case 0:{ // memoria
            switch (op.tamCelda) {
                case 0b00:  strcat(muestra,"l[");
                    break;
                case 0b10:  strcat(muestra,"w[");
                    break;
                case 0b11:  strcat(muestra,"b[");
                    break;
            }
            //strcat(muestra,"[");
            char aux[6];
            strcat(muestra,registros[op.posicion]);
            //--------------------------------------- aca tenemos que modificar para cuando tenemos cts negativas
            strcat(muestra," + ");
            sprintf(aux, "%d", op.offset);
            strcat(muestra,aux);
            strcat(muestra,"]");
            break;
        }
        case 1:{ //inmediato
            char aux[6];
            long int num;
            if((op.valor & 0x80000000) == 0x80000000){
                num = op.valor | 0xFFFF0000;
            }
            else
                num = op.valor;
            sprintf(aux, "%d", num);
            strcat(muestra,aux);
            break;
        }
        case 2:{ // registro
            int aux = 0;
            aux = (op.parteReg << 4) & 0xF0;
            aux = aux | (op.posicion & 0x0F);
            if(registros[aux != NULL])
                strcat(muestra,registros[aux]);
            else
                printf("NULL! \n");
            break;
        }
    }
    printf("%s",muestra);
}

void muestra(TDisassembler dis){
    char *mnemonicos[NUM_MNEMONICOS] = {
        "MOV", "ADD", "SUB", "SWAP", "MUL", "DIV", "CMP", "SHL",
        "SHR", "AND", "OR ", "XOR", "RND", NULL, NULL, NULL, "SYS", "JMP",
        "JZ ", "JP ", "JN ", "JNZ", "JNP", "JNN", "LDL", "LDH",
        "NOT", "PUSH", "POP", "CALL", "RET", "STOP"
    };

    int tamanio, i, espacio = 0;
    char muestra[40];
    strcpy(muestra,"");

    printf("[%04X] %02X ", dis.posinstr, ((unsigned int)dis.instr)&0xFF); // 0 en byte mas significativo para que se muestre bien,sino pone todo FFFFFF

    //OP2
    tamanio = (~dis.op2.tipo)&0x03; //el complemento del tipo de operando es su tama�o
    escribeInstruccion(dis.op2,tamanio);
    espacio += 3-tamanio;
    //OP1
    tamanio = (~dis.op1.tipo)&0x03; //el complemento del tipo de operando es su tama�o
    escribeInstruccion(dis.op1,tamanio);
    espacio += 3-tamanio;

    for(i=0; i<=espacio; i++)
        printf("   ");

    //MNEMONICOS
    printf(" | %s ", mnemonicos[dis.codOp]);
    if(dis.codOp<=12){
        mnemonicoOp(dis.op1);
        printf(", ");
        mnemonicoOp(dis.op2);
    }
    else if(dis.codOp>=16 && dis.codOp<=29){
        mnemonicoOp(dis.op1);
    }
    printf("\n");

}

