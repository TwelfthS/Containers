#ifndef S21_CONTAINERS_S21_SET_H_  // NOLINT
#define S21_CONTAINERS_S21_SET_H_  // NOLINT

#include <initializer_list>
#include <iostream>

#include "binary_tree/binary_tree.h"
#include "vector/s21_vector.h"  // for bonus task

namespace s21 {

template <typename T>
class set : public BinaryTree<T, T> {
 public:
  // Member type
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = ConstBinaryTreeIterator<T, T>;
  using const_iterator = ConstBinaryTreeIterator<T, T>;
  using size_type = size_t;

  // Functions
  set() = default;
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other) noexcept;
  ~set();
  set &operator=(set other);

  // Iterators
  using BinaryTree<T, T>::begin;
  using BinaryTree<T, T>::end;

  // Capacity
  using BinaryTree<T, T>::empty;
  using BinaryTree<T, T>::size;
  using BinaryTree<T, T>::max_size;

  // Modifiers
  using BinaryTree<T, T>::clear;
  using BinaryTree<T, T>::insert;
  using BinaryTree<T, T>::erase;
  using BinaryTree<T, T>::swap;
  using BinaryTree<T, T>::merge;

  // Lookup
  using BinaryTree<T, T>::find;
  using BinaryTree<T, T>::contains;

  // Bonus task
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(const Args &&...args);

  // Debug
  using BinaryTree<T, T>::print;
};

// Functions
template <typename T>
set<T>::set(std::initializer_list<value_type> const &items) {
  for (auto item : items) {
    insert(item);
  }
}

template <typename T>
set<T>::set(const set &other) : BinaryTree<T, T>(other) {}

template <typename T>
set<T>::set(set &&other) noexcept {
  swap(other);
}

template <typename T>
set<T>::~set() {}

template <typename T>
set<T> &set<T>::operator=(set<T> other) {
  swap(other);
  return *this;
}

// Bonus task
template <typename T>
template <typename... Args>
vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    const Args &&...args) {
  vector<std::pair<typename set<T>::iterator, bool>> res;
  for (const auto &e : {args...}) {
    res.push_back(insert(e));
  }
  return res;
}

}  // namespace s21

#endif  // S21_CONTAINERS_S21_SET_H_  // NOLINT
