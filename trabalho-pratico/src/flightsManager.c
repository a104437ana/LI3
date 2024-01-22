#include <stdio.h>
#include <stdlib.h>
#include "flightsManager.h"
#include "airportsManager.h"
#include "hashtable.h"
#include "utility.h"

struct flightsManager {
    Hashtable *flights;
    OrdList *flightsByDepartureDate;
};
//função que cria um catálogo de voos
FlightsManager *createFlightsCatalog(int size) {
    FlightsManager *flightsManager = malloc(sizeof(FlightsManager)); //aloca espaço para o catálogo
    flightsManager->flights = createHashtable(size, hashInt, intcmpVoid, intdupVoid, destroyFlight); //cria uma hashtable para o catálogo
    flightsManager->flightsByDepartureDate = createOrdList();
    return flightsManager;
}
//função que adiciona um voo ao catálogo de voos
int addFlightToCatalog(int id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog) {
    Flight *flight = createFlight(airline, airplane, origin, destination, scheduleDeparture, scheduleArrival, realDeparture, realArrival);
    flightsCatalog->flights = addHashtable(flightsCatalog->flights, flight, &id);
    addOrdList(flightsCatalog->flightsByDepartureDate, flight);
    return getDelay(flight);
}

//adiciona o utilizador à lista de passageiros do voo
void addUserToFlight(int id_flight, char *id_user, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, &id_flight);
    addPassengerToFlight(flight, id_user);
}

void radixSortDeparture(OrdList *list, void *lookupTable) {
    radixSort(list, getDepartureDay, lookupTable, 31, 0);
    radixSort(list, getDepartureMonth, lookupTable, 12, 0);
    radixSort(list, getDepartureYear, lookupTable, N_YEARS, BEGIN_YEAR);
}

void sortFlightsByDepartureDate(FlightsManager * flightsCatalog) {
    OrdList *list = flightsCatalog->flightsByDepartureDate;
    if (!isOrdered(list)) {
        radixSortDeparture(list, NULL); //ordena as reservas por data
        setOrdListOrd(list, 1);
    }
}

//gets
Flight *getFlightCatalog(FlightsManager *flightsManager, int *id) {
    Flight *flight = (Flight*) getData(flightsManager->flights, id);
    return flight;
}

int existsFlight (FlightsManager* flightsManager,char* id) {
    int key = atoi(id);
    return existsData(flightsManager->flights, &key);
}

Hashtable *getHashtableFlightsCatalog(FlightsManager *flightsManager) {
    return flightsManager->flights;
}

OrdList * getFlightsByDeparture(FlightsManager * flights){
    return (flights->flightsByDepartureDate);
}

int getFlightSD_flightscatalog(int time, int id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, &id);
    return getFlightSD(time, flight);
}

int getDepartureDayFlight(int id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, &id);
    return getDepartureDay(flight, NULL);
}

int getDepartureMonthFlight(int id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, &id);
    return getDepartureMonth(flight, NULL);
}

int getDepartureYearFlight(int id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, &id);
    return getDepartureYear(flight, NULL);
}

int getFirstFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog) {
    Flight *flight = getDataOrdList(flightsCatalog->flightsByDepartureDate, 0);
    return getDepartureYear(flight, NULL);
}

int getLastFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog) {
    OrdList *list = flightsCatalog->flightsByDepartureDate;
    Flight *flight = getDataOrdList(list, getOrdListSize(list)-1);
    return getDepartureYear(flight, NULL);
}

//função que liberta o espaço em memória alocado pelo catálogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager) {
    if (flightsManager == NULL) return; //se não exitir o catálogo
    destroyHashtable(flightsManager->flights); //liberta a hashtable
    destroyOnlyOrdList(flightsManager->flightsByDepartureDate);
    free(flightsManager);
}

//queries
void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, QueryResult* result) {
    int key = flightIdToInt(id);
    Flight* flight = getData(flightsManager->flights,&key);
    if (flight == NULL)
        return;
    else {
        setNumberResults(result,1);
        setNumberFieldsQ(result, 0, 8);
        char* airline = getFlightAirline(flight); char * field0 = strdup("airline");
        char* plane_model = getFlightAirplane(flight); char * field1 = strdup("plane_model");
        char* origin = getFlightOrigin(flight); char * field2 = strdup("origin");
        char* destination = getFlightDestination(flight); char * field3 = strdup("destination");
        Date* schedule_departure_date = getFlightScheduleDeparture(flight);
        Date* schedule_arrival_date = getFlightScheduleArrival(flight);
        char * dep = dateToString(schedule_departure_date); char * field4 = strdup("schedule_departure_date");
        free(schedule_departure_date);
        char * arr = dateToString(schedule_arrival_date); char * field5 = strdup("schedule_arrival_date");
        free(schedule_arrival_date);
        int number_of_passengers = getNumberPassengers(flight);
        char * nPassengersS= malloc(sizeof(char)*5);;
        sprintf(nPassengersS, "%d", number_of_passengers); char * field6 = strdup("passengers");
        int delay = (int) getDelay(flight);
        char * delayS = malloc(sizeof(char)*15);
        sprintf(delayS, "%d", delay); char * field7 = strdup("delay");

        setFieldQ(result, 0, 0, field0, airline);
        setFieldQ(result, 0, 1, field1, plane_model); 
        setFieldQ(result, 0, 2, field2, origin); 
        setFieldQ(result, 0, 3, field3, destination);
        setFieldQ(result, 0, 4, field4, dep); 
        setFieldQ(result, 0, 5, field5, arr); 
        setFieldQ(result, 0, 6, field6, nPassengersS); 
        setFieldQ(result, 0, 7, field7, delayS); 
        
        free(airline); free(plane_model); free(origin); free(destination); 
        free(dep); free(arr); free(nPassengersS); free(delayS);
        free(field0); free(field1); free(field2); free(field3); free(field4); free(field5); free(field6); free(field7);
    }
}

