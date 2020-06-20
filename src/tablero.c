#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	tablero->length = 32;
	tablero->piezas = pos_inicial(tablero->piezas);
	return(tablero);
}

tablero_t hacer_mov(tablero_t tablero, char piezaname, char colOrig, int filaOrig, char colDest, int filaDest){
	tablero->piezas = mover_pieza(tablero->piezas, piezaname, colOrig, filaOrig, colDest, filaDest);
	return(tablero);
}

tablero_t destroy_tablero(tablero_t tablero){
	assert(tablero != NULL);
	tablero->piezas = destroy_piezas(tablero->piezas);
	free(tablero);
	tablero = NULL;
	return(tablero);
}

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
		piezas = nueva_pieza(piezas, 7, col[i], 'p');
	}
	for (int i=0;i<8;i++){
		piezas = nueva_pieza(piezas, 2, col[i], 'P');
	}
	return(piezas);
}

void mostrar_tablero(tablero_t tablero){
	int pfila = 8;
	piezas_t piezas = NULL;
	piezas = tablero->piezas;

	char col[8] = {'a','b','c','d','e','f','g','h'};
	char tab[8][8];

	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){ 
			tab[i][j] = ' ';
		}
	}

	while (piezas != NULL){
		int i = 0;
		while ((pieza_column(piezas) != col[i]) & (i<8)){ 
			i++;
		}
		int j = 1;
		while ((pieza_fila(piezas) != j) & (j<9)){ 
			j++;
		}
		j--;
		tab[j][i] = nombre_pieza(piezas);
		piezas = sig_pieza(piezas);
	}

	printf("\t   ___________________________________\n");
	printf("\t---|                                 |\n");
	for (int i=8;i>0;i--){
		printf("\t %d | ", pfila);
		pfila--;
		for (int j=0;j<8;j++){ 
			printf("[%c] ", tab[i-1][j]);
		}
		if (i == 1){
			printf("|\n\t---|_________________________________|\n");
		}else{
			printf ("|\n\t---|                                 |\n");
		}
	}
	printf("\t    | a | b | c | d | e | f | g | h |\n\n");
}