#include "parser.h"

/* A função parse_file lê um ficheiro de entrada CSV e efetua o seu parsing genérico. Esta função recebe o caminho absoluto para o ficheiro de entrada CSV,
o caminho relativo para o ficheiro de erros, um apontador para os catálogos e um apontador para uma hashtable para contar passageiros. Primeiro, verificamos
se o ficheiro de entrada CSV existe. Depois com o caminho para o ficheiro de erros, conseguimos identificar o tipo de ficheiro. Dependendo do tipo de ficheiro,
criamos uma lista com tamanho adequado, para guardar apontadores. Depois iremos abrir o ficheiro para o poder ler. Primeiro, lemos a primeira linha onde se encontra
o header (o cabeçalho). Iremos colocar o header no ficheiro de erros. Para isso criamos (ou inicializamos) o ficheiro de erros e colocamos lá o header. Depois iremos
ler as próximas linhas. A cada linha que lemos, iremos pegar nela e dividi-la em várias partes. Cada parte terá um apontador que será guardado na lista criada no início
da função. Depois, utilizando as várias partes da linha, iremos verificar se uma determinada identidade (que depende do tipo de ficheiro) é válida. Se for, iremos 
transformar todas estas strings num tipo adequado e passar esses parâmetros para a estrutura de dados. Se for inválido, então iremos pegar na linha original e iremos 
acrescenta-la ao ficheiro de erros. Por fim, libertamos a memória alocada e fechamos o ficheiro CSV e o ficheiro de erros. */
void parse_file (char* file_path, char* error_file_path, Catalogs *catalogs, PassengersCounter* passengers_counter) {
    if (exist_file(file_path)) { //se o ficheiro CSV existir
        char type_file = error_file_path[11];
        int size;
        switch (type_file) {
            case 'r': size = 13; //reservas
                      break;
            case 'p': size = 2; //passageiros
                      break;
            default: size = 12; //outros
                     break;
        }
        char **token = malloc(sizeof(char*)*size); //lista de apontadores é criada
        FILE *file;
        file = fopen(file_path,"r"); //abertura do ﬁcheiro em modo de leitura. O ﬁcheiro deve existir.
        char* line = NULL;
        size_t n;
        ssize_t read;
        if ((read = getline(&line,&n,file)) != -1) {
            FILE *error_file;
            error_file = fopen(error_file_path,"w"); //abertura do ficheiro para escrita. Se o ficheiro não existir, é automaticamente criado. Se o ficheiro existir, é truncado.
            fprintf(error_file,"%s",line);
            int invalid; //variável para registar a validade de uma identidade
            char* line_pointer;
            int indice = 0; //variável para registar o número total de utilizadores (para o ficheiro users.csv) no fim da função, e ao longo da função para registar o indice do utilizador atual numa lista criada posteriormente
            while((read = getline(&line,&n,file)) != -1) {
                line_pointer = line;
                for (int i = 0; i < size; i++) {
                    token[i] = strsep(&line_pointer,";"); //dividir a linha em partes
                }
                invalid = 1;
                switch (type_file) {
                    //users
                    case 'u' : remove_new_line(token[11]);
                               //              id      name     email    phone_n  birth    gender   passport country  address  ac_creat pay_m     ac_status
                               if (valid_user(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[11])) {
                                    invalid = 0;
                                    int gender = 0;
                                    int accountStatus = 0;
                                    if (token[5][0] == 'F' || token[5][0] == 'f') gender = 1;
                                    if (token[11][0] == 'a' || token[11][0] == 'A') accountStatus = 1;
                                    addUser(token[0],token[1],gender,token[7],token[6],token[4],token[9],accountStatus,indice,catalogs);
                                    indice++;
                               }
                               break;
                    //reservations                    id      id_user  id_hotel h_name   h_stars  cityTax  address  begin    end      pricePN  inc_break userClass
                    case 'r' : if (valid_reservation(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[12],catalogs)) {
                                    invalid = 0;
                                    int cityTax = string_to_int(token[5]);
                                    int pricePerNight = atoi(token[9]);
                                    int includesBreakfast = 0;
                                    char hotelStars = token[4][0];
                                    char userClassification = token[12][0];
                                    if (token[10][0] == 't' || token[10][0] == 'T' || token[10][0] == '1') includesBreakfast = 1;
                                    int id = reservIdToInt(token[0]);
                                    addHotel(token[2],token[3],hotelStars,cityTax,userClassification,id,catalogs);
                                    addReservation(id,token[1],token[2],token[7],token[8],pricePerNight,includesBreakfast,userClassification,cityTax,catalogs);
                               }
                               break;
                    //flights                   id       airline  airplane t_seats  origin   dest     s_depart s_arriv  r_depart r_arriv  pilot     copilot
                    case 'f' : if (valid_flight(token[0],token[1],token[2],token[3],token[4],token[5],token[6],token[7],token[8],token[9],token[10],token[11],passengers_counter)) {
                                    invalid = 0;
                                    toUpperS(token[4]);
                                    toUpperS(token[5]);
                                    int id = flightIdToInt(token[0]);
                                    int delay = addFlight(id,token[1],token[2],token[4],token[5],token[6],token[7],token[8],token[9],catalogs);
                                    addAirport(delay,token[4],token[5],id,catalogs);
                               }
                               break;
                    //passengers                     id voo    id user
                    case 'p' : remove_new_line(token[1]);
                               if (valid_passenger(token[0],token[1],catalogs)) {
                                    invalid = 0;
                                    int id = flightIdToInt(token[0]);
                                    addPassenger(id, token[1], catalogs);
                               }
                               break;
                }
                if (invalid == 1) { // se a identidade for inválida
                    fseek(file, -read, SEEK_CUR); //colocar o apontador no inicio da linha que acabamos de ler
                    read = getline(&line, &n, file); //ler a linha
                    fprintf(error_file,"%s",line); //adicionar a linha ao ficheiro de erros
                }
            }
            fclose(error_file);
            // se o ficheiro for users.csv e se indice for maior que 0, criar lista com todos os passageiros no catálogo dos utilizadores (número de passageiros igual ao indice)
            if (type_file == 'u' && indice > 0) createListPassengers_UsersManager(catalogs,indice);
        }
        free(line);
        fclose(file);
        free(token);
    }
}

