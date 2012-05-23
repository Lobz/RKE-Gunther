#include "menu.h"

int main(){
	bool play = false;
	int section = TITLE;

	SDL_Surface *screen;

	init(&screen);

	while (section != QUIT){
		if(play){
			section = Game(screen,section);
			play = true;
		}
		else switch(section){
		case TITLE:
			section = title(screen);
			break;
		case NEWGAME:
			section = Game(screen,NEWGAME);
			break;
		case LOADGAME:
			section = loadgame(screen);
			play = true
			break;
		case OPTIONS:
			section = options(screen);
			break;
		case MANUAL:
			section = manual(screen,MANUAL);
			break;
		case COMMANDS:
			section = manual(screen,COMMANDS);
			break;
		case CREDITS:
			section = credits(screen);
			break;
		default:
			printerr("Retorno inválido: %d \n",section);
			return 1;
		}
	}

	SDL_Quit();
	return 0;
}
