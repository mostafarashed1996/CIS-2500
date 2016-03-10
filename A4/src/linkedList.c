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
// Header file with definitions and prototypes
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedList.h"

Food * createRecord(char * name, char * group, double calories, char theType)
{
    Food * foodStruct;
    foodStruct = malloc(sizeof(Food));
    if (foodStruct == NULL)
        return NULL;
    foodStruct -> name = malloc(sizeof(char *) * 26);
    if (foodStruct -> name == NULL)
        return NULL;
    strcpy(foodStruct -> name, name);
    foodStruct -> foodGroup = malloc(sizeof(char *) * 9);
    if (foodStruct -> foodGroup == NULL)
        return NULL;
    strcpy(foodStruct -> foodGroup, group);
    foodStruct -> calories = calories;
    foodStruct -> type = theType;
    return(foodStruct);
}

char * printRecord(Food * toPrint)
{
    char * str;
    str = malloc(sizeof(char) * 50);
    sprintf(str,"%s (%s): %.2f [%c]", toPrint -> name, toPrint -> foodGroup, toPrint -> calories, toPrint -> type);
    return(str);
}

void destroyElement(Food * theElement)
{
    free(theElement -> name);
    free(theElement -> foodGroup);
}

Food * addToFront(Food * theList, Food * toBeAdded)
{
    toBeAdded -> next = malloc(sizeof(Food));
    if (toBeAdded -> next == NULL)
        return NULL;
    toBeAdded -> next = theList;
    return(toBeAdded);
}

Food * addToBack(Food * theList, Food * toBeAdded)
{
    toBeAdded -> next = malloc(sizeof(Food));
    toBeAdded -> next = NULL;
    if (theList -> next == NULL)
        theList -> next = toBeAdded;
    else
    {
        Food * current;
        current = theList;
        while (current -> next != NULL)
        {
            current = current -> next;
        }
        current -> next = toBeAdded;
    }
    return(theList);
}

Food * removeFromFront(Food * theList)
{
    Food * temp;
    temp = theList;
    while (temp -> next != theList -> next)
    {
        temp -> next = theList -> next;
    }
    theList -> next = temp -> next;
    return(theList);
}

Food * removeFromBack(Food * theList)
{
    Food * temp;
    temp = theList;
    while ((temp -> next) -> next != NULL)
    {
        temp -> next = theList -> next;
    }
    temp -> next = NULL;
    return(temp);
}

Food * getLastItem(Food * theList)
{
    Food * temp;
    temp = theList;
    while ((temp -> next) != NULL)
    {
        temp -> next = theList -> next;
    }
    return(temp -> next);
}

bool isEmpty(Food * theList)
{
    if (theList == NULL || theList -> next == NULL)
        return true;
    else
        return false;
}

void printList(Food * theList)
{
    char * str;
    Food * toPrint;
    toPrint = theList;
    while (toPrint != NULL)
    {
        str = printRecord(toPrint);
        printf("%s\n", str);
        free(str);
        toPrint = toPrint -> next;
    }
}

void destroyList(Food * theList)
{
    Food * current;
    current = theList;
    Food * toFree;
    toFree = current -> next;
    while (current != NULL)
    {
        toFree = current;
        current = toFree -> next;
        destroyElement(toFree);
        free(toFree);
    }
}
