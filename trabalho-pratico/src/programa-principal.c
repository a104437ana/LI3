#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "catalogsManager.h"
#include "results.h"
#include "parser.h"
#include "interpreter.h"
#include <locale.h>
#include <sys/resource.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include "interactive.h"

int main (int argc, char** argv) {

    setlocale(LC_ALL, "en_US.UTF-8");

    Catalogs *catalogs = createCatalogs();

    if (argc == 3) {
        if (valid_directory_dataset(argv[1])) {
            if (exist_file(argv[2])) {

                parse_all_files(argv[1],catalogs);
                sortCatalogs(catalogs);
                parseCommandFile(argv[2],catalogs,0,NULL,NULL);

            }
            else printf("Error: The provided file path does not match any existing file.\n");
        }
        else printf("Error: The provided directory path is not valid for the dataset.\n");
    }
    else {
    if (argc == 1) {
    printf("Attention: This program requires a minimum window size of 154x26. Please adjust the window size now to meet the requirements and your preferences. Note that resizing won't be supported after this adjustment, so choose wisely. After adjusting, press Enter to continue...");
    getchar();
    interactive_mode(catalogs);
    }
    else printf("Error: This program requires either exactly 3 or 1 argument(s).\n");
    }

    //liberta o espaço em memória dos catalogos
    destroyCatalogs(catalogs);

    return 0;
}
