#include "utility.h"

//função que cria uma nova data sem horas
Date *createDate(char day, char month, int year) {
    Date *date = malloc(sizeof(Date)); //aloca espaço para a estrutura data
    date->day = day;
    date->month = month;
    date->year = year;
    date->hours = 0;
    date->minutes = 0;
    date->seconds = 0;

    return date;
}
//função que cria uma nova data com horas
Date *createDateHours(char day, char month, int year, char hours, char minutes, char seconds) {
    Date *date = malloc(sizeof(Date)); //aloca espaço para a estrutura data
    date->day = day;
    date->month = month;
    date->year = year;
    date->hours = hours;
    date->minutes = minutes;
    date->seconds = seconds;

    return date;
}

//Transforma uma string num tipo Date
Date* string_to_date (char* string) {
    int year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    int month = (string[5] - '0') * 10 + (string[6] - '0');
    int day = (string[8] - '0') * 10 + (string[9] - '0');
    Date* date = createDateHours(day,month,year,0,0,0);

    return date;
}

Date* string_to_date_hours (char* string) {
    int year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    int month = (string[5] - '0') * 10 + (string[6] - '0');
    int day = (string[8] - '0') * 10 + (string[9] - '0');
    int hours = (string[11] - '0') * 10 + (string[12] - '0');
    int minutes = (string[14] - '0') * 10 + (string[15] - '0');
    int seconds = (string[17] - '0') * 10 + (string[18] - '0');
    Date* date = createDateHours(day,month,year,hours,minutes,seconds);

    return date;
}

//gets
int getDay(void *date) {
    return (int) ((Date *) date)->day;
}

int getMonth(void *date) {
    return (int) ((Date *) date)->month;
}

int getYear(void *date) {
    return ((Date *) date)->year;
}

char getSeconds(Date *date) {
    return date->seconds;
}

char getMinutes(Date *date) {
    return date->minutes;
}

char getHours(Date *date) {
    return date->hours;
}

//sets


char* dateToString(Date *date){
    char* res = 0;
    if (date->hours == 0 && date->minutes ==0 && date->seconds==0) {
        res = malloc(11); //hhu short short unsigned output numerico tamanho 8 bits
        sprintf(res, "%04d/%02hhu/%02hhu", date->year, date->month, date->day);
    }
    else {
        res = malloc(20);
        sprintf(res, "%04d/%02hhu/%02hhu %02hhu:%02hhu:%02hhu", date->year, date->month, date->day, date->hours, date->minutes, date->seconds);
    }
    return res;
}

char* dateToStringNoHours(Date *date){
    char* res = 0;
    res = malloc(11);
    sprintf(res, "%04d/%02hhu/%02hhu", date->year, date->month, date->day);
    return res;
}

//funçaõ que calcula o total de anos bissextos de uma data
int totalLeapYears(int year, int month) {
  if (month <= 2) year--; //se o mês for menor que 3 não precisa de contar ano atual
  return (year / 4) - (year / 100) + (year / 400); //total de anos bissextos
  //um ano é bissexto se for multiplo de 4 mas não de 100 ou se for multiplo de 400
}
//função que calcula o total de dias dos meses dessa data
int totalDaysInMonths(int month) {
  int nDays = 0, daysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  for (int i=0; i <month-1; i++) //conta numero de dias até ao mês anterior ao atual
    nDays += daysOfMonth[i];
  return nDays;
}
//função que calcula o total de dias entre duas datas
int daysBetweenDates(Date *begin, Date *end) {
  int beginDay = getDay(begin), beginMonth = getMonth(begin), beginYear = getYear(begin);
  int endDay = getDay(end), endMonth = getMonth(end), endYear = getYear(end);
  int nDays;
  unsigned int totalDaysBegin, totalDaysEnd;
  //total de dias =  dia  +  dias de cada mês + dias de cada ano + um dia por cada ano bissexto
  totalDaysBegin = beginDay + totalDaysInMonths(beginMonth) + (365 * beginYear) + totalLeapYears(beginYear, beginMonth);
  totalDaysEnd = endDay + totalDaysInMonths(endMonth) + (365 * endYear) + totalLeapYears(endYear, endMonth);
  nDays = totalDaysEnd - totalDaysBegin;

  return nDays;
}
//função que compara duas datas
int compareDates(Date *date1, Date *date2) {
  int day1 = getDay(date1), month1 = getMonth(date1), year1 = getYear(date1);
  int day2 = getDay(date2), month2 = getMonth(date2), year2 = getYear(date2);
  int result = 0;

  if (year1 > year2) result--;
  else if (year2 > year1) result++;
  else if (month1 > month2) result--;
  else if (month2 > month1) result++;
  else if (day1 > day2) result--;
  else if (day2 > day1) result++;

  return result;
}
//função que liberta o espaço em memória alocado por uma data
void destroyDate(Date *date) {
    if (date == NULL) return; //se não existir a data
    free(date);
}
