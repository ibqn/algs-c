#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct node_t node;

struct node_t {
    void *data;
    node *next;
};

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

circular_list_destroy(circular_list *list) {


    if (list) {
        free(list);
    }
}

int main(int argc, char **argv)
{
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


    circular_list_destroy(list);

    return EXIT_SUCCESS;
}
