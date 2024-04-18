#include "lista.h"

pLista cria(){
    pLista lista;
    Reserva p1 = {" "," ",{0,0,0},{{0,0},{0,0}},0,0,0};
    lista=(pLista) malloc(sizeof(noLista));
    if(lista!=NULL){
        lista->itemLista=p1;
        lista->prox=NULL;
    }
    return lista;
}

int vazia(pLista lista){
    return lista->prox==NULL;
}

void destroi(pLista lista){
    pLista temp;
    while(!vazia(lista)){
        temp=lista;
        lista=lista->prox;
        free(temp);
    }
    free(lista);
}

void procura_primeiro(pLista lista, llu chave, pLista *ant, pLista *actual){
    *ant=lista; *actual=lista->prox;
    while((*actual)!=NULL && (*actual)->itemLista.referencia_inicial<chave){
        *ant=*actual;
        *actual=(*actual)->prox;
    }
    if((*actual)!=NULL && (*actual)->itemLista.referencia_inicial!=chave) *actual=NULL;
}

void procura_ultimo(pLista lista, llu chave, pLista *ant, pLista *actual){
    *ant = lista; *actual = lista->prox;
    while ((*actual) != NULL && (*actual)->itemLista.referencia_inicial <= chave){
        *ant = *actual;
        *actual = (*actual)->prox;
    }
}

void elimina(pLista lista, llu chave){
    pLista ant,actual;
    procura_primeiro(lista,chave,&ant,&actual);
    if(actual!=NULL && actual->itemLista.referencia_inicial==chave){
        ant->prox=actual->prox;
        free(actual);
    }else{
        printf("Elemento não encontrado.\n");
    }
}

void calcula_ref(Reserva *p1){
    p1->referencia_inicial = 366 * 24 * 60 * p1->data.ano + 31 * 24 * 60 * p1->data.mes + 24 * 60 * p1->data.dia + 60 * p1->hora.inicio.hora + p1->hora.inicio.minuto;
    if(p1->serviço==1){
        p1->referencia_final=p1->referencia_inicial+30;
    }else{
        p1->referencia_final=p1->referencia_inicial+60;
    }
}

void calcula_serviço(Reserva *p1){
    p1->hora.fim.hora = p1->hora.inicio.hora;
    p1->hora.fim.minuto = p1->hora.inicio.minuto;
    if(p1->serviço==2){
        p1->hora.fim.hora++;
    }else{
        p1->hora.fim.minuto += 30;
        if(p1->hora.fim.minuto>=60){
            p1->hora.fim.hora++;
            p1->hora.fim.minuto -= 60;
        }
    }
}

void insere (pLista lista, Reserva p1){
    pLista no, ant, inutil;
    no = (pLista) malloc (sizeof (noLista));
    if (no != NULL){
        no->itemLista = p1;
        procura_ultimo(lista, p1.referencia_inicial, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

pLista pesquisa(pLista lista, llu chave){
    pLista ant,actual;
    procura_primeiro(lista,chave,&ant,&actual);
    return actual;
}

void imprime(pLista lista,int reserva) {
    pLista aux = lista->prox;
    system("clear");
    while (aux != NULL) {
        if(reserva){
            printf("- Reserva -\n");
        }else{
            printf("- Pre-Reserva -\n");
        }
        printf("> Serviço: ");
        if(aux->itemLista.serviço==1){
            printf("Lavagem <\n");
        }else{
            printf("Manutenção <\n");
        }
        printf("Nome: %s\nContacto: %s\nData: %02d/%02d/%d\nHorario: %02d:%02d as %02d:%02d\n\n", 
            aux->itemLista.nome,aux->itemLista.numero, aux->itemLista.data.dia, aux->itemLista.data.mes, aux->itemLista.data.ano,
            aux->itemLista.hora.inicio.hora, aux->itemLista.hora.inicio.minuto, aux->itemLista.hora.fim.hora, aux->itemLista.hora.fim.minuto);
        aux = aux->prox;
    }
    printf("\n");
}

void inverteLista(pLista lista) {
    pLista atual = lista->prox;
    pLista anterior = NULL;
    pLista proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    lista->prox = anterior;
}