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

/* A função compare_files verifica se dois ficheiros são iguais. Se forem iguais, retorna 0. Se forem diferentes,
retorna o número da linha onde a primeira incongruência foi encontrada. Esta função recebe os caminhos absolutos
de dois ficheiros, que serão comparados.*/
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

    if (valid_directory_dataset(argv[1])) {

    if (exist_file(argv[2])) {

    if (exist_directory(argv[3])) {

    //inicialização de variáveis para medição de tempo
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);
    setlocale(LC_ALL, "en_US.UTF-8");

    //inicialização dos catalogos
    Catalogs *catalogs = createCatalogs();  

    parse_all_files(argv[1],catalogs); 

    sortCatalogs(catalogs);

    FILE *commands_file;
    char *command = NULL;
    size_t command_len;
    ssize_t command_read;
    int nCommands = 0;
    double *commands_time = NULL;
    double qTime[11] = {0.0};
    commands_file = fopen(argv[2], "r");
    while ((command_read = getline(&command, &command_len, commands_file)) != -1) {
        nCommands++;
    }
    commands_time = malloc(sizeof(double)*nCommands);
    for (int w = 0; w < nCommands; w++) {
        commands_time[w] = 0.0;
    }
    fclose(commands_file);
    
    free(command);
    parseCommandFile(argv[2],catalogs,1,commands_time,qTime);

    //liberta o espaço em memória dos catalogos
    destroyCatalogs(catalogs);

    //imprime tempo de execução
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Running the test with the assumption that the input file and the output directory paths are correct:\n\n");
    int size = strlen(argv[3]) + 23;
    char* correct_output_file = malloc(size);
    char* output_file = malloc(30); //-O2
    char* our_output_file = malloc(40); //-O2
    int equal_files = 0;

    int i = 1;
    int j;
    float queries[10][3] = {{0.0f, 0.0f, 0.0f}};
    commands_file = fopen(argv[2], "r");
    command = NULL;
    
    strcpy(correct_output_file,argv[3]);
    sprintf(output_file, "/command%d_output.txt", i);
    strcat(correct_output_file,output_file);
    while (exist_file(correct_output_file) && (command_read = getline(&command, &command_len, commands_file)) != -1) {
        sscanf(command, " %d", &j);
        printf("Command %d (query %d): %s",i,j,command);
        printf("Time taken for this command to complete: %.6f seconds\n",commands_time[i-1]);
        sprintf(our_output_file, "Resultados/command%d_output.txt", i);
        equal_files = compare_files(correct_output_file,our_output_file);
        if (j > 0 && j < 11) queries[j-1][2] += 1;
        if (equal_files == 0) {
            printf("Command %d passed the test",i);
            if (i<10) printf("   ✅\n\n");
            if (i>=10 && i<100) printf("  ✅\n\n");
            if (i>=100) printf(" ✅\n\n");
            if (j > 0 && j < 11) queries[j-1][1] += 1;
        }
        else {
            printf("Command %d failed the test",i);
            if (i<10) printf("   ❌\n");
            if (i>=10 && i<100) printf("  ❌\n");
            if (i>=100) printf(" ❌\n");
            printf("The first error is on line %d...\n\n",equal_files);
            if (j > 0 && j < 11) {
                if (queries[j-1][0] == 0) queries[j-1][0] = i;
            }
        }
        i++;
        strcpy(correct_output_file,argv[3]);
        sprintf(output_file, "/command%d_output.txt", i);
        strcat(correct_output_file,output_file);
    }
    for (j=0; j<10; j++) {
        printf("Query %2d total duration: %.6f\n",j+1,qTime[j+1]);
        if (queries[j][0] == 0)
            printf("Query %2d passed the tests ........... (%3.0f/%3.0f %3.0f%%) ✅\n", j+1, queries[j][1], queries[j][2], (queries[j][2] == 0) ? 100 : (queries[j][1] / queries[j][2]) * 100);
        else {
            printf("Query %2d failed the tests ........... (%3.0f/%3.0f %3.0f%%) ❌\n", j+1, queries[j][1], queries[j][2], (queries[j][2] == 0) ? 100 : (queries[j][1] / queries[j][2]) * 100);
            printf("The first error is in command %d...\n",(int)queries[j][0]);
        }
    }
    free(correct_output_file);
    free(output_file);
    free(our_output_file);
    free(command);
    fclose(commands_file);
    free(commands_time);
    printf("\nElapsed time: %4.2f seconds\n", elapsed);
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage: %4.2f MB\n", ((float) r_usage.ru_maxrss) / 1e3);
    }
    else printf("Error: The second provided directory path does not match any existing directory.\n");
    }
    else printf("Error: The provided file path does not match any existing file.\n");
    }
    else printf("Error: The first provided directory path is not valid for the dataset.\n");
    }
    else printf("Error: The program requires exactly 4 arguments.\n");
    return 0;
}