#ifndef S21_CONTAINERS_LIST_LIST_H_  // NOLINT
#define S21_CONTAINERS_LIST_LIST_H_  // NOLINT

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  // member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  struct Node {
    explicit Node(const value_type& value = value_type())
        : val_(value), p_prev_(nullptr), p_next_(nullptr) {}

    value_type val_;
    Node* p_prev_;
    Node* p_next_;
  };

  // List functions
 public:
  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(const list& l);
  list& operator=(list&& l);

  // List Element access
  const_reference front();
  const_reference back();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void reverse();
  void merge(list& other);
  void unique();
  void sort();

  class ListIterator {
   public:
    ListIterator() : ptr_(nullptr) {}
    explicit ListIterator(Node* ptr) : ptr_(ptr) {}

    reference operator*() {
      if (!ptr_) {
        throw std::invalid_argument("Element not exists");
      }
      return ptr_->val_;
    }

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      ptr_ = ptr_->p_next_;
      return tmp;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      ptr_ = ptr_->p_prev_;
      return tmp;
    }

    ListIterator operator++() {
      ptr_ = ptr_->p_next_;
      return *this;
    }

    ListIterator operator--() {
      ptr_ = ptr_->p_prev_;
      return *this;
    }

    bool operator==(const ListIterator& rhs) const { return ptr_ == rhs.ptr_; }

    bool operator!=(const ListIterator& rhs) const { return !(*this == rhs); }

   private:
    Node* ptr_ = nullptr;
    friend class list;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(ListIterator other_it)  // NOLINT
        : ListIterator(other_it) {}
    const T& operator*() { return ListIterator::operator*(); }
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Iterators
  iterator begin();
  iterator end();

  // Modifiers
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(const_iterator pos, list& other);  // NOLINT

  // Bonus
  template <typename... Args>
  void insert_many(iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  void split(Node* head, Node** left, Node** right);
  void add_end();
  void merge_sort(Node** list);
  Node* merge(Node* left, Node* right);

  Node* p_head_;
  Node* p_tail_;
  Node* p_end_;
  size_type size_;
};

// Constructors and destructor
template <typename value_type>
list<value_type>::list()
    : p_head_(nullptr), p_tail_(nullptr), p_end_(new Node()), size_(0) {
  add_end();
}

template <typename value_type>
list<value_type>::list(size_type n)
    : p_head_(nullptr), p_tail_(nullptr), size_(0) {
  if (n >= max_size()) {
    throw std::out_of_range("Incorrect size");
  }
  p_end_ = new Node();
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
  add_end();
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const& items)
    : p_head_(nullptr), p_tail_(nullptr), p_end_(new Node()), size_(0) {
  for (const auto& i : items) {
    push_back(i);
  }
}

template <typename value_type>
list<value_type>::list(const list& l)
    : p_head_(nullptr), p_tail_(nullptr), p_end_(new Node()), size_(0) {
  Node* curNode = l.p_head_;
  for (size_type i = 0; i != l.size_; ++i) {
    push_back(curNode->val_);
    curNode = curNode->p_next_;
  }
}

