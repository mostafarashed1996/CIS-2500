/*
Header File for Assignment 3
Mostafa Rashed
CIS2500
*/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UP	'w'
#define DOWN	's'
#define LEFT	'a'
#define RIGHT	'd'
#define SPACEBAR	' '
#define QUIT	'q'
#define MAXLINELENGTH	150
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

void initNcurses();
void parser(Room ** roomArray, Hero * mainHero, char * argv[]);
void setFloorLocation(Room ** roomArray, int i);
void addElement(Room * roomArray, Hero * mainHero, char ** tokArray, int j);
void drawRoom(Room * roomArray);
BOOLEAN movement(char keyPressed, Hero * mainHero, Room ** roomArray);
void printInventory(Hero * mainHero);
void initRoomArray(Room ** roomArray);
void initHero(Hero * mainHero);
void freeStuff(Room ** roomArray, Hero * mainHero);
