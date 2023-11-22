#include "hotelsManager.h"

struct hotelsManager {
    Hashtable *hotels;
//    OrdList *hotelsByName;
};
//função que cria um novo catálogo de hoteis
HotelsManager *createHotelsCatalog(int size) {
    HotelsManager *hotelsManager = malloc(sizeof(HotelsManager));
    hotelsManager->hotels = createHashtable(size);
    return hotelsManager;
}
//função que adiciona um hotel ao catálogo de hoteis
void addHotelToCatalog(HotelsManager *hotelsManager, Hotel *hotel, Reservation *reservation, unsigned int key) {
    addReservationToHotel(hotel, reservation);
    addHashtable(hotelsManager->hotels, key, hotel, getHotelId(hotel));
}
//função que ordena o catálogo hoteis
void sortHotelCatalog(HotelsManager *hotelsManager) {
    sortOrdlistHashtable(hotelsManager->hotels, sortHotelReservationsByDate); //ordena a lista de reservas de cada hotel na hashtable
}

//gets
Hotel *getHotelCatalog(HotelsManager *hotelsManager, unsigned int key, char *id) {
    Hotel *hotel = (Hotel *) getData(hotelsManager->hotels, key, id);
    return hotel;
}

Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager) {
    return hotelsManager->hotels;
}

//função que imprime o id de um hotel, para efeitos de teste
void printFunctionHotel(void *data) {
    char *hotelId = getHotelId((Hotel *) data);
    printf(" %8s)", hotelId);
    free(hotelId);
}
//função que imprime o catálogo de hoteis, para efeitos de teste
void printHotels(HotelsManager *hotelsManager) {
    printTable(hotelsManager->hotels, printFunctionHotel);
    printHashtableUsage(hotelsManager->hotels);
}

//função que liberta a memória alocada do catálogo de hoteis
void destroyHotelsCatalog(HotelsManager *hotelsManager) {
    if (hotelsManager == NULL) return; //se o catálogo não existir
    destroyHashtable(hotelsManager->hotels, destroyHotel); //liberta a hashtable de hoteis
    free(hotelsManager);
}
