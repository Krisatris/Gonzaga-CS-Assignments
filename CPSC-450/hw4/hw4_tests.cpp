//----------------------------------------------------------------------
// Name: 
// File: hw4_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for DFS and related algorithms
//----------------------------------------------------------------------


#include <iostream>
#include <string>
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

void print_search_tree(const Map& search_tree)
{
  for (pair<int,int> p : search_tree)
    cout << "parent: " << p.second << ", child: " << p.first << endl;
}

void print_path(const list<int>& path)
{
  for (int v : path)
    cout << v << " ";
  cout << endl;
}

void print_ordering(const Map& ordering)
{
  for (pair<int,int> p : ordering)
    cout << p.first << " has order " << p.second << endl;
}


//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

// Basic DFS test over a directed graph
TEST(AdjacencyListTest, BasicDirectedDFS) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(3, 0, 0);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
  // directed dfs from 1
  tree.clear();
  g.dfs(true, 1, tree);
  ASSERT_EQ(4, tree.size());
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[1]);
  ASSERT_EQ(1, tree[0]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
}


// TODO: at least two additional directed graph DFS tets
TEST(AdjacencyListTest, UnbalancedGraph) {
  AdjacencyList g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, -1, 3);
  g.set_edge(0, -1, 4);
  g.set_edge(2, -1, 3);
  Map search_tree;
  // bfs from 0
  g.dfs(true, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(0, search_tree[2]);
  ASSERT_EQ(0, search_tree[3]);
  ASSERT_EQ(0, search_tree[4]);
}

TEST(AdjacencyListTest, LineGraph) {
  AdjacencyList g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(1, -1, 2);
  g.set_edge(2, -1, 3);
  g.set_edge(3, -1, 4);
  g.set_edge(4, -1, 1);
  Map search_tree;
  // bfs from 0
  g.bfs(true, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(1, search_tree[2]);
  ASSERT_EQ(2, search_tree[3]);
  ASSERT_EQ(3, search_tree[4]);
}

// Basic undirected graph DFS test
TEST(AdjacencyListTest, BasicUndirectedDFS) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(3, 0, 0);
  Map tree;
  // undirected dfs from 0
  g.dfs(false, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(3, tree[2]);
  ASSERT_EQ(0, tree[3]);
  // undirected dfs from 1
  tree.clear();
  g.dfs(false, 1, tree);
  ASSERT_EQ(4, tree.size());
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[1]);
  ASSERT_EQ(1, tree[0]);
  ASSERT_EQ(3, tree[2]);
  ASSERT_EQ(0, tree[3]);
}


// TODO: at least two additional undirected graph DFS tets
TEST(AdjacencyListTest, UndirectedUnbalancedGraph) {
  AdjacencyList g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, -1, 3);
  g.set_edge(0, -1, 4);
  g.set_edge(2, -1, 3);
  Map search_tree;
  // bfs from 0
  g.dfs(false, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(3, search_tree[2]);
  ASSERT_EQ(0, search_tree[3]);
  ASSERT_EQ(0, search_tree[4]);
}

TEST(AdjacencyListTest, UndirectedLineGraph) {
  AdjacencyList g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(1, -1, 2);
  g.set_edge(2, -1, 3);
  g.set_edge(3, -1, 4);
  g.set_edge(4, -1, 1);
  Map search_tree;
  // bfs from 0
  g.bfs(false, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(1, search_tree[2]);
  ASSERT_EQ(2, search_tree[3]);
  ASSERT_EQ(1, search_tree[4]);
}

// Basic directed cycle check test
TEST(AdjacencyListTest, BasicDFSDirectedCycleCheck) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(0, 0, 3);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(2, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}


// TODO: at least two additional directed graph cycle tests
TEST(AdjacencyListTest, ShortCycles) {
  AdjacencyList g(5);
  g.set_edge(1, 0, 0);
  g.set_edge(2, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 4);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(2, 0, 4);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(3, 0, 2);
  ASSERT_EQ(false, g.acyclic(true));
}

TEST(AdjacencyListTest, LongCycle) {
  AdjacencyList g(10);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  g.set_edge(5, 0, 6);
  g.set_edge(6, 0, 7);
  g.set_edge(7, 0, 8);
  g.set_edge(8, 0, 9);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(9, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}


// Basic undirected cycle check test
TEST(AdjacencyListTest, BasicDFSUndirectedCycleCheck) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 2);
  ASSERT_EQ(true, g.acyclic(false));
  g.set_edge(3, -1, 2);
  ASSERT_EQ(false, g.acyclic(false));
}


