/**
 * @file    graphs.h
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    15-08-2021
 *
 */
#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <stdbool.h>

/**
 * @brief Adjacency list node
 * 
 */
struct node{
    int v;                  // successor vertex                             
    int w;                  // edge weight                                  
    struct node* next;      // next edge on linked list of adjacencies       
};

/**
 * @brief Adjacency list representation of graph
 * 
 */
typedef struct graph_s{
    int nv;                 // number of vertices       
    bool dir;               // direction flag          
    struct node** adj;      // array of adjacency linked lists  
}graph_t;


/**
 * @brief Create a graph object
 * 
 * @param nv number of vertices
 * @param dir direction flag (true if graph is directed)
 * @return graph_t*
 */
graph_t* create_graph(int nv, bool dir);

/**
 * @brief 
 * 
 * @param g 
 */
void destroy_graph(graph_t* g);

/**
 * @brief Add an edge to a graph. 
 * If graph is not directed this function will
 * add second edge from dst to src.
 * 
 * @param g pointer to graph
 * @param src source vertex
 * @param dst destine vertex
 * @param w edge weight
 */
void add_edge(graph_t* g, int src, int dst, int w);

/**
 * @brief Add a vertex to a graph
 * 
 * @param g pointer to graph
 */
void add_vertex(graph_t* g);

/**
 * @brief Print a graph in adjacency list representation
 * 
 * @param g pointer to graph
 */
void print_graph(graph_t* g);


/**
 * @brief Breadth-First Tree representation 
 * using one array for parent nodes and another for distance from root node.
 * 
 */
typedef struct bftree_s
{
     int* dist;   /* Array of distance from root note*/
     int* parent; /* Array of parent nodes. Each index is a node and the key is its parent node. Root node has parent -1*/

}bftree_t;


/**
 * @brief Build a breadth-first tree from a graph
 * 
 * @param g pointer to graph
 * @param root root of the tree
 * @return bftree_t* 
 */
bftree_t* bfs(graph_t* g, int root);

/**
 * @brief Prints the shortest path between two nodes in a graph
 * 
 * @param g pointer to graph
 * @param src source node
 * @param dst destination node
 */
void shortest_path_bfs(graph_t* g, int src , int dst);

#endif