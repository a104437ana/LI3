#ifndef _UTILITY_
#define _UTILITY_

#include <stdbool.h>

#define BEGIN_YEAR 1950
#define END_YEAR 2050
#define N_YEARS (END_YEAR - BEGIN_YEAR + 1)

#define TIME_DAY 0
#define TIME_MONTH 1
#define TIME_YEAR 2
#define TIME_SECONDS 3
#define TIME_MINUTES 4
#define TIME_HOURS 5

typedef struct date Date;

typedef enum gender {
    MALE,
    FEMALE,
} Gender;
//ficheiros
int exist_directory (char* directory);
int exist_file (char* file_path);
int valid_directory_dataset (char* directory);
int base_e_expoente (int base, int expoente);
int string_to_int (char* string);
void remove_new_line (char* string);

//datas
//cria datas
Date *createDate(char day, char month, int year);
Date *createDateHours(char day, char month, int year, char hours, char minutes, char seconds);
//transforma uma string num tipo date
void stringToDate(Date *date, char *string);
void stringToDateHours(Date *date, char *string);
Date* string_to_date (char* string);
Date* string_to_date_hours (char* string);
//transforma um tipo date numa string
char* dateToString(Date *date);
char* dateToStringNoHours(Date *date);
//gets
int getDay(void *date);
int getMonth(void *date);
int getYear(void *date);
char getSeconds(Date *date);
char getMinutes(Date *date);
char getHours(Date *date);
Date *dupDate(Date *date);
//sets
void setDate(Date *date, char day, char month, int year, char hours, char minutes, char seconds);
//liberta espaço alocado por um tipo date
void destroyDate(Date *date);
//compara datas
int compareDates(Date *date1, Date *date2);
int compareDatesNoHours(Date *date1, Date *date2);
//calcula dias entre datas
int daysBetweenDates(Date *begin, Date *end);
//calcula dias entre datas que estão dentro de um limite
int daysInsideDates(Date *limitBegin, Date *limitEnd, Date *begin, Date *end);

//strings
//minúsculas para maiúsculas
void toUpperS (char *word);
//compara strings
int strcmpVoid(void* s1, void *s2);
//duplica string
void *strdupVoid(void *s);
//id de uma flight de inteiro para string
char *flightIdToString(unsigned long int id);
//id de uma reserva de inteiro para string
char *reservIdToString(unsigned long int id);
//id de uma flight de string para inteiro
unsigned long int flightIdToInt(char *id);
//id de uma reserva de string para inteiro
unsigned long int reservIdToInt(char *id);

//inteiros
//compara inteiros em ordem reversa
int intcmpReverse(unsigned long int n1, unsigned long int n2, void *lookup);

#endif