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
#include "movements.h"

BOOLEAN movement(char keyPressed, Hero * mainHero, Room ** roomArray)
{
    char nextChar;
    int posx;
    int posy;
    getyx(stdscr,posy,posx);
    // Big switch statement for the up, down, left, right and space keys
    switch (keyPressed)
    {
        // Move to directions if it is legal (within boundries)
        case UP:
            nextChar = mvinch(mainHero -> posy-1, mainHero -> posx);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == posy && mainHero -> stairs[1] == posx)
                    mvaddch(mainHero -> posy, mainHero -> posx, '%');
                else if (mainHero -> lastChar == '+')
                    mvaddch(mainHero -> posy, mainHero -> posx, mainHero -> lastChar);
                else if (mainHero -> lastChar == ' ')
                    mvaddch(mainHero -> posy, mainHero -> posx, ' ');
                else
                    mvaddch(mainHero -> posy, mainHero -> posx, '.');
                mainHero -> posy = mainHero -> posy - 1;
            }
            break;

        case DOWN:
            nextChar = mvinch(mainHero -> posy+1, mainHero -> posx);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == posy && mainHero -> stairs[1] == posx)
                    mvaddch(mainHero -> posy, mainHero -> posx, '%');
                else if (mainHero -> lastChar == '+')
                    mvaddch(mainHero -> posy, mainHero -> posx, mainHero -> lastChar);
                else if (mainHero -> lastChar == ' ')
                    mvaddch(mainHero -> posy, mainHero -> posx, ' ');
                else
                    mvaddch(mainHero -> posy, mainHero -> posx, '.');
                mainHero -> posy = mainHero -> posy + 1;
            }
            break;

        case LEFT:
            nextChar = mvinch(mainHero -> posy, mainHero -> posx-1);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == posy && mainHero -> stairs[1] == posx)
                    mvaddch(mainHero -> posy, mainHero -> posx, '%');
                else if (mainHero -> lastChar == '+')
                    mvaddch(mainHero -> posy, mainHero -> posx, mainHero -> lastChar);
                else if (mainHero -> lastChar == ' ')
                    mvaddch(mainHero -> posy, mainHero -> posx, ' ');
                else
                    mvaddch(mainHero -> posy, mainHero -> posx, '.');
                mainHero -> posx = mainHero -> posx - 1;
            }
            break;

        case RIGHT:
            nextChar = mvinch(mainHero -> posy, mainHero -> posx+1);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == posy && mainHero -> stairs[1] == posx)
                    mvaddch(mainHero -> posy, mainHero -> posx, '%');
                else if (mainHero -> lastChar == '+')
                    mvaddch(mainHero -> posy, mainHero -> posx, mainHero -> lastChar);
                else if (mainHero -> lastChar == ' ')
                    mvaddch(mainHero -> posy, mainHero -> posx, ' ');
                else
                    mvaddch(mainHero -> posy, mainHero -> posx, '.');
                mainHero -> posx = mainHero -> posx + 1;
            }
            break;

        // If the user hits space bar, check if its a legal move and if so add the X in that position
        case QUIT:
            return TRUE;

        default:
            break;
    }
    if (mvinch(mainHero -> posy, mainHero -> posx) == '*')
    {
        mainHero -> goldCount++;
        mvwprintw(stdscr, 0, 90, "%d Gold Pieces", mainHero -> goldCount);
    }
    else if (mvinch(mainHero -> posy, mainHero -> posx) == '!')
    {
        mainHero -> potionCount++;
        mvwprintw(stdscr, 2, 90, "%d Potions", mainHero -> potionCount);
    }
    else if (mvinch(mainHero -> posy, mainHero -> posx) == ')')
    {
        mainHero -> weaponCount++;
        mvwprintw(stdscr, 4, 90, "%d Weapons", mainHero -> weaponCount);
    }
    else if (mvinch(mainHero -> posy, mainHero -> posx) == ' ')
    {
        if (mainHero -> currentRoom == 5)
            mainHero -> currentRoom = 0;
        else
            mainHero -> currentRoom++;
        mainHero -> posy = roomArray[mainHero -> currentRoom] -> doory;
        mainHero -> posx = roomArray[mainHero -> currentRoom] -> doorx;
        mvaddch(mainHero -> posy, mainHero -> posx, '@');
        move(mainHero -> posy, mainHero -> posx);
        mainHero -> lastChar = '+';
        return FALSE;
    }
    else if (mvinch(mainHero -> posy, mainHero -> posx) == '%')
        return TRUE;
    mvaddch(mainHero -> posy, mainHero -> posx, '@');
    move(mainHero -> posy, mainHero -> posx);
    mainHero -> lastChar = nextChar;
    return FALSE;
}
