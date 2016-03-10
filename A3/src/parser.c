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
#include "parser.h"

void parser(Room ** roomArray, Hero * mainHero, char * argv[])
{
    char line[MAXLINELENGTH];
    FILE * infile;
    char * tok;
    char * returnValue;
    int i;
    int j;
    i = 0;
    endwin();
    printf("%s", argv[1]);
    infile = fopen(argv[1], "r");
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
