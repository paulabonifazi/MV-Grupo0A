#include "Disassembler.h"
#include <string.h>

void inicializaDisassembler(TDisassembler *dis){
    dis->reg[CS] = "CS";
    dis->reg[DS] = "DS";
    dis->reg[IP] = "IP";
    dis->reg[CC] = "CC";
    dis->reg[AC] = "AC";

    dis->reg[EAX] = "EAX";
    dis->reg[EBX] = "EBX";
    dis->reg[ECX] = "ECX";
    dis->reg[EDX] = "EDX";
    dis->reg[EEX] = "EEX";
    dis->reg[EFX] = "EFX";
}

void cargaIns(TDisassembler *dis, short int posinstr, char instr, short int codOp){
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

void imprimeReg(long int registro, long int parteReg,char *registros[],char *muestra){
    if(parteReg==0){
        strcat(muestra,registros[registro]);
    }
    else{
        sprintf(muestra, "%1X", registro); //copia a muestra un string con el formato ("XXX")
        switch(parteReg){
            case 1: strcat(muestra,"L");
                    break;
            case 2: strcat(muestra,"H");
                    break;
            case 3: strcat(muestra,"X");
                    break;
        }
    }
}

void muestraop( int nroOp, TOp operando,char *registros[]){
    char muestra[15];
    char stnro[6];
    int espacio,i;

    strcpy(muestra,"");
    strcpy(stnro,"");
    switch(operando.tipo){
        case 0:  printf("\nsoy un op de memoria\n");
                strcpy(muestra,"l");
                strcat(muestra,"[");
                imprimeReg(operando.registro,0,registros,muestra);
                if(operando.nro!=0){
                    if(operando.nro>0){
                        strcat(muestra,"+");
                    }
                    sprintf(stnro,"%d",operando.nro);
                    strcat(muestra,stnro);
                }
                strcat(muestra,"]");
                break;
        case 1: sprintf(muestra,"%ld",operando.nro);
                break;
        case 2: imprimeReg(operando.registro,operando.nro,registros,muestra);
                break;

    }
    //crea string luego lo muestra dependiendo el operador que debe ir
    if(nroOp==1){
        espacio=10-strlen(muestra);
        for(i=0;i<=espacio;i++)
            printf(" ");
        printf("%s, ",muestra);
    }
    else
        printf("%s",muestra);
}

void muestra(TDisassembler dis){ //se llama desde la MV (ver que metodo)
    char *mnemonicos[NUM_MNEMONICOS] = {
        "MOV", "ADD", "SUB", "SWAP", "MUL", "DIV", "CMP", "SHL",
        "SHR", "AND", "OR ", "XOR", "RND", NULL, NULL, NULL, "SYS", "JMP",
        "JZ ", "JP ", "JN ", "JNZ", "JNP", "JNN", "LDL", "LDH",
        "NOT", NULL, NULL, NULL, NULL, "STOP"
    };

    char *registros[70] = {
        "CS", "DS", NULL, NULL, NULL, "IP", NULL, NULL, "CC", "AC",
        "EAX", "EBX", "ECX", "EDX", "EEX", "EFX", NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, "AL", "BL", "CL", "DL",
        "EL", "FL", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, "AH", "BH", "CH", "DH", "EH", "FH", NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "AX", "BX",
        "CX", "DX", "EX", "FX", NULL, NULL, NULL, NULL, NULL, NULL
    };

    int tamanio, i, espacio = 0;
    char muestra[40];
    strcpy(muestra,"");

    printf("[%04X] %02X ", dis.posinstr, ((unsigned int)dis.instr)&0xFF); // 0 en byte mas significativo para que se muestre bien,sino pone todo FFFFFF


    //OP2
    tamanio = (~dis.op2.tipo)&0x03; //el complemento del tipo de operando es su tama�o

    switch (tamanio){
        case 1:{ // registro
            char aux = 0;
            aux = (dis.op2.parteReg << 4) & 0xF0;
            aux = aux | (dis.op2.posicion & 0x0F);
            printf("%02X ", aux);
            break;
        }
        case 2:{ //inmediato
            int auxh = 0,auxl = 0;
            auxh = ((dis.op2.valor & 0xFF00) >> 8) & 0x000000FF;
            auxl = dis.op2.valor & 0x000000FF;
            printf("%02X %02X ",auxh,auxl);
            break;
        }
        case 3:{ // memoria
            char auxh = 0,auxl = 0;
            auxh = (dis.op2.offset & 0xFF00) >> 8;
            auxl = dis.op2.offset & 0x00FF;
            printf("0%01X %02X %02X ",dis.op2.posicion,auxh,auxl);
            break;
        }
    }
    espacio += 3-tamanio;
    //OP1
    tamanio = (~dis.op1.tipo)&0x03; //el complemento del tipo de operando es su tama�o

    switch (tamanio){
        case 1:{ // registro
            char aux = 0;
            aux = (dis.op1.parteReg << 4) & 0xF0;
            aux = aux | (dis.op1.posicion & 0x0F);
            printf("%02X ", aux);
            break;
        }
        case 2:{ //inmediato
            int auxh = 0,auxl = 0;
            auxh = ((dis.op1.valor & 0xFF00) >> 8) & 0x000000FF;
            auxl = dis.op1.valor & 0x000000FF;
            printf("%02X %02X ",auxh,auxl);
            break;
        }
        case 3:{ // memoria
            char auxh = 0,auxl = 0;
            auxh = (dis.op1.offset & 0xFF00) >> 8;
            auxl = dis.op1.offset & 0x00FF;
            printf("0%01X %02X %02X ",dis.op1.posicion,auxh,auxl);
            break;
        }
    }


    espacio += 3-tamanio;

    for(i=0; i<=espacio; i++)
        printf("   ");

    //MNEMONICOS
    printf(" | %s ", mnemonicos[dis.codOp]);
    if(dis.codOp<=12){
        //Dos op

        if(dis.op1.tipo == 2){ //registro
            int aux = 0;
            aux = (dis.op1.parteReg << 4) & 0xF0;
            aux = aux | (dis.op1.posicion & 0x0F);;
            strcat(muestra,registros[aux]);
        }
        else{
            strcat(muestra,"[");
            char aux[6];
            strcat(muestra,registros[dis.op1.posicion]);
            strcat(muestra," + ");
            sprintf(aux, "%d", dis.op1.offset);
            strcat(muestra,aux);
            strcat(muestra,"]");
        }
        strcat(muestra,", ");

        //op2

        if(dis.op2.tipo == 2){ //registro
            //strcat(muestra,"[");
            int aux = 0;
            aux = (dis.op2.parteReg << 4) & 0xF0;
            aux = aux | (dis.op2.posicion & 0x0F);
            if(registros[aux != NULL])
                strcat(muestra,registros[aux]);
            else
                printf("NULL! \n");

            //strcat(muestra,"]");
        }
        else if(dis.op2.tipo == 0){ //memoria
            strcat(muestra,"[");
            char aux[6];
            strcat(muestra,registros[dis.op2.posicion]);
            strcat(muestra," + ");
            sprintf(aux, "%d", dis.op2.offset);
            strcat(muestra,aux);
            strcat(muestra,"]");
        }
        else{ //inmediato
            char aux[6];
            long int num;
            if((dis.op2.valor & 0x80000000) == 0x80000000){
                num = dis.op2.valor | 0xFFFF0000;
            }
            else
                num = dis.op2.valor;
            sprintf(aux, "%d", num);
            strcat(muestra,aux);
        }


    }
    else if(dis.codOp>=16 && dis.codOp<=26){
        // 1 operando

        if(dis.op1.tipo == 2){ //registro
            int aux = 0;
            aux = (dis.op2.parteReg << 4) & 0b00110000;
            aux = aux | (dis.op2.posicion & 0b00001111);
            strcat(muestra,registros[aux]);
        }
        else if(dis.op1.tipo == 0){ //memoria
            char aux[6];
            strcat(muestra,"[");
            strcat(muestra,registros[dis.op1.posicion]);
            strcat(muestra," + ");
            sprintf(aux, "%d", dis.op1.offset);
            strcat(muestra,aux);
            strcat(muestra,"]");
        }
        else{ //inmediato
            char aux[6];
            long int num;
            if((dis.op1.valor & 0x80000000) == 0x80000000)
                num = dis.op1.valor | 0xFFFF0000;
            else
                num = dis.op1.valor;
            sprintf(aux, "%d", num);
            strcat(muestra,aux);
        }

    }
    printf(" %s",muestra);

    printf("\n");
}

