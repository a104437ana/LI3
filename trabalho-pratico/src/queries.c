#include "queries.h"

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
int getBeginDay(void* data, Hashtable *lookupTable){
  ResultQ2* res = (ResultQ2*) data;
  Date* date = getFlightScheduleDeparture((Flight *)res->result);
  int i = date->day;
  free(date);
  if (res->resultType == FLIGHTS) return (i);
  else return (getReservBeginDay((Reservation *)res->result));
}

//devolve o mês de início de uma reserva ou de um voo
int getBeginMonth(void* data, Hashtable *lookupTable){
  ResultQ2* res = (ResultQ2*) data;
  Date* date = getFlightScheduleDeparture((Flight *)res->result);
  int i = date->month;
  free(date);
  if (res->resultType == FLIGHTS) return (i);
  else return (getReservBeginMonth((Reservation *)res->result));
}

//devolve o ano de início de uma reserva ou de um voo
int getBeginYear(void* data, Hashtable *lookupTable){
  ResultQ2* res = (ResultQ2*) data;
  Date* date = getFlightScheduleDeparture((Flight *)res->result);
  int i = date->year;
  free(date);
  if (res->resultType == FLIGHTS) return i;
  else return (getReservBeginYear((Reservation *)res->result));
}

//devolve o segundo de início de um voo
int getBeginSeconds(void* data, Hashtable *lookupTable) {
  ResultQ2* res = (ResultQ2*) data;
  Date* date = getFlightScheduleDeparture((Flight *)res->result);
  int i = getSeconds(date);
  free(date);
  if (res->resultType == FLIGHTS) return i;
  else return (0);
}

//devolve o minuto de início de um voo
int getBeginMinutes(void* data, Hashtable *lookupTable) {
  ResultQ2* res = (ResultQ2*) data;
  Date* date = getFlightScheduleDeparture((Flight *)res->result);
  int i = getMinutes(date);
  free(date);
  if (res->resultType == FLIGHTS) return (i);
  else return (0);
}

//devolve a hora de início de um voo
int getBeginHours(void* data, Hashtable *lookupTable) {
  ResultQ2* res = (ResultQ2*) data;
  Date* date = getFlightScheduleDeparture((Flight *)res->result);
  int i = getHours(date);
  free(date);
  if (res->resultType == FLIGHTS) return (i);
  else return (0);
}

//devolve o id de uma reserva ou voo
char * getIdResultQ2(ResultQ2* data){
  if (data->resultType == FLIGHTS) return (getFlightId((Flight *)data->result));
  else return (getReservId((Reservation *)data->result));
}

