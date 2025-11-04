#include <iostream>
#include "TQueue.h"
#include "TStack.h"

int main()
{
  using std::cout, std::endl;
  /* TQueue<double> aboba(5);
  cout << bool(aboba.IsEmpty()) << endl;
  for (int i = 0; i < 5; ++i)
  {
    aboba.Put(i+1);
  }  
  cout << aboba << endl;
  aboba.Get();
  aboba.Get();
  cout << aboba << endl;
  aboba.Put(24);
  aboba.Put(1000);
  cout << aboba << endl;
  cout << aboba.MinElement() << endl;
  cout << bool(aboba.IsFull()) << endl; */
  TStack<double> aboba(5);
  cout << bool(aboba.IsEmpty()) << endl;
  for (int i = 0; i < 5; ++i)
  {
    aboba.Push(i+1);
  }  
  cout << aboba << endl;
  aboba.Get();
  aboba.Get();
  aboba.Pop();
  aboba.Pop();
  cout << aboba << endl;
  aboba.Push(24);
  aboba.Push(1000);
  cout << aboba << endl;
  cout << aboba.MinElement() << endl;
  cout << bool(aboba.IsFull()) << endl;
  return 0;
}