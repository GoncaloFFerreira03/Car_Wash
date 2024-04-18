#include "menu.h"

void corpo(pLista listaReserva, pLista listaPre,char *filename)
{
    int n,flag=1;
    while (flag)
    {
        n = menu();
        switch (n)
        {
        case ('0'):
            flag=0;
            break;
        case ('1'):
            Reservar(listaReserva,listaPre);
            break;
        case ('2'):
            Cancelamento(listaReserva,listaPre);
            break;
        case ('3'):
            ListarReserva(listaReserva,listaPre);
            break;
        case ('4'):
            AvancarTempo(listaReserva,listaPre);
            break;
        }
        upload(listaReserva,listaPre,filename);
    }
}

int menu()
{
    int c,flag;
    char escolha;
    do
    {
        system("clear");
        printf("-----------------Menu-----------------\n");
        printf("------------Reserva(Prima 1)----------\n");
        printf("---------Cancelamento(Prima 2)--------\n");
        printf("-Listar reservas existentes (Prima 3)-\n");
        printf("-------Avançar no tempo(Prima 4)------\n");
        printf("-------------Sair(Prima 0)------------\n");
        flag=0;
        printf("\nEscolha uma opção válida: ");
        scanf("%c", &escolha);
        while ((c = getchar()) != '\n' && c != EOF) flag=1;
    } while (escolha < '0' || escolha > '4' ||flag);
    return escolha;
}

void Reservar(pLista listaReserva, pLista listaPre)
{
    int c, flag;
    char escolha;
    do
    {
        system("clear");
        printf("----Reservar Lavagem(Prima 1)-----\n");
        printf("----Reservar Manutenção(Prima 2)--\n");
        printf("----Voltar ao Menu(Prima 0)-------\n");
        flag = 0;
        printf("\nEscolha uma opção válida: ");
        scanf("%c", &escolha);
        while ((c = getchar()) != '\n' && c != EOF)flag = 1;
    } while (escolha < '0' || escolha > '2' || flag);
    if(escolha=='0'){
        return;
    }
    fazer_reserva(listaReserva,listaPre,escolha-'0');
}

void ListarReserva(pLista listaReserva, pLista listaPre)
{
    int c, flag;
    char escolha;
    system("clear");
    if(vazia(listaReserva)){
        printf("A lista de reservas está vazia!\nPrima alguma tecla para continuar...\n> ");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    do
    {
        system("clear");
        printf("-----Listar todas as reservas e as pré-reservas(Prima 1)------------------\n");
        printf("-----Listar apenas as reservas e as pré-reservas de um cliente(Prima 2)---\n");
        printf("-----Voltar ao Menu(Prima 0)----------------------------------------------\n");
        flag = 0;
        printf("\nEscolha uma opção válida: ");
        scanf("%c", &escolha);
        while ((c = getchar()) != '\n' && c != EOF)flag = 1;
    } while (escolha < '0' || escolha > '2' || flag);
    if(escolha=='0'){
        return;
    }
    char metodo;
    do
    {
        system("clear");
        printf("-----------------------Metodo de ordenação-----------------------\n");
        printf("-----------Mais próxima para a mais distante(Prima 1)------------\n");
        printf("-----------Mais distante para a mais próxima(Prima 2)------------\n");
        printf("---------------------Voltar ao menu(Prima 0)---------------------\n");
        flag = 0;
        printf("\nEscolha uma opção válida: ");
        scanf("%c", &metodo);
        while ((c = getchar()) != '\n' && c != EOF) flag = 1;
    } while (metodo < '0' || metodo > '2' || flag);
    if(metodo=='0'){
        return;
    }
    escolha-='0';
    metodo-='0';
    listagem(listaReserva,listaPre,escolha,metodo);
}

void Cancelamento(pLista listaReserva, pLista listaPre)
{
    int c;
    system("clear");
    if (vazia(listaReserva))
    {
        printf("A lista de reservas está vazia!\nPrima alguma tecla para continuar...\n> ");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    int flag;
    char escolha;
    do
    {
        system("clear");
        printf("-----Cancelar Reserva de Lavagem(Prima 1)------------\n");
        printf("-----Cancelar Reserva de Manutenção(Prima 2)---------\n");
        printf("-----Cancelar Pré-Reserva de Lavagem(Prima 3)--------\n");
        printf("-----Cancelar Pré-Reserva de Manutenção(Prima 4)-----\n");
        printf("-----Voltar ao Menu(Prima 0)-------------------------\n");
        flag = 0;
        printf("\nEscolha uma opção: ");
        scanf("%c", &escolha);
        while ((c = getchar()) != '\n' && c != EOF)flag = 1;
    } while (escolha < '0' || escolha > '4' || flag);
    escolha-='0';
    if(escolha==0){
        return;
    }
    if ((escolha == 3 || escolha == 4)&&vazia(listaPre)){
        printf("A lista de pre-reservas está vazia!\nPrima alguma tecla para continuar...\n> ");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    char *numero;
    numero=(char*)malloc(11*sizeof(char));
    if(numero==NULL){
        printf("Erro de alocação.\n");
        return;
    }
    getNumero(numero);
    cancelar(listaReserva,listaPre,escolha,numero);
    free(numero);
}