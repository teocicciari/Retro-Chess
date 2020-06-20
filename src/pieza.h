#ifndef PIEZA_H
#define PIEZA_H

// Define structures
typedef struct _pieza_t *piezas_t;
typedef struct _casillas_t *casillas_t;

piezas_t piezas_empty();
piezas_t nueva_pieza(piezas_t piezas, int f, char c, char n);
piezas_t destroy_piezas(piezas_t pieza);
piezas_t mover_pieza(piezas_t piezas, char piezaname, char colOrig, int filaOrig, char colD, int fD);
piezas_t sig_pieza(piezas_t pieza);

// get info for piece
char nombre_pieza(piezas_t pieza);
char pieza_column(piezas_t pieza);
int  pieza_fila(piezas_t pieza);


#endif
