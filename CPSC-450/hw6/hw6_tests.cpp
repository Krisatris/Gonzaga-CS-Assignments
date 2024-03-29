//----------------------------------------------------------------------
// Name: 
// File: hw6_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for list and matrix graph implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <gtest/gtest.h>
#include "graph.h"
#include "adjacency_list.h"
#include "adjacency_matrix.h"


using namespace std;


//----------------------------------------------------------------------
// Helper functions for testing
//----------------------------------------------------------------------

void print_graph(const Graph& g)
{
  int n = g.vertex_count();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (g.has_edge(i,j)) {
        int edge_label;
        g.get_edge(i, j, edge_label);
        cout << "(" << i << "," << edge_label << "," << j << ")" << endl;
      }
    }
  }
}


void print_path(const list<int>& path)
{
  for (int v : path)
    cout << v << " ";
  cout << endl;
}


bool unique_path(const list<int>& path)
{
  set<int> s(path.begin(), path.end());
  return s.size() == path.size();
}


bool valid_path(const Graph& g, list<int>& path)
{
  vector<int> v(path.begin(), path.end());
  for (int i = 0; i < path.size() - 1; ++i)
    if(!g.has_edge(v[i], v[i+1]))
      return false;
  return true;
}


bool contains_clique(const list<Set>& cliques, const Set& clique)
{
  for (Set c : cliques) {
    if (clique.size() == c.size()) {
      bool missing = false;
      for (int v : clique) 
        if(c.count(v) == 0) 
          missing = true;
      if (!missing)
        return true;
    }
  }
  return false;
}

//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

TEST(AdjacencyListTest, HamiltonianPath) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(1, 0, 3);  
  g.set_edge(2, 0, 0);
  g.set_edge(3, 0, 2);  
  list<int> path;
  ASSERT_EQ(true, g.directed_hamiltonian_path(path));
  // ensure correct size
  ASSERT_EQ(g.vertex_count(), path.size());
  // test for duplicates
  ASSERT_EQ(true, unique_path(path));
  // check for valid path
  ASSERT_EQ(true, valid_path(g, path));
}

TEST(AdjacencyListTest, NonHamiltonianPath) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 2);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 1);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 2);  
  g.set_edge(2, 0, 4);
  list<int> path;
  ASSERT_EQ(false, g.directed_hamiltonian_path(path));
}

// TODO: Add at least two addition hamiltonian path tests
TEST(AdjacencyListTest, SingleAndDisconnectedHamiltonian) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 2);
  list<int> path;
  ASSERT_EQ(false, g.directed_hamiltonian_path(path));
}

TEST(AdjacencyListTest, SelfEdgeHamiltonian) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 0);
  g.set_edge(1, 0, 1);
  g.set_edge(2, 0, 2);
  g.set_edge(3, 0, 3);
  g.set_edge(4, 0, 4);
  list<int> path;
  ASSERT_EQ(false, g.directed_hamiltonian_path(path));
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 0);
  path.clear();
  ASSERT_EQ(true, g.directed_hamiltonian_path(path));
}

TEST(AdjacencyListTest, BasicGraphMatchingSimple) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 3);
  g.set_edge(0, 0, 2);
  g.set_edge(1, 0, 2);
  AdjacencyList m(4);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(2, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 3) or m.has_edge(3, 0));
  ASSERT_EQ(true, m.has_edge(1, 2) or m.has_edge(2, 1));
}

TEST(AdjacencyListTest, BasicGraphMatchingBook) {
  AdjacencyList g(8);
  g.set_edge(0, 0, 4);
  g.set_edge(0, 0, 5);
  g.set_edge(1, 0, 4);
  g.set_edge(1, 0, 5);
  g.set_edge(1, 0, 6);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 6);
  g.set_edge(3, 0, 7);
  AdjacencyList m(8);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(4, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 4) or m.has_edge(4, 0));
  ASSERT_EQ(true, m.has_edge(1, 6) or m.has_edge(6, 1));
  ASSERT_EQ(true, m.has_edge(2, 5) or m.has_edge(5, 2));
  ASSERT_EQ(true, m.has_edge(3, 7) or m.has_edge(7, 3));
}

