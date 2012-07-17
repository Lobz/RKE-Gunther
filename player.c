/**
 * \file player.c
 * \brief Código para o jogador: imagens, ataques, movimentos, comandos, etc.
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "player.h"


/**
 * Carrega os retângulos da imagem do jogador
 * \param O lugar para armazenar as informações
 * \param Largura em pixels do ladrilho
 * \param Altura em pixels do ladrilho
 */
void rke_carrega_jogador(Jogador* jogador, int larg_ladrilho, int alt_ladrilho)
{
    int posicoes_y[8] = {0, 0, 0, 0, 0, 1, 1, 1};
    int posicoes_x[8] = {0, 1, 2, 3, 4, 6, 7, 8};
    int i;

    for (i = 0; i < 8; i++)
    {
        jogador->retangulo[i].x = posicoes_x[i] * larg_ladrilho;
        jogador->retangulo[i].y = posicoes_y[i] * alt_ladrilho;
        jogador->retangulo[i].w = larg_ladrilho;
        jogador->retangulo[i].h = alt_ladrilho;
    }
}

/**
 * Função de movimentação do jogador.
 * \param jogador Informações do jogador
 * \param tabuleiro Informações do tabuleiro
 * \param terrenos Informações dos elementos de terreno
 * \param objetos Informações dos objetos
 * \param delta_x Movimentação no eixo X
 * \param delta_y Movimentação no eixo Y
 */
void rke_move_jogador(Jogador* jogador, GameBoard tabuleiro, Terrain* terrenos, Object* objetos, int delta_x, int delta_y)
{
    if (terrenos[(int)tabuleiro.scenario[jogador->x + delta_x][jogador->y + delta_y]].passavel == 1)
    {
        jogador->x += delta_x;
        jogador->y += delta_y;

        if      (delta_x <  0 && delta_y == 0) jogador->direcao = N;
        else if (delta_x <  0 && delta_y >  0) jogador->direcao = NE;
        else if (delta_x == 0 && delta_y >  0) jogador->direcao = E;
        else if (delta_x >  0 && delta_y >  0) jogador->direcao = SE;
        else if (delta_x >  0 && delta_y == 0) jogador->direcao = S;
        else if (delta_x >  0 && delta_y <  0) jogador->direcao = SO;
        else if (delta_x == 0 && delta_y <  0) jogador->direcao = O;
        else if (delta_x <  0 && delta_y <  0) jogador->direcao = NO;
    }
}

/**
 * Função de acao de atirar do jogador.
 * \param jogador Informações do jogador
 * \param tabuleiro Informações do tabuleiro
 * \param terrenos Informações dos elementos de terreno
 * \param objetos Informações dos objetos
 */
void rke_jogador_atira(Jogador* jogador, GameBoard tabuleiro, Terrain* terrenos, Object* objetos, int bomba)
{
    if (bomba && jogador->bombas) {
        jogador->bombas--;
        printf("atirou bomba\n%d\n", jogador->bombas);
        /*lanca_bomba(jogador);*/
    }
    else {
        printf("atirou flecha\n");
        /*lanca_flecha(jogador);*/
    }
}
