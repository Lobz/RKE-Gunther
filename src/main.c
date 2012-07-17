/**
 * \file main.c
 * \brief Ponto de entrada do jogo
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include <stdio.h>
#include <stdlib.h>

#include "gunther.h"

int largura = 720,
    altura  = 480;

int main(int argc, char** argv)
{
    SDL_Surface* tela;
    tela = rke_abre_janela(largura, altura);

    if (tela == NULL) return 1;

    gunther_menu(tela);

    SDL_Quit();
    return 0;
}