// TODO: Add at least two addition graph matching tests
TEST(AdjacencyListTest, FourMatchingLines) {
  AdjacencyList g(8);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 5);
  g.set_edge(1, 0, 6);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 7);
  g.set_edge(5, 0, 7);
  g.set_edge(6, 0, 7);
  AdjacencyList m(8);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(4, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 2) or m.has_edge(2, 0));
  ASSERT_EQ(true, m.has_edge(3, 4) or m.has_edge(4, 3));
  ASSERT_EQ(true, m.has_edge(1, 5) or m.has_edge(5, 1) or m.has_edge(1, 6) or m.has_edge(6, 1));
  ASSERT_EQ(true, m.has_edge(5, 7) or m.has_edge(7, 5) or m.has_edge(6, 7) or m.has_edge(7, 6));
}

TEST(AdjacencyListTest, FanMatching) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(0, 0, 3);
  g.set_edge(0, 0, 4);
  AdjacencyList m(5);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(1, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 1) or m.has_edge(1, 0));
}

TEST(AdjacencyListTest, BasicClique) {
  AdjacencyList g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 4);
  g.set_edge(2, 0, 3);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 5);
  g.set_edge(4, 0, 5);
  list<Set> cliques;
  g.cliques(cliques);
  ASSERT_EQ(5, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0,1}));
  ASSERT_EQ(true, contains_clique(cliques, Set {1,2}));
  ASSERT_EQ(true, contains_clique(cliques, Set {1,4}));
  ASSERT_EQ(true, contains_clique(cliques, Set {4,5}));  
  ASSERT_EQ(true, contains_clique(cliques, Set {2,3,5}));  
}

// TODO: Add at least two addition clique tests
TEST(AdjacencyListTest, CycleClique) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  list<Set> cliques;
  g.cliques(cliques);
  ASSERT_EQ(4, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1}));
  ASSERT_EQ(true, contains_clique(cliques, Set {1, 2}));
  ASSERT_EQ(true, contains_clique(cliques, Set {2, 3}));
  ASSERT_EQ(true, contains_clique(cliques, Set {3, 0}));
  g.set_edge(0, 0, 2);
  cliques.clear();
  g.cliques(cliques);
  ASSERT_EQ(2, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1, 2}));
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 2, 3}));
  g.set_edge(1, 0, 3);
  cliques.clear();
  g.cliques(cliques);
  ASSERT_EQ(1, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1, 2, 3}));
}

TEST(AdjacencyListTest, TriangleClique) {
  AdjacencyList g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(1, 0, 4);
  g.set_edge(2, 0, 4);
  g.set_edge(3, 0, 4);
  g.set_edge(3, 0, 5);
  g.set_edge(4, 0, 5);
  list<Set> cliques;
  g.cliques(cliques);
  ASSERT_EQ(4, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1, 3})); 
  ASSERT_EQ(true, contains_clique(cliques, Set {3, 1, 4})); 
  ASSERT_EQ(true, contains_clique(cliques, Set {1, 2, 4})); 
  ASSERT_EQ(true, contains_clique(cliques, Set {3, 4, 5})); 
}

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------


// TODO: Add your tests above but for your adjacency matrix
TEST(AdjacencyMatrixTest, HamiltonianPath) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(1, 0, 3);  
  g.set_edge(2, 0, 0);
  g.set_edge(3, 0, 2);  
  list<int> path;
  ASSERT_EQ(true, g.directed_hamiltonian_path(path));
  // ensure correct size
  ASSERT_EQ(g.vertex_count(), path.size());
  // test for duplicates
  ASSERT_EQ(true, unique_path(path));
  // check for valid path
  ASSERT_EQ(true, valid_path(g, path));
}

TEST(AdjacencyMatrixTest, NonHamiltonianPath) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 2);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 1);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 2);  
  g.set_edge(2, 0, 4);
  list<int> path;
  ASSERT_EQ(false, g.directed_hamiltonian_path(path));
}

// TODO: Add at least two addition hamiltonian path tests
TEST(AdjacencyMatrixTest, SingleAndDisconnectedHamiltonian) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 2);
  list<int> path;
  ASSERT_EQ(false, g.directed_hamiltonian_path(path));
}

TEST(AdjacencyMatrixTest, SelfEdgeHamiltonian) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 0);
  g.set_edge(1, 0, 1);
  g.set_edge(2, 0, 2);
  g.set_edge(3, 0, 3);
  g.set_edge(4, 0, 4);
  list<int> path;
  ASSERT_EQ(false, g.directed_hamiltonian_path(path));
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 0);
  path.clear();
  ASSERT_EQ(true, g.directed_hamiltonian_path(path));
}

