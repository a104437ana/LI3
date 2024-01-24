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
    //struct timespec start, end, interm;
    //double elapsed, cat, par, sor, com, des;
    //clock_gettime(CLOCK_REALTIME, &start);
    //setlocale(LC_COLLATE, "en_US.UTF-8");
    //setlocale(LC_CTYPE, "en_US.UTF-8");
    setlocale(LC_ALL, "en_US.UTF-8");
    //inicialização dos catalogos
    Catalogs *catalogs = createCatalogs();
        //clock_gettime(CLOCK_REALTIME, &interm);
        //cat = (interm.tv_sec - start.tv_sec) + (interm.tv_nsec - start.tv_nsec) / 1e9;

    if (argc == 3) {
        if (valid_directory_dataset(argv[1])) {
            if (exist_file(argv[2])) {
                parse_all_files(argv[1],catalogs);
                //clock_gettime(CLOCK_REALTIME, &end);
                //par = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;

                sortCatalogs(catalogs);
                //clock_gettime(CLOCK_REALTIME, &interm);
                //sor = (interm.tv_sec - end.tv_sec) + (interm.tv_nsec - end.tv_nsec) / 1e9;

                parseCommandFile(argv[2],catalogs,0,NULL,NULL);
                //clock_gettime(CLOCK_REALTIME, &end);
                //com = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;
            }
            else printf("Error: The provided file path does not match any existing file.\n");
        }
        else printf("Error: The provided directory path is not valid for the dataset.\n");
    }
    else {
    if (argc == 1) {
    printf("Attention: This program requires a minimum window size of 154x26. Please adjust the window size now to meet the requirements and your preferences. Note that resizing won't be supported after this adjustment, so choose wisely. After adjusting, press Enter to continue...");
    getchar();
    interactive_mode(catalogs);
    }
    else printf("Error: This program requires either exactly 3 or 1 argument(s).\n");
    }

//    printFullList(getUsersByName(getUsersCatalog(catalogs)));

    //liberta o espaço em memória dos catalogos
    destroyCatalogs(catalogs);
        //clock_gettime(CLOCK_REALTIME, &interm);
        //des = (interm.tv_sec - end.tv_sec) + (interm.tv_nsec - end.tv_nsec) / 1e9;

    //imprime tempo de execução
    /*clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %.6f seconds\n", elapsed);
        printf(" catalogs:\t %.6f seconds (%5.2f%%)\n", cat, (cat/elapsed)*100);
        printf(" parser:\t %.6f seconds (%5.2f%%)\n", par, (par/elapsed)*100);
        printf(" sort:\t\t %.6f seconds (%5.2f%%)\n", sor, (sor/elapsed)*100);
        printf(" commands:\t %.6f seconds (%5.2f%%)\n", com, (com/elapsed)*100);
        printf(" destroy:\t %.6f seconds (%5.2f%%)\n", des, (des/elapsed)*100);
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage: %ld MB\n", r_usage.ru_maxrss / 1000);*/

    return 0;
}
