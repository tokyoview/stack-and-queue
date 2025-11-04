#include <gtest.h>
#include "TStack.h"
#include <stdexcept>

// Тест конструктора по умолчанию
TEST(TStackTest, DefaultConstructor) {
    TStack<int> stack;
    EXPECT_TRUE(stack.IsEmpty());
}

// Тест конструктора с размером
TEST(TStackTest, SizeConstructor) {
    TStack<int> stack(5);
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_FALSE(stack.IsFull());
}

// Тест конструктора с невалидным размером
TEST(TStackTest, InvalidSizeConstructor) {
    EXPECT_THROW(TStack<int> stack(0), const char*);
    EXPECT_THROW(TStack<int> stack(-1), const char*);
}

// Тест копирующего конструктора
TEST(TStackTest, CopyConstructor) {
    TStack<int> stack1(3);
    stack1.Push(1);
    stack1.Push(2);
    
    TStack<int> stack2(stack1);
    EXPECT_FALSE(stack2.IsEmpty());
    
    // Проверяем, что данные скопировались
    EXPECT_EQ(stack1.Get(), 2);
    EXPECT_EQ(stack2.Get(), 2);
}

// Тест перемещающего конструктора
TEST(TStackTest, MoveConstructor) {
    TStack<int> stack1(3);
    stack1.Push(1);
    stack1.Push(2);
    
    TStack<int> stack2(std::move(stack1));
    EXPECT_FALSE(stack2.IsEmpty());
    EXPECT_TRUE(stack1.IsEmpty()); // Источник должен быть пустым после перемещения
    
    EXPECT_EQ(stack2.Get(), 2);
    stack2.Pop();
    EXPECT_EQ(stack2.Get(), 1);
}

// Тест оператора присваивания
TEST(TStackTest, AssignmentOperator) {
    TStack<int> stack1(3);
    stack1.Push(1);
    stack1.Push(2);
    
    TStack<int> stack2(2);
    stack2 = stack1;
    
    EXPECT_FALSE(stack2.IsEmpty());
    EXPECT_EQ(stack2.Get(), 2);
    stack2.Pop();
    EXPECT_EQ(stack2.Get(), 1);
}

// Тест присваивания пустого стека
TEST(TStackTest, AssignmentEmptyStack) {
    TStack<int> stack1;
    TStack<int> stack2(3);
    
    EXPECT_THROW(stack2 = stack1, const char*);
}

// Тест операторов сравнения
TEST(TStackTest, ComparisonOperators) {
    TStack<int> stack1(3);
    stack1.Push(1);
    stack1.Push(2);
    
    TStack<int> stack2(3);
    stack2.Push(1);
    stack2.Push(2);
    
    TStack<int> stack3(3);
    stack3.Push(3);
    stack3.Push(4);
    
    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_TRUE(stack1 != stack3);
    EXPECT_FALSE(stack1 != stack2);
}

// Тест сравнения с собой
TEST(TStackTest, SelfComparison) {
    TStack<int> stack(3);
    stack.Push(1);
    
    EXPECT_THROW(stack == stack, const char*);
}

// Тест добавления и извлечения элементов
TEST(TStackTest, PushAndGetAndPop) {
    TStack<int> stack(3);
    
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    
    EXPECT_TRUE(stack.IsFull());
    
    EXPECT_EQ(stack.Get(), 30);
    stack.Pop();
    EXPECT_EQ(stack.Get(), 20);
    stack.Pop();
    EXPECT_EQ(stack.Get(), 10);
    stack.Pop();
    
    EXPECT_TRUE(stack.IsEmpty());
}

// Тест переполнения
TEST(TStackTest, Overflow) {
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);
    
    EXPECT_THROW(stack.Push(3), const char*);
}

// Тест извлечения из пустого стека
TEST(TStackTest, GetFromEmpty) {
    TStack<int> stack(3);
    EXPECT_THROW(stack.Get(), const char*);
    
    stack.Push(1);
    stack.Get();
    stack.Pop();
    EXPECT_THROW(stack.Get(), const char*);
}

// Тест метода Pop на пустом стеке
TEST(TStackTest, PopFromEmpty) {
    TStack<int> stack(3);
    // Pop не должен бросать исключение на пустом стеке
    EXPECT_NO_THROW(stack.Pop());
    
    stack.Push(1);
    stack.Pop();
    EXPECT_NO_THROW(stack.Pop()); // Повторный Pop на пустом стеке
}

// Тест поиска минимального элемента
TEST(TStackTest, MinElement) {
    TStack<int> stack(5);
    stack.Push(5);
    stack.Push(2);
    stack.Push(8);
    stack.Push(1);
    stack.Push(4);
    
    EXPECT_EQ(stack.MinElement(), 1);
    
    // После извлечения минимальный элемент должен измениться
    stack.Pop(); // извлекаем 4
    EXPECT_EQ(stack.MinElement(), 1);
    
    stack.Pop(); // извлекаем 1
    EXPECT_EQ(stack.MinElement(), 2);
}

// Тест минимального элемента в пустом стеке
TEST(TStackTest, MinElementEmpty) {
    TStack<int> stack(3);
    EXPECT_THROW(stack.MinElement(), const char*);
}

// Тест метода GetCapacity
TEST(TStackTest, GetCapacity) {
    TStack<int> stack(5);
    EXPECT_EQ(stack.GetCapacity(), 5);
    
    TStack<int> emptyStack;
    EXPECT_EQ(emptyStack.GetCapacity(), 0);
}

// Тест вывода в поток
TEST(TStackTest, OutputStream) {
    TStack<int> stack(3);
    stack.Push(1);
    stack.Push(2);
    
    testing::internal::CaptureStdout();
    std::cout << stack;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Size of stack: 3") != std::string::npos);
    EXPECT_TRUE(output.find("End: 2") != std::string::npos);
    EXPECT_TRUE(output.find("1\t2\t") != std::string::npos);
}

// Тест вывода пустого стека
TEST(TStackTest, OutputStreamEmpty) {
    TStack<int> stack;
    
    testing::internal::CaptureStdout();
    std::cout << stack;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("nothing to print") != std::string::npos);
}

// Тест последовательности операций
TEST(TStackTest, ComplexOperations) {
    TStack<int> stack(4);
    
    stack.Push(10);
    stack.Push(20);
    EXPECT_EQ(20, stack.Get());
    stack.Pop();
    
    stack.Push(30);
    stack.Push(40);
    
    EXPECT_EQ(40, stack.Get());
    stack.Pop();
    EXPECT_EQ(30, stack.Get());
    stack.Pop();
    EXPECT_EQ(10, stack.Get());
    
    EXPECT_FALSE(stack.IsEmpty());
    stack.Pop();
    EXPECT_TRUE(stack.IsEmpty());
}