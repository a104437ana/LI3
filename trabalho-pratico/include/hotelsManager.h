#ifndef _HOTELS_MANAGER_
#define _HOTELS_MANAGER_

#include "hotel.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct hotelsManager HotelsManager;

HotelsManager *createHotelsCatalog(int size);
void addHotelToCatalog(HotelsManager *hotelsManager, Hotel *hotel, Reservation *reservation, unsigned int key);
void sortHotelCatalog(HotelsManager *hotelsManager);
//gets
Hotel *getHotelCatalog(HotelsManager *hotelsManager, unsigned int key, char *id);
Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager);

void printHotels(HotelsManager *hotelsManager);

void destroyHotelsCatalog(HotelsManager *hotelsManager);

#endif