/*************************a0.c****************************
Student Name: Mostafa Rashed                        Student Number:  0901940
Date: 8th January 2014                              Course Name: CIS2500
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
#include "a0.h"

int main() {
    char inputChar;

    srand (time(NULL));
    /*ncurses initialization */
    initscr();
    cbreak ();
    noecho ();

    mvwprintw (stdscr, 0, 0, "Use W, A, S, D to sketch and 'q' to Quit!");
    /* Get the input from the user and process the move*/
    inputChar = getch();
    while(inputChar !='q')
    {
        moveCursor(inputChar);
        inputChar = getch();
    }
    /* Refresh the screen*/
    refresh();
    endwin();
	return(0);
}
void moveCursor(char direction){
    int xpos, ypos;
    /* Get x position*/
    getyx(stdscr, ypos,xpos);
    /* Switch for the direction for the Up, Down, Left, Right*/
    switch (direction) 
    {
    /* For each direction make the "lines" to emitate the Etch-a-sketch feeling*/
    case UP:
        mvaddch(ypos, xpos, '|');
        ypos--;
        mvaddch(ypos, xpos, '|');
        break;
    case DOWN:
        ypos++; 
        mvaddch(ypos, xpos, '|');
        break;
    case RIGHT:
        if (mvinch(ypos, xpos) == '|' && mvinch(ypos+1, xpos) != ' ')
            mvaddch(ypos, xpos, ' ');
        xpos++; 
        mvaddch(ypos, xpos, '_');
        break;
    case LEFT:
        if (mvinch(ypos, xpos) == '|' && mvinch(ypos+1, xpos) != ' ')
            mvaddch(ypos, xpos, ' ');
        xpos--;
        mvaddch(ypos, xpos, '_');
        break;
    default:
        mvwprintw (stdscr, 0, 0, "Use W, A, S, D to sketch and 'q' to Quit!");
    }
    /* Move it*/
    move(ypos, xpos);
}