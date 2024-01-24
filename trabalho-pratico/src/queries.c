#include "queries.h"
#include "heap.h"

//verifica se uma string é um prefixo de outra
int same_prefix (char* prefix, char* name) { 
  int same_prefix = 0;
  if (strlen(name) >= strlen(prefix)) {
    int i = 0;
    while (prefix[i] != '\0') {
      if (prefix[i] != name[i]) break;
      i++;
    }
    if (prefix[i] == '\0') same_prefix = 1;
  }
  return same_prefix;
}

//query 1 - retorna o utilizador, reserva ou voo com o id passado como argumento (se existir e não for um utilizador inativo)
void Q1 (char *id, Catalogs* catalogs, QueryResult* result) {
  if(same_prefix("Book", id) == 1){ //se o id for de uma reserva
      catalogs_compute_Q1_reservation(id,catalogs,result);
  }
  else if (id[0]>='0' && id[0]<='9'){ //se o id for de um voo
        catalogs_compute_Q1_flight(id,catalogs,result);
  }
  else{ //se o id for de um utilizador
      catalogs_compute_Q1_user(id,catalogs,result);
  }
}

//query 2 - retorna a lista de reservas, voos, ou ambos - conforme o argumento type - de um utilizador (se existir e não estiver inativo)
void Q2(char *id_user, Q2Type type, Catalogs *catalogs, QueryResult *result){
    int userAccountStatus = getAccountStatus(id_user, catalogs);
    if (userAccountStatus<=0) return; //se o id não existir ou o utilizador não estiver ativo
    int i;
    int j = 0; //-O2
    int listSize, resultSize;
    listSize = getUserListSize(0, id_user, catalogs);
    sortUserList(id_user, catalogs);
    if (type == BOTH) j = 0;
    else if (type == FLIGHTS) j = 1;
    else if (type == RESERVATIONS) j = 2;
    resultSize = getUserListSize(j, id_user, catalogs); //tamanho do tipo de lista que for pedida
    setNumberResults(result, resultSize);
    char *field0 = strdup("id"), *field1 = strdup("date"), *field2 = strdup("type");
    char *id = 0;
    char *dateS = NULL; //-O2
    char *typeS = NULL; //-O2
    Q2Type resultType;
    if (type==BOTH) {
      for(i=0, j=resultSize-1;j>=0; i++, j--){
        unsigned long int key = getUserListId((int *) &resultType, id_user, i, catalogs);
        if (resultType == FLIGHTS) {
          dateS = getStringFlightDate(key, catalogs);
          typeS = strdup("flight");
          id = flightIdToString(key);
        }
        else if (resultType == RESERVATIONS) {
          dateS = getStringReservationDate(key, catalogs);
          typeS = strdup("reservation");
          id = reservIdToString(key);
        }
        setNumberFieldsQ(result, j, 3);
        setFieldQ(result, j, 0, field0, id);
        setFieldQ(result, j, 1, field1, dateS);
        setFieldQ(result, j, 2, field2, typeS);
        free(dateS);
        free(typeS);
        free(id);
      }
    }
    else {
      for(i=0, j=resultSize-1;i<listSize; i++){
        unsigned long int key = getUserListId((int *) &resultType, id_user, i, catalogs);
        if (resultType==type){ //verifica se a posição atual tem um voo ou uma reserva
          if (resultType == FLIGHTS) {
            dateS = getStringFlightDate(key, catalogs);
            id = flightIdToString(key);
          }
          else if (resultType == RESERVATIONS) {
            dateS = getStringReservationDate(key, catalogs);
            id = reservIdToString(key);
          }
          setNumberFieldsQ(result, j, 2);
          setFieldQ(result, j, 0, field0, id);
          setFieldQ(result, j, 1, field1, dateS);
          free(dateS);
          free(id);
          j--;
        }
      }
    }
    free(field0); free(field1); free(field2);
}

//query 3 - calcula a avaliação média do hotel com o id passado como argumento, se existir
void Q3 (char* id_hotel, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q3(id_hotel,catalogs,result);
}

//query 4
void Q4 (char* id_hotel, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q4(id_hotel,catalogs,result);
}

