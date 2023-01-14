//----------------------------------------------------------------------
// NAME: Stella Beemer
// FILE: graph.cpp
// DATE: Spring 2021
// DESC: Adjacency list implementation of the graph interface
//----------------------------------------------------------------------

#include "graph.h"
#include <queue>
#include <stack>
#include <list>
#include <unordered_map>
#include <iostream>
#include <set>
#include <algorithm>
#include <bits/stdc++.h>
#include <tuple>

// shortened hash-table map name for convenience
typedef std::unordered_map<int,int> Map;

// shortened tuple name for convenience
typedef std::tuple<int, int, int> Edge;

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
    int parent = -1;
    int child = dst;
    while(parent != src) {
        if(bfs_map.count(child) == 0) {
            path.clear();
            return;
        }
        parent = bfs_map[child];
        path.push_front(parent);
        child = parent;
    }
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

//----------------------------------------------------------------------
// Depth-first search from a given source vertex.
//
// Inputs: 
//   dir -- if true assumes graph is directed
//   src -- the source vertex
// Outputs:
//   tree -- search tree that maps vertices found during dfs to their
//           corresponding parent vertex.
//----------------------------------------------------------------------
void Graph::dfs(bool dir, int src, Map& tree) const {
    bool discovered [vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        discovered[i] = false;
    }
    tree[src] = -1;
    std::stack<int> s;
    s.push(src);
    int u;
    std::list<int> adj;
    while(!s.empty()) {
        u = s.top();
        if(discovered[u]) {
            s.pop();
            continue;
        }
        discovered[u] = true;
        adj.clear();
        if(dir) {
            connected_to(u, adj);
        } else {
            adjacent(u, adj);
        }
        for(int v: adj) {
            if(!discovered[v]) {
                s.push(v);
                tree[v] = u;
            }
        }
    }
}

