#ifndef _QUERIES_
#define _QUERIES_

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
#include <locale.h>

typedef enum{
   USER,
   FLIGHT,
   RESERVATION
} Q1Type;

typedef struct resultQ1{
    void* result;
    Q1Type resultType;
} ResultQ1;

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

typedef struct resultsQ4{
    Reservation** results;
    int N;
} ResultsQ4;

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

typedef struct resultQ7{
    char* name;
    double median;
} ResultQ7;

typedef struct resultsQ7{
    ResultQ7** results;
    int N;
} ResultsQ7;

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
double getReservPrice(Reservation* reservation);
int getBeginDay(void* data);
int getBeginMonth(void* data);
int getBeginYear(void* data);
int getBeginSeconds(void* data);
int getBeginMinutes(void* data);
int getBeginHours(void* data);
char * getIdResultQ2(ResultQ2* data);
void destroyResultQ2(void * data);

ResultQ1* Q1(char *id, UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,FlightsManager *flightsCatalog);

ResultsQ2* Q2(char *id, Q2Type type, UsersManager *usersCatalog);

double Q3(char *id, HotelsManager *hotelsCatalog);

ResultsQ4* Q4(char *id, HotelsManager *hotelsCatalog);

ResultsQ5* Q5(char *name, Date begin, Date end);

ResultsQ6* Q6(int year, int N);

ResultsQ7* Q7(int N);

int Q8(char *id, Date *begin, Date *end, HotelsManager *hotelsCatalog);

int same_prefix (char* prefix, char* name);
int bigger_user (char* id1, char* id2, char* name1, char* name2);
void ord_list_by_name (OrdList* list, int begin, int end,UsersManager *usersCatalog);
OrdList* Q9 (char* prefix,UsersManager *usersCatalog);

void Q10(int year, char month);

#endif