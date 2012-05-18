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


/* set_delta_t(double d_t)
 *
 * indica qual a resolucao da simulacao
 */
void rke_set_delta_t(double d_t)
{
    delta_t = d_t;
}

void rke_set_arrasto(double coef_arrasto)
{
    arrasto = coef_arrasto;
}


/* set_vetor_mundo(double x, double y)
 *
 * configura o vetor base que regirá todos os objetos do mundo
 */
void rke_set_vetor_mundo(double x, double y)
{
    mundo.x = x;
    mundo.y = y;
}

void rke_set_numero_objetos(int numero)
{
    objetos = malloc( (numero + 1) * sizeof(objeto) );
    num_objetos = numero;
}


/* itera_posicao(objeto* obj, vetor forca)
 *
 * de acordo com a resolucao da simulacao, soma a forca indicada ao objeto
 */
void itera_posicao(objeto* obj, vetor forca)
{
    if (obj->tempo == 0.0) return;
    
    obj->v_x += (forca.x / obj->massa);
    obj->v_y += (forca.y / obj->massa);
    
    obj->x += (obj->v_x * delta_t) + (forca.x / obj->massa) * (pow(delta_t, 2) / 2.0);
    obj->y += (obj->v_y * delta_t) + (forca.y / obj->massa) * (pow(delta_t, 2) / 2.0);
    
    // arrasto
    obj->v_x -= (arrasto / delta_t) * obj->v_x;
    obj->v_y -= (arrasto / delta_t) * obj->v_y;
    
    obj->x -= (arrasto / delta_t) * (forca.x / obj->massa) * (pow(delta_t, 2) / 2.0);
    obj->y -= (arrasto / delta_t) * (forca.y / obj->massa) * (pow(delta_t, 2) / 2.0);
    
    // tempo
    if (obj->tempo - delta_t <= 0.0) obj->tempo = 0.0;
    else obj->tempo -= delta_t;
}


vetor calcula_resultante(vetor forca1, vetor forca2)
{
    vetor resultante;
    resultante.x = forca1.x + forca2.x;
    resultante.y = forca1.y + forca2.y;
    
    return resultante;
}

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

objeto rke_get_objeto(int i)
{
    return objetos[i];
}

void rke_simula()
{
    int i;
    for (i = 0; i < num_objetos; i++)
        itera_posicao(&objetos[i], mundo);
}

