#include "heap_max.h"


// função que troca os valores, passando por parametro
static void trocar(int *a, int *b){

    int aux = *a;
    *a = *b;
    *b = aux;

}


// mantem o maior elemento na topo da árvore
static void heapfyMax(int lista[], int n, int pai) {

    // (+1) e (+2) no inicio garante que o nó raiz tenha filhos (1 e 2) 
    int maior = pai;
    int filho_esquerdo = 2 * pai + 1;
    int filho_direito = 2 * pai + 2;

    // verifica se o filho esquerdo é o maior
    if (filho_esquerdo < n && lista[filho_esquerdo] > lista[maior]) {

        maior = filho_esquerdo;

    }


    // verifica se o filho direito é o maior
    if (filho_direito < n && lista[filho_direito] > lista[maior]) {

        maior = filho_direito;

    }


    // se o pai não for o maior ele "desce" na árvore
    if (maior != pai) {

        trocar(&lista[pai], &lista[maior]);
        // reorganiza a árvore quantas vezes for necessária para levar o maior até o topo da árvore
        heapfyMax(lista, n, maior);
    
    }

}


void heapSortMax (int lista[], int n){

    // começa da metade da árvore para cima, cada pai chama a função para que garanta que o maior valor entre ele e seus filhos suba
    for (int i = (n/2) - 1; i >= 0; i--) {
        heapfyMax(lista, n, i);


    }

    // faz a ordenação final, colocando o maior elemento (topo da árvore) no ultimo lugar da lista[]
    for (int i = n - 1; i > 0; i--){

        trocar(&lista[0], &lista[i]);
        heapfyMax(lista, i, 0);


        
    }


}