OPTS=-lSDL
CC=gcc
FILES=main.c graphics.c manual.c title.c
all: menu

menu: ${FILES}
	${CC} ${FILES} -o menu ${OPTS}

debug: ${FILES}
	${CC} ${FILES} -g -ggdb -o menu-debug ${OPTS}
	gdb menu-debug
