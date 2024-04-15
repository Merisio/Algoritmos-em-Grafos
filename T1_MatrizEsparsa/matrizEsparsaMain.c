#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrizEsparsa.h"

int main (){
    MatEsparsa *mat1 = criar(3, 3);
    MatEsparsa *mat2 = criar(3, 3);

    inserir(1, 0, 0, mat1);
    inserir(2, 0, 1, mat1);
    inserir(3, 0, 2, mat1);
    inserir(4, 1, 2, mat2);
    inserir(5, 2, 0, mat2);
    inserir(6, 2, 1, mat2);

    printf("Primeira matriz:\n");
    imprimir(mat1);

    printf("\nSegunda matriz:\n");
    imprimir(mat2);

    printf("\nSegunda matriz transposta:\n");
    imprimir(criar_transposta(mat2));

    printf("\nSomando as duas matrizes:\n");
    imprimir(somar(mat1, mat2));

    printf("\nMultiplicando as duas matrizes:\n");
    imprimir(multiplicar(mat1, mat2));

    apagar(mat1);
    apagar(mat2);

    imprimir(mat1);
    imprimir(mat2);

    return 0;
}
