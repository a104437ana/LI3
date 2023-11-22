#include "parser.h"

/* A função parse_users_file lê o ficheiro users.csv e faz o parsing. Esta função começa por construir o caminho para o ficheiro
users.csv. Para isso, junta a string dada, que nos indica o caminho absoluto para a diretoria onde o ficheiro se encontra, com a 
string "/users.csv", para assim obtermos o caminho absoluto para o ficheiro. Depois se este ficheiro realmente existir, iremos 
abrir o ficheiro para o poder ler. Primeiro lemos a primeira linha onde se encontra o header (o cabeçalho). Iremos colocar o 
header no ficheiro de erros, cujo o caminho relativo é "Resultados/users_errors.csv". Depois iremos ler as próximas linhas. A cada
linha que lemos, iremos pegar nela e dividi-la em várias partes (id, nome, etc...). Com todas estas strings iremos verificar se o
utilizador é válido. Se for iremos transformar todas estas strings num tipo adequado e passar esses parametros para a estrutura de
dados, neste caso para o catálogo de utilizadores válidos. Se o utilizador for inválido, então iremos pegar na linha não modificada
e iremos acrescenta-la ao ficheiro de erros. Por fim, libertamos a memória alocada e fechamos o ficheiro. */
void parse_users_file (char* directory,UsersManager *usersCatalog) {
    char* file_path = malloc(strlen(directory) + strlen("/users.csv") + 1);
    strcpy(file_path, directory);
    strcat(file_path,"/users.csv");
    if (exist_file(file_path)) {
        FILE *file;
        file = fopen(file_path,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            char* file_path_errors = malloc(strlen("Resultados/users_errors.csv") + 1);
            strcpy(file_path_errors,"Resultados/users_errors.csv");
            add_invalid_line_to_error_file(file_path_errors,line);
            while((read = getline(&line,&n,file)) != -1) {
                char* line_modified = malloc(strlen(line) + 1);
                strcpy(line_modified,line);
                char *line_pointer = line_modified;
                char* token = strsep(&line_pointer,";"); //id user
                char* id_user = malloc(strlen(token) + 1);
                strcpy(id_user,token);
                token = strsep(&line_pointer,";"); //name
                char* name = malloc(strlen(token) + 1);
                strcpy(name,token);
                token = strsep(&line_pointer,";"); //email
                char* email = malloc(strlen(token) + 1);
                strcpy(email,token);
                token = strsep(&line_pointer,";"); //phone number
                char* phone_number = malloc(strlen(token) + 1);
                strcpy(phone_number,token);
                token = strsep(&line_pointer,";"); //birth date
                char* birth_date = malloc(strlen(token) + 1);
                strcpy(birth_date,token);
                token = strsep(&line_pointer,";"); //sex
                char* sex = malloc(strlen(token) + 1);
                strcpy(sex,token);
                token = strsep(&line_pointer,";"); //passporte
                char* passport = malloc(strlen(token) + 1);
                strcpy(passport,token);
                token = strsep(&line_pointer,";"); //country code
                char* country_code = malloc(strlen(token) + 1);
                strcpy(country_code,token);
                token = strsep(&line_pointer,";"); //address
                char* address = malloc(strlen(token) + 1);
                strcpy(address,token);
                token = strsep(&line_pointer,";"); //account creation
                char* account_creation = malloc(strlen(token) + 1);
                strcpy(account_creation,token);
                token = strsep(&line_pointer,";"); //pay method
                char* pay_method = malloc(strlen(token) + 1);
                strcpy(pay_method,token);
                token = strsep(&line_pointer,";"); //account status
                char* account_status = malloc(strlen(token) + 1);
                strcpy(account_status,token);
                remove_new_line(account_status);
                if (valid_user(id_user,name,email,phone_number,birth_date,sex,passport,country_code,address,account_creation,pay_method,account_status)) {
                    int gender = 0;
                    if (sex[0] == 'F' || sex[0] == 'f') gender = 1;
                    Date* birth = string_to_date(birth_date);
                    Date* accountCreation = string_to_date(account_creation);
                    int accountStatus = 0;
                    if (account_status[0] == 'a' || account_status[0] == 'A') {
                        accountStatus = 1;
                    }
                    User* user = createUser(id_user,name,gender,country_code,passport,birth,accountCreation,accountStatus);
                    addUserToCatalog(usersCatalog,user,hashFunction(id_user));
                    if (accountStatus) addUserToCatalogList(usersCatalog,user);
                }
                else {
                    add_invalid_line_to_error_file(file_path_errors,line);
                }
                free(line_modified);
                free(id_user); 
                free(name); 
                free(email); 
                free(phone_number); 
                free(birth_date); 
                free(sex);
                free(passport); 
                free(country_code); 
                free(address); 
                free(account_creation);
                free(pay_method); 
                free(account_status);
            }
            free(file_path_errors);
        }
        free(line);
        fclose(file);
    }
    free(file_path);
}

