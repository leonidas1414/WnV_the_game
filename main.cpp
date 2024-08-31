
#include <stdlib.h>
#include <time.h> 
//#include "players.h"
#include "map.h"
#include <cmath>
#include <curses.h>
#define EARTH  	  ' '
#define WATER	  '~'
#define TREES	  '!'
#define PLAYER_VAMP 'V'
#define PLAYER_WERE 'W'
#define WEREWOLF  'w'
#define VAMPIRE	  'v'

int main(void)
{
    int y, x;
    int ch;
    int lines,cols;
    
    
    /* initialize curses */

    initscr();
    keypad(stdscr, TRUE);
    cbreak();                                                                 
    noecho();
    cout << "War game Starts :  \n";
    cout << "War game Starts : Press number of x dimesion and enter:\n";             //take the window dimensions and find out if they are bigger of the terminal dimensions
    do{
    cin >> lines;
    if(lines>LINES){ cout <<" Please   insert a value < "<< (LINES-6);}               //if yes advise player
    }while( lines > LINES);
    cout << "War game Starts : Press number of y dimesion and enter:\n";
    do{
    cin >> cols;
    if(cols>COLS){ cout <<" Please  insert a value < "<< COLS;}
    }while( cols > COLS);
    clear();

   
    
    /* initialize the quest map */
	
    Map mp (lines,cols);	
    endwin();
    exit(0);
};
