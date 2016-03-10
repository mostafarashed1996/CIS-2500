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
#include "main.h"

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("ERROR: NO INPUT FILE, QUITTING\n");
        exit(1);
    }
    Room ** roomArray;
    Hero * mainHero;
    char inputChar;
    BOOLEAN endGame;
    endGame = FALSE;
    roomArray = malloc(sizeof(Room*)*6);
    mainHero = malloc(sizeof(Hero));
    // Initializing variables
    srand(time(NULL));
    initRoomArray(roomArray);
    initHero(mainHero);
    initNcurses();
    parser(roomArray, mainHero, argv);
    move(mainHero -> posy, mainHero -> posx);
    while (endGame == FALSE)
    {
        inputChar = getch();
        endGame = movement(inputChar, mainHero, roomArray);
    }
    printInventory(mainHero);
    if (getch() == 'g')
        printf("good");
    freeStuff(roomArray, mainHero);
    endwin();
    return(0);
}
