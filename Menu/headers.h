#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"

#define bool int
#define true 1
#define false 0

#define WIDTH 640
#define HEIGHT 480
#define RESOLUTION 16

#define QUIT -1

#define NEWGAME 0
#define LOADGAME 1
#define OPTIONS 2
#define MANUAL 3
#define CREDITS 4
#define TITLE 5
#define COMMANDS 6

#define CLIPSOURCE 1
#define CLIPDEST 0

/* SDL */
bool initSDL(SDL_Surface **screen);
SDL_Surface *loadBMP(char *file);
void applySurface(SDL_Surface *source, SDL_Surface *destination);
void applyClip(SDL_Surface *source, SDL_Surface *destination, SDL_Rect clip, int choice);
void loadClip(char *file,SDL_Surface *image, SDL_Rect *clip);

/* telas */
int intro(SDL_Surface *screen);
int title(SDL_Surface *screen);
int options(SDL_Surface *screen);
int manual(SDL_Surface *screen,int section);
int credits(SDL_Surface *screen);
int loadgame(SDL_Surface *screen);
int Game(SDL_Surface *screen,int game);
