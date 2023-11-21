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
#include "parser.h"
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
int getDelay(Flight* flight){
     Date* scheduleDep = getFlightScheduleDeparture(flight);
     Date* realDep = getFlightRealDeparture(flight);
     int res = ((realDep->hour->hours)-(scheduleDep->hour->hours))*3600 + ((realDep->hour->minutes)-(scheduleDep->hour->minutes))*60 +((realDep->hour->seconds)-(scheduleDep->hour->seconds));
     return res;
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
     double res = (ppn*nnights)+(((float)(ppn*nnights)/100)*cityTax);
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

int getBeginSeconds(void* data) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS){
    return ((getFlightScheduleDeparture((Flight *)res->result))->hour->seconds);
  }
  else{
    return (0);
  }
}

int getBeginMinutes(void* data) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS){
    return ((getFlightScheduleDeparture((Flight *)res->result))->hour->minutes);
  }
  else{
    return (0);
  }
}

int getBeginHours(void* data) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS){
    return ((getFlightScheduleDeparture((Flight *)res->result))->hour->hours);
  }
  else{
    return (0);
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

void destroyResultQ2(void * data){
  free((ResultQ2*)data);
}

ResultQ1* Q1(char *id, UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,FlightsManager *flightsCatalog){
    if(same_prefix("Book", id) == 1){
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getReservCatalog(reservationsCatalog, hashFunction(id), id);
      if (result->result==NULL){
        free(result);
        return NULL; //se o id não existir
      }
      result->resultType=RESERVATION;
      return result;
    }
    else if (id[0]>='0' && id[0]<='9'){
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getFlightCatalog(flightsCatalog, hashFunction(id), id);
      if (result->result==NULL){
        free(result);
        return NULL; //se o id não existir
      }
      result->resultType=FLIGHT;
      return result;   
    }
    else{
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getUserCatalog(usersCatalog, hashFunction(id), id);
      if (result->result==NULL){
        free(result);
        return NULL; //se o id não existir
      }
      if (getAccountStatus(result->result)==false){
        free(result);
        return NULL; //se o utilizador não estiver ativo
      }
      result->resultType=USER;
      return result;
    }
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
      results->results = malloc(sizeof(ResultQ2)*nFlights);
      int j = nFlights-1;
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
         if (data->resultType==FLIGHTS){
           results->results[j] = data; 
           j--;
         }
      }
    }
    else if (type==RESERVATIONS){
      OrdList* userList = getUserList(user);
      int listSize = getOrdListSize(userList);
      int nReservations = getNumberReservations(user);
      results->N = nReservations;
      results->results = malloc(sizeof(ResultQ2)*nReservations);
      int j = nReservations-1;
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
         if (data->resultType==RESERVATIONS){
           results->results[j] = data; 
           j--;
         }
      }
    }
    else{
      OrdList* userList = getUserList(user);
      int listSize = getOrdListSize(userList);
      results->N = listSize;
      results->results = malloc(sizeof(ResultQ2)*listSize);
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
        results->results[listSize-i-1] = data;
      }
    }
    return results;
}

double Q3(char *id, HotelsManager *hotelsCatalog) {
  Hotel *hotel = getHotelCatalog(hotelsCatalog, hashFunction(id), id);
  if (hotel==NULL) return -1;
  int numberClassifications = getOrdListSize(getHotelOrdList(hotel));
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
    results->results = malloc(sizeof(Reservation*)*listSize);
    for(i=0;i<listSize; i++){
      Reservation * data = (Reservation *)getDataOrdList(reservations, i);
      results->results[listSize-i-1] = data;     
    }
    return results;
}

void printDay(void *reservation) {
  printf(", %d", getReservBeginDay((Reservation *) reservation));
}

int daysInsideDates(Date *begin, Date *end, Date *reservBegin, Date *reservEnd) {
  int nDays = 0;
  int reservBegin_begin, reservEnd_end, reservBegin_end, reservEnd_begin;
  Date *lower, *higher;
  reservEnd_begin = compareDates(reservEnd, begin);
  if (reservEnd_begin > 0) return -1;
  reservBegin_begin = compareDates(reservBegin, begin);
  reservEnd_end = compareDates(reservEnd, end);
  reservBegin_end  = compareDates(reservBegin, end);
  if (reservBegin_end < 0) return -1;

  if (reservBegin_begin >= 0) lower = begin;
  else lower = reservBegin;
  if (reservEnd_end <= 0) higher = end;
  else higher = reservEnd;

  nDays = daysBetweenDates(lower, higher) + 1;
  if (reservBegin_begin <= 0 && reservEnd_end >= 0)
    nDays --;

  return nDays;
}

int getReservPriceBetweenDates(Reservation *reservation, Date *begin, Date *end, Date *reservBegin, Date *reservEnd) {
  int pricePerNight = getReservPricePerNight(reservation);
  int nDays = daysInsideDates(begin, end, reservBegin, reservEnd);
  if (nDays == -1) return 0;
  int total = (pricePerNight * nDays);
  return total;
}

