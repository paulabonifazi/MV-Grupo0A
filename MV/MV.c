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

      *ejecuta = 0;
      fread(identificador, sizeof(identificador),1, programa);
      fread(&version, sizeof(version),1,programa);

      if (strcmp(identificador, "VMX24")){
        if (version == 1){
            *ejecuta = 1;
            fread(&aux, sizeof(aux), 1, programa);
            tam = aux << 8;
            fread(&aux, sizeof(aux), 1, programa);  //leo tam del codigo
<<<<<<< Updated upstream
            tam = tam + aux;
            //printf("Tamanio: %d\n",tam);
=======
            tam = tam | (aux & 0x000000FF);
            tam = tam & 0x0000FFFF; //sI SE ROMPE ES ACA
>>>>>>> Stashed changes
            mv->tabla_de_segmentos[CS].tam = tam;    //seteo tama�o del cs
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
    setea los operandos y decifra instrucci�n �para mostrarlos por pantalla*/
void printeaDisassembler(MV *mv){

    TDisassembler dis;
    VectorFunciones vecF;
    char instr;
    short int codOp;
    short int posInstr;
    TOperando op1,op2;

    printf("Ejecucion Maquina Virtual: \n");
    inicializaDisassembler(&dis);
    iniciaVectorFunciones(vecF);

    //la ejecucion se da cuando el IP no sobrepasa el code segment
            while(mv->tabla_de_registros[IP] < mv->tabla_de_segmentos[CS].tam){
<<<<<<< Updated upstream
                //reiniciaOperandos(&dis);
               // printf("mv->tabla_de_registros[IP]: %d \n",mv->tabla_de_registros[IP]);
                //printf("mv->tabla_de_segmentos[CS].tam: %d \n",mv->tabla_de_segmentos[CS].tam);
=======
>>>>>>> Stashed changes
                posInstr = mv->tabla_de_registros[IP];
                decodifica_cod_op(&op1, &op2, &codOp, mv, &instr);
<<<<<<< Updated upstream

                //printf("%d",codOp);
                //seteo los operandos del disassembler
=======
>>>>>>> Stashed changes
                //rearmo toda la instrucción completa y se la seteo al disassembler para que la muestre por consola
                if((codOp >> 4) == 0){
                    //dos operandos
                    cargaOp(&dis, 1, op1);
                    cargaOp(&dis, 2, op2);
                }else if(instr>>6 != 0b11){
                    //un operando
                    cargaOp(&dis, 1, op1);
<<<<<<< Updated upstream
                    //instr = (instr<<2) + op1.tipo;
                    //instr = (instr<<(~op1.tipo)&0x03) + op1.valor;
=======
                    cargaOp(&dis, 2, op2);
>>>>>>> Stashed changes
                }else{
                    //sin operandos, Los operandos del disassembler ya estan inicializados, no se setean
                }

                if(((0x00 <= codOp) && (codOp <= 0x0C)) || ((0x10 <= codOp) && (codOp <= 0x1A)) || (codOp == 0x1F)){
<<<<<<< Updated upstream
                    vecF[codOp](&op1, &op2, mv);
                    //printf("MV mv->tabla_de_registros[12]: %d\n",mv->tabla_de_registros[12]);
                    cargaIns(&dis, posInstr, instr, codOp);
                    muestra(dis);
=======
                    cargaIns(&dis, posInstr, instr, codOp);
                    muestra(dis);
                    vecF[codOp](&op1, &op2, mv);
>>>>>>> Stashed changes
                }
                else{
                    printf("Codigo de operacion invalido.");
                    exit(1);
                }
            }
            if(mv->tabla_de_registros[IP] == 0xFFFFFFFF){
                printf("Fin de la ejecuci�n");
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
                    printf("C�digo de operaci�n inv�lido.");
                    exit(1);
                }
            }

            if(mv.tabla_de_registros[IP] == 0xFFFFFFFF){
                printf("Fin de la ejecuci�n");
                exit(1);
            }
        }
    }
}

