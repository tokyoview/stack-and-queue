#include <iostream>
#include "TQueue.h"
#include "TStack.h"
#include "TMultiStack.h"

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


  /* TStack<double> aboba(5);
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
  cout << bool(aboba.IsFull()) << endl; */

  /* int cap = 5;
  int** dt = new int*[cap];
  //cout << "ok1" << endl;
  for (int i = 0; i < cap; ++i)
  {
    dt[i] = new int[cap];
    for (int j = 0; j < cap; j++)
      dt[i][j] = i+j+1;
  } */

  //cout << "ok2" << endl;

  /* TStack<int> bruh(3);
  bruh.Push(228);
  cout << bruh << endl;
  bruh.SetData(&dt[1]);
  for (int i = 0; i < cap; ++i)
  {
    for (int j = 0; j < cap; j++)
      cout << dt[i][j] << " ";
    cout << endl;
  }
  cout << bruh << endl; */

  TMultiStack<int> aboba(3, 3);
  //cout << aboba << endl;
  //aboba.Pop(2);
  /* aboba.Push(0, 5);
  aboba.Push(0, 6);
  aboba.Push(0, 7); */
  aboba.Push(1, 15);
  aboba.Push(1, 16);
  aboba.Push(1, 17);
  aboba.Push(2, 25);
  aboba.Push(2, 26);
  aboba.Push(2, 27);

  cout << aboba << endl;

  /* TMultiStack<int> bebra = aboba;
  cout << bebra << endl; */
  aboba.Push(1, 3528);
  cout << aboba << endl;

  return 0;
}