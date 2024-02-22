#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "s21_containers.h"

using s21::vector;

TEST(CreateVector, test1) {
  vector<int> V1;
  std::vector<int> V2;
  V1.push_back(10);
  V2.push_back(10);
  ASSERT_EQ(V1.at(0), V2.at(0));
}

TEST(CreateVector, test2) {
  vector<int> V1(5);
  ASSERT_EQ(V1.size(), 5);
}

TEST(CreateVector, test3) {
  vector<int> V1 = {4, -9, 213342454};
  std::vector<int> V2 = {4, -9, 213342454};
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
  }
}

TEST(CreateVector, test4) {
  vector<char> V1;
  std::vector<char> V2;
  V1.push_back('r');
  V2.push_back('r');
  ASSERT_EQ(V1.at(0), V2.at(0));
}

TEST(CopyVector, test1) {
  vector<int> V1 = {6, 5, 10};
  vector<int> V2 = V1;

  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
    ASSERT_NE(&V1.at(i), &V2.at(i));
  }
}

TEST(MoveVector, test1) {
  vector<int> V1 = {4, 5, 6};
  vector<int> V2 = std::move(V1);
  for (int i = 0; i < (int)V2.size(); i++) {
    ASSERT_EQ(V2.at(i), i + 4);
  }
  ASSERT_TRUE(V1.empty());
}

TEST(vector, assign_operator) {
  vector<int> V1 = {4, 5, 6};
  vector<int> V2;
  V2 = V1;

  ASSERT_EQ(V1.size(), V2.size());
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
    ASSERT_NE(&V1.at(i), &V2.at(i));
  }
}

TEST(vector, assign_operator_chain) {
  vector<int> V1 = {4, 5, 6};
  vector<int> V2, V3;
  V3 = V2 = V1;

  ASSERT_EQ(V1.size(), V2.size());
  ASSERT_EQ(V2.size(), V3.size());
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
    ASSERT_EQ(V2.at(i), V3.at(i));

    ASSERT_NE(&V1.at(i), &V2.at(i));
    ASSERT_NE(&V2.at(i), &V3.at(i));
  }
}

TEST(vector, move_assign_operator) {
  vector<int> V1 = {4, 5, 6};
  vector<int> V2;
  V2 = std::move(V1);

  for (int i = 0; i < (int)V2.size(); i++) {
    ASSERT_EQ(V2.at(i), i + 4);
  }
  ASSERT_TRUE(V1.empty());
}

TEST(vector_at, test1) {
  vector<int> V1 = {3, 4, 5, 8, 9, 10, 11};
  ASSERT_THROW(V1.at(-1), std::out_of_range);
  ASSERT_THROW(V1.at(7), std::out_of_range);
  ASSERT_THROW(V1.at(100), std::out_of_range);

  for (size_t i = 0; i < V1.size(); ++i) {
    ASSERT_NO_THROW(V1.at(i));
  }
}

TEST(vector_operator, test1) {
  vector<int> V1 = {4, 5, 6};
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1[i], i + 4);
  }
}

TEST(vector_front, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  ASSERT_EQ(V1.front(), V2.front());
}

TEST(vector_begin, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  auto it1 = V1.begin();
  auto it2 = V2.begin();
  ASSERT_EQ(*it1, *it2);
}

TEST(vector_back, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  ASSERT_EQ(V1.back(), V2.back());
}

TEST(vector_end, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  auto it1 = V1.end();
  auto it2 = V2.end();
  it1--;
  it2--;
  ASSERT_EQ(*it1, *it2);
}

TEST(vector_data, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  int *data1 = V1.data();
  int *data2 = V2.data();
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(data1[i], data2[i]);
  }
}

TEST(vector_empty, test1) {
  vector<int> V1 = {};
  bool real = V1.empty();
  ASSERT_EQ(real, 1);
}

TEST(vector_empty, test2) {
  vector<int> V1(5);
  bool real = V1.empty();
  ASSERT_EQ(real, 0);
}

