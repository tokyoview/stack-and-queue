#include <gtest.h>
#include "TMultiStack.h"
#include <stdexcept>
#include <iostream>

// Тест конструктора по умолчанию
TEST(TMultiStackTest, DefaultConstructor) {
    TMultiStack<int> mstack(2,2);
    EXPECT_EQ(mstack.GetCapacity(0), 2);
}

// Тест конструктора с параметрами
TEST(TMultiStackTest, ParameterizedConstructor) {
    TMultiStack<int> mstack(10, 3);
    
    // Проверяем, что все стеки пусты
    for (int i = 0; i < 3; ++i) {
        EXPECT_TRUE(mstack.IsEmpty(i));
        EXPECT_FALSE(mstack.IsFull(i));
    }
}

// Тест конструктора с невалидными параметрами
TEST(TMultiStackTest, InvalidConstructorParameters) {
    EXPECT_THROW(TMultiStack<int> mstack(0, 3), const char*);
    EXPECT_THROW(TMultiStack<int> mstack(10, 0), const char*);
}

// Тест копирующего конструктора
TEST(TMultiStackTest, CopyConstructor) {
    TMultiStack<int> mstack1(5, 2);
    mstack1.Push(0, 10);
    mstack1.Push(0, 20);
    mstack1.Push(1, 30);

    //std::cout << mstack1 << std::endl;
    
    TMultiStack<int> mstack2(mstack1);
    
    //std::cout << mstack2 << std::endl;

    
    EXPECT_EQ(mstack2.Get(0), 20);
    EXPECT_EQ(mstack2.Get(1), 30);
}

// Тест оператора присваивания
TEST(TMultiStackTest, AssignmentOperator) {
    TMultiStack<int> mstack1(5, 2);
    mstack1.Push(0, 10);
    mstack1.Push(0, 20);
    mstack1.Push(1, 30);
    
    TMultiStack<int> mstack2(3, 1);
    mstack2 = mstack1;
    
    // Проверяем, что данные скопировались
    EXPECT_FALSE(mstack2.IsEmpty(0));
    EXPECT_FALSE(mstack2.IsEmpty(1));
    
    EXPECT_EQ(mstack2.Get(0), 20);
    EXPECT_EQ(mstack2.Get(1), 30);
}

// Тест самоприсваивания
TEST(TMultiStackTest, SelfAssignment) {
    TMultiStack<int> mstack(5, 2);
    mstack.Push(0, 10);
    mstack.Push(1, 20);
    
    mstack = mstack;
    
    // Проверяем, что состояние не изменилось
    EXPECT_FALSE(mstack.IsEmpty(0));
    EXPECT_FALSE(mstack.IsEmpty(1));
    EXPECT_EQ(mstack.Get(0), 10);
    EXPECT_EQ(mstack.Get(1), 20);
}

// Тест операторов сравнения
TEST(TMultiStackTest, ComparisonOperators) {
    TMultiStack<int> mstack1(5, 2);
    mstack1.Push(0, 10);
    mstack1.Push(1, 20);
    
    TMultiStack<int> mstack2(5, 2);
    mstack2.Push(0, 10);
    mstack2.Push(1, 20);
    
    TMultiStack<int> mstack3(5, 2);
    mstack3.Push(0, 30);
    mstack3.Push(1, 40);
    
    TMultiStack<int> mstack4(3, 2); // Другой размер
    
    EXPECT_TRUE(mstack1 == mstack2);
    EXPECT_FALSE(mstack1 == mstack3);
    EXPECT_FALSE(mstack1 == mstack4);
    
    EXPECT_TRUE(mstack1 != mstack3);
    EXPECT_FALSE(mstack1 != mstack2);
}

// Тест добавления элементов
TEST(TMultiStackTest, PushAndGet) {
    TMultiStack<int> mstack(5, 3);
    
    mstack.Push(0, 10);
    mstack.Push(0, 20);
    mstack.Push(1, 30);
    mstack.Push(2, 40);
    
    EXPECT_EQ(mstack.Get(0), 20);
    EXPECT_EQ(mstack.Get(1), 30);
    EXPECT_EQ(mstack.Get(2), 40);
    
    EXPECT_FALSE(mstack.IsEmpty(0));
    EXPECT_FALSE(mstack.IsEmpty(1));
    EXPECT_FALSE(mstack.IsEmpty(2));
}

