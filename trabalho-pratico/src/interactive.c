#include "interactive.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include "catalogsManager.h"
#include "parser.h"
#include "interpreter.h"
#include "results.h"
#include <ctype.h>

char* get_string (int max_row, int max_col,int min_row,int min_col, int n) {
    char* path = malloc(n);
    int row;
    int col;
    int i = 0;
    while (1) {
        int key = getch();
        getyx(stdscr, row, col);
        if (key == '\n') {
            break;
        }
        if (key == KEY_BACKSPACE || key == KEY_DC) {
            if (col == min_col) {
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
            if (key != KEY_UP && key != KEY_DOWN && key != KEY_LEFT && key != KEY_RIGHT && key != 27 && key != KEY_RESIZE && key != '\t') {
                if ((col != max_col || row != max_row) && i<n) {
                    printw("%c",key);
                    char key_char = key;
                    path[i] = key_char;
                    i++;
                }
            }
        }
    }
    path[i] = '\0';
    return path;
}

int get_option (int first_x, int last_option) {
    int x = first_x;
    int y = 1;
    int option = 1;
    mvaddch(x, y, 'x' | A_BOLD);
    move(x,y);
    int exit = 0;
    int key;
    while (exit == 0) {
        key = getch();
        switch (key) {
            case KEY_UP: mvaddch(x, y, ' ');
                         if (x != first_x) {
                            option--;
                            x-=2;
                         }
                         mvaddch(x, y, 'x' | A_BOLD);
                         move(x,y);
                         break;
            case KEY_DOWN: mvaddch(x, y, ' ');
                           if (option != last_option) {
                            option++;
                            x+=2;
                           }
                           mvaddch(x, y, 'x' | A_BOLD);
                           move(x,y);
                           break;
            case '\n': exit=1;
                       break;
        }
    }
    return option;
}

int get_querie (int max_row, int max_col,Catalogs* catalogs,QueryResult* result) {
    int proceed;
    clear();

    mvprintw(0, 0, "Menu :)\n\nNavigate options using the arrow keys (up and down). Press Enter to select your choice.");
    mvprintw(4, 0, "   Query 1 - Lists the summary of a user, flight, or reservation."); 
    mvprintw(6, 0, "   Query 2 - Lists the flights and/or reservations of a user.");
    mvprintw(8, 0, "   Query 3 - Presents the average rating of a hotel.");
    mvprintw(10, 0, "   Query 4 - Lists the hotel reservations, sorted by start date (from the most recent to the oldest).");
    mvprintw(12, 0, "   Query 5 - Lists the flights with origin at a given airport, between two dates, sorted by estimated departure date (from the most recent to the oldest).");
    mvprintw(14, 0, "   Query 6 - Lists the top N airports with the most passengers for a given year.");
    mvprintw(16, 0, "   Query 7 - Lists the top N airports with the highest median of delays.");
    mvprintw(18, 0, "   Query 8 - Presents the total revenue of a hotel between two dates (inclusive).");
    mvprintw(20, 0, "   Query 9 - Lists all users whose names start with the prefix provided as an argument, sorted by name in ascending order.");
    mvprintw(22, 0, "   Query 10 - Presents various overall metrics of the application.");
    mvprintw(24, 0, "   Exit the program.");

    int query = get_option(4,11);
    clear();
    int c;
    char* string1 = NULL;
    char* string2 = NULL;
    char* string3 = NULL;
    char* command = NULL;
    int option;
    int x = 0;
    switch(query) {
        case 1: mvprintw(0, 0, "Query 1 - Lists the summary of a user, flight, or reservation.");
                mvprintw(2, 0, "Enter the ID: ");
                string1 = get_string(max_row,max_col,2,14,60);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                x = 4;
                break;
        case 2: mvprintw(0, 0, "Query 2 - Lists the flights and/or reservations of a user.");
                mvprintw(2, 0, "Enter the ID of the user: ");
                string1 = get_string(max_row,max_col,2,26,60);
                mvprintw(4,0, "Navigate options using the arrow keys (up and down). Press Enter to select your choice.");
                mvprintw(6,0, "   Only flights.");
                mvprintw(8,0, "   Only reservations.");
                mvprintw(10,0, "   Both.");
                x = 12;
                option = get_option(6,3);
                switch(option) {
                    case 1: command = malloc(12+strlen(string1));
                            sprintf(command,"%d %s flights",query,string1);
                            break;
                    case 2: command = malloc(17+strlen(string1));
                            sprintf(command,"%d %s reservations",query,string1);
                            break;
                    case 3: command = malloc(4+strlen(string1));
                            sprintf(command,"%d %s",query,string1);
                            break;
                }
                break;
        case 3: mvprintw(0, 0, "Query 3 - Presents the average rating of a hotel.");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                x = 4;
                string1 = get_string(max_row,max_col,2,27,60);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 4: mvprintw(0, 0, "Query 4 - Lists the hotel reservations, sorted by start date (from the most recent to the oldest).");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                x = 4;
                string1 = get_string(max_row,max_col,2,27,60);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 5: mvprintw(0, 0, "Query 5 - Lists the flights with origin at a given airport, between two dates, sorted by estimated departure date (from the most recent to the oldest).");
                mvprintw(2, 0, "Enter the name of the airport: ");
                string1 = get_string(max_row,max_col,2,31,3);
                mvprintw(4,0, "Enter the begin date in this format yyyy/MM/dd hh:mm:ss (e.g. 2023/01/31 23:59:59): ");
                string2 = get_string(max_row,max_col,4,84,19);
                mvprintw(6,0, "Enter the end date in this format yyyy/MM/dd hh:mm:ss (e.g. 2023/01/31 23:59:59): ");
                x = 8;
                string3 = get_string(max_row,max_col,6,82,19);
                command = malloc(10+strlen(string1)+strlen(string2)+strlen(string3));
                sprintf(command,"%d %s \"%s\" \"%s\"",query,string1,string2,string3);
                break;
        case 6: mvprintw(0, 0, "Query 6 - Lists the top N airports with the most passengers for a given year.");
                mvprintw(2, 0, "Enter the year: ");
                string1 = get_string(max_row,max_col,2,16,6);
                mvprintw(4,0, "Enter a non-negative number N (e.g. 12): ");
                x = 6;
                string2 = get_string(max_row,max_col,4,41,10);
                for (c = 0; string2[c] != '\0';c++) {
                    if (!isdigit(string2[c])) break;
                }
                if (string2[c] != '\0' || c==0) {
                    mvprintw(4,0, "Enter a non-negative number N (e.g. 12) (use digits only instead of text): ");
                    refresh();
                    free(string2);
                    string2 = get_string(max_row,max_col,4,75,10);
                }
                command = malloc(5+strlen(string1)+strlen(string2));
                sprintf(command,"%d %s %s",query,string1,string2);
                break;
        case 7: mvprintw(0, 0, "Query 7 - Lists the top N airports with the highest median of delays.");
                mvprintw(2,0, "Enter a non-negative number N (e.g. 12): ");
                x = 4;
                string1 = get_string(max_row,max_col,2,41,10);
                for (c = 0; string1[c] != '\0';c++) {
                    if (!isdigit(string1[c])) break;
                }
                if (string1[c] != '\0' || c==0) {
                    mvprintw(2,0, "Enter a non-negative number N (e.g. 12) (use digits only instead of text): ");
                    refresh();
                    free(string1);
                    string1 = get_string(max_row,max_col,2,75,10);
                }
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 8: mvprintw(0, 0, "Query 8 - Presents the total revenue of a hotel between two dates (inclusive).");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                string1 = get_string(max_row,max_col,2,27,60);
                mvprintw(4,0, "Enter the begin date in this format yyyy/MM/dd (e.g. 2023/01/31): ");
                string2 = get_string(max_row,max_col,4,66,10);
                mvprintw(6,0, "Enter the end date int this format yyyy/MM/dd (e.g. 2023/01/31): ");
                x = 8;
                string3 = get_string(max_row,max_col,6,64,10);
                command = malloc(6+strlen(string1)+strlen(string2)+strlen(string3));
                sprintf(command,"%d %s %s %s",query,string1,string2,string3);
                break;
        case 9: mvprintw(0, 0, "Query 9 - Lists all users whose names start with the prefix provided as an argument, sorted by name in ascending order.");
                mvprintw(2, 0, "Enter the prefix: ");
                x = 4;
                string1 = get_string(max_row,max_col,2,18,60);
                command = malloc(6+strlen(string1));
                sprintf(command,"%d \"%s\"",query,string1);
                break;
        case 10: mvprintw(0, 0, "Query 10 - Presents various overall metrics of the application.");
                mvprintw(2,0, "Navigate options using the arrow keys (up and down). Press Enter to select your choice.");
                mvprintw(4,0, "   All years.");
                mvprintw(6,0, "   One specific year.");
                mvprintw(8,0, "   One specific month.");
                option = get_option(4,3);
                if (option != 1) {
                    mvprintw(10,0, "Enter the year: ");
                    string1 = get_string(max_row,max_col,10,16,4);
                    if (option == 3) {
                        mvprintw(11,0, "Enter the month: ");
                        x = 13;
                        string2 = get_string(max_row,max_col,11,17,2);
                        command = malloc(5+strlen(string1)+strlen(string2));
                        sprintf(command,"%d %s %s",query,string1,string2);
                    }
                    else {
                        x = 12;
                        command = malloc(4+strlen(string1));
                        sprintf(command,"%d %s",query,string1); 
                    }
                }
                else {
                    x = 10;
                    command = malloc(3);
                    sprintf(command,"%d",query);
                }
                break;
        case 11: break;
    }
    if (query != 11) {
        mvprintw(x,0,"Navigate options using the arrow keys (up and down). Press Enter to select the format of the output.");
        mvprintw(x+2,0,"   CSV");
        mvprintw(x+4,0,"   Field by field");
        option = get_option(x+2,2);
        proceed = option;
        printw("\n\nExecuting query. Please wait...");
        refresh();
        Command* c = parseCommandLine(command);
        processCommand(c,0,result,catalogs);
    }
    else proceed = 0;
    free(command);
    free(string1);
    free(string2);
    free(string3);
    return proceed;
}

void printResultP_CSV (int line,int j,int x,QueryResult* result) {
    move(line,0);
    int i;
    for (i = 1; i<x; i++) {
        char * data = getFieldData(result,j,i-1);
        printw("%s;",data);
        refresh();
        free(data);
    }
    char * data = getFieldData(result,j,i-1);
    printw("%s",data);
    refresh();
    free(data);
}

void printResultPage_CSV (int page, int max_row,int j, QueryResult* result) {
    int nResults = getNumberResults(result);
    int x = getNumberFieldsQ(result,j-1);
    for (int i = 2; i < max_row && j <= nResults; i++) {
        printResultP_CSV(i,j-1,x,result);
        j++;
        if (j<=nResults) x = getNumberFieldsQ(result,j-1);
        else break;
    }
}

void printResultP_Field (int line,int j,int x,QueryResult* result) {
    for (int i = 1; i<=x; i++) {
        char * name = getFieldName(result,j,i-1);
        char * data = getFieldData(result,j,i-1);
        mvprintw(line+i,0,"%s: %s",name,data);
        refresh();
        free(name); free(data);
    }
}

void printResultPage_Field (int page, int max_row,int j, QueryResult* result) {
    int nResults = getNumberResults(result);
    int x = getNumberFieldsQ(result,j-1);
    for (int i = 2; i+(x+2) <= max_row; i+=x+2) {
        mvprintw(i,0,"--- %d ---\n",j);
        refresh();
        printResultP_Field(i,j-1,x,result);
        j++;
        if (j<=nResults) x = getNumberFieldsQ(result,j-1);
        else break;
    }
}

void firstByPage (QueryResult* result, int max_row, int firstResult[],int format) {
    if (format == 2) {
    int nResults = getNumberResults(result);
    int page = 0;
    int i = 0;
    int nFields;
    while (i<nResults) {
        firstResult[page] = i+1;
        page++;
        nFields = getNumberFieldsQ(result,i);
        for (int j = 2; j+(nFields+2) <= max_row; j += (nFields+2)) {
            i++;
            if (i<nResults) nFields = getNumberFieldsQ(result,i);
            else break;
        }
    }
    }
    else {
        int nResults = getNumberResults(result);
        int page = 0;
        int i = 0;
        while (i<nResults) {
            firstResult[page] = i+1;
            page++;
            for (int j = 2; j < max_row && i<nResults; j++) {
                i++;
            }
        }
    }
}

int pagesNumber (QueryResult* result, int max_row, int format) {
    int nResults = getNumberResults(result);
    int page = 0;
    int i = 0;
    if (format == 2) {
    int nFields;
    while (i<nResults) {
        page++;
        nFields = getNumberFieldsQ(result,i);
        for (int j = 2; j+(nFields+2) <= max_row; j += (nFields+2)) {
            i++;
           if (i<nResults) nFields = getNumberFieldsQ(result,i);
           else break;
        }
    }
    }
    else {
        while (i<nResults) {
            page++;
            for (int j = 2; j < max_row && i<nResults; j++) {
                i++;
            }
        }
    }
    return page;
}

void interactive_mode(int max_row, int max_col,Catalogs* catalogs) {
    mvprintw(0, 0, "Welcome to Interactive Mode!\n\nWARNING: Do not resize the window during program execution.\nResizing may cause unexpected behavior.\nFrom now on, please keep the window size unchanged.\n\nEnter the path of the dataset: ");
    refresh();
    char* path = get_string(max_row,max_col,6,31,500);
    int n = 0;
    int not_error = 4;
    while (!valid_directory_dataset(path) && n<2) {
        not_error = 0;
        clear();
        mvprintw(0,0,"Invalid path for the dataset. Please try again!");
        refresh();
        mvprintw(2,0,"Enter the path of the dataset: ");
        refresh();
        path = get_string(max_row,max_col,2,31,500);
        n++;
    }
    if (valid_directory_dataset(path)) {
    mvprintw(4 + not_error,0, "Parsing files and sorting data. Please wait...");
    refresh();
    parse_all_files(path,catalogs);
    free(path);
    sortCatalogs(catalogs);
    QueryResult * result = createQResult();
    int proceed = get_querie(max_row,max_col,catalogs,result);
    while (proceed) {
        clear();
        mvprintw(0,0, " <  Previous page (Press Left)");
        mvprintw(0,max_col/2, "Page 1");
        mvprintw(0,max_col/4, "(Press Enter to access the menu)");
        mvprintw(0,max_col-27, "(Press Right) Next page  > ");
        int pages = pagesNumber(result,max_row,proceed);
        int firstResult[pages];
        firstByPage(result,max_row,firstResult,proceed);
        int page = 1;
        if (pages != 0) {
            if (proceed == 2) printResultPage_Field(page,max_row,firstResult[page-1],result);
            else printResultPage_CSV(page,max_row,firstResult[page-1],result);
        }
        move(0,1);     
        int key = getch();
        while (key != '\n') {
            if (key == KEY_LEFT) {
                if (page != 1 && pages!=0) {
                    page--;
                    clear();
                    mvprintw(0,0, " <  Previous page (Press Left)");
                    mvprintw(0,max_col/2, "Page %d     ",page);
                    mvprintw(0,max_col/4, "(Press Enter to access the menu)");
                    mvprintw(0,max_col-27, "(Press Right) Next page  > ");
                    if (pages != 0) {
                        if (proceed == 2) printResultPage_Field(page,max_row,firstResult[page-1],result);
                        else printResultPage_CSV(page,max_row,firstResult[page-1],result);
                    }
                }
                move(0,1);
            }
            if (key == KEY_RIGHT) {
                if (page != pages && pages!=0) {
                    page++;
                    clear();
                    mvprintw(0,0, " <  Previous page (Press Left)");
                    mvprintw(0,max_col/2, "Page %d     ",page);
                    mvprintw(0,max_col/4, "(Press Enter to access the menu)");
                    mvprintw(0,max_col-27, "(Press Right) Next page  > ");
                    if (pages != 0) {
                        if (proceed == 2) printResultPage_Field(page,max_row,firstResult[page-1],result);
                        else printResultPage_CSV(page,max_row,firstResult[page-1],result);
                    }
                }
                move(0,max_col-2);
            }
            key = getch();
        }
        destroyQResult(result);
        result = createQResult();
        proceed = get_querie(max_row,max_col,catalogs,result);
    }
    destroyQResult(result);
    }
    clear();
    mvprintw(0,0,"Exiting program...");
    refresh();
    sleep(1);
}