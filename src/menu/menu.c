/**
 * \file menu.c
 * \brief Implementação do menu principal
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "gunther.h"

/**
 * Renderiza o menu baseado na seleção
 * \param tela Tela onde o menu será renderizado
 */
void gunther_menu(SDL_Surface* tela)
{
    int selecao = INICIO;

    while (selecao != SAIR)
    {
        switch (selecao)
        {
        case INICIO:
            selecao = inicio(tela);
            break;
        case NOVOJOGO:
            rke_render("data/fase1.lvl", "ClipBoard.bmp", "navio.bmp", TELA_LARGURA, TELA_ALTURA, LADRILHO_LARGURA, LADRILHO_ALTURA);
            selecao = INICIO;
            break;
        case MANUAL:
            selecao = manual(tela, 0);
            break;
        case CARREGAJOGO:
        case OPCOES:
        case CREDITOS:
        case COMMANDOS:
            selecao = SAIR;
        }
    }
}

/**
 * Menu principal
 * \param tela Tela onde o menu será renderizado
 */
int inicio(SDL_Surface *screen)
{
    /* utils */
    bool quit = false, selected = false;
    SDL_Event event;

    /* Tela quase pronta */
    SDL_Surface *TitleScreen = NULL;

    /* Carregadores de imagens */
    SDL_Surface *TitleText = NULL;
    SDL_Surface *TitleBackground = NULL;
    SDL_Surface *Buttons = NULL;
    SDL_Surface *Cannon = NULL;

    /* Qual botão está selecionado */
    int selectedButton = NOVOJOGO;

    /* Para usar para DoubleInfoClip (v. graphics.c) */
    /* TITLE faz o papel de botão n+1 (v. headers.h) */
    SDL_Rect ButtonsClip[INICIO][2];
    SDL_Rect CannonClip[INICIO][2];

    TitleScreen = rke_carrega_BMP("blankFULL.bmp");
    TitleText = rke_carrega_BMP("TitleText.bmp");
    TitleBackground = rke_carrega_BMP("TitleBackground.bmp");
    Buttons = rke_carrega_BMP("TitleButtonsClip.bmp");
    Cannon = rke_carrega_BMP("TitleCannonClip.bmp");
    rke_carrega_clip_duplo("TitleButtons.dclip",ButtonsClip);
    rke_carrega_clip_duplo("TitleCannon.dclip",CannonClip);

    /* Inicializa a tela */
    rke_aplica_tela(TitleScreen,TitleBackground);
    rke_aplica_tela(TitleScreen,TitleText);

    rke_aplica_tela(screen,TitleScreen);

    rke_aplica_clip_duplo(screen,Buttons,ButtonsClip,selectedButton);
    rke_aplica_clip_duplo(screen,Cannon,CannonClip,selectedButton);

    SDL_Flip(screen);

    /* da loop */
    while(!selected)
    {

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
                selected = true;
                break;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    /* seleciona o botão mod(INICIO) para não selecionar botões inexistentes */
                case SDLK_UP:
                    selectedButton += INICIO-1; /* isso equivale a += 1 mod INICIO */
                    selectedButton %= INICIO;
                    break;
                case SDLK_DOWN:
                    ++selectedButton;
                    selectedButton %= INICIO;
                    break;
                case SDLK_RETURN:
                    selected = true;
                    break;
                case SDLK_ESCAPE:
                    selected = true;
                    quit = true;
                    break;
                default:
                    ;
                }
            }
        }

        rke_aplica_tela(screen, TitleScreen);
        rke_aplica_clip_duplo(screen, Buttons, ButtonsClip, selectedButton);
        rke_aplica_clip_duplo(screen, Cannon, CannonClip, selectedButton);

        SDL_Flip(screen);
    }

    /* libera */
    rke_libera_tela(Buttons);
    rke_libera_tela(Cannon);
    rke_libera_tela(TitleText);
    rke_libera_tela(TitleBackground);
    rke_libera_tela(TitleScreen);

    if(quit)
        return SAIR;
    else
        return selectedButton;

}

/**
 * Seção "Manual" do menu
 * \param tela Tela onde a seção será renderizada
 */
int manual(SDL_Surface *screen, int mode)
{
    bool quit = false, quitman = false;
    int page, pagenum;
    char monsterFile[50];
    FILE *F;

    SDL_Event event;

    SDL_Surface *ManPage = NULL;
    SDL_Surface *Monsters[50];

    ManPage = rke_carrega_BMP("ManPage.bmp");

    F = fopen("data/monsters.txt","r");
    if(F == NULL) return -90;

    for(pagenum = 0; fscanf(F," %s",monsterFile) != EOF; pagenum++)
    {
        Monsters[pagenum] = rke_carrega_BMP(monsterFile);
    }

    fclose(F);

    page = 0;
    while(quitman == false)
    {

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
                quitman = true;
                break;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if(page > 0) page--;
                    break;
                case SDLK_RIGHT:
                    if(page+1 < pagenum) page++;
                    break;
                case SDLK_RETURN:
                    quitman = true;
                    break;
                case SDLK_ESCAPE:
                    quitman = true;
                    quit = true;
                    break;
                default:
                    ;
                }
            }
        }

        rke_aplica_tela(screen, ManPage);
        rke_aplica_tela(screen, Monsters[page]);
        SDL_Flip(screen);
    }

    rke_libera_tela(ManPage);

    for(page = 0; page < pagenum; page++)
    {
        rke_libera_tela(Monsters[page]);
    }

    if(quit)
        return SAIR;

    else
        return INICIO;
}
