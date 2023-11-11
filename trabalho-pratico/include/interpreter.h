#ifndef interpreter
#define interpreter //header file para o interpretador de comandos

typedef struct command Command;

typedef enum{
   FLIGHTS,
   RESERVATIONS
} Q2Type;

void processCommand(Command* command);
Command* parseCommandLine (char* line);
void parseCommandFile (char* name);

#endif