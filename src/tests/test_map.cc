#include <gtest/gtest.h>

#include <stdexcept>

#include "s21_containers.h"

using s21::map;
using std::string;

// Member functions
// --------------------------------
TEST(MapMemberFunctions, DefaultConstructor) {
  map<int, string> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(MapMemberFunctions, InitListConstructor) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a[1], "one");
  ASSERT_EQ(a[2], "two");
  ASSERT_EQ(a[3], "three");
}

TEST(MapMemberFunctions, CopyConstructor) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b = a;

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a[1], "one");
  ASSERT_EQ(a[2], "two");
  ASSERT_EQ(a[3], "three");

  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(b[1], "one");
  ASSERT_EQ(b[2], "two");
  ASSERT_EQ(b[3], "three");
}

TEST(MapMemberFunctions, MoveConstructor) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b = std::move(a);

  ASSERT_EQ(a.size(), 0);

  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(b[1], "one");
  ASSERT_EQ(b[2], "two");
  ASSERT_EQ(b[3], "three");
}

TEST(MapMemberFunctions, AssignmentOperator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b;
  b = a;

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a[1], "one");
  ASSERT_EQ(a[2], "two");
  ASSERT_EQ(a[3], "three");

  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(b[1], "one");
  ASSERT_EQ(b[2], "two");
  ASSERT_EQ(b[3], "three");
}

TEST(MapMemberFunctions, ChainedAssignmentOperator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b, c, d;
  d = c = b = a;

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a[1], "one");
  ASSERT_EQ(a[2], "two");
  ASSERT_EQ(a[3], "three");

  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(b[1], "one");
  ASSERT_EQ(b[2], "two");
  ASSERT_EQ(b[3], "three");

  ASSERT_EQ(c.size(), 3);
  ASSERT_EQ(c[1], "one");
  ASSERT_EQ(c[2], "two");
  ASSERT_EQ(c[3], "three");

  ASSERT_EQ(d.size(), 3);
  ASSERT_EQ(d[1], "one");
  ASSERT_EQ(d[2], "two");
  ASSERT_EQ(d[3], "three");
}

TEST(MapMemberFunctions, MoveAssignmentOperator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b = std::move(a);

  ASSERT_EQ(a.size(), 0);

  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(b[1], "one");
  ASSERT_EQ(b[2], "two");
  ASSERT_EQ(b[3], "three");
}

// Element access
// --------------------------------
TEST(MapElementAccess, at) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");
  ASSERT_EQ(a.at(3), "three");

  ASSERT_THROW(a.at(0), std::out_of_range);
  ASSERT_THROW(a.at(5), std::out_of_range);
}

TEST(MapElementAccess, index_read) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  ASSERT_EQ(a[1], "one");
  ASSERT_EQ(a[2], "two");
  ASSERT_EQ(a[3], "three");
}

TEST(MapElementAccess, index_write) {
  map<int, string> a;
  a[1] = "one";
  a[2] = "two";
  a[3] = "three";

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");
  ASSERT_EQ(a.at(3), "three");
}

// Map Iterators
// --------------------------------
TEST(MapIterators, begin) {
  map<int, string> empty_map;
  ASSERT_EQ(empty_map.begin(), empty_map.end());

  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::iterator it = a.begin();
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");
}

TEST(MapIterators, end) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::iterator it = a.end();
  --it;
  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, "three");
}

TEST(MapIterators, IteratorNext) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::iterator it = a.begin();
  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "two");

  ++it;
  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, "three");

  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(MapIterators, ApplyStarToIterator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::iterator it = a.begin();
  std::pair<const int, string> p1{1, "one"};
  ASSERT_TRUE(*it == p1);

  ++it;
  std::pair<const int, string> p2{2, "two"};
  ASSERT_TRUE(*it == p2);

  ++it;
  std::pair<const int, string> p3{3, "three"};
  ASSERT_TRUE(*it == p3);
}

TEST(MapIterators, ApplyArrowToIterator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::iterator it = a.begin();
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");
}

TEST(MapIterators, ApplyArrowToConstIterator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::const_iterator it = a.begin();
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");
}

TEST(MapIterators, AssignValueUsingIterator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::iterator it = a.begin();

  // THIS MUST NOT COMPILE!
  // it->first = 100;

  it->second = "ONE";
  ASSERT_EQ(it->second, "ONE");

  ++it;
  (*it).second = "TWO";
  ASSERT_EQ(it->second, "TWO");

  ++it;
  (*it).second = "THREE";
  ASSERT_EQ(it->second, "THREE");
}

TEST(MapIterators, AssignUsingConstIterator) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  map<int, string>::const_iterator it = a.begin();
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");

  // THIS MUST NOT COMPILE!
  // (*it).second = "ONE";
  // it->second = "ONE";
}

// Map Capacity
// -------------------------
TEST(MapCapacity, empty) {
  map<int, string> a;
  ASSERT_TRUE(a.empty());

  map<int, string> b{{1, "one"}};
  ASSERT_FALSE(b.empty());
}

