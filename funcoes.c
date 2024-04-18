#include "funcoes.h"

void limpar(){
    int c;
    printf("(prima Enter) ");
    while ((c = getchar()) != '\n' && c != EOF);
}

void getNome(char **buffer) {
    int flag,i;
    do {
        flag = 0;
        i=0;
        printf("Introduza o seu nome: ");
        fgets(*buffer, 50, stdin);
        (*buffer)[strcspn(*buffer, "\n")] = '\0'; // Remove a quebra de linha do final
        while ((*buffer)[i] != '\0') {
            if (!isalpha((*buffer)[i])) {
                flag = 1;
                break;
            }
            i++;
        }
        if (flag) {
            printf("Nome inválido. Tente novamente. ");
            free(*buffer);
            *buffer = (char*)malloc(50 * sizeof(char));
        }
        limpar();
    } while (flag);
}

void getNumero(char *buffer){
    int flag, i;
    do {
        flag = 0;
        i = 2;
        printf("Introduza o seu numero de telemovel: ");
        fgets(buffer, 11, stdin);
        if (buffer[9] != '\n')
            flag = 1;
        buffer[9] = '\0';
        if (buffer[0] != '9' || (buffer[1] != '1' && buffer[1] != '2' && buffer[1] != '3' && buffer[1] != '6')) {
            flag = 1;
        }
        while (buffer[i] != '\0' && !flag) {
            if (!isdigit(buffer[i])) {
                flag = 1;
                break;
            }
            i++;
        }
        limpar();
    } while (flag);
}

void getData(Reserva *pessoa,int reserva){
    char *buffer;
    buffer=(char*)malloc(13*sizeof(char));
    if(buffer==NULL){
        printf("Erro de alocação.\n");
        return;
    }
    int flag,i;
    do{
        flag=0;
        i=0;
        printf("Introduza a data que pretende(dd/mm/aaaa): ");
        fgets(buffer, 13, stdin);
        limpar();
        while(buffer[i]!='\n'){
            if(((i==2||i==5)&&buffer[i]!='/')||(i!=2&&i!=5&&!isdigit(buffer[i]))){
                flag=1;
                break;
            }
            i++;
        }
        if(flag){
            printf("Erro de formatação. Tente novamente. ");
        }else{
            pessoa->data.dia = (buffer[0] - '0') * 10 + (buffer[1] - '0');
            pessoa->data.mes = (buffer[3] - '0') * 10 + (buffer[4] - '0');
            pessoa->data.ano = (buffer[6] - '0') * 1000 + (buffer[7] - '0') * 100 + (buffer[8] - '0') * 10 + (buffer[9] - '0');
            getHora(pessoa);
            if(verificarData(*pessoa,reserva)){
                printf("Data inválida. Tente novamente. ");
                flag=1;
            }
        }
    }while(flag);
    free(buffer);
}

void getHora(Reserva *pessoa){
    char *buffer;
    buffer=(char*)malloc(6*sizeof(char));
    if(buffer==NULL){
        printf("Erro de alocação.\n");
        return;
    }
    int flag,i;
    do
    {
        flag=0;
        i=0;
        printf("Que horas pretende? (hh:mm)(das 8h as 18h)(caso seja um numero simples, escreva um 0 antes, por exemplo: em vez de 9, escreva 09)\n> ");
        fgets(buffer,6,stdin);
        while(buffer[i]!='\n'&&i<5){
            if((i==2&&buffer[i]!=':')||(i!=2&&!isdigit(buffer[i]))){
                flag=1;
                break;
            }
            i++;
        }
        if(flag){
            printf("Erro de formatação. Tente novamente. ");
        }else{
            pessoa->hora.inicio.hora = (buffer[0] - '0') * 10 + (buffer[1] - '0');
            pessoa->hora.inicio.minuto = (buffer[3] - '0') * 10 + (buffer[4] - '0');
            calcula_serviço(pessoa);
            if (verificar_hora(pessoa->hora)){
                printf("Hora inválida. Tente novamente. ");
                flag=1;
            }
        }
        limpar();
    } while (flag);
    free(buffer);
}

