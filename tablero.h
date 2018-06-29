#ifndef TABLERO_H
#define TABLERO_H

typedef struct _tablero_t *tablero_t;

tablero_t tablero_vacio();

tablero_t inicializar_tablero(tablero_t tablero);

void mostrar_tablero(tablero_t tablero);

piezas_t pos_inicial(piezas_t piezas);

#endif
