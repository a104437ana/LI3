#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"
#include "flight.h"
#include "flightsManager.h"
#include "hotel.h"
#include "hotelsManager.h"
#include "reservation.h"
#include "reservationsManager.h"
#include "user.h"
#include "usersManager.h"
#include "utility.h"
#include "hashtable.h"
#include "orderedList.h"
#include "queries.h"
#define YEAR 2023
#define MONTH 10
#define DAY 01

int getAge(User* user){
  Date *birthdate = getBirth(user);
  bool birthday;
  if(MONTH<birthdate->month){
    birthday=false;
  }
  else if(MONTH>birthdate->month){
    birthday=true;
  }
  else{
    if(DAY<birthdate->day){
      birthday=false;
    }
    else{
      birthday=true;
    }
  }
  if(birthday==true){
    return (YEAR-birthdate->year);
  }
  else{
    return (YEAR-birthdate->year-1);
  }
}

int getNumberPassengers(Flight* flight){
    OrdList* passengers = getPassengers(flight);
    return(getOrdListSize(passengers));
}
char* getDelay(Flight* flight){
     Date* scheduleDep = getFlightScheduleDeparture(flight);
     Date* realDep = getFlightRealDeparture(flight);
     char* delay = malloc(sizeof(char)*20);
     int diffseg=0; int diffmin=0; int diffhour=0; int diffday=0;
     diffseg += (realDep->hour->seconds - scheduleDep->hour->seconds);
     if (diffseg<0){
      diffseg+=60; diffmin-=1;
     }
     diffmin += (realDep->hour->minutes - scheduleDep->hour->minutes);
     if (diffmin<0){
      diffmin+=60; diffhour-=1;
     }
     diffhour += (realDep->hour->hours - scheduleDep->hour->hours);
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

int getBeginDay(void* data){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS){
    return ((getFlightScheduleDeparture((Flight *)res->result))->day);
  }
  else{
    return (getReservBeginDay((Reservation *)res->result));
  }
}

int getBeginMonth(void* data){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS){
    return ((getFlightScheduleDeparture((Flight *)res->result))->month);
  }
  else{
    return (getReservBeginMonth((Reservation *)res->result));
  }
}

int getBeginYear(void* data){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS){
    return ((getFlightScheduleDeparture((Flight *)res->result))->year);
  }
  else{
    return (getReservBeginYear((Reservation *)res->result));
  }
}

char * getIdResultQ2(ResultQ2* data){
  if (data->resultType == FLIGHTS){
    return (getFlightId((Flight *)data->result));
  }
  else{
    return (getReservId((Reservation *)data->result));
  }
}

ResultQ1* Q1(char *id, UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,FlightsManager *flightsCatalog){
    if(id[0]=='U'){
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getUserCatalog(usersCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      if (getAccountStatus(result->result)==false) return NULL; //se o utilizador não estiver ativo
      result->resultType=USER;
      return result;
    }
    else if(id[0]=='F'){
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getFlightCatalog(flightsCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=FLIGHT;
      return result;   
    }
    else if(id[0]=='R'){
      ResultQ1* result = malloc(sizeof(ResultQ1));
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
    if (getAccountStatus(user)==false) return NULL; //se o utilizador não estiver ativo
    int i;
    ResultsQ2 *results = malloc(sizeof(ResultsQ2));
    if (type==FLIGHTS){
      OrdList* userList = getUserList(user);
      int listSize = getOrdListSize(userList);
      int nFlights = getNumberFlights(user);
      results->N = nFlights;
      int j = nFlights-1;
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
         if (data->resultType==FLIGHTS){
           results->results[j]->result = data; 
           j--;
         }
      }
    }
    else if (type==RESERVATIONS){
      OrdList* userList = getUserList(user);
      int listSize = getOrdListSize(userList);
      int nReservations = getNumberReservations(user);
      results->N = nReservations;
      int j = nReservations-1;
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
         if (data->resultType==RESERVATIONS){
           results->results[j]->result = data; 
           j--;
         }
      }
    }
    else{
      OrdList* userList = getUserList(user);
      int listSize = getOrdListSize(userList);
      results->N = listSize;
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
           results->results[listSize-i-1]->result = data;
           
      }
    }
    return results;
}

double Q3(char *id, HotelsManager *hotelsCatalog) {
  Hotel *hotel = getHotelCatalog(hotelsCatalog, hashFunction(id), id);
  double numberClassifications = getOrdListSize(getHotelOrdList(hotel));
  double result = getHotelRatingsSum(hotel);
  result /= numberClassifications;

  return result;
}

ResultsQ4* Q4(char *id, HotelsManager *hotelsCatalog){
    Hotel *hotel = getHotelCatalog(hotelsCatalog, hashFunction(id), id);
    if (hotel==NULL) return NULL; //se o id não existir
    int i;
    ResultsQ4 *results = malloc(sizeof(ResultsQ4));
    OrdList *reservations = getHotelOrdList(hotel);
    int listSize = getOrdListSize(reservations);
    results->N = listSize;
    for(i=0;i<listSize; i++){
      Reservation * data = (Reservation *)getDataOrdList(reservations, i);
      results->results[listSize-i-1] = data;     
    }
    return results;
}

double Q8(char *id, Date *begin, Date *end, HotelsManager *hotelsCatalog) {
  OrdList *reservations = getHotelOrdList(getHotelCatalog(hotelsCatalog, hashFunction(id), id));
  int index = searchReservDateIndex(reservations, begin);
  int endDay = getDay(end);
  int size = getOrdListSize(reservations);
  Reservation *reservation = getDataOrdList(reservations, index);
  int day = getReservBeginDay(reservation);
  int reservEnd;
  double total = 0, nDays, pricePerNight, cityTax;

  for (int i=index; i<size && day < endDay; i++) {
    reservation = getDataOrdList(reservations, i);
    day = getReservBeginDay(reservation);
    reservEnd = getReservEndDay(reservation);
    pricePerNight = getReservPricePerNight(reservation);
    cityTax = getReservCityTax(reservation);
    if (reservEnd <= endDay) nDays = reservEnd - day;
    else nDays = endDay - day;
    total += (pricePerNight*nDays)+(((pricePerNight*nDays)/100)*cityTax);
  }

  return total;
}

ResultsQ9* Q9(char *prefix);
