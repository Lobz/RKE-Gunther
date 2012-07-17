/**
 * \file rkerender.h
 * \brief Arquivo header do renderizador
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "rkegraficos.h"

#define N  0
#define NE 1
#define E  2
#define SE 3
#define S  4
#define SO 5
#define O  6
#define NO 7

/**
 * Struct Ladrilho
 * \param retangulo Retângulo do ladrilho
 * \param passavel  Indica se o jogador pode andar em cima do ladrilho
 */
typedef struct _ladrilho
{
    SDL_Rect retangulo;
    int passavel;
} Ladrilho;

/**
 * Struct Tabuleiro
 * \param terreno Matriz que armazena como o terreno é construído
 * \param objetos Matriz que armazena a localização dos objetos
 */
typedef struct _tabuleiro
{
    char** terreno;
    char** objetos;
} Tabuleiro;

/**
 * Struct Objeto
 * \param retangulo Retângulo do objeto
 * \param hp Quantidade de hp do objeto
 * \param attack Tipo de ataque do objeto
 * \param bonus Tipo de bonus do objeto
 */
typedef struct _objeto
{
    SDL_Rect retangulo;
    int vida, ataque, bonus, periodo;
} Objeto;

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
    int x, y, direcao, vida;
    int poder_flecha, poder_bomba;
    int bombas;
} Jogador;

void rke_render(char* fase, char* imagens, char* img_jogador, int larg, int alt, int largura_ladrilho, int altura_ladrilho);
void rke_carrega_terreno(char* arquivo, Ladrilho terrenos[], int larg_ladrilho, int alt_ladrilho);
void rke_carrega_objetos(char* arquivo, Objeto objetos[], int larg_ladrilho, int alt_ladrilho);
void rke_carrega_fase(char* arquivo, Tabuleiro* tabuleiro, int* jogador_x, int* jogador_y);
void rke_carrega_jogador(Jogador* jogador, int larg_ladrilho, int alt_ladrilho);
void rke_move_jogador(Jogador* jogador, Tabuleiro tabuleiro, Ladrilho* terrenos, Objeto* objetos, int delta_x, int delta_y);
void rke_jogador_atira(Jogador* jogador, Tabuleiro tabuleiro, Ladrilho* terrenos, Objeto* objetos, int bomba);
int rke_acoes_objetos(Jogador* jogador, Tabuleiro tabuleiro, Ladrilho* terrenos, Objeto* objetos, int turno);
