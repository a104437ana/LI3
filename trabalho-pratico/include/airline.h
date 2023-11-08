#ifndef _AIRLINE_
#define _AIRLINE_

#include "utility.h"

//repetidos no flight
//queries de estatisticas top N aeroportos

typedef struct airline {
    char[3] name;
    int *id_flight;        //q5 ordenados em arvore
} Airline;

#endif