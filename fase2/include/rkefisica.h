/**
 * \file rkefisica.h
 * \brief Arquivo header da biblioteca de funções físicas.
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "rketypes.h"

void rke_set_delta_t(double d_t);
void rke_set_arrasto(double coef_arrasto);
void rke_set_vetor_mundo(double x, double y);
void rke_set_numero_objetos(int numero);
void rke_adiciona_objeto(int id, double x, double y, double v_x, double v_y, double massa, double tempo);
objeto rke_get_objeto(int i);
int rke_conta_objetos();
void rke_simula();
