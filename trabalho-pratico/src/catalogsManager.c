#include <stdio.h>
#include "catalogsManager.h"
#include "queries.h"
#include "results.h"

struct catalogsManager {
    UsersManager *usersCatalog;
    FlightsManager *flightsCatalog;
    ReservationsManager *reservationsCatalog;
    HotelsManager *hotelsCatalog;
    AirportsManager *airportsCatalog;
};

//cria todos os catálogos
Catalogs *createCatalogs() {
    Catalogs *catalogs = malloc(sizeof(Catalogs));
    catalogs->usersCatalog = createUsersCatalog(USERS_HASHTABLE_INI_SIZE);
    catalogs->reservationsCatalog = createReservsCatalog(RESERVATIONS_HASHTABLE_INI_SIZE);
    catalogs->hotelsCatalog = createHotelsCatalog(HOTELS_HASHTABLE_INI_SIZE);
    catalogs->flightsCatalog = createFlightsCatalog(FLIGHTS_HASHTABLE_INI_SIZE);
    catalogs->airportsCatalog = createAirportsCatalog(AIRPORTS_HASHTABLE_INI_SIZE);

    return catalogs;
}

//função que ordena todos os catálogos
void sortCatalogs(Catalogs *catalogs) {
//    sortHotelCatalog(catalogs); //ordena o catálogo dos hoteis
    sortUserCatalog(catalogs); //ordena o catálogo dos utilizadores
//    sortAirportCatalog(catalogs); //ordena o catálogo de aeroportos
}
//função que ordena o catálogo de hoteis
void sortHotelCatalog(Catalogs *catalogs) {
    Hashtable *hotels = getHashtableHotelsCatalog(catalogs->hotelsCatalog);
    Hashtable *reservations = getHashtableReservCatalog(catalogs->reservationsCatalog);
    sortOrdlistHashtable(hotels, sortHotelReservationsByDate, reservations); //ordena a lista de reservas de cada hotel na hashtable
}
//função que ordena o catálogo de utilizadores
void sortUserCatalog(Catalogs *catalogs) {
//    Hashtable *flights = getHashtableFlightsCatalog(catalogs->flightsCatalog);
//    Hashtable *reservations = getHashtableReservCatalog(catalogs->reservationsCatalog);
//    Hashtable *users = getHashtableUserCatalog(catalogs->usersCatalog);
//    sortOrdlistHashtable(users, sortUserList, NULL); //ordena a lista de voos e reservas de todos os utilizadores
    OrdList *usersByName = getUsersByName(catalogs->usersCatalog);
    quickSort(usersByName, 0, getOrdListSize(usersByName)-1, compareUsersNames, 0); //ordena os utilizadores por nome na lista de utilizadores
}
//ordena o catálogo de aeroportos
void sortAirportCatalog(Catalogs *catalogs) {
    Hashtable *airports = getHashtableAirportsCatalog(catalogs->airportsCatalog);
    Hashtable *flights = getHashtableFlightsCatalog(catalogs->flightsCatalog);
    sortOrdlistHashtable(airports, sortAirportFlightsByDepartureDate, flights);
}
//ordena reservas por data
void radixSortReservDate(OrdList *list, Hashtable *lookupTable) {
    radixSort(list, getReservBeginDayId, lookupTable, 31, 0);
    radixSort(list, getReservBeginMonthId, lookupTable, 12, 0);
    radixSort(list, getReservBeginYearId, lookupTable, N_YEARS, BEGIN_YEAR);
}
//ordena voos por data
void radixSortFlightDate(OrdList *list, Hashtable *lookupTable) {
    radixSort(list, getFlightScheduleDepartureSeconds, lookupTable, 60, 0);
    radixSort(list, getFlightScheduleDepartureMinutes, lookupTable, 60, 0);
    radixSort(list, getFlightScheduleDepartureHours, lookupTable, 24, 0);
    radixSort(list, getFlightScheduleDepartureDay, lookupTable, 31, 0);
    radixSort(list, getFlightScheduleDepartureMonth, lookupTable, 12, 0);
    radixSort(list, getFlightScheduleDepartureYear, lookupTable, N_YEARS, BEGIN_YEAR);
}
//ordena reservas e voos por data
void radixSortUserList(OrdList *list, Hashtable *lookupTable) {
    radixSort(list, getBeginSeconds, lookupTable, 60, 0);
    radixSort(list, getBeginMinutes, lookupTable, 60, 0);
    radixSort(list, getBeginHours, lookupTable, 24, 0);
    radixSort(list, getBeginDay, lookupTable, 31, 0);
    radixSort(list, getBeginMonth, lookupTable, 12, 0);
    radixSort(list, getBeginYear, lookupTable, N_YEARS, BEGIN_YEAR);
}

