//----------------------------------------------------------------------
// Name: Stella Beemer
// File: hw1_tests.cpp
// Date: Spring 2021
// Desc: Unit tests experiments.
//----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>


using namespace std;


// TODO: 
// Merge helper for mergesort
// Assumes A1 length is n1 and A2 length is n2
void merge(int A[], size_t start, size_t mid, size_t end)
{
  // declare iterating vars and temp array
  int temp[end - start + 1];
  int i = start;
  int j = mid + 1;
  int k = 0;

  // merge temp array
  while(i <= mid && j <= end) {
    if(A[i] <= A[j]) {
      temp[k] = A[i];
      i++;
    } else {
      temp[k] = A[j];
      j++;
    }
    k++;
  }

  // fill in temp array if still items in first sublist
  while(i <= mid) {
    temp[k] = A[i];
    k++;
    i++;
  }

  // fill in temp array if still items in second sublist
  while(j <= end) {
    temp[k] = A[j];
    k++;
    j++;
  }

  // copy temp array into A
  for(i = start; i <= end; ++i) {
    A[i] = temp[i - start];
  }
}


// TODO: 
// Basic array-based merge sort
// Assumes A is of length n
void merge_sort(int A[], size_t start, size_t end)
{
  if(start < end) {
    int mid = (start + end) / 2;
    merge_sort(A, start, mid);
    merge_sort(A, mid + 1, end);
    merge(A, start, mid, end);
  }
}


// Test 1 (example)
TEST(ProvidedTest, Test1) {
  string s = "Hello World!";
  ASSERT_EQ(12, s.size());
  ASSERT_NE(13, s.size());
}


// Test 2 (example)
TEST(ProvidedTest, Test2) {
  int A[] = {1, 2, 3, 4, 5};
  size_t n = 5; 
  // check that the array is in ascending (sorted) order
  for (int i = 0; i < n - 1; ++i) {
    int v = A[i];
    ASSERT_LT(v, A[i + 1]);
  }
}


// very short merge test w/ 3 elements
TEST(MergeTest, Test1) {
  int A[] = {10, 20, 15};
  merge(A, 0, 1, 2);
  ASSERT_EQ(A[0], 10);
  ASSERT_EQ(A[1], 15);
  ASSERT_EQ(A[2], 20);
}


/*
  larger merge test w/ 10 elements
  merge would not be called on a list as unsorted as this one
  but wanted to test with more elements
*/
TEST(MergeTest, Test2) {
  int A[] = {963, 444, 186, 962, 718, 917, 783, 444, 180, 904};
  merge(A, 0, 4, 9);
  ASSERT_EQ(A[0], 917);
  ASSERT_EQ(A[1], 783);
  ASSERT_EQ(A[2], 444);
  ASSERT_EQ(A[3], 180);
  ASSERT_EQ(A[4], 904);
  ASSERT_EQ(A[5], 963);
  ASSERT_EQ(A[6], 444);
  ASSERT_EQ(A[7], 186);
  ASSERT_EQ(A[8], 962);
  ASSERT_EQ(A[9], 718);
}


// merge sort w/10 elements and one double entry (444)
TEST(MergeSortTest, Test1) {
  int A[] = {963, 444, 186, 962, 718, 917, 783, 444, 180, 904};
  merge_sort(A, 0, 9);
  size_t n = 10;
  for (int i = 0; i < n - 1; ++i) {
    int v = A[i];
    ASSERT_LE(v, A[i + 1]);
  }
}


// larger sort test w/100 elements in descending order
TEST(MergeSortTest, Test2) {
  int A[100];
  for(int i = 0; i < 99; ++i) {
    A[i] = 100 - i;
  }
  merge_sort(A, 0, 99);
  for(int j = 0; j < 99; ++j) {
    int v = A[j];
    ASSERT_LE(v, A[j + 1]);
  }
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

