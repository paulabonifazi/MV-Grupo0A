//las funciones en sí

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

//2 operandos
void MOV(char *op1, char *op2);

void ADD(char *op1, char *op2);

void SUB(char *op1, char *op2);

void SWAP(char *op1, char *op2);

void MUL(char *op1, char *op2);

void DIV(char *op1, char *op2);

void CMP(char *op1, char *op2);

void SHL(char *op1, char *op2);

void SHR(char *op1, char *op2);

void AND(char *op1, char *op2);

void OR(char *op1, char *op2);

void XOR(char *op1, char *op2);

void RND(char *op1, char *op2);

//1 operando
void SYS(char *op2);

void JMP(char *op2);

void JZ(char *op2);

void JP(char *op2);

void JN(char *op2);

void JNZ(char *op2);

void JNP(char *op2);

void JNN(char *op2);

void LDL(char *op2);

void LDH(char *op2);

void NOT(char *op2);

//0 operandos
void stop();


/*
FUNCIONES

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
