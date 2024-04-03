

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

//2 operandos
void MOV(char *op1, char *op2);
/*
asigna a un registro o posición de memoria un valor, que puede ser el contenido de otro registro,
posición de memoria o un valor inmediato.

-> modifico op2 con el valor del op1
*/

void ADD(char *op1, char *op2);

void SUB(char *op1, char *op2);

void MUL(char *op1, char *op2);

void DIV(char *op1, char *op2);

/*
realizan las cuatro operaciones matemáticas básicas. El primer operando debe
ser de registro o memoria, ya que es donde se guarda el resultado. El resultado de estas instrucciones
afecta el valor del registro CC

El DIV tiene la particularidad de que además guarda el resto de la división
entera (módulo) en AC.

-> el registro CC: bit mas significativo es el de signo (1 negativo) y el 2do mas significativo bit de cero (1 si es cero)
*/

void SWAP(char *op1, char *op2);

/*
intercambia los valores de los dos operandos (ambos deben ser registros y/o celdas de
memoria).
*/

void CMP(char *op1, char *op2);
/*
el segundo operando se resta del primero, pero éste no almacena el
resultado, solamente se modifican los bits NZ del registro CC.
*/

void SHL(char *op1, char *op2);

void SHR(char *op1, char *op2);

/*
realizan desplazamientos a izquierda o a derecha, respectivamente, de los bits
almacenados en un registro o una posición de memoria. También afectan al registro CC.
En SHL los bits derechos que quedan libres se completan con ceros.
En SHR los bits de la derecha propagan el bit anterior, es decir si el contenido es un número negativo
el resultado seguirá siendo negativo, porque agrega 1. Si era un número positivo, agrega 0.
*/

void AND(char *op1, char *op2);

void OR(char *op1, char *op2);

void XOR(char *op1, char *op2);

/*
efectúan las operaciones lógicas básicas bit a bit entre los operandos y afectan al
registro CC. El resultado se almacena en el primer operando.(calculo que será el op2 ya que es el primero que decodificamos)
*/

void RND(char *op1, char *op2);

/*
carga en el primer operando un número aleatorio entre 0 y el valor del segundo operando.

vamos a tener que crear una semilla para la selección de un nro aleatorio
*/

//1 operando
void SYS(char *op2);

void JMP(char *op2);

void JZ(char *op2);

void JP(char *op2);

void JN(char *op2);

void JNZ(char *op2);

void JNP(char *op2);

void JNN(char *op2);

/*
los saltos se dan analizando el valor del CC
*/

void LDL(char *op2);

/*
carga en los 2 bytes menos significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucción está especialmente pensada para poder cargar un inmediato de 16 bits,
aunque también se puede utilizar con otro tipo de operando.
*/

void LDH(char *op2);

/*
carga en los 2 bytes más significativos del registro AC, con los 2 bytes menos significativos del
operando. Esta instrucción está especialmente pensada para poder cargar un inmediato de 16 bits,
aunque también se puede utilizar con otro tipo de operando.
*/

void NOT(char *op2);

/*
not lógico bit a bit, afecta al CC
*/

//0 operandos
void stop();


/*
  2 operandos:
        MOV 00
        ADD 01
        SUB 02
        SWAP 03
        MUL 04
        DIV 05
        CMP 06
        SHL 07
        SHR 08
        AND 09
        OR 0A
        XOR 0B
        RND 0C

    1 operando:
        SYS 10
        JMP 11
        JZ 12
        JP 13
        JN 14
        JNZ 15
        JNP 16
        JNN 17
        LDL 18
        LDH 19
        NOT 1A

    0 operandos:
        STOP 1F

*/

void decodifica_cod_op(char *op1,char *op2,char *cod_op) {
        /*en base a los cod de op hay que hacer un switch con los cod de arriba para que se ejecute la función*/
}
