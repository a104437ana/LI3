#ifndef _UTILIZADOR_
#define _UTILIZADOR_

#include "utilidade.h"
#include "hashtable.h"

typedef struct utilizador Utilizador;

// melhor forma de criar utilizador garantindo encapsulamento, sem passar todos parametros um a um
Utilizador *criaUtilizador(char *id, char *nome, Genero genero, char pais[2], char *morada, char *passaporte, Data nascimento, char *email, Telemovel telemovel, Data criacao_conta);
void adicionaUtilizadorVoo(char *id, int id_voo);
void adicionaUtilizadorReserva(char *id, int id_reserva);

//gets e sets fazer get multiplo e set multiplo
//gets
char *getNome(Hashtable *hashtable, unsigned int chave);
Genero getGenero(Hashtable *hashtable, unsigned int chave);
char *getPais(Hashtable *hashtable, unsigned int chave);
char *getMorada(Hashtable *hashtable, unsigned int chave);
char *getPassaporte(Hashtable *hashtable, unsigned int chave);
Data getNascimento(Hashtable *hashtable, unsigned int chave);
char *getEmail(Hashtable *hashtable, unsigned int chave);
Telemovel getTelemovel(Hashtable *hashtable, unsigned int chave);
Data getCriacaoConta(Hashtable *hashtable, unsigned int chave);
//sets
void setNome(Hashtable *hashtable, unsigned int chave, char *nome);
void setGenero(Hashtable *hashtable, unsigned int chave, Genero genero);
void setPais(Hashtable *hashtable, unsigned int chave, char *pais);
void setMorada(Hashtable *hashtable, unsigned int chave, char *morada);
void setPassaporte(Hashtable *hashtable, unsigned int chave, char *passaporte);
void setNascimento(Hashtable *hashtable, unsigned int chave, Data nascimento);
void setEmail(Hashtable *hashtable, unsigned int chave, char *email);
void setTelemovel(Hashtable *hashtable, unsigned int chave, Telemovel telemovel);
void setCriacaoConta(Hashtable *hashtable, unsigned int chave, Data criacaoConta);

#endif