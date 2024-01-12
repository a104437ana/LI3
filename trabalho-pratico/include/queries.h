#ifndef _QUERIES_
#define _QUERIES_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "utility.h"
#include "catalogsManager.h"
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
    char* id; //flight ou reservation
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
double getReservPrice(Reservation* reservation, Hashtable *hotels);
int getBeginDay(void* data, void *catalog);
int getBeginMonth(void* data, void *catalog);
int getBeginYear(void* data, void *catalog);
int getBeginSeconds(void* data, void *catalog);
int getBeginMinutes(void* data, void *catalog);
int getBeginHours(void* data, void *catalog);
char * getIdResultQ2(ResultQ2* data);
void destroyResultQ2(void * data);

void Q1(char *id, Catalogs* catalogs, QueryResult* result);

void Q2(char *id, Q2Type type, Catalogs *catalogs, QueryResult* result);

void Q3(char *id, Catalogs* catalogs, QueryResult* result);

void Q4(char *id, Catalogs* catalogs, QueryResult* result);

void Q5 (char* airport, Date *begin, Date *end, Catalogs* catalogs, QueryResult* result);

void Q6 (int year, int N, Catalogs* catalogs, QueryResult* result);

void Q7 (int n, Catalogs* catalogs, QueryResult* result);

void Q8(char *id, char *begin, char *end, Catalogs *catalogs, QueryResult* result);

int same_prefix (char* prefix, char* name);
//int bigger_user (char* id1, char* id2, char* name1, char* name2);
//void ord_list_by_name (OrdList* list, int begin, int end,UsersManager *usersCatalog);
void Q9(char *prefix, Catalogs* catalogs, QueryResult* result);

void Q10 (int year, int month, Catalogs* catalogs, QueryResult* qresult);

#endif