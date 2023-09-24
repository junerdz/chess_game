all: compile link

compile:
	g++ -Wall -Wextra -c main.cpp chess_window.cpp -Isrc/include

link:
	g++ main.o chess_window.o -o chess -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
 
clean: 
	rm *.o