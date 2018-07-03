#ifndef PIEZA_H
#define PIEZA_H

typedef struct _pieza_t *piezas_t;

piezas_t piezas_empty();

piezas_t nueva_pieza(piezas_t piezas, int f, char c, char n);

piezas_t destroy_piezas(piezas_t pieza);

piezas_t mover_pieza(piezas_t piezas, char piezaname, char colOrig, int filaOrig, char colD, int fD);

char pieza_column(piezas_t pieza);

int pieza_fila(piezas_t pieza);

piezas_t sig_pieza(piezas_t pieza);

char nombre_pieza(piezas_t pieza);

#endif
