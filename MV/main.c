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

    /*
    argumento[0] = argv[1];
    argumento[1] = argv[2];
    */


    //antes era                   vmx.exe filename.vmx [-d]
    // ahora ejecutamos   vmx.exe [filename.vmx] [filename.vmi] [m=M] [-d]

    for(int i =1; i < argc; i++){
        if (strcmp(argv[i],"-d")==0)
            argumento[1]=argv[i];
        if (argv[i][0]=='m' && argv[i][1]=='=')
            tam=argv[i];       //creo que le asigna el tamanio, o seria argumento[2]=argv[i][2]??
       if (strstr(argv[i], ".vmx") != NULL)
            argumento[0] = argv[i];
       if (strstr(argv[i], ".vmi") != NULL)
            argumento[2] = argv[i];

        //convendria tener en argumento[0] el programa traducido y en argumento[3] el archivo imagen?
        //para conocer más rápido la forma de ejecucion de la mv
    }

    if (tam == 0){  //memo ram por default
        tam = TAM_MEMO;
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

