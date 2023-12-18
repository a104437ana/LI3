#include "results.h"
struct results {
    ResultQ3* resultQ3;
};

struct resultQ3 {
    double rating;
};

Results *createResults() {
    Results *results = malloc(sizeof(Results));
    results->resultQ3 = malloc(sizeof(ResultQ3));

    return results;
}

void destroyResults (Results* results) {
  free(results->resultQ3);
  free(results);
}

double getRating (Results* results) {
  return results->resultQ3->rating;
}

void setRating (Results* results, double newRating) {
  results->resultQ3->rating = newRating;
}