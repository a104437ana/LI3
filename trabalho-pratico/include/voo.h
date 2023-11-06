#ifndef _VOO_
#define _VOO_

#include "utilidade.h"
#include "passageiro.h"

typedef struct voo {
    int id;
    char *companhia;            //q1
    char *aviao;                //q1
    int lugares;
    char origem[3];             //q1
    char destino[3];            //q1
    Data partida_est;           //q1/q2
    Data chegada_est;           //q1
    Data partida_real;
    Data chegada_real;
    char *piloto;
    char *copiloto;
    char *notas;
    Passageiro *passageiros;    //q1
} Voo;

#endif