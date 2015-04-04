#include "minunit.h"
#include "../src/lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define assert mu_assert
#define run_test mu_run_test

int tests_run = 0;
int assertions = 0;

//------------------------------------------------------------ list_new
static char * test_list_new()
{
    list_t *lista = list_new();

    assert("lista tamanho != 0", lista->tamanho == 0);
    assert("lista primeiro item != NULL", lista->primeiroItem == NULL);
    assert("lista último item != NULL", lista->ultimoItem == NULL);

    list_free(lista);

    return 0;
}

//------------------------------------------------------------ list_add
static char * test_list_add()
{
    list_t *lista = list_new();

    int resultado = list_add(lista, "ola", 0);

    assert("resultado != SUCESS", resultado == SUCCESS);
    assert("tamanho da lista != 1", lista->tamanho == 1);
    assert("valor do primeiro item != ola", strcmp(lista->primeiroItem->valor, "ola") == 0);
    assert("primeiro item != último", lista->primeiroItem == lista->ultimoItem);
    assert("primeiro item proximo != NULL", lista->primeiroItem->proximo == NULL);

    list_free(lista);

    return 0;
}

static char * test_list_add_com_dois_itens()
{
    list_t *lista = list_new();
    int resultado[2];

    resultado[0] = list_add(lista, "ola", 0);
    resultado[1] = list_add(lista, "ole", 0);

    assert("resultado[0] != SUCCESS", resultado[0] == SUCCESS);
    assert("resultado[1] != SUCCESS", resultado[1] == SUCCESS);
    assert("tamanho da lista != 2", lista->tamanho == 2);
    assert("valor do primeiro item != ole", strcmp(lista->primeiroItem->valor, "ole") == 0);
    assert("valor do segundo item != ola", strcmp(lista->primeiroItem->proximo->valor, "ola") == 0);
    assert("valor do último item != ola", strcmp(lista->ultimoItem->valor, "ola") == 0);
    assert("último item proximo != NULL", lista->ultimoItem->proximo == NULL);

    list_free(lista);

    return 0;
}

static char * test_list_add_inserindo_no_meio()
{
    list_t *lista = list_new();
    int resultado[5];

    resultado[0] = list_add(lista, "a", 0);
    resultado[1] = list_add(lista, "e", 0);
    resultado[2] = list_add(lista, "i", 0);
    resultado[3] = list_add(lista, "o", 0);
    resultado[4] = list_add(lista, "u", 2);

    assert("resultado[0] != SUCCESS", resultado[0] == SUCCESS);
    assert("resultado[1] != SUCCESS", resultado[1] == SUCCESS);
    assert("resultado[2] != SUCCESS", resultado[2] == SUCCESS);
    assert("resultado[3] != SUCCESS", resultado[3] == SUCCESS);
    assert("resultado[4] != SUCCESS", resultado[4] == SUCCESS);
    assert("tamanho da lista != 5", lista->tamanho == 5);
    assert("valor do primeiro item != o", strcmp(lista->primeiroItem->valor, "o") == 0);
    assert("valor do segundo item != i", strcmp(lista->primeiroItem->proximo->valor, "i") == 0);
    assert("valor do terceiro item != u", strcmp(lista->primeiroItem->proximo->proximo->valor, "u") == 0);
    assert("valor do quarto item != e", strcmp(lista->primeiroItem->proximo->proximo->proximo->valor, "e") == 0);
    assert("valor do quinto item != a", strcmp(lista->primeiroItem->proximo->proximo->proximo->proximo->valor, "a") == 0);
    assert("valor do último item != a", strcmp(lista->ultimoItem->valor, "a") == 0);
    assert("último item proximo != NULL", lista->ultimoItem->proximo == NULL);

    list_free(lista);

    return 0;
}

static char * test_list_add_inserindo_no_final()
{
    list_t *lista = list_new();

    list_add(lista, "ola", 0);
    list_add(lista, "ole", 0);
    list_add(lista, "oli", 2);

    assert("tamanho da lista != 3", lista->tamanho == 3);
    assert("valor do primeiro item != ole", strcmp(lista->primeiroItem->valor, "ole") == 0);
    assert("valor do segundo item != ola", strcmp(lista->primeiroItem->proximo->valor, "ola") == 0);
    assert("valor do terceiro item != oli", strcmp(lista->primeiroItem->proximo->proximo->valor, "oli") == 0);
    assert("valor do último item != oli", strcmp(lista->ultimoItem->valor, "oli") == 0);
    assert("último item proximo != NULL", lista->ultimoItem->proximo == NULL);

    list_free(lista);

    return 0;
}

static char * test_list_add_inserindo_com_indice_invalido()
{
    list_t *lista = list_new();

    assert("índice -5 retorno != INDEX_ERROR", list_add(lista, "ola", -5) == INDEX_ERROR);
    assert("índice -1 retorno != INDEX_ERROR", list_add(lista, "ola", -1) == INDEX_ERROR);
    assert("índice 1 retorno != INDEX_ERROR",  list_add(lista, "ola", 1) == INDEX_ERROR);
    assert("índice 10 retorno != INDEX_ERROR", list_add(lista, "ola", 10) == INDEX_ERROR);

    list_free(lista);

    return 0;

}

