CC=gcc
CFLAGS=-Wall -std=c99
OBJ= main.o maps.o player.o ennemies.o screens.o bananas.o
GLFLAGS=-lglut -lGLU -lGL

game: $(OBJ)
		$(CC) -o bananas $(OBJ) $(LDFLAGS) $(GLFLAGS)

main: main.c

bananas: bananas.c bananas.h

maps: maps.c maps.h

ennemies : ennemies.c ennemies.h

player : player.c player.h

screens : screens.c screens.h


clean :
	rm *.o
	rm bananas