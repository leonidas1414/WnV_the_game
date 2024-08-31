WnV_the_game: main.o players.o map.o
	g++ main.o players.o map.o -lncurses -o WnV_the_game


new.o: main.cpp
	g++ -c main.cpp

players.o: players.cpp
	g++ -c players.cpp
	
map.o: map.cpp
	g++ -c map.cpp
	
run:
		./WnV_the_game

clean:
	rm -f main.o main players.o map.o   




