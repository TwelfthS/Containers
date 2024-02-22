#ifndef S21_CONTAINERS_STACK_STACK_H_  // NOLINT
#define S21_CONTAINERS_STACK_STACK_H_  // NOLINT

#include <exception>
#include <initializer_list>
#include <iostream>

#include "vector/s21_vector.h"

namespace s21 {

template <typename T>
class stack {
 public:
  // overrides
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // constructors
  stack() noexcept {
    size_ = 0;
    arr_ = vector<T>();
  }

  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s) noexcept;

  ~stack() { size_ = 0; }

  stack &operator=(const stack &s) noexcept {
    if (this != &s) {
      stack tmp(s);
      swap(tmp);
    }
    return *this;
  }

  stack &operator=(stack &&s) noexcept {
    if (this != &s) {
      stack tmp(std::move(s));
      swap(tmp);
    }
    return *this;
  }

  // element access
  const_reference top() const { return arr_.back(); }
  bool empty() const noexcept { return size_ ? 0 : 1; }
  size_type size() { return size_; }

  void push(const_reference value) {
    arr_.push_back(value);
    size_++;
  }
  void pop() {
    arr_.pop_back();
    size_--;
  }

  void swap(stack &other);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  size_t size_;
  vector<T> arr_;
};

// functions
template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) {
  arr_ = vector<T>(items);
  size_ = items.size();
}

template <typename T>
stack<T>::stack(const stack &s) {
  size_ = s.size_;
  arr_.reserve(size_);
  for (int i = 0; i < (int)size_; i++) {
    arr_.push_back(s.arr_[i]);
  }
}

template <typename T>
stack<T>::stack(stack &&s) noexcept {
  size_ = s.size_;
  arr_ = vector(s.arr_);
  s.size_ = 0;
}

template <typename T>
void stack<T>::swap(stack &other) {
  arr_.swap(other.arr_);
  size_t temp_size = other.size_;
  other.size_ = size_;
  size_ = temp_size;
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  vector<T> a = {args...};
  for (int i = 0; i < (int)sizeof...(args); i++) {
    push(a[i]);
  }
}

}  // namespace s21

#endif  // S21_CONTAINERS_STACK_STACK_H_  // NOLINT
