
//----------------------------------------------------------------------
// Author: Stella Beemer
// Course: CPSC 223, Spring 2020
// Assign: 10
// File:   avl_collection.h
// ...
//----------------------------------------------------------------------


#ifndef AVL_COLLECTION_H
#define AVL_COLLECTION_H

#include <vector>
#include <algorithm>
#include <string>               // for testing
#include "collection.h"


template<typename K, typename V>
class AVLCollection : public Collection<K,V>
{
public:

  // create an empty tree
  AVLCollection();
  
  // tree copy constructor
  AVLCollection(const AVLCollection<K,V>& rhs);

  // tree assignment operator
  AVLCollection<K,V>& operator=(const AVLCollection<K,V>& rhs);

  // delete a tree
  ~AVLCollection();
  
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

  // return the height of the tree
  int height() const;
  
private:
  
  // avl tree node structure
  struct Node {
    K key;
    V value;
    int height;
    Node* left;
    Node* right;
  };

  // helper to empty entire tree
  void make_empty(Node* subtree_root);
  
  // helper to build sorted list of keys (used by keys and sort)
  void inorder(const Node* subtree_root, std::vector<K>& keys) const;

  // helper to recursively find range of values
  void range_search(const Node* subtree_root, const K& k1, const K& k2,
                    std::vector<V>& vals) const;

  // recursively (deep) copy ancestors of src to dst
  void preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst);

  // helper function to remove a node recursively
  Node* remove(const K& key, Node* subtree_root);

  // recursive add helper
  Node* add(Node* subtree_root, const K& a_key, const V& a_val);
  
  // rotate right helper
  Node* rotate_right(Node* k2);

  // rotate left helper
  Node* rotate_left(Node* k2);

  // rebalance the subtree rooted at subtree_root
  Node* rebalance(Node* subtree_root);
  
  // number of k-v pairs in the collection
  int tree_size; 

  // root node of tree
  Node* root;

  // for testing only: "pretty" prints a tree with node heights
  void print_tree(std::string indent, Node* subtree_root);
};

// create an empty tree
template<typename K, typename V>
AVLCollection<K, V>::AVLCollection()
{
  root = nullptr;
  tree_size = 0;
}

// tree copy constructor
template<typename K, typename V>
AVLCollection<K, V>::AVLCollection(const AVLCollection<K, V> &rhs)
{
  root = nullptr;
  tree_size = 0;
  if(rhs.tree_size > 0)
  {
    Node* tmp_root = new Node;
    tmp_root->key = rhs.root->key;
    tmp_root->value = rhs.root->value;
    tmp_root->right = nullptr;
    tmp_root->left = nullptr;
    tmp_root->height = rhs.root->height;
    root = tmp_root;
    *this = rhs;
  }
}

// tree assignment operator
template<typename K, typename V>
AVLCollection<K, V>& AVLCollection<K, V>::operator=(const AVLCollection<K, V> &rhs)
{
  if(this == &rhs)
  {
    return *this;
  }
  if(root) 
  {
    make_empty(root->left);
    make_empty(root->right);
  }
  else
  {
    Node* tmp = new Node;
    tmp->right = nullptr;
    tmp->left = nullptr;
    root = tmp;
  }
  root->key = rhs.root->key;
  root->value = rhs.root->value;
  root->height = rhs.root->height;
  preorder_copy(rhs.root, root);
  tree_size = rhs.tree_size;

  return *this;
}

// delete a tree
template<typename K, typename V>
AVLCollection<K, V>::~AVLCollection()
{
  make_empty(root);
  tree_size = 0;
}

template<typename K, typename V>
void AVLCollection<K,V>::add(const K& a_key, const V& a_val)
{
  // to build in the height and rebalance, this must be a recursive
  // function!
  root = add(root, a_key, a_val);
  ++tree_size;
  // print_tree("", root); // for debugging
}

template <typename K, typename V>
void AVLCollection<K,V>::remove(const K& a_key)
{
  root = remove(a_key, root);
  // print_tree("", root); // for debugging
}

