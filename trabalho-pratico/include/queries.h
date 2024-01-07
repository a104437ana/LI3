#ifndef _QUERIES_
#define _QUERIES_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
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
#include "parser.h"
#include "results.h"

#define YEAR 2023
#define MONTH 10
#define DAY 01



typedef enum{
   FLIGHTS,
   RESERVATIONS,
   BOTH
} Q2Type;

typedef struct resultQ2{
    void* result; //flight ou reservation
    Q2Type resultType;
} ResultQ2;

typedef struct resultsQ2{
    ResultQ2** results;
    int N;
} ResultsQ2;


typedef struct resultsQ5{
    Flight** results;
    int N;
} ResultsQ5;

typedef struct resultQ6{
    char* name;
    int nPassengers;
} ResultQ6;

typedef struct resultsQ6{
    ResultQ6** results;
    int N;
} ResultsQ6;

typedef struct resultQ9{
    char* id;
    char* name;
} ResultQ9;

typedef struct resultsQ9{
    ResultQ9** results;
    int N;
} ResultsQ9;

int getAge(User* user);
int getNumberPassengers(Flight* flight);
int getDelay(Flight* flight);
int getReservNights(Reservation* reservation);
double getReservPrice(Reservation* reservation, Hashtable *hotels);
int getBeginDay(void* data, Hashtable *lookupTable);
int getBeginMonth(void* data, Hashtable *lookupTable);
int getBeginYear(void* data, Hashtable *lookupTable);
int getBeginSeconds(void* data, Hashtable *lookupTable);
int getBeginMinutes(void* data, Hashtable *lookupTable);
int getBeginHours(void* data, Hashtable *lookupTable);
char * getIdResultQ2(ResultQ2* data);
void destroyResultQ2(void * data);

void Q1(char *id, Catalogs* catalogs, QueryResult* result);

ResultsQ2* Q2(char *id, Q2Type type, UsersManager *usersCatalog);

void Q3(char *id, Catalogs* catalogs, QueryResult* result);

void Q4(char *id, Catalogs* catalogs, QueryResult* result);

void Q5 (char* airport, Date *begin, Date *end, Catalogs* catalogs, QueryResult* result);

ResultsQ6* Q6(int year, int N);

void Q7 (int n, Catalogs* catalogs, QueryResult* result);

int Q8(char *id, Date *begin, Date *end, HotelsManager *hotelsCatalog, ReservationsManager *reservationsCatalog);

int same_prefix (char* prefix, char* name);
//int bigger_user (char* id1, char* id2, char* name1, char* name2);
//void ord_list_by_name (OrdList* list, int begin, int end,UsersManager *usersCatalog);
OrdList* Q9 (char* prefix,UsersManager *usersCatalog);

void Q10(int year, char month);

#endif