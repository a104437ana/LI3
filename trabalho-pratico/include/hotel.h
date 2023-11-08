#ifndef _HOTEL_
#define _HOTEL_

#include "utility.h"

//repetidos na reservation
//queries de estatistica receita total entre duas datas

typedef struct hotel {
    char *id;
    char *name;
    char stars;          //q3
    char *address;
    int cityTax;
    char **reservations;        //q4
} Hotel;

#endif