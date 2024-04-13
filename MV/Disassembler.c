#include "Disassembler.h"

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

void reiniciaOperandos(TDisassembler *ins){
    strcpy((*ins).codoperacion,"");
    (*ins).op1.codOp = 0;
    (*ins).op1.nro = 0;
    (*ins).op1.registro = 0;
    (*ins).op1.tipo = 3;
    (*ins).op1.tamaniocelda = 0;

    (*ins).op2.codOp = 0;
    (*ins).op2.nro = 0;
    (*ins).op2.registro = 0;
    (*ins).op2.tipo = 3;
    (*ins).op2.tamaniocelda = 0;
    (*ins).instr = 0;
    (*ins).posinstr = 0;
}


void cargaIns(TDisassembler *dis, unsigned int posinstr, char instr, char codoperacion[]){
    (*dis).posinstr = posinstr;
    (*dis).instr = instr;
    strcpy((*dis).codoperacion, codoperacion);
}


void cargaOp(TDisassembler *dis, int nrodeop, char tipo, long int codOp, long int nro, long int registro, char tamaniocelda){
    TOp operando;

    operando.tamaniocelda = tamaniocelda;
    operando.codOp = codOp;
    operando.nro = nro;
    operando.registro = registro;
    operando.tipo = tipo;

    if(nrodeop == 1)
        (*dis).op1 = operando;
    else
        (*dis).op2 = operando;
}


void muestraop( int nroOp, TOp operando,char *registros[]){}

void muestra(TDisassembler dis){ //se llama desde la MV (ver que metodo)
    int tamanio, i, espacio = 0;

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
    if(dis.op1.tipo != 0b11){
        if(dis.op2.tipo != 0b11){ //2 operandos
            muestraop(1, dis.op1, dis.reg);
            muestraop(2, dis.op2, dis.reg);
        }
        else{ //1 operando
            muestraop(2, dis.op1,dis.reg);
        }
    }
    //deberia de imprimir el de 1 op o 0 op??
    printf("\n");
}

