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
/* Note: Some parts of the algorithem are influenced by the 'findTheM' program*/
// Header file with definitions and prototypes
#include "a3.h"

// This function initializes ncurses and defines colour pairs
void initNcurses()
{
    /*ncurses initialization */
    initscr();
    cbreak ();
    noecho ();
    refresh();
}
//void parser(Room room1, Room room2, Room room3, Room room4, Room room5, Room room6)
void parser(Room ** roomArray, Hero * mainHero)
{
    char line[MAXLINELENGTH];
    FILE * infile;
    char * tok;
    char * returnValue;
    //char * filename;
    int i;
    i = 0;
    //filename = malloc(sizeof(char)*40);
    //sprintf(filename, "assets/%s", argv[1]);
    infile = fopen("assets/input.txt", "r");
    if (infile == NULL) { 
        printf("error opening file \n");
        endwin();
        exit(0);
    }
    returnValue = fgets(line, MAXLINELENGTH, infile);
    while (returnValue != NULL)
    {
        tok = strtok(line, "X");
        roomArray[i] -> length = atoi(tok);
        tok = strtok(NULL, " ");
        roomArray[i] -> width = atoi(tok);
        setFloorLocation(roomArray, i);
        drawRoom(roomArray[i]);
        while (tok != NULL)
        {
            tok = strtok(NULL, " ");
            // if (tok != " ")
            // {

            // }
            addElement(roomArray[i], mainHero, tok);
        }
        i++;
        returnValue = fgets(line, MAXLINELENGTH, infile);
    }
}
void setFloorLocation(Room ** roomArray, int i)
{
    if (i%3 == 0)
    {
        roomArray[i] -> posx = 10;
        if (i == 0)
            roomArray[i] -> posy = 15;
        else
            roomArray[i] -> posy = 55;
    }
    else
    {
        roomArray[i] -> posx = 10 + (roomArray[i-1] -> posx);
        roomArray[i] -> posy = (roomArray[i-1] -> posy);
    }
}
void addElement(Room * roomArray, Hero * mainHero, char * tok)
{
    int i;
    int x;
    int y;
    if (tok[0] == 'd')
    {
        x = tok[2] - '0';
        if (tok[1] == 'n')
        {
            mvaddch((roomArray -> posy)-1, roomArray -> posx + x, '+');
        }
        else if (tok[1] == 's')
        {
            mvaddch((roomArray -> posy)+(roomArray -> length)+1, roomArray -> posx + x, '+');
        }
        else if (tok[1] == 'e')
        {
            mvaddch((roomArray -> posy)+x, roomArray -> posx - 1, '+');
        }
        else
        {
            mvaddch((roomArray -> posy)+x, roomArray -> posx +(roomArray -> width)+1, '+');
        }
    }
    else if (tok[0] == 'g')
    {
        y = tok[1] - '0';
        x = tok[3] - '0';
        mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, '*');
        //mainHero -> goldCount = (mainHero -> goldCount) + ((rand()%50) + 1);
    }
    else if (tok[0] == 'm')
    {
        y = tok[1] - '0';
        x = tok[3] - '0';
        //do magic shit
    }
    else if (tok[0] == 'h')
    {
        y = tok[1] - '0';
        x = tok[3] - '0';
        mainHero -> posy = (roomArray -> posy)+y;
        mainHero -> posx = (roomArray -> posx)+x;
        move(mainHero -> posy, mainHero -> posx);
        addch('@');
    }
    else if (tok[0] == 'p')
    {
        y = tok[1] - '0';
        x = tok[3] - '0';
        mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, '!');
        //mainHero -> potionCount = (mainHero -> potionCount) + 1;
    }
    else if (tok[0] == 'w')
    {
        y = tok[1] - '0';
        x = tok[3] - '0';
        mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, ')');
        //mainHero -> weaponCount = (mainHero -> weaponCount) + 1;
    }
    else if (tok[0] == 'M')
    {
        y = tok[1] - '0';
        x = tok[3] - '0';
        mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, 'M');
    }
    else if (tok[0] == 's')
    {
        y = tok[1] - '0';
        x = tok[3] - '0';
        mvaddch((roomArray -> posy)+y, (roomArray -> posx)+x, '%');
        mainHero -> stairs[0] = (roomArray -> posy)+y;
        mainHero -> stairs[1] = (roomArray -> posx)+x;
    }
    else
    {
        //continue();
    }
}
void drawRoom(Room * roomArray)
{
    int i;
    int j;
    for (i = roomArray -> posy; i < (roomArray -> posy + roomArray -> length); i++)
    {
        for (j = roomArray -> posx; j < (roomArray -> posy + roomArray -> width); j++)
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
// This is the function where the movements get processed
BOOLEAN movement(char keyPressed, Hero * mainHero)
{
    char nextChar;
    int x;
    int y;
    getyx(stdscr,y,x);
    // Big switch statement for the up, down, left, right and space keys
    switch (keyPressed)
    {
        // Move to directions if it is legal (within boundries)
        case UP:
            nextChar = mvinch(mainHero -> posy-1, mainHero -> posx);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == y && mainHero -> stairs[1] == x)
                    addch('%');
                else
                    addch('.');
                move(mainHero -> posy-1, mainHero -> posx);
                addch('@');
            }
            break;

        case DOWN:
            nextChar = mvinch(mainHero -> posy+1, mainHero -> posx);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == y && mainHero -> stairs[1] == x)
                    addch('%');
                else
                    addch('.');
                move(mainHero -> posy+1, mainHero -> posx);
                addch('@');
            }
            break;

        case LEFT:
            nextChar = mvinch(mainHero -> posy, mainHero -> posx-1);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == y && mainHero -> stairs[1] == x)
                    addch('%');
                else
                    addch('.');
                move(mainHero -> posy, mainHero -> posx-1);
                addch('@');
            }
            break;

        case RIGHT:
            nextChar = mvinch(mainHero -> posy, mainHero -> posx+1);
            if (nextChar != '-' && nextChar != '|' && nextChar != 'M')
            {
                if (mainHero -> stairs[0] == y && mainHero -> stairs[1] == x)
                    addch('%');
                else
                    addch('.');
                move(mainHero -> posy, mainHero -> posx+1);
                addch('@');
            }
            break;

        // If the user hits space bar, check if its a legal move and if so add the X in that position
        case QUIT:
            return TRUE;

        default:
            printf("Use IJKL to move and q to quit");
    }
    return FALSE;
}
void printInventory(Hero * mainHero)
{
    erase();
    printw("Here is the inventory:");
    if (mainHero -> goldCount > 0)
        printw("%d Gold Pieces", mainHero -> goldCount);
    if (mainHero -> potionCount > 0)
        printw("%d Potions", mainHero -> potionCount);
    if (mainHero -> weaponCount > 0)
        printw("%d Weapons", mainHero -> weaponCount);
}
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
        //roomArray[i].doors = malloc(sizeof(int)*8);
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
}
// Main
int main()
{
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
    //parser(room1, room2, room3, room4, room5, room6);
    parser(roomArray, mainHero);
    while (endGame == FALSE)
    {
        inputChar = getch();
        endGame = movement(inputChar, mainHero);
    }
    printInventory(mainHero);
    endwin();
    return(0);
}
