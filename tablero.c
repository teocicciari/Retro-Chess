#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pieza.h"
#include "tablero.h"

struct _tablero_t{
	piezas_t piezas;
	unsigned int length;
};

tablero_t tablero_vacio(){
	tablero_t tablero;
	tablero = calloc(1, sizeof(struct _tablero_t));
	tablero->piezas = piezas_empty();
	tablero->length = 0;
	return(tablero);
}

tablero_t inicializar_tablero(tablero_t tablero){
	tablero = tablero_vacio();
	tablero->length = 32;
	tablero->piezas = pos_inicial(tablero->piezas);
	return(tablero);
}
/*
tablero_t agregar_pieza(tablero_t tablero){
}*/


piezas_t pos_inicial(piezas_t piezas){
	char col[8] = {'a','b','c','d','e','f','g','h'};

	piezas = nueva_pieza(piezas, 1, 'a', 'T');
	piezas = nueva_pieza(piezas, 1, 'b', 'C');
	piezas = nueva_pieza(piezas, 1, 'c', 'A');
	piezas = nueva_pieza(piezas, 1, 'd', 'D');
	piezas = nueva_pieza(piezas, 1, 'e', 'R');
	piezas = nueva_pieza(piezas, 1, 'f', 'A');
	piezas = nueva_pieza(piezas, 1, 'g', 'C');
	piezas = nueva_pieza(piezas, 1, 'h', 'T');

	piezas = nueva_pieza(piezas, 8, 'a', 't');
	piezas = nueva_pieza(piezas, 8, 'b', 'c');
	piezas = nueva_pieza(piezas, 8, 'c', 'a');
	piezas = nueva_pieza(piezas, 8, 'd', 'd');
	piezas = nueva_pieza(piezas, 8, 'e', 'r');
	piezas = nueva_pieza(piezas, 8, 'f', 'a');
	piezas = nueva_pieza(piezas, 8, 'g', 'c');
	piezas = nueva_pieza(piezas, 8, 'h', 't');

	for (int i=0;i<8;i++){
		piezas = nueva_pieza(piezas, 2, col[i], 'P');
	}
	for (int i=0;i<8;i++){
		piezas = nueva_pieza(piezas, 7, col[i], 'p');
	}
	return(piezas);
}

void mostrar_tablero(tablero_t tablero){
	piezas_t piezas = NULL;
	piezas = tablero->piezas;

	char col[8] = {'a','b','c','d','e','f','g','h'};
	char names[12] = {'P','T','A','C','R','D','p','t','a','c','r','d'};
	char tab[8][8];

	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){ 
			tab[i][j] = ' ';
		}
	}

	while (piezas != NULL){
		int i = 0;
		while (piezas->column != col[i]){ i++; }
		int j = 0;
		while (piezas->name != names[j]){ j++; }
		tab[i][piezas->fila] = names[j];
		piezas = piezas->next;
	}

	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){ 
			printf("[%c] ", tab[i][j]);
		}
		printf ("\n");
	}
}
