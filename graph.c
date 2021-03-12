#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_VTX 4096
#define NO_ID -1

struct _Graph
{
    Vertex *vertices[MAX_VTX];          /*!<Arraywiththegraphvertices*/
    Bool connections[MAX_VTX][MAX_VTX]; /*!<Adjacencymatrix*/
    int num_vertices;                   /*!<Totalnumberofvertices*/
    int num_edges;                      /*!<Totalnumberofedges*/
};
Graph *graph_init()
{
    Graph *g;
    int i, j;
    g = (Graph *)malloc(sizeof(Graph));
    if (g == NULL)
        return NULL;
    g->num_edges = 0;
    g->num_vertices = 0;
    for (i = 0; i < MAX_VTX; i++)
    {        
        for (j = 0; j < MAX_VTX; j++)
        {
            g->connections[i][j] = FALSE;
        }
    }
    return g;
}
void graph_free(Graph *g)
{
    int i;
    for (i=0;i<MAX_VTX;i++) {
        vertex_free(g->vertices[i]);
    }
    free(g);
}

Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *v;
    int i;
    v = vertex_initFromString(desc);
    if (v == NULL)
        return ERROR;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (v == g->vertices[i])
            return ERROR;
       
    }
    g->vertices[g->num_vertices] = v;
    g->num_vertices++;        
    return OK;    
}

Status graph_newEdge(Graph *g, long orig, long dest)
{
    int i,j;
    if (!g || orig == dest) 
        return ERROR;
    for (i = 0; i < MAX_VTX; i++)
    {
        if (vertex_getId(g->vertices[i]) == orig)
        {
            for (j = 0; j < MAX_VTX; j++)
            {
                if (vertex_getId(g->vertices[j]) == dest)
                {
                    g->connections[i][j] = TRUE;
                    return OK;
                }
            }
        }
    }
    return ERROR;
}
Bool graph_contains(const Graph *g, long id)
{
    int i;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
            return TRUE;
        else
            return FALSE;
    }
    return FALSE;
}
int graph_getNumberOfVertices(const Graph *g)
{
    if (g == NULL)
        return NO_ID;
    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g)
{
    if (g == NULL)
        return NO_ID;
    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    int i, j;

    if (!g || orig == dest)
        return FALSE;

    for (i = 0; i < MAX_VTX; i++)
    {
        if (vertex_getId(g->vertices[i]) == orig)
        {
            for (j = 0; j < MAX_VTX; j++)
            {
                if (vertex_getId(g->vertices[j]) == dest)
                {
                    return g->connections[i][j];
                }
            }
        }
    }
    return FALSE;
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int i, j, num_connections;
    if (!g)
        return NO_ID;

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            for (j = 0, num_connections = 0; j < graph_getNumberOfVertices(g); j++)
            {
                if (g->connections[i][j] == TRUE)
                {
                    num_connections++;
                }
            }
            return num_connections;
        }
    }

    return 0;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{
    int num_connections, i, j,flag;
    long *conn;
    if (!g)
        return NULL;

    if ((num_connections = graph_getNumberOfConnectionsFromId(g, id)) == NO_ID)
        return NULL;

    if ((conn = (long *)malloc(sizeof(long) * num_connections)) == NULL)
        return NULL;

    for (i = 0,flag=0; i < graph_getNumberOfVertices(g); i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            for (j = 0; j < graph_getNumberOfVertices(g); j++)
            {
                if (g->connections[i][j] == TRUE)
                {
                    conn[flag] = vertex_getId(g->vertices[j]);
                    flag++;
                }
            }
            return conn;
        }
    }
    return NULL;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i, j, num_connections;
    if (!g)
        return NO_ID;

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            for (j = 0, num_connections = 0; j < graph_getNumberOfVertices(g); j++)
            {
                if (g->connections[i][j] == TRUE)
                {
                    num_connections++;
                }
            }
            return num_connections;
        }
    }

    return NO_ID;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int num_connections, i, j,flag;
    long *conn;
    if (!g)
        return NULL;

    if ((num_connections = graph_getNumberOfConnectionsFromTag(g, tag)) == NO_ID)
        return NULL;

    if ((conn = (long *)malloc(sizeof(long) * num_connections)) == NULL)
        return NULL;

    for (i = 0,flag=0; i < graph_getNumberOfVertices(g); i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            for (j = 0; j < graph_getNumberOfVertices(g); j++)
            {
                if (g->connections[i][j] == TRUE)
                {
                    conn[flag] = vertex_getId(g->vertices[j]);
                    flag++;
                }
            }
            return conn;
        }
    }
    return NULL;
}

int graph_print(FILE *pf, const Graph *g)
{
    int i, j, num_car;

    for (i = 0, num_car = 0; i < graph_getNumberOfVertices(g); i++)
    {
        fprintf(pf, "[%d, %s, 0]: ", i + 1, vertex_getTag(g->vertices[i]));
        num_car += strlen(vertex_getTag(g->vertices[i]));
 
        if (graph_getNumberOfConnectionsFromId(g, vertex_getId(g->vertices[i])) > 0)
        {
            for (j = 0; j<graph_getNumberOfVertices(g); j++)
            {
                if (graph_connectionExists(g, vertex_getId(g->vertices[i]), vertex_getId(g->vertices[j])) == TRUE)
                {
                    fprintf(pf, "[%d, %s, 0] ", j + 1, vertex_getTag(g->vertices[j]));
                    num_car += strlen(vertex_getTag(g->vertices[j]));
                }
            }
        }
        fprintf(pf, "\n");
    }
    return num_car;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{
    int i,num_v;
    long orig,dest;
    char flag[TAG_LENGTH];

    for(i=0;fscanf(fin, "%d", &num_v)==1;i++){        
    }
    
    for (i = 0; i<num_v; i++)
    {
        
        fgets(flag,64,fin);
        if ((graph_newVertex(g,flag)) == ERROR) return ERROR;
        
    }
    for (i = 0; fscanf(fin, "%ld %ld", &orig, &dest) == 2; i++)
    {
        graph_newEdge(g,orig,dest);
    }
    return OK;
}