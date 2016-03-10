/*
Header File for a1.c
Mostafa Rashed
CIS2500
*/
/*Include the ncurses library and other libraries*/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UP	'i'
#define DOWN	'k'
#define LEFT	'j'
#define RIGHT	'l'
#define SPACEBAR	' '
#define TRUE	1
#define FALSE	0
#define BOOLEAN	int

void drawGrid();
void initNcurses();
void resetGame();
BOOLEAN legalMove(int ypos, int xpos);
BOOLEAN winCheck();
void playGame(int usrWins, int cpuWins, char name[]);
BOOLEAN movement(char keyPressed);
void fillSurrounding();
BOOLEAN ai();