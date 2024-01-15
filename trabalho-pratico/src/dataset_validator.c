#include "dataset_validator.h"
#include "utility.h"

/* A função length_bigger_than_zero verifica se uma string tem comprimento maior que 0. Se tiver
comprimento maior que 0, a função retorna 1. Se não, retorna 0. Esta função será usada para verificar
se vários parametros de várias identidades são válidos. */
int length_bigger_than_zero (char* string) {
    int bigger = 0;
    if (strlen(string) > 0) bigger = 1;
    return bigger;
}

/* A função valid_email verifica se um email é válido, dado o email. Para o email ser válido tem de ter
o seguinte formato “<username>@<domain>.<TLD>”, sendo que o username e domain tem de ter pelo menos comprimento
igual a 1 e o TDL tem de ter pelo menos comprimento igual a 2. Assim para ser válido, o email tem de ter pelo menos
comprimento 6 e tem de respeitar o seu formato. Se o email for válido, a função retorna 1. Se não,
a função retorna 0. */
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

/* A função valid_country_code verifica se o código do país de residência é válido, dado o
código do país de residência. Esta função verifica se o código tem comprimento igual a 2. Se
sim, retorna 1. Se não, retorna 0. */
int valid_country_code (char* country_code) {
    int valid = 0;
    if (strlen(country_code) == 2) valid = 1;
    return valid;
}

/* A função valid_account_status verifica se o estado da conta é válido. Esta função verifica se
o estado da conta tem comprimento 6 ou 8 (as únicas maneiras de ser válido pois "active" tem 
comprimento 6 e "inactive" tem comprimento 8) e se é igual a uma combinação de maiúsculas e minúsculas
de "active" ou de "inactive". Se for válido, retorna 1. Se não, retorna 0. */
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

/* A função is_digit, dado um char, verifica se este char representa um dígito decimal. Esta função verifica se
o código ASCII deste char está entre os código ASCII de '0' e '9' ou se é igual a um deles, ou seja, verifica se 
o char é algum dos dígitos possíveis (0,1,2,3,4,5,6,7,8,9). Se for um dígito decimal, retorna 1. Se não, retorna 0. */
int is_digit (char n) {
    int digit = 0;
    if (n >= '0' && n <= '9') digit = 1;
    return digit;
}

/* A função valid_date_ymd verifica se uma data (com ano, mês e dia) é válida, dada essa data (string). Para esta data ser
válida tem de ter o seguinte formato "nnnn/nn/nn", onde n é um número entre 0 e 9 (inclusivo). Para além disso, para ser
uma data válida, o mês precisa de estar entre 1 e 12 (inclusive) e o dia precisa de estar entre 1 e 31 (inclusive). Se a
data for válida, a função retorna 1. Se não, retorna 0.*/
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

/* A função valid_date_ymd_hms verifica se uma data (com ano, mês e dia) com tempo (com hora, minuto e segundo) é válida,
dada essa data (string). Para esta data com tempo ser válida tem de ter o seguinte formato "nnnn/nn/nn nn:nn:nn", onde n é 
um número entre 0 e 9 (inclusivo). Para além disso, para ser uma data com tempo válida, o mês precisa de estar entre 1 e 12 
(inclusive), o dia precisa de estar entre 1 e 31 (inclusive), a hora precisa de estar entre 0 e 23 (inclusive), os minutos
precisam de estar entre 0 e 59 (inclusive) e os segundos precisam de estar entre 0 e 59 (inclusive). Se a data com tempo for
válida, a função retorna 1. Se não, retorna 0.*/
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

/* A função the bigger_date calcula qual é a string que representa a maior data, dadas duas strings que representam
datas (sem tempo) no formato válido (pré-condição). Se a maior data for a primeira string, a função retorna 1. Se a 
maior data for a segunda string, a função retorna 2. Se as duas datas forem iguais, a função retorna 0.*/
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

