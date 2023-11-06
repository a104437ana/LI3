#ifndef _RESERVA_
#define _RESERVA_

#include "utilidade.h"

//q1 - n_noites e preco total

typedef struct reserva {
    char *id;                       //q2
    char *id_utilizador;
    char *id_hotel;                 //q1
    char *nome_hotel;               //q1
    char estrelas_hotel;            //q1
    int imposto_cidade;
    char *morada_hotel;
    Data inicio;                    //q1/q2/q4
    Data fim;                       //q1
    int preco_por_noite;
    bool inclui_pequeno_almoco;     //q1
    char *detalhes_quarto;
    char classificacao_utilizador;
    char *comentario_utilizador;
} Reserva;

#endif