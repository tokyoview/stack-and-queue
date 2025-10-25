#pragma once
#include <iostream>

template <typename T>
class TQueue
{
private:
  size_t capacity;
  size_t start;
  size_t end;
  T* data;

public:
  TQueue();
  TQueue(int size);
  TQueue(const TQueue<T>& other);
  TQueue(TQueue<T>&& other);
  ~TQueue();

  TQueue<T>& operator=(const TQueue<T>& other);
  bool operator==(const TQueue<T>& other);
  bool operator!=(const TQueue<T>& other);
  void Put(T value);
  void Reconfigure(size_t old_start, size_t old_end);
  T Get();
  bool IsEmpty();
  bool IsFull();

  T MinElement();

  template<typename O>
  friend std::ostream& operator<<(std::ostream& os, const TQueue<O>& q);
  template<typename I>
  friend std::istream& operator>>(std::istream& is, const TQueue<I>& q);
};

template<typename T>
inline TQueue<T>::TQueue()
{
  capacity = 0;
  start = 0;
  end = 0;
  data = nullptr;
}

template<typename T>
inline TQueue<T>::TQueue(int size)
{
  if (size < 1)
    throw "lmao";
  capacity = size;
  start = 0;
  end = 0;
  data = new T[capacity]{0};
}

template<typename T>
inline TQueue<T>::TQueue(const TQueue<T>& other)
{
  capacity = other.capacity;
  start = other.start;
  end = other.end;
  data = new T[capacity];
  for (int i = start; i < capacity; ++i)
    data[i] = other.data[i];
}

template<typename T>
inline TQueue<T>::TQueue(TQueue<T>&& other)
{
  capacity = other.capacity;
  start = other.start;
  end = other.end;
  data = other.data;
  other.capacity = 0;
  other.start = 0;
  other.end = 0;
  other.data = nullptr;
}

template<typename T>
inline TQueue<T>::~TQueue()
{
  if (data != nullptr)
    delete data;
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(const TQueue<T>& other)
{
  if (other.IsEmpty()) 
    throw "nothing to copy";

  capacity = other.capacity;
  start = other.start;
  end = other.end;

  if (data != nullptr) delete data;
  data = new T[capacity];
  for (int i = start; i < capacity; ++i)
    data[i] = other.data[i];

  return *this;
}

template<typename T>
inline bool TQueue<T>::operator==(const TQueue<T>& other)
{
  if (this == &other)
    throw "self";
  if (IsEmpty() && other.IsEmpty())
    return true;
  if ((capacity != other.capacity) 
      || (start != other.start)
      || (end != other.end))
    return false;
  bool flag = true;
  for (int i = start; i < capacity; ++i)
    if (data[i] != other.data[i])
    {
      flag = false;
      break;
    }
  return flag;
}

template<typename T>
inline bool TQueue<T>::operator!=(const TQueue<T>& other)
{
  return !((*this) == other);
}

template<typename T>
inline void TQueue<T>::Put(T value)
{
  if (IsFull())
    throw "retard";
  if ((end >= capacity) && (start > 0))
    Reconfigure(start, end);
  data[end++] = value;
  //std::cout << "end " << end << std::endl;
}

template<typename T>
inline void TQueue<T>::Reconfigure(size_t old_start, size_t old_end)
{
  start = 0;
  end = old_end - old_start;
  //T* temp = new T[capacity];
  for (int i = 0; i < capacity; ++i)
  {
    T temp = data[old_start+i];
    data[i] = temp;
    data[old_start+i] = 0;
  }
}

template<typename T>
inline T TQueue<T>::Get()
{
  if (IsEmpty())
    throw "nothing to get here";
  T temp = data[start];
  data[start++] = 0;
  //std::cout << "start " << start << std::endl;
  return temp;
}

template<typename T>
inline bool TQueue<T>::IsEmpty()
{
  bool flag = true;
  for (int i = start; i < capacity; ++i)
    if (data[i] != 0)
    {
      flag = false;
      break;
    }
  return flag;
}

template<typename T>
inline bool TQueue<T>::IsFull()
{
  return (start == 0) && (end == capacity) && (start < end);
}

template<typename T>
inline T TQueue<T>::MinElement()
{
  if (IsEmpty())
    throw "silly";
  T mn = 100000;
  for (int i = start; i < capacity; ++i)
    if (data[i] < mn) mn = data[i];
  return mn;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const TQueue<T>& q)
{
  using std::endl;
  if (q.IsEmpty())
  {
    os << "nothing to print";
    return os;
  }
  os << "Size of queue: " << q.capacity << endl;
  os << "Start: " << q.start << endl;
  os << "End: " << q.end << endl;
  for (int i  = q.start; i < q.capacity; ++i)
    os << q.data[i] << "\t";
  os << endl;
  return os;
}

/* template<typename T>
inline std::istream& operator>>(std::istream& is, const TQueue<T>& q)
{
} */