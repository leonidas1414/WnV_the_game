#include <iostream>
using namespace std;
#include <cstring>
#include "players.h"


//functions that find werewolves or vampires around the coordinates of instance.Not used in the final game but useful for farther developing.
bool Werewolves::check_friend(){                                                  
		for (int i=-1;i<2;i++){
			for (int j=-1;j<2;j++){
				if((j!=0 || i!=0) && mvinch(this->get_y_human()+j, this->get_x_human()+i)== WEREWOLF){
					return true;
				}
			}
		}
		return false;}

bool Werewolves::check_enemy(){
		for (int i=-1;i<2;i++){
			for (int j=-1;j<2;j++){
				if((j!=0 || i!=0) && mvinch(this->get_y_human()+j, this->get_x_human()+i)== VAMPIRE){
					return true;
				}
			}
		}
		return false;}




bool Vampires::check_friend_V(){
		for (int i=-1;i<2;i++){
			for (int j=-1;j<2;j++){
				if((j!=0 || i!=0) && mvinch(this->get_y_human()+j, this->get_x_human()+i)== VAMPIRE){
					return true;
				}
			}
		}
		return false;}

bool Vampires::check_enemy_V(){
		for (int i=-1;i<2;i++){
			for (int j=-1;j<2;j++){
				if((j!=0 || i!=0) && mvinch(this->get_y_human()+j, this->get_x_human()+i)== WEREWOLF){
					return true;
				}
			}
		}
		return false;}
