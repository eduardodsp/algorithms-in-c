/**
 * @file    graphs.c
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    15-08-2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../inc/graphs.h"
#include "../inc/queue.h"
#include "../inc/heap.h"

/**
 * @brief Create a graph object
 * 
 * @param nv number of vertices
 * @param dir direction flag (true if graph is directed)
 * @return graph_t*
 */
graph_t* create_graph(int nv, bool dir)
{
    graph_t* g = malloc(sizeof(graph_t));

    g->dir = dir;
    g->nv = nv;
    g->adj = calloc(nv, sizeof(struct node));

    return g;
}

/**
 * @brief recursively deallocate nodes in an adjacency list
 * 
 * @param n first node in the linked list of adjacencies
 */
static
void dealloc_node(struct node* n)
{
    if(n)
    {
        dealloc_node(n->next);
        free(n);
    }
}

void destroy_graph(graph_t* g)
{
    for (int v = 0; v < g->nv; v++) 
    {
        struct node* tmp = g->adj[v];

        dealloc_node(tmp);
    }

    free(g->adj);
    free(g);
}
    
/**
 * @brief Add an edge to a graph. 
 * If graph is not directed this function will
 * add second edge from dst to src.
 * 
 * @param g pointer to graph
 * @param src source vertex
 * @param dst destination vertex
 * @param w edge weight
 */
void add_edge(graph_t* g, int src, int dst, int w)
{
    if(g == (void*)0)
        return;

    struct node* node = malloc(sizeof(struct node));
    node->v = dst;
    node->w = w;
    node->next = g->adj[src];
    g->adj[src] = node;

    if(!g->dir)
    {
        struct node* dir_node = malloc(sizeof(struct node));
        dir_node->v = src;
        dir_node->w = w;
        dir_node->next = g->adj[dst];
        g->adj[dst] = dir_node;
    }
}

/**
 * @brief Add a vertex to a graph
 * 
 * @param g pointer to graph
 */
void add_vertex(graph_t* g)
{    
    g->nv++;
    struct node** adj = calloc(g->nv, sizeof(struct node));

    for(int i=0; i < (g->nv-1) ;i++)
    {
        adj[i] = g->adj[i];
    }
    free(g->adj);

    g->adj = calloc(g->nv, sizeof(struct node));
    for(int i=0; i < (g->nv-1) ;i++)
    {
        g->adj[i] = adj[i];
    }
    free(adj);
}

/**
 * @brief Print a graph in adjacency list representation
 * 
 * @param g pointer to graph
 */
void print_graph(graph_t* g) 
{ 
    for (int v = 0; v < g->nv; v++) 
    {
    struct node* tmp = g->adj[v];

    printf("\n Vertex %d: \n ", v);

    while (tmp) 
    {
        printf("(%d)%d -> ", tmp->w, tmp->v);
        tmp = tmp->next;
    }

    printf("\n");
    }
}

/**
 * @brief Solves single source shortest path problem on an unweighted directed graph
 * 
 * @param g pointer to graph
 * @param src source node
 * @return sssp_t* 
 */
sssp_t* bfs(graph_t* g, int src)
{
    bool visited[g->nv];
    int u;
    struct node* tmp;
    queue_t q;

    sssp_t* sssp = malloc(sizeof(sssp_t));

    sssp->cost = (int*)malloc(g->nv * sizeof(int));
    sssp->prev = (int*)malloc(g->nv * sizeof(int));

    for(int j=0; j < g->nv; j++)
    {
        sssp->cost[j] = INT_MAX;
        sssp->prev[j] = -1;
        visited[j] = false;
    }

    queue(&q,g->nv);
    visited[src] = true;
    sssp->cost[src] = 0;

    enqueue(&q,src);
    while(q.ctr)
    {
        dequeue(&q,&u);
        tmp = g->adj[u];
        while(tmp)
        {
            if(visited[tmp->v] == false)
            {
                visited[tmp->v] = true;
                sssp->cost[tmp->v] = sssp->cost[u] + 1;
                sssp->prev[tmp->v] = u;
                enqueue(&q,tmp->v);
            }
            tmp = tmp->next;
        }

    }
    queue_delete(&q);
    return sssp;
}
/**
 * @brief Prints the path between two nodes in a single source shortest path array
 * 
 * @param g pointer to single source shortest path structure
 * @param src source node
 * @param dst destination node
 */
