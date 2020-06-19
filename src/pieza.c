#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pieza.h"

struct _pieza_t {
	int fila;
	char column;
	char name;
	casillas_t mov_pos;
	piezas_t next;
};

struct _casillas_t {
	int fil;
	char col;
	casillas_t nextC;
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

piezas_t destroy_piezas(piezas_t pieza){
	assert(pieza != NULL);
	piezas_t sig = pieza->next;
	free(pieza);
	while (sig != NULL){
		sig = sig->next;
		free(sig);
	}
	return(sig);
}

piezas_t busq_pieza(piezas_t piezas, char piezaname, char col, int f){
	piezas_t pieza = NULL;
	if ((piezas->fila != f) | (piezas->column != col)){
		while((piezas->next != NULL) & !((piezas->fila == f) & (piezas->column == col))){
			piezas = piezas->next;
		}
	}
	if ((piezas->fila == f) & (piezas->column == col) & (piezas->name == piezaname)){
		pieza = piezas;
	}
	return(pieza);
}

piezas_t mover_pieza(piezas_t piezas, char piezaname, char colOrig, int filaOrig, char colD, int fD){
	piezas_t pieza = busq_pieza(piezas, piezaname, colOrig, filaOrig);
	piezas_t p = piezas;
	if (pieza == NULL){
		printf("\n Jugada incorrecta, pieza no encontrada \n");
	}
	else if (piezas != pieza){
		while (piezas->next != pieza){
			piezas = piezas->next;
		}
		piezas->next = pieza->next;
		pieza->column = colD;
		pieza->fila = fD;
		pieza->next = p;
		piezas = pieza;
	}
	else if (piezas == pieza){
		pieza->column = colD;
		pieza->fila = fD;
	}
	else {
		printf("\n Jugada incorrecta, algo anda mal \n");
	}
	return(piezas);
}

char pieza_column(piezas_t pieza){
	return(pieza->column);
}

int pieza_fila(piezas_t pieza){
	return(pieza->fila);
}

piezas_t sig_pieza(piezas_t pieza){
	return(pieza->next);
}

char nombre_pieza(piezas_t pieza){
	return(pieza->name);
}
/*
piezas_t eliminar_pieza(piezas_t piezas, piezas_t pieza){
	piezas_t pieza = NULL;
}

bool es_jug_pos(piezas_t tablero, jugada mov){
}

bool es_jug_valida(piezas_t tablero, jugada mov){
}

piezas_t hacer_mov(piezas_t tablero, jugada mov){
}
*/
