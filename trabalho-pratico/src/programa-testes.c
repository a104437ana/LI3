#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "usersManager.h"
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "flightsManager.h"
#include "airportsManager.h"
#include "catalogsManager.h"
#include "interpreter.h"
#include <locale.h>
#include <sys/resource.h>
#include "results.h"

//#define USERS_HASHTABLE_INI_SIZE 100000
//#define RESERVATIONS_HASHTABLE_INI_SIZE 40000
//#define HOTELS_HASHTABLE_INI_SIZE 100
//#define FLIGHTS_HASHTABLE_INI_SIZE 1000
//#define AIRPORTS_HASHTABLE_INI_SIZE 100

int compare_files (char* file_path1, char* file_path2) {
    int equal = 0;
    int current_line = 1;
    if (exist_file(file_path1) && exist_file(file_path2)) {
        equal = 1;
        FILE *file1;
        file1 = fopen(file_path1,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line1 = NULL;
        size_t n1;
        ssize_t read1;
        FILE *file2;
        file2 = fopen(file_path2,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line2 = NULL;
        size_t n2;
        ssize_t read2;
        while((read1 = getline(&line1,&n1,file1)) != -1 && equal != 0){
            if ((read2 = getline(&line2,&n2,file2)) != -1) {
                if (strcmp(line1,line2) != 0) {
                    equal = 0;
                }
                else current_line++;
            }
            else equal = 0;
        }
        if (equal == 1 && (read2 = getline(&line2,&n2,file2)) != -1) {
            equal = 0;
        }
        free(line1);
        free(line2);
        fclose(file1);
        fclose(file2);
    }
    if (equal == 1) current_line = 0;
    return current_line;
}

int main (int argc, char** argv) {
    if (argc == 4) {
    //inicialização de variáveis para medição de tempo
    struct timespec start, end, interm;
    double elapsed, cat, par, sor, com, des;
    clock_gettime(CLOCK_REALTIME, &start);
    setlocale(LC_COLLATE, "en_US.UTF-8");
    //inicialização dos catalogos
    Catalogs *catalogs = createCatalogs();
        clock_gettime(CLOCK_REALTIME, &interm);
        cat = (interm.tv_sec - start.tv_sec) + (interm.tv_nsec - start.tv_nsec) / 1e9;

    parse_all_files(argv[1],catalogs);
        clock_gettime(CLOCK_REALTIME, &end);
        par = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;

    sortCatalogs(catalogs);
        clock_gettime(CLOCK_REALTIME, &interm);
        sor = (interm.tv_sec - end.tv_sec) + (interm.tv_nsec - end.tv_nsec) / 1e9;

    parseCommandFile(argv[2],catalogs,1);
        clock_gettime(CLOCK_REALTIME, &end);
        com = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;

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
    printf("Memory usage: %ld KB\n", r_usage.ru_maxrss);
    /*

    nao apagar este codigo!

    int size = strlen(argv[3]) + 25;
    char* correct_error_file = malloc(size);
    char* our_error_file = malloc(35);
    int equal_file = 0;

    strcpy(correct_error_file,argv[3]);
    strcat(correct_error_file,"/users_errors.csv");
    strcpy(our_error_file,"Resultados/users_errors.csv");
    equal_file = compare_files(correct_error_file,our_error_file);
    if (equal_file == 1) printf("O ficheiro users_errors.csv está correto.✅\n");
    else printf("O ficheiro users_errors.csv não está correto.❌\n");

    strcpy(correct_error_file,argv[3]);
    strcat(correct_error_file,"/reservations_errors.csv");
    strcpy(our_error_file,"Resultados/reservations_errors.csv");
    equal_file = compare_files(correct_error_file,our_error_file);
    if (equal_file == 1) printf("O ficheiro reservations_errors.csv está correto.✅\n");
    else printf("O ficheiro reservations_errors.csv não está correto.❌\n");

    strcpy(correct_error_file,argv[3]);
    strcat(correct_error_file,"/flights_errors.csv");
    strcpy(our_error_file,"Resultados/flights_errors.csv");
    equal_file = compare_files(correct_error_file,our_error_file);
    if (equal_file == 1) printf("O ficheiro flights_errors.csv está correto.✅\n");
    else printf("O ficheiro flights_errors.csv não está correto.❌\n");

    strcpy(correct_error_file,argv[3]);
    strcat(correct_error_file,"/passengers_errors.csv");
    strcpy(our_error_file,"Resultados/passengers_errors.csv");
    equal_file = compare_files(correct_error_file,our_error_file);
    if (equal_file == 1) printf("O ficheiro passengers_errors.csv está correto.✅\n");
    else printf("O ficheiro passengers_errors.csv não está correto.❌\n");
    
    free(correct_error_file);
    free(our_error_file);

    */
    int size = strlen(argv[3]) + 23;
    char* correct_output_file = malloc(size);
    char* output_file = malloc(23);
    char* our_output_file = malloc(33);
    int equal_files = 0;
    int i = 1;
    int j, k;
    float queries[10][3];
    for (j=0; j<10; j++) {
        for (k=0; k<3; k++)
            queries[j][k] = 0;
    }
    FILE *commands_file;
    commands_file = fopen(argv[2], "r");
    char *command = NULL;
    size_t command_len;
    ssize_t command_read;
    strcpy(correct_output_file,argv[3]);
    sprintf(output_file, "/command%d_output.txt", i);
    strcat(correct_output_file,output_file);
    while (exist_file(correct_output_file)) {
        sprintf(our_output_file, "Resultados/command%d_output.txt", i);
        equal_files = compare_files(correct_output_file,our_output_file);
        if ((command_read = getline(&command, &command_len, commands_file)) != -1) sscanf(command, " %d", &j);
        queries[j-1][2] += 1;
        if (equal_files == 0) {
            printf("command%d_output.txt passou o teste",i);
            if (i<10) printf("   ✅\n");
            if (i>=10 && i<100) printf("  ✅\n");
            if (i>=100) printf(" ✅\n");
            queries[j-1][1] += 1;
        }
        else {
            printf("command%d_output.txt falhou o teste",i);
            if (i<10) printf("   ❌\n");
            if (i>=10 && i<100) printf("  ❌\n");
            if (i>=100) printf(" ❌\n");
            printf("O primeiro erro está na linha %d...\n",equal_files);
            if (queries[j-1][0] == 0)
                queries[j-1][0] = i;
        }
        i++;
        strcpy(correct_output_file,argv[3]);
        sprintf(output_file, "/command%d_output.txt", i);
        strcat(correct_output_file,output_file);
    }
    for (j=0; j<10; j++) {
        if (queries[j][0] == 0)
            printf("Querie %2d passou os testes ........... (%3.0f/%3.0f %3.0f%%)\n", j+1, queries[j][1], queries[j][2], (queries[j][1] / queries[j][2]) * 100);
        else
            printf("Querie %2d primeiro erro no comando %3.0f (%3.0f/%3.0f %3.0f%%)\n", j+1, queries[j][0], queries[j][1], queries[j][2], (queries[j][1] / queries[j][2]) * 100);
    }
    free(correct_output_file);
    free(output_file);
    free(our_output_file);
    free(command);
    fclose(commands_file);
    printf("Elapsed time: %4.2f seconds\n", elapsed);
    printf("Memory usage: %4.2f MB\n", ((float) r_usage.ru_maxrss) / 1e3);
    }
    else printf("Erro: O programa requer exatamente 4 argumentos.\n");
    return 0;
}
