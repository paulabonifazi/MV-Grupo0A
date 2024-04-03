//types
//cabeceras de las funciones

//decodifica_cod_op

void decodifica_cod_op(char *op1,char *op2,char *cod_op);

char set_operando(char codigo);

char set_cod_op(char codigo);

char set_offset(char codigo);

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