// Тест извлечения элементов
TEST(TMultiStackTest, Pop) {
    TMultiStack<int> mstack(5, 2);
    mstack.Push(0, 10);
    mstack.Push(0, 20);
    mstack.Push(1, 30);
    
    mstack.Pop(0);
    EXPECT_EQ(mstack.Get(0), 10);
    
    mstack.Pop(1);
    EXPECT_TRUE(mstack.IsEmpty(1));
}

// Тест невалидного индекса стека
TEST(TMultiStackTest, InvalidStackIndex) {
    TMultiStack<int> mstack(5, 2);
    
    EXPECT_THROW(mstack.Push(-1, 10), const char*);
    EXPECT_THROW(mstack.Push(2, 10), const char*);
    EXPECT_THROW(mstack.Get(-1), const char*);
    EXPECT_THROW(mstack.Get(2), const char*);
    EXPECT_THROW(mstack.Pop(-1), const char*);
    EXPECT_THROW(mstack.Pop(2), const char*);
    EXPECT_THROW(mstack.IsEmpty(-1), const char*);
    EXPECT_THROW(mstack.IsEmpty(2), const char*);
    EXPECT_THROW(mstack.IsFull(-1), const char*);
    EXPECT_THROW(mstack.IsFull(2), const char*);
}

// Тест переполнения и репака
TEST(TMultiStackTest, OverflowAndRepack) {
    TMultiStack<int> mstack(3, 2);
    
    // Заполняем оба стека
    mstack.Push(0, 1);
    mstack.Push(0, 2);
    mstack.Push(0, 3);
    
    mstack.Push(1, 4);
    mstack.Push(1, 5);
    
    // Проверяем, что стеки полны
    EXPECT_TRUE(mstack.IsFull(0));
    EXPECT_FALSE(mstack.IsFull(1));
    
    // Добавляем элемент в переполненный стек - должен сработать репак
    EXPECT_NO_THROW(mstack.Push(0, 6));
    
    // Проверяем, что элемент добавился
    EXPECT_EQ(mstack.Get(0), 6);
}

// Тест метода GetData
TEST(TMultiStackTest, GetData) {
    TMultiStack<int> mstack(5, 2);
    mstack.Push(0, 10);
    mstack.Push(0, 20);
    
    int* data = mstack.GetData(0);
    EXPECT_NE(data, nullptr);
    
    // Проверяем, что данные доступны для чтения
    EXPECT_EQ(data[0], 10);
    EXPECT_EQ(data[1], 20);
}

// Тест вывода в поток
TEST(TMultiStackTest, OutputStream) {
    TMultiStack<int> mstack(3, 2);
    mstack.Push(0, 10);
    mstack.Push(0, 20);
    mstack.Push(1, 30);
    
    testing::internal::CaptureStdout();
    std::cout << mstack;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Number of stacks: 2") != std::string::npos);
    EXPECT_TRUE(output.find("Stack 0:") != std::string::npos);
    EXPECT_TRUE(output.find("Stack 1:") != std::string::npos);
}

// Тест комплексной последовательности операций
TEST(TMultiStackTest, ComplexOperations) {
    TMultiStack<int> mstack(10, 3);
    
    // Добавляем элементы во все стеки
    for (int i = 0; i < 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            mstack.Push(i, i * 10 + j);
        }
    }
    
    // Проверяем состояние
    for (int i = 0; i < 3; ++i) {
        EXPECT_FALSE(mstack.IsEmpty(i));
        EXPECT_EQ(mstack.Get(i), i * 10 + 3);
    }
    
    // Извлекаем элементы
    for (int i = 0; i < 3; ++i) {
        mstack.Pop(i);
        EXPECT_EQ(mstack.Get(i), i * 10 + 2);
    }
    
    // Копируем и проверяем копию
    TMultiStack<int> copy = mstack;
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(copy.Get(i), mstack.Get(i));
    }
    
    // Проверяем оператор сравнения
    EXPECT_TRUE(copy == mstack);
    
    // Меняем копию и проверяем неравенство
    copy.Push(0, 100);
    EXPECT_TRUE(copy != mstack);
}

// Тест с различными типами данных
TEST(TMultiStackTest, DifferentDataTypes) {
    TMultiStack<double> doubleStack(5, 2);
    doubleStack.Push(0, 1.5);
    doubleStack.Push(1, 2.7);
    
    EXPECT_DOUBLE_EQ(doubleStack.Get(0), 1.5);
    EXPECT_DOUBLE_EQ(doubleStack.Get(1), 2.7);
}