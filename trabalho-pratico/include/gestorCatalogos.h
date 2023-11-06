#ifndef _GESTOR_CATALOGOS_
#define _GESTOR_CATALOGOS_

#include "gestorUtilizadores.h"
#include "gestorVoos.h"
#include "gestorReservas.h"
#include "gestorHoteis.h"
#include "gestorAeroportos.h"

typedef struct catalogos Catalogos;

void criaGestorUtilizadores();
//void adicionaUtilizador();
//void procuraUtilizador();
//void removeUtilizador();
void destroiGestorUtilizadores();

void criaGestorVoos();
void adicionaVoo();
void procuraVoo();
void removeVoo();
void destroiGestorVoos();

void criaGestorReservas();
void adicionaReserva();
void procuraReserva();
void removeReserva();
void destroiGestorReservas();

void criaGestorHoteis();
void adicionaHotel();
void procuraHotel();
void removeHotel();
void destroiGestorHoteis();

void criaGestorAeroportos();
void adicionaAeroporto();
void procuraAeroporto();
void removeAeroporto();
void destroiGestorAeroportos();

#endif