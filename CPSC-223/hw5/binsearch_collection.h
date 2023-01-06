//----------------------------------------------------------------------
// Author: Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 5
// File:   binsearch_collection.h
//
// TODO: Vector-based binsearch collection used to store key-value pairs
//----------------------------------------------------------------------

#ifndef BINSEARCH_COLLECTION_H
#define BINSEARCH_COLLECTION_H

#include <vector>
#include <algorithm>            
#include "collection.h"


template<typename K, typename V>
class BinSearchCollection : public Collection<K,V>
{
public:

  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

private:

  // helper function for binary search
  bool binsearch(const K& key, int& index) const;

  // vector storage
  std::vector<std::pair<K,V>> kv_list;

};

  // add a new key-value pair into the collection 
  template<typename K, typename V>
  void BinSearchCollection<K,V>::add(const K& a_key, const V& a_val){
    std::pair<K, V> pair_one;
    pair_one.first = a_key;
    pair_one.second = a_val;
    if(kv_list.size() == 0) {
      kv_list.push_back(pair_one);
      return;
    } else if(kv_list[kv_list.size() - 1].first < a_key) {
      kv_list.push_back(pair_one);
      return;
    }
    int insert;
    binsearch(a_key, insert);
    if(insert == 0 && kv_list[insert].first < a_key) {
      ++insert; // catches bug in small collections where elements can be inserted wrong
    }
    kv_list.insert(kv_list.begin() + insert, pair_one);
  }

  // remove a key-value pair from the collections
  template<typename K, typename V>
  void BinSearchCollection<K,V>::remove(const K& a_key) {
    int index;
    if(binsearch(a_key, index)) {
      kv_list.erase(kv_list.begin() + index);
    }
  }

  // find and return the value associated with the key
  template<typename K, typename V>
  bool BinSearchCollection<K,V>::find(const K& search_key, V& the_val) const {
    int index;
    if(binsearch(search_key, index)) {
      the_val = kv_list[index].second;
      return true;
    } else {
      return false;
    }
  }

  // find and return the values with keys >= to k1 and <= to k2 
  template<typename K, typename V>
  void BinSearchCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const {
    int startIndex;
    int endIndex;
    binsearch(k1, startIndex); 
    binsearch(k2, endIndex);
    if(kv_list[startIndex].first < k1) {
      ++startIndex;
    }
    if(kv_list[endIndex].first > k2) {
      --endIndex;
    }
    for(int i = startIndex; i <= endIndex; ++i) {
      vals.push_back(kv_list[i].second);
    }
  }
  
  // return all of the keys in the collection 
  template<typename K, typename V>
  void BinSearchCollection<K,V>::keys(std::vector<K>& all_keys) const {
    int unsigned i;
    for(i = 0; i < kv_list.size(); ++i)
    {
      all_keys.push_back(kv_list[i].first);
    }
  }

  // return all of the keys in ascending (sorted) order
  template<typename K, typename V>
  void BinSearchCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const {
    keys(all_keys_sorted);
  }

  // return the number of key-value pairs in the collection
  template<typename K, typename V>
  int BinSearchCollection<K,V>::size() const {
    return kv_list.size();
  }

  // helper function for binary search
  template<typename K, typename V>
  bool BinSearchCollection<K,V>::binsearch(const K& key, int& index) const {
    int top = 0;
    int bottom = kv_list.size() - 1;
    int middle;
    while(top <= bottom) {
      middle = (top + bottom) / 2;
      if(kv_list[middle].first == key) {
        index = middle;
        return true;
      } else if(kv_list[middle].first > key) {
        bottom = middle - 1;
      } else if (kv_list[middle].first < key) {
        top = middle + 1;
      }
    }
    index = middle;
    return false;
  }

#endif
