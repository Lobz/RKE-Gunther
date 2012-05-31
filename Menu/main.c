#include "headers.h"

int main(){
	int section = TITLE;

	SDL_Surface *screen = NULL;

	/* incializa tela */
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)	return 1;

	screen = SDL_SetVideoMode(WIDTH,HEIGHT,RESOLUTION,SDL_SWSURFACE);

	if(screen == NULL) return 1;

	while (section != QUIT){
		switch(section){
		case TITLE:
			section = title(screen);
			break;
/*		case NEWGAME:
			section = Game(screen,NULL);
			break;
		case LOADGAME:
			section = loadgame(screen);
			break;
		case OPTIONS:
			section = options(screen);
			break;
*/		case MANUAL:
			section = manual(screen,0);
			break;
/*		case COMMANDS:
			section = manual(screen,COMMANDS);
			break;
		case CREDITS:
			section = credits(screen);
			break;
*/		default:
			printf(" %d\n",section);
			return 1;
		}
	}

	SDL_Quit();
	return 0;
}
