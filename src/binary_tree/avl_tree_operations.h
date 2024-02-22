// This file provides only operations to work with self-balancing
// binary AVL trees (https://en.wikipedia.org/wiki/AVL_tree)
// It's based on th article: https://habr.com/ru/articles/150732/

#ifndef S21_CONTAINERS_AVL_TREE_OPERATIONS_H_  // NOLINT
#define S21_CONTAINERS_AVL_TREE_OPERATIONS_H_  // NOLINT

#ifdef DEBUG
#include <iostream>
#endif  // DEBUG

namespace s21 {

template <typename T>
struct Node {
  explicit Node(const T& data) noexcept
      : data_(data), left_(nullptr), right_(nullptr), height_(1) {}

  T data_;
  Node* left_;
  Node* right_;
  unsigned char height_;
};

template <typename K, typename T>
class AvlTreeOperations {
  typedef K (*FuncPtr)(const T& data);

 public:
  explicit AvlTreeOperations(FuncPtr key_extractor);

  inline unsigned char Height(Node<T>* p) const noexcept;
  inline int BFactor(Node<T>* p) const noexcept;
  inline void FixHeight(Node<T>* p) const noexcept;

  Node<T>* RotateRight(Node<T>* p) const;
  Node<T>* RotateLeft(Node<T>* p) const;
  Node<T>* Balance(Node<T>* p) const;
  Node<T>* InsertNode(Node<T>* p, Node<T>* node) const;
  Node<T>* Insert(Node<T>* p, T k) const;
  Node<T>* FindMin(Node<T>* p) const;
  Node<T>* FindMax(Node<T>* p) const;
  Node<T>* Find(Node<T>* p, K key) const;
  Node<T>* RemoveMin(Node<T>* p) const;
  Node<T>* ExtractNode(Node<T>* root, Node<T>* node) const;
  Node<T>* Remove(Node<T>* p, Node<T>* node) const;
  Node<T>* Copy(Node<T>* p) const;
  Node<T>* Clear(Node<T>* p) const;
  Node<T>* Next(Node<T>* root, Node<T>* p) const;
  Node<T>* Prev(Node<T>* root, Node<T>* p) const;

  void Print(Node<T>* p, int level = 0) const;