// find and return the value associated with the key
template<typename K, typename V>
bool AVLCollection<K, V>::find(const K &search_key, V &the_val) const
{
  Node* tmp = root;
  while(tmp)
  {
    if(search_key < tmp->key)
    {
      tmp = tmp->left;
    }
    else if(search_key > tmp->key)
    {
      tmp = tmp->right;
    }
    else {
      the_val = tmp->value;
      return true;
    }
  }
  return false;
}

// find and return the values with keys >= to k1 and <= to k2
template<typename K, typename V>
void AVLCollection<K, V>::find(const K &k1, const K &k2, std::vector<V> &vals) const
{
  range_search(root, k1, k2, vals);
}

// return all of the keys in the collection
template<typename K, typename V>
void AVLCollection<K, V>::keys(std::vector<K> &all_keys) const
{
  inorder(root, all_keys);
}

// return all of the keys in ascending (sorted) order
template<typename K, typename V>
void AVLCollection<K, V>::sort(std::vector<K> &all_keys_sorted) const
{
  inorder(root, all_keys_sorted);
}

// return the number of key-value pairs in the collection
template<typename K, typename V>
int AVLCollection<K, V>::size() const
{
  return tree_size;
}

// to see how height should work
template<typename K, typename V> 
int AVLCollection<K,V>::height() const
{
  if (!root) {
    return 0;
  }
  return root->height;
}

// helper to empty entire tree
template<typename K, typename V> 
void AVLCollection<K,V>::make_empty(Node *subtree_root)
{
  if(subtree_root)
  {
    if(subtree_root->left)
      make_empty(subtree_root->left);
    if(subtree_root->right)
      make_empty(subtree_root->right);
    if(subtree_root->right && subtree_root->left)
    {
      delete subtree_root;
      return;
    }
  }
}

// helper to build sorted list of keys (used by keys and sort)
template<typename K, typename V> 
void AVLCollection<K,V>::inorder(const Node *subtree_root, std::vector<K> &keys) const
{
  if(subtree_root)
  {
    inorder(subtree_root->left, keys);
    keys.push_back(subtree_root->key);
    inorder(subtree_root->right, keys);
  }
}

// helper to recursively find range of values
template<typename K, typename V> 
void AVLCollection<K,V>::range_search(const Node *subtree_root, const K &k1, const K &k2,
                  std::vector<V> &vals) const
{
  if(!subtree_root)
    return;
  if(k1 < subtree_root->key)
    range_search(subtree_root->left, k1, k2, vals);
  if(k1 <= subtree_root->key && k2 >= subtree_root->key)
    vals.push_back(subtree_root->value);
  if(k2 > subtree_root->key)
    range_search(subtree_root->right, k1, k2, vals);
}

// recursively (deep) copy ancestors of src to dst
template<typename K, typename V> 
void AVLCollection<K,V>::preorder_copy(const Node *subtree_root_src, Node *subtree_root_dst)
{
  if(subtree_root_src->left)
  {
    Node* tmp = new Node;
    tmp->key = subtree_root_src->left->key;
    tmp->value = subtree_root_src->left->value;
    tmp->height = subtree_root_src->left->height;
    subtree_root_dst->left = tmp;
    preorder_copy(subtree_root_src->left, tmp);
  }
  else
  {
    subtree_root_dst->left = nullptr;
  }
  if(subtree_root_src->right)
  {
    Node* tmp = new Node;
    tmp->key = subtree_root_src->right->key;
    tmp->value = subtree_root_src->right->value;
    tmp->height = subtree_root_src->right->height;
    subtree_root_dst->right = tmp;
    preorder_copy(subtree_root_src->right, tmp);
  }
  else 
  {
    subtree_root_dst->right = nullptr;
  }
}

template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::add(Node* subtree_root, const K& a_key, const V& a_val)
{
  if(!subtree_root)
  {
    Node* tmp = new Node;
    tmp->key = a_key;
    tmp->value = a_val;
    tmp->height = 1;
    tmp->left = nullptr;
    tmp->right = nullptr;
    return tmp;
  }
  if(a_key < subtree_root->key)
    subtree_root->left = add(subtree_root->left, a_key, a_val);
  else
    subtree_root->right = add(subtree_root->right, a_key, a_val);
  return rebalance(subtree_root);
}  