TEST(MapCapacity, size) {
  map<int, string> a;
  ASSERT_EQ(a.size(), 0);

  map<int, string> b{{1, "one"}};
  ASSERT_EQ(b.size(), 1);

  map<int, string> c{{1, "one"}, {2, "two"}, {3, "three"}};
  ASSERT_EQ(c.size(), 3);
}

TEST(MapCapacity, max_size) {
  map<int, string> a;
  ASSERT_TRUE(a.max_size() > a.size());
}

// Modifiers
// -------------------
TEST(MapModifiers, clear) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  ASSERT_EQ(a.size(), 3);

  a.clear();
  ASSERT_EQ(a.size(), 0);
}

TEST(MapModifiers, insert_pair) {
  map<int, string> a;
  ASSERT_EQ(a.size(), 0);

  std::pair<map<int, string>::iterator, bool> res;

  res = a.insert({2, "two"});
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(res.second, true);
  ASSERT_EQ(res.first->first, 2);
  ASSERT_EQ(res.first->second, "two");
  ASSERT_EQ(a.at(2), "two");

  res = a.insert({1, "one"});
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(res.second, true);
  ASSERT_EQ(res.first->first, 1);
  ASSERT_EQ(res.first->second, "one");
  ASSERT_EQ(a.at(1), "one");

  res = a.insert({3, "three"});
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(res.second, true);
  ASSERT_EQ(res.first->first, 3);
  ASSERT_EQ(res.first->second, "three");
  ASSERT_EQ(a.at(3), "three");

  // insert twice
  res = a.insert({1, "one"});
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(res.second, false);
  ASSERT_EQ(res.first->first, 1);
  ASSERT_EQ(res.first->second, "one");
  ASSERT_EQ(a.at(1), "one");

  // insert twice with another value
  res = a.insert({1, "ONE"});
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(res.second, false);
  ASSERT_EQ(res.first->first, 1);
  ASSERT_EQ(res.first->second, "one");
  ASSERT_EQ(a.at(1), "one");
}

TEST(MapModifiers, insert_key_obj) {
  map<int, string> a;
  ASSERT_EQ(a.size(), 0);

  a.insert(1, "one");
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.at(1), "one");

  a.insert(2, "two");
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.at(2), "two");

  a.insert(3, "three");
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.at(3), "three");
}

TEST(MapModifiers, insert_or_assign) {
  map<int, string> a;
  ASSERT_EQ(a.size(), 0);

  a.insert_or_assign(1, "one");
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.at(1), "one");

  a.insert_or_assign(2, "two");
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.at(2), "two");

  a.insert_or_assign(3, "three");
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.at(3), "three");

  a.insert_or_assign(1, "ONE");
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.at(1), "ONE");

  a.insert_or_assign(4, "four");
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.at(4), "four");
}

TEST(MapModifiers, erase) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  ASSERT_EQ(a.size(), 3);

  auto b = a;
  auto it = b.begin();
  b.erase(it);
  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(b.at(2), "two");
  ASSERT_EQ(b.at(3), "three");

  b = a;
  it = b.begin();
  ++it;
  b.erase(it);
  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(b.at(1), "one");
  ASSERT_EQ(b.at(3), "three");

  b = a;
  it = b.begin();
  ++it;
  ++it;
  b.erase(it);
  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(b.at(1), "one");
  ASSERT_EQ(b.at(2), "two");
}

TEST(MapModifiers, swap) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b{{5, "five"}, {6, "six"}};

  a.swap(b);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.at(5), "five");
  ASSERT_EQ(a.at(6), "six");

  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(b.at(1), "one");
  ASSERT_EQ(b.at(2), "two");
  ASSERT_EQ(b.at(3), "three");
}

TEST(MapModifiers, merge1) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b{{5, "five"}, {6, "six"}};

  a.merge(b);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");
  ASSERT_EQ(a.at(3), "three");
  ASSERT_EQ(a.at(5), "five");
  ASSERT_EQ(a.at(6), "six");

  ASSERT_TRUE(b.empty());
}

TEST(MapModifiers, merge2) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, string> b{{1, "one"}, {3, "THREE"}, {5, "five"}, {6, "six"}};

  a.merge(b);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");
  ASSERT_EQ(a.at(3), "three");
  ASSERT_EQ(a.at(5), "five");
  ASSERT_EQ(a.at(6), "six");

  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(b.at(1), "one");
  ASSERT_EQ(b.at(3), "THREE");
}

TEST(MapModifiers, merge3) {
  map<int, string> a{{1, "one"}, {2, "two"}};
  map<int, string> b{{5, "five"}};

  a.merge(b);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");
  ASSERT_EQ(a.at(5), "five");

  ASSERT_EQ(b.size(), 0);
}

