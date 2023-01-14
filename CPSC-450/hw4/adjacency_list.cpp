//----------------------------------------------------------------------
// NAME: Stella Beemer
// FILE: adjacency_list.h
// DATE: Spring 2021
// DESC: Adjacency list implementation of the graph interface
//----------------------------------------------------------------------

#include "graph.h"
#include "adjacency_list.h"

// default constructor
AdjacencyList::AdjacencyList(int vertex_count)
{
    number_of_vertices = vertex_count;
    number_of_edges = 0;
    adj_list_out = new Node*[number_of_vertices];
    adj_list_in = new Node*[number_of_vertices];
    for(int i = 0; i < number_of_vertices; ++i) {
        adj_list_out[i] = nullptr;
        adj_list_in[i] = nullptr;
    }
}

// destructor
AdjacencyList::~AdjacencyList()
{
    make_empty();
}

// copy constructor
AdjacencyList::AdjacencyList(const AdjacencyList& rhs)
{
    number_of_vertices = rhs.number_of_vertices;
    number_of_edges = rhs.number_of_edges;
    adj_list_out = new Node*[number_of_vertices];
    adj_list_in = new Node*[number_of_vertices];
    for(int i = 0; i < number_of_vertices; ++i) {
        adj_list_out[i] = nullptr;
        adj_list_in[i] = nullptr;
    }
    Node* out_iterator;
    Node* in_iterator;
    Node* prev;
    for(int i = 0; i < number_of_vertices; ++i) {
        out_iterator = rhs.adj_list_out[i];
        in_iterator = rhs.adj_list_in[i];
        prev = adj_list_out[i];
        while(out_iterator) {
            Node* out_insert = new Node;
            out_insert->edge = out_iterator->edge;
            out_insert->vertex = out_iterator->vertex;
            out_insert->next = nullptr;
            if(prev) {
                prev->next = out_insert;
                prev = prev->next;
            } else {
                adj_list_out[i] = out_insert;
                prev = adj_list_out[i];
            }
            out_iterator = out_iterator->next;
        }
        prev = adj_list_in[i];
        while(in_iterator) {
            Node* in_insert = new Node;
            in_insert->edge = in_iterator->edge;
            in_insert->vertex = in_iterator->vertex;
            in_insert->next = nullptr;
            if(prev) {
                prev->next = in_insert;
                prev = prev->next;
            } else {
                adj_list_in[i] = in_insert;
                prev = adj_list_in[i];
            }
            in_iterator = in_iterator->next;
        }
        
    }
}

// assignment operator
AdjacencyList& AdjacencyList::operator=(const AdjacencyList& rhs) 
{
    if(adj_list_out == rhs.adj_list_out) {
        return *this;
    }
    make_empty();
    AdjacencyList temp(rhs);
    std::swap(adj_list_out, temp.adj_list_out);
    std::swap(adj_list_in, temp.adj_list_in);
    std::swap(number_of_vertices, temp.number_of_vertices);
    std::swap(number_of_edges, temp.number_of_edges);
    return *this;
}

// add or update an edge between existing vertices in the graph
void AdjacencyList::set_edge(int v1, int edge_label, int v2)
{
    Node* iterator = adj_list_out[v1];
    if(has_edge(v1, v2)) {
        while(iterator) {
            if(iterator->vertex == v2) {
                iterator->edge = edge_label;
            }
            iterator = iterator->next;
        }
        iterator = adj_list_in[v2];
        while(iterator) {
            if(iterator->vertex == v1) {
                iterator->edge = edge_label;
            }
            iterator = iterator->next;
        }
    } else {
        Node* out_insert = new Node;
        out_insert->edge = edge_label;
        out_insert->vertex = v2;
        out_insert->next = nullptr;
        Node* in_insert = new Node;
        in_insert->edge = edge_label;
        in_insert->vertex = v1;
        in_insert->next = nullptr;
        if(iterator) {
            while(iterator->next) {
                iterator = iterator->next;
            }
            iterator->next = out_insert;
        } else {
            adj_list_out[v1] = out_insert;
        }
        iterator = adj_list_in[v2];
        if(iterator) {
            while(iterator->next) {
                iterator = iterator->next;
            }
            iterator->next = in_insert;
        } else {
            adj_list_in[v2] = in_insert;
        }
        ++number_of_edges;
    }
}

// check if the given edge is in the graph
bool AdjacencyList::has_edge(int v1, int v2) const
{
    Node* iterator = adj_list_out[v1];
    while(iterator) {
        if(iterator->vertex == v2) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyList::get_edge(int v1, int v2, int& edge) const
{
    Node* iterator = adj_list_out[v1];
    while(iterator) {
        if(iterator->vertex == v2) {
            edge = iterator->edge;
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}
  
// get all vertices on an outgoing edge from given vertex
void AdjacencyList::connected_to(int v1, std::list<int>& vertices) const
{
    Node* iterator = adj_list_out[v1];
    while(iterator) {
        vertices.push_back(iterator->vertex);
        iterator = iterator->next;
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyList::connected_from(int v2, std::list<int>& vertices) const
{
    Node* iterator = adj_list_in[v2];
    while(iterator) {
        vertices.push_back(iterator->vertex);
        iterator = iterator->next;
    }
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyList::adjacent(int v, std::list<int>& vertices) const
{
    connected_to(v, vertices);
    connected_from(v, vertices);
    vertices.unique();
}

// get number of nodes in the graph
int AdjacencyList::vertex_count() const
{
    return number_of_vertices;
}

// get number of edges in the graph
int AdjacencyList::edge_count() const
{
    return number_of_edges;
}
  
// helper function to delete adj_list
void AdjacencyList::make_empty()
{
    Node* iterator;
    Node* prev;
    for(int i = 0; i < number_of_vertices; ++i) {
        if(adj_list_out[i]) {
            Node* prev = adj_list_out[i];
            if(prev->next) {
                iterator = prev->next;
                while(iterator) {
                    delete prev;
                    prev = iterator;
                    iterator = iterator->next;
                }
            }
            delete prev;
        }
    }
    for(int i = 0; i < number_of_vertices; ++i) {
        if(adj_list_in[i]) {
            prev = adj_list_in[i];
            if(prev->next) {
                iterator = prev->next;
                while(iterator) {
                    delete prev;
                    prev = iterator;
                    iterator = iterator->next;
                }
            }
            delete prev;
        }
    }
    number_of_vertices = 0;
    number_of_edges = 0;
    delete[] adj_list_out;
    adj_list_out = nullptr;
    delete[] adj_list_in;
    adj_list_in = nullptr;
}