//funções sobre diferêntes catálogos
//adiciona um utilizador ao catálogo
void addUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, Catalogs *catalogs) {
    addUserToCatalog(id, name, gender, country, passport, birth, accountCreation, accountStatus, catalogs->usersCatalog);
}
//adiciona uma reserva ao catálogo
void addReservation(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, Catalogs *catalogs) {
    addReservToCatalog(id, id_user, id_hotel, begin, end, pricePerNight, includesBreakfast, userClassification, catalogs->reservationsCatalog, catalogs->usersCatalog, getHashtableHotelsCatalog(catalogs->hotelsCatalog));
}
//adiciona um voo ao catálogo
int addFlight(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, Catalogs *catalogs) {
    int delay = addFlightToCatalog(id, airline, airplane, origin, destination, scheduleDeparture, scheduleArrival, realDeparture, realArrival, catalogs->flightsCatalog);
    return delay;
}
//adiciona uma reserva ao catálogo
void addHotel(char *id, char *name, char stars, int cityTax, char userClassification, char *id_reserv, Catalogs *catalogs) {
    updateHotelCatalog(id, name, stars, cityTax, userClassification, id_reserv, catalogs->hotelsCatalog);
}
//adiciona uma reserva ao catálogo
void addAirport(int delay, char *id, char *id_flight, Catalogs *catalogs) {
    updateAirportCatalog(delay, id, id_flight, catalogs->airportsCatalog);
}
//adiciona um passageiro ao catálogo
void addPassenger(char *flightId, char *userId, Catalogs *catalogs) {
    unsigned int flightKey = hashFunction(flightId);
    unsigned int userKey = hashFunction(userId);
    addPassengerToCatalog(catalogs->flightsCatalog, flightKey, catalogs->usersCatalog, userKey, flightId, userId);
}
//verifica se um utilizador existe no catálogo
int userExists(char *id, Catalogs *catalogs) {
    return existsUser(catalogs->usersCatalog, id);
}
//verifica se um voo existe no catálogo
int flightExists(char *id, Catalogs *catalogs) {
    return existsFlight(catalogs->flightsCatalog, id);
}
//funções alternativas enquanto encapsulamento não está completo
//obtem catálogo de utilizadores
UsersManager *getUsersCatalog(Catalogs *catalogs) {
    return catalogs->usersCatalog;
}
//obtem catálogo de voos
FlightsManager *getFlightsCatalog(Catalogs *catalogs) {
    return catalogs->flightsCatalog;
}
//obtem catálogo de reservas
ReservationsManager *getReservationsCatalog(Catalogs *catalogs) {
    return catalogs->reservationsCatalog;
}
//obtem catálogo de hoteis
HotelsManager *getHotelsCatalog(Catalogs *catalogs) {
    return catalogs->hotelsCatalog;
}
//obtem catálogo de aeroportos
AirportsManager *getAirportsCatalog(Catalogs *catalogs) {
    return catalogs->airportsCatalog;
}

//função que liberta o espaço em memória alocado por todos os catálogos
void destroyCatalogs(Catalogs *catalogs) {
    destroyUsersCatalog(catalogs->usersCatalog); //liberta o catálogo de utilizadores
    destroyreservationsCatalog(catalogs->reservationsCatalog); //liberta o catálogo de reservas
    destroyHotelsCatalog(catalogs->hotelsCatalog); //liberta o catálogo de hoteis
    destroyFlightsCatalog(catalogs->flightsCatalog); //liberta o catálogo de voos
    destroyAirportsCatalog(catalogs->airportsCatalog); //liberta o catálogo de aeroportos
    free(catalogs);
}

//queries
void catalogs_compute_Q1_user (char *id, Catalogs* catalogs, QueryResult* result) {
    user_catalog_compute_Q1(id,catalogs->usersCatalog,result);
}

void catalogs_compute_Q1_flight (char *id, Catalogs* catalogs, QueryResult* result) {
    flight_catalog_compute_Q1(id,catalogs->flightsCatalog,result);
}

void catalogs_compute_Q1_reservation (char *id, Catalogs* catalogs, QueryResult* result) {
    char* hotel_id = reservation_catalog_compute_Q1(id,catalogs->reservationsCatalog,result);
    if (hotel_id == NULL) return;
    hotel_catalog_compute_Q1(hotel_id,catalogs->hotelsCatalog,result);
    Reservation* reservation = getData(getHashtableReservCatalog(catalogs->reservationsCatalog),hashFunction(id),id);
    int ppn = getReservPricePerNight(reservation); //preço por noite
    int nnights = getReservNights(reservation); //número de noites
    int cityTax = getHotelCityTax2(hotel_id, getHashtableHotelsCatalog(catalogs->hotelsCatalog)); //taxa turística
    double total = (ppn*nnights)+(((float)(ppn*nnights)/100)*cityTax);
    char * totalS = malloc(sizeof(char)*15);
    sprintf(totalS, "%.3f", total); char * field7 = strdup("total_price");
    setFieldQ(result, 0, 7, field7, totalS); 

    free(hotel_id); free(totalS);
    free(field7);
}


