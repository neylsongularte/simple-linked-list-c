
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
int list_add(list_t *lista, void *valor);
node_t * list_get(const list_t *lista, register int indice);
node_t * node_new(void);
