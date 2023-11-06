#ifndef _AEROPORTO_
#define _AEROPORTO_

#include "utilidade.h"

//repetidos no voo
//queries de estatisticas top N aeroportos

typedef struct aeroporto {
    char[3] nome;
    int *id_voo;        //q5 ordenados em arvore
} Aeroporto;

#endif