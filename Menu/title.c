#include "headers.h"

int title(SDL_Surface *screen){
	/* utils */
	bool quit = false;
	Uint8 *keystates;
	SDL_Event event;

	/* Tela quase pronta */
	SDL_Surface *TitleScreen = NULL;

	/* Carregadores de imagens */
	SDL_Surface *TitleText = NULL;
	SDL_Surface *TitleBackground = NULL;
	SDL_Surface *Buttons = NULL;
	SDL_Surface *Cannon = NULL;
	
	int selectedButton = NEWGAME;
	
	/* a primeira linha guarda onde se aplica o clip, a segunda, de onde tirar */
	/* TITLE faz o papel de botão n+1 (vide headers.h) */
	SDL_Rect ButtonsClip[2][TITLE];
	SDL_Rect CannonClip[2][TITLE];

	TitleScreen = loadBMP("blankFULL.bmp");
	TitleText = loadBMP("TitleText.bmp");
	TitleBackground = loadBMP("TitleBackground.bmp");
/*	loadClip("buttons",&Buttons,&ButtonsClip);
	loadClip("cannon",&Cannon,&CannonClip);
*/
	/* Inicializa a tela */
	applySurface(TitleBackground,TitleScreen);
	applySurface(TitleText,TitleScreen);

	applySurface(TitleScreen,screen);
/*
	applyClip(Buttons,screen,ButtonsClip,selectedButton);
	applyClip(Cannon,screen,CannonClip,selectedButton);
*/
	SDL_Flip(screen);
	/* da loop */
	while(!quit){

		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				quit = true;
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					/* seleciona o botão mod(TITLE) para não selecionar botões inexistentes */
					case SDLK_UP:
						--selectedButton;
						selectedButton %= TITLE;
						break;
					case SDLK_DOWN:
						++selectedButton;
						selectedButton %= TITLE;
						break;
					default:;
				}
			}
		}

		keystates = SDL_GetKeyState(NULL);
/*
		if(keystates[SDLK_UP])
			selectedButton--;

		if(keystates[SDLK_DOWN])
			selectedButton++;

*/		applySurface(TitleScreen,screen);
/*		applyClip(Buttons,screen,ButtonsClip,selectedButton);
		applyClip(Cannon,screen,CannonClip,selectedButton);
*/
		SDL_Flip(screen);
		if(keystates[SDLK_RETURN])
			break;

	}
	
	/* the end */
/*	SDL_FreeSurface(Buttons);
	SDL_FreeSurface(Cannon);
*/	SDL_FreeSurface(TitleText);
	SDL_FreeSurface(TitleBackground);
	SDL_FreeSurface(TitleScreen);

	if(quit)
		return QUIT;
	else
		return selectedButton;

}
