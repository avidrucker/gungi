CC = clang++-3.5
#CC = g++
CFLAGS = -std=c++14
DEBUG = -Wall -Werror -g
INC = ../include/
SRC = ../src/


Play: Play.cpp Protocol.o Utility.o Gungi.o
	$(CC) $(CFLAGS) $(DEBUG) -I $(INC)  Protocol.o Utility.o Gungi.o Play.cpp -o Play

Gungi.o: 
	$(CC) $(CFLAGS) $(DEBUG) -I $(INC) -c $(SRC)Gungi.cpp -o Gungi.o

Protocol.o: 
	$(CC) $(CFLAGS) $(DEBUG) -I $(INC) -c $(SRC)Protocol.cpp -o Protocol.o

Utility.o:
	$(CC) $(CFLAGS) $(DEBUG) -I $(INC) -c $(SRC)Utility.cpp -o Utility.o

clean:
	rm *o ; rm Play ; 
