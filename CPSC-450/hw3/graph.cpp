//----------------------------------------------------------------------
// NAME: Stella Beemer
// FILE: graph.cpp
// DATE: Spring 2021
// DESC: Adjacency list implementation of the graph interface
//----------------------------------------------------------------------

#include "graph.h"
#include <queue>
#include <list>
#include <unordered_map>
#include <iostream>

// shortened hash-table map name for convenience
typedef std::unordered_map<int,int> Map;

//----------------------------------------------------------------------
// Breadth-first search from a given source vertex. 
//
// Inputs: 
//   dir -- true if directed
//   src -- the source vertex
// Outputs:
//   tree -- search tree that maps vertices found during bfs from the
//           source to their parent vertices
//----------------------------------------------------------------------
void Graph::bfs(bool dir, int src, Map& tree) const {
    tree[src] = -1;
    std::queue<int> q;
    q.push(src);
    int u;
    std::list<int> adj;
    while(!q.empty()) {
        u = q.front();
        q.pop();
        adj.clear();
        if(dir) {
            connected_to(u, adj);
        } else {
            adjacent(u, adj); 
        }
        for(int v: adj) {
            if(tree.count(v) == 0) {
                tree[v] = u;
                q.push(v);
            }
        }
    }
}
  
//----------------------------------------------------------------------
// Shortest path length from source to destination vertices.
//
// Conditions:
//   The source and destination vertices must be unique.  
// Inputs:
//   dir -- true if directed
//   src -- the vertex starting the path
//   dst -- the vertex ending the path
// Outputs:
//   path -- sequence of nodes that define the shortest path
//----------------------------------------------------------------------
void Graph::shortest_path_length(bool dir, int src, int dst, std::list<int>& path) const {
    Map bfs_map;
    bfs(dir, src, bfs_map);
    int i = dst;
    while(i != src) {
        path.push_front(i);
        i = bfs_map[i];
    }
    path.push_front(i);
}

//----------------------------------------------------------------------
// Find connected components based on breadth-first search.
//
// Conditions:
//   Finds strongly connected components in an undirected graph and
//   weakly-connected components in a directed graph.
// Inputs:
//   None
// Outputs: 
//   components -- mapping from each graph vertex to its corresponding
//                 component number where component numbers range from
//                 0 to c-1 (for c components)
//----------------------------------------------------------------------
void Graph::bfs_connected_components(Map& components) const {
    std::queue<int> q;
    int u;
    int c = 0;
    std::list<int> adj;
    for(int i = 0; i < vertex_count(); ++i) {
        if(components.count(i) == 0) {
            components[i] = c;
            q.push(i);
            while(!q.empty()) {
                u = q.front();
                q.pop();
                adj.clear();
                adjacent(u, adj);
                for(int v: adj) {
                    if(components.count(v) == 0) {
                        components[v] = c;
                        q.push(v);
                    }
                }
            }
            c++;
        }
    }
    
}

//----------------------------------------------------------------------
// Determine if the graph is bipartite (i.e., 2-colorable)
//
// Inputs:
//   None
// Outputs:
//   returns  -- true if the graph is bipartite, false otherwise
//   coloring -- mapping from each graph vertex to its corresponding
//               color (either 0 or 1) if graph is bipartite
//----------------------------------------------------------------------
bool Graph::bipartite_graph(Map& coloring) const {
    std::queue<int> q;
    int u;
    std::list<int> adj;
    
    for(int i = 0; i < vertex_count(); ++i) {
        if(coloring.count(i) == 0) {
            coloring[i] = 0;
            q.push(i);
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                adj.clear();
                adjacent(u, adj);
                for(int v: adj) {
                    if(coloring.count(v) == 0) { //check theres nothing there
                        coloring[v] = 1 - coloring[u];
                        q.push(v);
                    } else if(coloring[v] == coloring[u]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}