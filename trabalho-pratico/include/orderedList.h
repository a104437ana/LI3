#ifndef _ORDERED_LIST_
#define _ORDERED_LIST_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "reservation.h"
#include "flight.h"
#include "queries.h"

typedef struct ordList OrdList;
//cria uma nova lista
OrdList *createOrdList(int size);
//adiciona um novo elemento à lista
void addOrdList(OrdList *ordList, void *data);
//procura um elemento na lista
int searchDataOrdList(OrdList *list, void *data, int (*compareFunction)(void*,void*), int equal, int searchBack);
void removeOrdList(OrdList *ordList, unsigned int key);

//ordenação
//radixsorts
void radixSort(OrdList *list, int (*getParameterFunction)(void*), int interval, int offset);
void radixSortReservDate(OrdList *list);
void radixSortFlightDate(OrdList *list);
void radixSortUserList(OrdList *list);
//quicksorts
void quickSort(OrdList *list, int lower, int higher, int (*compareFunction)(void*,void*), int equal);
void reverseOrdList(OrdList* list);

//obetem elemento da lista
void *getDataOrdList(OrdList *ordList, int index);
//obtem numero de elementos da lista
int getOrdListSize(OrdList *ordList);
//modifical elemento da lista
void setDataOrdList (OrdList *ordList, int index, void* data);

//imprime todos os elementos da lista, para efeitos de testes
void printOrdList(OrdList *ordList, void (*printFunction)(void*));

//liberta espaço em memória da lista
void destroyOrdList(OrdList *ordlist, void (*destroyDataFunction)(void*));
//liberta apenas espaço em memóra da lista
void destroyOnlyOrdList(OrdList *list);
//troca posição de dois elementos da lista
void swap (OrdList *ordlist, int i, int j);
//inverte uma lista
void reverseOrdList(OrdList* list);

#endif