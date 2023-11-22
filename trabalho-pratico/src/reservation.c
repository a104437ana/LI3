#include "reservation.h"

struct reservation {
    char *id;
    char *id_user;
    Hotel *hotel;
    Date *begin;
    Date *end;
    int pricePerNight;
    bool includesBreakfast;
    //char *roomDetails;
    char userClassification;
    //char *userComment;
};
//função que cria uma nova reserva dados os dados da mesma
Reservation *createReservation(char *id, char *id_user, char *id_hotel, char *hotelName, char hotelStars, /*char *hotelAddress,*/ int cityTax, Date *begin, Date *end, int pricePerNight, bool includesBreakfast, /*char *roomDetails,*/ char userClassification, /*char *userComment,*/ Hashtable *hotels) {
    Reservation *reservation = malloc(sizeof(Reservation)); //aloca espaço em memória para a reserva
    reservation->id = strdup(id); //aloca espaço para os diferentes campos da reserva
    reservation->id_user = strdup(id_user);
    unsigned int hotelKey = hashFunction(id_hotel);
    int existsHotel = existsData(hotels, hotelKey, id_hotel); //verifica se o hotel já existe no catálogo de hoteis
    Hotel *hotel;
    if (existsHotel == 0) { //caso não exista cria um novo hotel
        hotel = createHotel(id_hotel, hotelName, hotelStars, /*hotelAddress,*/ cityTax);
        addHashtable(hotels, hotelKey, hotel, id_hotel); //adiciona o hotel ao catálogo dos hoteis
    } else //caso já exista
        hotel = (Hotel*) getData(hotels, hotelKey, id_hotel); //obtem apontador para o hotel do catálogo dos hoteis
    addReservationToHotel(hotel, reservation); //adiciona o apontador da reserva às reservas do hotel
    addToHotelRatingsSum(hotel, userClassification); //incremanta a soma das classificações do hotel caso tenha sido dada uma
    addToHotelNumberRatings(hotel, userClassification); //incrementa o numero de classificações do hotel
    reservation->hotel = hotel;
    reservation->begin = begin;
    reservation->end = end;
    reservation->pricePerNight = pricePerNight;
    reservation->includesBreakfast = includesBreakfast;
    //reservation->roomDetails = strdup(roomDetails);
    reservation->userClassification = userClassification;
    //reservation->userComment = strdup(userComment);

    return reservation; //retorna o apontador para a nova reserva
}

//gets dos campos da reserva
char *getReservId(Reservation *reservation) {
    return reservation->id; //falta encapsulamento
}

char *getReservUserId(Reservation *reservation) {
    return reservation->id_user; //encapsulamento
}

char *getReservHotelId(Reservation *reservation) {
    return getHotelId(reservation->hotel);
}

int getReservUserKey(Reservation *reservation) {
    return hashFunction(reservation->id_user);
}

char *getReservHotelName(Reservation *reservation) {
    return getHotelName(reservation->hotel);
}
/*
char *getReservHotelAddress(Reservation *reservation) {
    return getHotelAddress(reservation->hotel);
}

char *getReservRoomDetails(Reservation *reservation) {
    return reservation->roomDetails; //falta encapsulamento
}

char *getReservUserComment(Reservation *reservation) {
    return reservation->userComment; //falta encapsulamento
}
*/
Hotel *getReservHotel(Reservation *reservation) {
    return reservation->hotel;
}

int getReservCityTax(Reservation *reservation) {
    return getHotelCityTax(reservation->hotel);
}

int getReservPricePerNight(Reservation *reservation) {
    return reservation->pricePerNight;
}

int getReservUserClassification(Reservation *reservation) {
    return (reservation->userClassification-'0');
}

char getReservHotelStars(Reservation *reservation) {
    return getHotelStars(reservation->hotel);
}

Date *getReservBegin(Reservation *reservation) {
    return reservation->begin;
}

Date *getReservEnd(Reservation *reservation) {
    return reservation->end;
}

int getReservBeginDay(void *reservation) {
    return ((Reservation*)reservation)->begin->day;
}

int getReservBeginMonth(void *reservation) {
    return ((Reservation*)reservation)->begin->month;
}