// TODO: at least two additional undirected graph cycle tests
TEST(AdjacencyListTest, UndirectedShortCycles) {
  AdjacencyList g(5);
  g.set_edge(1, 0, 0);
  g.set_edge(2, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 4);
  ASSERT_EQ(true, g.acyclic(false));
  g.set_edge(2, 0, 4);
  ASSERT_EQ(false, g.acyclic(false));
  g.set_edge(3, 0, 2);
  ASSERT_EQ(false, g.acyclic(false));
}

TEST(AdjacencyListTest, UndirectedLongCycle) {
  AdjacencyList g(10);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  g.set_edge(5, 0, 6);
  g.set_edge(6, 0, 7);
  g.set_edge(7, 0, 8);
  g.set_edge(8, 0, 9);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(9, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}

// Basic directed transitive closure test
TEST(AdjacencyListTest, BasicDirectedUnweightedDFSTransClosure) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(1, 4));
}


// TODO: at least two additional directed graph transitive closure tests
TEST(AdjacencyListTest, LineDFSTransClosure) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(1, 3));
}

TEST(AdjacencyListTest, TreeDFSTransClosure) {
  AdjacencyList g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(1, 0, 4);
  g.set_edge(1, 0, 5);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(0, 5));
}

// Basic undirected transitive closure test
TEST(AdjacencyListTest, UndirectedUnweightedDFSTransClosure) {
  AdjacencyList g(3);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2) || tc_g.has_edge(2, 0));
}



// TODO: at least two additional undirected graph transitive closure tests
TEST(AdjacencyListTest, UndirectedLineDFSTransClosure) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(1, 3));
}

TEST(AdjacencyListTest, UndirectedTreeDFSTransClosure) {
  AdjacencyList g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(1, 0, 4);
  g.set_edge(1, 0, 5);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(0, 5));
}

// Basic topological sort test
TEST(AdjacencyListTest, BasicDFSTopologicalSort) {
  AdjacencyList g1(5);
  g1.set_edge(0, 0, 2);
  g1.set_edge(1, 0, 2);
  g1.set_edge(2, 0, 3);
  g1.set_edge(2, 0, 4);
  g1.set_edge(3, 0, 4);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
  AdjacencyList g2(5);
  g2.set_edge(0, 0, 2);
  g2.set_edge(1, 0, 2);
  g2.set_edge(2, 0, 3);
  g2.set_edge(2, 0, 4);
  g2.set_edge(4, 0, 3);
  vertex_ordering.clear();
  g2.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[4], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
  
}


// TODO: at least two additional topological sorting tests
TEST(AdjacencyListTest, LineTopologicalSort) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  Map vertex_ordering;
  g.dfs_topological_sort(vertex_ordering);
  ASSERT_EQ(5, vertex_ordering.size());
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[1]);
}

TEST(AdjacencyListTest, MoreEdgesTopologicalSort) {
  AdjacencyList g(8);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 4);
  g.set_edge(1, 0, 5);
  g.set_edge(1, 0, 6);
  g.set_edge(2, 0, 6);
  g.set_edge(3, 0, 7);
  g.set_edge(5, 0, 7);
  g.set_edge(6, 0, 7);
  Map vertex_ordering;
  g.dfs_topological_sort(vertex_ordering);
  ASSERT_EQ(8, vertex_ordering.size());
  ASSERT_EQ(1, vertex_ordering[3]);
  ASSERT_EQ(2, vertex_ordering[2]);
  ASSERT_EQ(3, vertex_ordering[0]);
  ASSERT_EQ(4, vertex_ordering[1]);
  ASSERT_EQ(5, vertex_ordering[5]);
  ASSERT_EQ(6, vertex_ordering[6]);
  ASSERT_EQ(7, vertex_ordering[7]);
  ASSERT_EQ(8, vertex_ordering[4]);
}

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------


