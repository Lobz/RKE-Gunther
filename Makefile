CC=gcc
CFLAGS=-Wall -g
FILES=src/main.c src/menu/menu.c src/rkefisica/rkefisica.c src/rkegraficos/rkegraficos.c src/rkerender/rkerender.c
OPTS=`sdl-config --libs` `sdl-config --cflags` -Iinclude
OUTPUT=gunthers

all:
	${CC} ${CFLAGS} -o ${OUTPUT} ${FILES} ${OPTS}
