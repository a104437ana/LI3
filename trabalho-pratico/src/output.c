#include "output.h"

//cria o ficheiro para o output de um comando
void createOutputFile (int nCommand){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", nCommand);
  FILE* file = fopen(path, "w");
  fclose(file);
}

//devolve, numa string, os vários campos do resultado com índice r na lista do QueryResult, formatados de acordo com a flag 'F'
char * printResultF(QueryResult * result, int r){
  int nFields = getNumberFieldsQ(result,r);
  char * res = malloc(sizeof(char)*100*nFields);
  sprintf (res, "--- %d ---\n", (r+1)); //imprime o número do resultado (índice na lista + 1)
  int i; int ssize = 0;
  ssize+=(strlen(res)); 
  for (i=0; i<nFields; i++){
    char * name = getFieldName(result,r,i); //nome do campo
    char * data = getFieldData(result,r,i); //valor desse campo
    sprintf(res+ssize, "%s: %s\n", name, data);
    ssize+=(strlen(name)+ strlen(data)+3); //atualiza o tamanho da string, somando-lhe o tamanho do nome do campo e resultado atuais mais 3 (para o caracter ':', o espaço, e o newline)
    free(name); free(data);
  }
  res[ssize] = '\n'; //coloca o newline
  res[ssize+1] = '\0'; //termina a string
  return res;
}

//devolve, numa string, os vários campos do resultado com índice r na lista do QueryResult, para quando a query é chamada sem format flags
char * printResult(QueryResult * result, int r){
  int nFields = getNumberFieldsQ(result,r);
  char * res = malloc(sizeof(char)*100*nFields);
  int i; int ssize = 0;
  for (i=0; i<nFields; i++){
    char * data = getFieldData(result,r,i); //valor do campo i
    sprintf(res+ssize, "%s;", data);
    ssize+=(strlen(data)+1); //atualiza o tamanho da string, somando-lhe o tamanho do resultado atual mais 1 (para o ';')
    free(data);
  }
  res[ssize-1] = '\n'; //substitui o último ';' por um newline
  res[ssize] = '\0'; //termina a string
  return res;
}

//imprime no ficheiro o resultado de uma query
void printQueryOutput (int commandN, char format_flag, QueryResult * output){
   char path[100];
   sprintf (path, "./Resultados/command%d_output.txt", commandN);
   FILE* file = fopen(path, "w");
   int i;
   int nResults = getNumberResults(output);
   if (format_flag=='F'){
     for (i=0; i<nResults; i++){ //imprime cada elemento da lista de resultados da query, com a format flag 'F'
       char * print = printResultF (output,i);
       if (i==nResults-1) print[strlen(print)-1] = '\0'; //retira o último newline
       fprintf (file, "%s", print);
       free(print);
     }
    }
   else{
     for (i=0; i<nResults; i++){ //imprime cada elemento da lista de resultados da query
       char * print = printResult (output,i);
       fprintf (file, "%s", print);
       free(print);
     }
  }
  fclose(file);
}