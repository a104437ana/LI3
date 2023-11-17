#include <string.h>
#include <stdio.h>
#include "output.h"
#include "queries.h"
#include <stdlib.h>
#include "flight.h"
#include "hotel.h"
#include "reservation.h"
#include "user.h"
#include "utility.h"

void createOutputFile (int nCommand){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", nCommand);
  FILE* file = fopen(path, "w");
  fclose(file);
}

void printOutputQ1 (char format_flag, ResultQ1* output, int i){
  if (output==NULL) return; //se o id não existir, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   if (output->resultType==USER){
    char sex;
    if (getGender(output->result)==MALE){
      sex='M';
    }
    else{
      sex='F';
    }
    fprintf(file, "name: %s\nsex: %c\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n",getName(output->result), sex, getAge(output->result), getCountry(output->result), getPassport(output->result), getNumberFlights(output->result), getNumberReservations(output->result), getTotalSpent(output->result));
   }
   if (output->resultType==FLIGHT){
    fprintf(file, "airline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d\n",getFlightAirline(output->result), getFlightAirplane(output->result), getFlightOrigin(output->result), getFlightDestination(output->result), dateToString(getFlightScheduleDeparture(output->result)), dateToString(getFlightScheduleArrival(output->result)), getNumberPassengers(output->result), getDelay(output->result)); 
   }
   if (output->resultType==RESERVATION){
    char breakfast[6];
    if (getReservIncludesBreakfast(output->result)==true){
      strcpy(breakfast, "True");
    }
    else{
      strcpy(breakfast, "False");
    }
    fprintf(file, "hotel_id: %s\nhotel_name: %s\nhotel_stars: %c\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",getReservHotelId(output->result), getReservHotelName(output->result), getReservHotelStars(output->result), dateToString(getReservBegin(output->result)), dateToString(getReservEnd(output->result)), breakfast, getReservNights(output->result), getReservPrice(output->result));
   }
  }
  else{
   if (output->resultType==USER){
    char sex;
    if (getGender(output->result)==MALE){
      sex='M';
    }
    else{
      sex='F';
    }
    fprintf(file, "%s;%c;%d;%s;%s;%d;%d;%.3f\n",getName(output->result), sex, getAge(output->result), getCountry(output->result), getPassport(output->result), getNumberFlights(output->result), getNumberReservations(output->result), getTotalSpent(output->result));
   }
   if (output->resultType==FLIGHT){
    fprintf(file, "%s;%s;%s;%s;%s;%s;%d;%d\n",getFlightAirline(output->result), getFlightAirplane(output->result), getFlightOrigin(output->result), getFlightDestination(output->result), dateToString(getFlightScheduleDeparture(output->result)), dateToString(getFlightScheduleArrival(output->result)), getNumberPassengers(output->result), getDelay(output->result));
   }
   if (output->resultType==RESERVATION){
    char breakfast[6];
    if (getReservIncludesBreakfast(output->result)==true){
      strcpy(breakfast, "True");
    }
    else{
      strcpy(breakfast, "False");
    }
    fprintf(file, "%s;%s;%c;%s;%s;%s;%d;%.3f\n",getReservHotelId(output->result), getReservHotelName(output->result), getReservHotelStars(output->result), dateToString(getReservBegin(output->result)), dateToString(getReservEnd(output->result)), breakfast, getReservNights(output->result), getReservPrice(output->result));
   }
  }
  free(output);
  fclose(file);
}

void printOutputQ2 (char format_flag, Q2Type qType,ResultsQ2* output, int i){
  if (output==NULL) return; //se o id não existir, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
    if (qType==BOTH){
     for (j=0; j<output->N; j++){
       char* resultT;
       if (output->results[j]->resultType==FLIGHTS) resultT=strdup("flight");
       else resultT = strdup("reservation");
       fprintf (file, "--- %d ---\n", j);
       fprintf (file,"id: %s\ndate: %04d/%02d/%02d\ntype: %s\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j]),getBeginMonth(output->results[j]),getBeginDay(output->results[j]), resultT);
     }
    }
    else{
     if(qType==FLIGHTS){
      for (j=0; j<output->N; j++){
        fprintf (file, "--- %d ---\n", j);
        fprintf (file,"id: %s\ndate: %s\n", getFlightId(output->results[j]->result), dateToString(getFlightScheduleDeparture(output->results[j]->result)));
      }
     }
     else{
      for (j=0; j<output->N; j++){
        fprintf (file, "--- %d ---\n", j);
        fprintf (file,"id: %s\ndate: %s\n", getReservId(output->results[j]->result), dateToStringNoHours(getReservBegin(output->results[j]->result)));
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
       fprintf (file,"%s;%04d/%02d/%02d;%s\n", getIdResultQ2(output->results[j]),getBeginYear(output->results[j]),getBeginMonth(output->results[j]),getBeginDay(output->results[j]), resultT);
     }
    }
    else{
     if(qType==FLIGHTS){
      for (j=0; j<output->N; j++){
        fprintf (file,"%s;%s\n", getFlightId(output->results[j]->result), dateToStringNoHours(getFlightScheduleDeparture(output->results[j]->result)));
      }
     }
     else{
      for (j=0; j<output->N; j++){
        fprintf (file,"%s;%s\n", getReservId(output->results[j]->result), dateToString(getReservBegin(output->results[j]->result)));
      }
     }
    } 
   }
  free(output);
  fclose(file);
}

void printOutputQ3 (char format_flag, double output, int i){
  if (output==-1) return; //se o id não existir, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   fprintf (file,"rating: %.3f\n", output);
  }
  else{
   fprintf (file,"%f\n", output);
  }
  fclose(file);
}

void printOutputQ4 (char format_flag, ResultsQ4* output, int i){
  if (output==NULL) return; //se o id não existir, não escreve nada
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
     for (j=0; j<output->N; j++){
       fprintf (file, "--- %d ---\n", j);
       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n",getReservId(output->results[j]), dateToString(getReservBegin(output->results[j])), dateToString(getReservEnd(output->results[j])), getReservUserId(output->results[j]), getReservUserClassification(output->results[j]), getReservPrice(output->results[j]));
     }
    }
  else{
     for (j=0; j<output->N; j++){
        fprintf(file, "%s;%s;%s;%s;%d;%.3f\n",getReservId(output->results[j]), dateToString(getReservBegin(output->results[j])), dateToString(getReservEnd(output->results[j])), getReservUserId(output->results[j]), getReservUserClassification(output->results[j]), getReservPrice(output->results[j]));
     }
  }
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

void printOutputQ8 (char format_flag, double output, int i){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   fprintf (file,"revenue: %.3f\n", output);
  }
  else{
   fprintf (file,"%f\n", output);
  }
  fclose(file);
}

void printOutputQ9 (char format_flag, OrdList* list, int i) {
  int N = getOrdListSize(list);
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
     for (j=0; j<N; j++){
       fprintf (file, "--- %d ---\n", j);
       UserByName* user = getDataOrdList(list,i);
       char* id = getId_UserByName(user);
       char* name = getName_UserByName(user);
       fprintf (file,"id: %s\nname: %s\n", id, name);
       free(id);
       free(name);
     }
    }
  else{
     for (j=0; j<N; j++){
       UserByName* user = getDataOrdList(list,i);
       char* id = getId_UserByName(user);
       char* name = getName_UserByName(user);
       fprintf (file,"%s;%s\n", id, name);
       free(id);
       free(name);
     }
  }
  fclose(file);
}