#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MV.h"
#include "funciones.h"

void iniciaMV(FILE *programa, MV *mv, int *ejecuta){
      VectorFunciones vecF;
      unsigned short int tam;           //tamanio del codigo
      char version, identificador[5];   //version 1, indentificador = "VMX24"

      *ejecuta = 0;
      fread(identificador, sizeof(identificador),1, programa);
      fread(&version, sizeof(version),1,programa);

      if (strcmp(identificador, "VMX24")){
        if (version == 1){
            fread(&tam, sizeof(tam), 1, programa);  //leo tam del codigo
            mv->tabla_de_segmentos[0].tam = tam;    //seteo tamaño del cs
            mv->tabla_de_segmentos[1].tam = 16384 - tam;    //al ds le asigno toda la memoria menos el cs
            mv->tabla_de_registros[0] = 0;             //seteo pos del registro CS
            mv->tabla_de_registros[1] = tam;        //seteo pos del registo DS
            mv->tabla_de_registros[5] = 0;             //pongo el cero el IP

            //cargo el codigo al code segment
            for (int i=0; i<tam; i++ ){
                fread(&mv->RAM[i], sizeof(char), 1, programa);
            }
        }
        else
            printf("Version incorrecta");
      }
      else
        printf("Identificador incorrecto");

}

/* se pasa el archivo asm para cargarlo a memoria y el disassembler para printear el pograma ejecutandose
    el metodo tiene que llamar a una funcion para iniciar la mv*/
void ejecutaMV(char arch[], char disassembler[]){
    MV mv;
    int ejecuta;
    FILE* programa;
    char instr,car;
    unsigned char codoperacion;
    TOperando op1,op2;


}
