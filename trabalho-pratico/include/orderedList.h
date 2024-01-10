#ifndef _ORDERED_LIST_
#define _ORDERED_LIST_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "hashtable.h"

typedef struct ordList OrdList;
//cria uma nova lista
OrdList *createOrdList();
//adiciona um novo elemento à lista
void addOrdList(OrdList *ordList, void *data);
//procura um elemento na lista
int searchDataOrdList(OrdList *list, void *data, int (*compareFunction)(void*,void*,void*), void *lookup, int equal, int (*searchBackFunction)(void*,void*,void*));
void removeOrdList(OrdList *ordList, unsigned int key);
void printFullList(OrdList *list);

//ordenação
//radixsorts
void radixSort(OrdList *list, int (*getParameterFunction)(void*,void*), void *lookupTable, int interval, int offset);
//quicksorts
void quickSort(OrdList *list, int lower, int higher, int (*compareFunction)(void*,void*), int equal);
//inverte uma lista
void reverseOrdList(OrdList* list);

//obtem elemento da lista
void *getDataOrdList(OrdList *ordList, int index);
//obtem numero de elementos da lista
int getOrdListSize(OrdList *ordList);
//verifica de uma lista está ordenada
bool isOrdered(OrdList *ordList);
//modifica elemento da lista
void setDataOrdList (OrdList *ordList, int index, void* data);
//função que altera o campo de uma lista que diz se ela está ou não ordenada
void setOrdListOrd (OrdList *ordList, bool ord);

//imprime todos os elementos da lista, para efeitos de testes
void printOrdList(OrdList *ordList, void (*printFunction)(void*));

//liberta espaço em memória da lista
void destroyOrdList(OrdList *ordlist, void (*destroyDataFunction)(void*));
//liberta apenas espaço em memória da lista
void destroyOnlyOrdList(OrdList *list);
//troca posição de dois elementos da lista
void swap (OrdList *ordlist, int i, int j);

#endif