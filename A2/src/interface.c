/*************************interface.c****************************
Student Name: Mostafa Rashed                        Student Number:  0901940
Date: 13th February 2015                             Course Name: CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include "interface.h"
// This function initializes ncurses and defines colour pairs
// Pre: None
// Post: None
void initNcurses()
{
    /*ncurses initialization */
    initscr();
    cbreak ();
    echo ();
    // start_color();          /* Start color          */
    // init_pair(1, COLOR_CYAN, COLOR_BLACK);
    // init_pair(2, COLOR_GREEN, COLOR_BLACK);
    // init_pair(3, COLOR_WHITE, COLOR_RED);
    // init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    // attron(COLOR_PAIR(3));
    refresh();
}
// Initializes the cursor structure
// Pre: A cursor type structure to initialize
// Post: None
void initCursor(Cursor * mainCursor)
{
    mainCursor->cursorShape = '^';
    mainCursor->posx = 40;
    mainCursor->posy = 19;
    mainCursor->degree = 90;
    mainCursor->penDown = 1;
    mainCursor->hidden = 0;
    mvaddch(mainCursor->posy,mainCursor->posx, mainCursor->cursorShape);
}

// This function draws the inital grid
// Pre: None
// Post: None
void drawGrid()
{
    int i, j;
    for (i = 1; i < MAX_WIDTH; i++)
        mvaddch(0,i,'-');
    for (i = 1; i <= MAX_HEIGHT+1; i++)
    {
        mvaddch(i,0,'|');
        mvaddch(i,MAX_WIDTH-20,'|');
        mvaddch(i,MAX_WIDTH,'|');
        if (i == MAX_HEIGHT)
            for (j = 1; j < MAX_WIDTH-20; j++)
                mvaddch(i,j,'-');
        if (i > MAX_HEIGHT)
            mvaddch(i, 5, '>');
    }
    for (i = 1; i <= MAX_WIDTH; i++)
        mvaddch(MAX_HEIGHT+2, i, '-');
    refresh();
}

