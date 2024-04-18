#ifndef MENU_H
#define MENU_H

#include "funcoes.h"

void corpo(pLista listaReserva,pLista listaPre,char *filename); // função que dirige chama outras funcões com base na escolha retornada do menu
int menu(); // função que exibe o menu e retorna a escolha do utilizador
void Reservar(pLista listaReserva, pLista listaPre);        // função que permite ao utlizador escolher o serviço que pretende reservar (ou pre-reservar caso não haja disponibilidade)
void ListarReserva(pLista listaReserva, pLista listaPre);   // função que permite escolher como listar as reservas e pre-reservas
void Cancelamento(pLista listaReserva, pLista listaPre);    // função que permite escolher o que cancelar

#endif