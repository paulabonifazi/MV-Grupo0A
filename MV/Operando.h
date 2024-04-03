typedef struct TOperando{
    char tipo;
    unsigned int posicion;
    char parteReg; //la posicion se usa solo para registros y memoria y partereg solo para registros
    long int valor;
} TOperando;
/* podríamos usar este tipo para los operandos así almacenamos toda la info
    no sé si op1 y op2 sean parte de la MV o definirlas en el main*/

void decodifica_cod_op(char *op1,char *op2,char *cod_op);

char set_operando(char codigo);

char set_cod_op(char codigo);

char set_offset(char codigo);
