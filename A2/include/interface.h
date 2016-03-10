/*
Header File for a2.c
Mostafa Rashed
CIS2500
*/
/*Include the ncurses library and other libraries*/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH	100
#define MAX_HEIGHT	38
#define TRUE	1
#define FALSE	0
#define BOOLEAN	int

typedef struct arrow
{
    char cursorShape;
    int posx;
    int posy;
    int degree;
    int penDown;
    int hidden;
}Cursor;

void writeHistory(char ** commandArray, int i);
void initNcurses();
void initCursor(Cursor * mainCursor);
void drawGrid();
void drawCursor(Cursor * mainCursor, int distance);
BOOLEAN commands(Cursor * mainCursor, char ** commandArray, int i);
void saveGame(FILE * infile, char ** commandArray, int i);