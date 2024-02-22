#include <gtest/gtest.h>

#include <iostream>
#include <stack>
#include <vector>

#include "s21_containers.h"

using s21::stack;

TEST(create_stack, test1) {
  stack<int> S1;
  std::stack<int> S2;
  S1.push(10);
  S2.push(10);
  ASSERT_EQ(S1.top(), S2.top());
}

TEST(create_stack, test2) {
  stack<int> S1 = {20, 18, 2132};
  std::stack<int> S2;
  for (auto& item : {20, 18, 2132}) {
    S2.push(item);
  }
  ASSERT_EQ(S1.top(), S2.top());
}

TEST(stack_copy, test1) {
  stack<int> S1{20, 18, 2132};
  stack<int> S2(S1);

  ASSERT_EQ(S1.top(), S2.top());
  ASSERT_NE(&S1.top(), &S2.top());
  S1.pop();
  S2.pop();
  ASSERT_EQ(S1.top(), S2.top());
  ASSERT_NE(&S1.top(), &S2.top());
  S1.pop();
  S2.pop();
  ASSERT_EQ(S1.top(), S2.top());
  ASSERT_NE(&S1.top(), &S2.top());
  S1.pop();
  S2.pop();

  ASSERT_TRUE(S1.empty());
  ASSERT_TRUE(S2.empty());
}

TEST(stack, copy_assignment) {
  stack<int> S1{20, 18, 2132};
  stack<int> S2;

  S2 = S1;

  ASSERT_EQ(S1.top(), S2.top());
  ASSERT_NE(&S1.top(), &S2.top());
  S1.pop();
  S2.pop();
  ASSERT_EQ(S1.top(), S2.top());
  ASSERT_NE(&S1.top(), &S2.top());
  S1.pop();
  S2.pop();
  ASSERT_EQ(S1.top(), S2.top());
  ASSERT_NE(&S1.top(), &S2.top());
  S1.pop();
  S2.pop();

  ASSERT_TRUE(S1.empty());
  ASSERT_TRUE(S2.empty());
}

TEST(stack_move, test1) {
  stack<int> S1 = {20, 18, 2132};
  stack<int> S2 = std::move(S1);

  EXPECT_TRUE(S1.empty());

  ASSERT_EQ(2132, S2.top());
  S2.pop();
  ASSERT_EQ(18, S2.top());
  S2.pop();
  ASSERT_EQ(20, S2.top());
  S2.pop();
  ASSERT_TRUE(S2.empty());
}

TEST(stack, move_assignment) {
  stack<int> S1 = {20, 18, 2132};
  stack<int> S2;
  S2 = std::move(S1);

  EXPECT_TRUE(S1.empty());

  ASSERT_EQ(2132, S2.top());
  S2.pop();
  ASSERT_EQ(18, S2.top());
  S2.pop();
  ASSERT_EQ(20, S2.top());
  S2.pop();
  ASSERT_TRUE(S2.empty());
}

TEST(stack_copy, test2) {
  stack<int> S1 = {20, 18, 2132};
  stack<int> S2 = S1;
  ASSERT_EQ(2132, S1.top());
  ASSERT_EQ(2132, S2.top());
}

TEST(stack_top, test1) {
  stack<int> S1 = {20, 18, 2132};
  std::stack<int> S2;
  for (auto& item : {20, 18, 2132}) {
    S2.push(item);
  }
  ASSERT_EQ(S1.top(), S2.top());
}

TEST(stack_empty, test1) {
  stack<int> S1;
  int e = S1.empty();
  ASSERT_EQ(e, 1);
}

TEST(stack_empty, test2) {
  stack<int> S1 = {20, 18, 2132};
  int e = S1.empty();
  ASSERT_EQ(e, 0);
}

TEST(stack_size, test1) {
  stack<int> S1 = {20, 18, 2132, 8, 19};
  size_t s = S1.size();
  ASSERT_EQ(s, 5);
}

TEST(stack_push, test1) {
  stack<int> S1 = {20, 18, 2132, 8, 19};
  S1.push(199);
  ASSERT_EQ(S1.top(), 199);
}

TEST(stack_pop, test1) {
  stack<int> S1 = {20, 18, 2132, 8, 19};
  S1.pop();
  ASSERT_EQ(S1.top(), 8);
}

TEST(stack_swap, test1) {
  stack<int> S1 = {19, 20, 21};
  stack<int> S2 = {5, 4, 3, 2};
  S1.swap(S2);
  ASSERT_EQ(S1.top(), 2);
  ASSERT_EQ(S2.top(), 21);
}

TEST(stack_insert_many_front, test1) {
  stack<int> S1 = {19, 20, 21, 542};
  stack<int> S2 = {19};
  S2.insert_many_front(20, 21, 542);
  ASSERT_EQ(S1.top(), S2.top());
  S1.pop();
  S2.pop();
  ASSERT_EQ(S1.top(), S2.top());
  S1.pop();
  S2.pop();
  ASSERT_EQ(S1.top(), S2.top());
  S1.pop();
  S2.pop();
  ASSERT_EQ(S1.top(), S2.top());
}
