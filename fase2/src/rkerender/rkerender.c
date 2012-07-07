/**
 * \file rkerender.c
 * \brief Renderizador de fases
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "gunther.h"
#include <string.h>

/**
 * Função principal do renderizador de fases
 * \param fase Arquivo de fase
 * \param imagens Arquivo clipboard com as imagens para terreno e objetos
 * \param img_jogador Arquivo clipboard com as imagens do jogador
 * \param largura Largura em ladrilhos da tela
 * \param altura Altura em ladrilhos da tela
 * \param larg_ladrilho Largura em pixels do ladrilho
 * \param alt_ladrilho Altura em pixels do ladrilho
 */
void rke_render(char* fase, char* imagens, char* img_jogador, int largura, int altura, int larg_ladrilho, int alt_ladrilho)
{
    int i, j;
    int sair = 0;
    SDL_Event evento;
    Tabuleiro tabuleiro;
    Ladrilho terrenos[255];
    Objeto objetos[255];
    Jogador jogador;
    SDL_Surface* mapa;
    SDL_Surface* mapa_jogador;
    SDL_Surface* tela;

    rke_carrega_terreno("data/terreno.dat", terrenos, larg_ladrilho, alt_ladrilho);
    rke_carrega_objetos("data/objetos.dat", objetos, larg_ladrilho, alt_ladrilho);
    rke_carrega_jogador(&jogador, larg_ladrilho, alt_ladrilho);

    mapa = rke_carrega_BMP(imagens);
    mapa_jogador = rke_carrega_BMP(img_jogador);

    rke_carrega_fase(fase, &tabuleiro, &(jogador.x), &(jogador.y));
    jogador.direcao = E;

    tela = SDL_GetVideoSurface();
    SDL_FillRect(tela, NULL, 0x000000);

    while(!sair)
    {
        for (i = 0; i < altura; i++)
        {
            for (j = 0; j < largura; j++)
            {
                rke_aplica_clip_a_mapa(tela, mapa, j, i, terrenos[(int)tabuleiro.terreno[i][j]].retangulo);
                if ((int)(tabuleiro.objetos[i][j])) rke_aplica_clip_a_mapa(tela, mapa, j, i, objetos[(int)tabuleiro.objetos[i][j]].retangulo);
            }
        }

        rke_aplica_clip_a_mapa(tela, mapa_jogador, jogador.y, jogador.x, jogador.retangulo[jogador.direcao]);

        SDL_Flip(tela);

        while(SDL_PollEvent(&evento))
        {
            if(evento.type == SDL_QUIT)
            {
                sair = 1;
            }
            else if(evento.type == SDL_KEYDOWN)
            {
                switch (evento.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    sair = 1;
                    break;
                case SDLK_UP:
                    rke_move_jogador(&jogador, tabuleiro, terrenos, objetos, -1, 0);
                    break;
                case SDLK_DOWN:
                    rke_move_jogador(&jogador, tabuleiro, terrenos, objetos,  1, 0);
                    break;
                case SDLK_LEFT:
                    rke_move_jogador(&jogador, tabuleiro, terrenos, objetos,  0, -1);
                    break;
                case SDLK_RIGHT:
                    rke_move_jogador(&jogador, tabuleiro, terrenos, objetos,  0,  1);
                    break;
                default:
                    break;
                }
            }
        }
    }

    SDL_FillRect(tela, NULL, 0x000000);
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
void rke_move_jogador(Jogador* jogador, Tabuleiro tabuleiro, Ladrilho* terrenos, Objeto* objetos, int delta_x, int delta_y)
{
    if (terrenos[(int)tabuleiro.terreno[jogador->x + delta_x][jogador->y + delta_y]].passavel == 1)
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
 * Carrega as informações dos elementos de terreno de um arquivo
 * \param arquivo O arquivo com as informações
 * \param terrenos O lugar para armazenar as informações
 * \param larg_ladrilho Largura em pixels do ladrilho
 * \param alt_ladrilho Altura em pixels do ladrilho
 */
void rke_carrega_terreno(char* arquivo, Ladrilho terrenos[], int larg_ladrilho, int alt_ladrilho)
{
    FILE* arq;
    char nome[255], codigo;
    int passavel, x, y;

    arq = fopen(arquivo, "r");

    while ((codigo = fgetc(arq)) != EOF)
    {
        if (codigo == '\n' || codigo == '\r') continue;
        if (codigo == '#' || codigo == ' ')
        {
            while (codigo != '\n')
            {
                fscanf(arq, "%c", &codigo);
            }
            continue;
        }

        fscanf(arq, " %s %d %d %d", nome, &passavel, &y, &x);

        terrenos[(int)codigo].passavel = passavel;
        terrenos[(int)codigo].retangulo.x = x * larg_ladrilho;
        terrenos[(int)codigo].retangulo.y = y * alt_ladrilho;
        terrenos[(int)codigo].retangulo.w = larg_ladrilho;
        terrenos[(int)codigo].retangulo.h = alt_ladrilho;
    }

    fclose(arq);
}

/**
 * Carrega as informações dos objetos de um arquivo
 * \param arquivo O arquivo com as informações
 * \param objetos O lugar para armazenar as informações
 * \param larg_ladrilho Largura em pixels do ladrilho
 * \param alt_ladrilho Altura em pixels do ladrilho
 */
void rke_carrega_objetos(char* arquivo, Objeto objetos[], int larg_ladrilho, int alt_ladrilho)
{
    FILE* arq;
    char nome[255], codigo;
    int x, y, attack, hp, bonus;

    arq = fopen(arquivo, "r");

    while ((codigo = fgetc(arq)) != EOF)
    {
        if (codigo == '\n' || codigo == '\r') continue;
        if (codigo == '#' || codigo == ' ')
        {
            while (codigo != 10)
            {
                fscanf(arq, "%c", &codigo);
            }
            continue;
        }

        fscanf(arq, "%s %d %d %d %d %d", nome, &hp, &attack, &bonus, &y, &x);

        objetos[(int)codigo].retangulo.x = x * larg_ladrilho;
        objetos[(int)codigo].retangulo.y = y * alt_ladrilho;
        objetos[(int)codigo].retangulo.w = larg_ladrilho;
        objetos[(int)codigo].retangulo.h = alt_ladrilho;
    }

    fclose(arq);
}

/**
 * Carrega as informações do tabuleiro da fase
 * \param arquivo O arquivo com as informações
 * \param tabuleiro O lugar para armazenar as informações
 * \param jogador_x Argumento que devolve a posição X do jogador
 * \param jogador_y Argumento que devolve a posição Y do jogador
 */
void rke_carrega_fase(char* arquivo, Tabuleiro* tabuleiro, int* jogador_x, int* jogador_y)
{
    FILE* arq;
    int x, y, i, j;
    char codigo;

    arq = fopen(arquivo, "r");

    fscanf(arq, "%d %d", &y, &x);

    tabuleiro->terreno = (char**)malloc(x * sizeof(char*));
    tabuleiro->objetos = (char**)malloc(x * sizeof(char*));
    for (j = 0; j < y; j++)
    {
        tabuleiro->terreno[j] = (char*)malloc(y * sizeof(char));
        tabuleiro->objetos[j] = (char*)malloc(y * sizeof(char));
    }

    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            fscanf(arq, " %c", &codigo);
            tabuleiro->terreno[i][j] = codigo;

            fscanf(arq, "%c", &codigo);
            if (codigo == '@')
            {
                *jogador_x = i;
                *jogador_y = j;
            }
            else if (codigo != '-') tabuleiro->objetos[i][j] = codigo;
        }
    }

    fclose(arq);
}

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
