#define cantSeg 2;

typedef struct {
    //
} tabla_segmentos;

typedef struct {

} tabla_registros;


typedef struct {
    char RAM[16384];
    tabla_segmentos  tabla_de_segmentos[cantSeg];
    //tabla de registros
} MV;


