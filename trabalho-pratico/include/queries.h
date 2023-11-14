#ifndef _QUERIES_
#define _QUERIES_

#include "utility.h"

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
    ResultQ2* results[];
    int N;
} ResultsQ2;

typedef struct resultsQ4{
    Reservation* results[];
    int N;
} ResultsQ4;

typedef struct resultsQ5{
    Flight* results[];
    int N;
} ResultsQ5;

typedef struct resultQ6{
    char* name;
    int nPassengers;
} ResultQ6;

typedef struct resultsQ6{
    ResultQ6* results[];
    int N;
} ResultsQ6;

typedef struct resultQ7{
    char* name;
    double median;
} ResultQ7;

typedef struct resultsQ7{
    ResultQ7* results[];
    int N;
} ResultsQ7;

typedef struct resultQ9{
    char* id;
    char* name;
} ResultQ9;

typedef struct resultsQ9{
    ResultQ9* results[];
    int N;
} ResultsQ9;

int getNumberFlights(User* user);
int getNumberReservations(User* user);
int getNumberPassengers(Flight* flight);
char* getDelay(Flight* flight);
int getReservNights(Reservation* reservation);
double getReservPrice(Reservation* reservation);

ResultQ1* Q1(char *id);

ResultQ2* Q2(char *id, Q2Type type);

double Q3(char *id);

ResultsQ4* Q4(char *id);

ResultsQ5* Q5(char *name, Date begin, Date end);

ResultsQ6* Q6(int year, int N);

ResultsQ7* Q7(int N);

double Q8(char *id, Date begin, Date end);

ResultsQ9* Q9(char *prefix);

void Q10(int year, char month);

#endif