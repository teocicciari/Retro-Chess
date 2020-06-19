#ifndef TABLERO_H
#define TABLERO_H

typedef struct _tablero_t *tablero_t;

tablero_t tablero_vacio();

tablero_t inicializar_tablero(tablero_t tablero);

tablero_t destroy_tablero(tablero_t tablero);

tablero_t hacer_mov(tablero_t tablero, char piezaname, char colOrig, int filaOrig, char colDest, int filaDest);

void mostrar_tablero(tablero_t tablero);

piezas_t pos_inicial(piezas_t piezas);

#endif