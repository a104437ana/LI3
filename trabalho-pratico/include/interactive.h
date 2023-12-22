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

void get_path_dataset (int max_row, int max_col,int min_row,int min_col,Catalogs* catalogs);
void interactive_mode(int max_row, int max_col,int row,int col, Catalogs* catalogs);

#endif