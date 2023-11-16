#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "usersManager.h"
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "flightsManager.h"
#include "catalogsManager.h"
#include "interpreter.h"

#define USERS_HASHTABLE_INI_SIZE 10000
#define RESERVATIONS_HASHTABLE_INI_SIZE 40000
#define HOTELS_HASHTABLE_INI_SIZE 100
#define FLIGHTS_HASHTABLE_INI_SIZE 1000

void printDate(void *data) {
    printf(", %d/%d/%d", getDay(getReservBegin((Reservation *) data)), getMonth(getReservBegin((Reservation *) data)), getYear(getReservBegin((Reservation *) data)));
}

int main (int argc, char** argv) {

    //inicialização de variáveis para medição de tempo
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);

    //inicialização dos catalogos
    UsersManager *usersCatalog = createUsersCatalog(USERS_HASHTABLE_INI_SIZE);
    ReservationsManager *reservationsCatalog = createReservsCatalog(RESERVATIONS_HASHTABLE_INI_SIZE);
    HotelsManager *hotelsCatalog = createHotelsCatalog(HOTELS_HASHTABLE_INI_SIZE);
    FlightsManager *flightsCatalog = createFlightsCatalog(FLIGHTS_HASHTABLE_INI_SIZE);

    if (argc == 3) {
    parse_all_files(argv[1],usersCatalog,reservationsCatalog,hotelsCatalog,flightsCatalog);
    parseCommandFile(argv[2],usersCatalog,reservationsCatalog,hotelsCatalog,flightsCatalog);
    }

//    printUsers(usersCatalog);
//    printReservations(reservationsCatalog);
//    printHotels(hotelsCatalog);
//    printFlights(flightsCatalog);

    sortCatalogs(usersCatalog, hotelsCatalog);

//    printHotelTableReservs(getHashtableHotelsCatalog(hotelsCatalog), printDate);

//    char *id = strdup("Book0000000247");
//    Date *date = getReservBegin((Reservation *) getData(getHashtableReservCatalog(reservationsCatalog), hashFunction(id), id));
//
//    printf("%s: %d/%d/%d\n", id, getDay(date), getMonth(date), getYear(date));

    destroyCatalogs(usersCatalog, reservationsCatalog, hotelsCatalog, flightsCatalog);

    //print tempo de execução
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %.6f seconds\n", elapsed);

    return 0;
}
