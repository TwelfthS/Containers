#ifndef S21_CONTAINERS_BINARY_TREE_H_  // NOLINT
#define S21_CONTAINERS_BINARY_TREE_H_  // NOLINT

#include <initializer_list>
#include <iostream>
#include <stdexcept>

#include "avl_tree_operations.h"

namespace s21 {

template <typename Key, typename T>
class BinaryTree;

template <typename Key, typename T>
class BinaryTreeBaseIterator {
  friend class BinaryTree<Key, T>;

 public:
  BinaryTreeBaseIterator() = default;

  BinaryTreeBaseIterator(const BinaryTree<Key, T> *owner, Node<T> *p)
      : owner_(owner), p_(p) {}

  BinaryTreeBaseIterator &operator++() {
    p_ = owner_->avl_oper_.Next(owner_->root_, p_);
    return *this;
  }

  BinaryTreeBaseIterator &operator--() {
    p_ = owner_->avl_oper_.Prev(owner_->root_, p_);
    return *this;
  }

  bool operator==(BinaryTreeBaseIterator other) const { return p_ == other.p_; }
  bool operator!=(BinaryTreeBaseIterator other) const { return p_ != other.p_; }

 protected:
  // owner_ - a pointer to the tree we iterate over
  const BinaryTree<Key, T> *owner_ = nullptr;

  // p_ - a pointer to the current node
  Node<T> *p_ = nullptr;
};

template <typename Key, typename T>
class ConstBinaryTreeIterator : public BinaryTreeBaseIterator<Key, T> {
  friend class BinaryTree<Key, T>;
  using BinaryTreeBaseIterator<Key, T>::p_;

 public:
  ConstBinaryTreeIterator() = default;

  ConstBinaryTreeIterator(const BinaryTree<Key, T> *owner, Node<T> *p)
      : BinaryTreeBaseIterator<Key, T>(owner, p) {}

  typename BinaryTree<Key, T>::const_reference operator*() { return p_->data_; }

  const T *operator->() { return &(p_->data_); }
};

template <typename Key, typename T>
class BinaryTreeIterator : public BinaryTreeBaseIterator<Key, T> {
  friend class BinaryTree<Key, T>;
  using BinaryTreeBaseIterator<Key, T>::owner_;
  using BinaryTreeBaseIterator<Key, T>::p_;

 public:
  BinaryTreeIterator() = default;

  BinaryTreeIterator(const BinaryTree<Key, T> *owner, Node<T> *p)
      : BinaryTreeBaseIterator<Key, T>(owner, p) {}

  typename BinaryTree<Key, T>::reference operator*() { return p_->data_; }

  T *operator->() { return &(p_->data_); }

  // Allows conversion from an iterator to a const_iterator
  operator ConstBinaryTreeIterator<Key, T>() {
    return ConstBinaryTreeIterator<Key, T>(owner_, p_);
  }
};

// T - type of all the data to store, Key - type of the key.
// The key is used to compare and arrange nodes in the tree.
template <typename Key, typename T>
class BinaryTree {
  friend class BinaryTreeBaseIterator<Key, T>;

 public:
  // Member type
  using key_type = Key;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = BinaryTreeIterator<Key, T>;
  using const_iterator = ConstBinaryTreeIterator<Key, T>;
  using size_type = size_t;

  using key_extractor_type = Key (*)(const T &);

  // Functions
  BinaryTree() = default;
  explicit BinaryTree(key_extractor_type key_extractor);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other) noexcept;
  ~BinaryTree();
  BinaryTree &operator=(BinaryTree other);

  // Iterators
  iterator begin() const noexcept;
  iterator end() const noexcept;

  // Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(BinaryTree &other) noexcept;
  void merge(BinaryTree &other);

  // Lookup
  iterator find(const key_type &val) const noexcept;
  bool contains(const key_type &val) const noexcept;

  // Debug
  void print();

 private:
  Node<T> *root_ = nullptr;
  size_type size_ = 0;

  // It shows how to extract the key from the data
  // and by default the data are itself the key.
  key_extractor_type key_extractor_{[](const T &data) -> Key { return data; }};

  // Contains all the operations to operate with AVL-Tree.
  AvlTreeOperations<Key, T> avl_oper_{key_extractor_};
};

