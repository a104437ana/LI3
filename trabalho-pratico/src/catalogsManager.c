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

//funções de ordenação dos catálogos
//função que ordena todos os catálogos
void sortCatalogs(Catalogs *catalogs) {
//    sortHotelCatalog(catalogs); //ordena o catálogo dos hoteis
    sortUsersByName(catalogs->usersCatalog); //ordena o catálogo dos utilizadores
    sortUsersByAccountCreation(catalogs->usersCatalog); 
    sortFlightsByDepartureDate(catalogs->flightsCatalog);
    sortReservationsByBeginDate(catalogs->reservationsCatalog);
//    sortAirportCatalog(catalogs); //ordena o catálogo de aeroportos
}

////função que ordena o catálogo de hoteis
//void sortHotelCatalog(Catalogs *catalogs) {
//    Hashtable *hotels = getHashtableHotelsCatalog(catalogs->hotelsCatalog);
//    Hashtable *reservations = getHashtableReservCatalog(catalogs->reservationsCatalog);
//    sortOrdlistHashtable(hotels, sortHotelReservationsByDate, reservations); //ordena a lista de reservas de cada hotel na hashtable
//}
//função que ordena o catálogo de utilizadores
void sortUserCatalog(char *id, Catalogs *catalogs) {
}
//ordena reservas por data
//void radixSortReservEndDate(OrdList *list, void *lookupTable) {
//    radixSort(list, getReservationEndDay, lookupTable, 31, 0);
//    radixSort(list, getReservationEndMonth, lookupTable, 12, 0);
//    radixSort(list, getReservationEndYear, lookupTable, N_YEARS, BEGIN_YEAR);
//}

////ordena o catálogo de aeroportos
//void sortAirportCatalog(Catalogs *catalogs) {
//    Hashtable *airports = getHashtableAirportsCatalog(catalogs->airportsCatalog);
//    Hashtable *flights = getHashtableFlightsCatalog(catalogs->flightsCatalog);
//    sortOrdlistHashtable(airports, sortAirportFlightsByDepartureDate, flights);
//}
/*
//ordena voos por data
void radixSortFlightDate(OrdList *list, void *lookupTable) {
    radixSort(list, getFlightScheduleDepartureSeconds, lookupTable, 60, 0);
    radixSort(list, getFlightScheduleDepartureMinutes, lookupTable, 60, 0);
    radixSort(list, getFlightScheduleDepartureHours, lookupTable, 24, 0);
    radixSort(list, getFlightScheduleDepartureDay, lookupTable, 31, 0);
    radixSort(list, getFlightScheduleDepartureMonth, lookupTable, 12, 0);
    radixSort(list, getFlightScheduleDepartureYear, lookupTable, N_YEARS, BEGIN_YEAR);
}
*/
//ordena reservas e voos por data
void radixSortUserList(OrdList *list, void *lookupTable) {
    radixSort(list, getBeginSeconds, lookupTable, 60, 0);
    radixSort(list, getBeginMinutes, lookupTable, 60, 0);
    radixSort(list, getBeginHours, lookupTable, 24, 0);
    radixSort(list, getBeginDay, lookupTable, 31, 0);
    radixSort(list, getBeginMonth, lookupTable, 12, 0);
    radixSort(list, getBeginYear, lookupTable, N_YEARS, BEGIN_YEAR);
}

void radixSortHotelReservByDate(void *list, void *lookupTable) {
    radixSortInt((OrdList *) list, getReservationBeginDay, lookupTable, 31, 0);
    radixSortInt((OrdList *) list, getReservationBeginMonth, lookupTable, 12, 0);
    radixSortInt((OrdList *) list, getReservationBeginYear, lookupTable, N_YEARS, BEGIN_YEAR);
}

void radixSortAirportFlightByDate(void *list, void *lookupTable) {
    radixSortInt((OrdList *) list, getFlightDepartureSeconds, lookupTable, 60, 0);
    radixSortInt((OrdList *) list, getFlightDepartureMinutes, lookupTable, 60, 0);
    radixSortInt((OrdList *) list, getFlightDepartureHours, lookupTable, 24, 0);
    radixSortInt((OrdList *) list, getFlightDepartureDay, lookupTable, 31, 0);
    radixSortInt((OrdList *) list, getFlightDepartureMonth, lookupTable, 12, 0);
    radixSortInt((OrdList *) list, getFlightDepartureYear, lookupTable, N_YEARS, BEGIN_YEAR);
}

