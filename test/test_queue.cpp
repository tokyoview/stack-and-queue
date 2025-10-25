#include <gtest.h>
#include "TQueue.h"
#include <stdexcept>

// Тест конструктора по умолчанию
TEST(TQueueTest, DefaultConstructor) {
    TQueue<int> queue;
    EXPECT_TRUE(queue.IsEmpty());
}

// Тест конструктора с размером
TEST(TQueueTest, SizeConstructor) {
    TQueue<int> queue(5);
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_FALSE(queue.IsFull());
}

// Тест конструктора с невалидным размером
TEST(TQueueTest, InvalidSizeConstructor) {
    EXPECT_THROW(TQueue<int> queue(0), const char*);
    EXPECT_THROW(TQueue<int> queue(-1), const char*);
}

// Тест копирующего конструктора
TEST(TQueueTest, CopyConstructor) {
    TQueue<int> queue1(3);
    queue1.Put(1);
    queue1.Put(2);
    
    TQueue<int> queue2(queue1);
    EXPECT_FALSE(queue2.IsEmpty());
    
    // Проверяем, что данные скопировались
    EXPECT_EQ(queue1.Get(), 1);
    EXPECT_EQ(queue2.Get(), 1);
    EXPECT_EQ(queue1.Get(), 2);
    EXPECT_EQ(queue2.Get(), 2);
}

// Тест перемещающего конструктора
TEST(TQueueTest, MoveConstructor) {
    TQueue<int> queue1(3);
    queue1.Put(1);
    queue1.Put(2);
    
    TQueue<int> queue2(std::move(queue1));
    EXPECT_FALSE(queue2.IsEmpty());
    EXPECT_TRUE(queue1.IsEmpty()); // Источник должен быть пустым после перемещения
    
    EXPECT_EQ(queue2.Get(), 1);
    EXPECT_EQ(queue2.Get(), 2);
}

// Тест оператора присваивания
TEST(TQueueTest, AssignmentOperator) {
    TQueue<int> queue1(3);
    queue1.Put(1);
    queue1.Put(2);
    
    TQueue<int> queue2(2);
    queue2 = queue1;
    
    EXPECT_FALSE(queue2.IsEmpty());
    EXPECT_EQ(queue2.Get(), 1);
    EXPECT_EQ(queue2.Get(), 2);
}

// Тест присваивания пустой очереди
TEST(TQueueTest, AssignmentEmptyQueue) {
    TQueue<int> queue1;
    TQueue<int> queue2(3);
    
    EXPECT_THROW(queue2 = queue1, const char*);
}

// Тест операторов сравнения
TEST(TQueueTest, ComparisonOperators) {
    TQueue<int> queue1(3);
    queue1.Put(1);
    queue1.Put(2);
    
    TQueue<int> queue2(3);
    queue2.Put(1);
    queue2.Put(2);
    
    TQueue<int> queue3(3);
    queue3.Put(3);
    queue3.Put(4);
    
    EXPECT_TRUE(queue1 == queue2);
    EXPECT_FALSE(queue1 == queue3);
    EXPECT_TRUE(queue1 != queue3);
    EXPECT_FALSE(queue1 != queue2);
}

// Тест сравнения с собой
TEST(TQueueTest, SelfComparison) {
    TQueue<int> queue(3);
    queue.Put(1);
    
    EXPECT_THROW(queue == queue, const char*);
}

// Тест добавления и извлечения элементов
TEST(TQueueTest, PutAndGet) {
    TQueue<int> queue(3);
    
    queue.Put(10);
    queue.Put(20);
    queue.Put(30);
    
    EXPECT_TRUE(queue.IsFull());
    
    EXPECT_EQ(queue.Get(), 10);
    EXPECT_EQ(queue.Get(), 20);
    EXPECT_EQ(queue.Get(), 30);
    
    EXPECT_TRUE(queue.IsEmpty());
}

// Тест переполнения
TEST(TQueueTest, Overflow) {
    TQueue<int> queue(2);
    queue.Put(1);
    queue.Put(2);
    
    EXPECT_THROW(queue.Put(3), const char*);
}

// Тест извлечения из пустой очереди
TEST(TQueueTest, GetFromEmpty) {
    TQueue<int> queue(3);
    EXPECT_THROW(queue.Get(), const char*);
    
    queue.Put(1);
    queue.Get();
    EXPECT_THROW(queue.Get(), const char*);
}

// Тест реконфигурации
TEST(TQueueTest, Reconfiguration) {
    TQueue<int> queue(3);
    queue.Put(1);
    queue.Put(2);
    queue.Put(3);
    
    // Извлекаем один элемент, чтобы освободить место в начале
    EXPECT_EQ(queue.Get(), 1);
    
    // Теперь должно быть место для добавления
    queue.Put(4);
    
    EXPECT_EQ(queue.Get(), 2);
    EXPECT_EQ(queue.Get(), 3);
    EXPECT_EQ(queue.Get(), 4);
}

// Тест поиска минимального элемента
TEST(TQueueTest, MinElement) {
    TQueue<int> queue(5);
    queue.Put(5);
    queue.Put(2);
    queue.Put(8);
    queue.Put(1);
    queue.Put(4);
    
    EXPECT_EQ(queue.MinElement(), 1);
    
    // После извлечения минимальный элемент должен измениться
    queue.Get(); // извлекаем 5
    queue.Get(); // извлекаем 2
    EXPECT_EQ(queue.MinElement(), 1);
    
    queue.Get(); // извлекаем 8
    queue.Get(); // извлекаем 1
    EXPECT_EQ(queue.MinElement(), 4);
}

// Тест минимального элемента в пустой очереди
TEST(TQueueTest, MinElementEmpty) {
    TQueue<int> queue(3);
    EXPECT_THROW(queue.MinElement(), const char*);
}

// Тест вывода в поток
TEST(TQueueTest, OutputStream) {
    TQueue<int> queue(3);
    queue.Put(1);
    queue.Put(2);
    
    testing::internal::CaptureStdout();
    std::cout << queue;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Size of queue: 3") != std::string::npos);
    EXPECT_TRUE(output.find("Start: 0") != std::string::npos);
    EXPECT_TRUE(output.find("End: 2") != std::string::npos);
    EXPECT_TRUE(output.find("1\t2\t") != std::string::npos);
}

// Тест вывода пустой очереди
TEST(TQueueTest, OutputStreamEmpty) {
    TQueue<int> queue;
    
    testing::internal::CaptureStdout();
    std::cout << queue;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("nothing to print") != std::string::npos);
}