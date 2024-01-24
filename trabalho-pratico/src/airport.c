#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"
#include "utility.h"

struct airport {
    char name[4];
    double median;
    OrdList *originFlights;
    OrdList *destinationFlights;
    int *listOfDelays;
    int maxSize_list;
    int size_list;
};

//cria um novo aeroporto
Airport *createAirport(char *name) {
    Airport *airport = malloc(sizeof(Airport));
    memcpy(airport->name, name, 4);
    airport->originFlights = createOrdListInt();
    airport->destinationFlights = createOrdListInt();
    airport->median = -1.0;
    airport->size_list = 0;
    airport->listOfDelays = malloc(sizeof(int)*500);
    airport->maxSize_list = 500;

    return airport;
}

//adiciona voo à lista de voos de um aeroporto
void addFlightToAirport(Airport *airport, unsigned long int id_flight, int origin) {
    if (origin)
    addOrdListInt(airport->originFlights, id_flight);
    else
    addOrdListInt(airport->destinationFlights, id_flight);
}

void addDelayToAirport(Airport* airport, int delay) {
    if (airport->maxSize_list == airport->size_list) {
        airport->maxSize_list *= 2;
        airport->listOfDelays = (int*)realloc(airport->listOfDelays, airport->maxSize_list * sizeof(int));
    }
    airport->listOfDelays[airport->size_list] = delay;
    airport->size_list++;
}

//ordena os voos do aeroporto
void sortAirportFlightsByDepartureDate_airport(Airport *airport, void (*radixsortFlightsDate)(void*,void*), void *lookup) {
    OrdList *origin = airport->originFlights;
    OrdList *destination = airport->destinationFlights;
    if (!isOrdered(origin)) {
        heapsortInt(origin, intcmpReverse, NULL, 0); //ordena por ids
        radixsortFlightsDate(origin, lookup); //ordena por datas
        setOrdListOrd(origin, 1);
    }
    if (!isOrdered(destination)) {
        heapsortInt(destination, intcmpReverse, NULL, 0); //ordena por ids
        radixsortFlightsDate(destination, lookup); //ordena por datas
        setOrdListOrd(destination, 1);
    }
}

//ordena a lista de atrasos de um aeroporto
int sortAirportDelays (Airport* airport) {
    int size = airport->size_list;
    if (size == 0) return -1;
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
    return airport->median;
}

//gets
char *getAirportId(Airport *airport) {
    char * res = strdup(airport->name);
    return res;
}

double getAirportMedian(Airport *airport) {
    return airport->median;
}

int getAirportListSize(Airport *airport) {
    return getOrdListSize(airport->originFlights);
}

//obtem a lista de voos do aeroporto
OrdList *getAirportOriginOrdList(Airport *airport) {
    return airport->originFlights;
}

OrdList *getAirportDestinationOrdList(Airport *airport) {
    return airport->destinationFlights;
}

//obtem o número de passageiros do aeroporto num dado ano
int getAirportPassengersYear(int year, Airport *airport, int (*compareFunction)(unsigned long int,unsigned long int,void*), int equal, void *lookup, int (*getFunction)(unsigned long int,void*)) {
    OrdList *origin = airport->originFlights; //voos de origem do aeroporto
    OrdList *destination = airport->destinationFlights; //voos de destino do aeroporto
    int i = searchValueOrdList(origin, year, compareFunction, lookup, equal, compareFunction, 0);
    int passengers = 0, size, exit;
    if (i >= 0) { //se não houver voos nesse ano
        size = getOrdListSize(origin);
        exit = 0;
        while (i < size && !exit) {
            unsigned long int id = getValueOrdList(origin, i);
            if (compareFunction(year, id, lookup) != equal) exit = 1; //se já não estamos no ano pedido
            else {
                i++;
                passengers+=getFunction(id, lookup); //adiona número de passageiros do voo
            }
        }
    }
    i = searchValueOrdList(destination, year, compareFunction, lookup, equal, compareFunction, 0);
    if (i >= 0) { //se houver voos nesse ano
        exit = 0;
        size = getOrdListSize(destination);
        while (i < size && !exit) {
            unsigned long int id = getValueOrdList(destination, i);
            if (compareFunction(year, id, lookup) != equal) exit = 1; //se já não estamos no ano pedido
            else {
                i++;
                passengers+=getFunction(id, lookup); //adiciona número de passageiros do voo
            }
        }
    }
    return passengers;
}

//sets

//sort
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

//liberta espaço em memória do aeroporto
void destroyAirport(void *airport) {
    destroyOrdListInt(((Airport *) airport)->originFlights);
    destroyOrdListInt(((Airport *) airport)->destinationFlights);
    free(((Airport*)airport)->listOfDelays);
    free(((Airport *) airport)->name);
}
