#include "parser.h"

/* A função parse_file lê um ficheiro de entrada CSV e efetua o seu parsing genérico. Esta função recebe o caminho absoluto para o ficheiro de entrada CSV
e o caminho relativo para o ficheiro de erros. Primeiro, verificamos se o ficheiro de entrada CSV existe. Depois com o caminho para o ficheiro de erros,
conseguimos identificar o tipo de ficheiro. Dependendo do tipo de ficheiro, criamos uma lista com tamanho adequado, para guardar apontadores. Depois iremos
abrir o ficheiro para o poder ler. Primeiro lemos a primeira linha onde se encontra o header (o cabeçalho). Iremos colocar o header no ficheiro de erros.
Depois iremos ler as próximas linhas. A cada linha que lemos, iremos pegar nela e dividi-la em várias partes. Cada parte terá um apontador que será guardado 
na lista criada no início da função. Depois, utilizando as várias partes da linha, iremos verificar se uma determinada identidade (que depende do tipo de ficheiro) 
é válida. Se for iremos transformar todas estas strings num tipo adequado e passar esses parametros para a estrutura de dados. Se for inválido, então iremos 
pegar na linha não modificada e iremos acrescenta-la ao ficheiro de erros. Por fim, libertamos a memória alocada e fechamos o ficheiro. */
void parse_file (char* file_path, char* error_file_path, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog, FlightsManager* flightsCatalog, PassengersCounter* passengers_counter) {
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
                char* line_modified = malloc(strlen(line) + 1);
                strcpy(line_modified,line);
                char *line_pointer = line_modified;
                int i = -1;
                do {
                    token[++i] = strsep(&line_pointer,";");
                } while (i<size-1);
                switch (type_file) {
                    //users
                    case 'u' : remove_new_line(token[11]);
                               if (valid_user(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[11])) {
                                    int gender = 0;
                                    if (token[5][0] == 'F' || token[5][0] == 'f') gender = 1;
                                    Date* birth = string_to_date(token[4]);
                                    Date* accountCreation = string_to_date(token[9]);
                                    int accountStatus = 0;
                                    if (token[11][0] == 'a' || token[11][0] == 'A') {
                                        accountStatus = 1;
                                    }
                                    User* user = createUser(token[0],token[1],gender,token[7],token[6],birth,accountCreation,accountStatus);
                                    addUserToCatalog(usersCatalog,user,hashFunction(token[0]));
                                    if (accountStatus) addUserToCatalogList(usersCatalog,user);
                               }
                               else add_invalid_line_to_error_file(error_file_path,line);
                               break;
                    //reservations
                    case 'r' : if (valid_reservation(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[12],usersCatalog)) {
                                    int cityTax = string_to_int(token[5]);
                                    int pricePerNight = atoi(token[9]);
                                    int includesBreakfast = 0;
                                    if (token[10][0] == 't' || token[10][0] == 'T' || token[10][0] == '1') includesBreakfast = 1;
                                    Date* begin = string_to_date(token[7]);
                                    Date* end = string_to_date(token[8]);
                                    Reservation* reservation = createReservation(token[0],token[1],token[2],token[3],token[4][0],cityTax,begin,end,pricePerNight,includesBreakfast,token[12][0],getHashtableHotelsCatalog(hotelsCatalog));
                                    addReservToCatalog(reservationsCatalog,reservation,hashFunction(token[0]),hotelsCatalog,usersCatalog);
                               }
                               else add_invalid_line_to_error_file(error_file_path,line);
                               break;
                    //flights
                    case 'f' : if (valid_flight(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[11],passengers_counter)) {   
                                    Date* scheduleDeparture = string_to_date_hours(token[6]);
                                    Date* scheduleArrival = string_to_date_hours(token[7]);
                                    Date* realDeparture = string_to_date_hours(token[8]);
                                    Date* realArrival = string_to_date_hours(token[9]);
                                    Flight *flight = createFlight(token[0],token[1],token[2],token[4],token[5],scheduleDeparture,scheduleArrival,realDeparture,realArrival);
                                    addFlightToCatalog(flightsCatalog,flight,hashFunction(token[0]));
                               }
                               else add_invalid_line_to_error_file(error_file_path,line);
                               break;
                    //passengers
                    case 'p' : remove_new_line(token[1]);
                               if (valid_passenger(token[0],token[1],usersCatalog,flightsCatalog)) {
                                    addPassengerToCatalog(flightsCatalog,hashFunction(token[0]),usersCatalog,hashFunction(token[1]),token[0],token[1]);
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
void parse_all_files (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog, FlightsManager* flightsCatalog) {
    PassengersCounter* passengers_counter = createPassengersCounter(PASSENGERS_PER_FLIGHT_HASHTABLE_INI_SIZE);
    
    char* file_path = malloc(strlen(directory) + strlen("/reservations.csv") + 1);
    char* error_file_path = malloc(strlen("Resultados/reservations_errors.csv") + 1);

    strcpy(file_path,directory);
    strcat(file_path,"/users.csv");
    strcpy(error_file_path,"Resultados/users_errors.csv");
    parse_file(file_path,error_file_path,usersCatalog,reservationsCatalog,hotelsCatalog,flightsCatalog,passengers_counter);

    strcpy(file_path,directory);
    strcat(file_path,"/reservations.csv");
    strcpy(error_file_path,"Resultados/reservations_errors.csv");
    parse_file(file_path,error_file_path,usersCatalog,reservationsCatalog,hotelsCatalog,flightsCatalog,passengers_counter);

    count_passengers(directory,usersCatalog,passengers_counter);

    strcpy(file_path,directory);
    strcat(file_path,"/flights.csv");
    strcpy(error_file_path,"Resultados/flights_errors.csv");
    parse_file(file_path,error_file_path,usersCatalog,reservationsCatalog,hotelsCatalog,flightsCatalog,passengers_counter);

    strcpy(file_path,directory);
    strcat(file_path,"/passengers.csv");
    strcpy(error_file_path,"Resultados/passengers_errors.csv");
    parse_file(file_path,error_file_path,usersCatalog,reservationsCatalog,hotelsCatalog,flightsCatalog,passengers_counter);

    free(file_path);
    free(error_file_path);

    destroyPassengersCounter(passengers_counter);
}