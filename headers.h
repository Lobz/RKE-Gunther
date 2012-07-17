/**
 * \file headers.h
 * \brief Arquivo header geral do jogo, incluindo menu e gráficos
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL/SDL.h"

#define bool int
#define true 1
#define false 0

#define MAXLEN 100

#define QUIT -1

#define IMAGEDIR "data/imagens/"
#define SCREEN_WIDTH (48*15) 
#define SCREEN_HEIGHT 480
#define RESOLUTION 24
#define BR 0
#define BG 0xFF
#define BB 0xFF

#define TILE_WIDTH 48
#define TILE_HEIGHT 48

#define BOARD_WIDTH 15
#define BOARD_HEIGHT 10

#define DATADIR "data/"

/* SDL */
SDL_Surface *initScreen(int largura, int altura);
SDL_Surface *loadBMP(char *file);
void applySurface(SDL_Surface *destination,  SDL_Surface *source);
void applyDoubleInfoClip(SDL_Surface *destination,  SDL_Surface *source,  SDL_Rect clip[][2],  int choice);
void loadDoubleInfoClip(char *file,  SDL_Rect clip[][2]);
void applyClip( SDL_Surface *destination,  SDL_Surface *source,  int x,  int y,  SDL_Rect clip);
void applyClipToBoard( SDL_Surface *destination,  SDL_Surface *source,  int board_x,  int board_y,  SDL_Rect clip);
void safeFreeSurface(SDL_Surface *dead);

/* telas */
#define NEWGAME 0
#define LOADGAME 1
#define OPTIONS 2
#define MANUAL 3
#define CREDITS 4
#define TITLE 5
#define COMMANDS 6
void gunther_menu(SDL_Surface* screen);
int intro(SDL_Surface *screen);
int title(SDL_Surface *screen);
int options(SDL_Surface *screen);
int manual(SDL_Surface *screen, int section);
int credits(SDL_Surface *screen);
int loadgame(SDL_Surface *screen);
int newgame(SDL_Surface *screen);
