#include <stdio.h>
#include <stdlib.h>

// estrutura para um no da lista de adjacência
struct No {
    int vertice; // número do vértice adjacente
    struct No* prox; // ponteiro para o próximo nó da lista
};

// Estrutura para representar o grafo
struct Grafo {
    int numVertices; // Número de vértices no grafo
    struct No** listasAdj; // array de ponteiros para listas de adjacência
};

// Função para criar um nó na lista de adjacência
struct No* criarNo(int v) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No)); // aloca memória para o novo nó
    novoNo->vertice = v; // define o número do vértice adjacente
    novoNo->prox = NULL; // inicializa o ponteiro para o próximo nó como NULL
    return novoNo; // retorna o novo nó feito
}

// Função para criar um grafo com numVertices vértices
struct Grafo* criarGrafo(int numVertices) {
struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo)); // alooca memória para a estrutura de Grafo
    grafo->numVertices = numVertices; // define o número de vértices no grafo
    grafo->listasAdj = (struct No*)malloc(numVertices * sizeof(struct No));  // aloca memória para o array de listas de adjacência

    for (int i = 0; i < numVertices; i++) { // Inicializa todas as listas de adjacência como NULL
        grafo->listasAdj[i] = NULL;
    }

    return grafo; // retorna o grafo criado
}

// função para adicionar uma aresta ao grafo
void adicionarAresta(struct Grafo* grafo, int origem, int destino) {
    // adiciona uma aresta de origem para o destino
    struct No* novoNo = criarNo(destino);
    novoNo->prox = grafo->listasAdj[origem];
    grafo->listasAdj[origem] = novoNo;

    // adiciona uma aresta de destino para origem (grafo não direcionado)
    novoNo = criarNo(origem);
    novoNo->prox = grafo->listasAdj[destino];
    grafo->listasAdj[destino] = novoNo;
}
// função para adicionar uma aresta ao grafo
void inserirAresta(struct Grafo* grafo, int origem, int destino) {
    adicionarAresta(grafo, origem, destino);
}

// função para remover uma aresta do grafo
void removerAresta(struct Grafo* grafo, int origem, int destino) {
    struct No* anterior = NULL; // define o no anterior como null
    struct No* temp = grafo->listasAdj[origem]; // cria um no temporario
    while (temp) {
        if (temp->vertice == destino) { // o vertice do no temporario aponta para o destino
            if (anterior)
                anterior->prox = temp->prox; // iguala o proximo do anterior com o do temporario
            else
                grafo->listasAdj[origem] = temp->prox; // a origem aponta para o proximo
            free(temp);
            break;
        }
        anterior = temp;
        temp = temp->prox;
    }

    // Remover a aresta de destino para origem (grafo não direcionado)
    anterior = NULL; // define o anterior como nulo
    temp = grafo->listasAdj[destino]; // define o temporario como destino da lista
    while (temp) {
        if (temp->vertice == origem) { // o vertice temporario aponta para a origem
            if (anterior)
                anterior->prox = temp->prox; // iguala o proximo do anterior com o do temporario
            else
                grafo->listasAdj[destino] = temp->prox; // / a origem aponta para o proximo
            free(temp); // libera a memoria alocada para temp
            break;
        }
        anterior = temp; // faz as substituições
        temp = temp->prox;
    }
}
// Função para inserir um vértice ao grafo
void inserirVertice(struct Grafo* grafo) {
    grafo->numVertices++; // aumenta o numero de vertices
    grafo->listasAdj = realloc(grafo->listasAdj, grafo->numVertices * sizeof(struct No*)); // realocar a memória apontada por grafo->listasAdj
    // para poder aumentar o numero de vertices
    grafo->listasAdj[grafo->numVertices - 1] = NULL; // quando adiciona um vertice no grafo, sua lista de adjacência é inicializada como vazia,
    //pronta para ser preenchida com as arestas que serão adicionadas
}

