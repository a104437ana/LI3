#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main (int argc, char** argv) {
    if (argc == 3) {
    parse_all_files(argv[1]);
    }
    return 0;
}