/* A função parse_reservations_file lê o ficheiro reservations.csv e faz o parsing. Esta função começa por construir o caminho para 
o ficheiro reservations.csv. Para isso, junta a string dada, que nos indica o caminho absoluto para a diretoria onde o ficheiro se 
encontra, com a string "/reservations.csv", para assim obtermos o caminho absoluto para o ficheiro. Depois se este ficheiro realmente 
existir, iremos abrir o ficheiro para o poder ler. Primeiro lemos a primeira linha onde se encontra o header (o cabeçalho). Iremos colocar
o header no ficheiro de erros, cujo o caminho relativo é "Resultados/reservations_errors.csv". Depois iremos ler as próximas linhas. A cada
linha que lemos, iremos pegar nela e dividi-la em várias partes (id, nome do hotel, etc...). Com todas estas strings iremos verificar se a
reserva é válida. Se for iremos transformar todas estas strings num tipo adequado e passar esses parametros para a estrutura de dados, neste
caso para o catálogo de reservas válidas. Se a reserva for inválida, então iremos pegar na linha não modificada e iremos acrescenta-la ao
ficheiro de erros. Por fim, libertamos a memória alocada e fechamos o ficheiro.*/
void parse_reservations_file (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog) {
    char* file_path = malloc(strlen(directory) + strlen("/reservations.csv") + 1);
    strcpy(file_path, directory);
    strcat(file_path,"/reservations.csv");
    if (exist_file(file_path)) {
        FILE *file;
        file = fopen(file_path,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            char* file_path_errors = malloc(strlen("Resultados/reservations_errors.csv") + 1);
            strcpy(file_path_errors,"Resultados/reservations_errors.csv");
            add_invalid_line_to_error_file(file_path_errors,line);
            while((read = getline(&line,&n,file)) != -1) {
                char* line_modified = malloc(strlen(line) + 1);
                strcpy(line_modified,line);
                char* line_pointer = line_modified;
                char* token = strsep(&line_pointer,";"); //id reservation
                char* id_reservation = malloc(strlen(token) + 1);
                strcpy(id_reservation,token);
                token = strsep(&line_pointer,";"); //id user
                char* id_user = malloc(strlen(token) + 1);
                strcpy(id_user,token);
                token = strsep(&line_pointer,";"); //id hotel
                char* id_hotel = malloc(strlen(token) + 1);
                strcpy(id_hotel,token);
                token = strsep(&line_pointer,";"); //hotel name
                char* hotel_name = malloc(strlen(token) + 1);
                strcpy(hotel_name,token);
                token = strsep(&line_pointer,";"); //hotel stars
                char* hotel_stars = malloc(strlen(token) + 1);
                strcpy(hotel_stars,token);
                token = strsep(&line_pointer,";"); //city tax
                char* city_tax = malloc(strlen(token) + 1);
                strcpy(city_tax,token);
                token = strsep(&line_pointer,";"); //address
                char* address = malloc(strlen(token) + 1);
                strcpy(address,token);
                token = strsep(&line_pointer,";"); //begin date
                char* begin_date = malloc(strlen(token) + 1);
                strcpy(begin_date,token);
                token = strsep(&line_pointer,";"); //end date
                char* end_date = malloc(strlen(token) + 1);
                strcpy(end_date,token);
                token = strsep(&line_pointer,";"); //price per night
                char* price_per_night = malloc(strlen(token) + 1);
                strcpy(price_per_night,token);
                token = strsep(&line_pointer,";"); //includes breakfast
                char* includes_breakfast = malloc(strlen(token) + 1);
                strcpy(includes_breakfast,token);
                token = strsep(&line_pointer,";"); //room details
                token = strsep(&line_pointer,";"); //rating
                char* rating = malloc(strlen(token) + 1);
                strcpy(rating,token);
                //comment
                if (valid_reservation(id_reservation,id_user,id_hotel,hotel_name,hotel_stars,city_tax,address,begin_date,end_date,price_per_night,includes_breakfast,rating,usersCatalog)) {
                    int cityTax = string_to_int(city_tax);
                    int pricePerNight = atoi(price_per_night);
                    int includesBreakfast = 0;
                    if (includes_breakfast[0] == 't' || includes_breakfast[0] == 'T' || includes_breakfast[0] == '1') includesBreakfast = 1;
                    Date* begin = string_to_date(begin_date);
                    Date* end = string_to_date(end_date);
                    Reservation* reservation = createReservation(id_reservation,id_user,id_hotel,hotel_name,hotel_stars[0],cityTax,begin,end,pricePerNight,includesBreakfast,rating[0],getHashtableHotelsCatalog(hotelsCatalog));
                    addReservToCatalog(reservationsCatalog,reservation,hashFunction(id_reservation),hotelsCatalog,usersCatalog);
                }
                else add_invalid_line_to_error_file(file_path_errors,line);
                free(line_modified);
                free(id_reservation);
                free(id_user);
                free(id_hotel);
                free(hotel_name);
                free(hotel_stars);
                free(city_tax);
                free(address);
                free(begin_date);
                free(end_date);
                free(price_per_night);
                free(includes_breakfast);
                free(rating);
            }
            free(file_path_errors);
        }
        free(line);
        fclose(file);
    }
    free(file_path);
}

