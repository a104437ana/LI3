#ifndef _RESULTS_
#define _RESULTS_

#include <stdlib.h>
#include <string.h>
#include "utility.h"

typedef struct queryResult QueryResult;
typedef struct result Result;
typedef struct result_field Result_Field;

Result_Field * createField();
Result * createResult() ;
QueryResult * createQResult() ;

void destroyField (Result_Field * field);
void destroyResult (Result* result) ;
void destroyQResult (QueryResult* qresult) ;

void clearResult (Result* result);

void setNumberResults (QueryResult* qresult, int n);
void setNumberFieldsQ (QueryResult* result, int i, int n);
void setNumberFields (Result* result, int n);
void addResult (QueryResult * qresult, int i);
void addSetResult (QueryResult * qresult, int i, Result * result);
void setField (Result * result, int i, char * name, char * data);
void setFieldQ (QueryResult * result, int r, int i, char * name, char * data);

void swapResults(QueryResult *qresult, int i, int j);
void reverseResults (QueryResult * qresult);

int getNumberResults (QueryResult* qresult);
int getNumberFieldsQ (QueryResult* result, int i);
int getNumberFields (Result* result);
char * getFieldName (QueryResult * result, int r, int i);
char * getFieldData (QueryResult * result, int r, int i);

#endif