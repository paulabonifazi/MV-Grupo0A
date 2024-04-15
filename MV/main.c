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

    for(int i=0; i<argc; i++){
        if (strcmp(argv[i],"-d")==0)
            argumento[1]=argv[i];

        if (strlen(argv[i])>4 && (strcmp(argv[i]+strlen(argv[i])-4,".vmx")==0))
            argumento[0]=argv[i];

    }

    ejecutaMV(argumento[0], argumento[1]);

}
