#include "funciones.h"

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

//2 operandos
void MOV(TOperando *op1, TOperando *op2) {
    //analizaoperandos()
    op1->valor=op2->valor;
}

/* habria que ver el tipo??
aunque hay que hacerlo para todas las funciones, tal vez se podría realizar la verificación de tipo antes del llamado a cada función y que los operandos
tengan la responsabilidad de ver que hacer para cada caso (cambiar el tipo, posicion, etc)
*/
/*
asigna a un registro o posici�n de memoria un valor, que puede ser el contenido de otro registro,
posici�n de memoria o un valor inmediato.

-> modifico op2 con el valor del op1

*/

void ADD(TOperando *op1, TOperando *op2);

void SUB(TOperando *op1, TOperando *op2);

void MUL(TOperando *op1, TOperando *op2);

void DIV(TOperando *op1, TOperando *op2);

/*
realizan las cuatro operaciones matem�ticas b�sicas. El primer operando debe
ser de registro o memoria, ya que es donde se guarda el resultado. El resultado de estas instrucciones
afecta el valor del registro CC

El DIV tiene la particularidad de que adem�s guarda el resto de la divisi�n
entera (m�dulo) en AC.

-> el registro CC: bit mas significativo es el de signo (1 negativo) y el 2do mas significativo bit de cero (1 si es cero)
*/

void SWAP(TOperando *op1, TOperando *op2);

/*
intercambia los valores de los dos operandos (ambos deben ser registros y/o celdas de
memoria).
*/

void CMP(TOperando *op1, TOperando *op2);
/*
el segundo operando se resta del primero, pero �ste no almacena el
resultado, solamente se modifican los bits NZ del registro CC.
*/

void SHL(TOperando *op1, TOperando *op2);

void SHR(TOperando *op1, TOperando *op2);

/*
realizan desplazamientos a izquierda o a derecha, respectivamente, de los bits
almacenados en un registro o una posici�n de memoria. Tambi�n afectan al registro CC.
En SHL los bits derechos que quedan libres se completan con ceros.
En SHR los bits de la derecha propagan el bit anterior, es decir si el contenido es un n�mero negativo
el resultado seguir� siendo negativo, porque agrega 1. Si era un n�mero positivo, agrega 0.
*/

void AND(TOperando *op1, TOperando *op2);

void OR(TOperando *op1, TOperando *op2);

void XOR(TOperando *op1, TOperando *op2);

/*
efect�an las operaciones l�gicas b�sicas bit a bit entre los operandos y afectan al
registro CC. El resultado se almacena en el primer operando.(calculo que ser� el op2 ya que es el primero que decodificamos)
*/

void RND(TOperando *op1, TOperando *op2);

/*
carga en el primer operando un n�mero aleatorio entre 0 y el valor del segundo operando.

vamos a tener que crear una semilla para la selecci�n de un nro aleatorio
*/

//1 operando
void SYS(TOperando *op2);

void JMP(TOperando *op2);

void JZ(TOperando *op2);

void JP(TOperando *op2);

void JN(TOperando *op2);

void JNZ(TOperando *op2);

void JNP(TOperando *op2);

void JNN(TOperando *op2);

/*
los saltos se dan analizando el valor del CC
*/

void LDL(TOperando *op2);

/*
carga en los 2 bytes menos significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucci�n est� especialmente pensada para poder cargar un inmediato de 16 bits,
aunque tambi�n se puede utilizar con otro tipo de operando.
*/

void LDH(TOperando *op2);

/*
carga en los 2 bytes m�s significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucci�n est� especialmente pensada para poder cargar un inmediato de 16 bits,
aunque tambi�n se puede utilizar con otro tipo de operando.
*/

void NOT(TOperando *op2);

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
