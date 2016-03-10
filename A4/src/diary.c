/*************************a3.c****************************
Student Name: Mostafa Rashed                        Student Number:  0901940
Date: 1st April 2014                             Course Name: CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedList.h"
#include "parser.h"
#include "printCals.h"

int main(int argc, char * argv[])
{
    Food * theList;
    if (argc != 2)
    {
        printf("ERROR: NO INPUT FILE, QUITTING\n");
        exit(0);
    }
    theList = parser(argv);
    printCals(theList);
    printList(theList);
    destroyList(theList);
    free(theList);
    return(0);
}