int dias(int mes,int ano){
    switch (mes)
    {
    case 2:
        if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0){ // verifar se o ano é bissexto
            return 29;
        }
        else{
            return 28;
        }
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

int verificarData(Reserva pessoa,int reserva) {
    int ano=pessoa.data.ano,mes=pessoa.data.mes,dia=pessoa.data.dia,hora=pessoa.hora.inicio.hora,minutos=pessoa.hora.inicio.hora;
    if (ano < 0 || mes < 1 || mes > 12 || dia < 1) {
        return 1;
    }

    int diasNoMes=dias(mes,ano);

    if (dia > diasNoMes) {
        return 1;
    }

    if(reserva){
        time_t t = time(NULL);  // Obtém a data atual
        struct tm *hoje = localtime(&t);  // Converte para uma estrutura tm
        mktime(hoje);
        hoje->tm_year+=1900;
        hoje->tm_mon+=1;
        if(ano<hoje->tm_year){
            return 1;
        }
        if(ano==hoje->tm_year&&mes<hoje->tm_mon){
            return 1;
        }
        if(ano==hoje->tm_year&&mes==hoje->tm_mon&&dia<hoje->tm_mday){
            return 1;
        }
        if(ano==hoje->tm_year&&mes==hoje->tm_mon&&dia==hoje->tm_mday&&(hora<hoje->tm_hour||(hora==hoje->tm_hour&&minutos<hoje->tm_min))) return 1;
    }
    return 0;
}

int conflito(Reserva atual, Reserva nova){
    if(atual.referencia_inicial==nova.referencia_inicial||atual.referencia_final==nova.referencia_final) return 1;
    if(atual.referencia_inicial<nova.referencia_inicial&&atual.referencia_final>nova.referencia_inicial) return 1;
    if(atual.referencia_inicial>nova.referencia_inicial&&atual.referencia_inicial<nova.referencia_final) return 1;
    return 0;
}

int verifica_reserva(pLista lista, Reserva nova){
    pLista aux=lista->prox;
    Data data_atual;
    while(aux!=NULL){
        data_atual=aux->itemLista.data;
        if(data_atual.ano==nova.data.ano&&data_atual.mes==nova.data.mes&&data_atual.dia==nova.data.dia){
            if(conflito(aux->itemLista,nova)){
                return 1;
            }
        }
        aux=aux->prox;
    }
    return 0;
}

int verificar_hora(Horario hora){
    if ((hora.inicio.hora < 8 || hora.inicio.hora > 17) || (hora.inicio.minuto < 0 || hora.inicio.minuto >= 60)) return 1;
    if(hora.fim.hora>18||(hora.fim.hora==18&&hora.fim.minuto>0)){
        printf("Serviço ultrapassa a hora de fecho\n");
        return 1;
    }
    return 0;
}

int verfica_numero(pLista listaReserva, pLista listaPre,char *nome,char *numero){
    int flag=0;
    pLista aux=listaReserva->prox;
    while(aux!=NULL){
        if(strcmp(aux->itemLista.nome,nome)!=0&&strcmp(aux->itemLista.numero,numero)==0){
            flag=1;
            break;
        }
        aux=aux->prox;
    }
    if(flag==0){
        aux=listaPre->prox;
        while(aux!=NULL){
            if(strcmp(aux->itemLista.nome,nome)!=0&&strcmp(aux->itemLista.numero,numero)==0){
                flag=1;
                break;
            }
            aux=aux->prox;
        }
    }
    return flag;
}

void fazer_reserva(pLista listaReserva, pLista listaPre, int servico)
{
    int escolha=1,cont=0,flag;
    char esc;
    Reserva pessoa;
    pessoa.nome=(char*)malloc(50*sizeof(char));
    pessoa.numero=(char*)malloc(11*sizeof(char));
    if(pessoa.nome==NULL||pessoa.numero==NULL) return;
    getNome(&pessoa.nome);
    do{
        if(cont>0){
            printf("Este número já está associado a outra pessoa!\n");
        }
        getNumero(pessoa.numero);
        cont++;
    } while (verfica_numero(listaReserva, listaPre, pessoa.nome, pessoa.numero));
    pessoa.serviço=servico;
    cont=0;
    do{
        flag=0;
        if(cont>0){
            int c,bandeira;
            do
            {
                system("clear");
                printf("\n> A hora que escolheu não se encontra disponivel <\n");
                printf("- Pretende escolher outro dia (prima 1)\n");
                printf("- Pretende fazer uma pre-reserva (prima 2)\n");
                printf("- Retornar ao menu (prima 0)\n");
                bandeira = 0;
                printf("\nEscolha uma opção válida: ");
                scanf("%c", &esc);
                while ((c = getchar()) != '\n' && c != EOF) bandeira = 1;
                escolha=esc-'0';
                printf("(prima Enter)");
            } while (escolha < 0 || escolha > 2 || bandeira);
        }
        if(escolha==1){
            getData(&pessoa,1);
            calcula_ref(&pessoa);
            system("clear");
            if (verifica_reserva(listaReserva, pessoa)){
                flag=1;
            }else{
                insere(listaReserva,pessoa);
            }
        }else if(escolha==2){
            int ver=0;
            if(!(vazia(listaPre))){
                pLista aux = listaPre->prox;
                while (aux !=NULL){
                    if(verifica_reserva(listaPre,pessoa)&&strcmp(aux->itemLista.nome,pessoa.nome)==0&&strcmp(aux->itemLista.numero,pessoa.numero)==0){
                        ver=1;
                        break;
                    }
                    aux=aux->prox;
                }
            }
            if(ver){
                printf("O utlizador já possui uma pre-reserva marcada para este dia e hora!\n");
            }else{
                insere(listaPre, pessoa);
            }
        }
        cont++;
    }while(flag);
    getchar();
}

void cancelar(pLista listaReserva, pLista listaPre, int escolha,char *numero){
    pLista aux;
    int flag=1;
    Reserva p1;
    getData(&p1,0);
    calcula_serviço(&p1);
    calcula_ref(&p1);
    if(escolha<3){
        aux=listaReserva->prox;
        while(aux!=NULL){
            if(aux->itemLista.serviço==escolha&&strcmp(aux->itemLista.numero,numero)==0&&aux->itemLista.referencia_inicial==p1.referencia_inicial){
                flag=0;
                break;
            }
            aux=aux->prox;
        }
        if(flag){
            printf("Não foi encontrada nenhuma reserva correspondente.\n");
        }else{
            elimina(listaReserva, aux->itemLista.referencia_inicial);
            printf("Cancelamento de reserva bem sucedido.\n");
            if(!vazia(listaPre)){
                pLista pre=listaPre->prox;
                while(pre!=NULL){
                    if(verifica_reserva(listaReserva,pre->itemLista)==0){
                        insere(listaReserva, pre->itemLista);
                        elimina(listaPre,pre->itemLista.referencia_inicial);
                    }
                    pre=pre->prox;
                }
            }
        }
    }else{
        escolha-=2;
        aux=listaPre->prox;
        while(aux!=NULL){
            if(aux->itemLista.serviço==escolha&&strcmp(aux->itemLista.numero,numero)==0&&aux->itemLista.referencia_inicial==p1.referencia_inicial){
                flag=0;
                break;
            }
            aux=aux->prox;
        }
        if(flag){
            printf("Não foi encontrada nenhuma reserva correspondente.\n");
        }else{
            elimina(listaPre, aux->itemLista.referencia_inicial);
            printf("Cancelamento de pre-reserva bem sucedido.\n");
        }
    }
    limpar();
}

int download(pLista ListaReserva, pLista listaPre, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fclose(file);
        FILE *f=fopen(filename,"w");
        if(f==NULL){
            fclose(f);
            printf("Erro ao abrir o arquivo %s\n", filename);
            return 0;
        }else{
            fclose(f);
            printf("Base de dados criada com sucesso.\n");
            return 1;
        }
    }
    int flag=1;
    char buffer[100];
    while (fgets(buffer, 100, file)) {
        Reserva novaReserva;
        novaReserva.nome = (char *)malloc(50 * sizeof(char));
        novaReserva.numero = (char *)malloc(11 * sizeof(char));
        if (novaReserva.nome == NULL || novaReserva.numero == NULL){
            fclose(file);
            return 0;
        }
        char tipo[20];
        char *token;
        token = strtok(buffer, ";");
        strcpy(tipo, token);

        token = strtok(NULL, ";");
        strcpy(novaReserva.nome, token);

        token = strtok(NULL, ";");
        strcpy(novaReserva.numero, token);

        token = strtok(NULL, ";");
        sscanf(token, "%d/%d/%d", &novaReserva.data.dia, &novaReserva.data.mes, &novaReserva.data.ano);

        token = strtok(NULL, ";");
        if (token != NULL) {
            sscanf(token, "%d:%d-%d:%d", &novaReserva.hora.inicio.hora, &novaReserva.hora.inicio.minuto,&novaReserva.hora.fim.hora, &novaReserva.hora.fim.minuto);
        } else {
            printf("Erro ao tirar a informação do ficheiro.\n");
            flag=0;
            break;
        }

        if(flag){
            token = strtok(NULL, "\n");
            novaReserva.serviço = atoi(token);

            calcula_ref(&novaReserva);

            if (strcmp(tipo, "Reserva") == 0) {
                insere(ListaReserva, novaReserva);
            } else if (strcmp(tipo, "Pre-Reserva") == 0) {
                insere(listaPre, novaReserva);
            }
        }
    }
    fclose(file);
    return flag;
}

