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
#include "structControl.h"

void initRoomArray(Room ** roomArray)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        roomArray[i] = malloc(sizeof(Room));
        roomArray[i] -> length = 0;
        roomArray[i] -> width = 0;
        roomArray[i] -> posx = 0;
        roomArray[i] -> posy = 0;
        roomArray[i] -> tokArray = malloc(sizeof(char *)*150);
        roomArray[i] -> doorx = 0;
        roomArray[i] -> doory = 0;
    }
}

void initHero(Hero * mainHero)
{
    mainHero -> posx = 0;
    mainHero -> posy = 0;
    mainHero -> goldCount = 0;
    mainHero -> potionCount = 0;
    mainHero -> weaponCount = 0;
    mainHero -> stairs[0] = 0;
    mainHero -> stairs[1] = 0;
    mainHero -> lastChar = ' ';
    mainHero -> currentRoom = 0;
}

void freeStuff(Room ** roomArray, Hero * mainHero)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        free(roomArray[i] -> tokArray);
        free(roomArray[i]);
    }
    free(roomArray);
    free(mainHero);
}