int compareDates_flight(void *date, void *flight, void *flightsCatalog) {
    Date * d = (Date *) date;
    Date * flightDate = getFlightScheduleDeparture((Flight *) flight);
    int day1 = getDay(d), month1 = getMonth(d), year1 = getYear(d);
    int day2 = getDay(flightDate), month2 = getMonth(flightDate), year2 = getYear(flightDate);
    int res = 0;
    if (year1 > year2) res = 1;
    else if (year2 > year1) res = -1;
    else if (month1 > month2) res = 1;
    else if (month2 > month1) res = -1;
    else if (day1 > day2) res = 1;
    else if (day2 > day1) res = -1;
    destroyDate(flightDate);
    return res;
}

int compareMonths_flight(void *date, void *flight, void *flightsCatalog) {
    Date * d = (Date *) date;
    Date * flightDate = getFlightScheduleDeparture((Flight *) flight);
    int month1 = getMonth(d), year1 = getYear(d);
    int month2 = getMonth(flightDate), year2 = getYear(flightDate);
    int res = 0;
    if (year1 > year2) res = 1;
    else if (year2 > year1) res = -1;
    else if (month1 > month2) res = 1;
    else if (month2 > month1) res = -1;
    destroyDate(flightDate);
    return res;
}

int compareYears_flight(void *date, void *flight, void *flightsCatalog) {
    Date * d = (Date *) date;
    Date * flightDate = getFlightScheduleDeparture((Flight *) flight);
    int year1 = getYear(d);
    int year2 = getYear(flightDate);
    int res = 0;
    if (year1 > year2) res = 1;
    else if (year2 > year1) res = -1;
    destroyDate(flightDate);
    return res;
}

OrdList* getFlightsDataQ10(int year, int month, int day, FlightsManager * flightsCatalog,int * flights,int * passengers,int  * unique_passengers){
    OrdList* list_passengers = createOrdList();
    (*flights) = 0; (*passengers) = 0; (*unique_passengers) = 0;
    OrdList * list = flightsCatalog->flightsByDepartureDate;
    Date * date = malloc(sizeof(Date));
    date->year = year;
    date->month = month;
    date->day = day;
    if (day!=-1){
        int i = searchDataOrdList(list, date, compareDates_flight, flightsCatalog, 0, compareDates_flight);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            Flight * flight;
            while (i < size && !exit) {
                flight = getDataOrdList(list, i);
                if (compareDates_flight(date, flight, NULL) != 0) exit = 1;
                else {
                    i++;
                    (*flights)++;
                    (*passengers)+=getNumberPassengers(flight);

                    OrdList * passengers_list = getPassengers(flight);
                    int j;
                    int size = getOrdListSize(passengers_list);
                    for (j=0; j<size; j++){
                        char *id_user = getDataOrdList(passengers_list,j);
                        addOrdList(list_passengers,strdup(id_user));
                    }
                    
                }
            }
        }
    }
    else if (month!=-1){
        int i = searchDataOrdList(list, date, compareMonths_flight, flightsCatalog, 0, compareMonths_flight);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            Flight * flight;
            while (i < size && !exit) {
                flight = getDataOrdList(list, i);
                if (compareMonths_flight(date, flight, NULL) != 0) exit = 1;
                else {
                    i++;
                    (*flights)++;
                    (*passengers)+=getNumberPassengers(flight);

                    OrdList * passengers_list = getPassengers(flight);
                    int j;
                    int size = getOrdListSize(passengers_list);
                    for (j=0; j<size; j++){
                        char *id_user = getDataOrdList(passengers_list,j);
                        addOrdList(list_passengers,strdup(id_user));
                    }
                    
                }
            }
        }
    }
    else if (year!=-1){
        int i = searchDataOrdList(list, date, compareYears_flight, flightsCatalog, 0, compareYears_flight);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            Flight * flight;
            while (i < size && !exit) {
                flight = getDataOrdList(list, i);
                if (compareYears_flight(date, flight, NULL) != 0) exit = 1;
                else {
                    i++;
                    (*flights)++;
                    (*passengers)+=getNumberPassengers(flight);

                    OrdList * passengers_list = getPassengers(flight);
                    int j;
                    int size = getOrdListSize(passengers_list);
                    for (j=0; j<size; j++){
                        char *id_user = getDataOrdList(passengers_list,j);
                        addOrdList(list_passengers,strdup(id_user));
                    }

                }
            }
        }
    }
    destroyDate(date);
    return list_passengers;
}

//gets
int getSDFlight(int time, int id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, &id);
    return getFlightSD(time, flight);
}
char *getSFlightDate(int id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, &id);
    return getStringFlightDateNoHours(flight);
}
int compareFlightYear_flightsCatalog(int year, int id, void *flightsCatalog) {
    Hashtable *flights = ((FlightsManager *) flightsCatalog)->flights;
    Flight *flight = getData(flights, &id);
    int yearFlight = getFlightSD(TIME_YEAR, flight);
    int res = 0;
    if (year > yearFlight) res++;
    else if (year < yearFlight) res--;
    return res;
}
int getNumberPassengers_flightsCatalog(int id, void *flightsCatalog) {
    Hashtable *flights = ((FlightsManager *) flightsCatalog)->flights;
    Flight *flight = getData(flights, &id);
    return getNumberPassengers(flight);
}
