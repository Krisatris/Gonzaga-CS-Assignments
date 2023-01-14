//----------------------------------------------------------------------
// Name: 
// File: hw1_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for list and matrix graph implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "adjacency_list.h"
#include "adjacency_matrix.h"

using namespace std;


// Tests you will need to create for your adjacency list and matrix
// implementations(see TODO comments below)
//   1. has_edge
//   2. get_edge
//   3. connected_to
//   4. connected_from
//   5. edge/boundary cases



// Helper function to check if search_val is in the_list
bool is_member(int search_val, const list<int>& the_list)
{
  for (int v : the_list)
    if (v == search_val)
      return true;
  return false;
}


//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------


// Test 1
TEST(AdjacencyListTest, CorrectSizes) {
  AdjacencyList g(3);
  ASSERT_EQ(3, g.vertex_count());
  ASSERT_EQ(0, g.edge_count());
  g.set_edge(0, -1, 1);
  ASSERT_EQ(1, g.edge_count());
  g.set_edge(1, -1, 2);
  ASSERT_EQ(2, g.edge_count());
  g.set_edge(2, -1, 0);
  ASSERT_EQ(3, g.edge_count());
  g.set_edge(0, -1, 0);
  ASSERT_EQ(4, g.edge_count());
  g.set_edge(0, 0, 0);
  ASSERT_EQ(4, g.edge_count());  
}

// Test 2
TEST(AdjacencyListTest, DestructorCall) {
  int n = 10;
  Graph* g = new AdjacencyList(n);
  for (int i = 0; i < n-1; ++i)
    g->set_edge(i, 0, i+1);
  ASSERT_EQ(n, g->vertex_count());
  ASSERT_EQ(n-1, g->edge_count());
  delete g;
}

// Test 3
TEST(AdjacencyListTest, CopyAndAssign) {
  AdjacencyList g1(3);
  g1.set_edge(0, 10, 1);
  g1.set_edge(1, 20, 2);
  ASSERT_EQ(3, g1.vertex_count());
  ASSERT_EQ(2, g1.edge_count());
  AdjacencyList g2(g1);
  g2.set_edge(2, 30, 0);
  ASSERT_EQ(3, g2.vertex_count());
  ASSERT_EQ(3, g2.edge_count());
  ASSERT_EQ(2, g1.edge_count());
  AdjacencyList g3(5);
  for (int i = 0; i < 4; ++i)
    g3.set_edge(i, 0, i+1);
  g2 = g3;
  for (int i = 0; i < 4; ++i)
    ASSERT_EQ(true, g2.has_edge(i, i+1));
}

