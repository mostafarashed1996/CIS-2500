/*************************a1.c****************************
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
/* Note: Some parts of the algorithem are influenced by the 'findTheM' program*/
#include "a1.h"

int main() {
    char name[50];
    initNcurses();
    mvwprintw (stdscr, 0, 0, "Please enter your name (hit ENTER when you're done): ");
    getnstr(name, 50);
    int usrWins, cpuWins;
    usrWins = 0, cpuWins = 0;
    playGame(usrWins, cpuWins, name);
    endwin();
    return(0);
}
void initNcurses() {
    /*ncurses initialization */
    initscr();
    cbreak ();
    noecho ();
    start_color();          /* Start color          */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(3));
    refresh();
}
void resetGame() {
    int i, j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            mvaddch(i, 24, ' ');
        }
    }
}
BOOLEAN legalMove(int ypos, int xpos) {
    char nextSpace;
    nextSpace = mvinch(ypos, xpos);
    if (nextSpace == ' ')
        return TRUE;
    else
        return FALSE;
}
BOOLEAN winCheck() {
    int i, j;
    for (i = 1; i < 12; i=i+2) {
        for (j = 2; j < 24; j=j+4) {
            if (mvinch(i, j) == ' ')
                return FALSE;
        }
    }
    return TRUE;
}
BOOLEAN ai() {
    int i, j;
    for (i = 1; i < 12; i=i+2) {
        for (j = 2; j < 24; j=j+4) {
            if (mvinch(i, j) == ' ') {
                attron(COLOR_PAIR(2));
                mvaddch(i, j, 'O');
                fillSurrounding(i, j);
                return TRUE;
            }
        }
    }
    return FALSE;
}
void instructions() {
    attron(COLOR_PAIR(4));
    mvwprintw(stdscr, 14, 0, "INSTRUCTIONS:");
    mvwprintw(stdscr, 16, 0, "Use i, j, k, l to move and 'q' to quit");
    mvwprintw(stdscr, 18, 0, "Use space to plot your point");
    mvwprintw(stdscr, 20, 0, "The first player that can't move, loses!");
}
void fillSurrounding(int ypos, int xpos) {
    if (ypos != 1 && mvinch(ypos-2, xpos) == ' ')
        mvaddch(ypos-2, xpos, '-');
    if (ypos != 11 && mvinch(ypos+2, xpos) == ' ')
        mvaddch(ypos+2, xpos, '-');
    if (xpos != 1 && mvinch(ypos, xpos-4) == ' ')
        mvaddch(ypos, xpos-4, '-');
    if (xpos != 22 && mvinch(ypos, xpos+4) == ' ')
        mvaddch(ypos, xpos+4, '-');
    if (ypos != 1 && xpos != 1 && mvinch(ypos-2, xpos-4) == ' ')
        mvaddch(ypos-2, xpos-4, '-');
    if (ypos != 11 && xpos != 1 && mvinch(ypos+2, xpos-4) == ' ')
        mvaddch(ypos+2, xpos-4, '-');
    if (ypos != 1 && xpos != 22 && mvinch(ypos-2, xpos+4) == ' ')
        mvaddch(ypos-2, xpos+4, '-');
    if (ypos != 11 && xpos != 22 && mvinch(ypos+2, xpos+4) == ' ')
        mvaddch(ypos+2, xpos+4, '-');
}
void playGame(int usrWins, int cpuWins, char name[]) {
    char inputChar;
    int ypos, xpos, counter;
    BOOLEAN win;
    win = FALSE;
    counter = 0;
    getmaxyx(stdscr, ypos, xpos);
    erase();
    drawGrid();
    mvwprintw(stdscr, 1, (xpos/2) - 15, "SCOREBOARD:");
    attron(COLOR_PAIR(1));
    mvwprintw(stdscr, 3, (xpos/2) - 15, "User Wins: %d", usrWins);
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr, 3, (xpos/2), "Computer Wins: %d", cpuWins);
    instructions();
    move(1,2);
    inputChar = getch();
    while (inputChar !='q' && win != TRUE)
    {
        attron(COLOR_PAIR(1));
        while (movement(inputChar) == FALSE && inputChar !='q')
            inputChar = getch();
        if (inputChar !='q')
            exit(0);
        counter++;
        win = winCheck();
        if (win == TRUE)
            break;
        ai();
        counter++;
        win = winCheck();
        move(1,2);
    }
    if (counter % 2 != 0) {
        mvwprintw (stdscr, (ypos/2)-5, (xpos/2) - 22, "Congrats %s! You won! -- If you want to play again, press space", name);
        usrWins++;
    }
    else {
        mvwprintw (stdscr, (ypos/2)-5, (xpos/2) - 22, "The computer won! -- If you want to play again, press space");
        cpuWins++;
    }
    if (getch() == SPACEBAR) {
        attron(COLOR_PAIR(3));
        playGame(usrWins, cpuWins, name);
    }    
}
BOOLEAN movement(char keyPressed) {
    int ypos, xpos;
    getyx(stdscr, ypos, xpos);
    switch(keyPressed) {
        case UP:
            if (ypos != 1)
                move(ypos-2, xpos);
            break;
        case DOWN:
            if (ypos != 11)
                move(ypos+2, xpos);
            break;
        case LEFT:
            if (xpos != 1)
                move(ypos, xpos-4);
            break;
        case RIGHT:
            if (xpos != 22)
                move(ypos, xpos+4);
            break;
        case SPACEBAR:
            if (legalMove(ypos, xpos) == TRUE) {
                mvaddch(ypos, xpos, 'X');
                fillSurrounding(ypos, xpos);
                return TRUE;
            }
            else {
                printf("You can't move there!");
                return FALSE;
            }
            break;
        default:
            printf("Use IJKL to move and q to quit");
    }
    return FALSE;
}
void drawGrid() {
    int i, j;
    for (i = 0; i <= 12; i++) {
        mvaddch(i, 0, '|');
        mvaddch(i, 4, '|');
        mvaddch(i, 8, '|');
        mvaddch(i, 12, '|');
        mvaddch(i, 16, '|');
        mvaddch(i, 20, '|');
        mvaddch(i, 24, '|');
        if (i%2 == 0) {
            for (j = 0; j<=24; j++) {
                mvaddch(i, j, '-');
            }
        }
    }
    move(1,2);
    refresh();
}