//------------------------------------------------------------ list_add_end
static char * test_list_add_end_inserindo_tres_itens()
{
    list_t *lista = list_new();

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");
    list_add_end(lista, "oli");

    assert("tamanho da lista != 3", lista->tamanho == 3);
    assert("valor do primeiro item != ola", strcmp(lista->primeiroItem->valor, "ola") == 0);
    assert("valor do segundo item != ole", strcmp(lista->primeiroItem->proximo->valor, "ole") == 0);
    assert("valor do terceiro item != oli", strcmp(lista->primeiroItem->proximo->proximo->valor, "oli") == 0);
    assert("valor do último item != oli", strcmp(lista->ultimoItem->valor, "oli") == 0);
    assert("último item proximo != NULL", lista->ultimoItem->proximo == NULL);

    list_free(lista);

    return 0;
}

static char * test_list_add_end_inserindo_no_fim()
{
    list_t *lista = list_new();

    list_add(lista, "ola", 0);
    list_add(lista, "ole", 0);
    list_add(lista, "oli", 1);
    list_add_end(lista, "olu");

    assert("tamanho da lista != 4", lista->tamanho == 4);
    assert("valor do primeiro item != ole", strcmp(lista->primeiroItem->valor, "ole") == 0);
    assert("valor do segundo item != oli", strcmp(lista->primeiroItem->proximo->valor, "oli") == 0);
    assert("valor do terceiro item != ola", strcmp(lista->primeiroItem->proximo->proximo->valor, "ola") == 0);
    assert("valor do quarto item != olu", strcmp(lista->primeiroItem->proximo->proximo->proximo->valor, "olu") == 0);
    assert("valor do último item != olu", strcmp(lista->ultimoItem->valor, "olu") == 0);
    assert("último item proximo != NULL", lista->ultimoItem->proximo == NULL);

    list_free(lista);

    return 0;
}

//------------------------------------------------------------ list_free
static char * test_list_free()
{
    list_t *lista = list_new();

    list_add(lista, "ola", 0);
    list_add(lista, "ole", 0);
    list_add(lista, "oli", 0);

    list_free(lista);

    assert("primeiro item da lista != NULL", lista->primeiroItem == NULL);
    assert("último item da lista != NULL", lista->ultimoItem == NULL);

    return 0;
}

//------------------------------------------------------------ list_get
static char * test_list_get()
{
    list_t *lista = list_new();

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");
    list_add_end(lista, "oli");
    list_add_end(lista, "olo");
    list_add_end(lista, "olu");

    assert("lista(0) != \"ola\"", strcmp((char *) list_get(lista, 0), "ola") == 0);
    assert("lista(1) != \"ole\"", strcmp((char *) list_get(lista, 1), "ole") == 0);
    assert("lista(2) != \"oli\"", strcmp((char *) list_get(lista, 2), "oli") == 0);
    assert("lista(3) != \"olo\"", strcmp((char *) list_get(lista, 3), "olo") == 0);
    assert("lista(4) != \"olu\"", strcmp((char *) list_get(lista, 4), "olu") == 0);

    list_free(lista);

    return 0;
}

static char * test_list_get_com_indice_invalido()
{
    list_t *lista = list_new();

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");

    assert("get index -1 != NULL", (char *) list_get(lista, -1) == NULL);
    assert("get index 2 != NULL", (char *) list_get(lista, 2) == NULL);
    assert("get index 3 != NULL", (char *) list_get(lista, 3) == NULL);
    assert("get index 10 != NULL", (char *) list_get(lista, 10) == NULL);

    list_free(lista);

    return 0;
}

//------------------------------------------------------------ list_get_end
static char * test_list_get_end()
{
    list_t *lista = list_new();
    char *valor;

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");
    list_add_end(lista, "oli");

    valor = (char *) list_get_end(lista);

    assert("valor do último item != oli", strcmp(valor, "oli") == 0);

    list_free(lista);

    return 0;
}

static char * test_list_get_end_com_lista_vazia()
{
    list_t *lista = list_new();
    char *valor;

    valor = (char *) list_get_end(lista);

    assert("valor retornado != NULL", valor == NULL);

    list_free(lista);

    return 0;
}

//------------------------------------------------------------ list_remove
static char * test_list_remove_com_um_unico_item()
{
    list_t *lista = list_new();
    char *valor;

    list_add_end(lista, "ola");
    valor = (char *) list_remove(lista, 0);

    assert("lista tamanho != 0", lista->tamanho == 0);
    assert("valor != ola", strcmp(valor, "ola") == 0);
    assert("primeiro item da lista != NULL", lista->primeiroItem == NULL);
    assert("ultimo item da lista != NULL", lista->ultimoItem == NULL);

    list_free(lista);

    return 0;
}

