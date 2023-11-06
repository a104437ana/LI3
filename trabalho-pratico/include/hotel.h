#ifndef _HOTEL_
#define _HOTEL_

#include "utilidade.h"

//repetidos na reserva
//queries de estatistica receita total entre duas datas

typedef struct hotel {
    char *id;
    char *nome;
    char estrelas;          //q3
    char *morada;
    int imposto_cidade;
    char **reservas;        //q4
} Hotel;

#endif