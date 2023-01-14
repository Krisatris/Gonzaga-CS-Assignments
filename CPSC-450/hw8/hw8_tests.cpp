//----------------------------------------------------------------------
// Name: 
// File: hw8_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for list and matrix graph implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <gtest/gtest.h>
#include <bits/stdc++.h>
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

TEST(AdjacencyListTest, BasicPositiveWeightBellmanFordShortesPath) {
  AdjacencyList g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 6, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(3, 3, 2);
  g.set_edge(0, 4, 3);  
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

TEST(AdjacencyListTest, BasicNegativeWeightBellmanFordShortesPath) {
  AdjacencyList g(5);
  g.set_edge(0, 6, 1);
  g.set_edge(0, 7, 3);
  g.set_edge(1, 5, 2);
  g.set_edge(1, 8, 3);
  g.set_edge(1, -4, 4);
  g.set_edge(2, -2, 1);
  g.set_edge(3, -3, 2);
  g.set_edge(3, 9, 4);  
  g.set_edge(4, 7, 2);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(2, path_costs[1]);
  ASSERT_EQ(4, path_costs[2]);
  ASSERT_EQ(7, path_costs[3]);
  ASSERT_EQ(-2, path_costs[4]);
}


// TODO: Add two additional shortest path tests
TEST(AdjacencyListTest, LoopBellmanFord) {
  AdjacencyList g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(1, 2, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 10, 4);
  g.set_edge(4, 3, 0);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(4, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(7, path_costs[3]);
  ASSERT_EQ(17, path_costs[4]);
}

TEST(AdjacencyListTest, DisconnectedBellmanFord) {
  AdjacencyList g(8);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(3, 5, 2);
  g.set_edge(4, 5, 6);
  g.set_edge(6, 1, 5);
  g.set_edge(5, 6, 7);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
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
  ASSERT_EQ(true, g.bellman_ford_shortest_path(4, path_costs));
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

TEST(AdjacencyListTest, NegativeBellmanFord) {
  AdjacencyList g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, 2, 5);
  g.set_edge(1, -2, 3);
  g.set_edge(1, 2, 4);
  g.set_edge(2, 3, 4);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(-1, path_costs[2]);
  ASSERT_EQ(-1, path_costs[3]);
  ASSERT_EQ(2, path_costs[4]);
  ASSERT_EQ(2, path_costs[5]);
}

TEST(AdjacencyListTest, CyclicBellmanFord) {
  AdjacencyList g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 1, 4);
  g.set_edge(4, 1, 5);
  g.set_edge(5, 1, 0);
  g.set_edge(2, -3, 0);
  g.set_edge(0, -4, 3);
  g.set_edge(1, -2, 4);
  Map path_costs;
  ASSERT_EQ(false, g.bellman_ford_shortest_path(0, path_costs));
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(-5, path_costs[0]);
  ASSERT_EQ(-3, path_costs[1]);
  ASSERT_EQ(-2, path_costs[2]);
  ASSERT_EQ(-8, path_costs[3]);
  ASSERT_EQ(-7, path_costs[4]);
  ASSERT_EQ(-6, path_costs[5]);
}

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------
TEST(AdjacencyMatrixTest, BasicPositiveWeightBellmanFordShortesPath) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 6, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(3, 3, 2);
  g.set_edge(0, 4, 3);  
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

TEST(AdjacencyMatrixTest, BasicNegativeWeightBellmanFordShortesPath) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 6, 1);
  g.set_edge(0, 7, 3);
  g.set_edge(1, 5, 2);
  g.set_edge(1, 8, 3);
  g.set_edge(1, -4, 4);
  g.set_edge(2, -2, 1);
  g.set_edge(3, -3, 2);
  g.set_edge(3, 9, 4);  
  g.set_edge(4, 7, 2);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(2, path_costs[1]);
  ASSERT_EQ(4, path_costs[2]);
  ASSERT_EQ(7, path_costs[3]);
  ASSERT_EQ(-2, path_costs[4]);
}


// TODO: Add two additional shortest path tests
TEST(AdjacencyMatrixTest, LoopBellmanFord) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(1, 2, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 10, 4);
  g.set_edge(4, 3, 0);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(4, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(7, path_costs[3]);
  ASSERT_EQ(17, path_costs[4]);
}

TEST(AdjacencyMatrixTest, DisconnectedBellmanFord) {
  AdjacencyMatrix g(8);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(3, 5, 2);
  g.set_edge(4, 5, 6);
  g.set_edge(6, 1, 5);
  g.set_edge(5, 6, 7);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
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
  ASSERT_EQ(true, g.bellman_ford_shortest_path(4, path_costs));
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

TEST(AdjacencyMatrixTest, NegativeBellmanFord) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(0, -1, 2);
  g.set_edge(0, 2, 5);
  g.set_edge(1, -2, 3);
  g.set_edge(1, 2, 4);
  g.set_edge(2, 3, 4);
  Map path_costs;
  ASSERT_EQ(true, g.bellman_ford_shortest_path(0, path_costs));
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(-1, path_costs[2]);
  ASSERT_EQ(-1, path_costs[3]);
  ASSERT_EQ(2, path_costs[4]);
  ASSERT_EQ(2, path_costs[5]);
}

TEST(AdjacencyMatrixTest, CyclicBellmanFord) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 1, 4);
  g.set_edge(4, 1, 5);
  g.set_edge(5, 1, 0);
  g.set_edge(2, -3, 0);
  g.set_edge(0, -4, 3);
  g.set_edge(1, -2, 4);
  Map path_costs;
  ASSERT_EQ(false, g.bellman_ford_shortest_path(0, path_costs));
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  ASSERT_EQ(-5, path_costs[0]);
  ASSERT_EQ(-3, path_costs[1]);
  ASSERT_EQ(-2, path_costs[2]);
  ASSERT_EQ(-8, path_costs[3]);
  ASSERT_EQ(-7, path_costs[4]);
  ASSERT_EQ(-6, path_costs[5]);
}

// TODO: Add your tests above but for your adjacency matrix


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

