#ifndef BOOL_DEF
#define BOOL_DEF
/*Judi's home made bool type.*/
typedef int bool;
enum {false, true};
#endif
#ifndef _judi_LINKEDLISTH
#define _judi_LINKEDLISTH

/***************************************
struct and operations that work directly on the struct
The struct operations and definition could be in their 
own .c and .h files (and sometimes should be). For the purposes of
this assignment, please leave the struct definition here
****************************************/


struct Food{
 char * name;
 char * foodGroup;
 double calories;
 char type;
 struct Food * next;
};

/*do not remove this typedef. We need it for testing your code */

typedef struct Food Food;


/******************************
 Functions operating on structs 
 *******************************/

/*This function takes in two strings for name and food group, the number of calories 
the food contained and a single character representing the type of food (h for healthy, j for junk). 
The function allocates memory for the struct, initializes the variables to the supplied
values, initializes the next pointer to null and returns a pointer to the allocated memory. 
Returns NULL on failure.The value for name and group are copied into newly allocated memory.
The passed-in memory for name and group must be freed elsewhere in the program.
Memory for the struct must be freed elsewhere in the program. 
*/
Food * createRecord(char * name, char * group, double calories, char theType);


/*This function takes a pointer to a food linked list element and returns a pointer to a string 
that contains the information from the struct formatted
in the following manner: "Name (Food Group):calories[type] The string should not 
contain a newline. Calories should be reported to two decimal places, padding where necessary.
The string memory is allocated in this function and must be freed elsewhere in 
the program.
*/
char * printRecord(Food * toPrint);


/*Takes a pointer to a list element and frees the memory for the internal variables.
the struct itself must be freed separately */
void destroyElement(Food * theElement);

/********************************
List operations
*********************************/


/*addToFront(Food * theList, Food * toBeAdded)
Takes a pointer to the head of the list and an initialized list 
element. Adds the element to the front of the linked list and
returns a pointer to the new head of the list. */
Food * addToFront(Food * theList, Food * toBeAdded);


/*addToBack(Food * theList, Food * toBeAdded)
Takes a pointer to the head of the list and an initialized list 
element. Adds the element to the back of the linked list and
returns a pointer to the head of the list. */
Food * addToBack(Food * theList, Food * toBeAdded);


/*removeFromFront(Food * theList)
Takes a pointer to the head of the list. Removes the front
item from the head of the list. Does not free the memory for 
the item removed. Returns a pointer to the head of the list.
Returns NULL if the list is empty*/
Food * removeFromFront(Food * theList);


/*removeFromBack(Food * theList)
Takes a pointer to the head of the list. Removes the last
item from the head of the list. Does not free the memory for 
the item removed. Returns a pointer to the head of the list.
Returns NULL if the list is empty.
*/
Food * removeFromBack(Food * theList);


/*getLastItem(Food * theList)
Takes a pointer to the head of the list. Returns 
a pointer to the item at the end of the list.
Returns NULL if the list is empty.
*/
Food * getLastItem(Food * theList);


/*isEmpty(Food * theList)
Takes a pointer to the head of the list. Returns 
true if the list is empty and false 
if the list has elements.
*/
bool isEmpty(Food * theList);


/*printList(Food * theList)
Takes a pointer to the head of the list. Prints to stdout
 all of the elements of the list (formatted 
as specified for the printRecord function) separated by newlines.
*/
void printList(Food * theList);


/*destroyList(Food * theList)
Takes a pointer to the list and frees the memory for each struct in the list.
Handles an empty list gracefully.
*/
void destroyList(Food * theList);

#endif
