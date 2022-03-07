TARGET=app.out
CC=gcc
CFLAGS=
LDFLAGS = -lncursesw

app.out: main.o game.o
	gcc -o app.out main.o game.o $(LDFLAGS)

main.o: game.h main.c
	gcc -c -o main.o main.c $(LDFLAGS)

game.o: game.h game.c
	gcc -c -o game.o game.c $(LDFLAGS)

clean: 
	rm *.o app.out