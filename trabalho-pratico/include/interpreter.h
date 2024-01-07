#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "flightsManager.h"
#include "hotelsManager.h"
#include "reservationsManager.h"
#include "usersManager.h"
#include "output.h"
#include "queries.h"
#include "flight.h"
#include "hotel.h"
#include "reservation.h"
#include "user.h"
#include "utility.h"
#include "results.h"

#ifndef _INTERPRETER_
#define _INTERPRETER_ //header file para o interpretador de comandos

typedef struct command Command;

int processCommand(Command* command, int i,UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,HotelsManager *hotelsCatalog,FlightsManager *flightsCatalog, Catalogs* catalogs, QueryResult* result);
Command* parseCommandLine (char* line);
void parseCommandFile (char* name,Catalogs *catalogs, QueryResult* result);

#endif