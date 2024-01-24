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
void updateHotelCatalog(char *id, char *name, char stars, int cityTax, char userClassification, unsigned long int id_reserv, HotelsManager *hotelsCatalog);

//gets
int hotelExists(char *id, HotelsManager *hotelsCatalog);
int getCityTax(char *id, HotelsManager *hotelsCatalog);
int getHotelSizeReservations(char *id, HotelsManager *hotelsCatalog);
unsigned long int getHotelReservationId(char *id, int index, HotelsManager *hotelsCatalog);
int searchHotelDates_hotelsCatalog(Date *date, char *id, int (*compareDates)(void*,void*,void*), void *lookup, HotelsManager *hotelsCatalog);
Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager);

//liberta espaço em memória do catálogo de hoteis
void destroyHotelsCatalog(HotelsManager *hotelsManager);

//sort
void sortHotelReservationsByDate_hotelsCatalog(char *id, HotelsManager *hotelsCatalog, void (*sortFunction)(void*,void*), void *lookup);

// queries
int hotel_catalog_compute_Q1(char* hotel_id,HotelsManager* hotel_catalog,QueryResult* result);
void hotel_catalog_compute_Q3(char* id_hotel,HotelsManager* hotel_catalog, QueryResult* result);

#endif