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

void parser(Room ** roomArray, Hero * mainHero)
{
    char line[MAXLINELENGTH];
    FILE * infile;
    char * tok;
    char * returnValue;
    //char * filename;
    int i;
    int j;
    i = 0;
    //tok = malloc(sizeof(char)*MAXLINELENGTH);
    //filename = malloc(sizeof(char)*40);
    //sprintf(filename, "assets/%s", argv[1]);
    infile = fopen("assets/input.txt", "r");
    if (infile == NULL)
    {
        printf("error opening file \n");
        endwin();
        exit(0);
    }
    returnValue = fgets(line, MAXLINELENGTH, infile);
    while (returnValue != NULL || i < 6)
    {
        j = 0;
        tok = strtok(line, "X");
        roomArray[i] -> length = atol(tok);
        tok = strtok(NULL, " ");
        roomArray[i] -> width = atol(tok);
        setFloorLocation(roomArray, i);
        drawRoom(roomArray[i]);
        tok = strtok(NULL, " ");
        while (tok != NULL)
        {
            if (tok[0] != ' ')
            {
                roomArray[i] -> tokArray[j] = malloc(sizeof(char)*5);
                strcpy(roomArray[i] -> tokArray[j], tok);
                j++;
            }
            tok = strtok(NULL, " ");
        }
        addElement(roomArray[i], mainHero, roomArray[i] -> tokArray, j);
        j = 0;
        i++;
        returnValue = fgets(line, MAXLINELENGTH, infile);
    }
}

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
            }
            else if (tokArray[i][1] == 's')
            {
                mvaddch((roomArray -> posy)+(roomArray -> length), roomArray -> posx + x, '+');
            }
            else if (tokArray[i][1] == 'e')
            {
                mvaddch((roomArray -> posy)+x, roomArray -> posx - 1, '+');
            }
            else if (tokArray[i][1] == 'w')
            {
                mvaddch((roomArray -> posy)+x, roomArray -> posx +(roomArray -> width), '+');
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
            switch(type)
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
// This is the function where the movements get processed
BOOLEAN movement(char keyPressed, Hero * mainHero)
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
    else if (mvinch(mainHero -> posy, mainHero -> posx) == '%')
        return TRUE;
    mvaddch(mainHero -> posy, mainHero -> posx, '@');
    move(mainHero -> posy, mainHero -> posx);
    mainHero -> lastChar = nextChar;
    return FALSE;
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
    parser(roomArray, mainHero);
    move(mainHero -> posy, mainHero -> posx);
    while (endGame == FALSE)
    {
        inputChar = getch();
        endGame = movement(inputChar, mainHero);
    }
    printInventory(mainHero);
    if (getch() == 'g')
        printf("good");
    freeStuff(roomArray, mainHero);
    endwin();
    return(0);
}
