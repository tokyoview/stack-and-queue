#pragma once
#include <iostream>
#include "TStack.h"
#include <algorithm>

template <typename T>
class TMultiStack
{
private:
  size_t len;
  size_t stackCount;
  T** data;
  TStack<T> *stacks;

public:
  TMultiStack();
  TMultiStack(int len_, int stackCount_);
  TMultiStack(const TMultiStack<T> &other);
  TMultiStack(TMultiStack<T> &&other);
  ~TMultiStack();

  TMultiStack<T> &operator=(const TMultiStack<T> &other);
  bool operator==(const TMultiStack<T> &other) const;
  bool operator!=(const TMultiStack<T> &other) const;
  void Push(int ind, T value);
  void Pop(int ind);
  T Get(int ind) const;
  int GetCapacity(int ind);
  bool IsEmpty(int ind) const;
  bool IsFull(int ind) const;
  void Repack(int expandedStack = -1);
  T* GetData(int ind);

  template <typename O>
  friend std::ostream &operator<<(std::ostream &os, const TMultiStack<O> &q);
};

template <typename T>
inline TMultiStack<T>::TMultiStack()
{
  len = 0;
  stackCount = 0;
  data = nullptr;
  stacks = nullptr;
}

template <typename T>
inline TMultiStack<T>::TMultiStack(int len_, int stackCount_)
{
  if ((len_ < 1) || (stackCount_ < 1)) throw "wtf";
  stackCount = stackCount_;
  len = len_;
  data = new T *[stackCount];
  stacks = new TStack<T>[stackCount];
  for (int i = 0; i < stackCount; ++i)
  {
    data[i] = new T[len];
    for (int j = 0; j < len; ++j)
      data[i][j] = 0;
    stacks[i].SetCapacity(len);
    stacks[i].SetData(&data[i]);
  }
}

template<typename T>
inline TMultiStack<T>::TMultiStack(const TMultiStack<T>& other)
{
  len = other.len;
  stackCount = other.stackCount;
  data = new T*[stackCount];

  for (int i = 0; i < stackCount; ++i)
  {
    data[i] = new T[len];
    for (int j = 0; j < len; ++j)
    {
      //std::cout << another[j] << "\t";
      data[i][j] = other.data[i][j];
    }
    //std::cout << std::endl;
  }

  stacks = new TStack<T>[stackCount];
  //u_int8_t sz = 0;
  for (int i = 0; i < stackCount; ++i)
  {
    int temp = other.stacks[i].GetCapacity();
    stacks[i].SetCapacity(temp);
    /* for (int j = 0; j < len; ++j)
      std::cout << data[i][j] << "\t";
    std::cout << std::endl; */
    //std::cout << *((*data)+sz*sizeof(T)) << std::endl;
    //stacks[i].SetData(data+sz*sizeof(T));
    //stacks[i].SetData(&(data[i]));
    //std::cout << stacks[i] << std::endl;
    int aboba = other.stacks[i].GetEnd();
    //std::cout << "ABOBA " << aboba << std::endl;
    int enis = 0;
    T* lol = new T[aboba];
    for (int j = 0; j < aboba; ++j)
    {
      /* lol[enis++] = data[i][j];
      if (enis == aboba) break; */
      lol[j] = data[i][j];
    }
    stacks[i].SetData(&lol);
    //sz += temp;
  }
}

template <typename T>
inline TMultiStack<T>::TMultiStack(TMultiStack<T> &&other)
{
  len = other.len;
  stackCount = other.stackCount;
  data = other.data;
  stacks = other.stacks;
  other.len = 0;
  other.stackCount = 0;
  other.data = nullptr;
  other.stacks = nullptr;
}

template <typename T>
inline TMultiStack<T>::~TMultiStack()
{
  if (data != nullptr)
  {
    for (int i = 0; i < stackCount; ++i)
      delete[] data[i];
    delete[] data;
  }
  if (stacks != nullptr)
    delete[] stacks;
}

template <typename T>
inline TMultiStack<T>& TMultiStack<T>::operator=(const TMultiStack<T> &other)
{
  if (this == &other)
    return *this;

  if (data != nullptr)
  {
    for (int i = 0; i < stackCount; ++i)
      delete[] data[i];
    delete[] data;
  }
  if (stacks != nullptr)
    delete[] stacks;

  len = other.len;
  stackCount = other.stackCount;
  data = new T*[stackCount];

  for (int i = 0; i < stackCount; ++i)
  {
    data[i] = new T[len];
    for (int j = 0; j < len; ++j)
      data[i][j] = other.data[i][j];
  }

  stacks = new TStack<T>[stackCount];

  for (int i = 0; i < stackCount; ++i)
  {
    int temp = other.stacks[i].GetCapacity();
    stacks[i].SetCapacity(temp);

    int enis = 0;
    T* lol = new T[temp];
    for (int j = 0; j < len; ++j)
      lol[enis++] = data[i][j];

    stacks[i].SetData(&lol);
  }

  return *this;
}

