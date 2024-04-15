#include <stdio.h>
#include <stdlib.h>

typedef struct Cell Cell;
typedef struct ListaE ListaE;
typedef struct MatEsparsa MatEsparsa;

// Structs base da matriz esparsa (celulas, listas e matriz por si so)
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

static int procurar_na_lista(int item, ListaE *l){// Busca um item dentro de uma lista encadeada (usada na funcao verificar)
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

int verificar(int item, MatEsparsa *mat){// Verifica se um item existe dentro da matriz, retornando 1 para true e 0 para false
        int i;
        int aux = 0;

        for (i = 0; (i < mat->n_lin) && (aux == 0); i++)
                aux = procurar_na_lista(item, mat->lin[i]);

        return aux;
}

static int validar_pos_matriz(int lin, int col, MatEsparsa *mat){// Verifica se ij e uma posicao que existe na matriz
    return (mat != NULL) && (lin >= 0) && (lin < mat->n_lin) && (col >= 0) && (col < mat->n_col);
}

int buscar_por_posicao(int l, int c, MatEsparsa *mat){// Busca o valor presente numa posicao ij da matriz
    Cell *aux;
    int valor = 0;

    if ((mat != NULL) && validar_pos_matriz(l, c, mat)){// Verificando se a posicao existe na matriz
        aux = mat->lin[l]->head; // Celula auxiliar recebe a cabeca da lista

        while ((aux != NULL) && (c > aux->col))// Inicia o laco para percorrer a lista
            aux = aux->next; // Percorrendo a lista

        if ((aux != NULL) && (c == aux->col))
            valor = aux->item;
    }

    return valor;
}

static void inserir_na_lista(int item, int col, ListaE *l){// Funcao que troca ou insere um valor em uma determinada celula
    Cell *auxA, *auxP, *novo;                              // (usada na funcao inserir)

    if ((l->head == NULL) || (col < l->head->col)){
        novo = criar_celula(item, col);
        novo->next = l->head;
        l->head = novo;
    }
    else if (col == l->head->col){// Caso em que a coluna desejada ja e a primeira
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
    Cell *auxA = NULL;                           // Usada na funcao remover
    Cell *auxP = NULL;

    if (l->head != NULL){
        if (col == l->head->col){// Tratando o caso em que o item a ser removido ja e o primeiro
            auxP = l->head;// Variavel auxiliar recebe a cabeca da lista para poder remove-la
            l->head = l->head->next;
            free(auxP); // Liberando o conteudo da celula
        }
        else// Percorrendo a lista no caso em que o item nao esta na cabeca
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

void inserir(int item, int l, int c, MatEsparsa *mat){// Insere ou troca de posicao um item na matriz
    if (validar_pos_matriz(l, c, mat))
        inserir_na_lista(item, c, mat->lin[l]);
}

void remover(int l, int c, MatEsparsa *mat){// Remove um item na matriz
    if (validar_pos_matriz(l, c, mat))
        remover_na_lista(c, mat->lin[l]);
}

void imprimir(MatEsparsa* mat){
    int i;

    for (i = 0; i < mat->n_lin; i++){
        Cell *celula_atual = mat->lin[i]->head;
        int col_atual = 0;

        while (celula_atual != NULL){
            while (col_atual < celula_atual->col){// Imprimir zeros ate a coluna atual da celula
                printf("0 ");
                col_atual++;
            }

            printf("%d ", celula_atual->item);// Imprimir o valor da celula
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
            int i = 0;
            lista_atual = mat->lin[i];
            celula_atual = lista_atual->head; // Percorrer todas as celulas da lista atual

            while (celula_atual != NULL){
                proxima = celula_atual->next; // Pegando dado da celula atual para libera-la
                free(celula_atual); // Liberando a celula atual
                celula_atual = proxima; //atribuido a proxima celula para execucao da remocao novamente
            }

            free(lista_atual); // Liberar a lista atual
            i++; //Incremento no i para percorrer a lista
        }
        free(mat); // Liberar a estrutura da matriz esparsa
    }
}

MatEsparsa* criar_transposta(MatEsparsa *mat){
    if (mat == NULL)
        return NULL;

    MatEsparsa *transposta = criar(mat->n_col, mat->n_lin);// Criando uma nova matriz com as colunas e linhas trocadas

    for (int i = 0; i < mat->n_lin; i++){ // Percorrer a matriz original e inserir as celulas nao nulas na matriz transposta
        ListaE *lista_atual = mat->lin[i];

        Cell *celula_atual = lista_atual->head; // Percorrer todas as celulas da lista atual

        while (celula_atual != NULL){ // Inserir a celula na posicao transposta correspondente
            inserir(celula_atual->item, celula_atual->col, i, transposta);
            celula_atual = celula_atual->next;
        }
    }
    return transposta;
}

MatEsparsa* somar(MatEsparsa *mat1, MatEsparsa *mat2){
    if (mat1 == NULL || mat2 == NULL || mat1->n_lin != mat2->n_lin || mat1->n_col != mat2->n_col)// Tratamento de caso para quando
        return NULL;                                                                             // a matriz nao for da mesma ordem

    MatEsparsa *soma = criar(mat1->n_lin, mat1->n_col);// Cria uma nova matriz para armazenar a soma

    for (int i = 0; i < mat1->n_lin; i++){// Percorre cada linha da matriz
        Cell *celula_mat1 = mat1->lin[i]->head;// Percorre as celulas da linha i de ambas as matrizes
        Cell *celula_mat2 = mat2->lin[i]->head;

        while (celula_mat1 != NULL || celula_mat2 != NULL){// Percorre ate que ambas as celulas sejam nulas
            int col_atual;

            if (celula_mat1 != NULL)
                col_atual = celula_mat1->col;
            else
                col_atual = celula_mat2->col;

            int valor_soma = 0;

            if (celula_mat1 != NULL && celula_mat1->col == col_atual){// Soma os valores das celulas correspondentes
                valor_soma += celula_mat1->item;
                celula_mat1 = celula_mat1->next;
            }
            if (celula_mat2 != NULL && celula_mat2->col == col_atual){
                valor_soma += celula_mat2->item;
                celula_mat2 = celula_mat2->next;
            }

            // Insere a celula na matriz de soma se o valor for diferente de zero
            inserir(valor_soma, i, col_atual, soma);

            // Avanca para a proxima coluna
            if (celula_mat1 != NULL && celula_mat1->col == col_atual)
                celula_mat1 = celula_mat1->next;
            if (celula_mat2 != NULL && celula_mat2->col == col_atual)
                celula_mat2 = celula_mat2->next;
        }
    }

    return soma;
}

MatEsparsa* multiplicar(MatEsparsa *mat1, MatEsparsa *mat2){
    if (mat1 == NULL || mat2 == NULL || mat1->n_col != mat2->n_lin){// Tratando os casos no qual a multiplicacao nao e possivel
        printf("Nao e possivel multiplicar");
        return NULL;
    }

    MatEsparsa *resultado = criar(mat1->n_lin, mat2->n_col);// Criando uma nova matriz para armazenar o resultado

    for (int i = 0; i < mat1->n_lin; i++){// Percorrendo cada linha da primeira matriz
        for (int j = 0; j < mat2->n_col; j++){ // Percorrendo cada coluna da segunda matriz
            int valor_soma = 0;

            for (int k = 0; k < mat1->n_col; k++){// Calculando o produto escalar entre a linha i da primeira matriz e a coluna j da segunda matriz
                int elemento_mat1 = buscar_por_posicao(i, k, mat1);
                int elemento_mat2 = buscar_por_posicao(k, j, mat2);
                valor_soma += elemento_mat1 * elemento_mat2;
            }
            // Inserindo o elemento na matriz resultado se o valor for diferente de zero
            inserir(valor_soma, i, j, resultado);
        }
    }
    return resultado;
}
