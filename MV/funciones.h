//types
//cabeceras de las funciones

//decodifica_cod_op

void decodifica_cod_op(char *op1,char *op2,char *cod_op);

char set_operando(char codigo);

char set_cod_op(char codigo);

char set_offset(char codigo);


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
