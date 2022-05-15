#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INFINITY 10000

unsigned int *distance;
int *previous;
bool *visited;
unsigned int **predef_graph(unsigned int **graph)
{
    unsigned int pregraph[6][6] = {
        {0, 4, 4, 0, 0, 0},
        {4, 0, 2, 0, 0, 0},
        {4, 2, 0, 3, 2, 4},
        {0, 0, 3, 0, 0, 3},
        {0, 0, 2, 0, 0, 3},
        {0, 0, 4, 3, 3, 0}};
    int i = 0, j = 0;
    graph = malloc(6 * sizeof(unsigned int *));
    for (i = 0; i < 6; i++)
    {
        graph[i] = malloc(6 * sizeof(unsigned int));
        for (j = 0; j < 6; j++)
        {
            graph[i][j] = pregraph[i][j];
        }
    }
    return graph;
}

unsigned int **input_graph(unsigned int **graph, int vertices)
{
    int i = 0, j = 0;
    unsigned int weight;
    printf("Enter weight data for %d nodes[0 if nodes are not connected]\n", vertices);
    graph = malloc(vertices * sizeof(unsigned int *));
    for (i = 0; i < vertices; i++)
    {
        graph[i] = malloc(vertices * sizeof(unsigned int));
        graph[i][i] = 0;
    }
    for (i = 0; i < vertices; i++)
    {
        for (j = i + 1; j < vertices; j++)
        {
            printf("Enter non-negative weight from node %c to %c> ", 'A' + i, 'A' + j);
            scanf("%d", &weight);
            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }
    return graph;
}

void print_graph(unsigned int **graph, int vertices)
{
    int i = 0, j = 0;
    printf("  ");
    for (j = 0; j < vertices; j++)
    {
        printf("%*c ", 3, 'A' + j);
    }
    printf("\n");
    for (i = 0; i < vertices; i++)
    {
        printf("%c ", 'A' + i);
        for (j = 0; j < vertices; j++)
        {
            printf("%*d ", 3, graph[i][j]);
        }
        printf("\n");
    }
}

void print_shortest_path(int src, int dst)
{
    if (src == dst)
        printf("%c", 'A', dst);
    else
    {
        print_shortest_path(src, previous[dst]);
        printf(" --> %c", 'A' + dst);
    }
}

void bellman_ford(unsigned int **graph, int vertices, int src, int dst)
{
    int i = 0, j = 0, k = 0;
    int mindist = INFINITY, minindex;
    int vertex = dst;
    distance = calloc(vertices, sizeof(unsigned int));
    previous = calloc(vertices, sizeof(int));
    visited = calloc(vertices, sizeof(bool));
    for (i = 0; i < vertices; i++)
    {
        distance[i] = INFINITY;
        previous[i] = -1;
    }
    distance[src] = 0;
    for (k = 0; k < vertices - 1; k++)
    {
        for (i = 0; i < vertices; i++)
        {
            for (j = 0; j < vertices; j++)
            {
                if (!graph[i][j])
                    continue;
                if (distance[i] + graph[i][j] < distance[j])
                {
                    distance[j] = distance[i] + graph[i][j];
                    previous[j] = i;
                }
            }
        }
    }
    printf("Shortest path is: \n");
    print_shortest_path(src, dst);
    printf("\nDistance from %c to %c is: %d", 'A' + src, 'A' + dst, distance[dst]);
}

void main(int argc, char *argv[])
{
    unsigned int **graph;
    char choice;
    int i = 0, j = 0, weight;
    int vertices;
    int src = 0, dst = 5;
    printf("Use pre-defined graph? [Y/y]> ");
    scanf("%c", &choice);
    if (choice != 'y' && choice != 'Y')
    {
        printf("Enter number of vertices> ");
        scanf("%d", &vertices);
        graph = input_graph(graph, vertices);
        getchar();
        printf("Enter start node from %c to %c> ", 'A', 'A' + vertices - 1);
        scanf("%c", &choice);
        if (choice >= 'A' && choice <= 'Z')
        {
            src = choice - 'A';
        }
        else
        {
            src = choice - 'a';
        }
        printf("Enter end node from %c to %c> ", 'A', 'A' + vertices - 1);
        fflush(stdout);
        scanf(" %c", &choice);
        if (choice >= 'A' && choice <= 'Z')
        {
            dst = choice - 'A';
        }
        else
        {
            dst = choice - 'a';
        }
    }
    else
    {
        vertices = 6;
        graph = predef_graph(graph);
    }
    print_graph(graph, vertices);
    bellman_ford(graph, vertices, src, dst);
}