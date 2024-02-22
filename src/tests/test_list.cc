// @todo ${file}:69

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>

#include "s21_containers.h"

TEST(list_CTor, with_int) {
  // initializer_list
  std::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), s21_a.size());

  auto s21_i = s21_a.begin();
  for (auto i = a.begin(); i != a.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }

  // empty with size
  s21::list<int> a5(5);
  EXPECT_EQ(5, a5.size());

  // copy CTor
  s21::list<int> s21_a_copy = s21_a;

  EXPECT_EQ(s21_a_copy.size(), s21_a.size());

  s21_i = s21_a.begin();
  for (auto i = s21_a_copy.begin(); i != s21_a_copy.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }

  // move CTor
  s21::list<int> s21_a_move = std::move(s21_a_copy);

  EXPECT_EQ(s21_a_move.size(), s21_a.size());

  s21_i = s21_a.begin();
  for (auto i = s21_a_move.begin(); i != s21_a_move.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }

  // move operator=
  s21::list<int> s21_a_move_oper;
  s21_a_move_oper = std::move(s21_a_move);
  EXPECT_EQ(s21_a_move_oper.size(), s21_a.size());

  s21_i = s21_a.begin();
  for (auto i = s21_a_move_oper.begin(); i != s21_a_move_oper.end();
       i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list, copy_assignment_operator) {
  // copy operator=
  s21::list<int> a{1, 2, 3};
  s21::list<int> b;
  b = a;

  EXPECT_EQ(b.size(), a.size());

  auto s21_i = a.begin();
  for (auto i = b.begin(); i != b.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list, move_assignment_operator) {
  // move operator=
  s21::list<int> a{1, 2, 3};
  s21::list<int> b;
  b = std::move(a);

  EXPECT_EQ(b.size(), 3);

  s21::list<int> c{1, 2, 3};
  auto s21_i = c.begin();
  for (auto i = b.begin(); i != b.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list_front_back, with_int) {
  std::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.front(), s21_a.front());
  EXPECT_EQ(a.back(), s21_a.back());
}

TEST(list_empty_and_size, with_int) {
  std::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> l_empt;
  s21::list<int> s21_l_empt;

  EXPECT_TRUE(l_empt.empty());
  EXPECT_TRUE(s21_l_empt.empty());

  EXPECT_FALSE(s21_a.empty());
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.size(), s21_a.size());
  EXPECT_EQ(l_empt.size(), s21_l_empt.size());
}

TEST(list_clear, with_int) {
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> s21_l_empt;

  s21_l_empt.clear();
  s21_a.clear();

  EXPECT_TRUE(s21_a.empty());
  EXPECT_TRUE(s21_l_empt.empty());
}

