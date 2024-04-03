typedef void (*VectorFunciones[32])(MV);    //hasta el 1F

void iniciaVectorFunciones(VectorFunciones);

/*cambiar cabeceras de las funciones, poner TOperando!! y pasar la MV
*/

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

//2 operandos
void MOV(TOperando *op1, TOperando *op2);

void ADD(TOperando *op1, TOperando *op2);

void SUB(TOperando *op1, TOperando *op2);

void SWAP(TOperando *op1, TOperando *op2);

void MUL(TOperando *op1, TOperando *op2);

void DIV(TOperando *op1, TOperando *op2);

void CMP(TOperando *op1, TOperando *op2);

void SHL(TOperando *op1, TOperando *op2);

void SHR(TOperando *op1, TOperando *op2);

void AND(TOperando *op1, TOperando *op2);

void OR(TOperando *op1, TOperando *op2);

void XOR(TOperando *op1, TOperando *op2);

void RND(TOperando *op1, TOperando *op2);

//1 operando
void SYS(TOperando *op2);

void JMP(TOperando *op2);

void JZ(TOperando *op2);

void JP(TOperando *op2);

void JN(TOperando *op2);

void JNZ(TOperando *op2);

void JNP(TOperando *op2);

void JNN(TOperando *op2);

void LDL(TOperando *op2);

void LDH(TOperando *op2);

void NOT(TOperando *op2);

//0 operandos
void stop();

