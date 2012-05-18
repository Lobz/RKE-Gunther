//
//  rketypes.h
//  
//
//  Created by Ricardo Macedo on 17/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#define BARCOID  -1
#define ESTATICO -1

typedef struct struct_vetor
{
    double x, y;
} vetor;


typedef struct struct_objeto
{
    int id;
    double x, y;
    double v_x, v_y;
    double massa;
    double tempo;
} objeto;
