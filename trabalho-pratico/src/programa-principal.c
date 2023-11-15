#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "usersManager.h"
#include "reservationsManager.h"

int main (int argc, char** argv) {
    if (argc == 3) {
    UsersManager * user_catalog = createUsersCatalog(600);
    ReservationsManager * reservation_catalog = createReservsCatalog(600);
    parse_all_files(argv[1],user_catalog,reservation_catalog);
    }
    return 0;
}
