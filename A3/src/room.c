/*************************a3.c****************************
Student Name: Mostafa Rashed                        Student Number:  0901940
Date: 16th January 2014                             Course Name: CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
// Header file with definitions and prototypes
#include "room.h"

void setFloorLocation(Room ** roomArray, int i)
{
    if (i == 0 || i == 3)
    {
        roomArray[i] -> posx = 10;
        if (i == 0)
            roomArray[i] -> posy = 5;
        else
            roomArray[i] -> posy = 25;
    }
    else
    {
        roomArray[i] -> posx = 10 + (roomArray[i-1] -> posx) + (roomArray[i-1] -> width);
        if (i <= 3)
            roomArray[i] -> posy = 25;
        else
            roomArray[i] -> posy = 5;
    }
}

void addElement(Room * roomArray, Hero * mainHero, char ** tokArray, int j)
{
    int i;
    int x;
    int y;
    char type;
    char * tok;
    for (i = 0; i < j; i++)
    {
        if (tokArray[i][0] == 'd')
        {
            x = tokArray[i][2] - '0';
            if (tokArray[i][1] == 'n')
            {
                mvaddch((roomArray -> posy)-1, roomArray -> posx + x, '+');
                roomArray -> doory = (roomArray -> posy)-1;
                roomArray -> doorx = roomArray -> posx + x;
            }
            else if (tokArray[i][1] == 's')
            {
                mvaddch((roomArray -> posy)+(roomArray -> length), roomArray -> posx + x, '+');
                roomArray -> doory = (roomArray -> posy)+(roomArray -> length);
                roomArray -> doorx = roomArray -> posx + x;
            }
            else if (tokArray[i][1] == 'e')
            {
                mvaddch((roomArray -> posy)+x, roomArray -> posx - 1, '+');
                roomArray -> doory = (roomArray -> posy)+x;
                roomArray -> doorx = roomArray -> posx-1;
            }
            else if (tokArray[i][1] == 'w')
            {
                mvaddch((roomArray -> posy)+x, roomArray -> posx +(roomArray -> width), '+');
                roomArray -> doory = (roomArray -> posy)+x;
                roomArray -> doorx = roomArray -> posx + (roomArray -> width);
            }
        }
        else
        {
            type = tokArray[i][0];
            tok = strtok(tokArray[i], &type);
            tok = strtok(tok, ",");
            y = atol(tok)-1;
            tok = strtok(NULL, "\n");
            x = atol(tok)-1;
            switch (type)
            {
                case 'g':
                    mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, '*');
                    break;

                case 'm':
                    mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, '!');
                    break;

                case 'h':
                    mainHero -> posy = (roomArray -> posy)+y;
                    mainHero -> posx = (roomArray -> posx)+x;
                    move(mainHero -> posy, mainHero -> posx);
                    addch('@');
                    break;

                case 'p':
                    mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, '$');
                    break;

                case 'w':
                    mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, ')');
                    break;

                case 'M':
                    mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, 'M');
                    break;

                case 's':
                    mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, '%');
                    mainHero -> stairs[0] = (roomArray -> posy)+y;
                    mainHero -> stairs[1] = (roomArray -> posx)+x;
                    break;

                default:
                    break;

            }
        }
        refresh();
    }
}

void drawRoom(Room * roomArray)
{
    int i;
    int j;
    for (i = roomArray -> posy; i < (roomArray -> posy + roomArray -> length); i++)
    {
        for (j = roomArray -> posx; j < (roomArray -> posx + roomArray -> width); j++)
        {
            mvaddch(i, j, '.');
        }
    }
    for (i = roomArray -> posx; i < (roomArray -> posx + roomArray -> width); i++)
    {
        mvaddch((roomArray -> posy)-1, i, '-');
        mvaddch((roomArray -> posy)+roomArray -> length, i, '-');
    }
    for (i = roomArray -> posy; i < (roomArray -> posy + roomArray -> length); i++)
    {
        mvaddch(i, (roomArray -> posx)-1, '|');
        mvaddch(i, (roomArray -> posx)+roomArray -> width, '|');
    }
}

void printInventory(Hero * mainHero)
{
    erase();
    printw("Here is the inventory:\n");
    printw("%d Gold Pieces\n", mainHero -> goldCount);
    printw("%d Potions\n", mainHero -> potionCount);
    printw("%d Weapons\n", mainHero -> weaponCount);
    printw("Press anything to quit");
}
