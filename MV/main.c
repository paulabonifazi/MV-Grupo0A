#include <stdio.h>
#include <stdlib.h>
#include "Operando.h"
#include "funciones.h"
#include "MV.h"
#include "Disassembler.h"

//punteros a char -> op1, op2
//char -> operacion

//La ejecucion corta solo con stop o tambien sin stop?
//Corta la ejecucion cuando hay un STOP o cuando IP apunta fuera del CS


// con el vector de arg sabemos que hay que ejecutar, ver los flags!

int main(int argc, char *argv[])
{

    TOperando* opa;
    opa = (TOperando *) malloc (sizeof(TOperando));
    TOperando* opb;
    opb = (TOperando *) malloc (sizeof(TOperando));
    char cod_op[5]; //4 bits de cod de operación y el mas significativo indica la cantidad de operandos
    cod_op[0] = '0';

    MV mv;
    mv.tabla_de_segmentos[0].segmento = 0;
    mv.tabla_de_segmentos[0].tam = 3; // 6 para dos operando mem e inmediato, 4 para un operando mem
    mv.tabla_de_segmentos[1].segmento = 3; // 6 para dos operando mem e inmediato, 4 para un operando mem

    /*Instruccion MOV [5], 37
    mv.RAM[0] = 0b01000000;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00100101;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion ADD [5], 10 con [5] conteniendo 2
    mv.RAM[14] = 0b00000010;
    mv.RAM[0] = 0b01000001;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00001010;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion SUB [5], 10 con [5] conteniendo 3
    mv.RAM[14] = 0b00000011;
    mv.RAM[0] = 0b01000010;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00001010;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion MUL [5], 10 con [5] conteniendo 3
    mv.RAM[14] = 0b00000011;
    mv.RAM[0] = 0b01000100;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00001010;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion DIV [5], 10 con [5] conteniendo 31
    mv.RAM[14] = 0b00011111;
    mv.RAM[0] = 0b01000101;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00001010;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion DIV [5], 10 con [5] conteniendo 30
    mv.RAM[14] = 0b00011110;
    mv.RAM[0] = 0b01000101;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00001010;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion CMP [5], 10 con [5] conteniendo 30
    mv.RAM[14] = 0b00011110;
    mv.RAM[0] = 0b01000110;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00001010;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion SHL [5], 4 con [5] conteniendo 2
    mv.RAM[14] = 0b00000010;
    mv.RAM[0] = 0b01000111;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00000100;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion SHR [5], 4 con [5] conteniendo 16
    mv.RAM[14] = 0b00010000;
    mv.RAM[0] = 0b01001000;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00000100;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion AND [5], 6 con [5] conteniendo 5
    mv.RAM[14] = 0b00000101;
    mv.RAM[0] = 0b01001001;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00000110;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion OR [5], 6 con [5] conteniendo 5
    mv.RAM[14] = 0b00000101;
    mv.RAM[0] = 0b01001010;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00000110;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion XOR [5], 6 con [5] conteniendo 5
    mv.RAM[14] = 0b00000101;
    mv.RAM[0] = 0b01001011;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00000110;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion RND [5], 6 con [5] conteniendo 5
    mv.RAM[14] = 0b00000101;
    mv.RAM[0] = 0b01001100;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00000110;
    mv.RAM[3] = 0b00000001;
    mv.RAM[4] = 0b00000000;
    mv.RAM[5] = 0b00000101;
    */

    /*Instruccion JMP [5] con [5] conteniendo 5
    mv.RAM[12] = 0b00000101;
    mv.RAM[0] = 0b00110001;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00000101;
    */

    /*Instruccion JZ [5] con [5] conteniendo 9
    mv.tabla_de_registros[8] = 0x01000000;
    mv.RAM[12] = 0b00001001;
    mv.RAM[0] = 0b00110010;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00000101;
    */

    /*Instruccion JP [5] con [5] conteniendo 9
    mv.tabla_de_registros[8] = 0x01000000;
    mv.RAM[12] = 0b00001001;
    mv.RAM[0] = 0b00110011;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00000101;
    */

    /*Instruccion JN [5] con [5] conteniendo 9
    mv.tabla_de_registros[8] = 0x00000000;
    mv.RAM[12] = 0b00001001;
    mv.RAM[0] = 0b00110100;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00000101;
    */

    /*Instruccion JNZ [5] con [5] conteniendo 9
    mv.tabla_de_registros[8] = 0x01000000;
    mv.RAM[12] = 0b00001001;
    mv.RAM[0] = 0b00110101;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00000101;
    */

    /*Instruccion JNP [5] con [5] conteniendo 9
    mv.tabla_de_registros[8] = 0x00000000;
    mv.RAM[12] = 0b00001001;
    mv.RAM[0] = 0b00110110;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00000101;
    */

    /*Instruccion JNP [5] con [5] conteniendo 9
    mv.tabla_de_registros[8] = 0x00000000;
    mv.RAM[12] = 0b00001001;
    mv.RAM[0] = 0b00110111;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00000101;
    */

    /*Instruccion SWAP [5], [9] con [5] conteniendo 2 y [9] conteniendo 16
    mv.RAM[15] = 0b00000010;
    mv.RAM[19] = 0b00010000;
    mv.RAM[0] = 0b00000011;
    mv.RAM[1] = 0b00000001;
    mv.RAM[2] = 0b00000000;
    mv.RAM[3] = 0b00001001;
    mv.RAM[4] = 0b00000001;
    mv.RAM[5] = 0b00000000;
    mv.RAM[6] = 0b00000101;
    */

    //*Instruccion SYS 2
    mv.RAM[3] = 'h';
    mv.RAM[4] = 'o';
    mv.RAM[5] = 'l';
    mv.RAM[6] = 'a';
    mv.tabla_de_registros[13] = 3;
    mv.tabla_de_registros[12] = 0b0000000100000100;
    mv.tabla_de_registros[10] = 2;
    mv.RAM[0] = 0b01110000;
    mv.RAM[1] = 0b00000000;
    mv.RAM[2] = 0b00000010;




    decodifica_cod_op(opa,opb,cod_op,&mv);

    SYS(opa,opb,&mv);
    return 0;
    //printf("%x",mv.tabla_de_registros[8]);return 0; // Muestra CC

    //printf("%d",mv.tabla_de_registros[5]);return 0; // Muestra IP

    long int aux = 0;
    for(int i = 11; i<16; i++){
        aux = aux + (mv.RAM[i]<<(24-((i-11)*8)) & 0xFF000000 >> ((i-11)*8));
        //printf("%x \n",aux);
    }


    printf("%ld \n",aux);
    //printf("%ld ",mv.tabla_de_registros[9]); // Muestra AL
    return 0;
    /* operandos: primero se hace el alloc y despues se llama a set_operando()*/
    /*
        Testeo Funciones:
        MOV: Funciona correctamente
        ADD: Funciona correctamente
        SUB: Funciona correctamente
        SWAP: Funciona correctamente
        MUL: Funciona correctamente
        DIV: Funciona correctamente
        CMP: Funciona correctamente
        SHL: Funciona correctamente
        SHR: Funciona correctamente
        AND: Funciona correctamente
        OR: Funciona correctamente
        XOR: Funciona correctamente
        RND: Funciona correctamente

        SYS: WRITE: Funciona correctamente / READ: Sin Probar
        JMP: Funciona correctamente
        JZ: Funciona correctamente
        JP: Funciona correctamente
        JN: Funciona correctamente
        JNZ: Funciona correctamente
        JNP: Funciona correctamente
        JNN: Funciona correctamente
        LDL: Sin probar
        LDH: Sin probar
        NOT: Sin probar

        STOP: Sin probar
    */

}
