#include "interactive.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include "catalogsManager.h"
#include "parser.h"
#include "interpreter.h"
#include "results.h"
#include "output.h"
#include <ctype.h>

/* A função get_string recebe uma linha máxima, uma coluna máxima, uma linha mínima, uma coluna mínima, um número que representa o tamanho máximo da string
que queremos obter e um apontador para um inteiro, cujo o valor define se saimos ou não do modo interativo. Esta função retorna uma string escrita pelo
utilizador no modo interativo. Se o utilizador escrever algo entre duas aspas, a string final será apenas o que está escrito entre as duas aspas exclusive.
Esta função, para além de guardar aquilo que o utilizador escreve e apaga, também é responsável pela visualização deste processo no ecrã.*/
char* get_string (int max_row, int max_col,int min_row,int min_col, int n, int *proceed) {
    char* path = malloc(n); //criar uma string com comprimento máximo n (incluindo '\0' no fim) (n-1 será para o '\0')
    int row;
    int col;
    int i = 0;
    while (1) {
        int key = getch(); //tecla pressionada pelo utilizador
        getyx(stdscr, row, col);
        if (key == '\n') { //Enter -> acabou a string
            break;
        }
        if (key == KEY_BACKSPACE || key == KEY_DC) { //delete ou tecla de apagar -> apagar 1 caracter da string
            if (col == 0) { // coluna 0
                if (row != min_row) { // se não for na linha mínima
                    move(row-1,max_col-1); //vai para a linha anterior
                    printw(" ");
                    move(row-1,max_col-1);
                    i--;
                    path[i] = '\0';
                }
            }
            else {
                if (col != min_col || row != min_row) { //se não estiver na posição inicial (limites mínimos) então pode apagar 1 caracter
                    move(row,col-1);
                    printw(" ");
                    move(row,col-1);
                    i--;
                    path[i] = '\0';
                }
            }
        }
        else {
            if (key == KEY_RESIZE || key == KEY_F(11)) { //se o utilizador alterar o tamanho da janela do terminal
                *proceed = 0;                            //então o modo interativo irá encerrar
                break;
            }
            else {
                if (key != KEY_UP && key != KEY_DOWN && key != KEY_LEFT && key != KEY_RIGHT && key != 27 && key != '\t') { //se a tecla for normal
                    if ((col != max_col || row != max_row) && i<n-1) { // e se a posição atual não for a posição máxima e se ainda temos espaço para utlizar na string alocada
                        printw("%c",key);  //escrever 1 caracter                                                                    (n-1 será para o '\0')
                        char key_char = key;
                        path[i] = key_char;
                        i++;
                    }
                }
            }
        }
    }
    path[i] = '\0'; //colocar o '\0' no fim da string

    int inicial = -1;
    int final = -1;
    i = 0;
    int len = strlen(path) - 1;

    while (path[i] == ' ') i++; //verificar se a string apresenta duas aspas que rodeiam todo o texto
        if (path[i] == '\"') {
        inicial = i;
        while (path[len] == ' ') len--;
        if (path[len] == '\"') final = len;
    }

    if (inicial != -1 && final != -1 && final - inicial > 1) { // se a string apresenta duas aspas que rodeiam todo o texto
        char* string = malloc(final-inicial);                  // então vamos apenas retornar o texto entre essas aspas
        strncpy(string,path+inicial+1,final-inicial);
        string[final-inicial-1] = '\0';
        free(path);
        path = string;
    }

    return path; //retornar a string
}

