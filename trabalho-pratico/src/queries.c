#include "queries.h"

//calcula a idade de um utilizador em anos
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
     int res = ((realDep->hour->hours)-(scheduleDep->hour->hours))*3600 + ((realDep->hour->minutes)-(scheduleDep->hour->minutes))*60 +((realDep->hour->seconds)-(scheduleDep->hour->seconds));
     return res;
}

//calcula o número de noites de uma reserva
int getReservNights(Reservation* reservation){
     Date* begin = getReservBegin(reservation);
     Date* end = getReservEnd(reservation);
     int res = (end->day) - (begin->day);
     return res;
}

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
  if (res->resultType == FLIGHTS) return ((getFlightScheduleDeparture((Flight *)res->result))->day);
  else return (getReservBeginDay((Reservation *)res->result));
}

//devolve o mês de início de uma reserva ou de um voo
int getBeginMonth(void* data, Hashtable *lookupTable){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return ((getFlightScheduleDeparture((Flight *)res->result))->month);
  else return (getReservBeginMonth((Reservation *)res->result));
}

//devolve o ano de início de uma reserva ou de um voo
int getBeginYear(void* data, Hashtable *lookupTable){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return ((getFlightScheduleDeparture((Flight *)res->result))->year);
  else return (getReservBeginYear((Reservation *)res->result));
}

//devolve o segundo de início de um voo
int getBeginSeconds(void* data, Hashtable *lookupTable) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return ((getFlightScheduleDeparture((Flight *)res->result))->hour->seconds);
  else return (0);
}

//devolve o minuto de início de um voo
int getBeginMinutes(void* data, Hashtable *lookupTable) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return ((getFlightScheduleDeparture((Flight *)res->result))->hour->minutes);
  else return (0);
}

//devolve a hora de início de um voo
int getBeginHours(void* data, Hashtable *lookupTable) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return ((getFlightScheduleDeparture((Flight *)res->result))->hour->hours);
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
  if (reservEnd_begin > 0) return -1; //se a data de fim da reserva for maior que a de inicio do limite
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
  if (reservBegin_begin <= 0 && reservEnd_end >= 0) //caso contrário retiramos o dia adicionado
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

//verifica se uma string é um prefixo do nome de um utilizador
int isPrefix(void *prefix, void *user) {
  int compare, prefixSize = strlen((char *) prefix);
  char *namePrefix = malloc(sizeof(char) * (prefixSize + 1));
  char *name = getName((User *) user); //nome do utilizador
  namePrefix = strncpy(namePrefix, (char *) name, prefixSize); //prefixo do utilizador com o mesmo tamanho do prefixo a comparar
  namePrefix[prefixSize] = '\0';
  compare = strcoll((char *) prefix, (char *) namePrefix); //compara os dois prefixos
  free(namePrefix); //liberta o prefixo do utilizador

  return compare;
}

//query 1 - retorna o utilizador, reserva ou voo com o id passado como argumento (se existir e não for um utilizador inativo)
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
void Q3 (char* id_hotel, Catalogs* catalogs, Results* results) {
  return catalogs_compute_Q3(id_hotel,catalogs,results);
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

//query 4 - devolve a lista de reservas do hotel com o id passado como argumento, se existir
ResultsQ4* Q4(char *id, HotelsManager *hotelsCatalog, ReservationsManager *reservationsCatalog){
    Hotel *hotel = getHotelCatalog(getHashtableHotelsCatalog(hotelsCatalog), hashFunction(id), id);
    if (hotel==NULL) return NULL; //se o id não existir
    int i;
    ResultsQ4 *results = malloc(sizeof(ResultsQ4));
    OrdList *reservations = getHotelOrdList(hotel);
    if (getOrdListOrd(reservations) == 0) sortHotelReservationsByDate(hotel, getHashtableReservCatalog(reservationsCatalog));
    int listSize = getOrdListSize(reservations);
    results->N = listSize;
    results->results = malloc(sizeof(Reservation*)*listSize);
    for(i=0;i<listSize; i++){
      char *id = getDataOrdList(reservations, i);
      unsigned int key = hashFunction(id);
      Reservation * data = (Reservation *) getData(getHashtableReservCatalog(reservationsCatalog), key, id);
      results->results[listSize-i-1] = data; //coloca os dados na lista resposta do mais recente para o mais antigo
    }
    return results;
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
    reservBegin = getReservBegin(reservation); //dia inicio da reserva
    reservEnd = getReservEnd(reservation); //dia fim da reserva
  }

  return total;
}

//query 9 - devolve a lista de nomes de utilizadores que começam com um prefixo dado ordenada por nome e id
OrdList *Q9(char *prefix, UsersManager *usersCatalog) {
  OrdList *result = createOrdList(100);
  OrdList *usersByName = getUsersByName(usersCatalog); //obtem lista ordenada por nome dos utilizadores
  int size = getOrdListSize(usersByName);
  int i = searchDataOrdList(usersByName, prefix, isPrefix, 0, 1); //obtem primeiro indice da lista onde o nome começa com o prefixo dado
  if (i == -1) return result; //se não existir nomes começados pelo prefixo dado
  User *user = getDataOrdList(usersByName, i);
  while (i < size && isPrefix(prefix, user) == 0) { //enquanto um nome começar pelo prefixo dado
    addOrdList(result, user); //adiciona à lista resultado
    i++;
    user = getDataOrdList(usersByName, i);
  }

  return result;
}