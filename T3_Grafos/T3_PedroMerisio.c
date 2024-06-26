#include <stdio.h>
#include <stdlib.h>
#include "T3_PedroMerisio.h"

int main(){
    Grafo *grafo = criar_grafo();
    int opcao = 0, a, b, i;

    for(i = 0; i < 5; i++)
        adicionar_vertice(grafo, i);

    adicionar_aresta(grafo, 1, 2);
    adicionar_aresta(grafo, 1, 3);
    adicionar_aresta(grafo, 2, 4);
    adicionar_aresta(grafo, 2, 3);
    adicionar_aresta(grafo, 3, 5);
    adicionar_vertice(grafo, 6);
    

    do{
        printf("\n==== OPERACOES COM GRAFOS ====\n");
        printf("1) Inserir Vertice;\n");
        printf("2) Inserir Aresta;\n");
        printf("3) Remover Vertice;\n");
        printf("4) Remover Aresta;\n");
        printf("5) Visualizar Grafo;\n");
        printf("6) Informar grau de um vertice;\n");
        printf("7) Verificar se e conexo;\n");
        printf("8) Mostrar matriz de adjacencias;\n");
        printf("9) Sair.\n");
        printf("Indique a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Qual vertice deseja inserir: ");
                scanf("%d", &a);
                adicionar_vertice(grafo, a);
                break;

            case 2:
                printf("Informe o vertice de origem e de destino: ");
                scanf("%d %d", &a, &b);
                adicionar_aresta(grafo, a, b);
                break;

            case 3:
                printf("Qual vertice deseja remover: ");
                scanf("%d", &a);
                remover_vertice(grafo, a);
                break;

            case 4:
                printf("Informe o vertice de origem e de destino da aresta a ser removida: ");
                scanf("%d %d", &a, &b);
                remover_aresta(grafo, a, b);
                break;

            case 5:
                visualizar(grafo);
                break;

            case 6:
                printf("Qual vertice deseja saber o grau: ");
                scanf("%d", &a);
                printf("\nO vertice e de grau %d.\n", grauVertice(grafo, a));
                break;

            case 7:
                if (eh_conexo(grafo))
                    printf("\nE conexo.\n");
                else
                    printf("\nNao eh conexo.\n\n");
                break;

            case 8:
                matrizAdjacencia(grafo);
                break;

            case 9:
                printf("Saindo.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

    }while(opcao != 9);

    liberar(grafo);

    return 0;
}

