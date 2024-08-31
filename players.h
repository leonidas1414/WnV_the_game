#include <iostream>
#include <curses.h>

using namespace std;
#include <cstring>
#define EARTH  	  ' '
#define WATER	  '~'
#define TREES	  '!'
#define PLAYER_VAMP 'V'
#define PLAYER_WERE 'W'
#define WEREWOLF  'w'
#define VAMPIRE	  'v'



// Base class
class  Human {
    private:
        int x;
        int y;
        string type;
	int potions;
	int id;

    public:
    
        Human(string type,int y,int x, int potions,int id){
            this->type = type;
            this->y =  y;
            this->x = x;
            this->potions = potions;
            this->id = id;
        }
        ~Human(){cout<< "Human Deleted" << endl;}

        void set_type(string type){ this->type = type; }
        void set_x(int x){ this->x = x; }
         void set_y(int y){ this->y = y; }
        void set_potions(int potions){this->potions = potions;}
        void set_id(int id){this->id=id;}
        
        string get_type()const{ return type;}
        int get_x()const{return x; }
        int get_y()const {return y;}
        int get_potions()const{return potions;}
        int get_id(){return this->id;}
	virtual void move(int d){}
        
};




// Derived class
class  avatar: public Human {
    private:
        int side;

    public:
	int press;
        avatar(int side,string type_human,int y, int x,int potions,int id): Human( type_human, y,x,potions,id) {
            this->side = side;
            cout <<"Pick a side between Vampires and Werewolves and be their healer.You can heal Vampires at DAY and Werewolves at NIGHT.Press H to heal, W,A,S,D arrows keys to move, SPACE to see  the score and C to hide it.Press Q to quit.Take P (potion) for extra healing."<<endl; 
            cout << "Let's start : if you want to be a vampire press 1 and ENTER else press any number and ENTER to  be a werewolf." << endl;
            cin >> press;
  
	    if(press == 1){
		set_side(1); //Vampire
	    }else{
		set_side(2); //Werewolf
	    }
        }
        ~avatar(){
            cout<< "Deleted avatar" << endl;
           // delete this;
        }

        void set_side(int side_a){this-> side = side_a;}
        int get_side()const{return side;}
        
	

        void set_type_human(string type){ Human::set_type(type); }
        void set_y_human(int y){ Human::set_y(y); }
        void set_x_human(int x){ Human::set_x(x); }
        void set_potions_human(int potions) {Human:set_potions(potions);}

        string get_type_human()const{ return Human::get_type(); }
        int get_y_human()const{ return Human::get_y(); }
        int get_x_human()const{ return Human::get_x(); }
        int get_potions_human() { return Human::get_potions();}
};




// Derived class
class Werewolves : public Human {
    private:
        int strength;
        int defence;
        int health;
    public:

    Werewolves(int strength,int defence,int health, string type_human,int y, int x,int potions,int id): Human ( type_human, y,x,potions,id){
        this -> strength =strength;
        this -> defence=defence;
        this -> health = health;
        

    }
    ~Werewolves(){
       
    }
	bool isAlive(){return (this->health>0);}
    void set_strength_W(int strength_Werewolves){ this->strength=strength_Werewolves; }
    int get_strength_W()const{return strength;}
	void set_defence_W(int defence_Werewolves){ this->defence=defence_Werewolves; }
    int get_defence_W()const{return defence;}
    void set_health_W(int health_Werewolves){ this->health=health_Werewolves; }
    int get_health_W()const{return health;}

    bool check_friend();
    
	bool check_enemy();




		
	bool check_power(){return false;}
	void attack(){return;}
	void escape(){return;}
	bool check_friendly_health(){ return (this->get_health_W()<2); }
	void heal(void){
		
					
						this->set_potions_human(this->get_potions_human()-1);
					
					return ;
	}
	
    	void set_type_human(string type){ Human::set_type(type); }
        void set_y_human(int y){ Human::set_y(y); }
        void set_x_human(int x){ Human::set_x(x); }
        void set_potions_human(int potions) {Human:set_potions(potions);}

        string get_type_human()const{ return Human::get_type(); }
        int get_y_human()const{ return Human::get_y(); }
        int get_x_human()const{ return Human::get_x(); }
        int get_potions_human() { return Human::get_potions();}
        
};




// Derived class
class  Vampires : public Human {
    private:
         int strength;
        int defence;
        int health;
    public:
    Vampires(int strength,int defence,int health, string type_human,int y, int x,int potions,int id): Human ( type_human, y,x,potions,id){
       this -> strength =strength;
        this -> defence=defence;
        this -> health = health;
        
    }
     ~Vampires(){
        
    }
    void takeDmg(int dmg){this->set_health_V(this->health-dmg);return;}
	bool isAlive(){return (this->health>0);}
    void set_strength_V(int strength_Vampires){ this->strength=strength_Vampires; }
    int get_strength_V()const{return strength;}
	void set_defence_V(int defence_Vampires){ this->defence=defence_Vampires; }
    int get_defence_V()const{return defence;}
    void set_health_V(int health_Vampires){ this->health=health_Vampires; }
    int get_health_V()const{return health;}
	
    bool check_friend_V();

	bool check_enemy_V();



	bool check_power(){return false;}
	void attack(){return;}
	void escape(){return;}
	bool check_friendly_health(){ return (this->get_health_V()<2); }
	void heal(void){
		
					
						this->set_potions_human(this->get_potions_human()-1);
					
					return ;
	}
	void set_type_human(string type){ Human::set_type(type); }
        void set_y_human(int y){ Human::set_y(y); }
        void set_x_human(int x){ Human::set_x(x); }
        void set_potions_human(int potions) {Human:set_potions(potions);}

        string get_type_human()const{ return Human::get_type(); }
        int get_y_human()const{ return Human::get_y(); }
        int get_x_human()const{ return Human::get_x(); }
        int get_potions_human() { return Human::get_potions();}

       
};

  