void catalogs_compute_Q3(char* id_hotel, Catalogs* catalogs, QueryResult* result) {
    hotel_catalog_compute_Q3(id_hotel,catalogs->hotelsCatalog,result);
}

void catalogs_compute_Q4(char* id, Catalogs* catalogs, QueryResult* result){
    Hotel* hotel = getData(getHashtableHotelsCatalog(catalogs->hotelsCatalog),hashFunction(id),id);
    if (hotel==NULL) return; //se o id não existir
    else {
       int i;
       OrdList *reservations = getHotelOrdList(hotel);
       if (getOrdListOrd(reservations) == 0) sortHotelReservationsByDate(hotel, getHashtableReservCatalog(catalogs->reservationsCatalog));
       int listSize = getOrdListSize(reservations);
       setNumberResults (result,listSize);
       for(i=0;i<listSize; i++){
            char *id = getDataOrdList(reservations, i); char * field0 = strdup("id");
            Reservation* reservation = getData(getHashtableReservCatalog(catalogs->reservationsCatalog),hashFunction(id),id);
            int rating = getReservUserClassification(reservation);
            if (rating>=1){
                setNumberFieldsQ(result, listSize-i-1, 6);
                Date* begin_date = getReservBegin(reservation);
                Date* end_date = getReservEnd(reservation);
                char * begin = dateToStringNoHours(begin_date); char * field1 = strdup("begin_date");
                char * end = dateToStringNoHours(end_date); char * field2 = strdup("end_date");
                char * userId = getReservUserId(reservation); char * field3 = strdup("user_id");
                char * ratingS = malloc(sizeof(char)*3);
                sprintf(ratingS, "%d", rating); char * field4 = strdup("rating");
                int ppn = getReservPricePerNight(reservation); //preço por noite
                int nnights = getReservNights(reservation); //número de noites
                int cityTax = getReservCityTax(reservation, getHashtableHotelsCatalog(catalogs->hotelsCatalog)); //taxa turística
                double total = (ppn*nnights)+(((float)(ppn*nnights)/100)*cityTax);
                char * totalS = malloc(sizeof(char)*15);
                sprintf(totalS, "%.3f", total); char * field5 = strdup("total_price");

                setFieldQ(result, listSize-i-1, 0, field0, id);
                setFieldQ(result, listSize-i-1, 1, field1, begin); 
                setFieldQ(result, listSize-i-1, 2, field2, end); 
                setFieldQ(result, listSize-i-1, 3, field3, userId);
                setFieldQ(result, listSize-i-1, 4, field4, ratingS); 
                setFieldQ(result, listSize-i-1, 5, field5, totalS); 

                destroyDate(begin_date); destroyDate(end_date); free(begin); free(end); free(userId); free(ratingS); free(totalS);
                free(field0); free(field1); free(field2); free(field3); free(field4); free(field5);
            }
            else{
                setNumberFieldsQ(result, listSize-i-1, 5);
                Date* begin_date = getReservBegin(reservation);
                Date* end_date = getReservEnd(reservation);
                char * begin = dateToStringNoHours(begin_date); char * field1 = strdup("begin_date");
                char * end = dateToStringNoHours(end_date); char * field2 = strdup("end_date");
                char * userId = getReservUserId(reservation); char * field3 = strdup("user_id");
                int ppn = getReservPricePerNight(reservation); //preço por noite
                int nnights = getReservNights(reservation); //número de noites
                int cityTax = getReservCityTax(reservation, getHashtableHotelsCatalog(catalogs->hotelsCatalog)); //taxa turística
                double total = (ppn*nnights)+(((float)(ppn*nnights)/100)*cityTax);
                char * totalS = malloc(sizeof(char)*15);
                sprintf(totalS, "%.3f", total); char * field4 = strdup("total_price");

                setFieldQ(result, listSize-i-1, 0, field0, id);
                setFieldQ(result, listSize-i-1, 1, field1, begin); 
                setFieldQ(result, listSize-i-1, 2, field2, end); 
                setFieldQ(result, listSize-i-1, 3, field3, userId);
                setFieldQ(result, listSize-i-1, 4, field4, totalS); 

                destroyDate(begin_date); destroyDate(end_date); free(begin); free(end); free(userId); free(totalS);
                free(field0); free(field1); free(field2); free(field3); free(field4);
            }
       }
    }
}

void catalogs_compute_Q7(int n, Catalogs* catalogs, QueryResult* result){
    airport_calalog_compute_Q7(n,catalogs->airportsCatalog,result);
}