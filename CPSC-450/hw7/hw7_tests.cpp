//----------------------------------------------------------------------
// Name: 
// File: hw7_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for list and matrix graph implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <bits/stdc++.h>
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


//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

TEST(AdjacencyListTest, BasicDijkstraShortestPath) {
  AdjacencyList g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 6, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(3, 3, 2);
  g.set_edge(0, 4, 3);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

// TODO: Add two additional shortest path tests
TEST(AdjacencyListTest, LoopDijkstra) {
  AdjacencyList g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(1, 2, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 10, 4);
  g.set_edge(4, 3, 0);
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(4, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(7, path_costs[3]);
  ASSERT_EQ(17, path_costs[4]);
}

TEST(AdjacencyListTest, DisconnectedDijkstra) {
  AdjacencyList g(8);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(3, 5, 2);
  g.set_edge(4, 5, 6);
  g.set_edge(6, 1, 5);
  g.set_edge(5, 6, 7);
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(2, path_costs[1]);
  ASSERT_EQ(8, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
  ASSERT_EQ(INT_MAX, path_costs[4]);
  ASSERT_EQ(INT_MAX, path_costs[5]);
  ASSERT_EQ(INT_MAX, path_costs[6]);
  ASSERT_EQ(INT_MAX, path_costs[7]);
  path_costs.clear();
  g.dijkstra_shortest_path(4, path_costs);
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[4]);
  ASSERT_EQ(6, path_costs[5]);
  ASSERT_EQ(5, path_costs[6]);
  ASSERT_EQ(12, path_costs[7]);
  ASSERT_EQ(INT_MAX, path_costs[0]);
  ASSERT_EQ(INT_MAX, path_costs[1]);
  ASSERT_EQ(INT_MAX, path_costs[2]);
  ASSERT_EQ(INT_MAX, path_costs[3]);
}

TEST(AdjacencyListTest, BasicPrimMinSpanningTree) {
  AdjacencyList g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(0, 4, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(2, 5, 3);
  AdjacencyList tree(4);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
}

// TODO: Add two additional tests for Prim's algorithm
TEST(AdjacencyListTest, NegativePrim) {
  AdjacencyList g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, 2, 5);
  g.set_edge(1, -2, 3);
  g.set_edge(1, 2, 4);
  g.set_edge(2, 3, 4);
  AdjacencyList tree(6);
  g.prim_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

TEST(AdjacencyListTest, CyclicPrim) {
  AdjacencyList g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 1, 4);
  g.set_edge(4, 1, 5);
  g.set_edge(5, 1, 0);
  g.set_edge(0, -2, 2);
  g.set_edge(0, -3, 3);
  g.set_edge(1, -2, 4);
  AdjacencyList tree(6);
  g.prim_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0) or tree.has_edge(4, 5) or tree.has_edge(5, 4));
  ASSERT_EQ(true, tree.has_edge(0, 3) or tree.has_edge(3, 0));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

TEST(AdjacencyListTest, BasicKruskalMinSpanningTree) {
  AdjacencyList g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 3, 2);
  g.set_edge(1, 5, 3);
  g.set_edge(1, 1, 4);  
  g.set_edge(2, 6, 3);  
  g.set_edge(3, 7, 4);
  AdjacencyList tree(5);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

// TODO: Add two additional tests for Kruskal's algorithm
TEST(AdjacencyListTest, NegativeKruskal) {
  AdjacencyList g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, 2, 5);
  g.set_edge(1, -2, 3);
  g.set_edge(1, 2, 4);
  g.set_edge(2, 3, 4);
  AdjacencyList tree(6);
  g.kruskal_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

TEST(AdjacencyListTest, CyclicKruskal) {
  AdjacencyList g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 1, 4);
  g.set_edge(4, 1, 5);
  g.set_edge(5, 1, 0);
  g.set_edge(0, -2, 2);
  g.set_edge(0, -3, 3);
  g.set_edge(1, -2, 4);
  AdjacencyList tree(6);
  g.kruskal_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0) or tree.has_edge(4, 5) or tree.has_edge(5, 4));
  ASSERT_EQ(true, tree.has_edge(0, 3) or tree.has_edge(3, 0));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------
