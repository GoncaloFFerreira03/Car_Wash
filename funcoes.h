#ifndef FUNCOES_H
#define FUNCOES_H

#include "lista.h"

void limpar(); // função que remove(limpa) caracteres perdidos do buffer para não gerar conflitos e permite também fazer uma especie de controlo em que para o utilizador para continuar tem de premir a tecla Enter 
void getNome(char **buffer);    // função que pede um nome ao utilizador, faz todas as verificações necessarias e depois o guarda na variavel passada por argumento (a variavel é alterada diretamente pois é passada por referencia)
void getNumero(char *buffer);   // função que pede um numero de telemovel ao utilizador, faz todas as verificações necessarias e depois o guarda na variavel passada por argumento (a variavel é alterada diretamente pois é passada por referencia)
void getData(Reserva *pessoa,int reserva);      // função que pede uma data ao utilizador, faz todas as verificações necessarias e depois a guarda na variavel passada por argumento (a variavel é alterada diretamente pois é passada por referencia)
void getDataCancelar(Reserva *pessoa);
void getHora(Reserva *pessoa);  // função que pede uma hora ao utilizador, faz todas as verificações necessarias e depois a guarda na variavel passada por argumento (a variavel é alterada diretamente pois é passada por referencia)
int dias(int mes, int ano);     // função que devolve quantos dias é que um determinado mês de um determinado ano tem (dá jeito porque fevereiro não tem o mesmo numero de dias todos os anos, e também porque há meses com 30 e outros com 31 dias)
int verificarData(Reserva pessoa,int reserva);   // função que verifica se uma data existe e não está ultrapassada, se a data não existir ou estiver ultrapassada devolve 1, se estiver tudo bem devolve 0
int conflito(Reserva atual, Reserva nova);          // função que verifica se a nova reserva entra em conflito com uma reserva já existente, se entrar devolve 1, se não devolve 0
int verifica_reserva(pLista lista,Reserva nova);    // função que vai percorrer a lista de reservas e comparando a reserva nova com cada uma das existentes através da função conflito, caso haja conflito com alguma devolve 1, caso contrário devolve 0
int verificar_hora(Horario hora);                   // função que verifica se a hora escolhida está dentro do intervalo real (sistema de 24h com 60 mminutos por hora) e dentro do horario de trabalho (das 8h as 18h)
int verfica_numero(pLista listaReserva,pLista listaPre,char *nome,char *numero);                        // função que percorre as listas à procura de alguem que tenha o mesmo numero mas um nome diferente
void fazer_reserva(pLista listaReserva, pLista listaPre, int servico);          // função que permite ao utlizador fazer uma reserva (ou pre-reserva caso não haja disponibilidade)
void cancelar(pLista listaReserva,pLista listaPre,int escolha,char *numero);    // função que permite cancelar uma reserva ou pre-reserva
int download(pLista ListaReserva,pLista listaPre,const char *filename);         // função que descarrega a informação do ficheiro para a lista, devolve 1 se for bem sucedida, caso contrário devolve 0
void upload(pLista ListaReserva, pLista listaPre, const char *filename);        // função que carrega a informação das listas para o ficheiro
void listagem(pLista listaReserva, pLista listaPre, int escolha, int metodo);   // função que permite fazer a listagem da listas
void AvancarTempo(pLista listaReserva,pLista listaPre);                         // função que executa reservas e elimina pre-reservas caso estas já estejam datadas

#endif