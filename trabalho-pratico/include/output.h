#ifndef _OUTPUT_
#define _OUTPUT_ //header file para o output dos resultados

void createOutputFile (int nCommand);
void printOutputQ1 (char format_flag, ResultQ1* output, int i);
void printOutputQ2 (char format_flag, Q2Type qType,ResultsQ2* output, int i);
void printOutputQ3 (char format_flag, float output, int i);

#endif