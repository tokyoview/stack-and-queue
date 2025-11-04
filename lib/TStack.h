#pragma once
#include <iostream>

template <typename T>
class TStack
{
private:
  size_t capacity;
  size_t end;
  T* data;

public:
  TStack();
  TStack(int size);
  TStack(const TStack<T>& other);
  TStack(TStack<T>&& other);
  ~TStack();

  TStack<T>& operator=(const TStack<T>& other);
  bool operator==(const TStack<T>& other);
  bool operator!=(const TStack<T>& other);
  void Push(T value);
  void Pop();
  T Get();
  bool IsEmpty();
  bool IsFull();
  int GetCapacity();

  T MinElement();

  template<typename O>
  friend std::ostream& operator<<(std::ostream& os, const TStack<O>& q);
};

template<typename T>
inline TStack<T>::TStack()
{
  capacity = 0;
  end = 0;
  data = nullptr;
}

template<typename T>
inline TStack<T>::TStack(int size)
{
  if (size < 1)
    throw "lmao";
  capacity = size;
  end = 0;
  data = new T[capacity]{0};
}

template<typename T>
inline TStack<T>::TStack(const TStack<T>& other)
{
  capacity = other.capacity;
  end = other.end;
  data = new T[capacity];
  for (int i = 0; i < end; ++i)
    data[i] = other.data[i];
}

template<typename T>
inline TStack<T>::TStack(TStack<T>&& other)
{
  capacity = other.capacity;
  end = other.end;
  data = other.data;
  other.capacity = 0;
  other.end = 0;
  other.data = nullptr;
}

template<typename T>
inline TStack<T>::~TStack()
{
  if (data != nullptr)
    delete data;
}

template<typename T>
inline TStack<T>& TStack<T>::operator=(const TStack<T>& other)
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
inline bool TStack<T>::operator==(const TStack<T>& other)
{
  if (this == &other)
    throw "self";
  if (IsEmpty() && other.IsEmpty())
    return true;
  if ((capacity != other.capacity) 
      || (end != other.end))
    return false;
  bool flag = true;
  for (int i = 0; i < end; ++i)
    if (data[i] != other.data[i])
    {
      flag = false;
      break;
    }
  return flag;
}

template<typename T>
inline bool TStack<T>::operator!=(const TStack<T>& other)
{
  return !((*this) == other);
}

template<typename T>
inline void TStack<T>::Push(T value)
{
  if (IsFull())
    throw "retard";
  data[end++] = value;
  //std::cout << "end, val: " << end << "\t" << value << std::endl;
}

template<typename T>
inline void TStack<T>::Pop()
{
  if (IsEmpty())
    return;
  data[end] = 0;
  end--;
}

template<typename T>
inline T TStack<T>::Get()
{
  if (IsEmpty())
    throw "nothing to get here";
  //std::cout << "end, val: " << end << "\t" << data[end-1] << std::endl;
  return data[end-1];
}

template<typename T>
inline bool TStack<T>::IsEmpty()
{
  return (end == 0);
}

template<typename T>
inline bool TStack<T>::IsFull()
{
  return (end == capacity);
}

template<typename T>
inline int TStack<T>::GetCapacity()
{
  return capacity;
}

template<typename T>
inline T TStack<T>::MinElement()
{
  if (IsEmpty())
    throw "silly";
  T mn = 100000;
  for (int i = 0; i < end; ++i)
    if (data[i] < mn) mn = data[i];
  return mn;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const TStack<T>& q)
{
  using std::endl;
  if (q.IsEmpty())
  {
    os << "nothing to print";
    return os;
  }
  os << "Size of stack: " << q.capacity << endl;
  os << "End: " << q.end << endl;
  for (int i  = 0; i < q.end; ++i)
    os << q.data[i] << "\t";
  os << endl;
  return os;
}