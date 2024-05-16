#include <stdio.h>
#include <stdlib.h>
#include "Operando.h"
#include "funciones.h"
#include "MV.h"
#include "Disassembler.h"

int main(int argc, char *argv[])
{
    char* argumento[3];
    int tam = 0;

    argumento[0]=NULL;  //programa traducido
    argumento[1]=NULL;  //-d
    argumento[2]=NULL;  //archivo imagen

    //version 1                 vmx.exe filename.vmx [-d]
    // version 2                vmx.exe [filename.vmx] [filename.vmi] [m=M] [-d]

    for(int i =1; i < argc; i++){
        if (strcmp(argv[i],"-d")==0)
            argumento[1]=argv[i];
        if (argv[i][0]=='m' && argv[i][1]=='=')
            tam=argv[i];       //creo que le asigna el tamanio, o seria argumento[2]=argv[i][2]??
       if (strstr(argv[i], ".vmx") != NULL)
            argumento[0] = argv[i];
       if (strstr(argv[i], ".vmi") != NULL)
            argumento[2] = argv[i];

    }

    if (argumento[0] != NULL){
        ejecutaMV(argumento[0], argumento[1], tam);
    }
    else{
        ejecutaMV(argumento[2], argumento[1], tam);
    }

    //ejecutaMV(argumento[0], argumento[1]);

    return 0;
}

