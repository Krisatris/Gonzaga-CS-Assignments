//----------------------------------------------------------------------
// Author: Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 6
// File:   linked_list_collection.h
//
// TODO: Description here
//----------------------------------------------------------------------


#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"


template<typename K, typename V>
class LinkedListCollection : public Collection<K,V>
{
public:

  // constructor to initialize empty linked list
  LinkedListCollection();

  // copy constructor
  LinkedListCollection(const LinkedListCollection<K,V>& rhs);

  // assignment operator
  LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs);
  
  // destructor to delete a linked list
  ~LinkedListCollection();
  
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

  // in place sorting 
  void selection_sort();
  void insertion_sort();
  
private:
  
  // linked list node structure
  struct Node {
    K key;
    V value;
    Node* next;
  };
  Node* head;
  Node* tail;
  int length;

  void make_empty();

};

  // constructor to initialize empty linked list
  template<typename K, typename V>
  LinkedListCollection<K, V>::LinkedListCollection()
  {
    head = nullptr;
    tail = nullptr;
    length = 0;
  }

  // copy constructor
  template<typename K, typename V>
  LinkedListCollection<K, V>::LinkedListCollection(const LinkedListCollection<K,V>& rhs)
  {
    head = nullptr;
    tail = nullptr;
    length = 0;
    Node* tmp = rhs.head;
    while(tmp != nullptr)
    {
      add(tmp->key, tmp->value);
      tmp = tmp->next;
    }
    tmp = nullptr;
  }

  // assignment operator
  template<typename K, typename V>
  LinkedListCollection<K,V>& LinkedListCollection<K, V>::operator=(const LinkedListCollection<K,V>& rhs)
  {
    if(head == rhs.head)
    {
      return *this;
    }
    make_empty();
    Node* tmp = rhs.head;
    while(tmp != nullptr)
    {
      add(tmp->key, tmp->value);
      tmp = tmp->next;
    }
    tmp = nullptr;
    return *this;
  }
  
  // destructor to delete a linked list
  template<typename K, typename V>
  LinkedListCollection<K, V>::~LinkedListCollection()
  {
    while(length > 0)
    {
      remove(head->key);
    }
  }
  
  // add a new key-value pair into the collection (at the tail)
  template<typename K, typename V>
  void LinkedListCollection<K, V>::add(const K& a_key, const V& a_val)
  {
    Node* tmp = new Node;
    tmp->key = a_key;
    tmp->value = a_val;
    tmp->next = nullptr;
    if(head == NULL) 
    {
      head = tmp;
      tail = tmp;
    } else 
    {
      tail->next = tmp;
      tail = tail->next;
    }
    tmp = nullptr;
    length++;
  }

  // remove a key-value pair from the collections
  template<typename K, typename V>
  void LinkedListCollection<K, V>::remove(const K& a_key)
  {
    if(head->key == a_key) // edge case if key is equal to head key
    {
      Node* tmp = head->next;
      delete head;
      head = tmp;
      tmp = nullptr;
      length--;
      return;
    } else if(tail->key == a_key) // edge case if key is equal to tail key
    {
      Node* tmp = head;
      while(tmp->next != tail) 
        tmp = tmp->next;
      tail = tmp;
      delete tmp->next;
      length--;
      tmp = nullptr;
      tail->next = nullptr;
    } else 
    {
      Node* prev = head;
      Node* cur = head;
      while(cur->key != a_key && cur->next != nullptr)
      {
        prev = cur;
        cur = cur->next;
      }
      if(cur->key == a_key) // check to make sure code is deleting an actual element in list
      {
        prev->next = cur->next;
        delete cur;
        prev = nullptr;
        length--;
      }
    }
  }

  // find and return the value associated with the key
  template<typename K, typename V>
  bool LinkedListCollection<K, V>::find(const K& search_key, V& the_val) const
  {
    Node* tmp = head;
    while(tmp != nullptr)
    {
      if(tmp->key == search_key)
      {
        the_val = tmp->value;
        tmp = nullptr;
        return true;
      }
      tmp = tmp->next;
    }
    tmp = nullptr;
    return false;
  }

  // find and return the values with keys >= to k1 and <= to k2 
  template<typename K, typename V>
  void LinkedListCollection<K, V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
  {
    Node* tmp = head;
    while(tmp != nullptr)
    {
      if(tmp->key >= k1 && tmp->key <= k2)
      {
        vals.push_back(tmp->value);
      }
      tmp = tmp->next;
    }
    tmp = nullptr;
  }
  
  // return all of the keys in the collection 
  template<typename K, typename V>
  void LinkedListCollection<K, V>::keys(std::vector<K>& all_keys) const
  {
    Node* tmp = head;
    while(tmp != nullptr)
    {
      all_keys.push_back(tmp->key);
      tmp = tmp->next;
    }
    tmp = nullptr;
  }

  // return all of the keys in ascending (sorted) order
  template<typename K, typename V>
  void LinkedListCollection<K, V>::sort(std::vector<K>& all_keys_sorted) const
  {
    keys(all_keys_sorted);
    std::sort(all_keys_sorted.begin(), all_keys_sorted.end());
  }

  // return the number of key-value pairs in the collection
  template<typename K, typename V>
  int LinkedListCollection<K, V>::size() const 
  {
    return length;
  }

  template<typename K, typename V>
  void LinkedListCollection<K, V>::make_empty() 
  {
    while(length > 0)
    {
      remove(head->key);
    }
    head = nullptr;
    tail = nullptr;
  }

