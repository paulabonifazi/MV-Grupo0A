#include "funciones.h"

void setea_cc(long int resultadoFunc, MV *mv){
    if (resultadoFunc < 0)
        mv->tabla_de_registros[8] = 0x10000000;
    else if (resultadoFunc == 0)
         mv->tabla_de_registros[8] = 0x01000000;
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
    prod = op1->valor - op2->valor;
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
        //  Aca se lanza error de division por cero
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

/*
intercambia los valores de los dos operandos (ambos deben ser registros y/o celdas de
memoria).
*/

void CMP(TOperando *op1, TOperando *op2, MV *mv){
    long int aux;
    aux = op1->valor - op1->valor;
    setea_cc(aux, mv);
}
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

/*
efect�an las operaciones l�gicas b�sicas bit a bit entre los operandos y afectan al
registro CC. El resultado se almacena en el primer operando.(calculo que ser� el op2 ya que es el primero que decodificamos)
*/

void RND(TOperando *op1, TOperando *op2, MV *mv){
    op1->valor = rand() % (op2->valor + 1);
    reset_valor_op(op1,mv);
}

/*
carga en el primer operando un n�mero aleatorio entre 0 y el valor del segundo operando.

vamos a tener que crear una semilla para la selecci�n de un nro aleatorio
*/

//1 operando
void SYS(TOperando *op, MV *mv);

void JMP(TOperando *op, MV *mv);

void JZ(TOperando *op, MV *mv);

void JP(TOperando *op, MV *mv);

void JN(TOperando *op, MV *mv);

void JNZ(TOperando *op, MV *mv);

void JNP(TOperando *op, MV *mv);

void JNN(TOperando *op, MV *mv);

/*
los saltos se dan analizando el valor del CC
*/

void LDL(TOperando *op, MV *mv){
    int ms;
    ms = op->valor & 0x0000FFFF;
    mv->tabla_de_registros[9] = ms;
}

/*
carga en los 2 bytes menos significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucci�n est� especialmente pensada para poder cargar un inmediato de 16 bits,
aunque tambi�n se puede utilizar con otro tipo de operando.
*/

void LDH(TOperando *op, MV *mv){
    long int ms;
    ms = (op->valor & 0x0000FFFF) << 16;
    mv->tabla_de_registros[9] = ms;
}

/*
carga en los 2 bytes m�s significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucci�n est� especialmente pensada para poder cargar un inmediato de 16 bits,
aunque tambi�n se puede utilizar con otro tipo de operando.
*/

void NOT(TOperando *op, MV *mv){
    long int not;
    not = ~(op->valor);
    op->valor = not;
    setea_cc(not,mv);
    reset_valor_op(op,mv);
}

/*
not l�gico bit a bit, afecta al CC
*/

//0 operandos
void STOP();


/*void decodifica_cod_op(TOperando *op1,TOperando *op2,TOperando *cod_op) {
        /*en base a los cod de op hay que hacer un switch con los cod de arriba para que se ejecute la funci�n*/
        /* con el bit m�s significativo del cod_op m�s los �ltimos 4 se genera el nro de operaci�n. Los �ltimos 4 se pasan a hexa y luego buscamos en el vec de funciones
}
*/

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
