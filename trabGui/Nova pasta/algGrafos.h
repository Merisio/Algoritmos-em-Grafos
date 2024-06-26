#include <stdio.h>
#include <stdlib.h>

typedef struct NoAdj NoAdj;
typedef struct ListaAdj ListaAdj;
typedef struct NoGrafo NoGrafo;
typedef struct Grafo Grafo;

struct NoAdj{ //estrutura para nó de adjacencia
    int item;
    NoAdj* next;
};

struct ListaAdj{
    NoAdj* head;
};

struct NoGrafo{ //estrutura para representar os vértices do grafo e apontar para lista de adjacencia
    int vert;
    ListaAdj* lista;
    NoGrafo* next;
};

struct Grafo{
    NoGrafo* head; //estrutura do grafo
};

NoAdj* novo_noAdj(int i){
    NoAdj* novoNo = (NoAdj*)malloc(sizeof(NoAdj)); //cria novo no de adjacencia
    novoNo->item = i;
    novoNo->next = NULL;
    return novoNo;
}

ListaAdj* criar_lista(){            //cria lista de adjacencia
    ListaAdj* lista = (ListaAdj*)malloc(sizeof(ListaAdj));
    lista->head = NULL;
    return lista;
}

NoGrafo* novo_noGrafo(int vert){ //cria novo no de vértices
    NoGrafo* novoNo = (NoGrafo*)malloc(sizeof(NoGrafo));
    novoNo->vert = vert;
    novoNo->lista = criar_lista();
    novoNo->next = NULL;
    return novoNo;
}

Grafo* criar_grafo(){ //cria o grafo como outra lista de adjacencia
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->head = NULL;
    return grafo;
}

NoGrafo* encontra_vertice(Grafo* g, int vert){
    if(g != NULL){                  //se o grafo for diferente nulo aux recebe o grafo
        NoGrafo* aux = g->head;

        while(aux){                 //enquanto aux nao for nulo
            if(aux->vert == vert)   // percorre aux procurando o valor do vértice
                return aux;         // se o vertice já existe retorna aux
            aux = aux->next;        // se o vertice não existe retorna NULL
        }
        return NULL;
    }
}

void adicionar_vertice(Grafo* g, int vert){
    if(encontra_vertice(g, vert) == NULL){  //por meio da função anterior verifica se o vertice ja existe
        NoGrafo* novo = novo_noGrafo(vert); //se o vertice nao existe é criado um novo nó e inserido na ultima posição do grafo
        NoGrafo* aux = g->head;
        if(aux == NULL)
            g->head = novo;
        else{
            while(aux->next != NULL){
                aux = aux->next;
            }
            aux->next = novo;
        }
    }else{
        printf("Vértice já existe.\n");
    }
}

void remover_vertice(Grafo* g, int v){
    NoGrafo* atual = g->head;
    NoGrafo* anterior = NULL;

    while(atual != NULL && atual->vert != v){   //enquanto grafo não for nulo e se o valor for diferente do vertice
        anterior = atual;                       // percorre o grafo e remove o vertice
        atual = atual->next;
    }

    NoGrafo* aux = g->head;
    while (aux != NULL) {                       //percorre a lista de adjacencia removendo as arestas do vertice removido
        if (aux->vert != v) {
            NoAdj* adjAtual = aux->lista->head;
            NoAdj* adjAnterior = NULL;
            while (adjAtual != NULL) {
                if (adjAtual->item == v) {
                    if (adjAnterior == NULL) {
                        aux->lista->head = adjAtual->next;
                    } else {
                        adjAnterior->next = adjAtual->next;
                    }
                    free(adjAtual);
                    break;
                }
                adjAnterior = adjAtual;
                adjAtual = adjAtual->next;
            }
        }
        aux = aux->next;
    }

    if (anterior == NULL) {
        g->head = atual->next;
    } else {
        anterior->next = atual->next;
    }
}

int aresta_existe(Grafo* g, int a, int b){
    NoGrafo* vertice = encontra_vertice(g, a);
    if (vertice != NULL) {                          //verifica se o vertice informado existe
        NoAdj* adj = vertice->lista->head;          //caso ele exista adj recebe a cabeça do vertice A
        while (adj != NULL) {                       //percorre a lista de adjacencia de A procurando B
            if (adj->item == b) {                   //se encontrado retorna 1 e a aresta existe
                return 1;
            }
            adj = adj->next;
        }
    }
    return 0;
}

void adicionar_aresta(Grafo* g, int a, int b){
    NoGrafo* origem = encontra_vertice(g, a);           //procura os vértice A e B
    NoGrafo* destino = encontra_vertice(g, b);

    if(!aresta_existe(g, a, b) && destino != NULL){     //se os vértices existem
        NoAdj* novoNo = novo_noAdj(b);                  //cria um novo NoAdj com valor de B
        novoNo->next = origem->lista->head;             //o novo nó recebe o valor de A
        origem->lista->head = novoNo;
        adicionar_aresta(g, b, a);                      //chamada recursiva da função
    }
}

