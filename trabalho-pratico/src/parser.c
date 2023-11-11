#include "parser.h"

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

Date string_to_date (char* string) {
    Date date;
    date.year = string[0] * 1000 + string[1] * 100 + string[2] * 10 + string[3];
    date.month = string[5] * 10 + string[6];
    date.day = string[8] * 10 + string[9];
    int hasHours = 0;
    if (strlen(string) == 19) {
        hasHours = 1;
        date.hour.hours = string[11] * 10 + string[12];
        date.hour.minutes = string[14] * 10 + string[15];
        date.hour.seconds = string[17] * 10 + string[18];
    }
    date.hasHours = hasHours;
    return date;
}

void parse_file (char* path_directory, enum Type_file type_file) {
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
                     while((read = getline(&line,&n,file)) != -1){
                        char* total_line = malloc(strlen(line) + 1);
                        strcpy(total_line,line);
                        char* token = strsep(&line,";"); //id
                        char* id = malloc(strlen(token) + 1);
                        strcpy(id,token);
                        token = strsep(&line,";"); //name
                        char* name = malloc(strlen(token) + 1);
                        strcpy(name,token);
                        token = strsep(&line,";"); //email
                        char* email = malloc(strlen(token) + 1);
                        strcpy(email,token);
                        token = strsep(&line,";"); //phone_number
                        char* phone_number = malloc(strlen(token) + 1);
                        strcpy(phone_number,token);
                        token = strsep(&line,";"); //birth_date
                        char* birth_date = malloc(strlen(token) + 1);
                        strcpy(birth_date,token);
                        token = strsep(&line,";"); //sex
                        char* sex = malloc(strlen(token) + 1);
                        strcpy(sex,token);
                        token = strsep(&line,";"); //passporte
                        char* passport = malloc(strlen(token) + 1);
                        strcpy(passport,token);
                        token = strsep(&line,";"); //country_code
                        char* country_code = malloc(strlen(token) + 1);
                        strcpy(country_code,token);
                        token = strsep(&line,";"); //address
                        char* address = malloc(strlen(token) + 1);
                        strcpy(address,token);
                        token = strsep(&line,";"); //account_creation
                        char* account_creation = malloc(strlen(token) + 1);
                        strcpy(account_creation,token);
                        token = strsep(&line,";"); //pay_method
                        char* pay_method = malloc(strlen(token) + 1);
                        strcpy(pay_method,token);
                        token = strsep(&line,";"); //account_status
                        char* account_status = malloc(strlen(token) + 1);
                        strcpy(account_status,token);
                        if (valid_user(id,name,email,phone_number,birth_date,sex,passport,country_code,address,account_creation,pay_method,account_status)) {
                            int gender = 0;
                            if (sex[0] == 'F' || sex[0] == 'f') gender = 1;
                            Date birth = string_to_date(birth_date);
                            Date accountCreation = string_to_date(account_creation);
                            createUser(id,name,gender,country_code,address,passport,birth,email,0,accountCreation);
                        }
                        else add_invalid_line_to_error_file(users,total_line);
                        free(total_line);
                        free(id); 
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
                     add_invalid_line_to_error_file(flight,line);
                     while((read = getline(&line,&n,file)) != -1){
                        char* total_line = malloc(strlen(line) + 1);
                        strcpy(total_line,line);
                        char* token = strsep(&line,";"); //id fligth
                        token = strsep(&line,";"); //airline
                        token = strsep(&line,";"); //plane_model
                        token = strsep(&line,";"); //total_seats
                        token = strsep(&line,";"); //origin
                        token = strsep(&line,";"); //destination
                        token = strsep(&line,";"); //data planeada partida
                        token = strsep(&line,";"); //data planeada chegada
                        token = strsep(&line,";"); //data real partida
                        token = strsep(&line,";"); //data real chegada
                        token = strsep(&line,";"); //piloto
                        token = strsep(&line,";"); //copiloto
                        token = strsep(&line,";"); //notas
                        cre
                        //add_invalid_line_to_error_file(flight,total_line);
                        free(total_line);
                     }
                     }
                     break;
            case 2 : if ((read = getline(&line,&n,file)) != -1) {
                     add_invalid_line_to_error_file(passengers,line);
                     while((read = getline(&line,&n,file)) != -1){
                        char* total_line = malloc(strlen(line) + 1);
                        strcpy(total_line,line);
                        char* token = strsep(&line,";"); //id fligth
                        token = strsep(&line,";"); //id user
                        add_invalid_line_to_error_file(passengers,total_line);
                        free(total_line);
                     }
                     }
                     break;
            case 3 : if ((read = getline(&line,&n,file)) != -1) {
                     add_invalid_line_to_error_file(reservations,line);
                     while((read = getline(&line,&n,file)) != -1){
                        char* total_line = malloc(strlen(line) + 1);
                        strcpy(total_line,line);
                        char* token = strsep(&line,";"); //id reservation
                        token = strsep(&line,";"); //id user
                        token = strsep(&line,";"); //id hotel
                        token = strsep(&line,";"); //nome hotel
                        token = strsep(&line,";"); //estrelas hotel
                        token = strsep(&line,";"); //city tax
                        token = strsep(&line,";"); //morada
                        token = strsep(&line,";"); //data inicio
                        token = strsep(&line,";"); //data fim
                        token = strsep(&line,";"); //preço por noite
                        token = strsep(&line,";"); //pequeno-almoço
                        token = strsep(&line,";"); //room details
                        token = strsep(&line,";"); //rating
                        token = strsep(&line,";"); //coments
                        add_invalid_line_to_error_file(reservations,total_line);
                        free(total_line);
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

void parse_all_files (char* path_directory) {
    parse_file(path_directory,users);
    parse_file(path_directory,flights);
    parse_file(path_directory,passengers);
    parse_file(path_directory,reservations);
}