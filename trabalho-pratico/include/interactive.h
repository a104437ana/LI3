#ifndef _INTERACTIVE_
#define _INTERACTIVE_

#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include "catalogsManager.h"
#include "parser.h"

char* get_string (int max_row, int max_col,int min_row,int min_col,int n, int *proceed);
int get_querie (int max_row, int max_col,Catalogs* catalogs,QueryResult* result);
void printResultPage_CSV (int page, int max_row,int j, QueryResult* result);
void printResultPage_Field (int page, int max_row,int j, QueryResult* result);
void firstByPage (QueryResult* result, int max_row, int firstResult[], int format);
int pagesNumber (QueryResult* result, int max_row,int format);
void interactive_mode(Catalogs* catalogs);

#endif