#include <gtest/gtest.h>

#include <algorithm>
#include <utility>

#include "s21_containers.h"

using s21::set;

// Member functions
// --------------------------------
TEST(SetMemberFunctions, DefaultConstructor) {
  set<int> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(SetMemberFunctions, InitListConstructor) {
  set<int> a{1, 2, 3};
  ASSERT_EQ(a.size(), 3);
  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(SetMemberFunctions, CopyConstructor) {
  set<int> a{1, 2, 3};
  set<int> b = a;

  ASSERT_EQ(a.size(), 3);
  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);

  ASSERT_EQ(b.size(), 3);
  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(SetMemberFunctions, MoveConstructor) {
  set<int> a{1, 2, 3};
  set<int> b = std::move(a);

  ASSERT_EQ(a.size(), 0);

  ASSERT_EQ(b.size(), 3);
  auto it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(SetMemberFunctions, AssignmentOperator) {
  set<int> a{1, 2, 3};
  set<int> b;
  b = a;

  ASSERT_EQ(a.size(), 3);
  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);

  ASSERT_EQ(b.size(), 3);
  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(SetMemberFunctions, MoveAssignmentOperator) {
  set<int> a{1, 2, 3};
  set<int> b;
  b = std::move(a);

  ASSERT_EQ(a.size(), 0);

  ASSERT_EQ(b.size(), 3);
  auto it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

// Set Iterators
// --------------------------------
TEST(SetIterators, begin) {
  set<int> empty_set;
  ASSERT_EQ(empty_set.begin(), empty_set.end());

  set<int> a{1, 2, 3};

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
}

TEST(SetIterators, end) {
  set<int> a{1, 2, 3};

  set<int>::iterator it = a.end();
  --it;
  ASSERT_EQ(*it, 3);
}

TEST(SetIterators, IteratorNext) {
  set<int> a{1, 2, 3};
  ASSERT_EQ(a.size(), 3);

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(SetIterators, IteratorPrev) {
  set<int> a{1, 2, 3};
  ASSERT_EQ(a.size(), 3);

  set<int>::iterator it = a.end();
  --it;

  ASSERT_EQ(*it, 3);
  --it;
  ASSERT_EQ(*it, 2);
  --it;
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(it, a.begin());
}

TEST(SetIterators, ApplyStarToIterator) {
  set<int> a{1, 2, 3};
  set<int>::iterator it = a.begin();

  // MUST NOT COMPILE
  // *it = 0;

  ASSERT_EQ(*it, 1);
}

TEST(SetIterators, ConstIterator) {
  set<int> a{1, 2, 3};
  set<int>::const_iterator it = a.begin();

  // MUST NOT COMPILE
  // *it = 0;

  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;

  ASSERT_EQ(it, a.end());
}

// Set Capacity
// -------------------------
TEST(SetCapacity, empty) {
  set<int> a;
  ASSERT_TRUE(a.empty());

  set<int> b{1};
  ASSERT_FALSE(b.empty());
}

TEST(SetCapacity, size) {
  set<int> a;
  ASSERT_EQ(a.size(), 0);

  set<int> b{1};
  ASSERT_EQ(b.size(), 1);

  set<int> c{1, 2, 3};
  ASSERT_EQ(c.size(), 3);
}

TEST(SetCapacity, max_size) {
  set<int> a;
  ASSERT_TRUE(a.max_size() > a.size());

  set<int> b{1, 2, 3, 4, 5, 6};
  ASSERT_TRUE(b.max_size() > b.size());
}

// Modifiers
// -------------------
TEST(SetModifiers, clear) {
  set<int> a{1, 2, 3};
  ASSERT_EQ(a.size(), 3);

  a.clear();
  ASSERT_EQ(a.size(), 0);
}

TEST(SetModifiers, insert) {
  set<int> a;
  ASSERT_EQ(a.size(), 0);

  std::pair<set<int>::iterator, bool> res;
  res = a.insert(3);
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(res.second, true);
  ASSERT_EQ(*res.first, 3);

  res = a.insert(1);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(res.second, true);
  ASSERT_EQ(*res.first, 1);

  res = a.insert(2);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(res.second, true);
  ASSERT_EQ(*res.first, 2);

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());

  res = a.insert(2);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(res.second, false);
  ASSERT_EQ(*res.first, 2);
}

TEST(SetModifiers, erase) {
  set<int> a{2, 1, 3};
  ASSERT_EQ(a.size(), 3);

  auto b = a;
  auto it = b.begin();
  b.erase(it);
  ASSERT_EQ(b.size(), 2);

  b = a;
  it = b.begin();
  ++it;
  b.erase(it);
  ASSERT_EQ(b.size(), 2);

  b = a;
  it = b.begin();
  ++it;
  ++it;
  b.erase(it);
  ASSERT_EQ(b.size(), 2);
}

TEST(SetModifiers, swap) {
  set<int> a{2, 1, 3};

  set<int> b{6, 5};

  a.swap(b);
  ASSERT_EQ(a.size(), 2);
  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_EQ(b.size(), 3);
  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(SetModifiers, merge1) {
  set<int> a{1, 2, 3};
  set<int> b{5, 6};

  a.merge(b);
  ASSERT_EQ(a.size(), 5);

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

TEST(SetModifiers, merge2) {
  set<int> a{1, 2, 3};
  set<int> b{2, 3, 5, 6};

  a.merge(b);
  ASSERT_EQ(a.size(), 5);

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(it, a.end());

  it = b.begin();
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, b.end());
}

TEST(SetModifiers, merge3) {
  set<int> a{1, 2, 3};
  set<int> b{};

  a.merge(b);
  ASSERT_EQ(a.size(), 3);

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

TEST(SetModifiers, merge4) {
  set<int> a{1, 2, 3};
  set<int> b{4};

  a.merge(b);
  ASSERT_EQ(a.size(), 4);

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_TRUE(b.empty());
}

TEST(SetModifiers, merge5) {
  set<int> a{1, 2, 3};
  set<int> b{1};

  a.merge(b);
  ASSERT_EQ(a.size(), 3);

  set<int>::iterator it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());

  ASSERT_EQ(b.size(), 1);

  it = b.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(it, b.end());
}
// Set Lookup
// -----------------------------
TEST(SetModifiers, find) {
  set<int> a{1, 2, 3};

  auto it1 = a.begin();
  auto it2 = ++a.begin();
  auto it3 = ++(++a.begin());

  ASSERT_EQ(a.find(0), a.end());
  ASSERT_EQ(a.find(1), it1);
  ASSERT_EQ(a.find(2), it2);
  ASSERT_EQ(a.find(3), it3);
  ASSERT_EQ(a.find(4), a.end());
}

TEST(SetModifiers, contains) {
  set<int> a{1, 2, 3};

  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
  ASSERT_TRUE(a.contains(3));

  ASSERT_FALSE(a.contains(0));
  ASSERT_FALSE(a.contains(4));
}

// Extra tests
// -------------------------------------------
TEST(SetExtraTests, insert_iterate_remove) {
  int arr[] = {9, 0, 3, 5, 2, 7, 6, 4, 1, 8};
  set<int> s;
  for (auto e : arr) {
    s.insert(e);
  }

  ASSERT_EQ(s.size(), 10);

  // iterate forward
  set<int>::iterator it = s.begin();
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(*it, i);
    ++it;
  }

  // iterate backward
  set<int>::iterator it2 = s.end();
  for (int i = 9; i >= 0; --i) {
    --it2;
    ASSERT_EQ(*it2, i);
  }

  for (auto e : arr) {
    auto it = s.find(e);
    s.erase(it);
  }

  ASSERT_TRUE(s.empty());
}

using s21::vector;

TEST(SetInsertMany, test1) {
  set<int> s;
  using iterator = set<int>::iterator;

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

TEST(SetInsertMany, test2) {
  set<int> s{1, 2, 3};
  using iterator = set<int>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(1, 2, 3);

  ASSERT_EQ(res.size(), 3);

  ASSERT_EQ(res[0].first, s.begin());
  ASSERT_FALSE(res[0].second);

  ASSERT_EQ(res[1].first, ++s.begin());
  ASSERT_FALSE(res[1].second);

  ASSERT_EQ(res[2].first, ++(++s.begin()));
  ASSERT_FALSE(res[2].second);

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

TEST(SetInsertMany, test3) {
  set<int> s{1, 2, 3};
  using iterator = set<int>::iterator;

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

TEST(SetInsertMany, test4) {
  set<int> s{1, 2, 3};
  using iterator = set<int>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(1, 8, 1, 2, 9);

  ASSERT_EQ(res.size(), 5);

  ASSERT_EQ(*res[0].first, 1);
  ASSERT_FALSE(res[0].second);

  ASSERT_EQ(*res[1].first, 8);
  ASSERT_TRUE(res[1].second);

  ASSERT_EQ(*res[2].first, 1);
  ASSERT_FALSE(res[2].second);

  ASSERT_EQ(*res[3].first, 2);
  ASSERT_FALSE(res[3].second);

  ASSERT_EQ(*res[4].first, 9);
  ASSERT_TRUE(res[4].second);

  ASSERT_EQ(s.size(), 5);
  auto it = s.begin();
  ASSERT_EQ(*it, 1);
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
