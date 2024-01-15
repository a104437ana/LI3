#include "queries.h"
#include "heap.h"

/*calcula a idade de um utilizador em anos
int getAge(User* user){
  Date *birthdate = getBirth(user);
  bool birthday; //se o aniversário do utilizador é ou não antes da data atual
  if(MONTH<birthdate->month) birthday=false;
  else if(MONTH>birthdate->month) birthday=true;
  else{
    if(DAY<birthdate->day) birthday=false;
    else birthday=true;
  }

  if(birthday==true) return (YEAR-birthdate->year);
  else return (YEAR-birthdate->year-1);
}

//retorna o número de passageiros num voo
int getNumberPassengers(Flight* flight){
    OrdList* passengers = getPassengers(flight);
    return(getOrdListSize(passengers));
}

//calcula o atrado de um voo em segundos
int getDelay(Flight* flight){
     Date* scheduleDep = getFlightScheduleDeparture(flight);
     Date* realDep = getFlightRealDeparture(flight);
     int res = ((getHours(realDep))-(getHours(scheduleDep)))*3600 + ((getMinutes(realDep))-(getMinutes(scheduleDep)))*60 +((getSeconds(realDep))-(getSeconds(scheduleDep)));
     return res;
}

//calcula o número de noites de uma reserva
int getReservNights(Reservation* reservation){
     Date* begin = getReservBegin(reservation);
     Date* end = getReservEnd(reservation);
     int res = (end->day) - (begin->day);
     return res;
}
*/
//calcula o preço de uma reserva
double getReservPrice(Reservation* reservation, Hashtable *hotels){
     int ppn = getReservPricePerNight(reservation); //preço por noite
     int nnights = getReservNights(reservation); //número de noites
     int cityTax = getReservCityTax(reservation, hotels); //taxa turística
     double res = (ppn*nnights)+(((float)(ppn*nnights)/100)*cityTax);
     return res;
}

//devolve o dia de início de uma reserva ou de um voo
int getBeginDay(void* data, void *catalog){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(0, res->id, (Catalogs *) catalog));
  else return (getReservationBegin(0, res->id, (Catalogs *) catalog));
}

//devolve o mês de início de uma reserva ou de um voo
int getBeginMonth(void* data, void *catalog){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(1, res->id, (Catalogs *) catalog));
  else return (getReservationBegin(1, res->id, (Catalogs *) catalog));
}

//devolve o ano de início de uma reserva ou de um voo
int getBeginYear(void* data, void *catalog){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(2, res->id, (Catalogs *) catalog));
  else return (getReservationBegin(2, res->id, (Catalogs *) catalog));
}

//devolve o segundo de início de um voo
int getBeginSeconds(void* data, void *catalog) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(3, res->id, (Catalogs *) catalog));
  else return (0);
}

//devolve o minuto de início de um voo
int getBeginMinutes(void* data, void *catalog) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(4, res->id, (Catalogs *) catalog));
  else return (0);
}

//devolve a hora de início de um voo
int getBeginHours(void* data, void *catalog) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(5, res->id, (Catalogs *) catalog));
  else return (0);
}

//devolve o id de uma reserva ou voo
char * getIdResultQ2(ResultQ2* data){
  return data->id;
//  if (data->resultType == FLIGHTS) return (getFlightId((Flight *)data->result));
//  else return (getReservId((Reservation *)data->result));
}

//liberta dados do tipo ResultQ2
void destroyResultQ2(void * data){
  free(((ResultQ2*)data)->id);
  free((ResultQ2*)data);
}

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
/*
int sameFirstLetter(char *prefix, User *user) {
  int compare = 1;
  char *name = getName(user);
  char c1 = prefix[0], c2 = name[0];
  if (c1 == c2) compare = 0;
  else if (c1 == 'A' || c1 == 'E' || c1 == 'I' || c1 == 'O' || c1 == 'U' ||
           c2 == 'A' || c2 == 'E' || c2 == 'I' || c2 == 'O' || c2 == 'U') compare = 0;
  free(name);
  return compare;
}
*/
/*
//verifica se uma string é um prefixo do nome de um utilizador
int isPrefix(void *prefix, void *user) {
  int compare, prefixSize = strlen((char *) prefix), nameSize;
  char *namePrefix = malloc(sizeof(char) * (prefixSize + 1));
  char *name = getName((User *) user); //nome do utilizador
  nameSize = strlen(name);
  if (nameSize >= prefixSize) {
    namePrefix = strncpy(namePrefix, (char *) name, prefixSize); //prefixo do utilizador com o mesmo tamanho do prefixo a comparar
    namePrefix[prefixSize] = '\0';
  }
  else
    namePrefix = strdup(name);
//  printf("  %s - %s\n", (char *) prefix, namePrefix);
  compare = strcoll((char *) prefix, (char *) namePrefix); //compara os dois prefixos
  free(namePrefix); //liberta o prefixo do utilizador
  free(name);

  return compare;
}
*/
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