// Functions
template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(
    // Construct a tree with user-defined key_extractor function
    typename BinaryTree<Key, T>::key_extractor_type key_extractor)
    : root_(nullptr),
      size_(0),
      key_extractor_{key_extractor},
      avl_oper_{key_extractor} {}

// copy constructor
template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(const BinaryTree &other)
    : root_(nullptr),
      size_(other.size_),
      key_extractor_(other.key_extractor_),
      avl_oper_(other.avl_oper_) {
  root_ = avl_oper_.Copy(other.root_);
}

// move constructor
template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(BinaryTree &&other) noexcept {
  swap(other);
}

// desturctor
template <typename Key, typename T>
BinaryTree<Key, T>::~BinaryTree() {
  avl_oper_.Clear(root_);
}

// replaces copy and move operator=
// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
template <typename Key, typename T>
BinaryTree<Key, T> &BinaryTree<Key, T>::operator=(BinaryTree<Key, T> other) {
  swap(other);
  return *this;
}

// Iterators
template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::begin()
    const noexcept {
  Node<T> *p = root_;
  while (p && p->left_) p = p->left_;
  return BinaryTreeIterator<Key, T>(this, p);
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::end() const noexcept {
  return BinaryTreeIterator<Key, T>(this, nullptr);
}

// Capacity
template <typename Key, typename T>
bool BinaryTree<Key, T>::empty() const noexcept {
  return root_ == nullptr;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::size_type BinaryTree<Key, T>::size()
    const noexcept {
  return size_;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::size_type BinaryTree<Key, T>::max_size()
    const noexcept {
  return (~(size_type(0))) / sizeof(Node<T>);
}

// Modifiers
// clears the contents
template <typename Key, typename T>
void BinaryTree<Key, T>::clear() {
  root_ = avl_oper_.Clear(root_);
  size_ = 0;
}

// inserts a node and returns an iterator to where the element
// is in the container and bool denoting whether the insertion took place
template <typename Key, typename T>
std::pair<BinaryTreeIterator<Key, T>, bool> BinaryTree<Key, T>::insert(
    const value_type &value) {
  BinaryTreeIterator<Key, T> it = find(key_extractor_(value));
  if (it != end()) {
    return {it, false};
  }

  root_ = avl_oper_.Insert(root_, value);
  ++size_;
  return {find(key_extractor_(value)), true};
}

// erases an element at pos
template <typename Key, typename T>
void BinaryTree<Key, T>::erase(BinaryTreeIterator<Key, T> pos) {
  root_ = avl_oper_.Remove(root_, pos.p_);
  --size_;
}

// swaps the contents
template <typename Key, typename T>
void BinaryTree<Key, T>::swap(BinaryTree<Key, T> &other) noexcept {
  using std::swap;
  swap(root_, other.root_);
  swap(size_, other.size_);
  swap(key_extractor_, other.key_extractor_);
  swap(avl_oper_, other.avl_oper_);
}

// Splices nodes from another container.
// Only the internal pointers of the container nodes are repointed.
template <typename Key, typename T>
void BinaryTree<Key, T>::merge(BinaryTree<Key, T> &other) {  // NOLINT
  Node<T> *p = other.begin().p_;
  while (p) {
    Key p_key = other.key_extractor_(p->data_);
    if (!avl_oper_.Find(root_, p_key)) {
      Node<T> *node = p;
      p = other.avl_oper_.Next(other.root_, p);

      other.root_ = other.avl_oper_.ExtractNode(other.root_, node);
      --other.size_;

      root_ = avl_oper_.InsertNode(root_, node);
      ++size_;
    } else {
      p = other.avl_oper_.Next(other.root_, p);
    }
  }
}

// Lookup
// finds an element with a specific key
template <typename Key, typename T>
BinaryTreeIterator<Key, T> BinaryTree<Key, T>::find(
    const key_type &key) const noexcept {
  return BinaryTreeIterator<Key, T>(this, avl_oper_.Find(root_, key));
}

// checks if the container contains an element with a specific key
template <typename Key, typename T>
bool BinaryTree<Key, T>::contains(const key_type &key) const noexcept {
  return avl_oper_.Find(root_, key);
}

// Debug
template <typename Key, typename T>
void BinaryTree<Key, T>::print() {
  avl_oper_.Print(root_);
}

}  // namespace s21

#endif  // S21_CONTAINERS_BINARY_TREE_H_  // NOLINT
