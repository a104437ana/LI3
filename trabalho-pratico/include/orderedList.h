#ifndef _ORDERED_LIST_
#define _ORDERED_LIST_

#include "utility.h"

typedef struct ordList OrdList;

OrdList *createOrdList(int size);
//acabar
void *searchOrdList(OrdList *ordList, unsigned int key);
void addOrdList(OrdList *ordList, void *data);
int searchReservDateIndex(OrdList *ordlist, Date *date);
//falta libertar espaço em memória
void removeOrdList(OrdList *ordList, unsigned int key);
//void destroyOrdList(OrdList *ordList);
//ordenação
void radixSort(OrdList *list, int (*getParameterFunction)(void*), int interval, int offset);
void radixSortDate(OrdList *list);
void radixSortReservDate(OrdList *list);
void radixSortFlightDate(OrdList *list);
void radixSortUserList(OrdList *list);
void quickSort(OrdList *list, int (*compareFunction)(void*));
void sortByName(char **names, int size);

void *getDataOrdList(OrdList *ordList, int index);
int getOrdListSize(OrdList *ordList);
void setDataOrdList (OrdList *ordList, int index, void* data);
//para testar
void printOrdList(OrdList *ordList, void (*printFunction)(void*));

void destroyOrdList(OrdList *ordlist, void (*destroyDataFunction)(void*));
//void destroyFlights(OrdList *flights);
//void destroyReservations(OrdList *reservations);
void swap (OrdList *ordlist, int i, int j);

#endif