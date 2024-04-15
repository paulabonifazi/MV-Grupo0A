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
      char aux;

      printf("incia MV\n");

      *ejecuta = 0;
      fread(identificador, sizeof(identificador),1, programa);
      fread(&version, sizeof(version),1,programa);

      if (strcmp(identificador, "VMX24")){
            printf("verifica programa %s\n", identificador);
        if (version == 1){
            *ejecuta = 1;
            fread(&aux, sizeof(aux), 1, programa);
            tam = aux << 8;
            fread(&aux, sizeof(aux), 1, programa);  //leo tam del codigo
            tam = tam + aux;
            printf("%d\n", tam);

            mv->tabla_de_segmentos[CS].tam = tam;    //seteo tamaño del cs
            mv->tabla_de_segmentos[DS].tam = 16384 - tam;    //al ds le asigno toda la memoria menos el cs
            mv->tabla_de_segmentos[CS].segmento = 0;
            mv->tabla_de_segmentos[DS].segmento =  tam;
            mv->tabla_de_registros[CS] = 0;             //seteo pos del registro CS
            mv->tabla_de_registros[DS] = tam;        //seteo pos del registo DS
            mv->tabla_de_registros[IP] = 0;             //pongo el cero el IP

            //cargo el codigo al code segment
            for (int i=0; i<tam; i++ ){
                fread(&mv->RAM[i], sizeof(char), 1, programa);
            }
        }
        else{
            printf("Version incorrecta");
            exit(1);
        }
      }
      else{
        printf("Identificador incorrecto");
        exit(1);
      }
}

/* metodo que se encarga de mostrar por pantalla el disassembler
    setea los operandos y decifra instrucción ´para mostrarlos por pantalla*/
void printeaDisassembler(MV *mv){
    TDisassembler dis;
    char instr;
    short int codOp;
    short int posInstr;
    TOperando op1,op2;

    printf("Ejecución Maquina Virtual: \n");
    inicializaDisassembler(&dis);

    //la ejecucion se da cuando el IP no sobrepasa el code segment
            while(mv->tabla_de_registros[IP] < mv->tabla_de_segmentos[CS].tam){
                reiniciaOperandos(&dis);
                instr = get_instruccion(mv);
                posInstr = mv->tabla_de_registros[IP];
                decodifica_cod_op(&op1, &op2, &codOp, mv);
            //decodifica_cod_op(TOperando *op1,TOperando *op2,short int *cod_op, MV *mv);

                if(((0x00 <= codOp) && (codOp <= 0x0C)) || ((0x10 <= codOp) && (codOp <= 0x1A)) || (codOp == 0x1F)){
                    cargaIns(&dis,posInstr, instr, codOp);
                    muestra(dis);
                }
                else{
                    printf("Código de operación inválido.");
                    exit(1);
                }
            }
            if(mv->tabla_de_registros[IP] == 0xFFFFFFFF){
                printf("Fin de la ejecución");
                exit(1);
            }

}

/* se pasa el archivo asm para cargarlo a memoria y el flag del disassembler para printear el pograma ejecutandose
    el metodo tiene que llamar a una funcion para iniciar la mv*/
void ejecutaMV(char arch[], char disassembler[]){
    MV mv;
    int ejecuta;
    VectorFunciones vecF;
    FILE* programa;
    short int codOp;
    TOperando op1,op2;

    printf("entre ejecuta mv\n");

    iniciaVectorFunciones(vecF);
    programa = fopen(arch, "rb");

    if(programa == NULL) {
        printf("Error. No se encuentra el archivo.");
        exit(1);
    }
    else{
        iniciaMV(programa, &mv, &ejecuta);
        fclose(programa);
        printf("salió de inviia MV\n");

        if (disassembler != NULL){
            printeaDisassembler(&mv);
        }
        else{
            //la ejecucion se da cuando el IP no sobrepasa el code segment
            while(mv.tabla_de_registros[IP] < mv.tabla_de_segmentos[CS].tam){
                decodifica_cod_op(&op1, &op2, &codOp, &mv);

                if(((0x00 <= codOp) && (codOp <= 0x0C)) || ((0x10 <= codOp) && (codOp <= 0x1A)) || (codOp == 0x1F))
                    vecF[codOp](&op1, &op1, &mv);
                else{
                    printf("Código de operación inválido.");
                    exit(1);
                }
            }
            if(mv.tabla_de_registros[IP] == 0xFFFFFFFF){
                printf("Fin de la ejecución");
                exit(1);
            }
        }
    }
}

