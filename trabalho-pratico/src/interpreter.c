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
   if (command->query_id==1){
     if (command->n_args==0) return 0;
     else{
        if (i != 0) {
         QueryResult * result = createQResult();
         Q1(command->args[0],catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q1(command->args[0],catalogs,result2);
        return 1;
     }
   }
    else if (command->query_id==2){
     if (command->n_args==0) return 0;
     else{
        Q2Type type;
        if (command->n_args==1) type = BOTH; //se só tiver o id como argumento,
        else if ((strcmp(command->args[1], "flights")==0)) type = FLIGHTS;
        else if ((strcmp(command->args[1], "reservations")==0)) type = RESERVATIONS;
        else return 0;
        if (i != 0) {
         QueryResult * result = createQResult();
         Q2(command->args[0], type, catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else  Q2(command->args[0], type, catalogs, result2);
        return 2;
     }
   }
    else if (command->query_id==3){
     if (command->n_args==0) return 0;
     else{
        if (i != 0) {
         QueryResult * result = createQResult();
         Q3(command->args[0], catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q3(command->args[0], catalogs, result2);
        return 3;
     }
   }
    else if (command->query_id==4){
     if (command->n_args==0) return 0;
     else{
        if (i != 0) {
         QueryResult * result = createQResult();
         Q4(command->args[0], catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q4(command->args[0], catalogs,result2);
        return 4;
     }
   }
    else if (command->query_id==5){
     if (command->n_args<3) return 0;
     else{
        Date *begin = string_to_date_hours(command->args[1]);
        Date *end = string_to_date_hours(command->args[2]);
        if (i != 0) {
         QueryResult * result = createQResult();
         Q5(command->args[0], begin, end, catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q5(command->args[0], begin, end, catalogs, result2);
        destroyDate(begin); destroyDate(end);
        return 5;
     }
   }
    else if (command->query_id==6){
     if (command->n_args<2) return 0;
     else{
        QueryResult * result = createQResult();
        Q6(atoi(command->args[0]), atoi(command->args[1]), catalogs, result);
        printQueryOutput(i,command->format_flag, result);
        destroyQResult(result);
        return 6;
     }
   }
    else if (command->query_id==7){
     if (command->n_args==0) return 0;
     else{
        if (i != 0) {
         QueryResult * result = createQResult();
         Q7(atoi(command->args[0]),catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        }
        else Q7(atoi(command->args[0]),catalogs,result2);
        return 7;
     }
   }
    else if (command->query_id==8){
     if (command->n_args<3) return 0;
     else{
      if (i != 0) {
         QueryResult * result = createQResult();
         Q8(command->args[0], command->args[1], command->args[2], catalogs, result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
      }
      else Q8(command->args[0], command->args[1], command->args[2], catalogs, result2);
        return 8;
     }
   }
    else if (command->query_id==9){
     if (command->n_args==0) return 0;
     else{
      if (i != 0) {
         QueryResult * result = createQResult();
         //UsersManager *usersCatalog = getUsersCatalog(catalogs);
        //OrdList* list = 
         Q9(command->args[0],catalogs,result);
         printQueryOutput(i,command->format_flag,result);
         destroyQResult(result);
        //printOutputQ9(command->format_flag, list, i);
        //destroyOnlyOrdList(list);
      }
      else Q9(command->args[0],catalogs,result2);
        return 9;
     }
   }
    /*else if (command->query_id==10){
      // Q10(atoi(command->args[0]), command->args[1]); //confirmar o que recebe
      return;
   }*/
    else return 0;
}

//lê uma linha do ficheiro de comandos e devolve um comando
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

//processa o ficheiro de comandos
void parseCommandFile (char* name,Catalogs *catalogs, bool test){
   //inicialização de variáveis para medição de tempo
   struct timespec start, end;
   double qTime[11]; // indice 0 - tempo total, 1 - query 1, etc..
   int j; for (j=0; j<11; j++) qTime[j] = 0;

 char* line = NULL;
 ssize_t read;
 size_t len;
 int i = 1;

 FILE* file = fopen(name, "r");
    if (file != NULL) {
 while((read = getline(&line, &len, file))!= -1){
    clock_gettime(CLOCK_REALTIME, &start);
    line[read-1]='\0'; //retira o newline
    Command *command = parseCommandLine(line);
    QueryResult * result = NULL;
    int q = processCommand(command, i,result,catalogs);
    i++;
    free(command);
    clock_gettime(CLOCK_REALTIME, &end);
    double dif = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    qTime[0]+=dif; if (q!=0) qTime[q]+=dif;
    if (test==1) printf("Command %d :\t\t %.6f seconds\n", i-1, dif);
 }
    }
 free(line);
 if (file != NULL)
 fclose(file);
 //imprime tempo de execução
  printf(" Interpreter/queries:\n");
  for (j=1; j<11; j++){
    printf("Query %d :\t\t %.6f seconds (%5.2f%%)\n",j, qTime[j], (qTime[j]/qTime[0])*100);
  }
   printf("  total:\t %.6f seconds\n", qTime[0]);
}
