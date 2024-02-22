#ifndef S21_CONTAINERS_ARRAY_S21_ARRAY_H_  // NOLINT
#define S21_CONTAINERS_ARRAY_S21_ARRAY_H_  // NOLINT

#include <algorithm>
#include <array>
#include <initializer_list>

#ifdef DEBUG
#include <iostream>
#endif

#include <iterator>
#include <string>

namespace s21 {

template <typename Tp_, std::size_t N_>
class array {
 public:
  // in-class type overrides
  typedef Tp_ value_type;
  typedef std::size_t size_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *iterator;
  typedef const value_type *const_iterator;

  // default constructor, creates an empty array
  array() = default;

  // initializer list constructor, creates array initizialized using
  array(const std::initializer_list<value_type> &items);

  // copy constructor
  array(const array &other) { std::copy(other.data_, other.data_ + N_, data_); }

  // move constructor
  array(array &&a) { std::move(a.data_, a.data_ + N_, data_); }

  // assignment operator overload for copying an object
  array &operator=(const array &other);

  // assignment operator overload for moving an object
  array &operator=(array &&a);

  // destructor
  ~array() = default;  // nothing to do

  // access a specified element with bounds checking
  reference at(size_type pos) {
    if (pos >= N_) throw std::out_of_range("array::at: pos >= N_");
    return data_[pos];
  }

  // access a specified element
  reference operator[](size_type pos) {
    if (pos >= N_)
      throw std::out_of_range(
          "array::at: pos >= N_");  // std::array does not throw
    return data_[pos];
  }

  // access the first element
  const_reference front() { return data_[0]; }

  // access the last element
  const_reference back() { return (N_) ? data_[N_ - 1] : data_(0); }

  // direct access to the underlying array
  iterator data() { return iterator(data_); }

  // returns an iterator to the beginning
  iterator begin(void) { return iterator(data_); }

  // returns an iterator to the end
  iterator end() { return iterator(data_ + N_); }  // out of bounds

  // checks whether the container is empty
  bool empty() noexcept { return (size() == 0) ? true : false; };

  // returns the number of elements
  size_type size() { return N_; }

  // returns the maximum possible number of elements
  size_type max_size() { return N_; }

  // swaps the contents
  void swap(array &other) { std::swap_ranges(begin(), end(), other.begin()); }

  // assigns the given value to all elements in the container.
  void fill(const_reference value) {
    for (size_type i = 0; i < N_; i++) data_[i] = value;
  }

#ifdef DEBUG
  void print() {
    for (size_type i = 0; i < N_; i++)
      if (i == N_ - 1)
        std::cout << data_[i] << "\n";
      else
        std::cout << data_[i] << ", ";
  }
#endif  // DEBUG

 private:
  Tp_ data_[(N_) ? N_ : 1];  // NOLINT
};

template <typename Tp_, size_t N_>
array<Tp_, N_>::array(std::initializer_list<Tp_> const &items) : data_() {
  if (items.size() > N_) {
    throw std::out_of_range("array::initilized_constructor out of range");
  }

  int i = 0;
  for (value_type item : items) {
    data_[i++] = item;
  }
}

template <typename Tp_, size_t N_>
array<Tp_, N_> &array<Tp_, N_>::operator=(const array &other) {
  if (this != &other) {
    std::copy(other.data_, other.data_ + N_, data_);
  }

  return *this;
}
template <typename Tp_, size_t N_>
array<Tp_, N_> &array<Tp_, N_>::operator=(array &&a) {
  if (this != &a) {
    std::move(a.data_, a.data_ + N_, data_);
  }
  return *this;
}

}  // namespace s21

#endif  // S21_CONTAINERS_ARRAY_S21_ARRAY_H_  // NOLINT
