#include <stdlib.h>
#include "lista.h"


static node_t * node_new()
{
    node_t *node;

    node = malloc(sizeof(node_t)); // aloca memória para o nodo
    // inicializa campos
    node->proximo = NULL;
    node->valor = NULL;

    return node;
}

node_t * list_get_node(const list_t *lista, register int indice)
{
    node_t *node;

    // não encontrado
    if(indice < 0 || indice >= lista->tamanho)
        return NULL;

    node = lista->primeiroItem;
    while(indice--)
        node = node->proximo;

    return node;
}

node_t * list_get_node_end(const list_t *lista)
{
    // retorna o último node
    return list_get_node(lista, lista->tamanho - 1);
}

// retorna o valor do último node
void * list_get_end(const list_t *lista)
{
    node_t *node;

    node = list_get_node(lista, lista->tamanho - 1);

    if(node == NULL)
        return NULL;

    return node->valor;
}

// retorna o valor do node no índice especificado
void * list_get(const list_t *lista, int indice)
{
    node_t *node;

    node = list_get_node(lista, indice);

    if(node == NULL)
        return NULL;

    return node->valor;
}

list_t * list_new() // cria uma nova lista
{
    list_t *lista;

    lista = malloc(sizeof(list_t));
    lista->tamanho = 0;
    lista->primeiroItem = NULL;
    lista->ultimoItem = NULL;

    return lista;
}

int list_add_end(list_t *lista, void *valor){

    // o tamanho da lista é a posição que o item deve ser inserido
    return list_add(lista, valor, lista->tamanho);
}

int list_add(list_t *lista, void *valor, int indice)
{
    node_t *node, *node_tmp;
    int i;

    if(indice < 0 || indice > lista->tamanho){
        return INDEX_ERROR; // índice inválido
    }

    node = node_new();
    node->valor = valor;

    // lista vazia
    if(lista->primeiroItem == NULL)
    {
        lista->primeiroItem = node;
        lista->ultimoItem = node;
        lista->tamanho++;

        return SUCCESS;
    }

    // primeiro item na lista
    if(indice == 0)
    {
        node->proximo = lista->primeiroItem;
        lista->primeiroItem = node;
        lista->tamanho++;

        return SUCCESS;
    }

    // insere no final
    if(indice == lista->tamanho)
    {
        lista->ultimoItem->proximo = node;
        lista->ultimoItem = node;
        lista->tamanho++;

        return SUCCESS;
    }

    // insere no meio

    // busca o item com índice anterior
    node_tmp = list_get_node(lista, indice - 1);
    node->proximo = node_tmp->proximo;
    node_tmp->proximo = node;
    lista->tamanho++;

    return SUCCESS;
}

void list_free(list_t *lista)
{
    node_t *node, *proximoNode;

    node = lista->primeiroItem;
    while(node){
        proximoNode = node->proximo;
        free(node);
        node = proximoNode;
    }

    free(lista);
    lista->primeiroItem = NULL;
    lista->ultimoItem = NULL;
}


void * list_remove(list_t *lista, int indice)
{
    node_t *node, *node2;
    void *valor;

    if(indice < 0 || indice >= lista->tamanho)
        return NULL;


    if(lista->tamanho == 1) // a lista ficará vazia
    {
        node = lista->primeiroItem;
        lista->primeiroItem = NULL;
        lista->ultimoItem = NULL;
    }
    else if(indice == 0) // remove do início
    {
        node = lista->primeiroItem;
        lista->primeiroItem = node->proximo;
    }
    else if(lista->tamanho == indice + 1) // remove no fim
    {
        node = list_get_node(lista, indice - 1); // node anterior ao que será excluído
        lista->ultimoItem = node;
        node = lista->ultimoItem->proximo;
        lista->ultimoItem->proximo = NULL;
    }
    else // remove no meio
    {
        node = list_get_node(lista, indice - 1); // node anterior ao que será excluído
        node2 = node->proximo;
        node->proximo = node->proximo->proximo;
        node = node2;
    }

    lista->tamanho--;
    valor = node->valor;
    free(node);

    return valor;
}

void * list_remove_end(list_t *lista)
{
    return list_remove(lista, lista->tamanho - 1);
}
