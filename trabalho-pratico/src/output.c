#include "output.h"

//cria o ficheiro para o output de um comando
void createOutputFile (int nCommand){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", nCommand);
  FILE* file = fopen(path, "w");
  fclose(file);
}

//imprime o output da query 1
void printOutputQ1 (char format_flag, Results* results, int i){
  if (getQ1type(results) == 0) return; //se o id não existir ou pertencer a um utilizador inválido, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   if (getQ1type(results)==1){
    char sex;
    if (getGenderQ1(results)==MALE) sex='M';
    else sex='F';
    char* name = getNameQ1(results);
    char* country_code = getCountryCodeQ1(results);
    char* passport = getPassportQ1(results);
    fprintf(file, "name: %s\nsex: %c\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n",name, sex, getAgeQ1(results), country_code, passport, getNflightsQ1(results), getNreservsQ1(results), getTotalSpentQ1(results));
    free(name); free(country_code); free(passport);
   }
   if (getQ1type(results)==2){
    char * dep = dateToString(getScheduleDepartureQ1(results));
    char * arrival = dateToString(getScheduleArrivalQ1(results));
    char* airline = getAirlineQ1(results);
    char* plane_model = getPlaneModelQ1(results);
    char* origin = getOriginlQ1(results);
    char* destination = getDestlQ1(results);
    fprintf(file, "airline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %g\n",airline, plane_model, origin, destination, dep, arrival, getNpassengersQ1(results), getDelayQ1(results)); 
     free(dep); free (arrival); free(airline); free(plane_model); free(origin); free(destination);
   }
   if (getQ1type(results)==3){
    char breakfast[6];
    if (getIncludesBreakfastQ1(results)==true) strcpy(breakfast, "True");
    else strcpy(breakfast, "False");
    char * begin = dateToStringNoHours(getBeginDateQ1(results));
    char * end = dateToStringNoHours(getEndDateQ1(results));
    char* hotel_id = getHotelIdQ1(results);
    char* hotel_name = getHotelNameQ1(results);
    fprintf(file, "hotel_id: %s\nhotel_name: %s\nhotel_stars: %c\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",hotel_id, hotel_name, getHotelStarsQ1(results), begin, end, breakfast, getNnightsQ1(results), getTotalPriceQ1(results));
    free(begin); free(end); free(hotel_id); free(hotel_name);
   }
  }
  else{
   if (getQ1type(results)==1){
    char sex;
    if (getGenderQ1(results)==MALE) sex='M';
    else sex='F';
    char* name = getNameQ1(results);
    char* country_code = getCountryCodeQ1(results);
    char* passport = getPassportQ1(results);
    fprintf(file, "%s;%c;%d;%s;%s;%d;%d;%.3f\n",name, sex, getAgeQ1(results), country_code, passport, getNflightsQ1(results), getNreservsQ1(results), getTotalSpentQ1(results));
    free(name); free(country_code); free(passport);
   }
   if (getQ1type(results)==2){
    char * dep = dateToString(getScheduleDepartureQ1(results));
    char * arrival = dateToString(getScheduleArrivalQ1(results));
    char* airline = getAirlineQ1(results);
    char* plane_model = getPlaneModelQ1(results);
    char* origin = getOriginlQ1(results);
    char* destination = getDestlQ1(results);
    fprintf(file, "%s;%s;%s;%s;%s;%s;%d;%g\n",airline, plane_model, origin, destination, dep, arrival, getNpassengersQ1(results), getDelayQ1(results));
    free(dep); free (arrival); free(airline); free(plane_model); free(origin); free(destination);
   }
   if (getQ1type(results)==3){
    char breakfast[6];
    if (getIncludesBreakfastQ1(results)==true) strcpy(breakfast, "True");
    else strcpy(breakfast, "False");
    char * begin = dateToStringNoHours(getBeginDateQ1(results));
    char * end = dateToStringNoHours(getEndDateQ1(results));
    char* hotel_id = getHotelIdQ1(results);
    char* hotel_name = getHotelNameQ1(results);
    fprintf(file, "%s;%s;%c;%s;%s;%s;%d;%.3f\n",hotel_id, hotel_name, getHotelStarsQ1(results), begin, end, breakfast, getNnightsQ1(results), getTotalPriceQ1(results));
    free(begin); free(end); free(hotel_id); free(hotel_name);
   }
  }
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

