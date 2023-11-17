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

char * getIdResultQ2(ResultQ2* data){
  if (data->resultType == FLIGHTS){
    return (getFlightId((Flight *)data->result));
  }
  else{
    return (getReservId((Reservation *)data->result));
  }
}

ResultQ1* Q1(char *id, UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,FlightsManager *flightsCatalog){
    if(same_prefix("Book", id) == 1){
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getReservCatalog(reservationsCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=RESERVATION;
      return result;
    }
    else if (id[0]>='0' && id[0]<='9'){
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getFlightCatalog(flightsCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      result->resultType=FLIGHT;
      return result;   
    }
    else{
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getUserCatalog(usersCatalog, hashFunction(id), id);
      if (result->result==NULL) return NULL; //se o id não existir
      if (getAccountStatus(result->result)==false) return NULL; //se o utilizador não estiver ativo
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

int getReservPriceBetweenDates(Reservation *reservation, Date *begin, Date *end) {
  int pricePerNight = getReservPricePerNight(reservation);
//  double cityTax = getReservCityTax(reservation);
  int nDays = daysBetweenDates(begin, end);
  int total = (pricePerNight * nDays);
  return total;
}

int Q8(char *id, Date *begin, Date *end, HotelsManager *hotelsCatalog) {
  OrdList *reservations = getHotelOrdList(getHotelCatalog(hotelsCatalog, hashFunction(id), id));
  int index = searchReservDateIndex(reservations, begin); //procura indice da reserva inicial
  int size = getOrdListSize(reservations);
  Reservation *reservation = getDataOrdList(reservations, index);
  Date *reservBegin = getReservBegin(reservation), *reservEnd = getReservEnd(reservation);
  double total = 0;

  for (int i=index; i<size && compareDates(reservBegin, end) >= 0; i++) { //enquanto dia limite maior ou igual a dia atual
    if (compareDates(reservEnd, end) < 0) //se dia limite menor que dia de fim da reserva
      total += getReservPriceBetweenDates(reservation, reservBegin, end);
    else
      total += getReservPriceBetweenDates(reservation, reservBegin, reservEnd);
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

void swap (UserByName* user1, UserByName* user2) {
  char* name1 = getName_UserByName(user1);
  char* name2 = getName_UserByName(user2);
  char* id1 = getId_UserByName(user1);
  char* id2 = getId_UserByName(user2);
  setName_UserByName(user1,name2);
  setName_UserByName(user2,name1);
  setId_UserByName(user1,id2);
  setId_UserByName(user2,id1);
  free(name1);
  free(name2);
  free(id1);
  free(id2);
}

int bigger_user (UserByName* user1, UserByName* user2) {
  int bigger_user = 2;
  char* name1 = getName_UserByName(user1);
  char* name2 = getName_UserByName(user2);
  int result = strcoll(name1,name2);
  free(name1);
  free(name2);
  if (result == 0) {
    char* id1 = getId_UserByName(user1);
    char* id2 = getId_UserByName(user2);
    result = strcoll(id1,id2);
    free(id1);
    free(id2);
  }
  if (result > 0) bigger_user = 1;
  return bigger_user;
}

void ord_list_by_name (OrdList* list, int begin, int end) {
  if (begin != end) {
    UserByName* pivo = getDataOrdList(list,end);
    int i = begin-1;
    int j = begin;
    while (j < end) {
      UserByName* user_j = getDataOrdList(list,j);
      if (bigger_user(user_j,pivo) == 1) {
        j++;
      }
      else {
        i++;
        UserByName* user_i = getDataOrdList(list,i);
        swap(user_i,user_j);
      }
    }
    if (j == end) {
      i++;
      UserByName* user_j = getDataOrdList(list,j);
      UserByName* user_i = getDataOrdList(list,i);
      swap(user_i,user_j);
    }
    ord_list_by_name(list,0,i-1);
    ord_list_by_name(list,i+1,end);
  }
}

OrdList* Q9 (char* prefix,UsersManager *usersCatalog) {
  OrdList* name_with_prefix = createOrdList(10000);
  OrdList* usersByName = getOrdListUser(usersCatalog);
  int size = getOrdListSize(usersByName);
  int i = 0;
  while (i<size) {
    UserByName* userByName = getDataOrdList(usersByName,i);
    char* name = getName_UserByName(userByName);
    int addToList = same_prefix(prefix,name);
    free(name);
    if (addToList) {
      addOrdList(name_with_prefix,userByName);
    }
    i++;
  }
  ord_list_by_name(name_with_prefix,0,size-1);
  return name_with_prefix;
}
