#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/pieza.h"
#include "src/tablero.h"
#include "src/print.h"

#define START     's'
#define RESTART   'r'
#define OPTIONS   'o'
#define BACK      'b'
#define QUIT      'q'

char get_input(void) {
    char input = '\0';
    char line[10];

    if (fgets(line, sizeof line, stdin) != NULL) {
        input = line[0];
    }

    return(input);
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
    char input = 'n';

    tablero_t tablero = tablero_vacio();
    tablero = inicializar_tablero(tablero);

    print_init();
    input = get_input();
    
    switch (input)
    {
    case START:
        start_message();
        break;
    case OPTIONS:
        print_options();
        break;
    case QUIT:
        quit_message();
        return(EXIT_SUCCESS);
    default:
        return(EXIT_SUCCESS);
    }
    
    mostrar_tablero(tablero);
    
    do {
        first_move_message();
        input = get_input();
        switch (input) {
	        case RESTART:
                tablero = destroy_tablero(tablero);
                tablero = tablero_vacio();
                tablero = inicializar_tablero(tablero);
                mostrar_tablero(tablero);
	            break;
	        case QUIT:
	            quit_message2();
	            return (EXIT_SUCCESS);
	        default:
	            tablero = move(tablero);
                mostrar_tablero(tablero);
	            break;
        }
    } while (input != QUIT);

    return(EXIT_SUCCESS);
}