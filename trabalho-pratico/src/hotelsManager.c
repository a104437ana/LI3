#include <stdio.h>
#include <stdlib.h>
#include "hotelsManager.h"
#include "hashtable.h"

struct hotelsManager {
    Hashtable *hotels;
};
//função que cria um novo catálogo de hoteis
HotelsManager *createHotelsCatalog(int size) {
    HotelsManager *hotelsManager = malloc(sizeof(HotelsManager));
    hotelsManager->hotels = createHashtable(size, hashString, strcmpVoid, strdupVoid, destroyHotel);
    return hotelsManager;
}
//atualiza catálogo de hoteis
void updateHotelCatalog(char *id, char *name, char stars, int cityTax, char userClassification, int id_reserv, HotelsManager *hotelsCatalog) {
    int existsHotel = existsData(hotelsCatalog->hotels, id); //verifica se o hotel já existe no catálogo de hoteis
    Hotel *hotel;
    if (existsHotel == 0) { //caso não exista cria um novo hotel
        hotel = createHotel(id, name, stars, cityTax);
        hotelsCatalog->hotels = addHashtable(hotelsCatalog->hotels, hotel, id); //adiciona o hotel ao catálogo dos hoteis
    } else //caso já exista
        hotel = (Hotel*) getData(hotelsCatalog->hotels, id); //obtem apontador para o hotel do catálogo dos hoteis
    addReservationToHotel(hotel, id_reserv, userClassification); //adiciona reserva às reservas do hotel e atualiza classificação do hotel
}

void sortHotelReservationsByDate_hotelsCatalog(char *id, HotelsManager *hotelsCatalog, void (*sortFunction)(void*,void*), void *lookup) {
    Hotel *hotel = getData(hotelsCatalog->hotels, id);
    sortHotelReservationsByDate_hotel(hotel, sortFunction, lookup);
}

//função que liberta a memória alocada do catálogo de hoteis
void destroyHotelsCatalog(HotelsManager *hotelsManager) {
    if (hotelsManager == NULL) return; //se o catálogo não existir
    destroyHashtable(hotelsManager->hotels); //liberta a hashtable de hoteis
    free(hotelsManager);
}

//queries
int hotel_catalog_compute_Q1(char* hotel_id,HotelsManager* hotel_catalog,QueryResult* result) {
    if (hotel_id == NULL) {
        return -1;
    }
    else {
        Hotel* hotel = getData(hotel_catalog->hotels,hotel_id);
        if (hotel==NULL) return -1;
        char* hotel_name = getHotelName(hotel); char * field1 = strdup("hotel_name");
        char hotel_stars = getHotelStars(hotel);
        char * stars = malloc(sizeof(char)*2);
        sprintf(stars, "%c", hotel_stars); char * field2 = strdup("hotel_stars");

        setFieldQ(result, 0, 1, field1, hotel_name);
        setFieldQ(result, 0, 2, field2, stars); 
        //os outros campos são preenchidos pela reservation_catalog_compute_Q1 e catalogs_compute_Q1_reservation

        free(hotel_name); free(stars);
        free(field1); free(field2);

        int city_tax = getHotelCityTax(hotel);
        return city_tax;
    }
}

void hotel_catalog_compute_Q3 (char* id_hotel,HotelsManager* hotel_catalog, QueryResult* result) {
    if (id_hotel==NULL) return;
    Hotel* hotel = getData(hotel_catalog->hotels,id_hotel);
    if (hotel == NULL) {
        return;
    }
    else {
        setNumberResults(result,1);
        setNumberFieldsQ(result, 0, 1);
        int numberClassifications = getHotelNumberOfReservations(hotel);
        double rating = getHotelRatingsSum(hotel);
        rating /= numberClassifications;
        char * ratingS = malloc(sizeof(char)*6);
        sprintf(ratingS, "%.3f", rating); char * field0 = strdup("rating");
        
        setFieldQ(result, 0, 0, field0, ratingS); 

        free(ratingS);
        free(field0);
    }
}

//gets
Hashtable *getHashtableHotelsCatalog(HotelsManager *hotelsManager) {
    return hotelsManager->hotels;
}

int getCityTax(char *id, HotelsManager *hotelsCatalog) {
    Hotel *hotel = getData(hotelsCatalog->hotels, id);
    int cityTax = getHotelCityTax(hotel);
    return cityTax;
}
Hotel *getHotelCatalog(HotelsManager *hotelsCatalog, char *id) {
    Hotel *hotel = (Hotel *) getData(hotelsCatalog->hotels, id);
    return hotel;
}
int getHotelSizeReservations(char *id, HotelsManager *hotelsCatalog) {
    Hotel *hotel = getData(hotelsCatalog->hotels, id);
    return getHotelNumberOfReservations(hotel);
}

int hotelExists(char *id, HotelsManager *hotelsCatalog) {
    return existsData(hotelsCatalog->hotels, id);
}
int getHotelReservationId(char *id, int index, HotelsManager *hotelsCatalog) {
    Hotel *hotel = getData(hotelsCatalog->hotels, id);
    return getHotelReservId(hotel, index);
}
//int searchHotelDates_hotelsCatalog(Date *date, char *id, int (*compareDate)(void*,void*,void*), void *lookup, HotelsManager *hotelsCatalog) {
//    Hotel *hotel = getData(hotelsCatalog->hotels, id);
//    return searchHotelDates(date, compareDate, lookup, hotel);
//}