static
void print_shortest_path(sssp_t* sssp, int src , int dst)
{
    static int n = 0;
    n++;
    if(src == dst)
    {
        printf("%d -> ", src);
        n--;
    } 

    else if (sssp->prev[dst] == -1)
    {   
        printf("no path from %d to %d \n", src, dst);
        return;
    }
    else
    {
        print_shortest_path(sssp, src, sssp->prev[dst]);
        n--;
        if(n)
           printf("%d -> ", dst);
        else
           printf("%d \n", dst);
    }    

}


/**
 * @brief Finds the shortest path from node src to node dst in a positively weighted directed graph
 * using Dijkstras algorithm
 * 
 * @param g pointer to graph
 * @param src source node
 * @return sssp_t* 
 */
sssp_t* dijkstra(graph_t* g, int src)
{
    heap_t* heap;
    key_value_t item;
    struct node* tmp;
    int u,i;

    sssp_t* sssp = malloc(sizeof(sssp_t));

    sssp->cost = (int*)malloc(g->nv * sizeof(int));
    sssp->prev = (int*)malloc(g->nv * sizeof(int));

    for(int j=0; j < g->nv; j++)
    {
        sssp->cost[j] = INT_MAX;
        sssp->prev[j] = -1;
    }
    sssp->cost[src] = 0;

    heap = min_heap(g->nv);    
    for(int j=0; j < g->nv; j++)
    {
        min_insert(heap, j, sssp->cost[j]);
    }

    while(heap->ctr != 0)
    {
        if(extract_min(heap, &item) == 0)
        {
            return NULL;
        }
        u = item.key;
        tmp = g->adj[u];

        //for each vertex v ∈ G.Adj[u]
        while(tmp)
        {
            //relax
            if(sssp->cost[u] + tmp->w < sssp->cost[tmp->v])
            {
                sssp->cost[tmp->v] = sssp->cost[u] + tmp->w ;
                sssp->prev[tmp->v] = u;
                min_decrease_key(heap, tmp->v,sssp->cost[tmp->v]);
            }

            tmp = tmp->next;
        }
    }

    return sssp;
}


/**
 * @brief Finds the shortest path from node src to node dst in a weighted directed graph
 * using Bellman-Ford's algorithm
 * 
 * @param g pointer to graph
 * @param src source node
 * @return An sssp object if no negative cycles are found, NULL if a negative cycle is found 
 */
sssp_t* bellman_ford(graph_t* g, int src)
{
    struct node* tmp;
    sssp_t* sssp = malloc(sizeof(sssp_t));
    sssp->cost = (int*)malloc(g->nv * sizeof(int));
    sssp->prev = (int*)malloc(g->nv * sizeof(int));

    for(int j=0; j < g->nv; j++)
    {
        sssp->cost[j] = INT_MAX;
        sssp->prev[j] = -1;
    }

    sssp->cost[src] = 0;


    for(int i=0; i < g->nv; i++)
    {

        //foreach (u,v) ∈ E
        for(int u = 0; u < g->nv; u++)
        {
            tmp = g->adj[u];
            while(tmp)
            {
                //relax
                if(sssp->cost[u] + tmp->w < sssp->cost[tmp->v])
                {
                    sssp->cost[tmp->v] = sssp->cost[u] + tmp->w ;
                    sssp->prev[tmp->v] = u;
                }

                tmp = tmp->next;
            }
        }
    }

    //foreach (u,v) ∈ E
    for(int u = 0; u < g->nv; u++)
    {
        tmp = g->adj[u];
        while(tmp)
        {
            //relax
            if(sssp->cost[u] + tmp->w < sssp->cost[tmp->v])
            {
                free(sssp->cost);
                free(sssp->prev);
                free(sssp);

                return NULL;
            }

            tmp = tmp->next;
        }
    }

    return sssp;
}


/**
 * @brief Prints the shortest path between two nodes in a graph
 * 
 * @param g pointer to graph
 * @param src source node
 * @param dst destination node
 * @param algo algorithm to use. Options: USE_BFS (only unweighted graphs), USE_DIJKSTRA, USE_BELLMAN_FORD

 * @return TRUE if successful, FALSE if failed
 */
bool shortest_path(graph_t* g, int src , int dst, int algo)
{
    sssp_t* sssp = NULL;

    switch(algo)
    {
        case USE_BFS:
            sssp = bfs(g, src);
        break;

        case USE_BELLMAN_FORD:
            sssp = bellman_ford(g, src);

        break;
        
        case USE_DIJKSTRA:
            sssp = dijkstra(g, src);
        break;
    }

    if(sssp == NULL)
        return false;
        
    print_shortest_path(sssp, src, dst);
    return true;
}