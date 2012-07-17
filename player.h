/**
 * \file player.h
 * \brief Header para o jogador: imagens, ataques, movimentos, comandos, etc.
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "game.h"

#define N  0
#define NE 1
#define E  2
#define SE 3
#define S  4
#define SO 5
#define O  6
#define NO 7

/**
 * Struct Jogador
 * \param retangulo Vetor com os 8 retângulos das visões do jogador
 * \param x Posição x do jogador
 * \param y Posição y do jogador
 * \param direcao Direção que o jogador está olhando
 * \param hp Quantidade de hp do jogador
 */
typedef struct _jogador
{
    SDL_Rect retangulo[8];
    int x, y, direcao, hp;
    int poder_flecha, poder_bomba;
    int bombas;
} Jogador;

void rke_carrega_jogador(Jogador* jogador, int larg_ladrilho, int alt_ladrilho);
void rke_move_jogador(Jogador* jogador, GameBoard tabuleiro, Terrain* terrenos, Object* objetos, int delta_x, int delta_y);
void rke_jogador_atira(Jogador* jogador, GameBoard tabuleiro, Terrain* terrenos, Object* objetos, int bomba);
