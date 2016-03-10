/*
Header File for Assignment 3
Mostafa Rashed
CIS2500
*/
#ifndef _ROOMH_
#define _ROOMH_

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

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
/*
* printInventory Function
* This function prints the inventory at the end
* Pre: a Hero struct
* Post: None
*/
void printInventory(Hero * mainHero);

#endif
