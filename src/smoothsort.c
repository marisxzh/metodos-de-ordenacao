#include "smoothsort.h"
#include <stdio.h>
#include <stdlib.h>


// função que troca os valores, passando por parametro
static void trocar(int *a, int *b){

    int aux = *a;
    *a = *b;
    *b = aux;

}



// calcula os números de Leonardo de acordo com a quantidade de números na lista[]

static int* gerarLeonardo (int n, int *qtd){

    //dar um limite de criação para os números de leonardo

    int limite = 64;
    int *L = (int*)malloc(limite * sizeof(int));

    //a sequencia de leonardo inicia com {1,1,...}
    L[0] = 1;
    L[1] = 1;

    //o loop infinito começa com o proximo número de leonardo
    int i = 2;
    while(1) {

        //calculo do número de leonardo 
        L[i] = L[i - 1] + L[i - 2] + 1;

        //se o número de leonardo for maior que n ou estourar o limite
        if(L[i] > n || i >= (limite - 1)) {

            //passar a quantidade de números de leonardo
            *qtd = i;
            break;
        }

        i++;
    }

    // retorna onde o array de números de leonardo começa
    return L;

}


// organiza os filhos para que eles estejam na posição correta, garantindo um heap valido
// i -> tamanho da arvore a ser analisada
static void sift(int lista[], int raiz, int i, const int L[]){

    while ( i >= 2){

        // acha os filhos
        int filho_direita = raiz - 1;
        // pula o tamanho da arvore para achar o filho da esquerda
        int filho_esquerda = raiz - 1 - L[i-2];

        // Verificação de segurança
        if (filho_direita < 0 || filho_esquerda < 0) {
            break;
        }

        if (lista[raiz] >= lista[filho_direita] && lista[raiz] >= lista[filho_esquerda]) {
            // se o pai for maior ele sai do loop
            break;
        }

        // entre os filhos, o maior passa a ser o pai
        if (lista[filho_direita] >= lista[filho_esquerda]){

            trocar(&lista[raiz], &lista[filho_direita]);
            raiz = filho_direita;
            i = i -1;

        } else {

            trocar (&lista[raiz], &lista[filho_esquerda]);
            raiz = filho_esquerda;
            i = i - 2;

        }

    }
}



// garante que as raízes das arvores de leonardo estejam em ordem crescente
static void trillium(int lista[], int i, int forest[], int qtd_arvores, const int L[]) {

    if (qtd_arvores <= 0) {
        return;
    }

    int raiz = i;
    int arvore_atual = qtd_arvores - 1;

    while (arvore_atual > 0) {

        int k = forest[arvore_atual];
        // acha a arvore a esquerda para comparar
        int raiz_anterior = raiz - L[k];

        // Verificação de segurança para índice negativo
        if (raiz_anterior < 0) {
            break;
        }

        // se ja estiver na ordem certa, sai do loop
        if (lista[raiz_anterior] <= lista[raiz]) {
            break;
        }

        // se a arvore possui galhos
        if (k>=2) {

            int filho_direita = raiz - 1;
            int filho_esquerda = raiz - 1 - L[k-2];

            if (filho_direita < 0 || filho_esquerda < 0) {
                break;
            }

            if (lista[raiz_anterior] <= lista[filho_esquerda] || lista[raiz_anterior] <= lista[filho_direita]) {
                break;
            }

        }


        // se não entrar em nenhum dos ifs
        trocar(&lista[raiz], &lista[raiz_anterior]);
        raiz = raiz_anterior;
        arvore_atual--;
    }

    // organiza a arvore (arvore_atual agora é >= 0)
    if (arvore_atual >= 0 && arvore_atual < 64) {
        sift (lista, raiz, forest[arvore_atual], L);
    }

}




void smoothSort(int lista[], int n) {
    if (n<2) return;

    // gerar os números de leonardo
    int qtd_L;
    int *L = gerarLeonardo(n, &qtd_L);

    int forest[64];
    int qtd_arvores = 0;

    // construindo a floresta
    for (int i = 0; i < n; i++){

        // CORRIGIDO: verifica se as duas últimas árvores são consecutivas (penúltima == última + 1)
        // essa é a condição real para unir duas árvores de Leonardo
        if (qtd_arvores >= 2 && forest[qtd_arvores - 2] == forest[qtd_arvores - 1] + 1){

            if (forest[qtd_arvores - 2] < 63) {
                forest[qtd_arvores - 2] = forest[qtd_arvores - 2] + 1;
            }
            qtd_arvores--;

        } else {

            if (qtd_arvores < 64) {
                // CORRIGIDO: se a última árvore tem ordem 1, a nova tem ordem 0; senão ordem 1
                if (qtd_arvores >= 1 && forest[qtd_arvores - 1] == 1) {
                    forest[qtd_arvores] = 0;
                } else {
                    forest[qtd_arvores] = 1;
                }

                qtd_arvores++;
            }
        }

        if (qtd_arvores > 0 && qtd_arvores <= 64) {
            trillium(lista, i, forest, qtd_arvores, L);
        }
    }


    // ordenação final
    for (int i = n - 1; i > 0; i--) {

        if (qtd_arvores <= 0) {
            break;
        }

        int k = forest[qtd_arvores - 1];

        if (k <= 1) {
            qtd_arvores--;
        } else {

            qtd_arvores--;
            
            if (qtd_arvores >= 0 && qtd_arvores + 1 < 64 && k >= 2) {
                forest[qtd_arvores] = k-1;
                qtd_arvores++;
                
                if (qtd_arvores < 64) {
                    forest[qtd_arvores] = k-2;
                    qtd_arvores++;

                    int filho_esquerda = i - 1 - L[k-2];
                    int filho_direita = i -1;

                    if (filho_esquerda >= 0 && filho_direita >= 0) {
                        if (qtd_arvores > 0) {
                            trillium(lista, filho_esquerda, forest, qtd_arvores -1, L);
                        }
                        trillium(lista, filho_direita, forest, qtd_arvores, L);
                    }
                }
            }
        }
    }


    // liberação da memoria alocada para os números de leonardo
    free(L);

}