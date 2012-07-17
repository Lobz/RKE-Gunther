/**
 * \file main.c
 * \brief Ponto de entrada do jogo
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "headers.h"

int main(int argc, char** argv)
{
    SDL_Surface* tela;
    tela = initScreen(SCREEN_WIDTH,SCREEN_HEIGHT);

    if (tela == NULL) return 1;

    gunther_menu(tela);

    SDL_Quit();
    return 0;
}