////imprime o output da query 4
//void printOutputQ4 (char format_flag, ResultsQ4* output, int i, HotelsManager *hotelsCatalog){
//  Hashtable *hotels = getHashtableHotelsCatalog(hotelsCatalog); //provisório
//  if (output==NULL) return; //se o id não existir, não escreve nada
//  char path[100];
//  sprintf (path, "./Resultados/command%d_output.txt", i);
//  FILE* file = fopen(path, "w");
//  int j;
//  if (format_flag=='F'){
//     for (j=0; j<output->N; j++){
//      int rating = getReservUserClassification(output->results[j]);
//      if (rating<0){
//       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
//       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
//       fprintf (file, "--- %d ---\n", (j+1));
//       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\ntotal_price: %.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), getReservPrice(output->results[j], hotels));
//       if (j<output->N-1) fprintf (file, "\n");
//       free(begin); free(end);
//      }
//      else{
//       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
//       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
//       fprintf (file, "--- %d ---\n", (j+1));
//       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), rating, getReservPrice(output->results[j], hotels));
//       if (j<output->N-1) fprintf (file, "\n");
//       free(begin); free(end);
//      }
//     }
//  }
//  else{
//     for (j=0; j<output->N; j++){
//      int rating = getReservUserClassification(output->results[j]);
//      if (rating<0){
//       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
//       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
//       fprintf(file, "%s;%s;%s;%s;%.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), getReservPrice(output->results[j], hotels));
//       free(begin); free(end);
//      }
//      else{
//       char * begin = dateToStringNoHours(getReservBegin(output->results[j]));
//       char * end = dateToStringNoHours(getReservEnd(output->results[j]));
//       fprintf(file, "%s;%s;%s;%s;%d;%.3f\n",getReservId(output->results[j]), begin, end, getReservUserId(output->results[j]), rating, getReservPrice(output->results[j], hotels));
//       free(begin); free(end);
//      }
//     }
//  }
//  free(output->results);
//  free(output);
//  fclose(file);
//}

//imprime o output da query 4
void printOutputQ4 (char format_flag, Results* results, int i){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
     for (j=0; j<getResultQ4Size(results); j++){
      char* id = getResultQ4IdInd(results, j);
      int rating = getResultQ4RatingInd(results,j);
      Date * begin = getResultQ4BeginInd(results,j);
      Date * end = getResultQ4EndInd(results,j);
      char * beginS = dateToStringNoHours(begin);
      char * endS= dateToStringNoHours(end);
      char * userId = getResultQ4UserIdInd(results, j);
      if (rating<0){
       fprintf (file, "--- %d ---\n", (j+1));
       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\ntotal_price: %.3f\n",id, beginS, endS, userId, getResultQ4TotalPriceInd(results, j));
       if (j<getResultQ4Size(results)-1) fprintf (file, "\n");
       free(id); destroyDate(begin); destroyDate(end); free(beginS); free(endS); free(userId);
      }
      else{
       fprintf (file, "--- %d ---\n", (j+1));
       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n",id, beginS, endS, userId, rating, getResultQ4TotalPriceInd(results, j));
       if (j<getResultQ4Size(results)-1) fprintf (file, "\n");
       free(id); destroyDate(begin); destroyDate(end); free(beginS); free(endS); free(userId);
      }
     }
  }
  else{
     for (j=0; j<getResultQ4Size(results); j++){
      char* id = getResultQ4IdInd(results, j);
      int rating = getResultQ4RatingInd(results,j);
      Date * begin = getResultQ4BeginInd(results,j);
      Date * end = getResultQ4EndInd(results,j);
      char * beginS = dateToStringNoHours(begin);
      char * endS= dateToStringNoHours(end);
      char * userId = getResultQ4UserIdInd(results, j);
      if (rating<0){
       fprintf(file, "%s;%s;%s;%s;%.3f\n",id, beginS, endS, userId, getResultQ4TotalPriceInd(results, j));
       free(id); destroyDate(begin); destroyDate(end); free(beginS); free(endS); free(userId);
      }
      else{
       fprintf(file, "%s;%s;%s;%s;%d;%.3f\n",id, beginS, endS, userId, rating, getResultQ4TotalPriceInd(results, j));
       free(id); destroyDate(begin); destroyDate(end); free(beginS); free(endS); free(userId);
      }
     }
  }
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

/*
void printOutputQ7 (char format_flag, Results* results, int i){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  int N = getSizeQ7(results) + 1;
  if (format_flag=='F'){
     for (j=1; j<N; j++){
      if (j != 1) fprintf(file,"\n");
       fprintf (file, "--- %d ---\n", j);
       fprintf (file,"name: %s\nmedian: %g\n", output->results[j]); //incompleto
     }
    }
  else{
     for (j=1; j<N; j++){
       fprintf (file,"%s;%g\n", output->results[j]); //incompleto
     }
  }
  fclose(file);
}
*/

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