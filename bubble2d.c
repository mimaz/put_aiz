#include <stdlib.h>
#include <stdio.h>

void swap_ints(int *p, int *q)
{
    int t = *p;

    *p = *q;
    *q = t;
}

struct matrix
{
    int **matrix;
    int columns;
    int rows;
};

struct matrix *create_matrix(int columns, int rows)
{
    struct matrix *m = malloc(sizeof(struct matrix));

    m->matrix = malloc(sizeof(int *) * rows);
    m->columns = columns;
    m->rows = rows;

    for (int i = 0; i < rows; i++)
        m->matrix[i] = calloc(sizeof(int), columns);

    return m;
}

void delete_matrix(struct matrix *m)
{
    for (int i = 0; i < m->rows; i++)
        free(m->matrix[i]);

    free(m->matrix);
    free(m);
}

struct matrix *create_random_matrix(int columns, int rows)
{
    struct matrix *m = create_matrix(columns, rows);

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
            m->matrix[y][x] = rand() % 90 + 10;

    return m;
}

void print_matrix(struct matrix *m)
{
    for (int y = 0; y < m->rows; y++)
    {
        printf("[");

        for (int x = 0; x < m->columns; x++)
        {
            if (x > 0)
                printf(", ");

            printf("%d", m->matrix[y][x]);
        }

        printf("]\n");
    }
}

int *get_value(struct matrix *m, int idx)
{
    int y = idx / m->columns;
    int x = idx % m->columns;

    return &m->matrix[y][x];
}

void bubble2d(struct matrix *m)
{
    int count = m->columns * m->rows;

    int repeat;

    do {
        repeat = 0;

        for (int i = 1; i < count; i++)
        {
            int *f = get_value(m, i - 1);
            int *s = get_value(m, i);

            if (*s < *f)
            {
                repeat = 1;
                swap_ints(f, s);
            }
        }
    } while(repeat);
}

int main()
{
    struct matrix *m = create_random_matrix(3, 4);


    printf("random matrix:\n");
    print_matrix(m);

    bubble2d(m);

    printf("\nsorted:\n");
    print_matrix(m);


    delete_matrix(m);
    return 0;
}
