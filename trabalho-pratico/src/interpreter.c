#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "output.h"
#include "queries.h"
#include <stdlib.h>
#include "flight.h"
#include "hotel.h"
#include "reservation.h"
#include "user.h"
#include "utility.h"
#include "flightsManager.h"
#include "hotelsManager.h"
#include "reservationsManager.h"
#include "usersManager.h"


struct command {
 int query_id; //número da query
 char format_flag;
 char args[3][100]; //as queries têm no maśximo 3 argumentos
 int n_args; //número de argumentos
};

void processCommand(Command* command, int i,UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,HotelsManager *hotelsCatalog,FlightsManager *flightsCatalog){
   createOutputFile(i); //cria um ficheiro mesmo que o comando não seja executado
   if (command->query_id==1){
     if (command->n_args==0) return;
     else{
        ResultQ1* output = Q1(command->args[0],usersCatalog,reservationsCatalog,flightsCatalog);
        printOutputQ1(command->format_flag, output,i);
     }
   }
    else if (command->query_id==2){
     if (command->n_args==0) return;
     else{
        if (command->n_args==1){ //se só tiver o id como argumento,
           ResultsQ2* output = Q2(command->args[0], BOTH, usersCatalog);
           printOutputQ2(command->format_flag, BOTH, output, i);
        }
        else{
          if ((strcmp(command->args[1], "flights")==0)){
            ResultsQ2* output = Q2(command->args[0], FLIGHTS, usersCatalog);
            printOutputQ2(command->format_flag, FLIGHTS, output, i);
          }
          else if ((strcmp(command->args[1], "reservations")==0)){
           ResultsQ2* output = Q2(command->args[0], RESERVATIONS, usersCatalog);
           printOutputQ2(command->format_flag, RESERVATIONS, output, i);
          }
          else return;
        }
     }
   }
    else if (command->query_id==3){
     if (command->n_args==0) return;
     else{
        double output = Q3(command->args[0], hotelsCatalog);
        printOutputQ3(command->format_flag, output, i);
     }
   }
    else if (command->query_id==4){
     if (command->n_args==0) return;
     else{
        ResultsQ4* output = Q4(command->args[0], hotelsCatalog);
        printOutputQ4(command->format_flag, output, i);
     }
   }
    else if (command->query_id==5){
     if (command->n_args<3) return;
     else{
        //ResultsQ5* output = Q5(command->args[0], toDate(command->args[1]), toDate(command->args[2])); //falta funcao toDate
        //printOutputQ5(command->format_flag, output, i);
        return;
     }
   }
    else if (command->query_id==6){
     if (command->n_args<2) return;
     else{
        //ResultsQ6* output = Q6(atoi(command->args[0]), atoi(command->args[1]));
        //printOutputQ6(command->format_flag, output, i);
        return;
     }
   }
    else if (command->query_id==7){
     if (command->n_args==0) return;
     else{
        //ResultsQ7* output = Q7(atoi(command->args[0]));
        //printOutputQ7(command->format_flag, output, i);
        return;
     }
   }
    else if (command->query_id==8){
     if (command->n_args<3) return;
     else{
        //double output = Q8(command->args[0], toDate(command->args[1]), toDate(command->args[2]));
        //printOutputQ8(command->format_flag, output, i);
        return;
     }
   }
    else if (command->query_id==9){
     if (command->n_args==0) return;
     else{
        //ResultsQ9* output = Q9(command->args[0]);
        //printOutputQ9(command->format_flag, output, i);
        return;
     }
   }
    else if (command->query_id==10){
      // Q10(atoi(command->args[0]), command->args[1]); //confirmar o que recebe
      return;
   }
    else return; 
}

Command* parseCommandLine (char* line){
    Command* command = malloc(sizeof(Command));
    command->query_id= line[0]-'0';
    command->format_flag = '\0';
    command->n_args=0;
    int j;
    //inicializa os argumentos
    for (j=0; j<100; j++) command->args[0][j]='\0';
    for (j=0; j<100; j++) command->args[1][j]='\0';
    for (j=0; j<100; j++) command->args[2][j]='\0';
    int i;
    if (line[1]!=' '){
       command->format_flag = line[1];
       i=2; //início dos argumentos
    }
    else i=1;
    while(i<strlen(line)){
     while(line[i]==' ') i++;
     if (line[i]=='\"'){ //lê um argumento delimitado por aspas
       i++;
       while(line[i]!='\"' && line[i]!='\0'){
         command->args[command->n_args][strlen(command->args[command->n_args])]=line[i];
         i++;
       }
       command->n_args++;
       i++;
     }
     else{ //lê um argumento separado por espacos
       while(line[i]!=' ' && line[i]!='\0'){
         command->args[command->n_args][strlen(command->args[command->n_args])]=line[i];
         i++;
       }
       command->n_args++;
       i++;
     }
    }
    return command;
}

void parseCommandFile (char* name,UsersManager *usersCatalog,ReservationsManager *reservationsCatalog,HotelsManager *hotelsCatalog,FlightsManager *flightsCatalog){
 char* line = NULL;
 ssize_t read;
 size_t len;
 int i = 1;

 FILE* ficheiro = fopen(name, "r");
 while((read = getline(&line, &len, ficheiro))!= -1){
    line[read-1]='\0'; //retira o newline
    Command *command = parseCommandLine(line);
    processCommand(command, i,usersCatalog,reservationsCatalog,hotelsCatalog,flightsCatalog);
    i++;
    free(command);
 }
 free(line);
 fclose(name);
}
