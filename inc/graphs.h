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


#define DIRECTED true
#define UNDIRECTED false

#define USE_BFS             0
#define USE_DIJKSTRA        1
#define USE_BELLMAN_FORD    2


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
 * @brief Single-Source Shortest Path structure
 * that contains information about shortest path from one vertex to all other vertices on a graph
 * 
 */
typedef struct sssp_s
{
     int* cost;   /* Array of cost, or distance, from source node*/
     int* prev;   /* Array of previous nodes. Each index is a node and the key is its 
                     previous node on the path. Root node has parent -1*/

}sssp_t;

/**
 * @brief Solves single source shortest path problem on an unweighted directed graph
 * 
 * @param g pointer to graph
 * @param src source node
 * @return sssp_t* 
 */
sssp_t* bfs(graph_t* g, int src);


/**
 * @brief Finds the shortest path from node src to node dst in a positively weighted directed graph
 * using Dijkstras algorithm
 * 
 * @param g pointer to graph
 * @param src source node
 * @return sssp_t* 
 */
sssp_t* dijkstra(graph_t* g, int src);


/**
 * @brief Finds the shortest path from node src to node dst in a weighted directed graph
 * using Bellman-Ford's algorithm
 * 
 * @param g pointer to graph
 * @param src source node
 * @return An sssp object if no negative cycles are found, NULL if a negative cycle is found 
 */
sssp_t* bellman_ford(graph_t* g, int src);

/**
 * @brief Prints the shortest path between two nodes in a graph
 * 
 * @param g pointer to graph
 * @param src source node
 * @param dst destination node
 * @param algo algorithm to use. Options: USE_BFS (only unweighted graphs), USE_DIJKSTRA, USE_BELLMAN_FORD

 * @return TRUE if successful, FALSE if failed
 */
bool shortest_path(graph_t* g, int src , int dst, int algo);
#endif