// This function handles the main function of the program, which is to do the actual forwards/backwards movements
// Pre: A cursor type and an integer for the distance/steps taken
// Post: None
void drawCursor(Cursor * mainCursor, int distance)
{
    int i;
    int finalDistance;
    finalDistance = 0;
    mvaddch(mainCursor->posy, mainCursor->posx, ' ');
    // Here lies the statements of the 90 degree angles. I used modulus to determine their quadrent, then applied the movement in that direction
    if (mainCursor->degree % 90 == 0 || mainCursor->degree == 0)
    {
        if (mainCursor->degree == 0 || mainCursor->degree%360 == 0)
        {
            mainCursor->cursorShape = '>';
            if (distance + mainCursor->posx > MAX_WIDTH-1)
                finalDistance = MAX_WIDTH-mainCursor->posx-1;
            else
                finalDistance = distance+1;
            if (mainCursor->penDown == 1)
                hline('-', finalDistance);
            mvaddch(mainCursor->posy, mainCursor->posx + finalDistance, mainCursor->cursorShape);
            mainCursor->posx = mainCursor->posx + finalDistance;
        }
        else if (mainCursor->degree%270 == 0||((mainCursor->degree < 0) && (mainCursor->degree%90 == 0) && (mainCursor->degree%180 != 0)))
        {
            mainCursor->cursorShape = 'v';
            if (distance + mainCursor->posy > MAX_HEIGHT-1)
                finalDistance = MAX_HEIGHT-mainCursor->posy-1;
            else
                finalDistance = distance;
            if (mainCursor->penDown == 1)
                vline('|', finalDistance);
            mvaddch(mainCursor->posy + finalDistance, mainCursor->posx+1, mainCursor->cursorShape);
            mainCursor->posy = mainCursor->posy + finalDistance;
            mainCursor->posx = mainCursor->posx + 1;
        }
        else if (mainCursor->degree%180 == 0)
        {
            mainCursor->cursorShape = '<';
            if (mainCursor->posx - distance < 1)
            {
                finalDistance = mainCursor->posx-1;
                mvaddch(mainCursor->posy, 1, mainCursor->cursorShape);
                if (mainCursor->penDown == 1)
                {
                    move(mainCursor->posx, 2);
                    hline('-', finalDistance-1);
                    move(39,7);
                }
            }
            else
            {
                finalDistance = distance;
                mvaddch(mainCursor->posy, mainCursor->posx-finalDistance, mainCursor->cursorShape);
                if (mainCursor->penDown == 1)
                {
                    move(mainCursor->posy, mainCursor->posx-finalDistance+1);
                    hline('-', finalDistance);
                    move(39,7);
                }
                mainCursor->posx = mainCursor->posx-finalDistance;
            }
        }
        else
        {
            mainCursor->cursorShape = '^';
            if (mainCursor->posy - distance < 1)
            {
                finalDistance = mainCursor->posy-1;
                mvaddch(1, mainCursor->posx, mainCursor->cursorShape);
                mainCursor->posy = 1;
                if (mainCursor->penDown == 1)
                {
                    move(2, mainCursor->posx);
                    vline('|', finalDistance-1);
                    move(39,7);
                }
            }
            else
            {
                finalDistance = distance;
                mvaddch(mainCursor->posy-finalDistance-5, mainCursor->posx, mainCursor->cursorShape);
                mainCursor->posy = mainCursor->posy - finalDistance;
                if (mainCursor->penDown == 1)
                {
                    move(mainCursor->posy-finalDistance+1, mainCursor->posx);
                    vline('|', finalDistance);
                    move(39,7);
                }
            }
            mainCursor->posy = mainCursor->posy-finalDistance;
        }
    }
    // Same thing as above, but for 45 degree angles
    else if (mainCursor->degree % 45 == 0)
    {
        if (mainCursor->degree % 315 == 0)
        {
            if (mainCursor->posy+distance>MAX_HEIGHT-1 || mainCursor->posx+distance>MAX_WIDTH-1)
            {
                if (mainCursor->posy+distance>MAX_HEIGHT-1)
                {
                    finalDistance = MAX_HEIGHT-mainCursor->posy-1;
                }
                else
                {
                    finalDistance = MAX_WIDTH-mainCursor->posx-1;
                }
            }
            else
                finalDistance = distance;
            if (mainCursor->penDown == 1)
            {
                for (i = 1; i < finalDistance; i++)
                {
                    mvaddch(mainCursor->posy+i, mainCursor->posx+i, '\\');
                }
            }
            mvaddch(mainCursor->posy + finalDistance, mainCursor->posx + finalDistance, 'O');
            mainCursor->posy = mainCursor->posy + finalDistance;
            mainCursor->posx = mainCursor->posx + finalDistance;
        }
        else if (mainCursor->degree % 225 == 0)
        {
            if (mainCursor->posy+distance>MAX_HEIGHT+1 || mainCursor->posx+distance<1)
            {
                if (mainCursor->posy+distance>MAX_HEIGHT+1)
                {
                    finalDistance = MAX_HEIGHT-mainCursor->posy-1;
                }
                else
                {
                    finalDistance = mainCursor->posx-1;
                }
            }
            else 
                finalDistance = distance;
            if (mainCursor->penDown == 1)
            {
                for (i = 0; i < finalDistance; i++)
                {
                    mvaddch(mainCursor->posy+i, mainCursor->posx-i, '/');
                }
            }
            mvaddch(mainCursor->posy + finalDistance, mainCursor->posx - finalDistance, 'O');
            mainCursor->posy = mainCursor->posy + finalDistance;
            mainCursor->posx = mainCursor->posx - finalDistance;
        }
        else if (mainCursor->degree % 135 == 0)
        {
            if (mainCursor->posy+distance<1 || mainCursor->posx+distance<1)
            {
                if (mainCursor->posy+distance>MAX_HEIGHT+1)
                {
                    finalDistance = mainCursor->posy-1;
                }
                else
                {
                    finalDistance = mainCursor->posx-1;
                }
            }
            else 
                finalDistance = distance;
            if (mainCursor->penDown == 1)
            {
                for (i = 0; i < finalDistance; i++)
                {
                    mvaddch(mainCursor->posy-i, mainCursor->posx-i, '\\');
                }
            }
            mvaddch(mainCursor->posy - finalDistance, mainCursor->posx - finalDistance, 'O');
            mainCursor->posy = mainCursor->posy - finalDistance;
            mainCursor->posx = mainCursor->posx - finalDistance;
        }
        else
        {
            if (mainCursor->posy+distance<1 || mainCursor->posx+distance>MAX_WIDTH-1)
            {
                if (mainCursor->posy+distance>MAX_HEIGHT+1)
                {
                    finalDistance = mainCursor->posy-1;
                }
                else
                {
                    finalDistance = mainCursor->posx-1;
                }
            }
            else 
                finalDistance = distance;
            if (mainCursor->penDown == 1)
            {
                for (i = 0; i < finalDistance; i++)
                {
                    mvaddch(mainCursor->posy-i, mainCursor->posx+i, '/');
                }
            }
            mvaddch(mainCursor->posy - finalDistance, mainCursor->posx + finalDistance, 'O');
            mainCursor->posy = mainCursor->posy - finalDistance;
            mainCursor->posx = mainCursor->posx + finalDistance;
        }
    }
    else
    {
        printf("Other degrees not implemented yet");
    }
}

