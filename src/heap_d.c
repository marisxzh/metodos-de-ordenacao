#include "heap_d.h"


// função que troca os valores, passando por parametro
static void trocar(int *a, int *b){

    int aux = *a;
    *a = *b;
    *b = aux;

}


static void heapfyD(int lista[], int n, int pai, int d){


    int maior = pai;

    // calula o primeiro e ultimo filho
    int primeiro_filho = d * pai + 1;
    int ultimo_filho = d * pai + d;

    // verifica qual filho é o maior
    for (int i = primeiro_filho; i <= ultimo_filho && i < n; i++) {

        if (lista[i] > lista[maior]){
            maior = i;
        }
    }


    // se o maior dos filhos for maior que o pai ele vai para o topo
    if (maior != pai) {

        trocar(&lista[pai], &lista[maior]);
        heapfyD(lista, n, maior, d);

    }

}


void heapSortD(int lista[], int n, int d){

    //garantir que a divisão por d seja possivel
    if (d < 1){

        d = 2;
    
    }


    // o ultimo pai está em (n-2)/d
    for (int i = (n-2)/d; i>=0; i--){

        heapfyD(lista, n , i, d);

    }


    //ordenação final
    for (int i = n - 1; i>0; i--){

        trocar(&lista[0], &lista[i]);
        heapfyD(lista, i, 0, d);


        
    }

}
