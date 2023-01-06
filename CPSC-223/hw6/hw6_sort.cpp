//----------------------------------------------------------------------
// Author: S Bowers
// Course: CPSC 223, Spring 2020
// Assign: 6
// File:   hw6_sort.cpp
//
// Simple program to test and time different in-place linked list
// sorting algorithms. 
//----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>
#include "linked_list_collection.h"

using namespace std;
using namespace std::chrono;

typedef pair<string,double> pair_t;


const int SEL_SORT = 0;
const int INS_SORT = 1;
// const int QCK_SORT = 2;
// const int MRG_SORT = 3;

void do_sort(const vector<pair_t>& kv_pairs, int type)
{
  // create collection
  LinkedListCollection<string,double> c;
  for (pair_t p : kv_pairs)
    c.add(p.first, p.second);
  // time sort
  if (type == SEL_SORT) {
    auto start = high_resolution_clock::now();
    c.selection_sort();
    auto end = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(end - start);
    cout << "  Selection Sort.: " << time.count() << " microseconds" << endl;
  }
  else if (type == INS_SORT) {
    auto start = high_resolution_clock::now();
    c.insertion_sort();
    auto end = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(end - start);
    cout << "  Insertion Sort.: " << time.count() << " microseconds" << endl;
  }
  // else if (type == QCK_SORT) {
  //   auto start = high_resolution_clock::now();
  //   c.quick_sort();
  //   auto end = high_resolution_clock::now();
  //   auto time = duration_cast<microseconds>(end - start);
  //   cout << "  Quick Sort.....: " << time.count() << " microseconds" << endl;
  // }
  // else if (type == MRG_SORT) {
  //   auto start = high_resolution_clock::now();
  //   c.merge_sort();
  //   auto end = high_resolution_clock::now();
  //   auto time = duration_cast<microseconds>(end - start);
  //   cout << "  Merge Sort.....: " << time.count() << " microseconds" << endl;
  // }
  // check correctness
  vector<string> ks;
  c.keys(ks);
  assert(ks.size() == c.size());
  assert(kv_pairs.size() == ks.size());
  for (auto i = 0; i < ks.size() - 1; ++i) {
    assert(ks[i] <= ks[i+1]);
  }
}


int main(int argc, char** argv)
{
  if (argc != 3) {
    cout << "usage: " << argv[0] << " (q | m | i) filename " << endl;
    return 1;
  }
  // load the data
  vector<pair_t> kv_pairs;
  fstream in_file;
  in_file.open(argv[2]);
  while (in_file) {
    string op;
    in_file >> op;
    if (op == "add") {
      string key;
      double val;
      in_file >> key;
      in_file >> val;
      pair_t p(key, val);
      kv_pairs.push_back(p);
    }
  }
  // run the sort algos
  if (string(argv[1]) == "s")
    do_sort(kv_pairs, SEL_SORT);
  else if (string(argv[1]) == "i")
    do_sort(kv_pairs, INS_SORT);
  // else if (string(argv[1]) == "q")
  //   do_sort(kv_pairs, QCK_SORT);
  // else if (string(argv[1]) == "m") 
  //   do_sort(kv_pairs, MRG_SORT);

}
