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
char * printResultF(QueryResult * result, int r);
char * printResult(QueryResult * result, int r);
void printQueryOutput (int commandN, char format_flag, QueryResult * output);

#endif