// This is an important function which analyzes the user inputs and has the if statements to call other functions to preform tasks
// Pre: A cursor type, a dynamic array to store the commands, and an indexing integer
// Post: A TRUE or FALSE boolean answer to determine if the game is still going or not
BOOLEAN commands(Cursor * mainCursor, char ** commandArray, int i)
{
    // Many declerations and initializations
    char command[50];
    char * splittedCommand;
    char *ptr;
    int usrNumber;  
    int j;
    j = 0;
    BOOLEAN hasSpace;
    hasSpace = FALSE;
    usrNumber = 0;
    move(39,7);
    getstr(command);
    mvwprintw(stdscr, 39, 7, "                      ");
    commandArray[i] == command;
    // Print to the side
    mvwprintw(stdscr, 2+i, MAX_WIDTH-18, "%s", command);
    // This checks if there are any space tokens or not, and if there is, split it
    if (strchr(command, ' ') != NULL)
    {
        // First part, the command
        splittedCommand = strtok(command," ");
        // Second part, the condition
        usrNumber = atol(strtok(NULL," "));
    }
    else
        splittedCommand = command;
    // Analyize user input here
    if (strcmp(splittedCommand, "fd") == 0)
    {
        drawCursor(mainCursor, usrNumber);
        return TRUE;
    }
    else if (strcmp(splittedCommand, "bk") == 0)
    {
        drawCursor(mainCursor, -1*usrNumber);
        return TRUE;
    }
    else if (strcmp(splittedCommand, "rt") == 0)
    {
        mainCursor->degree = mainCursor->degree - usrNumber;
        return TRUE;
    }
    else if (strcmp(splittedCommand, "lt") == 0)
    {
        mainCursor->degree = mainCursor->degree + usrNumber;
        return TRUE;
    }
    else if (strcmp(splittedCommand, "pu") == 0)
    {
        mainCursor->penDown = 0;
        return TRUE;
    }
    else if (strcmp(splittedCommand, "pd") == 0)
    {
        mainCursor->penDown = 1;
        return TRUE;
    }
    else if (strcmp(splittedCommand, "st") == 0)
    {
        mainCursor-> hidden = 0;
        mvaddch(mainCursor->posy, mainCursor->posx, mainCursor->cursorShape);
        refresh();
        return TRUE;
    }
    else if (strcmp(splittedCommand, "ht") == 0)
    {
        mainCursor->hidden = 1;
        mvaddch(mainCursor->posy, mainCursor->posx, ' ');
        refresh();
        return TRUE;
    }
    else if (strcmp(splittedCommand, "exit") != 0)
    {
        mvwprintw(stdscr, 38, 7, "don't know how to %s", splittedCommand);
        return TRUE;
    }
    else
        return FALSE;
}
// This command writes the array of commands to a file
// Pre: A file, a dynamic array, and an integer for the index
// Post: None
void saveGame(FILE * infile, char ** commandArray, int i)
{
    int j;
    fopen("save.txt", "w");
    if ( infile == NULL ) { 
        printf("error opening file \n"); 
        exit(0);
    }
    // Write line by line the commands into file
    for (j = 0; j < i; j++)
    {
        fputs(commandArray[j],infile);
    }
    fclose(infile);
}
