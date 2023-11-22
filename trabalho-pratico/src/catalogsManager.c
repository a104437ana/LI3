#include <stdio.h>
#include "catalogsManager.h"
#include "hotelsManager.h"
#include "usersManager.h"

struct catalogsManager {
    UsersManager *usersManager;
    FlightsManager *flightsManager;
    ReservationsManager *reservationsManager;
//    HotelsManager *hotelsManager;
//    AirportsManager *airportsManager;
};
//função que ordena todos os catálogos
void sortCatalogs(UsersManager *usersManager, HotelsManager *hotelsManager) {
    sortHotelCatalog(hotelsManager); //ordena o catálogo dos hoteis
    sortUserCatalog(usersManager); //ordena o catálogo dos utilizadores
}

//função que liberta o espaço em memória alocado por todos os catálogos
void destroyCatalogs(UsersManager *usersManager, ReservationsManager *reservationsManager, HotelsManager *hotelsManager, FlightsManager *flightsManager) {
    destroyUsersCatalog(usersManager); //liberta o catálogo de utilizadores
    destroyreservationsCatalog(reservationsManager); //liberta o catálogo de reservas
    destroyHotelsCatalog(hotelsManager); //liberta o catálogo de hoteis
    destroyFlightsCatalog(flightsManager); //liberta o catálogo de voos
}
