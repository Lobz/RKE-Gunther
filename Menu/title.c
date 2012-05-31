#include "headers.h"

int title(SDL_Surface *screen){
	/* utils */
	bool quit = false, selected = false;
	Uint8 *keystates;
	SDL_Event event;

	/* Tela quase pronta */
	SDL_Surface *TitleScreen = NULL;

	/* Carregadores de imagens */
	SDL_Surface *TitleText = NULL;
	SDL_Surface *TitleBackground = NULL;
	SDL_Surface *Buttons = NULL;
	SDL_Surface *Cannon = NULL;
	
	/* Qual botão está selecionado */
	int selectedButton = NEWGAME;
	
	/* Para usar para DoubleInfoClip (v. graphics.c) */
	/* TITLE faz o papel de botão n+1 (v. headers.h) */
	SDL_Rect ButtonsClip[TITLE][2];
	SDL_Rect CannonClip[TITLE][2];

	TitleScreen = loadBMP("blankFULL.bmp");
	TitleText = loadBMP("TitleText.bmp");
	TitleBackground = loadBMP("TitleBackground.bmp");
	Buttons = loadBMP("TitleButtonsClip.bmp");
	Cannon = loadBMP("TitleCannonClip.bmp");
	loadDoubleInfoClip("TitleButtons.dclip",ButtonsClip);
	loadDoubleInfoClip("TitleCannon.dclip",CannonClip);

	/* Inicializa a tela */
	applySurface(TitleScreen,TitleBackground);
	applySurface(TitleScreen,TitleText);

	applySurface(screen,TitleScreen);

	applyDoubleInfoClip(screen,Buttons,ButtonsClip,selectedButton);
	applyDoubleInfoClip(screen,Cannon,CannonClip,selectedButton);

	SDL_Flip(screen);
	/* da loop */
	while(!selected){

		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
				selected = true;
				break;
			}
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					/* seleciona o botão mod(TITLE) para não selecionar botões inexistentes */
					case SDLK_UP:
						selectedButton += TITLE-1; /* isso equivale a += 1 mod TITLE */
						selectedButton %= TITLE;
						break;
					case SDLK_DOWN:
						++selectedButton;
						selectedButton %= TITLE;
						break;
					case SDLK_RETURN:
						selected = true;
						break;
					case SDLK_ESCAPE:
						selected = true;
						quit = true;
						break;
					default:;
				}
			}
		}
/*
		keystates = SDL_GetKeyState(NULL);

		if(keystates[SDLK_RETURN])
			break;

		if(keystates[SDLK_ESCAPE]){
			quit = true;
			break;
		}

		if(keystates[SDLK_UP]){
			selectedButton += TITLE-1;
			selectedButton %= TITLE;
		}

		if(keystates[SDLK_DOWN]){
			selectedButton++;
			selectedButton %= TITLE;
		}
*/
		applySurface(screen,TitleScreen);
		applyDoubleInfoClip(screen,Buttons,ButtonsClip,selectedButton);
		applyDoubleInfoClip(screen,Cannon,CannonClip,selectedButton);

		SDL_Flip(screen);
	}
	
	/* the end */
	safeFreeSurface(Buttons);
	safeFreeSurface(Cannon);
	safeFreeSurface(TitleText);
	safeFreeSurface(TitleBackground);
	safeFreeSurface(TitleScreen);

	if(quit)
		return QUIT;
	else
		return selectedButton;

}