/* A função parse_flights_file lê o ficheiro flights.csv e faz o parsing. Esta função começa por construir o caminho para 
o ficheiro flights.csv. Para isso, junta a string dada, que nos indica o caminho absoluto para a diretoria onde o ficheiro se 
encontra, com a string "/flights.csv", para assim obtermos o caminho absoluto para o ficheiro. Depois se este ficheiro realmente 
existir, iremos abrir o ficheiro para o poder ler. Primeiro lemos a primeira linha onde se encontra o header (o cabeçalho). Iremos colocar
o header no ficheiro de erros, cujo o caminho relativo é "Resultados/flights_errors.csv". Depois iremos ler as próximas linhas. A cada
linha que lemos, iremos pegar nela e dividi-la em várias partes (id, aeroporto, etc...). Com todas estas strings iremos verificar se o
voo é válido. Se for iremos transformar todas estas strings num tipo adequado e passar esses parametros para a estrutura de dados, neste
caso para o catálogo de voos válidos. Se o voo for inválido, então iremos pegar na linha não modificada e iremos acrescenta-la ao
ficheiro de erros. Por fim, libertamos a memória alocada e fechamos o ficheiro.*/
void parse_flights_file (char* directory, UsersManager* usersCatalog, FlightsManager* flightsCatalog, PassengersCounter* passengers_counter) {
    char* file_path = malloc(strlen(directory) + strlen("/flights.csv") + 1);
    strcpy(file_path, directory);
    strcat(file_path,"/flights.csv");
    if (exist_file(file_path)) {
        FILE *file;
        file = fopen(file_path,"r"); //abertura do ficheiro em modo de leitura. O ficheiro deve existir.
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            char* file_path_errors = malloc(strlen("Resultados/flights_errors.csv") + 1);
            strcpy(file_path_errors,"Resultados/flights_errors.csv");
            add_invalid_line_to_error_file(file_path_errors,line);
            while((read = getline(&line,&n,file)) != -1) {
                char* line_modified = malloc(strlen(line) + 1);
                strcpy(line_modified,line);
                char* line_pointer = line_modified;
                char* token = strsep(&line_pointer,";"); //id fligth
                char* id_flight = malloc(strlen(token) + 1);
                strcpy(id_flight,token);
                token = strsep(&line_pointer,";"); //airline
                char* airline = malloc(strlen(token) + 1);
                strcpy(airline,token);
                token = strsep(&line_pointer,";"); //plane model
                char* plane_model = malloc(strlen(token) + 1);
                strcpy(plane_model,token);
                token = strsep(&line_pointer,";"); //total seats
                char* total_seats = malloc(strlen(token) + 1);
                strcpy(total_seats,token);
                token = strsep(&line_pointer,";"); //origin
                char* origin = malloc(strlen(token) + 1);
                strcpy(origin,token);
                token = strsep(&line_pointer,";"); //destination
                char* destination = malloc(strlen(token) + 1);
                strcpy(destination,token);
                token = strsep(&line_pointer,";"); //schedule departure date
                char* schedule_departure_date = malloc(strlen(token) + 1);
                strcpy(schedule_departure_date,token);
                token = strsep(&line_pointer,";"); //schedule arrival date
                char* schedule_arrival_date = malloc(strlen(token) + 1);
                strcpy(schedule_arrival_date,token);
                token = strsep(&line_pointer,";"); //real departure date
                char* real_departure_date = malloc(strlen(token) + 1);
                strcpy(real_departure_date,token);
                token = strsep(&line_pointer,";"); //real arrival date
                char* real_arrival_date = malloc(strlen(token) + 1);
                strcpy(real_arrival_date,token);
                token = strsep(&line_pointer,";"); //pilot
                char* pilot = malloc(strlen(token) + 1);
                strcpy(pilot,token);
                token = strsep(&line_pointer,";"); //copilot
                char* copilot = malloc(strlen(token) + 1);
                strcpy(copilot,token);
                //notes
                if (valid_flight(id_flight,airline,plane_model,total_seats,origin,destination,schedule_departure_date,schedule_arrival_date,real_departure_date,real_arrival_date,pilot,copilot,passengers_counter)) {
                    Date* scheduleDeparture = string_to_date_hours(schedule_departure_date);
                    Date* scheduleArrival = string_to_date_hours(schedule_arrival_date);
                    Date* realDeparture = string_to_date_hours(real_departure_date);
                    Date* realArrival = string_to_date_hours(real_arrival_date);
                    Flight *flight = createFlight(id_flight,airline,plane_model,origin,destination,scheduleDeparture,scheduleArrival,realDeparture,realArrival);
                    addFlightToCatalog(flightsCatalog,flight,hashFunction(id_flight));
                }
                else add_invalid_line_to_error_file(file_path_errors,line);
                free(line_modified);
                free(id_flight);
                free(airline);
                free(plane_model);
                free(total_seats);
                free(origin);
                free(destination);
                free(schedule_departure_date);
                free(schedule_arrival_date);
                free(real_departure_date);
                free(real_arrival_date);
                free(pilot);
                free(copilot);
            }
            free(file_path_errors);
        }
        free(line);
        fclose(file);
    }
    free(file_path);
}


