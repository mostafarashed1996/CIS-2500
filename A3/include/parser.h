/*
Header File for Assignment 3
Mostafa Rashed
CIS2500
*/
#ifndef _PARSERH_ 
#define _PARSERH_

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINELENGTH	150

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
* parser Function
* This function parses a text file into arrays and variables
* Pre: a Room struct, a Hero struct, and a string
* Post: None
*/
void parser(Room ** roomArray, Hero * mainHero, char * argv[]);
/*
* setFloorLocation Function
* This function sets the x and y values for the room
* Pre: a Room struct and an integer
* Post: None
*/
void setFloorLocation(Room ** roomArray, int i);
/*
* addElement Function
* This function adds the elements such as doors and weapons on the map
* Pre: a Room struct, a Hero struct, a dynamic 2D array and an integer
* Post: None
*/
void addElement(Room * roomArray, Hero * mainHero, char ** tokArray, int j);
/*
* drawRoom Function
* This function draws the room
* Pre: a Room struct
* Post: None
*/
void drawRoom(Room * roomArray);

#endif