static char * test_list_remove_no_inicio_da_lista()
{
    list_t *lista = list_new();
    char *valor;

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");
    list_add_end(lista, "oli");

    valor = (char *) list_remove(lista, 0);

    assert("lista tamanho != 2", lista->tamanho == 2);
    assert("primeiro item da lista != ole", strcmp(lista->primeiroItem->valor, "ole") == 0);
    assert("segundo item da lista != oli", strcmp(lista->primeiroItem->proximo->valor, "oli") == 0);
    assert("ultimo item da lista != oli", strcmp(lista->ultimoItem->valor, "oli") == 0);
    assert("ultimo item proximo != NULL", lista->ultimoItem->proximo == NULL);
    assert("valor retornado != ola", strcmp(valor, "ola") == 0);

    list_free(lista);

    return 0;
}

static char * test_list_remove_no_fim_da_lista()
{
    list_t *lista = list_new();
    char *valor;

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");
    list_add_end(lista, "oli");

    valor = (char *) list_remove(lista, 2);

    assert("lista tamanho != 2", lista->tamanho == 2);
    assert("primeiro item da lista != ola", strcmp(lista->primeiroItem->valor, "ola") == 0);
    assert("segundo item da lista != ole", strcmp(lista->primeiroItem->proximo->valor, "ole") == 0);
    assert("ultimo item da lista != ole", strcmp(lista->ultimoItem->valor, "ole") == 0);
    assert("ultimo item proximo != NULL", lista->ultimoItem->proximo == NULL);
    assert("valor retornado != oli", strcmp(valor, "oli") == 0);

    list_free(lista);

    return 0;
}

static char * test_list_remove_no_meio_da_lista()
{
    list_t *lista = list_new();
    char *valor;

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");
    list_add_end(lista, "oli");

    valor = (char *) list_remove(lista, 1);

    assert("lista tamanho != 2", lista->tamanho == 2);
    assert("primeiro item da lista != ola", strcmp(lista->primeiroItem->valor, "ola") == 0);
    assert("segundo item da lista != oli", strcmp(lista->primeiroItem->proximo->valor, "oli") == 0);
    assert("ultimo item da lista != oli", strcmp(lista->ultimoItem->valor, "oli") == 0);
    assert("ultimo item proximo != NULL", lista->ultimoItem->proximo == NULL);
    assert("valor retornado != ole", strcmp(valor, "ole") == 0);

    list_free(lista);

    return 0;
}

static char * test_list_remove_com_indices_invalidos()
{
    list_t *lista = list_new();

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");

    assert("remove index -10 != NULL", list_remove(lista, -10) == NULL);
    assert("remove index -1 != NULL", list_remove(lista, -1) == NULL);
    assert("remove index 2 != NULL", list_remove(lista, 2) == NULL);
    assert("remove index 3 != NULL", list_remove(lista, 3) == NULL);
    assert("remove index 10 != NULL", list_remove(lista, 10) == NULL);

    list_free(lista);

    return 0;
}

//------------------------------------------------------------ list_remove_end

static char * test_list_remove_end()
{
    list_t *lista = list_new();
    char *valor;

    list_add_end(lista, "ola");
    list_add_end(lista, "ole");

    valor = (char *) list_remove_end(lista);

    assert("valor retornado != ole", strcmp(valor, "ole") == 0);
    assert("tamanho da lista != 1", lista->tamanho == 1);

    list_free(lista);

    return 0;
}

static char * all_tests()
{
    // list_new
    run_test(test_list_new);

    // list_add
    run_test(test_list_add);
    run_test(test_list_add_com_dois_itens);
    run_test(test_list_add_inserindo_no_meio);
    run_test(test_list_add_inserindo_no_final);
    run_test(test_list_add_inserindo_com_indice_invalido);

    // list_add_end
    run_test(test_list_add_end_inserindo_tres_itens);
    run_test(test_list_add_end_inserindo_no_fim);

    // list_get
    run_test(test_list_get);
    run_test(test_list_get_com_indice_invalido);

    // list_get_end
    run_test(test_list_get_end);
    run_test(test_list_get_end_com_lista_vazia);

    // list_remove
    run_test(test_list_remove_com_um_unico_item);
    run_test(test_list_remove_no_inicio_da_lista);
    run_test(test_list_remove_no_fim_da_lista);
    run_test(test_list_remove_no_meio_da_lista);
    run_test(test_list_remove_com_indices_invalidos);

    // list_remove_end
    run_test(test_list_remove_end);

    // list_free
    run_test(test_list_free);

    return 0;
}

int main(void)
{
    char *result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    }
    else
    {
        printf("Bom trabalho, todos o testes passaram!\n");
    }

    printf("Quantidade de testes executados: %d\n", tests_run);
    printf("Quantidade de asserções: %d\n", assertions);

    return result != 0;
}