TEST(MapModifiers, merge4) {
  map<int, string> a{{1, "one"}, {2, "two"}};
  map<int, string> b{{0, "zero"}};

  a.merge(b);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.at(0), "zero");
  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");

  ASSERT_EQ(b.size(), 0);
}

TEST(MapModifiers, merge5) {
  map<int, string> a{{1, "one"}, {2, "two"}};
  map<int, string> b{{1, "ONE"}};

  a.merge(b);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");

  ASSERT_EQ(b.size(), 1);
  ASSERT_EQ(b.at(1), "ONE");
}

TEST(MapModifiers, merge6) {
  map<int, string> a{{1, "one"}, {2, "two"}};
  map<int, string> b{};

  a.merge(b);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.at(1), "one");
  ASSERT_EQ(a.at(2), "two");

  ASSERT_EQ(b.size(), 0);
}

// Map Lookup
// -----------------------------
TEST(MapModifiers, contains) {
  map<int, string> a{{1, "one"}, {2, "two"}, {3, "three"}};

  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
  ASSERT_TRUE(a.contains(3));

  ASSERT_FALSE(a.contains(0));
  ASSERT_FALSE(a.contains(4));
}

using s21::vector;

TEST(MapInsertMany, test1) {
  map<int, string> s;
  using iterator = map<int, string>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(
      std::pair{1, "one"}, std::pair{2, "two"}, std::pair{3, "three"});

  ASSERT_EQ(res.size(), 3);

  ASSERT_EQ(res[0].first, s.begin());
  ASSERT_TRUE(res[0].second);

  ASSERT_EQ(res[1].first, ++s.begin());
  ASSERT_TRUE(res[1].second);

  ASSERT_EQ(res[2].first, ++(++s.begin()));
  ASSERT_TRUE(res[2].second);

  ASSERT_EQ(s.size(), 3);
  auto it = s.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");
  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "two");
  ++it;
  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, "three");
  ++it;
  ASSERT_EQ(it, s.end());
}

TEST(MapInsertMany, test2) {
  map<int, string> s{
      {1, "one"},
      {2, "two"},
      {3, "three"},
  };
  using iterator = map<int, string>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(
      std::pair{1, "one"}, std::pair{2, "two"}, std::pair{3, "three"});

  ASSERT_EQ(res.size(), 3);

  ASSERT_EQ(res[0].first, s.begin());
  ASSERT_FALSE(res[0].second);

  ASSERT_EQ(res[1].first, ++s.begin());
  ASSERT_FALSE(res[1].second);

  ASSERT_EQ(res[2].first, ++(++s.begin()));
  ASSERT_FALSE(res[2].second);

  ASSERT_EQ(s.size(), 3);
  auto it = s.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");
  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "two");
  ++it;
  ASSERT_EQ(it->first, 3);
  ASSERT_EQ(it->second, "three");
  ++it;
  ASSERT_EQ(it, s.end());
}

TEST(MapInsertMany, test3) {
  map<int, string> s{
      {1, "one"},
      {5, "five"},
      {8, "eight"},
  };
  using iterator = map<int, string>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(
      std::pair{0, "zero"}, std::pair{2, "two"}, std::pair{7, "seven"});

  ASSERT_EQ(res.size(), 3);

  ASSERT_TRUE(res[0].second);
  ASSERT_TRUE(res[1].second);
  ASSERT_TRUE(res[2].second);

  ASSERT_EQ(s.size(), 6);
  auto it = s.begin();

  ASSERT_EQ(it->first, 0);
  ASSERT_EQ(it->second, "zero");
  ++it;
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");
  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "two");
  ++it;
  ASSERT_EQ(it->first, 5);
  ASSERT_EQ(it->second, "five");
  ++it;
  ASSERT_EQ(it->first, 7);
  ASSERT_EQ(it->second, "seven");
  ++it;
  ASSERT_EQ(it->first, 8);
  ASSERT_EQ(it->second, "eight");
  ++it;
  ASSERT_EQ(it, s.end());
}

TEST(MapInsertMany, test4) {
  map<int, string> s{
      {1, "one"},
      {5, "five"},
      {8, "eight"},
  };
  using iterator = map<int, string>::iterator;

  vector<std::pair<iterator, bool>> res = s.insert_many(
      std::pair{1, "ONE"}, std::pair{2, "two"}, std::pair{5, "FIVE"});

  ASSERT_EQ(res.size(), 3);

  ASSERT_FALSE(res[0].second);
  ASSERT_TRUE(res[1].second);
  ASSERT_FALSE(res[2].second);

  ASSERT_EQ(s.size(), 4);
  auto it = s.begin();

  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "one");
  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "two");
  ++it;
  ASSERT_EQ(it->first, 5);
  ASSERT_EQ(it->second, "five");
  ++it;
  ASSERT_EQ(it->first, 8);
  ASSERT_EQ(it->second, "eight");
  ++it;
  ASSERT_EQ(it, s.end());
}
