#include <stdio.h>
#include "catalogsManager.h"
#include "queries.h"

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
void addFlight(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, Catalogs *catalogs) {
    addFlightToCatalog(id, airline, airplane, origin, destination, scheduleDeparture, scheduleArrival, realDeparture, realArrival, catalogs->flightsCatalog);
}
//adiciona uma reserva ao catálogo
void addHotel(char *id, char *name, char stars, int cityTax, char userClassification, char *id_reserv, Catalogs *catalogs) {
    updateHotelCatalog(id, name, stars, cityTax, userClassification, id_reserv, catalogs->hotelsCatalog);
}
//adiciona uma reserva ao catálogo
void addAirport(char *id, char *id_flight, Catalogs *catalogs) {
    updateAirportCatalog(id, id_flight, catalogs->airportsCatalog);
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
}
