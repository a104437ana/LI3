#include "dataset_validator.h"

int length_bigger_than_zero (char* string) {
    int bigger = 0;
    if (strlen(string) > 0) bigger = 1;
    return bigger;
}

int valid_email (char* email) {
    int valid = 0;
    if (strlen(email) >= 6) {
        int i = 0;
        while (email[i] != '\0' && email[i] != '@') {
            i++;
        }
        int length_username = i;
        if (email[i] == '@' && length_username>=1) {
            i++;
            while (email[i] != '\0' && email[i] != '.') {
                i++;
            }
            int length_domain = i - length_username - 1;
            if (email[i] == '.' && length_domain>=1) {
                i++;
                while (email[i] != '\0') {
                    i++;
                }
                int length_tld = i - length_domain - 1;
                if (length_tld>=2) {
                    valid = 1;
                }
            }
        }
    }
    return valid;
}

int valid_country_code (char* country_code) {
    int valid = 0;
    if (strlen(country_code) == 2) valid = 1;
    return valid;
}

int valid_account_status (char* account_status) {
    int valid = 0;
    if (strlen(account_status) == 7 || strlen(account_status) == 9) {
        int i = 0;
        int continua = 1;
        if (account_status[i] == 'i' || account_status[i] == 'I') {
            i++;
            if (account_status[i] == 'n' || account_status[i] == 'N') {
                i++;
            }
            else continua = 0;
        }
        if (continua) {
            if (account_status[i] == 'a' || account_status[i] == 'A') {
                i++;
                if (account_status[i] == 'c' || account_status[i] == 'C') {
                    i++;
                    if (account_status[i] == 't' || account_status[i] == 'T') {
                        i++;
                        if (account_status[i] == 'i' || account_status[i] == 'I') {
                            i++;
                            if (account_status[i] == 'v' || account_status[i] == 'V') {
                                i++;
                                if (account_status[i] == 'e' || account_status[i] == 'E') {
                                    i++;
                                    if (account_status[i] == '\n') valid = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return valid;
}

int is_digit (char n) {
    int digit = 0;
    if (n >= '0' && n <= '9') digit = 1;
    return digit;
}

int valid_date_ymd (char* date) {
    int valid = 0;
    if (strlen(date) == 10) {
        if (date[4] == '/' && date[7] == '/' && date[10] == '\0') {
            if (is_digit(date[0]) && is_digit(date[1]) &&  is_digit(date[2]) && is_digit(date[3]) && is_digit(date[5]) && is_digit(date[6]) && is_digit(date[8]) && is_digit(date[9])) {
                int month = ((date[5] - '0')*10+(date[6] - '0'));
                if (month <= 12 && month >= 1) {
                    int day = ((date[8] - '0')*10+(date[9] - '0'));
                    if (day <= 31 && day >= 1) valid = 1;
                }
            }
        }
    }
    return valid;
}

int valid_date_ymd_hms (char* date) {
    int valid = 0;
    if (strlen(date) == 19) {
        if (date[4] == '/' && date[7] == '/' && date[10] == ' ' && date[13] == ':' && date[16] == ':' && date[19] == '\0') {
            if (is_digit(date[0]) && is_digit(date[1]) &&  is_digit(date[2]) && is_digit(date[3]) && is_digit(date[5]) && is_digit(date[6]) && is_digit(date[8]) && is_digit(date[9]) && is_digit(date[11]) && is_digit(date[12]) && is_digit(date[14]) && is_digit(date[15]) && is_digit(date[17]) && is_digit(date[18])) {
                int month = ((date[5] - '0')*10+(date[6] - '0'));
                if (month <= 12 && month >= 1) {
                    int day = ((date[8] - '0')*10+(date[9] - '0'));
                    if (day <= 31 && day >= 1) {
                        int hour = ((date[11] - '0')*10+(date[12] - '0'));
                        if (hour <= 23 && hour >= 0) {
                            int minutes = ((date[14] - '0')*10+(date[15] - '0'));
                            if (minutes <= 59 && minutes >= 0) {
                                int seconds = ((date[14] - '0')*10+(date[15] - '0'));
                                if (seconds <= 59 && seconds >= 0) valid = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return valid;
}

int valid_user (char *id, char* name, char* email, char* phone_number, char* birth_date, char* sex, char* passport, char* country_code, char* address, char* account_creation, char* pay_method, char* account_status) {
    int valid = 0;
    if (length_bigger_than_zero(id)) {
        if (length_bigger_than_zero(name)) {
            if (valid_email(email)) {
                if (length_bigger_than_zero(phone_number)) {
                    if (valid_date_ymd(birth_date)) {
                        if (length_bigger_than_zero(sex)) {
                            if (length_bigger_than_zero(passport)) {
                                if (valid_country_code(country_code)) {
                                    if (length_bigger_than_zero(address)) {
                                        if (valid_date_ymd_hms(account_creation)) {
                                            if (length_bigger_than_zero(pay_method)) {
                                                if (valid_account_status(account_status)) valid = 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return valid;
}

int valid_hotel_star (char *hotel_star) {
    int valid = 0;
    if (hotel_star[0] >= 1 && hotel_star[0] <= 5) valid = 1;
    return valid;
}

void add_invalid_line_to_error_file (enum Type_file type_file, char* string_line) {
    char* path_file = NULL;
    switch (type_file) {
        case 0 : path_file = malloc(strlen("../Resultados/users_errors.csv") + 1);
                 strcpy(path_file,"../Resultados/users_errors.csv");
                 break;
        case 1 : path_file = malloc(strlen("../Resultados/flights_errors.csv") + 1);
                 strcpy(path_file,"../Resultados/flights_errors.csv");
                 break;
        case 2 : path_file = malloc(strlen("../Resultados/passengers_errors.csv") + 1);
                 strcpy(path_file,"../Resultados/passengers_errors.csv");
                 break;
        case 3 : path_file = malloc(strlen("../Resultados/reservations_errors.csv") + 1);
                 strcpy(path_file,"../Resultados/reservations_errors.csv");
                 break;
    }
    FILE *file;
    file = fopen(path_file,"a");
    printf("%s",string_line);
    fclose(file);
    free(path_file);
}