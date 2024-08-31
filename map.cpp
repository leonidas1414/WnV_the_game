#include <iostream>
#include <stdlib.h>
#include "map.h"
using namespace std;

//adding monster's name to the class
string Map::take_name(int i, int number){
    string str1 = "Werewolve_";
    string str2 = "Vampire_";

    if(i == 1){
        str1 += to_string(number);
        return str1;
    }else{
        str2 += to_string(number);
        return  str2;
    }
}
//create and add all te monsters
void Map::add_monsters(int vamp_number,int wolf_number, int lines, int cols){
    srand (time(NULL));
    
    wer = new Werewolves*[wolf_number];
    var = new Vampires*[vamp_number];
    int found = 0;                                                                                
    for ( int monster_counter = 0; monster_counter<=wolf_number; monster_counter++){
        int v0= rand()%(lines-1);
        int v1= rand()%(cols-1);	
        found=0;
    	for (int y = v0; y < lines; y++) {
		for (int x = v1; x < cols ; x++) {
			if(mvinch(y, x)== EARTH && found == 0){
				mvaddch(y, x, WEREWOLF);                                          //add werewolves acording to wolf number and giving them streangth,defence and potions randomly
				int str=rand()%3+1;                                               //acording to numbers provided
				int def=rand()%2+1;
				int health=rand()%3+2;
				
				int potions= rand()%2;
				 wer[monster_counter] = new Werewolves(str,def,health,"wolf"+ to_string (monster_counter),y,x,potions,monster_counter); //table of werewolf objects
				
				found=1;
			}
    	    }
    	}
    }

    for ( int monster_counter = 0; monster_counter<=vamp_number; monster_counter++){
        int v0= rand()%(lines-1);
        int v1= rand()%(cols-1);	
        found=0;
    	for (int y = v0; y < lines; y++) {
		for (int x = v1; x < cols ; x++) {                                             //add vampires acording to vamp number and giving them streangth,defence and potions randomly
			if(mvinch(y, x)== EARTH && found == 0){                                                //acording to numbers provided
				mvaddch(y, x, VAMPIRE);	                                                         
				int str=rand()%3+1;
				int def=rand()%2+1;
				int health=rand()%3+2;
				
				int potions= rand()%2;
				var[monster_counter] = new Vampires(str,def,health,"vamp"+ to_string (monster_counter),y,x,potions,monster_counter); //table of vampire objects
				found=1;
			}
    	    }
    	}
    }
}

//battle function
void Map::move_wolf(int vamp_number,int wolf_number, int lines, int cols,int is_night)
{
 srand (time(NULL));
    

 int found = 0;
    for ( int monster_counter = 0; monster_counter<=wolf_number ; monster_counter++){
        int v0= rand()%(lines-5);
        int v1= rand()%(cols-5);	
        int x;
        int y;
        x= wer[monster_counter]->get_x_human();
        y= wer[monster_counter]->get_y_human();
        int dmg =0;
        
        int nearest_vamp = find_neighbor_vamp(y,x,vamp_number,monster_counter);
        int nearest_wolf = find_neighbor_wolf(y,x,wolf_number,monster_counter);
        if(wer[monster_counter]->get_health_W()>0){
        if(nearest_vamp!=-1){
        	if( var[nearest_vamp]->get_strength_V()<wer[monster_counter]->get_strength_W()){
        		if (var[nearest_vamp]->get_defence_V() < wer[monster_counter]->get_strength_W()){  
        			dmg = wer[monster_counter]->get_strength_W() - var[nearest_vamp]->get_defence_V(); //Wolf :if there is a vampire near you compare your strength. If yours is bigger and 
        			                                                                                   //their defence lower do them damage == strength-defence
        			}
			else {dmg =0;}
			var[nearest_vamp]->set_health_V(var[nearest_vamp]->get_health_V()-dmg);
			if(var[nearest_vamp]->get_health_V()==0){
			mvaddch(var[nearest_vamp]->get_y_human(), var[nearest_vamp]->get_x_human(), EARTH);}
        	}else{                                                                                             //Wolf : if you are not stronger move-run
        		move_werewolf(y, x, lines, monster_counter, cols);
        	}
        }else if(nearest_wolf!=-1){
        	if(wer[monster_counter]->get_potions_human() > 0 && wer[nearest_wolf]->get_health_W()<2 && wer[nearest_wolf]->get_health_W()>0){  //Wolf:if you have a friend wolf near you and it has
        		wer[nearest_wolf]->set_health_W(wer[nearest_wolf]->get_health_W()+1);                                                        //health lower of 2 heal it
        		wer[monster_counter]->heal();
        	}else{
        	move_werewolf(y, x, lines, monster_counter, cols);                                            //otherwise move
        	}
        	
        
        }else{
        	move_werewolf(y, x, lines, monster_counter, cols);
        
        }
        }}
        
}