/* A função valid_par_of_dates verifica se um par de datas é válido, dadas duas strings que representam datas com
formato válido (pré-condição). Um par de datas é válido se a data inicial não for superior a data final. Nos
utilizadores, o birth_date tem que vir antes de account_creation (a não ser que criem a conta no mesmo dia em que
a pessoa nasceu). Nos voos, o schedule_departure_date tem que vir antes de schedule_arrival_date, e o real_departure_date
tem que vir antes de real_arrival_date. E nas reservas, o begin_date tem que vir antes do end_date. Se o par é válido,
a função retorna 1. Se não, retorna 0. */
int valid_par_of_dates (char* date1, char* date2) {
    int valid = 0;
    if (strlen(date1) == 10) {
        if (strlen(date2) == 10) { //datas nas reservas
            if (the_bigger_date(date1,date2) == 2) valid = 1;
        }
        else {
            if (strlen(date2) == 19) { //datas nos utilizadores
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
        if (strlen(date1) == 19 && strlen(date2) == 19) { //datas nos voos
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

/* A função valid_user verifica se um utilizador é válido, dado o seu id, nome, email, número de telemóvel, data de nascimento,
sexo, número do passaporte, código do país de residência, morada, data de criação de conta, método de pagamento e o estado da
conta. Esta função verifica se cada um dos parametros listados anteriormente são válidos. Se sim, retorna 1. Se não, retorna 0.*/
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

/* A função valid_hotel_stars verifica se o número de estrelas de um hotel é válido, dado um número de estrelas
de um hotel. Esta função verifica se o número de estrelas é um número inteiro, e se está entre 1 e 5 (inclusive). 
Se sim, retorna 1. Se não, retorna 0. */
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

/* A função is_non_negative_integer verifica se uma string representa um número inteiro não negativo,
dada uma string. Se representar um número inteiro não negativo, retorna 1. Se não, retorna 0. Esta 
função será usada para verificar se a percentagem do imposto da cidade é válida, ou seja, se é
um número inteiro não negativo. */
int is_non_negative_integer (char* city_tax) {
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

/* A função is_positive_integer verifica se uma string representa um número inteiro positivo, dada
uma string. Se representar um número inteiro positivo, retorna 1. Se não, retorna 0. Esta função
será usada para verificar se o preço por noite é válido mas também será usada para verificar se
o número de lugares num voo pode ser válido. */
int is_positive_integer (char* price_per_night) {
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


/* A função valid_includes_breakfast verifica se a string, que representa a inclusão ou não de pequeno-almoço, é válida,
dada essa string. Se a string tiver tamanho 0, então a string é válida. Se a string tiver tamanho 1 e for igual a "0","1",
"f","F","t" ou "T", então a string é válida. Se a string tiver tamanho 5 e for igual a qualquer combinação de maiúsculas 
e minúsculas de "false", então a string é válida. Se a string tiver tamanho 4 e for igual a qualquer combinação de maiúsculas
e minúsculas de "true", então a string é válida. Se a string for válida, a função retorna 1. Se não, a função retorna 0. */
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

/* A função valid_rating verifica se a classificação dada pelo utilizador é válida, dada essa classificação.
Se a classificação tiver comprimento 0 (o utilizador não deu classificação ao hotel), então a classificação
é válida. Se tiver comprimento superior a 0 e se a classificação for um número de estrela de hotel válido,
a classificação é válida. Se a classificação é válida, a função retorna 1. Se não, a função retorna 0. */
int valid_rating (char* rating) {
    int valid = 0;
    if (strlen(rating) == 0) valid = 1;
    else {
        if (valid_hotel_stars(rating)) valid = 1;
    }
    return valid;
}

/* A função valid_reservation verifica se uma reserva é válida, dado o seu id, id do utilizador, id do hotel, nome do hotel,
número de estrelas do hotel, percentagem do imposto da cidade, morada, data de início, data de fim, preço por noite, a string que 
diz se inclui pequeno-almoço ou não, a classificação atribuída pelo utilizador e dado o catálogo de utilizadores válidos. Esta 
função verifica se cada um dos parametros listados anteriormente são válidos e se o utilizador da reserva existe no catálogo de 
utilizadores válidos. Se sim, retorna 1. Se não, retorna 0.*/
int valid_reservation (char* id_reservation, char* id_user, char* id_hotel, char* hotel_name, char* hotel_stars, char* city_tax, char* address, char* begin_date, char* end_date, char* price_per_night, char* includes_breakfast, char* rating, Catalogs* catalogs) {
    int valid = 0;
    if (length_bigger_than_zero(id_reservation)) {
        if (length_bigger_than_zero(id_user)) { 
            if (length_bigger_than_zero(id_hotel)) {
                if (length_bigger_than_zero(hotel_name)) {
                    if (valid_hotel_stars(hotel_stars)) {
                        if (is_non_negative_integer(city_tax)) {
                            if (length_bigger_than_zero(address)) {
                                if (valid_date_ymd(begin_date)) {
                                    if (valid_date_ymd(end_date)) {
                                        if (is_positive_integer(price_per_night)) {
                                            if (valid_includes_breakfast(includes_breakfast)) {
                                                if (valid_rating(rating)) {
                                                    if (valid_par_of_dates(begin_date,end_date)) {
                                                        if (userExists(id_user,catalogs)) valid = 1;
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

/* A função valid_origin_or_destination verifica se a origem ou o destino (de um voo) é válido, dada a origem ou o
destino. A função verifica se a string tem comprimento igual a 3. Se tiver, a string é válida e a função retorna 1.
Se não, a string é inválida e a função retorna 0. */
int valid_origin_or_destination (char* local) {
    int valid = 0;
    if (strlen(local) == 3) valid = 1;
    return valid;
}

/* A função valid_par_of_origin_and_destination verifica se o par origem e destino é válido. Esta função verifica se
as duas strings não são duas combinações diferentes ou iguais de maiúsculas e minúsuculas da mesma string. Se ambas for 
combinação de maiúsculas e minúsculas da mesma string, o par é inválido e a função retorna 0. Se não, o par é válido e
a função retorna 1. Nesta função já garantimos (pré-codição) que a origem e o destino são válidos separadamente. */
int valid_par_of_origin_and_destination (char* origin, char* destination) {
    int valid = 1;
    if (origin[0] == destination[0] || origin[0] + 32 == destination[0] || origin[0] == destination[0] + 32) {
        if (origin[1] == destination[1] || origin[1] + 32 == destination[1] || origin[1] == destination[1] + 32) {
            if (origin[2] == destination[2] || origin[2] + 32 == destination[2] || origin[2] == destination[2] + 32) valid = 0;
        }
    }
    return valid;
}

/* Estrutura passengers_per_flight é uma estrutura constituída por um número inteiro onde iremos guardar o número total de passageiros de cada voo. */
struct passengers_per_flight {
    int number;
};

/* A função createPassengersPerFlight cria uma estrutura passengers_per_flight, ou seja, aloca memória dinamicamente para essa estrutura e coloca o
o número total de passageiros como sendo 0. Esta função inicializa uma estrutura passengers_per_flight e retorna essa estrutura. */
PassengersPerFlight *createPassengersPerFlight () {
    PassengersPerFlight* passengers_per_flight = malloc(sizeof(PassengersPerFlight));
    passengers_per_flight->number = 0;
    return passengers_per_flight;
}

/* A função destroyPassengersPerFlight destroi uma estrutura passengers_per_flight já existente, ou seja, liberta a memória dinámica que guardava a
estrutura passengers_per_flight, se esta estrutura já existir (se for diferente de NULL). */
void destroyPassengersPerFlight (void* passengers_per_flight) {
    if (passengers_per_flight != NULL) {
        free(passengers_per_flight);
    }
}

/* A estrutura passengers_counter é uma hashtable usada para guardar o número total de passageiros por id de voo. Logo é uma hashtable constítuida por 
estruturas passengers_per_flight. Nesta hashtable iremos guardar o número de passageiros que contarmos por id de voo, logo o propósito desta hashtable é
contar o número de passageiros por voo. Iremos fazer isto para depois sabermos se os lugares disponíveis no voo são superiores ou iguais aos números de
passageiros, ou seja, para sabermos se um número de lugares disponíveis num voo é válido.*/
struct passengers_counter {
    Hashtable* passengers_per_flight;
};

/* A função createPassengersCounter cria a hashtable passengers_counter, ou seja aloca memória dinamicamente para essa estrutura e depois cria uma
hashtable. Esta função recebe um número que será o tamanho da hashtable criada. Esta função retorna a estrutura passengers_counter. */
PassengersCounter *createPassengersCounter (int size) {
    PassengersCounter* passengers_counter = malloc(sizeof(PassengersCounter));
    passengers_counter->passengers_per_flight = createHashtable(size, hashFunction, strcmpVoid, strdupVoid, destroyPassengersPerFlight);
    return passengers_counter;
}

/* A função addPassengersPerFlight_ToPassengersCounter addiciona à hashtable uma estrutura passengers_per_flight, dada essa estrutura, a
hashtable passengers_counter, o id de voo e a chave.*/
void addPassengersPerFlight_ToPassengersCounter (PassengersCounter* passengers_counter, PassengersPerFlight* passengers_per_flight, char* id_flight) {
    passengers_counter->passengers_per_flight = addHashtable(passengers_counter->passengers_per_flight, passengers_per_flight, id_flight);
}

/* A função existsPassengersPerFlight verifica se para um id de voo existe uma estrutura passangers_per_flight na hashtable passengers_counter.
Se existir, a função retorna 1. Se não, a função retorna 0.*/
int existsPassengersPerFlight (PassengersCounter* passengers_counter, char* id_flight) {
    return existsData(passengers_counter->passengers_per_flight, id_flight);
}

/* A função addPassenger_ToPassengersPerFlight adiciona um ao número de passageiros de um voo guardados na hashtable passengers_counter, dado
um id de voo, uma chave e a hashtable passengers_counter. */
void addPassenger_ToPassengersPerFlight (PassengersCounter* passengers_counter, char *id) {
    PassengersPerFlight *data = getData(passengers_counter->passengers_per_flight, id);
    data->number++;
}

/* A função getPassengersNumber retorna o número de passageiros de um determinado voo, dado o id do voo, a chave e a hashtable passengers_counter.*/
int getPassengersNumber (PassengersCounter* passengers_counter, char *id) {
    PassengersPerFlight *data = getData(passengers_counter->passengers_per_flight, id);
    int passengers = data->number;
    return passengers;
}

/* A função destroyPassengersCounter destroi a hashtable passengers_counter, ou seja, liberta a memória dinámica que guardava a hashtable e
liberta a memória dinámica que guardava cada estrutura passengers_per_flight. */
void destroyPassengersCounter (PassengersCounter* passengers_counter) {
    if (passengers_counter != NULL) {
        destroyHashtable(passengers_counter->passengers_per_flight);
        free(passengers_counter);
    }
}

/* A função count_passengers conta para cada id de voo (para cada voo) o número de passageiros nesse voo. Esta função começa por 
construir o caminho para o ficheiro passengers.csv. Para isso, junta a string dada, que nos indica o caminho absoluto para a 
diretoria onde o ficheiro se encontra, com a string "/passengers.csv", para assim obtermos o caminho absoluto para o ficheiro.
Depois verifica se o ficheiro existe. Depois se este ficheiro realmente existir, iremos abrir o ficheiro para o poder ler. Primeiro 
lemos a primeira linha onde se encontra o header (o cabeçalho). Esta linha não apresenta informação relevante para contar os passageiros,
logo não fazemos nada com ela. Depois iremos ler as próximas linhas. A cada linha que lemos, iremos pegar nela e dividi-la em várias partes 
(id de utilizador e id de voo). Com o id de utilizador iremos verificar se o utilizador já existe no catálogo de utilizadores válidos. Se
não, não iremos fazer nada. Se existir, iremos verificar se o id de voo já tem estrutura na hashtable. Se não, iremos inicializar a estrutura
e adicionamos um passageiro. Se já existia, adicionamos mais um passageiro a estrutura já existente. Por fim, libertamos a memória alocada e 
fechamos o ficheiro. E no final, conseguimos contar todos os passageiros de cada voo.*/
void count_passengers (char* directory, Catalogs *catalogs, PassengersCounter* passengers_counter) {
    int size = strlen(directory) + 16;
    char* file_path = malloc(size);
    strcpy(file_path, directory);
    strcat(file_path,"/passengers.csv");
    if (exist_file(file_path)) {
        char **token = malloc(sizeof(char*)*2);
        FILE *file;
        file = fopen(file_path,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            while((read = getline(&line,&n,file)) != -1){
                int size_line = strlen(line) + 1;
                char* line_modified = malloc(size_line);
                strcpy(line_modified,line);
                char* line_pointer = line_modified;
                token[0] = strsep(&line_pointer,";");
                token[1] = strsep(&line_pointer,";");
                remove_new_line(token[1]);
                if (userExists(token[1],catalogs)) {
                    if (!(existsPassengersPerFlight(passengers_counter,token[0]))) {
                        PassengersPerFlight* passengers_per_flight = createPassengersPerFlight();
                        addPassengersPerFlight_ToPassengersCounter(passengers_counter,passengers_per_flight,token[0]);
                    }
                    addPassenger_ToPassengersPerFlight(passengers_counter,token[0]);
                }
                free(line_modified);
            }
        }
        free(line);
        fclose(file);
        free(token);
    }
    free(file_path);
}

/* A função valid_total_seats verifica se o número de lugares totais disponíveis num voo é válido, dado esse número, dada a hashtable com o
número de passageiros por id de voo e dado o id do voo. Primeiro, a função verifica se o número de lugares é um inteiro positivo.
Se não for, o número é inválido, logo a função irá restornar 0. Se for, a função irá agora ver se o id de voo está associado a alguma
estrutura na hashtable. Se não estiver, significa que não foi criada estrutura para esse voo, logo esse voo não apresenta qualquer passageiro.
Como 0 passageiros é sempre inferior a um número inteiro positivo de lugares, então o número é válido e a função retorna 1. Se estiver na 
hashtable, então agora é só verificar se o número de lugares do voo é superior ou igual ao número de passageiros. Se sim, o número é válido
e a função retorna 1. Se não, o número é inválido e a função retorna 0. */
int valid_total_seats (char* total_seats,PassengersCounter* passengers_counter, char* id_flight) {
    int valid = 0;
    if (is_positive_integer(total_seats)) {
        if (!(existsPassengersPerFlight(passengers_counter,id_flight))) valid = 1;
        else {
            int seats = string_to_int(total_seats);
            int passengers = getPassengersNumber(passengers_counter,id_flight);
            if (seats >= passengers) valid = 1;
        }
    }
    return valid;
}

/* A função valid_flight verifica se um voo é válido, dado o seu id, companhia aérea, modelo de avião, número de lugares totais disponíveis,
aeroporto de origem, aeroporto de destino, data e hora estimada de partida, date e hora estimada de chegada, data e hora real de partida, data
e hora real de chegada, piloto, copiloto e dada hashtable com o número de passageiros por id de voo. Esta função verifica se cada um dos parametros
listados anteriormente são válidos. Se sim, retorna 1. Se não, retorna 0. */
int valid_flight (char* id_flight, char* airline, char* plane_model, char* total_seats, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, char* real_departure_date, char* real_arrival_date, char* pilot, char* copilot, PassengersCounter* passengers_counter) {
    int valid = 0;
    if (length_bigger_than_zero(id_flight)) {
        if (length_bigger_than_zero(airline)) {
            if (length_bigger_than_zero(plane_model)) {
                if (valid_total_seats(total_seats,passengers_counter,id_flight)) {
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

/* A função valid_passenger verifica se um passageiro é válido, dado o id de voo do passageiro, o id de utilizador do passageiro,
o catálogo de utilizadores válidos e o catálogo de voos válidos. A função verifica se o utilizador existe no catálogo de utilizadores válidos e se o voo
existe no catálogo de voos válidos. Se sim, o passageiro é válido e a função retorna 1. Se não, o passageiro é inválido e a função retorna 0. */
int valid_passenger (char* id_flight, char* id_user, Catalogs* catalogs) {
    int valid = 0;
    if (userExists(id_user,catalogs)) {
        if (flightExists(id_flight,catalogs)) valid = 1;
    }
    return valid;
}

/* A função add_invalid_line_to_error_file adiciona uma linha inválida ao ficheiro de erros, 
dado o caminho relativo para esse ficheiro de erros e dada a linha inválida. Esta função
também é usada para adicionar o header (o cabeçalho) do ficheiro original, ao ficheiro de erros.*/
void add_invalid_line_to_error_file (char* file_path, char* string_line) {
    FILE *file;
    file = fopen(file_path,"a"); //abertura do ﬁcheiro em modo de escrita para acrescentar dados aos já existentes. O ﬁcheiro é criado se não existir.
    fprintf(file,"%s",string_line);
    fclose(file);
}

void create_error_file (char *file_path) {
    FILE *file;
    file = fopen(file_path,"w");
    fclose(file);
}