//----------------------------------------------------------------------
// Determine if the graph is acyclic or not.
//
// Inputs:
//   dir -- if true assumes graph is directed
// Outputs:
//   returns -- true if acyclic
//----------------------------------------------------------------------
bool Graph::acyclic(bool dir) const {
    int discovered [vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        discovered[i] = 0;
    }
    Map tree;
    std::stack<int> s;
    int u;
    std::list<int> adj;
    for(int i = 0; i < vertex_count(); ++i) {
        if(discovered[i] == 0) {
            s.push(i);
            tree[i] = -1;
            while(!s.empty()) {
                u = s.top();
                if(discovered[u] == 1) {
                    s.pop();
                    discovered[u] = 2;
                    continue;
                }
                discovered[u] = 1;
                adj.clear();
                if(dir) {
                    connected_to(u, adj);
                } else {
                    adjacent(u, adj);
                }
                for(int v: adj) {
                    if(tree[u] == v) {
                        continue;
                    }
                    if(discovered[v] == 0) {
                        s.push(v);
                        tree[v] = u;
                        //discovered[v] = 1;
                    } else if(discovered[v] == 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------
// Brute force implementation to compute the transitive closure of
// the current graph without consideration of edge weights.
//
// Conditions: Assumes that the given graph (the closed_graph) is a
//             copy of the current graph prior to the call.
// 
// Inputs:
//   dir -- if true assumes graph is directed
// Outputs:
//   closed_graph -- the transitively closed graph, where added
//                   edges have
//----------------------------------------------------------------------
void Graph::unweighted_transitive_closure(bool dir, Graph& closed_graph) const {
    bool discovered [vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        discovered[i] = false;
    }
    std::stack<int> s;
    int u;
    std::list<int> adj;
    for(int i = 0; i < vertex_count(); ++i) {
        s.push(i);
        while(!s.empty()) {
            u = s.top();
            if(discovered[u]) {
                s.pop();
                continue;
            }
            discovered[u] = true;
            adj.clear();
            if(dir) {
                connected_to(u, adj);
            } else {
                adjacent(u, adj);
            }
            for(int v: adj) {
                if(!discovered[v]) {
                    s.push(v);
                    if(!closed_graph.has_edge(i, v)) {
                        closed_graph.set_edge(i, 0, v);
                    }
                }
            }
        }
        for(int i = 0; i < vertex_count(); ++i) {
            discovered[i] = false;
        }
    }
}

//----------------------------------------------------------------------
// Computes a topological sort of the current graph based on dfs.
//
// Conditions: Assumes the graph is directed.
// Outputs:
//
//   vertex_ordering -- a map from vertex to its corresponding
//                      order in the topological sort (where nodes
//                      are ordered from 1 to n)
//----------------------------------------------------------------------
void Graph::dfs_topological_sort(Map& vertex_ordering) const {
    int discovered [vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        discovered[i] = 0;
    }
    std::stack<int> s;
    int u;
    std::list<int> adj;
    std::list<int> sort;
    for(int i = 0; i < vertex_count(); ++i) {
        if(discovered[i] == 0) {
            s.push(i);
            while(!s.empty()) {
                u = s.top();
                if(discovered[u] == 1) {
                    sort.push_front(u);
                    s.pop();
                    discovered[u] = 2;
                    continue;
                }
                discovered[u] = 1;
                adj.clear();
                connected_to(u, adj);
                for(int v: adj) {
                    if(discovered[v] == 0) {
                        s.push(v);
                    }
                }
            }
        }
    }
    int j = 1;
    for(int k: sort) {
        vertex_ordering[k] = j;
        ++j;
        //std::cout << "j is " << j << std::endl;
    }
}

//----------------------------------------------------------------------
// HW-5 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Computes the strongly connected components.
//
// Inputs:
//   none
// Outputs: 
//   components -- mapping from each graph vertex to its corresponding
//                 component number where component numbers range from
//                 0 to c-1 (for c components)
//----------------------------------------------------------------------
void Graph::strongly_connected_components(Map& components) const {
    int pre [vertex_count()];
    int post [vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        pre[i] = -1;
        post[i] = -1;
    }
    Map tree;
    std::stack<int> s;
    std::stack<int> reverse_post;
    int u;
    std::list<int> adj;
    int clock = 0;
    for(int i = 0; i < vertex_count(); ++i) {
        if(pre[i] == -1) {
            s.push(i);
            //tree[i] = -1;
            while(!s.empty()) {
                u = s.top();
                if(pre[u] > -1) {
                    s.pop();
                    if(post[u] > -1) {
                        continue;
                    }
                    post[u] = clock;
                    ++clock;
                    reverse_post.push(u);
                    continue;
                }
                pre[u] = clock;
                ++clock;
                adj.clear();
                connected_from(u, adj);
                for(int v: adj) {
                    /*
                    if(tree[u] == v) {
                        continue;
                    }
                    */
                    if(pre[v] == -1) {
                        s.push(v);
                        //tree[v] = u;
                    }
                }
            }
        }
    }
    for(int i = 0; i < vertex_count(); ++i) {
        pre[i] = -1;
        post[i] = -1;
    }
    int i;
    int component_num = -1;
    while(!reverse_post.empty()) {
        i = reverse_post.top();
        if(pre[i] == -1) {
            s.push(i);
            ++component_num;
            components[i] = component_num;
            while(!s.empty()) {
                u = s.top();
                //std::cout << "u is " << u << std::endl;
                if(pre[u] > -1) {
                    s.pop();
                    if(post[u] > -1) {
                        continue;
                    }
                    post[u] = clock;
                    ++clock;
                    continue;
                }
                pre[u] = clock;
                components[u] = component_num;
                ++clock;
                adj.clear();
                connected_to(u, adj);
                for(int v: adj) {
                    /*
                    if(tree[u] == v) {
                        continue;
                    }
                    */
                    if(pre[v] == -1) {
                        s.push(v);
                        //tree[v] = u;
                    }
                }
            }
        }
        reverse_post.pop();
    }
}

//----------------------------------------------------------------------
// Computes the transitive reduction.
//
// Conditions: Assumes that the given graph (the closed_graph) has
//             the same number of nodes as the current graph. But
//             does not have any edges prior to the call
//
// Inputs:
//   none
// Outputs:
//   reduced_graph -- the reduced edges are added to the reduced graph
//----------------------------------------------------------------------
void Graph::transitive_reduction(Graph& reduced_graph) const {

    // fill unordered map
    Map scc;
    strongly_connected_components(scc);
    std::unordered_map<int, std::list<int>> c_list;
    std::list<int> adj;
    int index;
    for(int i = 0; i < vertex_count(); ++i) {
        index = scc[i];
        c_list[index].push_back(i);
    }

    // cycle in each component
    std::list<int> curr_component;
    int first_node;
    int prev_node;
    int curr_node;
    int c_array[c_list.size()];
    for(int i = 0; i < c_list.size(); ++i) {
        curr_component = c_list[i];
        first_node = curr_component.front();
        if(curr_component.size() > 1) {
            while(curr_component.size() > 1) {
                curr_node = curr_component.front();
                curr_component.pop_front();
                prev_node = curr_component.front();
                reduced_graph.set_edge(curr_node, 0, prev_node);
            }
            reduced_graph.set_edge(prev_node, 0, first_node);
        }
        curr_component.clear();
        c_array[i] = first_node;
    }

    // set edges if path between components exist
    std::list<int> path;
    for(int i = 0; i < c_list.size(); ++i) {
        for(int j = 0; j < c_list.size(); ++j) {
            path.clear();
            if(i != j) {
                shortest_path_length(true, c_array[i], c_array[j], path);
                if(path.size() > 0) {
                    reduced_graph.set_edge(c_array[i], 0, c_array[j]);
                }
            }
        }
    }

    // reduce the graph
    for(int i = 0; i < vertex_count(); ++i) {
        adj.clear();
        reduced_graph.connected_to(i, adj);
        for(int v : adj) {
            reduced_graph.remove_edge(i, v);
            reduced_graph.shortest_path_length(true, i, v, path);
            if(path.empty()) {
                reduced_graph.set_edge(i, 0, v);
            }
        }
    }
}

//----------------------------------------------------------------------
// Check if an eulerian exists in a directed graph, and if so,
// return one.
//
// Conditions: Assumes the graph is not disconnected.
//
// Inputs:
//   none
// Outputs:
//   path -- the path as an ordered list of vertices
//----------------------------------------------------------------------
bool Graph::directed_eulerian_path(std::list<int>& path) const {

    // determine if the graph can have an eulerian path
    int source_index = 0;
    int source_count = 0;
    int sink_count = 0;
    int edge_count = 0;
    std::list<int> adj_to; // out edges
    std::list<int> adj_from; // in edges
    for(int i = 0; i < vertex_count(); ++i) {
        adj_to.clear();
        adj_from.clear();
        connected_to(i, adj_to);
        connected_from(i, adj_from);
        if(adj_to.size() == adj_from.size() + 1) { // test for source
            ++source_count;
            source_index = i;
        } else if (adj_to.size() + 1 == adj_from.size()) { // test for sink
            ++sink_count;
        } else if(adj_to.size() == adj_from.size()) { // test for same number of edges
            ++edge_count;
        } else { // this is a node with two or more in/out edges, so graph can't be eulerian
            return false;
        }
    }
    if(source_count > 1 || sink_count > 1) {
        return false;
    } else if((vertex_count() - source_count - sink_count) != edge_count) {
        return false;
    }

    // find the path
    std::list<int> adj;
    int remaining_edges[vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        adj.clear();
        connected_to(i, adj);
        remaining_edges[i] = adj.size();
    }

    std::stack<int> s;
    int u;
    s.push(source_index);
    while(!s.empty()) {
        u = s.top();
        if(remaining_edges[u] <= 0) {
            s.pop();
            path.push_front(u);
            continue;
        }

        adj.clear();
        connected_to(u, adj);
        if(adj.size() > 0)
            adj.sort();
        for(int v : adj) {
            if(remaining_edges > 0) {
                --remaining_edges[u];
                s.push(v);
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------
// HW-6 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Returns a Hamiltonian path if one exists in the current graph.
//
// Conditions: Treats the graph as directed.
//
// Outputs:
//   path -- the Hamiltonian path
//
// Returns:
//   true if a Hamiltonian path exists, false otherwise.
//----------------------------------------------------------------------
bool Graph::directed_hamiltonian_path(std::list<int>& path) const {
    bool discovered[vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        for(int j = 0; j < vertex_count(); ++j) {
            discovered[j] = false;
        }
        if(directed_hamiltonian_rec(i, path, discovered))
            return true;
    }
    return false;
}

//----------------------------------------------------------------------
// Find a maximum matched graph using the augmenting paths algorithm
// from the textbook.
//
// Conditions: Finds a matching only if the current graph is bipartite
//
// Output:
//   max_matched_graph -- A graph with same vertices as original
//                        graph, containing the edges in the
//                        matching. The output graph is assumed to
//                        be initialized with the same number of
//                        vertices, but without any edges.
// Returns:
//   true if the current graph is bipartite, false otherwise
//----------------------------------------------------------------------
bool Graph::bipartite_graph_matching(Graph& max_matched_graph) const {
    Map coloring;
    if(!bipartite_graph(coloring)) {
        return false;
    } else {
        std::set<int> v1, v2;
        Map labels;
        bool free[vertex_count()];
        int matching[vertex_count()];

        for(int i = 0; i < vertex_count(); ++i) {
            if(coloring[i] == 0)
                v1.insert(i);
            else
                v2.insert(i);
            free[i] = true;
            matching[i] = -1;
        }

        std::queue<int> q;
        for(int i : v1)
            q.push(i);
        
        std::list<int> adj;
        int v, w;
        while(!q.empty()) {
            w = q.front();
            q.pop();
            if(v1.find(w) != v1.end()) {
                adj.clear();
                adjacent(w, adj);
                for(int u : adj) {
                    if(v2.find(u) != v2.end()) {
                        if(free[u]) { // time to augment
                            max_matched_graph.set_edge(w, 0, u);
                            free[w] = false;
                            free[u] = false;
                            matching[w] = u;
                            matching[u] = w;
                            v = w;
                            while(labels.count(v) > 0) {
                                u = labels[v];
                                max_matched_graph.remove_edge(v, u);
                                free[v] = true;
                                free[u] = true;
                                matching[v] = -1;
                                matching[u] = -1;
                                v = labels[u];
                                max_matched_graph.set_edge(v, 0, u);
                                free[v] = false;
                                free[u] = false;
                                matching[v] = u;
                                matching[u] = v;
                            }

                            // start over after matching path found
                            labels.clear();
                            while(!q.empty())
                                q.pop();
                            for(int i : v1) {
                                if(free[i])
                                    q.push(i);
                            }
                            break;
                        } else { // u is matched
                            if(!max_matched_graph.has_edge(w, u) && labels.count(u) == 0) {
                                labels[u] = w;
                                q.push(u);
                            }
                        }
                    }
                }
            } else { // w is in v2
                v = matching[w];
                matching[v] = w;
                labels[v] = w;
                q.push(v);
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------
// Finds all (maximal) cliques in the graph using the Bron-Kerbosch
// algorithm.
//
// Conditions: Assumes the graph is undirected.
//
// Output:
//   cliques -- a list of list of vertices denoting a maximal clique
//----------------------------------------------------------------------
void Graph::cliques(std::list<Set>& cliques) const {
    std::set<int> p, r, x;
    for(int i = 0; i < vertex_count(); ++i) {
        p.insert(i);
    }
    cliques_rec(p, r, x, cliques);
}

// helper function for directed hamiltonian recursive function
bool Graph::directed_hamiltonian_rec(int v, std::list<int>& path,
                            bool discovered[]) const {
    if(path.size() == vertex_count()) {
        return true;
    } else {
        std::list<int> adj;
        connected_to(v, adj);
        for(int u : adj) {
            if(!discovered[u]) {
                discovered[u] = true;
                path.push_back(u);
                if(directed_hamiltonian_rec(u, path, discovered))
                    return true;
                path.pop_back();
            }
        }
    }
    return false;
}

// helper function for finding all cliques
void Graph::cliques_rec(Set& p, Set& r, Set& x, std::list<Set>& cliques) const {
    //std::cout << "recursive funtion started" << std::endl;
    if(p.empty() && x.empty()) {
        cliques.push_back(r);
        return;
    }
    
    while(!p.empty()) {
        // set up the recursive call
        std::set<int>::iterator it = p.begin();
        int v = *it;
        std::list<int> tmp;
        adjacent(v, tmp);
        std::set<int> adj(tmp.begin(), tmp.end());

        // get the intersect of p, adj(v)
        tmp.clear();
        std::set_intersection(p.begin(), p.end(), adj.begin(), adj.end(), std::back_inserter(tmp));
        std::set<int> p_v(tmp.begin(), tmp.end());

        // get union of r, v
        std::set<int> r_v = r;
        r_v.insert(v);

        // get intersect of x, adj(v)
        tmp.clear();
        std::set_intersection(x.begin(), x.end(), adj.begin(), adj.end(), std::back_inserter(tmp));
        std::set<int> x_v(tmp.begin(), tmp.end());

        // recursive call
        cliques_rec(p_v, r_v, x_v, cliques);
        // p = p - v
        p.erase(v);
        // x = x + v
        x.insert(v);
    }
    return;
}

//----------------------------------------------------------------------
// HW-7 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Single-source shortest paths from the given source using
// Dijkstra's algorithm.
//
// Conditions: Assumes graph is directed and maximum weight is
//             numeric_limits<int>::max()
// 
// Input:
//  src -- the source vertex
//
// Output:
//  path_costs -- the minimum path cost from src to each vertex v
//                given as path_costs[v].
//----------------------------------------------------------------------
void Graph::dijkstra_shortest_path(int src, Map& path_costs) const {
    bool discovered[vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        path_costs[i] = INT_MAX;
        discovered[i] = false;
    }
    path_costs[src] = 0;
    discovered[src] = true;

    int weight;
    int min_dist;
    int u_p, v_p;
    do {
        min_dist = -1;
        for(int u = 0; u < vertex_count(); ++u) {
            for(int v = 0; v < vertex_count(); ++v) {
                if(discovered[u] && !discovered[v] && get_edge(u, v, weight)) {
                    if(min_dist > (path_costs[u] + weight) || min_dist == -1) {
                        u_p = u;
                        v_p = v;
                        min_dist = path_costs[u] + weight;
                    }
                }
            }
        }
        if(min_dist != -1) {
            discovered[v_p] = true;
            path_costs[v_p] = min_dist;
        }
    } while(min_dist != -1);
}

//----------------------------------------------------------------------
// Compute a minimum spanning tree using Prim's algorithm.
//
// Conditions: Assumes a connected, undirected graph. The spanning
//             tree is represented as a graph, which is initialized
//             with the same vertices as the current graph, but with
//             no edges (on input).
//
// Output:
//  spanning-tree -- A graph containing the minimum spanning tree
//                   edges.
//
//----------------------------------------------------------------------
void Graph::prim_min_spanning_tree(Graph& spanning_tree) const {
    bool discovered[vertex_count()];
    for(int i = 0; i < vertex_count(); ++i) {
        discovered[i] = false;
    }
    discovered[0] = true;

    int weight;
    int min_dist;
    int u_p, v_p;
    do {
        min_dist = INT_MIN;
        for(int u = 0; u < vertex_count(); ++u) {
            for(int v = u + 1; v < vertex_count(); ++v) {
                if(discovered[u] && !discovered[v] && (get_edge(u, v, weight) || get_edge(v, u, weight))) {
                    if(min_dist > weight || min_dist == INT_MIN) {
                        u_p = u;
                        v_p = v;
                        min_dist = weight;
                    }
                }
            }
        }
        if(min_dist != INT_MIN) {
            discovered[v_p] = true;
            spanning_tree.set_edge(u_p, min_dist, v_p);
        }
    } while(min_dist != INT_MIN);
}

// helper function for merge sorting edge weights for Kruskal's
// merge helper function
void merge(Edge A[], size_t start, size_t mid, size_t end)
{
  // declare iterating vars and temp array
  Edge temp[end - start + 1];
  int i = start;
  int j = mid + 1;
  int k = 0;
  int a_i, a_j;

  // merge temp array
  while(i <= mid && j <= end) {
    a_i = std::get<2>(A[i]);
    a_j = std::get<2>(A[j]);
    //std::cout << "a_i = " << a_i << ", a_j = " << a_j << std::endl;
    if(a_i <= a_j) {
      temp[k] = A[i];
      i++;
    } else {
      temp[k] = A[j];
      j++;
    }
    k++;
  }

  // fill in temp array if still items in first sublist
  while(i <= mid) {
    temp[k] = A[i];
    k++;
    i++;
  }

  // fill in temp array if still items in second sublist
  while(j <= end) {
    temp[k] = A[j];
    k++;
    j++;
  }

  // copy temp array into A
  for(i = start; i <= end; ++i) {
    A[i] = temp[i - start];
  }
}


// TODO: 
// Basic array-based merge sort
// Assumes A is of length n
void merge_sort(Edge A[], size_t start, size_t end)
{
  if(start < end) {
    int mid = (start + end) / 2;
    merge_sort(A, start, mid);
    merge_sort(A, mid + 1, end);
    merge(A, start, mid, end);
  }
}

//----------------------------------------------------------------------
// Compute a minimum spanning tree using Kruskal's algorithm.
//
// Conditions: Assumes a connected, undirected graph. The spanning
//             tree is represented as a graph, which is initialized
//             with the same vertices as the current graph, but with
//             no edges (on input).
//
// Output:
//  spanning-tree -- A graph containing the minimum spanning tree
//                   edges.
//
//----------------------------------------------------------------------
void Graph::kruskal_min_spanning_tree(Graph& spanning_tree) const {
    Edge edge_list[edge_count()];
    int index = 0;
    int weight;
    for(int u = 0; u < vertex_count(); ++u) {
        for(int v = 0; v < vertex_count(); ++v) {
            if(get_edge(u, v, weight)) {
                edge_list[index] = Edge(u, v, weight);
                ++index;
            }
        }
    }
    merge_sort(edge_list, 0, edge_count() - 1);
    int n = 0;
    int u_p, v_p;
    for(int i = 0; n < vertex_count() - 1; ++i) {
        u_p = std::get<0>(edge_list[i]);
        v_p = std::get<1>(edge_list[i]);
        weight = std::get<2>(edge_list[i]);
        spanning_tree.set_edge(u_p, weight, v_p);
        if(spanning_tree.acyclic(false)) {
            ++n;
        } else {
            //std::cout << "what the fuck is c++" << std::endl;
            spanning_tree.remove_edge(u_p, v_p);
        }
    }
}

//----------------------------------------------------------------------
// HW-8 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Single-source shortest paths from the given source using
// Bellman-Ford's algorithm.
//
// Conditions: Assumes graph is directed and maximum weight is
//             numeric_limits<int>::max()
// 
// Input:
//  src -- the source vertex
//
// Output:
//  path_costs -- the minimum path cost from src to each vertex v
//                given as path_costs[v].
//
// Returns: true if there is not a negative cycle, and false
//          otherwise
//----------------------------------------------------------------------
bool Graph::bellman_ford_shortest_path(int src, Map& path_costs) const {
    for(int i = 0; i < vertex_count(); ++i) {
        path_costs[i] = INT_MAX;
    }
    path_costs[src] = 0;

    int weight;
    for(int i = 0; i < (vertex_count() - 1); ++i) {
        for(int u = 0; u < vertex_count(); ++u) {
            for(int v = 0; v < vertex_count(); ++v) {
                if(get_edge(u, v, weight) && (path_costs[v] > path_costs[u] + weight) && (path_costs[u] != INT_MAX)) {
                    path_costs[v] = path_costs[u] + weight;
                }
            }
        }
    }

    for(int u = 0; u < vertex_count(); ++u) {
        for(int v = 0; v < vertex_count(); ++v) {
            if(get_edge(u, v, weight) && (path_costs[v] > path_costs[u] + weight) && (path_costs[u] != INT_MAX)) {
                return false;
            }
        }
    }

    return true;
}