/* A função parse_passengers_file lê o ficheiro passengers.csv e faz o parsing. Esta função começa por construir o caminho para 
o ficheiro passengers.csv. Para isso, junta a string dada, que nos indica o caminho absoluto para a diretoria onde o ficheiro se 
encontra, com a string "/passengers.csv", para assim obtermos o caminho absoluto para o ficheiro. Depois se este ficheiro realmente 
existir, iremos abrir o ficheiro para o poder ler. Primeiro lemos a primeira linha onde se encontra o header (o cabeçalho). Iremos colocar
o header no ficheiro de erros, cujo o caminho relativo é "Resultados/flights_errors.csv". Depois iremos ler as próximas linhas. A cada
linha que lemos, iremos pegar nela e dividi-la em várias partes (id do utilizador e id do voo). Com todas estas strings iremos verificar se o
passageiro é válido. Se for iremos transformar todas estas strings num tipo adequado e passar esses parametros para a estrutura de dados, neste
caso para o catálogo de passageiros válidos. Se o passageiro for inválido, então iremos pegar na linha não modificada e iremos acrescenta-la ao
ficheiro de erros. Por fim, libertamos a memória alocada e fechamos o ficheiro.*/
void parse_passengers_file (char* directory, UsersManager* usersCatalog, FlightsManager* flightsCatalog) {
    char* file_path = malloc(strlen(directory) + strlen("/passengers.csv") + 1);
    strcpy(file_path, directory);
    strcat(file_path,"/passengers.csv");
    if (exist_file(file_path)) {
        FILE *file;
        file = fopen(file_path,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            char* file_path_errors = malloc(strlen("Resultados/passengers_errors.csv") + 1);
            strcpy(file_path_errors,"Resultados/passengers_errors.csv");
            add_invalid_line_to_error_file(file_path_errors,line);
            while((read = getline(&line,&n,file)) != -1) {
                char* line_modified = malloc(strlen(line) + 1);
                strcpy(line_modified,line);
                char* line_pointer = line_modified;
                char* token = strsep(&line_pointer,";"); //id flight
                char* id_flight = malloc(strlen(token) + 1);
                strcpy(id_flight,token);
                token = strsep(&line_pointer,";"); //id user
                char* id_user = malloc(strlen(token) + 1);
                strcpy(id_user,token);
                remove_new_line(id_user);
                if (valid_passenger(id_flight,id_user,usersCatalog,flightsCatalog)) {
                    addPassengerToCatalog(flightsCatalog,hashFunction(id_flight),usersCatalog,hashFunction(id_user),id_flight,id_user);
                }
                else add_invalid_line_to_error_file(file_path_errors,line);
                free(line_modified);
                free(id_flight);
                free(id_user);
            }
            free(file_path_errors);
        }
        free(line);
        fclose(file);
    }
    free(file_path);
}

/* A função parse_all_files lê todos os ficheiros de entrada CSV e efetua um parsing genérico. Para além disso, nesta função é criada uma hashtable
com os números de passageiros por id de voo e é chamada uma função que contará o número de passageiros por voo. Os resultados desta função
serão usados para verificar se os voos são válidos e para assim sabermos se devemos guardar o voo na estrutura de dados ou se devemos coloca-
-lo no ficheiro de erros. Após a utilização destes resultados para validar os voos, destruimos a hashtable.*/
void parse_all_files (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog, FlightsManager* flightsCatalog) {
    parse_users_file(directory,usersCatalog);
    parse_reservations_file(directory,usersCatalog,reservationsCatalog,hotelsCatalog);
    PassengersCounter* passengers_counter = createPassengersCounter(PASSENGERS_PER_FLIGHT_HASHTABLE_INI_SIZE);
    count_passengers(directory,usersCatalog,passengers_counter);
    parse_flights_file(directory,usersCatalog,flightsCatalog,passengers_counter);
    destroyPassengersCounter(passengers_counter);
    parse_passengers_file(directory,usersCatalog,flightsCatalog);
}