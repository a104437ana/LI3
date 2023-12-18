#include "output.h"

//cria o ficheiro para o output de um comando
void createOutputFile (int nCommand){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", nCommand);
  FILE* file = fopen(path, "w");
  fclose(file);
}

//imprime o output da query 1
void printOutputQ1 (char format_flag, ResultQ1* output, int i, HotelsManager *hotelsCatalog){
  Hashtable *hotels = getHashtableHotelsCatalog(hotelsCatalog); //provisório
  if (output==NULL) return; //se o id não existir ou pertencer a um utilizador inválido, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   if (output->resultType==USER){
    char sex;
    if (getGender(output->result)==MALE) sex='M';
    else sex='F';
    fprintf(file, "name: %s\nsex: %c\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n",getName(output->result), sex, getAge(output->result), getCountry(output->result), getPassport(output->result), getNumberFlights(output->result), getNumberReservations(output->result), getTotalSpent(output->result));
   }
   if (output->resultType==FLIGHT){
    char * origin = getFlightOrigin(output->result);
    char * dest = getFlightDestination(output->result);
    char * dep = dateToString(getFlightScheduleDeparture(output->result));
    char * arrival = dateToString(getFlightScheduleArrival(output->result));
    fprintf(file, "airline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d\n",getFlightAirline(output->result), getFlightAirplane(output->result), origin, dest, dep, arrival, getNumberPassengers(output->result), getDelay(output->result)); 
    free(origin); free(dest); free(dep); free (arrival);
   }
   if (output->resultType==RESERVATION){
    char breakfast[6];
    if (getReservIncludesBreakfast(output->result)==true) strcpy(breakfast, "True");
    else strcpy(breakfast, "False");
    char * begin = dateToStringNoHours(getReservBegin(output->result));
    char * end = dateToStringNoHours(getReservEnd(output->result));
    fprintf(file, "hotel_id: %s\nhotel_name: %s\nhotel_stars: %c\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",getReservHotelId(output->result), getReservHotelName(output->result, hotels), getReservHotelStars(output->result, hotels), begin, end, breakfast, getReservNights(output->result), getReservPrice(output->result, hotels));
    free(begin); free(end);
   }
  }
  else{
   if (output->resultType==USER){
    char sex;
    if (getGender(output->result)==MALE) sex='M';
    else sex='F';
    fprintf(file, "%s;%c;%d;%s;%s;%d;%d;%.3f\n",getName(output->result), sex, getAge(output->result), getCountry(output->result), getPassport(output->result), getNumberFlights(output->result), getNumberReservations(output->result), getTotalSpent(output->result));
   }
   if (output->resultType==FLIGHT){
    char * origin = getFlightOrigin(output->result);
    char * dest = getFlightDestination(output->result);
    char * dep = dateToString(getFlightScheduleDeparture(output->result));
    char * arrival = dateToString(getFlightScheduleArrival(output->result));
    fprintf(file, "%s;%s;%s;%s;%s;%s;%d;%d\n",getFlightAirline(output->result), getFlightAirplane(output->result), origin, dest, dep, arrival, getNumberPassengers(output->result), getDelay(output->result));
    free(origin); free(dest); free(dep); free (arrival);
   }
   if (output->resultType==RESERVATION){
    char breakfast[6];
    if (getReservIncludesBreakfast(output->result)==true) strcpy(breakfast, "True");
    else strcpy(breakfast, "False");
    char * begin = dateToStringNoHours(getReservBegin(output->result));
    char * end = dateToStringNoHours(getReservEnd(output->result));
    fprintf(file, "%s;%s;%c;%s;%s;%s;%d;%.3f\n",getReservHotelId(output->result), getReservHotelName(output->result, hotels), getReservHotelStars(output->result, hotels), begin, end, breakfast, getReservNights(output->result), getReservPrice(output->result, hotels));
    free(begin); free(end);
   }
  }
  free(output);
  fclose(file);
}

