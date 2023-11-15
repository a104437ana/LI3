#include "queries.h"

int getNumberFlights(User* user){
    OrdList* flights = getFlightsByDate(user);
    return(flights->size);
}
int getNumberReservations(User* user){
    OrdList* reservations = getReservationsByDate(user);
    return(reservations->size);
}

int getNumberPassengers(Flight* flight){
    OrdList* passengers = getPassengers(flight);
    return(passengers->size);
}
char* getDelay(Flight* flight){ //incompleta
     Date* scheduleDep = getFlightScheduleDeparture(flight);
     Date* realDep = getFlightRealDeparture(flight);
     char* delay;
     sprintf(delay, "%d:%d:%d");
}

int getReservNights(Reservation* reservation){
     Date* begin = getReservBegin(reservation);
     Date* end = getReservEnd(reservation);
     int res = (end->day) - (begin->day);
     return res;
}

double getReservPrice(Reservation* reservation){
     int ppn = getReservPricePerNight(reservation);
     int nnights = getReservNights(reservation);
     int cityTax = getReservCityTax(reservation);
     double res = (ppn*nnights)+(((ppn*nnights)/100)*cityTax);
     return res;
}


ResultQ1* Q1(char *id){
    if(id[0]=='U'){
      ResultQ1* result;
      result->result = getUserCatalog(usersManager, hashFunction(id)); //falta verificar se o utilizador está ativo
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=USER;
      return result;
    }
    else if(id[0]=='F'){
      ResultQ1* result;
      result->result = getFlightCatalog(flightsManager, hashFunction(id));
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=FLIGHT;
      return result;   
    }
    else if(id[0]=='R'){
      ResultQ1* result;
      result->result = getReservCatalog(reservationsManager, hashFunction(id));
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=RESERVATION;
      return result;
    }
    else return NULL; //se o id não for válido
}

ResultQ2* Q2(char *id, Q2Type type);

double Q3(char *id);

ResultsQ4* Q4(char *id);

double Q8(char *id, Date begin, Date end);

ResultsQ9* Q9(char *prefix);
