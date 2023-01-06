//----------------------------------------------------------------------
// Author: Dr. Bowers & Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 3
// File:   hw3_test.cpp
//
// Purpose: This file implents 10 different unit tests to test edge
//          cases and usability for the vector_collection class
//----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "vector_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  VectorCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());

}

// Test 2
TEST(BasicListTest, SimpleFind) {
  VectorCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20.0, v);
}

// Test 3
TEST(BasicListTest, SimpleRemoveElems) {
  VectorCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 4
TEST(BasicListTest, SimpleRange) {
  VectorCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(20, 40, vs);
  ASSERT_EQ(3, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));  
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));  
}

// Test 5
TEST(BasicListTest, SimpleSort) {
  VectorCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

// test with different types than string and int
// plus large sort
TEST(VectorCollectionTest, LargeSort) {
  VectorCollection<int, int> c;
  for(int i = 100; i > 0; --i) {
    c.add(i, i*100);
  }
  vector<int> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(100, sorted_ks.size());
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
  // check that no test has altered c's size in any way
  ASSERT_EQ(100, c.size());
}

// testing for edge find case that only one value is in range
TEST(VectorCollectionTest, EdgeFind) {
  VectorCollection<int, string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(0, 15, vs);
  ASSERT_EQ(1, vs.size());
  // NE in this case will check if its there, EQ if its not
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));
  // check that no test has altered c's size in any way
  ASSERT_EQ(6, c.size());
}

// edge case test that all values are in range for find
TEST(VectorCollectionTest, EdgeFind2) {
  VectorCollection<int, string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(0, 60, vs);
  ASSERT_EQ(6, vs.size());
  // NE in this case will check if its there, EQ if its not
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "e"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "f"));
  // check that no test has altered c's size in any way
  ASSERT_EQ(6, c.size());
}

// sort removes any values that are in the passed in vector
// test makes sure that they are gone when added
TEST(VectorCollectionTest, FullVectorSort) {
  VectorCollection<int, string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<int> vi;
  vi.push_back(1);
  vi.push_back(2);
  c.sort(vi);
  ASSERT_EQ(6, c.size());
  ASSERT_EQ(6, vi.size());
  for (int i = 0; i < int(vi.size()) -1; ++i)
    ASSERT_LE(vi[i], vi[i+1]);
  ASSERT_EQ(vi.end(), find(vi.begin(), vi.end(), 1));
  ASSERT_EQ(vi.end(), find(vi.begin(), vi.end(), 2));
}

// range find DOES NOT remove any extra values that are in the
// passed in vector, test makes sure they are still there
TEST(VectorCollectionTest, FullVectorFind) {
  VectorCollection<int, string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  vs.push_back("g");
  vs.push_back("h");
  c.find(20, 40, vs);
  ASSERT_EQ(6, c.size());
  ASSERT_EQ(5, vs.size());
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "g"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "h"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