int Q8(char *id, Date *begin, Date *end, HotelsManager *hotelsCatalog) {
  Hotel *hotel = getHotelCatalog(hotelsCatalog, hashFunction(id), id);
  if (hotel==NULL) return -1;
  OrdList *reservations = getHotelOrdList(hotel);
  int size = getOrdListSize(reservations);
  Reservation *reservation = getDataOrdList(reservations, 0);
  Date *reservBegin = getReservBegin(reservation), *reservEnd = getReservEnd(reservation);
  int total = 0;

  for (int i=0; i<size && compareDates(reservBegin, end) >= 0; i++) { //enquanto dia limite maior ou igual a dia atual
    total += getReservPriceBetweenDates(reservation, begin, end, reservBegin, reservEnd);
    reservation = getDataOrdList(reservations, i+1); //proxima reserva
    reservBegin = getReservBegin(reservation); //dia inicio da reserva
    reservEnd = getReservEnd(reservation); //dia fim da reserva
  }

  return total;
}

int same_prefix (char* prefix, char* name) { 
  int same_prefix = 0;
  if (strlen(name) >= strlen(prefix)) {
    int i = 0;
    while (prefix[i] != '\0') {
      if (prefix[i] != name[i]) break;
      i++;
    }
    if (prefix[i] == '\0') same_prefix = 1;
  }
  return same_prefix;
}
/*
int bigger_user (char* id1, char* name1, char* id2, char* name2) {
  int bigger_user = 2;
  int result = strcoll(name1,name2);
  if (result == 0) {
    result = strcoll(id1,id2);
  }
  if (result > 0) bigger_user = 1;
  return bigger_user;
}

void ord_list_by_name (OrdList* list, int begin, int end, UsersManager *usersCatalog) {
  if (begin < end) {
    void* pivo2 = getDataOrdList(list,end);
    UserId* pivoId = (UserId*) pivo2;
    char* id1 = getId_UserId(pivoId);
    User* pivo = getUserCatalog(usersCatalog,hashFunction(id1),id1);
    char* name1 = getName(pivo);
    int i = begin-1;
    int j = begin;
    while (j < end) {
      UserId* userId = getDataOrdList(list,j);
      char* id2 = getId_UserId(userId);
      User* user = getUserCatalog(usersCatalog,hashFunction(id2),id2);
      char* name2 = getName(user);
      if (bigger_user(id1,id2,name1,name2) == 1) {
        j++;
      }
      else {
        i++;
        swap(list,i,j);
      }
    }
    if (j == end) {
      i++;
      swap(list,i,j);
    }
    ord_list_by_name(list,begin,i-1,usersCatalog);
    ord_list_by_name(list,i+1,end,usersCatalog);
  }
}

int compareStrings(void *string1, void *string2) {
  return strcmp((char *) string1, (char *) string2);
}

//OrdList* Q9 (char* prefix,UsersManager *usersCatalog) {
//  OrdList* name_with_prefix = createOrdList(10000);
//  OrdList* usersId = getOrdListUser(usersCatalog);
//  int size_listId = getOrdListSize(usersId);
//  int i = 0;
//  while (i<size_listId) {
//    UserId* userId = getDataOrdList(usersId,i);
//    char* id = getId_UserId(userId);
//    User* user = getUserCatalog(usersCatalog,hashFunction(id),id);
//    char* name = getName(user);
//    int addToList = same_prefix(prefix,name);
//    free(id);
//    if (addToList) {
//      addOrdList(name_with_prefix,userId);
//    }
//    i++;
//  }
//  ord_list_by_name(name_with_prefix,0,getOrdListSize(name_with_prefix)-1,usersCatalog);
//  return name_with_prefix;
//}
*/
int isPrefix(void *prefix, void *user) {
  int compare, prefixSize = strlen((char *) prefix);
  char *namePrefix = malloc(sizeof(char) * (prefixSize + 1));
  char *name = getName((User *) user);
  namePrefix = strncpy(namePrefix, (char *) name, prefixSize);
  namePrefix[prefixSize] = '\0';
  compare = strcoll((char *) prefix, (char *) namePrefix);
  free(namePrefix);

  return compare;
}

OrdList *Q9(char *prefix, UsersManager *usersCatalog) {
  OrdList *result = createOrdList(100);
  OrdList *usersByName = getUsersByName(usersCatalog);
  int size = getOrdListSize(usersByName);
  int i = searchDataOrdList(usersByName, prefix, isPrefix, 0, 1);
  if (i == -1) return result;
  User *user = getDataOrdList(usersByName, i);
  while (i < size && isPrefix(prefix, user) == 0) {
    addOrdList(result, user);
    i++;
    user = getDataOrdList(usersByName, i);
  }

  return result;
}