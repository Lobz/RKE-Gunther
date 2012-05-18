CC=gcc
CFLAGS=-c -Wall

all: rke-tmf

rke-tmf: ./src/main.o ./src/fisica.o
	$(CC) ./src/main.o ./src/fisica.o -o rke-tmf

./src/main.o: ./src/main.c
	$(CC) $(CFLAGS) ./src/main.c -o ./src/main.o

./src/fisica.o: ./src/fisica.c
	$(CC) $(CFLAGS) ./src/fisica.c -o ./src/fisica.o

clean:
	rm -rf ./src/*.o rke-tmf