/* A função get_option recebe um número que representa a linha onde irá estar a primeira opção no ecrã e recebe um número que representa o número de
opções, ou a última opção se contarmos apartir do número 1. Esta função permite que o utilizar navega pelas opções, usando as teclas up and down
(cima e baixo). Esta função printa um x na opção escolhida. Por fim, esta função retorna um inteiro que representa o número da opção escolhida
pelo utilizador. As opções são de 1 a last_option. Se a função retornar 0, então sabemos que o programa irá encerrar asseguir.*/
int get_option (int first_x, int last_option) {
    int x = first_x;
    int y = 1;
    int option = 1;
    mvaddch(x, y, 'x' | A_BOLD); //coloca x na primeira opção
    move(x,y);
    int exit = 0;
    int key;
    while (exit == 0) {
        key = getch();
        switch (key) {
            case KEY_UP: mvaddch(x, y, ' '); // se a tecla for up (cima)
                         if (x != first_x) { // e se não estivermos na opção 1
                            option--;        // vamos para a opção em cima
                            x-=2;
                         }
                         mvaddch(x, y, 'x' | A_BOLD); //colocar x na opção
                         move(x,y);
                         break;
            case KEY_DOWN: mvaddch(x, y, ' ');          // se a tecla for down (baixo)
                           if (option != last_option) { // e se não estivermos na última opção
                            option++;                   // vamos para a opção em baixo
                            x+=2;
                           }
                           mvaddch(x, y, 'x' | A_BOLD); //colocar x na opção
                           move(x,y);
                           break;
            case '\n': exit=1; // se a tecla for Enter, a opção foi escolhida
                       break;
            case KEY_F(11):            // se o utilizador alterar o tamanho da janela do terminal
            case KEY_RESIZE: exit = 1; // então a função irá retornar 0
                             option = 0; // e o programa irá encerrar asseguir
                             break;
        }
    }
    return option;
}

