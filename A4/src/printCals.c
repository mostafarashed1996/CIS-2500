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
#include "printCals.h"

void printCals(Food * theList)
{
    Food * current;
    current = theList;
    int i;
    double average;
    double cals[5] = {0.0,0.0,0.0,0.0,0.0};
    int count[5] = {0,0,0,0,0};
    if (isEmpty(theList))
        current = theList -> next;
    while (current != NULL)
    {
        if (strcmp("vegfruit", current -> foodGroup) == 0)
        {
            cals[0] = cals[0] + (current -> calories);
            count[0]++;
        }
        else if (strcmp("meat", current -> foodGroup) == 0)
        {
            cals[1] = cals[1] + (current -> calories);
            count[1]++;
        }
        else if (strcmp("dairy", current -> foodGroup) == 0)
        {
            cals[2] = cals[2] + (current -> calories);
            count[2]++;
        }
        else if (strcmp("grains", current -> foodGroup) == 0)
        {
            cals[3] = cals[3] + (current -> calories);
            count[3]++;
        }
        else
        {
            cals[4] = cals[4] + (current -> calories);
            count[4]++;
        }
        current = current -> next;
    }
    printf("%d\n", (int)(cals[0] + cals[1] + cals[2] + cals[3] + cals[4]));
    for (i = 0; i < 5; i++)
    {
        if (count[i] != 0)
        {
            average = cals[i]/count[i];
            printf("%.2f\n", average);
        }
        else
            printf("0.00\n");
    }
}
