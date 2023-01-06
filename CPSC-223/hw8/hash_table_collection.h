
//----------------------------------------------------------------------
// Author: Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 8
// File:   hash_table_collection.h
// ...
//----------------------------------------------------------------------

 
#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"


template<typename K, typename V>
class HashTableCollection : public Collection<K,V>
{
public:

  // create an empty hash table with default number of buckets
  HashTableCollection();

  // hash table copy constructor
  HashTableCollection (const HashTableCollection <K,V>& rhs);

  // hash table assignment operator
  HashTableCollection <K,V>& operator=(const HashTableCollection <K ,V >& rhs);

  // delete a linked list
  ~HashTableCollection();
  
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

  // helper to empty entire hash table
  void make_empty();
  
  // helper to resize and rehash the hash table
  void resize_and_rehash();
  
  // linked list node structure
  struct Node {
    K key;
    V value;
    Node* next;
  };
  
  // number of k-v pairs in the collection
  int collection_size;

  // number of hash table buckets (default is 16)
  int table_capacity;

  // hash table array load factor (set at 75% for resizing)
  double load_factor_threshold;

  // hash table array
  Node** hash_table;
   
};


// create an empty hash table with default number of buckets
template<typename K, typename V>
HashTableCollection<K, V>::HashTableCollection()
{
  table_capacity = 16;
  hash_table = new Node*[table_capacity];
  for(int i = 0; i < table_capacity; ++i)
  {
    hash_table[i] = nullptr;
  }
  collection_size = 0;
  load_factor_threshold = double(table_capacity) * 0.75;
}

// hash table copy constructor
template<typename K, typename V>
HashTableCollection<K, V>::HashTableCollection(const HashTableCollection <K,V>& rhs)
{
  table_capacity = rhs.table_capacity;
  collection_size = rhs.collection_size;
  load_factor_threshold = rhs.load_factor_threshold;
  hash_table = new Node*[table_capacity];
  for(int i = 0; i < table_capacity; ++i)
  {
    hash_table[i] = nullptr;
  }
  for(int j = 0; j < table_capacity; ++j)
  {
    Node* rhs_temp = rhs.hash_table[j];
    Node* lhs_temp = hash_table[j];
    if(rhs_temp)
    {
      Node* temp = new Node;
      temp->key = rhs_temp->key;
      temp->value = rhs_temp->value;
      temp->next = nullptr;
      hash_table[j] = temp;
      lhs_temp = temp;
      rhs_temp = rhs_temp->next;
    }
    while(rhs_temp)
    {
      Node* temp = new Node;
      temp->key = rhs_temp->key;
      temp->value = rhs_temp->value;
      temp->next = nullptr;
      lhs_temp->next = temp;
      lhs_temp = lhs_temp->next;
      rhs_temp = rhs_temp->next;
    }
  }
}

// hash table assignment operator
template<typename K, typename V>
HashTableCollection<K, V>& HashTableCollection<K, V>::operator=(const HashTableCollection <K ,V >& rhs)
{
  if(this == &rhs)
  {
    return *this;
  }
  HashTableCollection<K, V> temp(rhs);
  std::swap(hash_table, temp.hash_table);
  std::swap(load_factor_threshold, temp.load_factor_threshold);
  std::swap(table_capacity, temp.table_capacity);
  std::swap(collection_size, temp.collection_size);
  return *this;
}

// delete a linked list
template<typename K, typename V>
HashTableCollection<K, V>::~HashTableCollection()
{
  make_empty();
  delete hash_table;
}
  
// add a new key-value pair into the collection
template<typename K, typename V>
void HashTableCollection<K, V>::add(const K& a_key, const V& a_val)
{
  if(collection_size > load_factor_threshold)
  {
    resize_and_rehash();
  }
  std::hash<K> hash_fun;
  size_t value = hash_fun(a_key);
  size_t index = value % table_capacity;
  Node* insert = new Node;
  insert->key = a_key;
  insert->value = a_val;
  insert->next = hash_table[index];
  hash_table[index] = insert;
  ++collection_size;
}

