/**
 * \file rkegraficos.c
 * \brief Utilitários gráficos
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "gunther.h"

/**
 * Abre uma nova janela
 * \param largura Largura em pixels
 * \param altura Altura em pixels
 */
SDL_Surface* rke_abre_janela(int largura, int altura)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return NULL;
    return SDL_SetVideoMode(largura, altura, 24, SDL_SWSURFACE);
}

/**
 * Aplica uma tela guardada em memória em outra
 * \param destino Tela de destino
 * \param origem Tela de origem
 */
void rke_aplica_tela(SDL_Surface *destino, SDL_Surface *origem)
{
    if (destino && origem) SDL_BlitSurface(origem, NULL, destino, NULL);
}

/**
 * Carrega um arquivo Bitmap em uma tela
 * \param arquivo O nome do arquivo
 */
SDL_Surface *rke_carrega_BMP(char* arquivo)
{
    SDL_Surface* imagem = NULL;
    char caminho[TAMMAX] = DIR_IMAGENS;

    strcat(caminho, arquivo);

    imagem = SDL_LoadBMP(caminho);

    if(imagem == NULL)
    {
        printf("Arquivo '%s' nao encontrado\n", arquivo);
        return NULL;
    }

    /* indica a cor transparente (chroma key) da tela */
    SDL_SetColorKey( imagem, SDL_SRCCOLORKEY, SDL_MapRGB(imagem->format, KEY_VERMELHO, KEY_VERDE, KEY_AZUL));

    return imagem;
}

/**
 * Copia um retângulo em uma tela para um outro retângulo em outra tela
 * \param destino Tela de destino
 * \param origem Tela de origem
 * \param clip Vetor com os retângulos
 * \param selecao Opção selecionada no menu
 */
void rke_aplica_clip_duplo(SDL_Surface *destino, SDL_Surface *origem, SDL_Rect clip[][2], int selecao)
{
    if(destino && origem && (int)clip[0][0].x != -1)
        SDL_BlitSurface(origem, &(clip[selecao][0]), destino, &(clip[selecao][1]));
}

/**
 * Carrega retângulos a partir de um arquivo
 * \param arquivo O arquivo a ser carregado
 * \param clip O vetor de retângulos que conterá as informações
 */
void rke_carrega_clip_duplo(char *arquivo, SDL_Rect clip[][2])
{
    int i, j, num;
    int x, y, w, h;
    SDL_Rect *p;
    FILE *F;
    char caminho[TAMMAX] = IMAGEDIR;

    strcat(caminho, arquivo);

    F = fopen(caminho, "r");

    if(F == NULL)
    {
        printf("Arquivo '%s' nao encontrado\n", arquivo);
        clip[0][0].x = -1;
        return;
    }
    else
    {
        fscanf(F, " %d", &num);
        for(i = 0; i < 2; i++)
        {
            for(j = 0; j < num; j++)
            {
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
void rke_libera_tela(SDL_Surface *tela)
{
    if (tela) SDL_FreeSurface(tela);
}

/**
 * Aplica um retângulo a uma tela
 * \param destino A tela que receberá a imagem
 * \param origem A tela de origem
 * \param mapa_x A posição X (em ladrilhos) no destino
 * \param mapa_y A posição Y (em ladrilhos) no destino
 * \param clip O retângulo a ser aplicado
 */
void rke_aplica_clip_a_mapa(SDL_Surface *destino, SDL_Surface *origem, int mapa_x, int mapa_y, SDL_Rect clip)
{
    SDL_Rect deslocamento;
    if(destino && origem && (int)clip.x != -1)
    {
        deslocamento.x = mapa_x*LADRILHO_LARGURA;
        deslocamento.y = mapa_y*LADRILHO_ALTURA;
        deslocamento.w = LADRILHO_LARGURA;
        deslocamento.h = LADRILHO_ALTURA;
        SDL_BlitSurface (origem, &clip, destino, &deslocamento);
    }
}
