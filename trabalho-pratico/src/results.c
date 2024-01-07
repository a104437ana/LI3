#include "results.h"

struct queryResult{
    int number_of_results;
    Result ** results;
};

struct result{
     int number_of_fields;
     Result_Field ** fields;
};

struct result_field{
    char * field_name;
    char * data;
};

Result_Field * createField() {
    Result_Field * field = malloc(sizeof(Result_Field));
    field->field_name = NULL;
    field->data = NULL;
    return field;
}

Result * createResult() {
    Result * result = malloc(sizeof(Result));
    result->number_of_fields = 0;
    result->fields = NULL;
    return result;
}

QueryResult * createQResult() {
    QueryResult * qresult = malloc(sizeof(QueryResult));
    qresult->number_of_results = 0;
    qresult->results = NULL;
    return qresult;
}

void destroyField (Result_Field * field){
    free(field->field_name);
    free(field->data);
}

void destroyResult (Result* result) {
    int i;
    for (i=0; i<result->number_of_fields; i++){
        destroyField(result->fields[i]);
    }
    free(result->fields);
}

void destroyQResult (QueryResult* qresult) {
    int i;
    for (i=0; i<qresult->number_of_results; i++){
        destroyResult(qresult->results[i]);
    }
    free(qresult->results);
    free(qresult);
}

void clearQResult (QueryResult* qresult){
    int i;
    for (i=0; i<qresult->number_of_results; i++){
        destroyResult(qresult->results[i]);
    }
    free(qresult->results); qresult->results = NULL;
    qresult->number_of_results = 0;
}

void clearResult (Result* result){
    int i;
    for (i=0; i<result->number_of_fields; i++){
        destroyField(result->fields[i]);
    }
    free(result->fields); result->fields = NULL;
    result->number_of_fields = 0;
}


void setNumberResults (QueryResult* qresult, int n){
    clearQResult(qresult);
    qresult->number_of_results = n;
    qresult->results = malloc(sizeof(Result *)*n);
    int i;
    for (i=0; i<n; i++){
        qresult->results[i] = createResult();
    }
}

void setNumberFieldsQ (QueryResult* result, int i, int n){
   setNumberFields(result->results[i], n);
}

void setNumberFields (Result* result, int n){
    clearResult(result);
    result->number_of_fields = n;
    result->fields = malloc(sizeof(Result_Field *)*n);
    int i;
    for (i=0; i<n; i++){
        result->fields[i] = createField();
    }
}

void setResult (QueryResult * qresult, Result* result, int i){
    int j;
    for (j=0; j< result->number_of_fields; j++){
        setField(qresult->results[i], j, result->fields[j]->field_name, result->fields[j]->data);
    }
}

void setField (Result * result, int i, char * name, char * data){
    result->fields[i]->field_name = strdup(name);
    result->fields[i]->data = strdup(data);
}

void setFieldQ (QueryResult * result, int r, int i, char * name, char * data){
    setField(result->results[r], i, name, data);
}

int getNumberResults (QueryResult* qresult){
    return (qresult->number_of_results);
}

int getNumberFieldsQ (QueryResult* result, int i){
   return (getNumberFields(result->results[i]));
}

int getNumberFields (Result* result){
    return (result->number_of_fields);
}

char * getFieldName (QueryResult * result, int r, int i){
    char * res = strdup(result->results[r]->fields[i]->field_name);
    return res;
}

char * getFieldData (QueryResult * result, int r, int i){
    char * res = strdup(result->results[r]->fields[i]->data);
    return res;
}