//imprime o output da query 2
void printOutputQ2 (char format_flag, Q2Type qType,ResultsQ2* output, int i){
  if (output==NULL) return; //se o id não existir ou pertencer a um utilizador inativo, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
    if (qType==BOTH){
     for (j=0; j<output->N; j++){
       char* resultT; //se o resultado é um voo ou uma reserva
       if (output->results[j]->resultType==FLIGHTS) resultT=strdup("flight");
       else resultT = strdup("reservation");
       fprintf (file, "--- %d ---\n", (j+1));
       fprintf (file,"id: %s\ndate: %04d/%02d/%02d\ntype: %s\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j], NULL),getBeginMonth(output->results[j], NULL),getBeginDay(output->results[j], NULL), resultT);
       if (j<output->N-1) fprintf (file, "\n"); //se não for o último resultado, escreve um newline
       free(resultT);
     }
    }
    else{
     if(qType==FLIGHTS){
      for (j=0; j<output->N; j++){
        fprintf (file, "--- %d ---\n", (j+1));
        fprintf (file,"id: %s\ndate: %04d/%02d/%02d\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j], NULL),getBeginMonth(output->results[j], NULL),getBeginDay(output->results[j], NULL));
        if (j<output->N-1) fprintf (file, "\n");
      }
     }
     else{
      for (j=0; j<output->N; j++){
        fprintf (file, "--- %d ---\n", (j+1));
        fprintf (file,"id: %s\ndate: %04d/%02d/%02d\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j], NULL),getBeginMonth(output->results[j], NULL),getBeginDay(output->results[j], NULL));
        if (j<output->N-1) fprintf (file, "\n");
      }
     }
    }
  }
  else{
    if (qType==BOTH){
     for (j=0; j<output->N; j++){
       char* resultT;
       if (output->results[j]->resultType==FLIGHTS) resultT=strdup("flight");
       else resultT = strdup("reservation");
       fprintf (file,"%s;%04d/%02d/%02d;%s\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j], NULL),getBeginMonth(output->results[j], NULL),getBeginDay(output->results[j], NULL), resultT);
       free(resultT);
      }
     }
     else if(qType==FLIGHTS){
      for (j=0; j<output->N; j++){
        fprintf (file,"%s;%04d/%02d/%02d\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j], NULL),getBeginMonth(output->results[j], NULL),getBeginDay(output->results[j], NULL));
      }
     }
     else{
      for (j=0; j<output->N; j++){
        fprintf (file,"%s;%04d/%02d/%02d\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j], NULL),getBeginMonth(output->results[j], NULL),getBeginDay(output->results[j], NULL));
      }
     }
  } 
  free(output->results);
  free(output);
  fclose(file);
}

//imprime o output da query 3
void printOutputQ3 (char format_flag, Results* results, int i){
  if (getRating(results)==-1) return; //se o id não existir, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   fprintf (file,"rating: %.3f\n", getRating(results));
  }
  else{
   fprintf (file,"%.3f\n", getRating(results));
  }
  fclose(file);
}

//imprime o output da query 4
void printOutputQ4 (char format_flag, ResultsQ4* output, int i, HotelsManager *hotelsCatalog){
  Hashtable *hotels = getHashtableHotelsCatalog(hotelsCatalog); //provisório
  if (output==NULL) return; //se o id não existir, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
     for (j=0; j<output->N; j++){
      int rating = getReservUserClassification(output->results[j]);
      if (rating<0){
       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
       fprintf (file, "--- %d ---\n", (j+1));
       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\ntotal_price: %.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), getReservPrice(output->results[j], hotels));
       if (j<output->N-1) fprintf (file, "\n");
       free(begin); free(end);
      }
      else{
       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
       fprintf (file, "--- %d ---\n", (j+1));
       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), rating, getReservPrice(output->results[j], hotels));
       if (j<output->N-1) fprintf (file, "\n");
       free(begin); free(end);
      }
     }
  }
  else{
     for (j=0; j<output->N; j++){
      int rating = getReservUserClassification(output->results[j]);
      if (rating<0){
       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
       fprintf(file, "%s;%s;%s;%s;%.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), getReservPrice(output->results[j], hotels));
       free(begin); free(end);
      }
      else{
       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
       fprintf(file, "%s;%s;%s;%s;%d;%.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), rating, getReservPrice(output->results[j], hotels));
       free(begin); free(end);
      }
     }
  }
  free(output->results);
  free(output);
  fclose(file);
}

//void printOutputQ5 (char format_flag, ResultsQ5* output, int i){
//  char path[100];
//  sprintf (path, "./Resultados/command%d_output.txt", i);
//  FILE* file = fopen(path, "w");
//  int j;
//  if (format_flag=='F'){
//     for (j=0; j<output->N; j++){
//       fprintf (file, "--- %d ---\n", j);
//       fprintf (file,"%s\n", output->results[j]); //incompleto
//     }
//    }
//  else{
//     for (j=0; j<output->N; j++){
//       fprintf (file,"%s\n", output->results[j]); //incompleto
//     }
//  }
//  fclose(file);
//}

//void printOutputQ6 (char format_flag, ResultsQ6* output, int i){
//  char path[100];
//  sprintf (path, "./Resultados/command%d_output.txt", i);
//  FILE* file = fopen(path, "w");
//  int j;
//  if (format_flag=='F'){
//     for (j=0; j<output->N; j++){
//       fprintf (file, "--- %d ---\n", j);
//       fprintf (file,"%s\n", output->results[j]); //incompleto
//     }
//    }
//  else{
//     for (j=0; j<output->N; j++){
//       fprintf (file,"%s\n", output->results[j]); //incompleto
//     }
//  }
//  fclose(file);
//}

//void printOutputQ7 (char format_flag, ResultsQ7* output, int i){
//  char path[100];
//  sprintf (path, "./Resultados/command%d_output.txt", i);
//  FILE* file = fopen(path, "w");
//  int j;
//  if (format_flag=='F'){
//     for (j=0; j<output->N; j++){
//       fprintf (file, "--- %d ---\n", j);
//       fprintf (file,"%s\n", output->results[j]); //incompleto
//     }
//    }
//  else{
//     for (j=0; j<output->N; j++){
//       fprintf (file,"%s\n", output->results[j]); //incompleto
//     }
//  }
//  fclose(file);
//}

//imprime o output da query 8
void printOutputQ8 (char format_flag, int output, int i){
  if (output==-1) return; //se o id não existir, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   fprintf (file,"revenue: %d\n", output);
  }
  else{
   fprintf (file,"%d\n", output);
  }
  fclose(file);
}

//imprime o output da query 9
void printOutputQ9 (char format_flag, OrdList* list, int i) {
  int N = getOrdListSize(list);
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
     for (j=0; j<N; j++){
       fprintf (file, "--- %d ---\n", (j+1));
       User* user = getDataOrdList(list,j);
       char* id = strdup(getUserId(user));
       char* name = strdup(getName(user));
       fprintf (file,"id: %s\nname: %s\n", id, name);
       if (j<N-1) fprintf (file,"\n");
       free(id);
       free(name);
     }
    }
  else{
     for (j=0; j<N; j++){
       User* user = getDataOrdList(list,j);
       char* id = strdup(getUserId(user));
       char* name = strdup(getName(user));
       fprintf (file,"%s;%s\n", id, name);
       free(id);
       free(name);
     }
  }
  fclose(file);
}