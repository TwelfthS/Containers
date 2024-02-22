#include <gtest/gtest.h>

#include <iostream>

#include "s21_containers.h"
#include "s21_containersplus.h"

using s21::multiset;

// Member functions
// --------------------------------
TEST(MultisetMemberFunctions, DefaultConstructor) {
  multiset<int> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(MultisetMemberFunctions, InitListConstructor) {
  multiset<int> a{1, 2, 3};
  ASSERT_EQ(a.size(), 3);
  multiset<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);

  multiset<int> b{1, 2, 3, 1, 2};
  ASSERT_EQ(b.size(), 5);
  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(MultisetMemberFunctions, CopyConstructor) {
  multiset<int> a{1, 2, 3, 1};
  multiset<int> b = a;

  ASSERT_EQ(a.size(), 4);
  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);

  ASSERT_EQ(b.size(), 4);
  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(MultisetMemberFunctions, MoveConstructor) {
  multiset<int> a{1, 2, 3, 1};
  multiset<int> b = std::move(a);

  ASSERT_EQ(a.size(), 0);

  ASSERT_EQ(b.size(), 4);
  auto it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(MultisetMemberFunctions, AssignmentOperator) {
  multiset<int> a{1, 2, 3, 1};
  multiset<int> b;
  b = a;

  ASSERT_EQ(a.size(), 4);
  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);

  ASSERT_EQ(b.size(), 4);
  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(MultisetMemberFunctions, MoveAssignmentOperator) {
  multiset<int> a{1, 2, 3, 1};
  multiset<int> b;
  b = std::move(a);

  ASSERT_EQ(a.size(), 0);

  ASSERT_EQ(b.size(), 4);
  auto it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

// Multiset Iterators
// --------------------------------
TEST(MultisetIterators, begin) {
  multiset<int> empty_multiset;
  ASSERT_EQ(empty_multiset.begin(), empty_multiset.end());

  multiset<int> a{1, 2, 3, 1};

  multiset<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
}

TEST(MultisetIterators, end) {
  multiset<int> a{1, 2, 3, 1};

  multiset<int>::iterator it = a.end();
  --it;
  ASSERT_EQ(*it, 3);
}

TEST(MultisetIterators, IteratorNext) {
  multiset<int> a{1, 2, 3, 1};
  ASSERT_EQ(a.size(), 4);

  multiset<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(MultisetIterators, IteratorPrev) {
  multiset<int> a{1, 2, 3, 1};
  ASSERT_EQ(a.size(), 4);

  multiset<int>::iterator it = a.end();
  --it;

  ASSERT_EQ(*it, 3);
  --it;
  ASSERT_EQ(*it, 2);
  --it;
  ASSERT_EQ(*it, 1);
  --it;
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(it, a.begin());
}

TEST(MultisetIterators, ApplyStarToIterator) {
  multiset<int> a{1, 2, 3, 1};
  multiset<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);

  // MUST NOT COMPILE!
  // *it = 0;
}

TEST(MultisetIterators, ApplyStarToConstIterator) {
  multiset<int> a{1, 2, 3, 1};
  multiset<int>::const_iterator it = a.begin();
  ASSERT_EQ(*it, 1);

  // MUST NOT COMPILE!
  // *it = 0;
}

// Multiset Capacity
// -------------------------
TEST(MultisetCapacity, empty) {
  multiset<int> a;
  ASSERT_TRUE(a.empty());

  multiset<int> b{1};
  ASSERT_FALSE(b.empty());

  multiset<int> c{1, 1};
  ASSERT_FALSE(c.empty());
}

TEST(MultisetCapacity, size) {
  multiset<int> a;
  ASSERT_EQ(a.size(), 0);

  multiset<int> b{1};
  ASSERT_EQ(b.size(), 1);

  multiset<int> c{1, 2, 3};
  ASSERT_EQ(c.size(), 3);

  multiset<int> d{1, 2, 3, 1};
  ASSERT_EQ(d.size(), 4);

  multiset<int> e{1, 2, 3, 1, 3};
  ASSERT_EQ(e.size(), 5);
}

TEST(MultisetCapacity, max_size) {
  multiset<int> a;
  ASSERT_TRUE(a.max_size() > a.size());

  multiset<int> b{1, 2, 3, 4, 5, 6};
  ASSERT_TRUE(b.max_size() > b.size());
}

// Modifiers
// -------------------
TEST(MultisetModifiers, clear) {
  multiset<int> a{1, 2, 3, 1};
  ASSERT_EQ(a.size(), 4);

  a.clear();
  ASSERT_EQ(a.size(), 0);
}

TEST(MultisetModifiers, insert) {
  multiset<int> a;
  ASSERT_EQ(a.size(), 0);

  multiset<int>::iterator res;
  res = a.insert(3);
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(*res, 3);

  res = a.insert(1);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(*res, 1);

  res = a.insert(2);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(*res, 2);

  res = a.insert(1);
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(*res, 1);

  multiset<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(MultisetModifiers, erase) {
  multiset<int> a{2, 1, 3, 2};
  ASSERT_EQ(a.size(), 4);

  auto b = a;
  auto it = b.begin();
  b.erase(it);
  ASSERT_EQ(b.size(), 3);

  b = a;
  it = b.begin();
  ++it;
  b.erase(it);
  ASSERT_EQ(b.size(), 3);

  b = a;
  it = b.begin();
  ++it;
  ++it;
  b.erase(it);
  ASSERT_EQ(b.size(), 3);

  b = a;
  it = b.begin();
  ++it;
  ++it;
  ++it;
  b.erase(it);
  ASSERT_EQ(b.size(), 3);
}

TEST(MultisetModifiers, swap) {
  multiset<int> a{2, 1, 3, 1};

  multiset<int> b{6, 5, 5};

  a.swap(b);
  ASSERT_EQ(a.size(), 3);
  multiset<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_EQ(b.size(), 4);
  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(MultisetModifiers, merge1) {
  multiset<int> a{1, 2, 3, 1};
  multiset<int> b{5, 6, 5};

  a.merge(b);
  ASSERT_EQ(a.size(), 7);

  multiset<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(MultisetModifiers, merge2) {
  multiset<char> a{'C', 'B', 'B', 'A'}, b{'E', 'D', 'E', 'C'};

  a.merge(b);
  ASSERT_EQ(a.size(), 8);

  multiset<char>::iterator it = a.begin();
  ASSERT_EQ(*it, 'A');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'C');
  ++it;
  ASSERT_EQ(*it, 'C');
  ++it;
  ASSERT_EQ(*it, 'D');
  ++it;
  ASSERT_EQ(*it, 'E');
  ++it;
  ASSERT_EQ(*it, 'E');
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

TEST(MultisetModifiers, merge3) {
  multiset<char> a{'C', 'B', 'B', 'A'}, b{};

  a.merge(b);
  ASSERT_EQ(a.size(), 4);

  multiset<char>::iterator it = a.begin();
  ASSERT_EQ(*it, 'A');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'C');
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

TEST(MultisetModifiers, merge4) {
  multiset<char> a{'C', 'B', 'B', 'A'}, b{'E'};

  a.merge(b);
  ASSERT_EQ(a.size(), 5);

  multiset<char>::iterator it = a.begin();
  ASSERT_EQ(*it, 'A');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'C');
  ++it;
  ASSERT_EQ(*it, 'E');
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

TEST(MultisetModifiers, merge5) {
  multiset<char> a{'C', 'B', 'B', 'A'}, b{'A'};

  a.merge(b);
  ASSERT_EQ(a.size(), 5);

  multiset<char>::iterator it = a.begin();
  ASSERT_EQ(*it, 'A');
  ++it;
  ASSERT_EQ(*it, 'A');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'B');
  ++it;
  ASSERT_EQ(*it, 'C');
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

TEST(MultisetModifiers, merge6) {
  multiset<char> a{}, b{'A'};

  a.merge(b);
  ASSERT_EQ(a.size(), 1);

  multiset<char>::iterator it = a.begin();
  ASSERT_EQ(*it, 'A');
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

// Multiset Lookup
// -----------------------------
TEST(MultisetModifiers, count) {
  multiset<int> a{1, 2, 3, 3, 3, 2};

  ASSERT_EQ(a.count(0), 0);
  ASSERT_EQ(a.count(1), 1);
  ASSERT_EQ(a.count(2), 2);
  ASSERT_EQ(a.count(3), 3);
  ASSERT_EQ(a.count(4), 0);
}

TEST(MultisetModifiers, find) {
  multiset<int> a{1, 2, 3, 1};

  auto it1 = a.begin();
  auto it2 = ++a.begin();
  auto it3 = ++(++a.begin());
  auto it4 = ++(++(++a.begin()));

  ASSERT_EQ(a.find(0), a.end());
  ASSERT_EQ(a.find(1), it1);
  ASSERT_EQ(++a.find(1), it2);

  ASSERT_EQ(a.find(2), it3);
  ASSERT_EQ(a.find(3), it4);
  ASSERT_EQ(a.find(4), a.end());
}

TEST(MultisetModifiers, contains) {
  multiset<int> a{1, 2, 3, 1};

  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
  ASSERT_TRUE(a.contains(3));

  ASSERT_FALSE(a.contains(0));
  ASSERT_FALSE(a.contains(4));
}

TEST(MultisetModifiers, lower_bound) {
  multiset<int> a{1, 2, 3, 1, 3};

  ASSERT_EQ(a.lower_bound(0), a.begin());

  ASSERT_EQ(a.lower_bound(1), a.begin());
  ASSERT_EQ(a.lower_bound(2), ++(++a.begin()));
  ASSERT_EQ(a.lower_bound(3), ++(++ ++a.begin()));

  ASSERT_EQ(a.lower_bound(4), a.end());
}

TEST(MultisetModifiers, upper_bound) {
  multiset<int> a{1, 2, 3, 1, 3};

  ASSERT_EQ(a.upper_bound(0), a.begin());

  ASSERT_EQ(a.upper_bound(1), ++(++a.begin()));
  ASSERT_EQ(a.upper_bound(2), ++(++(++a.begin())));

  ASSERT_EQ(a.upper_bound(3), a.end());
  ASSERT_EQ(a.upper_bound(100), a.end());
}

TEST(MultisetModifiers, equal_range) {
  multiset<int> a{1, 2, 3, 1, 3};

  ASSERT_EQ(a.equal_range(0).first, a.begin());
  ASSERT_EQ(a.equal_range(0).second, a.begin());

  ASSERT_EQ(a.equal_range(1).first, a.begin());
  ASSERT_EQ(a.equal_range(1).second, ++(++a.begin()));

  ASSERT_EQ(a.equal_range(2).first, ++(++a.begin()));
  ASSERT_EQ(a.equal_range(2).second, ++(++(++a.begin())));

  ASSERT_EQ(a.equal_range(3).first, --(--a.end()));
  ASSERT_EQ(a.equal_range(3).second, a.end());

  ASSERT_EQ(a.equal_range(4).first, a.end());
  ASSERT_EQ(a.equal_range(4).second, a.end());
}

// Extra tests
// -------------------------------------------
TEST(MultisetExtraTests, insert_iterate_remove) {
  int arr[] = {9, 0, 3, 5, 2, 7, 6, 4, 1, 8, 1, 9, 3, 7};
  multiset<int> s;
  for (auto e : arr) {
    s.insert(e);
  }

  const size_t arr_size = sizeof(arr) / sizeof(*arr);
  ASSERT_EQ(s.size(), arr_size);

  std::sort(std::begin(arr), std::end(arr));

  // iterate forward
  multiset<int>::iterator it = s.begin();
  for (size_t i = 0; i < arr_size; ++i) {
    ASSERT_EQ(*it, arr[i]);
    ++it;
  }

  // iterate backward
  multiset<int>::iterator it2 = s.end();
  for (int i = arr_size - 1; i >= 0; --i) {
    --it2;
    ASSERT_EQ(*it2, arr[i]);
  }

  for (auto e : arr) {
    auto it = s.find(e);
    s.erase(it);
  }
  ASSERT_TRUE(s.empty());
}

using s21::vector;

TEST(MultisetInsertMany, test1) {
  multiset<int> s;
  using iterator = multiset<int>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(1, 2, 3);

  ASSERT_EQ(res.size(), 3);

  ASSERT_EQ(res[0].first, s.begin());
  ASSERT_TRUE(res[0].second);

  ASSERT_EQ(res[1].first, ++s.begin());
  ASSERT_TRUE(res[1].second);

  ASSERT_EQ(res[2].first, ++(++s.begin()));
  ASSERT_TRUE(res[2].second);

  ASSERT_EQ(s.size(), 3);
  auto it = s.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, s.end());
}

TEST(MultisetInsertMany, test2) {
  multiset<int> s{1, 2, 3};
  using iterator = multiset<int>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(1, 2, 3);

  ASSERT_EQ(res.size(), 3);

  ASSERT_EQ(*res[0].first, 1);
  ASSERT_TRUE(res[0].second);

  ASSERT_EQ(*res[1].first, 2);
  ASSERT_TRUE(res[1].second);

  ASSERT_EQ(*res[2].first, 3);
  ASSERT_TRUE(res[2].second);

  ASSERT_EQ(s.size(), 6);
  auto it = s.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, s.end());
}

TEST(MultisetInsertMany, test3) {
  multiset<int> s{1, 2, 3};
  using iterator = multiset<int>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(4, 5, 6);

  ASSERT_EQ(res.size(), 3);

  ASSERT_EQ(*res[0].first, 4);
  ASSERT_TRUE(res[0].second);

  ASSERT_EQ(*res[1].first, 5);
  ASSERT_TRUE(res[1].second);

  ASSERT_EQ(*res[2].first, 6);
  ASSERT_TRUE(res[2].second);

  ASSERT_EQ(s.size(), 6);
  auto it = s.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(it, s.end());
}

TEST(MultisetInsertMany, test4) {
  multiset<int> s{1, 2, 3};
  using iterator = multiset<int>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(1, 8, 1, 2, 9);

  ASSERT_EQ(res.size(), 5);

  ASSERT_EQ(*res[0].first, 1);
  ASSERT_TRUE(res[0].second);

  ASSERT_EQ(*res[1].first, 8);
  ASSERT_TRUE(res[1].second);

  ASSERT_EQ(*res[2].first, 1);
  ASSERT_TRUE(res[2].second);

  ASSERT_EQ(*res[3].first, 2);
  ASSERT_TRUE(res[3].second);

  ASSERT_EQ(*res[4].first, 9);
  ASSERT_TRUE(res[4].second);

  ASSERT_EQ(s.size(), 8);
  auto it = s.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 8);
  ++it;
  ASSERT_EQ(*it, 9);
  ++it;
  ASSERT_EQ(it, s.end());
}
