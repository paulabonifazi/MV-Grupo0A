#include "funciones.h"
#include "Disassembler.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>



void setea_cc(long int resultadoFunc, MV *mv){
    if (resultadoFunc < 0)
        mv->tabla_de_registros[8] = 0x80000000; //  indicador signo
    else if (resultadoFunc == 0)
         mv->tabla_de_registros[8] = 0x40000000; // indicador 0
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
    op1->valor = suma;
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

//---------------------------------------------------------- PODRIAMOS DIVIDIR EL SYS EN SYS 1, 2, 3, 4, 7 Y F-----------------------------------//
/*hacemos un switch entre cada opción y que cada uno llame al sys que corresponde  */

void SYS(TOperando *op, TOperando *op2, MV *mv){
    unsigned int entrada;
    char entradaChar, salidaChar;
    long int salida = 0;
    char tamCeldas = (mv->tabla_de_registros[12] & 0x0000FF00) >> 8; // CH
    char cantCeldas = mv->tabla_de_registros[12] & 0x000000FF; // CL
    unsigned int cantChar = mv->tabla_de_registros[12] & 0x0000FFFF; // CX
    char formato = mv->tabla_de_registros[10] & 0x000000FF; //AL
    int posEDX = mv->tabla_de_registros[13];
    //printf("%d \n",mv->tabla_de_registros[13]);
    //printf("%d \n",mv->RAM[posEDX]);
    if(op->valor == 1){         //READ
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
    else if(op->valor == 2){    //WRITE
        for(int i = 0; i<cantCeldas; i++){
            printf(" [%04X]: ",posEDX);
            salida = 0;
            if(formato & 0b0010){ //Caracter
                for(int j=0; j<tamCeldas; j++){
                    salida = mv->RAM[posEDX++];
                    if(salida >= 32 && salida <= 126)
                        printf("%c ",salida);
                    else
                        printf(". ");
                }
            }
            else{
                for(int j=0; j<tamCeldas; j++){
                    salida = salida | ((mv->RAM[posEDX++] << (8*(tamCeldas-(j+1)))) & (0x000000FF << (8*(tamCeldas-(j+1)))));
                }
                /*if((salida & 0x80000000) == 0x8000){
                    salida = salida | 0xFFFF0000;
                }*/
                if(formato & 0b1000) // Hexa
                    printf("%% %08X ",salida);
                if(formato & 0b0100) //Octal
                    printf("@ %o ",salida);
                if(formato & 0b0001){ // Decimal
                    /*if((salida & 0x00008000) == 0x00008000){
                        salida = salida | 0xFFFF0000;
                    }
                    else{
                        salida = salida & 0x0000FFFF;
                    }*/
                    printf("%d ",salida);
                }
            }
            printf("\n");
        }
    }
    else if(op->valor == 3){ //STRING READ
        if(cantChar != -1){
            for(int j=0; j<cantChar; j++){
                //scanf("%c",&entradaChar);
                entradaChar = getchar();
                mv->RAM[posEDX++] = entradaChar;
            }
            mv->RAM[posEDX] = '\0';
        }
        else{
            entradaChar = getchar();
            while(entradaChar != '\0'){
                mv->RAM[posEDX++] = entradaChar;
                entradaChar = getchar();
            }
            mv->RAM[posEDX] = entradaChar;
        }
    }
    else if(op->valor == 4){    //STRING WRITE
        salidaChar = mv->RAM[posEDX++];
        while(salidaChar != '\0'){
            printf("%c",salidaChar);
            salidaChar = mv->RAM[posEDX++];
        }
        printf("\n");
    }
    else if(op->valor == 7){    //CLEAR SCREEN
        system("cls");
    }
    else if(op->valor == 15){  //BREAKPOINT
        generaImagen(mv);
        char aux = getchar();
        char op = getchar();
        if(op == 'g'){
            mv->breakpoint = 0;
            //Continua ejecucion
        }
        else if(op == 'q'){
            //Aborta ejecucion
            mv->breakpoint = 0;
            STOP(op,op2,mv);
        }
        else if(op == 13){  //13 = ENTER en ASCII
            mv->breakpoint = 1;
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
    long int ms;
    ms = op->valor & 0x0000FFFF;
    mv->tabla_de_registros[9] = (mv->tabla_de_registros[9] & 0xFFFF0000) | ms;
}


void LDH(TOperando *op, TOperando *op2, MV *mv){
    long int ms;
    ms = (op->valor & 0x0000FFFF) << 16;
    mv->tabla_de_registros[9] = (mv->tabla_de_registros[9] & 0x0000FFFF) | ms;
}


void NOT(TOperando *op, TOperando *op2, MV *mv){
    long int not;
    not = ~(op->valor);
    op->valor = not;
    setea_cc(not,mv);
    reset_valor_op(op,mv);
}



/*almacena un dato de 4 bytes en el tope de la pila. Requiere un solo operando que puede ser de
cualquier tipo. Primero decrementa en 4 el valor del registro SP y luego guarda el valor del operando en la
posición de memoria apuntada por SP. */
void PUSH(TOperando *op, TOperando *op2, MV *mv){
    printf("entre al push\n");
    mv->tabla_de_registros[SP] -=4;
    if(mv->tabla_de_registros[SP]<mv->tabla_de_registros[SS]){
        printf("Stack Overflow");
        exit(1);
    }
    //similar a lo que hace reset operando, pero en vez de tomar la posicion del operando, la toma de SP
    unsigned int aux_valor = 0;
    unsigned int posRAM = mv->tabla_de_registros[SP];
    for(int i=0; i<4; i++){
        aux_valor = (op->valor >> (24 - (i*8))) & 0x000000FF;
        aux_valor = aux_valor & 0x000000FF;
        mv->RAM[posRAM++] = aux_valor;
    }
}


/* extrae el dato del tope de pila y lo almacena en el único operando (puede ser de registro o
memoria). Luego incrementa en 4 el valor del registro SP.*/
void POP(TOperando *op, TOperando *op2, MV *mv){
    /*if(pilaVacia || bytesInsuficientes){
        printf("Stack Underflow")
        exit(1);
    }*/
    printf("\n\nentre a pop\n");
    if((mv->tabla_de_registros[6]+4) > (mv->tabla_de_segmentos[3].segmento + mv->tabla_de_segmentos[3].tam)){ /*|| pila vacia*/
        printf("Stack Underflow");
        exit(1);
    }
    if(op->tipo == 0b00){
        unsigned int posRAM = mv->tabla_de_registros[6];
        for(int i=0; i<4; i++){
            op->valor = op->valor | ((mv->RAM[posRAM++] << (24 - (i*8))) & (0x000000FF << (24 - (i*8))));
        }
    }
    else if(op->tipo == 0b10){  //Registro
        switch(op->parteReg) {
            case 0b00: {
                //registro de 4 bytes
                mv->tabla_de_registros[mv->tabla_de_registros[6]] = op->valor;
                break;}
            case 0b01: {
                //4to byte del registro
                mv->tabla_de_registros[mv->tabla_de_registros[6]] = (mv->tabla_de_registros[mv->tabla_de_registros[6]] & 0xFFFFFF00) | (op->valor & 0x000000FF);
                break;}
            case 0b10: {
                //3er byte del registro
                mv->tabla_de_registros[mv->tabla_de_registros[6]] = (mv->tabla_de_registros[mv->tabla_de_registros[6]] & 0xFFFF00FF) | ((op->valor & 0x000000FF) << 8);
                break;}
            case 0b11: {
                //registro de 2 bytes
                mv->tabla_de_registros[mv->tabla_de_registros[6]] = (mv->tabla_de_registros[mv->tabla_de_registros[6]] & 0xFFFF0000) | (op->valor & 0x0000FFFF);
                break;}
        }
    }

    mv->tabla_de_registros[6] +=4;

}


/* efectúa un llamado a una subrutina. Requiere un solo operando que puede ser de cualquier
tipo. Primero almacena en el tope de la pila el valor del IP, que indica la dirección de memoria a la que se
retornará luego de que la subrutina finalice. Luego, realiza un salto a la posición de memoria indicada por
el operando.*/
void CALL(TOperando *op, TOperando *op2, MV *mv){
    mv->tabla_de_registros[SP] -=4;

    printf("\nSP: %X\n", mv->tabla_de_registros[SP]);
    printf("\nSS: %X\n", mv->tabla_de_registros[SS]);

    if(mv->tabla_de_registros[SP]<mv->tabla_de_registros[SS]){
        printf("Stack Overflow");
        exit(1);
    }
    //similar a lo que hace reset operando, pero en vez de tomar la posicion del operando, la toma de SP
    unsigned int aux_valor = 0;
    unsigned int posRAM = mv->tabla_de_registros[6];
    for(int i=0; i<4; i++){
        aux_valor = (mv->tabla_de_registros[IP] >> (24 - (i*8))) & 0x000000FF;
        aux_valor = aux_valor & 0x000000FF;
        mv->RAM[posRAM++] = aux_valor;
    }
    printf("\ndentro del CALL valor que tiene la ip: %X\n", op->valor);
    mv->tabla_de_registros[IP] = op->valor;
}

//0 operandos
void STOP(TOperando *op, TOperando *op2, MV *mv){
    mv->tabla_de_registros[5] = 0xFFFFFFFF;
}


/* efectúa una retorno desde una subrutina. No requiere parámetros. Extrae el valor del tope de la
pila y realiza un salto a esa dirección de memoria.*/
void RET(TOperando *op, TOperando *op2, MV *mv){
    unsigned int posRAM = mv->tabla_de_registros[6];
    long int valor = 0;
    for(int i=0; i<4; i++){
        valor = valor | ((mv->RAM[posRAM++] << (24 - (i*8))) & (0x000000FF << (24 - (i*8))));
    }
    mv->tabla_de_registros[5] = valor;
}

void generaImagen(MV *mv){
    FILE *imagen;

    imagen = fopen(mv->imagen, "wb");

    printf("%s",mv->imagen);
    printf("%s", imagen);

    if(imagen != NULL){
        char id[5] = {'V','M','I','2','4'};
        char version = 1;
        unsigned char aux;

        printf("entro genera imagen. id: %s", id);
        fwrite(id, sizeof(id), 1, imagen);
        fwrite(&version, sizeof(version), 1, imagen);
        fwrite(&(mv->tamanioM), sizeof(mv->tamanioM), 1, imagen);
        for(int i = 0; i<16; i++){
            for(int j = 0; j<4; j++){
                aux = (mv->tabla_de_registros[i] >> (8*(3-j))) & 0x000000FF;
                fwrite(&aux, sizeof(char), 1, imagen);
            }
        }
        for(int i = 0; i<8; i++){   //Aca en la consigna dice 8 pero los segmentos son 5, habria que preguntarlo
            for(int j = 0; j<2; j++){
                aux = (mv->tabla_de_segmentos[i].segmento >> (8*(1-j))) & 0x00FF;
                fwrite(&aux, sizeof(char), 1, imagen);
            }
            for(int j = 0; j<2; j++){
                aux = (mv->tabla_de_segmentos[i].tam >> (8*(1-j))) & 0x00FF;
                fwrite(&aux, sizeof(char), 1, imagen);
            }
        }
        for(int k = 0; k<mv->tamanioM; k++){

            aux = mv->RAM[k];
            fwrite(&aux, sizeof(unsigned char), 1, imagen);
        }
        fclose(imagen);
    }
    else{
        printf("Error al abrir el archivo");
    }
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

    vecF[0x1B]=&PUSH;
    vecF[0x1C]=&POP;
    vecF[0x1D]=&CALL;

    vecF[0x1E]=&RET;
    vecF[0x1F]=&STOP;
}
