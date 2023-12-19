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
    hotelsManager->hotels = createHashtable(size);
    return hotelsManager;
}
//atualiza catálogo de hoteis
void updateHotelCatalog(char *id, char *name, char stars, int cityTax, char userClassification, char *id_reserv, HotelsManager *hotelsCatalog) {
    unsigned int key = hashFunction(id);
    int existsHotel = existsData(hotelsCatalog->hotels, key, id); //verifica se o hotel já existe no catálogo de hoteis
    Hotel *hotel;
    if (existsHotel == 0) { //caso não exista cria um novo hotel
        hotel = createHotel(id, name, stars, cityTax);
        hotelsCatalog->hotels = addHashtable(hotelsCatalog->hotels, key, hotel, id); //adiciona o hotel ao catálogo dos hoteis
    } else //caso já exista
        hotel = (Hotel*) getData(hotelsCatalog->hotels, key, id); //obtem apontador para o hotel do catálogo dos hoteis
    addReservationToHotel(hotel, id_reserv); //adiciona reserva às reservas do hotel
    addToHotelRatingsSum(hotel, userClassification); //incremanta a soma das classificações do hotel caso tenha sido dada uma
    addToHotelNumberRatings(hotel, userClassification); //incrementa o numero de classificações do hotel
}

//gets
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

//queries
void hotel_catalog_compute_Q1(char* hotel_id,HotelsManager* hotel_catalog,Results* results) {
    if (hotel_id == NULL) {
        setQ1type(results,0);
    }
    else {
    Hotel* hotel = getData(hotel_catalog->hotels,hashFunction(hotel_id),hotel_id);
    if (hotel==NULL) setQ1type(results,0); //se o id não existir
    else {
        char* hotel_name = getHotelName(hotel);
        int hotel_stars = getHotelStars(hotel);
        int ppn = getTotalPriceQ1(results); //preço por noite
        int nnights = getNnightsQ1(results); //número de noites
        int cityTax = getHotelCityTax(hotel); //taxa turística
        double res = (double) ((ppn*nnights)+(((double)(ppn*nnights)/100.0)*cityTax));
        setHotelNameQ1(results,hotel_name);
        setHotelStarsQ1(results,hotel_stars);
        setTotalPriceQ1(results,res);
    }
    }
}

void hotel_catalog_compute_Q3 (char* id_hotel,HotelsManager* hotel_catalog, Results* results) {
    if (id_hotel == NULL) {
        setRating(results,-1.0);
    }
    else {
    Hotel* hotel = getData(hotel_catalog->hotels,hashFunction(id_hotel),id_hotel);
    if (hotel==NULL) setRating(results,-1.0); //se o id não existir
    else {
        int numberClassifications = getHotelNumberOfReservations(hotel);
        double result = getHotelRatingsSum(hotel);
        result /= numberClassifications;
        setRating(results,result);
    }
    }
}