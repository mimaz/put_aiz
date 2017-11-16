#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct graph
{
    int vno;
    int **matrix;
};

struct graph *make_graph(int vno)
{
    struct graph *g = malloc(sizeof(struct graph));

    g->vno = vno;
    g->matrix = malloc(sizeof(int *) * vno);

    for (int i = 0; i < vno; i++)
        g->matrix[i] = calloc(sizeof(int), vno);
    
    return g;
}

void delete_graph(struct graph *g)
{
    for (int i = 0; i < g->vno; i++)
        free(g->matrix[i]);

    free(g->matrix);
    free(g);
}

void connect_vertices(struct graph *g, int p, int q)
{
    g->matrix[p][q] = 1;
    g->matrix[q][p] = 1;
}

void print_graph(struct graph *g)
{
    for (int i = 0; i < g->vno; i++)
    {
        printf("[");

        for (int j = 0; j < g->vno; j++)
        {
            if (j > 0)
                printf(" ");
            
            printf("%d", g->matrix[i][j]);
        }

        printf("]\n");
    }
}

struct graph *make_graph_gnp(int n, float p)
{
    // create empty graph
    struct graph *g = make_graph(n);

    // for each possibly connection
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
        {
            // randomize number from range 0..1
            float r = (float) rand() / RAND_MAX;

            // make connection if r is less than p
            if (r < p)
                connect_vertices(g, j, i);
        }

    return g;
}

struct graph *make_graph_gnk(int n, int k)
{
    struct graph *g = make_graph(n);

    // create list of all possible connections
    struct pair 
    {
        int p, q;
    } list[n * n];

    int listsiz = 0;

    // generate the list
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            list[listsiz++] = (struct pair) { i, j };

    // randomize connection from list k-times
    for (int i = 0; i < k; i++)
    {
        int idx = rand() % listsiz;

        int p = list[idx].p;
        int q = list[idx].q;

        connect_vertices(g, p, q);

        // remove already used connection
        list[idx] = list[--listsiz];
    }

    return g;
}

int main()
{
    srand(clock());


    int n = 6;
    float p = 0.25;
    int k = 6;



    struct graph *g = make_graph_gnp(n, p);

    printf("\nG(n, p) graph with n = %d, p = %f\n", n, p);
    print_graph(g);

    delete_graph(g);




    g = make_graph_gnk(n, k);

    printf("\nG(n, k) graph with n = %d, k = %d\n", n, k);
    print_graph(g);

    delete_graph(g);


    return 0;
}
