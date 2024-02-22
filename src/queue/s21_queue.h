#ifndef S21_CONTAINERS_S21_QUEUE_H_  // NOLINT
#define S21_CONTAINERS_S21_QUEUE_H_  // NOLINT

#include <initializer_list>

#include "list/s21_list.h"

namespace s21 {

template <typename T>
class queue : private list<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue() : list<T>() {}
  queue(std::initializer_list<value_type> const &items) : list<T>(items) {}

  queue(const queue &q) : list<T>(q) {}
  queue(queue &&q) noexcept { swap(q); }
  ~queue() = default;

  queue &operator=(queue q) {
    swap(q);
    return *this;
  }

  using list<T>::front;
  using list<T>::back;
  using list<T>::empty;
  using list<T>::size;

  void push(const_reference value) { list<T>::push_back(value); }
  void pop() { list<T>::pop_front(); }

  void swap(queue &other) noexcept { list<T>::swap(other); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto &&arg : {args...}) push(arg);
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_QUEUE_H_  // NOLINT
