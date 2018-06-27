#ifndef PIEZA_H
#define PIEZA_H

typedef struct _pieza_t *piezas_t;

piezas_t piezas_empty();

piezas_t nueva_pieza(piezas_t piezas, int f, char c, char n);

#endif
