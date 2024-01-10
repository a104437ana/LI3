#include "parser.h"
#include <time.h>
#include <sys/resource.h>

/* A função parse_file lê um ficheiro de entrada CSV e efetua o seu parsing genérico. Esta função recebe o caminho absoluto para o ficheiro de entrada CSV
e o caminho relativo para o ficheiro de erros. Primeiro, verificamos se o ficheiro de entrada CSV existe. Depois com o caminho para o ficheiro de erros,
conseguimos identificar o tipo de ficheiro. Dependendo do tipo de ficheiro, criamos uma lista com tamanho adequado, para guardar apontadores. Depois iremos
abrir o ficheiro para o poder ler. Primeiro lemos a primeira linha onde se encontra o header (o cabeçalho). Iremos colocar o header no ficheiro de erros.
Depois iremos ler as próximas linhas. A cada linha que lemos, iremos pegar nela e dividi-la em várias partes. Cada parte terá um apontador que será guardado 
na lista criada no início da função. Depois, utilizando as várias partes da linha, iremos verificar se uma determinada identidade (que depende do tipo de ficheiro) 
é válida. Se for iremos transformar todas estas strings num tipo adequado e passar esses parametros para a estrutura de dados. Se for inválido, então iremos 
pegar na linha não modificada e iremos acrescenta-la ao ficheiro de erros. Por fim, libertamos a memória alocada e fechamos o ficheiro. */
void parse_file (char* file_path, char* error_file_path, Catalogs *catalogs, PassengersCounter* passengers_counter) {
    if (exist_file(file_path)) {
        char type_file = error_file_path[11];
        int size;
        switch (type_file) {
            case 'r': size = 13; //reservations
                      break;
            case 'p': size = 2; //passengers
                      break;
            default: size = 12; //others
                     break;
        }
        char **token = malloc(sizeof(char*)*size);
        FILE *file;
        file = fopen(file_path,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            add_invalid_line_to_error_file(error_file_path,line);
            while((read = getline(&line,&n,file)) != -1) {
                int size_line = strlen(line) + 1;
                char* line_modified = malloc(size_line);
                strcpy(line_modified,line);
                char *line_pointer = line_modified;
                for (int i = 0; i < size; i++) {
                    token[i] = strsep(&line_pointer,";");
                }
                switch (type_file) {
                    //users
                    case 'u' : remove_new_line(token[11]);
                               //              id      name     email    phone_n  birth    gender   passport country  address  ac_creat pay_m     ac_status
                               if (valid_user(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[11])) {
                                    int gender = 0;
                                    int accountStatus = 0;
                                    if (token[5][0] == 'F' || token[5][0] == 'f') gender = 1;
                                    if (token[11][0] == 'a' || token[11][0] == 'A') accountStatus = 1;
                                    addUser(token[0],token[1],gender,token[7],token[6],token[4],token[9],accountStatus,catalogs);
                               }
                               else add_invalid_line_to_error_file(error_file_path,line);
                               break;
                    //reservations                    id      id_user  id_hotel h_name   h_stars  cityTax  address  begin    end      pricePN  inc_break userClass
                    case 'r' : if (valid_reservation(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[12],catalogs)) {
                                    int cityTax = string_to_int(token[5]);
                                    int pricePerNight = atoi(token[9]);
                                    int includesBreakfast = 0;
                                    char hotelStars = token[4][0];
                                    char userClassification = token[12][0];
                                    if (token[10][0] == 't' || token[10][0] == 'T' || token[10][0] == '1') includesBreakfast = 1;
                                    addHotel(token[2],token[3],hotelStars,cityTax,userClassification,token[0],catalogs);
                                    addReservation(token[0],token[1],token[2],token[7],token[8],pricePerNight,includesBreakfast,userClassification,catalogs);
                               }
                               else add_invalid_line_to_error_file(error_file_path,line);
                               break;
                    //flights                   id       airline  airplane t_seats  origin   dest     s_depart s_arriv  r_depart r_arriv  pilot     copilot
                    case 'f' : if (valid_flight(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[11],passengers_counter)) {
                                    for(int w = 0; w<3; w++) {
                                        if (token[4][w] >= 97 && token[4][w] <= 122) token[4][w] -= 32;
                                    }
                                    int delay = addFlight(token[0],token[1],token[2],token[4],token[5],token[6],token[7],token[8],token[9],catalogs);
                                    addAirport(delay,token[4],token[0],catalogs);
                               }
                               else add_invalid_line_to_error_file(error_file_path,line);
                               break;
                    //passengers
                    case 'p' : remove_new_line(token[1]);
                               if (valid_passenger(token[0],token[1],catalogs)) {
                                    addPassenger(token[0], token[1], catalogs);
                               }
                               else add_invalid_line_to_error_file(error_file_path,line);
                               break;
                }
                free(line_modified);
            }
        }
        free(line);
        fclose(file);
        free(token);
    }
}