//função que compara os ids de dois voos ou reservas
int compareFlightReservsIds(void *data1, void *data2, void *lookup) {
    int res = 0;
    ResultQ2 *r1 = (ResultQ2 *) data1, *r2 = (ResultQ2 *) data2;
    Q2Type t1 = getResultType(r1), t2 = getResultType(r2);
    if (t1 == t2) {
        int id1 = getIdResultQ2(r1), id2 = getIdResultQ2(r2);
        if (id1 < id2) res++;
        else if (id2 < id1) res--;
    }
    else if (t1 == RESERVATIONS) res--;
    else if (t1 == FLIGHTS) res++;
    return res;
}

//função que ordena a lista de reservas de um hotel
void sortHotelReservationsByDate(char *id, Catalogs *catalogs) {
    sortHotelReservationsByDate_hotelsCatalog(id, catalogs->hotelsCatalog, radixSortHotelReservByDate, catalogs);
}
//void sortHotelReservationsByEndDate(char *id, Catalogs *catalogs) {
//    Hotel *hotel = getHotelCatalog(catalogs->hotelsCatalog, id);
//    OrdList *list = getHotelEndOrdList(hotel); //obtem lista de reservas
//    if(!isOrdered(list)) {
//        quickSort(list, 0, getOrdListSize(list)-1, compareReservsIds, NULL, 0); //ordena as reservas por ids
////        reverseOrdList(list); //inverte a lista
//        radixSortReservEndDate(list, catalogs); //ordena as reservas por data
//        setOrdListOrd(list, 1);
//    }
//}
//função que ordena a lista de voos e reservas de um utilizador
void sortUserList(char *id, Catalogs *catalogs) {
    User *user = getUserCatalog(catalogs->usersCatalog, id);
    OrdList *list = getUserList(user);
    if (!isOrdered(list)) {
        quickSort(list, 0, getOrdListSize(list)-1, compareFlightReservsIds, NULL, 0);
//        reverseOrdList(list);
        radixSortUserList(list, catalogs);
        setOrdListOrd(list, 1);
    }
}
void sortAirportFlightsByDepartureDate(char *id, Catalogs* catalogs) {
//    Hashtable *lookup = getHashtableFlightsCatalog(catalogs->flightsCatalog);
    sortAirportFlightsByDepartureDate_airportsCatalog(id, catalogs->airportsCatalog, radixSortAirportFlightByDate, catalogs);
}
/*
//ordena os voos do aeroporto
void sortAirportFlightsByDepartureDate(char *id, Catalogs *catalogs) {
    Airport *airport = getAirportCatalog(catalogs->airportsCatalog, key, id);
    OrdList *list = getAirportOriginOrdList(airport);
    if (!isOrdered(list)) {
        quickSort(list, 0, getOrdListSize(list)-1, compareFlightsIds, 0); //ordena por ids
        radixSortFlightDate(list, catalogs); //ordena por datas
        setOrdListOrd(list, 1);
    }
}
*/

