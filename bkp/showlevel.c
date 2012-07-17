#include "game.h"

int main(int argc, char *argv[]){
	int i, j;
	bool quit = false;
	SDL_Event event;

	SDL_Surface *screen = NULL;

	SDL_Surface *clipboard = NULL;

	GameBoard board;
	Object defs[10];

	SDL_Rect land,  water;
	
	if(argc < 2){
		printf("Passe o nome do arquivo de level\n");
		return 0;
	}

	land.x = 5*TILE_WIDTH;
	land.y = 2*TILE_HEIGHT;
	water.x = 4*TILE_WIDTH;
	water.y = 2*TILE_HEIGHT;
	land.h = water.h = TILE_HEIGHT;
	land.w = water.h = TILE_WIDTH;

	/* incializa tela */
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)	return 1;

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, RESOLUTION, SDL_SWSURFACE);

	if(screen == NULL) return 1;

	/*inicializa clipboard */
	clipboard = loadBMP("ClipBoard.bmp");

	/*inicializa objetos */
	loadObjectDefinitions(defs, "objects.dat");

	/*inicializa level*/
	loadBoard(&board, defs, argv[1]);

	/*desenha*/
	for(i=0;i<BOARD_HEIGHT;i++){
		for(j=0;j<BOARD_WIDTH;j++){
			switch(board.scenario[i][j]){
				case LAND:
					applyClipToBoard(screen, clipboard, j, i, land);
					break;
				case WATER:
					applyClipToBoard(screen, clipboard, j, i, water);
					break;
				default:;
			}
			if(board.objects[i][j]){
				applyClipToBoard(screen, clipboard, j, i, board.objects[i][j]->clip);
			}
		}
	}
	
	SDL_Flip(screen);
	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
			else if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}
			}
		}
	}

	SDL_Quit();
	return 0;
}
