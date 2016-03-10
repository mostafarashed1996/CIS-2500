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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedList.h"
#include "parser.h"

Food * parser(char * argv[])
{
    char line[MAXLINELENGTH];
    FILE * infile;
    Food * returnFood;
    Food * theList;
    char * name;
    char * group;
    double calories;
    char * type;
    char * returnValue;
    int i;
    i = 0;
    theList = malloc(sizeof(Food));
    infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("error opening file \n");
        exit(0);
    }
    returnValue = fgets(line, MAXLINELENGTH, infile);
    while (returnValue != NULL)
    {
        name = strtok(line, ",");
        group = strtok(NULL, ",");
        calories = atof(strtok(NULL, ","));
        type = strtok(NULL, "\n");
        returnFood = createRecord(name, group, calories, type[0]);
        if (i == 0)
            theList = returnFood;
        else
        {
            if (type[0] == 'h')
                theList = addToFront(theList, returnFood);
            else
                theList = addToBack(theList, returnFood);
        }
        returnValue = fgets(line, MAXLINELENGTH, infile);
        i++;
    }
    return(theList);
}
