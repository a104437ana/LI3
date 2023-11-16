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
    if (strlen(account_status) == 6 || strlen(account_status) == 8) {
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
                                    if (account_status[i] == '\0') valid = 1;
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

int the_bigger_date (char* date1, char* date2) {
    int bigger_date = 1;
    int year1 = (date1[0] - '0') * 1000 + (date1[1] - '0') * 100 + (date1[2] - '0') * 10 + (date1[3] - '0');
    int year2 = (date2[0] - '0') * 1000 + (date2[1] - '0') * 100 + (date2[2] - '0') * 10 + (date2[3] - '0');
    if (year1 < year2) bigger_date = 2;
    else {
        if (year1 == year2) {
            int month1 = (date1[5] - '0') * 10 + (date1[6] - '0');
            int month2 = (date2[5] - '0') * 10 + (date2[6] - '0');
            if (month1 < month2) bigger_date = 2;
            else {
                if (month1 == month2) {
                    int day1 = (date1[8] - '0') * 10 + (date1[9] - '0');
                    int day2 = (date2[8] - '0') * 10 + (date2[9] - '0');
                    if (day1 < day2) bigger_date = 2;
                    else {
                        if (day1 == day2) bigger_date = 0;
                    }
                }
            }
        }
    }
    return bigger_date;
}

int valid_par_of_dates (char* date1, char* date2) {
    int valid = 0;
    if (strlen(date1) == 10) {
        if (strlen(date2) == 10) {
            if (the_bigger_date(date1,date2) == 2) valid = 1;
        }
        else {
            if (strlen(date2) == 19) {
                if (the_bigger_date(date1,date2) == 2) valid = 1;
                else {
                    if (the_bigger_date(date1,date2) == 0) {
                        valid = 1;
                    }
                }
            }
        }
    }
    else {
        if (strlen(date1) == 19 && strlen(date2) == 19) {
            if (the_bigger_date(date1,date2) == 2) valid = 1;
            else {
                if (the_bigger_date(date1,date2) == 0) {
                    int hour1 = (date1[11] - '0') * 10 + (date1[12] - '0');
                    int hour2 = (date2[11] - '0') * 10 + (date2[12] - '0');
                    if (hour1 < hour2) valid = 1;
                    else {
                        if (hour1 == hour2) {
                            int minute1 = (date1[14] - '0') * 10 + (date1[15] - '0');
                            int minute2 = (date2[14] - '0') * 10 + (date2[15] - '0');
                            if (minute1 < minute2) valid = 1;
                            else {
                                if (minute1 == minute2) {
                                    int second1 = (date1[17] - '0') * 10 + (date1[18] - '0');
                                    int second2 = (date2[17] - '0') * 10 + (date2[18] - '0');
                                    if (second1 < second2) valid = 1;
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

int valid_user (char *id_user, char* name, char* email, char* phone_number, char* birth_date, char* sex, char* passport, char* country_code, char* address, char* account_creation, char* pay_method, char* account_status) {
    int valid = 0;
    if (length_bigger_than_zero(id_user)) {
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
                                                if (valid_account_status(account_status)) {
                                                    if (valid_par_of_dates(birth_date,account_creation)) valid = 1;
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
    }
    return valid;
}

int valid_hotel_stars (char *hotel_stars) {
    int valid = 0;
    if (hotel_stars[0] >= '1' && hotel_stars[0] <= '5' ) {
        if (hotel_stars[1] == '\0') valid = 1;
        else {
            if (hotel_stars[1] == '.') {
                int i = 2;
                while (hotel_stars[i] != '\0') {
                    if (hotel_stars[i] != '0') break;
                    else i++;
                }
                if (hotel_stars[i] == '\0') valid = 1;
            }
        }
    }
    return valid;
}

int valid_city_tax (char* city_tax) {
    int valid = 0;
    if (is_digit(city_tax[0])) {
        int i = 1;
        while (city_tax[i] != '\0') {
            if (!is_digit(city_tax[i])) break;
            else i++;
        }
        if (city_tax[i] == '.') {
            i++;
            while (city_tax[i] != '\0') {
                if (city_tax[i] != '0') break;
                else i++;
            }
            if (city_tax[i] == '\0') valid = 1;
        }
        else {
            if (city_tax[i] == '\0') valid = 1;
        }
    }
    return valid;
}

int valid_price_per_night (char* price_per_night) {
    int zeros = 0;
    int valid = 0;
    if (is_digit(price_per_night[0])) {
        if (price_per_night[0] == '0') zeros++;
        int i = 1;
        while (price_per_night[i] != '\0') {
            if (price_per_night[i] == '0') zeros++;
            if (!is_digit(price_per_night[i])) break;
            else i++;
        }
        if (price_per_night[i] == '.') {
            i++;
            while (price_per_night[i] != '\0') {
                if (price_per_night[i] != '0') break;
                else {
                    zeros++;
                    i++;
                }
            }
            if (price_per_night[i] == '\0' && zeros != i - 1) valid = 1;
        }
        else {
            if (price_per_night[i] == '\0' && zeros != i ) valid = 1;
        }
    }
    return valid;
}

int valid_includes_breakfast (char* includes_breakfast) {
    int valid = 0;
    if (strlen(includes_breakfast) == 0) valid = 1;
    else {
        if (strlen(includes_breakfast) == 1) {
            if (includes_breakfast[0] == '0' || includes_breakfast[0] == '1' || includes_breakfast[0] == 'f' || includes_breakfast[0] == 't' || includes_breakfast[0] == 'F' || includes_breakfast[0] == 'T') {
                valid = 1;
            }
        }
        else {
            if (strlen(includes_breakfast) == 5) {
                if (includes_breakfast[0] == 'f' || includes_breakfast[0] == 'F') {
                    if (includes_breakfast[1] == 'a' || includes_breakfast[1] == 'A') {
                        if (includes_breakfast[2] == 'l' || includes_breakfast[2] == 'L') {
                            if (includes_breakfast[3] == 's' || includes_breakfast[3] == 'S') {
                                if (includes_breakfast[4] == 'e' || includes_breakfast[4] == 'E') {
                                    if (includes_breakfast[5] == '\0') valid = 1;
                                }
                            }
                        }
                    }
                }
            }
            else {
                if (strlen(includes_breakfast) == 4) {
                    if (includes_breakfast[0] == 't' || includes_breakfast[0] == 'T') {
                        if (includes_breakfast[1] == 'r' || includes_breakfast[1] == 'R') {
                            if (includes_breakfast[2] == 'u' || includes_breakfast[2] == 'U') {
                                if (includes_breakfast[3] == 'e' || includes_breakfast[3] == 'E') {
                                    if (includes_breakfast[4] == '\0') valid = 1;
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

int valid_rating (char* rating) {
    int valid = 0;
    if (strlen(rating) == 0) valid = 1;
    else {
        if (valid_hotel_stars(rating)) valid = 1;
    }
    return valid;
}

int valid_reservation (char* id_reservation, char* id_user, char* id_hotel, char* hotel_name, char* hotel_stars, char* city_tax, char* address, char* begin_date, char* end_date, char* price_per_night, char* includes_breakfast, char* rating, UsersManager* usersCatalog) {
    int valid = 0;
    if (length_bigger_than_zero(id_reservation)) {
        if (length_bigger_than_zero(id_user)) { 
            if (length_bigger_than_zero(id_hotel)) {
                if (length_bigger_than_zero(hotel_name)) {
                    if (valid_hotel_stars(hotel_stars)) {
                        if (valid_city_tax(city_tax)) {
                            if (length_bigger_than_zero(address)) {
                                if (valid_date_ymd(begin_date)) {
                                    if (valid_date_ymd(end_date)) {
                                        if (valid_price_per_night(price_per_night)) {
                                            if (valid_includes_breakfast(includes_breakfast)) {
                                                if (valid_rating(rating)) {
                                                    if (valid_par_of_dates(begin_date,end_date)) {
                                                        if (existsUser(usersCatalog,id_user)) valid = 1;
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
        }
    }
    return valid;
}

int valid_origin_or_destination (char* local) {
    int valid = 0;
    if (strlen(local) == 3) valid = 1;
    return valid;
}

int valid_par_of_origin_and_destination (char* origin, char* destination) {
    int valid = 1;
    if (origin[0] == destination[0] || origin[0] + 32 == destination[0] || origin[0] == destination[0] + 32) {
        if (origin[1] == destination[1] || origin[1] + 32 == destination[1] || origin[1] == destination[1] + 32) {
            if (origin[2] == destination[2] || origin[2] + 32 == destination[2] || origin[2] == destination[2] + 32) valid = 0;
        }
    }
    return valid;
}

struct flight_passengers {
    int number;
};

FlightPassengers *createFlightPassengers () {
    FlightPassengers* flight_passengers = malloc(sizeof(FlightPassengers));
    flight_passengers->number = 0;
    return flight_passengers;
}

void AddPassenger(Hashtable *hashtable, unsigned int key, char *id) {
    FlightPassengers *data = getData(hashtable, key, id);
    data->number++;
}

int getPassengersNumber (Hashtable *hashtable, unsigned int key, char *id) {
    FlightPassengers *data = getData(hashtable, key, id);
    int passengers = data->number;
    return passengers;
}

void count_passengers (char* directory, UsersManager* usersCatalog, Hashtable* passengers_per_flight) {
    char* file_path = malloc(strlen(directory) + strlen("/passengers.csv") + 1); int i = 0;
    strcpy(file_path, directory);
    strcat(file_path,"/passengers.csv");
    if (exist_file(file_path)) {
        FILE *file;
        file = fopen(file_path,"r");
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            while((read = getline(&line,&n,file)) != -1){
                char* line2 = malloc(strlen(line) + 1);
                strcpy(line2,line);
                char* token = strsep(&line2,";"); //id flight
                char* id_flight = malloc(strlen(token) + 1);
                strcpy(id_flight,token);
                token = strsep(&line2,";"); //id user
                char* id_user = malloc(strlen(token) + 1);
                strcpy(id_user,token);
                remove_new_line(id_user);
                if (existsUser(usersCatalog,id_user)) {
                    if (searchHashtable(passengers_per_flight,hashFunction(id_flight),id_flight) == NULL) {
                        FlightPassengers* flight_passengers = createFlightPassengers();
                        addHashtable(passengers_per_flight, hashFunction(id_flight), flight_passengers, id_flight);
                        i++;
                    }
                    AddPassenger (passengers_per_flight,hashFunction(id_flight),id_flight);
                }
                free(line2);
                free(id_flight);
                free(id_user);
            }
        }
        free(line);
        fclose(file);
    }
    free(file_path);
    printf("%d\n",i);
}

int valid_total_seats (char* total_seats,Hashtable* passengers_per_flight, char* id_flight) {
    int valid = 0;
    if (valid_price_per_night(total_seats)) {
        if (searchHashtable(passengers_per_flight,hashFunction(id_flight),id_flight) == NULL) valid = 1;
        else {
            int seats = string_to_int(total_seats);
            int passengers = getPassengersNumber(passengers_per_flight,hashFunction(id_flight),id_flight);
            if (seats >= passengers) valid = 1;
        }
    }
    return valid;
}

int valid_flight (char* id_flight, char* airline, char* plane_model, char* total_seats, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, char* real_departure_date, char* real_arrival_date, char* pilot, char* copilot,Hashtable* passengers_per_flight) {
    int valid = 0;
    if (length_bigger_than_zero(id_flight)) {
        if (length_bigger_than_zero(airline)) {
            if (length_bigger_than_zero(plane_model)) {
                if (valid_total_seats(total_seats,passengers_per_flight,id_flight)) {
                    if (valid_origin_or_destination(origin)) {
                        if (valid_origin_or_destination(destination)) {
                            if (valid_par_of_origin_and_destination(origin,destination)) {
                                if (valid_date_ymd_hms(schedule_departure_date)) {
                                    if (valid_date_ymd_hms(schedule_arrival_date)) {
                                        if (valid_par_of_dates(schedule_departure_date,schedule_arrival_date)) {
                                            if (valid_date_ymd_hms(real_departure_date)) {
                                                if (valid_date_ymd_hms(real_arrival_date)) {
                                                    if (valid_par_of_dates(real_departure_date,real_arrival_date)) {
                                                        if (length_bigger_than_zero(pilot)) {
                                                            if (length_bigger_than_zero(copilot)) valid = 1;
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
            }
        }
    }
    return valid;
}

int valid_passenger (char* id_flight, char* id_user, UsersManager* usersCatalog, FlightsManager* flightsCatalog) {
    int valid = 0;
    if (existsUser(usersCatalog,id_user)) {
        if (existsFlight(flightsCatalog,id_flight)) valid = 1;
    }
    return valid;
}
