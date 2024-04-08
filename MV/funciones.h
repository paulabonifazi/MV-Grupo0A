typedef void (*VectorFunciones[32])(MV *mv);    //hasta el 1F

void iniciaVectorFunciones(VectorFunciones);

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

//2 operandos
void MOV(TOperando *op1, TOperando *op2, MV *mv);

void ADD(TOperando *op1, TOperando *op2, MV *mv);

void SUB(TOperando *op1, TOperando *op2, MV *mv);

void SWAP(TOperando *op1, TOperando *op2, MV *mv);

void MUL(TOperando *op1, TOperando *op2, MV *mv);

void DIV(TOperando *op1, TOperando *op2, MV *mv);

void CMP(TOperando *op1, TOperando *op2, MV *mv);

void SHL(TOperando *op1, TOperando *op2, MV *mv);

void SHR(TOperando *op1, TOperando *op2, MV *mv);

void AND(TOperando *op1, TOperando *op2, MV *mv);

void OR(TOperando *op1, TOperando *op2, MV *mv);

void XOR(TOperando *op1, TOperando *op2, MV *mv);

void RND(TOperando *op1, TOperando *op2, MV *mv);

//1 operando
void SYS(TOperando *op2, MV *mv);

void JMP(TOperando *op2, MV *mv);

void JZ(TOperando *op2, MV *mv);

void JP(TOperando *op2, MV *mv);

void JN(TOperando *op2, MV *mv);

void JNZ(TOperando *op2, MV *mv);

void JNP(TOperando *op2, MV *mv);

void JNN(TOperando *op2, MV *mv);

void LDL(TOperando *op2, MV *mv);

void LDH(TOperando *op2, MV *mv);

void NOT(TOperando *op2, MV *mv);

//0 operandos
void stop();