// TODO: Implement the two "in place" sorting algorithms below

template<typename K, typename V>
void LinkedListCollection<K,V>::selection_sort()
{
  // define nodes for iteratoring and swapping
  Node* presorted;
  Node* sorted = head;
  Node* least = sorted;
  Node* preleast;
  Node* iterator = sorted;

  // find nodes to be swapped
  while(sorted->next) 
  {
    while(iterator->next)
    {
      if((least->key) > (iterator->next->key))
      {
        least = iterator->next;
        preleast = iterator;
      }
      iterator = iterator->next;
    }
    
    // the swaping

    // if nodes are right next to each other
    if(sorted->next == least) 
    {
      // if sorted is head, head needs to be redifined
      if(sorted == head)
      {
        sorted->next = least->next;
        least->next = sorted;
        sorted = least;
        head = sorted;
      }
      // if sorted is not head but nodes are together
      else
      {
        sorted->next = least->next;
        least->next = sorted;
        presorted->next = least;
        sorted = least;
      }
    }
    // if there is an unknown num of nodes between nodes to swap
    else if(least != sorted)
    {
      // if sorted is the head of the list
      if(sorted == head)
      {
        iterator = sorted->next;
        sorted->next = least->next;
        least->next = iterator;
        preleast->next = sorted;
        sorted = least;
        head = sorted;
      }
      // if sorted is not the head of the list
      else
      {
        iterator = sorted->next;
        sorted->next = least->next;
        least->next = iterator;
        preleast->next = sorted;
        presorted->next = least;
        sorted = least;
      }
    }

    // reset nodes to prepare for next loop through
    presorted = sorted;
    sorted = sorted->next;
    iterator = sorted;
    least = sorted;
  }

  iterator = head;
  while(iterator->next != nullptr)
  {
    iterator = iterator->next;
  }
  tail = iterator;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort()
{
  // define nodes for iteratoring and insertion
  Node* presorted;
  Node* sorted = head;
  Node* least = sorted;
  Node* preleast;
  Node* iterator = sorted;

  // find least node
  while(sorted->next != nullptr) 
  {
    while(iterator->next != nullptr)
    {
      if((least->key) > (iterator->next->key))
      {
        least = iterator->next;
        preleast = iterator;
      }
      iterator = iterator->next;
    }    
    
    // the inserting

    // the first insert
    if(sorted == head)
    {
      if(sorted == least)
      {
        sorted = sorted->next;
      } else 
      {
      preleast->next = preleast->next->next;
      least->next = sorted;
      head = least;
      }
    }
    // if there is no lower node to insert before sorted
    else if(sorted == least)
    {
      sorted = sorted->next;
    }
    // every other case
    else
    {
      preleast->next = preleast->next->next;
      least->next = sorted;
      presorted->next = least;
    }

    // resesetting pointers for next loop through
    presorted = least;
    least = sorted;
    iterator = sorted;
  }

  // redefine the tail pointer
  iterator = head;
  while(iterator->next != nullptr)
  {
    iterator = iterator->next;
  }
  tail = iterator;
}


#endif
