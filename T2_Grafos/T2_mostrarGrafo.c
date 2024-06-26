#include <stdio.h>
#include <stdlib.h>
#include "T2_TAD.h"

int main(){
    int origem, destino;

    Grafo* grafo = criarGrafo();
    inserirVertice(grafo);
    inserirVertice(grafo);
    inserirVertice(grafo);
    inserirVertice(grafo);
    inserirVertice(grafo);
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 5);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 5, 4);

    int opcao;

    while (opcao != 6){
        printf("\nOperacoes com o grafo:\n");
        printf("1) Inserir Vertice\n");
        printf("2) Inserir Aresta\n");
        printf("3) Visualizar\n");
        printf("4) Remover Vertice\n");
        printf("5) Remover Aresta\n");
        printf("6) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                inserirVertice(grafo);
                printf("\nVertice inserido.\n");
                break;
            case 2:
                printf("Digite a origem e o destino da aresta: ");
                scanf("%d %d", &origem, &destino);
                inserirAresta(grafo, origem, destino);
                break;
            case 3:
                printf("\nGrafo abstrato:\n");
                imprimir(grafo);
                break;
            case 4:
                removerVertice(grafo);
                printf("\nVertice removido.\n");
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
                printf("Opcao invalida.\n");
                break;
        }
    }

    liberar(grafo);

    imprimir(grafo);

    return 0;
}
