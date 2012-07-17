/**
 * \file rketypes.h
 * \brief Arquivo header de tipos e defines do Red Knife Engine
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#define BARCOID  -1
#define ESTATICO -1.0

/**
 * Struct vetor
 * \param x Componente x
 * \param y Componente y
 */
typedef struct struct_vetor
{
    double x, y;
} vetor;

/**
 * Struct objeto
 * \param id    Identificador único
 * \param x Componente x
 * \param y Componente y
 * \param v_x   Componente x da velocidade do objeto
 * \param v_y   Componente y da velocidade do objeto
 * \param massa Massa do objeto
 * \param tempo Tempo de vida do objeto
 */
typedef struct struct_objeto
{
    int id;
    double x, y;
    double v_x, v_y;
    double massa;
    double tempo;
} objeto;
