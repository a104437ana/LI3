#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "catalogsManager.h"
#include "results.h"
#include "parser.h"
#include "interpreter.h"
#include <locale.h>
#include <sys/resource.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include "interactive.h"

int main (int argc, char** argv) {

    //inicialização de variáveis para medição de tempo
    struct timespec start, end, interm;
    double elapsed, cat, par, sor, com, des;
    clock_gettime(CLOCK_REALTIME, &start);
    setlocale(LC_COLLATE, "en_US.UTF-8");
    setlocale(LC_CTYPE, "en_US.UTF-8");
    //inicialização dos catalogos
    Catalogs *catalogs = createCatalogs();
        clock_gettime(CLOCK_REALTIME, &interm);
        cat = (interm.tv_sec - start.tv_sec) + (interm.tv_nsec - start.tv_nsec) / 1e9;

    if (argc == 3) {
    parse_all_files(argv[1],catalogs);
        clock_gettime(CLOCK_REALTIME, &end);
        par = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;

    sortCatalogs(catalogs);
        clock_gettime(CLOCK_REALTIME, &interm);
        sor = (interm.tv_sec - end.tv_sec) + (interm.tv_nsec - end.tv_nsec) / 1e9;

    parseCommandFile(argv[2],catalogs);
        clock_gettime(CLOCK_REALTIME, &end);
        com = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;
    }
    else if (argc == 1) {
    printf("Attention: This program requires a maximized window at all times for optimal performance. Please ensure that the window is maximized before proceeding. Press Enter to continue...");
    getchar();
    setlocale(LC_ALL,""); //permite a utilização de caracteres especiais da nossa localidade
    initscr(); //inicia ncurses

    noecho(); //para não escrever as teclas que são pressionadas no teclado

    keypad(stdscr, TRUE); //permite a interpretação de caracteres especiais

    int max_row, max_col;
    getmaxyx(stdscr, max_row, max_col);

    mvprintw(0, 0, "Welcome to Interactive Mode!\n\nEnter the path of the dataset: ");

    refresh();
    int row, col;
    getyx(stdscr,row,col);

    interactive_mode(max_row,max_col,row,col,catalogs);

    endwin(); //termina ncurses
    }

//    printFullList(getUsersByName(getUsersCatalog(catalogs)));

    //liberta o espaço em memória dos catalogos
    destroyCatalogs(catalogs);
        clock_gettime(CLOCK_REALTIME, &interm);
        des = (interm.tv_sec - end.tv_sec) + (interm.tv_nsec - end.tv_nsec) / 1e9;

    //imprime tempo de execução
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %.6f seconds\n", elapsed);
        printf(" catalogs:\t %.6f seconds (%5.2f%%)\n", cat, (cat/elapsed)*100);
        printf(" parser:\t %.6f seconds (%5.2f%%)\n", par, (par/elapsed)*100);
        printf(" sort:\t\t %.6f seconds (%5.2f%%)\n", sor, (sor/elapsed)*100);
        printf(" commands:\t %.6f seconds (%5.2f%%)\n", com, (com/elapsed)*100);
        printf(" destroy:\t %.6f seconds (%5.2f%%)\n", des, (des/elapsed)*100);
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage: %ld MB\n", r_usage.ru_maxrss / 1000);

    return 0;
}
