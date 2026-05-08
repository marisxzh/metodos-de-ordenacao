#include "heap_min.h"



// função que troca os valores, passando por parametro
static void trocar(int *a, int *b){

    int aux = *a;
    *a = *b;
    *b = aux;

}



// mantem o menor elemento na topo da árvore
static void heapfyMin(int lista[], int n, int pai) {

    // (+1) e (+2) no inicio garante que o nó raiz tenha filhos (1 e 2) 
    int menor = pai;
    int filho_esquerdo = 2 * pai + 1;
    int filho_direito = 2 * pai + 2;

    // verifica se o filho esquerdo é o menor
    if (filho_esquerdo < n && lista[filho_esquerdo] < lista[menor]) {

        menor = filho_esquerdo;

    }


    // verifica se o filho direito é o menor
    if (filho_direito < n && lista[filho_direito] < lista[menor]) {

        menor = filho_direito;

    }


    // se o pai não for o menor ele "desce" na árvore
    if (menor != pai) {

        trocar(&lista[pai], &lista[menor]);
        // reorganiza a árvore quantas vezes for necessária para levar o menor até o topo da árvore
        heapfyMin(lista, n, menor);
    
    }

}



void heapSortMin (int lista[], int n){

    // começa da metade da árvore para cima, cada pai chama a função para que garanta que o menor valor entre ele e seus filhos suba
    for (int i = (n/2) - 1; i >= 0; i--) {
        heapfyMin(lista, n, i);


    }

    // faz a ordenação final, colocando o menor elemento (topo da árvore) no ultimo lugar da lista[] (lista decrescente)
    for (int i = n - 1; i > 0; i--){

        trocar(&lista[0], &lista[i]);
        heapfyMin(lista, i, 0);


        
    }


}