template <typename value_type>
list<value_type>::list(list&& l)
    : p_head_(nullptr), p_tail_(nullptr), p_end_(nullptr), size_(0) {
  swap(l);
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  delete p_end_;
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(const list& l) {
  if (this != &l) {
    list<value_type> tmp(l);
    swap(tmp);
  }
  return *this;
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(list&& l) {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

// Iterator funcs
template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  if (!p_head_) {
    return iterator(p_end_);
  } else {
    return iterator(p_head_);
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(p_end_);
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  return p_head_->val_;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  return p_tail_->val_;
}

// List sizes
template <typename value_type>
bool list<value_type>::empty() {
  return size_ == 0;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() {
  return size_;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  return (std::numeric_limits<size_t>::max() / 2) / sizeof(Node);
}

// List funcions
template <typename value_type>
void list<value_type>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node* current = pos.ptr_;

  if (empty()) {
    push_back(value);
    return begin();
  }
  if (current == p_head_) {
    push_front(value);
    return begin();
  }
  if (current == p_end_) {
    push_back(value);
    return --end();
  }
  Node* insertNode = new Node(value);

  insertNode->p_next_ = current;
  insertNode->p_prev_ = current->p_prev_;
  current->p_prev_->p_next_ = insertNode;
  current->p_prev_ = insertNode;
  ++size_;
  add_end();
  return iterator(insertNode);
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (size_ == 0) {
    return;
  }
  Node* current = pos.ptr_;
  if (current == p_head_) {
    pop_front();
  } else if (current == p_tail_) {
    pop_back();
  } else {
    Node* prevNode = current->p_prev_;
    Node* nextNode = current->p_next_;
    prevNode->p_next_ = nextNode;
    nextNode->p_prev_ = prevNode;
    delete current;
    size_--;
  }
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    p_head_ = new_node;
    p_tail_ = new_node;
  } else {
    new_node->p_prev_ = p_tail_;
    p_tail_->p_next_ = new_node;
    p_tail_ = new_node;
  }
  size_++;
  add_end();
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (empty()) {
    throw std::logic_error("List size is 0");
  }
  Node* lNode = p_tail_;
  if (size_ > 1) {
    p_tail_ = lNode->p_prev_;
    p_tail_->p_next_ = nullptr;
  } else {
    p_head_ = nullptr;
    p_tail_ = nullptr;
  }
  delete lNode;
  size_--;
  add_end();
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    p_head_ = new_node;
    p_tail_ = new_node;
  } else {
    new_node->p_next_ = p_head_;
    p_head_->p_prev_ = new_node;
    p_head_ = new_node;
  }
  size_++;
  add_end();
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (empty()) {
    throw std::logic_error("List size is 0");
  }
  Node* front_node = p_head_;
  if (size_ > 1) {
    p_head_ = front_node->p_next_;
    p_head_->p_prev_ = nullptr;
  } else {
    p_head_ = nullptr;
    p_tail_ = nullptr;
  }
  delete front_node;
  size_--;
  add_end();
}

template <typename value_type>
void list<value_type>::swap(list& other) {
  std::swap(p_head_, other.p_head_);
  std::swap(p_tail_, other.p_tail_);
  std::swap(p_end_, other.p_end_);
  std::swap(size_, other.size_);
}

template <typename value_type>
void list<value_type>::reverse() {
  using std::swap;
  Node* p = p_head_;
  while (p && p != p_end_) {
    swap(p->p_next_, p->p_prev_);
    p = p->p_prev_;
  }
  swap(p_head_, p_tail_);
}

template <typename value_type>
void list<value_type>::merge(list& other) {  // NOLINT
  splice(end(), other);
  sort();
}

template <typename value_type>
void list<value_type>::unique() {
  if (empty()) {
    throw std::logic_error("List size is 0");
  }
  Node* curr = p_head_;

  while (curr->p_next_ != p_end_) {
    if (curr->val_ == curr->p_next_->val_) {
      Node* not_uniq = curr->p_next_;
      curr->p_next_ = not_uniq->p_next_;
      if (curr->p_next_ != p_end_) {
        curr->p_next_->p_prev_ = curr;
      }
      delete not_uniq;
      --size_;
    } else {
      curr = curr->p_next_;
    }
  }
  p_tail_ = curr;
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list& other) {  // NOLINT
  if (!other.empty()) {
    auto it = pos;
    if (pos != begin()) {
      --it;
      Node* prev_node = it.ptr_;
      prev_node->p_next_ = other.p_head_;
      other.p_head_->p_prev_ = prev_node;
    } else {
      p_head_ = other.p_head_;
    }
    if (pos.ptr_ == p_end_) {
      p_tail_ = other.p_tail_;
    }

    size_ += other.size_;
    other.p_tail_->p_next_ = pos.ptr_;
    pos.ptr_->p_prev_ = other.p_tail_;

    other.p_head_ = nullptr;
    other.p_tail_ = nullptr;
    other.size_ = 0;
  }
}

// support funcs

template <typename value_type>
void list<value_type>::add_end() {
  if (p_end_) {
    p_end_->p_next_ = p_head_;
    p_end_->p_prev_ = p_tail_;
    p_end_->val_ = value_type();
    if (p_head_) {
      p_head_->p_prev_ = p_end_;
    }
    if (p_tail_) {
      p_tail_->p_next_ = p_end_;
    }
  }
}

template <typename value_type>
typename list<value_type>::Node* list<value_type>::merge(Node* left,
                                                         Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }

  Node* result = nullptr;

  if (left->val_ <= right->val_) {
    result = left;
    result->p_next_ = merge(left->p_next_, right);
    result->p_next_->p_prev_ = result;
  } else {
    result = right;
    result->p_next_ = merge(left, right->p_next_);
    result->p_next_->p_prev_ = result;
  }
  return result;
}

template <typename value_type>
void list<value_type>::split(Node* head, Node** left, Node** right) {
  if (head == nullptr || head->p_next_ == nullptr) {
    *left = head;
    *right = nullptr;
    return;
  }
  Node* slow = head;
  Node* fast = head->p_next_;
  head->p_prev_ = nullptr;
  p_tail_->p_next_ = nullptr;

  while (fast != nullptr) {
    fast = fast->p_next_;
    if (fast != nullptr) {
      slow = slow->p_next_;
      fast = fast->p_next_;
    }
  }
  *left = head;
  *right = slow->p_next_;
  slow->p_next_ = nullptr;
  (*right)->p_prev_ = nullptr;
}

template <typename value_type>
void list<value_type>::sort() {
  if (size() > 1) {
    merge_sort(&p_head_);
    add_end();
  }
}

template <typename value_type>
void list<value_type>::merge_sort(Node** head) {
  if (*head == nullptr || (*head)->p_next_ == nullptr) {
    return;
  }
  Node* left;
  Node* right;

  split(*head, &left, &right);

  merge_sort(&left);
  merge_sort(&right);

  *head = merge(left, right);
  (*head)->p_prev_ = nullptr;
  Node* current = *head;
  while (current->p_next_ != nullptr) {
    current = current->p_next_;
  }
  p_tail_ = current;
}

// Bonus
template <typename T>
template <typename... Args>
void list<T>::insert_many(iterator pos, Args&&... args) {
  std::initializer_list<T> values{args...};
  for (auto it = rbegin(values); it != rend(values); ++it) {
    pos = insert(pos, *it);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) push_back(arg);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) push_front(arg);
}

}  // namespace s21

#endif  // S21_CONTAINERS_LIST_LIST_H_  // NOLINT