//query 5
void Q5 (char* airport, Date *begin, Date *end, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q5(airport,begin,end,catalogs,result);
}

//query 6 - devolve os top N aeroportos com mais passageiros num dado ano
void Q6 (int year, int N, Catalogs* catalogs, QueryResult* result) {
  if (N <= 0) return;
  int passengers, numberAirports = getNumberAirports_catalog(catalogs);
  Heap h = createHeap(N, comparePair, comparePairAdd, NULL, destroyPair);
  int i = 0;
  while (i < numberAirports) {
    char *id = getNextAirportId_catalog(i, catalogs);
    sortAirportFlightsByDepartureDate(id, catalogs);
    passengers = getAirportPassengersYear_catalog(year, id, catalogs);
    PairIntString *airport = createPairIntString(passengers, id);
    if (addHeap(airport, h) == -1) destroyPair(airport);
    i++;
  }
  i = getHeapUsed(h)-1;
  setNumberResults(result, i+1);
  char *field0 = strdup("name"), *field1 = strdup("passengers");
  while (i >= 0) {
    PairIntString *res = removeHeap(h);
    char *p = malloc(sizeof(char)*10);
    int value = getPairValue(res);
    char *string = getPairString(res);
    sprintf(p, "%d", value);
    setNumberFieldsQ(result, i, 2);
    setFieldQ(result, i, 0, field0, string);
    setFieldQ(result, i, 1, field1, p);
    destroyPair(res);
    free(string);
    free(p);
    i--;
  }
  destroyHeap(h);
  free(field0); free(field1);
}

//query 7
void Q7 (int n, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q7(n,catalogs,result);
}

//query 8 - devolve a receita total de um hotel entre duas datas limites dadas
void Q8(char *id, char *beginDate, char *endDate, Catalogs *catalogs, QueryResult *result) {
  if (doesHotelExist(id, catalogs) == 0) return; //se o hotel não existir
  Date *begin = string_to_date(beginDate);
  Date *end = string_to_date(endDate);
  int size = getHotelReservationsSize(id, catalogs);
  int total = 0, price = 0;

  for (int i=0; i<size && getHotelReservPriceBetweenDates(id, i, &price, begin, end, catalogs); i++) { //enquanto dia limite maior ou igual a dia atual
    total += price;
    price = 0;
  }

  char *field0 = strdup("revenue");
  char *revenue = malloc(sizeof(char)*10);
  sprintf(revenue, "%d", total);
  setNumberResults(result, 1);
  setNumberFieldsQ(result, 0, 1);
  setFieldQ(result, 0, 0, field0, revenue);

  destroyDate(begin);
  destroyDate(end);
  free(field0); free(revenue);
}

//query 9 - devolve a lista de nomes de utilizadores que começam com um prefixo dado ordenada por nome e id
void Q9 (char *prefix, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q9(prefix,catalogs,result);
}

//query 10
void Q10 (int year, int month, Catalogs* catalogs, QueryResult* qresult) {
  if(year==-1){ //se a query for executada sem argumentos
     int begin = getYearFirstResults(catalogs);
     int end = getYearLastResults(catalogs);
     int y;
     for (y = begin;y<=end; y++){
        Result * result = catalogs_compute_Q10(y, -1, -1, catalogs);
        if (result!=NULL){
            addSetResult(qresult, getNumberResults(qresult), result);
        }
     }
  }
  else if (year>=BEGIN_YEAR && year<=END_YEAR && month==-1){ //se a query for executada com um argumento e esse for um ano válido
     int m = 1;
     for ( ;m<=12; m++){
        Result * result = catalogs_compute_Q10(year, m, -1, catalogs);
        if (result!=NULL){
            addSetResult(qresult, getNumberResults(qresult), result);
        }
     }
  }
  else if (year>=BEGIN_YEAR && year<=END_YEAR && month>=1 && month<=12){ //se a query for executada com dois argumentos e forem um ano e um mês válidos
     int d = 1;
     for ( ;d<=31; d++){
        Result * result = catalogs_compute_Q10(year, month, d, catalogs);
        if (result!=NULL){
            addSetResult(qresult, getNumberResults(qresult), result);
        }
     }
  }
  else{
    return;
  }
}
