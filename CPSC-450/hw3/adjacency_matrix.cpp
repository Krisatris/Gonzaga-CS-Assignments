//----------------------------------------------------------------------
// NAME: Stella Beemer
// FILE: adjacency_matrix.h
// DATE: Spring 2021
// DESC: Adjacency matrix implementation of the graph interface
//----------------------------------------------------------------------

#include <iostream>
#include "graph.h"
#include "adjacency_matrix.h"


// default constructor
AdjacencyMatrix::AdjacencyMatrix(int vertex_count)
{
    number_of_vertices = vertex_count;
    number_of_edges = 0;
    int size = number_of_vertices * number_of_vertices;
    adj_matrix = new int*[size];
    for(int i = 0; i < size; ++i) {
        adj_matrix[i] = nullptr;
    }
}

// destructor
AdjacencyMatrix::~AdjacencyMatrix()
{
    make_empty();
}

// copy constructor
AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& rhs)
{
    number_of_edges = 0;
    number_of_vertices = 0;
    adj_matrix = nullptr;
    *this = rhs;
}

// assignment operator
AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& rhs)
{
    if(adj_matrix && adj_matrix == rhs.adj_matrix) {
        return *this;
    }
    make_empty();

    number_of_vertices = rhs.number_of_vertices;
    number_of_edges = rhs.number_of_edges;
    int size = number_of_vertices * number_of_vertices;

    adj_matrix = new int*[size];
    for(int i = 0; i < size; ++i) {
        if(rhs.adj_matrix[i]) {
            adj_matrix[i] = new int;
            *adj_matrix[i] = *rhs.adj_matrix[i];
        } else {
            adj_matrix[i] = nullptr;
        }
    }
    return *this;
}

// add or update an edge between existing vertices in the graph
void AdjacencyMatrix::set_edge(int v1, int edge_label, int v2)
{
    int insert_index = index(v1, v2);
    if(adj_matrix[insert_index]) {
        *adj_matrix[insert_index] = edge_label;
    } else {
        adj_matrix[insert_index] = new int;
        *adj_matrix[insert_index] = edge_label;
        ++number_of_edges;
    }
}

// check if the given edge is in the graph
bool AdjacencyMatrix::has_edge(int v1, int v2) const
{
    int insert_index = index(v1, v2);
    if(adj_matrix[insert_index]) {
        return true;
    } else {
        return false;
    }
}

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyMatrix::get_edge(int v1, int v2, int& edge) const
{
    int insert_index = index(v1, v2);
    if(adj_matrix[insert_index]) {
        edge = *adj_matrix[insert_index];
        return true;
    }
    return false;
}
  
// get all vertices on an outgoing edge from given vertex
void AdjacencyMatrix::connected_to(int v1, std::list<int>& vertices) const
{
    int start_index = index(v1, 0);
    int end_index = index(v1, number_of_vertices);
    for(int i = start_index; i < end_index; ++i) {
        if(adj_matrix[i]) {
            vertices.push_back((i - (v1 * number_of_vertices)));
        }
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyMatrix::connected_from(int v2, std::list<int>& vertices) const
{
    int start_index = index(0, v2);
    int end_index = index((number_of_vertices - 1), v2);
    for(int i = start_index; i <= end_index; i += number_of_vertices) {
        if(adj_matrix[i]) {
            vertices.push_back((i - v2) / number_of_vertices);
        }
    }
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyMatrix::adjacent(int v, std::list<int>& vertices) const
{
    connected_to(v, vertices);
    connected_from(v, vertices);
    vertices.unique();
}

// get number of nodes in the graph
int AdjacencyMatrix::vertex_count() const
{
    return number_of_vertices;
}

// get number of edges in the graph
int AdjacencyMatrix::edge_count() const
{
    return number_of_edges;
}

// return the matrix index for edge x->y
int AdjacencyMatrix::index(int x, int y) const
{
    return (x * number_of_vertices) + y;
}

// delete the adjacency matrix
void AdjacencyMatrix::make_empty()
{
    /*
    delete[] adj_matrix;
    number_of_vertices = 0;
    number_of_edges = 0;
    */
    for(int i = 0; i < (number_of_vertices * number_of_vertices); ++i) {
        delete adj_matrix[i];
        adj_matrix[i] = nullptr;
    }
    number_of_vertices = 0;
    number_of_edges = 0;
    delete[] adj_matrix;
    adj_matrix = nullptr;
}