void Map::move_vamp(int vamp_number,int wolf_number, int lines, int cols,int is_night)
{
 srand (time(NULL));
    

    int found = 0;
    for ( int monster_counter = 0; monster_counter<=vamp_number ; monster_counter++){
        int v0= rand()%(lines-5);
        int v1= rand()%(cols-5);	
        int x;
        int y;
        x= var[monster_counter]->get_x_human();
        y= var[monster_counter]->get_y_human();
        int dmg =0;
        
        int nearest_vamp = find_neighbor_vamp(y,x,vamp_number,monster_counter);
        int nearest_wolf = find_neighbor_wolf(y,x,wolf_number,monster_counter);
        if(var[monster_counter]->get_health_V()>0){
        if(nearest_wolf!=-1){
        	if( wer[nearest_wolf]->get_strength_W()<var[monster_counter]->get_strength_V()){                 //Vampire:if there is a werewolf near you compare your strength. If yours is bigger and 
        		if (wer[nearest_wolf]->get_defence_W() < var[monster_counter]->get_strength_V()){           //their defence lower do them damage == strength-defence
        			dmg = var[monster_counter]->get_strength_V() - wer[nearest_wolf]->get_defence_W(); 
        			
        			}
			else {dmg =0;}
			wer[nearest_wolf]->set_health_W(wer[nearest_wolf]->get_health_W()-dmg);                 //Vampire : if you are not stronger move-run
			if(wer[nearest_wolf]->get_health_W()==0){
			mvaddch(wer[nearest_wolf]->get_y_human(), wer[nearest_wolf]->get_x_human(), EARTH);}     
        	}else{
        		move_vampire(y, x, lines, monster_counter, cols);
        	}
        }else if(nearest_vamp!=-1){
        	if(var[monster_counter]->get_potions_human() > 0 && var[nearest_vamp]->get_health_V()<2 && var[nearest_vamp]->get_health_V()>0){ //Vampire:if you have a friend wolf near you and it has
        		var[nearest_vamp]->set_health_V(var[nearest_vamp]->get_health_V()+1);                                                    //health lower of 2 heal it
        		var[monster_counter]->heal();
        	}else{
        	move_vampire(y, x, lines, monster_counter, cols);
        	}
        	
        
        }else{
        	move_vampire(y, x, lines, monster_counter, cols);                                                                       //otherwise move
        
        }
        }}
        
}
    //random move of werewolves similar to avatar without the need of keys
void Map::move_werewolf(int y, int x,int lines,int monster_counter, int cols){
	int ch;
	
	
	
	
	
	ch = rand()%5 +1;
	switch (ch) {
	
	case 1:
	    if ((y > 0) && mvinch(y-1, x)== EARTH) {
		mvaddch(y, x, EARTH);
		wer[monster_counter]->set_y_human(y-1);
        	wer[monster_counter]->set_x_human(x);                                                 
		mvaddch(y-1 ,x, WEREWOLF);
		
	    }
	    break;
	
	case 2:
	    if ( (y < lines - 1) && mvinch(y +1, x)== EARTH) {
		mvaddch(y, x, EARTH);
		wer[monster_counter]->set_y_human(y+1);
        	wer[monster_counter]->set_x_human(x);
		mvaddch(y+1, x, WEREWOLF);
	    }
	    break;
	case 3:
	
	    if ((x > 0) && mvinch(y, x-1 )== EARTH ) {
		mvaddch(y, x, EARTH);
		wer[monster_counter]->set_y_human(y);
        	wer[monster_counter]->set_x_human(x-1);
		mvaddch(y, x-1, WEREWOLF);
	    }
	    break;
	case 4:
	    if ((x < cols - 1) && mvinch(y, x+1)== EARTH) {
		mvaddch(y, x, EARTH);
		wer[monster_counter]->set_y_human(y);
        	wer[monster_counter]->set_x_human(x+1);
		mvaddch(y, x+1, WEREWOLF);
	    }
	    break;
	}
	
        
        
	}
	
	
	
	//random move of vampires similar to avatar without the need of keys
