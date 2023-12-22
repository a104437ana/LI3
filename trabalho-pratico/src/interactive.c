#include "interactive.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include "catalogsManager.h"
#include "parser.h"

void get_path_dataset (int max_row, int max_col,int min_row,int min_col,Catalogs* catalogs) {
    char* path = malloc(500);
    int row;
    int col;
    int i = 0;
    while (1) {
        int key = getch();
        getyx(stdscr, row, col);
        if (key == 27 || key == '\n') break; //27 ESQ KEY
        if (key == KEY_BACKSPACE || key == KEY_DC) {
            if (col == 0) {
                if (row != min_row) {
                    move(row-1,max_col-1);
                    printw(" ");
                    move(row-1,max_col-1);
                    i--;
                    path[i] = '\0';
                }
            }
            else {
                if (col != min_col || row != min_row) {
                    move(row,col-1);
                    printw(" ");
                    move(row,col-1);
                    i--;
                    path[i] = '\0';
                }
            }
        }
        else {
            if ((col != max_col || row != max_row) && i<500) {
                printw("%c",key);
                char key_char = key;
                path[i] = key_char;
                i++;
            }
        }
    }
    path[i] = '\0';
    //printf("\n%s\n",path);
    parse_all_files(path,catalogs);
    free(path);

}

void interactive_mode(int max_row, int max_col,int row,int col, Catalogs* catalogs) {
    get_path_dataset(max_row,max_col,row,col,catalogs);
}