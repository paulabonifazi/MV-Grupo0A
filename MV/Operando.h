typedef struct{
    char tipo;
    unsigned int posicion;
    char parteReg; //la posicion se usa solo para registros y memoria y partereg solo para registros
    long int valor;
    long int offset;
} TOperando;
/* podríamos usar este tipo para los operandos así almacenamos toda la info
    no sé si op1 y op2 sean parte de la MV o definirlas en el main*/

void decodifica_cod_op(TOperando *op1,TOperando *op2,char *cod_op);

void set_operando(TOperando op, char tipo, long int valor);

void set_parteReg(TOperando op, char parteReg);

void set_posicion(TOperando op, unsigned int pos);

void set_offset(TOperando op, long int offset);

TOperando get_operando();

char set_cod_op(char* cod_op);


