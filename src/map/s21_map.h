#ifndef S21_CONTAINERS_S21_MAP_H_  // NOLINT
#define S21_CONTAINERS_S21_MAP_H_  // NOLINT

#include <initializer_list>
#include <iostream>
#include <stdexcept>

#include "binary_tree/binary_tree.h"
#include "vector/s21_vector.h"  // for bonus task

namespace s21 {

template <typename K, typename T>
class map : public BinaryTree<K, std::pair<const K, T>> {
 public:
  // Member type
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = BinaryTreeIterator<K, value_type>;
  using const_iterator = ConstBinaryTreeIterator<K, value_type>;
  using size_type = size_t;

  using BinaryTreeMap = BinaryTree<K, value_type>;

  // Functions
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &other);
  map(map &&other) noexcept;
  ~map() = default;
  map &operator=(map other);

  // Element access
  T &at(const K &key);
  T &operator[](const K &key);

  // Iterators
  using BinaryTreeMap::begin;
  using BinaryTreeMap::end;

  // Capacity
  using BinaryTreeMap::empty;
  using BinaryTreeMap::max_size;
  using BinaryTreeMap::size;

  // Modifiers
  using BinaryTreeMap::clear;
  using BinaryTreeMap::erase;
  using BinaryTreeMap::insert;
  using BinaryTreeMap::merge;
  using BinaryTreeMap::swap;

  size_type erase(const K &key);
  std::pair<iterator, bool> insert(const K &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const K &key, const T &obj);

  // Lookup
  using BinaryTreeMap::contains;
  using BinaryTreeMap::find;

  // Bonus task
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(const Args &&...args);

  // Debug
  using BinaryTreeMap::print;
};

// Functions
template <typename K, typename T>
map<K, T>::map()
    : BinaryTreeMap([](const value_type &data) { return data.first; }) {}

template <typename K, typename T>
map<K, T>::map(std::initializer_list<value_type> const &items) : map<K, T>() {
  for (auto item : items) {
    insert(item);
  }
}

template <typename K, typename T>
map<K, T>::map(const map &other) : BinaryTreeMap(other) {}

template <typename K, typename T>
map<K, T>::map(map &&other) noexcept : map<K, T>() {
  swap(other);
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map<Key, T> other) {
  swap(other);
  return *this;
}

// Element access
template <typename K, typename T>
T &map<K, T>::at(const K &key) {
  map<K, T>::iterator it = find(key);
  if (it == end()) {
    throw std::out_of_range("map::at");
  }
  return it->second;
}

template <typename K, typename T>
T &map<K, T>::operator[](const K &key) {
  map<K, T>::iterator it = find(key);
  if (it != end()) {
    return it->second;
  }

  it = insert(key, T()).first;
  return it->second;
}

// Iterators
// Capacity

// Modifiers
template <typename K, typename T>
typename map<K, T>::size_type map<K, T>::erase(const K &key) {
  map<K, T>::iterator it = find(key);
  if (it == end()) return 0;
  erase(it);
  return 1;
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(const K &key,
                                                                const T &obj) {
  return insert({key, obj});
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(
    const K &key, const T &obj) {
  map<K, T>::iterator it = find(key);
  if (it == end()) {
    return insert({key, obj});
  }

  it->second = obj;
  return {it, false};
}

// Bonus task
template <typename K, typename T>
template <typename... Args>
vector<std::pair<typename map<K, T>::iterator, bool>> map<K, T>::insert_many(
    const Args &&...args) {
  vector<std::pair<typename map<K, T>::iterator, bool>> res;
  for (const auto &e : {args...}) {
    res.push_back(insert(e));
  }
  return res;
}

}  // namespace s21

#endif  // S21_CONTAINERS_S21_MAP_H_  // NOLINT
