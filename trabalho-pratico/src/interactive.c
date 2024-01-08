#include "interactive.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include "catalogsManager.h"
#include "parser.h"

char* get_string (int max_row, int max_col,int min_row,int min_col, int n) {
    char* path = malloc(n);
    int row;
    int col;
    int i = 0;
    while (1) {
        int key = getch();
        getyx(stdscr, row, col);
        if (key == 27 || key == '\n' || key == KEY_RESIZE) {
            if (key != '\n') {
                i=0;
            }
            break; //27 ESQ KEY
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
            if (key != KEY_UP && key != KEY_DOWN && key != KEY_LEFT && key != KEY_RIGHT) {
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

void get_querie (int max_row, int max_col,int min_row,int min_col,Catalogs* catalogs) {
    int exit = 0;
    clear();
    mvprintw(0, 0, "Choose one of the queries below:");
    mvprintw(2, 0, "   Query 1 - List the summary of a user, flight, or reservation."); 
    mvprintw(4, 0, "   Query 2 - List the flights and/or reservations of a user.");
    mvprintw(6, 0, "   Query 3 - Present the average rating of a hotel.");
    mvprintw(8, 0, "   Query 4 - List the hotel reservations, sorted by start date (from the most recent to the oldest).");
    mvprintw(10, 0, "   Query 5 - List the flights with origin at a given airport, between two dates, sorted by estimated departure date (from the most recent to the oldest).");
    mvprintw(12, 0, "   Query 6 - List the top N airports with the most passengers for a given year.");
    mvprintw(14, 0, "   Query 7 - List the top N airports with the highest median of delays.");
    mvprintw(16, 0, "   Query 8 - Present the total revenue of a hotel between two dates (inclusive).");
    mvprintw(18, 0, "   Query 9 - List all users whose names start with the prefix provided as an argument, sorted by name in ascending order.");
    mvprintw(20, 0, "   Query 10 - Present various overall metrics of the application.");


    mvaddch(2, 1, 'x' | A_BOLD);
    move (2,1);
    int key;
    int x = 2;
    int y = 1;
    int query = x;
    while (exit == 0) {
        key = getch();
        switch (key) {
            case KEY_UP: mvaddch(x, y, ' ');
                         move(x,y);
                         if (x != 2) x-=2;
                         mvaddch(x, y, 'x' | A_BOLD);
                         move(x,y);
                         query = x;
                         break;
            case KEY_DOWN: mvaddch(x, y, ' ');
                           move(x,y);
                           if (x != 20) x+=2; 
                           mvaddch(x, y, 'x' | A_BOLD);
                           move(x,y);
                           query = x;
                           break;
            case '\n': query /= 2; exit=1; break;
            case 27: query = 0; exit = 1;
                     break;
        }
    }
    clear();
    char* string1 = NULL;
    char* string2 = NULL;
    char* string3 = NULL;
    char* command = NULL;
    int query2;
    switch(query) {
        case 1: mvprintw(0, 0, "Query 1 - List the summary of a user, flight, or reservation.");
                mvprintw(2, 0, "Enter the ID: ");
                string1 = get_string(max_row,max_col,2,14,60);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 2: mvprintw(0, 0, "Query 2 - List the flights and/or reservations of a user.");
                mvprintw(2, 0, "Enter the ID of the user: ");
                string1 = get_string(max_row,max_col,2,26,60);
                mvprintw(4,0, "Choose one of the options below:");
                mvprintw(6,0, "   Only flights.");
                mvprintw(8,0, "   Only reservations.");
                mvprintw(10,0, "   Both.");
                mvaddch(6, 1, 'x' | A_BOLD);
                move (6,1);
                x = 6;
                y = 1;
                query2 = x;
                exit = 0;   
                while (exit == 0) {
                    key = getch();
                    switch (key) {
                        case KEY_UP: mvaddch(x, y, ' ');
                                     move(x,y);
                                     if (x != 6) x-=2;
                                     mvaddch(x, y, 'x' | A_BOLD);
                                     move(x,y);
                                     query2 = x;
                                     break;
                        case KEY_DOWN: mvaddch(x, y, ' ');
                                       move(x,y);
                                       if (x != 10) x+=2; 
                                       mvaddch(x, y, 'x' | A_BOLD);
                                       move(x,y);
                                       query2 = x;
                                       break;
                        case '\n': query2 /= 2; exit=1; break;
                        case 27: query2 = 0; exit = 1;
                                    break;
                        }
                }
                switch(query2) {
                    case 3: command = malloc(12+strlen(string1));
                            sprintf(command,"%d %s flights",query,string1);
                            break;
                    case 4: command = malloc(17+strlen(string1));
                            sprintf(command,"%d %s reservations",query,string1);
                            break;
                    case 5: command = malloc(4+strlen(string1));
                            sprintf(command,"%d %s",query,string1);
                            break;
                }
                break;
        case 3: mvprintw(0, 0, "Query 3 - Present the average rating of a hotel.");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                string1 = get_string(max_row,max_col,2,27,60);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 4: mvprintw(0, 0, "Query 4 - List the hotel reservations, sorted by start date (from the most recent to the oldest).");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                string1 = get_string(max_row,max_col,2,27,60);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 5: mvprintw(0, 0, "Query 5 - List the flights with origin at a given airport, between two dates, sorted by estimated departure date (from the most recent to the oldest).");
                mvprintw(2, 0, "Enter the name of the airport: ");
                string1 = get_string(max_row,max_col,2,31,3);
                mvprintw(4,0, "Enter the begin date (in this format 2023/01/31): ");
                string2 = get_string(max_row,max_col,4,50,10);
                mvprintw(6,0, "Enter the end date (int this format 2023/01/31): ");
                string3 = get_string(max_row,max_col,6,49,10);
                command = malloc(6+strlen(string1)+strlen(string2)+strlen(string3));
                sprintf(command,"%d %s %s %s",query,string1,string2,string3);
                break;
        case 6: mvprintw(0, 0, "Query 6 - List the top N airports with the most passengers for a given year.");
                mvprintw(2, 0, "Enter the year: ");
                string1 = get_string(max_row,max_col,2,16,6);
                mvprintw(4,0, "Enter the number N: ");
                string2 = get_string(max_row,max_col,4,20,10);
                command = malloc(5+strlen(string1)+strlen(string2));
                sprintf(command,"%d %s %s",query,string1,string2);
                break;
        case 7: mvprintw(0, 0, "Query 7 - List the top N airports with the highest median of delays.");
                mvprintw(2,0, "Enter the number N: ");
                string1 = get_string(max_row,max_col,2,20,10);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 8: mvprintw(0, 0, "Query 8 - Present the total revenue of a hotel between two dates (inclusive).");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                string1 = get_string(max_row,max_col,2,27,60);
                mvprintw(4,0, "Enter the begin date (in this format 2023/01/31): ");
                string2 = get_string(max_row,max_col,4,50,10);
                mvprintw(6,0, "Enter the end date (int this format 2023/01/31): ");
                string3 = get_string(max_row,max_col,6,49,10);
                command = malloc(6+strlen(string1)+strlen(string2)+strlen(string3));
                sprintf(command,"%d %s %s %s",query,string1,string2,string3);
                break;
        case 9: mvprintw(0, 0, "Query 9 - List all users whose names start with the prefix provided as an argument, sorted by name in ascending order.");
                mvprintw(2, 0, "Enter the prefix: ");
                string1 = get_string(max_row,max_col,2,18,60);
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 10: mvprintw(0, 0, "Query 10 - Present various overall metrics of the application.");
                mvprintw(2,0, "Choose one of the options below:");
                mvprintw(4,0, "   All years.");
                mvprintw(6,0, "   One specific year.");
                mvprintw(8,0, "   One specific month.");
                mvaddch(4, 1, 'x' | A_BOLD);
                move (4,1);
                x = 4;
                y = 1;
                query2 = x;
                exit = 0;   
                while (exit == 0) {
                    key = getch();
                    switch (key) {
                        case KEY_UP: mvaddch(x, y, ' ');
                                     move(x,y);
                                     if (x != 4) x-=2;
                                     mvaddch(x, y, 'x' | A_BOLD);
                                     move(x,y);
                                     query2 = x;
                                     break;
                        case KEY_DOWN: mvaddch(x, y, ' ');
                                       move(x,y);
                                       if (x != 8) x+=2; 
                                       mvaddch(x, y, 'x' | A_BOLD);
                                       move(x,y);
                                       query2 = x;
                                       break;
                        case '\n': query2 /= 2; exit=1; break;
                        case 27: query2 = 0; exit = 1;
                                    break;
                        }
                }
                if (query2 != 2) {
                    mvprintw(10,0, "Enter the year: ");
                    string1 = get_string(max_row,max_col,10,16,4);
                    if (query2 == 4) {
                        mvprintw(11,0, "Enter the month: ");
                        string2 = get_string(max_row,max_col,11,17,2);
                        command = malloc(5+strlen(string1)+strlen(string2));
                        sprintf(command,"%d %s %s",query,string1,string2);
                    }
                    else {
                        command = malloc(4+strlen(string1));
                        sprintf(command,"%d %s",query,string1); 
                    }
                }
                else {
                    command = malloc(3);
                    sprintf(command,"%d",query);
                }
                break;
        default: break;
    }
    //processCommand(parseCommandLine(command),1,1,2,3,4,catalogs,result);
    clear();
    mvprintw(0,0, "%s",command);
    getch();
    free(command);
    free(string1);
    free(string2);
    free(string3);
}

void interactive_mode(int max_row, int max_col,int row,int col, Catalogs* catalogs) {
    char* path = get_string(max_row,max_col,row,col,500);
    if (path[0] != '\0') {
        mvprintw(4,0, "Parsing files. Please wait...");
        refresh();
        parse_all_files(path,catalogs);
        free(path);
        get_querie(max_row,max_col,row,col,catalogs);
        clear();
        mvprintw(0,0, " <  Previous page");
        mvprintw(0,max_col/2, "Page 1");
        mvprintw(0,max_col-13, "Next page  > ");
        move(0,1);
        int key = getch();
        while (key != '\n') {
            if (key == KEY_LEFT) move(0,1);
            if (key == KEY_RIGHT) move(0,max_col-2);
            key = getch();
        }
    }
    else free(path);
}