//liberta dados do tipo ResultQ2
void destroyResultQ2(void * data){
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

//calcula o numero de dias (noites) de uma reserva que estão dentro de duas datas limites
int daysInsideDates(Date *begin, Date *end, Date *reservBegin, Date *reservEnd) {
  int nDays = 0;
  int reservBegin_begin, reservEnd_end, reservBegin_end, reservEnd_begin;
  Date *lower, *higher;
  reservEnd_begin = compareDates(reservEnd, begin); //compara a data de fim da reserva e inicio do limite
  if (reservEnd_begin >= 0) return -1; //se a data de fim da reserva for maior que a de inicio do limite
  reservBegin_begin = compareDates(reservBegin, begin); //compara a data de inicio da reserva e inicio do limite
  reservEnd_end = compareDates(reservEnd, end); //compara a data de fim da reserva e fim do limite
  reservBegin_end  = compareDates(reservBegin, end); //compara a data de inicio da reserva e fim do limite
  if (reservBegin_end < 0) return -1; //se a data de inicio da reserva for maior que a de fim do limite

  //se a data de inicio da reserva for maior que a de inicio do limite
  if (reservBegin_begin >= 0) lower = begin; //a primeira data de contagem é a data de inicio do limite
  else lower = reservBegin; //caso contrário é a data de inicio da reserva
  //se a data de fim da reserva for maior que a de fim do limite
  if (reservEnd_end <= 0) higher = end; //a última data de contagem é a data de fim do limite
  else higher = reservEnd; //caso contrário é a data de fim da reserva
  //o número de dias é a diferença entre as datas de contagem
  nDays = daysBetweenDates(lower, higher) + 1; //caso ambas as datas da reserva não estiverem dentro do intervalo de contagem temos que adicionar mais um dia
  if (reservEnd_end >= 0) //caso contrário retiramos o dia adicionado
    nDays --;

  return nDays;
}

//calcula o preço de uma reserva entre duas datas limites
int getReservPriceBetweenDates(Reservation *reservation, Date *begin, Date *end, Date *reservBegin, Date *reservEnd) {
  int pricePerNight = getReservPricePerNight(reservation); //preço por noite da reserva
  int nDays = daysInsideDates(begin, end, reservBegin, reservEnd); //número de noites entre as datas limites
  if (nDays == -1) return 0;
  int total = (pricePerNight * nDays); //preço total
  return total;
}

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
char *sameLenPrefix(char *prefix, char *name) {
  unsigned char *up = (unsigned char *) prefix, *un = (unsigned char *) name;
  int i = 0, j = 0, p = 0, n = 0, e = 0;
  while (up[i] != '\0' && un[j] != '\0') {
    if (up[i] == un[j]) e++;
    if (up[i] > 128) {p++; i+=2;}
    else if (up[i] != '\0') i++;
    if (un[j] > 128) {n++; j+=2;}
    else if (un[j] != '\0') j++;
  }

  char *namePrefix;
  if (i == e + 1) return NULL;
  else if (i < j) {
    if (n > p) {i += n;}
    namePrefix = malloc(sizeof(char) * (i + 1));
    //namePrefix = 
    strncpy(namePrefix, name, i);
    namePrefix[i] = '\0';
  }
  else {
    int len;
    if (n > p) len = i + (n - p);
    else len = i;
    namePrefix = malloc(sizeof(char) * (len + 1));
    //namePrefix = 
    strncpy(namePrefix, name, len);
    namePrefix[len] = '\0';
  }

  return namePrefix;
}
int prefixSearch(void *prefixVoid, void *user) {
  int compare;
  char *prefix = (char *) prefixVoid;
  char *name = getName((User *) user); //nome do utilizador
  char *namePrefix = sameLenPrefix(prefix, name);
  if (namePrefix == NULL) return 0;
  compare = strcoll(prefix, namePrefix); //compara os dois prefixos
  free(namePrefix); //liberta o prefixo do utilizador
  free(name);
  return compare;
}
int prefixSearchBack(void *prefixVoid, void *user) {
  int compare;
  char *prefix = (char *) prefixVoid;
  char *name = getName((User *) user); //nome do utilizador
  compare = strcoll(prefix, name); //compara os dois prefixos
  free(name);
  return compare;
}
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
ResultsQ2* Q2(char *id, Q2Type type, UsersManager *usersCatalog){
    User *user = getUserCatalog(usersCatalog, hashFunction(id), id);
    if (user==NULL) return NULL; //se o id não existir
    if (getAccountStatus(user)==false) return NULL; //se o utilizador não estiver ativo
    int i;
    ResultsQ2 *results = malloc(sizeof(ResultsQ2));
    if (type==FLIGHTS){ //se for pedida a lista de voos
      OrdList* userList = getUserList(user);
      if (getOrdListOrd(userList) == 0) sortUserList(user, NULL);
      int listSize = getOrdListSize(userList);
      int nFlights = getNumberFlights(user);
      results->N = nFlights;
      results->results = malloc(sizeof(ResultQ2)*nFlights);
      int j = nFlights-1;
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
         if (data->resultType==FLIGHTS){ //verifica se a posição atual tem um voo ou uma reserva
           results->results[j] = data;  //coloca os dados na lista resposta do mais recente para o mais antigo
           j--;
         }
      }
    }
    else if (type==RESERVATIONS){ //se for pedida a lista de reservas
      OrdList* userList = getUserList(user);
      if (getOrdListOrd(userList) == 0) sortUserList(user, NULL);
      int listSize = getOrdListSize(userList);
      int nReservations = getNumberReservations(user);
      results->N = nReservations;
      results->results = malloc(sizeof(ResultQ2)*nReservations);
      int j = nReservations-1;
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
         if (data->resultType==RESERVATIONS){ //verifica se a posição atual tem um voo ou uma reserva
           results->results[j] = data; //coloca os dados na lista resposta do mais recente para o mais antigo
           j--;
         }
      }
    }
    else{ //se for pedida a lista de voos e reservas
      OrdList* userList = getUserList(user);
      if (getOrdListOrd(userList) == 0) sortUserList(user, NULL);
      int listSize = getOrdListSize(userList);
      results->N = listSize;
      results->results = malloc(sizeof(ResultQ2)*listSize);
      for(i=0;i<listSize; i++){
        ResultQ2 * data = (ResultQ2 *)getDataOrdList(userList, i);
        results->results[listSize-i-1] = data; //coloca os dados na lista resposta do mais recente para o mais antigo
      }
    }
    return results;
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
//    if (getOrdListOrd(reservations) == 0) sortHotelReservationsByDate(hotel, getHashtableReservCatalog(reservationsCatalog));
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

