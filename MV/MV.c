#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MV.h"
#include "funciones.h"
#include "Disassembler.h"
#include "Operando.h"


void iniciaMV(FILE *programa, MV *mv){
      long int tam;           //tamanio del codigo
      long int tamTotal = 0;
      long int base = 0;
      int i = 0;
      char version, identificador[5];   //version 1 y 2, indentificador = "VMX24"
      char aux;
      fread(identificador, sizeof(identificador),1, programa);
      fread(&version, sizeof(version),1,programa);

      if (strcmp(identificador, "VMX24")){
        if (version == 1){
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
            while(tamTotal<16384 && i<5){
                fread(&aux, sizeof(aux), 1, programa);
                tam = aux << 8;
                fread(&aux, sizeof(aux), 1, programa);  //leo tam del codigo
                tam = tam | (aux & 0x000000FF);
                tam = tam & 0x0000FFFF;

                tamTotal += tam;
                switch(i){
                    case 0: {
                        //mv->tabla_de_segmentos[CS].segmento = base;
                        mv->tabla_de_segmentos[CS].tam = tam;
                    break;}
                    case 1: {
                        //mv->tabla_de_segmentos[DS].segmento = base;
                        mv->tabla_de_segmentos[DS].tam = tam;
                    break;}
                    case 2: {
                        //mv->tabla_de_segmentos[ES].segmento = base;
                        mv->tabla_de_segmentos[ES].tam = tam;
                    break;}
                    case 3: {
                        //mv->tabla_de_segmentos[SS].segmento = base;
                        mv->tabla_de_segmentos[SS].tam = tam;
                    break;}
                    case 4: {
                        //mv->tabla_de_segmentos[KS].segmento = base;
                        mv->tabla_de_segmentos[KS].tam = tam;
                    break;}
                }
                i +=1;
            }
            //if(tamTotal<16384){
            if(tamTotal<mv->tamanioM){
                mv->tabla_de_segmentos[KS].segmento = base;
                base += mv->tabla_de_segmentos[KS].tam;
                mv->tabla_de_segmentos[CS].segmento = base;
                base += mv->tabla_de_segmentos[CS].tam;
                mv->tabla_de_segmentos[DS].segmento = base;
                base += mv->tabla_de_segmentos[DS].tam;
                mv->tabla_de_segmentos[ES].segmento = base;
                base += mv->tabla_de_segmentos[ES].tam;
                mv->tabla_de_segmentos[SS].segmento = base;
                base += mv->tabla_de_segmentos[SS].tam;

                fread(&aux, sizeof(aux), 1, programa);
                tam = aux << 8;
                fread(&aux, sizeof(aux), 1, programa);
                tam = tam | (aux & 0x000000FF);
                tam = tam & 0x0000FFFF;
                mv->tabla_de_registros[IP] = tam; //ENTRY POINT

                //cargo registros
                mv->tabla_de_registros[CS] = mv->tabla_de_segmentos[CS].segmento;
                mv->tabla_de_registros[DS] = mv->tabla_de_segmentos[DS].segmento;
                mv->tabla_de_registros[ES] = mv->tabla_de_segmentos[ES].segmento;
                mv->tabla_de_registros[SS] = mv->tabla_de_segmentos[SS].segmento;
                mv->tabla_de_registros[KS] = mv->tabla_de_segmentos[KS].segmento;

            }
            else{
                printf("Memoria insuficiente");
                exit(1);
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
void ejecutaMV(char arch[], char disassembler[], int tam){
    MV mv;
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
        //------------------------------------------------ creo que aca deberia de chequear el tam de la memoria-----------------//
        if (tam == 0){  //memo ram por default
            mv.tamanioM = TAM_MEMO;
        }
        else{
            mv.tamanioM = tam*1024; //tam viene en KiB
        }
        iniciaMV(programa, &mv);
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

