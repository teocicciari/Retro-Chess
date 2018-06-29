#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pieza.h"
#include "tablero.h"

#define MOVE      'm'
#define GO_BACK   'b'
#define RESTART   'r'
#define QUIT      'q'

#define RESULT_PREFIX "\t-> "

/*
char print_menu(void) {
    char result = '\0';
    char *line = NULL;

    printf("\nAJEDREZ By Wubadubalublub\n"
           "\n"
           "\t**************************************************************\n"
           "\t* m: Hacer movimiento                                        *\n"
           "\t* r: Empezar un juego nuevo                                  *\n"
           "\t* b: Volver el movimiento atras                              *\n"
           "\t* q: Quit                                                    *\n"
           "\t**************************************************************\n"
			);

    line = readline_from_stdin();
    if (line != NULL) {
        result = line[0];
    }

    free(line);
    return (result);
}*/

bool is_valid_option(char option) {
    bool result = false;

    result = (option == MOVE || option == RESTART ||
              option == GO_BACK || option == QUIT);

    return (result);
}

/*
string_t get_input(const char *message) { 						//ADAPTAR
    string_t result = NULL;
    printf("\t%s: ", message);
    result = readstring_from_stdin();
    assert(result != NULL);
    return (result);
}

tablero_t move(tablero_t tablero, jugada *planilla){
	jugada movida = NULL;
	movida = get_input("");
	if ((!es_jug_pos(tablero, movida)) || (!es_jug_valida(tablero, movida))){	
		return(tablero);
	}
	planilla = agregar_jug(movida);
	tablero = hacer_mov(tablero, movida);
	return(tablero);
}

tablero_t volver_jugada(tablero_t tablero, jugada *jugadas){
	planilla = borrar_jugada(planilla);
	tablero = deshacer_jugada(tablero);
	ret(tablero);
}
*/

int main(void) {
	tablero_t tablero = tablero_vacio();
  tablero = inicializar_tablero(tablero);
//	jugada *planilla = crear_planilla(planilla);
	mostrar_tablero(tablero);

/*
    char option = '\0';
     print a simple menu and do the requested operations 
    do {
        option = print_menu();
        switch (option) {
	case MOVE:
//	    tablero = move(tablero, planilla);
	    break;
	case RESTART:
//	    tablero = inicializar_tablero(tablero);
	    break;
	case GO_BACK:
//	    tablero = volver_jugada(tablero, planilla);
	    break;
	case QUIT:
//		tablero = tablero_destroy(tablero);
	    printf(RESULT_PREFIX "Exiting.\n");
	    return (EXIT_SUCCESS);
	default:
	    printf("\n\"%c\" is invalid. Please choose a valid "
		   "option.\n\n", option);
        }
    } while (option != QUIT);
*/
    return (EXIT_SUCCESS);
}
