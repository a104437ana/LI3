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
int addFlightToCatalog(int *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog) {
    Flight *flight = createFlight(airline, airplane, origin, destination, scheduleDeparture, scheduleArrival, realDeparture, realArrival);
    flightsCatalog->flights = addHashtable(flightsCatalog->flights, flight, id);
    int *id_flight = malloc(sizeof(int));
    *id_flight = *id;
    addOrdList(flightsCatalog->flightsByDepartureDate, id_flight);
    return getDelay(flight);
}

//adiciona o utilizador à lista de passageiros do voo
void addUserToFlight(int *id_flight, char *id_user, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, id_flight);
    addPassengerToFlight(flight, id_user);
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

int getDepartureDayFlight(int *id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, id);
    return getDepartureDay(flight);
}

int getDepartureMonthFlight(int *id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, id);
    return getDepartureMonth(flight);
}

int getDepartureYearFlight(int *id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, id);
    return getDepartureYear(flight);
}

//função que liberta o espaço em memória alocado pelo catálogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager) {
    if (flightsManager == NULL) return; //se não exitir o catálogo
    destroyHashtable(flightsManager->flights); //liberta a hashtable
    destroyOrdList(flightsManager->flightsByDepartureDate, free);
    free(flightsManager);
}

//queries
void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, QueryResult* result) {
    int *key = flightIdToInt(id);
    Flight* flight = getData(flightsManager->flights,key);
    if (flight == NULL) {
        free(key);
        return;
    }
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
    free(key);
}

int compareDates_flight(void *date, void *id, void *flightsCatalog) {
    Date * d = (Date *) date;
    Hashtable *flights = ((FlightsManager *) flightsCatalog)->flights;
    Date * flightDate = getFlightDepartureDate(id, (void *) flights);
    int day1 = getDay(d), month1 = getMonth(d), year1 = getYear(d);
    int day2 = getDay(flightDate), month2 = getMonth(flightDate), year2 = getYear(flightDate);
    if (year1 > year2) return 1;
    else if (year2 > year1) return -1;
    else if (month1 > month2) return 1;
    else if (month2 > month1) return -1;
    else if (day1 > day2) return 1;
    else if (day2 > day1) return -1;
    else return 0;
}

int compareMonths_flight(void *date, void *id, void *flightsCatalog) {
    Date * d = (Date *) date;
    Hashtable *flights = ((FlightsManager *) flightsCatalog)->flights;
    Date * flightDate = getFlightDepartureDate(id, (void *) flights);
    int month1 = getMonth(d), year1 = getYear(d);
    int month2 = getMonth(flightDate), year2 = getYear(flightDate);
    if (year1 > year2) return 1;
    else if (year2 > year1) return -1;
    else if (month1 > month2) return 1;
    else if (month2 > month1) return -1;
    else return 0;
}

int compareYears_flight(void *date, void *id, void *flightsCatalog) {
    Date * d = (Date *) date;
    Hashtable *flights = ((FlightsManager *) flightsCatalog)->flights;
    Date * flightDate = getFlightDepartureDate(id, (void *) flights);
    int year1 = getYear(d);
    int year2 = getYear(flightDate);
    if (year1 > year2) return 1;
    else if (year2 > year1) return -1;
    else return 0;
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
        int i = searchDataOrdList(list, date, compareDates_flight, flightsCatalog, 0, compareDates_flight, 0);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            int * id;
            while (i < size && !exit) {
                id = intdupVoid (getDataOrdList(list, i));
                if (compareDates_flight(date, id, flightsCatalog) != 0) exit = 1;
                else {
                    i++;
                    (*flights)++;
                    (*passengers)+=getNumberPassengers_flightsCatalog(id, flightsCatalog);

                    Flight* flight2 = getData(flightsCatalog->flights,id);
                    OrdList * passengers_list = getPassengers(flight2);
                    int j;
                    for (j=0; j<getOrdListSize(passengers_list); j++){
                        char* id2 = getDataOrdList(passengers_list,j);
                        addOrdList(list_passengers,strdup(id2));
                    }
                    
                }
                free(id);
            }
        }
    }
    else if (month!=-1){
        int i = searchDataOrdList(list, date, compareMonths_flight, flightsCatalog, 0, compareMonths_flight, 0);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            int * id;
            while (i < size && !exit) {
                id = intdupVoid (getDataOrdList(list, i));
                if (compareMonths_flight(date, id, flightsCatalog) != 0) exit = 1;
                else {
                    i++;
                    (*flights)++;
                    (*passengers)+=getNumberPassengers_flightsCatalog(id, flightsCatalog);

                    Flight* flight2 = getData(flightsCatalog->flights,id);
                    OrdList * passengers_list = getPassengers(flight2);
                    int j;
                    for (j=0; j<getOrdListSize(passengers_list); j++){
                        char* id2 = getDataOrdList(passengers_list,j);
                        addOrdList(list_passengers,strdup(id2));
                    }
                    
                }
                free(id);
            }
        }
    }
    else if (year!=-1){
        int i = searchDataOrdList(list, date, compareYears_flight, flightsCatalog, 0, compareYears_flight, 0);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            int * id;
            while (i < size && !exit) {
                id = intdupVoid (getDataOrdList(list, i));
                if (compareYears_flight(date, id, flightsCatalog) != 0) exit = 1;
                else {
                    i++;
                    (*flights)++;
                    (*passengers)+=getNumberPassengers_flightsCatalog(id, flightsCatalog);

                    Flight* flight2 = getData(flightsCatalog->flights,id);
                    OrdList * passengers_list = getPassengers(flight2);
                    int j;
                    for (j=0; j<getOrdListSize(passengers_list); j++){
                        char* id2 = getDataOrdList(passengers_list,j);
                        addOrdList(list_passengers,strdup(id2));
                    }

                }
                free(id);
            }
        }
    }
    destroyDate(date);
    return list_passengers;
}

//gets
int getSDFlight(int time, int *id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, id);
    return getFlightSD(time, flight);
}
char *getSFlightDate(int *id, FlightsManager *flightsCatalog) {
    Flight *flight = getData(flightsCatalog->flights, id);
    return getStringFlightDateNoHours(flight);
}
int compareFlightYear_flightsCatalog(void *year, void *id, void *flightsCatalog) {
    int *y = (int *) year;
    Hashtable *flights = ((FlightsManager *) flightsCatalog)->flights;
    int yearFlight = getFlightScheduleDepartureYear(id, (void *) flights);
    int res = 0;
    if (*y > yearFlight) res++;
    else if (*y < yearFlight) res--;
    return res;
}
int getNumberPassengers_flightsCatalog(void *id, void *flightsCatalog) {
    int *id_flight = (int *) id;
    Hashtable *flights = ((FlightsManager *) flightsCatalog)->flights;
    Flight *flight = getData(flights, id_flight);
    return getNumberPassengers(flight);
}
