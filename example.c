#include <stdio.h>
#include "src/lista.h"

int main(void){

    list_t *lista = list_new();

    list_add(lista, "Item 1", 0); // index 0
    list_add_end(lista, "Item 2");

    printf("Item: %s\n", list_get(lista, 0)); // Item: Item 1
    printf("Item: %s\n", list_get_end(lista));// Item: Item 2

    // list_get_node() return node_t
    list_get_node(lista, 0)->valor = "Item 0";
    list_get_node_end(lista)->valor = "Item 1";

    printf("Item: %s\n", list_get(lista, 0)); // Item: Item 0
    printf("Item: %s\n", list_get_end(lista));// Item: Item 1

    list_remove(lista, 0);
    printf("Tamanho da lista (size): %d\n", lista->tamanho); // Tamanho da lista (size): 1

    list_remove_end(lista);
    printf("Tamanho da lista (size): %d\n", lista->tamanho); // Tamanho da lista (size): 0

    list_free(lista);

    return 0;
}