TEST(AdjacencyMatrixTest, BasicGraphMatchingSimple) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 3);
  g.set_edge(0, 0, 2);
  g.set_edge(1, 0, 2);
  AdjacencyMatrix m(4);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(2, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 3) or m.has_edge(3, 0));
  ASSERT_EQ(true, m.has_edge(1, 2) or m.has_edge(2, 1));
}

TEST(AdjacencyMatrixTest, BasicGraphMatchingBook) {
  AdjacencyMatrix g(8);
  g.set_edge(0, 0, 4);
  g.set_edge(0, 0, 5);
  g.set_edge(1, 0, 4);
  g.set_edge(1, 0, 5);
  g.set_edge(1, 0, 6);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 6);
  g.set_edge(3, 0, 7);
  AdjacencyMatrix m(8);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(4, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 4) or m.has_edge(4, 0));
  ASSERT_EQ(true, m.has_edge(1, 6) or m.has_edge(6, 1));
  ASSERT_EQ(true, m.has_edge(2, 5) or m.has_edge(5, 2));
  ASSERT_EQ(true, m.has_edge(3, 7) or m.has_edge(7, 3));
}

// TODO: Add at least two addition graph matching tests
TEST(AdjacencyMatrixTest, FourMatchingLines) {
  AdjacencyMatrix g(8);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 5);
  g.set_edge(1, 0, 6);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 7);
  g.set_edge(5, 0, 7);
  g.set_edge(6, 0, 7);
  AdjacencyMatrix m(8);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(4, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 2) or m.has_edge(2, 0));
  ASSERT_EQ(true, m.has_edge(3, 4) or m.has_edge(4, 3));
  ASSERT_EQ(true, m.has_edge(1, 5) or m.has_edge(5, 1) or m.has_edge(1, 6) or m.has_edge(6, 1));
  ASSERT_EQ(true, m.has_edge(5, 7) or m.has_edge(7, 5) or m.has_edge(6, 7) or m.has_edge(7, 6));
}

TEST(AdjacencyMatrixTest, FanMatching) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(0, 0, 3);
  g.set_edge(0, 0, 4);
  AdjacencyMatrix m(5);
  ASSERT_EQ(true, g.bipartite_graph_matching(m));
  ASSERT_EQ(1, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 1) or m.has_edge(1, 0));
}

TEST(AdjacencyMatrixTest, BasicClique) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 4);
  g.set_edge(2, 0, 3);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 5);
  g.set_edge(4, 0, 5);
  list<Set> cliques;
  g.cliques(cliques);
  ASSERT_EQ(5, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0,1}));
  ASSERT_EQ(true, contains_clique(cliques, Set {1,2}));
  ASSERT_EQ(true, contains_clique(cliques, Set {1,4}));
  ASSERT_EQ(true, contains_clique(cliques, Set {4,5}));  
  ASSERT_EQ(true, contains_clique(cliques, Set {2,3,5}));  
}

// TODO: Add at least two addition clique tests
TEST(AdjacencyMatrixTest, CycleClique) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  list<Set> cliques;
  g.cliques(cliques);
  ASSERT_EQ(4, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1}));
  ASSERT_EQ(true, contains_clique(cliques, Set {1, 2}));
  ASSERT_EQ(true, contains_clique(cliques, Set {2, 3}));
  ASSERT_EQ(true, contains_clique(cliques, Set {3, 0}));
  g.set_edge(0, 0, 2);
  cliques.clear();
  g.cliques(cliques);
  ASSERT_EQ(2, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1, 2}));
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 2, 3}));
  g.set_edge(1, 0, 3);
  cliques.clear();
  g.cliques(cliques);
  ASSERT_EQ(1, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1, 2, 3}));
}

TEST(AdjacencyMatrixTest, TriangleClique) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(1, 0, 4);
  g.set_edge(2, 0, 4);
  g.set_edge(3, 0, 4);
  g.set_edge(3, 0, 5);
  g.set_edge(4, 0, 5);
  list<Set> cliques;
  g.cliques(cliques);
  ASSERT_EQ(4, cliques.size());
  ASSERT_EQ(true, contains_clique(cliques, Set {0, 1, 3})); 
  ASSERT_EQ(true, contains_clique(cliques, Set {3, 1, 4})); 
  ASSERT_EQ(true, contains_clique(cliques, Set {1, 2, 4})); 
  ASSERT_EQ(true, contains_clique(cliques, Set {3, 4, 5})); 
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

