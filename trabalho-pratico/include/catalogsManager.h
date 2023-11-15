#ifndef _CATALOG_MANAGER_
#define _CATALOG_MANAGER_

#include "usersManager.h"
#include "flightsManager.h"
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "airlinesManager.h"

typedef struct catalogs Catalogs;

void criaGestorUseres();
//void adicionaUser();
//void procuraUser();
//void removeUser();
void destroiGestorUseres();

void criaGestorFlights();
void adicionaFlight();
void procuraFlight();
void removeFlight();
void destroiGestorFlights();

void criaGestorReservas();
void adicionaReserva();
void procuraReserva();
void removeReserva();
void destroiGestorReservas();

void criaGestorHoteis();
void adicionaHotel();
void procuraHotel();
void removeHotel();
void destroiGestorHoteis();

void criaGestorAeroportos();
void adicionaAeroporto();
void procuraAeroporto();
void removeAeroporto();
void destroiGestorAeroportos();

void destroyCatalogs(UsersManager *usersManager, ReservationsManager *reservationsManager, HotelsManager *hotelsManager, FlightsManager *flightsManager);

#endif