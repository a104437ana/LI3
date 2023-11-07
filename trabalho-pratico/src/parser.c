#include "parser.h"

int exist_file (char* path_file) {
    int existe = 0;
	FILE *file;
	file = fopen(path_file,"r");
	if (file != NULL) {
		existe = 1;
        fclose(file);
	}
    return existe;
}

void parse_file (char* path_directory, enum Type_file type_file) {
    char* name_file = NULL;
    switch (type_file) {
        case 0 : name_file = malloc(sizeof("/users.csv"));
                 strcpy(name_file,"/users.csv");
                 break;
        case 1 : name_file = malloc(sizeof("/fligths.csv"));
                 strcpy(name_file,"/fligths.csv");
                 break;
        case 2 : name_file = malloc(sizeof("/passengers.csv"));
                 strcpy(name_file,"/passengers.csv");
                 break;
        case 3 : name_file = malloc(sizeof("/reservations.csv"));
                 strcpy(name_file,"/reservations.csv");
                 break;
    }
    char* path_file = malloc(strlen(path_directory) + strlen(name_file) + sizeof(char));
    strcpy(path_file, path_directory);
    strncat(path_file, name_file,strlen("/reservations.csv") + 1);
    if (exist_file(path_file)) {
        FILE *file;
        file = fopen(path_file,"r");
        char* line = NULL;
        size_t n;
        ssize_t read;
        switch (type_file) {
            case 0 : if ((read = getline(&line,&n,file)) != -1) {

                     while((read = getline(&line,&n,file)) != -1){
                        char* token = strsep(&line,";"); //id user
                        token = strsep(&line,";"); //nome
                        token = strsep(&line,";"); //email
                        token = strsep(&line,";"); //numero
                        token = strsep(&line,";"); //data nascimento
                        token = strsep(&line,";"); //genero
                        token = strsep(&line,";"); //passaporte
                        token = strsep(&line,";"); //pais
                        token = strsep(&line,";"); //morada
                        token = strsep(&line,";"); //data conta
                        token = strsep(&line,";"); //forma de pagamento
                        token = strsep(&line,";"); //estado da conta
                     }
                     }
                     break;
            case 1 : while((read = getline(&line,&n,file)) != -1){
                        char* token = strsep(&line,";"); //id fligth
                        token = strsep(&line,";"); //airline
                        token = strsep(&line,";"); //plane_model
                        token = strsep(&line,";"); //total_seats
                        token = strsep(&line,";"); //origin
                        token = strsep(&line,";"); //destination
                        token = strsep(&line,";"); //data planeada partida
                        token = strsep(&line,";"); //data planeada chegada
                        token = strsep(&line,";"); //data real partida
                        token = strsep(&line,";"); //data real chegada
                        token = strsep(&line,";"); //piloto
                        token = strsep(&line,";"); //copiloto
                        token = strsep(&line,";"); //notas
                     }
                     break;
            case 2 : while((read = getline(&line,&n,file)) != -1){
                        char* token = strsep(&line,";"); //id fligth
                        token = strsep(&line,";"); //id user
                     }
                     break;
            case 3 : while((read = getline(&line,&n,file)) != -1){
                        char* token = strsep(&line,";"); //id reservation
                        token = strsep(&line,";"); //id user
                        token = strsep(&line,";"); //id hotel
                        token = strsep(&line,";"); //nome hotel
                        token = strsep(&line,";"); //estrelas hotel
                        token = strsep(&line,";"); //city tax
                        token = strsep(&line,";"); //morada
                        token = strsep(&line,";"); //data inicio
                        token = strsep(&line,";"); //data fim
                        token = strsep(&line,";"); //preço por noite
                        token = strsep(&line,";"); //pequeno-almoço
                        token = strsep(&line,";"); //room details
                        token = strsep(&line,";"); //rating
                        token = strsep(&line,";"); //coments
                     }
                     break;
        }
        free(line);
        fclose(file);
    }
    free(name_file);
    free(path_file);
}

void parse_all_files (char* path_directory) {
    parse_file(path_directory,users);
    parse_file(path_directory,fligths);
    parse_file(path_directory,passengers);
    parse_file(path_directory,reservations);
}