#include "parser.h"

enum Type_file {
    users,
    flights,
    passengers,
    reservations
};

//Verifica se um ficheiro existe ou não, dado um path para o ficheiro
int exist_file (char* path_file) {
    int exist = 0;
	FILE *file;
	file = fopen(path_file,"r");
	if (file != NULL) {
		exist = 1;
        fclose(file);
	}
    return exist;
}

//Transforma uma string num tipo Date
Date* string_to_date (char* string) {
    int year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    int month = (string[5] - '0') * 10 + (string[6] - '0');
    int day = (string[8] - '0') * 10 + (string[9] - '0');
    Date* date = createDate(day,month,year);
    /*Date* date;
    date.year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    date.month = (string[5] - '0') * 10 + (string[6] - '0');
    date.day = (string[8] - '0') * 10 + (string[9] - '0');
    int hasHours = 0;
    if (strlen(string) == 19) {
        hasHours = 1;
        date.hour->hours = (string[11] -'0') * 10 + (string[12] - '0');
        date.hour->minutes = (string[14] - '0') * 10 + (string[15] - '0');
        date.hour->seconds = (string[17] - '0') * 10 + (string[18] - '0');
    }
    date.hasHours = hasHours;*/
    return date;
}

//Constroi o path para o ficheiro e faz o parsing generico desse ficheiro
void parse_file (char* path_directory, enum Type_file type_file, UsersManager* user_catalog, ReservationsManager * reservation_catalog, HotelsManager *hotel_catalog) {
    char* name_file = NULL;
    switch (type_file) {
        case 0 : name_file = malloc(strlen("/users.csv") + 1);
                 strcpy(name_file,"/users.csv");
                 break;
        case 1 : name_file = malloc(strlen("/flights.csv") + 1);
                 strcpy(name_file,"/flights.csv");
                 break;
        case 2 : name_file = malloc(strlen("/passengers.csv") + 1);
                 strcpy(name_file,"/passengers.csv");
                 break;
        case 3 : name_file = malloc(strlen("/reservations.csv") + 1);
                 strcpy(name_file,"/reservations.csv");
                 break;
    }
    char* path_file = malloc(strlen(path_directory) + strlen(name_file) + 1);
    strcpy(path_file, path_directory);
    strncat(path_file, name_file,strlen("/reservations.csv") + 1);
    if (exist_file(path_file)) {
        FILE *file;
        file = fopen(path_file,"r");
        char* line = NULL;
        size_t n;
        ssize_t read;
        switch (type_file) {
            case 0 : if ((read = getline(&line,&n,file)) != -1) {
                     add_invalid_line_to_error_file(users,line);
                     while((read = getline(&line,&n,file)) != -1) {
                        char *line2 = line;
                        char* total_line = malloc(strlen(line2) + 1);
                        strcpy(total_line,line2);
                        char* token = strsep(&line2,";"); //id user
                        char* id_user = malloc(strlen(token) + 1);
                        strcpy(id_user,token);
                        token = strsep(&line2,";"); //name
                        char* name = malloc(strlen(token) + 1);
                        strcpy(name,token);
                        token = strsep(&line2,";"); //email
                        char* email = malloc(strlen(token) + 1);
                        strcpy(email,token);
                        token = strsep(&line2,";"); //phone number
                        char* phone_number = malloc(strlen(token) + 1);
                        strcpy(phone_number,token);
                        token = strsep(&line2,";"); //birth date
                        char* birth_date = malloc(strlen(token) + 1);
                        strcpy(birth_date,token);
                        token = strsep(&line2,";"); //sex
                        char* sex = malloc(strlen(token) + 1);
                        strcpy(sex,token);
                        token = strsep(&line2,";"); //passporte
                        char* passport = malloc(strlen(token) + 1);
                        strcpy(passport,token);
                        token = strsep(&line2,";"); //country code
                        char* country_code = malloc(strlen(token) + 1);
                        strcpy(country_code,token);
                        token = strsep(&line2,";"); //address
                        char* address = malloc(strlen(token) + 1);
                        strcpy(address,token);
                        token = strsep(&line2,";"); //account creation
                        char* account_creation = malloc(strlen(token) + 1);
                        strcpy(account_creation,token);
                        token = strsep(&line2,";"); //pay method
                        char* pay_method = malloc(strlen(token) + 1);
                        strcpy(pay_method,token);
                        token = strsep(&line2,";"); //account status
                        char* account_status = malloc(strlen(token) + 1);
                        strcpy(account_status,token);
                        if (valid_user(id_user,name,email,phone_number,birth_date,sex,passport,country_code,address,account_creation,pay_method,account_status)) {
                            int gender = 0;
                            if (sex[0] == 'F' || sex[0] == 'f') gender = 1;
                            Date* birth = string_to_date(birth_date);
                            Date* accountCreation = string_to_date(account_creation);
                            User* user = createUser(id_user,name,gender,country_code,address,passport,birth,email,0,accountCreation,pay_method,account_status);
                            addUserToCatalog(user_catalog,user,hashFunction(id_user));
                        }
                        else {
                            add_invalid_line_to_error_file(users,total_line);
                        }
                        free(total_line);
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
                     }
                     break;
            case 1 : if ((read = getline(&line,&n,file)) != -1) {
                     add_invalid_line_to_error_file(flights,line);

                     while((read = getline(&line,&n,file)) != -1){
                        char* line2 = line;
                        char* total_line = malloc(strlen(line2) + 1);
                        strcpy(total_line,line2);
                        char* token = strsep(&line2,";"); //id fligth
                        char* id_flight = malloc(strlen(token) + 1);
                        strcpy(id_flight,token);
                        token = strsep(&line2,";"); //airline
                        char* airline = malloc(strlen(token) + 1);
                        strcpy(airline,token);
                        token = strsep(&line2,";"); //plane model
                        char* plane_model = malloc(strlen(token) + 1);
                        strcpy(plane_model,token);
                        token = strsep(&line2,";"); //total seats
                        char* total_seats = malloc(strlen(token) + 1);
                        strcpy(total_seats,token);
                        token = strsep(&line2,";"); //origin
                        char* origin = malloc(strlen(token) + 1);
                        strcpy(origin,token);
                        token = strsep(&line2,";"); //destination
                        char* destination = malloc(strlen(token) + 1);
                        strcpy(destination,token);
                        token = strsep(&line2,";"); //schedule departure date
                        char* schedule_departure_date = malloc(strlen(token) + 1);
                        strcpy(schedule_departure_date,token);
                        token = strsep(&line2,";"); //schedule arrival date
                        char* schedule_arrival_date = malloc(strlen(token) + 1);
                        strcpy(schedule_arrival_date,token);
                        token = strsep(&line2,";"); //real departure date
                        char* real_departure_date = malloc(strlen(token) + 1);
                        strcpy(real_departure_date,token);
                        token = strsep(&line2,";"); //real arrival date
                        char* real_arrival_date = malloc(strlen(token) + 1);
                        strcpy(real_arrival_date,token);
                        token = strsep(&line2,";"); //pilot
                        char* pilot = malloc(strlen(token) + 1);
                        strcpy(pilot,token);
                        token = strsep(&line2,";"); //copilot
                        char* copilot = malloc(strlen(token) + 1);
                        strcpy(copilot,token);
                        token = strsep(&line2,";"); //notes
                        if (valid_flight(id_flight,airline,plane_model,total_seats,origin,destination,schedule_departure_date,schedule_arrival_date,real_departure_date,real_arrival_date,pilot,copilot)) {

                        }
                        else add_invalid_line_to_error_file(flights,total_line);
                        free(total_line);
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
                     }
                     break;
            case 2 : if ((read = getline(&line,&n,file)) != -1) {
                     add_invalid_line_to_error_file(passengers,line);
                     while((read = getline(&line,&n,file)) != -1){
                        char* line2 = line;
                        char* total_line = malloc(strlen(line2) + 1);
                        strcpy(total_line,line2);
                        char* token = strsep(&line2,";"); //id flight
                        char* id_flight = malloc(strlen(token) + 1);
                        strcpy(id_flight,token);
                        token = strsep(&line2,";"); //id user
                        char* id_user = malloc(strlen(token) + 1);
                        strcpy(id_user,token);
                        if (existsUser(user_catalog,id_user)) add_invalid_line_to_error_file(passengers,total_line);
                        free(total_line);
                        free(id_flight);
                        free(id_user);
                     }
                     }
                     break;
            case 3 : if ((read = getline(&line,&n,file)) != -1) {
                     add_invalid_line_to_error_file(reservations,line);
                     while((read = getline(&line,&n,file)) != -1){
                        char* line2 = line;
                        char* total_line = malloc(strlen(line2) + 1);
                        strcpy(total_line,line2);
                        char* token = strsep(&line2,";"); //id reservation
                        char* id_reservation = malloc(strlen(token) + 1);
                        strcpy(id_reservation,token);
                        token = strsep(&line2,";"); //id user
                        char* id_user = malloc(strlen(token) + 1);
                        strcpy(id_user,token);
                        token = strsep(&line2,";"); //id hotel
                        char* id_hotel = malloc(strlen(token) + 1);
                        strcpy(id_hotel,token);
                        token = strsep(&line2,";"); //hotel name
                        char* hotel_name = malloc(strlen(token) + 1);
                        strcpy(hotel_name,token);
                        token = strsep(&line2,";"); //hotel stars
                        char* hotel_stars = malloc(strlen(token) + 1);
                        strcpy(hotel_stars,token);
                        token = strsep(&line2,";"); //city tax
                        char* city_tax = malloc(strlen(token) + 1);
                        strcpy(city_tax,token);
                        token = strsep(&line2,";"); //address
                        char* address = malloc(strlen(token) + 1);
                        strcpy(address,token);
                        token = strsep(&line2,";"); //begin date
                        char* begin_date = malloc(strlen(token) + 1);
                        strcpy(begin_date,token);
                        token = strsep(&line2,";"); //end date
                        char* end_date = malloc(strlen(token) + 1);
                        strcpy(end_date,token);
                        token = strsep(&line2,";"); //price per night
                        char* price_per_night = malloc(strlen(token) + 1);
                        strcpy(price_per_night,token);
                        token = strsep(&line2,";"); //includes breakfast
                        char* includes_breakfast = malloc(strlen(token) + 1);
                        strcpy(includes_breakfast,token);
                        token = strsep(&line2,";"); //room details
                        char* room_details = malloc((sizeof(char) * 2));
                        strcpy(room_details,"a");
                        token = strsep(&line2,";"); //rating
                        char* rating = malloc(strlen(token) + 1);
                        strcpy(rating,token);
                        token = strsep(&line2,";"); //comment
                        char* comment = malloc(sizeof(char) * 2);
                        strcpy(comment,"a");
                        if (valid_reservation(id_reservation,id_user,id_hotel,hotel_name,hotel_stars,city_tax,address,begin_date,end_date,price_per_night,includes_breakfast,rating,user_catalog)) {
                            Date *begin = string_to_date(begin_date);
                            Date *end = string_to_date(end_date);
                            Reservation *reservation = createReservation(id_reservation,id_user,id_hotel,hotel_name,4,address,1,begin,end,0,0,room_details,4,comment,getHashtableHotelsCatalog(hotel_catalog));
                            addReservToCatalog(reservation_catalog,reservation,hashFunction(id_reservation),hotel_catalog,user_catalog);
                        }
                        else add_invalid_line_to_error_file(reservations,total_line);
                        free(total_line);
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
                     }
                     break;
        }
        free(line);
        fclose(file);
    }
    free(name_file);
    free(path_file);
}

//Faz o parsing de todos os tipos de ficheiros
void parse_all_files (char* path_directory, UsersManager* user_catalog, ReservationsManager * reservation_catalog, HotelsManager *hotel_catalog) {
    parse_file(path_directory,users,user_catalog,reservation_catalog,hotel_catalog);
    parse_file(path_directory,reservations,user_catalog,reservation_catalog,hotel_catalog);
//    parse_file(path_directory,flights,user_catalog,reservation_catalog);
//    parse_file(path_directory,passengers,user_catalog,reservation_catalog);
}