/* A função parse_all_files lê todos os ficheiros de entrada CSV e efetua o seu parsing. Para cada ficheiro diferente, criamos o caminho 
absoluto para o ficheiro de entrada CSV e criamos o caminho relativo para o ficheiro de erros. Para além disso, nesta função é criada uma 
hashtable com os números de passageiros por id de voo e é chamada uma função que contará o número de passageiros por voo. Os resultados desta
função serão usados para verificar se os voos são válidos e para assim sabermos se devemos guardar o voo na estrutura de dados ou se devemos 
coloca-lo no ficheiro de erros. Após a utilização destes resultados para validar os voos, destruimos a hashtable. Para efetivamente ler e
fazer o parsing de cada ficheiro, chamamos a função parse_file.*/
void parse_all_files (char* directory, Catalogs *catalogs) {

        //inicialização de variáveis para medição de tempo
        struct timespec start, end, interm;
        double use, res, passc, fli, pass, des, total;
        clock_gettime(CLOCK_REALTIME, &start);

    PassengersCounter* passengers_counter = createPassengersCounter(PASSENGERS_PER_FLIGHT_HASHTABLE_INI_SIZE);

    int size = strlen(directory) + 18;
    char* file_path = malloc(size);
    char* error_file_path = malloc(35);

    strcpy(file_path,directory);
    strcat(file_path,"/users.csv");
    strcpy(error_file_path,"Resultados/users_errors.csv");
    parse_file(file_path,error_file_path,catalogs,passengers_counter);
        clock_gettime(CLOCK_REALTIME, &interm);
        use = (interm.tv_sec - start.tv_sec) + (interm.tv_nsec - start.tv_nsec) / 1e9;

    strcpy(file_path,directory);
    strcat(file_path,"/reservations.csv");
    strcpy(error_file_path,"Resultados/reservations_errors.csv");
    parse_file(file_path,error_file_path,catalogs,passengers_counter);
        clock_gettime(CLOCK_REALTIME, &end);
        res = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;

    count_passengers(directory,catalogs,passengers_counter);
        clock_gettime(CLOCK_REALTIME, &interm);
        passc = (interm.tv_sec - end.tv_sec) + (interm.tv_nsec - end.tv_nsec) / 1e9;

    strcpy(file_path,directory);
    strcat(file_path,"/flights.csv");
    strcpy(error_file_path,"Resultados/flights_errors.csv");
    parse_file(file_path,error_file_path,catalogs,passengers_counter);
        clock_gettime(CLOCK_REALTIME, &end);
        fli = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;

    strcpy(file_path,directory);
    strcat(file_path,"/passengers.csv");
    strcpy(error_file_path,"Resultados/passengers_errors.csv");
    parse_file(file_path,error_file_path,catalogs,passengers_counter);
        clock_gettime(CLOCK_REALTIME, &interm);
        pass = (interm.tv_sec - end.tv_sec) + (interm.tv_nsec - end.tv_nsec) / 1e9;

    free(file_path);
    free(error_file_path);

    destroyPassengersCounter(passengers_counter);
        clock_gettime(CLOCK_REALTIME, &end);
        des = (end.tv_sec - interm.tv_sec) + (end.tv_nsec - interm.tv_nsec) / 1e9;

        // Tamanho dos dados processados dataset normal
        // use = 10001
        // fli = 1000
        // pass = 81204
        // res = 40953

        // Dataset large clean
        // use = 990134 / 940529
        // fli = 179946
        // pass = ?
        // res = ?

        //imprime tempo de execução
        total = use + res + passc + fli + pass + des; total++;
        /*
        printf(" Parser:\n");
        printf("  user:\t\t %.6f seconds (%5.2f%%)\n", use, (use/total)*100);
        printf("  reservation:\t %.6f seconds (%5.2f%%)\n", res, (res/total)*100);
        printf("  passenger_c:\t %.6f seconds (%5.2f%%)\n", passc, (passc/total)*100);
        printf("  flight:\t %.6f seconds (%5.2f%%)\n", fli, (fli/total)*100);
        printf("  passenger:\t %.6f seconds (%5.2f%%)\n", pass, (pass/total)*100);
        printf("  destroy:\t %.6f seconds (%5.2f%%)\n", des, (des/total)*100);
        printf("  total:\t %.6f seconds\n", total);
        */
 }