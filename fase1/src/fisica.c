/**
 * \file fisica.c
 * \brief Esta é a biblioteca de funções que lidam com a física do Red Knife Engine.
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/rketypes.h"


double delta_t;
double percentual_atrito;
double arrasto;
vetor mundo;

int ult_objeto = 0;
int num_objetos = 0; 
objeto* objetos;


/**
 * Indica a resolução da simulação. Este é o tamanho do quanta de tempo.
 * \param d_t   Resolução em segundos
 */
void rke_set_delta_t(double d_t)
{
    delta_t = d_t;
}

/**
 * Configura o coeficiente de arrasto da superfície.
 * \param coef_arrasto  Coeficiente de 0.0 a 1.0
 */
void rke_set_arrasto(double coef_arrasto)
{
    arrasto = coef_arrasto;
}


/**
 * Configura o vetor base que regirá todos os objetos do mundo.
 * \param x Componente x
 * \param y Componente y
 */
void rke_set_vetor_mundo(double x, double y)
{
    mundo.x = x;
    mundo.y = y;
}

/**
 * Configura o número total de objetos a serem simulados.
 * \param numero    Número de objetos
 */
void rke_set_numero_objetos(int numero)
{
    objetos = malloc( (numero + 1) * sizeof(objeto) );
    num_objetos = numero + 1;
}


/**
 * De acordo com a velocidade do objeto, o tempo de vida dele, o vetor mundo e a massa, calcula a posição seguinte no próximo quanta de tempo.
 * \param obj   Endereço do objeto
 * \param forca Força a ser aplicada
 */
void itera_posicao(objeto* obj, vetor forca)
{
    if (obj->tempo == 0.0) return;
    
    obj->x += (obj->v_x * delta_t) + (forca.x / obj->massa) * (pow(delta_t, 2) / 2.0);
    obj->y += (obj->v_y * delta_t) + (forca.y / obj->massa) * (pow(delta_t, 2) / 2.0);
    
    obj->v_x += delta_t * (forca.x / obj->massa);
    obj->v_y += delta_t * (forca.y / obj->massa);
    
    /** O arrasto é modelado como resistência viscosa, com um número de Reynolds desprezível.*/
    obj->v_x -= (arrasto * delta_t) * obj->v_x;
    obj->v_y -= (arrasto * delta_t) * obj->v_y;
    
    obj->x -= (arrasto * obj->v_x / obj->massa) * (pow(delta_t, 2) / 2.0);
    obj->y -= (arrasto * obj->v_y / obj->massa) * (pow(delta_t, 2) / 2.0);
    
    /* tempo */
    if (obj->tempo == ESTATICO) return;
    
    if (obj->tempo - delta_t <= 0.0) obj->tempo = 0.0;
    else obj->tempo -= delta_t;
}

/**
 * Adiciona um objeto à lista de objetos a serem simulados.
 * \param id    Identificador único do objeto
 * \param x Posição x do objeto
 * \param y Posição y do objeto
 * \param v_x Velocidade em x do objeto
 * \param v_y Velocidade em y do objeto
 * \param massa Massa do objeto
 * \param tempo Tempo de vida do objeto em segundos
 */
void rke_adiciona_objeto(int id, double x, double y, double v_x, double v_y, double massa, double tempo)
{
    objetos[ult_objeto].id    =    id;
    objetos[ult_objeto].x     =     x;
    objetos[ult_objeto].y     =     y;
    objetos[ult_objeto].v_x   =   v_x;
    objetos[ult_objeto].v_y   =   v_y;
    objetos[ult_objeto].massa = massa;
    objetos[ult_objeto].tempo = tempo;
    ult_objeto++;
}

/**
 * Retorna o i-ésimo objeto.
 * \param i Índice do objeto
 */
objeto rke_get_objeto(int i)
{
    return objetos[i];
}

/**
 * Conta o número de objetos ativos, ou seja, com tempo de vida diferente de zero.
 */
int rke_conta_objetos()
{
    int i, ativos = 0;
    
    for (i = 0; i < num_objetos; i++)
    {
        if (objetos[i].tempo != 0.0)
            ativos++;
    }
    
    return ativos;
}

/**
 * Simula todos os objetos por um quanta de tempo.
 */
void rke_simula()
{
    int i;
    for (i = 0; i < num_objetos; i++)
        itera_posicao(&objetos[i], mundo);
}

