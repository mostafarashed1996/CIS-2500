/*************************main.c****************************
Student Name: Mostafa Rashed                        Student Number:  0901940
Date: 13th February 2015                            Course Name: CIS2500
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
int main() {
    // Initialize variables
    int i;
    Cursor * mainCursor;
    char ** commandArray;
    BOOLEAN running = TRUE;
    FILE * infile;
    i = 0;
    // Allocare memory for the array to store commands
    commandArray = malloc(sizeof(char *)*100);
    if (commandArray == NULL)
    {
        printf("Out of memory: exiting\n");
        exit(1);
    }
    for (i = 0; i < 100; i++)
    {
        commandArray[i] = malloc(sizeof(char) * 50);
        if (commandArray[i] == NULL)
        {
            printf("Out of memory: exiting\n");
            exit(1);
        }
    }
    initNcurses();
    mainCursor = malloc(sizeof(Cursor));
    if (mainCursor == NULL)
    {
        printf("Out of memory: exiting\n");
        exit(1);
    }
    initCursor(mainCursor);
    drawGrid();
    // Game loop
    i = 0;
    while (running == TRUE)
    {
        if (commands(mainCursor, commandArray, i) == FALSE)
            running = FALSE;
        i++;
    }
    // Save the game to a text file
    saveGame(infile, commandArray, i);
    endwin();
    return(0);
}
