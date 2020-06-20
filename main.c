#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/pieza.h"
#include "src/tablero.h"
#include "src/print.h"

#define MOVE      'm'
#define RESTART   'r'
#define QUIT      'q'
#define START     's'
#define OPTIONS   'o'
#define BACK      'b'
#define YES       'y'
#define NO        'n'

char get_option(void) {
    char option = '\0';
    char line[10];

    if (fgets(line, sizeof line, stdin) != NULL) {
        option = line[0];
    }

    return(option);
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
    char option = 'n';

    tablero_t tablero = tablero_vacio();
    tablero = inicializar_tablero(tablero);

    print_init();
    option = get_option();
    
    switch (option)
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
        break;
    default:
        return(EXIT_SUCCESS);
    }

    
    mostrar_tablero(tablero);
    print_menu();
    
    do {
        first_move_message();
        option = get_option();
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
	            quit_message2();
	            return (EXIT_SUCCESS);
	        default:
	            printf("\nPlease choose a valid option!\n\n");
        }
    } while (option != QUIT);

    return(EXIT_SUCCESS);
}