#ifndef _HOTELS_MANAGER_
#define _HOTELS_MANAGER_

#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct hotelsManager HotelsManager;
//cria um novo catálogo de hoteis
HotelsManager *createHotelsCatalog(int size);
//adiciona um hotel ao catálogo de hoteis
void addHotelToCatalog(HotelsManager *hotelsManager, Hotel *hotel, Reservation *reservation, unsigned int key);
//ordena o catálogo de hoteis
void sortHotelCatalog(HotelsManager *hotelsManager);

//gets
Hotel *getHotelCatalog(HotelsManager *hotelsManager, unsigned int key, char *id);
Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager);

//imprime o catálogo de hoteis, para efeitos de teste
void printHotels(HotelsManager *hotelsManager);

//liberta espaço em memória do catálogo de hoteis
void destroyHotelsCatalog(HotelsManager *hotelsManager);

#endif