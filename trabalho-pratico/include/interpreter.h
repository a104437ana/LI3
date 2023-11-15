#ifndef _INTERPRETER_
#define _INTERPRETER_ //header file para o interpretador de comandos

typedef struct command Command;

void processCommand(Command* command, int i,UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,HotelsManager *hotelsCatalog,FlightsManager *flightsCatalog);
Command* parseCommandLine (char* line);
void parseCommandFile (char* name,UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,HotelsManager *hotelsCatalog,FlightsManager *flightsCatalog);

#endif