void upload(pLista ListaReserva, pLista listaPre, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    pLista reservaAtual = ListaReserva->prox;
    while (reservaAtual != NULL) {
        fprintf(file, "Reserva;%s;%s;%02d/%02d/%d;%02d:%02d-%02d:%02d;%d\n",
                reservaAtual->itemLista.nome, reservaAtual->itemLista.numero,
                reservaAtual->itemLista.data.dia, reservaAtual->itemLista.data.mes, reservaAtual->itemLista.data.ano,
                reservaAtual->itemLista.hora.inicio.hora, reservaAtual->itemLista.hora.inicio.minuto,
                reservaAtual->itemLista.hora.fim.hora, reservaAtual->itemLista.hora.fim.minuto, reservaAtual->itemLista.serviço);
        reservaAtual = reservaAtual->prox;
    }

    pLista preAtual = listaPre->prox;
    while (preAtual != NULL) {
        fprintf(file, "Pre-Reserva;%s;%s;%02d/%02d/%d;%02d:%02d-%02d:%02d;%d\n",
                preAtual->itemLista.nome, preAtual->itemLista.numero,
                preAtual->itemLista.data.dia, preAtual->itemLista.data.mes, preAtual->itemLista.data.ano,
                preAtual->itemLista.hora.inicio.hora, preAtual->itemLista.hora.inicio.minuto,
                preAtual->itemLista.hora.fim.hora, preAtual->itemLista.hora.fim.minuto, preAtual->itemLista.serviço);
        preAtual = preAtual->prox;
    }

    fclose(file);
}

