#include <stdio.h>
#include <stdlib.h>
#include "Operando.h"
#include "funciones.h"
#include "MV.h"

//punteros a char -> op1, op2
//char -> operacion

//La ejecucion corta solo con stop o tambien sin stop?


// con el vector de arg sabemos que hay que ejecutar, ver los flags!

int main(int argc, char *argv[])
{

    TOperando* opa = NULL;
    TOperando* opb = NULL;
    char cod_op[5]; //4 bits de cod de operación y el mas significativo indica la cantidad de operandos


    /* operandos: primero se hace el alloc y despues se llama a set_operando()*/

    return 0;
}