TEST(list_push_and_pop, with_int) {
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_TRUE((s21_a.size() == 10) && s21_a.back() == 10);
  s21_a.push_back(11);
  EXPECT_TRUE((s21_a.size() == 11) && s21_a.back() == 11);
  // push some
  s21_a.push_back(12);
  s21_a.push_back(13);
  s21_a.push_front(0);
  s21_a.push_front(-1);
  s21::list<int> s21_a_reference = {-1, 0, 1, 2,  3,  4,  5, 6,
                                    7,  8, 9, 10, 11, 12, 13};
  // check
  EXPECT_EQ(s21_a.size(), 15);
  auto s21_i = s21_a.begin();
  for (auto i = s21_a_reference.begin(); i != s21_a_reference.end();
       i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
  // pop some
  for (int i = 0; i < 3; i++) s21_a.pop_back();
  for (int i = 0; i < 3; i++) s21_a.pop_front();
  s21_a_reference = {2, 3, 4, 5, 6, 7, 8, 9, 10};
  // check
  s21_i = s21_a.begin();
  for (auto i = s21_a_reference.begin(); i != s21_a_reference.end();
       i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
  // pop all
  for (int i = 0; i < 5; i++) s21_a.pop_back();
  for (int i = 0; i < 4; i++) s21_a.pop_front();
  EXPECT_TRUE(s21_a.empty());
  // pop empty
  EXPECT_ANY_THROW(s21_a.pop_back());
  EXPECT_ANY_THROW(s21_a.pop_front());
  // push back 1 to empty
  s21_a.push_back(11);
  EXPECT_TRUE((s21_a.size() == 1) && s21_a.back() == 11 && s21_a.front() == 11);

  s21_a.pop_front();
  EXPECT_TRUE(s21_a.empty());
  // push front 1 to empty
  s21_a.push_front(-1);
  EXPECT_TRUE((s21_a.size() == 1) && s21_a.back() == -1 && s21_a.front() == -1);
}

TEST(list_swap, with_int) {
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> s21_b = {10, 9, 8, 7, 6, 5, 4, 3, 2};
  s21::list<int> s21_a_reference = s21_a;
  s21::list<int> s21_b_reference = s21_b;
  s21_a.swap(s21_b);

  EXPECT_TRUE(s21_a.size() == 9 && s21_b.size() == 10);

  auto i_ref = s21_b_reference.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
  i_ref = s21_a_reference.begin();
  for (auto i = s21_b.begin(); i != s21_b.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }

  // swap with empty
  s21_b.clear();
  EXPECT_TRUE(s21_b.empty());

  s21_b.swap(s21_a);
  EXPECT_TRUE(s21_a.empty());
  i_ref = s21_a_reference.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }

  s21_b.swap(s21_a);
  EXPECT_TRUE(s21_b.empty());
  i_ref = s21_a_reference.begin();
  for (auto i = s21_b.begin(); i != s21_b.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_reverse, with_int1) {
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> s21_a_rev_ref = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  s21_a.reverse();
  auto i_ref = s21_a_rev_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
  // reverse empty
  s21_a.clear();
  s21_a.reverse();
  EXPECT_TRUE(s21_a.empty());

  // reverse single-elem list
  s21_a.push_back(117);
  s21_a.reverse();
  EXPECT_TRUE(!s21_a.empty() && s21_a.size() == 1 && s21_a.front() == 117);
}

TEST(list_reverse, with_int2) {
  s21::list<int> s21_a = {1, 2, 3};
  s21::list<int> s21_a_rev_ref = {3, 2, 1};

  s21_a.reverse();
  auto i_ref = s21_a_rev_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }

  // reverse empty
  s21_a.clear();
  s21_a.reverse();
  EXPECT_TRUE(s21_a.empty());

  // reverse single-elem list
  s21_a.push_back(117);
  s21_a.reverse();
  EXPECT_TRUE(!s21_a.empty() && s21_a.size() == 1 && s21_a.front() == 117);
}

TEST(list_reverse, with_int3) {
  s21::list<int> s21_a = {1, 2, 3, 4};
  s21::list<int> s21_a_rev_ref = {4, 3, 2, 1};

  s21_a.reverse();
  auto i_ref = s21_a_rev_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }

  s21_a.insert(s21_a.end(), 100);
  s21::list<int> s21_a_rev_ref2 = {4, 3, 2, 1, 100};
  auto i_ref2 = s21_a_rev_ref2.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref2++) {
    EXPECT_EQ(*i_ref2, *i);
  }
}