template <typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::remove(const K& key, Node* subtree_root)
{
  if(subtree_root && key < subtree_root->key)
  {
    subtree_root->left = remove(key, subtree_root->left);
    subtree_root = rebalance(subtree_root);
  } 
  else if(subtree_root && key > subtree_root->key)
  {
    subtree_root->right = remove(key, subtree_root->right);
    subtree_root = rebalance(subtree_root);
  } 
  else if(subtree_root && key == subtree_root->key)
  {
    Node* right_side = subtree_root->right;
    Node* left_side = subtree_root->left;
    if(!right_side || !left_side)
    {
      delete subtree_root;
      --tree_size;
      return (left_side) ? left_side : right_side;
    }
    else
    {
      Node* tmp = subtree_root->right;
      while(tmp->left)
        tmp = tmp->left;
      subtree_root->key = tmp->key;
      subtree_root->value = tmp->value;
      subtree_root->height = tmp->height;
      subtree_root->right = remove(tmp->key, subtree_root->right);
      subtree_root = rebalance(subtree_root);
      return subtree_root;
    }
  } 
  return subtree_root;
}

// from class
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_right(Node* k2)
{
  Node* k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  Node* right_side = k2->right;
  Node* left_side = k2->left;
  int left_height = (left_side) ? left_side->height : 0;
  int right_height = (right_side) ? right_side->height : 0;
  k2->height = 1 + ((left_height < right_height) ? right_height : left_height);
  return k1;
}

// from class
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_left(Node* k2)
{
  Node* k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;
  Node* right_side = k2->right;
  Node* left_side = k2->left;
  int left_height = (left_side) ? left_side->height : 0;
  int right_height = (right_side) ? right_side->height : 0;
  k2->height = 1 + ((left_height < right_height) ? right_height : left_height);
  return k1;
}

template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rebalance(Node* subtree_root)
{
  if(!subtree_root) {
    return subtree_root;
  }
  Node* left_side = subtree_root->left;
  Node* right_side = subtree_root->right;
  int left_height = (left_side) ? left_side->height : 0;
  int right_height = (right_side) ? right_side->height : 0;
  subtree_root->height = 1 + ((left_height < right_height) ? right_height : left_height);
  int balance = left_height - right_height;

  if (balance == -2) {
    Node* temp = subtree_root->right;
    left_side = temp->left;
    right_side = temp->right;

    left_height = (left_side) ? left_side->height : 0;
    right_height = (right_side) ? right_side->height : 0;

    balance = left_height - right_height;

    if(balance > 0)
    {
      temp = rotate_right(temp);
      subtree_root->right = temp;
    }

    subtree_root = rotate_left(subtree_root);
  } else if(balance == 2) {
    Node* temp = subtree_root->left;
    left_side = temp->left;
    right_side = temp->right;

    left_height = (left_side) ? left_side->height : 0;
    right_height = (right_side) ? right_side->height : 0;

    balance = left_height - right_height;

    if(balance < 0)
    {
      temp = rotate_left(temp);
      subtree_root->left = temp;
    }
  
    subtree_root = rotate_right(subtree_root);
  }
  left_side = subtree_root->left;
  right_side = subtree_root->right;
  left_height = (left_side) ? left_side->height : 0;
  right_height = (right_side) ? right_side->height : 0;
  subtree_root->height = 1 + ((left_height < right_height) ? right_height : left_height);
  return subtree_root;
}

template<typename K, typename V>
void AVLCollection<K,V>::print_tree(std::string indent, Node* subtree_root)
{
  if (!subtree_root)
    return;
  std::cout << indent << subtree_root->key << " (h="
            << subtree_root->height << ")" << std::endl;
  print_tree(indent + "  ", subtree_root->left);
  print_tree(indent + "  ", subtree_root->right);
}


#endif
