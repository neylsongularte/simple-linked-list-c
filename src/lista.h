#define SUCCESS 0
#define INDEX_ERROR 1


// estrutura do node
typedef struct node_t {
    void *valor;
    struct node_t *proximo;
} node_t;

// estrutura da lista
typedef struct {
    node_t *primeiroItem;
    node_t *ultimoItem;
    int tamanho;
} list_t;


list_t * list_new(void);
void list_free(list_t *lista);

void * list_remove(list_t *lista, int indice);
void * list_remove_end(list_t *lista);

int list_add(list_t *lista, void *valor, int indice);
int list_add_end(list_t *lista, void *valor);

node_t * list_get_node(const list_t *lista, int indice);
node_t * list_get_node_end(const list_t *lista);

void * list_get(const list_t *lista, int indice);
void * list_get_end(const list_t *lista);
