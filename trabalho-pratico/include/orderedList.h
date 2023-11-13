#ifndef _ORDERED_LIST_
#define _ORDERED_LIST_

#include "utility.h"

typedef struct ordList OrdList;

OrdList *createOrdList(int size);
//acabar
void *searchOrdList(OrdList *ordList, unsigned int key);
void addOrdList(OrdList *ordList, void *data);
//falta libertar espaço em memória
void removeOrdList(OrdList *ordList, unsigned int key);
void destroyOrdList(OrdList *ordList);
//ordenação
void radixSort(OrdList *list, int (*getParameterFunction)(void*), int interval, int offset);
void radixSortDate(OrdList *list);

void *getDataOrdList(OrdList *ordList, int index);
//para testar
void printOrdList(OrdList *ordList, void (*printFunction)(void*));

#endif