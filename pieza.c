#include <stdlib.h>

#include "pieza.h"

struct _pieza_t {
	int fila;
	char column;
	char name;
	piezas_t next;
};

piezas_t piezas_empty(){
	piezas_t piezas = NULL;
	return(piezas);
}

piezas_t nueva_pieza(piezas_t piezas, int f, char c, char n){
	piezas_t pieza = calloc(1, sizeof(struct _pieza_t));
	pieza->fila = f;
	pieza->column = c;
	pieza->name = n;
	pieza->next = piezas;
	return(pieza);
}

/*
bool es_jug_pos(piezas_t tablero, jugada mov){
}

bool es_jug_valida(piezas_t tablero, jugada mov){
}

piezas_t hacer_mov(piezas_t tablero, jugada mov){
}
*/