// Basic DFS test over a directed graph
TEST(AdjacencyMatrixTest, BasicDirectedDFS) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(3, 0, 0);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
  // directed dfs from 1
  tree.clear();
  g.dfs(true, 1, tree);
  ASSERT_EQ(4, tree.size());
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[1]);
  ASSERT_EQ(1, tree[0]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
}


// TODO: at least two additional directed graph DFS tets
TEST(AdjacencyMatrixTest, UnbalancedGraph) {
  AdjacencyMatrix g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, -1, 3);
  g.set_edge(0, -1, 4);
  g.set_edge(2, -1, 3);
  Map search_tree;
  // bfs from 0
  g.dfs(true, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(0, search_tree[2]);
  ASSERT_EQ(0, search_tree[3]);
  ASSERT_EQ(0, search_tree[4]);
}

TEST(AdjacencyMatrixTest, LineGraph) {
  AdjacencyMatrix g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(1, -1, 2);
  g.set_edge(2, -1, 3);
  g.set_edge(3, -1, 4);
  g.set_edge(4, -1, 1);
  Map search_tree;
  // bfs from 0
  g.bfs(true, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(1, search_tree[2]);
  ASSERT_EQ(2, search_tree[3]);
  ASSERT_EQ(3, search_tree[4]);
}

// Basic undirected graph DFS test
TEST(AdjacencyMatrixTest, BasicUndirectedDFS) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(3, 0, 0);
  Map tree;
  // undirected dfs from 0
  g.dfs(false, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(3, tree[2]);
  ASSERT_EQ(0, tree[3]);
  // undirected dfs from 1
  tree.clear();
  g.dfs(false, 1, tree);
  ASSERT_EQ(4, tree.size());
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[1]);
  ASSERT_EQ(1, tree[0]);
  ASSERT_EQ(3, tree[2]);
  ASSERT_EQ(0, tree[3]);
}


// TODO: at least two additional undirected graph DFS tets
TEST(AdjacencyMatrixTest, UndirectedUnbalancedGraph) {
  AdjacencyMatrix g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, -1, 3);
  g.set_edge(0, -1, 4);
  g.set_edge(2, -1, 3);
  Map search_tree;
  // bfs from 0
  g.dfs(false, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(3, search_tree[2]);
  ASSERT_EQ(0, search_tree[3]);
  ASSERT_EQ(0, search_tree[4]);
}

TEST(AdjacencyMatrixTest, UndirectedLineGraph) {
  AdjacencyMatrix g(5);
  g.set_edge(0, -1, 1);
  g.set_edge(1, -1, 2);
  g.set_edge(2, -1, 3);
  g.set_edge(3, -1, 4);
  g.set_edge(4, -1, 1);
  Map search_tree;
  // bfs from 0
  g.bfs(false, 0, search_tree);
  ASSERT_EQ(5, search_tree.size());
  ASSERT_EQ(-1, search_tree[0]);
  ASSERT_EQ(0, search_tree[1]);
  ASSERT_EQ(1, search_tree[2]);
  ASSERT_EQ(2, search_tree[3]);
  ASSERT_EQ(1, search_tree[4]);
}

// Basic directed cycle check test
TEST(AdjacencyMatrixTest, BasicDFSDirectedCycleCheck) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(0, 0, 3);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(2, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}


// TODO: at least two additional directed graph cycle tests
TEST(AdjacencyMatrixTest, ShortCycles) {
  AdjacencyMatrix g(5);
  g.set_edge(1, 0, 0);
  g.set_edge(2, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 4);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(2, 0, 4);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(3, 0, 2);
  ASSERT_EQ(false, g.acyclic(true));
}

TEST(AdjacencyMatrixTest, LongCycle) {
  AdjacencyMatrix g(10);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  g.set_edge(5, 0, 6);
  g.set_edge(6, 0, 7);
  g.set_edge(7, 0, 8);
  g.set_edge(8, 0, 9);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(9, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}


// Basic undirected cycle check test
TEST(AdjacencyMatrixTest, BasicDFSUndirectedCycleCheck) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 2);
  ASSERT_EQ(true, g.acyclic(false));
  g.set_edge(3, -1, 2);
  ASSERT_EQ(false, g.acyclic(false));
}


