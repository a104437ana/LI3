#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"
#include "flight.h"
#include "orderedList.h"
#include "utility.h"

struct airport {
    char name[4];
    double median;
    OrdList *flightsByDepartureDate;
    int *listOfDelays;
    int maxSize_list;
    int size_list;
};

//cria um novo aeroporto
Airport *createAirport(char *name) {
    Airport *airport = malloc(sizeof(Airport));
    memcpy(airport->name, name, 4);
    airport->flightsByDepartureDate = createOrdList();
    airport->median = 0.0;
    airport->size_list = 0;
    airport->listOfDelays = malloc(sizeof(int)*500);
    airport->maxSize_list = 500;

    return airport;
}

//adiciona voo à lista de voos de um aeroporto
void addFlightToAirport(Airport *airport, char *id_flight) {
    char *flight = strdup(id_flight);
    addOrdList(airport->flightsByDepartureDate, flight);
}

void addDelayToAirport(Airport* airport, int delay) {
    if (airport->maxSize_list == airport->size_list) {
        airport->maxSize_list *= 2;
        airport->listOfDelays = (int*)realloc(airport->listOfDelays, airport->maxSize_list * sizeof(int));
    }
    airport->listOfDelays[airport->size_list] = delay;
    airport->size_list++;
}

int compareFlightsIds(void *id1, void *id2) {
//    char *id1 = getFlightId((Flight *) flight1), *id2 = getFlightId((Flight *) flight2);
    return strcoll(id1, id2);
}

//ordena os voos do aeroporto
void sortAirportFlightsByDepartureDate(void *airport, Hashtable *lookupTable) {
    OrdList *flightsByDepartureDate = ((Airport *) airport)->flightsByDepartureDate;
    quickSort(flightsByDepartureDate, 0, getOrdListSize(flightsByDepartureDate)-1, compareFlightsIds, 0); //ordena por ids
    radixSortFlightDate(flightsByDepartureDate, lookupTable); //ordena por datas
    setOrdListOrd(flightsByDepartureDate, 1);
    reverseOrdList(flightsByDepartureDate);
}

//obtem a lista de voos do aeroporto
OrdList *getAirportOrdList(Airport *airport) {
    return airport->flightsByDepartureDate;
}

//gets
char *getAirportId(Airport *airport) {
    char * res = strdup(airport->name);
    return res;
}

double getAirportMedian(Airport *airport) {
    return airport->median;
}

void swapL(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partitionL(int a[], int high, int pivot) {
    int i = -1;
    for (int j = 0; j < high; j++) {
        if (a[j] > pivot) {
            i++;
            swapL(a, i, j);
        }
    }
    return i + 1;
}

void qsortL (int a[], int n) {
    if (n < 2) return;
    int p = partitionL(a, n-1, a[n-1]);
    swapL(a, p, n-1);
    qsortL(a, p);
    qsortL(a+p+1, n-p-1);
}

void sortAirportDelays (Airport* airport) {
    int size = airport->size_list;
    qsortL(airport->listOfDelays,size);
    if (size % 2 == 0) {
        int indice1 = size / 2;
        int indice2 = indice1 - 1;
        int mediana1 = airport->listOfDelays[indice1];
        int mediana2 = airport->listOfDelays[indice2];
        double mediana = ((double) mediana1) + ((double) mediana2);
        airport->median = (double) (mediana/2.0);
    }
    else {
        int indice = size / 2;
        airport->median = airport->listOfDelays[indice];
    }
}
//sets

//liberta espaço em memória do aeroporto
void destroyAirport(void *airport) {
    destroyOrdList(((Airport *) airport)->flightsByDepartureDate, free);
    free(((Airport*)airport)->listOfDelays);
    free(((Airport *) airport)->name);
}
