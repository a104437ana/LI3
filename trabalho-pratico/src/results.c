#include "results.h"

struct queryResult{
    int number_of_results;
    int max_results;
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
    result->fields = malloc(sizeof(Result_Field*));
    return result;
}

QueryResult * createQResult() {
    QueryResult * qresult = malloc(sizeof(QueryResult));
    qresult->number_of_results = 0;
    qresult->max_results = 2;
    qresult->results = malloc(sizeof(Result*)*2);
    qresult->results[0] = createResult();
    qresult->results[1] = createResult();
    return qresult;
}

void destroyField (Result_Field * field){
    if (field==NULL) return;
    free(field->field_name);
    free(field->data);
    free(field);
}

void destroyResult (Result* result) {
    if (result==NULL) return;
    int i;
    for (i=0; i<result->number_of_fields; i++){
        destroyField(result->fields[i]);
    }
    free(result->fields);
    free(result);
}

void destroyQResult (QueryResult* qresult) {
    if(qresult==NULL) return;
    int i;
    for (i=0; i<qresult->number_of_results; i++){
        destroyResult(qresult->results[i]);
    }
    free(qresult->results);
    free(qresult);
}

void clearResult (Result* result){
    if (result==NULL) return;
    int i;
    for (i=0; i<(result->number_of_fields); i++){
        destroyField(result->fields[i]);
    }
    free(result->fields); result->fields = NULL;
    result->number_of_fields = 0;
}


void setNumberResults (QueryResult* qresult, int n){
    int i;
    for (i=0; i<qresult->number_of_results;i++){
        destroyResult(qresult->results[i]);
    }
    free(qresult->results);
    qresult->number_of_results = n;
    qresult->max_results = n;
    qresult->results = malloc(sizeof(Result *)*n);
    for (i=0; i<n; i++){
        qresult->results[i] = createResult();
    }
}

void setNumberFieldsQ (QueryResult* result, int i, int n){
   setNumberFields(result->results[i], n);
}

void setNumberFields (Result* result, int n){
    result->number_of_fields = n;
    result->fields = realloc(result->fields,sizeof(Result_Field *)*n);
    int i;
    for (i=0; i<n; i++){
        result->fields[i] = createField();
    }
}

void addResult (QueryResult * qresult, int i){
    if (i>=qresult->max_results){
        qresult->results = realloc(qresult->results, (sizeof(Result*)*(qresult->max_results)*2));
        qresult->max_results*=2;
        qresult->results[i] = createResult();
        qresult->number_of_results = i+1;
    }
    else{
        qresult->results[i] = createResult();
        qresult->number_of_results = i+1;
    }
}

void swapResults(QueryResult *qresult, int i, int j) {
    Result *aux = qresult->results[i];
    qresult->results[i] = qresult->results[j];
    qresult->results[j] = aux;
}

void reverseResults (QueryResult * qresult){
    int size = qresult->number_of_results;
    int i = 0;
    int j = size-1;
    while(i<j){
        swapResults(qresult, i, j);
        i++; j--;
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
