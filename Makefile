#compiler
CC = g++

#compiler flags:

CFLAGS = -g -Wall

#build target executable
TARGET = snake

#common dirs
COMMON = -Iinclude/
#SFML links
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
default: $(TARGET)

$(TARGET): Map.o Game.o Snake.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) $(COMMON) Map.o Game.o Snake.o main.o $(SFMLFLAGS)
	
Map.o: src/Map.cpp
	$(CC) $(CFLAGS) -c $(COMMON) src/Map.cpp

Snake.o:  src/Snake.cpp
	$(CC) $(CFLAGS) -c $(COMMON) src/Snake.cpp

Game.o:  src/Game.cpp
	$(CC) $(CFLAGS) -c $(COMMON) src/Game.cpp
	
main.o:  main.cpp
	$(CC) $(CFLAGS) -c $(COMMON) main.cpp
clean:
	$(RM) $(TARGET) *.o *~
