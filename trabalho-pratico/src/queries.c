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
char* getDelay(Flight* flight){
     Date* scheduleDep = getFlightScheduleDeparture(flight);
     Date* realDep = getFlightRealDeparture(flight);
     char* delay;
     int diffseg=0; int diffmin=0; int diffhour=0; int diffday=0;
     diffseg += (realDep->seconds - scheduleDep->seconds);
     if (diffseg<0){
      diffseg+=60; diffmin-=1;
     }
     diffmin += (realDep->minutes - scheduleDep->minutes);
     if (diffmin<0){
      diffmin+=60; diffhour-=1;
     }
     diffhour += (realDep->hours - scheduleDep->hours);
     if (diffhour<0){
      diffhour+=24; diffday-=1;
     }
     diffday += (realDep->day - scheduleDep->day);
     sprintf(delay, "0000/00/%02d %02d:%02d:%02d", diffday, diffhour, diffmin, diffseg);
     return delay;
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
      result->result = getUserCatalog(usersManager, hashFunction(id));
      if (getAccountStatus(result->result)==false) return NULL; //se o utilizador não estiver ativo
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
