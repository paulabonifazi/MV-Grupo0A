#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MV.h"
#include "funciones.h"
#include "Disassembler.h"
#include "Operando.h"

//---------------------------------------- creo que deberiamos tener una funcion que chequee la memoria ya que se pasa por cmd el tam de la memoria-----------//

void iniciaMV(FILE *programa, MV *mv, int *ejecuta){
      long int tam;           //tamanio del codigo
      char version, identificador[5];   //version 1 y 2, indentificador = "VMX24"
      char aux;
      *ejecuta = 0;
      fread(identificador, sizeof(identificador),1, programa);
      fread(&version, sizeof(version),1,programa);

      //------------- aca tenemos que asignar el tamanio de la memoria----------------------//

      if (strcmp(identificador, "VMX24")){
        if (version == 1){
            *ejecuta = 1;
            fread(&aux, sizeof(aux), 1, programa);
            tam = aux << 8;
            fread(&aux, sizeof(aux), 1, programa);  //leo tam del codigo
            tam = tam | (aux & 0x000000FF);
            tam = tam & 0x0000FFFF;
            mv->tabla_de_segmentos[CS].tam = tam;    //seteo tamanio del cs
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
        else if (version == 2){
            //----------------------------------------------- ACA TENEMOS QUE CAMBIAR EL SETEO DE LOS SEGMENTOS-----------------------------------------------------------------//
            /* en le header viene  tam CS, DS, ES, SS, KS y el oofset del entry point*/


            /* CAMBIA EL ORDEN EN LA TABLA DE SEGMENTOS!!
                KS - CS - DS - ES - SS
                los indices de segmentos no se condicen con los indices de registros! en los define de CS, Ks, etc corresponden a la tabla de registros*/
                //hacer for para leer todo el header y luego switch para ver que segmento y registro cargar

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
    setea los operandos y decifra instrucci�n �para mostrarlos por pantalla*/
void printeaDisassembler(MV *mv){

    TDisassembler dis;
    VectorFunciones vecF;
    char instr;
    short int codOp;
    short int posInstr;
    TOperando op1,op2;

    printf("Ejecucion Maquina Virtual: \n");
    //inicializaDisassembler(&dis);
    iniciaVectorFunciones(vecF);

    //la ejecucion se da cuando el IP no sobrepasa el code segment
            while(mv->tabla_de_registros[IP] < mv->tabla_de_segmentos[CS].tam){
                posInstr = mv->tabla_de_registros[IP];
                decodifica_cod_op(&op1, &op2, &codOp, mv, &instr);
                if((codOp >> 4) == 0){
                    //dos operandos
                    cargaOp(&dis, 1, op1);
                    cargaOp(&dis, 2, op2);
                }else if(instr>>6 != 0b11){
                    //un operando
                    cargaOp(&dis, 1, op1);
                    cargaOp(&dis, 2, op2);
                }else{
                    //sin operandos, Los operandos del disassembler ya estan inicializados, no se setean
                }

                if(((0x00 <= codOp) && (codOp <= 0x0C)) || ((0x10 <= codOp) && (codOp <= 0x1A)) || (codOp == 0x1F)){
                    cargaIns(&dis, posInstr, instr, codOp);
                    muestra(dis);
                    vecF[codOp](&op1, &op2, mv);
                }
                else{
                    printf("Codigo de operacion invalido.");
                    exit(1);
                }
            }
            if(mv->tabla_de_registros[IP] == 0xFFFFFFFF){
                printf("Fin de la ejecucion");
                exit(1);
            }

}

/* se pasa el archivo asm para cargarlo a memoria y el flag del disassembler para printear el pograma ejecutandose
    el metodo tiene que llamar a una funcion para iniciar la mv*/
void ejecutaMV(char arch[], char disassembler[]){
    MV mv;
    int ejecuta;
    char inst;
    VectorFunciones vecF;
    FILE* programa;
    short int codOp;
    TOperando op1,op2;

    iniciaVectorFunciones(vecF);
    programa = fopen(arch, "rb");

    if(programa == NULL) {
        printf("Error. No se encuentra el archivo.");
        exit(1);
    }
    else{
        iniciaMV(programa, &mv, &ejecuta);
        fclose(programa);

        if (disassembler != NULL){
            printeaDisassembler(&mv);
        }
        else{
            //la ejecucion se da cuando el IP no sobrepasa el code segment
            while(mv.tabla_de_registros[IP] < mv.tabla_de_segmentos[CS].tam){
                decodifica_cod_op(&op1, &op2, &codOp, &mv, &inst);

                if(((0x00 <= codOp) && (codOp <= 0x0C)) || ((0x10 <= codOp) && (codOp <= 0x1A)) || (codOp == 0x1F)){
                    vecF[codOp](&op1, &op2, &mv);}
                else{
                    printf("Codigo de operacion invalido.");
                    exit(1);
                }
            }

            if(mv.tabla_de_registros[IP] == 0xFFFFFFFF){
                printf("Fin de la ejecucion");
                exit(1);
            }
        }
    }
}

