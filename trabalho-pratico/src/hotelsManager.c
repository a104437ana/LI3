#include <stdio.h>
#include <stdlib.h>
#include "hotelsManager.h"
#include "hashtable.h"

struct hotelsManager {
    Hashtable *hotels;
//    OrdList *hotelsByName;
};

HotelsManager *createHotelsCatalog(int size) {
    HotelsManager *hotelsManager = malloc(sizeof(HotelsManager));
    hotelsManager->hotels = createHashtable(size);
    return hotelsManager;
}

void addHotelToCatalog(HotelsManager *hotelsManager, Hotel *hotel, Reservation *reservation, unsigned int key) {
    addReservationToHotel(hotel, reservation);
    addHashtable(hotelsManager->hotels, key, hotel, getHotelId(hotel));
}

void sortHotelCatalog(HotelsManager *hotelsManager) {
    sortOrdlistHashtable(hotelsManager->hotels, sortHotelReservationsByDate);
}

Hotel *getHotelCatalog(HotelsManager *hotelsManager, unsigned int key, char *id) {
    Hotel *hotel = (Hotel *) getData(hotelsManager->hotels, key, id);
    return hotel;
}

Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager) {
    return hotelsManager->hotels;
}

void printFunctionHotel(void *data) {
    char *hotelId = getHotelId((Hotel *) data);
    printf(" %8s)", hotelId);
    free(hotelId);
}

void printHotels(HotelsManager *hotelsManager) {
    printTable(hotelsManager->hotels, printFunctionHotel);
    printHashtableUsage(hotelsManager->hotels);
}
