#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>


typedef struct node_t node;

struct node_t {
    void *data;
    node *next;
};

node* node_new(void *data) {
    node *tmp = malloc(sizeof(node));

    tmp->data = data;
    tmp->next = NULL;

    return tmp;
}

typedef void (*data_free_fn)(void *);

void node_destroy(node *n, data_free_fn data_free) {
    data_free(n->data);
    free(n);
}

typedef struct circular_list_t circular_list;

struct circular_list_t {
    int size;
    node *tail;
};

circular_list* circular_list_new(void) {
    circular_list* tmp = malloc(sizeof(circular_list));

    tmp->size = 0;
    tmp->tail = NULL;
    return tmp;
}

void circular_list_add(circular_list *list, void *data) {
    assert(data != NULL);

    node *tmp = node_new(data);

    if (list->tail) {
        tmp->next = list->tail->next;
        list->tail->next = tmp;
        list->tail = tmp;
    } else {
        list->tail = tmp;
        tmp->next = tmp;
    }

    list->size++;
}

node* circular_list_eliminate_every(circular_list *list, const int *num, data_free_fn data_free) {
    assert(list != NULL);
    assert(list->tail != NULL);

    node *n = list->tail;

    node* c;
    while (n != n->next) {
        for (int i = 1; i < *num; i++) {
            n = n->next;
        }
        c = n->next;
        printf("%d ", *((int *)c->data));
        n->next = n->next->next;
        node_destroy(c, data_free);
    }
    printf("done\n");

    list->tail = n;

    return n;
}

node* circular_list_get_first(circular_list *list) {
    assert(list != NULL);
    assert(list->tail != NULL);

    return list->tail->next;
}

int circular_list_get_size(circular_list *list) {
    assert(list != NULL);

    return list->size;
}

void circular_list_destroy(circular_list *list, data_free_fn data_free) {
    assert(list != NULL);

    node *n = list->tail;

    free(list);

    if (n == NULL) {
        return;
    }

    node *c;
    node *tail = n;
    do {
        c = n;
        n = n->next;
        node_destroy(c, data_free);
    } while (n != tail);
}

int main(int argc, char **argv) {
    int N = 41;
    int M = 3;

    fprintf(stdout, "%s\n", "Josephus problem");

    /* Stwitch to the non-blocking stdin */
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);

    /* Obtain N */
    if (argc >= 2) {
        sscanf(argv[1], "%d", &N);
        printf("N is set to %d\n", N);
    } else if (scanf("%d", &N) == 1) {
        printf("Received N from standard input, which is set to %d\n", N);
    } else {
        printf("Using default value for N which is set to %d\n", N);
    }

    /* Obtain M */
    if (argc == 3) {
        sscanf(argv[2], "%d", &M);
        printf("M is set to %d\n", M);
    } else if (scanf("%d", &M) == 1) {
        printf("Received M from standard input, which is set to %d\n", M);
    } else {
        printf("Using default value for M which is set to %d\n", M);
    }

    circular_list *list = circular_list_new();

    int *data;
    for(int i = 1; i <= N; i++) {
        data = malloc(sizeof(int));
        *data = i;

        // printf("%d ", *data);

        circular_list_add(list, (void *)data);
    }
    // printf("done\n");

    int size = circular_list_get_size(list);
    printf("Created circular list of size %d\n", size);

    /* Cyrcle once */
    node *first = circular_list_get_first(list);
    node *n = first;
    do {
        printf("%d ", *((int *)n->data));
        n = n->next;
    } while (n != first);

    printf("done\n");

    node *last = circular_list_eliminate_every(list, &M, free);
    printf("Last element is %d ", *((int *)last->data));

    circular_list_destroy(list, free);

    return EXIT_SUCCESS;
}