//funções sobre diferêntes catálogos
//adiciona um utilizador ao catálogo
void addUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice, Catalogs *catalogs) {
    addUserToCatalog(id, name, gender, country, passport, birth, accountCreation, accountStatus, indice, catalogs->usersCatalog);
}
//adiciona uma reserva ao catálogo
void addReservation(int id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, int cityTax, Catalogs *catalogs) {
    int priceNoTax = addReservToCatalog(id, id_user, id_hotel, begin, end, pricePerNight, includesBreakfast, userClassification, catalogs->reservationsCatalog);
    double reservPrice = priceNoTax + (((double) priceNoTax / 100) * cityTax);
    addReservToUser(id_user, id, reservPrice, catalogs->usersCatalog);
}
//adiciona um voo ao catálogo
int addFlight(int id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, Catalogs *catalogs) {
    int delay = addFlightToCatalog(id, airline, airplane, origin, destination, scheduleDeparture, scheduleArrival, realDeparture, realArrival, catalogs->flightsCatalog);
    return delay;
}
//adiciona uma reserva ao catálogo
void addHotel(char *id, char *name, char stars, int cityTax, char userClassification, int id_reserv, Catalogs *catalogs) {
    updateHotelCatalog(id, name, stars, cityTax, userClassification, id_reserv, catalogs->hotelsCatalog);
}
//adiciona uma reserva ao catálogo
void addAirport(int delay, char *id_origin, char *id_destination, int id_flight, Catalogs *catalogs) {
    updateAirportCatalog(delay, id_origin, id_destination, id_flight, catalogs->airportsCatalog);
}
//adiciona um passageiro ao catálogo
//função que adiciona um utilizador à lista de passageiros de um certo voo no catálogo
//e adiciona esse voo à lista de voos do utilizador
void addPassenger(int flightId, char *userId, Catalogs *catalogs) {
    addUserToFlight(flightId, userId, catalogs->flightsCatalog); //adiciona o utilizador à lista de passageiros do voo
    addFlightToUser(userId, flightId, catalogs->usersCatalog); //adiciona o voo à lista de voos do utilizador
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
    int ppn;
    int nnights;
    char* hotel_id = reservation_catalog_compute_Q1(id,&ppn,&nnights,catalogs->reservationsCatalog,result);
    if (hotel_id == NULL) return;
    int cityTax = hotel_catalog_compute_Q1(hotel_id,catalogs->hotelsCatalog,result);

    //int cityTax = getHotelCityTax2(hotel_id, getHashtableHotelsCatalog(catalogs->hotelsCatalog)); //taxa turística
    
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
    Hotel* hotel = getData(getHashtableHotelsCatalog(catalogs->hotelsCatalog),id);
    if (hotel==NULL) return; //se o id não existir
    else {
       int i;
       OrdList *reservations = getHotelOrdList(hotel);
       if (isOrdered(reservations) == 0) sortHotelReservationsByDate(id, catalogs);
       int listSize = getOrdListSize(reservations);
       setNumberResults (result,listSize);
       for(i=0;i<listSize; i++){
            int key = getValueOrdList(reservations, i); char * field0 = strdup("id");
            char *id_reserv = reservIdToString(key);
            Reservation* reservation = getDataInt(getHashtableReservCatalog(catalogs->reservationsCatalog),key);
            int rating = getReservUserClassification(reservation);
            if (rating>=1){
                setNumberFieldsQ(result, listSize-i-1, 6);
                Date* begin_date = getReservBegin(reservation);
                Date* end_date = getReservEnd(reservation);
                char * begin = dateToStringNoHours(begin_date); char * field1 = strdup("begin_date");
                char * end = dateToStringNoHours(end_date); char * field2 = strdup("end_date");
                char * userId = getReservUserId(reservation); char * field3 = strdup("user_id");
                char * ratingS = malloc(sizeof(char)*11); // -O2
                sprintf(ratingS, "%d", rating); char * field4 = strdup("rating");
                int ppn = getReservPricePerNight(reservation); //preço por noite
                int nnights = getReservNights(reservation); //número de noites
                int cityTax = getReservCityTax(reservation, getHashtableHotelsCatalog(catalogs->hotelsCatalog)); //taxa turística
                double total = (ppn*nnights)+(((float)(ppn*nnights)/100)*cityTax);
                char * totalS = malloc(sizeof(char)*15);
                sprintf(totalS, "%.3f", total); char * field5 = strdup("total_price");

                setFieldQ(result, listSize-i-1, 0, field0, id_reserv);
                setFieldQ(result, listSize-i-1, 1, field1, begin); 
                setFieldQ(result, listSize-i-1, 2, field2, end); 
                setFieldQ(result, listSize-i-1, 3, field3, userId);
                setFieldQ(result, listSize-i-1, 4, field4, ratingS); 
                setFieldQ(result, listSize-i-1, 5, field5, totalS); 

                destroyDate(begin_date); destroyDate(end_date); free(begin); free(end); free(userId); free(ratingS); free(totalS); free(id_reserv);
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

                setFieldQ(result, listSize-i-1, 0, field0, id_reserv);
                setFieldQ(result, listSize-i-1, 1, field1, begin); 
                setFieldQ(result, listSize-i-1, 2, field2, end); 
                setFieldQ(result, listSize-i-1, 3, field3, userId);
                setFieldQ(result, listSize-i-1, 4, field4, totalS); 

                destroyDate(begin_date); destroyDate(end_date); free(begin); free(end); free(userId); free(totalS); free(id_reserv);
                free(field0); free(field1); free(field2); free(field3); free(field4);
            }
       }
    }
}

