#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "MV.h"
#include "Operando.h"

typedef void (*VectorFunciones[32])(MV *mv);    //hasta el 1F

void iniciaVectorFunciones(VectorFunciones);

/*  ----------------------------------------- FUNCIONES ----------------------------------------------*/

void valorOp(TOperando *op,MV *mv);

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
void SYS(TOperando *op, MV *mv);

void JMP(TOperando *op, MV *mv);

void JZ(TOperando *op, MV *mv);

void JP(TOperando *op, MV *mv);

void JN(TOperando *op, MV *mv);

void JNZ(TOperando *op, MV *mv);

void JNP(TOperando *op, MV *mv);

void JNN(TOperando *op, MV *mv);

void LDL(TOperando *op, MV *mv);

void LDH(TOperando *op, MV *mv);

void NOT(TOperando *op, MV *mv);

//0 operandos
void STOP();

#endif

