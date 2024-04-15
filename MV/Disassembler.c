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

<<<<<<< Updated upstream
void reiniciaOperandos(TDisassembler *ins){
    strcpy((*ins).codoperacion,"");
    (*ins).op1.codOp = 0;
    (*ins).op1.nro = 0;
    (*ins).op1.registro = 0;
    (*ins).op1.tipo = 3;
    (*ins).op1.tamaniocelda = 0;
=======
void reiniciaOperandos(TDisassembler *dis){
    strcpy((*dis).codoperacion, "");
    (*dis).op1.codOp = 0;
    (*dis).op1.nro = 0;
    (*dis).op1.registro = 0;
    (*dis).op1.tipo = 3;
>>>>>>> Stashed changes

    (*ins).op2.codOp = 0;
    (*ins).op2.nro = 0;
    (*ins).op2.registro = 0;
    (*ins).op2.tipo = 3;
    (*ins).op2.tamaniocelda = 0;
    (*ins).instr = 0;
    (*ins).posinstr = 0;
}

<<<<<<< Updated upstream

void cargaIns(TDisassembler *dis, unsigned int posinstr, char instr, char codoperacion[]){
=======
void cargaIns(TDisassembler *dis, short int posinstr, char instr, char codoperacion){
>>>>>>> Stashed changes
    (*dis).posinstr = posinstr;
    (*dis).instr = instr;
    strcpy((*dis).codoperacion, codoperacion);
}


<<<<<<< Updated upstream
void cargaOp(TDisassembler *dis, int nrodeop, char tipo, short int codOp, long int nro, long int registro, char tamaniocelda){
    TOp operando;

    operando.tamaniocelda = tamaniocelda;
    operando.codOp = codOp;
=======
void cargaOp(TDisassembler *dis, int nrodeop, char tipo, char codOp, long int nro, long int registro){
    TOp operando;

    strcpy(operando.codOp, codOp);
>>>>>>> Stashed changes
    operando.nro = nro;
    operando.registro = registro;
    operando.tipo = tipo;

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
<<<<<<< Updated upstream
        case 0: if(operando.tamaniocelda==4)
                    strcpy(muestra,"l");
                else
                    if(operando.tamaniocelda==2)
                       strcpy(muestra,"w");
                    else
                        strcpy(muestra,"b");

=======
        case 0:  printf("\nsoy un op de memoria\n");
                strcpy(muestra,"l");
>>>>>>> Stashed changes
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
    int tamanio, i, espacio = 0;

    printf("\n\ninstr: %02X\n\n", dis.instr);

    printf("[%04X] %02X ", dis.posinstr, ((unsigned int)dis.instr)&0xFF); // 0 en byte mas significativo para que se muestre bien,sino pone todo FFFFFF

    tamanio = (~dis.op1.tipo)&0x03; //el complemento del tipo de operando es su tamaño
    for(i=0; i<tamanio; i++){
        printf("%02X ", dis.op1.codOp&0xFF);
        dis.op1.codOp = dis.op1.codOp>>8;
    }

    espacio += 3-tamanio;
    tamanio = (~dis.op2.tipo)&0x03;

    for(i=0; i<tamanio; i++){
        printf("%02X ",dis.op2.codOp&0xFF);
        dis.op2.codOp = dis.op2.codOp>>8;
    }
    espacio += 3-tamanio;

    for(i=0; i<=espacio; i++)
        printf("   ");
    printf(" | %s ", dis.codoperacion);
    if(dis.op1.tipo != 0x01){
        if(dis.op2.tipo != 0x01){ //2 operandos
            muestraop(1, dis.op1, dis.reg);
            muestraop(2, dis.op2, dis.reg);
        }
        else{ //1 operando
            muestraop(2, dis.op1,dis.reg);
        }
    }
    printf("\n");
}

