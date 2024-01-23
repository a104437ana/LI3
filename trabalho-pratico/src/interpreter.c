#include "interpreter.h"
#include <time.h>

struct command {
 int query_id; //número da query
 char format_flag;
 char args[3][100]; //as queries têm no máximo 3 argumentos
 int n_args; //número de argumentos
};

//função que processa um comando, chamando a respetiva query e a função que imprime o resultado
int processCommand(Command* command, int i, QueryResult* result2, Catalogs* catalogs){
   if (i!= 0) createOutputFile(i); //cria um ficheiro mesmo que o comando não seja executado
   if (command->query_id==1){ //query 1
     if (command->n_args==0) return 0;
     else{
        if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q1(command->args[0],catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q1(command->args[0],catalogs,result2); //modo interativo
        return 1;
     }
   }
    else if (command->query_id==2){ //query 2
     if (command->n_args==0) return 0;
     else{
        Q2Type type;
        if (command->n_args==1) type = BOTH; //se só tiver o id como argumento,
        else if ((strcmp(command->args[1], "flights")==0)) type = FLIGHTS;
        else if ((strcmp(command->args[1], "reservations")==0)) type = RESERVATIONS;
        else return 0;
        if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q2(command->args[0], type, catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q2(command->args[0], type, catalogs, result2); //modo interativo
        return 2;
     }
   }
    else if (command->query_id==3){ //query 3
     if (command->n_args==0) return 0;
     else{
        if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q3(command->args[0], catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q3(command->args[0], catalogs, result2); //modo interativo
        return 3;
     }
   }
    else if (command->query_id==4){ //query 4
     if (command->n_args==0) return 0;
     else{
        if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q4(command->args[0], catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q4(command->args[0], catalogs,result2); //modo interativo
        return 4;
     }
   }
    else if (command->query_id==5){ //query 5
     if (command->n_args<3) return 0;
     else{
        Date *begin = string_to_date_hours(command->args[1]);
        Date *end = string_to_date_hours(command->args[2]);
        if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q5(command->args[0], begin, end, catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q5(command->args[0], begin, end, catalogs, result2); //modo interativo
        destroyDate(begin); destroyDate(end);
        return 5;
     }
   }
    else if (command->query_id==6){ //query 6
     if (command->n_args<2) return 0;
     else{
      if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q6(atoi(command->args[0]), atoi(command->args[1]), catalogs, result);
         printQueryOutput(i,command->format_flag, result);
         destroyQResult(result);
      }
      else Q6(atoi(command->args[0]), atoi(command->args[1]), catalogs, result2); //modo interativo
        return 6;
     }
   }
    else if (command->query_id==7){ //query 7
     if (command->n_args==0) return 0;
     else{
        if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q7(atoi(command->args[0]),catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q7(atoi(command->args[0]),catalogs,result2); //modo interativo
        return 7;
     }
   }
    else if (command->query_id==8){ //query 8
     if (command->n_args<3) return 0;
     else{
      if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q8(command->args[0], command->args[1], command->args[2], catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
      }
      else Q8(command->args[0], command->args[1], command->args[2], catalogs, result2); //modo interativo
        return 8;
     }
   }
    else if (command->query_id==9){ //query 9
     if (command->n_args==0) return 0;
     else{
      if (i != 0) { //modo batch
         QueryResult * result = createQResult();
         Q9(command->args[0],catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
      }
      else Q9(command->args[0],catalogs,result2); //modo interativo
        return 9;
     }
   }
   else if (command->query_id==10){ //query 10
      if (command->n_args==0){ //query é executada sem argumentos
            if (i != 0) { //modo batch
               QueryResult * result = createQResult();
               Q10(-1,-1,catalogs,result);
               printQueryOutput(i,command->format_flag,result);
               destroyQResult(result);
            }
            else Q10(-1,-1,catalogs,result2); //modo interativo
            return 10;
      }
      else if (command->n_args==1){ //query é executada com um argumento - o ano
            if (i != 0) { //modo batch
               QueryResult * result = createQResult();
               Q10(atoi(command->args[0]), -1,catalogs,result);
               printQueryOutput(i,command->format_flag,result);
               destroyQResult(result);
            }
            else Q10(atoi(command->args[0]), -1,catalogs,result2); //modo interativo
            return 10;
      }
      else{ //query é executada com dois argumentos - ano e mês
            if (i != 0) { //modo batch
               QueryResult * result = createQResult();
               Q10(atoi(command->args[0]),atoi(command->args[1]),catalogs,result);
               printQueryOutput(i,command->format_flag,result);
               destroyQResult(result);
            }
            else Q10(atoi(command->args[0]),atoi(command->args[1]),catalogs,result2); //modo interativo
            return 10;
      }
   }
    else return 0;
}

//lê uma linha do ficheiro de comandos e devolve um comando
Command* parseCommandLine (char* line){
    Command* command = malloc(sizeof(Command));
    command->n_args=0; int j; int i;
    if (line[1] == ' '){ //id da query só tem um dígito e não tem format flags
      command->query_id= line[0]-'0';
      command->format_flag = '\0';
      i=1; //início dos argumentos
    }
    else if (line[1]=='0'){ //id da query é 10
      command->query_id = 10;
      if (line[2]!=' '){ //tem format flags
         command->format_flag = line[2];
         i=3;
      }
      else{ //não tem format flags
         command->format_flag = '\0';
         i = 2;
      }
    }
    else{ //id da query só tem um dígito e tem format flags
       command->query_id= line[0]-'0';
       command->format_flag = line[1];
       i=2; //início dos argumentos
    }

    //inicializa os argumentos
    for (j=0; j<100; j++) command->args[0][j]='\0';
    for (j=0; j<100; j++) command->args[1][j]='\0';
    for (j=0; j<100; j++) command->args[2][j]='\0';

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

//processa o ficheiro de comandos
void parseCommandFile (char* name,Catalogs *catalogs, bool test, double* commands_time, double* qTime){
   struct timespec start, end;

 char* line = NULL;
 ssize_t read;
 size_t len;
 int i = 1;

 FILE* file = fopen(name, "r");
    if (file != NULL) {
 while((read = getline(&line, &len, file))!= -1){
    clock_gettime(CLOCK_REALTIME, &start); //lê o tempo de início
    line[read-1]='\0'; //retira o newline
    Command *command = parseCommandLine(line);
    QueryResult * result = NULL;
    int q = processCommand(command, i,result,catalogs);
    free(command);
    clock_gettime(CLOCK_REALTIME, &end); //lê o tempo de fim da execução do comando
    double dif = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; //tempo de execução
    if (test == 1) { //se estiver no modo testes
      qTime[0]+=dif; //adiciona o tempo ao total da execução das queries
      if (q != 0) qTime[q]+=dif; //adiciona o tempo ao total de execução dessa query (a função processCommand devolve o id da query executada)
      commands_time[i-1] = dif; //guarda o tempo de execução do comando
    }
    i++;
 }
    }
 free(line);
 if (file != NULL)
 fclose(file);
}
