/*
Header File for Assignment 3
Mostafa Rashed
CIS2500
*/
#ifndef _MOVEMENTSH_
#define _MOVEMENTSH_

#include <ncurses.h>
#include <time.h>

#define UP	'w'
#define DOWN	's'
#define LEFT	'a'
#define RIGHT	'd'
#define SPACEBAR	' '
#define QUIT	'q'
#define TRUE	1
#define FALSE	0
#define BOOLEAN	int

typedef struct floorArea
{
    int length;
    int width;
    int posx;
    int posy;
    char ** tokArray;
    int doorx;
    int doory;
}Room;

typedef struct mainPlayer
{
    int posx;
    int posy;
    int goldCount;
    int potionCount;
    int weaponCount;
    int stairs[2];
    char lastChar;
    int currentRoom;
}Hero;

/*
* Movement Function
* This function does the moving of the object, and it also picks up the objects and adds them to the inventory
* Pre: Takes a char for the key and a Hero structure
* Post: A TRUE or FALSE BOOLEAN value
*/
BOOLEAN movement(char keyPressed, Hero * mainHero, Room ** roomArray);

#endif
