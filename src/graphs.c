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
 * @brief Build a breadth-first tree from a graph
 * 
 * @param g pointer to graph
 * @param root root of the tree
 * @return bftree_t* 
 */
bftree_t* bfs(graph_t* g, int root)
{
    bool visited[g->nv];
    int u;
    struct node* tmp;
    queue_t q;

    bftree_t* bftree = malloc(sizeof(bftree_t));

    bftree->dist = (int*)malloc(g->nv * sizeof(int));
    bftree->parent = (int*)malloc(g->nv * sizeof(int));

    for(int j=0; j < g->nv; j++)
    {
        bftree->dist[j] = INT_MAX;
        bftree->parent[j] = -1;
        visited[j] = false;
    }

    queue(&q,g->nv);
    visited[root] = true;
    bftree->dist[root] = 0;

    enqueue(&q,root);
    while(q.ctr)
    {
        dequeue(&q,&u);
        tmp = g->adj[u];
        while(tmp)
        {
            if(visited[tmp->v] == false)
            {
                visited[tmp->v] = true;
                bftree->dist[tmp->v] = bftree->dist[u] + 1;
                bftree->parent[tmp->v] = u;
                enqueue(&q,tmp->v);
            }
            tmp = tmp->next;
        }

    }
    queue_delete(&q);
    return bftree;
}
/**
 * @brief Prints the path between two nodes in a Breadth-First tree
 * 
 * @param g pointer to bftree
 * @param src source node
 * @param dst destination node
 */
static
void print_path_bftree(bftree_t* bftree, int src , int dst)
{
    static int n = 0;
    n++;
    if(src == dst)
    {
        printf("%d -> ", src);
        n--;
    } 

    else if (bftree->parent[dst] == -1)
    {   
        printf("no path from %d to %d \n", src, dst);
        return;
    }
    else
    {
        print_path_bftree(bftree, src, bftree->parent[dst]);
        n--;
        if(n)
           printf("%d -> ", dst);
        else
           printf("%d \n", dst);
    }    

}

/**
 * @brief Prints the shortest path between two nodes in a graph
 * 
 * @param g pointer to graph
 * @param src source node
 * @param dst destination node
 */
void shortest_path_bfs(graph_t* g, int src , int dst)
{
    bftree_t* bftree = bfs(g, src);
    print_path_bftree(bftree, src, dst);
}
