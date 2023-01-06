//----------------------------------------------------------------------
// Author: Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 9
// File:   hw9_test.cpp
//
// TODO:   add your own description
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "bst_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  BSTCollection<string,double> c;
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
  BSTCollection<string,double> c;
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
  BSTCollection<string,int> c;
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
  ASSERT_EQ(false, c.find("d", v));  
}


// Test 4
TEST(BasicListTest, SimpleRange) {
  BSTCollection<int,string> c;
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
  BSTCollection<string,int> c;
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
  BSTCollection<int, int> c;
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
  BSTCollection<int, string> c;
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
  BSTCollection<int, string> c;
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

// sort does not remove any keys that are already in 
// the passed in vector, this makes sure they're still there.
TEST(VectorCollectionTest, FullVectorSort) {
  BSTCollection<int, string> c;
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
  ASSERT_EQ(8, vi.size());
  for (int i = 0; i < int(vi.size()) - 1; ++i)
    ASSERT_LE(vi[i], vi[i+1]);
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 1));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 2));
}

// range find DOES NOT remove any extra values that are in the
// passed in vector, test makes sure they are still there
TEST(VectorCollectionTest, FullVectorFind) {
  BSTCollection<int, string> c;
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


// LINKED LIST COLLECTION TESTS
// copy constructor test
TEST(LinkedListCollection, CopyConstructor) {
  BSTCollection<int, int> c;
  for(int i = 5; i > 0; --i) {
    c.add(i, i*100);
  }
  BSTCollection<int, int> d = c;
  ASSERT_EQ(5, d.size());
  ASSERT_EQ(5, c.size());
  vector<int> vi;
  d.keys(vi);
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 5));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 4));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 3));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 2));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 1));
}

// assignment operator test
TEST(LinkedListCollection, AssignmentOperator) {
  BSTCollection<int, int> c;
  for(int i = 5; i > 0; --i) {
    c.add(i, i*100);
  }
  BSTCollection<int, int> d;
  d = c;
  ASSERT_EQ(5, d.size());
  ASSERT_EQ(5, c.size());
  vector<int> vi;
  d.keys(vi);
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 5));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 4));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 3));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 2));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 1));
}

// assignment operator edge case of setting a collection
// equal to itself
TEST(LinkedListCollection, EqualAssignment) {
  BSTCollection<int, int> c;
  for(int i = 5; i > 0; --i) {
    c.add(i, i*100);
  }
  c = c;
  ASSERT_EQ(5, c.size());
  vector<int> vi;
  c.keys(vi);
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 5));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 4));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 3));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 2));
  ASSERT_NE(vi.end(), find(vi.begin(), vi.end(), 1));
}


// Binsearch tests
TEST(BinSearchTest, RemoveNonexistantElems) {
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("e");
  ASSERT_EQ(4, c.size());
  ASSERT_EQ(false, c.find("e", v));
  c.remove("f");
  ASSERT_EQ(4, c.size());
  ASSERT_EQ(false, c.find("f", v));  
  c.remove("g");
  ASSERT_EQ(4, c.size());
  ASSERT_EQ(false, c.find("g", v));  
  c.remove("h");
  ASSERT_EQ(4, c.size());
  ASSERT_EQ(false, c.find("h", v));  
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(true, c.find("d", v));
}

// keys does not remove elems in passed in vector
// allowing the user to return many copies of keys
// (if they wanted to for some crazy reason)
TEST(BinSearchTest, ReturnTooManyKeys) {
  BSTCollection<int, int> c;
  for(int i = 10; i > 0; --i) {
    c.add(i, i*100);
  }
  vector<int> keys;
  c.keys(keys);
  c.keys(keys);
  c.keys(keys);
  c.keys(keys);
  ASSERT_EQ(10, c.size());
  ASSERT_EQ(40, keys.size());
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 1));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 2));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 3));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 4));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 5));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 6));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 7));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 8));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 9));
  ASSERT_NE(keys.end(), find(keys.begin(), keys.end(), 10));
}


// tests that removing elements from the collection
// that are in the middle of a chain works correctly
TEST(HashTableCollection, CopyRemove)
{
  BSTCollection<int, int> c;
  c.add(105, 5123);
  c.add(100, 591);
  c.add(417, 329131);
  c.add(3281, 5321);
  c.add(312, 9401);
  c.add(859429, 391);
  c.add(666, 420);
  c.add(528, 3281);
  c.add(537, 32193);
  c.add(31, 3219);
  c.add(318, 328);
  c.add(9924, 5832);
  BSTCollection<int, int> d = c;
  ASSERT_EQ(12, d.size());
  ASSERT_EQ(12, c.size());
  d.remove(417);
  ASSERT_EQ(11, d.size());
  ASSERT_EQ(12, c.size());
  d.remove(100);
  ASSERT_EQ(10, d.size());
  ASSERT_EQ(12, c.size());
  d.remove(537);
  ASSERT_EQ(9, d.size());
  ASSERT_EQ(12, c.size());
}


// this test creates a copied list 
TEST(HashTableCollection, RemoveInChain)
{
  BSTCollection<int, int> c;
  c.add(105, 5123);
  c.add(100, 591);
  c.add(417, 329131);
  c.add(3281, 5321);
  c.add(312, 9401);
  c.add(859429, 391);
  c.add(666, 420);
  c.add(528, 3281);
  c.add(537, 32193);
  c.add(31, 3219);
  c.add(318, 328);
  c.add(9924, 5832);
  ASSERT_EQ(12, c.size());
  c.remove(417);
  ASSERT_EQ(11, c.size());
  c.remove(100);
  ASSERT_EQ(10, c.size());
  c.remove(537);
  ASSERT_EQ(9, c.size());
}

TEST(BSTTest, SimpleHeightTest) {
  BSTCollection<string, int> c;
  c.add("d", 40);
  c.add("b", 20);
  c.add("f", 60);
  c.add("a", 10);
  c.add("c", 30);
  c.add("z", 260);
  c.add("y", 250);
  ASSERT_EQ(4, c.height());
}

TEST(BSTTest, LongHeightTest) { // tracing this sucked
  BSTCollection<int, int> c;
  c.add(68, 100);
  c.add(28, 100);
  c.add(18, 100);
  c.add(97, 100);
  c.add(60, 100); // 5
  c.add(29, 100);
  c.add(38, 100);
  c.add(19, 100);
  c.add(32, 100);
  c.add(87, 100); // 10
  c.add(10, 100);
  c.add(48, 100);
  c.add(8, 100);
  c.add(33, 100);
  c.add(92, 100); // 15
  c.add(37, 100);
  c.add(30, 100);
  c.add(74, 100);
  c.add(70, 100);
  c.add(98, 100); // 20
  ASSERT_EQ(20, c.size());
  ASSERT_EQ(8, c.height());
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

