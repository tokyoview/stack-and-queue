#pragma once
#include <iostream>
#include "TStack.h"

template <typename T>
class TMultiStack
{
private:
  size_t len;
  size_t stackCount;
  T** data;
  TStack<T>* stacks;

public:
  TMultiStack();
  TMultiStack(int len_, int stackCount_);
  TMultiStack(const TMultiStack<T>& other);
  TMultiStack(TMultiStack<T>&& other);
  ~TMultiStack();

  TMultiStack<T>& operator=(const TMultiStack<T>& other);
  bool operator==(const TMultiStack<T>& other);
  bool operator!=(const TMultiStack<T>& other);
  void Push(int ind, T value);
  void Pop(int ind);
  T Get(int ind);
  bool IsEmpty(int ind);
  bool IsFull(int ind);

  template<typename O>
  friend std::ostream& operator<<(std::ostream& os, const TMultiStack<O>& q);
};

template<typename T>
inline TMultiStack<T>::TMultiStack()
{
  len = 0;
  stackCount = 0;
  data = nullptr;
  stacks = nullptr;
}

template<typename T>
inline TMultiStack<T>::TMultiStack(int len_, int stackCount_)
{
  stackCount = stackCount_;
  len = len_;
  data = new T*[len];
  stacks = new TStack<T>[stackCount];
  
}

template<typename T>
inline TMultiStack<T>::TMultiStack(const TMultiStack<T>& other)
{
  len = other.len;
  stackCount = other.stackCount;
  data = new T*[len];
  for (int i = 0; i < len; ++i)
    data[i] = T(*(other.data[i]));
  stacks = new TStack<T>[stackCount];
  int sz = 0;
  for (int i = 0; i < stackCount; ++i)
  {
    int temp = other.stacks[i].GetCapacity();
    stacks[i].SetData(data+sz);
    sz += temp;
  }
}

template<typename T>
inline TMultiStack<T>::TMultiStack(TMultiStack<T>&& other)
{
  len = other.len;
  stackCount = other.stackCount;
  data = other.data;
  stacks = other.stacks;
  other.capacity = 0;
  other.end = 0;
  other.data = nullptr;
  other.stacks = nullptr;
}

template<typename T>
inline TMultiStack<T>::~TMultiStack()
{
  if (stacks != nullptr)
    delete stacks;
  if (data != nullptr)
  {
    for (int i = 0; i < len; ++i)
      delete data[i];
    delete data;
  }
}

template<typename T>
inline TMultiStack<T>& TMultiStack<T>::operator=(const TMultiStack<T>& other)
{
  if (other.IsEmpty()) 
    throw "nothing to copy";

  capacity = other.capacity;
  end = other.end;

  if (data != nullptr) delete data;
  data = new T[capacity];
  for (int i = 0; i < end; ++i)
    data[i] = other.data[i];

  return *this;
}

template<typename T>
inline bool TMultiStack<T>::operator==(const TMultiStack<T>& other)
{
  if (this == &other)
    throw "self";
  if ((len != other.len) 
      || (stackCount != other.stackCount))
    return false;
  bool flag = true;
  for (int i = 0; i < stackCount; ++i)
    if (stacks[i] != other.stacks[i])
    {
      flag = false;
      break;
    }
  return flag;
}

template<typename T>
inline bool TMultiStack<T>::operator!=(const TMultiStack<T>& other)
{
  return !((*this) == other);
}

template<typename T>
inline void TMultiStack<T>::Push(int ind, T value)
{
  if ((ind < 0) || (ind > stackCount))
    throw "bleh";
  stacks[ind].Push(value);
}

template<typename T>
inline void TMultiStack<T>::Pop(int ind)
{
  if ((ind < 0) || (ind > stackCount))
    throw "bleh";
  stacks[ind].Pop();
}

template<typename T>
inline T TMultiStack<T>::Get(int ind)
{
  if ((ind < 0) || (ind > stackCount))
    throw "bleh";
  return stacks[ind].Get();
}

template<typename T>
inline bool TMultiStack<T>::IsEmpty(int ind)
{
  if ((ind < 0) || (ind > stackCount))
    throw "bleh";
  return stacks[ind].IsEmpty();
}

template<typename T>
inline bool TMultiStack<T>::IsFull(int ind)
{
  if ((ind < 0) || (ind > stackCount))
    throw "bleh2";
  return stacks[ind].IsFull();
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const TMultiStack<T>& q)
{
  using std::endl;
  os << "Number of stacks: " << q.stackCount << endl;
  for (int i  = 0; i < q.stackCount; ++i)
    os << q.stacks[i] << "\t";
  os << endl;
  return os;
}