TEST(AdjacencyMatrixTest, BasicDijkstraShortestPath) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 6, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(3, 3, 2);
  g.set_edge(0, 4, 3);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

// TODO: Add two additional shortest path tests
TEST(AdjacencyMatrixTest, LoopDijkstra) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(1, 2, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 10, 4);
  g.set_edge(4, 3, 0);
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(4, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(7, path_costs[3]);
  ASSERT_EQ(17, path_costs[4]);
}

TEST(AdjacencyMatrixTest, DisconnectedDijkstra) {
  AdjacencyMatrix g(8);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(3, 5, 2);
  g.set_edge(4, 5, 6);
  g.set_edge(6, 1, 5);
  g.set_edge(5, 6, 7);
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(2, path_costs[1]);
  ASSERT_EQ(8, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
  ASSERT_EQ(INT_MAX, path_costs[4]);
  ASSERT_EQ(INT_MAX, path_costs[5]);
  ASSERT_EQ(INT_MAX, path_costs[6]);
  ASSERT_EQ(INT_MAX, path_costs[7]);
  path_costs.clear();
  g.dijkstra_shortest_path(4, path_costs);
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[4]);
  ASSERT_EQ(6, path_costs[5]);
  ASSERT_EQ(5, path_costs[6]);
  ASSERT_EQ(12, path_costs[7]);
  ASSERT_EQ(INT_MAX, path_costs[0]);
  ASSERT_EQ(INT_MAX, path_costs[1]);
  ASSERT_EQ(INT_MAX, path_costs[2]);
  ASSERT_EQ(INT_MAX, path_costs[3]);
}

TEST(AdjacencyMatrixTest, BasicPrimMinSpanningTree) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(0, 4, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(2, 5, 3);
  AdjacencyMatrix tree(4);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
}

// TODO: Add two additional tests for Prim's algorithm
TEST(AdjacencyMatrixTest, NegativePrim) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, 2, 5);
  g.set_edge(1, -2, 3);
  g.set_edge(1, 2, 4);
  g.set_edge(2, 3, 4);
  AdjacencyMatrix tree(6);
  g.prim_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

TEST(AdjacencyMatrixTest, CyclicPrim) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 1, 4);
  g.set_edge(4, 1, 5);
  g.set_edge(5, 1, 0);
  g.set_edge(0, -2, 2);
  g.set_edge(0, -3, 3);
  g.set_edge(1, -2, 4);
  AdjacencyMatrix tree(6);
  g.prim_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0) or tree.has_edge(4, 5) or tree.has_edge(5, 4));
  ASSERT_EQ(true, tree.has_edge(0, 3) or tree.has_edge(3, 0));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

TEST(AdjacencyMatrixTest, BasicKruskalMinSpanningTree) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 3, 2);
  g.set_edge(1, 5, 3);
  g.set_edge(1, 1, 4);  
  g.set_edge(2, 6, 3);  
  g.set_edge(3, 7, 4);
  AdjacencyMatrix tree(5);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

// TODO: Add two additional tests for Kruskal's algorithm
TEST(AdjacencyMatrixTest, NegativeKruskal) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, 2, 5);
  g.set_edge(1, -2, 3);
  g.set_edge(1, 2, 4);
  g.set_edge(2, 3, 4);
  AdjacencyMatrix tree(6);
  g.kruskal_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

TEST(AdjacencyMatrixTest, CyclicKruskal) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 1, 4);
  g.set_edge(4, 1, 5);
  g.set_edge(5, 1, 0);
  g.set_edge(0, -2, 2);
  g.set_edge(0, -3, 3);
  g.set_edge(1, -2, 4);
  AdjacencyMatrix tree(6);
  g.kruskal_min_spanning_tree(tree);
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(0, 5) or tree.has_edge(5, 0) or tree.has_edge(4, 5) or tree.has_edge(5, 4));
  ASSERT_EQ(true, tree.has_edge(0, 3) or tree.has_edge(3, 0));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

// TODO: Add your tests above but for your adjacency matrix


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