TEST(list_reverse, with_int4) {
  s21::list<int> s21_a = {1, 2};
  s21::list<int> s21_a_rev_ref = {2, 1};

  s21_a.reverse();
  auto i_ref = s21_a_rev_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

void TestSplice(std::initializer_list<int> const& l1, size_t n_pos,
                std::initializer_list<int> const& l2) {
  // first for s21::list
  s21::list<int> list1{l1};
  s21::list<int> list2{l2};

  auto it = list1.begin();
  for (size_t i = 0; i < n_pos; ++i) ++it;
  list1.splice(it, list2);

  // and then for std::list
  std::list<int> std_list1{l1};
  std::list<int> std_list2{l2};
  auto std_it = std_list1.begin();
  for (size_t i = 0; i < n_pos; ++i) ++std_it;
  std_list1.splice(std_it, std_list2);

  // compare results here
  auto s21_i = list1.begin();
  for (auto i = std_list1.begin(); i != std_list1.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list_splice, splice1) {
  TestSplice({}, 0, {});
  TestSplice({}, 0, {1});
  TestSplice({}, 0, {1, 2});
  TestSplice({}, 0, {1, 2, 3});
}

TEST(list_splice, splice2) {
  TestSplice({1}, 0, {});
  TestSplice({1}, 1, {});

  TestSplice({1}, 0, {2});
  TestSplice({1}, 1, {2});

  TestSplice({1}, 0, {2, 3});
  TestSplice({1}, 1, {2, 3});
}

TEST(list_splice, splice3) {
  TestSplice({1, 2, 3}, 0, {});
  TestSplice({1, 2, 3}, 1, {});
  TestSplice({1, 2, 3}, 2, {});
  TestSplice({1, 2, 3}, 3, {});
}

TEST(list_splice, splice4) {
  TestSplice({1, 2, 3}, 0, {4});
  TestSplice({1, 2, 3}, 1, {4});
  TestSplice({1, 2, 3}, 2, {4});
  TestSplice({1, 2, 3}, 3, {4});
}

TEST(list_splice, splice5) {
  TestSplice({1, 2, 3}, 0, {10, 20});
  TestSplice({1, 2, 3}, 1, {10, 20});
  TestSplice({1, 2, 3}, 2, {10, 20});
  TestSplice({1, 2, 3}, 3, {10, 20});
}

TEST(list_merge, with_int2) {
  s21::list<int> s21_a = {};
  s21::list<int> s21_b = {1, 2, 3};

  s21_a.merge(s21_b);
  EXPECT_EQ(s21_a.size(), 3);

  s21::list<int> s21_a_b_ref = {1, 2, 3};
  auto i_ref = s21_a_b_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_merge, with_int3) {
  s21::list<int> s21_a = {1, 2, 3};
  s21::list<int> s21_b = {};

  s21::list<int> s21_a_b_ref = {1, 2, 3};
  s21_a.merge(s21_b);
  EXPECT_EQ(s21_a.size(), 3);

  auto i_ref = s21_a_b_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_merge, with_int4) {
  s21::list<int> s21_a = {1, 2, 3};
  s21::list<int> s21_b = {1};

  s21::list<int> s21_a_b_ref = {1, 1, 2, 3};
  s21_a.merge(s21_b);
  EXPECT_EQ(s21_a.size(), 4);

  auto i_ref = s21_a_b_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_merge, with_int5) {
  s21::list<int> s21_a = {1, 2, 3};
  s21::list<int> s21_b = {3};

  s21::list<int> s21_a_b_ref = {1, 2, 3, 3};
  s21_a.merge(s21_b);
  EXPECT_EQ(s21_a.size(), 4);

  auto i_ref = s21_a_b_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_merge, with_int6) {
  s21::list<int> s21_a = {1, 3, 5, 100};
  s21::list<int> s21_b = {1, 2, 3, 4, 5, 6};

  s21::list<int> s21_a_b_ref = {1, 1, 2, 3, 3, 4, 5, 5, 6, 100};
  s21_a.merge(s21_b);
  EXPECT_EQ(s21_a.size(), 10);

  auto i_ref = s21_a_b_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_merge, with_int7) {
  s21::list<int> s21_a = {1, 3, 5, 7, 9};
  s21::list<int> s21_b = {2, 4, 6, 8, 10};

  s21::list<int> s21_a_b_ref = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_a.merge(s21_b);
  EXPECT_EQ(s21_a.size(), 10);

  auto i_ref = s21_a_b_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_sort, with_int) {
  s21::list<int> s21_a = {1, 4, 3, 5, 7, 9, 2, 4, 1, 6, 8, 10};
  s21::list<int> s21_a_sorted_ref = {1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 10};

  s21_a.sort();

  auto i_ref = s21_a_sorted_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }

  s21_a.clear();
  s21_a.sort();
  EXPECT_EQ(s21_a.size(), 0);

  // sort single-elem list
  s21_a.push_back(17);
  s21_a.sort();
  EXPECT_TRUE(s21_a.size() == 1 && s21_a.front() == 17);

  s21_a.push_back(17);
  s21_a.sort();
  EXPECT_TRUE(s21_a.size() == 2 && s21_a.front() == 17 && s21_a.back() == 17);
}

TEST(list_sort, with_int2) {
  s21::list<int> s21_a = {10, 4, 1, 4, 2, 1, 3, 6, 7, 5, 9, 8};
  s21::list<int> s21_a_sorted_ref = {1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 10};

  s21_a.sort();

  auto i_ref = s21_a_sorted_ref.begin();
  for (auto i = s21_a.begin(); i != s21_a.end(); i++, i_ref++) {
    EXPECT_EQ(*i_ref, *i);
  }
}

TEST(list_iterator, with_int) {
  s21::list<int> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto it_b = s21_a.begin();
  auto it_e = s21_a.end();
  it_e--;
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*it_b, i + 1);
    EXPECT_EQ(*it_e, 10 - i);

    it_b++;
    it_e--;
  }

  it_b = s21_a.begin();
  it_e = s21_a.end();
  for (int i = 0; i < 5; i++, it_b++, it_e--) EXPECT_TRUE(it_b != it_e);
  EXPECT_TRUE(it_b == it_e);
}

