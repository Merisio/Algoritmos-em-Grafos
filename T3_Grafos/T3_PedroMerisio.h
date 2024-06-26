#include <stdio.h>
#include <stdlib.h>


//funcoes estruturais
typedef struct NoAdj{
    int item;
    struct NoAdj* next;
}NoAdj;

typedef struct ListaAdj{
    NoAdj* head;
}ListaAdj;

typedef struct NoGrafo{
    int vert;
    ListaAdj* lista;
    struct NoGrafo* next;
}NoGrafo;

typedef struct Grafo{
    NoGrafo* head;
}Grafo;

NoAdj* novo_noAdj(int i){
    NoAdj* novoNo = (NoAdj*)malloc(sizeof(NoAdj));
    novoNo->item = i;
    novoNo->next = NULL;

    return novoNo;
}

ListaAdj* criar_lista(){
    ListaAdj* lista = (ListaAdj*)malloc(sizeof(ListaAdj));
    lista->head = NULL;

    return lista;
}

NoGrafo* novo_noGrafo(int vert){
    NoGrafo* novoNo = (NoGrafo*)malloc(sizeof(NoGrafo));
    novoNo->vert = vert;
    novoNo->lista = criar_lista();
    novoNo->next = NULL;

    return novoNo;
}

Grafo* criar_grafo(){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->head = NULL;

    return grafo;
}

//funcao que retorna o endereco de um vertice a partir de seu valor inteiro
NoGrafo* encontra_vertice(Grafo* g, int vert){
    if(g != NULL){
        NoGrafo* aux = g->head;

        while(aux != NULL){
            if(aux->vert == vert)
                return aux;
            aux = aux->next;
        }
        return NULL;
    }
}

//funcao que adiciona um vertice no grafo
void adicionar_vertice(Grafo* g, int v){
    if(encontra_vertice(g, v) == NULL){
        NoGrafo* novo = novo_noGrafo(v);
        NoGrafo* aux;

        aux = g->head;

        if (aux == NULL)
            g->head = novo;//adicionando na primeira posicao caso o grafo seja vazio

        else{
            while (aux->next != NULL)
                aux = aux->next;

            aux->next = novo;
        }
    }
    else
        printf("O vertice ja existe.\n");
}

//funcao que remove um vertice
void remover_vertice(Grafo* g, int v){
    NoGrafo* atual = g->head;
    NoGrafo* anterior = NULL;

    while(atual != NULL && atual->vert != v){
        anterior = atual;
        atual = atual->next;
    }

    NoGrafo* aux = g->head;

    while (aux != NULL){
        if (aux->vert != v){
            NoAdj* adjAtual = aux->lista->head;
            NoAdj* adjAnterior = NULL;

            while (adjAtual != NULL){
                if (adjAtual->item == v){
                    if (adjAnterior == NULL)
                        aux->lista->head = adjAtual->next;
                    else
                        adjAnterior->next = adjAtual->next;

                    free(adjAtual);
                    break;
                }
                adjAnterior = adjAtual;
                adjAtual = adjAtual->next;
            }
        }
        aux = aux->next;
    }

    if (anterior == NULL)
        g->head = atual->next;
    else
        anterior->next = atual->next;
}

//funcao que verifica se existe uma certa aresta
int aresta_existe(Grafo* g, int a, int b){
    NoGrafo* vertice = encontra_vertice(g, a);

    if (vertice != NULL){
        NoAdj* adj = vertice->lista->head;

        while (adj != NULL){
            if (adj->item == b)
                return 1;

            adj = adj->next;
        }
    }
    return 0;
}

//funcao que adiciona uma nova aresta no grafo
void adicionar_aresta(Grafo* g, int a, int b){
    NoGrafo* origem = encontra_vertice(g, a);
    NoGrafo* destino = encontra_vertice(g, b);

    if(!aresta_existe(g, a, b) && destino != NULL){
        NoAdj* novoNo = novo_noAdj(b);
        novoNo->next = origem->lista->head;
        origem->lista->head = novoNo;

        adicionar_aresta(g, b, a);//adicionar nas duas listas
    }
}

