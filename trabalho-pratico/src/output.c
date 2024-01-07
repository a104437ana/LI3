#include "output.h"

//cria o ficheiro para o output de um comando
void createOutputFile (int nCommand){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", nCommand);
  FILE* file = fopen(path, "w");
  fclose(file);
}

char * printResultF(QueryResult * result, int r){
  int nFields = getNumberFieldsQ(result,r);
  char * res = malloc(sizeof(char)*100*nFields);
  int i; int ssize = 0;
  for (i=0; i<nFields; i++){
    char * name = getFieldName(result,r,i);
    char * data = getFieldData(result,r,i);
    sprintf(res+ssize, "%s: %s\n", name, data);
    ssize+=(strlen(name)+ strlen(data)+3);
    free(name); free(data);
  }
  res[ssize] = '\0';
  return res;
}

char * printResult(QueryResult * result, int r){
  int nFields = getNumberFieldsQ(result,r);
  char * res = malloc(sizeof(char)*100*nFields);
  int i; int ssize = 0;
  for (i=0; i<nFields; i++){
    char * data = getFieldData(result,r,i);
    sprintf(res+ssize, "%s;", data);
    ssize+=(strlen(data)+1);
    free(data);
  }
  res[ssize-1] = '\n'; res[ssize] = '\0';
  return res;
}

void printQueryOutput (int commandN, char format_flag, QueryResult * output){
   char path[100];
   sprintf (path, "./Resultados/command%d_output.txt", commandN);
   FILE* file = fopen(path, "w");
   int i;
   int nResults = getNumberResults(output);
   if (format_flag=='F'){
     for (i=0; i<nResults; i++){
       fprintf (file, "--- %d ---\n", (i+1));
       char * print = printResultF (output,i);
       fprintf (file, "%s", print);
       if (i<nResults-1) fprintf(file, "\n");
       free(print);
     }
    }
   else{
     for (i=0; i<nResults; i++){
       char * print = printResult (output,i);
       fprintf (file, "%s", print);
       free(print);
     }
  }
  fclose(file);
}

//provisório

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