void Map::move_vampire(int y, int x,int lines,int monster_counter, int cols){
	int ch;
	
	
	
	
	
	ch = rand()%9 +1;
	switch (ch) {
	
	case 1:
	    if ((y > 0) && mvinch(y-1, x)== EARTH) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y-1);
        	var[monster_counter]->set_x_human(x);
		mvaddch(y-1 ,x, VAMPIRE);
		
	    }
	    break;
	
	case 2:
	    if ( (y < lines - 1) && mvinch(y +1, x)== EARTH) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y+1);
        	var[monster_counter]->set_x_human(x);
		mvaddch(y+1, x, VAMPIRE);
	    }
	    break;
	case 3:
	
	    if ((x > 0) && mvinch(y, x-1 )== EARTH ) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y);
        	var[monster_counter]->set_x_human(x-1);
		mvaddch(y, x-1, VAMPIRE);
	    }
	    break;
	case 4:
	    if ((x < cols - 1) && mvinch(y, x+1)== EARTH) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y);
        	var[monster_counter]->set_x_human(x+1);
		mvaddch(y, x+1, VAMPIRE);
	    }
	    break;
	
	case 5:
	    if ((y > 0) && (x > 0) && mvinch(y-1, x-1)== EARTH) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y-1);
        	var[monster_counter]->set_x_human(x-1);
		mvaddch(y-1 ,x-1, VAMPIRE);
		
	    }
	    break;
	case 6:
	    if ((y > 0)&& (x < cols - 1) && mvinch(y-1, x+1)== EARTH) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y-1);
        	var[monster_counter]->set_x_human(x+1);
		mvaddch(y-1 ,x+1, VAMPIRE);
		
	    }
	    break;
	case 7:
	    if ((x > 0)&& (y < lines - 1)  && mvinch(y+1, x-1)== EARTH) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y+1);
        	var[monster_counter]->set_x_human(x-1);
		mvaddch(y+1 ,x-1, VAMPIRE);
		
	    }
	    break;
	case 8:
	    if ((x < cols - 1) && (y < lines - 1) && mvinch(y+1, x+1)== EARTH) {
		mvaddch(y, x, EARTH);
		var[monster_counter]->set_y_human(y+1);
        	var[monster_counter]->set_x_human(x+1);
		mvaddch(y+1 ,x+1, VAMPIRE);
		
	    }
	    break;
		
        }
        
	}
	int Map::find_neighbor_wolf(int y, int x,int wolf_number, int current_wolf){ //find the wolves around a set of coordinates by asking every creature their coordinates.
		 for ( int monster_temp = 0; monster_temp<wolf_number; monster_temp++){
        		if(current_wolf!=monster_temp && abs(wer[monster_temp]->get_y_human() - y)<2 && abs(wer[monster_temp]->get_x_human() - x)<2 && wer[monster_temp]->get_health_W()>0) return monster_temp;
        	}
		
		return -1;
	
	}                                                                               //find the vampires around a set of coordinates by asking every creature their coordinates.
	int Map::find_neighbor_vamp(int y, int x,int vamp_number,int current_vamp){
		for ( int monster_temp = 0; monster_temp<vamp_number; monster_temp++){
        		if(current_vamp!=monster_temp && abs(var[monster_temp]->get_y_human() - y)<2 && abs(var[monster_temp]->get_x_human() - x)<2 && var[monster_temp]->get_health_V()>0) return monster_temp;
        	}
		return -1;
	
	}