void catalogs_compute_Q5(char* airport,Date* begin,Date* end,Catalogs* catalogs,QueryResult* result) {
    HashtableInt *lookup = getHashtableFlightsCatalog(catalogs->flightsCatalog);
    sortAirportFlightsByDepartureDate(airport, catalogs);
    airport_catalog_compute_Q5(airport,begin,end,catalogs->airportsCatalog,result,lookup);
}

void catalogs_compute_Q7(int n, Catalogs* catalogs, QueryResult* result){
    airport_calalog_compute_Q7(n,catalogs->airportsCatalog,result);
}

Result * catalogs_compute_Q10(int year, int month, int day, Catalogs* catalogs){
    int new_users = getNewUsers(year, month, day, catalogs->usersCatalog);
    int flights; int passengers; int unique_passengers;
    OrdList* list_passengers = getFlightsDataQ10(year, month, day, catalogs->flightsCatalog, &flights, &passengers, &unique_passengers);
    unique_passengers = count_unique_passengers(catalogs->usersCatalog,list_passengers);
    destroyOrdList(list_passengers,free);
    int reservations = getReservationsQ10(year, month, day, catalogs->reservationsCatalog);
    if (new_users==0 && flights==0 && reservations==0) return NULL;
    else{
        char * date; char * field0;
        Result * result = createResult();
        setNumberFields(result,6);
        if (day!=-1){
            date = malloc(sizeof(char)*10);
            sprintf(date, "%d", day); field0 = strdup("day");
        }
        else if (month!=-1){
            date = malloc(sizeof(char)*10);
            sprintf(date, "%d", month); field0 = strdup("month");
        }
        else{
            date = malloc(sizeof(char)*10);
            sprintf(date, "%d", year); field0 = strdup("year");
        }
        char * new_usersS = malloc(sizeof(char)*10);
        sprintf(new_usersS, "%d", new_users); char * field1 = strdup("users");
        char * flightsS = malloc(sizeof(char)*10);
        sprintf(flightsS, "%d", flights); char * field2 = strdup("flights");
        char * passengersS = malloc(sizeof(char)*10);
        sprintf(passengersS, "%d", passengers); char * field3 = strdup("passengers");
        char * unique_passengersS = malloc(sizeof(char)*10);
        sprintf(unique_passengersS, "%d", unique_passengers); char * field4 = strdup("unique_passengers");
        char * reservationsS = malloc(sizeof(char)*10);
        sprintf(reservationsS, "%d", reservations); char * field5 = strdup("reservations");

        setField(result, 0, field0, date);
        setField(result, 1, field1, new_usersS); 
        setField(result, 2, field2, flightsS); 
        setField(result, 3, field3, passengersS);
        setField(result, 4, field4, unique_passengersS);
        setField(result, 5, field5, reservationsS);
        free(date); free(new_usersS); free(flightsS); free(passengersS); free(unique_passengersS); free(reservationsS);
        free(field0); free(field1); free(field2); free(field3); free(field4); free(field5);
        return(result);
    }
}

