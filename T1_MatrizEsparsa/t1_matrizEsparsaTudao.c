#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Cell Cell;
typedef struct ListaE ListaE;
typedef struct MatEsparsa MatEsparsa;

// Structs base da matriz esparsa (células, listas e matriz por si só)
struct Cell{
        int item;
        int col;
        Cell *next;
};

struct ListaE{
        Cell *head;
};

struct MatEsparsa{ 
       int n_lin;
       int n_col;
       ListaE **lin;
};

MatEsparsa* criar(int l, int c){ //Cria matriz alocando dinamicamente as linhas e colunas
        MatEsparsa* mat = (MatEsparsa*) malloc(sizeof(MatEsparsa));
        int i;

        mat->n_col = c;
        mat->n_lin = l;
        mat->lin = (ListaE**) malloc(sizeof(ListaE*) * l);//aloca a linha por um ponteiro duplo de listas encadeadas

        for (i = 0; i < l; i++){
                mat->lin[i] = (ListaE*) malloc(sizeof(ListaE));//aloca cada coluna por item do vetor de listas encadeadas
                mat->lin[i]->head = NULL;
        }

        return mat;
}

Cell* criar_celula(int item, int col){// Cria uma nova celula atribuindo um valor e a sua respectiva coluna
	Cell *nova = (Cell*) malloc(sizeof(Cell));
	nova->item = item;
	nova->col = col;
	nova->next = NULL;

	return nova;
}

static int procurar_lista(int item, ListaE *l){// Busca um item dentro de uma lista encadeada (usada na função buscar)
        Cell *aux;

        if (l != NULL){
                aux = l->head;

                while ((aux != NULL) && (aux->item != item))
                	aux = aux->next;
        }

        if ((aux != NULL) && (aux->item == item))
                return 1;
        else
                return 0;
}

int buscar(int item, MatEsparsa *mat){// Busca um item dentro da matriz, retornando 1 para true e 0 para false
        int i;
        int aux = 0;

        for (i = 0; (i < mat->n_lin) && (aux == 0); i++)
                aux = procurar_lista(item, mat->lin[i]);

        return aux;
}

static int validar_pos_matriz(int lin, int col, MatEsparsa *mat){// Verifica se ij é uma posição válida na matriz
    return (mat != NULL) && (lin >= 0) && (lin < mat->n_lin) && (col >= 0) && (col < mat->n_col);
}

int buscar_posicao(int l, int c, MatEsparsa *mat){// Busca o valor presente numa posição ij da matriz
    Cell *aux;
    int valor = 0;

    if ((mat != NULL) && validar_pos_matriz(l, c, mat)){// Verificando se a posição existe na matriz
        aux = mat->lin[l]->head;

        while ((aux != NULL) && (c > aux->col))
            aux = aux->next;

        if ((aux != NULL) && (c == aux->col))
            valor = aux->item;
    }

    return valor;
}

static void trocar_inserir_na_lista(int item, int col, ListaE *l){// Função que troca ou insere um valor em uma determinada célula
    Cell *auxA, *auxP, *novo;                                     // (usada na função trocar)
    
    if ((l->head == NULL) || (col < l->head->col)){
        novo = criar_celula(item, col);
        novo->next = l->head;
        l->head = novo;
    }
    else if (col == l->head->col){// Caso em que a coluna desejada já é a primeira
        l->head->item = item;
    }
    else{
        auxA = l->head;// Usando as variaveis auxiliares para percorrer as listas encadeadas
        auxP = auxA;

        while ((auxP != NULL) && (auxP->col < col)){
            auxA = auxP;
            auxP = auxP->next;
        }
        
        if ((auxP != NULL) && (col == auxP->col))
            auxP->item = item;
        else{
            novo = criar_celula(item, col);
            novo->next = auxA->next;
            auxA->next = novo;
        }
    }
}

static void remover_na_lista(int col, ListaE *l){// Remove uma celula de uma lista com base na coluna
    Cell *auxA, *auxP = NULL;
    
    if (l->head != NULL){
        if (col == l->head->col){
            auxP = l->head;
            l->head = l->head->next;
            free(auxP);
        }else{
            auxA = l->head;
            auxP = auxA;
            
            while ((auxP != NULL) && (auxP->col < col)){
                auxA = auxP;
                auxP = auxP->next;
            }
            
            if ((auxP != NULL) && (col == auxP->col)){
                auxA->next = auxP->next;

                free(auxP);
            }
        }
    }
}

void trocar(int item, int l, int c, MatEsparsa *mat){// 
    if (validar_pos_matriz(l, c, mat)){
        if (item > 0)
            trocar_inserir_na_lista(item, c, mat->lin[l]);
        else
            remover_na_lista(c, mat->lin[l]);
    }
}

void imprimir(MatEsparsa* mat){
    if (mat == NULL){
        printf("A matriz não existe.");
    }
    int i;

    for (i = 0; i < mat->n_lin; i++){
        Cell *celula_atual = mat->lin[i]->head;
        int col_atual = 0;

        while (celula_atual != NULL){
            while (col_atual < celula_atual->col){// Imprimir zeros até a coluna atual da célula
                printf("0 ");
                col_atual++;
            }
            
            printf("%d ", celula_atual->item);// Imprimir o valor da célula
            col_atual++;
            celula_atual = celula_atual->next;
        }

        while (col_atual < mat->n_col){// Imprimir zeros para as colunas restantes
            printf("0 ");
            col_atual++;
        }
        printf("\n");
    }
}

