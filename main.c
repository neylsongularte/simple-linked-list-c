#include <stdio.h>
#include "src/lista.h"


int main(){

    list_t *lista;
    node_t *node;

    lista = list_new();
    list_add(lista, "iidk");

    node = list_get(lista, 0);

    printf("Ola: %s\n", node->valor);

    return 0;
}
