#include "headers.h"

int title(SDL_Surface *screen){
	/* flags */
	bool quit = false;

	/* Tela quase pronta */
	SDL_Surface *TitleScreen = NULL;

	/* Carregadores de imagens */
	SDL_Surface *TitleText = NULL;
	SDL_Surface *TitleBackground = NULL;
	SDL_Surface *Buttons = NULL;
	SDL_Surface *Cannon = NULL;
	
	int selectedButton = NEWGAME;
	
	/* a primeira linha guarda onde se aplica o clip, a segunda, de onde tirar */
	SDL_Rect ButtonsClip[2][TITLE];
	SDL_Rect CannonClip[2][TITLE];

	TitleScreen = loadBMP("IMAGEDIR/blankFULL.bmp");
	TitleText = loadBMP("IMAGEDIR/TitleText.bmp");
	TitleBackground = loadBMP("IMAGEDIR/TitleBackground.bmp");
	loadClip("IMAGEDIR/buttons",&Buttons,&ButtonsClip);
	loadClip("IMAGEDIR/cannon",&Cannon,&CannonClip);

	/* Inicializa a tela */
	applySurface(TitleBackground,TitleScreen);
	applySurface(TitleText,TitleScreen);

	applySurface(TitleScreen,screen);

	applyClip(Buttons,screen,ButtonsClip,selectedButton);
	applyClip(Cannon,screen,CannonClip,selectedButton);

	/* da loop */
	while(!quit){

		while(SDL_PollEvent(&event))
			if(event.type == SDL_QUIT)
				quit = true;

		keystates = SDL_GetKeyState(NULL);

		if(keystates[SDLK_UP])
			selectedButton--;

		if(keystates[SDLK_DOWN])
			selectedButton++;

		applySurface(TitleScreen,screen);
		applyClip(Buttons,screen,ButtonsClip,selectedButton);
		applyClip(Cannon,screen,CannonClip,selectedButton);

		if(keystates[SDLK_RETURN])
			break;

	}
	
	/* the end */
	SDL_FreeSurface(Buttons);
	SDL_FreeSurface(Cannon);
	SDL_FreeSurface(TitleText);
	SDL_FreeSurface(TitleBackground);
	SDL_FreeSurface(TitleScreen);

	if(quit)
		return QUIT;
	else
		return selectedButton;

}
