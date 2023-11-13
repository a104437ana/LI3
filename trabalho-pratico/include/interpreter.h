#ifndef _INTERPRETER_
#define _INTERPRETER_ //header file para o interpretador de comandos

typedef struct command Command;

void processCommand(Command* command, int i);
Command* parseCommandLine (char* line);
void parseCommandFile (char* name);

#endif