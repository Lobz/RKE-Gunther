/**
 * \file rkegraficos.h
 * \brief Arquivo header da parte gráfica
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */


#include "SDL/SDL.h"

#define bool int
#define true 1
#define false 0

#define TAMMAX 100

#define IMAGEDIR "data/imagens/"

#define KEY_VERMELHO 0
#define KEY_VERDE    0xFF
#define KEY_AZUL     0xFF


SDL_Surface* rke_abre_janela(int largura, int altura);
void rke_aplica_tela(SDL_Surface *destino, SDL_Surface *origem);
SDL_Surface *rke_carrega_BMP(char* arquivo);
void rke_aplica_clip_duplo(SDL_Surface *destino, SDL_Surface *origem, SDL_Rect clip[][2], int selecao);
void rke_carrega_clip_duplo(char *arquivo, SDL_Rect clip[][2]);
void rke_libera_tela(SDL_Surface *tela);
void rke_aplica_clip_a_mapa(SDL_Surface *destino, SDL_Surface *origem, int mapa_x, int mapa_y, SDL_Rect clip);
