#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "algGrafos.h"

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    Grafo *grafo = criar_grafo();
    int opcao = 0, a, b;

    for(int i=1; i<10; i++)
        adicionar_vertice(grafo, i);

    adicionar_aresta(grafo, 1, 2);
    adicionar_aresta(grafo, 1, 6);
    adicionar_aresta(grafo, 2, 4);
    adicionar_aresta(grafo, 2, 3);
    adicionar_aresta(grafo, 3, 5);
    adicionar_aresta(grafo, 4, 6);
    adicionar_aresta(grafo, 4, 5);
    adicionar_aresta(grafo, 4, 7);
    adicionar_aresta(grafo, 5, 6);
    adicionar_aresta(grafo, 7, 8);
    adicionar_aresta(grafo, 7, 9);

    do{
        printf("\n1- Inserir Vértice\n");
        printf("2- Inserir Aresta\n");
        printf("3- Remover Vértice\n");
        printf("4- Remover Aresta\n");
        printf("5- Visualizar Grafo\n");
        printf("6- Informar grau de um vértice\n");
        printf("7- Verificar se o grafo é conexo\n");
        printf("8- Transformar em Matriz\n");
        printf("9- Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Qual vértice deseja inserir: \n");
                scanf("%d", &a);
                adicionar_vertice(grafo, a);
                break;

            case 2:
                printf("Informe o vértice de origem e de destino: ");
                scanf("%d %d", &a, &b);
                adicionar_aresta(grafo, a, b);
                break;

            case 3:
                printf("Qual vértice deseja remover: \n");
                scanf("%d", &a);
                remover_vertice(grafo, a);
                break;

            case 4:
                printf("Informe o vértice de origem e de destino da aresta a ser removida: ");
                scanf("%d %d", &a, &b);
                remover_aresta(grafo, a, b);
                break;

            case 5:
                imprimir(grafo);
                break;

            case 6:
                printf("Qual vértice deseja saber o grau: \n");
                scanf("%d", &a);
                printf("O vértice é de grau %d \n", grau_do_vertice(grafo, a));
                break;
            case 7:
                if(eh_conexo(grafo)){
                    printf("O grafo é conexo.\n");
                }else{
                    printf("Não é conexo.\n");
                }
                break;
            case 8:
                converter_matriz(grafo);
                break;
            case 9:
                printf("Saindo\n");
                break;
            default:
                printf("Opção Invalida.\n");
                break;
        }

    }while(opcao != 9);

    liberar(grafo);
    return 0;
}