// remove a key-value pair from the collection
template<typename K, typename V>
void HashTableCollection<K, V>::remove(const K& a_key)
{
  std::hash<K> hash_fun;
  size_t value = hash_fun(a_key);
  size_t index = value % table_capacity;
  Node* temp = hash_table[index];
  Node* prev = temp;
  while(temp && temp->key != a_key)
  {
    prev = temp;
    temp = temp->next;
  }
  if(temp)
  {
    --collection_size;
    if(temp == hash_table[index])
    {
      hash_table[index] = temp->next;
    } else
    {
      prev->next = temp->next;
    }
    delete temp;
  }
}

// find and return the value associated with the key
template<typename K, typename V>
bool HashTableCollection<K, V>::find(const K& search_key, V& the_val) const
{
  std::hash<K> hash_fun;
  size_t value = hash_fun(search_key);
  size_t index = value % table_capacity;

  Node* iterator = hash_table[index];
  while(iterator)
  {
    if(iterator->key == search_key)
    {
      the_val = iterator->value;
      return true;
    }
    iterator = iterator->next;
  }
  return false;
}

// find and return the values with keys >= to k1 and <= to k2
template<typename K, typename V>
void HashTableCollection<K, V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  Node* iterator = nullptr;
  for(int i = 0; i < table_capacity; ++i)
  {
    iterator = hash_table[i];
    while(iterator)
    {
      if(iterator->key >= k1 && iterator->key <= k2)
      {
        vals.push_back(iterator->value);
      }
      iterator = iterator->next;
    }
  }
}
  
// return all of the keys in the collection
template<typename K, typename V>
void HashTableCollection<K, V>::keys(std::vector<K>& all_keys) const
{
  Node* iterator = nullptr;
  for(int i = 0; i < table_capacity; ++i)
  {
    iterator = hash_table[i];
    while(iterator)
    {
      all_keys.push_back(iterator->key);
      iterator = iterator->next;
    }
  }
}

// return all of the keys in ascending (sorted) order
template<typename K, typename V>
void HashTableCollection<K, V>::sort(std::vector<K>& all_keys_sorted) const
{
  keys(all_keys_sorted);
  std::sort(all_keys_sorted.begin(), all_keys_sorted.end());
}

// return the number of key-value pairs in the collection
template<typename K, typename V>
int HashTableCollection<K, V>::size() const
{
  for(int i = 0; i < table_capacity; ++i)
  {
    Node* iterator = hash_table[i];
    while(iterator)
    {
      iterator = iterator->next;
    }
  }
  return collection_size;
}

// helper to empty entire hash table
template<typename K, typename V>
void HashTableCollection<K, V>::make_empty()
{
  int i = 0;
  while(collection_size > 0)
  {
    while(hash_table[i])
    {
      remove(hash_table[i]->key);
    }
    ++i;
  }
}
  
// helper to resize and rehash the hash table
template<typename K, typename V>
void HashTableCollection<K, V>::resize_and_rehash()
{
  // redefine table capacity and new table
  int old_table_capacity = table_capacity;
  table_capacity = old_table_capacity * 2;
  Node** new_table = new Node*[table_capacity];
  for(int i = 0; i < table_capacity; ++i)
  {
    new_table[i] = nullptr;
  }

  // define variables needed for rehashing
  std::hash<K> hash_fun;

  // rehash table
  for(int j = 0; j < old_table_capacity; ++j)
  {
    Node* iterator;
    while(hash_table[j])
    {
      // get key and index for insert
      iterator = hash_table[j];
      K curr_key = iterator->key;
      size_t value = hash_fun(curr_key);
      size_t index = value % table_capacity;

      // create new node
      Node* insert = new Node;
      insert->key = curr_key;
      insert->value = iterator->value;
      insert->next = new_table[index];
      new_table[index] = insert;

      // delete node in old table
      hash_table[j] = iterator->next;
      delete iterator;
    }
  }

  // change pointers and update load factor
  delete hash_table;
  hash_table = new_table;
  load_factor_threshold = double(table_capacity) * 0.75;
}

#endif