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
    int maior = 0;
    Date *reservDate = getReservBegin((Reservation *) ordlist->data[higher]);
    if (compareDates(reservDate, date) > 0) return -1; //se último dia da lista for menor que a data
    reservDate = getReservBegin((Reservation *) ordlist->data[lower]);
    if (compareDates(reservDate, date) <= 0) return 0; //se primeiro dia da lista for maior ou igual que a data
    reservDate = getReservBegin((Reservation *) ordlist->data[index]);
    //enquanto as datas nao forem iguais ou indice diferente de limites
    while ((maior = compareDates(reservDate, date)) != 0 && index != lower) {
        if (maior == -1) //se data for menor que a data do indice
            higher = index; //limite superior igual a indice
        else //caso contrário
            lower = index; //limite inferior igual a indice
        index = (higher + lower) / 2; //novo indice entre os dois limites
        reservDate = getReservBegin(ordlist->data[index]);
    }
    if (maior == 0 && index > 0) { //se ambas as datas sao iguais procura a indice incial onde são iguais
        Reservation *reservDatePrevious = getReservBegin(ordlist->data[index-1]);
        while ( index > 0 && compareDates(reservDate, reservDatePrevious) == 0) {
            index--;
            reservDate = getReservBegin(ordlist->data[index]);
            if (index > 0)
            reservDatePrevious = getReservBegin(ordlist->data[index-1]);
        }
    }
//    if (index == lower) index++;

    return index;
}

int searchDataOrdList(OrdList *list, void *data, int (*compareFunction)(void*,void*), int equal, int searchBack) {
    int lower = 0, higher = list->size - 1;
    int i = (higher + lower) / 2, compare;
    void *compareData = list->data[i];
    while ((compare = compareFunction(data, compareData)) != equal && (higher - lower) > 1) {
        if (compare < equal) higher = i;
        else lower = i;
        i = (higher + lower) / 2;
        compareData = list->data[i];
    }
    if (higher - lower == 1 && compare != equal) return -1;
    if (searchBack) {
        while (i > 0 && compare == equal) {
            compareData = list->data[i-1];
            compare = compareFunction(data, compareData);
            i--;
        }
        if (compare != equal) i++;
    }

    return i;
}

void removeOrdList(OrdList *ordList, unsigned int key) {
}

void radixSort(OrdList *list, int (*getParameterFunction)(void*), int interval, int offset) {
    int size = list->size;
    void **newData = malloc(sizeof(void *) * size); //cria nova lista
    void *data;
    int count[interval+1], i ,j;
    for (i=0; i<=interval; i++) count[i] = 0;
    for (j=0; j<size; j++) {
        //conta ocorrencias de cada parametro
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
    free(list->data);
    list->data = newData;
}

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
    radixSort(list, getBeginSeconds, 60, 0);
    radixSort(list, getBeginMinutes, 60, 0);
    radixSort(list, getBeginHours, 24, 0);
    radixSort(list, getBeginDay, 31, 0);
    radixSort(list, getBeginMonth, 12, 0);
    radixSort(list, getBeginYear, N_YEARS, BEGIN_YEAR);
}

void swapOrdList(OrdList *list, int i, int j) {
    void *aux = list->data[i];
    list->data[i] = list->data[j];
    list->data[j] = aux;
}

int partitionOrdList(OrdList *list, int lower, int higher, void *pivotData, int (*compareFunction)(void*,void*), int equal) {
    void *data = getDataOrdList(list, lower);
    while (higher > lower) {
        while (compareFunction(data, pivotData) < equal) {
            lower++;
            data = getDataOrdList(list, lower);
        }
        data = getDataOrdList(list, higher);
        while (higher >= lower && compareFunction(data, pivotData) >= equal) {
            higher--;
            data = getDataOrdList(list, higher);
        }
        if (lower < higher)
            swapOrdList(list, lower, higher);
    }

    return lower;
}

void quickSort(OrdList* list, int lower, int higher, int (*compareFunction)(void*,void*), int equal) {
    if (higher - lower > 1) {
        int pivot = (lower + higher) / 2;
        swapOrdList(list, pivot, higher);
        void *pivotData = getDataOrdList(list, higher);
        int partition = partitionOrdList(list, lower, higher-1, pivotData, compareFunction, equal);
        swapOrdList(list, partition, higher);
        quickSort(list, lower, partition-1, compareFunction, equal);
        quickSort(list, partition+1, higher, compareFunction, equal);
    }
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

void swap (OrdList *ordlist, int i, int j) {
    void* data_i = ordlist->data[i];
    ordlist->data[i] = ordlist->data[j];
    ordlist->data[j] = data_i;
}
