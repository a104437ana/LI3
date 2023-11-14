#include <string.h>
#include <stdio.h>
#include "output.h"
#include "queries.h"

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
    if (getGender(output->result)==M){
      sex='M';
    }
    else{
      sex='F';
    }
    fprintf(file, "name: %s\nsex: %c\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n",getName(output->result), sex, getCountry(output->result), getPassport(output->result), getNumberFlights(output->result), getNumberReservations(output->result), getTotalSpent(output->result)); //incompleto, gets de n voos, n reservas não existem
   }
   if (output->resultType==FLIGHT){
    fprintf(file, "airline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %.3f\n",getFlightAirline(output->result), getFlightAirplane(output->result), getFlightOrigin(output->result), getFlightDestination(output->result), dateToString(getFlightScheduleDeparture(output->result)), dateToString(getFlightScheduleArrival(output->result)), getNumberPassengers(output->result), getDelay(output->result)); //incompleto, get n passageiros e delay não existem
   }
   if (output->resultType==RESERVATION){
    char breakfast[6];
    if (getReservIncludesBreakfast(output->result)==true){
      strcpy(breakfast, "true");
    }
    else{
      strcpy(breakfast, "false");
    }
    fprintf(file, "hotel_id: %s\nhotel_name: %s\nhotel_stars: %c\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",getReservHotelId(output->result), getReservHotelName(output->result), getReservHotelStars(output->result), dateToString(getReservBegin(output->result)), dateToString(getReservEnd(output->result)), breakfast, getReservNights(output->result), getReservPrice(output->result)); //incompleto, gets de n noites e preço total não existem
   }
  }
  else{
   if (output->resultType==USER){
    char sex;
    if (getGender(output->result)==M){
      sex='M';
    }
    else{
      sex='F';
    }
    fprintf(file, "%s;%c;%d;%s;%s;%d;%d;%.3f\n",getName(output->result), sex, getCountry(output->result), getPassport(output->result), getNumberFlights(output->result), getNumberReservations(output->result), getTotalSpent(output->result)); //incompleto, gets de n voos, n reservas e total gasto não existem
   }
   if (output->resultType==FLIGHT){
    fprintf(file, "%s;%s;%s;%s;%s;%s;%d;%.3f\n",getFlightAirline(output->result), getFlightAirplane(output->result), getFLightOrigin(output->result), getFlightDestination(output->result), dateToString(getFlightScheduleDeparture(output->result)), dateToString(getFlightScheduleArrival(output->result)), getNumberPassengers(output->result), getDelay(output->result));  //incompleto, get n passageiros e delay não existem
   }
   if (output->resultType==RESERVATION){
    char breakfast[6];
    if (getReservIncludesBreakfast(output->result)==true){
      strcpy(breakfast, "true");
    }
    else{
      strcpy(breakfast, "false");
    }
    fprintf(file, "%s;%s;%c;%s;%s;%s;%d;%.3f\n",getReservHotelId(output->result), getReservHotelName(output->result), getReservHotelStars(output->result), dateToString(getReservBegin(output->result)), dateToString(getReservEnd(output->result)), breakfast, getReservNights(output->result), getReservPrice(output->result)); //incompleto, gets de n noites e preço total não existem
   }
  }
  fclose(file);
}

void printOutputQ2 (char format_flag, Q2Type qType,ResultsQ2* output, int i){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
    if (Q2Type==BOTH){
     for (j=0; j<output->N; j++){
       fprintf (file, "--- %d ---\n", j);
       fprintf (file,"%s\n", output->results[j]->result); //incompleto
     }
    }
    else{
     for (j=0; j<output->N; j++){
       fprintf (file, "--- %d ---\n", j);
       fprintf (file,"%s\n", output->results[j]->result); //incompleto
     }
    }
  }
  else{
    if (Q2Type==BOTH){
     for (j=0; j<output->N; j++){
       fprintf (file, output->results[j]->result); //incompleto
     }
    }
    else{
     for (j=0; j<output->N; j++){
       fprintf (file, output->results[j]->result); //incompleto
     }
    }
  }
  fclose(file);
}

void printOutputQ3 (char format_flag, double output, int i){
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
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
     for (j=0; j<output->N; j++){
       fprintf (file, "--- %d ---\n", j);
       fprintf(file, "id: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %.3f\ntotal_price: %.3f\n",getReservId(output->result), dateToString(getReservBegin(output->result)), dateToString(getReservEnd(output->result)), getReservUserId(output->result), getReservUserClassification(output->result), getReservPrice(output->result)); //incompleto, get de preço total não existe
     }
    }
  else{
     for (j=0; j<output->N; j++){
        fprintf(file, "%s;%s;%s;%s;%.3f;%.3f\n",getReservId(output->result), dateToString(getReservBegin(output->result)), dateToString(getReservEnd(output->result)), getReservUserId(output->result), getReservUserClassification(output->result), getReservPrice(output->result)); //incompleto, get de preço total não existe
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

void printOutputQ9 (char format_flag, ResultsQ9* output, int i){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  int j;
  if (format_flag=='F'){
     for (j=0; j<output->N; j++){
       fprintf (file, "--- %d ---\n", j);
       fprintf (file,"id: %s\nname: %s\n", (output->results[j])->id, (output->results[j])->name);
     }
    }
  else{
     for (j=0; j<output->N; j++){
       fprintf (file,"%s;%s\n", (output->results[j])->id, (output->results[j])->name);
     }
  }
  fclose(file);
}