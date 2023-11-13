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
    addHashtable(hotelsManager->hotels, key, hotel);
}

void sortHotelCatalog(HotelsManager *hotelsManager) {
    sortHotelsReservsHashtable(hotelsManager->hotels);
}

Hotel *getHotelCatalog(HotelsManager *hotelsManager, unsigned int key) {
    Hotel *hotel = (Hotel *) getData(hotelsManager->hotels, key);
    return hotel;
}

Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager) {
    return hotelsManager->hotels;
}
