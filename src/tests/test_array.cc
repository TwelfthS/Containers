// @todo ${file}:69

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <utility>

#include "s21_containersplus.h"

TEST(array_initializer_list, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::array<int, 10> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (size_t i = 0; i < s21_a.size(); i++) {
    EXPECT_EQ(a[i], s21_a[i]);
  }

  for (size_t i = 0; i < s21_b.size(); i++) {
    EXPECT_EQ(b[i], s21_b[i]);
  }
}

TEST(array_at, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < (int)(s21_a.size()); i++) {
    EXPECT_EQ(a.at(i), s21_a.at(i));
  }

  EXPECT_ANY_THROW(s21_a.at(-1));
  EXPECT_ANY_THROW(s21_a.at(s21_a.size() + 1));
}

TEST(array_oper_SCOBKA, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < (int)(s21_a.size()); i++) {
    EXPECT_EQ(a[i], s21_a[i]);
  }

  EXPECT_ANY_THROW(s21_a[-1]);
  EXPECT_ANY_THROW(s21_a[s21_a.size() + 1]);
}

TEST(array_front_back, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.front(), s21_a.front());
  // a.back();s21_a.back();
  // EXPECT_EQ(a.back(), s21_a.back()); WTF
}

TEST(array_iterator, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto iter_d = a.data();
  auto s21_iter_d = s21_a.data();

  EXPECT_EQ(*iter_d, *s21_iter_d);  //!! no idea wht is it

  auto iter_b = a.begin();
  auto s21_iter_b = s21_a.begin();

  auto iter_e = a.end();  // out of range`
  auto s21_iter_e = s21_a.end();

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*(iter_b + i), *(s21_iter_b + i));
    EXPECT_EQ(*(iter_e - 1 - i), *(s21_iter_e - 1 - i));
    EXPECT_TRUE((iter_e - 10 + i) == (iter_b + i));
    EXPECT_TRUE((s21_iter_e - 10 + i) == (s21_iter_b + i));
  }
}

TEST(array_empty, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // std::array <int,0>a_empty = std::array();
  EXPECT_EQ(a.empty(), s21_a.empty());
  //!! add 0-sz array
}

TEST(array_size, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), s21_a.size());
  EXPECT_EQ(a.max_size(), s21_a.max_size());
  //!! add 0-sz array
}

TEST(array_swap, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> b = {1, 3, 1, 3, 1, 3, 1, 3, 1, 3};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_b = {1, 3, 1, 3, 1, 3, 1, 3, 1, 3};

  a.swap(b);
  s21_a.swap(s21_b);

  for (size_t i = 0; i < s21_a.size(); i++) {
    EXPECT_EQ(a[i], s21_a[i]);
    EXPECT_EQ(b[i], s21_b[i]);
  }
}

TEST(array_oper_copy, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> b;
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_b;

  b = a;
  s21_b = s21_a;

  for (size_t i = 0; i < s21_a.size(); i++) {
    EXPECT_EQ(a[i], b[i]);
    EXPECT_EQ(s21_a[i], s21_b[i]);
  }
}

TEST(array_oper_move, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> b;

  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_b;

  b = std::move(a);
  //   auto iter_s21_a_begin = s21_a.begin();
  //   auto iter_s21_a_end = s21_a.end();
  s21_b = std::move(s21_a);
  for (size_t i = 0; i < s21_a.size(); i++) {
    EXPECT_EQ(a[i], b[i]);
    EXPECT_EQ(s21_a[i], s21_b[i]);
  }
}

TEST(array_fill, with_int) {
  std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> s21_a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  a.fill(148);
  s21_a.fill(148);

  for (size_t i = 0; i < s21_a.size(); i++) {
    EXPECT_EQ(a[i], s21_a[i]);
  }
}
