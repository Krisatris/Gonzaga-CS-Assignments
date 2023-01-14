//----------------------------------------------------------------------
// Name: 
// File: hw9_tests.cpp
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

void print_weight_vector(const vector<vector<int>>& weights, int n) {
  for (int u = 0; u < n; ++u) {
    for (int v = 0; v < n; ++v) {
      if (weights[u][v] == std::numeric_limits<int>::max())
        cout << "inf" << " ";
      else
        cout << weights[u][v] << " ";
    }
    cout << endl;
  }
}


//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

TEST(AdjacencyListTest, BasicMaxIndependentSet) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  Set S;
  int weights[4] = {1, 4, 5, 4};
  ASSERT_EQ(true, g.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(2, S.size());
  // check members
  ASSERT_EQ(true, S.count(1));
  ASSERT_EQ(true, S.count(3));
}

TEST(AdjacencyListTest, SmallMaxIndependentSet) {
  AdjacencyList g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  Set S;
  int weights[6] = {3, 2, 1, 6, 4, 5};
  ASSERT_EQ(true, g.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(3, S.size());
  // check members
  ASSERT_EQ(true, S.count(0));
  ASSERT_EQ(true, S.count(3));
  ASSERT_EQ(true, S.count(5));
}

// TODO: Add two additional max independent set tests
TEST(AdjacencyListTest, LargeIndependantSet) {
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
  Set S;
  int weights[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  ASSERT_EQ(true, g.path_max_independent_set(weights, S));
  ASSERT_EQ(5, S.size());
  ASSERT_EQ(true, S.count(0));
  ASSERT_EQ(true, S.count(2));
  ASSERT_EQ(true, S.count(4));
  ASSERT_EQ(true, S.count(6));
  ASSERT_EQ(true, S.count(8));
}

TEST(AdjacencyListTest, InvalidIndependantSet) {
  AdjacencyList g1(4);
  g1.set_edge(0, 0, 1);
  g1.set_edge(1, 0, 3);
  g1.set_edge(2, 0, 3);
  Set S;
  int weights[4] = {1, 4, 5, 4};
  ASSERT_EQ(false, g1.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(0, S.size());
  // check members
  AdjacencyList g2(4);
  g2.set_edge(0, 0, 1);
  g2.set_edge(1, 0, 2);
  g2.set_edge(2, 0, 3);
  g2.set_edge(3, 0, 0);
  S.clear();
  ASSERT_EQ(false, g2.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(0, S.size());
}

TEST(AdjacencyListTest, BasicAllPairsShortestPaths) {
  AdjacencyList g(5);
  g.set_edge(0, -10, 1);
  g.set_edge(0, 2, 3);
  g.set_edge(1, -10, 2);
  g.set_edge(3, -4, 4);
  g.set_edge(4, 5, 2);
  vector<vector<int>> weights;
  ASSERT_EQ(true, g.all_pairs_shortest_paths(weights));
  // Note that you can call the following to help debug: 
  //   print_weight_vector(weights, 5);
  ASSERT_EQ(-10, weights[0][1]);
  ASSERT_EQ(-20, weights[0][2]);
  ASSERT_EQ(2, weights[0][3]);
  ASSERT_EQ(-2, weights[0][4]);
  ASSERT_EQ(-10, weights[1][2]);
  ASSERT_EQ(1, weights[3][2]);
  ASSERT_EQ(-4, weights[3][4]);
  ASSERT_EQ(5, weights[4][2]);
  // Note should also test MAX_INT cases above
}

// TODO: Add two additional max independent set tests
TEST(AdjacencyListTest, NegativeCycleTest) {
  AdjacencyList g(5);
  g.set_edge(0, -3, 1);
  g.set_edge(1, -2, 2);
  g.set_edge(2, -10, 3);
  g.set_edge(3, 5, 4);
  g.set_edge(4, 8, 0);
  vector<vector<int>> weights;
  ASSERT_EQ(false, g.all_pairs_shortest_paths(weights));
  ASSERT_EQ(0, weights.size());
}

TEST(AdjacencyListTest, DisconnectedShortestPaths) {
  AdjacencyList g(6);
  g.set_edge(0, 5, 1);
  g.set_edge(1, 10, 2);
  g.set_edge(0, 8, 3);
  g.set_edge(3, 2, 2);
  g.set_edge(4, 4, 5);
  vector<vector<int>> weights;
  ASSERT_EQ(true, g.all_pairs_shortest_paths(weights));
  ASSERT_EQ(5, weights[0][1]);
  ASSERT_EQ(10, weights[0][2]);
  ASSERT_EQ(8, weights[0][3]);
  ASSERT_EQ(INT_MAX, weights[0][4]);
  ASSERT_EQ(INT_MAX, weights[0][5]);
  ASSERT_EQ(10, weights[1][2]);
  ASSERT_EQ(INT_MAX, weights[1][3]);
  ASSERT_EQ(INT_MAX, weights[1][4]);
  ASSERT_EQ(INT_MAX, weights[1][5]);
  ASSERT_EQ(INT_MAX, weights[2][3]);
  ASSERT_EQ(INT_MAX, weights[2][4]);
  ASSERT_EQ(4, weights[4][5]);
  ASSERT_EQ(INT_MAX, weights[4][3]);
  ASSERT_EQ(2, weights[3][2]);
}

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------
TEST(AdjacencyMatrixTest, BasicMaxIndependentSet) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  Set S;
  int weights[4] = {1, 4, 5, 4};
  ASSERT_EQ(true, g.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(2, S.size());
  // check members
  ASSERT_EQ(true, S.count(1));
  ASSERT_EQ(true, S.count(3));
}

TEST(AdjacencyMatrixTest, SmallMaxIndependentSet) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  Set S;
  int weights[6] = {3, 2, 1, 6, 4, 5};
  ASSERT_EQ(true, g.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(3, S.size());
  // check members
  ASSERT_EQ(true, S.count(0));
  ASSERT_EQ(true, S.count(3));
  ASSERT_EQ(true, S.count(5));
}

// TODO: Add two additional max independent set tests
TEST(AdjacencyMatrixTest, LargeIndependantSet) {
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
  Set S;
  int weights[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  ASSERT_EQ(true, g.path_max_independent_set(weights, S));
  ASSERT_EQ(5, S.size());
  ASSERT_EQ(true, S.count(0));
  ASSERT_EQ(true, S.count(2));
  ASSERT_EQ(true, S.count(4));
  ASSERT_EQ(true, S.count(6));
  ASSERT_EQ(true, S.count(8));
}

TEST(AdjacencyMatrixTest, InvalidIndependantSet) {
  AdjacencyMatrix g1(4);
  g1.set_edge(0, 0, 1);
  g1.set_edge(1, 0, 3);
  g1.set_edge(2, 0, 3);
  Set S;
  int weights[4] = {1, 4, 5, 4};
  ASSERT_EQ(false, g1.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(0, S.size());
  // check members
  AdjacencyMatrix g2(4);
  g2.set_edge(0, 0, 1);
  g2.set_edge(1, 0, 2);
  g2.set_edge(2, 0, 3);
  g2.set_edge(3, 0, 0);
  S.clear();
  ASSERT_EQ(false, g2.path_max_independent_set(weights, S));
  // check size  
  ASSERT_EQ(0, S.size());
}

TEST(AdjacencyMatrixTest, BasicAllPairsShortestPaths) {
  AdjacencyMatrix g(5);
  g.set_edge(0, -10, 1);
  g.set_edge(0, 2, 3);
  g.set_edge(1, -10, 2);
  g.set_edge(3, -4, 4);
  g.set_edge(4, 5, 2);
  vector<vector<int>> weights;
  ASSERT_EQ(true, g.all_pairs_shortest_paths(weights));
  // Note that you can call the following to help debug: 
  //   print_weight_vector(weights, 5);
  ASSERT_EQ(-10, weights[0][1]);
  ASSERT_EQ(-20, weights[0][2]);
  ASSERT_EQ(2, weights[0][3]);
  ASSERT_EQ(-2, weights[0][4]);
  ASSERT_EQ(-10, weights[1][2]);
  ASSERT_EQ(1, weights[3][2]);
  ASSERT_EQ(-4, weights[3][4]);
  ASSERT_EQ(5, weights[4][2]);
  // Note should also test MAX_INT cases above
}

// TODO: Add two additional max independent set tests
TEST(AdjacencyMatrixTest, NegativeCycleTest) {
  AdjacencyMatrix g(5);
  g.set_edge(0, -3, 1);
  g.set_edge(1, -2, 2);
  g.set_edge(2, -10, 3);
  g.set_edge(3, 5, 4);
  g.set_edge(4, 8, 0);
  vector<vector<int>> weights;
  ASSERT_EQ(false, g.all_pairs_shortest_paths(weights));
  ASSERT_EQ(0, weights.size());
}

TEST(AdjacencyMatrixTest, DisconnectedShortestPaths) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 5, 1);
  g.set_edge(1, 10, 2);
  g.set_edge(0, 8, 3);
  g.set_edge(3, 2, 2);
  g.set_edge(4, 4, 5);
  vector<vector<int>> weights;
  ASSERT_EQ(true, g.all_pairs_shortest_paths(weights));
  ASSERT_EQ(5, weights[0][1]);
  ASSERT_EQ(10, weights[0][2]);
  ASSERT_EQ(8, weights[0][3]);
  ASSERT_EQ(INT_MAX, weights[0][4]);
  ASSERT_EQ(INT_MAX, weights[0][5]);
  ASSERT_EQ(10, weights[1][2]);
  ASSERT_EQ(INT_MAX, weights[1][3]);
  ASSERT_EQ(INT_MAX, weights[1][4]);
  ASSERT_EQ(INT_MAX, weights[1][5]);
  ASSERT_EQ(INT_MAX, weights[2][3]);
  ASSERT_EQ(INT_MAX, weights[2][4]);
  ASSERT_EQ(4, weights[4][5]);
  ASSERT_EQ(INT_MAX, weights[4][3]);
  ASSERT_EQ(2, weights[3][2]);
}

// TODO: Add your tests above but for your adjacency matrix


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

