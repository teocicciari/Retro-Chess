#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/pieza.h"
#include "src/tablero.h"

#define MOVE      'm'
#define RESTART   'r'
#define QUIT      'q'

char print_menu(void) {
    char result = '\0';
    char line[256];

    printf("\t* m: Hacer movimiento                                        *\n"
           "\t* r: Empezar un juego nuevo                                  *\n"
           "\t* q: Quit                                                    *\n"
			);

    if (fgets(line, sizeof line, stdin) != NULL) {
        result = line[0];
    }

    return(result);
}

tablero_t move(tablero_t tablero/*, planilla_t planilla*/){
    char line[5];
    int co, cd;

    if (fgets(line, sizeof line, stdin) == NULL) {
        printf("move fail");
        return(NULL);
    }
    
    co = line[2] - '0';
    cd = line[4] - '0';

    tablero = hacer_mov(tablero, line[0], line[1], co, line[3], cd);
    return(tablero);
}

int main(void) {
    char option = 'a';

    tablero_t tablero = tablero_vacio();
    tablero = inicializar_tablero(tablero);

    printf(   "\n\t****************\n"
              "\t* CHESSPROGRAM *\n"
              "\t****************\n\n");

    mostrar_tablero(tablero);
    
    do {
        option = print_menu();
        switch (option) {
	        case MOVE:
	            tablero = move(tablero);
                mostrar_tablero(tablero);
	            break;
	        case RESTART:
                tablero = destroy_tablero(tablero);
                tablero = tablero_vacio();
                tablero = inicializar_tablero(tablero);
                mostrar_tablero(tablero);
	            break;
	        case QUIT:
	            printf("Exiting.\n");
	            return (EXIT_SUCCESS);
	        default:
	            printf("\nPlease choose a valid option!\n\n");
        }
    } while (option != QUIT);

    return(EXIT_SUCCESS);
}