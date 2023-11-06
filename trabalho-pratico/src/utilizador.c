#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilizador.h"

struct utilizador {
    char *id;
    char *nome;             //q1
    Genero genero;          //q1
    char pais[2];
    char *morada;
    char *passaporte;       //q1
    Data nascimento;        //q1
    char *email;
    Telemovel telemovel;
    Data criacao_conta;
    int *id_voo;            //q1/q2
    int *id_reserva;        //q1/q2     //? Book<id>
    double total_gasto;     //q1        //?
};

// gets e sets em vez de criar utilizador completo por causa do apontador para a struct ?
Utilizador *criaUtilizador(char *id, char *nome, Genero genero, char pais[2], char *morada, char *passaporte, Data nascimento, char *email, Telemovel telemovel, Data criacao_conta) {
    Utilizador *utilizador = malloc(sizeof(Utilizador));
    utilizador->id = strdup(id);
    utilizador->nome = strdup(nome);
    utilizador->genero = genero;
    utilizador->pais[0] = pais[0];
    utilizador->pais[1] = pais[1];
    utilizador->morada = strdup(morada);
    utilizador->passaporte = strdup(passaporte);
    utilizador->nascimento = nascimento;
    utilizador->email = strdup(email);
    utilizador->telemovel = telemovel;
    utilizador->criacao_conta = criacao_conta;

    return utilizador;
}

void adicionaUtilizadorVoo(char *id, int id_voo) {
}

void adicionaUtilizadorReserva(char *id, int id_reserva) {
}

//gets
char *getNome(Hashtable *hashtable, unsigned int chave) {
    char *nome;
    Utilizador *data = getData(hashtable, chave);
    nome = strdup(data->nome);

    return nome;
}

Genero getGenero(Hashtable *hashtable, unsigned int chave) {
    Genero genero;
    Utilizador *data = getData(hashtable, chave);
    genero = data->genero;

    return genero;
}

char *getPais(Hashtable *hashtable, unsigned int chave) {
    char pais[2];
    Utilizador *data = getData(hashtable, chave);
    pais[0] = data->pais[0];
    pais[1] = data->pais[1];

    return pais;
}

char *getMorada(Hashtable *hashtable, unsigned int chave) {
    char *morada;
    Utilizador *data = getData(hashtable, chave);
    morada = strdup(data->morada);

    return morada;
}

char *getPassaporte(Hashtable *hashtable, unsigned int chave) {
    char *passaporte;
    Utilizador *data = getData(hashtable, chave);
    passaporte = strdup(data->passaporte);

    return passaporte;
}

Data getNascimento(Hashtable *hashtable, unsigned int chave) {
    Data nascimento;
    Utilizador *data = getData(hashtable, chave);
    nascimento = data->nascimento;

    return nascimento;
}

char *getEmail(Hashtable *hashtable, unsigned int chave) {
    char *email;
    Utilizador *data = getData(hashtable, chave);
    email = strdup(data->email);

    return email;
}

Telemovel getTelemovel(Hashtable *hashtable, unsigned int chave) {
    Telemovel numero;
    Utilizador *data = getData(hashtable, chave);
    numero = data->telemovel;

    return numero;
}

Data getCriacaoConta(Hashtable *hashtable, unsigned int chave) {
    Data criacaoConta;
    Utilizador *data = getData(hashtable, chave);
    criacaoConta = data->criacao_conta;

    return criacaoConta;
}

//sets
void setNome(Hashtable *hashtable, unsigned int chave, char *nome) {
    Utilizador *data = getData(hashtable, chave);
    char *nomeAntigo = data->nome;
    data->nome = strdup(nome);
    free(nomeAntigo);
}

void setGenero(Hashtable *hashtable, unsigned int chave, Genero genero) {
    Utilizador *data = getData(hashtable, chave);
    data->genero = genero;
}

void setPais(Hashtable *hashtable, unsigned int chave, char *pais) {
    Utilizador *data = getData(hashtable, chave);
    char paisAntigo[2];
    paisAntigo[0] = data->pais[0];
    paisAntigo[1] = data->pais[1];
    data->pais[0] = pais[0];
    data->pais[1] = pais[1];
}

void setMorada(Hashtable *hashtable, unsigned int chave, char *morada) {
    Utilizador *data = getData(hashtable, chave);
    char *moradaAntiga = data->morada;
    data->morada = strdup(morada);
    free(moradaAntiga);
}

void setPassaporte(Hashtable *hashtable, unsigned int chave, char *passaporte) {
    Utilizador *data = getData(hashtable, chave);
    char *passaporteAntigo = data->passaporte;
    data->passaporte = strdup(passaporte);
    free(passaporteAntigo);
}

void setNascimento(Hashtable *hashtable, unsigned int chave, Data nascimento) {
    Utilizador *data = getData(hashtable, chave);
    data->nascimento = nascimento;
}

void setEmail(Hashtable *hashtable, unsigned int chave, char *email) {
    Utilizador *data = getData(hashtable, chave);
    char *emailAntigo = data->email;
    data->email = strdup(email);
    free(emailAntigo);
}


void setTelemovel(Hashtable *hashtable, unsigned int chave, Telemovel telemovel) {
    Utilizador *data = getData(hashtable, chave);
    data->telemovel = telemovel;
}

void setCriacaoConta(Hashtable *hashtable, unsigned int chave, Data criacaoConta) {
    Utilizador *data = getData(hashtable, chave);
    data->criacao_conta = criacaoConta;
}
