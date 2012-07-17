#include "headers.h"

/**
 * Abre uma nova janela
 * \param largura Largura em pixels
 * \param altura Altura em pixels
 */
SDL_Surface* initScreen(int largura, int altura)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return NULL;
    return SDL_SetVideoMode(largura, altura, RESOLUTION, SDL_SWSURFACE);
}

/**
 * Aplica uma tela guardada em memória em outra
 * \param destino Tela de destino
 * \param origem Tela de origem
 */
void applySurface(SDL_Surface *destination, SDL_Surface *source){
	if(destination && source)
		SDL_BlitSurface(source, NULL, destination, NULL);
}

/**
 * Carrega um arquivo Bitmap em uma tela
 * \param arquivo O nome do arquivo
 */
SDL_Surface *loadBMP(char *file){
	SDL_Surface *image = NULL;
	char fullname[MAXLEN] = IMAGEDIR;

	strcat(fullname, file);

	image = SDL_LoadBMP(fullname);

	if(image == NULL){
		printf("File '%s' not found\n", file);
		return NULL;
    }

	/* Color key surface - background color is BR BG BB */
	SDL_SetColorKey( image, SDL_SRCCOLORKEY, SDL_MapRGB( image->format, BR, BG, BB ) );

	return image;
}

/**
 * Copia um retângulo em uma tela para um outro retângulo em outra tela
 * \param destino Tela de destino
 * \param origem Tela de origem
 * \param clip Vetor com os retângulos
 * \param selecao Opção selecionada no menu
 */
void applyDoubleInfoClip(SDL_Surface *destination, SDL_Surface *source, SDL_Rect clip[][2], int choice){
	if(destination && source && (int)clip[0][0].x != -1)
		SDL_BlitSurface(source, &(clip[choice][0]), destination, &(clip[choice][1]));
}

/**
 * Carrega retângulos a partir de um arquivo
 * \param arquivo O arquivo a ser carregado
 * \param clip O vetor de retângulos que conterá as informações
 */
void loadDoubleInfoClip(char *file, SDL_Rect clip[][2]){
	int i, j, num;
	int x, y, w, h;
	SDL_Rect *p;
	FILE *F;
	char fullname[MAXLEN] = IMAGEDIR;
	
	strcat(fullname, file);

	F = fopen(fullname, "r");

	if(F == NULL){
		printf("File '%s' not found\n", file);
		clip[0][0].x = -1;
		return;
	}
	else{	
		fscanf(F, " %d", &num);
		for(i = 0; i < 2; i++){
			for(j = 0; j < num; j++){
				fscanf(F, " %d %d %d %d", &x, &y, &w, &h);
				p = &clip[j][i];
				p->x = x;
				p->y = y;
				p->w = w;
				p->h = h;
			}
		}
		fclose(F);
	}
}

/**
 * Libera a memória de uma tela
 * \param tela A tela em questão
 */
void safeFreeSurface(SDL_Surface *dead){
	if(dead)
		SDL_FreeSurface(dead);
}

void applyClip( SDL_Surface *destination, SDL_Surface *source, int x, int y, SDL_Rect clip){
	SDL_Rect offset;
	if(destination && source && (int)clip.x != -1){
		offset.x = x;
		offset.y = y;
		SDL_BlitSurface (source, &clip, destination, &offset);
	}
}
	
/**
 * Aplica um retângulo a uma tela
 * \param destino A tela que receberá a imagem
 * \param origem A tela de origem
 * \param mapa_x A posição X (em ladrilhos) no destino
 * \param mapa_y A posição Y (em ladrilhos) no destino
 * \param clip O retângulo a ser aplicado
 */
void applyClipToBoard( SDL_Surface *destination, SDL_Surface *source, int board_x, int board_y, SDL_Rect clip){
	SDL_Rect offset;
	if(destination && source && (int)clip.x != -1){
		offset.x = board_x*TILE_WIDTH;
		offset.y = board_y*TILE_HEIGHT;
		offset.w = TILE_WIDTH;
		offset.h = TILE_HEIGHT;
		SDL_BlitSurface (source, &clip, destination, &offset);
	}
}
