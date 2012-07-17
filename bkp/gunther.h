/**
 * \file gunther.h
 * \brief Arquivo header geral do jogo
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include <SDL/SDL.h>
#include "rkegraficos.h"
#include "rkefisica.h"
#include "rkerender.h"

#define DIR_IMAGENS "data/imagens/"

#define LADRILHO_ALTURA  48
#define LADRILHO_LARGURA 48

#define TELA_LARGURA 15
#define TELA_ALTURA  10

#define SAIR        -1
#define NOVOJOGO     0
#define CARREGAJOGO  1
#define OPCOES       2
#define MANUAL       3
#define CREDITOS     4
#define INICIO       5
#define COMMANDOS    6


void gunther_menu(SDL_Surface* tela);

/* telas */
int inicio(SDL_Surface *screen);
int manual(SDL_Surface *screen, int section);