// Função para remover um vértice do grafo
void removerVertice(struct Grafo* grafo, int vertice) {
    struct No* temp = grafo->listasAdj[vertice]; // cria um no temporario
    while (temp) {
        struct No* proximo = temp->prox; //um no proximo que aponta para o proximo do no temporario
        free(temp);// libera o no temporario
        temp = proximo; // faz as substituiçoes
    }
    grafo->listasAdj[vertice] = NULL;

    // Remover todas as ocorrências do vértice nas listas de adjacência dos outros vértices
    for (int i = 0; i < grafo->numVertices; i++) {
        struct No* anterior = NULL; // aponta o no anterior como nulo
        temp = grafo->listasAdj[i];
        while (temp) {
            if (temp->vertice == vertice) {
                if (anterior)
                    anterior->prox = temp->prox;// faz o proximo do anterior se igualar ao do temporario
                else
                    grafo->listasAdj[i] = temp->prox; //faz cada parte grafo apontar para o proximo
                free(temp);
                break;
            }
            anterior = temp;// faz as substuições
            temp = temp->prox;
        }
    }
}



// Função para visualizar o grafo
void exibirGrafo(struct Grafo* grafo) {
    for (int i = 1; i < grafo->numVertices; i++) { // um loop q pega todos os vertices do grafo
        struct No* temp = grafo->listasAdj[i];//um no temporario pra percorrer a lista de adjacencia do vertice i
        printf("%d -> ", i);
        while (temp) {
            printf("%d -> ", temp->vertice);
            temp = temp->prox; // avança para um proximo no
        }
        printf("\n");
    }
}

// Função para liberar a memória alocada para o grafo
void liberarGrafo(struct Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) { // um loop que pega todos os vertices do grafo
        struct No* temp = grafo->listasAdj[i]; // um no temporario q aponta para a cada lista de adjacencia do vertice i
        while (temp) {
            struct No* proximo = temp->prox;//é usado para armazenar o próximo nó na lista de adjacência antes de liberar a memória do nó atual.
            // isso serve para evitar perder a referência para os nós restantes na lista.
            free(temp);//libera memoria do no temporario
            temp = proximo;//faz as substituiçoes
        }
    }
    free(grafo->listasAdj); // libera as listas de adjacencia
    free(grafo); //libera o grafo
}

int origem, destino;

int main() {
    struct Grafo* grafo = criarGrafo(10); // Criando um grafo com 10 vértices

    // Adicionando arestas conforme o grafo dado
    adicionarAresta(grafo, 1, 2);// adiciona uma aresta apontando de 1 para 2
    adicionarAresta(grafo, 1, 6);// adiciona uma aresta apontando de 1 para 6
    adicionarAresta(grafo, 2, 4);// adiciona uma aresta apontando de 2 para 4
    adicionarAresta(grafo, 2, 3);// adiciona uma aresta apontando de 2 para 3
    adicionarAresta(grafo, 3, 5);// adiciona uma aresta apontando de 3 para 5
    adicionarAresta(grafo, 4, 6);// adiciona uma aresta apontando de 4 para 6
    adicionarAresta(grafo, 4, 5);// adiciona uma aresta apontando de 4 para 5
    adicionarAresta(grafo, 4, 7);// adiciona uma aresta apontando de 4 para 7
    adicionarAresta(grafo, 5, 6);// adiciona uma aresta apontando de 5 para 6
    adicionarAresta(grafo, 7, 8);// adiciona uma aresta apontando de 7 para 8
    adicionarAresta(grafo, 7, 9);// adiciona uma aresta apontando de 7 para 9

    int escolha;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir Vertices\n");
        printf("2. Inserir Arestas\n");
        printf("3. Visualizar Grafo\n");
        printf("4. Remover Vertices\n");
        printf("5. Remover Arestas\n");
        printf("6. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                inserirVertice(grafo);
                break;
            case 2:

                printf("Digite a origem e o destino da aresta: ");
                scanf("%d %d", &origem, &destino);
                inserirAresta(grafo, origem, destino);
                break;
            case 3:
                printf("\nGrafo:\n");
                exibirGrafo(grafo);
                break;
            case 4:
                printf("Digite o vértice a ser removido: ");
                scanf("%d", &origem);
                removerVertice(grafo, origem);
                break;
            case 5:
                printf("Digite a origem e o destino da aresta a ser removida: ");
                scanf("%d %d", &origem, &destino);
                removerAresta(grafo, origem, destino);
                break;
            case 6:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (escolha != 6);

    // Libera memória alocada do grafo
    liberarGrafo(grafo);

    return 0;
}