#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>     // biblioteca que permite gerenciar e manipular memoria
#include <stdio.h>      // biblioteca que permite gerencia a entrada e saída de inforamção
#include <string.h>     // biblioteca que facilita a manipulação de strings
#include <ctype.h>      // biblioteca que facilita a manipulação de caracteres
#include <time.h>       // biblioteca que permite a obtenção e manipulação e obtenção de informações relacionadas ao tempo e data

typedef unsigned long long llu;

typedef struct{
    int minuto,hora;    // definição da estrutura que vai guardar uma hora escolhida (hh:mm)
}tempo;

typedef struct{
    tempo inicio, fim; // definição da estrutura que vai guardar a hora inicial e a hora final
}Horario;

typedef struct{
    int dia,mes,ano;   // definição da estrutura que vai guardar a data (dd/mm/aaaa)
}Data;

typedef struct{ // defenição da estrutura que vai guardar a informação geral da reserva
    char *nome,*numero; // variaveis que vão guardar o nome e o numero de telemovel (contato)
    Data data;          // variavel que guarda a data
    Horario hora;       // variavel que guarda a hora inicial e a hora final
    llu referencia_inicial; // variavel que guarda a referencia inicial (instante em que a reserva começa (em minutos))
    llu referencia_final;   // variavel que guarda a referencia final (instante em que a reserva acaba (em minutos))
    int serviço;        // tipo de serviço (lavagem(1) ou manutenção(2))
}Reserva;

typedef struct noLista{ // definição do nó da lista, contem informação sobre a reserva e um ponteiro para o proximo nó da lista
    Reserva itemLista;
    struct noLista *prox;
} noLista;

typedef noLista *pLista; // definição da lista como um ponteiro que aponta para o primeiro elemento (cabeçalho da lista)

pLista cria ();                 // função que vai inicializar a lista passada no argumento
int vazia (pLista lista);       // função que verfica se a lista está vazia, verdadeiro(1) se estiver ou falso(0) se não estiver
void destroi (pLista lista);  // função que liberta a memoria ocupada pela lista passada no argumento
void procura_ultimo(pLista lista, llu chave, pLista *ant, pLista *actual);      // função que procura o "sitio" onde vai ser inserido um novo elemento, o nome deriva da implementação das filas, onde o elemento inserido vai sempre para o fim
// neste caso, se existir algum elemento com a mesma chave (no caso de pre-reservas para a mesma hora) vai procurar o ultimo desses elementos 
void procura_primeiro(pLista lista, llu chave, pLista *ant, pLista *actual);    // função que procura o "sitio" onde vai ser retirado um elemento, o nome deriva da implementação das filas, onde o elemento retirado é sempre do inicio
// neste caso, se existir algum elemento com a mesma chave (no caso de pre-reservas para a mesma hora) vai procurar o primeiro desses elementos
void elimina (pLista lista, llu chave);     // função que elimina o elementa com chave correspondente da lista passado como argumento
void calcula_ref(Reserva *p1);              // função que calcula a referencia inicial e final
void calcula_serviço(Reserva *p1);          // função que calcula a hora final com base no serviço escolhido
void insere (pLista lista, Reserva p1);     // função que insere a reserva p1 na lista passada no argumento
pLista pesquisa (pLista lista, llu chave);  // função que vai pesquisar o nó com a chave correspondente, caso não seja encontrado nenhum, é retornado NULL
void imprime (pLista lista,int reserva);    // função que imprime todos os elementos da lista passada como argumento
void inverteLista(pLista lista);            // função que inverte a lista passada no argumento

#endif