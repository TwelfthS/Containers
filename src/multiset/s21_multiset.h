#ifndef S21_CONTAINERS_S21_MULTISET_H_  // NOLINT
#define S21_CONTAINERS_S21_MULTISET_H_  // NOLINT

#include <initializer_list>

#ifdef DEBUG
#include <iostream>
#endif  // DEBUG

#include "binary_tree/binary_tree.h"
#include "vector/s21_vector.h"

namespace s21 {

template <typename T>
class multiset;

template <typename T>
class MultisetIterator {
  friend class multiset<T>;
  using data_type = std::pair<const T, size_t>;

 public:
  MultisetIterator() = default;

  MultisetIterator(const multiset<T> *owner, Node<data_type> *p)
      : owner_(owner), p_(p), counter_(1) {}

  typename multiset<T>::const_reference operator*() { return p_->data_.first; }

  MultisetIterator &operator++() {
    if (counter_ < p_->data_.second)
      ++counter_;
    else
      MoveNextValue();
    return *this;
  }

  MultisetIterator &operator--() {
    if (counter_ > 1)
      --counter_;
    else
      MovePrevValue();
    return *this;
  }

  void MoveNextValue() {
    p_ = owner_->avl_oper_.Next(owner_->root_, p_);
    counter_ = 1;
  }

  void MovePrevValue() {
    p_ = owner_->avl_oper_.Prev(owner_->root_, p_);
    counter_ = p_ ? p_->data_.second : 1;
  }

  bool operator==(MultisetIterator other) const {
    return p_ == other.p_ && counter_ == other.counter_;
  }

  bool operator!=(MultisetIterator other) const { return !(*this == other); }

 private:
  const multiset<T> *owner_ = nullptr;
  Node<data_type> *p_ = nullptr;
  size_t counter_ = 0;
};

template <typename T>
class multiset {
  friend class MultisetIterator<T>;

 public:
  // Member type
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MultisetIterator<T>;
  using const_iterator = MultisetIterator<T>;
  using size_type = size_t;

  using data_type = std::pair<const T, size_t>;

  // Functions
  multiset() = default;
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &other);
  multiset(multiset &&other) noexcept;
  ~multiset();
  multiset &operator=(multiset other);

  // Iterators
  iterator begin() const noexcept;
  iterator end() const noexcept;

  // Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Modifiers
  void clear();
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset &other) noexcept;
  void merge(multiset &other);

  // Lookup
  size_type count(const key_type &key) const noexcept;
  iterator find(const value_type &val) const noexcept;
  bool contains(const value_type &val) const noexcept;
  std::pair<iterator, iterator> equal_range(const key_type &key) const noexcept;
  iterator lower_bound(const key_type &key) const noexcept;
  iterator upper_bound(const key_type &key) const noexcept;

  // Bonus task
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(const Args &&...args);

  // Debug
  void print();

 private:
  Node<data_type> *root_ = nullptr;
  size_type size_ = 0;
  AvlTreeOperations<T, data_type> avl_oper_{
      [](const data_type &data) { return data.first; }};
};

// Functions
template <typename T>
multiset<T>::multiset(std::initializer_list<value_type> const &items) {
  for (auto item : items) {
    insert(item);
  }
}

template <typename T>
multiset<T>::multiset(const multiset &other)
    : root_(nullptr), size_(other.size_), avl_oper_(other.avl_oper_) {
  root_ = avl_oper_.Copy(other.root_);
}

template <typename T>
multiset<T>::multiset(multiset &&other) noexcept {
  swap(other);
}

template <typename T>
multiset<T>::~multiset() {
  avl_oper_.Clear(root_);
}

template <typename T>
multiset<T> &multiset<T>::operator=(multiset<T> other) {
  swap(other);
  return *this;
}

// Iterators
template <typename T>
typename multiset<T>::iterator multiset<T>::begin() const noexcept {
  Node<typename multiset<T>::data_type> *p = root_;
  while (p && p->left_) p = p->left_;
  return MultisetIterator<T>(this, p);
}

