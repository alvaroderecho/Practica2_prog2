#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define FAIL 1

int main(int argc, char *argv[])
{

    Graph *g;
    FILE *f;
    int i;

    if (argc != 4)
    {
        printf("Wrong number of input arguments.\n");
        return FAIL;
    }

    if (strcmp(argv[1], "g2.txt"))
    {
        printf("Error opening file: %s\n",argv[1]);
        return FAIL;
    }

    if ((g = graph_init()) == NULL)
        return FAIL;

    if ((f = fopen(argv[1], "r")) == NULL)
    {
        graph_free(g);
        return FAIL;
    }

    if ((graph_readFromFile(f, g)) == ERROR)
    {
        graph_free(g);
        fclose(f);
        return FAIL;
    }
    printf("Input graph: \n");
    if ((graph_print(stdout, g)) == ERROR)
    {
        graph_free(g);
        fclose(f);
        return FAIL;
    }

    printf("From Vertex id: %ld\n", atol(argv[2]));
    printf("To Vertex id: %ld\n", atol(argv[3]));
    printf("Output: \n");

    if ((graph_depthSearch(g, atol(argv[2]), atol(argv[3]))) == ERROR)
    {
        graph_free(g);
        fclose(f);
        printf("Error in graph search algorith.\n");
        return FAIL;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {

        if ((vertex_getState(graph_get_vertex_fromIx(g, i)) == BLACK) && !(i % 2))
        {
            vertex_print(stdout, graph_get_vertex_fromIx(g, i));
            printf("\n");
        }
    }
    graph_free(g);
    fclose(f);

    return 0;
}