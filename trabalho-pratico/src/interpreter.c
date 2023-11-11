#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include <stdio.h>

struct command {
 int query_id; //numero da query
 char format_flag;
 char args[3][100]; // as queries tem no maximo 3 argumentos
 int n_args; //numero de argumentos
};

void processCommand(Command* command){
   if (command->query_id==1){
     if (command->n_args==0) return;
     else{
        Q1(command->args[0]);
     }
   }
    else if (command->query_id==2){
     if (command->n_args==0) return;
     else{
        if (command->n_args==1){ //se so tiver o id como argumento, listar os voos e reservas
           Q2(command->args[0], FLIGHTS);
           Q2(commmand->args[0], RESERVATIONS);
        }
        else{
          if ((strcmp(command->args[1], "flights")==0)){
            Q2(command->args[0], FLIGHTS);
          }
          else if ((strcmp(command->args[1], "reservations")==0)){
           Q2(command->args[0], RESERVATIONS);
          }
          else return;
        }
     }
   }
    else if (command->query_id==3){
     if (command->n_args==0) return;
     else{
        Q3(command->args[0]);
     }
   }
    else if (command->query_id==4){
     if (command->n_args==0) return;
     else{
        Q4(command->args[0]);
     }
   }
    else if (command->query_id==5){
     if (command->n_args<3) return;
     else{
        Q5(command->args[0], toDate(command->args[1]), toDate(command->args[2])); //falta funcao toDate
     }
   }
    else if (command->query_id==6){
     if (command->n_args<2) return;
     else{
        Q6(atoi(command->args[0]), atoi(command->args[1]));
     }
   }
    else if (command->query_id==7){
     if (command->n_args==0) return;
     else{
        Q7(atoi(command->args[0]));        
     }
   }
    else if (command->query_id==8){
     if (command->n_args<3) return;
     else{
        Q8(command->args[0], toDate(command->args[1]), toDate(command->args[2]));
     }
   }
    else if (command->query_id==9){
     if (command->n_args==0) return;
     else{
        Q9(command->args[0]);
     }
   }
    else if (command->query_id==10){
       Q10(atoi(command->args[0]), command->args[1]); //confirmar o que recebe
   }
    else return; 
}

Command* parseCommandLine (char* line){
    Command* command = malloc(sizeof(Command));
    command->query_id= line[0]-'0';
    command->n_args=0;
    int j;
    //inicializa os argumentos
    for (j=0; j<100; j++) command->args[0][j]='\0';
    for (j=0; j<100; j++) command->args[1][j]='\0';
    for (j=0; j<100; j++) command->args[2][j]='\0';
    int i;
    if (line[1]!=' '){
       command->format_flag = line[1];
       i=2; //inicio dos argumentos
    }
    else i=1;
    while(i<strlen(line)){
     while(line[i]==' ') i++;
     if (line[i]=='\"'){ //le um argumento delimitado por aspas
       i++;
       while(line[i]!='\"' && line[i]!='\0'){
         command->args[command->n_args][strlen(command->args[command->n_args])]=line[i];
         i++;
       }
       command->n_args++;
       i++;
     }
     else{ //le um argumento separado por espacos
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

void parseCommandFile (char* name){
 char* line = NULL;
 ssize_t read;
 size_t len;

 FILE* ficheiro = fopen(name, "r");
 while((read = getline(&line, &len, ficheiro))!= -1){
    line[read-1]='\0'; //retira o newline
    Command *command = parseCommandLine(line);
    processCommand(command);
    free(command);
 }
 free(line);
}
