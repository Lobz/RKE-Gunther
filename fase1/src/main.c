//
//  main.c
//  
//
//  Created by Ricardo Macedo on 16/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/rketypes.h"
#include "../include/rkefisica.h"

int main(int argc, char* argv[])
{
    double dt = 1000.0;
    double arrasto = 0.0;
    double vento_x, vento_y;
    double bomba_tempo, bomba_x, bomba_y;
    double barco_massa, barco_vx, barco_vy, barco_x, barco_y;
    
    char* nome_arquivo;
    char comando[5];
    
    int i, bomba_id, bomba_num;
    int iteracoes = 1;
    
    FILE *arquivo;
    objeto obj;
    
    if (argc == 1)
    {
        printf("RKE v0.1\nTestador do Modulo de Fisica\n\n");
        printf("Uso:\n");
        printf("  -f <arquivo>   carrega os dados do arquivo para a simulacao\n");
        printf("  -d <valor>     granularidade da simulação em milesimos de segundo [padrao = 1000]\n");
        printf("  -n <valor>     numero de iteracoes que a simulacao ira rodar\n");
        printf("  -a <valor>     coefiente de arrasto da superficie de 0.0 a 1.0 [padrao = 0.0]\n\n");
        
        return 0;
    }
    
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            i++;
            nome_arquivo = argv[i];
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            i++;
            dt = atof(argv[i]);
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            i++;
            iteracoes = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-a") == 0)
        {
            i++;
            arrasto = atof(argv[i]);
        }
    }
    
    rke_set_delta_t(dt / 1000.0);
    rke_set_arrasto(arrasto);
    
    arquivo = fopen(nome_arquivo, "r");
    
    while (!feof(arquivo))
    {
        fscanf(arquivo, "%s", comando);
        
        if (strcmp(comando, ".w") == 0)
        {
            fscanf(arquivo, "%lf %lf", &vento_x, &vento_y);
            rke_set_vetor_mundo(vento_x, vento_y);
        }
        else if (strcmp(comando, ".b") == 0)
        {
            fscanf(arquivo, "%d", &bomba_num);
            rke_set_numero_objetos(bomba_num);
            
            for (i = 0; i < bomba_num; i++)
            {
                fscanf(arquivo, "%d %lf %lf %lf", &bomba_id, &bomba_tempo, &bomba_x, &bomba_y);
                rke_adiciona_objeto(bomba_id, bomba_x, bomba_y, 0.0, 0.0, 1.0, bomba_tempo);
            }
        }
        else if (strcmp(comando, ".s") == 0)
        {
            fscanf(arquivo, "%lf %lf %lf %lf %lf", &barco_massa, &barco_x, &barco_y, &barco_vx, &barco_vy);
            rke_adiciona_objeto(BARCOID, barco_x, barco_y, barco_vx, barco_vy, barco_massa, ESTATICO);
        }
    }
    
    fclose(arquivo);
    
    for (i = 0; i < iteracoes; i++)
        rke_simula();
    
    arquivo = fopen("saida.out", "w");
    
    fprintf(arquivo, ".w\n%f\n%f\n", vento_x, vento_y);
    
    fprintf(arquivo, ".b\n");
    for (i = 0; i < (bomba_num + 1); i++)
    {
        obj = rke_get_objeto(i);
        
        if (obj.id == BARCOID)
        {
            barco_x     =     obj.x;
            barco_y     =     obj.y;
            barco_vx    =   obj.v_x;
            barco_vy    =   obj.v_y;
            barco_massa = obj.massa;
            
            continue;
        }
        if (obj.tempo > 0.0)
            fprintf(arquivo, "%d %f %f %f \n", obj.id, obj.tempo, obj.x, obj.y);
    }
    
    fprintf(arquivo, ".s\n%f\n%f\n%f\n%f\n%f\n", barco_massa, barco_x, barco_y, barco_vx, barco_vy);
    
    return 0;
}