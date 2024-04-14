#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MV.h"
#include "funciones.h"
#include "Disassembler.h"
#include "Operando.h"

void iniciaMV(FILE *programa, MV *mv, int *ejecuta){
      unsigned short int tam;           //tamanio del codigo
      char version, identificador[5];   //version 1, indentificador = "VMX24"

      *ejecuta = 0;
      fread(identificador, sizeof(identificador),1, programa);
      fread(&version, sizeof(version),1,programa);

      if (strcmp(identificador, "VMX24")){
        if (version == 1){
            *ejecuta = 1;
            fread(&tam, sizeof(tam), 1, programa);  //leo tam del codigo
            mv->tabla_de_segmentos[CS].tam = tam;    //seteo tamaño del cs
            mv->tabla_de_segmentos[DS].tam = 16384 - tam;    //al ds le asigno toda la memoria menos el cs
            mv->tabla_de_registros[CS] = 0;             //seteo pos del registro CS
            mv->tabla_de_registros[DS] = tam;        //seteo pos del registo DS
            mv->tabla_de_registros[IP] = 0;             //pongo el cero el IP

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

/* metodo que se encarga de mostrar por pantalla el disassembler
    setea los operandos y decifra instrucción ´para mostrarlos por pantalla*/
void printeaDisassembler(MV mv){

}

/* se pasa el archivo asm para cargarlo a memoria y el flag del disassembler para printear el pograma ejecutandose
    el metodo tiene que llamar a una funcion para iniciar la mv*/
void ejecutaMV(char arch[], char disassembler[]){
    MV mv;
    int ejecuta;
    VectorFunciones vecF;
    FILE* programa;
    char instr,car;
    unsigned char codOp;
    TOperando op1,op2;

    iniciaVectorFunciones(vecF);
    programa = fopen(arch, "rb");

    if(programa == NULL) {
        printf("Error. No se encuentra el archivo.");
    }
    else{
        iniciaMV(programa, &mv, &ejecuta);
        fclose(arch);

        if (disassembler != NULL){
            printeaDisassembler(mv);
        }
        else{
            //la ejecucion se da cuando el IP no sobrepasa el code segment
            while(mv.tabla_de_registros[IP] < mv.tabla_de_segmentos[CS].tam){
                instr = mv.RAM[(short int)mv.tabla_de_registros[IP]];
                mv.tabla_de_registros[IP]++;     //muevo el IP a la prox instr
                //decodifica_cod_op(&op1, &op2, codOp, inst, &mv);

            }
        }
    }
}
