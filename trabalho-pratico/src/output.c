#include <string.h>
#include <stdio.h>

void createOutputFile (int nCommand){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", nCommand);
  FILE* file = fopen(path, "w");
  fclose(file);
}

void printOutputQ1 (char format_flag, ResultQ1* output, int i){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   fprintf (file,"%s\n", output->result); //incompleto, output->result não é uma string
  }
  else{
   fprintf (file,"%s\n", output->result); //incompleto
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

void printOutputQ3 (char format_flag, float output, int i){
  char path[100];
  sprintf (path, "./Resultados/command%d_output.txt", i);
  FILE* file = fopen(path, "w");
  if (format_flag=='F'){
   fprintf (file, "--- 1 ---\n");
   fprintf (file,"rating: %f\n", output);
  }
  else{
   fprintf (file,"%f\n", output);
  }
  fclose(file);
}