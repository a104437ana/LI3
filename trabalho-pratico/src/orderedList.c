#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orderedList.h"
#include "utility.h"
#include "reservation.h"
#include "flight.h"
#include "queries.h"

struct ordList {
    int maxSize;
    int size;
    void **data;
};

OrdList *createOrdList(int size) {
    OrdList *ordList = malloc(sizeof(OrdList));
    void **data = malloc(sizeof(void *) * size);
    ordList->maxSize = size;
    ordList->size = 0;
    ordList->data = data;

    return ordList;
}
//acabar
void *searchOrdList(OrdList *ordList, unsigned int key) {
    return ordList->data[key];
}

void addOrdList(OrdList *ordList, void *data) {
    int maxSize = ordList->maxSize;
    int size = ordList->size;
//    void **ordData = ordList->data;
    if (size == maxSize) {
        maxSize *= 2;
        void **newData = malloc(sizeof(void *) * maxSize);
        int i=0;
        while (i < size) {
            newData[i] = ordList->data[i];
            i++;
        }
        free(ordList->data);
        ordList->data = newData;
        ordList->maxSize = maxSize;
    }
    ordList->data[size] = data;
    ordList->size = size + 1;
    ordList->maxSize = maxSize;
}
//procura indice da primeira data com dia igual ou maior que a data dada
int searchReservDateIndex(OrdList *ordlist, Date *date) {
    int size = ordlist->size;
    int lower = 0, higher = size - 1;
    int index = size / 2;
    int day = getDay(date), reservDay = getReservBeginDay(ordlist->data[index]);
    if (getReservBeginDay(ordlist->data[higher]) < day) return -1;
    if (getReservBeginDay(ordlist->data[lower]) >= day) return 0;
    while (reservDay != day && index != lower) {
        if (reservDay > day)
            higher = index;
        else
            lower = index;
        index = (higher + lower) / 2;
        reservDay = getReservBeginDay(ordlist->data[index]);
    }
    if (index == lower) index++;

    return index;
}

void removeOrdList(OrdList *ordList, unsigned int key) {
}

void radixSort(OrdList *list, int (*getParameterFunction)(void*), int interval, int offset) {
    int size = list->size;
    void **newData = malloc(sizeof(void *) * size);
    void *data;
    int count[interval+1], i ,j;
    for (i=0; i<=interval; i++) count[i] = 0;
    for (j=0; j<size; j++) {
        //conta ocorrencias
        data = list->data[j];
        i = (*getParameterFunction)(data) - offset;
        count[i] += 1;
    }
    for (i=1; i<=interval; i++) count[i] += count[i-1];
    for (j=size-1; j>=0; j--) {
        data = list->data[j];
        i = (*getParameterFunction)(data) - offset;
        newData[count[i]-1] = data;
        count[i] -= 1;
    }
//    for (i=0; i<size; i++) printf("%d / %d / %d\n", getReservBeginDay(list->data[i]), getReservBeginMonth(list->data[i]),getReservBeginYear(list->data[i]));
//    void **oldData = list->data;
    free(list->data);
    list->data = newData;
//    free(oldData);
}

//void radixSortDate(OrdList *list, void *(*getDateFunction)(void*)) {
//    radixSort(list, getDay, getDateFunction, 31, 0);
//    radixSort(list, getMonth, getDateFunction, 12, 0);
//    radixSort(list, getYear, getDateFunction, N_YEARS, BEGIN_YEAR);
//}

void radixSortReservDate(OrdList *list) {
    radixSort(list, getReservBeginDay, 31, 0);
    radixSort(list, getReservBeginMonth, 12, 0);
    radixSort(list, getReservBeginYear, N_YEARS, BEGIN_YEAR);
}

void radixSortFlightDate(OrdList *list) {
    radixSort(list, getFlightScheduleDepartureDay, 31, 0);
    radixSort(list, getFlightScheduleDepartureMonth, 12, 0);
    radixSort(list, getFlightScheduleDepartureYear, N_YEARS, BEGIN_YEAR);
}

void radixSortUserList(OrdList *list) {
    radixSort(list, getBeginDay, 31, 0);
    radixSort(list, getBeginMonth, 12, 0);
    radixSort(list, getBeginYear, N_YEARS, BEGIN_YEAR);
}

//void quickSortUserNames(OrdList *list) {
//    qSort(list->data, list->size, strcmp);
//}

void *getDataOrdList(OrdList *ordList, int index) {
    return ordList->data[index];
}

int getOrdListSize(OrdList *ordList) {
    return ordList->size;
}

void setDataOrdList (OrdList *ordList, int index, void* data) {
    void *oldData = ordList->data[index];
    ordList->data[index] = data;
    free(oldData);
}

void printOrdList(OrdList *ordList, void (*printFunction)(void*)) {
    int size = ordList->size;
    void **data = ordList->data;
    for (int i=0; i<size; i++) {
        (*printFunction)(data[i]);
    }
    printf(")");
}

void destroyOrdList(OrdList *ordlist, void (*destroyDataFunction)(void*)) {
    if (ordlist == NULL) return;
    void **data = ordlist->data;
    int size = ordlist->size;
    for (int i=0; i<size; i++)
        (*destroyDataFunction)(data[i]);
    free(ordlist);
}