//funcao que remove uma aresta no grafo
void remover_aresta(Grafo* g, int a, int b){
    if(aresta_existe(g, a, b)){
        NoGrafo* origem = encontra_vertice(g, a);
        NoGrafo* destino = encontra_vertice(g, b);

        if (destino != NULL){
            NoAdj* adjAtual = origem->lista->head;
            NoAdj* adjAnterior = NULL;

            while (adjAtual != NULL){
                if (adjAtual->item == b){
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
        remover_aresta(g, b, a); //fazer a remocao na outra lista encadeada
    }
    else
        printf("Aresta foi removida ou nao existe.\n");
}

//imprime o grafo na tela
void visualizar(Grafo* g){
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

// funcao que libera a memoria ocupada pelo grafo
void liberar(Grafo* g){
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

//funcao que mostra o grau de um vertice do grafo
int grauVertice(Grafo* g, int vert){
    NoGrafo* aux = encontra_vertice(g, vert);
    int grau = 0;

    if(aux != NULL){
        NoAdj* adj = aux->lista->head;

        while(adj != NULL){
            adj = adj->next;
            grau++;
        }
        return grau;
    }
    return 0;
}

void imprimir_matriz(int **mat, int n){
    int i, j;
    
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++)
            printf("%d ", mat[i][j]);

        printf("\n");
    }
}

void busca_profundidade(Grafo* g, NoGrafo* vertice, int* visitado){
    visitado[vertice->vert] = 1;                //marca o vertice como visitado
    NoAdj* adj = vertice->lista->head;

    while (adj != NULL){                        //percorre a lista de adjacencia
        if (!visitado[adj->item]){                  //se o vertice nao foi visitado, procura o vertice no grafo
            NoGrafo* adjVertice = encontra_vertice(g, adj->item);

            if (adjVertice != NULL){                  //se o vertice foi encontrado realiza a busca recursivamente
                busca_profundidade(g, adjVertice, visitado);
            }
            adj = adj->next;
        }
    }
}

int eh_conexo(Grafo *g){
    if (g->head == NULL) 
        return 1; // Um grafo vazio eh considerado conexo

    int numVert = 0;
    int menorVert = g->head->vert;
    NoGrafo* aux = g->head;   
    
    // Contar o numero de vertices e encontrar o vertice de menor valor
    while (aux != NULL){
        if (aux->vert < menorVert)
            menorVert = aux->vert;
        
        numVert++;
        aux = aux->next;
    }

    int* visitado = (int*)calloc(numVert + menorVert, sizeof(int)); // Aloca espaco para os vertices

    busca_profundidade(g, g->head, visitado);           // Iniciar a busca a partir do primeiro vertice na lista

    aux = g->head;    
                  
    while (aux != NULL){
        if (!visitado[aux->vert]){
            free(visitado);
            return 0;                   //Se algum vertice nao foi visitado retorna 0 e o grafo nao e conexo
        }
        aux = aux->next;
    }
    free(visitado);

    return 1;                   // Todos os vertices foram visitados grafo eh conexo
}

int matrizAdjacencia(Grafo *g){
    if (g->head != NULL){
        int i, j;
        // contar o numero de vertices e encontrar o maior valor de vertice
        int maiorVertice = g->head->vert;
        NoGrafo* temp = g->head;

        while (temp != NULL){
            if (temp->vert > maiorVertice)
                maiorVertice = temp->vert;

            temp = temp->next;
        }

        // criar a matriz de adjacencia
        int** matriz = (int**)malloc((maiorVertice + 1) * sizeof(int*));

        for (i = 0; i <= maiorVertice; i++)
            matriz[i] = (int*)calloc(maiorVertice + 1, sizeof(int));

        // preencher a matriz de adjacencia
        NoGrafo* node = g->head;

        while (node != NULL){
            NoAdj* adj = node->lista->head;

            while (adj != NULL){
                matriz[node->vert][adj->item] = 1;
                adj = adj->next;
            }
            node = node->next;
        }

        imprimir_matriz(matriz, maiorVertice);
    }
}