/*
ResultQ1* Q1(char *id, UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,FlightsManager *flightsCatalog){
    if(same_prefix("Book", id) == 1){ //se o id for de uma reserva
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getReservCatalog(getHashtableReservCatalog(reservationsCatalog), hashFunction(id), id);
      if (result->result==NULL){ //se o id não existir
        free(result);
        return NULL;
      }
      result->resultType=RESERVATION;
      return result;
    }
    else if (id[0]>='0' && id[0]<='9'){ //se o id for de um voo
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getFlightCatalog(flightsCatalog, hashFunction(id), id);
      if (result->result==NULL){ //se o id não existir
        free(result);
        return NULL;
      }
      result->resultType=FLIGHT;
      return result;   
    }
    else{ //se o id for de um utilizador
      ResultQ1* result = malloc(sizeof(ResultQ1));
      result->result = getUserCatalog(usersCatalog, hashFunction(id), id);
      if (result->result==NULL){ //se o id não existir
        free(result);
        return NULL;
      }
      if (getAccountStatus(result->result)==false){ //se o utilizador não estiver ativo
        free(result);
        return NULL;
      }
      result->resultType=USER;
      return result;
    }
}
*/

//query 2 - retorna a lista de reservas, voos, ou ambos - conforme o argumento type - de um utilizador (se existir e não estiver inativo)
void Q2(char *id_user, Q2Type type, Catalogs *catalogs, QueryResult *result){
    int userAccountStatus = getAccountStatus(id_user, catalogs);
    if (userAccountStatus<=0) return; //se o id não existir ou o utilizador não estiver ativo
    int i, j;
    int listSize, resultSize;
    listSize = getUserListSize(0, id_user, catalogs);
    sortUserList(id_user, catalogs);
    if (type == BOTH) j = 0;
    else if (type == FLIGHTS) j = 1;
    else if (type == RESERVATIONS) j = 2;
    resultSize = getUserListSize(j, id_user, catalogs); //tamanho do tipo de lista que for pedida
    setNumberResults(result, resultSize);
    char *field0 = strdup("id"), *field1 = strdup("date"), *field2 = strdup("type");
    char *id = 0, *dateS, *typeS;
    Q2Type resultType;
    if (type==BOTH) {
      for(i=0, j=resultSize-1;j>=0; i++, j--){
        id = getUserListId((int *) &resultType, id_user, i, catalogs);
        if (resultType == FLIGHTS) {
          dateS = getStringFlightDate(id, catalogs);
          typeS = strdup("flight");
        }
        else if (resultType == RESERVATIONS) {
          dateS = getStringReservationDate(id, catalogs);
          typeS = strdup("reservation");
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
        id = getUserListId((int *) &resultType, id_user, i, catalogs);
        if (resultType==type){ //verifica se a posição atual tem um voo ou uma reserva
          if (resultType == FLIGHTS)
            dateS = getStringFlightDate(id, catalogs);
          else if (resultType == RESERVATIONS)
            dateS = getStringReservationDate(id, catalogs);
          setNumberFieldsQ(result, j, 2);
          setFieldQ(result, j, 0, field0, id);
          setFieldQ(result, j, 1, field1, dateS);
          free(dateS);
          j--;
        }
        free(id);
      }
    }
    free(field0); free(field1); free(field2);
}

//query 3 - calcula a avaliação média do hotel com o id passado como argumento, se existir
void Q3 (char* id_hotel, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q3(id_hotel,catalogs,result);
}
/*
double Q3(char *id, HotelsManager *hotelsCatalog) {
  Hotel *hotel = getHotelCatalog(getHashtableHotelsCatalog(hotelsCatalog), hashFunction(id), id);
  if (hotel==NULL) return -1; //se o id não existir
  int numberClassifications = getOrdListSize(getHotelOrdList(hotel));
  double result = getHotelRatingsSum(hotel);
  result /= numberClassifications;
  return result;
}*/

////query 4 - devolve a lista de reservas do hotel com o id passado como argumento, se existir
//ResultsQ4* Q4(char *id, HotelsManager *hotelsCatalog, ReservationsManager *reservationsCatalog){
//    Hotel *hotel = getHotelCatalog(getHashtableHotelsCatalog(hotelsCatalog), hashFunction(id), id);
//    if (hotel==NULL) return NULL; //se o id não existir
//    int i;
//    ResultsQ4 *results = malloc(sizeof(ResultsQ4));
//    OrdList *reservations = getHotelOrdList(hotel);
//    if (isOrdered(reservations) == 0) sortHotelReservationsByDate(hotel, getHashtableReservCatalog(reservationsCatalog));
//    int listSize = getOrdListSize(reservations);
//    results->N = listSize;
//    results->results = malloc(sizeof(char*)*listSize);
//    for(i=0;i<listSize; i++){
//      char *id = getDataOrdList(reservations, i);
//      results->results[listSize-i-1] = id; //coloca os dados na lista resposta do mais recente para o mais antigo
//    }
//    return results;
//}

void Q4 (char* id_hotel, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q4(id_hotel,catalogs,result);
}

void Q5 (char* airport, Date *begin, Date *end, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q5(airport,begin,end,catalogs,result);
}

struct pairIntString {int value; char *string;};

void destroyPair(void *pair) {
  free(((struct pairIntString *) pair)->string);
  free((struct pairIntString *) pair);
}

int comparePair(void *pair1, void *pair2, void *lookup) {
  struct pairIntString *p1 = (struct pairIntString *) pair1;
  struct pairIntString *p2 = (struct pairIntString *) pair2;
  int res = 0;
  if (p1->value > p2->value) res++;
  else if (p1->value < p2->value) res--;
  else res = strcoll(p1->string,p2->string) * (-1);
  return res;
}

int comparePairAdd(void *pair1, void *pair2, void *lookup) {
  struct pairIntString *p1 = (struct pairIntString *) pair1;
  struct pairIntString *p2 = (struct pairIntString *) pair2;
  int res = 0;
  if (p1->value > p2->value) res++;
  else if (p1->value < p2->value) res--;
  else res = strcoll(p1->string,p2->string);
  return res;
}

void addPair(int value, char *string, struct pairIntString *pair) {
  pair->value = value;
  pair->string = string;
}

void Q6 (int year, int N, Catalogs* catalogs, QueryResult* result) {
  if (N == 0) return;
  int passengers, numberAirports = getNumberAirports_catalog(catalogs);
  Heap h = createHeap(N, comparePair, comparePairAdd, NULL, destroyPair);
  int i = 0;
  while (i < numberAirports) {
    char *id = getNextAirportId_catalog(i, catalogs);
    sortAirportFlightsByDepartureDate_catalog(id, catalogs);
    passengers = getAirportPassengersYear_catalog(year, id, catalogs);
    struct pairIntString *airport = malloc(sizeof(struct pairIntString));
    addPair(passengers, id, airport);
    if (addHeap(airport, h) == -1) destroyPair(airport);
    i++;
  }
  i = getHeapUsed(h)-1;
  setNumberResults(result, i+1);
  char *field0 = strdup("name"), *field1 = strdup("passengers");
  while (i >= 0) {
    struct pairIntString *res = removeHeap(h);
    char *p = malloc(sizeof(char)*10);
    sprintf(p, "%d", res->value);
    setNumberFieldsQ(result, i, 2);
    setFieldQ(result, i, 0, field0, res->string);
    setFieldQ(result, i, 1, field1, p);
    destroyPair(res);
    free(p);
    i--;
  }
  destroyHeap(h);
  free(field0); free(field1);
}

void Q7 (int n, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q7(n,catalogs,result);
}

//quey 8 - devolve a receita total de um hotel entre duas datas limites dadas
void Q8(char *id, char *beginDate, char *endDate, Catalogs *catalogs, QueryResult *result) {
  if (doesHotelExist(id, catalogs) == 0) return; //se o hotel não existir
  Date *begin = string_to_date(beginDate);
  Date *end = string_to_date(endDate);
  sortHotelReservationsByDate(id, catalogs);
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
void Q9(char *prefix, Catalogs* catalogs, QueryResult* result) {
  int size = getUsersByNameSize_catalog(catalogs);
  int i = searchPrefix_catalog(prefix, catalogs);
  if (i < 0) return; //se não existir nomes começados pelo prefixo dado
  int firstLetterCheck, validPrefix = isPrefix_catalog(&firstLetterCheck, prefix, i, catalogs);
  int j = 0;
  char* field0 = strdup("id");
  char* field1 = strdup("name");
  while (i < size && (validPrefix == 0 || firstLetterCheck == 0)) { //enquanto um nome começar pelo prefixo dado
    validPrefix = isPrefix_catalog(&firstLetterCheck, prefix, i, catalogs);
    if (validPrefix == 0) {
      addResult(result, j);
      setNumberFieldsQ(result,j, 2);
      char* id = getIdUsersByName_catalog(i, catalogs); //receber os dois na mesma função para melhorar desempenho
      char* name = getNameUsersByName_catalog(i, catalogs);
      setFieldQ(result,j,0,field0,id);
      setFieldQ(result,j,1,field1,name);
      free(id); free(name);
      j++;
    }
    i++;
  }
  free(field0); free(field1); 

  return;
}

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
