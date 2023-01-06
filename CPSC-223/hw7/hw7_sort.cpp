//----------------------------------------------------------------------
// Author: S Bowers, W Gray
// Course: CPSC 223, Spring 2020
// Assign: 7
// File:   hw7_sort.cpp
//
// Simple program to test and time different in-place linked list
// sorting algorithms.
// ----------------------------------------------------------------------

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>
#include "linked_list_collection.h"

using namespace std;
using namespace std::chrono;

typedef pair<string,double> pair_t;

// sort constants
const int SEL_SORT = 0;
const int INS_SORT = 1;
const int MRG_SORT = 2;
const int QCK_SORT = 3;

// error constants
const int INVALID_ARGS = -1;
const int INVALID_FILE = -2;
const int UNKNOWN_SORT = -3;

int timesToRun;

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
		cout << time.count() << ",";
	}
	else if (type == INS_SORT) {
		auto start = high_resolution_clock::now();
		c.insertion_sort();
		auto end = high_resolution_clock::now();
		auto time = duration_cast<microseconds>(end - start);
		cout << time.count() << ",";
	}
	else if (type == MRG_SORT) {
		auto start = high_resolution_clock::now();
		c.merge_sort();
		auto end = high_resolution_clock::now();
		auto time = duration_cast<microseconds>(end - start);
		cout << time.count() << ",";
	}
	else if (type == QCK_SORT) {
		auto start = high_resolution_clock::now();
		c.quick_sort();
		auto end = high_resolution_clock::now();
		auto time = duration_cast<microseconds>(end - start);
		cout << time.count() << ",";
	}
	// check correctness
	/*if(timesToRun == 1)
	{
		cout << " microseconds" << endl;
		vector<string> ks;
		c.keys(ks);
		assert(ks.size() == c.size());
		assert(kv_pairs.size() == ks.size());
		int size = ks.size();	// coerce unsigned int to signed int to avoid arithmetic overflow from 0-1
		for (auto i = 0; i < size - 1; ++i) {
			assert(ks[i] <= ks[i+1]);
		}
	} else {
		cout << ",";
	}*/
}

void invalid_execution(char** argv, int code)
{
	//this could be ordered with INVALID_ARGS at the bottom, and UNKNOWN_SORT without a break allowing it to fall through into INVALID_ARGS
	//this way is more clear with what each case does and ensures that if they need to change separately, no issues happen
	switch(code)
	{
		case INVALID_ARGS:
			cerr << "usage: " << argv[0] << " (s | i | m | q) filename " << endl;
			break;
		case INVALID_FILE:
			cerr << "error: invalid file '" << argv[2] << "'" << endl;
			break;
		case UNKNOWN_SORT:
			cerr << "error: unknown sort '" << argv[1] << "'" << endl;
			cerr << "usage: " << argv[0] << " (s | i | m | q) filename " << endl;
			break;
	}
	exit(1);
}

int main(int argc, char** argv)
{
	//int timesToRun;
	string sortInput;
	switch(argc) {
		case 3:
			timesToRun = 1;
			sortInput = string(argv[1]);
			break;
		case 4:
			try {
				timesToRun = stoi(string(argv[3]));
			} catch (const std::invalid_argument& e) {
				cerr << "error: " << argv[3] << " is not a number" << endl;
				invalid_execution(argv, INVALID_ARGS);
			}
			sortInput = string(argv[1]);
			break;
		default:
			invalid_execution(argv, INVALID_ARGS);
	}
	
	// load the data
	vector<pair_t> kv_pairs;
	fstream in_file;
	in_file.open(argv[2]);
	// check that the file can be opened / exists
	if (!in_file) {
		invalid_execution(argv, INVALID_FILE);
	}
	// build up the kv_pair vector
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
	int sort_type;
	// determine sort algorithm
	if (sortInput == "s")
	{
		sort_type = SEL_SORT;
		//cout << (timesToRun==1?"  ":"") << "Selection Sort" << (timesToRun==1?".: ":"");
	} else if (sortInput == "i") {
		sort_type = INS_SORT;
		//cout << (timesToRun==1?"  ":"") << "Insertion Sort" << (timesToRun==1?".: ":"");
	} else if (sortInput == "m") {
		sort_type = MRG_SORT;
		//cout << (timesToRun==1?"  ":"") << "Merge Sort" << (timesToRun==1?".....: ":"");
	} else if (sortInput == "q") {
		sort_type = QCK_SORT;
		//cout << (timesToRun==1?"  ":"") << "Quick Sort" << (timesToRun==1?".....: ":"");
	} else {
		invalid_execution(argv, UNKNOWN_SORT);
	}
	
	//execute requested number of runs, in microseconds
	for(int run = 0; run < timesToRun; run++)
	{
		do_sort(kv_pairs, sort_type);
	}
}
