#include <stdio.h>
#include <stdlib.h>


typedef struct No{
    int vertice; // numero do vertice
    struct No* prox; // ponteiro para o proximo no
}No;


typedef struct Grafo{
     int tamanho; // numero de vertices no grafo
     No** listasAdj; // listas de adjacencia
}Grafo;


No *criarNo(int v){
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = v;
    novoNo->prox = NULL; //inicializa com null pois ainda n�o se tem arestas

    return novoNo;
}


Grafo *criarGrafo(){// para criar o grafo precisamos de no minimo 1 vertice
    Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->tamanho = 0; // define o nemero de vertices no grafo
    grafo->listasAdj = (No*)malloc(sizeof(No));

    return grafo;

}


//Insere um vertice ordenado
void inserirVertice(Grafo *grafo){
    grafo->tamanho++;
    grafo->listasAdj = realloc(grafo->listasAdj, (grafo->tamanho) * sizeof(No));
    grafo->listasAdj[grafo->tamanho] = NULL;
}


// Verifica se uma aresta ja existe no grafo
int arestaNaoExiste(Grafo *grafo, int origem, int destino){
    No *temp = grafo->listasAdj[origem];// percorre a lista de adjacencia do vertice de origem
                                        // busca sequencial simples
    while (temp != NULL){
        if (temp->vertice == destino)
            return 0;

        temp = temp->prox;
    }
    return 1;
}


//Insere uma aresta entre 2 vertices
void inserirAresta(Grafo *grafo, int origem, int destino){
    if (arestaNaoExiste(grafo, origem, destino)){
        No *novoNo = criarNo(destino);// adiciona uma aresta de origem para o destino
        novoNo->prox = grafo->listasAdj[origem];
        grafo->listasAdj[origem] = novoNo;

        novoNo = criarNo(origem);// adiciona uma aresta de destino para origem (grafo nao direcionado)
        novoNo->prox = grafo->listasAdj[destino];
        grafo->listasAdj[destino] = novoNo;
    }
    else
        printf("\nA aresta ja existe no grafo\n");
}


// Remove o ultimo vertice do grafo
void removerVertice(Grafo *grafo){
    if (grafo->tamanho != 0){
        int n = grafo->tamanho;

        for (int i = 1; i <= n; i++)
            removerAresta(grafo, n, i);

        grafo->tamanho--;
        grafo->listasAdj = realloc(grafo->listasAdj, (grafo->tamanho + 1) * sizeof(No*));
    }
    else{
        printf("\nO grafo nao possui nenhum vertice.\n");
    }
}


// Remove uma aresta qualquer
void removerAresta(Grafo *grafo, int origem, int destino){
    if (!arestaNaoExiste(grafo, origem, destino)){
        No *anterior = NULL;
        No *aux = grafo->listasAdj[origem];

        while (aux){
            if (aux->vertice == destino){
                if (anterior)
                    anterior->prox = aux->prox;
                else
                    grafo->listasAdj[origem] = aux->prox;

                free(aux);
                break;
            }
            anterior = aux;
            aux = aux->prox;
        }

        //fazendo do outro lado, pois o grafo é nao direcionado
        anterior = NULL; // define o anterior como nulo
        aux = grafo->listasAdj[destino]; // define o temporario como destino da lista

        while (aux != NULL){
            if (aux->vertice == origem){ // o vertice temporario aponta para a origem
                if (anterior != NULL)
                    anterior->prox = aux->prox; // iguala o proximo do anterior com o do temporario
                else
                    grafo->listasAdj[destino] = aux->prox; // / a origem aponta para o proximo

                free(aux); // libera a memoria alocada para a aresta
                break;
            }
            anterior = aux;
            aux = aux->prox;
        }
    }
}


void imprimir(Grafo *grafo){
    if (grafo != NULL){
        int v;
        No *temp;

        for (v = 1; v <= grafo->tamanho; v++){ // um loop q pega todos os vertices do grafo
            temp = grafo->listasAdj[v];// no temporario percorre a lista de adjacencia do vertice v
            printf("%d -> ", v);

            while (temp != NULL){
                printf("%d -> ", temp->vertice);
                temp = temp->prox;
            }
            printf("\n");
        }
    }
}


void liberar(Grafo *grafo){
    for (int i = 0; i < grafo->tamanho; i++){
        No *temp = grafo->listasAdj[i];
        No *proximo = temp->prox;

        while (proximo != NULL){
            proximo = temp->prox;
            free(temp);// liberando cada espaco do vetor de listas adjacentes
            proximo = proximo->prox;
        }
    }

    free(grafo->listasAdj);// liberando a lista em si
    free(grafo);// liberando o grafo por fim
}