 private:
  // Function to extract the key from the node data.
  // The key is used to arrange the nodes of the tree.
  // By default the data are itself the key, but we can
  // change it using differnt ExtractKey functions.
  FuncPtr ExtractKey{[](const T& data) -> K { return data; }};
};

// Constructor takes key_extractor function as an argument
// and stores it as 'ExtractKey' function.
template <typename K, typename T>
AvlTreeOperations<K, T>::AvlTreeOperations(FuncPtr key_extractor)
    : ExtractKey(key_extractor) {}

template <typename K, typename T>
inline unsigned char AvlTreeOperations<K, T>::Height(
    Node<T>* p) const noexcept {
  return p ? p->height_ : 0;
}

template <typename K, typename T>
inline int AvlTreeOperations<K, T>::BFactor(Node<T>* p) const noexcept {
  return Height(p->right_) - Height(p->left_);
}

inline int Max(int a, int b) noexcept { return a > b ? a : b; }

template <typename K, typename T>
inline void AvlTreeOperations<K, T>::FixHeight(Node<T>* p) const noexcept {
  p->height_ = Max(Height(p->left_), Height(p->right_)) + 1;
}

// Return a pointer to the next node (ascending order)
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Next(Node<T>* root, Node<T>* p) const {
  if (p == nullptr) {
    return nullptr;
  } else if (p->right_) {
    // Find the minimum value in the right subtree
    p = FindMin(p->right_);
  } else {
    // Find the nearest parent node w with greater value
    Node<T>* w = nullptr;
    Node<T>* q = root;
    while (q != p) {
      if (ExtractKey(p->data_) < ExtractKey(q->data_)) {
        w = q;
        q = q->left_;
      } else {
        q = q->right_;
      }
    }
    p = w;
  }
  return p;
}

// Return a pointer to the previous node
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Prev(Node<T>* root, Node<T>* p) const {
  if (!p) {
    // It's the end() iterator! We are to find the last
    // node (with the greatest value)
    p = FindMax(root);
  } else if (p->left_) {
    // Find the maximum value in the left subtree
    p = FindMax(p->left_);
  } else {
    // Find the nearest parent node w with less value
    Node<T>* w = nullptr;
    Node<T>* q = root;
    while (q != p) {
      if (ExtractKey(p->data_) < ExtractKey(q->data_)) {
        q = q->left_;
      } else {
        w = q;
        q = q->right_;
      }
    }
    p = w;
  }
  return p;
}

template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::RotateRight(Node<T>* p) const {
  Node<T>* q = p->left_;
  p->left_ = q->right_;
  q->right_ = p;
  FixHeight(p);
  FixHeight(q);
  return q;
}

template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::RotateLeft(Node<T>* p) const {
  Node<T>* q = p->right_;
  p->right_ = q->left_;
  q->left_ = p;
  FixHeight(p);
  FixHeight(q);
  return q;
}

// Balances tree.
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Balance(Node<T>* p) const {
  FixHeight(p);
  if (BFactor(p) == 2) {
    if (BFactor(p->right_) < 0) p->right_ = RotateRight(p->right_);
    return RotateLeft(p);
  }
  if (BFactor(p) == -2) {
    if (BFactor(p->left_) > 0) p->left_ = RotateLeft(p->left_);
    return RotateRight(p);
  }
  return p;
}

// Insert an existing node into the tree.
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::InsertNode(Node<T>* p, Node<T>* node) const {
  if (!p) return node;
  K key = ExtractKey(node->data_);
  if (key < ExtractKey(p->data_))
    p->left_ = InsertNode(p->left_, node);
  else
    p->right_ = InsertNode(p->right_, node);
  return Balance(p);
}

template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Insert(Node<T>* p, T data) const {
  Node<T>* node = new Node<T>(data);
  return InsertNode(p, node);
}

template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::FindMin(Node<T>* p) const {
  return p->left_ ? FindMin(p->left_) : p;
}

template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::FindMax(Node<T>* p) const {
  return p->right_ ? FindMax(p->right_) : p;
}

// Returns the pointer to the node with the specified key
// or nullptr if there is no such node.
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Find(Node<T>* p, K key) const {
  if (!p) return nullptr;
  K root_key = ExtractKey(p->data_);
  if (key < root_key)
    return Find(p->left_, key);
  else if (key > root_key)
    return Find(p->right_, key);
  return p;
}

template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::RemoveMin(Node<T>* p) const {
  if (p->left_ == 0) return p->right_;
  p->left_ = RemoveMin(p->left_);
  return Balance(p);
}

// Just extracts the node from the tree (does not delete it's memory).
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::ExtractNode(Node<T>* p, Node<T>* node) const {
  if (!p) return nullptr;
  K p_key = ExtractKey(p->data_);
  K node_key = ExtractKey(node->data_);
  if (node_key < p_key) {
    p->left_ = ExtractNode(p->left_, node);
  } else if (node_key > p_key) {
    p->right_ = ExtractNode(p->right_, node);
  } else {
    Node<T>* q = node->left_;
    Node<T>* r = node->right_;

    node->left_ = nullptr;
    node->right_ = nullptr;

    if (!r) return q;
    Node<T>* min = FindMin(r);
    min->right_ = RemoveMin(r);
    min->left_ = q;
    return Balance(min);
  }
  return Balance(p);
}

template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Remove(Node<T>* p, Node<T>* node) const {
  Node<T>* ret = ExtractNode(p, node);
  if (node) delete node;
  return ret;
}

// Makes a deep copy of ther tree and returns it's root
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Copy(Node<T>* p) const {
  if (!p) return nullptr;
  Node<T>* t = new Node<T>(p->data_);
  t->left_ = Copy(p->left_);
  t->right_ = Copy(p->right_);
  return t;
}

// Deletes all the nodes in the three and free memory
template <typename K, typename T>
Node<T>* AvlTreeOperations<K, T>::Clear(Node<T>* p) const {
  if (p) {
    Clear(p->left_);
    Clear(p->right_);
    delete p;
  }
  return nullptr;
}

template <typename K, typename T>
std::ostream& operator<<(std::ostream& out, const std::pair<K, T>& p) {
  return out << p.first << "[" << p.second << "]";
}

#ifdef DEBUG
template <typename K, typename T>
void AvlTreeOperations<K, T>::Print(Node<T>* p, int level) const {
  if (p) {
    Print(p->right_, level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << p->data_ << std::endl;
    Print(p->left_, level + 1);
  }
}
#endif  // DEBUG

}  // namespace s21

#endif  // S21_CONTAINERS_AVL_TREE_OPERATIONS_H_  // NOLINT
