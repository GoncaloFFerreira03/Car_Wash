#include "menu.h"

int main(){
    pLista listaReserva,listaPre;               // definição inicial da lista de reservas e da lista de pre-reservas
    listaReserva=cria();                        // inicialização da lista de reservas
    listaPre=cria();                            // inicialização da lista de pre-reservas
    if(listaReserva==NULL||listaPre==NULL){     // se alguma das inicializações falhar, o programa não prossegue (termina)
        printf("Erro de alocação.\n");
        return -1;
    }
    char *filename="base.txt";  // "filname" é a variavel que vai guardar o nome do ficheiro que contem a informação das nossas listas
    listaReserva->prox=NULL;    // lista de reservas está vazia
    listaPre->prox=NULL;        // lista de pre-reservas está vazia
    if(download(listaReserva,listaPre,filename)){   // se o "download" ou descarregamento da informação do ficheiro ocorrer sem problemas
        corpo(listaReserva, listaPre,filename);     // é chama a função corpo que dá seguimento ao resto do programa
        upload(listaReserva, listaPre, filename);   // quando a função corpo é encerrada, toda a informação é carregada para o ficheiro escolhido
    }
    destroi(listaReserva);  // liberta a memoria ocupada pela lista de reservas
    destroi(listaPre);      // liberta a memoria ocupada pela lista de pre-reservas
    return 0;       // fim do programa
}