/* A função parse_all_files lê todos os ficheiros de entrada CSV e efetua o seu parsing. Esta função recebe um apontador para os catálogos e 
o caminho absoluto para a diretoria onde se encontram os ficheiros CSV. Para cada ficheiro diferente, criamos o caminho absoluto para esse 
ficheiro e criamos o caminho relativo para o ficheiro de erros. Para além disso, nesta função é criada uma hashtable com os números de
passageiros por id de voo e é chamada uma função que contará o número de passageiros por voo. Os resultados desta função serão usados para 
verificar se os voos são válidos e para assim sabermos se devemos guardar o voo na estrutura de dados ou se devemos coloca-lo no ficheiro de
erros. Após a utilização destes resultados para validar os voos, destruimos a hashtable. Para efetivamente ler e fazer o parsing de cada ficheiro,
chamamos a função parse_file.*/
void parse_all_files (char* directory, Catalogs *catalogs) {

    PassengersCounter* passengers_counter = createPassengersCounter(PASSENGERS_PER_FLIGHT_HASHTABLE_INI_SIZE);

    int size = strlen(directory) + 18;
    char* file_path = malloc(size);

    sprintf(file_path,"%s/users.csv",directory);
    parse_file(file_path,"Resultados/users_errors.csv",catalogs,passengers_counter);
        
    sprintf(file_path,"%s/reservations.csv",directory);
    parse_file(file_path,"Resultados/reservations_errors.csv",catalogs,passengers_counter);
        
    count_passengers(directory,catalogs,passengers_counter);
        
    sprintf(file_path,"%s/flights.csv",directory);
    parse_file(file_path,"Resultados/flights_errors.csv",catalogs,passengers_counter);
        
    sprintf(file_path,"%s/passengers.csv",directory);
    parse_file(file_path,"Resultados/passengers_errors.csv",catalogs,passengers_counter);
        
    free(file_path);

    destroyPassengersCounter(passengers_counter);
 }