// Test 4
TEST(AdjacencyListTest, Adjacent) {
  AdjacencyList g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  ASSERT_EQ(4, g.vertex_count());
  ASSERT_EQ(4, g.edge_count());
  list<int> vertices;
  g.adjacent(1, vertices);
  ASSERT_EQ(3, vertices.size());
  ASSERT_EQ(true, is_member(0, vertices));
  ASSERT_EQ(true, is_member(2, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
  vertices.clear();
  g.adjacent(2, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(true, is_member(1, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
  vertices.clear();
  g.adjacent(3, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(true, is_member(1, vertices));
  ASSERT_EQ(true, is_member(2, vertices));
  vertices.clear();
  g.adjacent(0, vertices);
  ASSERT_EQ(1, vertices.size());
  ASSERT_EQ(true, is_member(1, vertices));
}

// TODO: Additional Adjacency List Tests

TEST(AdjacencyListTest, HasEdge) {
  AdjacencyList g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  ASSERT_EQ(true, g.has_edge(0, 1));
  ASSERT_EQ(true, g.has_edge(1, 2));
  ASSERT_EQ(true, g.has_edge(1, 3));
  ASSERT_EQ(true, g.has_edge(3, 2));
  ASSERT_EQ(false, g.has_edge(0, 3));
  ASSERT_EQ(false, g.has_edge(3, 3));
}

TEST(AdjacencyListTest, GetEdge) {
  AdjacencyList g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  int edge;
  ASSERT_EQ(true, g.get_edge(0, 1, edge));
  ASSERT_EQ(10, edge);
  ASSERT_EQ(true, g.get_edge(1, 2, edge));
  ASSERT_EQ(20, edge);
  ASSERT_EQ(true, g.get_edge(1, 3, edge));
  ASSERT_EQ(30, edge);
  ASSERT_EQ(true, g.get_edge(3, 2, edge));
  ASSERT_EQ(40, edge);
  ASSERT_EQ(false, g.get_edge(0, 2, edge));
  ASSERT_NE(10, edge);
  ASSERT_EQ(false, g.get_edge(2, 0, edge));
  ASSERT_NE(10, edge);
}

TEST(AdjacencyListTest, ConnectedTo) {
  AdjacencyList g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  list<int> vertices;
  g.connected_to(1, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(false, is_member(0, vertices));
  ASSERT_EQ(true, is_member(2, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
}

TEST(AdjacencyListTest, ConnectedFrom) {
  AdjacencyList g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  list<int> vertices;
  g.connected_from(2, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(false, is_member(0, vertices));
  ASSERT_EQ(true, is_member(1, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
}

TEST(AdjacencyListTest, SelfCopy) {
  AdjacencyList g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  g = g;
  ASSERT_EQ(4, g.vertex_count());
  ASSERT_EQ(4, g.edge_count());
  int edge;
  ASSERT_EQ(true, g.get_edge(0, 1, edge));
  ASSERT_EQ(10, edge);
  ASSERT_EQ(true, g.get_edge(1, 2, edge));
  ASSERT_EQ(20, edge);
  ASSERT_EQ(true, g.get_edge(1, 3, edge));
  ASSERT_EQ(30, edge);
  ASSERT_EQ(true, g.get_edge(3, 2, edge));
  ASSERT_EQ(40, edge);
  ASSERT_EQ(false, g.get_edge(0, 2, edge));
  ASSERT_NE(10, edge);
  ASSERT_EQ(false, g.get_edge(2, 0, edge));
  ASSERT_NE(10, edge);
}

TEST(AdjacencyListTest, ConnectedToNothing) {
  AdjacencyList g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  list<int> vertices;
  g.connected_to(2, vertices);
  ASSERT_EQ(false, is_member(0, vertices));
  ASSERT_EQ(false, is_member(1, vertices));
  ASSERT_EQ(false, is_member(2, vertices));
  ASSERT_EQ(false, is_member(3, vertices));
}
     
//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------

// Test 1
TEST(AdjacencyMatrixTest, CorrectSizes) {
  AdjacencyMatrix g(3);
  ASSERT_EQ(3, g.vertex_count());
  ASSERT_EQ(0, g.edge_count());
  g.set_edge(0, -1, 1);
  ASSERT_EQ(1, g.edge_count());
  g.set_edge(1, -1, 2);
  ASSERT_EQ(2, g.edge_count());
  g.set_edge(2, -1, 0);
  ASSERT_EQ(3, g.edge_count());
  g.set_edge(0, -1, 0);
  ASSERT_EQ(4, g.edge_count());
  g.set_edge(0, 0, 0);
  ASSERT_EQ(4, g.edge_count());  
}

// Test 2
TEST(AdjacencyMatrixTest, DestructorCall) {
  int n = 10;
  Graph* g = new AdjacencyMatrix(n);
  for (int i = 0; i < n-1; ++i)
    g->set_edge(i, 0, i+1);
  ASSERT_EQ(n, g->vertex_count());
  ASSERT_EQ(n-1, g->edge_count());
  delete g;
}

// Test 3
TEST(AdjacencyMatrixTest, CopyAndAssign) {
  AdjacencyMatrix g1(3);
  g1.set_edge(0, 10, 1);
  g1.set_edge(1, 20, 2);
  ASSERT_EQ(3, g1.vertex_count());
  ASSERT_EQ(2, g1.edge_count());
  AdjacencyMatrix g2(g1);
  g2.set_edge(2, 30, 0);
  ASSERT_EQ(3, g2.vertex_count());
  ASSERT_EQ(3, g2.edge_count());
  ASSERT_EQ(2, g1.edge_count());
  AdjacencyMatrix g3(5);
  for (int i = 0; i < 4; ++i)
    g3.set_edge(i, 0, i+1);
  g2 = g3;
  int edge_ref;
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(true, g2.has_edge(i, i+1));
  }
}

// Test 4
TEST(AdjacencyMatrixTest, Adjacent) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  ASSERT_EQ(4, g.vertex_count());
  ASSERT_EQ(4, g.edge_count());
  list<int> vertices;
  g.adjacent(1, vertices);
  ASSERT_EQ(3, vertices.size());
  ASSERT_EQ(true, is_member(0, vertices));
  ASSERT_EQ(true, is_member(2, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
  vertices.clear();
  g.adjacent(2, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(true, is_member(1, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
  vertices.clear();
  g.adjacent(3, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(true, is_member(1, vertices));
  ASSERT_EQ(true, is_member(2, vertices));
  vertices.clear();
  g.adjacent(0, vertices);
  ASSERT_EQ(1, vertices.size());
  ASSERT_EQ(true, is_member(1, vertices));
}


// TODO: Additional Adjacency Matrix Tests
TEST(AdjacencyMatrixTest, HasEdge) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  ASSERT_EQ(true, g.has_edge(0, 1));
  ASSERT_EQ(true, g.has_edge(1, 2));
  ASSERT_EQ(true, g.has_edge(1, 3));
  ASSERT_EQ(true, g.has_edge(3, 2));
  ASSERT_EQ(false, g.has_edge(0, 3));
  ASSERT_EQ(false, g.has_edge(3, 3));
}

TEST(AdjacencyMatrixTest, GetEdge) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  int edge;
  ASSERT_EQ(true, g.get_edge(0, 1, edge));
  ASSERT_EQ(10, edge);
  ASSERT_EQ(true, g.get_edge(1, 2, edge));
  ASSERT_EQ(20, edge);
  ASSERT_EQ(true, g.get_edge(1, 3, edge));
  ASSERT_EQ(30, edge);
  ASSERT_EQ(true, g.get_edge(3, 2, edge));
  ASSERT_EQ(40, edge);
  ASSERT_EQ(false, g.get_edge(0, 2, edge));
  ASSERT_NE(10, edge);
  ASSERT_EQ(false, g.get_edge(2, 0, edge));
  ASSERT_NE(10, edge);
}

TEST(AdjacencyMatrixTest, ConnectedTo) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  list<int> vertices;
  g.connected_to(1, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(false, is_member(0, vertices));
  ASSERT_EQ(true, is_member(2, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
}

TEST(AdjacencyMatrixTest, ConnectedFrom) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  list<int> vertices;
  g.connected_from(2, vertices);
  ASSERT_EQ(2, vertices.size());
  ASSERT_EQ(false, is_member(0, vertices));
  ASSERT_EQ(true, is_member(1, vertices));
  ASSERT_EQ(true, is_member(3, vertices));
}

TEST(AdjacencyMatrixTest, SelfCopy) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  g = g;
  ASSERT_EQ(4, g.vertex_count());
  ASSERT_EQ(4, g.edge_count());
  int edge;
  ASSERT_EQ(true, g.get_edge(0, 1, edge));
  ASSERT_EQ(10, edge);
  ASSERT_EQ(true, g.get_edge(1, 2, edge));
  ASSERT_EQ(20, edge);
  ASSERT_EQ(true, g.get_edge(1, 3, edge));
  ASSERT_EQ(30, edge);
  ASSERT_EQ(true, g.get_edge(3, 2, edge));
  ASSERT_EQ(40, edge);
  ASSERT_EQ(false, g.get_edge(0, 2, edge));
  ASSERT_NE(10, edge);
  ASSERT_EQ(false, g.get_edge(2, 0, edge));
  ASSERT_NE(10, edge);
}

TEST(AdjacencyMatrixTest, ConnectedToNothing) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 10, 1);
  g.set_edge(1, 20, 2);
  g.set_edge(1, 30, 3);
  g.set_edge(3, 40, 2);
  list<int> vertices;
  g.connected_to(2, vertices);
  ASSERT_EQ(false, is_member(0, vertices));
  ASSERT_EQ(false, is_member(1, vertices));
  ASSERT_EQ(false, is_member(2, vertices));
  ASSERT_EQ(false, is_member(3, vertices));
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

