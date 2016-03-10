/*
Header File for a0.c
Mostafa Rashed
CIS2500
*/
/*Include the ncurses library and other libraries*/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UP	'w'
#define DOWN	's'
#define LEFT	'a'
#define RIGHT	'd'

void moveCursor(char direction);