#include <stdio.h>
#include <unistd.h>

#include "print.h"

void print_init() {
  
    printf(   "\n\t     ****************************\n"
                "\t     ********CHESSPROGRAM********\n"
                "\t     ****************************\n");

    printf("\nAn advance chess IA locked in this old ASCII interface\n\n");
    sleep(2);
                
    printf("\t     *   s: Start a new game!    *\n"
           "\t     *        o: Options         *\n"
           "\t     *          q: Quit          *\n\n"
			);

    printf("Which one? ");
}

void print_menu() {
  printf(" ");
}

void print_options() {
  printf("\nNo options. let's play!\n\n");
  sleep(2);
}

void start_message(){
  // TODO: choose a welcom message
  printf("\nFirst I have to give you a warning:\n");
  sleep(2);
  printf("there is NO WAY you can beat me\n"); 
  sleep(2);
  printf("enjoy your death\n\n"); 
  sleep(2);
}

void quit_message(){
  printf("\nU don't want to play?\n");
  sleep(2);
  printf("me neither.\n");
  sleep(2);
  printf("BYE!\n");
}

void quit_message2(){
  printf("\nAre you sure?\n");
  sleep(1);
  printf("I'm having a great time with you!\n");
  sleep(2);
}

void first_move_message(){
  printf("\nIt's your turn bitch: ");
}

void move_message(){
  printf("\nI'm waiting: ");
}

void standard_message(){
  // TODO: choose a standard message
  printf(" ");
}

void check(){
  // TODO: choose a check message
  printf(" ");
}