template <typename T>
typename multiset<T>::iterator multiset<T>::end() const noexcept {
  return MultisetIterator<T>(this, nullptr);
}

// Capacity
template <typename T>
bool multiset<T>::empty() const noexcept {
  return root_ == nullptr;
}

template <typename T>
typename multiset<T>::size_type multiset<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename multiset<T>::size_type multiset<T>::max_size() const noexcept {
  return (~(size_type(0))) / sizeof(Node<T>);
}

// Modifiers
template <typename T>
void multiset<T>::clear() {
  root_ = avl_oper_.Clear(root_);
  size_ = 0;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::insert(const value_type &value) {
  MultisetIterator<T> it = find(value);
  if (it != end()) {
    ++it.p_->data_.second;
    ++size_;
    return it;
  }
  root_ = avl_oper_.Insert(root_, {value, 1});
  ++size_;
  return find(value);
}

template <typename T>
void multiset<T>::erase(iterator pos) {
  size_t &counter = pos.p_->data_.second;
  if (counter > 1) {
    --counter;
  } else {
    root_ = avl_oper_.Remove(root_, pos.p_);
  }
  --size_;
}

template <typename T>
void multiset<T>::swap(multiset<T> &other) noexcept {
  using std::swap;
  swap(root_, other.root_);
  swap(size_, other.size_);
}

template <typename T>
void multiset<T>::merge(multiset<T> &other) {  // NOLINT
  Node<data_type> *p = other.begin().p_;
  while (p) {
    Node<data_type> *node = p;
    size_t node_counter = node->data_.second;
    p = other.avl_oper_.Next(other.root_, p);

    other.root_ = other.avl_oper_.ExtractNode(other.root_, node);

    T node_key = node->data_.first;
    Node<data_type> *found = avl_oper_.Find(root_, node_key);
    if (!found) {
      root_ = avl_oper_.InsertNode(root_, node);
    } else {
      found->data_.second += node_counter;
      delete node;
    }

    other.size_ -= node_counter;
    size_ += node_counter;
  }
}

// Lookup
template <typename T>
typename multiset<T>::size_type multiset<T>::count(
    const key_type &key) const noexcept {
  size_t res = 0;
  auto it = find(key);
  if (it != end()) res = it.p_->data_.second;
  return res;
}

template <typename T>
MultisetIterator<T> multiset<T>::find(const key_type &key) const noexcept {
  return MultisetIterator<T>(this, avl_oper_.Find(root_, key));
}

template <typename T>
bool multiset<T>::contains(const key_type &key) const noexcept {
  return avl_oper_.Find(root_, key);
}

template <typename T>
std::pair<MultisetIterator<T>, MultisetIterator<T>> multiset<T>::equal_range(
    const key_type &key) const noexcept {
  return {lower_bound(key), upper_bound(key)};
}

template <typename T>
MultisetIterator<T> multiset<T>::lower_bound(
    const key_type &key) const noexcept {
  auto it = begin();
  if (*it < key) it = find(key);
  return it;
}

template <typename T>
MultisetIterator<T> multiset<T>::upper_bound(
    const key_type &key) const noexcept {
  auto it = begin();
  if (*it <= key) {
    it = find(key);
    it.MoveNextValue();
  }
  return it;
}

// Bonus task
template <typename T>
template <typename... Args>
vector<std::pair<typename multiset<T>::iterator, bool>>
multiset<T>::insert_many(const Args &&...args) {
  vector<std::pair<typename multiset<T>::iterator, bool>> res;
  for (const auto &e : {args...}) {
    res.push_back({insert(e), true});
  }
  return res;
}

// Debug
#ifdef DEBUG
template <typename T>
void multiset<T>::print() {
  if (empty()) {
    std::cout << "multiset is empty";
  } else {
    avl_oper_.Print(root_);
  }
  std::cout << std::endl;
}
#endif  // DEBUG

}  // namespace s21

#endif  // S21_CONTAINERS_S21_MULTISET_H_   // NOLINT
