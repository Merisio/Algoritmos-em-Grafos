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
        printf("\n1- Inserir V�rtice\n");
        printf("2- Inserir Aresta\n");
        printf("3- Remover V�rtice\n");
        printf("4- Remover Aresta\n");
        printf("5- Visualizar Grafo\n");
        printf("6- Informar grau de um v�rtice\n");
        printf("7- Verificar se o grafo � conexo\n");
        printf("8- Transformar em Matriz\n");
        printf("9- Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Qual v�rtice deseja inserir: \n");
                scanf("%d", &a);
                adicionar_vertice(grafo, a);
                break;

            case 2:
                printf("Informe o v�rtice de origem e de destino: ");
                scanf("%d %d", &a, &b);
                adicionar_aresta(grafo, a, b);
                break;

            case 3:
                printf("Qual v�rtice deseja remover: \n");
                scanf("%d", &a);
                remover_vertice(grafo, a);
                break;

            case 4:
                printf("Informe o v�rtice de origem e de destino da aresta a ser removida: ");
                scanf("%d %d", &a, &b);
                remover_aresta(grafo, a, b);
                break;

            case 5:
                imprimir(grafo);
                break;

            case 6:
                printf("Qual v�rtice deseja saber o grau: \n");
                scanf("%d", &a);
                printf("O v�rtice � de grau %d \n", grau_do_vertice(grafo, a));
                break;
            case 7:
                if(eh_conexo(grafo)){
                    printf("O grafo � conexo.\n");
                }else{
                    printf("N�o � conexo.\n");
                }
                break;
            case 8:
                converter_matriz(grafo);
                break;
            case 9:
                printf("Saindo\n");
                break;
            default:
                printf("Op��o Invalida.\n");
                break;
        }

    }while(opcao != 9);

    liberar(grafo);
    return 0;
}


