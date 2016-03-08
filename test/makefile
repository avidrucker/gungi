CC = clang++-3.5
#CC = g++
CFLAGS = -std=c++14
DEBUG = -Wall -Werror -g
INC = ../include/
SRC = ../src/


Play: Play.cpp Protocol.o Engine.o
	$(CC) $(CFLAGS) $(DEBUG) -I $(INC)  Protocol.o Engine.o Play.cpp -o Play

Engine.o: 
	$(CC) $(CFLAGS) $(DEBUG) -I $(INC) -c $(SRC)Engine.cpp -o Engine.o

Protocol.o: 
	$(CC) $(CFLAGS) $(DEBUG) -I $(INC) -c $(SRC)Protocol.cpp -o Protocol.o

clean:
	rm *o ; rm Play ; 
