#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <cmath>
#include <curses.h>
using namespace std;
#include "players.h"
#include <string.h>
#define EARTH  	  ' '
#define EARTHT   'g'
#define EARTHTT   'H'
#define WATER	  '~'
#define TREES	  '!'
#define PLAYER_VAMP 'V'
#define PLAYER_WERE 'W'
#define WEREWOLF  'w'
#define VAMPIRE	  'v'
#define POTION 'P'




class Map {
    private:
    
int c;
Werewolves  **wer;
Vampires    **var;
 
public:
        Map( int lines, int cols){
        
        draw_map(lines,cols);                                 //drawing the earth,water,trees on map
        int vamp_number = floor((lines*cols)/15)-1;           //calculating the number of creatures

    	int wolf_number = floor((lines*cols)/15)-1; 
    	add_monsters(vamp_number,wolf_number,lines,cols);       //putting the creatures in random places on the map
    	
			
		
    	

    	int y = lines - 1;                                         
    	int x = 0;
    	int hour_counter=0;
	int is_night=1;
	int ch;
	int wolf_count=0;
	int vamp_count=0;
        avatar ang(0,"avatar",y,x,1,-1);          //creating object ang avatar
        do {

	
		if( ang.get_side()==1 )mvaddch(y, x, PLAYER_VAMP);       //adding V if avatar vampire or W if werewolf
		  
		else mvaddch(y, x, PLAYER_WERE);
		
		if(floor((hour_counter)/12)<1){                         //Calculating night and day
		mvprintw(lines +1,0,"DAY  ");
		is_night=0;} else {
		mvprintw(lines +1,0,"NIGHT");
		is_night=1;}
		hour_counter=(hour_counter+1)%24;
		move(y, x);
		
		
		
		
		refresh();
	
		ch = getch();
		switch (ch) {
	case KEY_UP:
	case 'w':
	case 'W':
	    if ((y > 0) && (mvinch(y-1, x)== EARTH || mvinch(y-1, x)== POTION ) ) {   //for every key used to move avatar , see if there is earth near by so it can move.If there is apotition
	                                                                                  //added to the potions
	    	if(mvinch(y-1, x)== POTION){
		mvaddch(y, x, EARTH);
		y = y - 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		ang.set_potions_human(ang.get_potions_human()+1);
		}
		else if(mvinch(y-1, x)== EARTH){
		mvaddch(y, x, EARTH);
		y = y - 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		
		}
	    }
	    break;
	case KEY_DOWN:
	case 's':
	case 'S':
	    if ((y < lines - 1) && (mvinch(y +1, x)== EARTH || mvinch(y+1, x)== POTION )) {
	    if(mvinch(y+1, x)== POTION){
		mvaddch(y, x, EARTH);
		y = y + 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		ang.set_potions_human(ang.get_potions_human()+1);
		}
		else if(mvinch(y+1, x)== EARTH){
		mvaddch(y, x, EARTH);
		y = y + 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		
		}
	  
		
	    }
	    break;
	case KEY_LEFT:
	case 'a':
	case 'A':
	    if ((x > 0) && (mvinch(y, x-1 )== EARTH || mvinch(y, x-1)== POTION) ) {
	    if(mvinch(y, x-1)== POTION){
		mvaddch(y, x, EARTH);
		x = x - 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		ang.set_potions_human(ang.get_potions_human()+1);
		}
		else if(mvinch(y, x-1)== EARTH){
		mvaddch(y, x, EARTH);
		x = x - 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		
		}
		
	    }
	    break;
	case KEY_RIGHT:                             //code inspired by https://www.linuxjournal.com
	case 'd':
	case 'D':
	    if ((x < cols - 1) && (mvinch(y, x+1)== EARTH || mvinch(y, x+1)== POTION)) {
	    if(mvinch(y, x+1)== POTION){
		mvaddch(y, x, EARTH);
		x = x + 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		ang.set_potions_human(ang.get_potions_human()+1);
		}
		else if(mvinch(y, x+1)== EARTH){
		mvaddch(y, x, EARTH);
		x = x + 1;
		ang.set_y_human(y);
		ang.set_x_human(x);                                      //code inspired by https://www.linuxjournal.com
		
		}
		/*mvaddch(y, x, EARTH);
		x = x + 1;
		ang.set_y_human(y);
		ang.set_x_human(x);
		*/
	    }
	    break;
	case 'H':
	case 'h':
		int co;
		int co_v;
		if(is_night==1 && ang.get_side() ==2 && ang.get_potions_human() >0){
			for(co=0; co<=wolf_number; co++){                                           //Find everyone with low health on our side and heal it.
			if(wer[co]-> get_health_W()<2){
			wer[co]-> set_health_W(wer[co] -> get_health_W()+1);
				}
			}
			ang.set_potions_human(ang.get_potions_human()-1 );
		 	}
		if(is_night ==0 && ang.get_side() == 1 && ang.get_potions_human() >0)  {
		for(co_v=0; co_v<=vamp_number; co_v++){
			if(var[co_v]-> get_health_V()<2){
			var[co_v]-> set_health_V(var[co_v] -> get_health_V()+1);
				}
			}
			ang.set_potions_human(ang.get_potions_human()-1);
		
		}
		break;
	case 'c':
		mvprintw(lines +2,5,"                ");
		mvprintw(lines +3,5,"                ");
		mvprintw(lines +4,5,"                ");
		break;	
	case ' ':
		int co_pw2=0;
		int co_pv2=0;
		for(int co_pw=0; co_pw <= wolf_number; co_pw++){
			
			
			 if(wer[co_pw]-> get_health_W() >0 )
			 	{co_pw2++;
			 	if(co_pw2==0){
			 	mvprintw(lines +2,5,"GAME OVER ");}
			}}
		for(int co_pv=0; co_pv <= vamp_number; co_pv++){
			
			
			 if(var[co_pv]-> get_health_V() >0 )
			 	{co_pv2++;
			 	if (co_pv2==0){
			 	mvprintw(lines +2,5,"GAME OVER ");}}
			}
		mvprintw(lines +2,5,"Werewolves: %d ",co_pw2);                            //show the statistics until now, if total number of creatures is zero cout game over.
		mvprintw(lines +3,5,"Vampires: %d ",co_pv2);
		mvprintw(lines +4,5,"Potions: %d ",ang.get_potions_human());
		mvprintw(lines +5,5,"Press SPACE to refrece or reappear the score,and press  C to hide it. Press Q to quit.");
		break;
		
	
		
		}	
	
		
		move_wolf(vamp_number,wolf_number, lines, cols,is_night);
		move_vamp(vamp_number,wolf_number,lines, cols,is_night);
		
		
    }
    while ((ch != 'q') && (ch != 'Q'));
        }
        
        
        
        
    void draw_map( int lines, int cols)
{
    int y, x;

    /* draw the quest map */

    /* background */

    for (y = 0; y < lines; y++) {
	mvhline(y, 0, EARTH, cols);                //adding the earth on the map
    }

    /* trees, and water*/
    for (x = 0; x < cols; x++) {
        for (y = 0; y < lines; y++) {
	    int temp = rand()%20;
	     switch(temp){                                //adding trees and water with randomly
	    case 1: mvaddch(y, x, TREES);
	    break;
	    case 2: mvaddch(y, x, WATER);
	    break;
    		}
    	}
    }
        int py= rand()%(lines-2)+1;
        int px= rand()%(cols-2)+1;
        
	mvaddch(py,px,POTION);    

}
    string take_name(int i, int number);

    void add_monsters(int vamp_number,int wolf_number, int lines, int cols);

    void move_wolf(int vamp_number,int wolf_number, int lines, int cols,int is_night);

    void move_vamp(int vamp_number,int wolf_number, int lines, int cols,int is_night);
    
    void move_werewolf(int y, int x,int lines,int monster_counter, int cols);
	
    void move_vampire(int y, int x,int lines,int monster_counter, int cols);
	
	int find_neighbor_wolf(int y, int x,int wolf_number, int current_wolf);

	int find_neighbor_vamp(int y, int x,int vamp_number,int current_vamp);

		 ~Map(){

        cout<< "Deleted Map" << endl;
		
    }



	};
