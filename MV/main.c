#include <stdio.h>
#include <stdlib.h>
#include "Operando.h"
#include "funciones.h"
#include "MV.h"
#include "Disassembler.h"

int main(int argc, char *argv[])
{
    char* argumento[2];

    argumento[0]=NULL;
    argumento[1]=NULL;

    argumento[0] = argv[1];
    argumento[1] = argv[2];


    ejecutaMV(argumento[0], argumento[1]);

    return 0;
}

