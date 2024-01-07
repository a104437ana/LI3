#ifndef _HOTELS_MANAGER_
#define _HOTELS_MANAGER_

#include "hotel.h"
#include "reservationsManager.h"
#include "hashtable.h"
#include "orderedList.h"
#include "results.h"

typedef struct hotelsManager HotelsManager;
//cria um novo catálogo de hoteis
HotelsManager *createHotelsCatalog(int size);
//atualiza catálogo de hoteis
void updateHotelCatalog(char *id, char *name, char stars, int cityTax, char userClassification, char *id_reserv, HotelsManager *hotelsCatalog);

//gets
Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager);

//imprime o catálogo de hoteis, para efeitos de teste
void printHotels(HotelsManager *hotelsManager);

//liberta espaço em memória do catálogo de hoteis
void destroyHotelsCatalog(HotelsManager *hotelsManager);

// queries
void hotel_catalog_compute_Q1(char* hotel_id,HotelsManager* hotel_catalog,QueryResult* result);
void hotel_catalog_compute_Q3(char* id_hotel,HotelsManager* hotel_catalog, QueryResult* result);

#endif