TEST(vector_empty, test3) {
  vector<int> V1;
  bool real = V1.empty();
  ASSERT_EQ(real, 1);
}

TEST(vector_size, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  int size1 = V1.size();
  int size2 = V2.size();
  ASSERT_EQ(size1, size2);
}

TEST(vector_max_size, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  int msize1 = V1.max_size();
  int msize2 = V2.max_size();
  ASSERT_EQ(msize1, msize2);
}

TEST(vector_reserve, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  V1.reserve(10);
  V2.reserve(10);
  int cap1 = V1.capacity();
  int cap2 = V2.capacity();
  ASSERT_EQ(cap1, cap2);
}

TEST(vector_capacity, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  int cap1 = V1.capacity();
  int cap2 = V2.capacity();
  ASSERT_EQ(cap1, cap2);
}

TEST(vector_shrink, test1) {
  vector<int> V1 = {4, 5, 6, 19, 201};
  std::vector<int> V2 = {4, 5, 6, 19, 201};
  V1.shrink_to_fit();
  V2.shrink_to_fit();
  int cap1 = V1.capacity();
  int cap2 = V2.capacity();
  ASSERT_EQ(cap1, cap2);
}

TEST(vector_clear, test1) {
  vector<int> V1 = {3, 4, 19, 18};
  V1.clear();
  ASSERT_EQ(V1.empty(), 1);
  ASSERT_EQ(V1.size(), 0);
  ASSERT_EQ(V1.capacity(), 4);
}

TEST(vector_insert, test1) {
  vector<int> V1 = {3, 4, 5, 8, 9, 10, 11};
  std::vector<int> V2 = {3, 4, 5, 8, 9, 10, 11};
  auto it = V1.begin();
  it = it + 5;
  V1.insert(it, 201);
  auto it2 = V2.begin();
  it2 = it2 + 5;
  V2.insert(it2, 201);
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
  }
}

TEST(vector_erase, test1) {
  vector<int> V1 = {3, 4, 5, 8, 9, 10, 11};
  std::vector<int> V2 = {3, 4, 5, 8, 9, 10, 11};
  auto it = V1.begin();
  it = it + 5;
  V1.erase(it);
  auto it2 = V2.begin();
  it2 = it2 + 5;
  V2.erase(it2);
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
  }
}

TEST(vector_push_back, test1) {
  vector<int> V1 = {3, 4, 5, 8, 9, 10, 11};
  std::vector<int> V2 = {3, 4, 5, 8, 9, 10, 11};
  V1.push_back(300);
  V2.push_back(300);
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
  }
}

TEST(vector_pop_back, test1) {
  vector<int> V1 = {3, 4, 5, 8, 9, 10, 11};
  std::vector<int> V2 = {3, 4, 5, 8, 9, 10, 11};
  V1.pop_back();
  V2.pop_back();
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
  }
}

TEST(vector_swap, test1) {
  vector<int> V1 = {3, 4, 5, 6, 7};
  vector<int> V2 = {10, 9, 8, 7};
  V1.swap(V2);
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), 10 - i);
  }
  for (int i = 0; i < (int)V2.size(); i++) {
    ASSERT_EQ(V2.at(i), 3 + i);
  }
}

TEST(vector_insert_many, test1) {
  vector<int> V1 = {3, 4, 5, 6, 7};
  vector<int> V2 = {3, 7};
  auto it = V2.begin();
  it++;
  V2.insert_many(it, 4, 5, 6);
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
  }
  ASSERT_EQ(V1.size(), V2.size());
}

TEST(vector_insert_many_back, test1) {
  vector<int> V1 = {3, 7, 4, 5, 6};
  vector<int> V2 = {3, 7};
  V2.insert_many_back(4, 5, 6);
  for (int i = 0; i < (int)V1.size(); i++) {
    ASSERT_EQ(V1.at(i), V2.at(i));
  }
  ASSERT_EQ(V1.size(), V2.size());
}