void imprimePorCliente(pLista lista,int reserva){
    char *numero;
    numero=(char*)malloc(11*sizeof(char));
    if(numero==NULL){
        printf("Erro de alocação.\n");
        return;
    }
    getNumero(numero);
    pLista aux=lista->prox;
    int flag=1;
    if(reserva){
        printf("\n --- Reservas ---\n");
    }else{
        printf("\n --- Pre-Reservas ---\n");
    }
    while(aux!=NULL){
        if(strcmp(numero,aux->itemLista.numero)==0){
            flag=0;
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
        }
        aux = aux->prox;
    }
    if(flag==1&&reserva==1){
        printf("Não foi encontrada nenhuma reserva correspondente.\n");
    }else if(flag==1&&reserva==0){
        printf("Não foi encontrada nenhuma pre-reserva correspondente.\n");
    }
    free(numero);
}

void listagem(pLista listaReserva, pLista listaPre, int escolha, int metodo){
    int reserva = 1;
    if(escolha==1&&metodo==1){
        printf("\n --- Reservas ---\n");
        imprime(listaReserva,reserva);
        if(vazia(listaPre)){
            printf("A lista de pre-reservas está vazia!\n");
        }else{
            reserva = 0; // reserva passa a ser falso (é uma pre-reserva)
            printf("\n --- Pre-Reservas ---\n");
            imprime(listaPre, reserva);
        }
        limpar();
    }else if(escolha==1&&metodo==2){
        inverteLista(listaReserva);
        printf("\n --- Reservas ---\n");
        imprime(listaReserva,reserva);
        inverteLista(listaReserva);
        if(vazia(listaPre)){
            printf("A lista de pre-reservas está vazia!\n");
        }else{
            reserva = 0; // reserva passa a ser falso (é uma pre-reserva)
            inverteLista(listaPre);
            printf("\n --- Pre-Reservas ---\n");
            imprime(listaPre, reserva);
            inverteLista(listaPre);
        }
        limpar();
    }else if(metodo==1){
        imprimePorCliente(listaReserva,reserva);
        if(vazia(listaPre)){
            printf("A lista de pre-reservas está vazia!\n");
        }else{
            reserva = 0; // reserva passa a ser falso (é uma pre-reserva)
            imprimePorCliente(listaPre, reserva);
        }
        limpar();
    }else{
        inverteLista(listaReserva);
        imprimePorCliente(listaReserva,reserva);
        inverteLista(listaReserva);
        if(vazia(listaPre)){
            printf("A lista de pre-reservas está vazia!\n");
        }else{
            reserva = 0; // reserva passa a ser falso (é uma pre-reserva)
            inverteLista(listaPre);
            imprimePorCliente(listaPre, reserva);
            inverteLista(listaPre);
        }
        limpar();
    }
}

void AvancarTempo(pLista listaReserva, pLista listaPre){
    if(vazia(listaReserva)){
        int c;
        printf("A lista de reservas está vazia!\nPrima alguma tecla para continuar...\n> ");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    pLista aux=listaReserva->prox;
    int cont=0;
    while(aux!=NULL){
        if(verificarData(aux->itemLista,1)){
            cont++;
            elimina(listaReserva,aux->itemLista.referencia_inicial);
        }
        aux=aux->prox;
    }
    if(cont>0){
        printf("Foram executadas %d tarefas.\n",cont);
    }else{
        printf("Não existem reservas que precisem de ser executadas, apenas reservas para o futuro à espera que chegue a sua vez.\n");
    }
    limpar();
    if(vazia(listaPre)){
        int c;
        printf("A lista de pre-reservas está vazia!\nPrima alguma tecla para continuar...\n> ");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    aux=listaPre->prox;
    while(aux!=NULL){
        if(verificarData(aux->itemLista,1)){
            elimina(listaPre,aux->itemLista.referencia_inicial);
        }
        aux=aux->prox;
    }
}