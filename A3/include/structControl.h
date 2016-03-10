/*
Header File for Assignment 3
Mostafa Rashed
CIS2500
*/
#ifndef _STRUCTCONTROLH_
#define _STRUCTCONTROLH_

#include <stdlib.h>

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
* initRoomArray Function
* This function initilizes the Room struct
* Pre: a Room struct
* Post: None
*/
void initRoomArray(Room ** roomArray);
/*
* initHero Function
* This function initilizes the Hero struct
* Pre: a Hero struct
* Post: None
*/
void initHero(Hero * mainHero);
/*
* freeStuff Function
* This function frees all the structs and its contents
* Pre: a Room struct and a Hero struct
* Post: None
*/
void freeStuff(Room ** roomArray, Hero * mainHero);

#endif