//gets
int getYearFirstResults(Catalogs * catalogs){
//    OrdList * users = getUsersByAccountCreation(catalogs->usersCatalog);
//    char * firstUserId = getDataOrdList(users, 0);
//    int firstUserYear = getUserAccountCreationYear(firstUserId, catalogs);
    int firstUserYear = getYearFirstResults_usersCatalog(catalogs->usersCatalog);

//    OrdList * flights = getFlightsByDeparture(catalogs->flightsCatalog);
//    char * firstFlightId = getDataOrdList(flights, 0);
//    int firstFlightYear = getFlightDepartureYear(firstFlightId, catalogs);
    int firstFlightYear = getFirstFlightDepartureYear_flightsCatalog(catalogs->flightsCatalog);

//    OrdList * reservations = getReservByBeginDate(catalogs->reservationsCatalog);
//    char * firstReservId = getDataOrdList(reservations, 0);
//    int firstReservYear = getReservationBeginYear(firstReservId, catalogs);
    int firstReservYear = getFirstReservationBeginYear_reservationsCatalog(catalogs->reservationsCatalog);

    if (firstUserYear<=firstFlightYear && firstUserYear<=firstReservYear) return firstUserYear;
    else if (firstFlightYear<= firstReservYear) return firstFlightYear;
    else return firstReservYear;
}
int getYearLastResults(Catalogs * catalogs){
//    OrdList * users = getUsersByAccountCreation(catalogs->usersCatalog);
//    char * lastUserId = getDataOrdList(users, getOrdListSize(users)-1);
//    int lastUserYear = getUserAccountCreationYear(lastUserId, catalogs);
    int lastUserYear = getYearLastResults_usersCatalog(catalogs->usersCatalog);

//    OrdList * flights = getFlightsByDeparture(catalogs->flightsCatalog);
//    char * lastFlightId = getDataOrdList(flights, getOrdListSize(flights)-1);
//    int lastFlightYear = getFlightDepartureYear(lastFlightId, catalogs);
    int lastFlightYear = getLastFlightDepartureYear_flightsCatalog(catalogs->flightsCatalog);

//    OrdList * reservations = getReservByBeginDate(catalogs->reservationsCatalog);
//    char * lastReservId = getDataOrdList(reservations, getOrdListSize(reservations)-1);
//    int lastReservYear = getReservationBeginYear(lastReservId, catalogs);
    int lastReservYear = getLastReservationBeginYear_reservationsCatalog(catalogs->reservationsCatalog);

    if (lastUserYear>=lastFlightYear && lastUserYear>=lastReservYear) return lastUserYear;
    else if (lastFlightYear>= lastReservYear) return lastFlightYear;
    else return lastReservYear;
}

//users
int getAccountStatus(char *id, Catalogs *catalogs) {
    return getAccountStatusUser(id, catalogs->usersCatalog);
}
int getUserListSize(int type, char *id, Catalogs *catalogs) {
    return getSizeUserList(type, id, catalogs->usersCatalog);
}
unsigned long int getUserListId(int *type, char *id_user, int index, Catalogs *catalogs) {
    return getIdUserList_usersCatalog(type, id_user, index, catalogs->usersCatalog);
}
int getUsersByNameSize_catalog(Catalogs *catalogs) {
    return getUsersByNameSize(catalogs->usersCatalog);
}
int searchPrefix_catalog(char *prefix, Catalogs *catalogs) {
    return searchPrefix(prefix, catalogs->usersCatalog);
}
int isPrefix_catalog(int *firstLetterCheck, char *prefix, int index, Catalogs *catalogs) {
    return (isPrefixUser(firstLetterCheck, prefix, index, catalogs->usersCatalog));
}
char *getIdUsersByName_catalog(int index, Catalogs *catalogs) {
    return getIdUsersByName(index, catalogs->usersCatalog);
}
char *getNameUsersByName_catalog(int index, Catalogs *catalogs) {
    return getNameUsersByName(index, catalogs->usersCatalog);
}
void getIdNameUsersByName_catalog(int index, char **id, char **name, Catalogs *catalogs) {
    getIdNameUsersByName(index, id, name, catalogs->usersCatalog);
}

