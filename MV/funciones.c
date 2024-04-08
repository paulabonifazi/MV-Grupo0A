#include "funciones.h"

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

//2 operandos
void MOV(TOperando *op1, TOperando *op2, MV *mv){
    //op1->valor=op2->valor;
    if (op1.tipo == 0x00) {     //de memoria
        mv.RAM[mv.tabla_de_segmentos[op1.posicion] + mv.tabla_de_segmentos[op1.offset]] = op2;
    }
    else if(op1.tipo == 0x10) {     //de registro
        unsigned int posAux;
        switch(op1.parteReg) {
            case 0x00: {
                //registro de 4 bytes
                mv.tabla_de_registros[op1.posicion] = op2;
                break;}
            case 0x01: {
                //4to byte del registro
                posAux = op2.posicion & 0xFF;   //me quedo con el byte menos significativo
                mv.tabla_de_registros[op1.posicion] = (mv.tabla_de_registros[op1.posicion] & 0xFFFFFF00) + aux; //me hace ruido la mascara, no se cuantos bytes son. Supongo que 4
                break;}
            case 0x10: {
                //3er byte del registro
                posAux = op2.posicion & 0xFF;   //me quedo con el byte menos significativo
                mv.tabla_de_registros[op1.posicion] = (mv.tabla_de_registros[op1.posicion] & 0xFFFF00FF) + aux;
                break;}
            case 0x11: {
                //registro de 2 bytes
                posAux = op2.posicion & 0xFFFF;   //me quedo con los ultimos 2 bytes
                mv.tabla_de_registros[op1.posicion] = (mv.tabla_de_registros[op1.posicion] & 0xFFFF0000) + aux;
                break;}
        }
    }
    //op1 no puede ser inmediato (cte)
}

void ADD(TOperando *op1, TOperando *op2, MV *mv);

void SUB(TOperando *op1, TOperando *op2, MV *mv);

void MUL(TOperando *op1, TOperando *op2, MV *mv);

void DIV(TOperando *op1, TOperando *op2, MV *mv);

/*
realizan las cuatro operaciones matem�ticas b�sicas. El primer operando debe
ser de registro o memoria, ya que es donde se guarda el resultado. El resultado de estas instrucciones
afecta el valor del registro CC

El DIV tiene la particularidad de que adem�s guarda el resto de la divisi�n
entera (m�dulo) en AC.

-> el registro CC: bit mas significativo es el de signo (1 negativo) y el 2do mas significativo bit de cero (1 si es cero)
*/

void SWAP(TOperando *op1, TOperando *op2, MV *mv);

/*
intercambia los valores de los dos operandos (ambos deben ser registros y/o celdas de
memoria).
*/

void CMP(TOperando *op1, TOperando *op2, MV *mv);
/*
el segundo operando se resta del primero, pero �ste no almacena el
resultado, solamente se modifican los bits NZ del registro CC.
*/

void SHL(TOperando *op1, TOperando *op2, MV *mv);

void SHR(TOperando *op1, TOperando *op2, MV *mv);

/*
realizan desplazamientos a izquierda o a derecha, respectivamente, de los bits
almacenados en un registro o una posici�n de memoria. Tambi�n afectan al registro CC.
En SHL los bits derechos que quedan libres se completan con ceros.
En SHR los bits de la derecha propagan el bit anterior, es decir si el contenido es un n�mero negativo
el resultado seguir� siendo negativo, porque agrega 1. Si era un n�mero positivo, agrega 0.
*/

void AND(TOperando *op1, TOperando *op2, MV *mv);

void OR(TOperando *op1, TOperando *op2, MV *mv);

void XOR(TOperando *op1, TOperando *op2, MV *mv);

/*
efect�an las operaciones l�gicas b�sicas bit a bit entre los operandos y afectan al
registro CC. El resultado se almacena en el primer operando.(calculo que ser� el op2 ya que es el primero que decodificamos)
*/

void RND(TOperando *op1, TOperando *op2, MV *mv);

/*
carga en el primer operando un n�mero aleatorio entre 0 y el valor del segundo operando.

vamos a tener que crear una semilla para la selecci�n de un nro aleatorio
*/

//1 operando
void SYS(TOperando *op2, MV *mv);

void JMP(TOperando *op2, MV *mv);

void JZ(TOperando *op2, MV *mv);

void JP(TOperando *op2, MV *mv);

void JN(TOperando *op2, MV *mv);

void JNZ(TOperando *op2, MV *mv);

void JNP(TOperando *op2, MV *mv);

void JNN(TOperando *op2, MV *mv);

/*
los saltos se dan analizando el valor del CC
*/

void LDL(TOperando *op2, MV *mv);

/*
carga en los 2 bytes menos significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucci�n est� especialmente pensada para poder cargar un inmediato de 16 bits,
aunque tambi�n se puede utilizar con otro tipo de operando.
*/

void LDH(TOperando *op2, MV *mv);

/*
carga en los 2 bytes m�s significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucci�n est� especialmente pensada para poder cargar un inmediato de 16 bits,
aunque tambi�n se puede utilizar con otro tipo de operando.
*/

void NOT(TOperando *op2, MV *mv);

/*
not l�gico bit a bit, afecta al CC
*/

//0 operandos
void stop();


void decodifica_cod_op(TOperando *op1,TOperando *op2,TOperando *cod_op) {
        /*en base a los cod de op hay que hacer un switch con los cod de arriba para que se ejecute la funci�n*/
        /* con el bit m�s significativo del cod_op m�s los �ltimos 4 se genera el nro de operaci�n. Los �ltimos 4 se pasan a hexa y luego buscamos en el vec de funciones */
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
