#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "usersManager.h"
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "flightsManager.h"

#define HASHTABLE_INI_SIZE 10000

int main (int argc, char** argv) {

    //inicialização de variáveis para medição de tempo
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);

    //inicialização dos catalogos
    UsersManager *usersCatalog = createUsersCatalog(HASHTABLE_INI_SIZE);
    ReservationsManager *reservationsCatalog = createReservsCatalog(HASHTABLE_INI_SIZE);
    HotelsManager *hotelsCatalog = createHotelsCatalog(HASHTABLE_INI_SIZE);
//    FlightsManager *flightsCatalog = createFlightsCatalog(HASHTABLE_INI_SIZE);

    if (argc == 3) {
    parse_all_files(argv[1],usersCatalog,reservationsCatalog,hotelsCatalog);
    }

//    printUsers(usersCatalog);
//    printReservations(reservationsCatalog);

    //print tempo de execução
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %.6f seconds\n", elapsed);

    return 0;
}