template <typename T>
inline bool TMultiStack<T>::operator==(const TMultiStack<T> &other) const
{
  if (this == &other)
    return true;
  if ((len != other.len) || (stackCount != other.stackCount))
    return false;

  for (int i = 0; i < stackCount; ++i)
    if (stacks[i] != other.stacks[i])
      return false;

  return true;
}

template <typename T>
inline bool TMultiStack<T>::operator!=(const TMultiStack<T> &other) const
{
  return !((*this) == other);
}

template <typename T>
inline void TMultiStack<T>::Push(int ind, T value)
{
  if ((ind < 0) || (ind >= stackCount))
  {
    std::cout << "Multi Push" << std::endl;
    throw "Invalid stack index";
  }

  if (stacks[ind].IsFull())
    Repack(ind);

  data[ind][stacks[ind].GetEnd()] = value;
  stacks[ind].Push(value);
}

template <typename T>
inline void TMultiStack<T>::Pop(int ind)
{
  if ((ind < 0) || (ind >= stackCount))
    throw "Invalid stack index";
  stacks[ind].Pop();
}

template <typename T>
inline T TMultiStack<T>::Get(int ind) const
{
  if ((ind < 0) || (ind >= stackCount))
    throw "Invalid stack index";
  return stacks[ind].Get();
}

template <typename T>
inline int TMultiStack<T>::GetCapacity(int ind)
{
  return stacks[ind].GetCapacity();
}

template <typename T>
inline bool TMultiStack<T>::IsEmpty(int ind) const
{
  if ((ind < 0) || (ind >= stackCount))
    throw "Invalid stack index";
  return stacks[ind].IsEmpty();
}

template <typename T>
inline bool TMultiStack<T>::IsFull(int ind) const
{
  if ((ind < 0) || (ind >= stackCount))
    throw "Invalid stack index";
  return stacks[ind].IsFull();
}

template <typename T>
inline T* TMultiStack<T>::GetData(int ind)
{
  return data[ind];
}

template<typename T>
inline void TMultiStack<T>::Repack(int expandedStack)
{
  size_t notFullStackPos = 1;
  for (int i = 0; i < stackCount; ++i)
    if (!IsFull(i) && (i != expandedStack))
    {
      notFullStackPos = i;
      break;
    }
  int nfssz = stacks[notFullStackPos].GetEnd();
  if (notFullStackPos == -1)
    throw "no empty cells";

  //std::cout << "=== Repack started for stack " << expandedStack << " ===" << std::endl;


  /* size_t totalElements = 0;
  for (int i = 0; i < stackCount; ++i) 
    totalElements += stacks[i].GetEnd();

  std::cout << "Total elements: " << totalElements << std::endl; */

  delete[] stacks;

  T** newData = new T*[stackCount];
  size_t* newCapacities = new size_t[stackCount];
  
  for (int i = 0; i < stackCount; ++i) 
  {
    newCapacities[i] = len + (i == notFullStackPos ? -1 : 0) + (i == expandedStack ? 1 : 0);
    newData[i] = new T[newCapacities[i]]();
    //std::cout << "Stack " << i << " new capacity: " << newCapacities[i] << std::endl;
  }

  for (int i = 0; i < stackCount; ++i) 
  {
    int woo = len - newCapacities[i];
    for (int j = 0; j < std::min(len, newCapacities[i]); ++j)
      newData[i][j] = data[i][j];

    if (woo < 0)
      for (int j = 0; j < (-woo - 1); ++j)
        newData[i][j] = 0;
  }

  for (int i = 0; i < stackCount; ++i)
    delete[] data[i];
  delete[] data;

  /* for (int i = 0; i < stackCount; ++i)
  {
    for (int j = 0; j < newCapacities[i]; ++j)
      std::cout << "newData[" << i << "][" << j << "] = " << newData[i][j] << "\t";
    std::cout << std::endl;
  } */

  data = new T*[stackCount];
  stacks = new TStack<T>[stackCount];
  int enis;
  for (int i = 0; i < stackCount; ++i)
  {
    enis = 0;
    T* lol = new T[newCapacities[i]];
    data[i] = new T[newCapacities[i]];
    stacks[i].SetCapacity(newCapacities[i]);
    for (int j = 0; j < newCapacities[i]; ++j)
    {
      data[i][j] = newData[i][j];
      lol[j] = data[i][j];
    }
    stacks[i].SetData(&lol);
    if (i == expandedStack) stacks[i].SetEnd(len); 
    if (i == notFullStackPos) stacks[i].SetEnd(nfssz); 
  }

  //std::cout << "hell yes" << std::endl;
  
  for (int i = 0; i < stackCount; ++i)
      delete[] newData[i];
  delete[] newData;
  delete[] newCapacities;
}
  
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const TMultiStack<T> &q)
{
  using std::endl;
  os << "Number of stacks: " << q.stackCount << endl;
  for (int i = 0; i < q.stackCount; ++i)
  {
    os << "Stack " << i << ": Capacity = " << q.stacks[i].GetCapacity() << "\t";
    os << q.stacks[i] << "\n";
  }
  os << endl;
  return os;
}