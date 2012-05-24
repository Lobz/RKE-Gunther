#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL/SDL.h"

#define bool int
#define true 1
#define false 0

#define MAXLEN 100

#define QUIT -1

#define NEWGAME 0
#define LOADGAME 1
#define OPTIONS 2
#define MANUAL 3
#define CREDITS 4
#define TITLE 5
#define COMMANDS 6

#define IMAGEDIR "imagens_prov/"
#define WIDTH 320
#define HEIGHT 240
#define RESOLUTION 16
#define BR 0
#define BG 0xFF
#define BB 0xFF

/* SDL */
SDL_Surface *loadBMP(char *file);
void applySurface(SDL_Surface *destination, SDL_Surface *source);
void applyTitleButtonsClip(SDL_Surface *destination, SDL_Surface *source, SDL_Rect clip[][TITLE], int choice);
void loadTitleButtonsClip(char *file, SDL_Rect clip[][TITLE]);

/* telas */
int intro(SDL_Surface *screen);
int title(SDL_Surface *screen);
int options(SDL_Surface *screen);
int manual(SDL_Surface *screen,int section);
int credits(SDL_Surface *screen);
int loadgame(SDL_Surface *screen);
int Game(SDL_Surface *screen,int game);
