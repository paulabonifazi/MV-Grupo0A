#include <stdio.h>
#include <stdlib.h>
#include "Operando.h"
#include "funciones.h"
#include "MV.h"
#include "Disassembler.h"

int main(int argc, char *argv[])
{
    char* argumento[3];

    argumento[0]=NULL;  //programa traducido o archivo imagen
    argumento[1]=NULL;  //-d
    argumento[2]=NULL;  //tamanio memo ram


    argumento[0] = argv[1];
    argumento[1] = argv[2];


    //antes era                   vmx.exe filename.vmx [-d]
    // ahora ejecutamos   vmx.exe [filename.vmx] [filename.vmi] [m=M] [-d]

    for(int i =1; i < argc; i++){
        if (strcmp(argv[i],"-d")==0)
            argumento[1]=argv[i];
        if (argv[i][0]=='m' && argv[i][1]=='=')
            argumento[2]=argv[i];       //creo que le asigna el tamanio, o seria argumento[2]=argv[i][2]??

        //convendria tener en argumento[0] el programa traducido y en argumento[3] el archivo imagen?
        //para conocer más rápido la forma de ejecucion de la mv
    }

    ejecutaMV(argumento[0], argumento[1]);

    return 0;
}

