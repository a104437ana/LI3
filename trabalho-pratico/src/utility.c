#include "utility.h"

/* A função exist_file verifica se um ficheiro existe ou não, dado um caminho relativo ou absoluto para o ficheiro.
Se o ficheiro existir, a função retorna 1. Se não, a função restorna 0. */
int exist_file (char* file_path) {
    int exist = 0;
	FILE *file;
	file = fopen(file_path,"r"); //abertura do ficheiro em modo de leitura. O ficheiro deve existir senão file será NULL.
	if (file != NULL) {
		exist = 1;
        fclose(file);
	}
    return exist;
}

/* A função base_e_expoente calcula uma potência, dado a base e o expoente, considerando apenas
expoentes positivos ou nulos (pré-condição). A função retorna o valor calculado. */
int base_e_expoente (int base, int expoente) {
    int r = 1;
    while (expoente > 0) {
        r *= base;
        expoente--;
    }
    return r;
}

/* A função string_to_int recebe uma string e retorna o número inteiro que essa string representa.
Usar apenas esta função quando sabemos que a string representa um número inteiro (pré-condição).*/
int string_to_int (char* string) {
    int number = 0;
    int i = 0;
    while (string[i] != '\0' && string[i] != '.') {
        i++;
    }
    i--;
    int j = 0;
    while (i>=0) {
        number += (string[i]-'0')*base_e_expoente(10,j);
        j++;
        i--;
    }
    return number;
}

/* A função remove_new_line recebe uma string e substitui o primeiro new line que aparecer na string ('\n')
por um null ('\0'). Esta função altera a string, removendo a new line e tudo o que vier após ela. */
void remove_new_line (char* string) {
    int i = 0;
    while (string[i] != '\n' && string[i] != '\0') {
        i++;
    }
    string[i] = '\0';
}

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
  int second1 = getSeconds(date1), minute1 = getMinutes(date1), hour1 = getHours(date1), day1 = getDay(date1), month1 = getMonth(date1), year1 = getYear(date1);
  int second2 = getSeconds(date2), minute2 = getMinutes(date2), hour2 = getHours(date2), day2 = getDay(date2), month2 = getMonth(date2), year2 = getYear(date2);
  int result = 0;

  if (date1 && date2) {
    if (year1 > year2) result--;
    else if (year2 > year1) result++;
    else if (month1 > month2) result--;
    else if (month2 > month1) result++;
    else if (day1 > day2) result--;
    else if (day2 > day1) result++;
    else if (hour1 > hour2) result--;
    else if (hour2 > hour1) result++;
    else if (minute1 > minute2) result--;
    else if (minute2 > minute1) result++;
    else if (second1 > second2) result--;
    else if (second2 > second1) result++;
  }

  return result;
}

//função que compara duas datas
int compareDatesNoHours(Date *date1, Date *date2) {
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

//calcula o numero de dias (noites) que estão dentro de duas datas limites
int daysInsideDates(Date *limitBegin, Date *limitEnd, Date *begin, Date *end) {
  int nDays = 0;
  int begin_limitBegin, end_limitEnd, begin_limitEnd, end_limitBegin;
  Date *lower, *higher;
  end_limitBegin = compareDatesNoHours(end, limitBegin); //compara a data de fim e a de inicio do limite
  if (end_limitBegin > 0) return -1; //se a data de fim for menor que a de inicio do limite                 == >=
  begin_limitEnd  = compareDatesNoHours(begin, limitEnd); //compara a data de inicio e a de fim do limite
  if (begin_limitEnd < 0) return -2; //se a data de inicio for maior que a de fim do limite
  begin_limitBegin = compareDatesNoHours(begin, limitBegin); //compara a data de inicio e a de inicio do limite
  end_limitEnd = compareDatesNoHours(end, limitEnd); //compara a data de fim e a de fim do limite

  //se a data de inicio for maior que a de inicio do limite
  if (begin_limitBegin > 0) lower = limitBegin; //a primeira data de contagem é a data de inicio do limite                  >=
  else lower = begin; //caso contrário é a data de inicio
  //se a data de fim for maior que a de fim do limite
  if (end_limitEnd < 0) higher = limitEnd; //a última data de contagem é a data de fim do limite                <=
  else higher = end; //caso contrário é a data de fim
  //o número de dias é a diferença entre as datas de contagem
  nDays = daysBetweenDates(lower, higher) + 1; //caso ambas as datas de inicio e fim não estiverem dentro do intervalo de contagem temos que adicionar mais um dia
  if (end_limitEnd >= 0) //caso contrário retiramos o dia adicionado
    nDays --;

  return nDays;
}

int strcoll_names(char *name1, char *name2) {
    char c1 = name1[0], c2 = name2[0];
    char *n1 = malloc(sizeof(char) * 2), *n2 = malloc(sizeof(char) * 2);
    memcpy(n1, name1, 2); n1[1] = '\0';
    memcpy(n2, name2, 2); n2[1] = '\0';
    int compare = strcoll(n1, n2);
    char *f1 = malloc(sizeof(char) * strlen(name1)), *f2 = malloc(sizeof(char) * strlen(name2));
    sscanf(name1, " %s", f1);
    sscanf(name2, " %s", f2);
    int len = strlen(f1) - strlen(f2);
    if (len != 0 && compare == 0)
        compare = strcoll(f1, f2);
    else if (compare == 1 && (c1 == 'A' || c1 == 'E' || c1 == 'I' || c1 == 'O' || c1 == 'U'))
        compare = 1;
    else if (compare == -1 && (c2 == 'A' || c2 == 'E' || c2 == 'I' || c2 == 'O' || c2 == 'U'))
        compare = -1;
    else
        compare = strcoll(name1, name2);
    free(n1);
    free(n2);
    free(f1);
    free(f2);

    return compare;
}

void toUpperS (char *word){
    int s = strlen(word);
    int i;
    for(i=0; i<s; i++){
        if (word[i]>='a' && word[i]<='z'){
            word[i]-=32;
        }
    }
}

//função que liberta o espaço em memória alocado por uma data
void destroyDate(Date *date) {
    if (date == NULL) return; //se não existir a data
    free(date);
}