void apagar(MatEsparsa *mat){
    if (mat != NULL){
        ListaE *lista_atual;
        Cell *celula_atual;
        Cell *proxima;

        while (lista_atual != NULL){
            lista_atual = mat->lin;
            celula_atual = lista_atual->head;// Percorrer todas as células da lista atual

            while (celula_atual != NULL){
                proxima = celula_atual->next; // Pegando dado da celula atual para liberá-la
                free(celula_atual); // Liberando a célula atual
                celula_atual = proxima; //atribuido a proxima celula para execução da remoção novamente
            }

            free(lista_atual); // Liberar a lista atual
        }
        free(mat);      // Liberar a estrutura da matriz esparsa
    }
}

MatEsparsa* criar_transposta(MatEsparsa *mat){
    if (mat == NULL)
        return NULL;

    MatEsparsa *transposta = criar(mat->n_col, mat->n_lin);// Criando uma nova matriz com as colunas e linhas trocadas

    for (int i = 0; i < mat->n_lin; i++){ // Percorrer a matriz original e inserir as células não nulas na matriz transposta
        ListaE *lista_atual = mat->lin[i];

        Cell *celula_atual = lista_atual->head; // Percorrer todas as células da lista atual

        while (celula_atual != NULL){ // Inserir a célula na posição transposta correspondente
            trocar(celula_atual->item, celula_atual->col, i, transposta);
            celula_atual = celula_atual->next;
        }
    }
    return transposta;
}

MatEsparsa* somar(MatEsparsa *mat1, MatEsparsa *mat2){
    if (mat1 == NULL || mat2 == NULL || mat1->n_lin != mat2->n_lin || mat1->n_col != mat2->n_col)// Tratamento de caso para quando
        return NULL;                                                                             // a matriz não for da mesma ordem

    MatEsparsa *soma = criar(mat1->n_lin, mat1->n_col);// Cria uma nova matriz para armazenar a soma

    for (int i = 0; i < mat1->n_lin; i++){// Percorre cada linha da matriz
        Cell *celula_mat1 = mat1->lin[i]->head;// Percorre as células da linha i de ambas as matrizes
        Cell *celula_mat2 = mat2->lin[i]->head;

        while (celula_mat1 != NULL || celula_mat2 != NULL){// Percorre até que ambas as células sejam nulas
            int col_atual = celula_mat1 != NULL ? celula_mat1->col : celula_mat2->col;
            int valor_soma = 0;

            // Soma os valores das células correspondentes
            if (celula_mat1 != NULL && celula_mat1->col == col_atual){
                valor_soma += celula_mat1->item;
                celula_mat1 = celula_mat1->next;
            }
            if (celula_mat2 != NULL && celula_mat2->col == col_atual){
                valor_soma += celula_mat2->item;
                celula_mat2 = celula_mat2->next;
            }

            // Insere a célula na matriz de soma se o valor for diferente de zero
            if (valor_soma != 0)
                trocar(valor_soma, i, col_atual, soma);
            
            // Avança para a próxima coluna
            if (celula_mat1 != NULL && celula_mat1->col == col_atual)
                celula_mat1 = celula_mat1->next;
            if (celula_mat2 != NULL && celula_mat2->col == col_atual)
                celula_mat2 = celula_mat2->next;
        }
    }

    return soma;
}

MatEsparsa* multiplicar(MatEsparsa *mat1, MatEsparsa *mat2){
    if (mat1 == NULL || mat2 == NULL || mat1->n_col != mat2->n_lin){// Tratando os casos no qual a multiplicação não é possível
        printf("Nao e possivel multiplicar");
        return NULL;
    }

    MatEsparsa *resultado = criar(mat1->n_lin, mat2->n_col);// Criando uma nova matriz para armazenar o resultado

    for (int i = 0; i < mat1->n_lin; i++){// Percorrendo cada linha da primeira matriz
        for (int j = 0; j < mat2->n_col; j++){ // Percorrendo cada coluna da segunda matriz
            int valor_soma = 0;

            for (int k = 0; k < mat1->n_col; k++){// Calculando o produto escalar entre a linha i da primeira matriz e a coluna j da segunda matriz
                int elemento_mat1 = buscar_posicao(i, k, mat1);
                int elemento_mat2 = buscar_posicao(k, j, mat2);
                valor_soma += elemento_mat1 * elemento_mat2;
            }

            if (valor_soma != 0)// Inserindo o elemento na matriz resultado se o valor for diferente de zero
                trocar(valor_soma, i, j, resultado);
        }
    }
    return resultado;
}

int main (){
    MatEsparsa *mat1 = criar(3, 3);
    MatEsparsa *mat2 = criar(3, 3);

    trocar(1, 0, 0, mat1);
    trocar(2, 0, 1, mat1);
    trocar(3, 0, 2, mat1);
    trocar(4, 1, 2, mat2);
    trocar(5, 2, 0, mat2);
    trocar(6, 2, 1, mat2);

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
    
    return 0;
}