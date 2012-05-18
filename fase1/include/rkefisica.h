/**
 * \file rkefisica.h
 * \brief Arquivo header da biblioteca de funções físicas.
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

extern void rke_set_delta_t(double d_t);
extern void rke_set_arrasto(double coef_arrasto);
extern void rke_set_vetor_mundo(double x, double y);
extern void rke_set_numero_objetos(int numero);
extern void rke_adiciona_objeto(int id, double x, double y, double v_x, double v_y, double massa, double tempo);
extern objeto rke_get_objeto(int i);
extern int rke_conta_objetos();
extern void rke_simula();