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

int getBeginDay(ResultQ2* data){
  if (data->type == FLIGHTS){
    return ((getFlightScheduleDeparture(data->result))->day);
  }
  else{
    return (getReservBeginDay(data->result));
  }
}

int getBeginMonth(ResultQ2* data){
  if (data->type == FLIGHTS){
    return ((getFlightScheduleDeparture(data->result))->month);
  }
  else{
    return (getReservBeginMonth(data->result));
  }
}

int getBeginYear(ResultQ2* data){
  if (data->type == FLIGHTS){
    return ((getFlightScheduleDeparture(data->result))->year);
  }
  else{
    return (getReservBeginYear(data->result));
  }
}

char * getIdResultQ2(ResultQ2* data){
  if (data->type == FLIGHTS){
    return (getFlightId(data->result));
  }
  else{
    return (getReservId(data->result));
  }
}

ResultQ1* Q1(char *id, UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,FlightsManager *flightsCatalog){
    if(id[0]=='U'){
      ResultQ1* result;
      result->result = getUserCatalog(usersCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      if (getAccountStatus(result->result)==false) return NULL; //se o utilizador não estiver ativo
      result->resultType=USER;
      return result;
    }
    else if(id[0]=='F'){
      ResultQ1* result;
      result->result = getFlightCatalog(flightsCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=FLIGHT;
      return result;   
    }
    else if(id[0]=='R'){
      ResultQ1* result;
      result->result = getReservCatalog(reservationsCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=RESERVATION;
      return result;
    }
    else return NULL; //se o id não for válido
}

ResultsQ2* Q2(char *id, Q2Type type, UsersManager *usersCatalog){
    User *user = getUserCatalog(usersCatalog, hashFunction(id), id);
    if (user==NULL) return NULL; //se o id não existir
    if (user==NULL) return NULL; //se o id não existir
    int i;
    ResultsQ2 *results;
    if (type==FLIGHTS){
      OrdList* flights = getFlightsByDate(user);
      results->N = flights->size;
       for(i=0;i<results->N; i--){
         results->results[i]->result = flights->data[(results->N)-i-1];
       }
    }
    else if (type==RESERVATIONS){
      OrdList* reservations = getReservationsByDate(user);
      results->N = reservations->size;
       for(i=0;i<results->N; i--){
         results->results[i]->result = reservations->data[(results->N)-i-1];
       }
    }
    else{
      OrdList* flights = getFlightsByDate(user);
      OrdList* reservations = getReservationsByDate(user);
      results->N = flights->size+reservations->size;
      int sizef = flights->size;
      int sizer = reservations->size; 
      OrdList* ordResults = createOrdList(results->N);
      for(i=0; i<sizef; i++){
        ResultQ2 res;
        res->type = FLIGHTS;
        res->result = flights->data[i];
        addOrdList(ordResults, res);
      }
      for(i=0; i<sizer; i++){
        ResultQ2 res;
        res->type = RESERVATIONS;
        res->result = reservations->data[i];
        addOrdList(ordResults, res);
      }
      radixSortDateResultQ2(ordResults);
      for(i=0; i<results->N; i++){
        results->results[i]->result = ordResults[(results->N)-i-1];
      }
    }
    return results;
}

double Q3(char *id, HotelsManager *hotelsCatalog) {
  Hotel *hotel = getHotelCatalog(hotelsManager, hashFunction(id), id);
  double numberClassifications = getOrdListSize(getHotelOrdList(hotel));
  double result = getHotelStarsSum(hotel);
  result /= numberClassifications;

  return result;
}

ResultsQ4* Q4(char *id);

double Q8(char *id, Date begin, Date end);

ResultsQ9* Q9(char *prefix);
