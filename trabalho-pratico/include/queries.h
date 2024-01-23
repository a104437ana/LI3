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

int same_prefix (char* prefix, char* name);

void Q1(char *id, Catalogs* catalogs, QueryResult* result);

void Q2(char *id, Q2Type type, Catalogs *catalogs, QueryResult* result);

void Q3(char *id, Catalogs* catalogs, QueryResult* result);

void Q4(char *id, Catalogs* catalogs, QueryResult* result);

void Q5 (char* airport, Date *begin, Date *end, Catalogs* catalogs, QueryResult* result);

void Q6 (int year, int N, Catalogs* catalogs, QueryResult* result);

void Q7 (int n, Catalogs* catalogs, QueryResult* result);

void Q8(char *id, char *begin, char *end, Catalogs *catalogs, QueryResult* result);

void Q9(char *prefix, Catalogs* catalogs, QueryResult* result);

void Q10 (int year, int month, Catalogs* catalogs, QueryResult* qresult);

#endif