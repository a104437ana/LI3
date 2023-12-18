#ifndef _RESULTS_
#define _RESULTS_

#include <stdlib.h>

typedef struct results Results;

typedef struct resultQ3 ResultQ3;

Results *createResults();

void destroyResults (Results* results);

double getRating (Results* results);

void setRating (Results* results, double newRating);

#endif