void Q7 (int n, Catalogs* catalogs, QueryResult* result) {
  catalogs_compute_Q7(n,catalogs,result);
}

//quey 8 - devolve a receita total de um hotel entre duas datas limites dadas
int Q8(char *id, Date *begin, Date *end, HotelsManager *hotelsCatalog, ReservationsManager *reservationsCatalog) {
  Hotel *hotel = getHotelCatalog(getHashtableHotelsCatalog(hotelsCatalog), hashFunction(id), id);
  if (hotel==NULL) return -1; //se o hotel não existir
  OrdList *reservations = getHotelOrdList(hotel);
  if (getOrdListOrd(reservations) == 0) sortHotelReservationsByDate(hotel, getHashtableReservCatalog(reservationsCatalog));
  int size = getOrdListSize(reservations);
  char *id_reserv = getDataOrdList(reservations, 0);
  unsigned int key = hashFunction(id_reserv);
  Reservation *reservation = (Reservation *) getData(getHashtableReservCatalog(reservationsCatalog), key, id_reserv);
  Date *reservBegin = getReservBegin(reservation), *reservEnd = getReservEnd(reservation);
  int total = 0;

  for (int i=0; i<size && compareDates(reservBegin, end) >= 0; i++) { //enquanto dia limite maior ou igual a dia atual
    total += getReservPriceBetweenDates(reservation, begin, end, reservBegin, reservEnd);
    id_reserv = getDataOrdList(reservations, i+1);
    key = hashFunction(id_reserv);
    reservation = (Reservation *) getData(getHashtableReservCatalog(reservationsCatalog), key, id_reserv); //proxima reserva
    free(reservBegin);
    free(reservEnd);
    reservBegin = getReservBegin(reservation); //dia inicio da reserva
    reservEnd = getReservEnd(reservation); //dia fim da reserva
  }
  free(reservBegin);
  free(reservEnd);
  return total;
}
////quey 8 - devolve a receita total de um hotel entre duas datas limites dadas
//int Q8(char *id, Date *begin, Date *end, Catalogs *catalogs) {
//  int size = getHotelReservationsSize(id, catalogs);
//  int total = 0, price = 0, valid = 0;
//
//  for (int i=0; i<size && valid = getHotelReservPriceBetweenDates(id, i, &price, begin, end); i++) { //enquanto dia limite maior ou igual a dia atual
//    total += price;
//    price = 0;
//  }
//
//  return total;
//}

//query 9 - devolve a lista de nomes de utilizadores que começam com um prefixo dado ordenada por nome e id
OrdList *Q9(char *prefix, UsersManager *usersCatalog) {
  OrdList *result = createOrdList();
  OrdList *usersByName = getUsersByName(usersCatalog); //obtem lista ordenada por nome dos utilizadores
  int size = getOrdListSize(usersByName);
  int i = searchDataOrdList(usersByName, prefix, prefixSearch, 0, prefixSearchBack); //obtem primeiro indice da lista onde o nome começa com o prefixo dado
  if (i == -1) return result; //se não existir nomes começados pelo prefixo dado
  User *user = getDataOrdList(usersByName, i);
  int validPrefix = isPrefix(prefix, user), firstLetterCheck = sameFirstLetter(prefix, user);
  while (i < size && (validPrefix == 0 || firstLetterCheck == 0)) { //enquanto um nome começar pelo prefixo dado
    user = getDataOrdList(usersByName, i);
    validPrefix = isPrefix(prefix, user);
    firstLetterCheck = sameFirstLetter(prefix, user);
    if (validPrefix == 0)
      addOrdList(result, user); //adiciona à lista resultado
    i++;
  }

  return result;
}