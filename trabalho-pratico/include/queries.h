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

//retornos (estrutura ?)
ResultQ1* Q1(char *id);

ResultQ2* Q2(char *id, Q2Type type);

float Q3(char *id);

void Q4(char *id);

void Q5(char *name, Date begin, Date end);

void Q6(int year, int N);

void Q7(int N);

void Q8(char *id, Date begin, Date end);

void Q9(char *prefix);

void Q10(int year, char month);

#endif