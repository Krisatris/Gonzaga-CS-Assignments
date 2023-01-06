//----------------------------------------------------------------------
// Author: Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 7
// File:   linked_list_collection.h
//
// TODO: Linked List collection that implements merge and quick
//       sort
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
  void merge_sort();
  void quick_sort();
  
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

  // helper to delete linked list (optional)
  void make_empty();

  // helper functions for merge and quick sort
  Node* merge_sort(Node* left, int len);
  Node* merge(Node* left, Node* right);
  Node* quick_sort(Node* start, int len);

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
    while(head)
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

template<typename K, typename V>
void LinkedListCollection<K,V>::merge_sort()
{
  head = merge_sort(head, length);
  if(tail)
  {
    while(tail->next)
    {
      tail = tail->next;
    }
  }
} 

template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::merge_sort(Node* left, int len)
{
  if(len <= 1)
  {
    return left;
  } else 
  {
    int iterator = (len - 1) / 2;
    int mid = len / 2;
    Node* prev = left;
    for(int i = 0; i < iterator; ++i) 
    {
      prev = prev->next;
    }
    Node* tmp = prev->next;
    prev->next = nullptr;
    left = merge_sort(left, len - mid);
    tmp = merge_sort(tmp, mid);
    return merge(left, tmp);
  }
}

template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::merge(Node* left, Node* right)
{
  Node* iterator = nullptr;
  Node* sorted = nullptr;
  Node* first1 = left;
  Node* first2 = right;

  if(first1 && first2)
  {
    if(first1->key < first2->key)
    {
      sorted = first1;
      first1 = first1->next;
    } else
    {
      sorted = first2;
      first2 = first2->next;
    }
    iterator = sorted;
  }

  while(first1 && first2)
  {
    if(first1->key < first2->key)
    {
      iterator->next = first1;
      first1 = first1->next;
    } else
    {
      iterator->next = first2;
      first2 = first2->next;
    }
    iterator = iterator->next;

  }
  if(first1)
  {
    iterator->next = first1;
  } else 
  {
    iterator->next = first2;
  }
  return sorted;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::quick_sort()
{
  head = quick_sort(head, length);
  if(tail)
  {
    while(tail->next)
    {
      tail = tail->next;
    }
  }
}

template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::quick_sort(Node* start, int len)
{
  if(len <= 1) {
    return start;
  } else if(len == 2)
  {
    Node* tmp = start->next;
    if(start->key > tmp->key)
    {
      tmp->next = start;
      start->next = nullptr;
      start = tmp;
    }
    return start;
  } else 
  {
    Node* pivot = start;
    K& pivotKey = pivot->key;
    Node* right = nullptr;
    Node* rightTail = nullptr;
    Node* left = nullptr;
    Node* leftTail = nullptr;
    Node* iterator = start->next;
    pivot->next = nullptr;
    int leftCounter = 0;
    while(iterator)
    {
      if(pivotKey < iterator->key)
      {
        if(!right)
        {
          right = iterator;
          rightTail = right;
        } else
        {
          rightTail->next = iterator;
          rightTail = rightTail->next;
        }
      } else
      {
        if(!left)
        {
          left = iterator;
          leftTail = left;
        } else
        {
          leftTail->next = iterator;
          leftTail = leftTail->next;
        }
        ++leftCounter;
      }
      iterator = iterator->next;
    }
    if(leftTail)
      leftTail->next = nullptr;
    if(rightTail)
      rightTail->next = nullptr;
    if(leftCounter > 1)
      start = quick_sort(left, leftCounter);
    else
      start = left;
    if((len - leftCounter - 1) > 1)
      right = quick_sort(right, len - leftCounter - 1);
    if(leftTail)
    {
      while(leftTail->next)
      {
        leftTail = leftTail->next;
      }
      leftTail->next = pivot;
    }
    else
    {
      start = pivot;
    }
    pivot->next = right;
    return start;
  }
}


#endif
