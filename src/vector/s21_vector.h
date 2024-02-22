#ifndef S21_CONTAINERS_VECTOR_VECTOR_H_  // NOLINT
#define S21_CONTAINERS_VECTOR_VECTOR_H_  // NOLINT

#include <exception>
#include <initializer_list>
#include <iostream>

#define MAX_SIZE 9223372036854775807

namespace s21 {
template <typename T>
class vector {
 private:
  size_t size_;
  size_t capacity_;
  T *arr_;

 public:
  // types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // constructors
  vector() noexcept {
    size_ = 0;
    capacity_ = 0;
    arr_ = nullptr;
  }

  explicit vector(size_type n) {
    size_ = n;
    capacity_ = n;
    arr_ = new value_type[n];
    for (int i = 0; i < (int)n; i++) {
      arr_[i] = 0;
    }
  }

  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;

  ~vector() {
    delete[] arr_;
    size_ = 0;
    capacity_ = 0;
  }

  // overload
  vector &operator=(const vector &v) {
    if (this != &v) {
      vector tmp(v);
      swap(tmp);
    }
    return *this;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      vector tmp(std::move(v));
      swap(tmp);
    }
    return *this;
  }

  // element access
  reference at(size_type pos) const;
  reference operator[](size_type pos) const { return arr_[pos]; }
  const_reference front() const { return arr_[0]; }
  const_reference back() const { return arr_[size_ - 1]; }
  T *data() { return arr_; }

  // iterators
  iterator begin() const { return arr_; }
  iterator end() const { return &arr_[size_]; }

  // capacity
  bool empty() const noexcept { return begin() == end() ? 1 : 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept { return MAX_SIZE / sizeof(T); }
  void reserve(size_type size);
  size_type capacity() const noexcept { return capacity_; }
  void shrink_to_fit();

  // modifiers
  void clear() { size_ = 0; }
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(size_ * 2 + 1);
    }
    arr_[size_++] = value;
  }
  void pop_back() { size_--; }
  void swap(vector &other);

  // bonus
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

// definitions
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  size_ = items.size();
  capacity_ = items.size();
}

template <typename T>
vector<T>::vector(const vector &v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  arr_ = new value_type[capacity_];
  for (int i = 0; i < (int)v.size_; i++) {
    arr_[i] = v.arr_[i];
  }
}

template <typename T>
vector<T>::vector(vector &&v) noexcept {
  size_ = v.size_;
  capacity_ = v.capacity_;
  arr_ = v.arr_;
  v.arr_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
T &vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("out of range");
  }
  return arr_[pos];
}

template <typename T>
void vector<T>::reserve(size_t size) {
  if (size > capacity_) {
    value_type *buff = new value_type[size];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size;
  }
}

template <typename T>
void vector<T>::shrink_to_fit() {
  value_type *buff = new value_type[size_];
  for (size_t i = 0; i < size_; ++i) {
    buff[i] = std::move(arr_[i]);
  }
  delete[] arr_;
  arr_ = buff;
  capacity_ = size_;
}

template <typename T>
T *vector<T>::insert(iterator pos, const_reference value) {
  size_t i = 0;
  for (auto *it = begin(); it < pos; it++) {
    i++;
  }
  if (size_ == capacity_) {
    reserve(size_ * 2 + 1);
  }
  for (size_t k = size_; k != i; k--) {
    arr_[k] = arr_[k - 1];
  }
  arr_[i] = value;
  size_++;
  return &arr_[i];
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_t i = 0;
  for (auto *it = begin(); it < pos; it++) {
    i++;
  }
  for (int k = i; k < (int)size_ - 1; k++) {
    arr_[k] = arr_[k + 1];
  }
  size_--;
}

template <typename T>
void vector<T>::swap(vector &other) {
  value_type *buff = other.arr_;
  size_t b_size = other.size();
  size_t b_capacity = other.capacity();
  other.arr_ = arr_;
  other.size_ = size();
  other.capacity_ = capacity();
  arr_ = buff;
  size_ = b_size;
  capacity_ = b_capacity;
}

template <typename T>
T helper(T value) {
  return value;
}

template <typename T>
template <typename... Args>
T *vector<T>::insert_many(const_iterator pos, Args &&...args) {
  vector<T> a = {args...};
  size_t number = sizeof...(args);
  int i = 0;
  for (auto *it = begin(); it < pos; it++) {
    i++;
  }
  if (size_ + number > capacity_) {
    reserve(size_ + number);
  }
  for (size_t k = size_ + number - 1; k != i + number - 1; k--) {
    arr_[k] = arr_[k - number];
  }
  for (size_t j = i; j < i + number; j++) {
    arr_[j] = a[j - i];
  }
  size_ += number;
  return &arr_[i];
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  vector<T> a = {args...};
  int number = sizeof...(args);
  if (size_ + number > capacity_) {
    reserve(size_ + number);
  }
  for (int i = 0; i < number; i++) {
    arr_[size_++] = a[i];
  }
}

}  // namespace s21

#endif  // S21_CONTAINERS_VECTOR_VECTOR_H_  // NOLINT