/* A função get_querie recebe um apontador para os catálogos, um apontador para um resultado, a linha máxima e a coluna máxima. Esta função
começa por nos apresentar o menu e permite nos explorar todas as opções. Depois de escolhermos uma querie, esta função irá nos apresentar
pedidos de informação e irá guardar a informação que lhe oferecermos sobre esta querie. Com estas informações iremos formar um comando e
iremos chamar a função processCommand para processar este comando. Assim, iremos obter um resultado. Por fim, esta função irá retornar um
número inteiro, que representa o formato em que o resultado irá ser apresentado (1 se o formato for CSV ou 2 se o formato for campo por campo).
A função também pode retornar 0, se o utilizador pretendeu sair do programa ou se alterou o tamanho da janela do terminal. Se a função
retornar 0, o programa irá terminar asseguir.*/
int get_querie (int max_row, int max_col,Catalogs* catalogs,QueryResult* result) {
    int proceed = 1;
    int* pointer = &proceed;
    clear();

    mvprintw(0, 0, "Menu :)\n\nNavigate options using the arrow keys (up and down). Press Enter to select your choice.");
    mvprintw(4, 0, "   Query 1 - Lists the summary of a user, flight, or reservation."); 
    mvprintw(6, 0, "   Query 2 - Lists the flights and/or reservations of a user.");
    mvprintw(8, 0, "   Query 3 - Presents the average rating of a hotel.");
    mvprintw(10, 0, "   Query 4 - Lists the hotel reservations, sorted by start date (from the most recent to the oldest).");
    mvprintw(12, 0, "   Query 5 - Lists the flights with origin at a given airport, between two dates, sorted by estimated departure date (from the most recent to the oldest).");
    mvprintw(14, 0, "   Query 6 - Lists the top N airports with the most passengers for a given year.");
    mvprintw(16, 0, "   Query 7 - Lists the top N airports with the highest median of delays.");
    mvprintw(18, 0, "   Query 8 - Presents the total revenue of a hotel between two dates (inclusive).");
    mvprintw(20, 0, "   Query 9 - Lists all users whose names start with the prefix provided as an argument, sorted by name in ascending order.");
    mvprintw(22, 0, "   Query 10 - Presents various overall metrics of the application.");
    mvprintw(24, 0, "   Exit the program.");

    int query = get_option(4,11);
    if (query == 0) return 0;
    clear();
    int c;
    char* string1 = NULL;
    char* string2 = NULL;
    char* string3 = NULL;
    char* command = NULL;
    int option;
    int x = 0;
    switch(query) {
        case 1: mvprintw(0, 0, "Query 1 - Lists the summary of a user, flight, or reservation.");
                mvprintw(2, 0, "Enter the ID: ");
                string1 = get_string(max_row,max_col,2,14,60,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                x = 4;
                break;
        case 2: mvprintw(0, 0, "Query 2 - Lists the flights and/or reservations of a user.");
                mvprintw(2, 0, "Enter the ID of the user: ");
                string1 = get_string(max_row,max_col,2,26,60,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                mvprintw(4,0, "Navigate options using the arrow keys (up and down). Press Enter to select your choice.");
                mvprintw(6,0, "   Only flights.");
                mvprintw(8,0, "   Only reservations.");
                mvprintw(10,0, "   Both.");
                x = 12;
                option = get_option(6,3);
                if (option == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                switch(option) {
                    case 1: command = malloc(12+strlen(string1));
                            sprintf(command,"%d %s flights",query,string1);
                            break;
                    case 2: command = malloc(17+strlen(string1));
                            sprintf(command,"%d %s reservations",query,string1);
                            break;
                    case 3: command = malloc(4+strlen(string1));
                            sprintf(command,"%d %s",query,string1);
                            break;
                }
                break;
        case 3: mvprintw(0, 0, "Query 3 - Presents the average rating of a hotel.");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                x = 4;
                string1 = get_string(max_row,max_col,2,27,60,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 4: mvprintw(0, 0, "Query 4 - Lists the hotel reservations, sorted by start date (from the most recent to the oldest).");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                x = 4;
                string1 = get_string(max_row,max_col,2,27,60,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 5: mvprintw(0, 0, "Query 5 - Lists the flights with origin at a given airport, between two dates, sorted by estimated departure date (from the most recent to the oldest).");
                mvprintw(2, 0, "Enter the name of the airport: ");
                string1 = get_string(max_row,max_col,2,31,10,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                mvprintw(4,0, "Enter the begin date in this format yyyy/MM/dd hh:mm:ss (e.g. 2023/01/31 23:59:59): ");
                string2 = get_string(max_row,max_col,4,84,29,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                mvprintw(6,0, "Enter the end date in this format yyyy/MM/dd hh:mm:ss (e.g. 2023/01/31 23:59:59): ");
                x = 8;
                string3 = get_string(max_row,max_col,6,82,29,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                command = malloc(10+strlen(string1)+strlen(string2)+strlen(string3));
                sprintf(command,"%d %s \"%s\" \"%s\"",query,string1,string2,string3);
                break;
        case 6: mvprintw(0, 0, "Query 6 - Lists the top N airports with the most passengers for a given year.");
                mvprintw(2, 0, "Enter the year: ");
                string1 = get_string(max_row,max_col,2,16,10,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                mvprintw(4,0, "Enter a non-negative number N (e.g. 12): ");
                x = 6;
                string2 = get_string(max_row,max_col,4,41,10,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                for (c = 0; string2[c] != '\0';c++) {
                    if (!isdigit(string2[c])) break;
                }
                if (string2[c] != '\0' || c==0) {
                    mvprintw(4,0, "Enter a non-negative number N (e.g. 12) (use digits only instead of text): ");
                    refresh();
                    free(string2);
                    string2 = get_string(max_row,max_col,4,75,10,pointer);
                    if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                }
                command = malloc(5+strlen(string1)+strlen(string2));
                sprintf(command,"%d %s %s",query,string1,string2);
                break;
        case 7: mvprintw(0, 0, "Query 7 - Lists the top N airports with the highest median of delays.");
                mvprintw(2,0, "Enter a non-negative number N (e.g. 12): ");
                x = 4;
                string1 = get_string(max_row,max_col,2,41,10,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                for (c = 0; string1[c] != '\0';c++) {
                    if (!isdigit(string1[c])) break;
                }
                if (string1[c] != '\0' || c==0) {
                    mvprintw(2,0, "Enter a non-negative number N (e.g. 12) (use digits only instead of text): ");
                    refresh();
                    free(string1);
                    string1 = get_string(max_row,max_col,2,75,10,pointer);
                    if (proceed == 0) {
                        free(command);
                        free(string1);
                        free(string2);
                        free(string3);
                        return 0;
                    }
                }
                command = malloc(4+strlen(string1));
                sprintf(command,"%d %s",query,string1);
                break;
        case 8: mvprintw(0, 0, "Query 8 - Presents the total revenue of a hotel between two dates (inclusive).");
                mvprintw(2, 0, "Enter the ID of the hotel: ");
                string1 = get_string(max_row,max_col,2,27,60,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                mvprintw(4,0, "Enter the begin date in this format yyyy/MM/dd (e.g. 2023/01/31): ");
                string2 = get_string(max_row,max_col,4,66,20,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                mvprintw(6,0, "Enter the end date int this format yyyy/MM/dd (e.g. 2023/01/31): ");
                x = 8;
                string3 = get_string(max_row,max_col,6,64,20,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                command = malloc(6+strlen(string1)+strlen(string2)+strlen(string3));
                sprintf(command,"%d %s %s %s",query,string1,string2,string3);
                break;
        case 9: mvprintw(0, 0, "Query 9 - Lists all users whose names start with the prefix provided as an argument, sorted by name in ascending order.");
                mvprintw(2, 0, "Enter the prefix: ");
                x = 4;
                string1 = get_string(max_row,max_col,2,18,60,pointer);
                if (proceed == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                command = malloc(6+strlen(string1));
                sprintf(command,"%d \"%s\"",query,string1);
                break;
        case 10: mvprintw(0, 0, "Query 10 - Presents various overall metrics of the application.");
                mvprintw(2,0, "Navigate options using the arrow keys (up and down). Press Enter to select your choice.");
                mvprintw(4,0, "   All years.");
                mvprintw(6,0, "   One specific year.");
                mvprintw(8,0, "   One specific month.");
                option = get_option(4,3);
                if (option == 0) {
                    free(command);
                    free(string1);
                    free(string2);
                    free(string3);
                    return 0;
                }
                if (option != 1) {
                    mvprintw(10,0, "Enter the year: ");
                    string1 = get_string(max_row,max_col,10,16,14,pointer);
                    if (proceed == 0) {
                        free(command);
                        free(string1);
                        free(string2);
                        free(string3);
                        return 0;
                    }
                    if (option == 3) {
                        mvprintw(11,0, "Enter the month: ");
                        x = 13;
                        string2 = get_string(max_row,max_col,11,17,12,pointer);
                        if (proceed == 0) {
                            free(command);
                            free(string1);
                            free(string2);
                            free(string3);
                            return 0;
                        }
                        command = malloc(5+strlen(string1)+strlen(string2));
                        sprintf(command,"%d %s %s",query,string1,string2);
                    }
                    else {
                        x = 12;
                        command = malloc(4+strlen(string1));
                        sprintf(command,"%d %s",query,string1); 
                    }
                }
                else {
                    x = 10;
                    command = malloc(3);
                    sprintf(command,"%d",query);
                }
                break;
        case 11: break;
    }
    if (query != 11 && proceed == 1) {
        mvprintw(x,0,"Navigate options using the arrow keys (up and down). Press Enter to select the format of the output.");
        mvprintw(x+2,0,"   CSV");
        mvprintw(x+4,0,"   Field by field");
        option = get_option(x+2,2);
        if (option == 0) {
            free(command);
            free(string1);
            free(string2);
            free(string3);
            return 0;
        }
        proceed = option;
        mvprintw(x+6,0,"Executing query. Please wait...");
        refresh();
        Command* c = parseCommandLine(command);
        processCommand(c,0,result,catalogs);
        free(c);
    }
    else proceed = 0;
    free(command);
    free(string1);
    free(string2);
    free(string3);
    return proceed;
}

/* A função printResultPage_CSV trata de apresentar na tela o resultado de uma página no formato CSV.
Para isso, usamos a função do módulo do output, printResultF, e chamamos-la, até os resultados já não 
caberem mais na tela.*/
void printResultPage_CSV (int page, int max_row,int j, QueryResult* result) {
    int nResults = getNumberResults(result);
    for (int i = 2; i < max_row && j <= nResults; i++) {
        char* print = printResult(result,j-1);
        mvprintw(i,0,"%s",print);
        free(print);
        j++;
    }
}

/* A função printResultPage_Field trata de apresentar na tela o resultado de uma página no formato campo
por campo. Para isso, usamos a função do módulo do output, printResultF, e chamamos-la, até os resultados
já não caberem mais na tela.*/
void printResultPage_Field (int page, int max_row,int j, QueryResult* result) {
    int nResults = getNumberResults(result);
    int x = getNumberFieldsQ(result,j-1);
    for (int i = 2; i+(x+2) <= max_row; i+=x+2) {
        char* print = printResultF(result,j-1);
        if (j-1 == nResults) print[strlen(print)-1] = '\0'; //retira o último newline
        mvprintw(i,0,"%s",print);
        refresh();
        free(print);
        j++;
        if (j<=nResults) x = getNumberFieldsQ(result,j-1);
        else break;
    }
}

/* A função firstByPage recebe um apontador para um resultado, uma linha máxima, um inteiro que representa um formato de output e uma
lista de inteiros. Nesta lista de inteiros pretendemos colocar o número do resultado que inicia cada página. Por exemplo, a página 14, irá
corresponder á posição 13 nesta lista. Nesta posição iremos encontrar o número do primeiro resultado a colocar nesta página. Assim, esta
função calcula o primeiro resultado de todas as páginas, para depois ser mais facil e rápido apresentar os resultados de cada página.*/
void firstByPage (QueryResult* result, int max_row, int firstResult[],int format) {
    if (format == 2) { //formato do output: campo por campo
    int nResults = getNumberResults(result);
    int page = 0;
    int i = 0;
    int nFields;
    while (i<nResults) {
        firstResult[page] = i+1;
        page++;
        nFields = getNumberFieldsQ(result,i);
        for (int j = 2; j+(nFields+2) <= max_row; j += (nFields+2)) {
            i++;
            if (i<nResults) nFields = getNumberFieldsQ(result,i);
            else break;
        }
    }
    }
    else { //formato do output: CSV
        int nResults = getNumberResults(result);
        int page = 0;
        int i = 0;
        while (i<nResults) {
            firstResult[page] = i+1;
            page++;
            for (int j = 2; j < max_row && i<nResults; j++) {
                i++;
            }
        }
    }
}

/* A função pagesNumber recebe um apontador para um resultado, uma linha máxima e um inteiro que representa um formato de output. Esta função retorna
o número de páginas necessárias para apresentar o resultado no ecrã. Se o formato for campo por campo, então o número de páginas irá ter em consideração
o número de campos de um resultado (cada campo ocupa uma linha e mais uma linha é usada para decoração e outra é usada para separar os resultados). Se o
formato for CSV, cada resultado ocupará apenas uma linha. Em ambos os formatos precisamos de saber a linha máxima, para não escrevermos os resultados em
linhas superiores a essa (o que poderia causar erros ou não aparecer no ecrã).*/
int pagesNumber (QueryResult* result, int max_row, int format) {
    int nResults = getNumberResults(result);
    int page = 0;
    int i = 0;
    if (format == 2) { //formato do output: campo por campo
    int nFields;
    while (i<nResults) {
        page++;
        nFields = getNumberFieldsQ(result,i);
        for (int j = 2; j+(nFields+2) <= max_row; j += (nFields+2)) {
            i++;
           if (i<nResults) nFields = getNumberFieldsQ(result,i);
           else break;
        }
    }
    }
    else { //formato do output: CSV
        while (i<nResults) {
            page++;
            for (int j = 2; j < max_row && i<nResults; j++) {
                i++;
            }
        }
    }
    return page;
}

/* A função interactive_mode recebe um apontador para os catálogos e é responsável pelo modo interativo. Nesta função, primeiro inicializamos o ncurses. Depois
vamos verificar se a janela tem o tamanho apropriado. Se não tiver, encerramos o ncurses e o programa. Se tiver, será nos pedido o dataset. Temos 3 tentativas
para colocar o dataset correto. Se falhares todas, o programa é encerrado. Se colocares o dataset correto, irás para o menu e irás escolher uma querie e dar
informação para depois executa-la. Ou então irás escolher encerrar o programa, e assim acontecerá. Se escolheres uma tal querie, depois irás observar
a apresentação dos resultados. Ai poderás navegar pelos resultados, virando de página, usando as teclas left and right (esquerda e direita). Depois para
voltar ao menu outra vez, é so clicar Enter.*/
void interactive_mode(Catalogs* catalogs) {
    initscr(); //inicia ncurses

    noecho(); //para não escrever as teclas que são pressionadas no teclado

    keypad(stdscr, TRUE); //permite a interpretação de caracteres especiais

    int max_row, max_col;
    getmaxyx(stdscr, max_row, max_col);
    
    if (max_row < 26 || max_col < 154) {
        mvprintw(0,0,"The window is too small.\nExiting the program..."); //erro: tamanho da janela do terminal pequeno demais para este programa
        refresh();
        sleep(5);
    }
    else {
    int proceed = 1;
    int* pointer = &proceed;
    mvprintw(0, 0, "Welcome to Interactive Mode!\n\nWARNING: From now on, please keep the window size unchanged.\nThis program cannot handle window resizing.\nIf you resize the window, the program will end immediately.\n\nEnter the path of the dataset: ");
    refresh();
    char* path = get_string(max_row,max_col,6,31,500,pointer);
    int n = 0;
    int not_error = 4;
    while (!valid_directory_dataset(path) && n<2 && proceed == 1) { //verificar se o dataset é válido, se ainda não é a terceira tentativa e se o utilizador não decidiu sair do programa
        free(path);
        not_error = 0;
        clear();
        mvprintw(0,0,"Invalid path for the dataset. Please try again!");
        refresh();
        mvprintw(2,0,"Enter the path of the dataset: ");
        refresh();
        path = get_string(max_row,max_col,2,31,500,pointer);
        n++;
    }
    if (valid_directory_dataset(path) && proceed == 1) { //se o dataset for válido e se o utilizador não causou o fim do programa
    mvprintw(4 + not_error,0, "Parsing files and sorting data. Please wait...");
    refresh();
    parse_all_files(path,catalogs);
    sortCatalogs(catalogs);
    QueryResult * result = createQResult();
    proceed = get_querie(max_row,max_col,catalogs,result);
    while (proceed) { //modo de paginação
        clear();
        mvprintw(0,0, " <  Previous page (Press Left)");
        mvprintw(0,max_col/2, "Page 1");
        mvprintw(0,max_col/4, "(Press Enter to access the menu)");
        mvprintw(0,max_col-27, "(Press Right) Next page  > ");
        int pages = pagesNumber(result,max_row,proceed); //calcular páginas totais
        int firstResult[pages];
        firstByPage(result,max_row,firstResult,proceed); //calcular primeiro resultado de todas as páginas
        int page = 1;
        if (pages != 0) {
            if (proceed == 2) printResultPage_Field(page,max_row,firstResult[page-1],result); //apresentar a primeira página, com os resultados campo por campo
            else printResultPage_CSV(page,max_row,firstResult[page-1],result); //apresentar a primeira página, com os resultados CSV
        }
        move(0,1);     
        int key = getch(); //tecla pressionada pelo utilizador
        while (key != '\n') { //enquanto a tecla não for Enter (pois Enter irá nos levar para o menu novamente)
            if (key == KEY_LEFT) {
                if (page != 1 && pages!=0) { //se a tecla for left e não estivermos na primeira página, passamos para a página anterior
                    page--;
                    clear();
                    mvprintw(0,0, " <  Previous page (Press Left)");
                    mvprintw(0,max_col/2, "Page %d     ",page);
                    mvprintw(0,max_col/4, "(Press Enter to access the menu)");
                    mvprintw(0,max_col-27, "(Press Right) Next page  > ");
                    if (pages != 0) {
                        if (proceed == 2) printResultPage_Field(page,max_row,firstResult[page-1],result);
                        else printResultPage_CSV(page,max_row,firstResult[page-1],result);
                    }
                }
                move(0,1);
            }
            if (key == KEY_RIGHT) {
                if (page != pages && pages!=0) { //se a tecla for right e não estivermos na última página, passamos para a página seguinte
                    page++;
                    clear();
                    mvprintw(0,0, " <  Previous page (Press Left)");
                    mvprintw(0,max_col/2, "Page %d     ",page);
                    mvprintw(0,max_col/4, "(Press Enter to access the menu)");
                    mvprintw(0,max_col-27, "(Press Right) Next page  > ");
                    if (pages != 0) {
                        if (proceed == 2) printResultPage_Field(page,max_row,firstResult[page-1],result);
                        else printResultPage_CSV(page,max_row,firstResult[page-1],result);
                    }
                }
                move(0,max_col-2);
            }
            if (key == KEY_RESIZE || key == KEY_F(11)) { //se o utilizador alterar o tamanho da janela do terminal, o programa será encerrado
                break;
            }
            key = getch(); //tecla pressionada pelo utilizador
        }
        destroyQResult(result);
        result = createQResult();
        if (key == KEY_RESIZE || key == KEY_F(11)) proceed = 0;
        else proceed = get_querie(max_row,max_col,catalogs,result); //se o utilizador não saiu do programa, então volta para o menu
    }
    destroyQResult(result);
    }
    free(path);
    clear();
    mvprintw(0,0,"Exiting program...");
    refresh();
    sleep(1);
    }
    endwin(); //terminar ncurses
}