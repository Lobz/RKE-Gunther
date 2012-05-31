CC=gcc
FLAGS=-Wall -pedantic
FILES=graphics.c boardloader.c
OPTS=-lSDL

showlevel:
	${CC} ${FLAGS} showlevel.c ${FILES} ${OPTS} 

debug:
	${CC} ${FLAGS} showlevel.c ${FILES} ${OPTS} -g -ggdb
	gdb ./a.out

clean:
	rm *.o a.out
