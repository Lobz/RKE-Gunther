//
//  rkefisica.h
//  
//
//  Created by Ricardo Macedo on 17/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

extern void rke_set_delta_t(double d_t);
extern void rke_set_arrasto(double coef_arrasto);
extern void rke_set_vetor_mundo(double x, double y);
extern void rke_set_numero_objetos(int numero);
extern void rke_adiciona_objeto(int id, double x, double y, double v_x, double v_y, double massa, double tempo);
extern objeto rke_get_objeto(int i);
extern void rke_simula();