//flights
int getFlightScheduleDepartureTime(int time, unsigned long int id, Catalogs *catalogs) {
    return getSDFlight(time, id, catalogs->flightsCatalog);
}
char *getStringFlightDate(unsigned long int id, Catalogs *catalogs) {
    return getSFlightDate(id, catalogs->flightsCatalog);
}
//reservations
int getReservationBegin(int time, int id, Catalogs *catalogs) {
    return getReservationBegin_reservationsCatalog(time, id, catalogs->reservationsCatalog);
}
char *getStringReservationDate(int id, Catalogs *catalogs) {
    return getSReservDate(id, catalogs->reservationsCatalog);
}
int getReservationBeginDay(unsigned long int id, void *catalogs){
    return getBeginDayReservation(id, ((Catalogs *) catalogs)->reservationsCatalog);
}
int getReservationBeginMonth(unsigned long int id, void *catalogs){
    return getBeginMonthReservation(id, ((Catalogs *) catalogs)->reservationsCatalog);
}
int getReservationBeginYear(unsigned long int id, void *catalogs){
    return getBeginYearReservation(id, ((Catalogs *) catalogs)->reservationsCatalog);
}
//int getReservationEndDay(void *id, void *catalogs){
//    return getEndDayReservation(id, ((Catalogs *) catalogs)->reservationsCatalog);
//}
//int getReservationEndMonth(void *id, void *catalogs){
//    return getEndMonthReservation(id, ((Catalogs *) catalogs)->reservationsCatalog);
//}
//int getReservationEndYear(void *id, void *catalogs){
//    return getEndYearReservation(id, ((Catalogs *) catalogs)->reservationsCatalog);
//}
int getFlightDepartureDay(unsigned long int id, void *catalogs){
    return getFlightSD_flightscatalog(TIME_DAY, id, ((Catalogs *) catalogs)->flightsCatalog);
}
int getFlightDepartureMonth(unsigned long int id, void *catalogs){
    return getFlightSD_flightscatalog(TIME_MONTH, id, ((Catalogs *) catalogs)->flightsCatalog);
}
int getFlightDepartureYear(unsigned long int id, void *catalogs){
    return getFlightSD_flightscatalog(TIME_YEAR, id, ((Catalogs *) catalogs)->flightsCatalog);
}
int getFlightDepartureSeconds(unsigned long int id, void *catalogs){
    return getFlightSD_flightscatalog(TIME_SECONDS, id, ((Catalogs *) catalogs)->flightsCatalog);
}
int getFlightDepartureMinutes(unsigned long int id, void *catalogs){
    return getFlightSD_flightscatalog(TIME_MINUTES, id, ((Catalogs *) catalogs)->flightsCatalog);
}
int getFlightDepartureHours(unsigned long int id, void *catalogs){
    return getFlightSD_flightscatalog(TIME_HOURS, id, ((Catalogs *) catalogs)->flightsCatalog);
}
int getUserAccountCreationDay(void *id, void *catalogs){
    return getCreationDayUser(id, ((Catalogs *) catalogs)->usersCatalog);
}
int getUserAccountCreationMonth(void *id, void *catalogs){
    return getCreationMonthUser(id, ((Catalogs *) catalogs)->usersCatalog);
}
int getUserAccountCreationYear(void *id, void *catalogs){
    return getCreationYearUser(id, ((Catalogs *) catalogs)->usersCatalog);
}
//int compareReservDates_catalog(void *date, void* id, void* lookup) {
//    return compareReservDates_reservationsCatalog((Date *) date, (char *) id, ((Catalogs *) lookup)->reservationsCatalog);
//}
//hotels
int getHotelReservationsSize(char *id, Catalogs *catalogs) {
    return getHotelSizeReservations(id, catalogs->hotelsCatalog);
}
int doesHotelExist(char *id, Catalogs *catalogs) {
    return hotelExists(id, catalogs->hotelsCatalog);
}
int getHotelReservPriceBetweenDates(char *id_hotel, int index, int *price, Date *begin, Date *end, Catalogs *catalogs) {
    int id_reserv = getHotelReservationId(id_hotel, index, catalogs->hotelsCatalog);
    int p = getReservPriceLimits(id_reserv, catalogs->reservationsCatalog, begin, end);
//    if (p == -2) return 0;
    if (p < 0) *price = 0;
    else *price = p;
    return 1;
}
//int searchHotelDates_catalog(Date *date, char *id, Catalogs *catalogs) {
//    return searchHotelDates_hotelsCatalog(date, id, compareReservDates_catalog, catalogs, catalogs->hotelsCatalog);
//}
//airports
int getAirportPassengersYear_catalog(int year, char *id, Catalogs *catalogs) {
    return getAirportPassengersYear_airportsCatalog(year, id, compareFlightYear_flightsCatalog, 0, (void *) catalogs->flightsCatalog, getNumberPassengers_flightsCatalog, catalogs->airportsCatalog);
}
char *getNextAirportId_catalog(int index, Catalogs *catalogs) {
    return getNextAirportId(index, catalogs->airportsCatalog);
}
int getNumberAirports_catalog(Catalogs *catalogs) {
    return getNumberAirports_airportsCatalog(catalogs->airportsCatalog);
}

void createListPassengers_UsersManager (Catalogs* catalogs, int size) {
    createListPassengers(catalogs->usersCatalog, size);
}