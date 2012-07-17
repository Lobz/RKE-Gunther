/**
 * \file menu.c
 * \brief Implementação do menu principal
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "headers.h"

/**
 * Renderiza o menu baseado na seleção
 * \param tela Tela onde o menu será renderizado
 */
void gunther_menu(SDL_Surface* screen)
{
	int section = TITLE;

	while (section != QUIT){
		switch(section){
			case TITLE:
				section = title(screen);
				break;
			case NEWGAME:
				section = newgame(screen);
				break;
			case LOADGAME:
				section = loadgame(screen);
				break;
			case OPTIONS:
				section = options(screen);
				break;
			case MANUAL:
				section = manual(screen,0);
				break;
			case COMMANDS:
				section = manual(screen,COMMANDS);
				break;
			case CREDITS:
				section = credits(screen);
				break;
			default:
				section = QUIT;
		}
	}
}

/**
 * Menu principal
 * \param tela Tela onde o menu será renderizado
 */
int title(SDL_Surface *screen)
{
	/* utils */
	bool quit = false, selected = false;
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
	while(!selected)
	{

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
				selected = true;
				break;
			}
			else if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
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
					default:
						;
				}
			}
		}

		applySurface(screen, TitleScreen);
		applyDoubleInfoClip(screen, Buttons, ButtonsClip, selectedButton);
		applyDoubleInfoClip(screen, Cannon, CannonClip, selectedButton);

		SDL_Flip(screen);
	}

	/* libera */
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

/**
 * Seção "Manual" do menu
 * \param tela Tela onde a seção será renderizada
 */
int manual(SDL_Surface *screen, int mode)
{
	bool quit = false, quitman = false;
	int page, pagenum;
	char monsterFile[50];
	FILE *F;

	SDL_Event event;

	SDL_Surface *ManPage = NULL;
	SDL_Surface *Monsters[50];

	ManPage = loadBMP("ManPage.bmp");

	F = fopen("data/monsters.txt","r");
	if(F == NULL) return -90;

	for(pagenum = 0; fscanf(F," %s",monsterFile) != EOF; pagenum++)
	{
		Monsters[pagenum] = loadBMP(monsterFile);
	}

	fclose(F);

	page = 0;
	while(quitman == false)
	{

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
				quitman = true;
				break;
			}
			else if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						if(page > 0) page--;
						break;
					case SDLK_RIGHT:
						if(page+1 < pagenum) page++;
						break;
					case SDLK_RETURN:
						quitman = true;
						break;
					case SDLK_ESCAPE:
						quitman = true;
						quit = true;
						break;
					default:
						;
				}
			}
		}

		applySurface(screen, ManPage);
		applySurface(screen, Monsters[page]);
		SDL_Flip(screen);
	}

	safeFreeSurface(ManPage);

	for(page = 0; page < pagenum; page++)
	{
		safeFreeSurface(Monsters[page]);
	}

	if(quit)
		return QUIT;

	else
		return TITLE;
}

int options(SDL_Surface *screen){return QUIT;}
int intro(SDL_Surface *screen){return QUIT;}
int credits(SDL_Surface *screen){return QUIT;}