// TODO: at least two additional undirected graph cycle tests
TEST(AdjacencyMatrixTest, UndirectedShortCycles) {
  AdjacencyMatrix g(5);
  g.set_edge(1, 0, 0);
  g.set_edge(2, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 4);
  ASSERT_EQ(true, g.acyclic(false));
  g.set_edge(2, 0, 4);
  ASSERT_EQ(false, g.acyclic(false));
  g.set_edge(3, 0, 2);
  ASSERT_EQ(false, g.acyclic(false));
}

TEST(AdjacencyMatrixTest, UndirectedLongCycle) {
  AdjacencyMatrix g(10);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  g.set_edge(5, 0, 6);
  g.set_edge(6, 0, 7);
  g.set_edge(7, 0, 8);
  g.set_edge(8, 0, 9);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(9, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}

// Basic directed transitive closure test
TEST(AdjacencyMatrixTest, BasicDirectedUnweightedDFSTransClosure) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(1, 4));
}


// TODO: at least two additional directed graph transitive closure tests
TEST(AdjacencyMatrixTest, LineDFSTransClosure) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(1, 3));
}

TEST(AdjacencyMatrixTest, TreeDFSTransClosure) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(1, 0, 4);
  g.set_edge(1, 0, 5);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(0, 5));
}

// Basic undirected transitive closure test
TEST(AdjacencyMatrixTest, UndirectedUnweightedDFSTransClosure) {
  AdjacencyMatrix g(3);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2) || tc_g.has_edge(2, 0));
}



// TODO: at least two additional undirected graph transitive closure tests
TEST(AdjacencyMatrixTest, UndirectedLineDFSTransClosure) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(1, 3));
}

TEST(AdjacencyMatrixTest, UndirectedTreeDFSTransClosure) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(1, 0, 4);
  g.set_edge(1, 0, 5);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(0, 5));
}

// Basic topological sort test
TEST(AdjacencyMatrixTest, BasicDFSTopologicalSort) {
  AdjacencyMatrix g1(5);
  g1.set_edge(0, 0, 2);
  g1.set_edge(1, 0, 2);
  g1.set_edge(2, 0, 3);
  g1.set_edge(2, 0, 4);
  g1.set_edge(3, 0, 4);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
  AdjacencyMatrix g2(5);
  g2.set_edge(0, 0, 2);
  g2.set_edge(1, 0, 2);
  g2.set_edge(2, 0, 3);
  g2.set_edge(2, 0, 4);
  g2.set_edge(4, 0, 3);
  vertex_ordering.clear();
  g2.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[4], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
  
}


// TODO: at least two additional topological sorting tests
TEST(AdjacencyMatrixTest, LineTopologicalSort) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  Map vertex_ordering;
  g.dfs_topological_sort(vertex_ordering);
  ASSERT_EQ(5, vertex_ordering.size());
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[1]);
}

TEST(AdjacencyMatrixTest, MoreEdgesTopologicalSort) {
  AdjacencyMatrix g(8);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 4);
  g.set_edge(1, 0, 5);
  g.set_edge(1, 0, 6);
  g.set_edge(2, 0, 6);
  g.set_edge(3, 0, 7);
  g.set_edge(5, 0, 7);
  g.set_edge(6, 0, 7);
  Map vertex_ordering;
  g.dfs_topological_sort(vertex_ordering);
  ASSERT_EQ(8, vertex_ordering.size());
  ASSERT_EQ(1, vertex_ordering[3]);
  ASSERT_EQ(2, vertex_ordering[2]);
  ASSERT_EQ(3, vertex_ordering[0]);
  ASSERT_EQ(4, vertex_ordering[1]);
  ASSERT_EQ(5, vertex_ordering[5]);
  ASSERT_EQ(6, vertex_ordering[6]);
  ASSERT_EQ(7, vertex_ordering[7]);
  ASSERT_EQ(8, vertex_ordering[4]);
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

