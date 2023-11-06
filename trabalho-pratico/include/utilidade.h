#ifndef _UTILIDADE_
#define _UTILIDADE_

#include <stdbool.h>

typedef struct hora {
    char horas;
    char minutos;
    char segundos;
} Hora;

typedef struct data {
    int ano;
    char mes;
    char dia;
    bool tem_horas;
    Hora hora;
} Data;

typedef struct telemovel {
    char indicativo[3];
    char numero[9];
} Telemovel;

typedef enum genero {
    MASCULINO,
    FEMININO,
} Genero;

#endif