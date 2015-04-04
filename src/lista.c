#include <stdlib.h>
#include <sys/time.h>
#include "lista.h"


// void imprimeListaDeString(const list_t *lista){
//
//     node_t *node;
//
//     node = lista->primeiroItem;
//
//     while(node){
//         printf("Valor do nodo no índice: %s\n", (char *) node->valor);
//         node = node->proximo;
//     }
//
// }

list_t * list_new() // cria uma nova lista
{
    list_t *novaLista;

    novaLista = malloc(sizeof(list_t));
    novaLista->tamanho = 0;
    novaLista->primeiroItem = NULL;
    novaLista->ultimoItem = NULL;

    return novaLista;
}

int list_add(list_t *lista, void *valor) // adiciona um item na lista
{
    node_t *nodo;

    nodo = node_new(); // cria um novo node
    nodo->valor = valor; // preenche o valor do node com o argumento passado

    // se a lista estiver vazia, o que significa que não existe primeiro e último
    lista->primeiroItem == NULL
        ? lista->primeiroItem = nodo // o nodo também se torna o primeiro item da lista,
        : (lista->ultimoItem->proximo = nodo); // o último nodo da lista aponta para o novo nodo


    lista->ultimoItem = nodo; // o nodo se torna o último item da lista
    lista->tamanho++; // o tamanho da lista é incrementado em 1

    return 0;
}

node_t * list_get(const list_t *lista, register int indice) // obtém o valor do índice
{
    node_t *nodo;

    if(indice >= lista->tamanho)
        return NULL; // código de índice inválido

    nodo = lista->primeiroItem;

    while(indice--){
        nodo = nodo->proximo;
    }

    return nodo;
}

node_t * node_new()
{
    node_t *nodo;

    nodo = malloc(sizeof(node_t)); // aloca memória para o nodo
    // inicializa campos
    nodo->proximo = NULL;
    nodo->valor = NULL;

    return nodo;
}


// int getTempo(struct timeval inicio, struct timeval fim){
//
//     long int tempoDeExecucao;
//
//     if(inicio.tv_usec > fim.tv_usec){
//         tempoDeExecucao = (1000000 - inicio.tv_usec) + fim.tv_usec;
//     } else {
//         tempoDeExecucao = fim.tv_usec - inicio.tv_usec;
//     }
//
//     // retorna tempo em milissegundos
//     return tempoDeExecucao / 1000;
// }
