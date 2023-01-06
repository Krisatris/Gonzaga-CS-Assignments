//----------------------------------------------------------------------
// Author: Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 3
// File:   vector_collection.h
//
// Purpose: The file defines and implements all functions needed for
//          a vector-based collections class of keys and pairs
//----------------------------------------------------------------------

#ifndef VECTOR_COLLECTION_H
#define VECTOR_COLLECTION_H

#include <vector>
#include <algorithm>            
#include "collection.h"


template<typename K, typename V>
class VectorCollection : public Collection<K,V>
{
public:

  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collections
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
  std::vector<std::pair<K,V>> kv_list;
};


// add a new key-value pair into the collection 
template<typename K, typename V>
void VectorCollection<K, V>::add(const K& a_key, const V& a_val) 
{
  std::pair<K, V> pair_one;
  pair_one.first = a_key;
  pair_one.second = a_val;
  kv_list.push_back(pair_one);
}

// remove a key-value pair from the collections
template<typename K, typename V>
void VectorCollection<K, V>::remove(const K& a_key)
{
  int unsigned i;
  for(i = 0; i < kv_list.size(); ++i) 
  {
    if(kv_list[i].first == a_key)
    {
      kv_list.erase(kv_list.begin() + i);
    }
  }
}

// find and return the value associated with the key
template<typename K, typename V>
bool VectorCollection<K, V>::find(const K& search_key, V& the_val) const 
{
  int unsigned i;
  for(i = 0; i < kv_list.size(); ++i) 
  {
    if(kv_list[i].first == search_key) 
    {
      the_val = kv_list[i].second;
      return true;
    }
  }
  return false;
}

// find and return the values with keys >= to k1 and <= to k2 
template<typename K, typename V>
void VectorCollection<K, V>::find(const K& k1, const K& k2, std::vector<V>& vals) const 
{
  int unsigned i;
  for(i = 0; i < kv_list.size(); ++i) 
  {
    if(kv_list[i].first >= k1 && kv_list[i].first <= k2) 
    {
      vals.push_back(kv_list[i].second);
    }
  }
}

// return all of the keys in the collection 
template<typename K, typename V>
void VectorCollection<K, V>::keys(std::vector<K>& all_keys) const
{
  // clear vector of any keys as to not affect sort negatively
  all_keys.clear(); 
  int unsigned i;
  for(i = 0; i < kv_list.size(); ++i)
  {
    all_keys.push_back(kv_list[i].first);
  }
}

// return all of the keys in ascending (sorted) order
template<typename K, typename V>
void VectorCollection<K, V>::sort(std::vector<K>& all_keys_sorted) const
{
  keys(all_keys_sorted);
  std::sort(all_keys_sorted.begin(), all_keys_sorted.end());
}

// return the number of key-value pairs in the collection
template<typename K, typename V>
int VectorCollection<K, V>::size() const
{
  return kv_list.size();
}


#endif