int getReservBeginYear(void *reservation) {
    return ((Reservation*)reservation)->begin->year;
}

int getReservEndDay(void *reservation) {
    return ((Reservation*)reservation)->end->day;
}

int getReservEndMonth(void *reservation) {
    return ((Reservation*)reservation)->end->month;
}

int getReservEndYear(void *reservation) {
    return ((Reservation*)reservation)->end->year;
}

bool getReservIncludesBreakfast(Reservation *reservation) {
    return reservation->includesBreakfast;
}

//sets dos campos da reserva
void setUserId(Hashtable *hashtable, unsigned int key, char *id_user, char *reservId) {
    Reservation *data = getData(hashtable, key, reservId);
    char *oldUserId = data->id_user;
    data->id_user = strdup(id_user);
    free(oldUserId);
}

void setHotelId(Hashtable *hashtable, unsigned int key, char *id_hotel, char* id) {
    Reservation *data = getData(hashtable, key, id);
    removeHId(data->hotel);
    setHId(data->hotel, id_hotel);
}

void setHotelName(Hashtable *hashtable, unsigned int key, char *hotelName, char* id) {
    Reservation *data = getData(hashtable, key, id);
    removeHName(data->hotel);
    setHName(data->hotel, hotelName);
}

void setHotelStars(Hashtable *hashtable, unsigned int key, char hotelStars, char *id) {
    Reservation *data = getData(hashtable, key, id);
    setHStars(data->hotel, hotelStars);
}

void setCityTax(Hashtable *hashtable, unsigned int key, int cityTax, char *id) {
    Reservation *data = getData(hashtable, key, id);
    setHCityTax(data->hotel, cityTax);
}
/*
void setHotelAdress(Hashtable *hashtable, unsigned int key, char *hotelAddress, char *id) {
    Reservation *data = getData(hashtable, key, id);
    removeHAddress(data->hotel);
    setHAddress(data->hotel, hotelAddress);
}
*/
void setBeginDate(Hashtable *hashtable, unsigned int key, Date *begin, char *id) {
    Reservation *data = getData(hashtable, key, id);
    data->begin = begin;
}

void setEndDate(Hashtable *hashtable, unsigned int key, Date *end, char *id) {
    Reservation *data = getData(hashtable, key, id);
    data->end = end;
}

void setPricePerNight(Hashtable *hashtable, unsigned int key, int pricePerNight, char *id) {
    Reservation *data = getData(hashtable, key, id);
    data->pricePerNight = pricePerNight;
}

void setIncludesBreakfast(Hashtable *hashtable, unsigned int key, bool includesBreakfast, char *id) {
    Reservation *data = getData(hashtable, key, id);
    data->includesBreakfast = includesBreakfast;
}
/*
void setRoomDetails(Hashtable *hashtable, unsigned int key, char *roomDetails, char *id) {
    Reservation *data = getData(hashtable, key, id);
    char *oldRoomDetails = roomDetails;
    data->roomDetails = strdup(roomDetails);
    free(oldRoomDetails);
}
*/
void setUserClassification(Hashtable *hashtable, unsigned int key, char userClassification, char *id) {
    Reservation *data = getData(hashtable, key, id);
    data->userClassification = userClassification;
}
/*
void setUserComment(Hashtable *hashtable, unsigned int key, char *userComment, char *id) {
    Reservation *data = getData(hashtable, key, id);
    char *oldUserComment = userComment;
    data->userComment = strdup(userComment);
    free(oldUserComment);
}
*/
Date *getBeginDateReservation(void *reservation) {
    return ((Reservation*)reservation)->begin;
}
//função que liberta o espaço em memória alocado pela reserva
void destroyReservation(void *reservation) {
    if (reservation == NULL) return; //se a reserva não existir
//    free(((Reservation *) reservation)->hotel);
//    destroyHotel(((Reservation *) reservation)->hotel);
    destroyDate(((Reservation *) reservation)->begin); //liberta espaço em memória dos diferentes campos
    destroyDate(((Reservation *) reservation)->end);
    //free(((Reservation *) reservation)->userComment);
    //free(((Reservation *) reservation)->roomDetails);
    free(((Reservation *) reservation)->id_user);
    free(((Reservation *) reservation)->id);
    free(reservation);
}