TEST(list_erase, erase) {
  s21::list<int> l1;
  EXPECT_TRUE(l1.empty());

  l1.erase(l1.begin());
  EXPECT_TRUE(l1.empty());

  s21::list<int> l2{13, 44, 112, 11};
  l2.erase(l2.begin());
  EXPECT_EQ(l2.front(), 44);

  l2.erase(++l2.begin());
  l2.erase(--l2.end());

  std::list<int> std_l2{44};

  auto s21_i = std_l2.begin();
  for (auto i = l2.begin(); i != l2.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list_iterator, insert_prev_end) {
  std::list<int> std_l1{1, 2, 3};
  s21::list<int> l1{1, 2, 3};

  auto std_it = std_l1.insert(--std_l1.end(), 7);
  ASSERT_EQ(*std_it, 7);

  auto it = l1.insert(--l1.end(), 7);
  ASSERT_EQ(*it, 7);

  auto s21_i = std_l1.begin();
  for (auto i = l1.begin(); i != l1.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list_iterator, insert_end) {
  std::list<int> std_l1{1, 2, 3};
  s21::list<int> l1{1, 2, 3};

  auto std_it = std_l1.insert(std_l1.end(), 7);
  ASSERT_EQ(*std_it, 7);

  auto it = l1.insert(l1.end(), 7);
  ASSERT_EQ(*it, 7);

  auto s21_i = std_l1.begin();
  for (auto i = l1.begin(); i != l1.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list_iterator, insert) {
  std::list<int> std_l1{1, 2, 3};
  s21::list<int> l1{1, 2, 3};
  std_l1.insert(++std_l1.begin(), 23);
  l1.insert(++l1.begin(), 23);
  std_l1.insert(std_l1.begin(), 22);
  l1.insert(l1.begin(), 22);
  std_l1.insert(std_l1.end()--, 22);
  l1.insert(l1.end()--, 22);

  auto s21_i = std_l1.begin();
  for (auto i = l1.begin(); i != l1.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(ListExtra, insert_empty) {
  s21::list<int> a;
  a.insert(a.begin(), 1);

  ASSERT_EQ(a.size(), 1);

  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many_back1) {
  s21::list<int> a;
  a.insert_many_back(1, 2);

  ASSERT_EQ(a.size(), 2);

  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many_back2) {
  s21::list<int> a{1, 2};
  a.insert_many_back(3, 4, 5);

  ASSERT_EQ(a.size(), 5);

  auto it = a.begin();
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
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many_front1) {
  s21::list<int> a;
  a.insert_many_front(1, 2);

  ASSERT_EQ(a.size(), 2);

  auto it = a.begin();
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many_front2) {
  s21::list<int> a{1, 2};
  a.insert_many_front(3, 4, 5);

  ASSERT_EQ(a.size(), 5);

  auto it = a.begin();
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many1) {
  s21::list<int> a;
  a.insert_many(a.begin(), 1, 2);

  ASSERT_EQ(a.size(), 2);

  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many2) {
  s21::list<int> a;
  a.insert_many(a.end(), 1, 2);

  ASSERT_EQ(a.size(), 2);

  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many3) {
  s21::list<int> a{1, 2, 3};
  a.insert_many(a.end(), 4, 5, 6);

  ASSERT_EQ(a.size(), 6);

  auto it = a.begin();
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
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many4) {
  s21::list<int> a{1, 2, 3};
  a.insert_many(a.begin(), 4, 5, 6);

  ASSERT_EQ(a.size(), 6);

  auto it = a.begin();
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(ListBonus, insert_many5) {
  s21::list<int> a{1, 2, 3};
  a.insert_many(++a.begin(), 4, 5, 6);

  ASSERT_EQ(a.size(), 6);

  auto it = a.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, a.end());
}

TEST(list_unique, unique) {
  s21::list<int> l1;

  EXPECT_THROW(l1.unique(), std::logic_error);

  s21::list<int> l2{1, 2, 3, 4, 4, 4, 4, 5, 5, 5};
  l2.unique();

  s21::list<int> std_l2{1, 2, 3, 4, 4, 4, 4, 5, 5, 5};
  std_l2.unique();

  auto s21_i = std_l2.begin();
  for (auto i = l2.begin(); i != l2.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list_splice, splice) {
  s21::list<int> list1{1, 2, 3, 4, 5};
  s21::list<int> list2{10, 20, 30, 40, 50};
  auto it = list1.begin();
  list1.splice(it, list2);

  s21::list<int> std_list1{1, 2, 3, 4, 5};
  s21::list<int> std_list2{10, 20, 30, 40, 50};
  auto it_std = std_list1.begin();
  std_list1.splice(it_std, std_list2);

  auto s21_i = list1.begin();
  for (auto i = std_list1.begin(); i != std_list1.end(); i++, s21_i++) {
    EXPECT_EQ(*i, *s21_i);
  }
}

TEST(list, ListOfStrings) {
  s21::list<std::string> a{"1", "2", "3"};

  a.push_front("0");
  a.push_back("4");

  std::string sum;
  for (auto e : a) {
    sum += e;
  }

  EXPECT_EQ(sum, "01234");
}
