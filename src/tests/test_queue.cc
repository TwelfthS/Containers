#include <gtest/gtest.h>

#include <queue>
#include <string>

#include "s21_containers.h"

using s21::queue;

TEST(QueueTest, CopyConstructor) {
  queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  queue<int> q2(q);
  ASSERT_EQ(q2.size(), q.size());

  ASSERT_EQ(q2.front(), 1);
  q2.pop();
  ASSERT_EQ(q2.front(), 2);
  q2.pop();
  ASSERT_EQ(q2.front(), 3);
  q2.pop();

  ASSERT_TRUE(q2.empty());
}

TEST(QueueTest, MoveConstructor) {
  queue<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);

  queue<int> q2(std::move(q1));

  ASSERT_EQ(q2.front(), 1);
  q2.pop();
  ASSERT_EQ(q2.front(), 2);
  q2.pop();
  ASSERT_EQ(q2.front(), 3);
  q2.pop();

  ASSERT_TRUE(q1.empty());
  ASSERT_TRUE(q2.empty());
}

TEST(QueueTest, CopyAssignmentOperator) {
  queue<int> q, q2;
  q.push(1);
  q.push(2);
  q.push(3);

  q2 = q;
  ASSERT_EQ(q2.size(), q.size());

  ASSERT_EQ(q2.front(), 1);
  q2.pop();
  ASSERT_EQ(q2.front(), 2);
  q2.pop();
  ASSERT_EQ(q2.front(), 3);
  q2.pop();

  ASSERT_TRUE(q2.empty());
}

TEST(QueueTest, AssignmentOperatorChain) {
  queue<int> q, q2, q3;
  q.push(1);
  q.push(2);
  q.push(3);

  q3 = q2 = q;
  ASSERT_EQ(q3.size(), q.size());

  ASSERT_EQ(q3.front(), 1);
  q3.pop();
  ASSERT_EQ(q3.front(), 2);
  q3.pop();
  ASSERT_EQ(q3.front(), 3);
  q3.pop();

  ASSERT_TRUE(q3.empty());
}

TEST(QueueTest, MoveAssignmentOperator) {
  queue<int> q1, q2;
  q1.push(1);
  q1.push(2);
  q1.push(3);

  q2 = std::move(q1);

  ASSERT_EQ(q2.front(), 1);
  q2.pop();
  ASSERT_EQ(q2.front(), 2);
  q2.pop();
  ASSERT_EQ(q2.front(), 3);
  q2.pop();

  ASSERT_TRUE(q1.empty());
  ASSERT_TRUE(q2.empty());
}

TEST(QueueTest, Empty) {
  queue<int> q;
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(q.size(), 0);
}

TEST(QueueTest, NotEmpty) {
  queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  ASSERT_FALSE(q.empty());
  ASSERT_EQ(q.size(), 3);
}

TEST(QueueTest, FrontAndPop) {
  queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  ASSERT_EQ(q.front(), 1);
  q.pop();
  ASSERT_EQ(q.front(), 2);
  q.pop();
  ASSERT_EQ(q.front(), 3);
  q.pop();

  ASSERT_TRUE(q.empty());
  ASSERT_EQ(q.size(), 0);
}

TEST(QueueTest, Swap) {
  std::initializer_list<int> q1 = {5, 7};
  std::initializer_list<int> q2 = {1, 2, 3};

  queue<int> s21_q1{q1};
  queue<int> s21_q2{q2};

  s21_q1.swap(s21_q2);

  ASSERT_EQ(s21_q1.size(), 3);
  ASSERT_EQ(s21_q1.front(), 1);
  ASSERT_EQ(s21_q1.back(), 3);

  ASSERT_EQ(s21_q2.size(), 2);
  ASSERT_EQ(s21_q2.front(), 5);
  ASSERT_EQ(s21_q2.back(), 7);
}

TEST(QueueExtraTest, FillAndEmpty) {
  queue<int> q;
  const int kNumber = 10;
  for (int i = 0; i < kNumber; i++) q.push(i);

  ASSERT_EQ(q.size(), kNumber);

  int i = 0;
  while (!q.empty()) {
    ASSERT_EQ(q.front(), i++);
    q.pop();
  }

  ASSERT_TRUE(q.empty());
  ASSERT_EQ(i, kNumber);
}

TEST(QueueExtraTest, QueueOfStrings) {
  queue<std::string> q{"first", "second", "third"};

  ASSERT_EQ(q.size(), 3);
  ASSERT_EQ(q.front(), "first");
}

TEST(QueueIsertManyBack, Test1) {
  queue<int> q;
  q.insert_many_back(1, 2, 3);

  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(q.front(), i);
    q.pop();
  }

  ASSERT_TRUE(q.empty());
}

TEST(QueueIsertManyBack, Test2) {
  queue<int> q{1, 2, 3};
  q.insert_many_back(4);

  for (int i = 1; i <= 4; ++i) {
    ASSERT_EQ(q.front(), i);
    q.pop();
  }

  ASSERT_TRUE(q.empty());
}

TEST(QueueIsertManyBack, Test3) {
  queue<int> q;
  q.insert_many_back(1);
  q.insert_many_back(2, 3);
  q.insert_many_back(4, 5, 6);

  ASSERT_EQ(q.size(), 6);

  for (int i = 1; i <= 6; ++i) {
    ASSERT_EQ(q.front(), i);
    q.pop();
  }

  ASSERT_TRUE(q.empty());
}
