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

char* get_string (int max_row, int max_col,int min_row,int min_col,int n);
int get_querie (int max_row, int max_col,Catalogs* catalogs,QueryResult* result);
void printResultP (int line,int j,int x,QueryResult* result);
int printResultPage (int page, int max_row,int j, QueryResult* result);
void firstByPage (QueryResult* result, int max_row, int firstResult[]);
int pagesNumber (QueryResult* result, int max_row);
void interactive_mode(int max_row, int max_col, Catalogs* catalogs);

#endif