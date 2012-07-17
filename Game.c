/**
 * \file Game.c
 * \brief Função principal do jogo
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "player.h"

#define FLECHA 0
#define BOMBA 1

int Game(SDL_Surface *screen);

int newgame(SDL_Surface *screen){
	return Game(screen);
}

int loadgame(SDL_Surface *screen){
	return Game(screen);
}

int Game(SDL_Surface *screen){
	int i, j;
	bool quit = false;
	SDL_Event event;
	SDL_Surface *clipboard = NULL;

	GameBoard board;
	Object objetos[255];
	Terrain terrenos[255];

	Jogador jogador;
	SDL_Rect *pos = NULL;
	SDL_Surface* clipboard_jogador;

	loadTerrainDefinitions(terrenos,"terreno.dat");
	loadObjectDefinitions(objetos, "objects.dat");
	rke_carrega_jogador(&jogador, TILE_WIDTH, TILE_HEIGHT);

	clipboard_jogador = loadBMP("navio.bmp");
	pos = loadBoard(&board,objetos,"level1.lvl");

	jogador.x = pos->x;
	jogador.y = pos->y;
	jogador.direcao = E;
	jogador.hp = 1000;
	jogador.poder_flecha=3;
	jogador.poder_bomba=10;
	jogador.bombas=5;

	free(pos);

	screen = SDL_GetVideoSurface();
	SDL_FillRect(screen, NULL, 0x000000);

	while(!quit)
	{
		for (i = 0; i < BOARD_HEIGHT ; i++)
		{
			for (j = 0; j < BOARD_WIDTH; j++)
			{
				applyClipToBoard(screen, clipboard, j, i, terrenos[(int)board.scenario[i][j]].retangulo);
				if ((int)(board.objects[i][j])) applyClipToBoard(screen, clipboard, j, i, objetos[(int)board.objects[i][j]].clip);
			}
		}

		applyClipToBoard(screen, clipboard_jogador, jogador.y, jogador.x, jogador.retangulo[jogador.direcao]);

		SDL_Flip(screen);

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = 1;
			}
			else
			{
				if(event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							quit = 1;
							break;
						case SDLK_UP:
							rke_move_jogador(&jogador, board, terrenos, objetos, -1, 0);
							break;
						case SDLK_DOWN:
							rke_move_jogador(&jogador, board, terrenos, objetos,  1, 0);
							break;
						case SDLK_LEFT:
							rke_move_jogador(&jogador, board, terrenos, objetos,  0, -1);
							break;
						case SDLK_RIGHT:
							rke_move_jogador(&jogador, board, terrenos, objetos,  0,  1);
							break;
						case SDLK_SPACE:
							rke_jogador_atira(&jogador, board, terrenos, objetos, FLECHA);
							break;
						case SDLK_RETURN:
							rke_jogador_atira(&jogador, board, terrenos, objetos, BOMBA);
							break;
						default:
							break;
					}
				}
			}
		}
	}

	SDL_FillRect(screen, NULL, 0x000000);
	return QUIT;
}
