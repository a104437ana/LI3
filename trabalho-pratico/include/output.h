#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orderedList.h"
#include "queries.h"
#include "flight.h"
#include "hotel.h"
#include "reservation.h"
#include "user.h"
#include "utility.h"
#include "results.h"


#ifndef _OUTPUT_
#define _OUTPUT_ //header file para o output dos resultados

void createOutputFile (int nCommand);
void printOutputQ1 (char format_flag, Results* results, int i);
void printOutputQ2 (char format_flag, Q2Type qType,ResultsQ2* output, int i);
void printOutputQ3 (char format_flag, Results* results, int i);
void printOutputQ4 (char format_flag, ResultsQ4* output, int i, HotelsManager *hotelsCatalog);
void printOutputQ5 (char format_flag, ResultsQ5* output, int i);
void printOutputQ6 (char format_flag, ResultsQ6* output, int i);
void printOutputQ7 (char format_flag, ResultsQ7* output, int i);
void printOutputQ8 (char format_flag, int output, int i);
void printOutputQ9 (char format_flag, OrdList* list, int i);

#endif