void remover_aresta(Grafo* g, int a, int b){
    if(aresta_existe(g, a, b)){
        NoGrafo* origem = encontra_vertice(g, a);
        NoGrafo* destino = encontra_vertice(g, b);

        if (destino != NULL){
            NoAdj* adjAtual = origem->lista->head;
            NoAdj* adjAnterior = NULL;

            while (adjAtual != NULL) {
                if (adjAtual->item == b) {
                    if (adjAnterior == NULL)
                        origem->lista->head = adjAtual->next;
                    else
                        adjAnterior->next = adjAtual->next;

                    free(adjAtual);
                    break;
                }
                adjAnterior = adjAtual;
                adjAtual = adjAtual->next;
            }

        }
        remover_aresta(g, b, a);
    }else
        printf("Aresta foi removida ou não existe.\n");
}

void imprimir(Grafo* g){
    NoGrafo* node = g->head;
    while(node != NULL){
        NoAdj* adj = node->lista->head;
        printf("%d", node->vert);
        while(adj != NULL){
            printf("-> %d", adj->item);
            adj = adj->next;
        }
        printf("-> NULL\n");
        node = node->next;
    }
}
void liberar (Grafo* g){
    NoGrafo* node = g->head;
    NoGrafo* aux;
    while(node != NULL){
        NoAdj* adj = node->lista->head;
        NoAdj* aux2;
        while(adj != NULL){
            aux2 = adj->next;
            free(adj);
            adj = aux2;
        }
        aux = node->next;
        free(node);
        node = aux;
    }
}

int grau_do_vertice(Grafo* g, int vert){
    NoGrafo* aux = encontra_vertice(g, vert);   //verifica se o vértice existe
    int grau = 0;
    if(aux != NULL){
        NoAdj* adj = aux->lista->head;
        while(adj){
            adj = adj->next;            //percorre a lista contando a quantidade de ligaçoes que o no tem e incrementa a variavel grau
            grau++;
        }
        return grau;
    }
    return 0;
}
void busca_profundidade(Grafo* g, NoGrafo* vertice, int* visitado){
    visitado[vertice->vert] = 1;                //marca o vertice como visitado
    NoAdj* adj = vertice->lista->head;
    while (adj != NULL){                        //percorre a lista de adjacencia
        if (!visitado[adj->item]){                  //se o vertice nao foi visitado, procura o vertice no grafo
            NoGrafo* adjVertice = encontra_vertice(g, adj->item);
            if (adjVertice != NULL) {                   //se o vertice foi encontrado realiza a busca recursivamente
                busca_profundidade(g, adjVertice, visitado);
            }
        }
        adj = adj->next;
    }
}

int eh_conexo(Grafo *g) {
    if (g->head == NULL) return 1; // Um grafo vazio é considerado conexo

    int numVert = 0;
    int menorVert = g->head->vert;
    NoGrafo* aux = g->head;                     // Contar o número de vértices e encontrar o vértice de menor valor
    while (aux != NULL) {
        if (aux->vert < menorVert) {
            menorVert = aux->vert;
        }
        numVert++;
        aux = aux->next;
    }

    int* visitado = (int*)calloc(numVert + menorVert, sizeof(int)); // Aloca espaço para os vértices

    busca_profundidade(g, g->head, visitado);           // Iniciar a busca a partir do primeiro vértice na lista

    aux = g->head;                  // Verificar se todos os vértices foram visitados
    while (aux != NULL){
        if (!visitado[aux->vert]) {
            free(visitado);
            return 0;                   //Se algum vértice não foi visitado retorna 0 e o grafo não é conexo
        }
        aux = aux->next;
    }
    free(visitado);
    return 1;                   // Todos os vértices foram visitados grafo é conexo
}
void converter_matriz(Grafo *g) {
    if (g->head == NULL) return;

    int numVert = 0;                    // Contar o número de vértices e encontrar o maior valor de vértice
    int maiorVert = g->head->vert;
    NoGrafo* aux = g->head;
    while (aux != NULL) {
        if (aux->vert > maiorVert){
            maiorVert = aux->vert;
        }
        numVert++;
        aux = aux->next;
    }

    int** matriz = (int**)malloc((maiorVert + 1) * sizeof(int*)); //cria a matriz e aloca o espaço necessario
    for (int i = 0; i <= maiorVert; i++) {
        matriz[i] = (int*)calloc(maiorVert + 1, sizeof(int));
    }

    NoGrafo* aux2 = g->head;                //preenche a matriz
    while (aux2 != NULL) {
        NoAdj* adj = aux2->lista->head;
        while (adj != NULL) {
            matriz[aux2->vert][adj->item] = 1;
            adj = adj->next;
        }
        aux2 = aux2->next;
    }

    imprimir_matriz(matriz, maiorVert);
}

void  imprimir_matriz(int** matriz, int n){
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i <= n; i++) {
        free(matriz[i]);
    }
    free(matriz);

}



