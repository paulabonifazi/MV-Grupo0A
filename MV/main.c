#include <stdio.h>
#include <stdlib.h>
#include "Operando.h"
#include "funciones.h"
#include "MV.h"

//punteros a char -> op1, op2
//char -> operacion

//La ejecucion corta solo con stop o tambien sin stop?
//Corta la ejecucion cuando hay un STOP o cuando IP apunta fuera del CS


// con el vector de arg sabemos que hay que ejecutar, ver los flags!

int main(int argc, char *argv[])
{

    TOperando* opa;
    opa = (TOperando *) malloc (sizeof(TOperando));
    TOperando* opb;
    opb = (TOperando *) malloc (sizeof(TOperando));
    char cod_op[5]; //4 bits de cod de operación y el mas significativo indica la cantidad de operandos
    cod_op[0] = '0';

    MV mv;
    mv.tabla_de_segmentos[0].segmento = 0;
    mv.tabla_de_segmentos[0].tam = 6;
    mv.tabla_de_segmentos[1].segmento = 6;

    //Instruccion ADD [5], 10
    mv.RAM[0] = 0b01000001;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00001010;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;

    decodifica_cod_op(opa,opb,cod_op,&mv);

    ADD(opa,opb,&mv);
    long int aux = 0;
    for(int i = 11; i<15; i++)
        aux = aux + (mv.RAM[i]<<(24-((i-11)*8)));

    printf("%ld",aux);

    /* operandos: primero se hace el alloc y despues se llama a set_operando()*/

    return 0;
}
